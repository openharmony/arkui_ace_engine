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

#include <array>
#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_data_detector_mgr.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "base/utils/type_definition.h"
#include "core/common/ai/data_detector_mgr.h"
#include "core/common/ime/constant.h"
#include "core/common/ime/text_editing_value.h"
#include "core/common/ime/text_input_action.h"
#include "core/common/ime/text_input_type.h"
#include "core/common/ime/text_selection.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/text_field/text_content_type.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double ICON_SIZE = 24;
constexpr double ICON_HOT_ZONE_SIZE = 40;
constexpr double FONT_SIZE = 16;
constexpr int32_t DEFAULT_NODE_ID = 1;
constexpr int32_t MIN_PLATFORM_VERSION = 10;
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
const std::string HELLO_TEXT = "hello";
const std::string DEFAULT_PLACE_HOLDER = "please input text here";
const std::string LOWERCASE_FILTER = "[a-z]";
const std::string NUMBER_FILTER = "^[0-9]*$";
const std::string DEFAULT_INPUT_FILTER = "[a-z]";
const TextAlign DEFAULT_TEXT_ALIGN = TextAlign::LEFT;
template<typename CheckItem, typename Expected>
struct TestItem {
    CheckItem item;
    Expected expected;
    std::string error;
    TestItem(CheckItem checkItem, Expected expectedValue, std::string message = "")
        : item(checkItem), expected(expectedValue), error(std::move(message))
    {}
    TestItem() = default;
};
struct ExpectParagraphParams {
    float height = 50.f;
    float longestLine = 460.f;
    float maxWidth = 460.f;
    size_t lineCount = 1;
    bool firstCalc = true;
    bool secondCalc = true;
};
} // namespace

class TextInputModifyBase : public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void TearDown() override;

    void CreateTextField(const std::string& text = "", const std::string& placeHolder = "",
        const std::function<void(TextFieldModelNG&)>& callback = nullptr);
    static void ExpectCallParagraphMethods(ExpectParagraphParams params);
    void GetFocus();

    RefPtr<FrameNode> frameNode_;
    RefPtr<TextFieldPattern> pattern_;
    RefPtr<TextFieldEventHub> eventHub_;
    RefPtr<TextFieldLayoutProperty> layoutProperty_;
    RefPtr<TextFieldAccessibilityProperty> accessibilityProperty_;
};

void TextInputModifyBase::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    ExpectCallParagraphMethods(ExpectParagraphParams());
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textFieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    textFieldTheme->iconSize_ = Dimension(ICON_SIZE, DimensionUnit::VP);
    textFieldTheme->iconHotZoneSize_ = Dimension(ICON_HOT_ZONE_SIZE, DimensionUnit::VP);
    textFieldTheme->fontSize_ = Dimension(FONT_SIZE, DimensionUnit::FP);
    textFieldTheme->fontWeight_ = FontWeight::W400;
    textFieldTheme->textColor_ = Color::FromString("#ff182431");
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([textFieldTheme = textFieldTheme](ThemeType type) -> RefPtr<Theme> {
            if (type == ScrollBarTheme::TypeId()) {
                return AceType::MakeRefPtr<ScrollBarTheme>();
            }
            return textFieldTheme;
        });
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(MIN_PLATFORM_VERSION);
    MockPipelineContext::GetCurrent()->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManagerNG>());
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void TextInputModifyBase::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    MockParagraph::TearDown();
}

void TextInputModifyBase::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void TextInputModifyBase::ExpectCallParagraphMethods(ExpectParagraphParams params)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, AddText(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, PopStyle()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Build()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Layout(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, GetTextWidth()).WillRepeatedly(Return(params.maxWidth));
    EXPECT_CALL(*paragraph, GetAlphabeticBaseline()).WillRepeatedly(Return(0.f));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(params.height));
    EXPECT_CALL(*paragraph, GetLongestLine()).WillRepeatedly(Return(params.longestLine));
    EXPECT_CALL(*paragraph, GetMaxWidth()).WillRepeatedly(Return(params.maxWidth));
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(params.lineCount));
}

