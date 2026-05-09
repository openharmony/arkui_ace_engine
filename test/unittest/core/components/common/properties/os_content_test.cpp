/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "os_content_test.h"

#include "core/components/common/properties/os_content.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
namespace {
const char* TEST_SCENARIO = "TEST_SCENARIO";
const char* TEST_ACTION_STR = "TEST_ACTION_STR";
const char* TEST_JSON = "TEST_JSON";
} // namespace

HWTEST_F(OsContentTest, OsContentTest_CallSendAction001, TestSize.Level1)
{
    auto result = OsContent::CallSendAction(TEST_SCENARIO, TEST_ACTION_STR, TEST_JSON);
    EXPECT_EQ(result, OsContent::CallSendAction(TEST_SCENARIO, TEST_ACTION_STR, TEST_JSON));
}
} // namespace OHOS::Ace