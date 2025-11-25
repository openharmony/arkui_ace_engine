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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/style_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorChangeReasonTest : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorChangeReasonTest::SetUp()
{
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

void RichEditorChangeReasonTest::TearDown()
{
    richEditorNode_ = nullptr;
}

void RichEditorChangeReasonTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: ControllerAddTextSpan
 * @tc.desc: test AddTextSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, ControllerAddTextSpan001, TestSize.Level0)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::CONTROLLER);
        changeReason = changeValue.changeReason_;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    richEditorController->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    EXPECT_EQ(changeReason, TextChangeReason::CONTROLLER);
}

/**
 * @tc.name: ControllerAddImageSpan
 * @tc.desc: test AddImageSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, ControllerAddImageSpan001, TestSize.Level0)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::CONTROLLER);
        changeReason = changeValue.changeReason_;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    richEditorController->AddImageSpan(IMAGE_SPAN_OPTIONS_1);
    EXPECT_EQ(changeReason, TextChangeReason::CONTROLLER);
}

/**
 * @tc.name: ControllerAddSymbolSpan
 * @tc.desc: test AddSymbolSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, ControllerAddSymbolSpan001, TestSize.Level0)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::CONTROLLER);
        changeReason = changeValue.changeReason_;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    richEditorController->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);
    EXPECT_EQ(changeReason, TextChangeReason::CONTROLLER);
}

/**
 * @tc.name: ControllerAddPlaceholderSpan
 * @tc.desc: test AddPlaceholderSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, ControllerAddPlaceholderSpan001, TestSize.Level0)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<SpanNode>(V2::IMAGE_ETS_TAG, -1);
    ASSERT_NE(customNode, nullptr);

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::CONTROLLER);
        changeReason = changeValue.changeReason_;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    richEditorController->AddPlaceholderSpan(customNode, SYMBOL_SPAN_OPTIONS_1);
    EXPECT_EQ(changeReason, TextChangeReason::UNKNOWN);
}

/**
 * @tc.name: ControllerUpdateSpanStyle
 * @tc.desc: test UpdateSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, ControllerUpdateSpanStyle001, TestSize.Level0)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    ImageSpanAttribute imageStyle;
    richEditorController->UpdateSpanStyle(0, 1, style, imageStyle);
    EXPECT_EQ(
        richEditorPattern->updateSpanStyle_.isInitDecoration, richEditorController->updateSpanStyle_.isInitDecoration);
}

/**
 * @tc.name: ControllerToStyledString
 * @tc.desc: test ToStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, ControllerToStyledString001, TestSize.Level0)
{
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. init spans
     */
    TextStyle style;
    style.SetFontSize(FONT_SIZE_VALUE);
    style.SetFontWeight(FONT_WEIGHT_VALUE);
    style.SetSymbolColorList(SYMBOL_COLOR_LIST_1);
    style.SetRenderStrategy(RENDER_STRATEGY_SINGLE);
    style.SetEffectStrategy(EFFECT_STRATEGY_NONE);
    SymbolSpanOptions symbolOptions;
    symbolOptions.symbolId = SYMBOL_ID;
    symbolOptions.style = style;
    richEditorController->AddSymbolSpan(symbolOptions);

    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    richEditorController->AddTextSpan(options);
    options.value = INIT_VALUE_2;
    richEditorController->AddTextSpan(options);

    /**
     * @tc.steps: step2. test ToStyledString
     */
    auto spanString = richEditorController->ToStyledString(0, 7);
    ASSERT_NE(spanString, nullptr);
}

/**
 * @tc.name: ControllerGetSpansInfo
 * @tc.desc: test GetSpansInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, ControllerGetSpansInfo001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. add span
     */
    TextStyle style;
    TextBackgroundStyle textBackgroundStyle;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    textBackgroundStyle.backgroundColor = Color::RED;
    textBackgroundStyle.backgroundRadius = borderRadius;
    textBackgroundStyle.needCompareGroupId = false;
    style.SetTextBackgroundStyle(textBackgroundStyle);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    auto newSpan = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    ASSERT_NE(newSpan, nullptr);
    EXPECT_TRUE(newSpan->GetTextBackgroundStyle().has_value());
    EXPECT_EQ(newSpan->GetTextBackgroundStyle().value(), textBackgroundStyle);

    /**
     * @tc.steps: step2. get span
     */
    auto info = richEditorController->GetSpansInfo(0, 1);
    auto spanTextBackground = info.selection_.resultObjects.front().textStyle.textBackgroundStyle;
    EXPECT_TRUE(spanTextBackground.has_value());
    EXPECT_EQ(spanTextBackground.value(), textBackgroundStyle);
}

