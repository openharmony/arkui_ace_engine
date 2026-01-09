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

#include "test/mock/core/common/mock_container.h"
#include "text_input_base.h"
#include "test/mock/core/common/mock_container.h"
#include "frameworks/core/components_ng/pattern/text/span_node.h"

namespace OHOS::Ace::NG {
class TextFieldPatternFuncTestTwo : public TextInputBases {
public:
};

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc001, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc002, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc003, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc004, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc005, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc006, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc007, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc008, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc009, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc010, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc011, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc012, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc013, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc014, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc015, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc016, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc017, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc018, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc019, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc020, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc021, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc022, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc023, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc024, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc025, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc026, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc027, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc028, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc029, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc030, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc031, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc032, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc033, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc034, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc035, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc037, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc038, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc039, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc040, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc041, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc042, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc043, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc044, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc045, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc046, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc047, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc048, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc049, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc050, TestSize.Level1)
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
    pattern->GetHost()->GetEventHub<TextFieldEventHub>()->SetOnDidInsertValueEvent(callback);
    std::u16string insertValue;
    pattern->AfterIMEInsertValue(insertValue);
    EXPECT_TRUE(state);
}

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc051, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto state = false;
    auto eventHub = pattern->GetHost()->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto callback = [&state](const InsertValueInfo& info){ return (state = true); };
    eventHub->SetOnWillInsertValueEvent(callback);
    InsertCommandInfo info;
    info.insertValue = u"";
    info.reason = InputReason::IME;
    pattern->ExecuteInsertValueCommand(info);
    EXPECT_TRUE(state);
}

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc052, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);

    auto eventHub = pattern->GetHost()->GetEventHub<TextFieldEventHub>();
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc053, TestSize.Level1)
{
    CreateTextField();
    auto frameId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, frameId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);

    auto eventHub = pattern->GetHost()->GetEventHub<TextFieldEventHub>();
    auto state = false;
    auto callback = [&state](const DeleteValueInfo&){ state = true; };
    eventHub->SetOnDidDeleteEvent(callback);
    pattern->selectController_->firstHandleInfo_.index = 0;
    pattern->selectController_->secondHandleInfo_.index = 0;

    pattern->AddInsertCommand(u"", InputReason::IME);
    EXPECT_FALSE(pattern->cursorVisible_);
}

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc054, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc055, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc056, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc057, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc058, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc059, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc060, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc061, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc062, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc063, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc064, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc065, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc066, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc067, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc068, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc069, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc0570, TestSize.Level1)
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

HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc071, TestSize.Level1)
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
HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc072, TestSize.Level1)
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
    textFieldNode->SetParent(element);
    auto result = textFieldManager->FindNavNode(textFieldNode);
    auto parent = textFieldNode->GetAncestorNodeOfFrame(false);
    EXPECT_EQ(parent, nullptr);
}

/**
 * @tc.name: TextPatternFunc073
 * @tc.desc: test FindNavNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc073, TestSize.Level1)
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
HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc074, TestSize.Level1)
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
HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc075, TestSize.Level1)
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
HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc076, TestSize.Level1)
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
HWTEST_F(TextFieldPatternFuncTestTwo, TextPatternFunc077, TestSize.Level1)
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
} // namespace OHOS::Ace
