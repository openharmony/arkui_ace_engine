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

#include "js_accessibility_manager.h"

#include "accessibility_constants.h"
#include "accessibility_event_info.h"
#include "accessibility_system_ability_client.h"

#include "adapter/ohos/entrance/ace_application_info.h"
#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/linear_map.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/common/dom/dom_type.h"

using namespace OHOS::Accessibility;
using namespace OHOS::AccessibilityConfig;
using namespace std;

namespace OHOS::Ace::Framework {
namespace {
const char DUMP_ORDER[] = "-accessibility";
const char DUMP_INSPECTOR[] = "-inspector";
const char ACCESSIBILITY_FOCUSED_EVENT[] = "accessibilityfocus";
const char ACCESSIBILITY_CLEAR_FOCUS_EVENT[] = "accessibilityclearfocus";
const char TEXT_CHANGE_EVENT[] = "textchange";
const char PAGE_CHANGE_EVENT[] = "pagechange";
const char SCROLL_END_EVENT[] = "scrollend";
const char SCROLL_START_EVENT[] = "scrollstart";
const char MOUSE_HOVER_ENTER[] = "mousehoverenter";
const char MOUSE_HOVER_EXIT[] = "mousehoverexit";
const char IMPORTANT_YES[] = "yes";
const char IMPORTANT_NO[] = "no";
const char IMPORTANT_NO_HIDE_DES[] = "no-hide-descendants";
const char LIST_TAG[] = "List";
const char SIDEBARCONTAINER_TAG[] = "SideBarContainer";
constexpr int32_t INVALID_PARENT_ID = -2100000;
constexpr int32_t DEFAULT_PARENT_ID = 2100000;
constexpr int32_t ROOT_STACK_BASE = 1100000;
constexpr int32_t ROOT_DECOR_BASE = 3100000;
constexpr int32_t CARD_NODE_ID_RATION = 10000;
constexpr int32_t CARD_ROOT_NODE_ID_RATION = 1000;
constexpr int32_t CARD_BASE = 100000;

struct ActionTable {
    AceAction aceAction;
    ActionType action;
};

struct CommonProperty {
    int32_t windowId = 0;
    int32_t windowLeft = 0;
    int32_t windowTop = 0;
    int32_t pageId = 0;
    std::string pagePath;
};

struct AccessibilityActionParam {
    RefPtr<NG::AccessibilityProperty> accessibilityProperty;
    std::string setTextArgument = "";
    int32_t setSelectionStart = -1;
    int32_t setSelectionEnd = -1;
    TextMoveUnit moveUnit = TextMoveUnit::STEP_CHARACTER;
};

const std::map<Accessibility::ActionType, std::function<bool(const AccessibilityActionParam& param)>> ACTIONS = {
    { ActionType::ACCESSIBILITY_ACTION_SCROLL_FORWARD,
        [](const AccessibilityActionParam& param) { return param.accessibilityProperty->ActActionScrollForward(); } },
    { ActionType::ACCESSIBILITY_ACTION_SCROLL_BACKWARD,
        [](const AccessibilityActionParam& param) { return param.accessibilityProperty->ActActionScrollBackward(); } },
    { ActionType::ACCESSIBILITY_ACTION_SET_TEXT,
        [](const AccessibilityActionParam& param) {
            return param.accessibilityProperty->ActActionSetText(param.setTextArgument);
        } },
    { ActionType::ACCESSIBILITY_ACTION_SET_SELECTION,
        [](const AccessibilityActionParam& param) {
            return param.accessibilityProperty->ActActionSetSelection(param.setSelectionStart, param.setSelectionEnd);
        } },
    { ActionType::ACCESSIBILITY_ACTION_COPY,
        [](const AccessibilityActionParam& param) { return param.accessibilityProperty->ActActionCopy(); } },
    { ActionType::ACCESSIBILITY_ACTION_CUT,
        [](const AccessibilityActionParam& param) { return param.accessibilityProperty->ActActionCut(); } },
    { ActionType::ACCESSIBILITY_ACTION_PASTE,
        [](const AccessibilityActionParam& param) { return param.accessibilityProperty->ActActionPaste(); } },
    { ActionType::ACCESSIBILITY_ACTION_SELECT,
        [](const AccessibilityActionParam& param) { return param.accessibilityProperty->ActActionSelect(); } },
    { ActionType::ACCESSIBILITY_ACTION_CLEAR_SELECTION,
        [](const AccessibilityActionParam& param) { return param.accessibilityProperty->ActActionClearSelection(); } },
    { ActionType::ACCESSIBILITY_ACTION_NEXT_TEXT,
        [](const AccessibilityActionParam& param) {
            return param.accessibilityProperty->ActActionMoveText(static_cast<int32_t>(param.moveUnit), true);
        } },
    { ActionType::ACCESSIBILITY_ACTION_PREVIOUS_TEXT,
        [](const AccessibilityActionParam& param) {
            return param.accessibilityProperty->ActActionMoveText(static_cast<int32_t>(param.moveUnit), false);
        } },
};

Accessibility::EventType ConvertStrToEventType(const std::string& type)
{
    // static linear map must be sorted by key.
    static const LinearMapNode<Accessibility::EventType> eventTypeMap[] = {
        { ACCESSIBILITY_CLEAR_FOCUS_EVENT, Accessibility::EventType::TYPE_VIEW_ACCESSIBILITY_FOCUS_CLEARED_EVENT },
        { ACCESSIBILITY_FOCUSED_EVENT, Accessibility::EventType::TYPE_VIEW_ACCESSIBILITY_FOCUSED_EVENT },
        { DOM_CLICK, Accessibility::EventType::TYPE_VIEW_CLICKED_EVENT },
        { DOM_FOCUS, Accessibility::EventType::TYPE_VIEW_FOCUSED_EVENT },
        { DOM_LONG_PRESS, Accessibility::EventType::TYPE_VIEW_LONG_CLICKED_EVENT },
        { MOUSE_HOVER_ENTER, Accessibility::EventType::TYPE_VIEW_HOVER_ENTER_EVENT },
        { MOUSE_HOVER_EXIT, Accessibility::EventType::TYPE_VIEW_HOVER_EXIT_EVENT },
        { PAGE_CHANGE_EVENT, Accessibility::EventType::TYPE_PAGE_STATE_UPDATE },
        { SCROLL_END_EVENT, Accessibility::EventType::TYPE_VIEW_SCROLLED_EVENT },
        { SCROLL_START_EVENT, Accessibility::EventType::TYPE_VIEW_SCROLLED_EVENT },
        { DOM_SELECTED, Accessibility::EventType::TYPE_VIEW_SELECTED_EVENT },
        { TEXT_CHANGE_EVENT, Accessibility::EventType::TYPE_VIEW_TEXT_UPDATE_EVENT },
        { DOM_TOUCH_END, Accessibility::EventType::TYPE_TOUCH_END },
        { DOM_TOUCH_START, Accessibility::EventType::TYPE_TOUCH_BEGIN },
    };
    Accessibility::EventType eventType = Accessibility::EventType::TYPE_VIEW_INVALID;
    int64_t idx = BinarySearchFindIndex(eventTypeMap, ArraySize(eventTypeMap), type.c_str());
    if (idx >= 0) {
        eventType = eventTypeMap[idx].value;
    }
    return eventType;
}

Accessibility::EventType ConvertAceEventType(AccessibilityEventType type)
{
    static const LinearEnumMapNode<AccessibilityEventType, Accessibility::EventType> eventTypeMap[] = {
        { AccessibilityEventType::CLICK, Accessibility::EventType::TYPE_VIEW_CLICKED_EVENT },
        { AccessibilityEventType::LONG_PRESS, Accessibility::EventType::TYPE_VIEW_LONG_CLICKED_EVENT },
        { AccessibilityEventType::SELECTED, Accessibility::EventType::TYPE_VIEW_SELECTED_EVENT },
        { AccessibilityEventType::FOCUS, Accessibility::EventType::TYPE_VIEW_FOCUSED_EVENT },
        { AccessibilityEventType::TEXT_CHANGE, Accessibility::EventType::TYPE_VIEW_TEXT_UPDATE_EVENT },
        { AccessibilityEventType::PAGE_CHANGE, Accessibility::EventType::TYPE_PAGE_STATE_UPDATE },
        { AccessibilityEventType::CHANGE, Accessibility::EventType::TYPE_PAGE_CONTENT_UPDATE },
        { AccessibilityEventType::SCROLL_END, Accessibility::EventType::TYPE_VIEW_SCROLLED_EVENT },
        { AccessibilityEventType::TEXT_SELECTION_UPDATE,
            Accessibility::EventType::TYPE_VIEW_TEXT_SELECTION_UPDATE_EVENT },
        { AccessibilityEventType::ACCESSIBILITY_FOCUSED,
            Accessibility::EventType::TYPE_VIEW_ACCESSIBILITY_FOCUSED_EVENT },
        { AccessibilityEventType::ACCESSIBILITY_FOCUS_CLEARED,
            Accessibility::EventType::TYPE_VIEW_ACCESSIBILITY_FOCUS_CLEARED_EVENT },
        { AccessibilityEventType::TEXT_MOVE_UNIT, Accessibility::EventType::TYPE_VIEW_TEXT_MOVE_UNIT_EVENT },
    };
    Accessibility::EventType eventType = Accessibility::EventType::TYPE_VIEW_INVALID;
    int64_t idx = BinarySearchFindIndex(eventTypeMap, ArraySize(eventTypeMap), type);
    if (idx >= 0) {
        eventType = eventTypeMap[idx].value;
    }
    return eventType;
}

ActionType ConvertAceAction(AceAction aceAction)
{
    static const ActionTable actionTable[] = {
        { AceAction::ACTION_CLICK, ActionType::ACCESSIBILITY_ACTION_CLICK },
        { AceAction::ACTION_LONG_CLICK, ActionType::ACCESSIBILITY_ACTION_LONG_CLICK },
        { AceAction::ACTION_SCROLL_FORWARD, ActionType::ACCESSIBILITY_ACTION_SCROLL_FORWARD },
        { AceAction::ACTION_SCROLL_BACKWARD, ActionType::ACCESSIBILITY_ACTION_SCROLL_BACKWARD },
        { AceAction::ACTION_FOCUS, ActionType::ACCESSIBILITY_ACTION_FOCUS },
        { AceAction::ACTION_CLEAR_FOCUS, ActionType::ACCESSIBILITY_ACTION_CLEAR_FOCUS },
        { AceAction::ACTION_ACCESSIBILITY_FOCUS, ActionType::ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS },
        { AceAction::ACTION_CLEAR_ACCESSIBILITY_FOCUS, ActionType::ACCESSIBILITY_ACTION_CLEAR_ACCESSIBILITY_FOCUS },
        { AceAction::ACTION_NEXT_AT_MOVEMENT_GRANULARITY, ActionType::ACCESSIBILITY_ACTION_NEXT_TEXT },
        { AceAction::ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY, ActionType::ACCESSIBILITY_ACTION_PREVIOUS_TEXT },
        { AceAction::ACTION_SET_TEXT, ActionType::ACCESSIBILITY_ACTION_SET_TEXT },
        { AceAction::ACTION_COPY, ActionType::ACCESSIBILITY_ACTION_COPY },
        { AceAction::ACTION_PASTE, ActionType::ACCESSIBILITY_ACTION_PASTE },
        { AceAction::ACTION_CUT, ActionType::ACCESSIBILITY_ACTION_CUT },
        { AceAction::ACTION_SELECT, ActionType::ACCESSIBILITY_ACTION_SELECT },
        { AceAction::ACTION_CLEAR_SELECTION, ActionType::ACCESSIBILITY_ACTION_CLEAR_SELECTION },
        { AceAction::ACTION_SET_SELECTION, ActionType::ACCESSIBILITY_ACTION_SET_SELECTION },
    };
    for (const auto& item : actionTable) {
        if (aceAction == item.aceAction) {
            return item.action;
        }
    }
    return ActionType::ACCESSIBILITY_ACTION_INVALID;
}

inline RangeInfo ConvertAccessibilityValue(const AccessibilityValue& value)
{
    return RangeInfo(static_cast<int>(value.min), static_cast<int>(value.max), static_cast<int>(value.current));
}

int32_t ConvertToCardAccessibilityId(int32_t nodeId, int32_t cardId, int32_t rootNodeId)
{
    // result is integer total ten digits, top five for agp virtualViewId, end five for ace nodeId,
    // for example agp virtualViewId is 32, ace nodeId is 1000001, convert to result is 00032 10001.
    int32_t result = 0;
    if (nodeId == rootNodeId + ROOT_STACK_BASE) {
        // for example agp virtualViewId is 32 root node is 2100000, convert to result is 00032 21000.
        result = cardId * CARD_BASE + (static_cast<int32_t>(nodeId / CARD_BASE)) * CARD_ROOT_NODE_ID_RATION +
                 nodeId % CARD_BASE;
    } else {
        result = cardId * CARD_BASE + (static_cast<int32_t>(nodeId / DOM_ROOT_NODE_ID_BASE)) * CARD_NODE_ID_RATION +
                 nodeId % DOM_ROOT_NODE_ID_BASE;
    }
    return result;
}

void UpdateAccessibilityNodeInfo(const RefPtr<AccessibilityNode>& node, AccessibilityElementInfo& nodeInfo,
    const RefPtr<JsAccessibilityManager>& manager, int windowId)
{
    LOGD("nodeId:%{public}d", node->GetNodeId());
    int leftTopX = static_cast<int>(node->GetLeft()) + manager->GetWindowLeft(node->GetWindowId());
    int leftTopY = static_cast<int>(node->GetTop()) + manager->GetWindowTop(node->GetWindowId());
    int rightBottomX = leftTopX + static_cast<int>(node->GetWidth());
    int rightBottomY = leftTopY + static_cast<int>(node->GetHeight());
    if (manager->isOhosHostCard()) {
        int32_t id = ConvertToCardAccessibilityId(node->GetNodeId(), manager->GetCardId(), manager->GetRootNodeId());
        nodeInfo.SetAccessibilityId(id);
        if (node->GetParentId() == -1) {
            nodeInfo.SetParent(-1);
        } else {
            nodeInfo.SetParent(
                ConvertToCardAccessibilityId(node->GetParentId(), manager->GetCardId(), manager->GetRootNodeId()));
        }
        leftTopX = static_cast<int>(node->GetLeft() + manager->GetCardOffset().GetX());
        leftTopY = static_cast<int>(node->GetTop() + manager->GetCardOffset().GetY());
        rightBottomX = leftTopX + static_cast<int>(node->GetWidth());
        rightBottomY = leftTopY + static_cast<int>(node->GetHeight());
        Accessibility::Rect bounds(leftTopX, leftTopY, rightBottomX, rightBottomY);
        nodeInfo.SetRectInScreen(bounds);
    } else {
        if (node->GetTag() == SIDEBARCONTAINER_TAG) {
            Rect sideBarRect = node->GetRect();
            for (const auto& childNode : node->GetChildList()) {
                sideBarRect = sideBarRect.CombineRect(childNode->GetRect());
            }
            leftTopX = static_cast<int>(sideBarRect.Left()) + manager->GetWindowLeft(node->GetWindowId());
            leftTopY = static_cast<int>(sideBarRect.Top()) + manager->GetWindowTop(node->GetWindowId());
            rightBottomX = static_cast<int>(sideBarRect.Right()) + manager->GetWindowLeft(node->GetWindowId());
            rightBottomY = static_cast<int>(sideBarRect.Bottom()) + manager->GetWindowTop(node->GetWindowId());
        }
        Accessibility::Rect bounds(leftTopX, leftTopY, rightBottomX, rightBottomY);
        nodeInfo.SetRectInScreen(bounds);
        nodeInfo.SetComponentId(static_cast<int>(node->GetNodeId()));
        nodeInfo.SetParent(static_cast<int>(node->GetParentId()));
    }

    if (node->GetParentId() == -1) {
        const auto& children = node->GetChildList();
        if (!children.empty()) {
            auto lastChildNode = manager->GetAccessibilityNodeById(children.back()->GetNodeId());
            if (lastChildNode) {
                rightBottomX = leftTopX + static_cast<int>(lastChildNode->GetWidth());
                rightBottomY = leftTopY + static_cast<int>(lastChildNode->GetHeight());
                Accessibility::Rect bounds(leftTopX, leftTopY, rightBottomX, rightBottomY);
                nodeInfo.SetRectInScreen(bounds);
            }
        }
        nodeInfo.SetParent(INVALID_PARENT_ID);
    }
    if (node->GetNodeId() == 0) {
        nodeInfo.SetParent(INVALID_PARENT_ID);
    }
    nodeInfo.SetPagePath(manager->GetPagePath());
    nodeInfo.SetWindowId(windowId);
    nodeInfo.SetChecked(node->GetCheckedState());
    nodeInfo.SetEnabled(node->GetEnabledState());
    nodeInfo.SetFocused(node->GetFocusedState());
    nodeInfo.SetSelected(node->GetSelectedState());
    nodeInfo.SetCheckable(node->GetCheckableState());
    nodeInfo.SetClickable(node->GetClickableState());
    nodeInfo.SetFocusable(node->GetFocusableState());
    nodeInfo.SetScrollable(node->GetScrollableState());
    nodeInfo.SetLongClickable(node->GetLongClickableState());
    nodeInfo.SetEditable(node->GetEditable());
    nodeInfo.SetPluraLineSupported(node->GetIsMultiLine());
    nodeInfo.SetPassword(node->GetIsPassword());
    nodeInfo.SetTextLengthLimit(node->GetMaxTextLength());
    nodeInfo.SetSelectedBegin(node->GetTextSelectionStart());
    nodeInfo.SetSelectedEnd(node->GetTextSelectionEnd());
    nodeInfo.SetVisible(node->GetShown() && node->GetVisible());
    nodeInfo.SetHint(node->GetHintText());
    std::string accessibilityLabel = node->GetAccessibilityLabel();
    nodeInfo.SetLabeled(atoi(accessibilityLabel.c_str()));
    nodeInfo.SetError(node->GetErrorText());
    nodeInfo.SetComponentResourceId(node->GetJsComponentId());
    nodeInfo.SetInspectorKey(node->GetJsComponentId());
    RangeInfo rangeInfo = ConvertAccessibilityValue(node->GetAccessibilityValue());
    nodeInfo.SetRange(rangeInfo);
    nodeInfo.SetInputType(static_cast<int>(node->GetTextInputType()));
    nodeInfo.SetComponentType(node->GetTag());
    GridInfo gridInfo(
        node->GetCollectionInfo().rows, node->GetCollectionInfo().columns, (nodeInfo.IsPluraLineSupported() ? 0 : 1));
    nodeInfo.SetGrid(gridInfo);
    nodeInfo.SetAccessibilityFocus(node->GetAccessibilityFocusedState());
    nodeInfo.SetPageId(node->GetPageId());

    int32_t row = node->GetCollectionItemInfo().row;
    int32_t column = node->GetCollectionItemInfo().column;
    GridItemInfo gridItemInfo(row, row, column, column, false, nodeInfo.IsSelected());
    nodeInfo.SetGridItem(gridItemInfo);
    nodeInfo.SetBundleName(AceApplicationInfo::GetInstance().GetPackageName());

    if (node->GetTag() == LIST_TAG) {
        nodeInfo.SetItemCounts(node->GetListItemCounts());
        nodeInfo.SetBeginIndex(node->GetListBeginIndex());
        nodeInfo.SetEndIndex(node->GetListEndIndex());
    }
    if (node->GetIsPassword()) {
        std::string strStar(node->GetText().size(), '*');
        nodeInfo.SetContent(strStar);
    } else {
        nodeInfo.SetContent(node->GetText());
    }

    if (!node->GetAccessibilityHint().empty()) {
        if (node->GetAccessibilityLabel().empty()) {
            LOGI("UpdateAccessibilityNodeInfo Label is null");
        } else {
            LOGI("UpdateAccessibilityNodeInfo Label is not null");
        }
    }

    auto supportAceActions = node->GetSupportAction();
    std::vector<ActionType> actions(supportAceActions.size());

    for (auto it = supportAceActions.begin(); it != supportAceActions.end(); ++it) {
        AccessibleAction action(ConvertAceAction(*it), "ace");
        nodeInfo.AddAction(action);
    }

    if (node->GetImportantForAccessibility() == IMPORTANT_YES) {
        actions.emplace_back(ActionType::ACCESSIBILITY_ACTION_FOCUS);
        nodeInfo.SetCheckable(true);
    } else if (node->GetImportantForAccessibility() == IMPORTANT_NO ||
               node->GetImportantForAccessibility() == IMPORTANT_NO_HIDE_DES) {
        nodeInfo.SetVisible(false);
    }

    manager->UpdateNodeChildIds(node);
    for (const auto& child : node->GetChildIds()) {
        nodeInfo.AddChild(child);
    }

#ifdef ACE_DEBUG
    std::string actionForLog;
    for (const auto& action : supportAceActions) {
        if (!actionForLog.empty()) {
            actionForLog.append(",");
        }
        actionForLog.append(std::to_string(static_cast<int32_t>(action)));
    }
    LOGD("Support action is %{public}s", actionForLog.c_str());
#endif
}

void UpdateCacheInfo(std::list<AccessibilityElementInfo>& infos, uint32_t mode, const RefPtr<AccessibilityNode>& node,
    const RefPtr<JsAccessibilityManager>& jsAccessibilityManager, int windowId)
{
    // parent
    uint32_t umode = mode;
    if (umode & static_cast<uint32_t>(PREFETCH_PREDECESSORS)) {
        if (node->GetParentId() != -1 && node->GetParentId() != DEFAULT_PARENT_ID) {
            AccessibilityElementInfo parentNodeInfo;
            UpdateAccessibilityNodeInfo(node->GetParentNode(), parentNodeInfo, jsAccessibilityManager, windowId);
            infos.emplace_back(parentNodeInfo);
        }
    }
    // sister/brothers
    if (umode & static_cast<uint32_t>(PREFETCH_SIBLINGS)) {
        if (node->GetParentId() != -1 && node->GetParentId() != DEFAULT_PARENT_ID) {
            for (const auto& item : node->GetParentNode()->GetChildList()) {
                if (node->GetNodeId() != item->GetNodeId()) {
                    AccessibilityElementInfo siblingNodeInfo;
                    UpdateAccessibilityNodeInfo(item, siblingNodeInfo, jsAccessibilityManager, windowId);
                    infos.emplace_back(siblingNodeInfo);
                }
            }
        }
    }
    // children
    if (umode & static_cast<uint32_t>(PREFETCH_CHILDREN)) {
        for (const auto& item : node->GetChildList()) {
            AccessibilityElementInfo childNodeInfo;
            UpdateAccessibilityNodeInfo(item, childNodeInfo, jsAccessibilityManager, windowId);
            infos.emplace_back(childNodeInfo);
        }
    }
}

inline std::string BoolToString(bool tag)
{
    return tag ? "true" : "false";
}

std::string ConvertInputTypeToString(AceTextCategory type)
{
    switch (type) {
        case AceTextCategory::INPUT_TYPE_DEFAULT:
            return "INPUT_TYPE_DEFAULT";
        case AceTextCategory::INPUT_TYPE_TEXT:
            return "INPUT_TYPE_TEXT";
        case AceTextCategory::INPUT_TYPE_EMAIL:
            return "INPUT_TYPE_EMAIL";
        case AceTextCategory::INPUT_TYPE_DATE:
            return "INPUT_TYPE_DATE";
        case AceTextCategory::INPUT_TYPE_TIME:
            return "INPUT_TYPE_TIME";
        case AceTextCategory::INPUT_TYPE_NUMBER:
            return "INPUT_TYPE_NUMBER";
        case AceTextCategory::INPUT_TYPE_PASSWORD:
            return "INPUT_TYPE_PASSWORD";
        case AceTextCategory::INPUT_TYPE_PHONENUMBER:
            return "INPUT_TYPE_PHONENUMBER";
        default:
            return "illegal input type";
    }
}

bool FindAccessibilityFocus(const RefPtr<AccessibilityNode>& node, RefPtr<AccessibilityNode>& resultNode)
{
    CHECK_NULL_RETURN_NOLOG(node, false);
    if (node->GetAccessibilityFocusedState()) {
        resultNode = node;
        LOGI("FindFocus nodeId(%{public}d)", resultNode->GetNodeId());
        return true;
    }
    if (!node->GetChildList().empty()) {
        for (const auto& item : node->GetChildList()) {
            if (resultNode != nullptr) {
                return true;
            }
            if (FindAccessibilityFocus(item, resultNode)) {
                LOGI("FindFocus nodeId:%{public}d", item->GetNodeId());
                return true;
            }
        }
    }

    return false;
}

RefPtr<NG::FrameNode> FindAccessibilityFocus(const RefPtr<NG::UINode>& node)
{
    CHECK_NULL_RETURN_NOLOG(node, nullptr);
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(node);
    if (frameNode) {
        if (frameNode->GetRenderContext()->GetAccessibilityFocus().value_or(false)) {
            LOGI("FindFocus nodeId(%{public}d)", node->GetAccessibilityId());
            return frameNode;
        }
    }

    if (!node->GetChildren().empty()) {
        for (const auto& child : node->GetChildren()) {
            auto result = FindAccessibilityFocus(child);
            if (result) {
                return result;
            }
        }
    }
    return nullptr;
}

bool FindInputFocus(const RefPtr<AccessibilityNode>& node, RefPtr<AccessibilityNode>& resultNode)
{
    CHECK_NULL_RETURN_NOLOG(node, false);
    if (!node->GetFocusedState() && (node->GetParentId() != -1)) {
        return false;
    }
    if (node->GetFocusedState()) {
        resultNode = node;
        LOGI("FindFocus nodeId:%{public}d", resultNode->GetNodeId());
    }
    if (!node->GetChildList().empty()) {
        for (const auto& item : node->GetChildList()) {
            if (FindInputFocus(item, resultNode)) {
                return true;
            }
        }
    }
    return node->GetFocusedState();
}

RefPtr<NG::FrameNode> FindInputFocus(const RefPtr<NG::UINode>& node)
{
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(node);
    CHECK_NULL_RETURN_NOLOG(frameNode, nullptr);
    if (!(frameNode->GetFocusHub() ? frameNode->GetFocusHub()->IsCurrentFocus() : false)) {
        return nullptr;
    }

    if (frameNode->GetFocusHub()->IsChild()) {
        LOGI("FoundFocus nodeId(%{public}d)", node->GetAccessibilityId());
        if (frameNode->IsInternal()) {
            return frameNode->GetFocusParent();
        }
        return frameNode;
    }

    auto focusHub = frameNode->GetFocusHub();
    auto focusChildren = focusHub->GetChildren();
    for (const auto& focusChild : focusChildren) {
        auto childNode = FindInputFocus(focusChild->GetFrameNode());
        if (childNode) {
            return childNode;
        }
    }
    return nullptr;
}

void FindText(
    const RefPtr<AccessibilityNode>& node, const std::string& text, std::list<RefPtr<AccessibilityNode>>& nodeList)
{
    CHECK_NULL_VOID_NOLOG(node);
    if (node->GetText().find(text) != std::string::npos) {
        LOGI("FindText find nodeId(%{public}d)", node->GetNodeId());
        nodeList.push_back(node);
    }
    if (!node->GetChildList().empty()) {
        for (const auto& child : node->GetChildList()) {
            FindText(child, text, nodeList);
        }
    }
}

void FindText(const RefPtr<NG::UINode>& node, const std::string& text, std::list<RefPtr<NG::FrameNode>>& nodeList)
{
    CHECK_NULL_VOID(node);

    auto frameNode = AceType::DynamicCast<NG::FrameNode>(node);
    if (frameNode && !frameNode->IsInternal()) {
        if (frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>()->GetAccessibilityText().find(text) !=
            std::string::npos) {
            LOGI("FindText find nodeId(%{public}d)", frameNode->GetAccessibilityId());
            nodeList.push_back(frameNode);
        }
    }

    if (!node->GetChildren().empty()) {
        for (const auto& child : node->GetChildren()) {
            FindText(child, text, nodeList);
        }
    }
}

RefPtr<NG::FrameNode> GetInspectorById(const RefPtr<NG::FrameNode>& root, int32_t id)
{
    CHECK_NULL_RETURN(root, nullptr);
    std::queue<RefPtr<NG::UINode>> nodes;
    nodes.push(root);
    RefPtr<NG::FrameNode> frameNode;
    while (!nodes.empty()) {
        auto current = nodes.front();
        nodes.pop();
        frameNode = AceType::DynamicCast<NG::FrameNode>(current);
        if (frameNode != nullptr) {
            if (id == frameNode->GetAccessibilityId()) {
                return frameNode;
            }
        }
        const auto& children = current->GetChildren();
        for (const auto& child : children) {
            nodes.push(child);
        }
    }
    return nullptr;
}

void GetFrameNodeParent(const RefPtr<NG::UINode>& uiNode, RefPtr<NG::FrameNode>& parent)
{
    if (AceType::InstanceOf<NG::FrameNode>(uiNode)) {
        auto frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode);
        if (!frameNode->IsInternal()) {
            parent = frameNode;
            return;
        }
    }
    CHECK_NULL_VOID(uiNode);
    auto parentNode = uiNode->GetParent();
    GetFrameNodeParent(parentNode, parent);
}

bool CheckFrameNodeByAccessibilityLevel(const RefPtr<NG::FrameNode>& frameNode, bool isParent)
{
    bool ret = false;
    CHECK_NULL_RETURN(frameNode, false);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    auto uiNode = frameNode->GetParent();
    RefPtr<NG::FrameNode> parentNode;
    if (uiNode != nullptr) {
        GetFrameNodeParent(uiNode, parentNode);
    }

    if (isParent) {
        if (accessibilityProperty->GetAccessibilityLevel() == IMPORTANT_NO_HIDE_DES) {
            ret = false;
            return ret;
        }
        if (!parentNode) {
            if (accessibilityProperty->IsAccessibilityGroup()) {
                ret = false;
            } else {
                ret = true;
            }
        } else {
            if (accessibilityProperty->IsAccessibilityGroup()) {
                ret = false;
            } else {
                ret = CheckFrameNodeByAccessibilityLevel(parentNode, true);
            }
        }
    } else {
        if (accessibilityProperty->GetAccessibilityLevel() == IMPORTANT_YES) {
            ret = true;
            if (!parentNode) {
                return ret;
            }
            auto parentAccessibilityProperty = parentNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
            if (parentAccessibilityProperty->IsAccessibilityGroup()) {
                ret = false;
            } else {
                ret = CheckFrameNodeByAccessibilityLevel(parentNode, true);
            }
        } else {
            ret = false;
        }
    }
    return ret;
}

void GetFrameNodeChildren(const RefPtr<NG::UINode>& uiNode, std::vector<int32_t>& children, int32_t pageId)
{
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode);
    if (AceType::InstanceOf<NG::FrameNode>(uiNode)) {
        CHECK_NULL_VOID_NOLOG(frameNode->IsActive());
        if (uiNode->GetTag() == "stage") {
        } else if (uiNode->GetTag() == "page") {
            if (uiNode->GetPageId() != pageId) {
                return;
            }
        } else if (!frameNode->IsInternal()) {
            if (CheckFrameNodeByAccessibilityLevel(frameNode, false)) {
                children.emplace_back(uiNode->GetAccessibilityId());
                return;
            }
        }
    }

