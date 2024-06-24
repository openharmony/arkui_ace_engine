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
    AceForwardCompatibility::ReclaimFileCache(0);
    AceForwardCompatibility::ReclaimFileCache(getpid());
    EXPECT_TRUE(AceForwardCompatibility::IsForceOldPipeline());
    EXPECT_TRUE(AceForwardCompatibility::PipelineChanged());
    EXPECT_STREQ(AceForwardCompatibility::GetAceLibName(), ARKUI_LIB_NAME_COMPATIBLE);
}

/**
 * @tc.name: TestIsForceOldPipeline001
 * @tc.desc: test without TestIsForceOldPipeline
 * @tc.type: FUNC
 */
HWTEST_F(AceForwardCompatibilityTest, TestIsForceOldPipeline001, TestSize.Level1)
{
    AceForwardCompatibility::Init("TestIsForceOldPipeline", 9, false);
    EXPECT_TRUE(AceForwardCompatibility::IsForceOldPipeline());
}

/**
 * @tc.name: TestIsForceOldPipeline002
 * @tc.desc: test without TestIsForceOldPipeline
 * @tc.type: FUNC
 */
HWTEST_F(AceForwardCompatibilityTest, TestIsForceOldPipeline002, TestSize.Level1)
{
    AceForwardCompatibility::Init("TestIsForceOldPipeline", 9, true);
    EXPECT_TRUE(AceForwardCompatibility::IsForceOldPipeline());
}

/**
 * @tc.name: TestIsNewPipeline001
 * @tc.desc: test TestIsNewPipeline
 * @tc.type: FUNC
 */
HWTEST_F(AceForwardCompatibilityTest, TestIsNewPipeline001, TestSize.Level1)
{
    AceForwardCompatibility::Init("TestIsNewPipeline", 10, false);
    EXPECT_FALSE(AceForwardCompatibility::IsNewPipeline());
}

/**
 * @tc.name: TestIsNewPipeline002
 * @tc.desc: test TestIsNewPipeline
 * @tc.type: FUNC
 */
HWTEST_F(AceForwardCompatibilityTest, TestIsNewPipeline002, TestSize.Level1)
{
    AceForwardCompatibility::Init("TestIsForceOldPipeline", 9, true);
    EXPECT_FALSE(AceForwardCompatibility::IsNewPipeline());
}

/**
 * @tc.name: TestIsUseNG001
 * @tc.desc: isNewPipeline_ is true
 * @tc.type: FUNC
 */
HWTEST_F(AceForwardCompatibilityTest, TestIsUseNG001, TestSize.Level1)
{
    AceForwardCompatibility::Init("TestIsUseNG", 10, false);
    EXPECT_TRUE(AceForwardCompatibility::IsUseNG());
}

/**
 * @tc.name: TestIsUseNG002
 * @tc.desc: isNewPipeline_ is false
 * @tc.type: FUNC
 */
HWTEST_F(AceForwardCompatibilityTest, TestIsUseNG002, TestSize.Level1)
{
    AceForwardCompatibility::Init("TestIsForceOldPipeline", 10, true);
    EXPECT_FALSE(AceForwardCompatibility::IsUseNG());
}

/**
 * @tc.name: TestPipelineChanged001
 * @tc.desc: isNewPipeline_ and isNewAppspawn_ is true
 * @tc.type: FUNC
 */
HWTEST_F(AceForwardCompatibilityTest, TestPipelineChanged001, TestSize.Level1)
{
    AceForwardCompatibility::Init("TestPipelineChanged", 9, false);
    EXPECT_TRUE(AceForwardCompatibility::PipelineChanged());
}

/**
 * @tc.name: TestGetAceLibName001
 * @tc.desc: test ARKUI_LIB_NAME_COMPATIBLE
 * @tc.type: FUNC
 */
HWTEST_F(AceForwardCompatibilityTest, TestGetAceLibName001, TestSize.Level1)
{
    AceForwardCompatibility::Init("TestGetAceLibName", 9, false);
    constexpr char aceLibName[] = "libace_compatible.z.so";
    EXPECT_STREQ(AceForwardCompatibility::GetAceLibName(), aceLibName);
}
} // namespace OHOS::ACE
