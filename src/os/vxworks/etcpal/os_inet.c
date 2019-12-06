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
 * This file is a part of EtcPal. For more information, go to:
 * https://github.com/ETCLabs/EtcPal
 ******************************************************************************/


#include "etcpal/inet.h"
#include "sockLib.h"

bool ip_os_to_etcpal(const etcpal_os_ipaddr_t* os_ip, EtcPalIpAddr* ip)
{
  if (os_ip->sa_family == AF_INET)
  {
    struct sockaddr* sin = (struct sockaddr)os_ip;
    ETCPAL_IP_SET_V4_ADDRESS(ip, ntohl(sin->sa_data));
    return true;
  }
  return false;
}

size_t ip_etcpal_to_os(const EtcPalIpAddr* ip, etcpal_os_ipaddr_t* os_ip)
{
  size_t ret = 0;
  if(ETCPAL_IP_IS_V4(ip))
  {
    struct sockaddr* sin = (struct sockaddr*)os_ip;
    memset(sin, 0, sizeof(struct sockaddr));
    sin->sa_family_t = AF_INET;
    sin->sa_data = htonl(ETCPAL_IP_V4_ADDRESS(ip));
    ret = sizeof(struct sockaddr);
  }
  return 0;
}

bool sockaddr_os_to_etcpal(const etcpal_os_sockaddr_t* os_sa, EtcPalSockAddr* sa)
{
  if (os_ip->sa_family == AF_INET)
  {
    struct sockaddr* sin = (struct sockaddr)os_ip;
    ETCPAL_IP_SET_V4_ADDRESS(ip, ntohl(sin->sa_data));
    return true;
  }
  return false
}

size_t sockaddr_etcpal_to_os(const EtcPalSockAddr* sa, etcpal_os_sockaddr_t* os_sa)
{
  size_t ret = 0;
  if(ETCPAL_IP_IS_V4(ip))
  {
    struct sockaddr* sin = (struct sockaddr*)os_ip;
    memset(sin, 0, sizeof(struct sockaddr));
    sin->sa_family_t = AF_INET;
    sin->sa_data = htonl(ETCPAL_IP_V4_ADDRESS(ip));
    ret = sizeof(struct sockaddr);
  }
  return ret;
}

etcpal_error_t etcpal_inet_ntop(const EtcPalIpAddr* src, char* dest, size_t size)
{
  if (!src || !dest)
    return kEtcPalErrInvalid;

  switch (src->type)
  {
    case kEtcPalIpTypeV4: {
      struct in_addr addr;
      addr.s_addr = htonl(ETCPAL_IP_V4_ADDRESS(src));
      if (NULL != inet_ntop(AF_INET, &addr, dest, size))
        return kEtcPalErrOk;
      return errno_lwip_to_etcpal(errno);
    }
    default:
      return kEtcPalErrInvalid;
  }
}

etcpal_error_t etcpal_inet_pton(etcpal_iptype_t type, const char* src, EtcPalIpAddr* dest)
{
  if (!src || !dest)
    return kEtcPalErrInvalid;

  switch (src->type)
  {
    case kEtcPalIpTypeV4: {
      struct in_addr addr;
      if (inet_pton(AF_INET, src, &addr) <= 0)
        return kEtcPalErrInvalid;
      ETCPAL_IP_SET_V4_ADDRESS(dest, ntohl(addr.s_addr));
      return kEtcPalErrOk;
    }
    default:
     return kEtcPalErrInvalid; 
  }
}
