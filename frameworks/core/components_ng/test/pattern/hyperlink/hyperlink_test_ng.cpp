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

#include "core/event/mouse_event.h"

#define private public
#define protected public
#include "base/memory/ace_type.h"
#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_model_ng.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TARGET_ID = 3;
constexpr double RADIUS_DEFAULT = 300.0;
const std::string HYPERLINK_ADDRESS = "https://www.baidu.com";
const std::string HYPERLINK_CONTENT = "baidu";
const std::string HYPERLINK_EXTRAINFO = "{\"url\":\"https://www.baidu.com\",\"title\":\"baidu\"}";
} // namespace

class HyperlinkTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static RefPtr<FrameNode> CreateHyperlinkNode(const std::string& address, const std::string& content);
};

void HyperlinkTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
}

void HyperlinkTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

RefPtr<FrameNode> HyperlinkTestNg::CreateHyperlinkNode(const std::string& address, const std::string& content)
{
    HyperlinkModelNG hyperlink;
    hyperlink.Create(address, content);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

/**
 * @tc.name: HyperlinkDrag001
 * @tc.desc: Test Hyperlink drag with src change.
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkDrag001, TestSize.Level1)
{
    auto frameNode = HyperlinkTestNg::CreateHyperlinkNode(HYPERLINK_ADDRESS, HYPERLINK_CONTENT);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::HYPERLINK_ETS_TAG);
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
    auto frameNode = HyperlinkTestNg::CreateHyperlinkNode(HYPERLINK_ADDRESS, HYPERLINK_CONTENT);
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
    auto* stack = ViewStackProcessor::GetInstance();
    auto hyperlinkNode = FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, stack->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<HyperlinkPattern>(HYPERLINK_ADDRESS); });
    stack->Push(hyperlinkNode);

    HyperlinkModelNG hyperlinkModelNG;
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    hyperlinkModelNG.SetDraggable(false);
    EXPECT_FALSE(hyperlinkNode->IsDraggable());
    EXPECT_EQ(gestureHub->dragEventActuator_, nullptr);

    hyperlinkModelNG.SetDraggable(false);
    EXPECT_FALSE(hyperlinkNode->IsDraggable());
    EXPECT_EQ(gestureHub->dragEventActuator_, nullptr);

    hyperlinkModelNG.SetDraggable(true);
    EXPECT_TRUE(hyperlinkNode->IsDraggable());
    EXPECT_NE(gestureHub->dragEventActuator_, nullptr);

    hyperlinkModelNG.SetDraggable(true);
    EXPECT_TRUE(hyperlinkNode->IsDraggable());
    EXPECT_NE(gestureHub->dragEventActuator_, nullptr);
}

/**
 * @tc.name: HyperlinkPatternTest002
 * @tc.desc: Test HyperlinkPattern InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkPatternTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto hyperlinkNode = FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, stack->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<HyperlinkPattern>(HYPERLINK_ADDRESS); });
    stack->Push(hyperlinkNode);

    auto hyperlinkPattern = hyperlinkNode->GetPattern<HyperlinkPattern>();
    ASSERT_NE(hyperlinkPattern, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    hyperlinkPattern->onTouchEvent_ = nullptr;
    hyperlinkPattern->InitTouchEvent(gestureEventHub);
    TouchEventFunc callback = [](TouchEventInfo& info) {};
    hyperlinkPattern->onTouchEvent_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(callback));
    EXPECT_TRUE(hyperlinkPattern->onTouchEvent_);
}

/**
 * @tc.name: HyperlinkPatternTest003
 * @tc.desc: Test HyperlinkPattern InitOnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkPatternTest003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto hyperlinkNode = FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, stack->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<HyperlinkPattern>(HYPERLINK_ADDRESS); });
    stack->Push(hyperlinkNode);

    auto hyperlinkPattern = hyperlinkNode->GetPattern<HyperlinkPattern>();
    ASSERT_NE(hyperlinkPattern, nullptr);
    RefPtr<EventHub> eventHub = AccessibilityManager::MakeRefPtr<EventHub>();
    RefPtr<FocusHub> focusHub = AccessibilityManager::MakeRefPtr<FocusHub>(eventHub, FocusType::DISABLE, false);
    hyperlinkPattern->InitOnKeyEvent(focusHub);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_TAB;
    bool result = hyperlinkPattern->OnKeyEvent(event);
    EXPECT_EQ(result, false);
    event.code = KeyCode::KEY_SPACE;
    result = hyperlinkPattern->OnKeyEvent(event);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: HyperlinkPatternTest004
 * @tc.desc: Test HyperlinkPattern OnTouchEvent when ouchType = TouchType::DOWN
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
    auto hyperlinkLayoutProperty = hyperlinkNode->GetLayoutProperty<HyperlinkLayoutProperty>();
    ASSERT_NE(hyperlinkLayoutProperty, nullptr);
    std::string type = "1";
    TouchEventInfo info(type);
    TouchType touchType = TouchType::DOWN;
    TouchLocationInfo locationInfo(TARGET_ID);
    Offset globalLocation(1, 1);
    locationInfo.SetTouchType(touchType);
    hyperlinkPattern->OnTouchEvent(info);
    hyperlinkLayoutProperty->UpdateTextDecoration(TextDecoration::UNDERLINE);
    EXPECT_EQ(hyperlinkLayoutProperty->GetTextDecoration(), TextDecoration::UNDERLINE);
}

/**
 * @tc.name: HyperlinkPatternTest005
 * @tc.desc: Test HyperlinkPattern OnTouchEvent when ouchType = TouchType::UP
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkPatternTest005, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto hyperlinkNode = FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, stack->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<HyperlinkPattern>(HYPERLINK_ADDRESS); });
    stack->Push(hyperlinkNode);
    auto hyperlinkPattern = hyperlinkNode->GetPattern<HyperlinkPattern>();
    ASSERT_NE(hyperlinkPattern, nullptr);
    auto hyperlinkLayoutProperty = hyperlinkNode->GetLayoutProperty<HyperlinkLayoutProperty>();
    ASSERT_NE(hyperlinkLayoutProperty, nullptr);
    std::string type = "1";
    TouchEventInfo info(type);
    TouchType touchType = TouchType::UP;
    TouchLocationInfo locationInfo(TARGET_ID);
    Offset globalLocation(1, 1);
    locationInfo.SetTouchType(touchType);
    hyperlinkPattern->OnTouchEvent(info);
    hyperlinkLayoutProperty->UpdateTextDecoration(TextDecoration::NONE);
    EXPECT_EQ(hyperlinkLayoutProperty->GetTextDecoration(), TextDecoration::NONE);
}

/**
 * @tc.name: HyperlinkPatternTest006
 * @tc.desc: Test HyperlinkPattern OnHoverEvent.
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkPatternTest006, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto hyperlinkNode = FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, stack->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<HyperlinkPattern>(HYPERLINK_ADDRESS); });
    stack->Push(hyperlinkNode);

    auto hyperlinkPattern = hyperlinkNode->GetPattern<HyperlinkPattern>();
    ASSERT_NE(hyperlinkPattern, nullptr);
    auto hyperlinkLayoutProperty = hyperlinkNode->GetLayoutProperty<HyperlinkLayoutProperty>();
    ASSERT_NE(hyperlinkLayoutProperty, nullptr);
    hyperlinkPattern->OnHoverEvent(true);
    hyperlinkLayoutProperty->UpdateTextDecoration(TextDecoration::UNDERLINE);
    EXPECT_EQ(hyperlinkLayoutProperty->GetTextDecoration(), TextDecoration::UNDERLINE);
}

/**
 * @tc.name: HyperlinkPatternTest007
 * @tc.desc: Test HyperlinkPattern OnHoverEvent when bool isHovered = false.
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkTestNg, HyperlinkPatternTest007, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto hyperlinkNode = FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG, stack->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<HyperlinkPattern>(HYPERLINK_ADDRESS); });
    stack->Push(hyperlinkNode);

    auto hyperlinkPattern = hyperlinkNode->GetPattern<HyperlinkPattern>();
    ASSERT_NE(hyperlinkPattern, nullptr);
    auto hyperlinkLayoutProperty = hyperlinkNode->GetLayoutProperty<HyperlinkLayoutProperty>();
    ASSERT_NE(hyperlinkLayoutProperty, nullptr);
    hyperlinkPattern->OnHoverEvent(false);
    hyperlinkLayoutProperty->UpdateTextDecoration(TextDecoration::NONE);
    EXPECT_EQ(hyperlinkLayoutProperty->GetTextDecoration(), TextDecoration::NONE);
}
} // namespace OHOS::Ace::NG
