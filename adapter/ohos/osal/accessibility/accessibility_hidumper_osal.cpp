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

#include "accessibility_element_info.h"
#include "accessibility_system_ability_client.h"

#include "adapter/ohos/osal/accessibility/accessibility_hidumper_osal.h"
#include "adapter/ohos/osal/js_accessibility_manager.h"
#include "base/json/json_util.h"
#include "base/log/dump_log.h"
#include "core/accessibility/accessibility_utils.h"
#include "core/accessibility/hidumper/accessibility_hidumper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/manager/safe_area/safe_area_manager.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_manager.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/components_ng/render/render_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/accessibility/node_utils/accessibility_frame_node_utils.h"

using namespace OHOS::Accessibility;
using namespace OHOS::AccessibilityConfig;

namespace OHOS::Ace::Framework {

namespace {
inline std::string BoolToString(bool tag)
{
    return tag ? "true" : "false";
}

inline std::string ChildrenToString(const std::vector<int64_t>& children, int32_t treeId)
{
    std::string ids;
    for (auto& child : children) {
        if (!ids.empty()) {
            ids.append(",");
        }
        int64_t childId = child;
        AccessibilitySystemAbilityClient::SetSplicElementIdTreeId(treeId, childId);
        ids.append(std::to_string(childId));
    }
    return ids;
}

inline void DumpRectNG(const Accessibility::Rect& rect)
{
    DumpLog::GetInstance().AddDesc(
        "width: ", std::to_string(rect.GetRightBottomXScreenPostion() - rect.GetLeftTopXScreenPostion()));
    DumpLog::GetInstance().AddDesc(
        "height: ", std::to_string(rect.GetRightBottomYScreenPostion() - rect.GetLeftTopYScreenPostion()));
    DumpLog::GetInstance().AddDesc("left: ", std::to_string(rect.GetLeftTopXScreenPostion()));
    DumpLog::GetInstance().AddDesc("top: ", std::to_string(rect.GetLeftTopYScreenPostion()));
    DumpLog::GetInstance().AddDesc("right: ", std::to_string(rect.GetRightBottomXScreenPostion()));
    DumpLog::GetInstance().AddDesc("bottom: ", std::to_string(rect.GetRightBottomYScreenPostion()));
}

std::string ConvertAccessibilityRoleTypeToString(AccessibilityRoleType roleType)
{
    if (roleType == AccessibilityRoleType::ROLE_NONE) {
        return "";
    }
    return AccessibilityUtils::GetRoleByType(roleType);
}

} // namespace

void AccessibilityElementInfoUtils::ToCommonInfo(
    const Accessibility::AccessibilityElementInfo& nodeInfo,
    int32_t treeId)
{
    int64_t elementId = nodeInfo.GetAccessibilityId();
    AccessibilitySystemAbilityClient::SetSplicElementIdTreeId(treeId, elementId);
    DumpLog::GetInstance().AddDesc("ID: ", elementId);
    DumpLog::GetInstance().AddDesc("UniqueID: ", nodeInfo.GetUniqueId());
    int64_t parentId = nodeInfo.GetParentNodeId();
    AccessibilitySystemAbilityClient::SetSplicElementIdTreeId(treeId, parentId);
    DumpLog::GetInstance().AddDesc("parent ID: ", parentId);
    DumpLog::GetInstance().AddDesc("child IDs: ", ChildrenToString(nodeInfo.GetChildIds(), treeId));
    DumpLog::GetInstance().AddDesc("component type: ", nodeInfo.GetComponentType());
    DumpLog::GetInstance().AddDesc("accessibilityCustomRole: " + nodeInfo.GetCustomComponentType());
    DumpLog::GetInstance().AddDesc("text: ", nodeInfo.GetContent());
    DumpLog::GetInstance().AddDesc("originText: ", nodeInfo.GetOriginalText());
    DumpLog::GetInstance().AddDesc("window id: " + std::to_string(nodeInfo.GetWindowId()));
    DumpRectNG(nodeInfo.GetRectInScreen());

    DumpLog::GetInstance().AddDesc("enabled: ", BoolToString(nodeInfo.IsEnabled()));
    DumpLog::GetInstance().AddDesc("focusable: ", BoolToString(nodeInfo.IsFocusable()));
    DumpLog::GetInstance().AddDesc("focused: ", BoolToString(nodeInfo.IsFocused()));
    DumpLog::GetInstance().AddDesc("visible: ", BoolToString(nodeInfo.IsVisible()));
    DumpLog::GetInstance().AddDesc("accessibility focused: ", BoolToString(nodeInfo.HasAccessibilityFocus()));
    DumpLog::GetInstance().AddDesc("accessibilityText: " + nodeInfo.GetAccessibilityText());
    DumpLog::GetInstance().AddDesc("accessibilityGroup: " + BoolToString(nodeInfo.GetAccessibilityGroup()));
    DumpLog::GetInstance().AddDesc("accessibilityLevel: " + nodeInfo.GetAccessibilityLevel());
    DumpLog::GetInstance().AddDesc("accessibilityDescription: " + nodeInfo.GetDescriptionInfo());
    DumpLog::GetInstance().AddDesc("hitTestBehavior: " + nodeInfo.GetHitTestBehavior());

    DumpLog::GetInstance().AddDesc("inspector key: ", nodeInfo.GetInspectorKey());
    DumpLog::GetInstance().AddDesc("bundle name: ", nodeInfo.GetBundleName());
    DumpLog::GetInstance().AddDesc("page id: " + std::to_string(nodeInfo.GetPageId()));
    DumpLog::GetInstance().AddDesc("page path: ", nodeInfo.GetPagePath());
    DumpLog::GetInstance().AddDesc("is valid element: ", BoolToString(nodeInfo.IsValidElement()));
    DumpLog::GetInstance().AddDesc("resource name: ", nodeInfo.GetComponentResourceId());

    DumpLog::GetInstance().AddDesc("clickable: ", BoolToString(nodeInfo.IsClickable()));
    DumpLog::GetInstance().AddDesc("long clickable: ", BoolToString(nodeInfo.IsLongClickable()));
    DumpLog::GetInstance().AddDesc("popup supported: ", BoolToString(nodeInfo.IsPopupSupported()));
    DumpLog::GetInstance().AddDesc("zindex: ", std::to_string(nodeInfo.GetZIndex()));
}

namespace {

class MockDumpExecuteActionCallBack : public Accessibility::AccessibilityElementOperatorCallback {
public:
    ~MockDumpExecuteActionCallBack() = default;

