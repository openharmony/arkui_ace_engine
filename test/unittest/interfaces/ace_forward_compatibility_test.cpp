/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "ace_forward_compatibility.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class AceForwardCompatibilityTest : public testing::Test {};

/**
 * @tc.name: TestWithInit
 * @tc.desc: test without init
 * @tc.type: FUNC
 */
HWTEST_F(AceForwardCompatibilityTest, TestWithInit, TestSize.Level1)
{
    constexpr char ARKUI_LIB_NAME_COMPATIBLE[] = "libace_compatible.z.so";
    AceForwardCompatibility::Init("do not care", 10, false);
    EXPECT_TRUE(AceForwardCompatibility::IsForceOldPipeline());
    EXPECT_TRUE(AceForwardCompatibility::PipelineChanged());
    EXPECT_STREQ(AceForwardCompatibility::GetAceLibName(), ARKUI_LIB_NAME_COMPATIBLE);
}
} // namespace OHOS::ACE
