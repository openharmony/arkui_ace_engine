/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/accessibility/js_accessibility_manager.h"

#include "accessibility_ability_client.h"
#include "accessibility_system_ability_client.h"

#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/linear_map.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "frameworks/bridge/common/dom/dom_type.h"

namespace OHOS::Ace::Framework {
namespace {

const int32_t EVENT_DUMP_PARAM_LENGTH = 3;
const int32_t PROPERTY_DUMP_PARAM_LENGTH = 2;
const char DUMP_ORDER[] = "-accessibility";
const char TEXT_CHANGE_EVENT[] = "textchange";
const char PAGE_CHANGE_EVENT[] = "pagechange";
const char EJECT_DISMISS_EVENT[] = "ejectdismiss";
const char SCROLL_START_EVENT[] = "scrollstart";
const char SCROLL_END_EVENT[] = "scrollend";
const char ACCESSIBILITY_EVENT_TYPE[] = "accessibilityeventtype";
const char IMPORTANT_YES[] = "yes";
const char IMPORTANT_NO[] = "no";
const char IMPORTANT_NO_HIDE_DES[] = "no-hide-descendants";
constexpr int32_t ROOT_STACK_BASE = 1100000;
constexpr int32_t CARD_NODE_ID_RATION = 10000;
constexpr int32_t CARD_ROOT_NODE_ID_RATION = 1000;
constexpr int32_t CARD_BASE = 100000;

// key event value
const char KEYBOARD_BACK[] = "4";
const char KEYBOARD_UP[] = "19";
const char KEYBOARD_DOWN[] = "20";
const char KEYBOARD_LEFT[] = "21";
const char KEYBOARD_RIGHT[] = "22";
const char KEYBOARD_CENTER[] = "23";
const char HANDLE_A[] = "96";
const char HANDLE_SELECT[] = "109";
const char KEYBOARD_TAB[] = "61";
const char KEYBOARD_SPACE[] = "62";
const char KEYBOARD_ENTER[] = "66";
const char KEYBOARD_ESCAPE[] = "111";
const char KEYBOARD_NUMBER_ENTER[] = "160";
const char TV_CONTROL_MEDIA_PLAY[] = "85";

struct ActionTable {
    AceAction aceAction;
    Action action;
};

AccessibilityEventType ConvertStrToEventType(const std::string& type)
{
    // static linear map must be sorted by key.
    static const LinearMapNode<AccessibilityEventType> eventTypeMap[] = {
        { HANDLE_SELECT, AccessibilityEventType::HANDLE_SELECT },
        { KEYBOARD_ESCAPE, AccessibilityEventType::KEYBOARD_ESCAPE },
        { KEYBOARD_NUMBER_ENTER, AccessibilityEventType::KEYBOARD_NUMBER_ENTER },
        { KEYBOARD_UP, AccessibilityEventType::KEYBOARD_UP },
        { KEYBOARD_DOWN, AccessibilityEventType::KEYBOARD_DOWN },
        { KEYBOARD_LEFT, AccessibilityEventType::KEYBOARD_LEFT },
        { KEYBOARD_RIGHT, AccessibilityEventType::KEYBOARD_RIGHT },
        { KEYBOARD_CENTER, AccessibilityEventType::KEYBOARD_CENTER },
        { KEYBOARD_BACK, AccessibilityEventType::KEYBOARD_BACK },
        { KEYBOARD_TAB, AccessibilityEventType::KEYBOARD_TAB },
        { KEYBOARD_SPACE, AccessibilityEventType::KEYBOARD_SPACE },
        { KEYBOARD_ENTER, AccessibilityEventType::KEYBOARD_ENTER },
        { TV_CONTROL_MEDIA_PLAY, AccessibilityEventType::TV_CONTROL_MEDIA_PLAY },
        { HANDLE_A, AccessibilityEventType::HANDLE_A },
        { DOM_BLUR, AccessibilityEventType::BLUR },
        { DOM_CHANGE, AccessibilityEventType::CHANGE },
        { DOM_CLICK, AccessibilityEventType::CLICK },
        { EJECT_DISMISS_EVENT, AccessibilityEventType::EJECT_DISMISS },
        { DOM_FOCUS, AccessibilityEventType::FOCUS },
        { DOM_LONG_PRESS, AccessibilityEventType::LONG_PRESS },
        { DOM_MOUSE, AccessibilityEventType::MOUSE },
        { PAGE_CHANGE_EVENT, AccessibilityEventType::PAGE_CHANGE },
        { SCROLL_END_EVENT, AccessibilityEventType::SCROLL_END },
        { SCROLL_START_EVENT, AccessibilityEventType::SCROLL_START },
        { DOM_SELECTED, AccessibilityEventType::SELECTED },
        { TEXT_CHANGE_EVENT, AccessibilityEventType::TEXT_CHANGE },
        { DOM_TOUCH_CANCEL, AccessibilityEventType::TOUCH_CANCEL },
        { DOM_TOUCH_END, AccessibilityEventType::TOUCH_END },
        { DOM_TOUCH_MOVE, AccessibilityEventType::TOUCH_MOVE },
        { DOM_TOUCH_START, AccessibilityEventType::TOUCH_START },
    };
    AccessibilityEventType eventType = AccessibilityEventType::UNKNOWN;
    int64_t idx = BinarySearchFindIndex(eventTypeMap, ArraySize(eventTypeMap), type.c_str());
    if (idx >= 0) {
        eventType = eventTypeMap[idx].value;
    }
    return eventType;
}

Action ConvertAceAction(AceAction aceAction)
{
    static const ActionTable actionTable[] = {
        { AceAction::GLOBAL_ACTION_BACK, Action::GLOBAL_ACTION_BACK },
        { AceAction::CUSTOM_ACTION, Action::CUSTOM_ACTION },
        { AceAction::ACTION_CLICK, Action::ACTION_CLICK },
        { AceAction::ACTION_LONG_CLICK, Action::ACTION_LONG_CLICK },
        { AceAction::ACTION_SCROLL_FORWARD, Action::ACTION_SCROLL_FORWARD },
        { AceAction::ACTION_SCROLL_BACKWARD, Action::ACTION_SCROLL_BACKWARD },
        { AceAction::ACTION_FOCUS, Action::CUSTOM_ACTION },
        { AceAction::ACTION_ACCESSIBILITY_FOCUS, Action::ACTION_ACCESSIBILITY_FOCUS },
        { AceAction::ACTION_CLEAR_ACCESSIBILITY_FOCUS, Action::ACTION_CLEAR_ACCESSIBILITY_FOCUS },
        { AceAction::ACTION_NEXT_AT_MOVEMENT_GRANULARITY, Action::ACTION_NEXT_AT_MOVEMENT_GRANULARITY },
        { AceAction::ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY, Action::ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY },
    };
    for (const auto& item : actionTable) {
        if (aceAction == item.aceAction) {
            return item.action;
        }
    }
    return Action::ACTION_NONE;
}

inline RangeInfo ConvertAccessibilityValue(const AccessibilityValue& value)
{
    return RangeInfo(value.current, value.min, value.max);
}

TEXT_CATEGORY ConvertInputType(AceTextCategory type)
{
    switch (type) {
        case AceTextCategory::INPUT_TYPE_TEXT:
            return TEXT_CATEGORY::INPUT_TYPE_TEXT;
        case AceTextCategory::INPUT_TYPE_EMAIL:
            return TEXT_CATEGORY::INPUT_TYPE_EMAIL;
        case AceTextCategory::INPUT_TYPE_DATE:
            return TEXT_CATEGORY::INPUT_TYPE_DATE;
        case AceTextCategory::INPUT_TYPE_TIME:
            return TEXT_CATEGORY::INPUT_TYPE_TIME;
        case AceTextCategory::INPUT_TYPE_NUMBER:
            return TEXT_CATEGORY::INPUT_TYPE_NUMBER;
        case AceTextCategory::INPUT_TYPE_PASSWORD:
            return TEXT_CATEGORY::INPUT_TYPE_PASSWORD;
        default:
            return TEXT_CATEGORY::INPUT_TYPE_DEFAULT;
    }
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

void UpdateAccessibilityNodeInfo(const RefPtr<AccessibilityNode>& node, AccessibilityNodeInfo& nodeInfo,
    const RefPtr<JsAccessibilityManager>& manager)
{
    if (manager->isOhosHostCard()) {
        nodeInfo.ID = ConvertToCardAccessibilityId(node->GetNodeId(), manager->GetCardId(), manager->GetRootNodeId());
        if (node->GetParentId() == -1) {
            nodeInfo.parentID = -1;
        } else {
            nodeInfo.parentID =
                ConvertToCardAccessibilityId(node->GetParentId(), manager->GetCardId(), manager->GetRootNodeId());
        }
        nodeInfo.left = node->GetLeft() + manager->GetCardOffset().GetX();
        nodeInfo.top = node->GetTop() + manager->GetCardOffset().GetY();
    } else {
        nodeInfo.ID = node->GetNodeId();
        nodeInfo.parentID = node->GetParentId();
        nodeInfo.left = node->GetLeft();
        nodeInfo.top = node->GetTop();
    }

    if (node->GetParentId() == -1) {
        const auto& children = node->GetChildList();
        if (!children.empty()) {
            auto lastChildNode = manager->GetAccessibilityNodeById(children.back()->GetNodeId());
            if (lastChildNode) {
                nodeInfo.width = lastChildNode->GetWidth();
                nodeInfo.height = lastChildNode->GetHeight();
            }
        }
    } else {
        nodeInfo.width = node->GetWidth();
        nodeInfo.height = node->GetHeight();
    }

    nodeInfo.isChecked = node->GetCheckedState();
    nodeInfo.isEnabled = node->GetEnabledState();
    nodeInfo.isFocused = node->GetFocusedState();
    nodeInfo.isSelected = node->GetSelectedState();
    nodeInfo.isCheckable = node->GetCheckableState();
    nodeInfo.isClickable = node->GetClickableState();
    nodeInfo.isFocusable = node->GetFocusableState();
    nodeInfo.isScrollable = node->GetScrollableState();
    nodeInfo.isLongClickable = node->GetLongClickableState();
    nodeInfo.isEditable = node->GetEditable();
    nodeInfo.isMultiLine = node->GetIsMultiLine();
    nodeInfo.isPassword = node->GetIsPassword();
    nodeInfo.maxTextLength = node->GetMaxTextLength();
    nodeInfo.textSelectionStart = node->GetTextSelectionStart();
    nodeInfo.textSelectionEnd = node->GetTextSelectionEnd();
    nodeInfo.isVisible = (node->GetWidth() != 0 && node->GetHeight() != 0);
    bool visible = node->GetShown() && node->GetVisible();
    nodeInfo.isVisible = nodeInfo.isVisible && visible;
    nodeInfo.hintText = node->GetHintText();
    nodeInfo.accessibilityLabel = node->GetAccessibilityLabel();
    nodeInfo.error = node->GetErrorText();
    nodeInfo.jsComponentID = node->GetJsComponentId();
    nodeInfo.rangeInfo = ConvertAccessibilityValue(node->GetAccessibilityValue());
    nodeInfo.inputType = node->GetInputType();
    nodeInfo.textInputType = ConvertInputType(node->GetTextInputType());
    nodeInfo.componentName = node->GetTag();
    nodeInfo.collectionInfo.rows = node->GetCollectionInfo().rows;
    nodeInfo.collectionInfo.columns = node->GetCollectionInfo().columns;
    nodeInfo.collectionItemInfo.row = node->GetCollectionItemInfo().row;
    nodeInfo.collectionItemInfo.column = node->GetCollectionItemInfo().column;

    if (node->GetIsPassword()) {
        std::string strStar(node->GetText().size(), '*');
        nodeInfo.text = strStar;
    } else {
        nodeInfo.text = node->GetText();
    }

    if (!node->GetAccessibilityHint().empty()) {
        if (node->GetAccessibilityLabel().empty()) {
            nodeInfo.accessibilityLabel = nodeInfo.text + "," + node->GetAccessibilityHint();
        } else {
            nodeInfo.accessibilityLabel = node->GetAccessibilityLabel() + "," + node->GetAccessibilityHint();
        }
    }

    auto supportAceActions = node->GetSupportAction();
    std::vector<Action> actions(supportAceActions.size());
    std::transform(supportAceActions.begin(), supportAceActions.end(), actions.begin(),
        [](const AceAction& action) { return ConvertAceAction(action); });
    if (node->GetImportantForAccessibility() == IMPORTANT_YES) {
        actions.emplace_back(Action::ACTION_FOCUS);
        nodeInfo.isCheckable = true;
    } else if (node->GetImportantForAccessibility() == IMPORTANT_NO ||
               node->GetImportantForAccessibility() == IMPORTANT_NO_HIDE_DES) {
        nodeInfo.isVisible = false;
    }

    if (!node->GetAccessible() && node->GetImportantForAccessibility() != IMPORTANT_NO_HIDE_DES && visible) {
        nodeInfo.childIDs = node->GetChildIds();
    }

    nodeInfo.supportAction = std::move(actions);
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

std::string PrepareCustomEventParam(const std::vector<std::pair<std::string, std::string>>& actionParam)
{
    std::string eventParam;
    std::string params;
    for (const auto& param : actionParam) {
        if (param.first == ACCESSIBILITY_EVENT_TYPE) {
            eventParam.append("{\"eventType\":\"").append(param.second).append("\"");
        } else {
            if (params.empty()) {
                params.append(",\"param\":{\"");
            } else {
                params.append(",\"");
            }
            params.append(param.first).append("\":\"").append(param.second).append("\"");
        }
    }

    if (eventParam.empty()) {
        return std::string();
    }

    if (!params.empty()) {
        params.append("}");
    }
    return eventParam.append(params).append("}");
}

bool AccessibilityActionEvent(const AccessibilityActionInfo& actionInfo, const RefPtr<AccessibilityNode>& node,
    const RefPtr<PipelineContext>& context)
{
    if (!node || !context) {
        return false;
    }
    // neither register fronted event nor set backend event will return false.
    switch (actionInfo.action) {
        case Action::GLOBAL_ACTION_BACK:
            return context->CallRouterBackToPopPage();
        case Action::CUSTOM_ACTION: {
            if (!node->GetAccessibilityEventMarker().IsEmpty()) {
                auto actionParam = actionInfo.param;
                if (actionParam.empty()) {
                    LOGW("param cannot be empty when accessibility event");
                    return false;
                }
                auto eventParam = PrepareCustomEventParam(actionParam);
                std::string param = node->GetAccessibilityEventMarker().GetData().GetEventParam();
                if (eventParam.empty()) {
                    param.append("null");
                } else {
                    param.append(eventParam);
                }
                context->SendEventToFrontend(node->GetAccessibilityEventMarker(), param);
                return true;
            }
            return false;
        }
        case Action::ACTION_CLICK: {
            node->SetClicked(true);
            if (!node->GetClickEventMarker().IsEmpty()) {
                context->SendEventToFrontend(node->GetClickEventMarker());
                node->ActionClick();
                return true;
            }
            return node->ActionClick();
        }
        case Action::ACTION_LONG_CLICK: {
            if (!node->GetLongPressEventMarker().IsEmpty()) {
                context->SendEventToFrontend(node->GetLongPressEventMarker());
                node->ActionLongClick();
                return true;
            }
            return node->ActionLongClick();
        }
        case Action::ACTION_FOCUS: {
            context->AccessibilityRequestFocus(std::to_string(node->GetNodeId()));
            if (!node->GetFocusEventMarker().IsEmpty()) {
                context->SendEventToFrontend(node->GetFocusEventMarker());
                node->ActionFocus();
                return true;
            }
            return node->ActionFocus();
        }
        case Action::ACTION_SCROLL_FORWARD:
            return node->ActionScrollForward();
        case Action::ACTION_SCROLL_BACKWARD:
            return node->ActionScrollBackward();
        default:
            return false;
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
        default:
            return "illegal input type";
    }
}

} // namespace

void JsAccessibilityManager::InitializeCallback()
{
    auto fetchNodeInfoCallback = [weak = WeakClaim(this)](AccessibilityNodeInfo& nodeInfo) {
        auto jsAccessibilityManager = weak.Upgrade();
        if (!jsAccessibilityManager) {
            return false;
        }

        auto node = jsAccessibilityManager->GetAccessibilityNodeFromPage(nodeInfo.ID);
        if (!node) {
            LOGW("AccessibilityNodeInfo can't attach component by Id = %{public}d", nodeInfo.ID);
            return false;
        }
        jsAccessibilityManager->UpdateNodeChildIds(node);
        UpdateAccessibilityNodeInfo(node, nodeInfo, jsAccessibilityManager);
        return true;
    };
    AccessibilityAbilityClient::GetInstance().RegisterFetchNodeInfoCallback(fetchNodeInfoCallback);

    auto eventHandleCallback = [weak = WeakClaim(this)](AccessibilityActionInfo& actionInfo) {
        LOGD("AccessibilityActionInfo nodeId= %{public}d, action=%{public}d", actionInfo.ID, actionInfo.action);

        auto jsAccessibilityManager = weak.Upgrade();
        if (!jsAccessibilityManager) {
            return false;
        }

        auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
        if (!context) {
            return false;
        }

        auto node = jsAccessibilityManager->GetAccessibilityNodeFromPage(actionInfo.ID);
        if (!node) {
            LOGW("AccessibilityActionInfo can't attach component by Id = %{public}d", actionInfo.ID);
            return false;
        }

        bool ret = false;
        if (actionInfo.action == Action::ACTION_SCROLL_FORWARD || actionInfo.action == Action::ACTION_SCROLL_BACKWARD) {
            context->GetTaskExecutor()->PostSyncTask(
                [&actionInfo, &node, &context, &ret]() { ret = AccessibilityActionEvent(actionInfo, node, context); },
                TaskExecutor::TaskType::UI);
        } else {
            ret = AccessibilityActionEvent(actionInfo, node, context);
        }
        return ret;
    };
    AccessibilityAbilityClient::GetInstance().RegisterEventHandleCallback(eventHandleCallback);
}

void JsAccessibilityManager::SendAccessibilitySyncEvent(const AccessibilityEvent& accessibilityEvent)
{
    AccessibilityEventType type = ConvertStrToEventType(accessibilityEvent.eventType);
    if (type == AccessibilityEventType::UNKNOWN) {
        return;
    }

    auto client = AccessibilitySystemAbilityClient::GetInstance(nullptr);
    if (!client) {
        return;
    }
    auto barrierEvent = std::make_unique<BarrierfreeEvent>();
    barrierEvent->SetId(accessibilityEvent.nodeId);
    barrierEvent->SetEventType(static_cast<int32_t>(type));
    barrierEvent->SetClassName(accessibilityEvent.componentType);
    barrierEvent->SetCurrentItemIndex(static_cast<int32_t>(accessibilityEvent.currentItemIndex));
    barrierEvent->SetItemCount(static_cast<int32_t>(accessibilityEvent.itemCount));
    client->SendBarrierfreeEvent(barrierEvent);
}

void JsAccessibilityManager::SendAccessibilityAsyncEvent(const AccessibilityEvent& accessibilityEvent)
{
    auto context = GetPipelineContext().Upgrade();
    if (!context) {
        return;
    }

    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), accessibilityEvent] {
            auto jsAccessibilityManager = weak.Upgrade();
            if (!jsAccessibilityManager) {
                return;
            }
            jsAccessibilityManager->SendAccessibilitySyncEvent(accessibilityEvent);
        },
        TaskExecutor::TaskType::BACKGROUND);
}