    void SetSearchElementInfoByAccessibilityIdResult(const std::list<Accessibility::AccessibilityElementInfo>& infos,
        const int32_t requestId) override {}

    void SetSearchElementInfoByTextResult(const std::list<Accessibility::AccessibilityElementInfo>& infos,
        const int32_t requestId) override {}

    void SetSearchDefaultFocusByWindowIdResult(const std::list<Accessibility::AccessibilityElementInfo>& infos,
        const int32_t requestId) override {}

    void SetFindFocusedElementInfoResult(const Accessibility::AccessibilityElementInfo& info,
        const int32_t requestId) override {}

    void SetFocusMoveSearchResult(const Accessibility::AccessibilityElementInfo& info,
        const int32_t requestId) override {}

    void SetExecuteActionResult(const bool succeeded, const int32_t requestId) override
    {
        if (succeeded) {
            DumpLog::GetInstance().Print("Result: execute action succeeded");
        } else {
            DumpLog::GetInstance().Print("Result: execute action failed");
        }
    }

    void SetCursorPositionResult(const int32_t cursorPosition, const int32_t requestId) override {}

    void SetSearchElementInfoBySpecificPropertyResult(const std::list<Accessibility::AccessibilityElementInfo>& infos,
        const std::list<Accessibility::AccessibilityElementInfo>& treeInfos, const int32_t requestId) override {}

    void SetFocusMoveSearchWithConditionResult(const std::list<Accessibility::AccessibilityElementInfo>& info,
        const Accessibility::FocusMoveResult& result, const int32_t requestId) override {}

    void SetUpdateCustomAccessibilityPropertyResult(
        const OperateVirtualNodeResult result, const int32_t requestId) override {}

    void SetAddAccessibilityVirtualNodeResult(
        const OperateVirtualNodeResult result, const int32_t requestId) override {}

