/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_model_ng.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double RADIUS_DEFAULT = 300.0;
const std::string HYPERLINK_ADDRESS = "https://www.baidu.com";
const std::string HYPERLINK_CONTENT = "baidu";
const std::string HYPERLINK_EXTRAINFO = "{\"url\":\"https://www.baidu.com\",\"title\":\"baidu\"}";
} // namespace

class HyperlinkTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static void SetThemeInCreate();
};

void HyperlinkTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    HyperlinkModelNG hyperlinkModelNG;
    SetThemeInCreate();
    hyperlinkModelNG.Create(HYPERLINK_ADDRESS, HYPERLINK_CONTENT);
}

void HyperlinkTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

void HyperlinkTestNg::SetThemeInCreate()
{
    auto themeManager = AceType::DynamicCast<MockThemeManager>(MockPipelineBase::GetCurrent()->GetThemeManager());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == TextTheme::TypeId()) {
            return AceType::MakeRefPtr<TextTheme>();
        }
        return AceType::MakeRefPtr<HyperlinkTheme>();
    }); 
}

/**
 * @tc.name: HyperlinkDrag001
 * @tc.desc: Test Hyperlink drag with src change.
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkDrag001, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<HyperlinkPattern>(HYPERLINK_ADDRESS); });
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::HYPERLINK_ETS_TAG);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(HYPERLINK_CONTENT);
    frameNode->SetDraggable(true);
    frameNode->MarkModifyDone();
    auto hyperlinkPattern = frameNode->GetPattern<HyperlinkPattern>();
    ASSERT_NE(hyperlinkPattern, nullptr);
    hyperlinkPattern->EnableDrag();
    // emulate drag event
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub->GetOnDragStart(), nullptr);
    auto extraParams =
        eventHub->GetDragExtraParams(std::string(), Point(RADIUS_DEFAULT, RADIUS_DEFAULT), DragEventType::START);
    auto dragDropInfo = (eventHub->GetOnDragStart())(nullptr, extraParams);

    // check dragInfo
    EXPECT_EQ(dragDropInfo.extraInfo, HYPERLINK_EXTRAINFO);
}

/**
 * @tc.name: HyperlinkPatternTest001
 * @tc.desc: Test HyperlinkPattern InitInputEvent.
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkPatternTest001, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<HyperlinkPattern>(HYPERLINK_ADDRESS); });
    ASSERT_NE(frameNode, nullptr);
    auto hyperlinkPattern = frameNode->GetPattern<HyperlinkPattern>();
    ASSERT_NE(hyperlinkPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto inputHub = AceType::MakeRefPtr<InputEventHub>(eventHub);

    hyperlinkPattern->InitInputEvent(inputHub);
    auto onHoverEvent = hyperlinkPattern->onHoverEvent_->onHoverCallback_;
    auto onMouseEvent = hyperlinkPattern->onMouseEvent_->onMouseCallback_;

    auto pipeline = PipelineContext::GetCurrentContext();
    onHoverEvent(true);
    EXPECT_EQ(pipeline->mouseStyleNodeId_, frameNode->GetId());

    onHoverEvent(false);
    EXPECT_EQ(pipeline->mouseStyleNodeId_, -1);

    MouseInfo mouseInfo;
    onMouseEvent(mouseInfo);
    EXPECT_EQ(pipeline->mouseStyleNodeId_, frameNode->GetId());
}

/**
 * @tc.name: HyperlinkModelNGTest001
 * @tc.desc: Test HyperlinkModelNG SetDraggable.
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkModelNGTest001, TestSize.Level1)
{
    auto themeManager = AceType::DynamicCast<MockThemeManager>(MockPipelineBase::GetCurrent()->GetThemeManager());
    ASSERT_NE(themeManager, nullptr);
    HyperlinkModelNG hyperlinkModelNG;
    SetThemeInCreate();
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    hyperlinkModelNG.SetDraggable(false);
    EXPECT_EQ(gestureHub->dragEventActuator_, nullptr);

    hyperlinkModelNG.SetDraggable(false);
    EXPECT_EQ(gestureHub->dragEventActuator_, nullptr);
}

/**
 * @tc.name: HyperlinkPatternTest002
 * @tc.desc: Test HyperlinkPattern InitLongPressEvent.
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkPatternTest002, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<HyperlinkPattern>(HYPERLINK_ADDRESS); });
    ASSERT_NE(frameNode, nullptr);
    auto hyperlinkPattern = frameNode->GetPattern<HyperlinkPattern>();
    ASSERT_NE(hyperlinkPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto inputHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);

    hyperlinkPattern->InitLongPressEvent(inputHub);
    auto longPressEvent = hyperlinkPattern->longPressEvent_->callback_;

    auto info = GestureEvent();
    longPressEvent(info);
    EXPECT_EQ(hyperlinkPattern->isLinked_, 1);
}

/**
 * @tc.name: HyperlinkPatternTest003
 * @tc.desc: Test HyperlinkPattern InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkPatternTest003, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<HyperlinkPattern>(HYPERLINK_ADDRESS); });
    ASSERT_NE(frameNode, nullptr);
    auto hyperlinkPattern = frameNode->GetPattern<HyperlinkPattern>();
    ASSERT_NE(hyperlinkPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto inputHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_FALSE(hyperlinkPattern->onTouchEvent_);
    hyperlinkPattern->InitTouchEvent(inputHub);
    EXPECT_TRUE(hyperlinkPattern->onTouchEvent_);
}

/**
 * @tc.name: HyperlinkPatternTest004
 * @tc.desc: Test HyperlinkPattern InitOnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkPatternTest004, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto hyperlinkNode = FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, stack->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<HyperlinkPattern>(HYPERLINK_ADDRESS); });
    stack->Push(hyperlinkNode);

    auto hyperlinkPattern = hyperlinkNode->GetPattern<HyperlinkPattern>();
    ASSERT_NE(hyperlinkPattern, nullptr);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_TAB;
    bool result = hyperlinkPattern->OnKeyEvent(event);
    EXPECT_FALSE(result);
    event.code = KeyCode::KEY_SPACE;
    result = hyperlinkPattern->OnKeyEvent(event);
    EXPECT_TRUE(result);
    event.code = KeyCode::KEY_ENTER;
    result = hyperlinkPattern->OnKeyEvent(event);
    EXPECT_TRUE(result);
    event.action = KeyAction::CLICK;
    result = hyperlinkPattern->OnKeyEvent(event);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HyperlinkPatternTest005
 * @tc.desc: Test HyperlinkPattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Hyperlink and get HyperlinkPattern.
     */
    auto hyperlinkNode =
        FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<HyperlinkPattern>(HYPERLINK_ADDRESS); });
    ASSERT_NE(hyperlinkNode, nullptr);
    auto hyperlinkPattern = hyperlinkNode->GetPattern<HyperlinkPattern>();
    ASSERT_NE(hyperlinkPattern, nullptr);

    /**
     * @tc.steps: step2. Call OnModifyDone while gestureHub is able or enable.
     * @tc.expected: TextColor of hyperlink is set different.
     */
    auto hub = hyperlinkNode->GetEventHub<EventHub>();
    ASSERT_NE(hub, nullptr);
    auto hyperlinkLayoutProperty = hyperlinkNode->GetLayoutProperty<HyperlinkLayoutProperty>();
    ASSERT_NE(hyperlinkLayoutProperty, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<HyperlinkTheme>();
    ASSERT_NE(theme, nullptr);
    hub->SetEnabled(true);
    hyperlinkNode->SetDraggable(false);
    hyperlinkLayoutProperty->UpdateTextColor(Color::BLUE);
    hyperlinkPattern->isLinked_ = true;
    hyperlinkPattern->OnModifyDone();
    EXPECT_EQ(hyperlinkLayoutProperty->GetTextColor().value(), Color::BLACK);
    EXPECT_FALSE(hyperlinkPattern->isLinked_);
    hub->SetEnabled(false);
    hyperlinkNode->SetDraggable(true);
    theme->textDisabledColor_ = Color::RED;
    hyperlinkPattern->isLinked_ = true;
    hyperlinkPattern->OnModifyDone();
    EXPECT_EQ(hyperlinkLayoutProperty->GetTextColor().value(), Color::BLACK);
    EXPECT_FALSE(hyperlinkPattern->isLinked_);
}

