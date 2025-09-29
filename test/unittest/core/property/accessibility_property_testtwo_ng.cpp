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

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const OffsetF OFFSETF { 1.0, 1.0 };
} // namespace

class MockPattern : public Pattern {
public:
    MockPattern() = default;
    ~MockPattern() override = default;
};
class AccessibilityPropertyTestTwoNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: AccessibilityPropertyTestTwoNg001
 * @tc.desc: test GetGroupTextRecursive
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestTwoNg, AccessibilityPropertyTest001, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    const std::string textValue = "textValue";
    accessibilityProperty.SetUserTextValue(textValue);
    auto node1 = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<FrameNode> hostBak = AceType::WeakClaim(AceType::RawPtr(node1));
    accessibilityProperty.SetHost(hostBak);
    std::string text = "";
    EXPECT_NE(hostBak.Upgrade(), nullptr);
    hostBak.Upgrade()->SetInternal();
    accessibilityProperty.GetGroupTextRecursive(false, text, false);
    EXPECT_EQ(text, "");

    accessibilityProperty.SetAccessibilityLevel(AccessibilityProperty::Level::NO_HIDE_DESCENDANTS);
    hostBak.Upgrade()->isInternal_ = false;
    accessibilityProperty.GetGroupTextRecursive(false, text, false);
    EXPECT_EQ(text, "");

    text = "";
    accessibilityProperty.SetAccessibilityLevel(AccessibilityProperty::Level::YES_STR);
    accessibilityProperty.GetGroupTextRecursive(false, text, false);

    text = "text";
    accessibilityProperty.propText_ = "";
    accessibilityProperty.accessibilityText_ = "";
    accessibilityProperty.GetGroupTextRecursive(false, text, false);
    EXPECT_EQ(text, "text");

    accessibilityProperty.propText_ = "text";
    accessibilityProperty.accessibilityText_ = "text";
        accessibilityProperty.GetGroupTextRecursive(false, text, false);
    EXPECT_EQ(text, "text, text");

    EXPECT_TRUE(hostBak.Upgrade()->frameChildren_.empty());
    hostBak.Upgrade()->frameChildren_.insert(nullptr);
    accessibilityProperty.GetGroupTextRecursive(false, text, false);
}

