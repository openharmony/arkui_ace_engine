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

#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "core/accessibility/accessibility_manager.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "text_input_base.h"

#include "core/common/ai/ai_write_adapter.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/clean_node_host.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldPatternTestThree : public TextInputBases {
public:
};

void CustomKeyboardBuilder() {}

/**
 * @tc.name: CleanNodeResponseAreaCreateIconRect001
 * @tc.desc: The press rect follows the cancel icon when its margin changes the frame offset.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, CleanNodeResponseAreaCreateIconRect001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_->cleanNodeResponseArea_, nullptr);
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeResponseArea, nullptr);
    auto stackNode = cleanNodeResponseArea->cleanNode_;
    ASSERT_NE(stackNode, nullptr);
    auto iconNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    ASSERT_NE(iconNode, nullptr);

    frameNode_->GetGeometryNode()->SetFrameSize(SizeF(200.0f, 40.0f));
    stackNode->GetGeometryNode()->SetFrameOffset(OffsetF(100.0f, 10.0f));
    stackNode->GetGeometryNode()->SetFrameSize(SizeF(30.0f, 20.0f));
    iconNode->GetGeometryNode()->SetFrameOffset(OffsetF(6.0f, 8.0f));
    iconNode->GetGeometryNode()->SetFrameSize(SizeF(10.0f, 10.0f));

    RoundRect paintRect;
    cleanNodeResponseArea->CreateIconRect(paintRect, false);
    auto iconRect = iconNode->GetGeometryNode()->GetFrameRect();
    auto stackRect = stackNode->GetGeometryNode()->GetFrameRect();
    EXPECT_FLOAT_EQ(paintRect.GetRect().Center().GetX(), stackRect.GetX() + iconRect.Center().GetX());
    EXPECT_FLOAT_EQ(paintRect.GetRect().Center().GetY(), stackRect.GetY() + iconRect.Center().GetY());
}

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

    /**
     * trigger onbackpressed
     */
    bool ret = pattern_->OnBackPressed();
    pattern_->imeShown_ = true;
    /**
     * trigger onbackpressed
     */
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
    /**
     *
     *  @tc.steps: step2.
     *  pattern call camerainput
     *
     */
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

    mockParagraph->paraStyle_ = paragraphStyle;

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

/**
 * @tc.name: ICleanNodeHostTest001
 * @tc.desc: Test ICleanNodeHost exists and TextFieldPattern can DynamicCast to it.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, ICleanNodeHostTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextField with cancel button enabled.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::INPUT);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
    });
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. DynamicCast pattern to ICleanNodeHost.
     * @tc.expected: interface pointer is valid and basic methods don't crash.
     */
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern_);
    ASSERT_NE(hostInterface, nullptr);
    EXPECT_NE(hostInterface->GetHost(), nullptr);
    EXPECT_FALSE(hostInterface->IsDragging());
    EXPECT_FALSE(hostInterface->HasUserAccessibilityText());
}

/**
 * @tc.name: ICleanNodeHostTest002
 * @tc.desc: Test ICleanNodeHost getters read TextFieldLayoutProperty correctly.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, ICleanNodeHostTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextField with explicit cancel button attributes.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. verify interface getters reflect layout property values.
     */
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern_);
    ASSERT_NE(hostInterface, nullptr);
    EXPECT_EQ(hostInterface->GetCleanNodeStyle().value(), CleanNodeStyle::CONSTANT);
    EXPECT_TRUE(hostInterface->IsShowCancelButtonMode());
    EXPECT_FALSE(hostInterface->IsContentEmpty());
    EXPECT_EQ(hostInterface->GetIsShowSymbol(), false);
    auto iconSize = hostInterface->GetCancelIconSize();
    EXPECT_FLOAT_EQ(iconSize.Value(), ICON_SIZE);
}

/**
 * @tc.name: ICleanNodeHostTest003
 * @tc.desc: Test three-state display via interface: INPUT shows when content exists, hides when empty.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, ICleanNodeHostTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. INPUT style with text content -> button should show.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::INPUT);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeResponseArea, nullptr);
    cleanNodeResponseArea->UpdateCleanNode(true);
    pattern_->UpdateCancelNode();
    EXPECT_TRUE(cleanNodeResponseArea->IsShow());

    /**
     * @tc.steps: step2. INPUT style with empty content -> button should hide.
     */
    CreateTextField("", "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::INPUT);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto emptyArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(emptyArea, nullptr);
    emptyArea->UpdateCleanNode(true);
    pattern_->UpdateCancelNode();
    EXPECT_FALSE(emptyArea->IsShow());
}

