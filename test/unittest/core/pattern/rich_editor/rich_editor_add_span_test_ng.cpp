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
#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorAddSpanTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
private:
    void TestMagnifier(const RefPtr<RichEditorPattern>& richEditorPattern,
        const RefPtr<MagnifierController>& controller, const OffsetF& localOffset);
};

void RichEditorAddSpanTestNg::SetUp()
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

void RichEditorAddSpanTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorAddSpanTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: AddImageSpan001
 * @tc.desc: test add image span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddImageSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    ImageSpanAttribute imageStyle;
    AddSpan("test");
    ImageSpanOptions options;
    options.imageAttribute = imageStyle;
    options.image = IMAGE_VALUE;
    options.bundleName = BUNDLE_NAME;
    options.moduleName = MODULE_NAME;
    options.offset = 1;
    auto index1 = richEditorController->AddImageSpan(options);
    EXPECT_EQ(index1, 1);
    options.image = IMAGE_VALUE;
    options.bundleName = BUNDLE_NAME;
    options.moduleName = MODULE_NAME;
    options.offset = 2;
    auto index2 = richEditorController->AddImageSpan(options);
    EXPECT_EQ(index2, 2);

    options.offset = std::nullopt;
    auto index3 = richEditorPattern->AddImageSpan(options, false, 0);
    EXPECT_EQ(index3, 4);

    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    options.imageAttribute = imageStyle;
    auto index4 = richEditorPattern->AddImageSpan(options, false, 0);
    EXPECT_EQ(index4, 5);

    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    options.imageAttribute = imageStyle;
    auto index5 = richEditorPattern->AddImageSpan(options, false, 0);
    EXPECT_EQ(index5, 6);

    marginProp = { ERROR_CALC_LENGTH_CALC, ERROR_CALC_LENGTH_CALC, ERROR_CALC_LENGTH_CALC, ERROR_CALC_LENGTH_CALC };
    borderRadius = { ERROR_CALC_TEST, ERROR_CALC_TEST, ERROR_CALC_TEST, ERROR_CALC_TEST };
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    options.imageAttribute = imageStyle;
    auto index6 = richEditorPattern->AddImageSpan(options, false, -1);
    EXPECT_EQ(index6, 7);
}

/**
 * @tc.name: AddImageSpan002
 * @tc.desc: test add image span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddImageSpan002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern and controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. add span and select text
     */
    AddSpan("test");
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 4);
    richEditorPattern->textSelector_.Update(3, 4);
    EXPECT_TRUE(richEditorPattern->textSelector_.IsValid());

    /**
     * @tc.steps: step3. test AddImageSpan when isPaste is false
     * @tc.expected: textSelector_ is reset
     */
    ImageSpanAttribute imageStyle;
    ImageSpanOptions options;
    options.imageAttribute = imageStyle;
    options.image = IMAGE_VALUE;
    options.bundleName = BUNDLE_NAME;
    options.moduleName = MODULE_NAME;
    options.offset = 1;
    auto index = richEditorPattern->AddImageSpan(options, false, 0, true);
    EXPECT_EQ(index, 1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 2);
    EXPECT_FALSE(richEditorPattern->textSelector_.IsValid());
}