    void SetRemoveAccessibilityVirtualNodeResult(
        const OperateVirtualNodeResult result, const int32_t requestId) override {}
};

} // namespace

void JsAccessibilityManager::DumpExecuteActionTest(const std::vector<std::string>& params)
{
    ExecuteActionArgument actionArg;
    if (!AccessibilityHidumper::DumpProcessExecuteActionParameters(params, actionArg)) {
        return;
    }

    auto pipeline = context_.Upgrade();
    CHECK_NULL_VOID(pipeline);

    ActionParam param;
    param.action = static_cast<Accessibility::ActionType>(actionArg.actionType);
    param.actionArguments = actionArg.actionArguments;
    MockDumpExecuteActionCallBack callback;
    ExecuteAction(actionArg.elementId, param, 0, callback, windowId_);
}

void AccessibilityManagerHidumper::DumpCustomActionTest(
    const std::vector<std::string>& params,
    const RefPtr<OHOS::Ace::NG::FrameNode>& frameNode)
{
    int64_t nodeId = 0;
    std::string actionName;
    bool listActions = false;

    if (!AccessibilityHidumper::DumpProcessCustomActionParameters(params, nodeId, actionName, listActions)) {
        return;
    }

    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);

    auto customActions = accessibilityProperty->GetAccessibilityCustomActions();
    if (customActions.empty()) {
        DumpLog::GetInstance().Print(std::string("Result: no custom actions found"));
        return;
    }

    DumpLog::GetInstance().Print(std::string("Custom Actions Count: ") + std::to_string(customActions.size()));

    for (size_t i = 0; i < customActions.size(); ++i) {
        auto& customAction = customActions[i];
        DumpLog::GetInstance().AddDesc(std::string("Index: ") + std::to_string(i));
        DumpLog::GetInstance().AddDesc(std::string("Action Name: ") + customAction.actionName);
        DumpLog::GetInstance().AddDesc(std::string("Callback Valid: ") +
            (customAction.customActionCallback ? "true" : "false"));
        DumpLog::GetInstance().Print(0, "Custom Action", 0);
    }

    if (listActions) {
        DumpLog::GetInstance().Print(std::string("Result: custom action list displayed"));
        return;
    }

    if (actionName.empty()) {
        DumpLog::GetInstance().Print(std::string("Error: action name is empty"));
        DumpLog::GetInstance().Print(
            std::string("Usage: --custom-action-test <nodeId> [--list] [--execute <actionName>]"));
        return;
    }

    bool found = false;
    for (auto& customAction : customActions) {
        if (customAction.actionName == actionName) {
            found = true;
            if (customAction.customActionCallback) {
                DumpLog::GetInstance().Print(std::string("Executing custom action: ") + customAction.actionName);
                customAction.customActionCallback();
                DumpLog::GetInstance().Print(std::string("Result: custom action executed successfully"));
            } else {
                DumpLog::GetInstance().Print(std::string("Error: custom action callback is null"));
            }
            break;
        }
    }

    if (!found) {
        DumpLog::GetInstance().Print(std::string("Error: custom action not found with name: ") + actionName);
    }
    DumpLog::GetInstance().Print(std::string("Result: custom action test done"));
}

void DumpAccessibilityElementInfosTreeNG(
    std::list<AccessibilityElementInfo>& infos, int32_t depth, int64_t accessibilityId, bool isRoot)
{
    AccessibilityElementInfo accessibilityInfo;
    for (auto& info : infos) {
        if (accessibilityId == info.GetAccessibilityId()) {
            accessibilityInfo = info;
            break;
        }
    }
    if (!isRoot) {
        DumpLog::GetInstance().AddDesc("ID: " + std::to_string(accessibilityInfo.GetAccessibilityId()));
        DumpLog::GetInstance().AddDesc("compid: " + accessibilityInfo.GetInspectorKey());
        DumpLog::GetInstance().AddDesc("text: " + accessibilityInfo.GetContent());
        DumpLog::GetInstance().AddDesc("accessibilityText: " + accessibilityInfo.GetContent());
        DumpLog::GetInstance().AddDesc("accessibilityCustomRole: " + accessibilityInfo.GetCustomComponentType());
        DumpLog::GetInstance().AddDesc("accessibilityGroup: ");
        DumpLog::GetInstance().AddDesc("accessibilityLevel: ");
        DumpLog::GetInstance().AddDesc("top: " +
            std::to_string(accessibilityInfo.GetRectInScreen().GetLeftTopYScreenPostion()));
        DumpLog::GetInstance().AddDesc("left: " +
            std::to_string(accessibilityInfo.GetRectInScreen().GetLeftTopXScreenPostion()));
        DumpLog::GetInstance().AddDesc("width: " + std::to_string(
            accessibilityInfo.GetRectInScreen().GetRightBottomXScreenPostion() -
            accessibilityInfo.GetRectInScreen().GetLeftTopXScreenPostion()));
        DumpLog::GetInstance().AddDesc("height: " + std::to_string(
            accessibilityInfo.GetRectInScreen().GetRightBottomYScreenPostion() -
            accessibilityInfo.GetRectInScreen().GetLeftTopYScreenPostion()));
        DumpLog::GetInstance().AddDesc("visible: " + std::to_string(accessibilityInfo.IsVisible()));
        DumpLog::GetInstance().AddDesc(
            "clickable: " + std::to_string(accessibilityInfo.IsClickable()));
        DumpLog::GetInstance().AddDesc("longclickable: " +
            std::to_string(accessibilityInfo.IsLongClickable()));
        DumpLog::GetInstance().AddDesc("checkable: " + std::to_string(accessibilityInfo.IsCheckable()));
        DumpLog::GetInstance().AddDesc("scrollable: " + std::to_string(accessibilityInfo.IsScrollable()));
        DumpLog::GetInstance().AddDesc("checked: " + std::to_string(accessibilityInfo.IsChecked()));
        DumpLog::GetInstance().AddDesc("hint: " + accessibilityInfo.GetHint());
        DumpLog::GetInstance().Print(depth, accessibilityInfo.GetComponentType(), accessibilityInfo.GetChildCount());
        depth ++;
    }
    for (auto child : accessibilityInfo.GetChildIds()) {
        DumpAccessibilityElementInfosTreeNG(infos, depth, child, false);
    }
}

