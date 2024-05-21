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
#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
} // namespace

class RichEditorStyledStringTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorStyledStringTestNg::SetUp()
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

void RichEditorStyledStringTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorStyledStringTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: StyledString001
 * @tc.desc: Test the styledString with image.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with image
     */
    ImageSpanSize size { .width = 50.0_vp, .height = 50.0_vp };
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(2.0_vp);
    MarginProperty margins;
    margins.SetEdges(CalcLength(10.0));
    PaddingProperty paddings;
    paddings.SetEdges(CalcLength(5.0));
    ImageSpanAttribute attr { .size = size,
        .paddingProp = paddings,
        .marginProp = margins,
        .borderRadius = borderRadius,
        .objectFit = ImageFit::COVER,
        .verticalAlign = VerticalAlign::BOTTOM };
    ImageSpanOptions imageOption { .image = "src/icon-1.png", .imageAttribute = attr };
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);
    /**
     * @tc.steps: step2. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step3. set styledString
     */
    richEditorPattern->SetStyledString(mutableStr);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 1);
    auto child = richEditorPattern->GetChildByIndex(0);
    auto imageNode = AceType::DynamicCast<ImageSpanNode>(child);
    ASSERT_NE(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_EQ(imageLayoutProperty->calcLayoutConstraint_->selfIdealSize, size.GetSize());
    EXPECT_EQ(imageLayoutProperty->GetVerticalAlignValue(), VerticalAlign::BOTTOM);
    EXPECT_EQ(imageLayoutProperty->GetImageFitValue(), ImageFit::COVER);
    auto&& padding = imageLayoutProperty->GetPaddingProperty();
    ASSERT_NE(padding, nullptr);
    EXPECT_EQ(padding->ToString(), paddings.ToString());
    auto imageRenderCtx = imageNode->GetRenderContext();
    ASSERT_NE(imageRenderCtx, nullptr);
    EXPECT_EQ(imageRenderCtx->GetBorderRadius(), borderRadius);
}

/**
 * @tc.name: StyledString002
 * @tc.desc: Test the styledString with image and text.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledString002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with image and text
     */
    ImageSpanOptions imageOption;
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);
    mutableStr->InsertString(0, "text");
    /**
     * @tc.steps: step2. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step3. set styledString
     */
    richEditorPattern->SetStyledString(mutableStr);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 1);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    /**
     * @tc.steps: step5. insert other image
     */
    auto imageSpan = AceType::MakeRefPtr<SpanString>(imageOption);
    mutableStr->AppendSpanString(imageSpan);
    richEditorPattern->SetStyledString(mutableStr);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 2);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
}
} // namespace OHOS::Ace::NG
