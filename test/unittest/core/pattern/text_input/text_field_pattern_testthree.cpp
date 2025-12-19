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

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "text_input_base.h"

#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldPatternTestThree : public TextInputBases {
public:
};

void CustomKeyboardBuilder() {}
/**
 * @tc.name: UpdateFocusForward001
 * @tc.desc: test testInput text UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, UpdateFocusForward001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelButtonSymbol(false);
    });
    GetFocus();
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    auto stackNode = cleanNodeResponseArea->cleanNode_;
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    cleanNodeResponseArea->UpdateCleanNode(false);
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    auto cleanNodeArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    cleanNodeArea->isShow_ = true;
    EXPECT_TRUE(pattern_->UpdateFocusForward());
}

/**
 * @tc.name: UpdateFocusBackward001
 * @tc.desc: test testInput text UpdateFocusBackward001
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, UpdateFocusBackward001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelButtonSymbol(false);
    });
    GetFocus();
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    auto stackNode = cleanNodeResponseArea->cleanNode_;
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    cleanNodeResponseArea->UpdateCleanNode(false);
    pattern_->focusIndex_ = FocuseIndex::UNIT;
    auto cleanNodeArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    cleanNodeArea->isShow_ = true;
    EXPECT_TRUE(pattern_->UpdateFocusBackward());
}

/**
 * @tc.name: RequestKeyboardAfterLongPress001
 * @tc.desc: test testInput text RequestKeyboardAfterLongPress001
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, RequestKeyboardAfterLongPress001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    pattern_->isLongPress_ = false;
    auto focusHub = pattern_->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    pattern_->isCustomKeyboardAttached_ = true;
    pattern_->RequestKeyboardAfterLongPress();
    EXPECT_FALSE(pattern_->isLongPress_);
    focusHub->currentFocus_ = false;
    pattern_->RequestKeyboardAfterLongPress();
    EXPECT_FALSE(pattern_->isLongPress_);
    pattern_->isLongPress_ = true;
    pattern_->RequestKeyboardAfterLongPress();
    EXPECT_FALSE(pattern_->isLongPress_);
    pattern_->isLongPress_ = true;
    focusHub->currentFocus_ = true;
    pattern_->RequestKeyboardAfterLongPress();
    EXPECT_FALSE(pattern_->isLongPress_);
}

/**
 * @tc.name: RequestKeyboardAfterLongPress002
 * @tc.desc: test testInput text RequestKeyboardAfterLongPress002
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, RequestKeyboardAfterLongPress002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    pattern_->isLongPress_ = false;
    auto focusHub = pattern_->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    pattern_->showKeyBoardOnFocus_ = true;
    auto func = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    pattern_->customKeyboard_ = AceType::Claim<UINode>(func);
    pattern_->customKeyboardBuilder_ = CustomKeyboardBuilder;
    pattern_->isCustomKeyboardAttached_ = true;
    pattern_->RequestKeyboardAfterLongPress();
    EXPECT_FALSE(pattern_->isLongPress_);
    focusHub->currentFocus_ = false;
    pattern_->RequestKeyboardAfterLongPress();
    EXPECT_FALSE(pattern_->isLongPress_);
    pattern_->isLongPress_ = true;
    pattern_->RequestKeyboardAfterLongPress();
    EXPECT_FALSE(pattern_->isLongPress_);
    pattern_->isLongPress_ = true;
    focusHub->currentFocus_ = true;
    pattern_->RequestKeyboardAfterLongPress();
    EXPECT_FALSE(pattern_->isLongPress_);
}

/**
 * @tc.name: GetAvoidSoftKeyboardOffset001
 * @tc.desc: test testInput text GetAvoidSoftKeyboardOffset001
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, GetAvoidSoftKeyboardOffset001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    PipelineBase::GetCurrentContext()->themeManager_ = nullptr;
    auto ret = pattern_->GetAvoidSoftKeyboardOffset();
    EXPECT_EQ(ret, 24.0_vp);
}

/**
 * @tc.name: SetPreviewTextOperation001
 * @tc.desc: test testInput text SetPreviewTextOperation001
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, SetPreviewTextOperation001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxLength(1000023);
    });
    GetFocus();

    auto controller = pattern_->GetTextSelectController();
    controller->UpdateCaretIndex(5);
    pattern_->SetPreviewTextOperation(PREVIEW_ONE);
    EXPECT_TRUE(pattern_->GetIsPreviewText());
    FlushLayoutTask(frameNode_);

    pattern_->InitEditingValueText(u"");
    EXPECT_FALSE(pattern_->GetIsPreviewText());
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: GetPreviewTextRects001
 * @tc.desc: test testInput text GetPreviewTextRects001
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, GetPreviewTextRects001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    pattern_->hasPreviewText_ = true;
    auto ret = pattern_->GetPreviewTextRects();
    EXPECT_FALSE(ret.empty());
}

/**
 * @tc.name: GetPreviewTextRects002
 * @tc.desc: test testInput text GetPreviewTextRects002
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, GetPreviewTextRects002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(10, 10, 20, 20), RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    pattern_->hasPreviewText_ = true;
    auto ret = pattern_->GetPreviewTextRects();
    EXPECT_FALSE(ret.empty());
}

/**
 * @tc.name: GetPreviewTextStyle001
 * @tc.desc: test testInput text GetPreviewTextStyle001
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, GetPreviewTextStyle001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    pattern_->ReceivePreviewTextStyle("normal");
    EXPECT_EQ(pattern_->GetPreviewTextStyle(), PreviewTextStyle::NORMAL);
    pattern_->ReceivePreviewTextStyle("underline");
    EXPECT_EQ(pattern_->GetPreviewTextStyle(), PreviewTextStyle::UNDERLINE);
}

/**
 * @tc.name: CalculatePreviewingTextMovingLimit001
 * @tc.desc: test testInput text CalculatePreviewingTextMovingLimit001
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, CalculatePreviewingTextMovingLimit001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(10, 10, 20, 20), RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    pattern_->hasPreviewText_ = true;
    auto ret = pattern_->GetPreviewTextRects();
    EXPECT_FALSE(ret.empty());
    double limitL = 0.0;
    double limitR = 0.0;
    pattern_->CalculatePreviewingTextMovingLimit(Offset(100, 100), limitL, limitR);
    ASSERT_NE(limitL, 0.0);
    pattern_->CalculatePreviewingTextMovingLimit(Offset(11, 11), limitL, limitR);
    ASSERT_NE(limitL, 0.0);
    pattern_->CalculatePreviewingTextMovingLimit(Offset(0, 0), limitL, limitR);
    ASSERT_NE(limitL, 0.0);
}

/**
 * @tc.name: ScrollPage001
 * @tc.desc: test testInput text ScrollPage001
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, ScrollPage001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(10, 10, 20, 20), RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    pattern_->hasPreviewText_ = true;
    pattern_->ScrollPage(true, true, AccessibilityScrollType::SCROLL_HALF);
    pattern_->ScrollPage(true, true, AccessibilityScrollType::SCROLL_MAX_TYPE);
    auto ret = pattern_->GetPreviewTextRects();
    EXPECT_FALSE(ret.empty());
}

/**
 * @tc.name: IsResponseRegionExpandingNeededForStylus001
 * @tc.desc: test testInput text IsResponseRegionExpandingNeededForStylus001
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, IsResponseRegionExpandingNeededForStylus001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.x = 10;
    touchEvent.y = 10;
    auto ret = pattern_->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
    touchEvent.sourceTool = SourceTool::PEN;
    ret = pattern_->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_TRUE(ret);
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.type = TouchType::MOVE;
    ret = pattern_->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
    touchEvent.sourceTool = SourceTool::PEN;
    touchEvent.type = TouchType::MOVE;
    ret = pattern_->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SearchRequestKeyboard001
 * @tc.desc: test SearchRequestKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, SearchRequestKeyboard001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    ASSERT_NE(pattern_, nullptr);

    auto focusHub = pattern_->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    pattern_->isLongPress_ = true;
    focusHub->currentFocus_ = true;
    pattern_->showKeyBoardOnFocus_ = true;
    pattern_->customKeyboardBuilder_ = CustomKeyboardBuilder;
    pattern_->isCustomKeyboardAttached_ = true;

    pattern_->SearchRequestKeyboard();
    EXPECT_EQ(pattern_->isEdit_, true);
}

/**
 * @tc.name: ResultImageSrc001
 * @tc.desc: test GetHideResultImageSrc and GetShowResultImageSrc
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, ResultImageSrc001, TestSize.Level0)
{
    struct PasswordIcon passwordIcon;
    passwordIcon.hideModuleName = "hideModuleName";
    passwordIcon.hideResult = "hideResult";
    passwordIcon.hideBundleName = "hideBundleName";
    passwordIcon.showModuleName = "showModuleName";
    passwordIcon.showResult = "showResult";
    passwordIcon.showBundleName = "showBundleName";
    CreateTextField(DEFAULT_TEXT, "", [passwordIcon](TextFieldModelNG model) {
        model.SetPasswordIcon(passwordIcon);
    });
    GetFocus();
    ASSERT_NE(pattern_, nullptr);
    auto ret = pattern_->GetHideResultImageSrc();
    ASSERT_EQ(ret, passwordIcon.hideResult);
    ret = pattern_->GetShowResultImageSrc();
    ASSERT_EQ(ret, passwordIcon.showResult);
}

/**
 * @tc.name: ResultImageSrc002
 * @tc.desc: test GetHideResultImageSrc and GetShowResultImageSrc
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, ResultImageSrc002, TestSize.Level0)
{
    const std::string SHOW_PASSWORD_SVG = "SYS_SHOW_PASSWORD_SVG";
    const std::string HIDE_PASSWORD_SVG = "SYS_HIDE_PASSWORD_SVG";
    struct PasswordIcon passwordIcon;
    CreateTextField(DEFAULT_TEXT, "", [passwordIcon](TextFieldModelNG model) {
        model.SetPasswordIcon(passwordIcon);
    });
    GetFocus();
    ASSERT_NE(pattern_, nullptr);
    auto ret = pattern_->GetHideResultImageSrc();
    ASSERT_EQ(ret, HIDE_PASSWORD_SVG);
    ret = pattern_->GetShowResultImageSrc();
    ASSERT_EQ(ret, SHOW_PASSWORD_SVG);
}

/**
 * @tc.name: OnBackPressed001
 * @tc.desc: test OnBackPressed
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, OnBackPressed001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    ASSERT_NE(pattern_, nullptr);

    pattern_->isLongPress_ = true;
    pattern_->showKeyBoardOnFocus_ = true;
    pattern_->customKeyboardBuilder_ = CustomKeyboardBuilder;
    pattern_->isCustomKeyboardAttached_ = true;

    int32_t start = 0;
    int32_t end = 4;
    SelectionOptions options;
    pattern_->SetSelectionFlag(start, end, options);
    EXPECT_EQ(pattern_->isEdit_, true);

    bool ret = pattern_->OnBackPressed();
    pattern_->imeShown_ = true;
    ret = pattern_->OnBackPressed();
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: UnitResponseKeyEvent001
 * @tc.desc: test UnitResponseKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, UnitResponseKeyEvent001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto unitResponseArea = AceType::MakeRefPtr<UnitResponseArea>(
        AceType::WeakClaim(AceType::RawPtr(pattern)), textFieldNode);
    ASSERT_NE(unitResponseArea, nullptr);
    pattern->responseArea_ = std::move(unitResponseArea);
    ASSERT_NE(pattern->responseArea_, nullptr);

    pattern->UnitResponseKeyEvent();
    EXPECT_NE(pattern->responseArea_->GetFrameNode()->GetTag(), V2::SELECT_ETS_TAG);
}

/**
 * @tc.name: UnitResponseKeyEvent002
 * @tc.desc: test UnitResponseKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, UnitResponseKeyEvent002, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto selectNode = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SelectPattern>(); });
    ASSERT_NE(selectNode, nullptr);
    auto selectPattern = selectNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);

    auto unitResponseArea = AceType::MakeRefPtr<UnitResponseArea>(
        AceType::WeakClaim(AceType::RawPtr(selectPattern)), selectNode);
    ASSERT_NE(unitResponseArea, nullptr);
    pattern->responseArea_ = std::move(unitResponseArea);
    ASSERT_NE(pattern->responseArea_, nullptr);

    pattern->UnitResponseKeyEvent();
    EXPECT_EQ(pattern->responseArea_->GetFrameNode()->GetTag(), V2::SELECT_ETS_TAG);
}

/**
 * @tc.name: OnTextGestureSelectionEnd001
 * @tc.desc: test testInput text OnTextGestureSelectionEnd001
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, OnTextGestureSelectionEnd001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    TouchLocationInfo locationInfo(0);
    pattern_->OnTextGestureSelectionEnd(locationInfo);
    EXPECT_FALSE(pattern_->IsContentRectNonPositive());
    pattern_->contentRect_.SetRect(10, 10, 0, 0);
    pattern_->OnTextGestureSelectionEnd(locationInfo);
    EXPECT_TRUE(pattern_->IsContentRectNonPositive());
}

/**
 * @tc.name: OnTextGestureSelectionUpdate001
 * @tc.desc: test testInput text OnTextGestureSelectionUpdate001
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, OnTextGestureSelectionUpdate001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    int32_t start = 0;
    int32_t end = 0;
    TouchEventInfo info("onTouch");
    TouchLocationInfo infoSub(1);
    infoSub.SetLocalLocation(Offset(10, 20));
    info.AddTouchLocationInfo(std::move(infoSub));
    pattern_->OnTextGestureSelectionUpdate(start, end, info);
    EXPECT_TRUE(pattern_->magnifierController_);
    pattern_->magnifierController_ = nullptr;
    pattern_->OnTextGestureSelectionUpdate(start, end, info);
    EXPECT_FALSE(pattern_->magnifierController_);
}

/**
 * @tc.name: HandleAIWrite001
 * @tc.desc: test GetAIWriteInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, HandleAIWrite001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto aiWriteAdapter = AceType::MakeRefPtr<AIWriteAdapter>();
    pattern_->aiWriteAdapter_ = aiWriteAdapter;

    /**
     * @tc.steps: step2. test GetAIWriteInfo
     */
    pattern_->HandleSetSelection(5, 10, false);
    auto selectController = pattern_->GetTextSelectController();
    AIWriteInfo info;
    pattern_->GetAIWriteInfo(info);
    EXPECT_EQ(info.selectStart, 5);
    EXPECT_EQ(info.selectEnd, 10);
    EXPECT_EQ(info.selectLength, 5);
    EXPECT_EQ(info.firstHandle, selectController->GetFirstHandleRect().ToString());
    EXPECT_EQ(info.secondHandle, selectController->GetSecondHandleRect().ToString());
    RefPtr<SpanString> spanString = SpanString::DecodeTlv(info.selectBuffer);
    ASSERT_NE(spanString, nullptr);
    auto textContent = spanString->GetString();
    EXPECT_EQ(textContent.empty(), false);
}

