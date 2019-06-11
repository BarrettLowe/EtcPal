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

#ifndef _LWPA_OS_THREAD_H_
#define _LWPA_OS_THREAD_H_

#include <pthread.h>
#include "lwpa/bool.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LWPA_THREAD_DEFAULT_PRIORITY 0 /* Priority ignored on Linux */
#define LWPA_THREAD_DEFAULT_STACK 0    /* 0 means keep default */
#define LWPA_THREAD_DEFAULT_NAME NULL  /* Name ignored on Linux */

#define LWPA_THREAD_NAME_MAX_LENGTH 0

typedef struct
{
  void (*fn)(void*);
  void* arg;
  pthread_t handle;
} lwpa_thread_t;

bool lwpa_thread_create(lwpa_thread_t* id, const LwpaThreadParams* params, void (*thread_fn)(void*), void* thread_arg);
bool lwpa_thread_stop(lwpa_thread_t* id);
void lwpa_thread_sleep(int sleep_ms);

#ifdef __cplusplus
}
#endif

#endif /* _LWPA_OS_THREAD_H_ */