void TextInputModifyBase::CreateTextField(
    const std::string& text, const std::string& placeHolder, const std::function<void(TextFieldModelNG&)>& callback)
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(DEFAULT_NODE_ID);
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(placeHolder, text);
    if (callback) {
        callback(textFieldModelNG);
    }
    stack->StopGetAccessRecording();
    frameNode_ = AceType::DynamicCast<FrameNode>(stack->Finish());
    pattern_ = frameNode_->GetPattern<TextFieldPattern>();
    eventHub_ = frameNode_->GetEventHub<TextFieldEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<TextFieldAccessibilityProperty>();
    FlushLayoutTask(frameNode_);
}

void TextInputModifyBase::GetFocus()
{
    auto focushHub = pattern_->GetFocusHub();
    focushHub->currentFocus_ = true;
    pattern_->HandleFocusEvent();
    FlushLayoutTask(frameNode_);
}

class TextFieldUXTest : public TextInputModifyBase {};
class TextFieldModifyTest : public TextInputModifyBase {};

/**
 * @tc.name: TextinputCaretPositionOnHandleMove001
 * @tc.desc: Test the caret position after handle move done in textinput.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, TextinputCaretPositionOnHandleMove001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
        model.SetShowUnderline(true);
    });

    GetFocus();
    EXPECT_FALSE(pattern_->IsTextArea());

    /**
     * @tc.steps: step2. Create localoffset.
     * tc.expected: step2. Check if the value is right.
     */
    OffsetF localOffset1(1.0f, 1.0f);
    EXPECT_EQ(pattern_->selectOverlay_->GetCaretPositionOnHandleMove(localOffset1), 0);

    FlushLayoutTask(frameNode_);
    GetFocus();
    OffsetF localOffset2(720.0f, 1.0f);
    EXPECT_EQ(pattern_->selectOverlay_->GetCaretPositionOnHandleMove(localOffset2), 26);

    FlushLayoutTask(frameNode_);
    GetFocus();
    OffsetF localOffset3(30.0f, 1.0f);
    EXPECT_EQ(pattern_->selectOverlay_->GetCaretPositionOnHandleMove(localOffset3), 0);
}

/**
 * @tc.name: SetTextDraggable001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, SetTextDraggable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
        model.SetShowUnderline(true);
    });

    /**
     * @tc.steps: step2. Set CustomerDraggable true. Call function OnModifyDone.
     * @tc.expected: Check if the text draggable.
     */
    GetFocus();
    frameNode_->SetCustomerDraggable(true);
    FlushLayoutTask(frameNode_);
    pattern_->InitDragEvent();
    EXPECT_NE(frameNode_->GetOrCreateGestureEventHub()->dragEventActuator_, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: Test textfield to create paint.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CreateNodePaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();
    auto focusHub = pattern_->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = false;
    EXPECT_TRUE(pattern_->IsNormalInlineState());
    pattern_->UpdateScrollBarOffset();

    auto paint = AceType::DynamicCast<TextFieldPaintMethod>(pattern_->CreateNodePaintMethod());
    auto inlineScrollRect = pattern_->GetScrollBar()->GetActiveRect();
    EXPECT_EQ(inlineScrollRect, Rect(720, 0, 0, 50));
    EXPECT_NE(pattern_->textFieldContentModifier_, nullptr);
}

/**
 * @tc.name: CheckBlurReason001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckBlurReason001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Set blurReason FRAME_DESTROY. Call function CheckBlurReason.
     * @tc.expected: Check if return true.
     */
    EXPECT_FALSE(pattern_->CheckBlurReason());
    auto focusHub = pattern_->GetFocusHub();
    focusHub->blurReason_ = BlurReason::FRAME_DESTROY;
    EXPECT_TRUE(pattern_->CheckBlurReason());
}

/**
 * @tc.name: HandleClickEvent001
 * @tc.desc: Test the clickevent for handle.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, HandleClickEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    GestureEvent gestureEvent;
    gestureEvent.SetLocalLocation(Offset(0.0f, 0.0f));
    gestureEvent.SetSourceDevice(SourceType::TOUCH);
    auto timeStampAce = TimeStamp(std::chrono::nanoseconds(1000));
    gestureEvent.SetTimeStamp(timeStampAce);

    /**
     * @tc.steps: step2. Set single clickevent. Call function HandleSingleClickEvent.
     * @tc.expected: Check if return true.
     */
    pattern_->OnAfterModifyDone();
    pattern_->HandleSingleClickEvent(gestureEvent);
    EXPECT_TRUE(pattern_->selectOverlay_->IsSingleHandle());
}

