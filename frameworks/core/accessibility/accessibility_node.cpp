/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/accessibility/accessibility_node.h"

#include "core/common/container.h"
namespace OHOS::Ace {
using ChartValue = std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>;
namespace {

const char ACCESSIBILITY_VALUE[] = "value";
const char ACCESSIBILITY_TYPE[] = "type";
const char ACCESSIBILITY_DISABLED[] = "disabled";
const char ACCESSIBILITY_GROUP[] = "accessibilitygroup";
const char ACCESSIBILITY_TEXT[] = "accessibilitytext";
const char ACCESSIBILITY_DESCRIPTION[] = "accessibilitydescription";
const char ACCESSIBILITY_IMPORTANCE[] = "accessibilityimportance";
const char ACCESSIBILITY_SHOW[] = "show";
const char ID[] = "id";

const char INPUT_TYPE_CHECKBOX[] = "checkbox";
const char INPUT_TYPE_RADIO[] = "radio";
const char INPUT_TYPE_PASSWORD[] = "password";

// common event definition
const char ACCESSIBILITY_EVENT[] = "accessibility";
const char CLICK[] = "click";
const char LONG_PRESS[] = "longpress";
const char FOCUS[] = "focus";
const char BLUR[] = "blur";

inline bool StringToBool(const std::string& value)
{
    return value == "true";
}

void MergeItems(const std::vector<std::pair<std::string, std::string>>& newItems,
    std::vector<std::pair<std::string, std::string>>& items)
{
    if (items.empty()) {
        items = newItems;
    } else {
        std::unordered_map<std::string, std::string> originItems;
        std::vector<std::pair<std::string, std::string>> sameVec;
        std::vector<std::pair<std::string, std::string>> diffVec;
        for (const auto& item: items) {
            originItems[item.first] = item.second;
        }

        for (const auto& item: newItems) {
            originItems[item.first] = item.second;
        }

        // find same element
        for (auto item = items.begin(); item != items.end(); item++) {
            const auto iter = originItems.find(item->first);
            if (iter != originItems.end()) {
                sameVec.emplace_back(iter->first, iter->second);
            }
        }

        // find different element
        for (auto newItem = newItems.begin(); newItem != newItems.end(); newItem++) {
            size_t diffFlagCount = 0;
            for (auto item = items.begin(); item != items.end(); item++) {
                if (newItem->first != item->first) {
                    diffFlagCount++;
                }
            }
            if (diffFlagCount == items.size()) {
                diffVec.emplace_back(newItem->first, newItem->second);
            }
        }
        sameVec.insert(sameVec.end(), diffVec.begin(), diffVec.end());
        items.clear();
        items = sameVec;
    }
}

} // namespace

AccessibilityNode::AccessibilityNode(NodeId nodeId, const std::string& nodeName) : nodeId_(nodeId), tag_(nodeName)
{
    // Initialize member variable in bitfield
    isEnabled_ = true;
    visible_ = true;
    shown_ = true;
}

void AccessibilityNode::SetActionClickImpl(const ActionClickImpl& actionClickImpl)
{
    actionClickImpl_ = actionClickImpl;
}

bool AccessibilityNode::ActionClick()
{
    if (actionClickImpl_) {
        actionClickImpl_();
        return true;
    }
    return false;
}

void AccessibilityNode::SetActionLongClickImpl(const ActionLongClickImpl& actionLongClickImpl)
{
    actionLongClickImpl_ = actionLongClickImpl;
}

bool AccessibilityNode::ActionLongClick()
{
    if (actionLongClickImpl_) {
        actionLongClickImpl_();
        return true;
    }
    return false;
}

void AccessibilityNode::SetActionSetTextImpl(const ActionSetTextImpl& actionSetTextImpl)
{
    actionSetTextImpl_ = actionSetTextImpl;
}

bool AccessibilityNode::ActionSetText(const std::string& text)
{
    if (actionSetTextImpl_) {
        actionSetTextImpl_(text);
        return true;
    }
    return false;
}

void AccessibilityNode::SetActionScrollForward(const ActionScrollForwardImpl& actionScrollForwardImpl)
{
    actionScrollForwardImpl_ = actionScrollForwardImpl;
}

bool AccessibilityNode::ActionScrollForward()
{
    if (actionScrollForwardImpl_) {
        return actionScrollForwardImpl_();
    }
    return false;
}

void AccessibilityNode::SetActionScrollBackward(const ActionScrollBackwardImpl& actionScrollBackwardImpl)
{
    actionScrollBackwardImpl_ = actionScrollBackwardImpl;
}

bool AccessibilityNode::ActionScrollBackward()
{
    if (actionScrollBackwardImpl_) {
        return actionScrollBackwardImpl_();
    }
    return false;
}

void AccessibilityNode::SetActionAccessibilityFocusImpl(
    const ActionAccessibilityFocusImpl& actionAccessibilityFocusImpl)
{
    actionAccessibilityFocusIdsImpl_ = actionAccessibilityFocusImpl;
}

bool AccessibilityNode::ActionAccessibilityFocus(bool isFocus)
{
    if (actionAccessibilityFocusIdsImpl_) {
        actionAccessibilityFocusIdsImpl_(isFocus);
        return true;
    }
    return false;
}

void AccessibilityNode::SetActionFocusImpl(const ActionFocusImpl& actionFocusImpl)
{
    actionFocusImpl_ = actionFocusImpl;
}

bool AccessibilityNode::ActionFocus()
{
    if (actionFocusImpl_) {
        actionFocusImpl_();
        return true;
    }
    return false;
}

void AccessibilityNode::SetActionUpdateIdsImpl(const ActionUpdateIdsImpl& actionUpdateIdsImpl)
{
    actionUpdateIdsImpl_ = actionUpdateIdsImpl;
}

void AccessibilityNode::ActionUpdateIds()
{
    if (actionUpdateIdsImpl_) {
        actionUpdateIdsImpl_();
    }
}

void AccessibilityNode::SetParentNode(const RefPtr<AccessibilityNode>& parentNode)
{
    parentNode_ = parentNode;
}

void AccessibilityNode::SetPositionInfo(const PositionInfo& positionInfo)
{
    rect_.SetRect(positionInfo.left, positionInfo.top, positionInfo.width, positionInfo.height);
}

void AccessibilityNode::SetAttr(const std::vector<std::pair<std::string, std::string>>& attrs)
{
    MergeItems(attrs, attrs_);

    for (const auto& attr : attrs) {
        if (attr.first == ACCESSIBILITY_VALUE) {
            text_ = attr.second;
            if (tag_ == ACCESSIBILITY_TAG_TEXT && parentNode_.Upgrade() &&
                parentNode_.Upgrade()->GetTag() == ACCESSIBILITY_TAG_POPUP) {
                auto spParent = parentNode_.Upgrade();
                auto parentText = spParent->GetText() + text_;
                spParent->SetText(parentText);
            }
        } else if (attr.first == ACCESSIBILITY_DISABLED) {
            isEnabled_ = !StringToBool(attr.second);
        } else if (attr.first == ACCESSIBILITY_TYPE) {
            inputType_ = attr.second;
        } else if (attr.first == ACCESSIBILITY_GROUP) {
            accessible_ = StringToBool(attr.second);
        } else if (attr.first == ACCESSIBILITY_TEXT) {
            accessibilityLabel_ = attr.second;
        } else if (attr.first == ACCESSIBILITY_DESCRIPTION) {
            accessibilityHint_ = attr.second;
        } else if (attr.first == ACCESSIBILITY_IMPORTANCE) {
            importantForAccessibility_ = attr.second;
        } else if (attr.first == ID) {
            jsComponentId_ = attr.second;
        } else if (attr.first == ACCESSIBILITY_SHOW) {
            shown_ = attr.second == "true";
        }
    }
    SetOperableInfo();
}

void AccessibilityNode::SetStyle(const std::vector<std::pair<std::string, std::string>>& styles)
{
    MergeItems(styles, styles_);
}

void AccessibilityNode::AddEvent(int32_t pageId, const std::vector<std::string>& events)
{
    for (const auto& event : events) {
        if (event == ACCESSIBILITY_EVENT) {
            onAccessibilityEventId_ = EventMarker(std::to_string(nodeId_), event, pageId);
        } else if (event == CLICK) {
            onClickId_ = EventMarker(std::to_string(nodeId_), event, pageId);
            SetClickableState(true);
        } else if (event == LONG_PRESS) {
            onLongPressId_ = EventMarker(std::to_string(nodeId_), event, pageId);
            SetLongClickableState(true);
        } else if (event == FOCUS) {
            onFocusId_ = EventMarker(std::to_string(nodeId_), event, pageId);
        } else if (event == BLUR) {
            onBlurId_ = EventMarker(std::to_string(nodeId_), event, pageId);
        }
    }
    AddSupportAction(AceAction::CUSTOM_ACTION);
    AddSupportAction(AceAction::GLOBAL_ACTION_BACK);
}

void AccessibilityNode::AddNode(const RefPtr<AccessibilityNode>& node, int32_t slot)
{
    CHECK_NULL_VOID(node);
    auto isExist = std::find_if(children_.begin(), children_.end(),
        [node](const RefPtr<AccessibilityNode>& child) { return child->GetNodeId() == node->GetNodeId(); });
    if (isExist != children_.end()) {
        return;
    }
    auto pos = children_.begin();
    std::advance(pos, slot);
    children_.insert(pos, node);
}

void AccessibilityNode::RemoveNode(const RefPtr<AccessibilityNode>& node)
{
    CHECK_NULL_VOID(node);
    children_.remove_if(
        [node](const RefPtr<AccessibilityNode>& child) { return node->GetNodeId() == child->GetNodeId(); });
}

void AccessibilityNode::Mount(int32_t slot)
{
    auto parentNode = parentNode_.Upgrade();
    CHECK_NULL_VOID(parentNode);
    parentNode->AddNode(AceType::Claim(this), slot);
}

void AccessibilityNode::AddOffsetForChildren(const Offset& offset)
{
    SetLeft(GetLeft() + offset.GetX());
    SetTop(GetTop() + offset.GetY());
    for (const auto& child : GetChildList()) {
        child->AddOffsetForChildren(offset);
    }
}

void AccessibilityNode::SetOperableInfo()
{
    static const LinearMapNode<OperableInfo> nodeOperatorMap[] = {
        { ACCESSIBILITY_TAG_BUTTON,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_CALENDAR,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_CANVAS,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_CHART,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_CLOCK,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_DIALOG,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_DIV,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_DIVIDER,
            { .checkable = false, .clickable = false, .scrollable = false,
              .longClickable = false, .focusable = false } },
        { ACCESSIBILITY_TAG_IMAGE,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_INPUT,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_LABEL,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_LIST,
            { .checkable = false, .clickable = true, .scrollable = true, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_LIST_ITEM,
            { .checkable = false, .clickable = true, .scrollable = true, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_LIST_ITEM_GROUP,
            { .checkable = false, .clickable = true, .scrollable = true, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_MARQUEE,
            { .checkable = false, .clickable = true, .scrollable = true, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_NAVIGATION_BAR,
            { .checkable = false, .clickable = true, .scrollable = true, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_OPTION,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_POPUP,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_PROGRESS,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_RATING,
            { .checkable = false, .clickable = true, .scrollable = true, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_REFRESH,
            { .checkable = false, .clickable = true, .scrollable = true, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_SELECT,
            { .checkable = false, .clickable = true, .scrollable = true, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_SLIDER,
            { .checkable = false, .clickable = true, .scrollable = true, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_SPAN,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_STACK,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_SWIPER,
            { .checkable = false, .clickable = true, .scrollable = true, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_SWITCH,
            { .checkable = true, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_TAB_BAR,
            { .checkable = false, .clickable = true, .scrollable = true, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_TAB_CONTENT,
            { .checkable = false, .clickable = true, .scrollable = true, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_TABS,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_TEXT,
            { .checkable = false, .clickable = true, .scrollable = true, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_TEXTAREA,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
        { ACCESSIBILITY_TAG_VIDEO,
            { .checkable = false, .clickable = true, .scrollable = false, .longClickable = true, .focusable = true } },
    };

    // set node operable info
    int64_t operateIter = BinarySearchFindIndex(nodeOperatorMap, ArraySize(nodeOperatorMap), tag_.c_str());
    if (operateIter != -1) {
        isCheckable_ = nodeOperatorMap[operateIter].value.checkable;
        isScrollable_ = nodeOperatorMap[operateIter].value.scrollable;
        isFocusable_ = nodeOperatorMap[operateIter].value.focusable;
        if (isFocusable_) {
            AddSupportAction(AceAction::ACTION_FOCUS);
        }
    } else {
        isCheckable_ = false;
        isClickable_ = false;
        isScrollable_ = false;
        isLongClickable_ = false;
        isFocusable_ = false;
    }

    if (tag_ == ACCESSIBILITY_TAG_INPUT) {
        if (inputType_ == INPUT_TYPE_CHECKBOX || inputType_ == INPUT_TYPE_RADIO) {
            isCheckable_ = true;
        } else if (inputType_ == INPUT_TYPE_PASSWORD) {
            isPassword_ = true;
        }
    }
}

std::unordered_set<AceAction> AccessibilityNode::GetSupportAction(uint64_t enableActions) const
{
    static const AceAction allActions[] = {
        AceAction::ACTION_NONE, AceAction::GLOBAL_ACTION_BACK, AceAction::CUSTOM_ACTION, AceAction::ACTION_CLICK,
        AceAction::ACTION_LONG_CLICK, AceAction::ACTION_SCROLL_FORWARD, AceAction::ACTION_SCROLL_BACKWARD,
        AceAction::ACTION_FOCUS, AceAction::ACTION_ACCESSIBILITY_FOCUS, AceAction::ACTION_CLEAR_ACCESSIBILITY_FOCUS,
        AceAction::ACTION_NEXT_AT_MOVEMENT_GRANULARITY, AceAction::ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY,
        AceAction::ACTION_SET_TEXT,
    };

    std::unordered_set<AceAction> supportActions;
    if (supportActions_ == 0) {
        return supportActions;
    }

    auto finalSupportActions = supportActions_ & enableActions;
    for (auto action : allActions) {
        if ((finalSupportActions & (1UL << static_cast<uint32_t>(action))) != 0) {
            supportActions.emplace(action);
        }
    }
    return supportActions;
}

void AccessibilityNode::SetFocusChangeEventMarker(const EventMarker& eventId)
{
    if (eventId.IsEmpty()) {
        return;
    }

    auto container = Container::Current();
    CHECK_NULL_VOID(container);
#ifndef NG_BUILD
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    focusChangeEventId_ =
        AceAsyncEvent<void(const std::string&)>::Create(eventId, pipelineContext);
#endif
}

void AccessibilityNode::OnFocusChange(bool isFocus)
{
    CHECK_NULL_VOID(focusChangeEventId_);
    auto json = JsonUtil::Create(true);
    json->Put("eventType", isFocused_ ? "1" : "2");
    focusChangeEventId_(json->ToString());
}

void AccessibilityNode::SetWindowId(uint32_t windowId)
{
    windowId_ = windowId;
}

uint32_t AccessibilityNode::GetWindowId() const
{
    return windowId_;
}

void AccessibilityNode::SetIsRootNode(bool isRootNode)
{
    isRootNode_ = isRootNode;
}

bool AccessibilityNode::IsRootNode() const
{
    return isRootNode_;
}

void AccessibilityNode::ResetChildList(std::list<RefPtr<AccessibilityNode>>& children)
{
    children_.clear();
    children_.swap(children);
}

const std::list<RefPtr<AccessibilityNode>> AccessibilityNode::GetChildList() const
{
    return children_;
}

NodeId AccessibilityNode::GetParentId() const
{
    auto parentNode = parentNode_.Upgrade();
    return parentNode ? parentNode->GetNodeId() : -1;
}

RefPtr<AccessibilityNode> AccessibilityNode::GetParentNode() const
{
    return parentNode_.Upgrade();
}

const std::string& AccessibilityNode::GetTag() const
{
    return tag_;
}

void AccessibilityNode::SetTag(const std::string& tag)
{
    tag_ = tag;
}

int32_t AccessibilityNode::GetPageId() const
{
    return pageId_;
}

void AccessibilityNode::SetPageId(int32_t pageId)
{
    pageId_ = pageId;
}

const EventMarker& AccessibilityNode::GetAccessibilityEventMarker() const
{
    return onAccessibilityEventId_;
}

const EventMarker& AccessibilityNode::GetClickEventMarker() const
{
    return onClickId_;
}

const EventMarker& AccessibilityNode::GetLongPressEventMarker() const
{
    return onLongPressId_;
}

const EventMarker& AccessibilityNode::GetSetTextEventMarker() const
{
    return onSetTextId_;
}

const EventMarker& AccessibilityNode::GetFocusEventMarker() const
{
    return onFocusId_;
}

const EventMarker& AccessibilityNode::GetBlurEventMarker() const
{
    return onBlurId_;
}

NodeId AccessibilityNode::GetNodeId() const
{
    return nodeId_;
}

const std::string& AccessibilityNode::GetText() const
{
    return text_;
}

void AccessibilityNode::SetText(const std::string& text)
{
    text_ = text;
}

const std::string& AccessibilityNode::GetHintText() const
{
    return hintText_;
}

void AccessibilityNode::SetHintText(const std::string& hintText)
{
    hintText_ = hintText;
}

const std::vector<int32_t>& AccessibilityNode::GetChildIds() const
{
    return childIds_;
}

void AccessibilityNode::SetChildIds(const std::vector<int32_t>& ids)
{
    childIds_ = ids;
}

double AccessibilityNode::GetWidth() const
{
    return rect_.Width();
}

void AccessibilityNode::SetWidth(double width)
{
    rect_.SetWidth(width);
}

double AccessibilityNode::GetHeight() const
{
    return rect_.Height();
}

void AccessibilityNode::SetHeight(double height)
{
    rect_.SetHeight(height);
}

double AccessibilityNode::GetLeft() const
{
    return rect_.Left();
}

void AccessibilityNode::SetLeft(double left)
{
    return rect_.SetLeft(left);
}

double AccessibilityNode::GetTop() const
{
    return rect_.Top();
}

void AccessibilityNode::SetTop(double top)
{
    return rect_.SetTop(top);
}

bool AccessibilityNode::GetCheckedState() const
{
    return isChecked_;
}

void AccessibilityNode::SetCheckedState(bool state)
{
    isChecked_ = state;
}

bool AccessibilityNode::GetEnabledState() const
{
    return isEnabled_;
}

void AccessibilityNode::SetEnabledState(bool state)
{
    isEnabled_ = state;
}

bool AccessibilityNode::GetEditable() const
{
    return isEditable_;
}

void AccessibilityNode::SetEditable(bool editable)
{
    isEditable_ = editable;
}

bool AccessibilityNode::GetFocusedState() const
{
    return isFocused_;
}

void AccessibilityNode::SetFocusedState(bool state)
{
    isFocused_ = state;
    OnFocusChange(isFocused_);
}

bool AccessibilityNode::GetAccessibilityFocusedState() const
{
    return isAccessibilityFocused_;
}

void AccessibilityNode::SetAccessibilityFocusedState(bool state)
{
    isAccessibilityFocused_ = state;
}

bool AccessibilityNode::GetSelectedState() const
{
    return isSelected_;
}

void AccessibilityNode::SetSelectedState(bool state)
{
    isSelected_ = state;
}

bool AccessibilityNode::GetCheckableState() const
{
    return isCheckable_;
}

void AccessibilityNode::SetCheckableState(bool state)
{
    isCheckable_ = state;
}

bool AccessibilityNode::GetClickableState() const
{
    return isClickable_;
}

void AccessibilityNode::SetClickableState(bool state)
{
    isClickable_ = state;
    SetSupportAction(AceAction::ACTION_CLICK, state);
}

bool AccessibilityNode::GetFocusableState() const
{
    return isFocusable_;
}

void AccessibilityNode::SetFocusableState(bool state)
{
    isFocusable_ = state;
}

bool AccessibilityNode::GetScrollableState() const
{
    return isScrollable_;
}

void AccessibilityNode::SetScrollableState(bool state)
{
    isScrollable_ = state;
}

bool AccessibilityNode::GetLongClickableState() const
{
    return isLongClickable_;
}

void AccessibilityNode::SetLongClickableState(bool state)
{
    isLongClickable_ = state;
    SetSupportAction(AceAction::ACTION_LONG_CLICK, state);
}

bool AccessibilityNode::GetIsMultiLine() const
{
    return isMultiLine_;
}

void AccessibilityNode::SetIsMultiLine(bool multiLine)
{
    isMultiLine_ = multiLine;
}

bool AccessibilityNode::GetIsPassword() const
{
    return isPassword_;
}

void AccessibilityNode::SetIsPassword(bool isPassword)
{
    isPassword_ = isPassword;
}

void AccessibilityNode::AddSupportAction(AceAction action)
{
    supportActions_ |= (1UL << static_cast<uint32_t>(action));
}

void AccessibilityNode::SetSupportAction(AceAction action, bool isEnable)
{
    isEnable ? supportActions_ |= (1UL << static_cast<uint32_t>(action))
                : supportActions_ &= (~(0UL)) ^ (1UL << static_cast<uint32_t>(action));
}

const std::string& AccessibilityNode::GetAccessibilityLabel() const
{
    return accessibilityLabel_;
}

void AccessibilityNode::SetAccessibilityLabel(const std::string& label)
{
    accessibilityLabel_ = label;
}

const std::string& AccessibilityNode::GetAccessibilityHint() const
{
    return accessibilityHint_;
}

void AccessibilityNode::SetAccessibilityHint(const std::string& hint)
{
    accessibilityHint_ = hint;
}

const std::string& AccessibilityNode::GetImportantForAccessibility() const
{
    return importantForAccessibility_;
}

void AccessibilityNode::SetImportantForAccessibility(const std::string& importance)
{
    importantForAccessibility_ = importance;
}

size_t AccessibilityNode::GetMaxTextLength() const
{
    return maxTextLength_;
}

void AccessibilityNode::SetMaxTextLength(size_t length)
{
    maxTextLength_ = length;
}

int32_t AccessibilityNode::GetTextSelectionStart() const
{
    return textSelectionStart_;
}

void AccessibilityNode::SetTextSelectionStart(int32_t start)
{
    textSelectionStart_ = start;
}

int32_t AccessibilityNode::GetTextSelectionEnd() const
{
    return textSelectionEnd_;
}

void AccessibilityNode::SetTextSelectionEnd(int32_t end)
{
    textSelectionEnd_ = end;
}

const std::string& AccessibilityNode::GetErrorText() const
{
    return errorText_;
}

void AccessibilityNode::SetErrorText(const std::string& errorText)
{
    errorText_ = errorText;
}

const std::string& AccessibilityNode::GetJsComponentId() const
{
    return jsComponentId_;
}

void AccessibilityNode::SetJsComponentId(const std::string& jsComponentId)
{
    jsComponentId_ = jsComponentId;
}

bool AccessibilityNode::GetAccessible() const
{
    return accessible_;
}

void AccessibilityNode::SetAccessible(bool accessible)
{
    accessible_ = accessible;
}

AccessibilityValue AccessibilityNode::GetAccessibilityValue() const
{
    return accessibilityValue_;
}

void AccessibilityNode::SetAccessibilityValue(double cur, double min, double max)
{
    accessibilityValue_.current = cur;
    accessibilityValue_.min = min;
    accessibilityValue_.max = max;
}

const std::unique_ptr<ChartValue>& AccessibilityNode::GetChartValue() const
{
    return chartValue_;
}

void AccessibilityNode::PutChartValue(
    const std::string& groupName, const std::vector<std::pair<std::string, double>>& values)
{
    if (!chartValue_) {
        chartValue_ = std::make_unique<ChartValue>();
    }

    auto result = chartValue_->try_emplace(groupName, values);
    if (!result.second) {
        result.first->second = values;
    }
}

std::string AccessibilityNode::GetInputType() const
{
    return inputType_;
}

AceTextCategory AccessibilityNode::GetTextInputType() const
{
    return textInputType_;
}

void AccessibilityNode::SetTextInputType(AceTextCategory type)
{
    textInputType_ = type;
}

const AceCollectionInfo& AccessibilityNode::GetCollectionInfo() const
{
    return collectionInfo_;
}

void AccessibilityNode::SetCollectionInfo(const AceCollectionInfo& collectionInfo)
{
    collectionInfo_ = collectionInfo;
}

const AceCollectionItemInfo& AccessibilityNode::GetCollectionItemInfo() const
{
    return collectionItemInfo_;
}

void AccessibilityNode::SetCollectionItemInfo(const AceCollectionItemInfo& collectionItemInfo)
{
    collectionItemInfo_ = collectionItemInfo;
}

bool AccessibilityNode::GetShown() const
{
    return shown_;
}

bool AccessibilityNode::GetVisible() const
{
    return visible_;
}

void AccessibilityNode::SetVisible(bool visible)
{
    visible_ = visible;
}

const Rect& AccessibilityNode::GetRect() const
{
    return rect_;
}

void AccessibilityNode::SetRect(const Rect& rect)
{
    isValidRect_ = rect.IsValid();
    if (isValidRect_) {
        rect_ = rect;
    }
}
} // namespace OHOS::Ace
