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
    EXPECT_TRUE(pattern_->isSingleHandle_);
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
    pattern_->OnCursorTwinkling();
    pattern_->OnAfterModifyDone();
    EXPECT_TRUE(pattern_->isSingleHandle_);
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
    pattern_->ProcessOverlay(true, true, true);
    pattern_->HandleSetSelection(5, 10, false);
    pattern_->UpdateSelectOverlaySecondHandle(true);
    EXPECT_NE(pattern_->GetSelectOverlayProxy(), nullptr);

    pattern_->UpdateSelectOverlayDoubleHandle(true, true);
    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->UpdateSelectOverlayDoubleHandle(true, true);
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
    OffsetF localOffset(1.0f, 1.0f);

    /**
     * @tc.steps: step2. Set secondhandle. Call function GetSelectHandleInfo.
     * @tc.expected: Check if return true.
     */
    pattern_->HandleSetSelection(5, 10, false);
    pattern_->UpdateSelectOverlaySecondHandle(true);
    EXPECT_EQ(pattern_->GetSelectHandleInfo(localOffset).paintRect, RectF(1.0f, 1.0f, 1.5f, 50.0f));
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
    EXPECT_FALSE(pattern_->isUsingMouse_);
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

    FlushLayoutTask(frameNode_);
    GetFocus();
    MouseInfo mouseInfo;
    pattern_->mouseEvent_->GetOnMouseEventFunc()(mouseInfo);
    EXPECT_TRUE(pattern_->isUsingMouse_);
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

    /**
     * @tc.steps: step2. callback the HandleLongPress in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    TouchEventInfo touchEventInfo("onTouch");

    /**
     * @tc.steps: step3. mock doubleClick.
     */
    pattern_->touchListener_->operator()(touchEventInfo);

    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->HandleTouchEvent(touchEventInfo);
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
    EXPECT_EQ(pattern_->selectController_->
        firstHandleInfo_.rect, RectF(0.0f, 0.0f, 0.0f, 0.0f));
}

} // namespace OHOS::Ace::NG
