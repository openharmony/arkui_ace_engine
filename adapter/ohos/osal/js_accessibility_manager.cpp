/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "core/pipeline/pipeline_context.h"
#include "frameworks/bridge/common/dom/dom_type.h"

using namespace OHOS::Accessibility;
using namespace OHOS::AccessibilityConfig;
using namespace std;

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t EVENT_DUMP_PARAM_LENGTH_UPPER = 4;
constexpr int32_t EVENT_DUMP_PARAM_LENGTH_LOWER = 3;
constexpr int32_t PROPERTY_DUMP_PARAM_LENGTH = 2;
constexpr int32_t EVENT_DUMP_ORDER_INDEX = 0;
constexpr int32_t EVENT_DUMP_ID_INDEX = 1;
constexpr int32_t EVENT_DUMP_ACTION_INDEX = 2;
constexpr int32_t EVENT_DUMP_ACTION_PARAM_INDEX = 3;
const char DUMP_ORDER[] = "-accessibility";
const char DUMP_INSPECTOR[] = "-inspector";
const char ACCESSIBILITY_FOCUSED_EVENT[] = "accessibilityfocus";
const char ACCESSIBILITY_CLEAR_FOCUS_EVENT[] = "accessibilityclearfocus";
const char TEXT_CHANGE_EVENT[] = "textchange";
const char PAGE_CHANGE_EVENT[] = "pagechange";
const char SCROLL_END_EVENT[] = "scrollend";
const char SCROLL_START_EVENT [] = "scrollstart";
const char MOUSE_HOVER_ENTER[] = "mousehoverenter";
const char MOUSE_HOVER_EXIT[] = "mousehoverexit";
const char IMPORTANT_YES[] = "yes";
const char IMPORTANT_NO[] = "no";
const char IMPORTANT_NO_HIDE_DES[] = "no-hide-descendants";
const char LIST_TAG[] = "List";
constexpr int32_t INVALID_PARENT_ID = -2100000;
constexpr int32_t DEFAULT_PARENT_ID = 2100000;
constexpr int32_t ROOT_STACK_BASE = 1100000;
constexpr int32_t ROOT_DECOR_BASE = 3100000;
constexpr int32_t CARD_NODE_ID_RATION = 10000;
constexpr int32_t CARD_ROOT_NODE_ID_RATION = 1000;
constexpr int32_t CARD_BASE = 100000;
constexpr int32_t WEIGHTED_VALUE = 13;

const int32_t FOCUS_DIRECTION_UP = 1;
const int32_t FOCUS_DIRECTION_DOWN = 1 << 1;
const int32_t FOCUS_DIRECTION_LEFT = 1 << 2;
const int32_t FOCUS_DIRECTION_RIGHT = 1 << 3;
const int32_t FOCUS_DIRECTION_FORWARD = 1 << 4;
const int32_t FOCUS_DIRECTION_BACKWARD = 1 << 5;

