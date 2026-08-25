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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorPlaceholderTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorPlaceholderTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorPlaceholderTestNg::TearDown()
{
    richEditorNode_.Reset();
    MockParagraph::TearDown();
}

void RichEditorPlaceholderTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: SetPlaceholder001
 * @tc.desc: test SetPlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderTestNg, SetPlaceholder001, TestSize.Level0)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create(true);
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorModel.GetRichEditorController();
    EXPECT_NE(richEditorController, nullptr);

    PlaceholderOptions options;
    options.value = std::nullopt;
    richEditorModel.SetPlaceholder(options);
    EXPECT_FALSE(options.value.has_value());

    richEditorModel.SetPlaceholder(richEditorNode, options);
    EXPECT_FALSE(options.fontSize.has_value());
}

/**
 * @tc.name: SetPlaceholder002
 * @tc.desc: Test that calling SetPlaceholder with the same options does not mark dirty on repeated calls
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderTestNg, SetPlaceholder002, TestSize.Level0)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto layoutProperty = richEditorNode->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    PlaceholderOptions options;
    options.value = INIT_VALUE_1;
    options.fontSize = FONT_SIZE_VALUE;
    options.fontStyle = ITALIC_FONT_STYLE_VALUE;
    options.fontWeight = FONT_WEIGHT_VALUE;
    options.fontColor = TEXT_COLOR_VALUE;
    options.fontFamilies = FONT_FAMILY_VALUE;
    richEditorModel.SetPlaceholder(options);

    auto flag = layoutProperty->GetPropertyChangeFlag();
    EXPECT_NE(flag, PROPERTY_UPDATE_NORMAL);

    layoutProperty->CleanDirty();
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), PROPERTY_UPDATE_NORMAL);
    richEditorModel.SetPlaceholder(options);

    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: SetPlaceholder003
 * @tc.desc: Test that calling SetPlaceholder with FrameNode and same options does not mark dirty on repeated calls
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderTestNg, SetPlaceholder003, TestSize.Level0)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto layoutProperty = richEditorNode->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    PlaceholderOptions options;
    options.value = INIT_VALUE_1;
    options.fontSize = FONT_SIZE_VALUE;
    options.fontStyle = ITALIC_FONT_STYLE_VALUE;
    options.fontWeight = FONT_WEIGHT_VALUE;
    options.fontColor = TEXT_COLOR_VALUE;
    options.fontFamilies = FONT_FAMILY_VALUE;
    RichEditorModelNG::SetPlaceholder(richEditorNode, options);

    auto flag = layoutProperty->GetPropertyChangeFlag();
    EXPECT_NE(flag, PROPERTY_UPDATE_NORMAL);

    layoutProperty->CleanDirty();
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), PROPERTY_UPDATE_NORMAL);
    RichEditorModelNG::SetPlaceholder(richEditorNode, options);

    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: SetPlaceholder004
 * @tc.desc: Test that calling SetPlaceholder without fontColor does not mark dirty on repeated calls
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPlaceholderTestNg, SetPlaceholder004, TestSize.Level0)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto layoutProperty = richEditorNode->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    PlaceholderOptions options;
    options.value = INIT_VALUE_1;
    options.fontSize = FONT_SIZE_VALUE;
    options.fontStyle = ITALIC_FONT_STYLE_VALUE;
    options.fontWeight = FONT_WEIGHT_VALUE;
    options.fontFamilies = FONT_FAMILY_VALUE;
    richEditorModel.SetPlaceholder(options);

    auto flag = layoutProperty->GetPropertyChangeFlag();
    EXPECT_NE(flag, PROPERTY_UPDATE_NORMAL);

    layoutProperty->CleanDirty();
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), PROPERTY_UPDATE_NORMAL);
    richEditorModel.SetPlaceholder(options);

    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), PROPERTY_UPDATE_NORMAL);
}
} // namespace OHOS::Ace::NG