/**
 * @tc.name: ControllerFromStyledString
 * @tc.desc: Test ControllerFromStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, ControllerFromStyledString001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. add span
     */
    TextStyle style;
    TextBackgroundStyle textBackgroundStyle;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(5, OHOS::Ace::DimensionUnit::VP);
    textBackgroundStyle.backgroundColor = Color::RED;
    textBackgroundStyle.backgroundRadius = borderRadius;
    textBackgroundStyle.needCompareGroupId = false;
    style.SetTextBackgroundStyle(textBackgroundStyle);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. toStyledString
     */
    auto spanString = richEditorPattern->ToStyledString(0, 6);
    ASSERT_NE(spanString, nullptr);
    auto spans = spanString->GetSpans(0, 6, SpanType::BackgroundColor);
    EXPECT_EQ(spans.size(), 1);
    auto backgroundSpan = AceType::DynamicCast<BackgroundColorSpan>(spans[0]);
    EXPECT_NE(backgroundSpan, nullptr);
    EXPECT_EQ(backgroundSpan->GetBackgroundColor(), textBackgroundStyle);

    /**
     * @tc.steps: step3. fromStyledString
     */
    auto info = richEditorController->FromStyledString(spanString);
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);
    auto spanTextBackground = info.selection_.resultObjects.front().textStyle.textBackgroundStyle;
    EXPECT_TRUE(spanTextBackground.has_value());
    EXPECT_EQ(spanTextBackground.value(), textBackgroundStyle);
}

/**
 * @tc.name: ControllerGetPreviewTextInfo
 * @tc.desc: Test ControllerGetPreviewTextInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, ControllerGetPreviewTextInfo001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    PreviewTextInfo info = richEditorController->GetPreviewTextInfo();
    ASSERT_EQ(richEditorPattern->previewTextRecord_.previewContent.empty(), true);

    richEditorPattern->previewTextRecord_.previewContent = u"abc";
    info = richEditorController->GetPreviewTextInfo();
    ASSERT_EQ(richEditorPattern->previewTextRecord_.previewContent.empty(), false);
}

/**
 * @tc.name: ControllerSetTypingParagraphStyle
 * @tc.desc: Test ControllerSetTypingParagraphStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, ControllerSetTypingParagraphStyle001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    std::optional<struct UpdateParagraphStyle> typingParagraphStyle = UpdateParagraphStyle();
    richEditorController->SetTypingParagraphStyle(typingParagraphStyle);
    auto& styleManager = richEditorPattern->styleManager_;
    std::list<RefPtr<SpanItem>> spans;
    RichEditorChangeValue changeValue;
    // empty
    EXPECT_EQ(styleManager->HasTypingParagraphStyle(), true);
    EXPECT_EQ(styleManager->UseTypingParaStyle(spans, changeValue), true);

    // delete to empty
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spans.push_back(spanItem);
    spanItem->content = u"123";
    spanItem->position = static_cast<int32_t>(spanItem->content.length());
    changeValue.rangeBefore_.start = 0;
    changeValue.rangeBefore_.end = 3;
    EXPECT_EQ(styleManager->UseTypingParaStyle(spans, changeValue), true);

    // insert in last new line
    spanItem->content = u"123\n";
    spanItem->position = static_cast<int32_t>(spanItem->content.length());
    changeValue.rangeBefore_.start = 4;
    changeValue.rangeBefore_.end = 4;
    EXPECT_EQ(styleManager->UseTypingParaStyle(spans, changeValue), true);

    richEditorController->SetTypingParagraphStyle(std::nullopt);
}

/**
 * @tc.name: ControllerDeleteBackward
 * @tc.desc: test DeleteBackward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, DeleteBackward001, TestSize.Level0)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);

    richEditorController->DeleteBackward();
    EXPECT_NE(richEditorPattern->IsPreviewTextInputting(), true);
}

/**
 * @tc.name: ControllerDeleteSpans
 * @tc.desc: test DeleteSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, ControllerDeleteSpans001, TestSize.Level0)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::CONTROLLER);
        changeReason = changeValue.changeReason_;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    RangeOptions options;
    options.start = 0;
    options.end = 1;
    richEditorController->DeleteSpans(options);
    EXPECT_EQ(changeReason, TextChangeReason::CONTROLLER);
}

/**
 * @tc.name: ControllerDeleteSpans
 * @tc.desc: test DeleteSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, DeleteRange001, TestSize.Level0)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::INPUT);
        changeReason = changeValue.changeReason_;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    richEditorPattern->DeleteRange(0, 1, true);
    EXPECT_EQ(changeReason, TextChangeReason::INPUT);
}

/**
 * @tc.name: DeleteBackwardForward
 * @tc.desc: test DeleteSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, DeleteBackwardForward001, TestSize.Level0)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::INPUT);
        changeReason = changeValue.changeReason_;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    richEditorPattern->HandleOnDelete(true);
    EXPECT_EQ(changeReason, TextChangeReason::INPUT);

    changeReason = TextChangeReason::UNKNOWN;
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(changeReason, TextChangeReason::INPUT);

    richEditorPattern->SetCaretPosition(0);

    changeReason = TextChangeReason::UNKNOWN;
    richEditorPattern->HandleOnDelete(false);
    EXPECT_EQ(changeReason, TextChangeReason::INPUT);
    
    changeReason = TextChangeReason::UNKNOWN;
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(changeReason, TextChangeReason::INPUT);
}

}