    for (const auto& frameChild : uiNode->GetChildren()) {
        GetFrameNodeChildren(frameChild, children, pageId);
    }
}

void GetFrameNodeChildren(const RefPtr<NG::UINode>& uiNode, std::list<RefPtr<NG::FrameNode>>& children)
{
    if (AceType::InstanceOf<NG::FrameNode>(uiNode)) {
        auto frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode);
        if (!frameNode->IsInternal()) {
            if (CheckFrameNodeByAccessibilityLevel(frameNode, false)) {
                children.emplace_back(frameNode);
                return;
            }
        }
    } else {
        for (const auto& frameChild : uiNode->GetChildren()) {
            GetFrameNodeChildren(frameChild, children);
        }
    }
}

int32_t GetParentId(const RefPtr<NG::UINode>& uiNode)
{
    auto parent = uiNode->GetParent();
    while (parent) {
        if (AceType::InstanceOf<NG::FrameNode>(parent)) {
            return parent->GetAccessibilityId();
        }
        parent = parent->GetParent();
    }
    return INVALID_PARENT_ID;
}

void FillEventInfo(const RefPtr<NG::FrameNode>& node, AccessibilityEventInfo& eventInfo)
{
    CHECK_NULL_VOID_NOLOG(node);
    eventInfo.SetComponentType(node->GetTag());
    eventInfo.SetPageId(node->GetPageId());
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    eventInfo.AddContent(accessibilityProperty->GetAccessibilityText());
    eventInfo.SetItemCounts(accessibilityProperty->GetCollectionItemCounts());
    eventInfo.SetBeginIndex(accessibilityProperty->GetBeginIndex());
    eventInfo.SetEndIndex(accessibilityProperty->GetEndIndex());
}

