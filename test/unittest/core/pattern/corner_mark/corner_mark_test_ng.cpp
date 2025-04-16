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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/theme/corner_mark_theme.h"
#include "core/components_ng/pattern/corner_mark/corner_mark.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {} // namespace

class CornerMarkTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void CornerMarkTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CornerMarkTheme>()));
}
void CornerMarkTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: ResponseShowCornerMarkEvent
 * @tc.desc: Test ResponseShowCornerMarkEvent function
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, ResponseShowCornerMarkEvent, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    std::string value = "{\"smarap\":{\"cornerMarkIndex\":88,\"showCornerMarkNode\":true}}";
    int32_t result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_FAILED);
    value = "{\"params\":{\"cornerMarkIndex\":true,\"showCornerMarkNode\":true}}";
    result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_FAILED);
    value = "{\"params\":{\"cornerMarkIndex\":88,\"showCornerMarkNode\":99}}";
    result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_FAILED);
    value = "{\"params\":{\"cornerMarkIndex\":88,\"showCornerMarkNode\":true}}";
    result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_SUCCESS);
}

/**
 * @tc.name: AddCornerMarkNode
 * @tc.desc: Test AddCornerMarkNode function
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, AddCornerMarkNode, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    int32_t index = 88;
    int32_t result = cornerMark->AddCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_NE(frameNode->GetCornerMarkNode(), nullptr);
    auto textLayoutProperty = frameNode->GetCornerMarkNode()->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto indexString = textLayoutProperty->GetContent();
    EXPECT_EQ(indexString.has_value(), true);
    if (indexString.has_value()) {
        std::u16string value = u"88";
        EXPECT_EQ(indexString.value(), value);
    }
}

/**
 * @tc.name: UpdateCornerMarkNode
 * @tc.desc: Test UpdateCornerMarkNode function
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, UpdateCornerMarkNode, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    int32_t index = 88;
    int32_t result = cornerMark->UpdateCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_FAILED);
    result = cornerMark->AddCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);
    index = 66;
    result = cornerMark->UpdateCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);
    auto textLayoutProperty = frameNode->GetCornerMarkNode()->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto indexString = textLayoutProperty->GetContent();
    EXPECT_EQ(indexString.has_value(), true);
    if (indexString.has_value()) {
        std::u16string value = u"66";
        EXPECT_EQ(indexString.value(), value);
    }
}

/**
 * @tc.name: RemoveCornerMarkNode
 * @tc.desc: Test RemoveCornerMarkNode function
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, RemoveCornerMarkNode, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    int32_t result = cornerMark->RemoveCornerMarkNode(frameNode);
    EXPECT_EQ(result, RET_FAILED);
    int32_t index = 88;
    result = cornerMark->AddCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);
    result = cornerMark->RemoveCornerMarkNode(frameNode);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_EQ(frameNode->GetCornerMarkNode(), nullptr);
}
} // namespace OHOS::Ace::NG