/**
 * @tc.name: HyperlinkPatternTest006
 * @tc.desc: Test HyperlinkPattern OnTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Hyperlink and get HyperlinkPattern.
     */
    auto hyperlinkNode =
        FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<HyperlinkPattern>(HYPERLINK_ADDRESS); });
    ASSERT_NE(hyperlinkNode, nullptr);
    auto hyperlinkPattern = hyperlinkNode->GetPattern<HyperlinkPattern>();
    ASSERT_NE(hyperlinkPattern, nullptr);

    /**
     * @tc.steps: step2. Call OnTouchEvent while isLinked_ is true or false.
     * @tc.expected: DecorationColor of hyperlink text is set.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<HyperlinkTheme>();
    ASSERT_NE(theme, nullptr);
    theme->textColor_ = Color::RED;
    theme->textLinkedColor_ = Color::GREEN;
    theme->textTouchedColor_ = Color::GRAY;
    theme->textUnSelectedDecoration_ = TextDecoration::UNDERLINE;
    auto hyperlinkLayoutProperty = hyperlinkNode->GetLayoutProperty<HyperlinkLayoutProperty>();
    ASSERT_NE(hyperlinkLayoutProperty, nullptr);
    hyperlinkLayoutProperty->UpdateTextColor(Color::BLACK);
    hyperlinkLayoutProperty->UpdateTextDecorationColor(Color::BLACK);
    hyperlinkPattern->isLinked_ = true;
    TouchEventInfo touchEventInfo("");
    TouchLocationInfo touchInfo(1);
    touchInfo.SetTouchType(TouchType::DOWN);
    touchEventInfo.changedTouches_.clear();
    touchEventInfo.changedTouches_.emplace_back(touchInfo);
    hyperlinkPattern->OnTouchEvent(touchEventInfo);
    EXPECT_EQ(hyperlinkLayoutProperty->GetTextDecorationColor().value(), Color::RED.BlendColor(Color::BLACK));

    hyperlinkPattern->isLinked_ = false;
    hyperlinkPattern->OnTouchEvent(touchEventInfo);
    EXPECT_EQ(hyperlinkLayoutProperty->GetTextColor().value(), Color::RED.BlendColor(Color::BLACK));
    EXPECT_EQ(hyperlinkLayoutProperty->GetTextDecorationColor().value(), Color::RED.BlendColor(Color::BLACK));

    /**
     * @tc.steps: step3. Call OnTouchEvent while TouchType is UP or DOWN or else.
     * @tc.expected: DecorationColor of hyperlink text is set.
     */
    touchInfo.SetTouchType(TouchType::UP);
    touchEventInfo.changedTouches_.clear();
    touchEventInfo.changedTouches_.emplace_back(touchInfo);
    hyperlinkPattern->OnTouchEvent(touchEventInfo);
    EXPECT_EQ(hyperlinkLayoutProperty->GetTextDecoration().value(), TextDecoration::NONE);
    touchInfo.SetTouchType(TouchType::CANCEL);
    touchEventInfo.changedTouches_.clear();
    touchEventInfo.changedTouches_.emplace_back(touchInfo);
    hyperlinkPattern->OnTouchEvent(touchEventInfo);
}