/**
 * @tc.name: AddTextSpan001
 * @tc.desc: test add text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddTextSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetTextColor(TEXT_COLOR_VALUE);
    style.SetFontSize(FONT_SIZE_VALUE);
    style.SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    style.SetFontWeight(FONT_WEIGHT_VALUE);
    style.SetFontFamilies(FONT_FAMILY_VALUE);
    style.SetTextDecoration(TEXT_DECORATION_VALUE);
    style.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    TextSpanOptions options;
    options.offset = 1;
    options.value = INIT_VALUE_1;
    options.style = style;
    auto index1 = richEditorController->AddTextSpan(options);
    EXPECT_EQ(index1, 0);
    auto index2 = richEditorController->AddTextSpan(options);
    EXPECT_EQ(index2, 1);
    options.value = "hello\n";
    auto index3 = richEditorController->AddTextSpan(options);
    EXPECT_EQ(index3, 1);
}

/**
 * @tc.name: AddPlaceholderSpan001
 * @tc.desc: test add builder span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddPlaceholderSpan001, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    RefPtr<GeometryNode> containerGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(containerGeometryNode == nullptr);
    containerGeometryNode->SetFrameSize(SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT));
    ASSERT_NE(richEditorNode_->GetLayoutProperty(), nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(richEditorNode_, containerGeometryNode, richEditorNode_->GetLayoutProperty());

    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));

    auto builderId = ElementRegister::GetInstance()->MakeUniqueId();
    auto builderNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, builderId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto index = richEditorController->AddPlaceholderSpan(builderNode, {});
    EXPECT_EQ(index, 0);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 1);
    auto builderSpanChildren = richEditorNode_->GetChildren();
    ASSERT_NE(static_cast<int32_t>(builderSpanChildren.size()), 0);
    auto builderSpan = builderSpanChildren.begin();
    auto builderSpanChild = AceType::DynamicCast<FrameNode>(*builderSpan);
    ASSERT_NE(builderSpanChild, nullptr);
    EXPECT_EQ(builderSpanChild->GetTag(), V2::PLACEHOLDER_SPAN_ETS_TAG);

    auto richEditorLayoutAlgorithm = richEditorPattern->CreateLayoutAlgorithm();
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(richEditorLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(BUILDER_SIZE);
    RefPtr<GeometryNode> builderGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    builderGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> builderLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        builderSpanChild, builderGeometryNode, builderSpanChild->GetLayoutProperty());
    EXPECT_FALSE(builderLayoutWrapper == nullptr);
    auto builderPattern = builderSpanChild->GetPattern();
    builderLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto firstItemLayoutAlgorithm = builderPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(firstItemLayoutAlgorithm == nullptr);
}

/**
 * @tc.name: AddPlaceholderSpan002
 * @tc.desc: test add builder span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddPlaceholderSpan002, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    AddSpan("test");
    auto builderId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto builderNode1 = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, builderId1, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto index1 = richEditorController->AddPlaceholderSpan(builderNode1, {});
    EXPECT_EQ(index1, 1);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 2);
    auto builderSpanChildren = richEditorNode_->GetChildren();
    ASSERT_NE(static_cast<int32_t>(builderSpanChildren.size()), 0);
    auto builderSpanChild = builderSpanChildren.begin();
    EXPECT_EQ((*builderSpanChild)->GetTag(), "Span");
    ClearSpan();
}

/**
 * @tc.name: AddPlaceholderSpan003
 * @tc.desc: test AddPlaceholderSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddPlaceholderSpan003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create richEditorNode_ and layoutWrapper.
     */
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);

    RefPtr<GeometryNode> containerGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(containerGeometryNode == nullptr);
    containerGeometryNode->SetFrameSize(SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT));
    ASSERT_NE(richEditorNode_->GetLayoutProperty(), nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(richEditorNode_, containerGeometryNode, richEditorNode_->GetLayoutProperty());

    /**
     * @tc.steps: step2. get richEditorPattern and richEditorController.
     */
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    AddSpan("test");

    /**
     * @tc.steps: step3. test AddPlaceholderSpan.
     */
    auto builderId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto builderNode1 = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, builderId1, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });

    auto index1 = richEditorController->AddPlaceholderSpan(builderNode1, {});
    EXPECT_EQ(index1, 1);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 2);
    auto builderSpanChildren = richEditorNode_->GetChildren();
    ASSERT_NE(static_cast<int32_t>(builderSpanChildren.size()), 0);
    auto eventHub = builderNode1->GetEventHub<EventHub>();
    EXPECT_NE(eventHub, nullptr);
}