void FillEventInfo(const RefPtr<AccessibilityNode>& node, AccessibilityEventInfo& eventInfo)
{
    eventInfo.SetComponentType(node->GetTag());
    if (node->GetTag() == LIST_TAG) {
        eventInfo.SetItemCounts(node->GetListItemCounts());
        eventInfo.SetBeginIndex(node->GetListBeginIndex());
        eventInfo.SetEndIndex(node->GetListEndIndex());
    }
    eventInfo.SetPageId(node->GetPageId());
    eventInfo.AddContent(node->GetText());
    eventInfo.SetLatestContent(node->GetText());
}

inline bool IsPopupSupported(const RefPtr<NG::PipelineContext>& pipeline, int32_t nodeId)
{
    CHECK_NULL_RETURN_NOLOG(pipeline, false);
    auto overlayManager = pipeline->GetOverlayManager();
    if (overlayManager) {
        return overlayManager->HasPopupInfo(nodeId);
    }
    return false;
}

void UpdateSupportAction(const RefPtr<NG::FrameNode>& node, AccessibilityElementInfo& nodeInfo)
{
    CHECK_NULL_VOID_NOLOG(node);
    auto gestureEventHub = node->GetEventHub<NG::EventHub>()->GetGestureEventHub();
    if (gestureEventHub) {
        nodeInfo.SetClickable(gestureEventHub->IsAccessibilityClickable());
        if (gestureEventHub->IsAccessibilityClickable()) {
            AccessibleAction action(ACCESSIBILITY_ACTION_CLICK, "ace");
            nodeInfo.AddAction(action);
        }
        nodeInfo.SetLongClickable(gestureEventHub->IsAccessibilityLongClickable());
        if (gestureEventHub->IsAccessibilityLongClickable()) {
            AccessibleAction action(ACCESSIBILITY_ACTION_LONG_CLICK, "ace");
            nodeInfo.AddAction(action);
        }
    }
    if (nodeInfo.IsFocusable()) {
        if (nodeInfo.IsFocused()) {
            AccessibleAction action(ACCESSIBILITY_ACTION_CLEAR_FOCUS, "ace");
            nodeInfo.AddAction(action);
        } else {
            AccessibleAction action(ACCESSIBILITY_ACTION_FOCUS, "ace");
            nodeInfo.AddAction(action);
        }
    }

    if (nodeInfo.HasAccessibilityFocus()) {
        AccessibleAction action(ACCESSIBILITY_ACTION_CLEAR_ACCESSIBILITY_FOCUS, "ace");
        nodeInfo.AddAction(action);
    } else {
        AccessibleAction action(ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS, "ace");
        nodeInfo.AddAction(action);
    }
}

static void UpdateAccessibilityElementInfo(const RefPtr<NG::FrameNode>& node, AccessibilityElementInfo& nodeInfo)
{
    CHECK_NULL_VOID_NOLOG(node);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID_NOLOG(accessibilityProperty);

    nodeInfo.SetContent(accessibilityProperty->GetAccessibilityText());
    if (accessibilityProperty->HasRange()) {
        RangeInfo rangeInfo = ConvertAccessibilityValue(accessibilityProperty->GetAccessibilityValue());
        nodeInfo.SetRange(rangeInfo);
    }
    nodeInfo.SetHint(accessibilityProperty->GetHintText());
    nodeInfo.SetTextLengthLimit(accessibilityProperty->GetTextLengthLimit());
    nodeInfo.SetChecked(accessibilityProperty->IsChecked());
    nodeInfo.SetSelected(accessibilityProperty->IsSelected());
    nodeInfo.SetPassword(accessibilityProperty->IsPassword());
    nodeInfo.SetPluraLineSupported(accessibilityProperty->IsMultiLine());
    nodeInfo.SetHinting(accessibilityProperty->IsHint());
    nodeInfo.SetCurrentIndex(accessibilityProperty->GetCurrentIndex());
    nodeInfo.SetBeginIndex(accessibilityProperty->GetBeginIndex());
    nodeInfo.SetEndIndex(accessibilityProperty->GetEndIndex());
    auto tag = node->GetTag();
    if (tag == V2::TOAST_ETS_TAG || tag == V2::POPUP_ETS_TAG || tag == V2::DIALOG_ETS_TAG ||
        tag == V2::ACTION_SHEET_DIALOG_ETS_TAG || tag == V2::ALERT_DIALOG_ETS_TAG || tag == V2::MENU_ETS_TAG ||
        tag == "SelectMenu") {
        nodeInfo.SetLiveRegion(1);
    }
    nodeInfo.SetContentInvalid(accessibilityProperty->GetContentInvalid());
    nodeInfo.SetError(accessibilityProperty->GetErrorText());
    nodeInfo.SetSelectedBegin(accessibilityProperty->GetTextSelectionStart());
    nodeInfo.SetSelectedEnd(accessibilityProperty->GetTextSelectionEnd());
    nodeInfo.SetInputType(static_cast<int>(accessibilityProperty->GetTextInputType()));
    nodeInfo.SetItemCounts(accessibilityProperty->GetCollectionItemCounts());

    GridInfo gridInfo(accessibilityProperty->GetCollectionInfo().rows,
        accessibilityProperty->GetCollectionInfo().columns, accessibilityProperty->GetCollectionInfo().selectMode);
    nodeInfo.SetGrid(gridInfo);

    int32_t row = accessibilityProperty->GetCollectionItemInfo().row;
    int32_t column = accessibilityProperty->GetCollectionItemInfo().column;
    int32_t rowSpan = accessibilityProperty->GetCollectionItemInfo().rowSpan;
    int32_t columnSpan = accessibilityProperty->GetCollectionItemInfo().columnSpan;
    bool heading = accessibilityProperty->GetCollectionItemInfo().heading;
    GridItemInfo gridItemInfo(row, rowSpan, column, columnSpan, heading, nodeInfo.IsSelected());
    nodeInfo.SetGridItem(gridItemInfo);

    if (nodeInfo.IsEnabled()) {
        nodeInfo.SetCheckable(accessibilityProperty->IsCheckable());
        nodeInfo.SetScrollable(accessibilityProperty->IsScrollable());
        nodeInfo.SetEditable(accessibilityProperty->IsEditable());
        nodeInfo.SetDeletable(accessibilityProperty->IsDeletable());
        UpdateSupportAction(node, nodeInfo);
        accessibilityProperty->ResetSupportAction();
        auto supportAceActions = accessibilityProperty->GetSupportAction();
        for (auto it = supportAceActions.begin(); it != supportAceActions.end(); ++it) {
            AccessibleAction action(ConvertAceAction(*it), "ace");
            nodeInfo.AddAction(action);
        }
    }
}

void UpdateAccessibilityElementInfo(const RefPtr<NG::FrameNode>& node, const CommonProperty& commonProperty,
    AccessibilityElementInfo& nodeInfo, const RefPtr<NG::PipelineContext>& ngPipeline)
{
    CHECK_NULL_VOID_NOLOG(node);
    nodeInfo.SetParent(GetParentId(node));
    std::vector<int32_t> children;
    for (const auto& item : node->GetChildren()) {
        GetFrameNodeChildren(item, children, commonProperty.pageId);
    }
    for (const auto& child : children) {
        nodeInfo.AddChild(child);
    }

    nodeInfo.SetAccessibilityId(node->GetAccessibilityId());
    nodeInfo.SetComponentType(node->GetTag());

    nodeInfo.SetEnabled(node->GetFocusHub() ? node->GetFocusHub()->IsEnabled() : true);
    nodeInfo.SetFocused(node->GetFocusHub() ? node->GetFocusHub()->IsCurrentFocus() : false);
    nodeInfo.SetAccessibilityFocus(node->GetRenderContext()->GetAccessibilityFocus().value_or(false));
    nodeInfo.SetInspectorKey(node->GetInspectorId().value_or(""));
    nodeInfo.SetVisible(node->IsVisible());
    if (node->IsVisible()) {
        auto rect = node->GetTransformRectRelativeToWindow();
        auto left = rect.Left() + commonProperty.windowLeft;
        auto top = rect.Top() + commonProperty.windowTop;
        auto right = rect.Right() + commonProperty.windowLeft;
        auto bottom = rect.Bottom() + commonProperty.windowTop;
        Accessibility::Rect bounds { left, top, right, bottom };
        nodeInfo.SetRectInScreen(bounds);
        LOGD("UpdateAccessibilityElementInfo nodeId:%{public}d, tag:%{public}s rect:left:%{public}f, top:%{public}f, "
             "right:%{public}f, bottom:%{public}f",
            node->GetAccessibilityId(), node->GetTag().c_str(), left, top, right, bottom);
    }

    nodeInfo.SetWindowId(commonProperty.windowId);
    nodeInfo.SetPageId(node->GetPageId());
    nodeInfo.SetPagePath(commonProperty.pagePath);
    nodeInfo.SetBundleName(AceApplicationInfo::GetInstance().GetPackageName());

    if (nodeInfo.IsEnabled()) {
        nodeInfo.SetFocusable(node->GetFocusHub() ? node->GetFocusHub()->IsFocusable() : false);
        nodeInfo.SetPopupSupported(IsPopupSupported(ngPipeline, node->GetId()));
    }
    nodeInfo.SetComponentResourceId(node->GetInspectorId().value_or(""));
    UpdateAccessibilityElementInfo(node, nodeInfo);
}

bool CanAccessibilityFocusedNG(const RefPtr<NG::FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    return !node->IsRootNode() &&
           node->GetLayoutProperty()->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::VISIBLE &&
           accessibilityProperty->GetAccessibilityLevel() != IMPORTANT_NO &&
           accessibilityProperty->GetAccessibilityLevel() != IMPORTANT_NO_HIDE_DES;
}
// focus move search
void AddFocusableNode(std::list<RefPtr<NG::FrameNode>>& nodeList, const RefPtr<NG::FrameNode>& node)
{
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    const std::string level = accessibilityProperty->GetAccessibilityLevel();
    if (CanAccessibilityFocusedNG(node)) {
        nodeList.emplace_back(node);
    }

    if (!accessibilityProperty->IsAccessibilityGroup() && level != IMPORTANT_NO_HIDE_DES) {
        std::list<RefPtr<NG::FrameNode>> children;
        for (const auto& child : node->GetChildren()) {
            GetFrameNodeChildren(child, children);
        }

        for (const auto& child : children) {
            AddFocusableNode(nodeList, child);
        }
    }
}

RefPtr<NG::FrameNode> GetNextFocusableNode(
    const std::list<RefPtr<NG::FrameNode>>& nodeList, RefPtr<NG::FrameNode>& node)
{
    auto nodeItem = nodeList.begin();
    for (; nodeItem != nodeList.end(); nodeItem++) {
        if ((*nodeItem)->GetAccessibilityId() == node->GetAccessibilityId()) {
            break;
        }
    }

    if (nodeItem != nodeList.end()) {
        if (++nodeItem != nodeList.end()) {
            return (*nodeItem);
        }
    }
    if (!nodeList.empty()) {
        return (*nodeList.begin());
    }

    return nullptr;
}

RefPtr<NG::FrameNode> GetPreviousFocusableNode(
    const std::list<RefPtr<NG::FrameNode>>& nodeList, RefPtr<NG::FrameNode>& node)
{
    auto nodeItem = nodeList.rbegin();
    for (; nodeItem != nodeList.rend(); nodeItem++) {
        if ((*nodeItem)->GetAccessibilityId() == node->GetAccessibilityId()) {
            break;
        }
    }

    if (nodeItem != nodeList.rend()) {
        if (++nodeItem != nodeList.rend()) {
            return (*nodeItem);
        }
    }
    if (!nodeList.empty()) {
        return (*nodeList.rbegin());
    }

    return nullptr;
}

RefPtr<NG::FrameNode> FindNodeInRelativeDirection(
    const std::list<RefPtr<NG::FrameNode>>& nodeList, RefPtr<NG::FrameNode>& node, int direction)
{
    switch (direction) {
        case FocusMoveDirection::FORWARD:
            return GetNextFocusableNode(nodeList, node);
        case FocusMoveDirection::BACKWARD:
            return GetPreviousFocusableNode(nodeList, node);
        default:
            break;
    }

    return nullptr;
}

RefPtr<NG::FrameNode> FindNodeInAbsoluteDirection(
    const std::list<RefPtr<NG::FrameNode>>& nodeList, RefPtr<NG::FrameNode>& node, const int direction)
{
    NG::RectF rect = node->GetTransformRectRelativeToWindow();
    auto left = rect.Left();
    auto top = rect.Top();
    auto width = rect.Width();
    auto height = rect.Height();
    Rect tempBest(left, top, width, height);
    auto nodeRect = tempBest;
    switch (direction) {
        case FocusMoveDirection::LEFT:
            tempBest.SetLeft(left + width + 1);
            break;
        case FocusMoveDirection::RIGHT:
            tempBest.SetLeft(left - width - 1);
            break;
        case FocusMoveDirection::UP:
            tempBest.SetTop(top + height + 1);
            break;
        case FocusMoveDirection::DOWN:
            tempBest.SetTop(top - height - 1);
            break;
        default:
            break;
    }

    RefPtr<NG::FrameNode> nearestNode = nullptr;
    for (const auto& nodeItem : nodeList) {
        if (nodeItem->GetAccessibilityId() == node->GetAccessibilityId() || nodeItem->IsRootNode()) {
            continue;
        }
        rect = nodeItem->GetTransformRectRelativeToWindow();
        rect.SetOffset(nodeItem->GetTransformRelativeOffset());
        Rect itemRect(rect.Left(), rect.Top(), rect.Width(), rect.Height());
        if (CheckBetterRect(nodeRect, direction, itemRect, tempBest)) {
            tempBest = itemRect;
            nearestNode = nodeItem;
        }
    }
    LOGI("found %{public}d", nearestNode ? nearestNode->GetAccessibilityId() : -1);
    return nearestNode;
}

// execute action
bool RequestFocus(RefPtr<NG::FrameNode>& frameNode)
{
    auto focusHub = frameNode->GetFocusHub();
    CHECK_NULL_RETURN_NOLOG(focusHub, false);
    return focusHub->RequestFocusImmediately();
}

bool LostFocus(const RefPtr<NG::FrameNode>& frameNode)
{
    CHECK_NULL_RETURN_NOLOG(frameNode, false);
    auto focusHub = frameNode->GetFocusHub();
    CHECK_NULL_RETURN_NOLOG(focusHub, false);
    focusHub->LostFocus();
    return true;
}

bool ActClick(RefPtr<NG::FrameNode>& frameNode)
{
    auto gesture = frameNode->GetEventHub<NG::EventHub>()->GetGestureEventHub();
    CHECK_NULL_RETURN_NOLOG(gesture, false);
    return gesture->ActClick();
}

bool ActLongClick(RefPtr<NG::FrameNode>& frameNode)
{
    auto gesture = frameNode->GetEventHub<NG::EventHub>()->GetGestureEventHub();
    CHECK_NULL_RETURN_NOLOG(gesture, false);
    return gesture->ActLongClick();
}

void ClearAccessibilityFocus(const RefPtr<NG::FrameNode>& root, int32_t focusNodeId)
{
    auto oldFocusNode = GetInspectorById(root, focusNodeId);
    CHECK_NULL_VOID_NOLOG(oldFocusNode);
    oldFocusNode->GetRenderContext()->UpdateAccessibilityFocus(false);
}

bool ActAccessibilityFocus(int32_t elementId, RefPtr<NG::FrameNode>& frameNode, RefPtr<NG::PipelineContext>& context,
    NodeId& currentFocusNodeId, bool isNeedClear)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    if (isNeedClear) {
        if (elementId != currentFocusNodeId) {
            return false;
        }
        renderContext->UpdateAccessibilityFocus(false);
        currentFocusNodeId = -1;
        return true;
    }
    if (elementId == currentFocusNodeId) {
        LOGW("This node is focused.");
        return false;
    }
    Framework::ClearAccessibilityFocus(context->GetRootElement(), currentFocusNodeId);
    renderContext->UpdateAccessibilityFocus(true);
    currentFocusNodeId = frameNode->GetAccessibilityId();
    return true;
}

inline string GetSupportAction(const std::unordered_set<AceAction>& supportAceActions)
{
    std::string actionForDump;
    for (const auto& action : supportAceActions) {
        if (!actionForDump.empty()) {
            actionForDump.append(",");
        }
        actionForDump.append(std::to_string(static_cast<int32_t>(action)));
    }
    return actionForDump;
}