struct ActionTable {
    AceAction aceAction;
    ActionType action;
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

ActionType ConvertAceAction(AceAction aceAction)
{
    static const ActionTable actionTable[] = {
        { AceAction::ACTION_CLICK, ActionType::ACCESSIBILITY_ACTION_CLICK },
        { AceAction::ACTION_LONG_CLICK, ActionType::ACCESSIBILITY_ACTION_LONG_CLICK },
        { AceAction::ACTION_SCROLL_FORWARD, ActionType::ACCESSIBILITY_ACTION_SCROLL_FORWARD },
        { AceAction::ACTION_SCROLL_BACKWARD, ActionType::ACCESSIBILITY_ACTION_SCROLL_BACKWARD },
        { AceAction::ACTION_FOCUS, ActionType::ACCESSIBILITY_ACTION_FOCUS },
        { AceAction::ACTION_ACCESSIBILITY_FOCUS, ActionType::ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS },
        { AceAction::ACTION_CLEAR_ACCESSIBILITY_FOCUS, ActionType::ACCESSIBILITY_ACTION_CLEAR_ACCESSIBILITY_FOCUS },
        { AceAction::ACTION_NEXT_AT_MOVEMENT_GRANULARITY, ActionType::ACCESSIBILITY_ACTION_NEXT_TEXT },
        { AceAction::ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY, ActionType::ACCESSIBILITY_ACTION_PREVIOUS_TEXT },
        { AceAction::ACTION_SET_TEXT, ActionType::ACCESSIBILITY_ACTION_SET_TEXT },
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
    const RefPtr<JsAccessibilityManager>& manager, int windowId, NodeId rootId)
{
    LOGD("nodeId:%{public}d", node->GetNodeId());
    int leftTopX = static_cast<int>(node->GetLeft()) + manager->GetWindowLeft();
    int leftTopY = static_cast<int>(node->GetTop()) + manager->GetWindowTop();
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
    nodeInfo.SetVisible(node->GetShown() && node->GetVisible() && (node->GetWidth() != 0 && node->GetHeight() != 0));
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
            UpdateAccessibilityNodeInfo(node->GetParentNode(), parentNodeInfo, jsAccessibilityManager, windowId,
                jsAccessibilityManager->GetRootNodeId());
            infos.emplace_back(parentNodeInfo);
        }
    }
    // sister/brothers
    if (umode & static_cast<uint32_t>(PREFETCH_SIBLINGS)) {
        if (node->GetParentId() != -1 && node->GetParentId() != DEFAULT_PARENT_ID) {
            for (const auto& item : node->GetParentNode()->GetChildList()) {
                if (node->GetNodeId() != item->GetNodeId()) {
                    AccessibilityElementInfo siblingNodeInfo;
                    UpdateAccessibilityNodeInfo(item, siblingNodeInfo, jsAccessibilityManager, windowId,
                        jsAccessibilityManager->GetRootNodeId());
                    infos.emplace_back(siblingNodeInfo);
                }
            }
        }
    }
    // children
    if (umode & static_cast<uint32_t>(PREFETCH_CHILDREN)) {
        for (const auto& item : node->GetChildList()) {
            AccessibilityElementInfo childNodeInfo;
            UpdateAccessibilityNodeInfo(
                item, childNodeInfo, jsAccessibilityManager, windowId, jsAccessibilityManager->GetRootNodeId());
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
        default:
            return "illegal input type";
    }
}

bool FindAccessibilityFocus(const RefPtr<AccessibilityNode>& node, RefPtr<AccessibilityNode>& resultNode)
{
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

bool FindInputFocus(const RefPtr<AccessibilityNode>& node, RefPtr<AccessibilityNode>& resultNode)
{
    LOGI("FindFocus nodeId(%{public}d focus(%{public}d))", node->GetNodeId(), node->GetFocusedState());
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
    if (node->GetFocusedState()) {
        return true;
    }

    return false;
}

void FindText(
    const RefPtr<AccessibilityNode>& node, const std::string& text, std::list<RefPtr<AccessibilityNode>>& nodeList)
{
    if ((node != nullptr) && (node->GetText().find(text) != std::string::npos)) {
        LOGI("FindText find nodeId(%{public}d)", node->GetNodeId());
        nodeList.push_back(node);
    }
    if (!node->GetChildList().empty()) {
        for (const auto& child : node->GetChildList()) {
            FindText(child, text, nodeList);
        }
    }
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
    LOGI("accessibility content timeout changed:%{public}u", value.contentTimeout);
    AceApplicationInfo::GetInstance().SetBarrierfreeDuration((int32_t)value.contentTimeout);
}

bool JsAccessibilityManager::SubscribeToastObserver()
{
    LOGI("SubscribeToastObserver");
    if (!toastObserver_) {
        toastObserver_ = std::make_shared<ToastAccessibilityConfigObserver>();
    }
    if (!toastObserver_) {
        return false;
    }
    auto& config = OHOS::Singleton<OHOS::AccessibilityConfig::AccessibilityConfig>::GetInstance();
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
    if (!toastObserver_) {
        return false;
    }
    auto& config = OHOS::Singleton<OHOS::AccessibilityConfig::AccessibilityConfig>::GetInstance();
    bool isSuccess = config.InitializeContext();
    if (!isSuccess) {
        LOGE("AccessibilityConfig InitializeContext failed");
        return false;
    }
    config.UnsubscribeConfigObserver(CONFIG_CONTENT_TIMEOUT, toastObserver_);
    return true;
}

bool JsAccessibilityManager::SubscribeStateObserver(const int eventType)
{
    LOGD("SubscribeStateObserver");
    if (!stateObserver_) {
        stateObserver_ = std::make_shared<JsAccessibilityStateObserver>();
    }

    stateObserver_->SetHandler(WeakClaim(this));

    auto instance = AccessibilitySystemAbilityClient::GetInstance();
    if (instance == nullptr) {
        return false;
    }

    bool ret = instance->SubscribeStateObserver(stateObserver_, eventType);
    LOGI("SubscribeStateObserver:%{public}d", ret);
    return ret;
}

bool JsAccessibilityManager::UnsubscribeStateObserver(const int eventType)
{
    LOGI("UnsubscribeStateObserver");
    if (!stateObserver_) {
        return false;
    }

    std::shared_ptr<AccessibilitySystemAbilityClient> instance = AccessibilitySystemAbilityClient::GetInstance();
    if (instance == nullptr) {
        return false;
    }

    bool ret = instance->UnsubscribeStateObserver(stateObserver_, eventType);
    LOGI("UnsubscribeStateObserver:%{public}d", ret);
    return ret;
}

void JsAccessibilityManager::InitializeCallback()
{
    LOGD("InitializeCallback");
    if (IsRegister()) {
        return;
    }

    auto pipelineContext = GetPipelineContext().Upgrade();
    if (!pipelineContext) {
        return;
    }
    windowId_ = pipelineContext->GetWindowId();

    auto client = AccessibilitySystemAbilityClient::GetInstance();
    if (!client) {
        return;
    }
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(client->IsEnabled());

    SubscribeToastObserver();
    SubscribeStateObserver(AccessibilityStateEventType::EVENT_ACCESSIBILITY_STATE_CHANGED);
    if (client->IsEnabled()) {
        RegisterInteractionOperation(windowId_);
    }
}

bool JsAccessibilityManager::SendAccessibilitySyncEvent(const AccessibilityEvent& accessibilityEvent)
{
    if (!IsRegister()) {
        return false;
    }

    auto client = AccessibilitySystemAbilityClient::GetInstance();
    if (!client) {
        return false;
    }
    if (!client->IsEnabled()) {
        return false;
    }

    LOGI("type:%{public}s nodeId:%{public}d", accessibilityEvent.eventType.c_str(), accessibilityEvent.nodeId);

    Accessibility::EventType type = ConvertStrToEventType(accessibilityEvent.eventType);
    if (type == Accessibility::EventType::TYPE_VIEW_INVALID) {
        return false;
    }

    auto pipelineContext = GetPipelineContext().Upgrade();
    if (!pipelineContext) {
        return false;
    }
    int32_t windowId = pipelineContext->GetWindowId();
    if (windowId == 0) {
        return false;
    }

    auto node = GetAccessibilityNodeFromPage(accessibilityEvent.nodeId);
    if (!node) {
        LOGW("can't attach component by Id = %{public}d", accessibilityEvent.nodeId);
        return false;
    }

    AccessibilityEventInfo eventInfo;
    eventInfo.SetWindowId(windowId);
    eventInfo.SetSource(accessibilityEvent.nodeId);
    eventInfo.SetEventType(type);
    eventInfo.SetComponentType(node->GetTag());
    eventInfo.SetCurrentIndex(static_cast<int>(accessibilityEvent.currentItemIndex));
    eventInfo.SetItemCounts(static_cast<int>(accessibilityEvent.itemCount));
    if (node->GetTag() == LIST_TAG) {
        eventInfo.SetItemCounts(node->GetListItemCounts());
        eventInfo.SetBeginIndex(node->GetListBeginIndex());
        eventInfo.SetEndIndex(node->GetListEndIndex());
    }
    eventInfo.SetBundleName(AceApplicationInfo::GetInstance().GetPackageName());
    eventInfo.SetPageId(node->GetPageId());
    eventInfo.AddContent(node->GetText());
    eventInfo.SetLatestContent(node->GetText());
    return client->SendEvent(eventInfo);
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

void JsAccessibilityManager::DumpHandleEvent(const std::vector<std::string>& params)
{
    if (params.empty()) {
        DumpLog::GetInstance().Print("Error: params is empty!");
        return;
    }
    if (!(params.size() == EVENT_DUMP_PARAM_LENGTH_LOWER || params.size() == EVENT_DUMP_PARAM_LENGTH_UPPER)) {
        DumpLog::GetInstance().Print("Error: params length is illegal!");
        return;
    }
    if (params[EVENT_DUMP_ORDER_INDEX] != DUMP_ORDER && params[EVENT_DUMP_ORDER_INDEX] != DUMP_INSPECTOR) {
        DumpLog::GetInstance().Print("Error: not accessibility dump order!");
        return;
    }
    int32_t nodeId = StringUtils::StringToInt(params[EVENT_DUMP_ID_INDEX]);
    auto node = GetAccessibilityNodeFromPage(nodeId);
    if (!node) {
        DumpLog::GetInstance().Print("Error: can't find node with ID");
        return;
    }
    auto action = static_cast<AceAction>(StringUtils::StringToInt(params[EVENT_DUMP_ACTION_INDEX]));
    std::string eventParams;
    if (params.size()==EVENT_DUMP_PARAM_LENGTH_UPPER) {
        eventParams = params[EVENT_DUMP_ACTION_PARAM_INDEX];
    }
    auto op = ConvertAceAction(action);
    std::map<std::string, std::string> paramsMap;
    if (op == ActionType::ACCESSIBILITY_ACTION_SET_TEXT) {
        paramsMap = {{ ACTION_ARGU_SET_TEXT, eventParams }};
    }
    auto context = GetPipelineContext().Upgrade();
    if (context) {
        context->GetTaskExecutor()->PostTask(
            [weak = WeakClaim(this), op, node, paramsMap, context]() {
                auto jsAccessibilityManager = weak.Upgrade();
                if (!jsAccessibilityManager) {
                    return;
                }
                jsAccessibilityManager->AccessibilityActionEvent(
                    op, paramsMap, node, AceType::DynamicCast<PipelineContext>(context));
            },
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
    if (params[0] != DUMP_ORDER && params[0] != DUMP_INSPECTOR) {
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
    DumpLog::GetInstance().AddDesc("accessibilityGroup: ", BoolToString(node->GetAccessible()));
    DumpLog::GetInstance().AddDesc("accessibilityImportance: ", node->GetImportantForAccessibility());
    DumpLog::GetInstance().AddDesc("support action: ", actionForDump);

    DumpLog::GetInstance().Print(0, node->GetTag(), node->GetChildList().size());
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
    if (!context) {
        return;
    }
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

void JsAccessibilityManager::JsInteractionOperation::SearchElementInfoByAccessibilityId(const int32_t elementId,
    const int32_t requestId, AccessibilityElementOperatorCallback& callback, const int32_t mode)
{
    LOGD("elementId(%{public}d) requestId(%{public}d) mode(%{public}d)", elementId, requestId, mode);
    auto jsAccessibilityManager = GetHandler().Upgrade();
    if (!jsAccessibilityManager) {
        LOGW("SetSearchElementInfoByAccessibilityIdResult elementId(%{public}d) requestId(%{public}d)", elementId,
            requestId);
        return;
    }

    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    if (context) {
        context->GetTaskExecutor()->PostTask(
            [jsAccessibilityManager, elementId, requestId, &callback, mode]() {
                if (!jsAccessibilityManager) {
                    LOGW("SetSearchElementInfoByAccessibilityIdResult elementId(%{public}d) requestId(%{public}d)",
                        elementId, requestId);
                    return;
                }
                jsAccessibilityManager->SearchElementInfoByAccessibilityId(elementId, requestId, callback, mode);
            },
            TaskExecutor::TaskType::UI);
    }
}

void JsAccessibilityManager::SearchElementInfoByAccessibilityId(const int32_t elementId, const int32_t requestId,
    AccessibilityElementOperatorCallback& callback, const int32_t mode)
{
    auto weak = WeakClaim(this);
    auto jsAccessibilityManager = weak.Upgrade();
    if (!jsAccessibilityManager) {
        return;
    }

    NodeId nodeId = static_cast<NodeId>(elementId);
    // get root node
    if (elementId == -1) {
        nodeId = 0;
    }
    std::list<AccessibilityElementInfo> infos;
    auto node = jsAccessibilityManager->GetAccessibilityNodeFromPage(nodeId);
    if (!node) {
        LOGW("AccessibilityNodeInfo can't attach component by Id = %{public}d", nodeId);
        SetSearchElementInfoByAccessibilityIdResult(callback, infos, requestId);
        return;
    }

    AccessibilityElementInfo nodeInfo;
    UpdateAccessibilityNodeInfo(node, nodeInfo, jsAccessibilityManager, jsAccessibilityManager->windowId_,
        jsAccessibilityManager->GetRootNodeId());
    infos.push_back(nodeInfo);
    // cache parent/siblings/children infos
    UpdateCacheInfo(infos, mode, node, jsAccessibilityManager, jsAccessibilityManager->windowId_);

    SetSearchElementInfoByAccessibilityIdResult(callback, infos, requestId);
    LOGD("requestId(%{public}d)", requestId);
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
    if (!jsAccessibilityManager) {
        return;
    }

    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    if (context) {
        context->GetTaskExecutor()->PostTask(
            [jsAccessibilityManager, elementId, text, requestId, &callback]() {
                if (!jsAccessibilityManager) {
                    return;
                }

                jsAccessibilityManager->SearchElementInfosByText(elementId, text, requestId, callback);
            },
            TaskExecutor::TaskType::UI);
    }
}

void JsAccessibilityManager::SearchElementInfosByText(const int32_t elementId, const std::string& text,
    const int32_t requestId, AccessibilityElementOperatorCallback& callback)
{
    if (text.empty()) {
        LOGW("Text is null");
        return;
    }
    auto weak = WeakClaim(this);
    auto jsAccessibilityManager = weak.Upgrade();
    if (!jsAccessibilityManager) {
        return;
    }

    NodeId nodeId = static_cast<NodeId>(elementId);
    if (elementId == -1) {
        return;
    }

    auto node = jsAccessibilityManager->GetAccessibilityNodeFromPage(nodeId);
    if (!node) {
        return;
    }

    std::list<AccessibilityElementInfo> infos;
    std::list<RefPtr<AccessibilityNode>> nodeList;
    FindText(node, text, nodeList);
    if (!nodeList.empty()) {
        for (const auto& node : nodeList) {
            LOGI(" FindText end nodeId:%{public}d", node->GetNodeId());
            AccessibilityElementInfo nodeInfo;
            UpdateAccessibilityNodeInfo(node, nodeInfo, jsAccessibilityManager, jsAccessibilityManager->windowId_,
                jsAccessibilityManager->GetRootNodeId());
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
    if (!jsAccessibilityManager) {
        return;
    }

    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    if (context) {
        context->GetTaskExecutor()->PostTask(
            [jsAccessibilityManager, elementId, focusType, requestId, &callback]() {
                if (!jsAccessibilityManager) {
                    return;
                }
                jsAccessibilityManager->FindFocusedElementInfo(elementId, focusType, requestId, callback);
            },
            TaskExecutor::TaskType::UI);
    }
}

void JsAccessibilityManager::FindFocusedElementInfo(const int32_t elementId, const int32_t focusType,
    const int32_t requestId, AccessibilityElementOperatorCallback& callback)
{
    AccessibilityElementInfo nodeInfo;
    if (focusType != FOCUS_TYPE_INPUT && focusType != FOCUS_TYPE_ACCESSIBILITY) {
        nodeInfo.SetValidElement(false);
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
        UpdateAccessibilityNodeInfo(resultNode, nodeInfo, Claim(this), windowId_, GetRootNodeId());
    }

    SetFindFocusedElementInfoResult(callback, nodeInfo, requestId);
}

void JsAccessibilityManager::JsInteractionOperation::ExecuteAction(const int32_t elementId, const int32_t action,
    const std::map<std::string, std::string>& actionArguments, const int32_t requestId,
    AccessibilityElementOperatorCallback& callback)
{
    LOGI("id:%{public}d, action:%{public}d, request:%{public}d.", elementId, action, requestId);
    auto jsAccessibilityManager = GetHandler().Upgrade();
    if (!jsAccessibilityManager) {
        return;
    }

    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    if (!context) {
        return;
    }

    ActionType actionInfo = static_cast<ActionType>(action);
    context->GetTaskExecutor()->PostTask(
        [jsAccessibilityManager, elementId, actionInfo, actionArguments, requestId, &callback] {
            if (!jsAccessibilityManager) {
                return;
            }
            jsAccessibilityManager->ExecuteAction(elementId, actionInfo, actionArguments, requestId, callback);
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
                context->SendEventToFrontend(node->GetClickEventMarker());
                node->ActionClick();
                return true;
            }
            return node->ActionClick();
        }
        case ActionType::ACCESSIBILITY_ACTION_LONG_CLICK: {
            if (!node->GetLongPressEventMarker().IsEmpty()) {
                context->SendEventToFrontend(node->GetLongPressEventMarker());
                node->ActionLongClick();
                return true;
            }
            return node->ActionLongClick();
        }
        case ActionType::ACCESSIBILITY_ACTION_SET_TEXT: {
            if (!node->GetSetTextEventMarker().IsEmpty()) {
                context->SendEventToFrontend(node->GetSetTextEventMarker());
                node->ActionSetText(actionArguments.find(ACTION_ARGU_SET_TEXT)->second);
                return true;
            }
            return node->ActionSetText(actionArguments.find(ACTION_ARGU_SET_TEXT)->second);
        }
        case ActionType::ACCESSIBILITY_ACTION_FOCUS: {
            context->AccessibilityRequestFocus(std::to_string(node->GetNodeId()));
            if (!node->GetFocusEventMarker().IsEmpty()) {
                context->SendEventToFrontend(node->GetFocusEventMarker());
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

void JsAccessibilityManager::ExecuteAction(const int32_t elementId, const ActionType& action,
    const std::map<std::string, std::string> actionArguments, const int32_t requestId,
    AccessibilityElementOperatorCallback& callback)
{
    LOGI("ExecuteAction elementId:%{public}d action:%{public}d", elementId, action);
    auto weak = WeakClaim(this);
    auto jsAccessibilityManager = weak.Upgrade();

    auto node = jsAccessibilityManager->GetAccessibilityNodeFromPage((NodeId)elementId);
    if (!node) {
        LOGW("AccessibilityNodeInfo can't attach component by Id = %{public}d", (NodeId)elementId);
        SetExecuteActionResult(callback, false, requestId);
        return;
    }

    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    if (!context) {
        SetExecuteActionResult(callback, false, requestId);
        return;
    }

    bool actionResult =
        AccessibilityActionEvent(action, actionArguments, node, AceType::DynamicCast<PipelineContext>(context));

    LOGI("SetExecuteActionResult actionResult= %{public}d", actionResult);
    SetExecuteActionResult(callback, actionResult, requestId);
    if (actionResult) {
        SendActionEvent(action, node->GetNodeId());
    }
}

void JsAccessibilityManager::JsInteractionOperation::ClearFocus()
{
    LOGI("ClearFocus");
    auto jsAccessibilityManager = GetHandler().Upgrade();
    if (!jsAccessibilityManager) {
        return;
    }

    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    if (!context) {
        return;
    }

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

int JsAccessibilityManager::RegisterInteractionOperation(const int windowId)
{
    LOGI("RegisterInteractionOperation windowId:%{public}d", windowId);
    if (IsRegister()) {
        return 0;
    }

    std::shared_ptr<AccessibilitySystemAbilityClient> instance = AccessibilitySystemAbilityClient::GetInstance();
    if (instance == nullptr) {
        return (-1);
    }

    interactionOperation_ = std::make_shared<JsInteractionOperation>();
    interactionOperation_->SetHandler(WeakClaim(this));
    auto retReg = instance->RegisterElementOperator(windowId, interactionOperation_);
    LOGI("RegisterInteractionOperation end windowId:%{public}d, ret:%{public}d", windowId, retReg);
    Register(retReg == 0);

    return retReg;
}

void JsAccessibilityManager::DeregisterInteractionOperation()
{
    if (!IsRegister()) {
        return;
    }
    int windowId = GetWindowId();

    auto instance = AccessibilitySystemAbilityClient::GetInstance();
    if (instance == nullptr) {
        return;
    }
    Register(false);
    currentFocusNodeId_ = -1;
    LOGI("DeregisterInteractionOperation windowId:%{public}d", windowId);
    return instance->DeregisterElementOperator(windowId);
}

void JsAccessibilityManager::JsAccessibilityStateObserver::OnStateChanged(const bool state)
{
    LOGI("accessibility state changed:%{public}d", state);
    auto jsAccessibilityManager = GetHandler().Upgrade();
    if (!jsAccessibilityManager) {
        return;
    }

    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    if (context) {
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
}

void JsAccessibilityManager::JsInteractionOperation::FocusMoveSearch(const int32_t elementId, const int32_t direction,
    const int32_t requestId, AccessibilityElementOperatorCallback& callback)
{
    LOGI("elementId:%{public}d,direction:%{public}d,requestId:%{public}d", elementId, direction, requestId);
    auto jsAccessibilityManager = GetHandler().Upgrade();
    if (!jsAccessibilityManager) {
        return;
    }

    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    if (!context) {
        return;
    }

    context->GetTaskExecutor()->PostTask(
        [jsAccessibilityManager, elementId, direction, requestId, &callback] {
            if (!jsAccessibilityManager) {
                return;
            }
            jsAccessibilityManager->FocusMoveSearch(elementId, direction, requestId, callback);
        },
        TaskExecutor::TaskType::UI);
}

void JsAccessibilityManager::FocusMoveSearch(const int32_t elementId, const int32_t direction, const int32_t requestId,
    Accessibility::AccessibilityElementOperatorCallback& callback)
{
    auto weak = WeakClaim(this);
    auto jsAccessibilityManager = weak.Upgrade();
    AccessibilityElementInfo nodeInfo;
    auto node = jsAccessibilityManager->GetAccessibilityNodeFromPage((NodeId)elementId);
    if (!node) {
        LOGW("AccessibilityNodeInfo can't attach component by Id = %{public}d", (NodeId)elementId);
        nodeInfo.SetValidElement(false);
        SetFocusMoveSearchResult(callback, nodeInfo, requestId);
        return;
    }

    auto context = GetPipelineContext().Upgrade();
    if (!context) {
        LOGI("FocusMoveSearch context is null");
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
        case FOCUS_DIRECTION_FORWARD:
        case FOCUS_DIRECTION_BACKWARD:
            // forward and backward
            resultNode = FindNodeInRelativeDirection(nodeList, node, direction);
            break;
        case FOCUS_DIRECTION_UP:
        case FOCUS_DIRECTION_DOWN:
        case FOCUS_DIRECTION_LEFT:
        case FOCUS_DIRECTION_RIGHT:
            // up, down, left and right
            resultNode = FindNodeInAbsoluteDirection(nodeList, node, direction);
            break;
        default:
            break;
    }

    if (resultNode) {
        LOGI("FocusMoveSearch end nodeId:%{public}d", resultNode->GetNodeId());
        UpdateAccessibilityNodeInfo(resultNode, nodeInfo, jsAccessibilityManager, windowId_, rootNode->GetNodeId());
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
        case FOCUS_DIRECTION_FORWARD:
            return GetNextFocusableNode(nodeList, node);
        case FOCUS_DIRECTION_BACKWARD:
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
        case FOCUS_DIRECTION_LEFT:
            tempBest.SetLeft(node->GetLeft() + node->GetWidth() + 1);
            break;
        case FOCUS_DIRECTION_RIGHT:
            tempBest.SetLeft(node->GetLeft() - node->GetWidth() - 1);
            break;
        case FOCUS_DIRECTION_UP:
            tempBest.SetTop(node->GetTop() + node->GetHeight() + 1);
            break;
        case FOCUS_DIRECTION_DOWN:
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
    if (nodeList.size() > 0) {
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

    if (nodeList.size() > 0) {
        return (*nodeList.rbegin());
    }
    return nullptr;
}

bool JsAccessibilityManager::CheckBetterRect(Rect nodeRect, const int direction, Rect itemRect, Rect tempBest)
{
    if (!IsCandidateRect(nodeRect, itemRect, direction)) {
        return false;
    }

    if (!IsCandidateRect(nodeRect, tempBest, direction)) {
        return true;
    }

    // now both of item and tempBest are all at the direction of node.
    if (OutrightBetter(nodeRect, direction, itemRect, tempBest)) {
        return true;
    }

    if (OutrightBetter(nodeRect, direction, tempBest, itemRect)) {
        return false;
    }

    // otherwise, do fudge-tastic comparison of the major and minor axis
    return (GetWeightedDistanceFor(
                MajorAxisDistance(nodeRect, itemRect, direction), MinorAxisDistance(nodeRect, itemRect, direction)) <
            GetWeightedDistanceFor(
                MajorAxisDistance(nodeRect, tempBest, direction), MinorAxisDistance(nodeRect, tempBest, direction)));
}

bool JsAccessibilityManager::IsCandidateRect(Rect nodeRect, Rect itemRect, const int direction)
{
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
            return nodeRect.Left() > itemRect.Left() && nodeRect.Right() > itemRect.Right();
        case FOCUS_DIRECTION_RIGHT:
            return nodeRect.Left() < itemRect.Left() && nodeRect.Right() < itemRect.Right();
        case FOCUS_DIRECTION_UP:
            return nodeRect.Top() > itemRect.Top() && nodeRect.Bottom() > itemRect.Bottom();
        case FOCUS_DIRECTION_DOWN:
            return nodeRect.Top() < itemRect.Top() && nodeRect.Bottom() < itemRect.Bottom();
        default:
            break;
    }
    return false;
}

// Check whether rect1 is outright better than rect2.
bool JsAccessibilityManager::OutrightBetter(Rect nodeRect, const int direction, Rect Rect1, Rect Rect2)
{
    bool rect1InSrcBeam = CheckRectBeam(nodeRect, Rect1, direction);
    bool rect2InSrcBeam = CheckRectBeam(nodeRect, Rect2, direction);
    if (rect2InSrcBeam || !rect1InSrcBeam) {
        return false;
    }

    if (!IsToDirectionOf(nodeRect, Rect2, direction)) {
        return true;
    }

    // for direction left or right
    if (direction == FOCUS_DIRECTION_LEFT || direction == FOCUS_DIRECTION_RIGHT) {
        return true;
    }

    return (MajorAxisDistance(nodeRect, Rect1, direction) < MajorAxisDistanceToFarEdge(nodeRect, Rect2, direction));
}

bool JsAccessibilityManager::CheckRectBeam(Rect nodeRect, Rect itemRect, const int direction)
{
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
        case FOCUS_DIRECTION_RIGHT:
            return nodeRect.Top() < itemRect.Bottom() && itemRect.Top() < nodeRect.Bottom();
        case FOCUS_DIRECTION_UP:
        case FOCUS_DIRECTION_DOWN:
            return nodeRect.Left() < itemRect.Right() && itemRect.Left() < nodeRect.Right();
        default:
            break;
    }
    return false;
}

bool JsAccessibilityManager::IsToDirectionOf(Rect nodeRect, Rect itemRect, const int direction)
{
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
            return nodeRect.Left() >= itemRect.Right();
        case FOCUS_DIRECTION_RIGHT:
            return nodeRect.Right() <= itemRect.Left();
        case FOCUS_DIRECTION_UP:
            return nodeRect.Top() >= itemRect.Bottom();
        case FOCUS_DIRECTION_DOWN:
            return nodeRect.Bottom() <= itemRect.Top();
        default:
            break;
    }
    return false;
}

double JsAccessibilityManager::MajorAxisDistanceToFarEdge(Rect nodeRect, Rect itemRect, const int direction)
{
    double distance = 0.0;
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
            distance = nodeRect.Left() - itemRect.Left();
            break;
        case FOCUS_DIRECTION_RIGHT:
            distance = nodeRect.Right() - itemRect.Right();
            break;
        case FOCUS_DIRECTION_UP:
            distance = nodeRect.Top() - itemRect.Top();
            break;
        case FOCUS_DIRECTION_DOWN:
            distance = nodeRect.Bottom() - itemRect.Bottom();
            break;
        default:
            break;
    }

    return distance > 1.0 ? distance : 1.0;
}

double JsAccessibilityManager::MajorAxisDistance(Rect nodeRect, Rect itemRect, const int direction)
{
    double distance = 0.0;
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
            distance = nodeRect.Left() - itemRect.Right();
            break;
        case FOCUS_DIRECTION_RIGHT:
            distance = nodeRect.Right() - itemRect.Left();
            break;
        case FOCUS_DIRECTION_UP:
            distance = nodeRect.Top() - itemRect.Bottom();
            break;
        case FOCUS_DIRECTION_DOWN:
            distance = nodeRect.Bottom() - itemRect.Top();
            break;
        default:
            break;
    }

    return distance > 0.0 ? distance : 0.0;
}

double JsAccessibilityManager::MinorAxisDistance(Rect nodeRect, Rect itemRect, const int direction)
{
    double distance = 0.0;
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
        case FOCUS_DIRECTION_RIGHT:
            distance = (nodeRect.Top() + nodeRect.Bottom()) / 2 - (itemRect.Top() + itemRect.Bottom()) / 2;
            break;
        case FOCUS_DIRECTION_UP:
        case FOCUS_DIRECTION_DOWN:
            distance = (nodeRect.Left() + nodeRect.Right()) / 2 - (itemRect.Left() + itemRect.Right()) / 2;
            break;
        default:
            break;
    }

    return distance > 0.0 ? distance : -distance;
}

double JsAccessibilityManager::GetWeightedDistanceFor(double majorAxisDistance, double minorAxisDistance)
{
    return WEIGHTED_VALUE * majorAxisDistance * majorAxisDistance + minorAxisDistance * minorAxisDistance;
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
    if (currentFocusNode != nullptr) {
        currentFocusNodeId_ = -1;
        currentFocusNode->SetFocusedState(false);
        currentFocusNode->SetAccessibilityFocusedState(false);
        LOGI("ClearCurrentFocus SetFocusedState false nodeId:%{public}d", currentFocusNode->GetNodeId());
        return currentFocusNode->ActionAccessibilityFocus(false);
    }
    return false;
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

} // namespace OHOS::Ace::Framework
