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

#include "text_input_base.h"

#include "test/mock/core/render/mock_paragraph.h"

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
 * @tc.name: OnTextGenstureSelectionEnd001
 * @tc.desc: test testInput text OnTextGenstureSelectionEnd001
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, OnTextGenstureSelectionEnd001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    TouchLocationInfo locationInfo(0);
    pattern_->OnTextGenstureSelectionEnd(locationInfo);
    EXPECT_FALSE(pattern_->IsContentRectNonPositive());
    pattern_->contentRect_.SetRect(10, 10, 0, 0);
    pattern_->OnTextGenstureSelectionEnd(locationInfo);
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
} // namespace OHOS::Ace::NG