/**
 * @tc.name: HandleAIWrite002
 * @tc.desc: test HandleOnAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, HandleAIWrite002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. test HandleOnAIWrite
     */
    pattern_->HandleSetSelection(0, 5, false);
    pattern_->HandleOnAIWrite();

    std::vector<uint8_t> buff;
    auto spanStr = AceType::MakeRefPtr<SpanString>(u"dddd结果回填123456");
    spanStr->EncodeTlv(buff);
    pattern_->HandleAIWriteResult(0, 5, buff);
    pattern_->BeforeCreateLayoutWrapper();
    auto contentController = pattern_->GetTextContentController();
    auto sentenceContent = StringUtils::Str16ToStr8(contentController->GetSelectedValue(0, spanStr->GetLength()));
    ASSERT_EQ(sentenceContent, spanStr->GetString());
}

HWTEST_F(TextFieldPatternTestThree, HandleAIWrite003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        pattern_->imeShown_ = true;
#else
        pattern_->connection_= true;
#endif
    pattern_->HandleOnCameraInput();
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 26);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 26);
}

HWTEST_F(TextFieldPatternTestThree, HandleAIWrite004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    pattern_->HandleOnCameraInput();
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 26);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 26);
}

/**
 * @tc.name: PlaceholderResponseArea001
 * @tc.desc: test PlaceholderResponseArea PlaceholderResponseArea001 function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, PlaceholderResponseArea001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    // 创建 PlaceholderResponseArea 实例
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(u"0123456789");
    pattern_->SetPlaceholderStyledString(spanString);
    auto placeholderResponseArea = pattern_->GetPlaceholderResponseArea();
    ASSERT_NE(placeholderResponseArea, nullptr);
    
    // 验证 placeholderNode_ 是否创建成功
    auto placeholderNode = placeholderResponseArea->GetFrameNode();
    ASSERT_NE(placeholderNode, nullptr);
    
    // 验证节点标签是否正确
    EXPECT_EQ(placeholderNode->GetTag(), V2::TEXT_ETS_TAG);
    
    // 验证手势事件中心是否正确配置
    auto gesture = placeholderNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    EXPECT_EQ(gesture->GetHitTestMode(), HitTestMode::HTMNONE);
}

/**
 * @tc.name: PlaceholderResponseArea002
 * @tc.desc: test PlaceholderResponseArea PlaceholderResponseArea002 function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, PlaceholderResponseArea002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    // 创建 PlaceholderResponseArea 实例
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(u"0123456789");
    pattern_->SetPlaceholderStyledString(spanString);
    auto placeholderResponseArea = pattern_->GetPlaceholderResponseArea();
    ASSERT_NE(placeholderResponseArea, nullptr);
    
    // 验证 placeholderNode_ 是否创建成功
    auto placeholderNode = placeholderResponseArea->GetFrameNode();
    ASSERT_NE(placeholderNode, nullptr);
    
    // 验证节点标签是否正确
    EXPECT_EQ(placeholderNode->GetTag(), V2::TEXT_ETS_TAG);
    
    // 验证手势事件中心是否正确配置
    auto gesture = placeholderNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    EXPECT_EQ(gesture->GetHitTestMode(), HitTestMode::HTMNONE);
}

/**
 * @tc.name: PlaceholderResponseArea003
 * @tc.desc: test PlaceholderResponseArea PlaceholderResponseArea003 function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, PlaceholderResponseArea003, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    // 创建 PlaceholderResponseArea 实例
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");
    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = TextAlign::END;
    spanParagraphStyle.maxLines = 4;
    spanString->AddSpan(AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 0, 1));
    spanString->AddSpan(AceType::MakeRefPtr<LineHeightSpan>(Dimension(30), 0, 3));
    pattern_->SetPlaceholderStyledString(spanString);
    auto placeholderResponseArea = pattern_->GetPlaceholderResponseArea();
    ASSERT_NE(placeholderResponseArea, nullptr);

    // 验证 placeholderNode_ 是否创建成功
    auto placeholderNode = placeholderResponseArea->GetFrameNode();
    ASSERT_NE(placeholderNode, nullptr);

    auto textInputLayoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    std::u16string textContent = u"";
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<TextFieldTheme>()));
    // 调用测试方法
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>(frameNode_->GetThemeScopeId());
    ASSERT_NE(textFieldTheme, nullptr);
    LayoutWrapperNode textInputLayoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    textInputLayoutAlgorithm->ConstructStyledPlaceholderStyle(&textInputLayoutWrapper, frameNode_, textFieldTheme);

    // 验证单行输入框text自身maxlines优先，且行数为1
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textLayoutProperty = placeholderNode->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(placeholderNode, geometryNode, textLayoutProperty);
    auto pattern = placeholderNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    TextStyle textStyleText;
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>(
        pattern->GetSpanItemChildren(), pattern->GetParagraphManager(), true, textStyleText, false);
    EXPECT_FALSE(textLayoutAlgorithm == nullptr);

    // set theme.
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    LayoutConstraintF contentConstraint;
    textLayoutAlgorithm->MeasureContent(contentConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    auto textStylePlaceholder = textLayoutAlgorithm->GetTextStyle();
    EXPECT_TRUE(textLayoutProperty->GetIsTextMaxlinesFirstValue(false));
    EXPECT_EQ(textStylePlaceholder.GetMaxLines(), 1);
}

/**
 * @tc.name: GetTextDirection001
 * @tc.desc: Test GetTextDirection with INHERIT textDirection_
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, GetTextDirection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and layout algorithm
     */
    CreateTextField("", "");
    auto layoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());

    /**
     * @tc.steps: step2. Get layout property and set layout direction
     */
    auto layoutProperty = pattern_->GetLayoutProperty<LayoutProperty>();
    layoutProperty->layoutDirection_ = TextDirection::RTL;

    /**
     * @tc.steps: step3. Set textDirection_ to INHERIT
     */
    layoutAlgorithm->textDirection_ = TextDirection::INHERIT;

    /**
     * @tc.steps: step4. Call GetTextDirection
     */
    auto direction = layoutAlgorithm->GetTextDirection(layoutProperty);

    /**
     * @tc.expected: Return layout direction (RTL) when textDirection_ is INHERIT
     */
    EXPECT_EQ(direction, TextDirection::RTL);
}

