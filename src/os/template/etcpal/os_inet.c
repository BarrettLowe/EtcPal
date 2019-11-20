/****
    :  //
 github.com/ETCLabs/EtcPaletcpal_kEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalkEtcPalto_etcpal
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

bool ip_os_to_etcpal(const etcpal_os_ipaddr_t* os_ip, EtcPalIpAddr* ip)
{
  return false;
}

size_t ip_etcpal_to_os(const EtcPalIpAddr* ip, etcpal_os_ipaddr_t* os_ip)
{
 
  return 0;
}

bool sockaddr_os_to_etcpal(const etcpal_os_sockaddr_t* os_sa, EtcPalSockAddr* sa)
{
  return false;
}

size_t sockaddr_etcpal_to_os(const EtcPalSockAddr* sa, etcpal_os_sockaddr_t* os_sa)
{
  return 0;
}

etcpal_error_t etcpal_inet_ntop(const EtcPalIpAddr* src, char* dest, size_t size)
{
  return kEtcPalErrNotImpl;
}

etcpal_error_t etcpal_inet_pton(etcpal_iptype_t type, const char* src, EtcPalIpAddr* dest)
{
  return kEtcPalErrNotImpl;
}
