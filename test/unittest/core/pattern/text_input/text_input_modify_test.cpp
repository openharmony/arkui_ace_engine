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

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "test/unittest/core/pattern/text_input/mock/mock_text_field_select_overlay.h"

#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

using namespace testing;
using namespace testing::ext;
using NodeId = int32_t;

namespace OHOS::Ace::NG {
namespace {
constexpr double ICON_SIZE = 24;
constexpr double ICON_HOT_ZONE_SIZE = 40;
constexpr double FONT_SIZE = 16;
const Dimension STROKE_DASH_1 {1.0, DimensionUnit::PX};
constexpr int32_t DEFAULT_NODE_ID = 1;
constexpr int32_t MIN_PLATFORM_VERSION = 10;
constexpr int32_t DEFAULT_VALUE = 0;
constexpr int32_t ID = 0;
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
const std::string HELLO_TEXT = "hello";
const std::u16string HELLO_TEXT_U16 = u"hello";
const std::string DEFAULT_PLACE_HOLDER = "please input text here";
const std::string LOWERCASE_FILTER = "[a-z]";
const std::string NUMBER_FILTER = "^[0-9]*$";
const std::string DEFAULT_INPUT_FILTER = "[a-z]";
const TextAlign DEFAULT_TEXT_ALIGN = TextAlign::LEFT;
const Color BUBBLE_PAINT_PROPERTY_MASK_COLOR = Color(0XFFFF0000);
const float PADDING_FIVE = 5.0f;
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

    void FlushLayoutTask(const RefPtr<FrameNode>& frameNode);
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
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([textFieldTheme = textFieldTheme](ThemeType type, int id) -> RefPtr<Theme> {
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

void TextInputModifyBase::FlushLayoutTask(const RefPtr<FrameNode>& frameNode)
{
    frameNode->SetActive();
    frameNode->isLayoutDirtyMarked_ = true;
    frameNode->CreateLayoutTask();
    auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
    auto wrapper = frameNode->CreatePaintWrapper();
    if (wrapper != nullptr) {
        wrapper->FlushRender();
    }
    paintProperty->CleanDirty();
    frameNode->SetActive(false);
}

void TextInputModifyBase::CreateTextField(
    const std::string& text, const std::string& placeHolder, const std::function<void(TextFieldModelNG&)>& callback)
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(DEFAULT_NODE_ID);
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(StringUtils::Str8ToStr16(placeHolder), StringUtils::Str8ToStr16(text));
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
    EXPECT_EQ(pattern_->selectOverlay_->GetCaretPositionOnHandleMove(localOffset1, true), 0);

    FlushLayoutTask(frameNode_);
    GetFocus();
    OffsetF localOffset2(720.0f, 1.0f);
    EXPECT_EQ(pattern_->selectOverlay_->GetCaretPositionOnHandleMove(localOffset2, true), 26);

    FlushLayoutTask(frameNode_);
    GetFocus();
    OffsetF localOffset3(30.0f, 1.0f);
    EXPECT_EQ(pattern_->selectOverlay_->GetCaretPositionOnHandleMove(localOffset3, true), 0);
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
    EXPECT_EQ(pattern_->selectOverlay_->GetSecondHandleInfo()->paintRect.GetOffset(), OffsetF(0.0f, 0.0f));
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
    EXPECT_FALSE(pattern_->moveCaretState_.isTouchCaret);
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
    mouseInfo.SetAction(MouseAction::PRESS);
    pattern_->selectOverlay_->SetUsingMouse(false);
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
    EXPECT_EQ(pattern_->moveCaretState_.touchDownOffset, Offset(0.0f, 0.0f));
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
 * @tc.name: DoCallback008
 * @tc.desc: Test function OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, DoCallback008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. callback the InitDragDrop in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();

    /**
     * @tc.steps: step3. mock drag drop.
     */
    pattern_->GetThumbnailCallback()(Offset(0.0f, 0.0f));
    pattern_->OnDragDrop()(dragEvent, "");
    EXPECT_TRUE(pattern_->showSelect_);
}

/**
 * @tc.name: DoCallback009
 * @tc.desc: Test function OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, DoCallback009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. callback the InitDragDrop in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();

    /**
     * @tc.steps: step3. mock drag drop.
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    pattern_->OnDragDrop()(dragEvent, "");
    EXPECT_EQ(pattern_->dragStatus_, DragStatus::ON_DROP);
}

/**
 * @tc.name: DoCallback0010
 * @tc.desc: Test function OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, DoCallback010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. callback the InitDragDrop in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();

    /**
     * @tc.steps: step3. mock drag drop.
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    pattern_->OnDragDrop()(dragEvent, "hello world");
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    EXPECT_EQ(pattern_->dragStatus_, DragStatus::NONE);
}

/**
 * @tc.name: DoCallback0011
 * @tc.desc: Test function OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, DoCallback011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. callback the AccessibilityActions in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    FlushLayoutTask(frameNode_);
    GetFocus();
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->actionSetTextImpl_.operator()(DEFAULT_TEXT);
    EXPECT_EQ(pattern_->GetTextValue(), DEFAULT_TEXT);

    FlushLayoutTask(frameNode_);
    GetFocus();
    int32_t start = 5;
    int32_t end = 10;
    accessibilityProperty->actionSetSelectionImpl_.operator()(start, end, false);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, start);
}

/**
 * @tc.name: DoCallback0012
 * @tc.desc: Test function OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, DoCallback012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCopyOption(CopyOptions::Local);
        model.SetType(TextInputType::TEXT);
    });

    /**
     * @tc.steps: step2. callback the AccessibilityActions in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    GetFocus();
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    int32_t start = 5;
    int32_t end = 10;
    pattern_->SetSelectionFlag(start, end);
    pattern_->SetAccessibilityAction();
    accessibilityProperty->actionCopyImpl_.operator()();
    accessibilityProperty->actionCutImpl_.operator()();
    accessibilityProperty->actionPasteImpl_.operator()();
    accessibilityProperty->actionClearSelectionImpl_.operator()();
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern_->GetTextValue(), "abcdefghijfghijklmnopqrstuvwxyz");
}

/**
 * @tc.name: DoCallback0013
 * @tc.desc: Test function OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, DoCallback013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. callback the AccessibilityActions in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->actionSetCursorIndexImpl_.operator()(5);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 5);
    auto index = accessibilityProperty->actionGetCursorIndexImpl_.operator()();
    EXPECT_EQ(index, 5);
}

/**
 * @tc.name: DoCallback0014
 * @tc.desc: Test function OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, DoCallback014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. callback the AccessibilityActions in OnModifyDone.
     * @tc.expected: Check if return true.
     */
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->actionMoveTextImpl_.operator()(0, false);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 26);

