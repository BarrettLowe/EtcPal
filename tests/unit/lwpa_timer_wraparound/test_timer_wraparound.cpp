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
#include "gtest/gtest.h"
#include "fff.h"

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(uint32_t, lwpa_getms);

class TimerWraparoundTest : public ::testing::Test
{
};

TEST_F(TimerWraparoundTest, wraparound)
{
  LwpaTimer t1;

  // Test the wraparound case by forcing a wraparound value returned from lwpa_getms()
  lwpa_getms_fake.return_val = 0xfffffff0u;
  lwpa_timer_start(&t1, 0x20);

  // We've wrapped around but have not exceeded the interval yet
  lwpa_getms_fake.return_val = 0x0f;
  ASSERT_FALSE(lwpa_timer_is_expired(&t1));
  ASSERT_EQ(lwpa_timer_elapsed(&t1), 0x1fu);

  lwpa_getms_fake.return_val = 0x11;
  ASSERT_TRUE(lwpa_timer_is_expired(&t1));
}