/**
 * @tc.name: OnCursorTwinkling001
 * @tc.desc: Test the cursor twinkling for handle.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, OnCursorTwinkling001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    pattern_->OnCursorTwinkling();
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step2. Set single clickevent. Call function OnCursorTwinkling.
     * @tc.expected: Check if return true.
     */
    pattern_->obscureTickCountDown_ = 1;
    GestureEvent gestureEvent;
    pattern_->HandleSingleClickEvent(gestureEvent);
    pattern_->OnCursorTwinkling();
    pattern_->OnAfterModifyDone();
    EXPECT_TRUE(pattern_->selectOverlay_->IsSingleHandle());
}

/**
 * @tc.name: UpdatSecondHandleInfo001
 * @tc.desc: Test the update for handleinfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, UpdateSecondHandleInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set secondhandle. Call function UpdateSelectOverlaySecondHandle.
     * @tc.expected: Check if return true.
     */
    pattern_->ProcessOverlay();
    pattern_->HandleSetSelection(5, 10, false);
    pattern_->selectOverlay_->UpdateSecondHandleOffset();
    EXPECT_NE(pattern_->selectOverlay_, nullptr);

    pattern_->selectOverlay_->UpdateAllHandlesOffset();
    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->selectOverlay_->UpdateAllHandlesOffset();
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 5);
}

/**
 * @tc.name: UpdatSecondHandleInfo001
 * @tc.desc: Test get Select HandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, UpdateSecondHandleInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
                                                                  /**
     * @tc.steps: step2. Set secondhandle. Call function GetSelectHandleInfo.
     * @tc.expected: Check if return true.
     */
    pattern_->HandleSetSelection(5, 10, false);
    pattern_->selectOverlay_->UpdateSecondHandleOffset();
    EXPECT_EQ(pattern_->selectOverlay_->GetSecondHandleInfo()->paintRect, RectF(0.0f, 0.0f, 1.5f, 0.0f));
}

/**
 * @tc.name: DoCallback001
 * @tc.desc: Test function OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, DoCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. callback the HandleClickEvent in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    GestureEvent gestureEvent;

    /**
     * @tc.steps: step3. mock click.
     */
    pattern_->HandleClickEvent(gestureEvent);
    EXPECT_TRUE(pattern_->cursorVisible_);

    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->clickListener_->operator()(gestureEvent);
    EXPECT_FALSE(pattern_->isFocusedBeforeClick_);
}

/**
 * @tc.name: DoCallback002
 * @tc.desc: Test function OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, DoCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. callback the HandleLongPress in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    GestureEvent gestureEvent;

    /**
     * @tc.steps: step3. mock LongPress.
     */
    pattern_->longPressEvent_->operator()(gestureEvent);
    EXPECT_FALSE(pattern_->IsUsingMouse());
    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->HandleLongPress(gestureEvent);
    EXPECT_TRUE(pattern_->isLongPress_);

    /**
     * @tc.steps: test the branch when SourceType = mouse.
     */
    FlushLayoutTask(frameNode_);
    GetFocus();
    gestureEvent.SetSourceDevice(SourceType::MOUSE);
    pattern_->HandleLongPress(gestureEvent);
    EXPECT_FALSE(pattern_->isTouchCaret_);
}

/**
 * @tc.name: DoCallback003
 * @tc.desc: Test function OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, DoCallback003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. callback the functions in OnModifyDone.
     * @tc.expected: Check if return true.
     */

    pattern_->GetFocusHub()->onFocusInternal_.operator()();
    RoundRect roundRect;
    pattern_->GetFocusHub()->getInnerFocusRectFunc_.operator()(roundRect);
    EXPECT_TRUE(pattern_->isFocusedBeforeClick_);

    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->GetFocusHub()->onBlurInternal_.operator()();
    EXPECT_FALSE(pattern_->isFocusedBeforeClick_);

    FlushLayoutTask(frameNode_);
    GetFocus();
    KeyEvent keyEvent;
    pattern_->GetFocusHub()->onKeyEventsInternal_[OnKeyEventType::DEFAULT].operator()(keyEvent);

    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();
    pattern_->UpdateScrollBarOffset();
    FlushLayoutTask(frameNode_);
    GetFocus();
    MouseInfo mouseInfo;
    pattern_->mouseEvent_->GetOnMouseEventFunc()(mouseInfo);
    EXPECT_TRUE(pattern_->IsUsingMouse());
}

