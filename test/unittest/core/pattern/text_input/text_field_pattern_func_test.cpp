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
#include "test/mock/core/common/mock_container.h"

namespace OHOS::Ace::NG {

namespace {
const int32_t TWO = 2;
const int32_t FIVE = 5;
constexpr FrameNodeChangeInfoFlag AVOID_KEYBOARD_END_FALG = 1<<8;
} // namespace

class TextFieldPatternFuncTest : public TextInputBases {
public:
};

Rect MyGetTextContentRect()
{
    return { TWO, TWO, TWO, TWO };
}

int32_t MyGetTextContentLinesNum()
{
    return FIVE;
}

int32_t MyGetCaretIndex()
{
    return FIVE;
}

NG::OffsetF MyGetCaretPosition()
{
    return OffsetF(FIVE, FIVE);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc001, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    std::u16string content;
    pattern->InitEditingValueText(content);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc002, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    std::u16string content = u"openharmony";
    ASSERT_NE(pattern->contentController_, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);
    pattern->deleteBackwardOperations_.push(1);
    pattern->InitEditingValueText(content);
    EXPECT_NE(StringUtils::Str16ToStr8(pattern->contentController_->content_), StringUtils::Str16ToStr8(content));
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc003, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    std::u16string content = u"openharmony";
    ASSERT_NE(pattern->contentController_, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);
    pattern->deleteBackwardOperations_.push(1);
    pattern->hasPreviewText_ = true;
    pattern->InitEditingValueText(content);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc004, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    std::u16string content;
    bool state = pattern->InitValueText(content);
    EXPECT_TRUE(state);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc005, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    std::u16string content = u"openharmony";
    pattern->hasPreviewText_ = true;
    pattern->deleteBackwardOperations_.push(1);
    bool state = pattern->InitValueText(content);
    EXPECT_FALSE(state);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc006, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->contentController_, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);
    std::u16string content;
    pattern->hasPreviewText_ = true;
    pattern->deleteBackwardOperations_.push(1);
    bool state = pattern->InitValueText(content);
    EXPECT_FALSE(state);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc007, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->contentController_, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);
    pattern->mouseEvent_ = nullptr;
    pattern->hoverEvent_ = nullptr;
    MouseInfo info;
    pattern->InitMouseEvent();
    pattern->mouseEvent_->onMouseCallback_(info);
    HoverInfo hoverInfo;
    pattern->hoverEvent_->onHoverEventCallback_(false, hoverInfo);
    EXPECT_TRUE(pattern->mouseEvent_->onMouseCallback_ != nullptr);
    EXPECT_TRUE(pattern->hoverEvent_->onHoverEventCallback_ != nullptr);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc008, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->contentController_, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);
    auto mouseCallback = [](MouseInfo& info) {};
    auto hoverCallback = [](MouseInfo& info) {};
    pattern->mouseEvent_ = AceType::MakeRefPtr<InputEvent>(std::move(mouseCallback));
    pattern->hoverEvent_ = AceType::MakeRefPtr<InputEvent>(std::move(hoverCallback));
    MouseInfo info;
    pattern->InitMouseEvent();
    EXPECT_TRUE(pattern->mouseEvent_->onMouseCallback_ != nullptr);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc009, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->contentController_, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);
    auto actionStartTask = [](const GestureEvent& info) {};
    auto actionUpdateTask = [](const GestureEvent& info) {};
    auto actionEndTask = [](const GestureEvent& info) {};
    auto actionCancelTask = []() {};
    pattern->boxSelectPanEvent_ = AceType::MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    pattern->InitPanEvent();
    EXPECT_TRUE(pattern->GetHost()->GetOrCreateGestureEventHub()->panEventActuator_ != nullptr);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc010, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->contentController_, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);
    pattern->boxSelectPanEvent_ = nullptr;
    pattern->InitPanEvent();
    const RefPtr<NG::GestureInfo> gestureInfo = AceType::MakeRefPtr<NG::GestureInfo>();
    gestureInfo->SetType(GestureTypeName::BOXSELECT);
    gestureInfo->SetInputEventType(InputEventType::MOUSE_BUTTON);
    const std::shared_ptr<BaseGestureEvent> info;
    auto state = pattern->GetHost()->GetOrCreateGestureEventHub()->gestureJudgeNativeFunc_(gestureInfo, info);
    EXPECT_TRUE(state == GestureJudgeResult::REJECT);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc011, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->contentController_, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);
    pattern->boxSelectPanEvent_ = nullptr;
    pattern->InitPanEvent();
    const RefPtr<NG::GestureInfo> gestureInfo = AceType::MakeRefPtr<NG::GestureInfo>();
    gestureInfo->SetType(GestureTypeName::CLICK);
    gestureInfo->SetInputEventType(InputEventType::TOUCH_PAD);
    const std::shared_ptr<BaseGestureEvent> info;
    pattern->GetHost()->SetDraggable(true);
    pattern->isPressSelectedBox_ = true;
    auto state = pattern->GetHost()->GetOrCreateGestureEventHub()->gestureJudgeNativeFunc_(gestureInfo, info);
    EXPECT_TRUE(state == GestureJudgeResult::CONTINUE);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc012, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    HoverInfo info;
    pattern->OnHover(true, info);
    EXPECT_TRUE(pattern->isOnHover_ == true);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc013, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    HoverInfo info;
    pattern->OnHover(false, info);
    EXPECT_FALSE(pattern->isOnHover_ == true);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc014, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    MouseInfo info;
    pattern->dragStatus_ = DragStatus::ON_DROP;
    pattern->HandleMouseEvent(info);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc015, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    ASSERT_NE(pattern->scrollBar_, nullptr);
    pattern->scrollBar_->SetPressed(true);
    MouseInfo info;
    pattern->dragStatus_ = DragStatus::DRAGGING;
    pattern->HandleMouseEvent(info);
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    EXPECT_TRUE(frameId == pattern->GetHost()->GetId());
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc016, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    ASSERT_NE(pattern->scrollBar_, nullptr);

    pattern->scrollBar_ = nullptr;
    MouseInfo info;
    info.SetButton(MouseButton::RIGHT_BUTTON);
    info.SetAction(OHOS::Ace::MouseAction::PRESS);
    pattern->HandleMouseEvent(info);
    EXPECT_TRUE(pattern->cursorVisible_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc017, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    ASSERT_NE(pattern->scrollBar_, nullptr);

    pattern->scrollBar_ = nullptr;
    MouseInfo info;
    Offset location(33.0, 33.0);
    info.SetGlobalLocation(location);
    info.SetButton(MouseButton::RIGHT_BUTTON);
    info.SetAction(OHOS::Ace::MouseAction::RELEASE);
    pattern->hasPreviewText_ = false;
    pattern->GetFocusHub()->currentFocus_ = true;
    pattern->HandleMouseEvent(info);
    OffsetF tempLocation(location.GetX(), location.GetY());
    EXPECT_TRUE(pattern->selectOverlay_->mouseMenuOffset_ == tempLocation);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc018, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    ASSERT_NE(pattern->scrollBar_, nullptr);

    pattern->scrollBar_ = nullptr;
    MouseInfo info;
    info.SetAction(OHOS::Ace::MouseAction::PRESS);
    info.SetButton(MouseButton::LEFT_BUTTON);
    pattern->HandleMouseEvent(info);
    EXPECT_TRUE(pattern->leftMouseCanMove_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc019, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->scrollBar_ = nullptr;
    MouseInfo info;
    info.SetAction(OHOS::Ace::MouseAction::MOVE);
    info.SetButton(MouseButton::LEFT_BUTTON);
    pattern->HandleMouseEvent(info);
    EXPECT_TRUE(pattern->showSelect_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc020, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->scrollBar_ = nullptr;
    MouseInfo info;
    info.SetAction(OHOS::Ace::MouseAction::RELEASE);
    info.SetButton(MouseButton::LEFT_BUTTON);
    pattern->HandleMouseEvent(info);
    EXPECT_FALSE(pattern->blockPress_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc021, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->scrollBar_ = nullptr;
    MouseInfo info;
    info.SetAction(OHOS::Ace::MouseAction::RELEASE);
    pattern->HandleRightMouseEvent(info);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc022, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->scrollBar_ = nullptr;
    MouseInfo info;
    info.SetAction(OHOS::Ace::MouseAction::PRESS);
    pattern->HandleRightMouseEvent(info);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc023, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    MouseInfo info;
    info.SetAction(OHOS::Ace::MouseAction::PRESS);
    pattern->cursorVisible_ = true;
    ASSERT_NE(pattern->GetFocusHub(), nullptr);
    pattern->GetFocusHub()->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();
    pattern->GetFocusHub()->focusCallbackEvents_->isFocusOnTouch_ = false;
    pattern->FocusAndUpdateCaretByMouse(info);
    EXPECT_FALSE(pattern->cursorVisible_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc024, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    MouseInfo info;
    info.SetAction(OHOS::Ace::MouseAction::PRESS);
    pattern->cursorVisible_ = true;
    ASSERT_NE(pattern->GetFocusHub(), nullptr);
    pattern->GetFocusHub()->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();
    pattern->GetFocusHub()->focusCallbackEvents_->isFocusOnTouch_ = true;
    pattern->FocusAndUpdateCaretByMouse(info);
    EXPECT_TRUE(pattern->cursorVisible_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc025, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    MouseInfo info;
    pattern->leftMouseCanMove_ = false;
    pattern->HandleLeftMouseMoveEvent(info);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc026, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    MouseInfo info;
    pattern->leftMouseCanMove_ = true;
    pattern->GetFocusHub()->currentFocus_ = false;
    pattern->HandleLeftMouseMoveEvent(info);
    EXPECT_FALSE(pattern->mouseStatus_ == MouseStatus::MOVE);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc027, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    MouseInfo info;
    pattern->blockPress_ = true;
    pattern->mouseStatus_ = MouseStatus::PRESSED;
    pattern->HandleLeftMouseReleaseEvent(info);
    EXPECT_FALSE(pattern->cursorVisible_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc028, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    Offset offset;
    float height = 1.0;
    pattern->GetFocusHub()->currentFocus_ = false;
    pattern->UpdateTextFieldManager(offset, height);
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    EXPECT_FALSE(textFieldManager == nullptr);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc029, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    Offset offset;
    float height = 0.0;
    pattern->GetFocusHub()->currentFocus_ = true;
    pattern->UpdateTextFieldManager(offset, height);
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    EXPECT_FALSE(textFieldManager->onFocusTextField_.Invalid());
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc030, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->isTextInput_ = true;
    auto state = pattern->GetDefaultTextInputAction();
    EXPECT_TRUE(state == TextInputAction::DONE);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc031, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->keyboard_ = TextInputType::TEXT;
    pattern->KeyboardContentTypeToInputType();
    EXPECT_FALSE(pattern->keyboard_ == TextInputType::VISIBLE_PASSWORD);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc032, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->showKeyBoardOnFocus_ = false;
    EXPECT_FALSE(pattern->RequestKeyboard(false, false, false));
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc033, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->showKeyBoardOnFocus_ = true;
    pattern->customKeyboard_ = AceType::MakeRefPtr<CustomNode>(1, "");
    pattern->isCustomKeyboardAttached_ = true;
    pattern->RequestKeyboard(false, false, false);
    EXPECT_TRUE(pattern->RequestCustomKeyboard());
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc034, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->showKeyBoardOnFocus_ = true;
    pattern->customKeyboard_ = nullptr;
    pattern->customKeyboardBuilder_ = nullptr;
    pattern->isCustomKeyboardAttached_ = true;
#define ENABLE_STANDARD_INPUT
    auto state = pattern->RequestKeyboard(false, false, false);
    EXPECT_FALSE(state);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc035, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->showKeyBoardOnFocus_ = true;
    pattern->customKeyboard_ = nullptr;
    pattern->customKeyboardBuilder_ = nullptr;
    pattern->isCustomKeyboardAttached_ = true;
#define ENABLE_STANDARD_INPUT
    auto contextPtr = pattern->GetHost()->GetContextRefPtr();
    contextPtr->textFieldManager_ = AceType::MakeRefPtr<ManagerInterface>();
    pattern->RequestKeyboard(false, false, false);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc037, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->connection_ = nullptr;
    pattern->keyboard_ = TextInputType::VISIBLE_PASSWORD;
    pattern->RequestKeyboardCrossPlatForm(true);
    EXPECT_TRUE(pattern->connection_ == nullptr);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc038, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextInputType type = TextInputType::MULTILINE;
    auto state = pattern->ConvertToAceAutoFillType(type);
    EXPECT_TRUE(state == AceAutoFillType::ACE_UNSPECIFIED);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc039, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextInputType type = TextInputType::VISIBLE_PASSWORD;
    auto state = pattern->ConvertToAceAutoFillType(type);
    EXPECT_TRUE(state == AceAutoFillType::ACE_PASSWORD);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc040, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextContentType type = TextContentType::VISIBLE_PASSWORD;
    auto state = pattern->TextContentTypeToAceAutoFillType(type);
    EXPECT_TRUE(state == AceAutoFillType::ACE_PASSWORD);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc041, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextContentType type = TextContentType(38);
    auto state = pattern->TextContentTypeToAceAutoFillType(type);
    EXPECT_TRUE(state == AceAutoFillType::ACE_UNSPECIFIED);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc042, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->cursorVisible_ = true;
    pattern->CloseKeyboard(true, true);
    EXPECT_FALSE(pattern->cursorVisible_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc043, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->CloseKeyboard(false, false));
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc044, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->customKeyboard_ = AceType::MakeRefPtr<CustomNode>(1, "");
    pattern->isCustomKeyboardAttached_ = true;
    pattern->CloseKeyboard(true, false);
    EXPECT_TRUE(pattern->isCustomKeyboardAttached_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc045, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetCustomKeyboardOption(true);
    EXPECT_TRUE(pattern->keyboardAvoidance_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc046, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->isCustomKeyboardAttached_ = true;
    auto state = pattern->RequestCustomKeyboard();
    EXPECT_TRUE(state);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc047, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->isCustomKeyboardAttached_ = false;
    pattern->customKeyboard_ = nullptr;
    pattern->customKeyboardBuilder_ = nullptr;
    auto state = pattern->RequestCustomKeyboard();
    EXPECT_FALSE(state);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc048, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->keyboardOverlay_ = AceType::MakeRefPtr<OverlayManager>(AceType::DynamicCast<FrameNode>(pattern));
    pattern->CloseCustomKeyboard();
    EXPECT_FALSE(pattern->isCustomKeyboardAttached_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc049, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    std::u16string insertValue;
    int32_t offset = 0.0;
    auto state = pattern->BeforeIMEInsertValue(insertValue, offset);
    EXPECT_TRUE(state);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc050, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto state = false;
    auto callback = [&state](const InsertValueInfo&){ state = true; };
    pattern->GetHost()->GetOrCreateEventHub<TextFieldEventHub>()->SetOnDidInsertValueEvent(callback);
    std::u16string insertValue;
    pattern->AfterIMEInsertValue(insertValue);
    EXPECT_TRUE(state);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc051, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto state = false;
    auto eventHub = pattern->GetHost()->GetOrCreateEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto callback = [&state](const InsertValueInfo& info){ return (state = true); };
    eventHub->SetOnWillInsertValueEvent(callback);
    InsertCommandInfo info;
    info.insertValue = u"";
    info.reason = InputReason::IME;
    pattern->ExecuteInsertValueCommand(info);
    EXPECT_TRUE(state);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc052, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);

    auto eventHub = pattern->GetHost()->GetOrCreateEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto state = false;
    auto callback = [&state](const InsertValueInfo&){ return (state = true); };
    eventHub->SetOnWillInsertValueEvent(callback);
    pattern->selectController_->firstHandleInfo_.index = 0;
    pattern->selectController_->secondHandleInfo_.index = 0;

    InsertCommandInfo info;
    info.insertValue = u"";
    info.reason = InputReason::IME;
    pattern->ExecuteInsertValueCommand(info);
    EXPECT_TRUE(state);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc053, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);

    auto eventHub = pattern->GetHost()->GetOrCreateEventHub<TextFieldEventHub>();
    auto state = false;
    auto callback = [&state](const DeleteValueInfo&){ state = true; };
    eventHub->SetOnDidDeleteEvent(callback);
    pattern->selectController_->firstHandleInfo_.index = 0;
    pattern->selectController_->secondHandleInfo_.index = 0;

    pattern->AddInsertCommand(u"", InputReason::IME);
    EXPECT_FALSE(pattern->cursorVisible_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc054, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);

    pattern->hasPreviewText_ = true;
    std::u16string insertValue;
    EXPECT_TRUE(pattern->FinishTextPreviewByPreview(insertValue));
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc055, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);

    pattern->hasPreviewText_ = false;
    std::u16string insertValue;
    EXPECT_FALSE(pattern->FinishTextPreviewByPreview(insertValue));
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc056, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);

    pattern->hasPreviewText_ = false;
    std::u16string insertValue;
    EXPECT_FALSE(pattern->FinishTextPreviewByPreview(insertValue));
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc057, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    std::u16string insertValue = u"1";
    pattern->obscureTickCountDown_ = 10;
    pattern->UpdateObscure(insertValue, false);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc058, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto eventHub = pattern->GetFocusHub();
    eventHub->currentFocus_ = false;
    pattern->InsertValue(u"", true);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc059, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto eventHub = pattern->GetFocusHub();
    eventHub->currentFocus_ = true;
    pattern->isEdit_ = false;
    pattern->InsertValue(u"", true);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc060, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto eventHub = pattern->GetFocusHub();
    eventHub->currentFocus_ = true;
    pattern->isEdit_ = true;
    pattern->focusIndex_ = FocuseIndex::CANCEL;
    pattern->InsertValue(u"", true);
    EXPECT_TRUE(pattern->HandleSpaceEvent());
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc061, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto eventHub = pattern->GetFocusHub();
    eventHub->currentFocus_ = true;
    pattern->isEdit_ = true;
    while (!pattern->inputOperations_.empty()) {
        pattern->inputOperations_.pop();
    }

    pattern->focusIndex_ = FocuseIndex::TEXT;
    pattern->hasPreviewText_ = true;
    pattern->InsertValue(u"", true);
    EXPECT_FALSE(pattern->inputOperations_.empty());
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc062, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto eventHub = pattern->GetFocusHub();
    eventHub->currentFocus_ = true;
    pattern->isEdit_ = true;
    while (!pattern->insertCommands_.empty()) {
        pattern->insertCommands_.pop();
    }

    pattern->focusIndex_ = FocuseIndex::TEXT;
    pattern->hasPreviewText_ = false;
    pattern->InsertValue(u"", true);
    EXPECT_FALSE(pattern->insertCommands_.empty());
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc063, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->propInputStyle_ = InputStyle::INLINE;
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propTextInputType_ = TextInputType::TEXT;
    pattern->contentController_->Reset();
    pattern->ProcessFocusStyle();
    EXPECT_TRUE(pattern->inlineFocusState_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc064, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->propInputStyle_ = InputStyle::INLINE;
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propTextInputType_ = TextInputType::TEXT;
    pattern->contentController_->Reset();
    pattern->blurReason_ = BlurReason::FOCUS_SWITCH;
    pattern->contentController_->SetTextValue(u"openharmony");
    pattern->ProcessFocusStyle();
    EXPECT_TRUE(pattern->inlineSelectAllFlag_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc065, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->propInputStyle_ = InputStyle::INLINE;

    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propTextInputType_ = TextInputType::TEXT;
    pattern->contentController_->Reset();
    pattern->blurReason_ = BlurReason::WINDOW_BLUR;
    pattern->contentController_->SetTextValue(u"openharmony");
    pattern->ProcessFocusStyle();
    EXPECT_FALSE(pattern->inlineSelectAllFlag_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc066, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propShowUnderline_ = true;
    layoutProperty->propTextInputType_ = TextInputType::TEXT;
    pattern->underlineWidth_ = 1.0_px;
    pattern->GetFocusHub()->currentFocus_ = false;
    pattern->ProcessFocusStyle();
    EXPECT_TRUE(pattern->underlineWidth_ == 2.0_px);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc067, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    pattern->contentController_->SetTextValue(u"openharmony");
    layoutProperty->propSelectAllValue_ = true;
    pattern->HandleFocusEvent();
    EXPECT_TRUE(pattern->needSelectAll_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc068, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->contentController_->SetTextValue(u"");

    auto layoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propMaxViewLines_ = 200000;
    pattern->HandleFocusEvent();
    EXPECT_FALSE(pattern->needSelectAll_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc069, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->contentController_->SetTextValue(u"");

    auto layoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propMaxViewLines_ = 00000;
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    auto instance = AceType::MakeRefPtr<TextFieldManagerNG>();
    instance->needToRequestKeyboard_ = false;
    pipeline->textFieldManager_ = instance;
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    ASSERT_NE(textFieldManager, nullptr);
    pattern->HandleFocusEvent();
    EXPECT_TRUE(textFieldManager->needToRequestKeyboard_);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc0570, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->moveCaretState_.isTouchCaret = true;
    pattern->moveCaretState_.isMoveCaret = false;
    TouchEventInfo info("type");
    TouchLocationInfo location(1);
    Offset pos;
    pos.deltaX_ = 10.0;
    pos.deltaY_ = 10.0;
    location.SetLocalLocation(pos);
    info.touches_.emplace_back(location);
    auto offset = info.GetTouches().front().GetLocalLocation();
    pattern->moveCaretState_.touchDownOffset = Offset(0, 0);
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(AceType::MakeRefPtr<TextFieldPattern>());
    pattern->HandleTouchMove(location);
    EXPECT_TRUE(pattern->moveCaretState_.isMoveCaret);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc071, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->moveCaretState_.isTouchCaret = false;
    pattern->moveCaretState_.isMoveCaret = false;

    pattern->isTouchPreviewText_ = true;
    pattern->hasPreviewText_ = true;
    TouchEventInfo info("type");
    TouchLocationInfo location(1);
    Offset pos;
    pos.deltaX_ = 10.0;
    pos.deltaY_ = 10.0;
    location.SetLocalLocation(pos);
    info.touches_.emplace_back(location);
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(AceType::MakeRefPtr<TextFieldPattern>());
    pattern->HandleTouchMove(location);
    EXPECT_TRUE(pattern->cursorVisible_);
}

/**
 * @tc.name: TextPatternFunc072
 * @tc.desc: test FindNavNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc072, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    RefPtr<UINode> element = AceType::Claim<UINode>(Referenced::RawPtr(textFieldNode));
    ASSERT_NE(element, nullptr);
    element->tag_ = V2::SHEET_WRAPPER_TAG;
    textFieldNode->SetParent(element, false);
    auto result = textFieldManager->FindNavNode(textFieldNode);
    auto parent = textFieldNode->GetAncestorNodeOfFrame(false);
    auto sheetNode = parent->GetChildAtIndex(0);
    EXPECT_EQ(result, sheetNode);
}

/**
 * @tc.name: TextPatternFunc073
 * @tc.desc: test FindNavNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc073, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    auto result = textFieldManager->FindNavNode(textFieldNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: TextPatternFunc074
 * @tc.desc: test FindNavNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc074, TestSize.Level1)
{
    CreateTextField();
    auto frameId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode1 = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId1, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode1, nullptr);
    auto textFieldNode2 = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId2, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode2, nullptr);
    RefPtr<TextFieldPattern> pattern1 = textFieldNode1->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern1, nullptr);
    RefPtr<TextFieldPattern> pattern2 = textFieldNode2->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern2, nullptr);
    auto manager = pattern1->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    RefPtr<UINode> element1 = AceType::Claim<UINode>(Referenced::RawPtr(textFieldNode1));
    ASSERT_NE(element1, nullptr);
    element1->tag_ = V2::NAVDESTINATION_VIEW_ETS_TAG;
    textFieldNode1->SetParent(element1);
    RefPtr<UINode> navigationNode = AceType::Claim<UINode>(Referenced::RawPtr(textFieldNode2));
    ASSERT_NE(navigationNode, nullptr);
    navigationNode->tag_ = V2::NAVIGATION_VIEW_ETS_TAG;
    element1->SetParent(navigationNode);
    auto oldParent = textFieldNode1->GetAncestorNodeOfFrame(false);
    auto result = textFieldManager->FindNavNode(textFieldNode1);
    auto newParent = textFieldNode1->GetAncestorNodeOfFrame(false);
    EXPECT_EQ(oldParent, newParent);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: TextPatternFunc075
 * @tc.desc: test FindNavNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc075, TestSize.Level1)
{
    CreateTextField();
    auto frameId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode1 = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId1, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode1, nullptr);
    auto textFieldNode2 = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId2, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode2, nullptr);
    RefPtr<TextFieldPattern> pattern1 = textFieldNode1->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern1, nullptr);
    RefPtr<TextFieldPattern> pattern2 = textFieldNode2->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern2, nullptr);
    auto manager = pattern1->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    RefPtr<UINode> element1 = AceType::Claim<UINode>(Referenced::RawPtr(textFieldNode1));
    ASSERT_NE(element1, nullptr);
    element1->tag_ = V2::NAVDESTINATION_VIEW_ETS_TAG;
    textFieldNode1->SetParent(element1);
    RefPtr<UINode> navigationNode = AceType::Claim<UINode>(Referenced::RawPtr(textFieldNode2));
    ASSERT_NE(navigationNode, nullptr);
    navigationNode->tag_ = V2::NAVDESTINATION_VIEW_ETS_TAG;
    element1->SetParent(navigationNode);
    auto oldParent = textFieldNode1->GetAncestorNodeOfFrame(false);
    auto oldNavigationNode = oldParent->GetAncestorNodeOfFrame(false);
    auto result = textFieldManager->FindNavNode(textFieldNode1);
    auto newParent = textFieldNode1->GetAncestorNodeOfFrame(false);
    auto newNavigationNode = oldParent->GetAncestorNodeOfFrame(false);
    EXPECT_EQ(oldNavigationNode, newNavigationNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: TextPatternFunc076
 * @tc.desc: test FindNavNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc076, TestSize.Level1)
{
    CreateTextField();
    auto frameId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode1 = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId1, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode1, nullptr);
    auto textFieldNode2 = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId2, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode2, nullptr);
    RefPtr<TextFieldPattern> pattern1 = textFieldNode1->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern1, nullptr);
    RefPtr<TextFieldPattern> pattern2 = textFieldNode2->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern2, nullptr);
    auto manager = pattern1->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    RefPtr<UINode> element1 = AceType::Claim<UINode>(Referenced::RawPtr(textFieldNode1));
    ASSERT_NE(element1, nullptr);
    element1->tag_ = V2::NAVBAR_ETS_TAG;
    textFieldNode1->SetParent(element1);
    RefPtr<UINode> navigationNode = AceType::Claim<UINode>(Referenced::RawPtr(textFieldNode2));
    ASSERT_NE(navigationNode, nullptr);
    navigationNode->tag_ = V2::NAVBAR_ETS_TAG;
    element1->SetParent(navigationNode);
    auto oldParent = textFieldNode1->GetAncestorNodeOfFrame(false);
    auto oldNavigationNode = oldParent->GetAncestorNodeOfFrame(false);
    auto result = textFieldManager->FindNavNode(textFieldNode1);
    auto newParent = textFieldNode1->GetAncestorNodeOfFrame(false);
    auto newNavigationNode = oldParent->GetAncestorNodeOfFrame(false);
    EXPECT_EQ(oldNavigationNode, newNavigationNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: TextPatternFunc077
 * @tc.desc: test TriggerCustomKeyboardAvoid.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc077, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto keyboardFst = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto keyboardScd = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    textFieldManager->usingCustomKeyboardAvoid_ = true;
    pattern->isCustomKeyboardAttached_ = false;
    pattern->selectController_->caretInfo_.rect.SetRect(0.0f, 5.0f, 0.0f, 1.0f);
    pattern->keyboardOverlay_ = AceType::MakeRefPtr<OverlayManager>(keyboardFst);
    auto host = pattern->GetHost();
    auto nodeId = host->GetId();
    pattern->keyboardOverlay_->customKeyboardMap_.emplace(std::make_pair(nodeId, AceType::RawPtr(keyboardScd)));
    textFieldManager->onFocusTextField_ = AceType::DynamicCast<Pattern>(pattern);
    textFieldManager->TriggerCustomKeyboardAvoid();
    EXPECT_EQ(keyboardScd->GetPattern<KeyboardPattern>()->safeHeight_, 0);
}

/**
 * @tc.name: TextPatternFunc078
 * @tc.desc: test TriggerCustomKeyboardAvoid.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc078, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto keyboardFst = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto keyboardScd = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    textFieldManager->usingCustomKeyboardAvoid_ = true;
    pattern->isCustomKeyboardAttached_ = true;
    pattern->selectController_->caretInfo_.rect.SetRect(0.0f, 5.0f, 0.0f, 1.0f);
    pattern->keyboardOverlay_ = AceType::MakeRefPtr<OverlayManager>(keyboardFst);
    auto host = pattern->GetHost();
    auto nodeId = host->GetId();
    pattern->keyboardOverlay_->customKeyboardMap_.emplace(std::make_pair(nodeId, AceType::RawPtr(keyboardScd)));
    textFieldManager->onFocusTextField_ = AceType::DynamicCast<Pattern>(pattern);
    textFieldManager->TriggerCustomKeyboardAvoid();
    EXPECT_EQ(keyboardScd->GetPattern<KeyboardPattern>()->safeHeight_, 1);
}

/**
 * @tc.name: TextPatternFunc079
 * @tc.desc: test TriggerCustomKeyboardAvoid.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc079, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto keyboardFst = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto keyboardScd = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    textFieldManager->usingCustomKeyboardAvoid_ = true;
    pattern->isCustomKeyboardAttached_ = true;
    pattern->selectController_->caretInfo_.rect.SetRect(0.0f, -2.0f, 0.0f, 5.0f);
    pattern->keyboardOverlay_ = AceType::MakeRefPtr<OverlayManager>(keyboardFst);
    auto host = pattern->GetHost();
    auto nodeId = host->GetId();
    pattern->keyboardOverlay_->customKeyboardMap_.emplace(std::make_pair(nodeId, AceType::RawPtr(keyboardScd)));
    textFieldManager->onFocusTextField_ = AceType::DynamicCast<Pattern>(pattern);
    textFieldManager->TriggerCustomKeyboardAvoid();
    EXPECT_EQ(keyboardScd->GetPattern<KeyboardPattern>()->safeHeight_, 3);
}

/**
 * @tc.name: TextPatternFunc080
 * @tc.desc: test TriggerAvoidOnCaretChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc080, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto keyboardFst = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto keyboardScd = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    textFieldManager->usingCustomKeyboardAvoid_ = true;
    pattern->isCustomKeyboardAttached_ = true;
    pattern->selectController_->caretInfo_.rect.SetRect(0.0f, -2.0f, 0.0f, 5.0f);
    pattern->keyboardOverlay_ = AceType::MakeRefPtr<OverlayManager>(keyboardFst);
    auto host = pattern->GetHost();
    auto nodeId = host->GetId();
    pattern->keyboardOverlay_->customKeyboardMap_.emplace(std::make_pair(nodeId, AceType::RawPtr(keyboardScd)));
    textFieldManager->onFocusTextField_ = AceType::DynamicCast<Pattern>(pattern);
    textFieldManager->TriggerAvoidOnCaretChange();
    EXPECT_EQ(keyboardScd->GetPattern<KeyboardPattern>()->safeHeight_, 0);
}

/**
 * @tc.name: TextPatternFunc081
 * @tc.desc: test SetClickPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc081, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    MockContainer::SetUp();
    RefPtr<UINode> element = AceType::Claim<UINode>(Referenced::RawPtr(textFieldNode));
    ASSERT_NE(element, nullptr);
    element->tag_ = "Panel";
    textFieldNode->SetParent(element, false);
    Offset menuOffset(960, 1660);
    textFieldManager->onFocusTextField_ = AceType::DynamicCast<Pattern>(pattern);
    textFieldManager->SetClickPosition(menuOffset);
    EXPECT_NE(textFieldManager->position_, menuOffset);
}

/**
 * @tc.name: TextPatternFunc082
 * @tc.desc: test SetClickPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc082, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    MockContainer::SetUp();
    RefPtr<UINode> element = AceType::Claim<UINode>(Referenced::RawPtr(textFieldNode));
    ASSERT_NE(element, nullptr);
    element->tag_ = "SheetPage";
    textFieldNode->SetParent(element, false);
    Offset menuOffset(960, 0.0f);
    textFieldManager->onFocusTextField_ = AceType::DynamicCast<Pattern>(pattern);
    textFieldManager->SetClickPosition(menuOffset);
    EXPECT_NE(textFieldManager->position_, menuOffset);
}

/**
 * @tc.name: TextPatternFunc083
 * @tc.desc: test SetClickPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc083, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    MockContainer::SetUp();
    Offset menuOffset(-1.0f, 100);
    textFieldManager->onFocusTextField_ = AceType::DynamicCast<Pattern>(pattern);
    textFieldManager->SetClickPosition(menuOffset);
    EXPECT_NE(textFieldManager->optionalPosition_, menuOffset);
}

/**
 * @tc.name: TextPatternFunc084
 * @tc.desc: test SetClickPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc084, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    ASSERT_NE(textFieldManager, nullptr);
    MockContainer::SetUp();
    Offset menuOffset(960, 100);
    textFieldManager->onFocusTextField_ = AceType::DynamicCast<Pattern>(pattern);
    textFieldManager->SetClickPosition(menuOffset);
    EXPECT_NE(textFieldManager->optionalPosition_, menuOffset);
}

/**
 * @tc.name: TextPatternFunc085
 * @tc.desc: test GetKeyboardHeight.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc085, TestSize.Level1)
{
    auto keyboard = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    ASSERT_NE(keyboard, nullptr);
    auto pattern = keyboard->GetPattern<KeyboardPattern>();
    auto result = pattern->GetKeyboardHeight();
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: TextPatternFunc086
 * @tc.desc: test SetKeyboardAreaChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc086, TestSize.Level1)
{
    auto keyboard = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    ASSERT_NE(keyboard, nullptr);
    auto pattern = keyboard->GetPattern<KeyboardPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<UINode> element = AceType::Claim<UINode>(Referenced::RawPtr(textFieldNode));
    keyboard->children_.emplace_back(element);
    RefPtr<SafeAreaManager> safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    ASSERT_NE(safeAreaManager, nullptr);
    safeAreaManager->SetRawKeyboardHeight(5.0f);
    auto pipeline = pattern->GetHost()->GetContext();
    pipeline->safeAreaManager_ = safeAreaManager;
    pattern->SetKeyboardAreaChange(true);
    EXPECT_EQ(pipeline->safeAreaManager_->GetRawKeyboardHeight(), 0.0f);
}

/**
 * @tc.name: TextPatternFunc087
 * @tc.desc: test SetKeyboardAreaChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc087, TestSize.Level1)
{
    auto keyboard = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    ASSERT_NE(keyboard, nullptr);
    auto pattern = keyboard->GetPattern<KeyboardPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = pattern->GetHost()->GetContext();
    pipeline->safeAreaManager_ = nullptr;
    pattern->SetKeyboardAreaChange(true);
    EXPECT_EQ(pipeline->safeAreaManager_, nullptr);
}

/**
 * @tc.name: TextPatternFunc088
 * @tc.desc: test SetKeyboardAreaChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc088, TestSize.Level1)
{
    auto keyboard = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    ASSERT_NE(keyboard, nullptr);
    auto pattern = keyboard->GetPattern<KeyboardPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<SafeAreaManager> safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    ASSERT_NE(safeAreaManager, nullptr);
    safeAreaManager->SetRawKeyboardHeight(5.0f);
    auto pipeline = pattern->GetHost()->GetContext();
    pipeline->safeAreaManager_ = safeAreaManager;
    pattern->SetKeyboardAreaChange(false);
    EXPECT_EQ(pipeline->safeAreaManager_->GetRawKeyboardHeight(), 5.0f);
}

/**
 * @tc.name: TextPatternFunc089
 * @tc.desc: test OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc089, TestSize.Level1)
{
    auto keyboard = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    ASSERT_NE(keyboard, nullptr);
    auto pattern = keyboard->GetPattern<KeyboardPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetKeyboardOption(true);
    pattern->OnAreaChangedInner();
    EXPECT_EQ(pattern->keyboardHeight_, 0.0f);
}

/**
 * @tc.name: TextPatternFunc091
 * @tc.desc: test OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc091, TestSize.Level1)
{
    auto keyboard = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<KeyboardPattern>(2));
    ASSERT_NE(keyboard, nullptr);
    auto pattern = keyboard->GetPattern<KeyboardPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetKeyboardOption(true);
    pattern->keyboardHeight_ = 5.0f;
    pattern->OnAreaChangedInner();
    EXPECT_EQ(pattern->keyboardHeight_, 0.0f);
}

/**
 * @tc.name: TextPatternFunc092
 * @tc.desc: test SetOnWillChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc092, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto state = false;
    auto eventHub = pattern->GetHost()->GetOrCreateEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto callback = [&state](const ChangeValueInfo& info){ return (state = true); };
    eventHub->SetOnWillChangeEvent(callback);

    InsertCommandInfo info;
    info.insertValue = u"openharmony";
    info.reason = InputReason::IME;
    pattern->ExecuteInsertValueCommand(info);
    EXPECT_TRUE(state);
}

/**
 * @tc.name: GetTextContentRect001
 * @tc.desc: test GetTextContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetTextContentRect001, TestSize.Level1)
{
    TextFieldController textFieldController;
    textFieldController.SetGetTextContentRect(MyGetTextContentRect);
    auto result = textFieldController.GetTextContentRect();
    EXPECT_EQ(result.GetOffset().GetX(), 2);
}

/**
 * @tc.name: GetTextContentRect002
 * @tc.desc: test GetTextContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetTextContentRect002, TestSize.Level1)
{
    TextFieldController textFieldController;
    auto result = textFieldController.GetTextContentRect();
    EXPECT_EQ(result.GetOffset().GetX(), 0);
}

/**
 * @tc.name: GetTextContentRect003
 * @tc.desc: test GetTextContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetTextContentRect003, TestSize.Level1)
{
    TextFieldController textFieldController;
    auto pattern_ = AceType::MakeRefPtr<TextFieldPattern>();
    pattern_->GetTextSelectController()->caretInfo_.rect.SetRect(1, 1, 1, 1);
    textFieldController.SetPattern(pattern_);
    auto result = textFieldController.GetTextContentRect();
    EXPECT_EQ(result.GetOffset().GetX(), 1);
}

/**
 * @tc.name: GetTextContentRect004
 * @tc.desc: test GetTextContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetTextContentRect004, TestSize.Level1)
{
    TextFieldController textFieldController;
    auto pattern_ = AceType::MakeRefPtr<TextFieldPattern>();
    pattern_->GetTextContentController()->SetTextValue(u"value");
    RectF textRect(3, 3, 3, 3);
    pattern_->SetTextRect(textRect);
    textFieldController.SetPattern(pattern_);
    auto result = textFieldController.GetTextContentRect();
    EXPECT_EQ(result.GetOffset().GetX(), 3);
}

/**
 * @tc.name: GetTextContentRect001
 * @tc.desc: test GetTextContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetTextContentLinesNum001, TestSize.Level1)
{
    TextFieldController textFieldController;
    textFieldController.SetGetTextContentLinesNum(MyGetTextContentLinesNum);
    auto result = textFieldController.GetTextContentLinesNum();
    EXPECT_EQ(result, 5);
}

/**
 * @tc.name: GetCaretIndex001
 * @tc.desc: test GetCaretIndex.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetCaretIndex001, TestSize.Level1)
{
    TextFieldController textFieldController;
    textFieldController.SetGetCaretIndex(MyGetCaretIndex);
    auto result = textFieldController.GetCaretIndex();
    EXPECT_EQ(result, 5);
}

/**
 * @tc.name: GetCaretIndex002
 * @tc.desc: test GetCaretIndex.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetCaretIndex002, TestSize.Level1)
{
    TextFieldController textFieldController;
    auto result = textFieldController.GetCaretIndex();
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: GetCaretPosition001
 * @tc.desc: test GetCaretPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetCaretPosition001, TestSize.Level1)
{
    TextFieldController textFieldController;
    textFieldController.SetGetCaretPosition(MyGetCaretPosition);
    auto result = textFieldController.GetCaretPosition();
    EXPECT_EQ(result.GetX(), 5);
}

/**
 * @tc.name: GetCaretPosition002
 * @tc.desc: test GetCaretPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetCaretPosition002, TestSize.Level1)
{
    TextFieldController textFieldController;
    auto result = textFieldController.GetCaretPosition();
    EXPECT_EQ(result.GetX(), -1);
}

/**
 * @tc.name: GetKeyboardAppearance001
 * @tc.desc: test SetKeyboardAppearance.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, GetKeyboardAppearance001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. check KeyboardAppearance's size and default value.
     */
    EXPECT_TRUE(pattern->GetKeyboardAppearance() == KeyboardAppearance::NONE_IMMERSIVE);
    /**
     * @tc.steps: step3. call SetKeyboardAppearance and use GetKeyboardAppearance to check
     */
    pattern->SetKeyboardAppearance(KeyboardAppearance::DARK_IMMERSIVE);
    EXPECT_TRUE(pattern->GetKeyboardAppearance() == KeyboardAppearance::DARK_IMMERSIVE);
    pattern->SetKeyboardAppearance(KeyboardAppearance::NONE_IMMERSIVE);
    EXPECT_TRUE(pattern->GetKeyboardAppearance() == KeyboardAppearance::NONE_IMMERSIVE);
}

/**
 * @tc.name: TextFieldSelectOverlay001
 * @tc.desc: test OnOverlayClick.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextFieldSelectOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    /**
     * @tc.steps: step2. call OnOverlayClick and expect no error.
     */
    GestureEvent event;
    pattern->selectOverlay_->OnOverlayClick(event, true);
    pattern->selectOverlay_->isSingleHandle_ = true;
    pattern->selectOverlay_->OnOverlayClick(event, true);
    pattern->multipleClickRecognizer_ = pattern->GetOrCreateMultipleClickRecognizer();
    pattern->multipleClickRecognizer_->clickCountTask_.Reset([] {});
    pattern->selectOverlay_->OnOverlayClick(event, true);
    pattern->multipleClickRecognizer_->lastClickPosition_ = Offset(0.0f, 0.0f);
    event.SetGlobalLocation(Offset(100.0f, 100.0f));
    auto timeStampAce = TimeStamp(std::chrono::nanoseconds(1000));
    event.SetTimeStamp(timeStampAce);
    pattern->multipleClickRecognizer_->lastClickTimeStamp_ = TimeStamp(std::chrono::nanoseconds(0));
    pattern->selectOverlay_->OnOverlayClick(event, true);
}

/**
 * @tc.name: TextFieldSelectOverlay002
 * @tc.desc: test OnHandleMoveStart.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextFieldSelectOverlay002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    /**
     * @tc.steps: step2. call OnHandleMoveStart and expect no error.
     */
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    pattern->selectOverlay_->isSingleHandle_ = true;
    GestureEvent event;
    pattern->selectOverlay_->OnHandleMoveStart(event, true);
    pattern->contentController_->content_ = u"";
    pattern->selectOverlay_->OnHandleMoveStart(event, true);
    EXPECT_FALSE(pattern->contentScroller_.isScrolling);
}

/**
 * @tc.name: TextFieldSelectOverlay003
 * @tc.desc: test AllowTranslate.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextFieldSelectOverlay003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    /**
     * @tc.steps: step2. call AllowTranslate and expect no error.
     */
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    auto layoutProperty = textFieldNode->GetLayoutPropertyPtr<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCopyOptions(CopyOptions::None);
    EXPECT_FALSE(pattern->selectOverlay_->AllowTranslate());
    layoutProperty->UpdateCopyOptions(CopyOptions::Local);
    layoutProperty->UpdateTextInputType(TextInputType::NEW_PASSWORD);
    EXPECT_FALSE(pattern->selectOverlay_->AllowTranslate());
    layoutProperty->UpdateTextInputType(TextInputType::NUMBER);
    EXPECT_TRUE(pattern->selectOverlay_->AllowTranslate());
}

/**
 * @tc.name: TextFieldSelectOverlay004
 * @tc.desc: test AllowSearch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextFieldSelectOverlay004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    /**
     * @tc.steps: step2. call AllowSearch and expect no error.
     */
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    auto layoutProperty = textFieldNode->GetLayoutPropertyPtr<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCopyOptions(CopyOptions::None);
    EXPECT_FALSE(pattern->selectOverlay_->AllowSearch());
    layoutProperty->UpdateCopyOptions(CopyOptions::Local);
    layoutProperty->UpdateTextInputType(TextInputType::NEW_PASSWORD);
    EXPECT_FALSE(pattern->selectOverlay_->AllowSearch());
    layoutProperty->UpdateTextInputType(TextInputType::NUMBER);
    EXPECT_TRUE(pattern->selectOverlay_->AllowSearch());
}

/**
 * @tc.name: TextFieldSelectOverlay005
 * @tc.desc: test GetHandleColor.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextFieldSelectOverlay005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    /**
     * @tc.steps: step2. call GetHandleColor and expect no error.
     */
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->ResetCursorColor();
    EXPECT_EQ(pattern->selectOverlay_->GetHandleColor(), std::nullopt);
    paintProperty->UpdateCursorColor(Color::GREEN);
    EXPECT_EQ(pattern->selectOverlay_->GetHandleColor(), Color::GREEN);
    pattern->selectOverlay_->hostTextBase_.Reset();
    EXPECT_EQ(pattern->selectOverlay_->GetHandleColor(), std::nullopt);
}

/**
 * @tc.name: TextFieldSelectOverlay006
 * @tc.desc: test UpdateAllHandlesOffset.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, TextFieldSelectOverlay006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    /**
     * @tc.steps: step2. call UpdateAllHandlesOffset and expect no error.
     */
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    pattern->selectOverlay_->dragHandleIndex_ = DragHandleIndex::NONE;
    pattern->selectOverlay_->UpdateAllHandlesOffset();
    pattern->selectOverlay_->dragHandleIndex_ = DragHandleIndex::FIRST;
    pattern->selectOverlay_->UpdateAllHandlesOffset();
    pattern->selectOverlay_->dragHandleIndex_ = DragHandleIndex::SECOND;
    pattern->selectOverlay_->UpdateAllHandlesOffset();
}

/**
 * @tc.name: BaseTextSelectOverlay000
 * @tc.desc: test base_text_select_overlay.cpp ToggleMenu
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay000, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call ToggleMenu and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    pattern->selectOverlay_->ToggleMenu();
    EXPECT_NE(pattern->selectOverlay_->GetManager<SelectContentOverlayManager>(), nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay001
 * @tc.desc: test base_text_select_overlay.cpp DisableMenu
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call DisableMenu and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    pattern->selectOverlay_->DisableMenu();
    EXPECT_NE(pattern->selectOverlay_->GetManager<SelectContentOverlayManager>(), nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay002
 * @tc.desc: test base_text_select_overlay.cpp OnHandleGlobalTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call OnHandleGlobalTouchEvent and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    auto sourceType = SourceType::MOUSE;
    auto touchType = TouchType::DOWN;
    pattern->selectOverlay_->OnHandleGlobalTouchEvent(sourceType, touchType);
    EXPECT_EQ(pattern->selectOverlay_->IsMouseClickDown(sourceType, touchType), true);
}

/**
 * @tc.name: BaseTextSelectOverlay003
 * @tc.desc: test base_text_select_overlay.cpp CheckTouchInHostNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call CheckTouchInHostNode and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    PointF point;
    pattern->selectOverlay_->CheckTouchInHostNode(point);
    EXPECT_NE(pattern->selectOverlay_->GetOwner(), nullptr);
    EXPECT_NE(pattern->selectOverlay_->GetOwner()->GetGeometryNode(), nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay004
 * @tc.desc: test base_text_select_overlay.cpp OnUpdateSelectOverlayInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call OnUpdateSelectOverlayInfo and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    SelectOverlayInfo selectInfo;
    int32_t requestCode = 0;
    pattern->selectOverlay_->hasTransform_ = true;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(selectInfo, requestCode);
    pattern->selectOverlay_->hasTransform_ = false;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(selectInfo, requestCode);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay005
 * @tc.desc: test base_text_select_overlay.cpp RemoveSelectionHoldCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call RemoveSelectionHoldCallback and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    pattern->selectOverlay_->RemoveSelectionHoldCallback();
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
}
 
/**
 * @tc.name: BaseTextSelectOverlay006
 * @tc.desc: test base_text_select_overlay.cpp GetVisibleContentRect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call GetVisibleContentRect and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    pattern->selectOverlay_->enableHandleLevel_ = true;
    pattern->selectOverlay_->handleLevelMode_ = HandleLevelMode::EMBED;
    pattern->selectOverlay_->GetVisibleContentRect(false);
    EXPECT_NE(pattern->selectOverlay_->GetPattern<Pattern>(), nullptr);
    EXPECT_NE(pattern->selectOverlay_->GetPattern<Pattern>()->GetHost(), nullptr);
    EXPECT_NE(pattern->selectOverlay_->GetPattern<Pattern>()->GetHost()->GetContext(), nullptr);
    EXPECT_NE(pattern->selectOverlay_->GetPattern<Pattern>()->GetHost()->GetGeometryNode(), nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay007
 * @tc.desc: test base_text_select_overlay.cpp MergeSelectedBoxes
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call MergeSelectedBoxes and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    std::vector<RectF> boxes;
    RectF contentRect(1.0f, 2.0f, 3.0f, 4.0f);
    RectF textRect(1.0f, 2.0f, 3.0f, 4.0f);
    OffsetF paintOffset(0.0f, 0.0f);
    auto rect = pattern->selectOverlay_->MergeSelectedBoxes(boxes, contentRect, textRect, paintOffset);
    EXPECT_EQ(rect.GetX(), 0);
    EXPECT_EQ(rect.GetY(), 0);
}
 
/**
 * @tc.name: BaseTextSelectOverlay008
 * @tc.desc: test base_text_select_overlay.cpp GetLocalPointWithTransform
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call GetLocalPointWithTransform and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    OffsetF localOffset(0.0f, 0.0f);
    pattern->selectOverlay_->hasTransform_ = false;
    pattern->selectOverlay_->GetLocalPointWithTransform(localOffset);
    pattern->selectOverlay_->hasTransform_ = true;
    pattern->selectOverlay_->GetLocalPointWithTransform(localOffset);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay009
 * @tc.desc: test base_text_select_overlay.cpp ConvertPaintInfoToRect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call ConvertPaintInfoToRect and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    SelectHandlePaintInfo paintInfo;
    auto rect = pattern->selectOverlay_->ConvertPaintInfoToRect(paintInfo);
    EXPECT_EQ(rect.GetX(), 0);
    EXPECT_EQ(rect.GetY(), 0);
}

/**
 * @tc.name: BaseTextSelectOverlay010
 * @tc.desc: test base_text_select_overlay.cpp GetHandleLocalPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call GetHandleLocalPaintRect and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    DragHandleIndex dragHandleIndex = DragHandleIndex::FIRST;
    auto rect = pattern->selectOverlay_->GetHandleLocalPaintRect(dragHandleIndex);
    EXPECT_EQ(rect.GetX(), 0);
    EXPECT_EQ(rect.GetY(), 0);
}
 
/**
 * @tc.name: BaseTextSelectOverlay011
 * @tc.desc: test base_text_select_overlay.cpp UpdateMenuWhileAncestorNodeChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call UpdateMenuWhileAncestorNodeChanged and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    bool shouldHideMenu = false;
    bool shouldShowMenu = false;
    FrameNodeChangeInfoFlag extraFlag = AVOID_KEYBOARD_END_FALG;
    pattern->selectOverlay_->UpdateMenuWhileAncestorNodeChanged(shouldHideMenu, shouldShowMenu, extraFlag);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
}
 
/**
 * @tc.name: BaseTextSelectOverlay012
 * @tc.desc: test base_text_select_overlay.cpp RegisterScrollingListener
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call RegisterScrollingListener and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textFieldNode);
    pattern->selectOverlay_->OnBind(manager);
    pattern->selectOverlay_->hasRegisterListener_ = true;
    pattern->selectOverlay_->RegisterScrollingListener(nullptr);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay013
 * @tc.desc: test base_text_select_overlay.cpp ConvertWindowToScreenDomain with Rect input
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call ConvertWindowToScreenDomain and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    RectF inputRectf;
    auto outputRecf = pattern->selectOverlay_->ConvertWindowToScreenDomain(inputRectf);
    EXPECT_EQ(outputRecf.GetX(), 0);
    EXPECT_EQ(outputRecf.GetY(), 0);
}

/**
 * @tc.name: BaseTextSelectOverlay014
 * @tc.desc: test base_text_select_overlay.cpp ConvertWindowToScreenDomain with Edge input
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call ConvertWindowToScreenDomain and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    EdgeF edgeF;
    auto outputEdgeF = pattern->selectOverlay_->ConvertWindowToScreenDomain(edgeF);
    EXPECT_EQ(outputEdgeF.x, 0);
    EXPECT_EQ(outputEdgeF.y, 0);
}

/**
 * @tc.name: BaseTextSelectOverlay015
 * @tc.desc: test base_text_select_overlay.cpp GetTranslateParamRectStr
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call GetTranslateParamRectStr and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);

    RectF rectf1(1.0f, 2.0f, 3.0f, 4.0f);
    EdgeF edgeF1(0.0f, 0.0f);
    EdgeF edgeF2(0.0f, 0.0f);
    pattern->selectOverlay_->GetTranslateParamRectStr(rectf1, edgeF1, edgeF2);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: BaseTextSelectOverlay016
 * @tc.desc: test base_text_select_overlay.cpp IsHandleVisible
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTest, BaseTextSelectOverlay016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textFieldNode and get pattern.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call IsHandleVisible and expect no error.
     */
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern);
    auto isHandleVisible = pattern->selectOverlay_->IsHandleVisible(false);
    EXPECT_EQ(isHandleVisible, false);
}

} // namespace OHOS::Ace