namespace {

void DumpAccessibilityGroupOptionsNG(const RefPtr<NG::AccessibilityProperty>& accessibilityProperty)
{
    if (!accessibilityProperty || !accessibilityProperty->IsAccessibilityGroup()) {
        return;
    }
    DumpLog::GetInstance().AddDesc("    accessibilityOptions: ");
    auto accessibilityOptions = accessibilityProperty->GetAccessibilityGroupOptions();
    DumpLog::GetInstance().AddDesc("        accessibilityTextPreferred: " +
        std::to_string(accessibilityOptions.accessibilityTextPreferred));
    DumpLog::GetInstance().AddDesc("        stateControllerByType: " +
        ConvertAccessibilityRoleTypeToString(accessibilityOptions.stateControllerByType));
    DumpLog::GetInstance().AddDesc("        stateControllerByInspector: " +
        accessibilityOptions.stateControllerByInspector);
    DumpLog::GetInstance().AddDesc("        actionControllerByType: " +
        ConvertAccessibilityRoleTypeToString(accessibilityOptions.actionControllerByType));
    DumpLog::GetInstance().AddDesc("        actionControllerByInspector: " +
        accessibilityOptions.actionControllerByInspector);
}

} // namespace

static void DumpTreeNodeInfoNG(
    const RefPtr<NG::FrameNode>& node, int32_t depth, const CommonProperty& commonProperty, int32_t childSize)
{
    CHECK_NULL_VOID(node);
    NG::RectF rect = node->GetTransformRectRelativeToWindow(true);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    DumpLog::GetInstance().AddDesc("ID: " + std::to_string(node->GetAccessibilityId()));
    DumpLog::GetInstance().AddDesc("compid: " + node->GetInspectorId().value_or(""));
    if (accessibilityProperty) {
        DumpLog::GetInstance().AddDesc("text: " + accessibilityProperty->GetGroupText());
        DumpLog::GetInstance().AddDesc("accessibilityText: " + accessibilityProperty->GetAccessibilityText());
        DumpLog::GetInstance().AddDesc("accessibilityGroup: "
            + std::to_string(accessibilityProperty->IsAccessibilityGroup()));
        DumpAccessibilityGroupOptionsNG(accessibilityProperty);
        DumpLog::GetInstance().AddDesc("accessibilityLevel: " + accessibilityProperty->GetAccessibilityLevel());
        DumpLog::GetInstance().AddDesc(
            "accessibilityCustomRole: " + accessibilityProperty->GetAccessibilityCustomRole());
    }
    DumpLog::GetInstance().AddDesc("top: " + std::to_string(rect.Top() + commonProperty.windowTop));
    DumpLog::GetInstance().AddDesc("left: " + std::to_string(rect.Left() + commonProperty.windowLeft));
    DumpLog::GetInstance().AddDesc("width: " + std::to_string(rect.Width()));
    DumpLog::GetInstance().AddDesc("height: " + std::to_string(rect.Height()));
    DumpLog::GetInstance().AddDesc("visible: " + std::to_string(node->IsVisible()));
    DumpLog::GetInstance().AddDesc("debugLine: " + node->GetDebugLine());
    auto eventHub = node->GetEventHub<NG::EventHub>();
    if (eventHub) {
        auto gestureEventHub = eventHub->GetGestureEventHub();
        DumpLog::GetInstance().AddDesc(
            "clickable: " + std::to_string(gestureEventHub ? gestureEventHub->IsAccessibilityClickable() : false));
        DumpLog::GetInstance().AddDesc("longclickable: " +
            std::to_string(gestureEventHub ? gestureEventHub->IsAccessibilityLongClickable() : false));
    }
    if (accessibilityProperty) {
        DumpLog::GetInstance().AddDesc("checkable: " + std::to_string(accessibilityProperty->IsCheckable()));
        DumpLog::GetInstance().AddDesc("scrollable: " + std::to_string(accessibilityProperty->IsScrollable()));
        DumpLog::GetInstance().AddDesc("checked: " + std::to_string(accessibilityProperty->IsChecked()));
        DumpLog::GetInstance().AddDesc("hint: " + accessibilityProperty->GetHintText());
        DumpLog::GetInstance().AddDesc("childTree: " + std::to_string(accessibilityProperty->GetChildTreeId()));
        DumpLog::GetInstance().AddDesc(
            "accessibilitySelected: " + std::to_string(accessibilityProperty->IsUserSelected()));
        DumpLog::GetInstance().AddDesc("accessibilityRole: " + accessibilityProperty->GetAccessibilityRole());
    }
    DumpLog::GetInstance().Print(depth, node->GetTag(), childSize);
}

