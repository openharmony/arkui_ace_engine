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

#include "text_area_base.h"
namespace OHOS::Ace::NG {

class TextAreaTestTwo : public TextAreaBase {};

/**
 * @tc.name: CalculateBoundsRect001
 * @tc.desc: Test is textarea, showError(true) while showCounter.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, CalculateBoundsRect001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLines(1);
        model.SetMaxLength(100);
        model.SetShowError(u"error", true);
    });
    auto height = pattern_->textFieldOverlayModifier_->rect_.Height();
    EXPECT_EQ(height, 116.0f);
}

/**
 * @tc.name: CalculateBoundsRect002
 * @tc.desc: Test is textarea, showError(false) while showCounter.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, CalculateBoundsRect002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLines(1);
        model.SetMaxLength(100);
        model.SetShowError(u"error", false);
    });
    auto height = pattern_->textFieldOverlayModifier_->rect_.Height();
    EXPECT_EQ(height, 116.0f);
}

/**
 * @tc.name: CalculateBoundsRect003
 * @tc.desc: Test is textarea, showError(false).
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, CalculateBoundsRect003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetShowError(u"error", true); });
    auto height = pattern_->textFieldOverlayModifier_->rect_.Height();
    EXPECT_EQ(height, 116.0f);
}

/**
 * @tc.name: CalculateBoundsRect004
 * @tc.desc: Test is textarea, showError(true).
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, CalculateBoundsRect004, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetShowError(u"error", true); });
    pattern_->maxFrameOffsetY_ = 5.0f;
    auto host = pattern_->GetHost();
    auto geometryNode = host->GetGeometryNode();
    RectF textRect(5.0f, 5.0f, 10.0f, 10.0f);
    SizeF size(10.0f, 10.0f);
    OffsetF translate(5.0f, 5.0f);
    geometryNode->SetContentSize(size);
    geometryNode->SetContentOffset(translate);
    pattern_->CalculateBoundsRect();
    EXPECT_EQ(pattern_->maxFrameOffsetY_, 5.0f);
}

/**
 * @tc.name: HandleOnCut001
 * @tc.desc: Test is textarea, HandleOnCut, while index of first hanele > second hanele.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, HandleOnCut001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    HandleInfoNG firstHandleInfo;
    firstHandleInfo.index = 5;
    HandleInfoNG secondHandleInfo;
    secondHandleInfo.index = 0;
    pattern_->selectController_->firstHandleInfo_ = firstHandleInfo;
    pattern_->selectController_->secondHandleInfo_ = secondHandleInfo;
    pattern_->HandleOnCut();
    EXPECT_EQ(pattern_->selectController_->firstHandleInfo_.index, 0);
}

/**
 * @tc.name: CalcScrollRect001
 * @tc.desc: Test is textarea, CalcScrollRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, CalcScrollRect001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetInputStyle(InputStyle::INLINE); });

    Rect inlineScrollRect(5.0f, 5.0f, 10.0f, 10.0f);
    pattern_->inlineMeasureItem_.inlineContentRectHeight = 1.0f;
    pattern_->CalcScrollRect(inlineScrollRect);
    EXPECT_EQ(inlineScrollRect.Height(), 2500);

    pattern_->inlineMeasureItem_.inlineContentRectHeight = 50.0f;
    pattern_->CalcScrollRect(inlineScrollRect);
    EXPECT_EQ(inlineScrollRect.Top(), -2450);
}

/**
 * @tc.name: CreateDisplayText003
 * @tc.desc: Test is textarea, CalcScrollRect at API 11;.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, CreateDisplayText003, TestSize.Level1)
{
    SystemProperties::debugEnabled_ = true;
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    std::u16string input = u"ال";
    auto res = StringUtils::Str16ToStr8(pattern_->CreateDisplayText(input, 3, true, true));
    EXPECT_EQ("••", res);

    int32_t lastPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    MockPipelineContext::GetCurrentContext()->SetMinPlatformVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    std::u16string input2 = u"اللغة العربية";
    auto res2 = StringUtils::Str16ToStr8(pattern_->CreateDisplayText(input2, 3, true, false));
    EXPECT_NE("••", res2);

    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(lastPlatformVersion);
    MockContainer::Current()->SetApiTargetVersion(lastPlatformVersion);
}

/**
 * @tc.name: UpdateSelectionAndHandleVisibility001
 * @tc.desc: Test is textarea, UpdateSelectionAndHandleVisibility while longress at diffent paragraph
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, UpdateSelectionAndHandleVisibility001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetDraggable(true); });

    auto localParagraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*localParagraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));

    pattern_->HandleOnSelectAll();
    GestureEvent info;
    info.localLocation_ = Offset(5, 5);
    pattern_->HandleLongPress(info);

    auto event = AceType::MakeRefPtr<Ace::DragEvent>();
    pattern_->releaseInDrop_ = false;
    EXPECT_TRUE(eventHub_->HasOnDragMove());
    eventHub_->FireOnDragMove(event, "");

    if (eventHub_->HasDefaultOnDragStart()) {
        (eventHub_->GetDefaultOnDragStart())(event, "");
    }
    if (eventHub_->HasOnDragEnd()) {
        (eventHub_->GetOnDragEnd())(event);
    }

    FlushLayoutTask(frameNode_);
    localParagraph = nullptr;
    EXPECT_TRUE(pattern_->showSelect_);
}

/**
 * @tc.name: UpdateSelectionAndHandleVisibility002
 * @tc.desc: Test is textarea, UpdateSelectionAndHandleVisibility while longress at diffent paragraph
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, UpdateSelectionAndHandleVisibility002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetDraggable(true); });

    auto localParagraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*localParagraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));

    pattern_->HandleOnSelectAll();
    GestureEvent info;
    info.localLocation_ = Offset(5, 5);
    pattern_->HandleLongPress(info);

    auto event = AceType::MakeRefPtr<Ace::DragEvent>();
    pattern_->releaseInDrop_ = true;
    EXPECT_TRUE(eventHub_->HasOnDragMove());
    eventHub_->FireOnDragMove(event, "");

    if (eventHub_->HasDefaultOnDragStart()) {
        (eventHub_->GetDefaultOnDragStart())(event, "");
    }
    if (eventHub_->HasOnDragEnd()) {
        (eventHub_->GetOnDragEnd())(event);
    }

    FlushLayoutTask(frameNode_);
    localParagraph = nullptr;
    EXPECT_TRUE(pattern_->showSelect_);
}

/**
 * @tc.name: UpdateSelectionAndHandleVisibility003
 * @tc.desc: Test is textarea, UpdateSelectionAndHandleVisibility while longress at diffent paragraph
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, UpdateSelectionAndHandleVisibility003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetDraggable(true); });

    auto localParagraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*localParagraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));

    pattern_->HandleOnSelectAll();
    GestureEvent info;
    info.localLocation_ = Offset(5, 5);
    pattern_->HandleLongPress(info);

    auto event = AceType::MakeRefPtr<Ace::DragEvent>();
    event->sourceTool_ = SourceTool::MOUSE;
    pattern_->releaseInDrop_ = true;
    EXPECT_TRUE(eventHub_->HasOnDragMove());
    eventHub_->FireOnDragMove(event, "");

    if (eventHub_->HasDefaultOnDragStart()) {
        (eventHub_->GetDefaultOnDragStart())(event, "");
    }
    if (eventHub_->HasOnDragEnd()) {
        (eventHub_->GetOnDragEnd())(event);
    }

    FlushLayoutTask(frameNode_);
    localParagraph = nullptr;
    EXPECT_TRUE(pattern_->showSelect_);
}

/**
 * @tc.name: UpdateSelectionAndHandleVisibility004
 * @tc.desc: Test is textarea, UpdateSelectionAndHandleVisibility while longress at diffent paragraph
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, UpdateSelectionAndHandleVisibility004, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetDraggable(true); });

    auto localParagraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*localParagraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));

    pattern_->HandleOnSelectAll();
    GestureEvent info;
    info.localLocation_ = Offset(5, 5);
    pattern_->HandleLongPress(info);

    auto event = AceType::MakeRefPtr<Ace::DragEvent>();
    event->sourceTool_ = SourceTool::UNKNOWN;
    pattern_->releaseInDrop_ = true;
    EXPECT_TRUE(eventHub_->HasOnDragMove());
    eventHub_->FireOnDragMove(event, "");

    if (eventHub_->HasDefaultOnDragStart()) {
        (eventHub_->GetDefaultOnDragStart())(event, "");
    }
    if (eventHub_->HasOnDragEnd()) {
        (eventHub_->GetOnDragEnd())(event);
    }

    FlushLayoutTask(frameNode_);
    localParagraph = nullptr;
    EXPECT_TRUE(pattern_->showSelect_);
}

/**
 * @tc.name: UpdateSelectionAndHandleVisibility005
 * @tc.desc: Test is textarea, UpdateSelectionAndHandleVisibility while longress at diffent paragraph
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, UpdateSelectionAndHandleVisibility005, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetDraggable(true); });

    auto localParagraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 4, 4), RectF(5, 5, 20, 20) };
    EXPECT_CALL(*localParagraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));

    pattern_->HandleOnSelectAll();
    GestureEvent info;
    info.localLocation_ = Offset(6, 6);
    pattern_->HandleLongPress(info);

    auto event = AceType::MakeRefPtr<Ace::DragEvent>();
    event->sourceTool_ = SourceTool::UNKNOWN;
    pattern_->releaseInDrop_ = true;
    EXPECT_TRUE(eventHub_->HasOnDragMove());
    eventHub_->FireOnDragMove(event, "");

    if (eventHub_->HasDefaultOnDragStart()) {
        (eventHub_->GetDefaultOnDragStart())(event, "");
    }
    if (eventHub_->HasOnDragEnd()) {
        (eventHub_->GetOnDragEnd())(event);
    }

    FlushLayoutTask(frameNode_);
    localParagraph = nullptr;
    EXPECT_TRUE(pattern_->showSelect_);
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: Test is textarea, HandleLongPress() while longress at diffent paragraph
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, HandleLongPress001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetDraggable(true);
        model.SetType(TextInputType::UNSPECIFIED);
        model.SetDraggable(true);
    });

    auto localParagraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*localParagraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));

    pattern_->HandleOnSelectAll();
    GestureEvent info;
    info.localLocation_ = Offset(5, 5);
    pattern_->HandleLongPress(info);

    EXPECT_FALSE(pattern_->isLongPress_);
}

/**
 * @tc.name: HandleLongPress002
 * @tc.desc: Test is textarea, HandleLongPress() while longress at diffent paragraph
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, HandleLongPress002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetDraggable(true);
        model.SetType(TextInputType::UNSPECIFIED);
        model.SetShowUnderline(true);
        model.SetDraggable(true);
    });

    auto localParagraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*localParagraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));

    pattern_->HandleOnSelectAll();
    GestureEvent info;
    info.localLocation_ = Offset(5, 5);
    pattern_->HandleLongPress(info);

    EXPECT_FALSE(pattern_->isLongPress_);
}

/**
 * @tc.name: HandleLongPress003
 * @tc.desc: Test is textarea, HandleLongPress() while longress with two finger
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, HandleLongPress003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetDraggable(true);
        model.SetType(TextInputType::UNSPECIFIED);
        model.SetShowUnderline(true);
        model.SetDraggable(true);
    });

    auto localParagraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*localParagraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));

    pattern_->HandleOnSelectAll();
    GestureEvent info;
    info.localLocation_ = Offset(5, 5);
    pattern_->longPressFingerNum_ = 2;
    pattern_->HandleLongPress(info);

    EXPECT_FALSE(pattern_->isLongPress_);
}

/**
 * @tc.name: OnKeyEvent001
 * @tc.desc: Test is textarea, OnKeyEvent(KEY_ENTER), case KEY_ENTER & HasFocus & independentControlKeyboard_
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, OnKeyEvent001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    KeyEvent keyE;
    keyE.code = KeyCode::KEY_ENTER;
    pattern_->independentControlKeyboard_ = true;
    EXPECT_TRUE(pattern_->OnKeyEvent(keyE));

    // no focus
    auto focushHub = pattern_->GetFocusHub();
    focushHub->currentFocus_ = false;
    pattern_->HandleBlurEvent();
    FlushLayoutTask(frameNode_);

    // GetFocus() & independentControlKeyboard_
    pattern_->independentControlKeyboard_ = false;
    EXPECT_FALSE(pattern_->OnKeyEvent(keyE));
}

/**
 * @tc.name: OnKeyEvent002
 * @tc.desc: Test is textarea, OnKeyEvent(KEY_DPAD_LEFT), case directionKeysMoveFocusOut_ & IsMoveFocusOutFromLeft
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, OnKeyEvent002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    KeyEvent keyE;
    keyE.code = KeyCode::KEY_DPAD_LEFT;
    HandleInfoNG caretInfo;
    caretInfo.index = 0;

    // !directionKeysMoveFocusOut_
    pattern_->directionKeysMoveFocusOut_ = false;
    EXPECT_FALSE(pattern_->OnKeyEvent(keyE));

    // directionKeysMoveFocusOut_ & IsMoveFocusOutFromLeft()
    pattern_->directionKeysMoveFocusOut_ = true;
    pattern_->selectController_->caretInfo_ = caretInfo;
    EXPECT_FALSE(pattern_->OnKeyEvent(keyE));
    caretInfo.index = 1;
    pattern_->selectController_->caretInfo_ = caretInfo;
    EXPECT_FALSE(pattern_->OnKeyEvent(keyE));
}

/**
 * @tc.name: OnKeyEvent003
 * @tc.desc: Test is textarea, OnKeyEvent(KEY_DPAD_RIGHT), case directionKeysMoveFocusOut_ & IsMoveFocusOutFromRight
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, OnKeyEvent003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    KeyEvent keyE;
    keyE.code = KeyCode::KEY_DPAD_RIGHT;
    HandleInfoNG caretInfo;
    caretInfo.index = 26;

    // directionKeysMoveFocusOut_ & IsMoveFocusOutFromRight()
    pattern_->directionKeysMoveFocusOut_ = true;
    pattern_->selectController_->caretInfo_ = caretInfo;
    EXPECT_FALSE(pattern_->OnKeyEvent(keyE));
}

/**
 * @tc.name: HandleTouchMove001
 * @tc.desc: Test is textarea, HandleTouchMove(), case isTouchCaret && isMoveCaret = (true,true)
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, HandleTouchMove001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    TouchEventInfo info("type");
    TouchLocationInfo location(1);
    Offset pos;
    pos.deltaX_ = 10.0;
    pos.deltaY_ = 10.0;
    location.SetLocalLocation(pos);
    info.touches_.emplace_back(location);
    auto offset = info.GetTouches().front().GetLocalLocation();

    auto manager = SelectContentOverlayManager::GetOverlayManager();
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    manager->selectOverlayHolder_ = holder;
    pattern_->selectOverlay_->OnBind(manager);
    Ace::NG::SelectOverlayInfo soi;
    soi.enableHandleLevel = true;
    manager->CreateSelectOverlay(soi, true);

    pattern_->moveCaretState_.isMoveCaret = false;
    pattern_->moveCaretState_.touchDownOffset = Offset(0, 0);
    pattern_->HandleTouchMove(location);
    EXPECT_TRUE(pattern_->selectOverlay_->SelectOverlayIsOn());
}

/**
 * @tc.name: HandleTouchMove002
 * @tc.desc: Test is textarea, HandleTouchMove(), case isTouchCaret && isMoveCaret = (true,false)
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, HandleTouchMove002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    TouchEventInfo info("type");
    TouchLocationInfo location(1);
    Offset pos;
    pos.deltaX_ = 10.0;
    pos.deltaY_ = 10.0;
    location.SetLocalLocation(pos);
    info.touches_.emplace_back(location);
    auto offset = info.GetTouches().front().GetLocalLocation();

    auto manager = SelectContentOverlayManager::GetOverlayManager();
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    manager->selectOverlayHolder_ = holder;
    pattern_->selectOverlay_->OnBind(manager);
    Ace::NG::SelectOverlayInfo soi;
    soi.enableHandleLevel = true;
    manager->CreateSelectOverlay(soi, true);

    pattern_->moveCaretState_.isMoveCaret = true;
    pattern_->moveCaretState_.touchDownOffset = Offset(0, 0);
    pattern_->HandleTouchMove(location);
    EXPECT_TRUE(pattern_->selectOverlay_->SelectOverlayIsOn());
}

/**
 * @tc.name: HandleTouchMove002
 * @tc.desc: Test is textarea, HandleTouchMove(), case SelectOverlayIsOn = (false)
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, HandleTouchMove003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    TouchEventInfo info("type");
    TouchLocationInfo location(1);
    Offset pos;
    pos.deltaX_ = 10.0;
    pos.deltaY_ = 10.0;
    location.SetLocalLocation(pos);
    info.touches_.emplace_back(location);
    auto offset = info.GetTouches().front().GetLocalLocation();

    auto manager = SelectContentOverlayManager::GetOverlayManager();
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    manager->selectOverlayHolder_ = holder;
    pattern_->selectOverlay_->OnBind(manager);
    Ace::NG::SelectOverlayInfo soi;
    soi.enableHandleLevel = true;
    manager->CreateSelectOverlay(soi, true);

    pattern_->moveCaretState_.isMoveCaret = false;
    pattern_->moveCaretState_.touchDownOffset = Offset(0, 0);
    pattern_->HandleTouchMove(location);
    EXPECT_TRUE(pattern_->selectOverlay_->SelectOverlayIsOn());
}

} // namespace OHOS::Ace::NG