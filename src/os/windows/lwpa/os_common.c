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

#include "lwpa/common.h"

#include <windows.h>
#include "lwpa/bool.h"
#include "winsock_error.h"

#define LWPA_WINDOWS_TIMER_RESOLUTION 1  // ms

lwpa_error_t lwpa_os_init(lwpa_features_t features)
{
  bool timer_initted = false;

  if (features & LWPA_FEATURE_TIMERS)
  {
    if (TIMERR_NOERROR == timeBeginPeriod(LWPA_WINDOWS_TIMER_RESOLUTION))
      timer_initted = true;
    else
      return kLwpaErrSys;
  }
  if (features & LWPA_FEATURE_SOCKETS)
  {
    WSADATA wsdata;
    WORD wsver = MAKEWORD(2, 2);
    int startup_res = WSAStartup(wsver, &wsdata);
    if (startup_res != 0)
    {
      if (timer_initted)
        timeEndPeriod(LWPA_WINDOWS_TIMER_RESOLUTION);
      return err_winsock_to_lwpa(startup_res);
    }
  }
  return kLwpaErrOk;
}

void lwpa_os_deinit(lwpa_features_t features)
{
  if (features & LWPA_FEATURE_TIMERS)
  {
    timeEndPeriod(LWPA_WINDOWS_TIMER_RESOLUTION);
  }
  if (features & LWPA_FEATURE_SOCKETS)
  {
    WSACleanup();
  }
}