void JsAccessibilityManager::DumpTreeNodeSafeAreaInfoNg(const RefPtr<NG::FrameNode>& node)
{
    auto layoutProperty = node->GetLayoutProperty();
    if (layoutProperty) {
        auto&& opts = layoutProperty->GetSafeAreaExpandOpts();
        if (opts && opts->type != NG::SAFE_AREA_TYPE_NONE && opts->edges != NG::SAFE_AREA_EDGE_NONE) {
            DumpLog::GetInstance().AddDesc(opts->ToString());
        }
        if (layoutProperty->GetSafeAreaInsets()) {
            DumpLog::GetInstance().AddDesc(layoutProperty->GetSafeAreaInsets()->ToString());
        }
    }
    if (node->SelfOrParentExpansive()) {
        auto geometryNode = node->GetGeometryNode();
        if (geometryNode) {
            auto rect = geometryNode->GetSelfAdjust();
            auto parentRect = geometryNode->GetParentAdjust();
            bool isDefaultSize = NearZero(rect.GetX(), 0.0) && NearZero(rect.GetY(), 0.0) &&
                                 NearZero(rect.Width(), 0.0) && NearZero(rect.Height(), 0.0);
            bool isParentDefaultSize = NearZero(parentRect.GetX(), 0.0) && NearZero(parentRect.GetY(), 0.0) &&
                                       NearZero(parentRect.Width(), 0.0) && NearZero(parentRect.Height(), 0.0);
            if (!isDefaultSize && !isParentDefaultSize) {
                DumpLog::GetInstance().AddDesc(std::string("selfAdjust: ")
                                                   .append(rect.ToString().c_str())
                                                   .append(",parentAdjust")
                                                   .append(parentRect.ToString().c_str()));
            }
        }
    }
    CHECK_NULL_VOID(node->GetTag() == V2::PAGE_ETS_TAG);
    auto pipeline = node->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(manager);
    if (!manager->IsIgnoreSafeArea() && !manager->IsNeedAvoidWindow() && !manager->IsFullScreen() &&
        !manager->KeyboardSafeAreaEnabled() && !manager->GetUseCutout()) {
        DumpLog::GetInstance().AddDesc(
            std::string("ignoreSafeArea: ")
                .append(std::to_string(manager->IsIgnoreSafeArea()))
                .append(std::string(", isNeedAvoidWindow: ").c_str())
                .append(std::to_string(manager->IsNeedAvoidWindow()))
                .append(std::string(", IisFullScreen: ").c_str())
                .append(std::to_string(manager->IsFullScreen()))
                .append(std::string(", isKeyboardAvoidMode: ").c_str())
                .append(std::to_string(static_cast<int32_t>(manager->GetKeyBoardAvoidMode())))
                .append(std::string(", isUseCutout: ").c_str())
                .append(std::to_string(manager->GetUseCutout())));
    }
}