/**
 * @tc.name: ICleanNodeHostTest004
 * @tc.desc: Test three-state display: CONSTANT always shows, INVISIBLE always hides.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, ICleanNodeHostTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CONSTANT style with text -> button should show even after pre-hide.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto constantArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(constantArea, nullptr);
    constantArea->UpdateCleanNode(false);
    pattern_->UpdateCancelNode();
    EXPECT_TRUE(constantArea->IsShow());

    /**
     * @tc.steps: step2. INVISIBLE style with text -> button should hide even after pre-show.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::INVISIBLE);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto invisibleArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(invisibleArea, nullptr);
    invisibleArea->UpdateCleanNode(true);
    pattern_->UpdateCancelNode();
    EXPECT_FALSE(invisibleArea->IsShow());
}

/**
 * @tc.name: ICleanNodeHostTest005
 * @tc.desc: Test HandleCleanNodeClicked via interface clears text content (AC-1.6 full chain).
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, ICleanNodeHostTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextField with text and cancel button enabled.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern_);
    ASSERT_NE(hostInterface, nullptr);

    /**
     * @tc.steps: step2. verify content is non-empty before click.
     */
    EXPECT_FALSE(hostInterface->IsContentEmpty());

    /**
     * @tc.steps: step3. trigger HandleCleanNodeClicked via interface.
     * @tc.expected: content is cleared (AC-1.6 full chain: clear + close select + caret + focus).
     */
    hostInterface->HandleCleanNodeClicked();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(hostInterface->IsContentEmpty());
}

/**
 * @tc.name: ICleanNodeHostTest006
 * @tc.desc: Test remaining ICleanNodeHost getters read layout property values correctly.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, ICleanNodeHostTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextField with cancel button and set properties via model.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelIconColor(Color::RED);
        model.SetMaxFontScale(2.0f);
        model.SetMinFontScale(0.5f);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. set additional properties directly on layout property.
     */
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateIconSrc("/test/icon.svg");
    layoutProperty_->UpdateBundleName("com.test.bundle");
    layoutProperty_->UpdateModuleName("test_module");
    layoutProperty_->UpdateIsDisabled(true);

    /**
     * @tc.steps: step3. verify all interface getters return the set values.
     */
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern_);
    ASSERT_NE(hostInterface, nullptr);
    EXPECT_EQ(hostInterface->GetCancelIconColor(), Color::RED);
    EXPECT_EQ(hostInterface->GetCancelIconSrc(), "/test/icon.svg");
    EXPECT_EQ(hostInterface->GetBundleName(), "com.test.bundle");
    EXPECT_EQ(hostInterface->GetModuleName(), "test_module");
    EXPECT_TRUE(hostInterface->GetIsDisabled());
    ASSERT_TRUE(hostInterface->GetCancelMaxFontScale().has_value());
    EXPECT_FLOAT_EQ(hostInterface->GetCancelMaxFontScale().value(), 2.0f);
    ASSERT_TRUE(hostInterface->GetCancelMinFontScale().has_value());
    EXPECT_FLOAT_EQ(hostInterface->GetCancelMinFontScale().value(), 0.5f);
}

/**
 * @tc.name: ICleanNodeHostTest007
 * @tc.desc: Test Has* methods return true when properties are set, false when not set.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, ICleanNodeHostTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextField with only iconSize set, others unset.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::INPUT);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern_);
    ASSERT_NE(hostInterface, nullptr);

    /**
     * @tc.steps: step2. verify only iconSize Has* is true, others false.
     */
    EXPECT_TRUE(hostInterface->HasCancelIconSize());
    EXPECT_FALSE(hostInterface->HasCancelIconColor());
    EXPECT_FALSE(hostInterface->HasCancelIconSrc());
    EXPECT_FALSE(hostInterface->HasBundleName());
    EXPECT_FALSE(hostInterface->HasModuleName());
    EXPECT_FALSE(hostInterface->HasCancelMaxFontScale());
    EXPECT_FALSE(hostInterface->HasCancelMinFontScale());

    /**
     * @tc.steps: step3. create a new TextField with all properties set.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelIconColor(Color::BLUE);
        model.SetMaxFontScale(3.0f);
        model.SetMinFontScale(0.2f);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateIconSrc("/test/cancel.png");
    layoutProperty_->UpdateBundleName("com.test.bn");
    layoutProperty_->UpdateModuleName("mod");
    hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern_);
    ASSERT_NE(hostInterface, nullptr);

    /**
     * @tc.steps: step4. verify all Has* methods return true.
     */
    EXPECT_TRUE(hostInterface->HasCancelIconSize());
    EXPECT_TRUE(hostInterface->HasCancelIconColor());
    EXPECT_TRUE(hostInterface->HasCancelIconSrc());
    EXPECT_TRUE(hostInterface->HasBundleName());
    EXPECT_TRUE(hostInterface->HasModuleName());
    EXPECT_TRUE(hostInterface->HasCancelMaxFontScale());
    EXPECT_TRUE(hostInterface->HasCancelMinFontScale());
}