/**
 * @tc.name: DoCallback004
 * @tc.desc: Test function OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, DoCallback004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. callback the HandleLongPress in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    TouchEventInfo touchEventInfo("onTouch");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::DOWN;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    /**
     * @tc.steps: step3. mock doubleClick.
     */
    pattern_->touchListener_->operator()(touchEventInfo);

    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->HandleTouchEvent(touchEventInfo);
}

/**
 * @tc.name: DoCallback005
 * @tc.desc: Test function OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, DoCallback005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. callback the InitDragDrop in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();

    /**
     * @tc.steps: step3. mock drag start.
     */
    pattern_->OnDragStart().operator()(dragEvent, "");
    EXPECT_TRUE(pattern_->showSelect_);
}

/**
 * @tc.name: DoCallback006
 * @tc.desc: Test function OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, DoCallback006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step2. callback the InitDragDrop in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    pattern_->ShowSelectAfterDragEvent();

    /**
     * @tc.steps: step3. mock show Select After DragEvent.
     */
    pattern_->processOverlayDelayTask_.operator()();
    EXPECT_EQ(pattern_->dragTextStart_, 0);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleIndex(), 0);
}

/**
 * @tc.name: DoCallback007
 * @tc.desc: Test function OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, DoCallback007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step2. callback the InitMouseEvent in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    bool isHover = true;

    /**
     * @tc.steps: step3. mock mouse hover.
     */
    pattern_->hoverEvent_->operator()(isHover);
    EXPECT_TRUE(pattern_->isOnHover_);

    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step4. mock mouse not hover.
     */
    isHover = false;
    pattern_->hoverEvent_->operator()(isHover);
    EXPECT_FALSE(pattern_->isOnHover_);
}

/**
 * @tc.name: MouseEvent001
 * @tc.desc: Test mouse event.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, MouseEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. callback the functions in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    FlushLayoutTask(frameNode_);
    GetFocus();

    MouseInfo mouseInfo;
    mouseInfo.SetButton(MouseButton::RIGHT_BUTTON);
    mouseInfo.SetAction(MouseAction::PRESS);
    pattern_->mouseEvent_->GetOnMouseEventFunc()(mouseInfo);
    EXPECT_TRUE(pattern_->IsUsingMouse());

    FlushLayoutTask(frameNode_);
    GetFocus();
    mouseInfo.SetButton(MouseButton::LEFT_BUTTON);
    mouseInfo.SetAction(MouseAction::PRESS);
    pattern_->mouseEvent_->GetOnMouseEventFunc()(mouseInfo);
    EXPECT_TRUE(pattern_->IsUsingMouse());
}

/**
 * @tc.name: MouseEvent002
 * @tc.desc: Test mouse event.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, MouseEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. callback the functions in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    FlushLayoutTask(frameNode_);
    GetFocus();

    MouseInfo mouseInfo;
    mouseInfo.SetButton(MouseButton::RIGHT_BUTTON);
    mouseInfo.SetAction(MouseAction::MOVE);
    pattern_->mouseEvent_->GetOnMouseEventFunc()(mouseInfo);
    EXPECT_TRUE(pattern_->IsUsingMouse());

    FlushLayoutTask(frameNode_);
    GetFocus();
    mouseInfo.SetButton(MouseButton::LEFT_BUTTON);
    mouseInfo.SetAction(MouseAction::MOVE);
    pattern_->mouseEvent_->GetOnMouseEventFunc()(mouseInfo);
    EXPECT_TRUE(pattern_->IsUsingMouse());
}

/**
 * @tc.name: MouseEvent003
 * @tc.desc: Test mouse event.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, MouseEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. callback the functions in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    FlushLayoutTask(frameNode_);
    GetFocus();

    MouseInfo mouseInfo;
    mouseInfo.SetButton(MouseButton::LEFT_BUTTON);
    mouseInfo.SetAction(MouseAction::RELEASE);
    pattern_->mouseEvent_->GetOnMouseEventFunc()(mouseInfo);
    EXPECT_FALSE(pattern_->IsUsingMouse());
}

/**
 * @tc.name: OnVirtualKeyboardAreaChanged001
 * @tc.desc: Test function OnVirtualKeyboardAreaChanged.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, OnVirtualKeyboardAreaChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. Set handlesSelection and call OnVirtualKeyboardAreaChanged.
     */
    FlushLayoutTask(frameNode_);
    pattern_->OnVirtualKeyboardAreaChanged();
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleIndex(), 0);
}