void JsAccessibilityManager::DumpPadding(const std::unique_ptr<NG::PaddingProperty>& padding, std::string label)
{
    NG::CalcLength defaultValue = NG::CalcLength(Dimension(0));
    auto left = padding->left.value_or(defaultValue).GetDimension().Value();
    auto right = padding->right.value_or(defaultValue).GetDimension().Value();
    auto top = padding->top.value_or(defaultValue).GetDimension().Value();
    auto bottom = padding->bottom.value_or(defaultValue).GetDimension().Value();
    if (!NearZero(left, 0.0) && !NearZero(right, 0.0) && !NearZero(top, 0.0) && !NearZero(bottom, 0.0)) {
        DumpLog::GetInstance().AddDesc(label.append(padding->ToString().c_str()));
    }
}

void JsAccessibilityManager::DumpBorder(const std::unique_ptr<NG::BorderWidthProperty>& border, std::string label)
{
    Dimension defaultValue(0);
    auto left = border->leftDimen.value_or(defaultValue).Value();
    auto right = border->rightDimen.value_or(defaultValue).Value();
    auto top = border->topDimen.value_or(defaultValue).Value();
    auto bottom = border->bottomDimen.value_or(defaultValue).Value();
    if (!NearZero(left, 0.0) && !NearZero(right, 0.0) && !NearZero(top, 0.0) && !NearZero(bottom, 0.0)) {
        DumpLog::GetInstance().AddDesc(label.append(border->ToString().c_str()));
    }
}

void JsAccessibilityManager::DumpTreeNodeCommonInfoNg(
    const RefPtr<NG::FrameNode>& node, const CommonProperty& commonProperty)
{
    DumpLog::GetInstance().AddDesc("ID: " + std::to_string(node->GetAccessibilityId()));
    auto renderContext = node->GetRenderContext();
    if (renderContext) {
        auto backgroundColor = renderContext->GetBackgroundColor();
        if (backgroundColor && backgroundColor->ColorToString().compare("#00000000") != 0) {
            DumpLog::GetInstance().AddDesc("BackgroundColor: " + backgroundColor->ColorToString());
        }
        DumpLog::GetInstance().AddDesc(std::string("PaintRectWithoutTransform: ")
                                           .append(renderContext->GetPaintRectWithoutTransform().ToString()));
    }
    NG::RectF rect = node->GetTransformRectRelativeToWindow(true);
    auto top = rect.Top() + commonProperty.windowTop;
    auto left = rect.Left() + commonProperty.windowLeft;
    if (!NearZero(top, 0.0) && !NearZero(left, 0.0)) {
        DumpLog::GetInstance().AddDesc("top: " + std::to_string(top));
        DumpLog::GetInstance().AddDesc("left: " + std::to_string(left));
    }
    DumpLog::GetInstance().AddDesc("width: " + std::to_string(rect.Width()));
    DumpLog::GetInstance().AddDesc("height: " + std::to_string(rect.Height()));
    auto layoutProperty = node->GetLayoutProperty();
    if (layoutProperty) {
        if (!node->IsVisible() && layoutProperty->GetVisibility().has_value()) {
            DumpLog::GetInstance().AddDesc(
                "visible: " + std::to_string(static_cast<int32_t>(layoutProperty->GetVisibility().value())));
        }
        auto& padding = layoutProperty->GetPaddingProperty();
        if (padding) {
            DumpPadding(padding, std::string("Padding: "));
        }
        auto& margin = layoutProperty->GetMarginProperty();
        if (margin) {
            DumpPadding(margin, std::string("Margin: "));
        }
        auto& border = layoutProperty->GetBorderWidthProperty();
        if (border) {
            DumpBorder(border, std::string("Border: "));
        }
        auto layoutRect = layoutProperty->GetLayoutRect();
        if (layoutRect) {
            DumpLog::GetInstance().AddDesc(std::string("LayoutRect: ").append(layoutRect.value().ToString().c_str()));
        }
    }
}