static std::string ConvertActionTypeToString(ActionType action)
{
    switch (action) {
        case ActionType::ACCESSIBILITY_ACTION_FOCUS:
            return "ACCESSIBILITY_ACTION_FOCUS";
        case ActionType::ACCESSIBILITY_ACTION_CLEAR_FOCUS:
            return "ACCESSIBILITY_ACTION_CLEAR_FOCUS";
        case ActionType::ACCESSIBILITY_ACTION_SELECT:
            return "ACCESSIBILITY_ACTION_SELECT";
        case ActionType::ACCESSIBILITY_ACTION_CLEAR_SELECTION:
            return "ACCESSIBILITY_ACTION_CLEAR_SELECTION";
        case ActionType::ACCESSIBILITY_ACTION_CLICK:
            return "ACCESSIBILITY_ACTION_CLICK";
        case ActionType::ACCESSIBILITY_ACTION_LONG_CLICK:
            return "ACCESSIBILITY_ACTION_LONG_CLICK";
        case ActionType::ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS:
            return "ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS";
        case ActionType::ACCESSIBILITY_ACTION_CLEAR_ACCESSIBILITY_FOCUS:
            return "ACCESSIBILITY_ACTION_CLEAR_ACCESSIBILITY_FOCUS";
        case ActionType::ACCESSIBILITY_ACTION_SCROLL_FORWARD:
            return "ACCESSIBILITY_ACTION_SCROLL_FORWARD";
        case ActionType::ACCESSIBILITY_ACTION_SCROLL_BACKWARD:
            return "ACCESSIBILITY_ACTION_SCROLL_BACKWARD";
        case ActionType::ACCESSIBILITY_ACTION_COPY:
            return "ACCESSIBILITY_ACTION_COPY";
        case ActionType::ACCESSIBILITY_ACTION_PASTE:
            return "ACCESSIBILITY_ACTION_PASTE";
        case ActionType::ACCESSIBILITY_ACTION_CUT:
            return "ACCESSIBILITY_ACTION_CUT";
        case ActionType::ACCESSIBILITY_ACTION_SET_SELECTION:
            return "ACCESSIBILITY_ACTION_SET_SELECTION";
        case ActionType::ACCESSIBILITY_ACTION_SET_TEXT:
            return "ACCESSIBILITY_ACTION_SET_TEXT";
        case ActionType::ACCESSIBILITY_ACTION_NEXT_TEXT:
            return "ACCESSIBILITY_ACTION_NEXT_TEXT";
        case ActionType::ACCESSIBILITY_ACTION_PREVIOUS_TEXT:
            return "ACCESSIBILITY_ACTION_PREVIOUS_TEXT";
        default:
            return "ACCESSIBILITY_ACTION_INVALID";
    }
}

static AceAction ConvertAccessibilityAction(ActionType accessibilityAction)
{
    static const ActionTable actionTable[] = {
        { AceAction::ACTION_CLICK, ActionType::ACCESSIBILITY_ACTION_CLICK },
        { AceAction::ACTION_LONG_CLICK, ActionType::ACCESSIBILITY_ACTION_LONG_CLICK },
        { AceAction::ACTION_SCROLL_FORWARD, ActionType::ACCESSIBILITY_ACTION_SCROLL_FORWARD },
        { AceAction::ACTION_SCROLL_BACKWARD, ActionType::ACCESSIBILITY_ACTION_SCROLL_BACKWARD },
        { AceAction::ACTION_FOCUS, ActionType::ACCESSIBILITY_ACTION_FOCUS },
        { AceAction::ACTION_CLEAR_FOCUS, ActionType::ACCESSIBILITY_ACTION_CLEAR_FOCUS },
        { AceAction::ACTION_ACCESSIBILITY_FOCUS, ActionType::ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS },
        { AceAction::ACTION_CLEAR_ACCESSIBILITY_FOCUS, ActionType::ACCESSIBILITY_ACTION_CLEAR_ACCESSIBILITY_FOCUS },
        { AceAction::ACTION_NEXT_AT_MOVEMENT_GRANULARITY, ActionType::ACCESSIBILITY_ACTION_NEXT_TEXT },
        { AceAction::ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY, ActionType::ACCESSIBILITY_ACTION_PREVIOUS_TEXT },
        { AceAction::ACTION_SET_TEXT, ActionType::ACCESSIBILITY_ACTION_SET_TEXT },
        { AceAction::ACTION_COPY, ActionType::ACCESSIBILITY_ACTION_COPY },
        { AceAction::ACTION_PASTE, ActionType::ACCESSIBILITY_ACTION_PASTE },
        { AceAction::ACTION_CUT, ActionType::ACCESSIBILITY_ACTION_CUT },
        { AceAction::ACTION_SELECT, ActionType::ACCESSIBILITY_ACTION_SELECT },
        { AceAction::ACTION_CLEAR_SELECTION, ActionType::ACCESSIBILITY_ACTION_CLEAR_SELECTION },
        { AceAction::ACTION_SET_SELECTION, ActionType::ACCESSIBILITY_ACTION_SET_SELECTION },
    };
    for (const auto& item : actionTable) {
        if (accessibilityAction == item.action) {
            return item.aceAction;
        }
    }
    return AceAction::ACTION_NONE;
}

static void DumpSupportActionNG(const AccessibilityElementInfo& nodeInfo)
{
    DumpLog::GetInstance().AddDesc(
        "support action instructions: use command to make application components perform corresponding action");
    DumpLog::GetInstance().AddDesc(
        "use support action command: aa dump -i [AbilityRecord] -c -inspector [AccessibilityId] [AceAction]");
    std::string actionForDump;
    for (const auto& action : nodeInfo.GetActionList()) {
        if (!actionForDump.empty()) {
            actionForDump.append(",");
        }
        actionForDump.append(ConvertActionTypeToString(action.GetActionType()));
        actionForDump.append(": ");
        actionForDump.append(std::to_string(static_cast<int32_t>(ConvertAccessibilityAction(action.GetActionType()))));
    }
    DumpLog::GetInstance().AddDesc("support action: ", actionForDump);
}

inline void DumpContentListNG(const AccessibilityElementInfo& nodeInfo)
{
    std::vector<std::string> contentList;
    nodeInfo.GetContentList(contentList);
    std::string contents;
    for (auto content : contentList) {
        if (!contents.empty()) {
            contents.append(",");
        }
        contents.append(content);
    }
    DumpLog::GetInstance().AddDesc("content list: ", contents);
}

static void DumpAccessibilityPropertyNG(const AccessibilityElementInfo& nodeInfo)
{
    DumpLog::GetInstance().AddDesc("checked: ", BoolToString(nodeInfo.IsChecked()));
    DumpLog::GetInstance().AddDesc("selected: ", BoolToString(nodeInfo.IsSelected()));
    DumpLog::GetInstance().AddDesc("checkable: ", BoolToString(nodeInfo.IsCheckable()));
    DumpLog::GetInstance().AddDesc("scrollable: ", BoolToString(nodeInfo.IsScrollable()));
    DumpLog::GetInstance().AddDesc("accessibility hint: ", BoolToString(nodeInfo.IsGivingHint()));
    DumpLog::GetInstance().AddDesc("hint text: ", nodeInfo.GetHint());
    DumpLog::GetInstance().AddDesc("error text: ", nodeInfo.GetError());
    DumpLog::GetInstance().AddDesc("max text length: ", nodeInfo.GetTextLengthLimit());
    DumpLog::GetInstance().AddDesc("text selection start: ", nodeInfo.GetSelectedBegin());
    DumpLog::GetInstance().AddDesc("text selection end: ", nodeInfo.GetSelectedEnd());
    DumpLog::GetInstance().AddDesc("is multi line: ", BoolToString(nodeInfo.IsPluraLineSupported()));
    DumpLog::GetInstance().AddDesc("is password: ", BoolToString(nodeInfo.IsPassword()));
    DumpLog::GetInstance().AddDesc(
        "text input type: ", ConvertInputTypeToString(static_cast<AceTextCategory>(nodeInfo.GetInputType())));

    DumpLog::GetInstance().AddDesc("min value: ", nodeInfo.GetRange().GetMin());
    DumpLog::GetInstance().AddDesc("max value: ", nodeInfo.GetRange().GetMax());
    DumpLog::GetInstance().AddDesc("current value: ", nodeInfo.GetRange().GetCurrent());
    DumpLog::GetInstance().AddDesc("gird info rows: ", nodeInfo.GetGrid().GetRowCount());
    DumpLog::GetInstance().AddDesc("gird info columns: ", nodeInfo.GetGrid().GetColumnCount());
    DumpLog::GetInstance().AddDesc("gird info select mode: ", nodeInfo.GetGrid().GetSelectionMode());
    DumpLog::GetInstance().AddDesc("gird item info, row: ", nodeInfo.GetGridItem().GetRowIndex());
    DumpLog::GetInstance().AddDesc("gird item info, column: ", nodeInfo.GetGridItem().GetColumnIndex());
    DumpLog::GetInstance().AddDesc("gird item info, rowSpan: ", nodeInfo.GetGridItem().GetRowSpan());
    DumpLog::GetInstance().AddDesc("gird item info, columnSpan: ", nodeInfo.GetGridItem().GetColumnSpan());
    DumpLog::GetInstance().AddDesc("gird item info, is heading: ", nodeInfo.GetGridItem().IsHeading());
    DumpLog::GetInstance().AddDesc("gird item info, selected: ", nodeInfo.GetGridItem().IsSelected());
    DumpLog::GetInstance().AddDesc("current index: ", nodeInfo.GetCurrentIndex());
    DumpLog::GetInstance().AddDesc("begin index: ", nodeInfo.GetBeginIndex());
    DumpLog::GetInstance().AddDesc("end index: ", nodeInfo.GetEndIndex());
    DumpLog::GetInstance().AddDesc("collection item counts: ", nodeInfo.GetItemCounts());
    DumpLog::GetInstance().AddDesc("editable: ", BoolToString(nodeInfo.IsEditable()));
    DumpLog::GetInstance().AddDesc("is essential: ", BoolToString(nodeInfo.IsEssential()));
    DumpLog::GetInstance().AddDesc("deletable: ", nodeInfo.IsDeletable());
    DumpLog::GetInstance().AddDesc("live region: ", nodeInfo.GetLiveRegion());
    DumpLog::GetInstance().AddDesc("content description: ", nodeInfo.GetDescriptionInfo());
    DumpLog::GetInstance().AddDesc("content invalid: ", BoolToString(nodeInfo.GetContentInvalid()));
    DumpLog::GetInstance().AddDesc("accessibility label: ", nodeInfo.GetLabeledAccessibilityId());
    DumpLog::GetInstance().AddDesc(
        "trigger action: ", static_cast<int32_t>(ConvertAccessibilityAction(nodeInfo.GetTriggerAction())));
    DumpLog::GetInstance().AddDesc("text move step: " + std::to_string(nodeInfo.GetTextMovementStep()));
    DumpSupportActionNG(nodeInfo);
    DumpContentListNG(nodeInfo);
    DumpLog::GetInstance().AddDesc("latest content: ", nodeInfo.GetLatestContent());
}

inline string ChildernToString(const vector<int32_t>& children)
{
    std::string ids;
    for (auto child : children) {
        if (!ids.empty()) {
            ids.append(",");
        }
        ids.append(std::to_string(child));
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

static void DumpCommonPropertyNG(const AccessibilityElementInfo& nodeInfo)
{
    DumpLog::GetInstance().AddDesc("ID: ", nodeInfo.GetAccessibilityId());
    DumpLog::GetInstance().AddDesc("parent ID: ", nodeInfo.GetParentNodeId());
    DumpLog::GetInstance().AddDesc("child IDs: ", ChildernToString(nodeInfo.GetChildIds()));
    DumpLog::GetInstance().AddDesc("component type: ", nodeInfo.GetComponentType());
    DumpLog::GetInstance().AddDesc("text: ", nodeInfo.GetContent());
    DumpLog::GetInstance().AddDesc("window id: " + std::to_string(nodeInfo.GetWindowId()));
    DumpRectNG(nodeInfo.GetRectInScreen());

    DumpLog::GetInstance().AddDesc("enabled: ", BoolToString(nodeInfo.IsEnabled()));
    DumpLog::GetInstance().AddDesc("focusable: ", BoolToString(nodeInfo.IsFocusable()));
    DumpLog::GetInstance().AddDesc("focused: ", BoolToString(nodeInfo.IsFocused()));
    DumpLog::GetInstance().AddDesc("visible: ", BoolToString(nodeInfo.IsVisible()));
    DumpLog::GetInstance().AddDesc("accessibility focused: ", BoolToString(nodeInfo.HasAccessibilityFocus()));
    DumpLog::GetInstance().AddDesc("inspector key: ", nodeInfo.GetInspectorKey());
    DumpLog::GetInstance().AddDesc("bundle name: ", nodeInfo.GetBundleName());
    DumpLog::GetInstance().AddDesc("page id: " + std::to_string(nodeInfo.GetPageId()));
    DumpLog::GetInstance().AddDesc("page path: ", nodeInfo.GetPagePath());
    DumpLog::GetInstance().AddDesc("is valid element: ", BoolToString(nodeInfo.IsValidElement()));
    DumpLog::GetInstance().AddDesc("resource name: ", nodeInfo.GetComponentResourceId());

    DumpLog::GetInstance().AddDesc("clickable: ", BoolToString(nodeInfo.IsClickable()));
    DumpLog::GetInstance().AddDesc("long clickable: ", BoolToString(nodeInfo.IsLongClickable()));
    DumpLog::GetInstance().AddDesc("popup supported: ", BoolToString(nodeInfo.IsPopupSupported()));
}
} // namespace

JsAccessibilityManager::~JsAccessibilityManager()
{
    auto eventType = AccessibilityStateEventType::EVENT_ACCESSIBILITY_STATE_CHANGED;

    UnsubscribeStateObserver(eventType);
    UnsubscribeToastObserver();

    DeregisterInteractionOperation();
}
void JsAccessibilityManager::ToastAccessibilityConfigObserver::OnConfigChanged(
    const AccessibilityConfig::CONFIG_ID id, const AccessibilityConfig::ConfigValue& value)
{
    LOGD("accessibility content timeout changed:%{public}u", value.contentTimeout);
    AceApplicationInfo::GetInstance().SetBarrierfreeDuration((int32_t)value.contentTimeout);
}

bool JsAccessibilityManager::SubscribeToastObserver()
{
    LOGD("SubscribeToastObserver");
    if (!toastObserver_) {
        toastObserver_ = std::make_shared<ToastAccessibilityConfigObserver>();
    }
    CHECK_NULL_RETURN_NOLOG(toastObserver_, false);
    auto& config = OHOS::AccessibilityConfig::AccessibilityConfig::GetInstance();
    bool isSuccess = config.InitializeContext();
    if (!isSuccess) {
        LOGE("AccessibilityConfig InitializeContext failed");
        return false;
    }
    config.SubscribeConfigObserver(CONFIG_CONTENT_TIMEOUT, toastObserver_);
    return true;
}

bool JsAccessibilityManager::UnsubscribeToastObserver()
{
    LOGI("UnsubscribeToastObserver");
    CHECK_NULL_RETURN_NOLOG(toastObserver_, false);
    auto& config = OHOS::AccessibilityConfig::AccessibilityConfig::GetInstance();
    bool isSuccess = config.InitializeContext();
    if (!isSuccess) {
        LOGE("AccessibilityConfig InitializeContext failed");
        return false;
    }
    config.UnsubscribeConfigObserver(CONFIG_CONTENT_TIMEOUT, toastObserver_);
    return true;
}

bool JsAccessibilityManager::SubscribeStateObserver(int eventType)
{
    LOGD("SubscribeStateObserver");
    if (!stateObserver_) {
        stateObserver_ = std::make_shared<JsAccessibilityStateObserver>();
    }

    stateObserver_->SetHandler(WeakClaim(this));

    auto instance = AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_RETURN_NOLOG(instance, false);
    Accessibility::RetError ret = instance->SubscribeStateObserver(stateObserver_, eventType);
    LOGD("SubscribeStateObserver:%{public}d", ret);
    return ret == RET_OK;
}

bool JsAccessibilityManager::UnsubscribeStateObserver(int eventType)
{
    LOGI("UnsubscribeStateObserver");
    CHECK_NULL_RETURN_NOLOG(stateObserver_, false);
    std::shared_ptr<AccessibilitySystemAbilityClient> instance = AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_RETURN_NOLOG(instance, false);
    Accessibility::RetError ret = instance->UnsubscribeStateObserver(stateObserver_, eventType);
    LOGI("UnsubscribeStateObserver:%{public}d", ret);
    return ret == RET_OK;
}

void JsAccessibilityManager::InitializeCallback()
{
    LOGD("InitializeCallback");
    if (IsRegister()) {
        return;
    }

    auto pipelineContext = GetPipelineContext().Upgrade();
    CHECK_NULL_VOID_NOLOG(pipelineContext);
    windowId_ = pipelineContext->GetWindowId();

    auto client = AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_VOID_NOLOG(client);
    bool isEnabled = false;
    client->IsEnabled(isEnabled);
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(isEnabled);

    SubscribeToastObserver();

    if (!pipelineContext->IsFormRender()) {
        SubscribeStateObserver(AccessibilityStateEventType::EVENT_ACCESSIBILITY_STATE_CHANGED);
        if (isEnabled) {
            RegisterInteractionOperation(windowId_);
        }
    }
}

bool JsAccessibilityManager::SendAccessibilitySyncEvent(
    const AccessibilityEvent& accessibilityEvent, AccessibilityEventInfo eventInfo)
{
    if (!IsRegister()) {
        return false;
    }

    auto client = AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_RETURN(client, false);
    bool isEnabled = false;
    client->IsEnabled(isEnabled);
    if (!isEnabled) {
        return false;
    }

    LOGD("type:%{public}s nodeId:%{public}d", accessibilityEvent.eventType.c_str(), accessibilityEvent.nodeId);

    Accessibility::EventType type = Accessibility::EventType::TYPE_VIEW_INVALID;
    if (accessibilityEvent.type != AccessibilityEventType::UNKNOWN) {
        type = ConvertAceEventType(accessibilityEvent.type);
    } else {
        type = ConvertStrToEventType(accessibilityEvent.eventType);
    }

    if (type == Accessibility::EventType::TYPE_VIEW_INVALID) {
        return false;
    }

    eventInfo.SetTimeStamp(GetMicroTickCount());
    eventInfo.SetBeforeText(accessibilityEvent.beforeText);
    eventInfo.SetLatestContent(accessibilityEvent.latestContent);
    eventInfo.SetWindowChangeTypes(static_cast<Accessibility::WindowUpdateType>(accessibilityEvent.windowChangeTypes));
    eventInfo.SetWindowContentChangeTypes(
        static_cast<Accessibility::WindowsContentChangeTypes>(accessibilityEvent.windowContentChangeTypes));
    eventInfo.SetSource(accessibilityEvent.nodeId);
    eventInfo.SetEventType(type);
    eventInfo.SetCurrentIndex(static_cast<int>(accessibilityEvent.currentItemIndex));
    eventInfo.SetItemCounts(static_cast<int>(accessibilityEvent.itemCount));
    eventInfo.SetBundleName(AceApplicationInfo::GetInstance().GetPackageName());

    return client->SendEvent(eventInfo);
}

void JsAccessibilityManager::SendAccessibilityAsyncEvent(const AccessibilityEvent& accessibilityEvent)
{
    auto context = GetPipelineContext().Upgrade();
    CHECK_NULL_VOID_NOLOG(context);
    int32_t windowId = context->GetWindowId();
    if (windowId == 0) {
        return;
    }

    AccessibilityEventInfo eventInfo;
    if (AceType::InstanceOf<NG::PipelineContext>(context)) {
        RefPtr<NG::FrameNode> node;
        auto ngPipeline = FindPipelineByElementId(accessibilityEvent.nodeId, node);
        CHECK_NULL_VOID_NOLOG(ngPipeline);
        CHECK_NULL_VOID_NOLOG(node);
        FillEventInfo(node, eventInfo);
    } else {
        auto node = GetAccessibilityNodeFromPage(accessibilityEvent.nodeId);
        CHECK_NULL_VOID_NOLOG(node);
        FillEventInfo(node, eventInfo);
    }
    if (accessibilityEvent.type != AccessibilityEventType::PAGE_CHANGE) {
        eventInfo.SetWindowId(windowId);
    } else {
        eventInfo.SetWindowId(accessibilityEvent.windowId);
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), accessibilityEvent, eventInfo] {
            auto jsAccessibilityManager = weak.Upgrade();
            CHECK_NULL_VOID(jsAccessibilityManager);
            jsAccessibilityManager->SendAccessibilitySyncEvent(accessibilityEvent, eventInfo);
        },
        TaskExecutor::TaskType::BACKGROUND);
}