/**
 * @tc.name: CreateNodePaintMethod004
 * @tc.desc: Test textfield to create paint.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CreateNodePaintMethod004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    auto scrollBar = pattern_->GetScrollBar();
    scrollBar->SetPositionMode(PositionMode::BOTTOM);

    pattern_->UpdateScrollBarOffset();
    auto paint = AceType::DynamicCast<TextFieldPaintMethod>(pattern_->CreateNodePaintMethod());
    pattern_->OnScrollEndCallback();
    EXPECT_NE(pattern_->textFieldContentModifier_, nullptr);
}

/**
 * @tc.name: UpdateCaretPositionOnHandleMove001
 * @tc.desc: Test the caret position after handle move done in textarea.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, UpdateCaretPositionOnHandleMove001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(HELLO_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Create localoffset.
     * tc.expected: step2. Check if the value is right.
     */
    OffsetF localOffset1(1.0f, 1.0f);
    pattern_->selectOverlay_->GetCaretPositionOnHandleMove(localOffset1);

    FlushLayoutTask(frameNode_);
    GetFocus();
    OffsetF localOffset2(60.0f, 0.0f);
    pattern_->selectOverlay_->GetCaretPositionOnHandleMove(localOffset2);

    FlushLayoutTask(frameNode_);
    GetFocus();
    OffsetF localOffset3(30.0f, 0.0f);
    EXPECT_EQ(pattern_->selectOverlay_->GetCaretPositionOnHandleMove(localOffset3), 0);
}

/**
 * @tc.name: StripNextLine001
 * @tc.desc: Test function OnVirtualKeyboardAreaChanged.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, StripNextLine001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. Call OnScrollEndCallback.
     */
    FlushLayoutTask(frameNode_);
    GetFocus();
    std::string ori = "12345";
    std::wstring value = StringUtils::ToWstring(ori);
    pattern_->StripNextLine(value);
    EXPECT_EQ(ori, StringUtils::ToString(value));
}

/**
 * @tc.name: OnHandleMove001
 * @tc.desc: Test get Select HandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, OnHandleMove001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Call ProcessOverlay.
     */
    pattern_->ProcessOverlay();

    RectF handleRect;
    pattern_->selectOverlay_->OnHandleMove(handleRect, false);
    EXPECT_EQ(pattern_->selectController_->
        firstHandleInfo_.rect, RectF(2.0f, 2.0f, 1.5f, 0.0f));
}

/**
 * @tc.name: OnHandleMove002
 * @tc.desc: Test get Select HandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, OnHandleMove002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Call ProcessOverlay.
     */
    pattern_->ProcessOverlay();

    /**
     * @tc.steps: step2. set two handle and call OnHandleMove
     * tc.expected: step2. Check if the value is created.
     */
    pattern_->HandleSetSelection(5, 10, false);
    pattern_->SetIsSingleHandle(false);
    RectF handleRect;
    pattern_->selectOverlay_->OnHandleMove(handleRect, false);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 5);
}

/**
 * @tc.name: OnHandleMove003
 * @tc.desc: Test get Select HandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, OnHandleMove003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Call ProcessOverlay.
     */
    pattern_->ProcessOverlay();

    /**
     * @tc.steps: step2. set two handle and call OnHandleMove
     * tc.expected: step2. Check if the value is created.
     */
    pattern_->SetIsSingleHandle(false);
    RectF handleRect;
    pattern_->selectOverlay_->OnHandleMove(handleRect, true);
    OffsetF localOffset(0.0f, 0.0f);
    EXPECT_EQ(pattern_->parentGlobalOffset_, localOffset);
}

/**
 * @tc.name: OnHandleMove004
 * @tc.desc: Test get Select HandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, OnHandleMove004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Call ProcessOverlay.
     */
    pattern_->ProcessOverlay();

    /**
     * @tc.steps: step2. set two handle and call OnHandleMove
     * tc.expected: step2. Check if the value is created.
     */
    pattern_->SetIsSingleHandle(false);
    FlushLayoutTask(frameNode_);
    RectF handleRect;
    pattern_->selectOverlay_->OnHandleMove(handleRect, false);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 0);
}