void JsAccessibilityManager::DumpTreeNodeSimplifyInfoNG(
    const RefPtr<NG::FrameNode>& node, int32_t depth, const CommonProperty& commonProperty, int32_t childSize)
{
    DumpTreeNodeCommonInfoNg(node, commonProperty);
    DumpTreeNodeSafeAreaInfoNg(node);
    DumpLog::GetInstance().Print(depth, node->GetTag(), childSize);
}

void JsAccessibilityManager::DumpTreeAccessibilityNodeNG(const RefPtr<NG::UINode>& uiNodeParent, int32_t depth,
    int64_t nodeID, const CommonProperty& commonProperty)
{
    CHECK_NULL_VOID(uiNodeParent);
    auto virtualFrameNode = AceType::DynamicCast<NG::FrameNode>(uiNodeParent);
    auto uiNodeChildren = uiNodeParent->GetChildren(true);
    auto vNode = NG::AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(virtualFrameNode, nodeID);
    if (!vNode) {
        if (uiNodeChildren.size() == 0) {
            return;
        }
    }
    std::vector<std::pair<int64_t, int32_t>> childrenIdInfo;
    for (const auto& item : uiNodeChildren) {
        GetFrameNodeChildren(item, childrenIdInfo, commonProperty);
    }
    if (vNode != nullptr) {
        DumpTreeNodeInfoNG(vNode, depth + 1, commonProperty, childrenIdInfo.size());
    }
    for (const auto& item : uiNodeChildren) {
        DumpTreeAccessibilityNodeNG(item, depth + 1, item->GetAccessibilityId(), commonProperty);
    }
}

void JsAccessibilityManager::DumpTreeNG(const RefPtr<NG::FrameNode>& parent, int32_t depth,
    int64_t nodeID, const CommonProperty& commonProperty, bool isDumpSimplify)
{
    auto node = NG::AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(parent, nodeID);
    if (!node) {
        DumpLog::GetInstance().Print("Error: failed to get accessibility node with ID " + std::to_string(nodeID));
        return;
    }
    if (!node->IsActive()) {
        return;
    }
    std::vector<std::pair<int64_t, int32_t>> childrenIdInfo;
    for (const auto& item : node->GetChildren(true)) {
        GetFrameNodeChildren(item, childrenIdInfo, commonProperty);
    }

    auto overlayNode = node->GetOverlayNode();
    if (overlayNode) {
        GetFrameNodeChildren(overlayNode, childrenIdInfo, commonProperty);
    }

    if (isDumpSimplify) {
        DumpTreeNodeSimplifyInfoNG(node, depth, commonProperty, childrenIdInfo.size());
    } else if (!isUseJson_) {
        DumpTreeNodeInfoNG(node, depth, commonProperty, childrenIdInfo.size());
    } else {
        DumpTreeNodeInfoInJson(node, depth, commonProperty, childrenIdInfo.size());
    }
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    auto uiVirtualNode = accessibilityProperty->GetAccessibilityVirtualNode();
    bool hasVirtualNode = false;
    if (uiVirtualNode != nullptr) {
        auto virtualNode = AceType::DynamicCast<NG::FrameNode>(uiVirtualNode);
        CHECK_NULL_VOID(virtualNode);
        hasVirtualNode = true;
        DumpTreeAccessibilityNodeNG(uiVirtualNode, depth+1, virtualNode->GetAccessibilityId(), commonProperty);
    }
    if (IsExtensionComponent(node) && !IsUIExtensionShowPlaceholder(node)) {
        std::list<AccessibilityElementInfo> extensionElementInfos;
        auto pipeline = context_.Upgrade();
        CHECK_NULL_VOID(pipeline);
        SearchElementInfoByAccessibilityIdNG(
            node->GetAccessibilityId(), PREFETCH_RECURSIVE_CHILDREN, extensionElementInfos,
            pipeline, NG::UI_EXTENSION_OFFSET_MAX);
        if (!extensionElementInfos.empty()) {
            DumpAccessibilityElementInfosTreeNG(extensionElementInfos, depth + 1, node->GetAccessibilityId(), true);
        }
    }
    if (!hasVirtualNode) {
        for (const auto& childIdPair : childrenIdInfo) {
            DumpTreeNG(node, depth + 1, childIdPair.first, commonProperty, isDumpSimplify);
        }
    }
}

