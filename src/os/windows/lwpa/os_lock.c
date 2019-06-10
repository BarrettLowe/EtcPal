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

#include "lwpa/lock.h"
#include "lwpa/int.h"
#include "mmsystem.h"

bool lwpa_mutex_create(lwpa_mutex_t* id)
{
  if (id)
  {
    InitializeCriticalSection(&id->cs);
    id->valid = true;
    return true;
  }
  return false;
}

bool lwpa_mutex_take(lwpa_mutex_t* id)
{
  if (id && id->valid)
  {
    EnterCriticalSection(&id->cs);
    return true;
  }
  return false;
}

bool lwpa_mutex_try_take(lwpa_mutex_t* id)
{
  if (id && id->valid)
  {
    return TryEnterCriticalSection(&id->cs);
  }
  return false;
}

void lwpa_mutex_give(lwpa_mutex_t* id)
{
  if (id && id->valid)
  {
    LeaveCriticalSection(&id->cs);
  }
}

void lwpa_mutex_destroy(lwpa_mutex_t* id)
{
  if (id && id->valid)
  {
    DeleteCriticalSection(&id->cs);
    id->valid = false;
  }
}

bool lwpa_signal_create(lwpa_signal_t* id)
{
  if (id)
  {
    *id = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (*id)
      return true;
  }
  return false;
}

bool lwpa_signal_wait(lwpa_signal_t* id)
{
  if (id)
    return (WAIT_OBJECT_0 == WaitForSingleObject(*id, INFINITE));
  return false;
}

bool lwpa_signal_poll(lwpa_signal_t* id)
{
  if (id)
    return (WAIT_OBJECT_0 == WaitForSingleObject(*id, 0));
  return false;
}

void lwpa_signal_post(lwpa_signal_t* id)
{
  if (id)
    SetEvent(*id);
}

void lwpa_signal_destroy(lwpa_signal_t* id)
{
  if (id)
    CloseHandle(*id);
}

bool lwpa_rwlock_create(lwpa_rwlock_t* id)
{
  if (id)
  {
    InitializeCriticalSection(&id->cs);
    id->valid = true;
    id->reader_count = 0;
    return true;
  }
  return false;
}

bool lwpa_rwlock_readlock(lwpa_rwlock_t* id)
{
  if (id && id->valid)
  {
    EnterCriticalSection(&id->cs);
    InterlockedIncrement(&id->reader_count);  // Add one to the reader count
    LeaveCriticalSection(&id->cs);
    return true;
  }
  return false;
}

void lwpa_rwlock_readunlock(lwpa_rwlock_t* id)
{
  if (id && id->valid)
    InterlockedDecrement(&(idptr)->reader_count);
}

bool lwpa_rwlock_writelock(lwpa_rwlock_t* id)
{
  if (id && id->valid)
  {
    EnterCriticalSection(&id->cs);
    // Wait until there are no readers, keeping the lock so that no new readers can get in.
    while (id->reader_count > 0)
    {
      Sleep(1);
    }
    // Hold on to the lock until writeunlock() is called
    return true;
  }
  return false;
}

void lwpa_rwlock_writeunlock(lwpa_rwlock_t* id)
{
  if (id && id->valid)
    LeaveCriticalSection(&id->cs);
}

void lwpa_rwlock_destroy(lwpa_rwlock_t* id)
{
  if (id && id->valid)
  {
    DeleteCriticalSection(&id->cs);
    id->valid = false;
  }
}