/**
 * @tc.name: OnHandleMoveDone001
 * @tc.desc: Test the result after handle move done.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, OnHandleMoveDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. call selectoverlay ProcessOverlay.
     */
    pattern_->ProcessOverlay();
    RectF handleRect;
    pattern_->selectOverlay_->OnHandleMove(handleRect, false);
    pattern_->SetIsSingleHandle(false);
    pattern_->selectOverlay_->OnHandleMoveDone(handleRect, false);

    pattern_->SetIsSingleHandle(true);
    pattern_->selectOverlay_->OnHandleMoveDone(handleRect, false);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 0);
}

/**
 * @tc.name: OnHandleMoveDone002
 * @tc.desc: Test the result after handle move done.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, OnHandleMoveDone002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Call ProcessOverlay.
     */
    pattern_->ProcessOverlay();
    RectF handleRect;
    pattern_->selectOverlay_->OnHandleMove(handleRect, false);
    pattern_->SetIsSingleHandle(false);
    pattern_->selectOverlay_->OnHandleMoveDone(handleRect, false);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 0);
}

/**
 * @tc.name: RequestKeyboard001
 * @tc.desc: Test the result after request custom keyboard.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, RequestKeyboard001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxLength(DEFAULT_TEXT.size() - 2);
        model.SetInputFilter(DEFAULT_INPUT_FILTER, nullptr);
        model.SetCopyOption(CopyOptions::InApp);
        model.SetTextAlign(DEFAULT_TEXT_ALIGN);
        model.SetEnableAutoFill(false);
        model.SetType(TextInputType::TEXT);
        model.SetShowUnderline(true);
    });
    GetFocus();

    /**
     * @tc.steps: step2. Set SetCustomKeyboard.
     */
    pattern_->SetCustomKeyboard([]() {});
    pattern_->DumpInfo();
    pattern_->DumpAdvanceInfo();

    /**
     * @tc.steps: step3. call RequestKeyboard.
     */
    EXPECT_TRUE(pattern_->RequestKeyboard(true, true, true));
}

/**
 * @tc.name: RequestKeyboard002
 * @tc.desc: Test the result after request custom keyboard.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, RequestKeyboard002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set SetCustomKeyboard.
     */
    pattern_->SetCustomKeyboard([]() {});
    pattern_->RequestCustomKeyboard();

    /**
     * @tc.steps: step3. call RequestKeyboard.
     */
    EXPECT_TRUE(pattern_->RequestKeyboard(true, true, true));
}

/**
 * @tc.name: DumpViewDataPageNode001
 * @tc.desc: Test the result after dump viewData pageNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, DumpViewDataPageNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Create PageNodeInfoWrap ptr.
     */
    auto info = PageNodeInfoWrap::CreatePageNodeInfoWrap();
    auto autoFillType = AceAutoFillType::ACE_UNSPECIFIED;

    /**
     * @tc.steps: step3. call DumpViewDataPageNode.
     */
    pattern_->NotifyFillRequestSuccess(info, autoFillType);
}