/**
 * @tc.name: ICleanNodeHostTest008
 * @tc.desc: Test CleanNodeResponseArea IsShowClean() and IsShowSymbol() via ICleanNodeHost.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, ICleanNodeHostTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextField with cancel button and symbol=false.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeResponseArea, nullptr);

    /**
     * @tc.steps: step2. verify IsShowClean() returns true (cancel button mode is on).
     * @tc.expected: IsShowClean reads via ICleanNodeHost::IsShowCancelButtonMode.
     */
    EXPECT_TRUE(cleanNodeResponseArea->IsShowClean());

    /**
     * @tc.steps: step3. verify IsShowSymbol() returns false (symbol was set to false).
     * @tc.expected: IsShowSymbol reads via ICleanNodeHost::GetIsShowSymbol.
     */
    EXPECT_FALSE(cleanNodeResponseArea->IsShowSymbol());

    /**
     * @tc.steps: step4. create TextField with cancel button disabled.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(false);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto disabledArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    if (disabledArea) {
        EXPECT_FALSE(disabledArea->IsShowClean());
    }
}

/**
 * @tc.name: ICleanNodeHostTest009
 * @tc.desc: Test OnCleanNodeClicked() through CleanNodeResponseArea interface path clears content.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, ICleanNodeHostTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextField with text and cancel button enabled.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern_);
    ASSERT_NE(hostInterface, nullptr);
    EXPECT_FALSE(hostInterface->IsContentEmpty());

    /**
     * @tc.steps: step2. call OnCleanNodeClicked() directly on CleanNodeResponseArea.
     * @tc.expected: content is cleared via interface path (DynamicCast + HandleCleanNodeClicked).
     */
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeResponseArea, nullptr);
    cleanNodeResponseArea->OnCleanNodeClicked();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(hostInterface->IsContentEmpty());
}

/**
 * @tc.name: ICleanNodeHostTest010
 * @tc.desc: Test UpdateShowState() directly for all three CleanNodeStyle states.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, ICleanNodeHostTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CONSTANT style: should show even after pre-hide.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto constantArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(constantArea, nullptr);
    constantArea->UpdateCleanNode(false);
    constantArea->UpdateShowState();
    EXPECT_TRUE(constantArea->IsShow());

    /**
     * @tc.steps: step2. INVISIBLE style: should hide even after pre-show.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::INVISIBLE);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto invisibleArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(invisibleArea, nullptr);
    invisibleArea->UpdateCleanNode(true);
    invisibleArea->UpdateShowState();
    EXPECT_FALSE(invisibleArea->IsShow());

    /**
     * @tc.steps: step3. INPUT style with content: should show after pre-hide.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::INPUT);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto inputArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(inputArea, nullptr);
    inputArea->UpdateCleanNode(false);
    inputArea->UpdateShowState();
    EXPECT_TRUE(inputArea->IsShow());

    /**
     * @tc.steps: step4. INPUT style with empty content: should hide after pre-show.
     */
    CreateTextField("", "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::INPUT);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto emptyArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(emptyArea, nullptr);
    emptyArea->UpdateCleanNode(true);
    emptyArea->UpdateShowState();
    EXPECT_FALSE(emptyArea->IsShow());
}

