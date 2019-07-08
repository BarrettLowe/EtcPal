/******************************************************************************
 * Copyright 2019 ETC Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************
 * This file is a part of lwpa. For more information, go to:
 * https://github.com/ETCLabs/lwpa
 ******************************************************************************/

#include "lwpa/netint.h"
#include "lwpa/private/netint.h"

#include <stdlib.h>

/**************************** Private variables ******************************/

static unsigned int init_count;
static CachedNetintInfo netint_cache;
static DefaultNetint default_netint;

/*********************** Private function prototypes *************************/

static int compare_netints(const void* a, const void* b);

/*************************** Function definitions ****************************/

lwpa_error_t lwpa_netint_init()
{
  lwpa_error_t res = kLwpaErrOk;
  if (init_count == 0)
  {
    res = os_enumerate_interfaces(&netint_cache);
    if (res == kLwpaErrOk)
    {
      // Sort the interfaces by OS index
      qsort(netint_cache.netints, netint_cache.num_netints, sizeof(LwpaNetintInfo), compare_netints);

      // Store the locations of the default netints for access by the API function
      for (size_t i = 0; i < netint_cache.num_netints; ++i)
      {
        LwpaNetintInfo* netint = &netint_cache.netints[i];
        if (LWPA_IP_IS_V4(&netint->addr) && netint->is_default)
        {
          default_netint.v4_valid = true;
          default_netint.v4_index = i;
        }
        else if (LWPA_IP_IS_V6(&netint->addr) && netint->is_default)
        {
          default_netint.v6_valid = true;
          default_netint.v6_index = i;
        }
      }
    }
  }

  if (res == kLwpaErrOk)
    ++init_count;

  return res;
}

void lwpa_netint_deinit()
{
  if (--init_count == 0)
  {
    os_free_interfaces(&netint_cache);
    memset(&netint_cache, 0, sizeof(netint_cache));
  }
}

/*! \brief Get the number of network interfaces present on the system.
 *  \return Number of interfaces present.
 */
size_t lwpa_netint_get_num_interfaces()
{
  return (init_count ? netint_cache.num_netints : 0);
}

/*! \brief Enumerate the network interfaces on the system.
 *
 *  For NICs with multiple IP addresses assigned, this module separates each address into its own
 *  entry in the netint array. Because of this, multiple array entries could have the same value
 *  for the index, mac and name parameters.
 *
 *  \param[out] netint_arr Array of network interface description structs to fill in with interface
 *                         info.
 *  \param[in] netint_arr_size Size of the netint array.
 *  \return Number of network interfaces that were enumerated, up to a maximum of netint_arr_size,
 *          or 0 if there are no interfaces present or an error occurred.
 */
size_t lwpa_netint_get_interfaces(LwpaNetintInfo* netint_arr, size_t netint_arr_size)
{
  if (!init_count || !netint_arr || netint_arr_size == 0)
    return 0;

  size_t addrs_copied = (netint_arr_size < netint_cache.num_netints ? netint_arr_size : netint_cache.num_netints);
  memcpy(netint_arr, netint_cache.netints, addrs_copied * sizeof(LwpaNetintInfo));
  return addrs_copied;
}

/*! \brief Get information about the default network interface.
 *
 *  For our purposes, the 'default' network interface is defined as the interface that is chosen
 *  for the default IP route. Note: If the network interfaces have already been enumerated with
 *  lwpa_netint_get_interfaces(), it is more efficient to inspect the is_default flag of each
 *  interface in that existing array.
 *
 *  \param[in] type The IP protocol for which to get the default network interface, either
 *                  #kLwpaIpTypeV4 or #kLwpaIpTypeV6. A separate default interface is maintained for
 *                  each.
 *  \param[out] netint Pointer to network interface description struct to fill with the information
 *                     about the default interface.
 *  \return #kLwpaErrOk: netint was filled in.
 *  \return #kLwpaErrInvalid: Invalid argument provided.
 *  \return #kLwpaErrNotFound: No default interface found for this type.
 */
lwpa_error_t lwpa_netint_get_default_interface(lwpa_iptype_t type, LwpaNetintInfo* netint)
{
  if (init_count && netint)
  {
    if (type == kLwpaIpTypeV4)
    {
      if (default_netint.v4_valid)
      {
        *netint = netint_cache.netints[default_netint.v4_index];
        return kLwpaErrOk;
      }
      else
      {
        return kLwpaErrNotFound;
      }
    }
    else if (type == kLwpaIpTypeV6)
    {
      if (default_netint.v6_valid)
      {
        *netint = netint_cache.netints[default_netint.v6_index];
        return kLwpaErrOk;
      }
      else
      {
        return kLwpaErrNotFound;
      }
    }
  }
  return kLwpaErrInvalid;
}

/*! \brief Get the network interface that the system will choose when routing an IP packet to the
 *         specified destination.
 *
 *  \param[in] dest IP address of the destination.
 *  \param[out] netint Pointer to network interface description struct to fill in with information
 *                     about the chosen interface.
 *  \return #kLwpaErrOk: Netint filled in successfully.
 *  \return #kLwpaErrInvalid: Invalid argument provided.
 *  \return #kLwpaErrNotInit: Module not initialized.
 *  \return #kLwpaErrNoNetints: No network interfaces found on system.
 *  \return #kLwpaErrNotFound: No route was able to be resolved to the destination.
 */
lwpa_error_t lwpa_netint_get_interface_for_dest(const LwpaIpAddr* dest, LwpaNetintInfo* netint)
{
  if (!dest || !netint)
    return kLwpaErrInvalid;
  if (!init_count)
    return kLwpaErrNotInit;
  if (netint_cache.num_netints == 0)
    return kLwpaErrNoNetints;

  unsigned int index;
  lwpa_error_t res = os_resolve_route(dest, &index);
  if (res == kLwpaErrOk)
  {
    for (LwpaNetintInfo* netint_entry = netint_cache.netints;
         netint_entry < netint_cache.netints + netint_cache.num_netints; ++netint_entry)
    {
      if (netint_entry->addr.type == dest->type && netint_entry->index == index)
      {
        *netint = *netint_entry;
        return kLwpaErrOk;
      }
    }
    return kLwpaErrNotFound;
  }
  return res;
}

int compare_netints(const void* a, const void* b)
{
  LwpaNetintInfo* netint1 = (LwpaNetintInfo*)a;
  LwpaNetintInfo* netint2 = (LwpaNetintInfo*)b;

  return (netint1->index > netint2->index) - (netint1->index < netint2->index);
}
