/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/column_model.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "frameworks/base/utils/multi_thread.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_TEXT = "test text";
} // namespace

class MockPattern : public Pattern {
public:
    MockPattern() = default;
    ~MockPattern() override = default;
};
class AccessibilityPropertyTestThreeNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = NG::MockPipelineContext::GetCurrent();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    }
    static void TearDownTestSuite()
    {
        NG::MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

/**
 * @tc.name: AccessibilityPropertyTest001
 * @tc.desc: Test the method IsTagInSubTreeComponent.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree001, TestSize.Level1)
{
    std::string tag = V2::XCOMPONENT_ETS_TAG;
    AccessibilityProperty accessibilityProperty;

    bool ret = accessibilityProperty.IsTagInSubTreeComponent(tag);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: AccessibilityPropertyTest002
 * @tc.desc: Test the method IsTagInSubTreeComponent.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree002, TestSize.Level1)
{
    std::string tag = V2::CHECKBOX_ETS_TAG;
    AccessibilityProperty accessibilityProperty;

    bool ret = accessibilityProperty.IsAccessibilityFocusableTag(tag);
    EXPECT_TRUE(ret);

    tag = "test";
    ret = accessibilityProperty.IsAccessibilityFocusableTag(tag);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AccessibilityPropertyTest003
 * @tc.desc: Test the method IsAccessibilityFocusableTag.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree003, TestSize.Level1)
{
    std::string tag = V2::CHECKBOX_ETS_TAG;
    AccessibilityProperty accessibilityProperty;

    bool ret = accessibilityProperty.IsAccessibilityFocusableTag(tag);
    EXPECT_TRUE(ret);

    tag = "test";
    ret = accessibilityProperty.IsAccessibilityFocusableTag(tag);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AccessibilityPropertyTest004
 * @tc.desc: Test the method SetAccessibilityNextFocusInspectorKey && SetAccessibilityTextWithEvent
 *           && SetAccessibilityDescriptionWithEvent.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree004, TestSize.Level1)
{
    std::string accessibilityNextFocusInspectorKey = "test";
    AccessibilityProperty accessibilityProperty;

    accessibilityProperty.SetAccessibilityNextFocusInspectorKey(accessibilityNextFocusInspectorKey);
    EXPECT_EQ(accessibilityNextFocusInspectorKey, accessibilityProperty.accessibilityNextFocusInspectorKey_);

    accessibilityNextFocusInspectorKey = "";
    accessibilityProperty.SetAccessibilityNextFocusInspectorKey(accessibilityNextFocusInspectorKey);
    EXPECT_EQ(accessibilityNextFocusInspectorKey,
        accessibilityProperty.accessibilityNextFocusInspectorKey_.value_or(""));

    std::string text = "test";
    accessibilityProperty.SetAccessibilityTextWithEvent(text);
    EXPECT_EQ(text, accessibilityProperty.accessibilityText_);

    text = "";
    accessibilityProperty.SetAccessibilityTextWithEvent(text);
    EXPECT_EQ(text, accessibilityProperty.accessibilityText_.value_or(""));

    std::string accessibilityDescription = "";
    accessibilityProperty.SetAccessibilityDescriptionWithEvent(accessibilityDescription);
    EXPECT_EQ(accessibilityDescription, accessibilityProperty.accessibilityDescription_.value_or(""));
}

/**
 * @tc.name: AccessibilityPropertyTest005
 * @tc.desc: Test the method ActActionClick.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree005, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;

    uint32_t action = 1;
    accessibilityProperty.accessibilityActions_ = 1;
    accessibilityProperty.actionsImpl_ = [](uint32_t type){};
    bool actionsDefined = accessibilityProperty.ActionsDefined(action);
    EXPECT_TRUE(actionsDefined);
    actionsDefined = accessibilityProperty.ActionsDefined(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_CLICK));
    EXPECT_TRUE(actionsDefined);
    auto result = accessibilityProperty.ActActionClick();
    EXPECT_TRUE(result);

    action = 0;
    accessibilityProperty.accessibilityActions_ = 0;
    accessibilityProperty.actionClickImpl_ = nullptr;
    result = accessibilityProperty.ActActionClick();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: AccessibilityPropertyTest006
 * @tc.desc: Test the method ActActionLongClick.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree006, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;

    uint32_t action = 2;
    accessibilityProperty.accessibilityActions_ = 2;
    accessibilityProperty.actionsImpl_ = [](uint32_t type){};
    bool actionsDefined = accessibilityProperty.ActionsDefined(action);
    EXPECT_TRUE(actionsDefined);
    actionsDefined = accessibilityProperty.ActionsDefined(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_LONG_CLICK));
    EXPECT_TRUE(actionsDefined);
    auto result = accessibilityProperty.ActActionLongClick();
    EXPECT_TRUE(result);

    action = 0;
    accessibilityProperty.accessibilityActions_ = 0;
    accessibilityProperty.actionClickImpl_ = nullptr;
    result = accessibilityProperty.ActActionLongClick();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: AccessibilityPropertyTest007
 * @tc.desc: Test the method ActActionPaste.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree007, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;

    uint32_t action = 16;
    accessibilityProperty.accessibilityActions_ = 16;
    accessibilityProperty.actionsImpl_ = [](uint32_t type){};
    bool actionsDefined = accessibilityProperty.ActionsDefined(action);
    EXPECT_TRUE(actionsDefined);
    actionsDefined = accessibilityProperty.ActionsDefined(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_PASTE));
    EXPECT_TRUE(actionsDefined);
    auto result = accessibilityProperty.ActActionPaste();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AccessibilityPropertyTest008
 * @tc.desc: Test the method ActActionCut.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree008, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;

    uint32_t action = 4;
    accessibilityProperty.accessibilityActions_ = 4;
    accessibilityProperty.actionsImpl_ = [](uint32_t type){};
    bool actionsDefined = accessibilityProperty.ActionsDefined(action);
    EXPECT_TRUE(actionsDefined);
    actionsDefined = accessibilityProperty.ActionsDefined(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_CUT));
    EXPECT_TRUE(actionsDefined);
    auto result = accessibilityProperty.ActActionCut();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AccessibilityPropertyTest009
 * @tc.desc: Test the method ActActionCopy.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree009, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;

    uint32_t action = 8;
    accessibilityProperty.accessibilityActions_ = 8;
    accessibilityProperty.actionsImpl_ = [](uint32_t type){};
    bool actionsDefined = accessibilityProperty.ActionsDefined(action);
    EXPECT_TRUE(actionsDefined);
    actionsDefined = accessibilityProperty.ActionsDefined(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_COPY));
    EXPECT_TRUE(actionsDefined);
    auto result = accessibilityProperty.ActActionCopy();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AccessibilityPropertyTest010
 * @tc.desc: Test the method UpdateHoverTestRect.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree010, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    RectF origRect;
    auto node = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto ret = accessibilityProperty.UpdateHoverTestRect(node);
    EXPECT_EQ(origRect, ret);
}

/**
 * @tc.name: AccessibilityPropertyTest011
 * @tc.desc: Test the method HoverTestRecursive.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree011, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    PointF parentPoint(1, 1);
    auto node = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    AccessibilityHoverTestPath path;
    std::unique_ptr<AccessibilityProperty::HoverTestDebugTraceInfo> debugInfo = nullptr;
    bool ancestorGroupFlag;

    node->SetAccessibilityNodeVirtual();
    EXPECT_TRUE(node->IsAccessibilityVirtualNode());
    debugInfo = std::make_unique<AccessibilityProperty::HoverTestDebugTraceInfo>();

    bool ret = accessibilityProperty.HoverTestRecursive(parentPoint, node, path, debugInfo, ancestorGroupFlag);
    EXPECT_FALSE(ret);

    node->isActive_ = true;
    ret = accessibilityProperty.HoverTestRecursive(parentPoint, node, path, debugInfo, ancestorGroupFlag);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AccessibilityPropertyTestThree012
 * @tc.desc: NotifyComponentChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree012, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    AccessibilityEventType eventType = AccessibilityEventType::CLICK;
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(false);
    accessibilityProperty.NotifyComponentChangeEvent(eventType);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    auto node = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, 0, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    accessibilityProperty.host_ = AceType::WeakClaim(AceType::RawPtr(node));

    accessibilityProperty.NotifyComponentChangeEvent(eventType);
    auto frameNode = accessibilityProperty.host_.Upgrade();
    EXPECT_NE(frameNode, nullptr);
    auto context = NG::MockPipelineContext::GetCurrent();
    frameNode->context_ = AceType::RawPtr(context);
    auto pipeline = frameNode->GetContext();
    EXPECT_NE(pipeline, nullptr);
}

/**
 * @tc.name: AccessibilityPropertyTestThree013
 * @tc.desc: HoverTestRecursive
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree013, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    NG::PointF parentPoint(1, 1);
    auto node = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 13, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    AccessibilityHoverTestPath path;
    auto debugInfo = std::make_unique<AccessibilityProperty::HoverTestDebugTraceInfo>();
    bool ancestorGroupFlag = false;

    node->isAccessibilityVirtualNode_ = true;
    bool result = accessibilityProperty.HoverTestRecursive(parentPoint, node, path, debugInfo, ancestorGroupFlag);
    EXPECT_FALSE(result);

    node->layoutProperty_->UpdateVisibility(VisibleType::INVISIBLE);
    EXPECT_FALSE(node->IsVisible());
    auto renderContext = node->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    result = accessibilityProperty.HoverTestRecursive(parentPoint, node, path, debugInfo, ancestorGroupFlag);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: AccessibilityPropertyTestThree014
 * @tc.desc: HoverTestRecursive
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree014, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    NG::PointF parentPoint(150, 160);
    auto node = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 13, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    AccessibilityHoverTestPath path;
    auto debugInfo = std::make_unique<AccessibilityProperty::HoverTestDebugTraceInfo>();
    bool ancestorGroupFlag = false;
    node->isAccessibilityVirtualNode_ = true;
    
    auto eventHub = node->GetOrCreateEventHub<EventHub>();
    eventHub->enabled_ = false;

    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    node->renderContext_ = mockRenderContext;
    RectF rect1(100, 100, 100, 100);
    mockRenderContext->SetPaintRectWithTransform(rect1);

    PointF selfPoint = parentPoint;
    mockRenderContext->GetPointWithRevert(selfPoint);
    
    auto property = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    property->accessibilityLevel_ = AccessibilityProperty::Level::YES_STR;
    property->accessibilityHoverPriority_ = true;

    auto result = accessibilityProperty.HoverTestRecursive(parentPoint, node, path, debugInfo, ancestorGroupFlag);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AccessibilityPropertyTestThree015
 * @tc.desc: ProcessHoverTestRecursive
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree015, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    AccessibilityHoverTestPath path;
    auto node = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 13, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    NG::PointF hoverPoint(1, 1);
    auto debugInfo = std::make_unique<AccessibilityProperty::HoverTestDebugTraceInfo>();
    AccessibilityProperty::RecursiveParam recursiveParam;
    recursiveParam.hitTarget = true;
    recursiveParam.ancestorGroupFlag = true;

    auto property = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    property->accessibilityVirtualNode_ = node;
    auto virtualNode = property->GetAccessibilityVirtualNode();
    EXPECT_NE(virtualNode, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(virtualNode);
    EXPECT_NE(frameNode, nullptr);

    bool ret = AccessibilityProperty::HoverTestRecursive(hoverPoint, frameNode, path, debugInfo,
            recursiveParam.ancestorGroupFlag);
    EXPECT_FALSE(ret);
    
    auto result = accessibilityProperty.ProcessHoverTestRecursive(hoverPoint, node, path, debugInfo, recursiveParam);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: AccessibilityPropertyTestThree016
 * @tc.desc: SpecificSupportActionCallback
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree016, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    
    accessibilityProperty.SetSpecificSupportActionCallback([&]() {
        accessibilityProperty.AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
    });
    auto supportAceActions = accessibilityProperty.GetSupportAction();
    auto ret = std::any_of(supportAceActions.begin(),
        supportAceActions.end(),
        [](const AceAction& action) { return action == AceAction::ACTION_SCROLL_BACKWARD; });
    EXPECT_EQ(ret, false);

    accessibilityProperty.ResetSupportAction();

    supportAceActions = accessibilityProperty.GetSupportAction();
    ret = std::any_of(supportAceActions.begin(),
        supportAceActions.end(),
        [](const AceAction& action) { return action == AceAction::ACTION_SCROLL_BACKWARD; });
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: AccessibilityPropertyTest017
 * @tc.desc: Test the method SetAccessibilityGroup.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree017, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    EXPECT_FALSE(accessibilityProperty.accessibilityGroup_);
    WeakPtr<FrameNode> hostBak = accessibilityProperty.host_;
    bool accessibilityGroup = true;
    accessibilityProperty.SetAccessibilityGroup(accessibilityGroup);
    EXPECT_TRUE(accessibilityProperty.accessibilityGroup_);
}

/**
 * @tc.name: AccessibilityPropertyTest018
 * @tc.desc: Test the method SetAccessibilityTextWithEvent.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree018, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    EXPECT_FALSE(accessibilityProperty.accessibilityText_.has_value());
    WeakPtr<FrameNode> hostBak = accessibilityProperty.host_;
    accessibilityProperty.SetAccessibilityTextWithEvent(TEST_TEXT);
    EXPECT_EQ(accessibilityProperty.accessibilityText_.value_or(""), TEST_TEXT);
}

/**
 * @tc.name: AccessibilityPropertyTest019
 * @tc.desc: Test the method SetAccessibilityDescriptionWithEvent.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree019, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    EXPECT_FALSE(accessibilityProperty.accessibilityDescription_.has_value());
    WeakPtr<FrameNode> hostBak = accessibilityProperty.host_;
    accessibilityProperty.SetAccessibilityDescriptionWithEvent(TEST_TEXT);
    EXPECT_EQ(accessibilityProperty.accessibilityDescription_.value_or(""), TEST_TEXT);
}

/**
 * @tc.name: AccessibilityPropertyTest020
 * @tc.desc: Test the method SetAccessibilityLevel.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree020, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    EXPECT_FALSE(accessibilityProperty.accessibilityLevel_.has_value());
    WeakPtr<FrameNode> hostBak = accessibilityProperty.host_;
    std::string accessibilityLevel = "auto";
    accessibilityProperty.SetAccessibilityLevel(accessibilityLevel);
    EXPECT_EQ(accessibilityProperty.accessibilityLevel_.value_or(""), accessibilityLevel);
}
} // namespace OHOS::Ace::NG