    pattern_->SetCaretPosition(5);
    pattern_->SetAccessibilityAction();
    accessibilityProperty->actionMoveTextImpl_.operator()(0, true);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 5);

    pattern_->SetCaretPosition(5);
    pattern_->SetAccessibilityAction();
    accessibilityProperty->actionMoveTextImpl_.operator()(1, false);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 4);

    pattern_->SetCaretPosition(5);
    pattern_->SetAccessibilityAction();
    accessibilityProperty->actionMoveTextImpl_.operator()(1, true);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 6);
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
    mouseInfo.SetAction(MouseAction::PRESS);
    pattern_->selectOverlay_->SetUsingMouse(false);
    pattern_->mouseEvent_->GetOnMouseEventFunc()(mouseInfo);
    EXPECT_TRUE(pattern_->IsUsingMouse());

    FlushLayoutTask(frameNode_);
    GetFocus();
    mouseInfo.SetButton(MouseButton::LEFT_BUTTON);
    mouseInfo.SetAction(MouseAction::PRESS);
    pattern_->selectOverlay_->SetUsingMouse(false);
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
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleIndex(), 26);
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
 * @tc.name: OnScrollEndMenuVisibile001
 * @tc.desc: Test textfield On Scroll End Menu Visibile.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, OnScrollEndMenuVisibile001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text field.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.steps: step2. call OnScrollEndCallback
     * tc.expected: step2. Check if the Menu Visibile.
    */
    pattern_->selectOverlay_->SetUsingMouse(false);
    pattern_->isTextSelectionMenuShow_ = true;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->SetSelectionFlag(5.0f, 5.0f, options);

    pattern_->OnScrollEndCallback();
    EXPECT_TRUE(pattern_->selectOverlay_->IsCurrentMenuVisibile());

    /**
     * @tc.steps: step2. call CloseSelectOverlay
     * tc.expected: step2. Check if the Menu Visibile.
    */
    pattern_->CloseSelectOverlay(true);
    pattern_->OnScrollEndCallback();
    EXPECT_FALSE(pattern_->selectOverlay_->IsCurrentMenuVisibile());
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
    pattern_->selectOverlay_->GetCaretPositionOnHandleMove(localOffset1, true);

    FlushLayoutTask(frameNode_);
    GetFocus();
    OffsetF localOffset2(60.0f, 0.0f);
    pattern_->selectOverlay_->GetCaretPositionOnHandleMove(localOffset2, true);

    FlushLayoutTask(frameNode_);
    GetFocus();
    OffsetF localOffset3(30.0f, 0.0f);
    EXPECT_EQ(pattern_->selectOverlay_->GetCaretPositionOnHandleMove(localOffset3, true), 0);
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
 * @tc.name: StripNextLine002
 * @tc.desc: Test function OnVirtualKeyboardAreaChanged.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, StripNextLine002, TestSize.Level1)
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
    std::string ori = "123\n45";
    std::wstring value = StringUtils::ToWstring(ori);
    pattern_->StripNextLine(value);
    EXPECT_EQ("12345", StringUtils::ToString(value));
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
        firstHandleInfo_.rect.GetOffset(), OffsetF(0.0f, 0.0f));
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
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 26);
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
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 26);
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
 * @tc.name: RequestKeyboard003
 * @tc.desc: Test the result after request custom keyboard.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, RequestKeyboard003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. CloseKeyboard.
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_TRUE(pattern_->showKeyBoardOnFocus_);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_FALSE(pattern_->showKeyBoardOnFocus_);

    /**
     * @tc.steps: step3. set RequestKeyboard.
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_TRUE(pattern_->showKeyBoardOnFocus_);
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
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetMaxLength(DEFAULT_TEXT.size());
    });
    GetFocus();

    /**
     * @tc.steps: step2. Create PageNodeInfoWrap ptr.
     */
    auto viewData = ViewDataWrap::CreateViewDataWrap();
    auto info = PageNodeInfoWrap::CreatePageNodeInfoWrap();
    auto autoFillType = AceAutoFillType::ACE_UNSPECIFIED;

    /**
     * @tc.steps: step3. call DumpViewDataPageNode.
     */
    pattern_->NotifyFillRequestSuccess(viewData, info, autoFillType);
    EXPECT_EQ(pattern_->selectController_->caretInfo_.index, 0);
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
    EXPECT_EQ(pattern_->floatCaretState_.OriginCursorColor, Color(0x4D000000));
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

    paintProperty->UpdateSelectedBackgroundColor(Color::BLUE);
    paintMethod->UpdateOverlayModifier(paintWrapper);
    EXPECT_TRUE(overlayModifier->selectedColor_->Get().ToColor() == Color::BLUE);
}