void JsAccessibilityManager::UpdateNodeChildIds(const RefPtr<AccessibilityNode>& node)
{
    CHECK_NULL_VOID_NOLOG(node);
    node->ActionUpdateIds();
    const auto& children = node->GetChildList();
    std::vector<int32_t> childrenVec;
    auto cardId = GetCardId();
    auto rootNodeId = GetRootNodeId();

    // get last stack children to barrier free service.
    if ((node->GetNodeId() == GetRootNodeId() + ROOT_STACK_BASE) && !children.empty() && !IsDeclarative()) {
        auto lastChildNodeId = children.back()->GetNodeId();
        if (isOhosHostCard()) {
            childrenVec.emplace_back(ConvertToCardAccessibilityId(lastChildNodeId, cardId, rootNodeId));
        } else {
            childrenVec.emplace_back(lastChildNodeId);
            for (const auto& child : children) {
                if (child->GetNodeId() == ROOT_DECOR_BASE - 1) {
                    childrenVec.emplace_back(child->GetNodeId());
                    break;
                }
            }
        }
    } else {
        childrenVec.resize(children.size());
        if (isOhosHostCard()) {
            std::transform(children.begin(), children.end(), childrenVec.begin(),
                [cardId, rootNodeId](const RefPtr<AccessibilityNode>& child) {
                    return ConvertToCardAccessibilityId(child->GetNodeId(), cardId, rootNodeId);
                });
        } else {
            std::transform(children.begin(), children.end(), childrenVec.begin(),
                [](const RefPtr<AccessibilityNode>& child) { return child->GetNodeId(); });
        }
    }
    node->SetChildIds(childrenVec);
}

void JsAccessibilityManager::ProcessParameters(
    ActionType op, const std::vector<std::string>& params, std::map<std::string, std::string>& paramsMap)
{
    if (op == ActionType::ACCESSIBILITY_ACTION_SET_TEXT) {
        if (params.size() == EVENT_DUMP_PARAM_LENGTH_UPPER) {
            paramsMap = { { ACTION_ARGU_SET_TEXT, params[EVENT_DUMP_ACTION_PARAM_INDEX] } };
        }
    }

    if (op == ActionType::ACCESSIBILITY_ACTION_SET_SELECTION) {
        if (params.size() == EVENT_DUMP_PARAM_LENGTH_LOWER) {
            paramsMap[ACTION_ARGU_SELECT_TEXT_START] = "-1";
            paramsMap[ACTION_ARGU_SELECT_TEXT_END] = "-1";
        } else if (params.size() == EVENT_DUMP_PARAM_LENGTH_UPPER) {
            paramsMap[ACTION_ARGU_SELECT_TEXT_START] = params[EVENT_DUMP_ACTION_PARAM_INDEX];
            paramsMap[ACTION_ARGU_SELECT_TEXT_END] = "-1";
        } else {
            paramsMap[ACTION_ARGU_SELECT_TEXT_START] = params[EVENT_DUMP_ACTION_PARAM_INDEX];
            paramsMap[ACTION_ARGU_SELECT_TEXT_END] = params[EVENT_DUMP_PARAM_LENGTH_UPPER];
        }
    }

    if (op == ActionType::ACCESSIBILITY_ACTION_NEXT_TEXT || op == ActionType::ACCESSIBILITY_ACTION_PREVIOUS_TEXT) {
        if (params.size() == EVENT_DUMP_PARAM_LENGTH_UPPER) {
            paramsMap[ACTION_ARGU_MOVE_UNIT] = std::to_string(TextMoveUnit::STEP_CHARACTER);
        }
        paramsMap[ACTION_ARGU_MOVE_UNIT] = std::to_string(TextMoveUnit::STEP_CHARACTER);
    }
}

void JsAccessibilityManager::DumpHandleEvent(const std::vector<std::string>& params)
{
    if (params.size() > EVENT_DUMP_PARAM_LENGTH_UPPER + 1) {
        DumpLog::GetInstance().Print("Error: params length is illegal!");
        return;
    }
    if (params[EVENT_DUMP_ORDER_INDEX] != DUMP_ORDER && params[EVENT_DUMP_ORDER_INDEX] != DUMP_INSPECTOR) {
        DumpLog::GetInstance().Print("Error: not accessibility dump order!");
        return;
    }

    auto pipeline = context_.Upgrade();
    CHECK_NULL_VOID(pipeline);
    int32_t nodeId = StringUtils::StringToInt(params[EVENT_DUMP_ID_INDEX]);
    auto action = static_cast<AceAction>(StringUtils::StringToInt(params[EVENT_DUMP_ACTION_INDEX]));
    auto op = ConvertAceAction(action);

    if ((op != ActionType::ACCESSIBILITY_ACTION_SET_SELECTION) && (params.size() > EVENT_DUMP_PARAM_LENGTH_UPPER + 1)) {
        DumpLog::GetInstance().Print("Error: params is illegal!");
        return;
    }

    std::map<std::string, std::string> paramsMap;
    ProcessParameters(op, params, paramsMap);
    if (AceType::InstanceOf<NG::PipelineContext>(pipeline)) {
        RefPtr<NG::FrameNode> node;
        pipeline = FindPipelineByElementId(nodeId, node);
        CHECK_NULL_VOID_NOLOG(pipeline);
        CHECK_NULL_VOID_NOLOG(node);
        pipeline->GetTaskExecutor()->PostTask(
            [weak = WeakClaim(this), op, nodeId, paramsMap, pipeline]() {
                auto jsAccessibilityManager = weak.Upgrade();
                CHECK_NULL_VOID(jsAccessibilityManager);
                jsAccessibilityManager->ExecuteActionNG(nodeId, paramsMap, op, pipeline);
            },
            TaskExecutor::TaskType::UI);
        return;
    }

    auto node = GetAccessibilityNodeFromPage(nodeId);
    CHECK_NULL_VOID(node);

    pipeline->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), op, node, paramsMap, pipeline]() {
            auto jsAccessibilityManager = weak.Upgrade();
            CHECK_NULL_VOID(jsAccessibilityManager);
            jsAccessibilityManager->AccessibilityActionEvent(
                op, paramsMap, node, AceType::DynamicCast<PipelineContext>(pipeline));
        },
        TaskExecutor::TaskType::UI);
}

void JsAccessibilityManager::DumpProperty(const RefPtr<AccessibilityNode>& node)
{
    const auto& supportAceActions = node->GetSupportAction();
    const auto& charValue = node->GetChartValue();

    DumpLog::GetInstance().AddDesc("ID: ", node->GetNodeId());
    DumpLog::GetInstance().AddDesc("parent ID: ", node->GetParentId());
    DumpLog::GetInstance().AddDesc("child IDs: ", GetNodeChildIds(node));
    DumpLog::GetInstance().AddDesc("component type: ", node->GetTag());
    DumpLog::GetInstance().AddDesc("input type: ", node->GetInputType());
    DumpLog::GetInstance().AddDesc("text: ", node->GetText());
    DumpLog::GetInstance().AddDesc("width: ", node->GetWidth());
    DumpLog::GetInstance().AddDesc("height: ", node->GetHeight());
    DumpLog::GetInstance().AddDesc("left: ", node->GetLeft() + GetCardOffset().GetX());
    DumpLog::GetInstance().AddDesc("top: ", node->GetTop() + GetCardOffset().GetY());
    DumpLog::GetInstance().AddDesc("enabled: ", BoolToString(node->GetEnabledState()));
    DumpLog::GetInstance().AddDesc("checked: ", BoolToString(node->GetCheckedState()));
    DumpLog::GetInstance().AddDesc("selected: ", BoolToString(node->GetSelectedState()));
    DumpLog::GetInstance().AddDesc("focusable: ", BoolToString(node->GetFocusableState()));
    DumpLog::GetInstance().AddDesc("focused: ", BoolToString(node->GetFocusedState()));
    DumpLog::GetInstance().AddDesc("checkable: ", BoolToString(node->GetCheckableState()));
    DumpLog::GetInstance().AddDesc("clickable: ", BoolToString(node->GetClickableState()));
    DumpLog::GetInstance().AddDesc("long clickable: ", BoolToString(node->GetLongClickableState()));
    DumpLog::GetInstance().AddDesc("scrollable: ", BoolToString(node->GetScrollableState()));
    DumpLog::GetInstance().AddDesc("editable: ", BoolToString(node->GetEditable()));
    DumpLog::GetInstance().AddDesc("hint text: ", node->GetHintText());
    DumpLog::GetInstance().AddDesc("error text: ", node->GetErrorText());
    DumpLog::GetInstance().AddDesc("js component id: ", node->GetJsComponentId());
    DumpLog::GetInstance().AddDesc("accessibility label: ", node->GetAccessibilityLabel());
    DumpLog::GetInstance().AddDesc("accessibility hint: ", node->GetAccessibilityHint());
    DumpLog::GetInstance().AddDesc("max text length: ", node->GetMaxTextLength());
    DumpLog::GetInstance().AddDesc("text selection start: ", node->GetTextSelectionStart());
    DumpLog::GetInstance().AddDesc("text selection end: ", node->GetTextSelectionEnd());
    DumpLog::GetInstance().AddDesc("is multi line: ", BoolToString(node->GetIsMultiLine()));
    DumpLog::GetInstance().AddDesc("is password", BoolToString(node->GetIsPassword()));
    DumpLog::GetInstance().AddDesc("text input type: ", ConvertInputTypeToString(node->GetTextInputType()));
    DumpLog::GetInstance().AddDesc("min value: ", node->GetAccessibilityValue().min);
    DumpLog::GetInstance().AddDesc("max value: ", node->GetAccessibilityValue().max);
    DumpLog::GetInstance().AddDesc("current value: ", node->GetAccessibilityValue().current);
    DumpLog::GetInstance().AddDesc("collection info rows: ", node->GetCollectionInfo().rows);
    DumpLog::GetInstance().AddDesc("collection info columns: ", node->GetCollectionInfo().columns);
    DumpLog::GetInstance().AddDesc("collection item info, row: ", node->GetCollectionItemInfo().row);
    DumpLog::GetInstance().AddDesc("collection item info, column: ", node->GetCollectionItemInfo().column);
    DumpLog::GetInstance().AddDesc("chart has value: ", BoolToString(charValue && !charValue->empty()));
    DumpLog::GetInstance().AddDesc("accessibilityGroup: ", BoolToString(node->GetAccessible()));
    DumpLog::GetInstance().AddDesc("accessibilityImportance: ", node->GetImportantForAccessibility());
    DumpLog::GetInstance().AddDesc("support action: ", GetSupportAction(supportAceActions));
    DumpLog::GetInstance().Print(0, node->GetTag(), node->GetChildList().size());
}

void JsAccessibilityManager::DumpPropertyNG(const std::vector<std::string>& params)
{
    auto pipeline = context_.Upgrade();
    CHECK_NULL_VOID(pipeline);

    RefPtr<NG::FrameNode> frameNode;
    auto nodeID = StringUtils::StringToInt(params[1]);
    auto ngPipeline = FindPipelineByElementId(nodeID, frameNode);
    CHECK_NULL_VOID(ngPipeline);
    CHECK_NULL_VOID(frameNode);

    auto windowLeft = GetWindowLeft(ngPipeline->GetWindowId());
    auto windowTop = GetWindowTop(ngPipeline->GetWindowId());
    int32_t pageId = 0;
    string pagePath;
    if (ngPipeline->GetWindowId() == pipeline->GetWindowId()) {
        auto stageManager = ngPipeline->GetStageManager();
        CHECK_NULL_VOID(stageManager);
        auto page = stageManager->GetLastPage();
        CHECK_NULL_VOID(page);
        pageId = page->GetPageId();
        pagePath = GetPagePath();
    }

    AccessibilityElementInfo nodeInfo;
    CommonProperty commonProperty { ngPipeline->GetWindowId(), windowLeft, windowTop, pageId, pagePath };
    UpdateAccessibilityElementInfo(frameNode, commonProperty, nodeInfo, ngPipeline);
    DumpCommonPropertyNG(nodeInfo);

    DumpAccessibilityPropertyNG(nodeInfo);
    DumpLog::GetInstance().Print(0, nodeInfo.GetComponentType(), nodeInfo.GetChildCount());
}

void JsAccessibilityManager::DumpProperty(const std::vector<std::string>& params)
{
    CHECK_NULL_VOID_NOLOG(DumpLog::GetInstance().GetDumpFile());
    if (params.empty()) {
        DumpLog::GetInstance().Print("Error: params cannot be empty!");
        return;
    }
    if (params.size() != PROPERTY_DUMP_PARAM_LENGTH) {
        DumpLog::GetInstance().Print("Error: params length is illegal!");
        return;
    }
    if (params[0] != DUMP_ORDER && params[0] != DUMP_INSPECTOR) {
        DumpLog::GetInstance().Print("Error: not accessibility dump order!");
        return;
    }

    auto pipeline = context_.Upgrade();
    CHECK_NULL_VOID(pipeline);

    if (!AceType::InstanceOf<NG::PipelineContext>(pipeline)) {
        auto node = GetAccessibilityNodeFromPage(StringUtils::StringToInt(params[1]));
        if (!node) {
            DumpLog::GetInstance().Print("Error: can't find node with ID " + params[1]);
            return;
        }
        DumpProperty(node);
    } else {
        DumpPropertyNG(params);
    }
}