void JsAccessibilityManager::UpdateNodeChildIds(const RefPtr<AccessibilityNode>& node)
{
    if (!node) {
        return;
    }
    node->ActionUpdateIds();
    const auto& children = node->GetChildList();
    std::vector<int32_t> childrenVec;
    auto cardId = GetCardId();
    auto rootNodeId = GetRootNodeId();

    // get last stack children to barrier free service.
    if ((node->GetNodeId() == GetRootNodeId() + ROOT_STACK_BASE) && !children.empty()) {
        auto lastChildNodeId = children.back()->GetNodeId();
        if (isOhosHostCard()) {
            childrenVec.emplace_back(ConvertToCardAccessibilityId(lastChildNodeId, cardId, rootNodeId));
        } else {
            childrenVec.emplace_back(lastChildNodeId);
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

void JsAccessibilityManager::DumpHandleEvent(const std::vector<std::string>& params)
{
    if (params.empty()) {
        DumpLog::GetInstance().Print("Error: params is empty!");
        return;
    }
    if (params.size() != EVENT_DUMP_PARAM_LENGTH) {
        DumpLog::GetInstance().Print("Error: params length is illegal!");
        return;
    }
    if (params[0] != DUMP_ORDER) {
        DumpLog::GetInstance().Print("Error: not accessibility dump order!");
        return;
    }
    int32_t ID = StringUtils::StringToInt(params[1]);
    auto node = GetAccessibilityNodeFromPage(ID);
    if (!node) {
        DumpLog::GetInstance().Print("Error: can't find node with ID");
        return;
    }
    auto action = static_cast<AceAction>(StringUtils::StringToInt(params[2]));
    AccessibilityActionInfo actionInfo = {
        .ID = ID,
    };
    static const ActionTable actionEventTable[] = {
        { AceAction::CUSTOM_ACTION, Action::CUSTOM_ACTION },
        { AceAction::ACTION_CLICK, Action::ACTION_CLICK },
        { AceAction::ACTION_LONG_CLICK, Action::ACTION_LONG_CLICK },
        { AceAction::ACTION_SCROLL_FORWARD, Action::ACTION_SCROLL_FORWARD },
        { AceAction::ACTION_SCROLL_BACKWARD, Action::ACTION_SCROLL_BACKWARD },
        { AceAction::ACTION_FOCUS, Action::CUSTOM_ACTION },
    };
    for (const auto& item : actionEventTable) {
        if (action == item.aceAction) {
            actionInfo.action = item.action;
            break;
        }
    }
    auto context = GetPipelineContext().Upgrade();
    if (context) {
        context->GetTaskExecutor()->PostTask(
            [actionInfo, node, context]() { AccessibilityActionEvent(actionInfo, node, context); },
            TaskExecutor::TaskType::UI);
    }
}

void JsAccessibilityManager::DumpProperty(const std::vector<std::string>& params)
{
    if (!DumpLog::GetInstance().GetDumpFile()) {
        return;
    }

    if (params.empty()) {
        DumpLog::GetInstance().Print("Error: params cannot be empty!");
        return;
    }
    if (params.size() != PROPERTY_DUMP_PARAM_LENGTH) {
        DumpLog::GetInstance().Print("Error: params length is illegal!");
        return;
    }
    if (params[0] != DUMP_ORDER) {
        DumpLog::GetInstance().Print("Error: not accessibility dump order!");
        return;
    }

    auto node = GetAccessibilityNodeFromPage(StringUtils::StringToInt(params[1]));
    if (!node) {
        DumpLog::GetInstance().Print("Error: can't find node with ID " + params[1]);
        return;
    }

    const auto& supportAceActions = node->GetSupportAction();
    std::string actionForDump;
    for (const auto& action : supportAceActions) {
        if (!actionForDump.empty()) {
            actionForDump.append(",");
        }
        actionForDump.append(std::to_string(static_cast<int32_t>(action)));
    }

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
    DumpLog::GetInstance().AddDesc("support action: ", actionForDump);

    DumpLog::GetInstance().Print(0, node->GetTag(), node->GetChildList().size());
}

void JsAccessibilityManager::DumpTree(int32_t depth, NodeId nodeID)
{
    if (!DumpLog::GetInstance().GetDumpFile()) {
        return;
    }

    auto node = GetAccessibilityNodeFromPage(nodeID);
    if (!node) {
        DumpLog::GetInstance().Print("Error: failed to get accessibility node with ID " + std::to_string(nodeID));
        return;
    }

    std::string info = "ID:";
    info.append(std::to_string(node->GetNodeId()));
    if (!node->GetText().empty()) {
        info.append(" ");
        info.append("text:");
        info.append(node->GetText());
    }
    DumpLog::GetInstance().AddDesc(info);
    DumpLog::GetInstance().Print(depth, node->GetTag(), node->GetChildList().size());
    for (const auto& item : node->GetChildList()) {
        DumpTree(depth + 1, item->GetNodeId());
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

} // namespace OHOS::Ace::Framework