/**
 * @tc.name: CheckTextAlignByDirection
 * @tc.desc: Test the effect of using TextAlign with direction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CheckTextAlignByDirection, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. set direction RTL
     */
    auto direction = TextDirection::RTL;
    auto textAlign = TextAlign::START;
    pattern_->CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(textAlign, TextAlign::END);

    FlushLayoutTask(frameNode_);
    GetFocus();
    textAlign = TextAlign::END;
    pattern_->CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(textAlign, TextAlign::START);
}

/**
 * @tc.name: CreateFrameNode001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, CreateFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    auto frameNode1 = TextFieldModelNG::CreateFrameNode(ID, u"", u"", false);
    EXPECT_NE(frameNode1, nullptr);
 
    /**
     * @tc.steps: step2. Set CustomerDraggable true. Call function OnModifyDone.
     * @tc.expected: Check if the text draggable.
     */
    auto frameNode2 = TextFieldModelNG::CreateFrameNode(ID, u"", HELLO_TEXT_U16, true);
    EXPECT_NE(frameNode2, nullptr);
}
 
/**
 * @tc.name: ProcessDefaultStyleAndBehaviors001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, ProcessDefaultStyleAndBehaviors001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = FrameNode::CreateFrameNode(
            true ? V2::TEXTAREA_ETS_TAG : V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
        model.ProcessDefaultStyleAndBehaviors(frameNode);
        ASSERT_NE(frameNode, nullptr);
    });
 
    /**
     * @tc.steps: step2. Set CustomerDraggable true. Call function OnModifyDone.
     * @tc.expected: Check if the text draggable.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = FrameNode::CreateFrameNode(
            true ? V2::TEXTAREA_ETS_TAG : V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
        frameNode->MarkBuildDone();
        model.ProcessDefaultStyleAndBehaviors(frameNode);
        ASSERT_NE(frameNode, nullptr);
    });
}
 
/**
 * @tc.name: SetBackgroundColor001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, SetBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetBackgroundColor(BUBBLE_PAINT_PROPERTY_MASK_COLOR, true);
    });
    auto paintProperty = frameNode_->GetPaintPropertyPtr<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetBackgroundColorValue(Color(0x00000000)), Color(0xFF000000));

    /**
     * @tc.steps: step2. Set CustomerDraggable true. Call function OnModifyDone.
     * @tc.expected: Check if the text draggable.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetBackgroundColor(BUBBLE_PAINT_PROPERTY_MASK_COLOR, false);
    });
    auto paintProperty2 = frameNode_->GetPaintPropertyPtr<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty2, nullptr);
    EXPECT_EQ(paintProperty2->GetBackgroundColorValue(Color(0x00000000)), Color(0xFFFF0000));
}

/**
 * @tc.name: SetPadding001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, SetPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        PaddingProperty padding;
        Edge edge;
        padding.left = CalcLength(PADDING_FIVE);
        padding.right = CalcLength(PADDING_FIVE);
        padding.top = CalcLength(PADDING_FIVE);
        padding.bottom = CalcLength(PADDING_FIVE);
        model.SetPadding(padding, edge, true);
    });
    auto paintProperty = frameNode_->GetPaintPropertyPtr<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    auto padding = paintProperty->GetPaddingByUser();
    EXPECT_EQ(padding->left, CalcLength(0.0f));
 
    /**
     * @tc.steps: step2. Set CustomerDraggable true. Call function OnModifyDone.
     * @tc.expected: Check if the text draggable.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        PaddingProperty padding;
        Edge edge;
        padding.left = CalcLength(PADDING_FIVE);
        padding.right = CalcLength(PADDING_FIVE);
        padding.top = CalcLength(PADDING_FIVE);
        padding.bottom = CalcLength(PADDING_FIVE);
        model.SetPadding(padding, edge, false);
    });
    auto paintProperty2 = frameNode_->GetPaintPropertyPtr<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty2, nullptr);
    auto padding2 = paintProperty2->GetPaddingByUser();
    EXPECT_EQ(padding2->left, CalcLength(5.0f));
}
 
/**
 * @tc.name: SetInputStyle001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, SetInputStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        frameNode->GetPattern<TextFieldPattern>()->isTextInput_ = true;
        model.SetInputStyle(frameNode, InputStyle::DEFAULT);
    });
 
    /**
     * @tc.steps: step2. Set CustomerDraggable true. Call function OnModifyDone.
     * @tc.expected: Check if the text draggable.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        model.SetInputStyle(frameNode, InputStyle::DEFAULT);
    });
 
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        frameNode->GetPattern<TextFieldPattern>()->isTextInput_ = true;
        model.SetInputStyle(frameNode, InputStyle::INLINE);
    });
}
 
/**
 * @tc.name: SetTextAlign001
 * @tc.desc: Test the SetTextAlign.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, SetTextAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        auto pattern = frameNode->GetPattern<TextFieldPattern>();
        ASSERT_NE(pattern, nullptr);
        model.SetTextAlign(frameNode, TextAlign::JUSTIFY);
    });
 
    /**
     * @tc.steps: step2. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        auto pattern = frameNode->GetPattern<TextFieldPattern>();
        ASSERT_NE(pattern, nullptr);
        model.SetTextAlign(frameNode, TextAlign::START);
    });
}
 
/**
 * @tc.name: ResetMaxLength001
 * @tc.desc: Test the ResetMaxLength.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, ResetMaxLength001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
        ASSERT_NE(textFieldLayoutProperty, nullptr);
        model.ResetMaxLength(frameNode);
    });
}
 
/**
 * @tc.name: SetEnterKeyType001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, SetEnterKeyType001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        auto pattern = AceType::DynamicCast<TextFieldPattern>(frameNode->GetPattern());
        ASSERT_NE(pattern, nullptr);
        model.SetEnterKeyType(frameNode, TextInputAction::UNSPECIFIED);
    });
    /**
     * @tc.steps: step2. Set CustomerDraggable true. Call function OnModifyDone.
     * @tc.expected: Check if the text draggable.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        auto pattern = AceType::DynamicCast<TextFieldPattern>(frameNode->GetPattern());
        ASSERT_NE(pattern, nullptr);
        model.SetEnterKeyType(frameNode, TextInputAction::NONE);
    });
}
 
/**
 * @tc.name: GetTextSelectionIndex001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, GetTextSelectionIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto pattern = frameNode->GetPattern<TextFieldPattern>();
        ASSERT_NE(pattern, DEFAULT_VALUE);
        model.GetTextSelectionIndex(frameNode, true);
    });
    /**
     * @tc.steps: step2. Set CustomerDraggable true. Call function OnModifyDone.
     * @tc.expected: Check if the text draggable.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto pattern = frameNode->GetPattern<TextFieldPattern>();
        ASSERT_NE(pattern, DEFAULT_VALUE);
        model.GetTextSelectionIndex(frameNode, false);
    });
}

/**
 * @tc.name: SetPlaceholderFont001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, SetPlaceholderFont001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        Font font;
        model.SetPlaceholderFont(font);
        font.fontSize = Dimension(2);
        font.fontStyle = Ace::FontStyle::NORMAL;
        font.fontWeight = FontWeight::W200;
        std::vector<std::string> families = { "cursive" };
        font.fontFamilies = families;
        model.SetPlaceholderFont(font);
    });
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_EQ(layoutProperty->GetPlaceholderFontSizeValue(Dimension(0)), Dimension(2));
}
 
/**
 * @tc.name: SetShowCounter001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, SetShowCounter001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
    });
    EXPECT_FALSE(pattern_->counterDecorator_);

    /**
     * @tc.steps: step2. Set CustomerDraggable true. Call function OnModifyDone.
     * @tc.expected: Check if the text draggable.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(false);
    });
    EXPECT_FALSE(pattern_->counterDecorator_);
}
 
/**
 * @tc.name: SetBackBorder001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, SetBackBorder001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        auto renderContext = frameNode->GetRenderContext();
        ASSERT_NE(renderContext, nullptr);
        model.SetBackBorder();
        EXPECT_FALSE(renderContext->HasBorderRadius());
        EXPECT_FALSE(renderContext->HasBorderColor());
        EXPECT_FALSE(renderContext->HasBorderWidth());
        EXPECT_FALSE(renderContext->HasBorderStyle());
    });
}
 
/**
 * @tc.name: SetCustomKeyboard001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, SetCustomKeyboard001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        std::function<void()> buildFunc;
        model.SetCustomKeyboard(std::move(buildFunc), true);
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        EXPECT_TRUE(frameNode->GetPattern<TextFieldPattern>());
    });
}
 
/**
 * @tc.name: SetCaretStyle001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, SetCaretStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CaretStyle caretStyle;
        caretStyle.caretWidth = STROKE_DASH_1;
        model.SetCaretStyle(frameNode, caretStyle);
    });
    auto paintProperty = frameNode_->GetPaintPropertyPtr<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetCursorWidthValue(Dimension(0.0f)), STROKE_DASH_1);

    /**
     * @tc.steps: step2. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CaretStyle caretStyle;
        model.SetCaretStyle(frameNode, caretStyle);
    });
    auto paintProperty2 = frameNode_->GetPaintPropertyPtr<TextFieldPaintProperty>();
    EXPECT_NE(paintProperty2, nullptr);
    EXPECT_EQ(paintProperty2->GetCursorWidthValue(Dimension(123.0f)), Dimension(0.0f));
}

/**
 * @tc.name: SetTextFieldText001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModifyTest, SetTextFieldText001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto pattern = frameNode->GetPattern<TextFieldPattern>();
        model.SetTextFieldText(frameNode, HELLO_TEXT_U16);
        auto textValue = pattern->GetTextValue();
        EXPECT_EQ(textValue, HELLO_TEXT);
    });
}
} // namespace OHOS::Ace::NG
