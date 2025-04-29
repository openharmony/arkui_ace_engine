/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_pattern.h"
#include "ui/base/agingadapation/aging_adapation_dialog_util.h"
#include "ui/view_factory/abstract_view_factory.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Kit;
namespace OHOS::Ace {
class AgingAdapationDialogUtilTest : public testing::Test {
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
 * @tc.name: AgingAdapationDialogUtilTest001
 * @tc.desc: Test ShowLongPressDialog when IconNodeType is SYMBOL
 * @tc.type: Func
 */
HWTEST_F(AgingAdapationDialogUtilTest, AgingAdapationDialogUtilTest001, TestSize.Level1)
{
    const std::string tag = "TEST1";
    const int32_t iconNodeId = 1001;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, iconNodeId, mockPattern);
    ASSERT_NE(frameNode, nullptr);

    std::string message = "Test Message";
    IconNodeType type = IconNodeType::SYMBOL;
    RefPtr<FrameNode> result = AgingAdapationDialogUtil::ShowLongPressDialog(message, iconNodeId, type);
    ASSERT_EQ(result, nullptr);
}

/**
 * @tc.name: AgingAdapationDialogUtilTest002
 * @tc.desc: Test ShowLongPressDialog when IconNodeType is IMAGE
 * @tc.type: Func
 */
HWTEST_F(AgingAdapationDialogUtilTest, AgingAdapationDialogUtilTest002, TestSize.Level1)
{
    const std::string tag = "TEST2";
    const int32_t iconNodeId = 1002;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, iconNodeId, mockPattern);
    ASSERT_NE(frameNode, nullptr);

    std::string message = "Test Message";
    IconNodeType type = IconNodeType::IMAGE;
    RefPtr<FrameNode> result = AgingAdapationDialogUtil::ShowLongPressDialog(message, iconNodeId, type);
    ASSERT_EQ(result, nullptr);
}
} // namespace OHOS::Ace
