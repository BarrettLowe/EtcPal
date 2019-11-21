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

#include "etcpal/thread.h"
#include <taskLib.h>

bool etcpal_thread_create(etcpal_thread_t* id, const EtcPalThreadParams* params, void (*thread_fn)(void*),
                          void* thread_arg)
{
  /*int taskSpawn(char* name,      // name of new task (stored at pStackBase) //
                int priority,    // priority of new task //
                int options,     // task option word //
                int stackSize,   // size (bytes) of stack needed plus name //
                FUNCPTR entryPt, // entry point of new task //
                int arg1,        // 1st of 10 req'd args to pass to entryPt //
                int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10)   */
  id = taskSpawn(params->thread_name, params->thread_priority, 0, params->stack_size, thread_fn, thread_arg);
  return false;
}

bool etcpal_thread_join(etcpal_thread_t* id)
{
  return false;
}