/**
 * @tc.name: CheckAutoSave001
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and SetEnableAutoFill false.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(false);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return false
     */
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave002
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and SetEnableAutoFill true.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return false
     */
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave003
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set textValue empty.
     */
    CreateTextField("", "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return false
     */
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave004
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextInputType USER_NAME.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::USER_NAME);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return false
     */
    EXPECT_FALSE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step4. set PasswordTextValue ne textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave005
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextInputType VISIBLE_PASSWORD.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave006
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextInputType NEW_PASSWORD.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::NEW_PASSWORD);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave007
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType USER_NAME.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::USER_NAME);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave008
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType VISIBLE_PASSWORD.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::VISIBLE_PASSWORD);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave009
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType NEW_PASSWORD.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::NEW_PASSWORD);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0010
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType FULL_STREET_ADDRESS.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::FULL_STREET_ADDRESS);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0011
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType HOUSE_NUMBER.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::HOUSE_NUMBER);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0012
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType DISTRICT_ADDRESS.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::DISTRICT_ADDRESS);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0013
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType CITY_ADDRESS.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::CITY_ADDRESS);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0014
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType PROVINCE_ADDRESS.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::PROVINCE_ADDRESS);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0015
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType COUNTRY_ADDRESS.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::COUNTRY_ADDRESS);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0016
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType PERSON_FULL_NAME.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::PERSON_FULL_NAME);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0017
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType PERSON_LAST_NAME.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::PERSON_LAST_NAME);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0018
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType PERSON_FIRST_NAME.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::PERSON_FIRST_NAME);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0019
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType PHONE_NUMBER.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::PHONE_NUMBER);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0020
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType PHONE_COUNTRY_CODE.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::PHONE_COUNTRY_CODE);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0021
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType FULL_PHONE_NUMBER.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::FULL_PHONE_NUMBER);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0022
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType EMAIL_ADDRESS.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::EMAIL_ADDRESS);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0023
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType BANK_CARD_NUMBER.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::BANK_CARD_NUMBER);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0024
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType ID_CARD_NUMBER.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::ID_CARD_NUMBER);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0025
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType PRECISE_TIME.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::PRECISE_TIME);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0026
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType HOUR_AND_MINUTE.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::HOUR_AND_MINUTE);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0027
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType DATE.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::DATE);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0028
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType MONTH.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::MONTH);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0029
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckAutoSave0029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType YEAR.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::YEAR);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillPasswordTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillPasswordTextValue_ = "abcdefghijklmnopqrstuvwx";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}
/**
 * @tc.name: IsTouchAtLeftOffset001
 * @tc.desc: Test the result after touch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, IsTouchAtLeftOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. set currentOffsetX 10 and call IsTouchAtLeftOffset.
     * @tc.expected: return true
     */
    EXPECT_TRUE(pattern_->IsTouchAtLeftOffset(10));

    /**
     * @tc.steps: step2. set currentOffsetX 400 and call IsTouchAtLeftOffset.
     * @tc.expected: return false
     */
    EXPECT_FALSE(pattern_->IsTouchAtLeftOffset(400));
}

/**
 * @tc.name: GetDragUpperLeftCoordinates001
 * @tc.desc: Test dragUpper left coordinates.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, GetDragUpperLeftCoordinates001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2.call GetDragUpperLeftCoordinates.
     * @tc.expected: return true
     */
    OffsetF localOffset(0.0f, 0.0f);
    EXPECT_EQ(pattern_->GetDragUpperLeftCoordinates(), localOffset);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test color configuration update.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, OnColorConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2.call OnColorConfigurationUpdate.
     */
    pattern_->OnColorConfigurationUpdate();
    EXPECT_TRUE(pattern_->colorModeChange_);
}

/**
 * @tc.name: UpdateOverlayModifier001
 * @tc.desc: Test textfield update overlay modifier.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, UpdateOverlayModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. set cursor color and call UpdateContentModifier
     * tc.expected: step2. selected color equals cursor color.
     */
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    auto paintMethod = AceType::DynamicCast<TextFieldPaintMethod>(pattern_->CreateNodePaintMethod());
    EXPECT_NE(paintMethod, nullptr);
    auto overlayModifier = paintMethod->textFieldOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);

    paintProperty->ResetSelectedBackgroundColor();
    EXPECT_FALSE(paintProperty->HasSelectedBackgroundColor());
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
    Color cursorColor = Color::RED;
    double defaultOpacity = 0.2;
    auto expectedSelectedColor = cursorColor.ChangeOpacity(defaultOpacity);
    paintProperty->UpdateCursorColor(cursorColor);
    paintMethod->UpdateOverlayModifier(paintWrapper);
    EXPECT_TRUE(overlayModifier->selectedColor_->Get().ToColor() == expectedSelectedColor);

    /**
     * @tc.steps: step3. set select background color and call UpdateContentModifier
     * tc.expected: step3. selected color equals setting select background.
     */
    paintProperty->UpdateSelectedBackgroundColor(Color::BLUE);
    paintMethod->UpdateOverlayModifier(paintWrapper);
    EXPECT_TRUE(overlayModifier->selectedColor_->Get().ToColor() == Color::BLUE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}
} // namespace OHOS::Ace::NG