/**
 * @tc.name: HyperlinkPatternTest007
 * @tc.desc: Test HyperlinkPattern OnTouchEvent Unnormal Scenario.
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Hyperlink and get HyperlinkPattern.
     */
    auto hyperlinkNode =
        FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<HyperlinkPattern>(HYPERLINK_ADDRESS); });
    ASSERT_NE(hyperlinkNode, nullptr);
    auto hyperlinkPattern = hyperlinkNode->GetPattern<HyperlinkPattern>();
    ASSERT_NE(hyperlinkPattern, nullptr);

    /**
     * @tc.steps: step2. Call OnTouchEvent when the touchEventInfo is empty.
     * @tc.expected: DecorationColor and TextColor of the hyperlink will not change.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<HyperlinkTheme>();
    ASSERT_NE(theme, nullptr);
    theme->textColor_ = Color::RED;
    theme->textLinkedColor_ = Color::GREEN;
    theme->textTouchedColor_ = Color::GRAY;
    theme->textUnSelectedDecoration_ = TextDecoration::UNDERLINE;
    auto hyperlinkLayoutProperty = hyperlinkNode->GetLayoutProperty<HyperlinkLayoutProperty>();
    ASSERT_NE(hyperlinkLayoutProperty, nullptr);
    hyperlinkLayoutProperty->UpdateTextColor(Color::BLACK);
    hyperlinkLayoutProperty->UpdateTextDecorationColor(Color::BLACK);
    hyperlinkPattern->isLinked_ = true;
    TouchEventInfo touchEventInfo("");
    hyperlinkPattern->OnTouchEvent(touchEventInfo);
    EXPECT_EQ(hyperlinkLayoutProperty->GetTextDecorationColor().value(), Color::BLACK);
    EXPECT_EQ(hyperlinkLayoutProperty->GetTextColor().value(), Color::BLACK);
}

/**
 * @tc.name: HyperlinkPatternTest008
 * @tc.desc: Test HyperlinkPattern OnHoverEvent.
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Hyperlink and get HyperlinkPattern.
     */
    auto hyperlinkNode =
        FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<HyperlinkPattern>(HYPERLINK_ADDRESS); });
    ASSERT_NE(hyperlinkNode, nullptr);
    auto hyperlinkPattern = hyperlinkNode->GetPattern<HyperlinkPattern>();
    ASSERT_NE(hyperlinkPattern, nullptr);

    /**
     * @tc.steps: step2. Call OnHoverEvent while isLinked_ is true or false.
     * @tc.expected: DecorationColor of hyperlink text is set.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<HyperlinkTheme>();
    ASSERT_NE(theme, nullptr);
    theme->textColor_ = Color::RED;
    theme->textLinkedColor_ = Color::GREEN;
    theme->textUnSelectedDecoration_ = TextDecoration::UNDERLINE;
    auto hyperlinkLayoutProperty = hyperlinkNode->GetLayoutProperty<HyperlinkLayoutProperty>();
    ASSERT_NE(hyperlinkLayoutProperty, nullptr);
    hyperlinkLayoutProperty->UpdateTextDecorationColor(Color::BLACK);
    hyperlinkPattern->isLinked_ = true;
    hyperlinkPattern->OnHoverEvent(true);
    EXPECT_EQ(hyperlinkLayoutProperty->GetTextDecorationColor().value(), Color::RED.BlendColor(Color::BLACK));
    hyperlinkPattern->isLinked_ = false;
    hyperlinkPattern->OnHoverEvent(true);
    EXPECT_EQ(hyperlinkLayoutProperty->GetTextDecorationColor().value(), Color::BLACK);
    hyperlinkPattern->OnHoverEvent(false);
    EXPECT_EQ(hyperlinkLayoutProperty->GetTextDecoration().value(), TextDecoration::NONE);
}
} // namespace OHOS::Ace::NG
