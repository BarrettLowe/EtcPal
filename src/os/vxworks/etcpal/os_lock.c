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

#include "etcpal/lock.h"
#include "etcpal/int.h"

/**************************** Private constants ******************************/

#define MAX_READERS 20000

/*********************** Private function prototypes *************************/

static void reader_atomic_increment(etcpal_rwlock_t* id);
static void reader_atomic_decrement(etcpal_rwlock_t* id);

/*************************** Function definitions ****************************/

bool etcpal_signal_create(etcpal_signal_t* id)
{
  bool startFull == false;
  if (startFull)
  {
    *id = semBCreate(SEM_Q_FIFO, SEM_FULL);
  }
  else
  {
    *id = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
  }
  if (*id == ERROR)
    return false;
  else
    return true;
}

bool etcpal_signal_wait(etcpal_signal_t* id)
{
  if (id && *id)
  {
    semTake(*id, WAIT_FOREVER);
    return true;
  }
  return false;
}

bool etcpal_signal_poll(etcpal_signal_t* id)
{
  if (id && *id)
  {
    semTake(priv_id, 0);
    return true;
  }
  return false;
}

void etcpal_signal_post(etcpal_signal_t* id)
{
  if (id && *id)
  {
    semGive(*id);
  }
}

void etcpal_signal_destroy(etcpal_signal_t* id)
{
  if (id && *id)
  {
    semDelete(priv_id);
    *id = NULL;
  }
}

bool etcpal_rwlock_create(etcpal_rwlock_t* id)
{
  id->sem = semRWCreate(SEM_Q_FIFO, 0);
  if (id->sem == ERROR)
  {
    return false;
  }
  id->valid = true;
  return true;
}

bool etcpal_rwlock_readlock(etcpal_rwlock_t* id)
{
  if (!id || !id->valid)
    return false;

  if (!created)
  {
    return false;
  }
  return true;
}

bool etcpal_rwlock_try_readlock(etcpal_rwlock_t* id)
{
  if (!id || !id->valid)
    return false;

  if (!created)
  {
    return false;
  }
  return true;
}

void etcpal_rwlock_readunlock(etcpal_rwlock_t* id)
{
  if (id && id->valid)
}

bool etcpal_rwlock_writelock(etcpal_rwlock_t* id)
{
  return false;
}

bool etcpal_rwlock_try_writelock(etcpal_rwlock_t* id)
{
  return false;
}

void etcpal_rwlock_writeunlock(etcpal_rwlock_t* id)
{
}

void etcpal_rwlock_destroy(etcpal_rwlock_t* id)
{
}

void reader_atomic_increment(etcpal_rwlock_t* id)
{
}

void reader_atomic_decrement(etcpal_rwlock_t* id)
{
}