/**
 * @tc.name: AccessibilityPropertyTestTwoNg002
 * @tc.desc: CreateNodeSearchInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestTwoNg, AccessibilityPropertyTestTwoNg002, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    AccessibilityHoverTestPath path;
    auto root = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 13, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    root->accessibilityProperty_ = nullptr;
    NG::PointF hoverPoint(0, 0);
    auto debugInfo = std::make_unique<AccessibilityProperty::HoverTestDebugTraceInfo>();
    accessibilityProperty.HoverTest(hoverPoint, root, debugInfo);

    auto subNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    root->AddChild(subNode);
    root->parent_ = nullptr;
    EXPECT_FALSE(subNode->IsRootNode());
    bool ancestorGroupFlag = false;
    auto result = accessibilityProperty.CreateNodeSearchInfo(subNode, hoverPoint, ancestorGroupFlag);
}

/**
 * @tc.name: AccessibilityPropertyTestTwoNg003
 * @tc.desc: ProcessHoverTestRecursive
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestTwoNg, AccessibilityPropertyTestTwoNg003, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    AccessibilityHoverTestPath path;
    auto root = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 13, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    NG::PointF hoverPoint(0, 0);
    auto debugInfo = std::make_unique<AccessibilityProperty::HoverTestDebugTraceInfo>();
    AccessibilityProperty::RecursiveParam recursiveParam;
    recursiveParam.hitTarget = true;
    recursiveParam.ancestorGroupFlag = true;
    auto node1 = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<FrameNode> hostBak = AceType::WeakClaim(AceType::RawPtr(node1));
    accessibilityProperty.SetHost(hostBak);
    EXPECT_NE(hostBak.Upgrade(), nullptr);
    hostBak.Upgrade()->frameChildren_.insert(nullptr);
    hostBak.Upgrade()->frameChildren_.insert(root);
    auto result = accessibilityProperty.ProcessHoverTestRecursive(hoverPoint, root, path, debugInfo, recursiveParam);
    EXPECT_EQ(result, true);

    accessibilityProperty.accessibilityVirtualNode_ = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 13, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    result = accessibilityProperty.ProcessHoverTestRecursive(hoverPoint, root, path, debugInfo, recursiveParam);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: AccessibilityPropertyTestTwoNg004
 * @tc.desc: test IsMatchAccessibilityResponseRegion
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestTwoNg, AccessibilityPropertyTestTwoNg004, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    auto host = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    host->isActive_ = true;
    DimensionRect responseRect(Dimension(-1), Dimension(-1), DimensionOffset(OFFSETF));
    std::vector<DimensionRect> responseRegion;
    responseRegion.push_back(responseRect);
    auto gestureEventHub = host->GetOrCreateEventHub<EventHub>()->GetOrCreateGestureEventHub();
    gestureEventHub->SetResponseRegion(responseRegion);
    auto paintRect = host->renderContext_->GetPaintRectWithoutTransform();
    auto responseRegionList = host->GetResponseRegionList(paintRect, 2);
    EXPECT_FALSE(responseRegionList.size() != 1);

    auto rect = responseRegionList.back();
    EXPECT_FALSE(rect == paintRect);

    EXPECT_FALSE(!accessibilityProperty.IsAccessibilityCompInResponseRegion(rect, paintRect));

    WeakPtr<FrameNode> hostBak = host;
    accessibilityProperty.SetHost(hostBak);
    auto result = accessibilityProperty.IsMatchAccessibilityResponseRegion(true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AccessibilityPropertyTestTwoNg005
 * @tc.desc: test ActActionClick
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestTwoNg, AccessibilityPropertyTestTwoNg005, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    auto host = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(accessibilityProperty.ActActionClick());

    accessibilityProperty.actionClickImpl_ = nullptr;
    EXPECT_FALSE(accessibilityProperty.ActActionClick());

    ActionClickImpl actionsImpl = [](){};
    accessibilityProperty.actionClickImpl_ = actionsImpl;
    EXPECT_TRUE(accessibilityProperty.ActActionClick());
}

/**
 * @tc.name: AccessibilityPropertyTestTwoNg006
 * @tc.desc: test ActActionLongClick
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestTwoNg, AccessibilityPropertyTestTwoNg006, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    auto host = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(accessibilityProperty.ActActionLongClick());

    accessibilityProperty.actionLongClickImpl_ = nullptr;
    EXPECT_FALSE(accessibilityProperty.ActActionLongClick());

    ActionLongClickImpl actionsImpl = [](){};
    accessibilityProperty.actionLongClickImpl_ = actionsImpl;
    EXPECT_TRUE(accessibilityProperty.ActActionLongClick());
}

/**
 * @tc.name: AccessibilityPropertyTestTwoNg007
 * @tc.desc: test ActActionLongClick, IsAccessibilityFocusableTag and GetWindowScenePosition
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestTwoNg, AccessibilityPropertyTestTwoNg007, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    auto node = FrameNode::CreateFrameNode("childNode", 10, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(node->GetRenderContext(), nullptr);
    accessibilityProperty.UpdateHoverTestRect(node);

    node->isAccessibilityVirtualNode_ = true;
    accessibilityProperty.UpdateHoverTestRect(node);

    std::string checkboxEtsTag = "Toggle";
    EXPECT_TRUE(accessibilityProperty.IsAccessibilityFocusableTag(checkboxEtsTag));

    checkboxEtsTag = "test";
    EXPECT_FALSE(accessibilityProperty.IsAccessibilityFocusableTag(checkboxEtsTag));

    NG::WindowSceneInfo windowSceneInfo;
    EXPECT_EQ(accessibilityProperty.getWindowScenePositionImpl_, nullptr);
    accessibilityProperty.GetWindowScenePosition(windowSceneInfo);

    GetWindowScenePositionImpl getWindowScenePositionImpl = [](NG::WindowSceneInfo& windowSceneInfo){};
    accessibilityProperty.getWindowScenePositionImpl_ = getWindowScenePositionImpl;
    EXPECT_NE(accessibilityProperty.getWindowScenePositionImpl_, nullptr);
    accessibilityProperty.GetWindowScenePosition(windowSceneInfo);
}

/**
 * @tc.name: AccessibilityPropertyTestTwoNg008
 * @tc.desc: HoverTestRecursive
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestTwoNg, AccessibilityPropertyTestTwoNg008, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    AccessibilityHoverTestPath path;
    auto root = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    NG::PointF hoverPoint(0, 0);
    auto debugInfo = std::make_unique<AccessibilityProperty::HoverTestDebugTraceInfo>();

    bool ancestorGroupFlag = false;

    root->SetActive(false);
    auto result = accessibilityProperty.HoverTestRecursive(hoverPoint, root, path, debugInfo, ancestorGroupFlag);
    EXPECT_EQ(result, false);
    root->SetActive(true);

    result = accessibilityProperty.HoverTestRecursive(hoverPoint, root, path, debugInfo, ancestorGroupFlag);
    EXPECT_EQ(result, false);

    root->isAccessibilityVirtualNode_ = true;
    debugInfo = nullptr;
    result = accessibilityProperty.HoverTestRecursive(hoverPoint, root, path, debugInfo, ancestorGroupFlag);
    EXPECT_EQ(result, false);

    debugInfo = std::make_unique<AccessibilityProperty::HoverTestDebugTraceInfo>();
    result = accessibilityProperty.HoverTestRecursive(hoverPoint, root, path, debugInfo, ancestorGroupFlag);
    EXPECT_EQ(result, false);
}

} // namespace OHOS::Ace::NG
