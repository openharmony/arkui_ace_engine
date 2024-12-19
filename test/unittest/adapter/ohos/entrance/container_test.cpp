/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ContainerTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
    }
    static void TearDownTestSuite()
    {
        MockContainer::Current()->pipelineContext_ = nullptr;
        NG::MockPipelineContext::TearDown();
    }
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: ContainerTest001
 * @tc.desc: Test autofill interface with native call
 * @tc.type: FUNC
 */
HWTEST_F(ContainerTest, ContainerTest001, TestSize.Level1)
{
    bool isNative = true;
    bool isPopup = false;
    uint32_t autoFillSessionId = 0;
    AceAutoFillType type = AceAutoFillType::ACE_USER_NAME;
    int32_t autoFillRet =
        MockContainer::Current()->RequestAutoFill(nullptr, type, false, isPopup, autoFillSessionId, isNative);
    EXPECT_EQ(autoFillRet, AceAutoFillError::ACE_AUTO_FILL_SUCCESS);

    bool updateRet = MockContainer::Current()->UpdatePopupUIExtension(nullptr, autoFillSessionId, isNative);
    EXPECT_EQ(updateRet, false);

    bool closeRet = MockContainer::Current()->ClosePopupUIExtension(autoFillSessionId);
    EXPECT_EQ(closeRet, false);
}

/**
 * @tc.name: ContainerTest002
 * @tc.desc: Test autofill interface with web call
 * @tc.type: FUNC
 */
HWTEST_F(ContainerTest, ContainerTest002, TestSize.Level1)
{
    bool isNative = false;
    bool isPopup = false;
    uint32_t autoFillSessionId = 0;
    AceAutoFillType type = AceAutoFillType::ACE_USER_NAME;
    int32_t autoFillRet =
        MockContainer::Current()->RequestAutoFill(nullptr, type, false, isPopup, autoFillSessionId, isNative);
    EXPECT_EQ(autoFillRet, AceAutoFillError::ACE_AUTO_FILL_SUCCESS);

    bool updateRet = MockContainer::Current()->UpdatePopupUIExtension(nullptr, autoFillSessionId, isNative);
    EXPECT_EQ(updateRet, false);

    bool closeRet = MockContainer::Current()->ClosePopupUIExtension(autoFillSessionId);
    EXPECT_EQ(closeRet, false);
}
} // namespace OHOS::Ace::NG