static void DumpTreeNG(
    const RefPtr<NG::FrameNode>& parent, int32_t depth, NodeId nodeID, const CommonProperty& commonProperty)
{
    auto node = GetInspectorById(parent, nodeID);
    if (!node) {
        DumpLog::GetInstance().Print("Error: failed to get accessibility node with ID " + std::to_string(nodeID));
        return;
    }

    if (!node->IsActive()) {
        return;
    }

    NG::RectF rect = node->GetTransformRectRelativeToWindow();
    DumpLog::GetInstance().AddDesc("ID: " + std::to_string(node->GetAccessibilityId()));
    DumpLog::GetInstance().AddDesc("compid: " + node->GetInspectorId().value_or(""));
    DumpLog::GetInstance().AddDesc("text: " + node->GetAccessibilityProperty<NG::AccessibilityProperty>()->GetText());
    DumpLog::GetInstance().AddDesc(
        "accessibilityText: " + node->GetAccessibilityProperty<NG::AccessibilityProperty>()->GetAccessibilityText());
    DumpLog::GetInstance().AddDesc(
        "accessibilityGroup: " +
        std::to_string(node->GetAccessibilityProperty<NG::AccessibilityProperty>()->IsAccessibilityGroup()));
    DumpLog::GetInstance().AddDesc(
        "accessibilityLevel: " + node->GetAccessibilityProperty<NG::AccessibilityProperty>()->GetAccessibilityLevel());
    DumpLog::GetInstance().AddDesc("top: " + std::to_string(rect.Top() + commonProperty.windowTop));
    DumpLog::GetInstance().AddDesc("left: " + std::to_string(rect.Left() + commonProperty.windowLeft));
    DumpLog::GetInstance().AddDesc("width: " + std::to_string(rect.Width()));
    DumpLog::GetInstance().AddDesc("height: " + std::to_string(rect.Height()));
    DumpLog::GetInstance().AddDesc("visible: " + std::to_string(node->IsVisible()));
    auto gestureEventHub = node->GetEventHub<NG::EventHub>()->GetGestureEventHub();
    DumpLog::GetInstance().AddDesc(
        "clickable: " + std::to_string(gestureEventHub ? gestureEventHub->IsAccessibilityClickable() : false));
    DumpLog::GetInstance().AddDesc(
        "checkable: " + std::to_string(node->GetAccessibilityProperty<NG::AccessibilityProperty>()->IsCheckable()));
    DumpLog::GetInstance().AddDesc(
        "longclickable: " + std::to_string(gestureEventHub ? gestureEventHub->IsAccessibilityLongClickable() : false));
    DumpLog::GetInstance().AddDesc(
        "scrollable: " + std::to_string(node->GetAccessibilityProperty<NG::AccessibilityProperty>()->IsScrollable()));
    DumpLog::GetInstance().AddDesc(
        "checked: " + std::to_string(node->GetAccessibilityProperty<NG::AccessibilityProperty>()->IsChecked()));
    DumpLog::GetInstance().AddDesc(
        "hint: " + node->GetAccessibilityProperty<NG::AccessibilityProperty>()->GetHintText());

    std::vector<int32_t> children;
    for (const auto& item : node->GetChildren()) {
        GetFrameNodeChildren(item, children, commonProperty.pageId);
    }
    DumpLog::GetInstance().Print(depth, node->GetTag(), children.size());

    for (auto nodeId : children) {
        DumpTreeNG(node, depth + 1, nodeId, commonProperty);
    }
}

void JsAccessibilityManager::DumpTree(int32_t depth, NodeId nodeID)
{
    auto pipeline = context_.Upgrade();
    CHECK_NULL_VOID(pipeline);
    if (!AceType::InstanceOf<NG::PipelineContext>(pipeline)) {
        AccessibilityNodeManager::DumpTree(depth, nodeID);
    } else {
        auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipeline);
        auto rootNode = ngPipeline->GetRootElement();
        CHECK_NULL_VOID(rootNode);
        nodeID = rootNode->GetAccessibilityId();
        auto windowLeft = GetWindowLeft(ngPipeline->GetWindowId());
        auto windowTop = GetWindowTop(ngPipeline->GetWindowId());
        auto stageManager = ngPipeline->GetStageManager();
        CHECK_NULL_VOID(stageManager);
        auto page = stageManager->GetLastPage();
        CHECK_NULL_VOID(page);
        auto pageId = page->GetPageId();
        auto pagePath = GetPagePath();
        CommonProperty commonProperty { ngPipeline->GetWindowId(), windowLeft, windowTop, pageId, pagePath };
        DumpTreeNG(rootNode, depth, nodeID, commonProperty);
        for (auto subContext : GetSubPipelineContexts()) {
            ngPipeline = AceType::DynamicCast<NG::PipelineContext>(subContext.Upgrade());
            CHECK_NULL_VOID(ngPipeline);
            rootNode = ngPipeline->GetRootElement();
            CHECK_NULL_VOID(rootNode);
            nodeID = rootNode->GetAccessibilityId();
            commonProperty.windowId = ngPipeline->GetWindowId();
            commonProperty.windowLeft = GetWindowLeft(ngPipeline->GetWindowId());
            commonProperty.windowTop = GetWindowTop(ngPipeline->GetWindowId());
            commonProperty.pageId = 0;
            commonProperty.pagePath = "";
            DumpTreeNG(rootNode, depth + 1, nodeID, commonProperty);
        }
    }
}

void JsAccessibilityManager::SetCardViewParams(const std::string& key, bool focus)
{
    LOGD("SetCardViewParams key=%{public}s  focus=%{public}d", key.c_str(), focus);
    callbackKey_ = key;
    if (!callbackKey_.empty()) {
        InitializeCallback();
    }
}

void JsAccessibilityManager::UpdateViewScale()
{
    auto context = GetPipelineContext().Upgrade();
    CHECK_NULL_VOID_NOLOG(context);
    float scaleX = 1.0;
    float scaleY = 1.0;
    if (context->GetViewScale(scaleX, scaleY)) {
        scaleX_ = scaleX;
        scaleY_ = scaleY;
    }
}

void JsAccessibilityManager::HandleComponentPostBinding()
{
    for (auto targetIter = nodeWithTargetMap_.begin(); targetIter != nodeWithTargetMap_.end();) {
        auto nodeWithTarget = targetIter->second.Upgrade();
        if (nodeWithTarget) {
            if (nodeWithTarget->GetTag() == ACCESSIBILITY_TAG_POPUP) {
                auto idNodeIter = nodeWithIdMap_.find(targetIter->first);
                if (idNodeIter != nodeWithIdMap_.end()) {
                    auto nodeWithId = idNodeIter->second.Upgrade();
                    if (nodeWithId) {
                        nodeWithId->SetAccessibilityHint(nodeWithTarget->GetText());
                    } else {
                        nodeWithIdMap_.erase(idNodeIter);
                    }
                }
            }
            ++targetIter;
        } else {
            // clear the disabled node in the maps
            nodeWithTargetMap_.erase(targetIter++);
        }
    }

    // clear the disabled node in the maps
    for (auto idItem = nodeWithIdMap_.begin(); idItem != nodeWithIdMap_.end();) {
        if (!idItem->second.Upgrade()) {
            nodeWithIdMap_.erase(idItem++);
        } else {
            ++idItem;
        }
    }
}

RefPtr<AccessibilityNodeManager> AccessibilityNodeManager::Create()
{
    return AceType::MakeRefPtr<JsAccessibilityManager>();
}

RefPtr<PipelineBase> JsAccessibilityManager::GetPipelineByWindowId(const int32_t windowId)
{
    auto context = context_.Upgrade();
    if (AceType::InstanceOf<NG::PipelineContext>(context)) {
        CHECK_NULL_RETURN_NOLOG(context, nullptr);
        if (context->GetWindowId() == static_cast<uint32_t>(windowId)) {
            return context;
        }
        for (auto& subContext : GetSubPipelineContexts()) {
            context = subContext.Upgrade();
            CHECK_NULL_RETURN_NOLOG(context, nullptr);
            if (context->GetWindowId() == static_cast<uint32_t>(windowId)) {
                return context;
            }
        }
        return nullptr;
    } else {
        return context;
    }
}

void JsAccessibilityManager::JsInteractionOperation::SearchElementInfoByAccessibilityId(const int32_t elementId,
    const int32_t requestId, AccessibilityElementOperatorCallback& callback, const int32_t mode)
{
    LOGD("elementId(%{public}d) requestId(%{public}d) mode(%{public}d)", elementId, requestId, mode);
    auto jsAccessibilityManager = GetHandler().Upgrade();
    CHECK_NULL_VOID(jsAccessibilityManager);
    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    CHECK_NULL_VOID_NOLOG(context);
    auto windowId = windowId_;
    context->GetTaskExecutor()->PostTask(
        [jsAccessibilityManager, elementId, requestId, &callback, mode, windowId]() {
            CHECK_NULL_VOID(jsAccessibilityManager);
            jsAccessibilityManager->SearchElementInfoByAccessibilityId(elementId, requestId, callback, mode, windowId);
        },
        TaskExecutor::TaskType::UI);
}

void JsAccessibilityManager::SearchElementInfoByAccessibilityId(const int32_t elementId, const int32_t requestId,
    AccessibilityElementOperatorCallback& callback, const int32_t mode, const int32_t windowId)
{
    std::list<AccessibilityElementInfo> infos;

    auto pipeline = GetPipelineByWindowId(windowId);
    if (pipeline) {
        auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipeline);
        if (ngPipeline) {
            SearchElementInfoByAccessibilityIdNG(elementId, mode, infos, pipeline);
            SetSearchElementInfoByAccessibilityIdResult(callback, infos, requestId);
            return;
        }
    }

    NodeId nodeId = elementId;
    // get root node
    if (elementId == -1) {
        nodeId = 0;
    }
    auto weak = WeakClaim(this);
    auto jsAccessibilityManager = weak.Upgrade();
    CHECK_NULL_VOID_NOLOG(jsAccessibilityManager);
    auto node = jsAccessibilityManager->GetAccessibilityNodeFromPage(nodeId);
    if (!node) {
        LOGW("AccessibilityNodeInfo can't attach component by Id = %{public}d, window:%{public}d", nodeId, windowId_);
        SetSearchElementInfoByAccessibilityIdResult(callback, infos, requestId);
        return;
    }

    AccessibilityElementInfo nodeInfo;
    UpdateAccessibilityNodeInfo(node, nodeInfo, jsAccessibilityManager, jsAccessibilityManager->windowId_);
    infos.push_back(nodeInfo);
    // cache parent/siblings/children infos
    UpdateCacheInfo(infos, mode, node, jsAccessibilityManager, jsAccessibilityManager->windowId_);

    SetSearchElementInfoByAccessibilityIdResult(callback, infos, requestId);
    LOGD("requestId(%{public}d)", requestId);
}

void JsAccessibilityManager::SearchElementInfoByAccessibilityIdNG(
    int32_t elementId, int32_t mode, std::list<AccessibilityElementInfo>& infos, const RefPtr<PipelineBase>& context)
{
    auto mainContext = context_.Upgrade();
    CHECK_NULL_VOID(mainContext);

    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(context);
    CHECK_NULL_VOID(ngPipeline);
    auto rootNode = ngPipeline->GetRootElement();
    CHECK_NULL_VOID(rootNode);

    AccessibilityElementInfo nodeInfo;
    NodeId nodeId = elementId;
    // accessibility use -1 for first search to get root node
    if (elementId == -1) {
        nodeId = rootNode->GetAccessibilityId();
    }

    auto node = GetInspectorById(rootNode, nodeId);
    CHECK_NULL_VOID(node);
    int32_t pageId = 0;
    std::string pagePath;
    if (context->GetWindowId() == mainContext->GetWindowId()) {
        auto stageManager = ngPipeline->GetStageManager();
        CHECK_NULL_VOID(stageManager);
        auto page = stageManager->GetLastPage();
        CHECK_NULL_VOID(page);
        pageId = page->GetPageId();
        pagePath = GetPagePath();
    }
    CommonProperty commonProperty { ngPipeline->GetWindowId(), GetWindowLeft(ngPipeline->GetWindowId()),
        GetWindowTop(ngPipeline->GetWindowId()), pageId, pagePath };
    UpdateAccessibilityElementInfo(node, commonProperty, nodeInfo, ngPipeline);

    infos.push_back(nodeInfo);
}

void JsAccessibilityManager::SearchElementInfosByTextNG(int32_t elementId, const std::string& text,
    std::list<Accessibility::AccessibilityElementInfo>& infos, const RefPtr<PipelineBase>& context)
{
    auto mainContext = context_.Upgrade();
    CHECK_NULL_VOID(mainContext);

    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(context);
    CHECK_NULL_VOID(ngPipeline);
    auto rootNode = ngPipeline->GetRootElement();
    CHECK_NULL_VOID(rootNode);

    auto node = GetInspectorById(rootNode, elementId);
    CHECK_NULL_VOID(node);
    std::list<RefPtr<NG::FrameNode>> results;
    FindText(node, text, results);
    if (results.empty()) {
        return;
    }
    int32_t pageId = 0;
    std::string pagePath;
    if (context->GetWindowId() == mainContext->GetWindowId()) {
        auto stageManager = ngPipeline->GetStageManager();
        CHECK_NULL_VOID(stageManager);
        auto page = stageManager->GetLastPage();
        CHECK_NULL_VOID(page);
        pageId = page->GetPageId();
        pagePath = GetPagePath();
    }
    CommonProperty commonProperty { ngPipeline->GetWindowId(), GetWindowLeft(ngPipeline->GetWindowId()),
        GetWindowTop(ngPipeline->GetWindowId()), pageId, pagePath };
    for (const auto& node : results) {
        AccessibilityElementInfo nodeInfo;
        UpdateAccessibilityElementInfo(node, commonProperty, nodeInfo, ngPipeline);
        infos.emplace_back(nodeInfo);
    }
}

void JsAccessibilityManager::JsInteractionOperation::SearchElementInfosByText(const int32_t elementId,
    const std::string& text, const int32_t requestId, AccessibilityElementOperatorCallback& callback)
{
    LOGI("elementId(%{public}d) text(%{public}s)", elementId, text.c_str());
    if (text.empty()) {
        LOGW("Text is null");
        return;
    }
    auto jsAccessibilityManager = GetHandler().Upgrade();
    CHECK_NULL_VOID_NOLOG(jsAccessibilityManager);
    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    CHECK_NULL_VOID_NOLOG(context);
    auto windowId = windowId_;
    if (context) {
        context->GetTaskExecutor()->PostTask(
            [jsAccessibilityManager, elementId, text, requestId, &callback, windowId]() {
                CHECK_NULL_VOID_NOLOG(jsAccessibilityManager);
                jsAccessibilityManager->SearchElementInfosByText(elementId, text, requestId, callback, windowId);
            },
            TaskExecutor::TaskType::UI);
    }
}

void JsAccessibilityManager::SearchElementInfosByText(const int32_t elementId, const std::string& text,
    const int32_t requestId, AccessibilityElementOperatorCallback& callback, const int32_t windowId)
{
    if (text.empty()) {
        LOGW("Text is null");
        return;
    }

    if (elementId == -1) {
        return;
    }

    std::list<AccessibilityElementInfo> infos;

    auto pipeline = GetPipelineByWindowId(windowId);
    if (pipeline) {
        if (AceType::InstanceOf<NG::PipelineContext>(pipeline)) {
            SearchElementInfosByTextNG(elementId, text, infos, pipeline);
            SetSearchElementInfoByTextResult(callback, infos, requestId);
            return;
        }
    }

    auto weak = WeakClaim(this);
    auto jsAccessibilityManager = weak.Upgrade();
    CHECK_NULL_VOID_NOLOG(jsAccessibilityManager);
    NodeId nodeId = elementId;
    auto node = jsAccessibilityManager->GetAccessibilityNodeFromPage(nodeId);
    CHECK_NULL_VOID_NOLOG(node);
    std::list<RefPtr<AccessibilityNode>> nodeList;
    FindText(node, text, nodeList);
    if (!nodeList.empty()) {
        for (const auto& node : nodeList) {
            LOGI(" FindText end nodeId:%{public}d", node->GetNodeId());
            AccessibilityElementInfo nodeInfo;
            UpdateAccessibilityNodeInfo(node, nodeInfo, jsAccessibilityManager, jsAccessibilityManager->windowId_);
            infos.emplace_back(nodeInfo);
        }
    }

    LOGI("SetSearchElementInfoByTextResult infos.size(%{public}zu)", infos.size());
    SetSearchElementInfoByTextResult(callback, infos, requestId);
}