/**
 * @tc.name: GetTextDirection002
 * @tc.desc: Test GetTextDirection with AUTO textDirection_ and valid paragraph_
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, GetTextDirection002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and layout algorithm
     */
    CreateTextField("", "");
    auto layoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());

    /**
     * @tc.steps: step2. Get layout property
     */
    auto layoutProperty = pattern_->GetLayoutProperty<LayoutProperty>();
    layoutProperty->layoutDirection_ = TextDirection::LTR;

    /**
     * @tc.steps: step3. Set textDirection_ to AUTO
     */
    layoutAlgorithm->textDirection_ = TextDirection::AUTO;

    /**
     * @tc.steps: step4. Create mock paragraph and set RTL direction
     */
    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ParagraphStyle paragraphStyle;
    paragraphStyle.direction = TextDirection::RTL;

    EXPECT_CALL(*mockParagraph, GetParagraphStyle()).WillRepeatedly(ReturnRef(paragraphStyle));

    /**
     * @tc.steps: step5. Set paragraph_ in layout algorithm
     */
    layoutAlgorithm->paragraph_ = mockParagraph;

    /**
     * @tc.steps: step6. Call GetTextDirection
     */
    auto direction = layoutAlgorithm->GetTextDirection(layoutProperty);

    /**
     * @tc.expected: Return paragraph's direction (RTL) when textDirection_ is AUTO
     */
    EXPECT_EQ(direction, TextDirection::RTL);
}

/**
 * @tc.name: GetTextDirection003
 * @tc.desc: Test GetTextDirection with LTR layout direction
 * @tc.type: FUNC
 * @tc.require: AR000H0F7I
 */
HWTEST_F(TextFieldPatternTestThree, GetTextDirection003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and layout algorithm
     */
    CreateTextField("", "");
    auto layoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());

    /**
     * @tc.steps: step2. Get layout property and set LTR layout direction
     */
    auto layoutProperty = pattern_->GetLayoutProperty<LayoutProperty>();
    layoutProperty->layoutDirection_ = TextDirection::LTR;

    /**
     * @tc.steps: step3. Set textDirection_ to INHERIT
     */
    layoutAlgorithm->textDirection_ = TextDirection::INHERIT;

    /**
     * @tc.steps: step4. Call GetTextDirection
     */
    auto direction = layoutAlgorithm->GetTextDirection(layoutProperty);

    /**
     * @tc.expected: Return LTR layout direction when textDirection_ is INHERIT
     */
    EXPECT_EQ(direction, TextDirection::LTR);
}
} // namespace OHOS::Ace::NG