void JsAccessibilityManager::DumpTree(int32_t depth, int64_t nodeID, bool isDumpSimplify)
{
    auto pipeline = context_.Upgrade();
    CHECK_NULL_VOID(pipeline);
    if (!AceType::InstanceOf<NG::PipelineContext>(pipeline)) {
        AccessibilityNodeManager::DumpTree(depth, nodeID, isDumpSimplify);
    } else {
        auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipeline);
        auto rootNode = ngPipeline->GetRootElement();
        CHECK_NULL_VOID(rootNode);
        nodeID = rootNode->GetAccessibilityId();
        CommonProperty commonProperty;
        GenerateCommonProperty(ngPipeline, commonProperty, pipeline, rootNode);
        DumpTreeNG(rootNode, depth, nodeID, commonProperty, isDumpSimplify);
        for (const auto& subContext : GetSubPipelineContexts()) {
            auto subPipeline = subContext.Upgrade();
            ngPipeline = AceType::DynamicCast<NG::PipelineContext>(subPipeline);
            CHECK_NULL_CONTINUE(ngPipeline);
            rootNode = ngPipeline->GetRootElement();
            CHECK_NULL_CONTINUE(rootNode);
            nodeID = rootNode->GetAccessibilityId();
            commonProperty.windowId = static_cast<int32_t>(ngPipeline->GetWindowId());
            commonProperty.windowLeft = GetWindowLeft(ngPipeline->GetWindowId());
            commonProperty.windowTop = GetWindowTop(ngPipeline->GetWindowId());
            commonProperty.pageNodes.clear(); // empty means search all page
            commonProperty.pagePaths.clear();
            DumpTreeNG(rootNode, depth, nodeID, commonProperty, isDumpSimplify);
        }
    }
}

void JsAccessibilityManager::CreateNodeInfoJson(const RefPtr<NG::FrameNode>& node, const CommonProperty& commonProperty,
    std::unique_ptr<JsonValue>& json, int32_t childSize)
{
    CHECK_NULL_VOID(node);
    auto child = JsonUtil::Create(true);
    child->Put("childSize", childSize);
    child->Put("ID", node->GetAccessibilityId());
    child->Put("compid", node->GetInspectorId().value_or("").c_str());
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    if (accessibilityProperty) {
        child->Put("text", accessibilityProperty->GetGroupText().c_str());
        child->Put("accessibilityText", accessibilityProperty->GetAccessibilityText().c_str());
        child->Put("accessibilityGroup", accessibilityProperty->IsAccessibilityGroup());
        child->Put("accessibilityLevel", accessibilityProperty->GetAccessibilityLevel().c_str());
    }
    NG::RectF rect = node->GetTransformRectRelativeToWindow(true);
    child->Put("top", rect.Top() + commonProperty.windowTop);
    child->Put("left", rect.Left() + commonProperty.windowLeft);
    child->Put("width", rect.Width());
    child->Put("height", rect.Height());
    child->Put("visible", node->IsVisible());
    auto eventHub = node->GetEventHub<NG::EventHub>();
    if (eventHub) {
        auto gestureEventHub = eventHub->GetGestureEventHub();
        child->Put("clickable", gestureEventHub ? gestureEventHub->IsAccessibilityClickable() : false);
        child->Put("longclickable", gestureEventHub ? gestureEventHub->IsAccessibilityLongClickable() : false);
    }
    if (accessibilityProperty) {
        child->Put("checkable", accessibilityProperty->IsCheckable());
        child->Put("scrollable", accessibilityProperty->IsScrollable());
        child->Put("checked", accessibilityProperty->IsChecked());
        child->Put("hint", accessibilityProperty->GetHintText().c_str());
        child->Put("childTree", accessibilityProperty->GetChildTreeId());
    }
    std::string tag =
        node->GetTag() == "root" ? "root" : node->GetTag() + "_" + std::to_string(node->GetAccessibilityId());
    json->Put(tag.c_str(), child);
}

void JsAccessibilityManager::DumpTreeNodeInfoInJson(
    const RefPtr<NG::FrameNode>& node, int32_t depth, const CommonProperty& commonProperty, int32_t childSize)
{
    auto json = JsonUtil::Create(true);
    CreateNodeInfoJson(node, commonProperty, json, childSize);
    std::string content = DumpLog::GetInstance().FormatDumpInfo(json->ToString(), depth);
    std::string prefix = DumpLog::GetInstance().GetPrefix(depth);
    std::string fulljson = prefix.append(content);
    DumpLog::GetInstance().PrintJson(fulljson);
}
} // namespace OHOS::Ace::Framework
