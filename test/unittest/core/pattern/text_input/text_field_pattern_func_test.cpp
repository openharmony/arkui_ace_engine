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

#include "adapter/preview/entrance/editing/text_input_connection_impl.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldPatternFuncTest : public TextInputBases {
public:
};

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc001, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    std::string content;
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
    std::string content = "openharmony";
    ASSERT_NE(pattern->contentController_, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);
    pattern->deleteBackwardOperations_.push(1);
    pattern->InitEditingValueText(content);
    EXPECT_NE(pattern->contentController_->content_, content);
}

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc003, TestSize.Level1)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    std::string content = "openharmony";
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
    std::string content;
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
    std::string content = "openharmony";
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
    std::string content;
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
    pattern->hoverEvent_->onHoverCallback_(false);
    EXPECT_TRUE(pattern->mouseEvent_->onMouseCallback_ != nullptr);
    EXPECT_TRUE(pattern->hoverEvent_->onHoverCallback_ != nullptr);
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
    pattern->OnHover(true);
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
    pattern->OnHover(false);
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

HWTEST_F(TextFieldPatternFuncTest, TextPatternFunc036, TestSize.Level1)
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
    contextPtr->textFieldManager_ = nullptr;
    std::unordered_map<std::string, std::variant<std::string, bool, int32_t>> fillContentMap_;
    std::variant<std::string, bool, int32_t> contentVariant;
    auto value = std::pair<std::string, std::variant<std::string, bool, int32_t>>("openharmony", contentVariant);
    pattern->fillContentMap_.insert(value);
    pattern->RequestKeyboard(false, false, false);
    EXPECT_FALSE(pattern->fillContentMap_.empty());
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
    TextContentType type = TextContentType(30);
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

    std::string insertValue;
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
    pattern->GetHost()->GetEventHub<TextFieldEventHub>()->SetOnDidInsertValueEvent(callback);
    std::string insertValue;
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

    SourceAndValueInfo info;
    info.isIME = true;
    auto state = false;
    auto eventHub = pattern->GetHost()->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto callback = [&state](const InsertValueInfo& info){ return (state = true); };
    eventHub->SetOnWillInsertValueEvent(callback);
    pattern->InsertValueOperation(info);
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

    auto eventHub = pattern->GetHost()->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto state = false;
    auto callback = [&state](const InsertValueInfo&){ return (state = true); };
    eventHub->SetOnWillInsertValueEvent(callback);
    SourceAndValueInfo info;
    info.isIME = true;
    pattern->selectController_->firstHandleInfo_.index = 0;
    pattern->selectController_->secondHandleInfo_.index = 0;
    
    pattern->InsertValueOperation(info);
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

    auto eventHub = pattern->GetHost()->GetEventHub<TextFieldEventHub>();
    auto state = false;
    auto callback = [&state](const DeleteValueInfo&){ state = true; };
    eventHub->SetOnDidDeleteEvent(callback);
    SourceAndValueInfo info;
    info.isIME = true;
    pattern->selectController_->firstHandleInfo_.index = 0;
    pattern->selectController_->secondHandleInfo_.index = 0;
    
    pattern->InsertValueOperation(info);
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
    std::string insertValue;
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
    std::string insertValue;
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
    std::string insertValue;
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
    
    std::string insertValue = "1";
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
    pattern->InsertValue("", true);
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
    pattern->InsertValue("", true);
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
    pattern->InsertValue("", true);
    EXPECT_FALSE(pattern->HandleSpaceEvent());
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
    pattern->InsertValue("", true);
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
    while (!pattern->insertValueOperations_.empty()) {
        pattern->insertValueOperations_.pop();
    }

    pattern->focusIndex_ = FocuseIndex::TEXT;
    pattern->hasPreviewText_ = false;
    pattern->InsertValue("", true);
    EXPECT_FALSE(pattern->insertValueOperations_.empty());
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
    pattern->contentController_->SetTextValue("openharmony");
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
    pattern->contentController_->SetTextValue("openharmony");
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
    pattern->contentController_->SetTextValue("openharmony");
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

    pattern->contentController_->SetTextValue("");

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

    pattern->contentController_->SetTextValue("");

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
} // namespace OHOS::Ace
