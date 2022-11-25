/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "adapter/ohos/test/unittest/mock/common.h"
#include "core/common/anr_thread.h"

using namespace testing::ext;

namespace OHOS::Ace {
class AnrThreadTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void AnrThreadTest::SetUpTestCase() {}

void AnrThreadTest::TearDownTestCase() {}

void AnrThreadTest::SetUp() {}

void AnrThreadTest::TearDown() {}

/**
 * @tc.name: AnrThreadTest_PostTaskToTaskRunner_001
 * @tc.desc: Verify that the asynchronous task is thrown into the specified thread
 * @tc.type: FUNC
 */
HWTEST_F(AnrThreadTest, AnrThreadTest_PostTaskToTaskRunner_001, TestSize.Level1)
{
    auto result = AnrThread::PostTaskToTaskRunner([]() {}, 0);
    EXPECT_TRUE(result);
}
} // namespace OHOS::Ace
