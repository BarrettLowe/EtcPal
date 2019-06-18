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

#include "lwpa/timer.h"
#include "lwpa/private/timer.h"

#include <windows.h>

#define LWPA_WINDOWS_TIMER_RESOLUTION 1  // ms

lwpa_error_t lwpa_timer_init()
{
  if (TIMERR_NOERROR == timeBeginPeriod(LWPA_WINDOWS_TIMER_RESOLUTION))
    return kLwpaErrOk;
  else
    return kLwpaErrSys;
}

void lwpa_timer_deinit()
{
  timeEndPeriod(LWPA_WINDOWS_TIMER_RESOLUTION);
}

uint32_t lwpa_getms()
{
  return timeGetTime();
}

uint32_t lwpa_timer_remaining(const LwpaTimer* timer)
{
  uint32_t res = 0;
  if (timer->interval != 0)
  {
    uint32_t cur_ms = lwpa_getms();
    if (cur_ms - timer->reset_time < timer->interval)
      res = timer->reset_time + timer->interval - cur_ms;
  }
  return res;
}