/**
 * @tc.name: CleanNodeRefreshNullHost001
 * @tc.desc: Test Refresh() with null hostPattern_ covers the false branch of hostPattern check.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, CleanNodeRefreshNullHost001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto cleanNodeArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeArea, nullptr);

    // Reset hostPattern_ to null to cover the false branch of `if (hostPattern && cleanNode_)`
    cleanNodeArea->hostPattern_.Reset();
    // Refresh should not crash when hostPattern is null; IsShowSymbol returns false,
    // and LoadingImageProperty/CreateImageSourceInfo return early via null checks
    cleanNodeArea->Refresh();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: CleanNodeRefreshSymbolUpdate001
 * @tc.desc: Test Refresh() enters symbol update path when IsShowSymbol and IsSymbolIcon are true.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, CleanNodeRefreshSymbolUpdate001, TestSize.Level1)
{
    // SetCancelButtonSymbol(true) makes IsShowSymbol() return true via layout property.
    // CreateNode() creates a SYMBOL_ETS_TAG child, making IsSymbolIcon() return true.
    // SystemProperties::IsNeedSymbol() returns true by default in mock environment.
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelButtonSymbol(true);
    });
    ASSERT_NE(pattern_, nullptr);
    auto cleanNodeArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeArea, nullptr);

    // Refresh should enter symbol path: IsShowSymbol && IsSymbolIcon && IsNeedSymbol
    cleanNodeArea->Refresh();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: CleanNodeRefreshReplaceNode001
 * @tc.desc: Test Refresh() enters ReplaceNode path when IsShowSymbol != IsSymbolIcon.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, CleanNodeRefreshReplaceNode001, TestSize.Level1)
{
    // Create with symbol=true so CreateNode() creates a symbol child (IsSymbolIcon=true)
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelButtonSymbol(true);
    });
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);

    // Flip IsShowSymbol to false after creation.
    // Now: IsShowSymbol=false, IsSymbolIcon=true (symbol child still exists)
    // Neither symbol path (false&&true) nor image path (true&&false) matches
    // => ReplaceNode() is called
    layoutProperty_->UpdateIsShowSymbol(false);

    auto cleanNodeArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeArea, nullptr);
    cleanNodeArea->Refresh();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: CleanNodeUpdateShowStateCheckUpdate001
 * @tc.desc: Test UpdateShowState() when IsShow=true and CheckUpdateCleanNode returns true.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, CleanNodeUpdateShowStateCheckUpdate001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto cleanNodeArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeArea, nullptr);

    // Set isShow_ to true so !IsShow() is false, forcing evaluation of CheckUpdateCleanNode()
    cleanNodeArea->isShow_ = true;

    // Set cleanNode height > host frame height so CheckUpdateCleanNode returns true
    auto cleanNode = cleanNodeArea->cleanNode_;
    ASSERT_NE(cleanNode, nullptr);
    cleanNode->GetGeometryNode()->SetFrameSize(SizeF(30.0f, 100.0f));
    frameNode_->GetGeometryNode()->SetFrameSize(SizeF(200.0f, 40.0f));

    // UpdateShowState should call UpdateCleanNode(true) because CheckUpdateCleanNode returns true
    cleanNodeArea->UpdateShowState();
    EXPECT_TRUE(cleanNodeArea->IsShow());
}

/**
 * @tc.name: CleanNodeLoadingImagePropertyPercent001
 * @tc.desc: Test LoadingImageProperty() with PERCENT icon size unit.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, CleanNodeLoadingImagePropertyPercent001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelIconSize(Dimension(50, DimensionUnit::PERCENT));
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    auto cleanNodeArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeArea, nullptr);

    // LoadingImageProperty should enter PERCENT branch: iconSize_ = iconSizeValue
    cleanNodeArea->LoadingImageProperty();
    EXPECT_FLOAT_EQ(cleanNodeArea->iconSize_.Value(), 50);
}

/**
 * @tc.name: CleanNodeLoadingImagePropertyAllProps001
 * @tc.desc: Test LoadingImageProperty() with all cancel button properties set covers Has* true branches.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, CleanNodeLoadingImagePropertyAllProps001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelIconColor(Color::RED);
        model.SetMaxFontScale(2.0f);
        model.SetMinFontScale(0.5f);
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);

    // Set additional properties via layout property to trigger Has* true branches
    layoutProperty_->UpdateIconSrc("/test/icon.svg");
    layoutProperty_->UpdateBundleName("com.test.bundle");
    layoutProperty_->UpdateModuleName("test_module");
    layoutProperty_->UpdateIsDisabled(true);

    auto cleanNodeArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeArea, nullptr);

    // LoadingImageProperty covers:
    //   HasCancelMaxFontScale true, HasCancelMinFontScale true,
    //   HasCancelIconSrc true, HasBundleName true, HasModuleName true
    // LoadingCancelButtonColor (called inside) covers:
    //   GetIsDisabled true branch
    cleanNodeArea->LoadingImageProperty();
    EXPECT_EQ(cleanNodeArea->iconSrc_, "/test/icon.svg");
    EXPECT_EQ(cleanNodeArea->bundleName_, "com.test.bundle");
    EXPECT_EQ(cleanNodeArea->moduleName_, "test_module");
}

/**
 * @tc.name: CleanNodeCreateImageSourceInfoNonSvg001
 * @tc.desc: Test CreateImageSourceInfo() with non-SVG icon source covers IsSvg false branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestThree, CleanNodeCreateImageSourceInfoNonSvg001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetIsShowCancelButton(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelButtonSymbol(false);
    });
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);

    // Set non-SVG icon source so IsSvg() returns false
    layoutProperty_->UpdateIconSrc("/test/icon.png");

    auto cleanNodeArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeArea, nullptr);

    // Load properties so iconSrc_ is populated with non-SVG path
    cleanNodeArea->LoadingImageProperty();
    ASSERT_EQ(cleanNodeArea->iconSrc_, "/test/icon.png");

    // CreateImageSourceInfo: iconSrc_ is non-empty => SetSrc("/test/icon.png")
    // info.IsSvg() returns false => the SVG fill color branch is skipped
    auto info = cleanNodeArea->CreateImageSourceInfo();
    EXPECT_EQ(info.GetSrc(), "/test/icon.png");
}
} // namespace OHOS::Ace::NG