/**
 * @tc.name: AddSymbolSpan001
 * @tc.desc: test add symbol span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddSymbolSpan001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. initalize symbol span properties
     */
    TextStyle style;
    style.SetFontSize(FONT_SIZE_VALUE);
    style.SetFontWeight(FONT_WEIGHT_VALUE);
    style.SetSymbolColorList(SYMBOL_COLOR_LIST_1);
    style.SetRenderStrategy(RENDER_STRATEGY_SINGLE);
    style.SetEffectStrategy(EFFECT_STRATEGY_NONE);
    SymbolSpanOptions options;
    options.symbolId = SYMBOL_ID;
    options.style = style;

    /**
     * @tc.steps: step3. test add symbol span
     */
    auto index1 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index1, 0);
    auto index2 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index2, 1);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 2);
    ClearSpan();
}

/**
 * @tc.name: AddSpans001
 * @tc.desc: test use span & imagespan & symbolspan together
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddSpans001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. initalize span properties
     */
    SymbolSpanOptions options1;
    options1.symbolId = SYMBOL_ID;
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;
    ImageSpanOptions options3;
    options3.image = IMAGE_VALUE;

    /**
     * @tc.steps: step3. test add span
     */
    richEditorController->AddSymbolSpan(options1);
    richEditorController->AddTextSpan(options2);
    richEditorController->AddImageSpan(options3);
    richEditorController->AddTextSpan(options2);
    richEditorController->AddSymbolSpan(options1);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 5);

    /**
     * @tc.steps: step4. test get span
     */
    auto info1 = richEditorController->GetSpansInfo(0, 3);
    EXPECT_EQ(info1.selection_.resultObjects.size(), 2);
    auto info2 = richEditorController->GetSpansInfo(8, 9);
    EXPECT_EQ(info2.selection_.resultObjects.size(), 1);

    /**
     * @tc.steps: step5. test update span
     */
    TextStyle textStyle;
    textStyle.SetFontSize(FONT_SIZE_VALUE_2);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE_2;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    ImageSpanAttribute imageStyle;
    richEditorController->UpdateSpanStyle(2, 8, textStyle, imageStyle);

    auto newSpan2 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(1));
    ASSERT_NE(newSpan2, nullptr);
    EXPECT_EQ(newSpan2->GetFontSize(), FONT_SIZE_VALUE_2);

    /**
     * @tc.steps: step6. test delete span
     */
    RangeOptions option;
    option.start = 8;
    option.end = 15;
    richEditorController->DeleteSpans(option);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 3);

    option.start = 0;
    option.end = 2;
    richEditorController->DeleteSpans(option);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 2);

    ClearSpan();
}

/**
 * @tc.name: AddSpans002
 * @tc.desc: test add many spans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddSpans002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. initalize span properties
     */
    SymbolSpanOptions options1;
    options1.symbolId = SYMBOL_ID;
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;
    ImageSpanOptions options3;
    options3.image = IMAGE_VALUE;

    /**
     * @tc.steps: step3. test add span
     */
    for (int i = 0; i < 100; i++) {
        richEditorController->AddSymbolSpan(options1);
        richEditorController->AddTextSpan(options2);
        richEditorController->AddImageSpan(options3);
        richEditorController->AddTextSpan(options2);
        richEditorController->AddSymbolSpan(options1);
    }
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 500);

    ClearSpan();
}

/**
 * @tc.name: AddSpanByPasteData001
 * @tc.desc: Test add span by pasteData.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddSpanByPasteData001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. init spans
    */
    ImageSpanOptions imageOptions;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(pixelMap, nullptr);
    imageOptions.imagePixelMap = pixelMap;
    richEditorPattern->AddImageSpan(imageOptions);

    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    richEditorController->AddTextSpan(options);

    /**
     * @tc.steps: step2. test AddSpanByPasteData001
     */
    auto spanString = richEditorPattern->ToStyledString(0, 8);
    ASSERT_NE(spanString, nullptr);
    richEditorPattern->spans_.clear();
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->AddSpanByPasteData(spanString);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
}
} // namespace OHOS::Ace::NG