void JsAccessibilityManager::JsInteractionOperation::FindFocusedElementInfo(const int32_t elementId,
    const int32_t focusType, const int32_t requestId, AccessibilityElementOperatorCallback& callback)
{
    LOGI("elementId(%{public}d) focusType(%{public}d)", elementId, focusType);
    auto jsAccessibilityManager = GetHandler().Upgrade();
    CHECK_NULL_VOID_NOLOG(jsAccessibilityManager);
    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    CHECK_NULL_VOID_NOLOG(context);
    auto windowId = windowId_;
    context->GetTaskExecutor()->PostTask(
        [jsAccessibilityManager, elementId, focusType, requestId, &callback, windowId]() {
            CHECK_NULL_VOID_NOLOG(jsAccessibilityManager);
            jsAccessibilityManager->FindFocusedElementInfo(elementId, focusType, requestId, callback, windowId);
        },
        TaskExecutor::TaskType::UI);
}

void JsAccessibilityManager::FindFocusedElementInfo(const int32_t elementId, const int32_t focusType,
    const int32_t requestId, AccessibilityElementOperatorCallback& callback, const int32_t windowId)
{
    AccessibilityElementInfo nodeInfo;
    if (focusType != FOCUS_TYPE_INPUT && focusType != FOCUS_TYPE_ACCESSIBILITY) {
        nodeInfo.SetValidElement(false);
        SetFindFocusedElementInfoResult(callback, nodeInfo, requestId);
        return;
    }

    auto context = GetPipelineByWindowId(windowId);
    if (!context) {
        SetFindFocusedElementInfoResult(callback, nodeInfo, requestId);
        return;
    }

    if (AceType::InstanceOf<NG::PipelineContext>(context)) {
        FindFocusedElementInfoNG(elementId, focusType, nodeInfo, context);
        SetFindFocusedElementInfoResult(callback, nodeInfo, requestId);
        return;
    }

    NodeId nodeId = static_cast<NodeId>(elementId);
    if (elementId == -1) {
        nodeId = 0;
    }

    auto node = GetAccessibilityNodeFromPage(nodeId);
    if (!node) {
        nodeInfo.SetValidElement(false);
        SetFindFocusedElementInfoResult(callback, nodeInfo, requestId);
        return;
    }

    RefPtr<AccessibilityNode> resultNode = nullptr;
    bool status = false;
    if (focusType == FOCUS_TYPE_ACCESSIBILITY) {
        status = FindAccessibilityFocus(node, resultNode);
    }
    if (focusType == FOCUS_TYPE_INPUT) {
        status = FindInputFocus(node, resultNode);
    }

    LOGI("FindFocus status(%{public}d)", status);
    if ((status) && (resultNode != nullptr)) {
        LOGI("FindFocus nodeId:%{public}d", resultNode->GetNodeId());
        UpdateAccessibilityNodeInfo(resultNode, nodeInfo, Claim(this), windowId_);
    }

    SetFindFocusedElementInfoResult(callback, nodeInfo, requestId);
}

void JsAccessibilityManager::FindFocusedElementInfoNG(int32_t elementId, int32_t focusType,
    Accessibility::AccessibilityElementInfo& info, const RefPtr<PipelineBase>& context)
{
    auto mainContext = context_.Upgrade();
    CHECK_NULL_VOID(mainContext);

    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(context);
    CHECK_NULL_VOID(ngPipeline);
    auto rootNode = ngPipeline->GetRootElement();
    CHECK_NULL_VOID(rootNode);

    NodeId nodeId = elementId;
    // accessibility use -1 for first search to get root node
    if (elementId == -1) {
        nodeId = rootNode->GetAccessibilityId();
    }

    auto node = GetInspectorById(rootNode, nodeId);
    if (!node) {
        info.SetValidElement(false);
        return;
    }
    RefPtr<NG::FrameNode> resultNode;
    if (focusType == FOCUS_TYPE_ACCESSIBILITY) {
        resultNode = FindAccessibilityFocus(node);
    }
    if (focusType == FOCUS_TYPE_INPUT) {
        resultNode = FindInputFocus(node);
    }
    CHECK_NULL_VOID_NOLOG(resultNode);
    int32_t pageId = 0;
    std::string pagePath;
    if (context->GetWindowId() == mainContext->GetWindowId()) {
        auto stageManager = ngPipeline->GetStageManager();
        CHECK_NULL_VOID(stageManager);
        auto page = stageManager->GetLastPage();
        CHECK_NULL_VOID(page);
        pageId = page->GetPageId();
        pagePath = GetPagePath();
    }
    CommonProperty commonProperty { ngPipeline->GetWindowId(), GetWindowLeft(ngPipeline->GetWindowId()),
        GetWindowTop(ngPipeline->GetWindowId()), pageId, pagePath };
    UpdateAccessibilityElementInfo(resultNode, commonProperty, info, ngPipeline);
}

RefPtr<NG::FrameNode> JsAccessibilityManager::FindNodeFromPipeline(
    const WeakPtr<PipelineBase>& context, const int32_t elementId)
{
    auto pipeline = context.Upgrade();
    CHECK_NULL_RETURN(pipeline, nullptr);

    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    auto rootNode = ngPipeline->GetRootElement();
    CHECK_NULL_RETURN(rootNode, nullptr);

    NodeId nodeId = elementId;
    // accessibility use -1 for first search to get root node
    if (elementId == -1) {
        nodeId = rootNode->GetAccessibilityId();
    }

    RefPtr<NG::FrameNode> node = GetInspectorById(rootNode, nodeId);
    if (node) {
        return node;
    }
    return nullptr;
}

RefPtr<NG::PipelineContext> JsAccessibilityManager::FindPipelineByElementId(
    const int32_t elementId, RefPtr<NG::FrameNode>& node)
{
    node = FindNodeFromPipeline(context_, elementId);
    if (node) {
        auto context = AceType::DynamicCast<NG::PipelineContext>(context_.Upgrade());
        return context;
    }
    for (auto subContext : GetSubPipelineContexts()) {
        node = FindNodeFromPipeline(subContext, elementId);
        if (node) {
            auto context = AceType::DynamicCast<NG::PipelineContext>(subContext.Upgrade());
            return context;
        }
    }
    return nullptr;
}

void JsAccessibilityManager::JsInteractionOperation::ExecuteAction(const int32_t elementId, const int32_t action,
    const std::map<std::string, std::string>& actionArguments, const int32_t requestId,
    AccessibilityElementOperatorCallback& callback)
{
    LOGI("id:%{public}d, action:%{public}d, request:%{public}d.", elementId, action, requestId);
    auto jsAccessibilityManager = GetHandler().Upgrade();
    CHECK_NULL_VOID_NOLOG(jsAccessibilityManager);
    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    CHECK_NULL_VOID_NOLOG(context);
    auto actionInfo = static_cast<ActionType>(action);
    ActionParam param { actionInfo, actionArguments };
    auto windowId = windowId_;
    context->GetTaskExecutor()->PostTask(
        [jsAccessibilityManager, elementId, param, requestId, &callback, windowId] {
            CHECK_NULL_VOID_NOLOG(jsAccessibilityManager);
            jsAccessibilityManager->ExecuteAction(elementId, param, requestId, callback, windowId);
        },
        TaskExecutor::TaskType::UI);
}

bool JsAccessibilityManager::AccessibilityActionEvent(const ActionType& action,
    const std::map<std::string, std::string> actionArguments, const RefPtr<AccessibilityNode>& node,
    const RefPtr<PipelineContext>& context)
{
    if (!node || !context) {
        return false;
    }
    ContainerScope scope(context->GetInstanceId());
    switch (action) {
        case ActionType::ACCESSIBILITY_ACTION_CLICK: {
            node->SetClicked(true);
            if (!node->GetClickEventMarker().IsEmpty()) {
#ifndef NG_BUILD
                context->SendEventToFrontend(node->GetClickEventMarker());
#endif
                node->ActionClick();
                return true;
            }
            return node->ActionClick();
        }
        case ActionType::ACCESSIBILITY_ACTION_LONG_CLICK: {
            if (!node->GetLongPressEventMarker().IsEmpty()) {
#ifndef NG_BUILD
                context->SendEventToFrontend(node->GetLongPressEventMarker());
#endif
                node->ActionLongClick();
                return true;
            }
            return node->ActionLongClick();
        }
        case ActionType::ACCESSIBILITY_ACTION_SET_TEXT: {
            if (!node->GetSetTextEventMarker().IsEmpty()) {
#ifndef NG_BUILD
                context->SendEventToFrontend(node->GetSetTextEventMarker());
#endif
                node->ActionSetText(actionArguments.find(ACTION_ARGU_SET_TEXT)->second);
                return true;
            }
            return node->ActionSetText(actionArguments.find(ACTION_ARGU_SET_TEXT)->second);
        }
        case ActionType::ACCESSIBILITY_ACTION_FOCUS: {
#ifndef NG_BUILD
            context->AccessibilityRequestFocus(std::to_string(node->GetNodeId()));
#endif
            if (!node->GetFocusEventMarker().IsEmpty()) {
#ifndef NG_BUILD
                context->SendEventToFrontend(node->GetFocusEventMarker());
#endif
                node->ActionFocus();
                return true;
            }
            return node->ActionFocus();
        }
        case ActionType::ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS: {
            return RequestAccessibilityFocus(node);
        }
        case ActionType::ACCESSIBILITY_ACTION_CLEAR_ACCESSIBILITY_FOCUS: {
            return ClearAccessibilityFocus(node);
        }
        case ActionType::ACCESSIBILITY_ACTION_SCROLL_FORWARD:
            return node->ActionScrollForward();
        case ActionType::ACCESSIBILITY_ACTION_SCROLL_BACKWARD:
            return node->ActionScrollBackward();
        default:
            return false;
    }
}

void JsAccessibilityManager::SendActionEvent(const Accessibility::ActionType& action, NodeId nodeId)
{
    static std::unordered_map<Accessibility::ActionType, std::string> actionToStr {
        { Accessibility::ActionType::ACCESSIBILITY_ACTION_CLICK, DOM_CLICK },
        { Accessibility::ActionType::ACCESSIBILITY_ACTION_LONG_CLICK, DOM_LONG_PRESS },
        { Accessibility::ActionType::ACCESSIBILITY_ACTION_FOCUS, DOM_FOCUS },
        { Accessibility::ActionType::ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS, ACCESSIBILITY_FOCUSED_EVENT },
        { Accessibility::ActionType::ACCESSIBILITY_ACTION_CLEAR_ACCESSIBILITY_FOCUS, ACCESSIBILITY_CLEAR_FOCUS_EVENT },
        { Accessibility::ActionType::ACCESSIBILITY_ACTION_SCROLL_FORWARD, SCROLL_END_EVENT },
        { Accessibility::ActionType::ACCESSIBILITY_ACTION_SCROLL_BACKWARD, SCROLL_END_EVENT },
    };
    if (actionToStr.find(action) == actionToStr.end()) {
        return;
    }
    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.eventType = actionToStr[action];
    accessibilityEvent.nodeId = static_cast<int>(nodeId);
    SendAccessibilityAsyncEvent(accessibilityEvent);
}

bool ActAccessibilityAction(Accessibility::ActionType action, const std::map<std::string, std::string> actionArguments,
    RefPtr<NG::AccessibilityProperty> accessibilityProperty)
{
    AccessibilityActionParam param;
    if (action == ActionType::ACCESSIBILITY_ACTION_SET_SELECTION) {
        int start = -1;
        int end = -1;
        auto iter = actionArguments.find(ACTION_ARGU_SELECT_TEXT_START);
        if (iter != actionArguments.end()) {
            std::stringstream str_start;
            str_start << iter->second;
            str_start >> start;
        }
        iter = actionArguments.find(ACTION_ARGU_SELECT_TEXT_END);
        if (iter != actionArguments.end()) {
            std::stringstream str_end;
            str_end << iter->second;
            str_end >> end;
        }
        param.setSelectionStart = start;
        param.setSelectionEnd = end;
    }
    if (action == ActionType::ACCESSIBILITY_ACTION_SET_TEXT) {
        auto iter = actionArguments.find(ACTION_ARGU_SET_TEXT);
        if (iter != actionArguments.end()) {
            param.setTextArgument = iter->second;
        }
    }
    if (action == ActionType::ACCESSIBILITY_ACTION_NEXT_TEXT ||
        action == ActionType::ACCESSIBILITY_ACTION_PREVIOUS_TEXT) {
        int moveUnit = TextMoveUnit::STEP_CHARACTER;
        auto iter = actionArguments.find(ACTION_ARGU_MOVE_UNIT);
        if (iter != actionArguments.end()) {
            std::stringstream str_moveUnit;
            str_moveUnit << iter->second;
            str_moveUnit >> moveUnit;
        }
        param.moveUnit = static_cast<TextMoveUnit>(moveUnit);
    }
    auto accessibiltyAction = ACTIONS.find(action);
    if (accessibiltyAction != ACTIONS.end()) {
        param.accessibilityProperty = accessibilityProperty;
        return accessibiltyAction->second(param);
    }
    return false;
}

bool JsAccessibilityManager::ExecuteActionNG(int32_t elementId,
    const std::map<std::string, std::string>& actionArguments, ActionType action, const RefPtr<PipelineBase>& context)
{
    bool result = false;
    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(context);
    CHECK_NULL_RETURN(ngPipeline, result);
    ContainerScope instance(ngPipeline->GetInstanceId());
    auto frameNode = GetInspectorById(ngPipeline->GetRootElement(), elementId);
    CHECK_NULL_RETURN(frameNode, result);
    auto enabled = frameNode->GetFocusHub() ? frameNode->GetFocusHub()->IsEnabled() : true;
    if (!enabled) {
        return result;
    }

    switch (action) {
        case ActionType::ACCESSIBILITY_ACTION_FOCUS: {
            result = RequestFocus(frameNode);
            break;
        }
        case ActionType::ACCESSIBILITY_ACTION_CLEAR_FOCUS: {
            result = LostFocus(frameNode);
            break;
        }
        case ActionType::ACCESSIBILITY_ACTION_CLICK: {
            result = ActClick(frameNode);
            break;
        }
        case ActionType::ACCESSIBILITY_ACTION_LONG_CLICK: {
            result = ActLongClick(frameNode);
            break;
        }
        case ActionType::ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS: {
            result = ActAccessibilityFocus(elementId, frameNode, ngPipeline, currentFocusNodeId_, false);
            break;
        }
        case ActionType::ACCESSIBILITY_ACTION_CLEAR_ACCESSIBILITY_FOCUS: {
            result = ActAccessibilityFocus(elementId, frameNode, ngPipeline, currentFocusNodeId_, true);
            break;
        }
        default:
            break;
    }
    if (!result) {
        auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
        CHECK_NULL_RETURN(accessibilityProperty, false);
        result = ActAccessibilityAction(action, actionArguments, accessibilityProperty);
    }
    return result;
}

void JsAccessibilityManager::ExecuteAction(const int32_t elementId, const ActionParam& param, const int32_t requestId,
    AccessibilityElementOperatorCallback& callback, const int32_t windowId)
{
    auto action = param.action;
    auto actionArguments = param.actionArguments;
    LOGI("ExecuteAction elementId:%{public}d action:%{public}d", elementId, action);

    bool actionResult = false;
    auto context = GetPipelineByWindowId(windowId);
    if (!context) {
        SetExecuteActionResult(callback, actionResult, requestId);
        return;
    }

    if (AceType::InstanceOf<NG::PipelineContext>(context)) {
        actionResult = ExecuteActionNG(elementId, actionArguments, action, context);
    } else {
        auto node = GetAccessibilityNodeFromPage(elementId);
        if (!node) {
            LOGW("AccessibilityNodeInfo can't attach component by Id = %{public}d", elementId);
            SetExecuteActionResult(callback, false, requestId);
            return;
        }

        actionResult =
            AccessibilityActionEvent(action, actionArguments, node, AceType::DynamicCast<PipelineContext>(context));
    }
    LOGI("SetExecuteActionResult actionResult= %{public}d", actionResult);
    SetExecuteActionResult(callback, actionResult, requestId);
    if (actionResult && AceType::InstanceOf<PipelineContext>(context)) {
        SendActionEvent(action, elementId);
    }
}

void JsAccessibilityManager::JsInteractionOperation::ClearFocus()
{
    LOGI("ClearFocus");
    auto jsAccessibilityManager = GetHandler().Upgrade();
    CHECK_NULL_VOID_NOLOG(jsAccessibilityManager);
    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    CHECK_NULL_VOID_NOLOG(context);
    context->GetTaskExecutor()->PostTask(
        [jsAccessibilityManager] {
            if (!jsAccessibilityManager) {
                return;
            }
            jsAccessibilityManager->ClearCurrentFocus();
        },
        TaskExecutor::TaskType::UI);
}

void JsAccessibilityManager::JsInteractionOperation::OutsideTouch() {}

bool JsAccessibilityManager::IsRegister()
{
    return isReg_;
}

void JsAccessibilityManager::Register(bool state)
{
    isReg_ = state;
}

int JsAccessibilityManager::RegisterInteractionOperation(int windowId)
{
    LOGI("RegisterInteractionOperation windowId:%{public}d", windowId);
    if (IsRegister()) {
        return 0;
    }

    std::shared_ptr<AccessibilitySystemAbilityClient> instance = AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_RETURN_NOLOG(instance, -1);
    auto interactionOperation = std::make_shared<JsInteractionOperation>(windowId);
    interactionOperation->SetHandler(WeakClaim(this));
    Accessibility::RetError retReg = instance->RegisterElementOperator(windowId, interactionOperation);
    RefPtr<PipelineBase> context;
    for (auto subContext : GetSubPipelineContexts()) {
        context = subContext.Upgrade();
        CHECK_NULL_RETURN_NOLOG(context, -1);
        interactionOperation = std::make_shared<JsInteractionOperation>(context->GetWindowId());
        interactionOperation->SetHandler(WeakClaim(this));
        retReg = instance->RegisterElementOperator(context->GetWindowId(), interactionOperation);
    }
    LOGI("RegisterInteractionOperation end windowId:%{public}d, ret:%{public}d", windowId, retReg);
    Register(retReg == RET_OK);

    return retReg;
}

void JsAccessibilityManager::RegisterSubWindowInteractionOperation(int windowId)
{
    if (!AceApplicationInfo::GetInstance().IsAccessibilityEnabled() || !IsRegister()) {
        return;
    }

    std::shared_ptr<AccessibilitySystemAbilityClient> instance = AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_VOID_NOLOG(instance);
    auto interactionOperation = std::make_shared<JsInteractionOperation>(windowId);
    interactionOperation->SetHandler(WeakClaim(this));
    Accessibility::RetError retReg = instance->RegisterElementOperator(windowId, interactionOperation);
    if (!retReg) {
        LOGE("RegisterInteractionOperation failed, windowId:%{public}d, ret:%{public}d", windowId, retReg);
    }
}

void JsAccessibilityManager::DeregisterInteractionOperation()
{
    if (!IsRegister()) {
        return;
    }
    int windowId = GetWindowId();

    auto instance = AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_VOID_NOLOG(instance);
    Register(false);
    currentFocusNodeId_ = -1;
    LOGI("DeregisterInteractionOperation windowId:%{public}d", windowId);
    instance->DeregisterElementOperator(windowId);
    RefPtr<PipelineBase> context;
    for (auto subContext : GetSubPipelineContexts()) {
        context = subContext.Upgrade();
        CHECK_NULL_VOID_NOLOG(context);
        instance->DeregisterElementOperator(context->GetWindowId());
    }
}

void JsAccessibilityManager::JsAccessibilityStateObserver::OnStateChanged(const bool state)
{
    LOGI("accessibility state changed:%{public}d", state);
    auto jsAccessibilityManager = GetHandler().Upgrade();
    CHECK_NULL_VOID_NOLOG(jsAccessibilityManager);
    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    CHECK_NULL_VOID_NOLOG(context);
    context->GetTaskExecutor()->PostTask(
        [jsAccessibilityManager, state]() {
            if (state) {
                jsAccessibilityManager->RegisterInteractionOperation(jsAccessibilityManager->GetWindowId());
            } else {
                jsAccessibilityManager->DeregisterInteractionOperation();
            }
            AceApplicationInfo::GetInstance().SetAccessibilityEnabled(state);
        },
        TaskExecutor::TaskType::UI);
}

void JsAccessibilityManager::JsInteractionOperation::FocusMoveSearch(
    int32_t elementId, const int32_t direction, const int32_t requestId, AccessibilityElementOperatorCallback& callback)
{
    LOGI("elementId:%{public}d,direction:%{public}d,requestId:%{public}d", elementId, direction, requestId);
    auto jsAccessibilityManager = GetHandler().Upgrade();
    CHECK_NULL_VOID_NOLOG(jsAccessibilityManager);
    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    CHECK_NULL_VOID_NOLOG(context);
    auto windowId = windowId_;
    context->GetTaskExecutor()->PostTask(
        [jsAccessibilityManager, elementId, direction, requestId, &callback, windowId] {
            CHECK_NULL_VOID_NOLOG(jsAccessibilityManager);
            jsAccessibilityManager->FocusMoveSearch(elementId, direction, requestId, callback, windowId);
        },
        TaskExecutor::TaskType::UI);
}

void JsAccessibilityManager::FocusMoveSearch(const int32_t elementId, const int32_t direction, const int32_t requestId,
    Accessibility::AccessibilityElementOperatorCallback& callback, const int32_t windowId)
{
    AccessibilityElementInfo nodeInfo;
    auto context = GetPipelineByWindowId(windowId);
    if (!context) {
        LOGI("FocusMoveSearch context is null");
        nodeInfo.SetValidElement(false);
        SetFocusMoveSearchResult(callback, nodeInfo, requestId);
        return;
    }

    if (AceType::InstanceOf<NG::PipelineContext>(context)) {
        FocusMoveSearchNG(elementId, direction, nodeInfo, context);
        SetFocusMoveSearchResult(callback, nodeInfo, requestId);
        return;
    }

    auto node = GetAccessibilityNodeFromPage(elementId);
    if (!node) {
        LOGW("AccessibilityNodeInfo can't attach component by Id = %{public}d", (NodeId)elementId);
        nodeInfo.SetValidElement(false);
        SetFocusMoveSearchResult(callback, nodeInfo, requestId);
        return;
    }

    // get root node.
    auto rootNode = node;
    while (rootNode->GetParentNode()) {
        rootNode = rootNode->GetParentNode();
        if (!rootNode->GetParentNode()) {
            break;
        }
    }

    std::list<RefPtr<AccessibilityNode>> nodeList;
    AddFocusableNode(nodeList, rootNode);
    RefPtr<AccessibilityNode> resultNode;

    switch (direction) {
        case FocusMoveDirection::FORWARD:
        case FocusMoveDirection::BACKWARD:
            // forward and backward
            resultNode = FindNodeInRelativeDirection(nodeList, node, direction);
            break;
        case FocusMoveDirection::UP:
        case FocusMoveDirection::DOWN:
        case FocusMoveDirection::LEFT:
        case FocusMoveDirection::RIGHT:
            // up, down, left and right
            resultNode = FindNodeInAbsoluteDirection(nodeList, node, direction);
            break;
        default:
            break;
    }

    if (resultNode) {
        LOGI("FocusMoveSearch end nodeId:%{public}d", resultNode->GetNodeId());
        auto jsAccessibilityManager = Claim(this);
        UpdateAccessibilityNodeInfo(resultNode, nodeInfo, jsAccessibilityManager, windowId_);
    }

    SetFocusMoveSearchResult(callback, nodeInfo, requestId);
}

void JsAccessibilityManager::AddFocusableNode(
    std::list<RefPtr<AccessibilityNode>>& nodeList, const RefPtr<AccessibilityNode>& node)
{
    const std::string importance = node->GetImportantForAccessibility();
    if (CanAccessibilityFocused(node)) {
        nodeList.push_back(node);
    }
    if (!node->GetAccessible() && importance != "no-hide-descendants") {
        for (auto& child : node->GetChildList()) {
            AddFocusableNode(nodeList, child);
        }
    }
}

bool JsAccessibilityManager::CanAccessibilityFocused(const RefPtr<AccessibilityNode>& node)
{
    return node != nullptr && !node->IsRootNode() && node->GetVisible() &&
           node->GetImportantForAccessibility() != "no" &&
           node->GetImportantForAccessibility() != "no-hide-descendants";
}

RefPtr<AccessibilityNode> JsAccessibilityManager::FindNodeInRelativeDirection(
    const std::list<RefPtr<AccessibilityNode>>& nodeList, RefPtr<AccessibilityNode>& node, const int direction)
{
    switch (direction) {
        case FocusMoveDirection::FORWARD:
            return GetNextFocusableNode(nodeList, node);
        case FocusMoveDirection::BACKWARD:
            return GetPreviousFocusableNode(nodeList, node);
        default:
            break;
    }

    return nullptr;
}

RefPtr<AccessibilityNode> JsAccessibilityManager::FindNodeInAbsoluteDirection(
    const std::list<RefPtr<AccessibilityNode>>& nodeList, RefPtr<AccessibilityNode>& node, const int direction)
{
    LOGI("FindNodeInAbsoluteDirection");
    auto tempBest = node->GetRect();
    auto nodeRect = node->GetRect();

    switch (direction) {
        case FocusMoveDirection::LEFT:
            tempBest.SetLeft(node->GetLeft() + node->GetWidth() + 1);
            break;
        case FocusMoveDirection::RIGHT:
            tempBest.SetLeft(node->GetLeft() - node->GetWidth() - 1);
            break;
        case FocusMoveDirection::UP:
            tempBest.SetTop(node->GetTop() + node->GetHeight() + 1);
            break;
        case FocusMoveDirection::DOWN:
            tempBest.SetTop(node->GetTop() - node->GetHeight() - 1);
            break;
        default:
            break;
    }

    RefPtr<AccessibilityNode> nearestNode = nullptr;
    for (auto nodeItem = nodeList.begin(); nodeItem != nodeList.end(); nodeItem++) {
        if ((*nodeItem)->GetNodeId() == node->GetNodeId() || (*nodeItem)->IsRootNode()) {
            continue;
        }
        auto itemRect = (*nodeItem)->GetRect();
        if (CheckBetterRect(nodeRect, direction, itemRect, tempBest)) {
            tempBest = itemRect;
            nearestNode = (*nodeItem);
        }
    }

    return nearestNode;
}

RefPtr<AccessibilityNode> JsAccessibilityManager::GetNextFocusableNode(
    const std::list<RefPtr<AccessibilityNode>>& nodeList, RefPtr<AccessibilityNode>& node)
{
    LOGI("GetNextFocusableNode");
    auto nodeItem = nodeList.begin();
    for (; nodeItem != nodeList.end(); nodeItem++) {
        if ((*nodeItem)->GetNodeId() == node->GetNodeId()) {
            break;
        }
    }

    if (nodeItem != nodeList.end() && ++nodeItem != nodeList.end()) {
        return (*nodeItem);
    }
    if (!nodeList.empty()) {
        return (*nodeList.begin());
    }

    return nullptr;
}

RefPtr<AccessibilityNode> JsAccessibilityManager::GetPreviousFocusableNode(
    const std::list<RefPtr<AccessibilityNode>>& nodeList, RefPtr<AccessibilityNode>& node)
{
    LOGI("GetPreviousFocusableNode");
    auto nodeItem = nodeList.rbegin();
    for (; nodeItem != nodeList.rend(); nodeItem++) {
        if ((*nodeItem)->GetNodeId() == node->GetNodeId()) {
            break;
        }
    }

    if (nodeItem != nodeList.rend() && ++nodeItem != nodeList.rend()) {
        return (*nodeItem);
    }

    if (!nodeList.empty()) {
        return (*nodeList.rbegin());
    }
    return nullptr;
}

bool JsAccessibilityManager::RequestAccessibilityFocus(const RefPtr<AccessibilityNode>& node)
{
    LOGI("RequestAccessibilityFocus");
    auto requestNodeId = node->GetNodeId();
    if (currentFocusNodeId_ == requestNodeId) {
        LOGW("This node is focused.");
        return false;
    }

    ClearCurrentFocus();
    currentFocusNodeId_ = requestNodeId;
    node->SetAccessibilityFocusedState(true);
    LOGI("RequestAccessibilityFocus SetFocusedState true nodeId:%{public}d", node->GetNodeId());
    return node->ActionAccessibilityFocus(true);
}

bool JsAccessibilityManager::ClearAccessibilityFocus(const RefPtr<AccessibilityNode>& node)
{
    LOGI("ClearAccessibilityFocus");
    auto requestNodeId = node->GetNodeId();
    if (currentFocusNodeId_ != requestNodeId) {
        LOGW("This node is not focused.");
        return false;
    }

    currentFocusNodeId_ = -1;
    node->SetAccessibilityFocusedState(false);
    return node->ActionAccessibilityFocus(false);
}

bool JsAccessibilityManager::ClearCurrentFocus()
{
    LOGI("ClearCurrentFocus");
    auto currentFocusNode = GetAccessibilityNodeFromPage(currentFocusNodeId_);
    CHECK_NULL_RETURN_NOLOG(currentFocusNode, false);
    currentFocusNodeId_ = -1;
    currentFocusNode->SetFocusedState(false);
    currentFocusNode->SetAccessibilityFocusedState(false);
    LOGI("ClearCurrentFocus SetFocusedState false nodeId:%{public}d", currentFocusNode->GetNodeId());
    return currentFocusNode->ActionAccessibilityFocus(false);
}

void JsAccessibilityManager::FocusMoveSearchNG(int32_t elementId, int32_t direction,
    Accessibility::AccessibilityElementInfo& info, const RefPtr<PipelineBase>& context)
{
    auto mainContext = context_.Upgrade();
    CHECK_NULL_VOID(mainContext);

    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(context);
    CHECK_NULL_VOID(ngPipeline);
    auto rootNode = ngPipeline->GetRootElement();
    CHECK_NULL_VOID(rootNode);

    auto node = GetInspectorById(rootNode, elementId);
    if (!node) {
        info.SetValidElement(false);
        return;
    }
    std::list<RefPtr<NG::FrameNode>> nodeList;
    Framework::AddFocusableNode(nodeList, rootNode);

    RefPtr<NG::FrameNode> resultNode;
    switch (direction) {
        case FocusMoveDirection::FORWARD:
        case FocusMoveDirection::BACKWARD:
            resultNode = Framework::FindNodeInRelativeDirection(nodeList, node, direction);
            break;
        case FocusMoveDirection::UP:
        case FocusMoveDirection::DOWN:
        case FocusMoveDirection::LEFT:
        case FocusMoveDirection::RIGHT:
            resultNode = Framework::FindNodeInAbsoluteDirection(nodeList, node, direction);
            break;
        default:
            break;
    }

    CHECK_NULL_VOID_NOLOG(resultNode);
    int32_t pageId = 0;
    std::string pagePath;
    if (context->GetWindowId() == mainContext->GetWindowId()) {
        auto stageManager = ngPipeline->GetStageManager();
        CHECK_NULL_VOID(stageManager);
        auto page = stageManager->GetLastPage();
        CHECK_NULL_VOID(page);
        pageId = page->GetPageId();
        pagePath = GetPagePath();
    }
    CommonProperty commonProperty { ngPipeline->GetWindowId(), GetWindowLeft(ngPipeline->GetWindowId()),
        GetWindowTop(ngPipeline->GetWindowId()), pageId, pagePath };
    UpdateAccessibilityElementInfo(resultNode, commonProperty, info, ngPipeline);
}

// AccessibilitySystemAbilityClient will release callback after DeregisterElementOperator
void JsAccessibilityManager::SetSearchElementInfoByAccessibilityIdResult(AccessibilityElementOperatorCallback& callback,
    const std::list<AccessibilityElementInfo>& infos, const int32_t requestId)
{
    if (IsRegister()) {
        callback.SetSearchElementInfoByAccessibilityIdResult(infos, requestId);
    }
}

void JsAccessibilityManager::SetSearchElementInfoByTextResult(AccessibilityElementOperatorCallback& callback,
    const std::list<AccessibilityElementInfo>& infos, const int32_t requestId)
{
    if (IsRegister()) {
        callback.SetSearchElementInfoByTextResult(infos, requestId);
    }
}

void JsAccessibilityManager::SetFindFocusedElementInfoResult(
    AccessibilityElementOperatorCallback& callback, const AccessibilityElementInfo& info, const int32_t requestId)
{
    if (IsRegister()) {
        callback.SetFindFocusedElementInfoResult(info, requestId);
    }
}

void JsAccessibilityManager::SetFocusMoveSearchResult(
    AccessibilityElementOperatorCallback& callback, const AccessibilityElementInfo& info, const int32_t requestId)
{
    if (IsRegister()) {
        callback.SetFocusMoveSearchResult(info, requestId);
    }
}

void JsAccessibilityManager::SetExecuteActionResult(
    AccessibilityElementOperatorCallback& callback, const bool succeeded, const int32_t requestId)
{
    if (IsRegister()) {
        callback.SetExecuteActionResult(succeeded, requestId);
    }
}

std::string JsAccessibilityManager::GetPagePath()
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, "");
    auto frontend = context->GetFrontend();
    CHECK_NULL_RETURN(frontend, "");
    ContainerScope scope(context->GetInstanceId());
    return frontend->GetPagePath();
}

} // namespace OHOS::Ace::Framework
