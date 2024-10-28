/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "accessibility_property.h"

#include "core/accessibility/accessibility_constants.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
constexpr uint64_t ACTIONS = std::numeric_limits<uint64_t>::max();
std::unordered_set<AceAction> AccessibilityProperty::GetSupportAction() const
{
    static const AceAction allActions[] = {
        AceAction::ACTION_NONE,
        AceAction::GLOBAL_ACTION_BACK,
        AceAction::CUSTOM_ACTION,
        AceAction::ACTION_CLICK,
        AceAction::ACTION_LONG_CLICK,
        AceAction::ACTION_SCROLL_FORWARD,
        AceAction::ACTION_SCROLL_BACKWARD,
        AceAction::ACTION_FOCUS,
        AceAction::ACTION_CLEAR_FOCUS,
        AceAction::ACTION_ACCESSIBILITY_FOCUS,
        AceAction::ACTION_CLEAR_ACCESSIBILITY_FOCUS,
        AceAction::ACTION_NEXT_AT_MOVEMENT_GRANULARITY,
        AceAction::ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY,
        AceAction::ACTION_SET_TEXT,
        AceAction::ACTION_COPY,
        AceAction::ACTION_PASTE,
        AceAction::ACTION_CUT,
        AceAction::ACTION_SELECT,
        AceAction::ACTION_SET_SELECTION,
        AceAction::ACTION_CLEAR_SELECTION,
        AceAction::ACTION_SET_CURSOR_POSITION,
        AceAction::ACTION_EXEC_SUB_COMPONENT,
    };

    std::unordered_set<AceAction> supportActions;
    if (supportActions_ == 0) {
        return supportActions;
    }

    auto finalSupportActions = supportActions_ & ACTIONS;
    for (auto action : allActions) {
        if ((finalSupportActions & (1UL << static_cast<uint32_t>(action))) != 0) {
            supportActions.emplace(action);
        }
    }
    return supportActions;
}

std::string AccessibilityProperty::GetText() const
{
    return propText_.value_or("");
}

std::string AccessibilityProperty::GetGroupText(bool forceGetChildren) const
{
    std::string text;
    GetGroupTextRecursive(forceGetChildren, text, false);
    return text;
}

std::string AccessibilityProperty::GetGroupPreferAccessibilityText(bool forceGetChildren) const
{
    std::string text;
    GetGroupTextRecursive(forceGetChildren, text, true);
    return text;
}

void AccessibilityProperty::GetGroupTextRecursive(bool forceGetChildren, std::string& text,
                                                  bool preferAccessibilityText) const
{
    auto node = host_.Upgrade();
    CHECK_NULL_VOID(node);
    if (node->IsInternal()) {
        return;
    }
    auto level = GetAccessibilityLevel();
    if (level == Level::AUTO || level == Level::YES_STR) {
        std::string accessibilityText = GetAccessibilityText();
        auto nodeText = preferAccessibilityText && !accessibilityText.empty() ? accessibilityText : GetText();
        if (!text.empty() && !nodeText.empty()) {
            text += ", ";
        }
        text += nodeText;
    } else if (level == Level::NO_HIDE_DESCENDANTS) {
        return;
    }
    // Do not change text if level is no

    if (!(forceGetChildren || IsAccessibilityGroup())) {
        return;
    }
    auto& children = node->GetFrameChildren();
    for (auto& childWeak : children) {
        auto child = childWeak.Upgrade();
        if (child == nullptr) {
            continue;
        }
        child->GetAccessibilityProperty<AccessibilityProperty>()->GetGroupTextRecursive(true, text,
                                                                                        preferAccessibilityText);
    }
}

float AccessibilityProperty::GetScrollOffSet() const
{
    return DEFAULT_ACCESSIBILITY_SCROLL_OFFSET;
}

AccessibilityHoverTestPath AccessibilityProperty::HoverTest(
    const PointF& point,
    const RefPtr<FrameNode>& root,
    std::unique_ptr<HoverTestDebugTraceInfo>& debugInfo)
{
    AccessibilityHoverTestPath path;
    CHECK_NULL_RETURN(root, path);
    ACE_SCOPED_TRACE("AccessibilityHoverTest");
    bool ancestorGroupFlag = false;
    auto accessibilityProperty = root->GetAccessibilityProperty<NG::AccessibilityProperty>();
    if (accessibilityProperty != nullptr) {
        ancestorGroupFlag = accessibilityProperty->IsAccessibilityGroup();
    }
    AccessibilityProperty::HoverTestRecursive(point, root, path, debugInfo, ancestorGroupFlag);
    return path;
}

void GetHitTestModeStr(HitTestMode hitTestMode, std::string& testModeStr)
{
    switch (hitTestMode) {
        case HitTestMode::HTMDEFAULT:
            testModeStr = "Default";
            break;
        case HitTestMode::HTMBLOCK:
            testModeStr = "Block";
            break;
        case HitTestMode::HTMTRANSPARENT:
            testModeStr = "Transparent";
            break;
        case HitTestMode::HTMNONE:
            testModeStr = "None";
            break;
        default:
            testModeStr = "Unsupported";
    }
}

std::unique_ptr<JsonValue> AccessibilityProperty::CreateNodeSearchInfo(const RefPtr<FrameNode>& node,
    const PointF& parentPoint, bool& ancestorGroupFlag)
{
    auto nodeInfo = JsonUtil::Create();
    nodeInfo->Put("id", node->GetAccessibilityId());
    nodeInfo->Put("tag", node->GetTag().c_str());
    if (!node->IsRootNode()) {
        if (node->GetParent()) {
            nodeInfo->Put("parent", node->GetParent()->GetAccessibilityId());
        } else {
            nodeInfo->Put("parent", -1);
        }
    }
    nodeInfo->Put("visible", node->IsVisible());
    auto [shouldSearchSelf, shouldSearchChildren, groupFlag]
        = AccessibilityProperty::GetSearchStrategy(node, ancestorGroupFlag);
    nodeInfo->Put("shouldSearchSelf", shouldSearchSelf);
    nodeInfo->Put("shouldSearchChildren", shouldSearchChildren);
    nodeInfo->Put("currentGroup", groupFlag);

    auto renderContext = node->GetRenderContext();
    auto rect = renderContext->GetPaintRectWithoutTransform();
    PointF selfPoint = parentPoint;
    renderContext->GetPointWithRevert(selfPoint);
    bool hitSelf = rect.IsInnerRegion(selfPoint);
    nodeInfo->Put("hitNode", hitSelf);
    nodeInfo->Put("rect", rect.ToString().c_str());
    nodeInfo->Put("hoverPoint", selfPoint.ToString().c_str());
    nodeInfo->Put("clip", renderContext->GetClipEdge().value_or(false));

    auto eventHub = node->GetEventHub<EventHub>();
    nodeInfo->Put("enabled", eventHub->IsEnabled());

    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    if (accessibilityProperty != nullptr) {
        nodeInfo->Put("accessibilityLevel", accessibilityProperty->GetAccessibilityLevel().c_str());
        nodeInfo->Put("accessibilityGroup", accessibilityProperty->IsAccessibilityGroup());
        nodeInfo->Put("hasVirtualNode", accessibilityProperty->HasAccessibilityVirtualNode());
        nodeInfo->Put("accessibilityText", accessibilityProperty->GetAccessibilityText().c_str());
        nodeInfo->Put("accessibilityDescription", accessibilityProperty->GetAccessibilityDescription().c_str());
    }

    std::string testModeStr = "";
    GetHitTestModeStr(node->GetHitTestMode(), testModeStr);
    nodeInfo->Put("hitTestMode", testModeStr.c_str());
    return nodeInfo;
}

bool AccessibilityProperty::ProcessHoverTestRecursive(const PointF& noOffsetPoint, const RefPtr<FrameNode>& node,
    AccessibilityHoverTestPath& path, std::unique_ptr<HoverTestDebugTraceInfo>& debugInfo,
    RecursiveParam recursiveParam)
{
    auto property = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    auto virtualNode = property->GetAccessibilityVirtualNode();
    if (virtualNode != nullptr) {
        auto frameNode = AceType::DynamicCast<FrameNode>(virtualNode);
        CHECK_NULL_RETURN(frameNode, false);

        if (AccessibilityProperty::HoverTestRecursive(noOffsetPoint, frameNode, path, debugInfo,
            recursiveParam.ancestorGroupFlag)) {
            return true;
        }
    } else {
        auto children = node->GetFrameChildren();
        for (auto childWeak = children.rbegin(); childWeak != children.rend(); ++childWeak) {
            auto child = childWeak->Upgrade();
            if (child == nullptr) {
                continue;
            }
            if (AccessibilityProperty::HoverTestRecursive(noOffsetPoint, child, path, debugInfo,
                recursiveParam.ancestorGroupFlag)) {
                return true;
            }
        }
    }
    return recursiveParam.hitTarget;
}

bool AccessibilityProperty::HoverTestRecursive(
    const PointF& parentPoint,
    const RefPtr<FrameNode>& node,
    AccessibilityHoverTestPath& path,
    std::unique_ptr<HoverTestDebugTraceInfo>& debugInfo,
    bool& ancestorGroupFlag)
{
    if (!node->IsAccessibilityVirtualNode()) {
        if (!node->IsActive() || node->IsInternal()) {
            return false;
        }
    }
    if (debugInfo != nullptr) {
        auto nodeInfo = CreateNodeSearchInfo(node, parentPoint, ancestorGroupFlag);
        debugInfo->trace.push_back(std::move(nodeInfo));
    }
    bool hitTarget = false;
    if (!node->IsVisible()) {
        return false;
    }

    auto [shouldSearchSelf, shouldSearchChildren, currentGroupFlag]
        = AccessibilityProperty::GetSearchStrategy(node, ancestorGroupFlag);

    auto renderContext = node->GetRenderContext();
    auto rect = renderContext->GetPaintRectWithoutTransform();
    PointF selfPoint = parentPoint;
    renderContext->GetPointWithRevert(selfPoint);
    bool hitSelf = rect.IsInnerRegion(selfPoint);
    if (hitSelf && shouldSearchSelf && IsAccessibilityFocusable(node)) {
        hitTarget = true;
        path.push_back(node);
    }
    bool hasClip = renderContext->GetClipEdge().value_or(false);
    if (hasClip && !hitSelf) {
        return false;
    }

    if (shouldSearchChildren) {
        PointF noOffsetPoint = selfPoint - rect.GetOffset();
        RecursiveParam recursiveParam;
        recursiveParam.hitTarget = hitTarget;
        recursiveParam.ancestorGroupFlag = currentGroupFlag;
        return ProcessHoverTestRecursive(noOffsetPoint, node, path, debugInfo, recursiveParam);
    }
    return hitTarget;
}

void UpdateSearchStrategyByHitTestMode(HitTestMode hitTestMode, bool& shouldSearchSelf, bool& shouldSearchChildren)
{
    switch (hitTestMode) {
        case HitTestMode::HTMBLOCK:
            shouldSearchChildren = false;
            break;
        case HitTestMode::HTMTRANSPARENT:
            break;
        case HitTestMode::HTMNONE:
            shouldSearchSelf = false;
            break;
        default:
            break;
    }
}

static const std::set<std::string> TAGS_SUBTREE_COMPONENT = {
    V2::XCOMPONENT_ETS_TAG,
    V2::UI_EXTENSION_COMPONENT_ETS_TAG,
    V2::EMBEDDED_COMPONENT_ETS_TAG,
    V2::FORM_ETS_TAG,
    V2::ISOLATED_COMPONENT_ETS_TAG
};

bool AccessibilityProperty::IsTagInSubTreeComponent(const std::string& tag)
{
    if (TAGS_SUBTREE_COMPONENT.find(tag) != TAGS_SUBTREE_COMPONENT.end()) {
        return true;
    }
    return false;
}

std::tuple<bool, bool, bool> AccessibilityProperty::GetSearchStrategy(const RefPtr<FrameNode>& node,
    bool& ancestorGroupFlag)
{
    bool shouldSearchSelf = true;
    bool shouldSearchChildren = true;
    bool currentGroupFlag = false;
    auto level = AccessibilityProperty::Level::AUTO;
    do {
        auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
        if (accessibilityProperty != nullptr) {
            level = accessibilityProperty->GetAccessibilityLevel();
            currentGroupFlag = accessibilityProperty->IsAccessibilityGroup();
            bool hasAccessibilityText = accessibilityProperty->HasAccessibilityTextOrDescription();
            if (level == AccessibilityProperty::Level::YES_STR) {
                break;
            } else if (level == AccessibilityProperty::Level::NO_HIDE_DESCENDANTS) {
                shouldSearchSelf = false;
                shouldSearchChildren = false;
                break;
            } else {
                if (level == AccessibilityProperty::Level::NO_STR) {
                    shouldSearchSelf = false;
                } else {
                    // shouldSearchSelf is true here
                    if (hasAccessibilityText) {
                        break;
                    }
                }
            }
        }
        auto eventHub = node->GetEventHub<EventHub>();
        if (!eventHub->IsEnabled()) {
            shouldSearchChildren = false;
            // Fall through to update `shouldSearchSelf`
        }
        HitTestMode hitTestMode = node->GetHitTestMode();
        UpdateSearchStrategyByHitTestMode(hitTestMode, shouldSearchSelf, shouldSearchChildren);
        if (accessibilityProperty != nullptr && accessibilityProperty->HasAccessibilityVirtualNode() &&
            accessibilityProperty->GetAccessibilityLevel() != AccessibilityProperty::Level::NO_HIDE_DESCENDANTS) {
            shouldSearchChildren = true;
        }
    } while (0);
    shouldSearchSelf = IsTagInSubTreeComponent(node->GetTag()) ? true : shouldSearchSelf;
    if (ancestorGroupFlag == true) {
        if (level != AccessibilityProperty::Level::YES_STR) {
            shouldSearchSelf = false;
        }
        currentGroupFlag = true;
    }

    return std::make_tuple(shouldSearchSelf, shouldSearchChildren, currentGroupFlag);
}

static const std::set<std::string> TAGS_FOCUSABLE = {
    V2::CHECKBOX_ETS_TAG,
    V2::CHECKBOXGROUP_ETS_TAG,
    V2::GAUGE_ETS_TAG,
    V2::MARQUEE_ETS_TAG,
    V2::MENU_ETS_TAG,
    V2::MENU_ITEM_ETS_TAG,
    V2::MENU_ITEM_GROUP_ETS_TAG,
    V2::NAVIGATION_VIEW_ETS_TAG,
    V2::DATE_PICKER_ETS_TAG,
    V2::PROGRESS_ETS_TAG,
    V2::RADIO_ETS_TAG,
    V2::RATING_ETS_TAG,
    V2::SCROLL_BAR_ETS_TAG,
    V2::SELECT_ETS_TAG,
    V2::SLIDER_ETS_TAG,
    V2::STEPPER_ETS_TAG,
    V2::TEXT_ETS_TAG,
    V2::TEXTCLOCK_ETS_TAG,
    V2::TEXT_PICKER_ETS_TAG,
    V2::TEXTTIMER_ETS_TAG,
    V2::TIME_PICKER_ETS_TAG,
    V2::TOGGLE_ETS_TAG,
    V2::WEB_ETS_TAG,
    V2::XCOMPONENT_ETS_TAG,
    V2::UI_EXTENSION_COMPONENT_ETS_TAG,
    V2::EMBEDDED_COMPONENT_ETS_TAG,
    V2::FORM_ETS_TAG
};

bool AccessibilityProperty::IsAccessibilityFocusableTag(const std::string &tag)
{
    if (TAGS_FOCUSABLE.find(tag) != TAGS_FOCUSABLE.end()) {
        return true;
    }
    return false;
}

bool AccessibilityProperty::IsAccessibilityFocusableDebug(const RefPtr<FrameNode>& node,
    std::unique_ptr<JsonValue>& info)
{
    bool focusable = IsAccessibilityFocusable(node);
    info->Put("id", node->GetAccessibilityId());
    info->Put("tag", node->GetTag().c_str());
    if (!node->IsRootNode()) {
        info->Put("parent", node->GetParent()->GetAccessibilityId());
    }
    info->Put("selected", focusable);

    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    if (accessibilityProperty != nullptr) {
        info->Put("accessibilityLevel", accessibilityProperty->GetAccessibilityLevel().c_str());
        info->Put("accessibilityGroup", accessibilityProperty->IsAccessibilityGroup());
        info->Put("hasVirtualNode", accessibilityProperty->HasAccessibilityVirtualNode());
        info->Put("accessibilityText", accessibilityProperty->GetAccessibilityText().c_str());
        info->Put("accessibilityDescription", accessibilityProperty->GetAccessibilityDescription().c_str());
        info->Put("text", accessibilityProperty->GetText().c_str());
        info->Put("hasAction", accessibilityProperty->HasAction());
    }

    auto eventHub = node->GetEventHub<EventHub>();
    info->Put("enabled", eventHub->IsEnabled());
    auto gestureEventHub = eventHub->GetGestureEventHub();
    if (gestureEventHub != nullptr) {
        info->Put("clickable", gestureEventHub->IsAccessibilityClickable());
        info->Put("longClickable", gestureEventHub->IsAccessibilityLongClickable());
    }
    return focusable;
}


bool AccessibilityProperty::IsAccessibilityFocusable(const RefPtr<FrameNode>& node)
{
    if (node->IsRootNode()) {
        return false;
    }
    bool focusable = false;
    do {
        auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
        if (accessibilityProperty != nullptr) {
            auto level = accessibilityProperty->GetAccessibilityLevel();
            if (level == AccessibilityProperty::Level::YES_STR) {
                focusable = true;
                break;
            }
            if (level == AccessibilityProperty::Level::NO_STR) {
                break;
            }
            if (accessibilityProperty->IsAccessibilityGroup() ||
                accessibilityProperty->HasAccessibilityVirtualNode() ||
                accessibilityProperty->HasAction() ||
                accessibilityProperty->HasAccessibilityTextOrDescription() ||
                !accessibilityProperty->GetText().empty()) {
                focusable = true;
                break;
            }
        }

        auto eventHub = node->GetEventHub<EventHub>();
        if (!eventHub->IsEnabled()) {
            focusable = true;
            break;
        }
        auto gestureEventHub = eventHub->GetGestureEventHub();
        if (gestureEventHub != nullptr) {
            if (gestureEventHub->IsAccessibilityClickable() ||
                gestureEventHub->IsAccessibilityLongClickable()) {
                focusable = true;
                break;
            }
        }

        if (TAGS_FOCUSABLE.find(node->GetTag()) != TAGS_FOCUSABLE.end()) {
            focusable = true;
            break;
        }
    } while (0);
    if (IsTagInSubTreeComponent(node->GetTag())) {
        focusable = true;
    }
    return focusable;
}

bool AccessibilityProperty::HasAccessibilityTextOrDescription() const
{
    return !accessibilityText_.value_or("").empty() ||
        !accessibilityDescription_.value_or("").empty();
}

bool AccessibilityProperty::HasAction() const
{
    return (supportActions_ & ACTIONS) != 0 ||
        IsCheckable() ||
        IsScrollable() ||
        IsEditable() ||
        IsDeletable();
}

void AccessibilityProperty::SetAccessibilityActions(uint32_t actions)
{
    accessibilityActions_ = actions;
}

void AccessibilityProperty::ResetAccessibilityActions()
{
    accessibilityActions_ = std::nullopt;
}

bool AccessibilityProperty::HasAccessibilityActions()
{
    return accessibilityActions_.has_value();
}

uint32_t AccessibilityProperty::GetAccessibilityActions() const
{
    return accessibilityActions_.value_or(0);
}

void AccessibilityProperty::SetAccessibilityRole(const std::string& role)
{
    accessibilityRole_ = role;
}

void AccessibilityProperty::ResetAccessibilityRole()
{
    accessibilityRole_ = std::nullopt;
}

bool AccessibilityProperty::HasAccessibilityRole()
{
    return accessibilityRole_.has_value();
}

std::string AccessibilityProperty::GetAccessibilityRole() const
{
    return accessibilityRole_.value_or("");
}

void AccessibilityProperty::SetActions(const ActionsImpl& actionsImpl)
{
    actionsImpl_ = actionsImpl;
}

bool AccessibilityProperty::ActionsDefined(uint32_t action)
{
    if (!HasAccessibilityActions()) {
        return false;
    }
    if (!actionsImpl_) {
        return false;
    }
    int result = GetAccessibilityActions() & action;
    return result != 0;
}

void AccessibilityProperty::SetUserDisabled(const bool& isDisabled)
{
    isDisabled_ = isDisabled;
}

bool AccessibilityProperty::HasUserDisabled()
{
    return isDisabled_.has_value();
}

bool AccessibilityProperty::IsUserDisabled()
{
    return isDisabled_.value_or(false);
}

void AccessibilityProperty::SetUserSelected(const bool& isSelected)
{
    isSelected_ = isSelected;
}

bool AccessibilityProperty::HasUserSelected()
{
    return isSelected_.has_value();
}

bool AccessibilityProperty::IsUserSelected()
{
    return isSelected_.value_or(false);
}

void AccessibilityProperty::ResetUserSelected()
{
    isSelected_.reset();
}

void AccessibilityProperty::SetUserCheckedType(const int32_t& checkedType)
{
    checkedType_ = checkedType;
}

bool AccessibilityProperty::HasUserCheckedType()
{
    return checkedType_.has_value();
}

int32_t AccessibilityProperty::GetUserCheckedType()
{
    return checkedType_.value_or(0);
}

void AccessibilityProperty::ResetUserCheckedType()
{
    checkedType_.reset();
}

void AccessibilityProperty::SetUserCheckable(const bool& checkable)
{
    isUserCheckable_ = checkable;
}

bool AccessibilityProperty::HasUserCheckable()
{
    return isUserCheckable_.has_value();
}

bool AccessibilityProperty::IsUserCheckable()
{
    return isUserCheckable_.value_or(false);
}

void AccessibilityProperty::ResetUserCheckable()
{
    isUserCheckable_.reset();
}

void AccessibilityProperty::SetUserMinValue(const int32_t& minValue)
{
    minValue_ = minValue;
}

bool AccessibilityProperty::HasUserMinValue()
{
    return minValue_.has_value();
}

int32_t AccessibilityProperty::GetUserMinValue()
{
    return minValue_.value_or(-1);
}

void AccessibilityProperty::SetUserMaxValue(const int32_t& maxValue)
{
    maxValue_ = maxValue;
}

bool AccessibilityProperty::HasUserMaxValue()
{
    return maxValue_.has_value();
}

int32_t AccessibilityProperty::GetUserMaxValue()
{
    return maxValue_.value_or(-1);
}

void AccessibilityProperty::SetUserCurrentValue(const int32_t& currentValue)
{
    currentValue_ = currentValue;
}

bool AccessibilityProperty::HasUserCurrentValue()
{
    return currentValue_.has_value();
}

int32_t AccessibilityProperty::GetUserCurrentValue()
{
    return currentValue_.value_or(-1);
}

void AccessibilityProperty::SetUserTextValue(const std::string& textValue)
{
    textValue_ = textValue;
}

bool AccessibilityProperty::HasUserTextValue()
{
    return textValue_.has_value();
}

std::string AccessibilityProperty::GetUserTextValue()
{
    return textValue_.value_or("");
}

bool AccessibilityProperty::GetAccessibilityFocusState() const
{
    return isAccessibilityFocused_;
}

void AccessibilityProperty::SetAccessibilityFocusState(bool state)
{
    isAccessibilityFocused_ = state;
}

void AccessibilityProperty::SetAccessibilityGroup(bool accessibilityGroup)
{
    accessibilityGroup_ = accessibilityGroup;
}

void AccessibilityProperty::SetChildTreeId(int32_t childTreeId)
{
    childTreeId_ = childTreeId;
}

void AccessibilityProperty::SetChildWindowId(int32_t childWindowId)
{
    childWindowId_ = childWindowId;
}

void AccessibilityProperty::SetAccessibilityText(const std::string& text)
{
    accessibilityText_ = text;
}

void AccessibilityProperty::SetAccessibilityTextWithEvent(const std::string& text)
{
    auto backupStr = accessibilityText_.value_or("");
    if (text == backupStr) {
        return;
    }
    accessibilityText_ = text;
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    frameNode->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, backupStr, text);
}

void AccessibilityProperty::SetAccessibilityTextHint(const std::string& text)
{
    textTypeHint_ = text;
}

void AccessibilityProperty::SetAccessibilityDescription(const std::string& accessibilityDescription)
{
    accessibilityDescription_ = accessibilityDescription;
}

void AccessibilityProperty::SetAccessibilityDescriptionWithEvent(const std::string& accessibilityDescription)
{
    auto backupStr = accessibilityDescription_.value_or("");
    if (accessibilityDescription == backupStr) {
        return;
    }
    accessibilityDescription_ = accessibilityDescription;
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    frameNode->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, backupStr, accessibilityDescription);
}

bool AccessibilityProperty::IsAccessibilityGroup() const
{
    return accessibilityGroup_;
}

int32_t AccessibilityProperty::GetChildTreeId() const
{
    return childTreeId_;
}

int32_t AccessibilityProperty::GetChildWindowId() const
{
    return childWindowId_;
}

void AccessibilityProperty::SaveAccessibilityVirtualNode(const RefPtr<UINode>& node)
{
    accessibilityVirtualNode_ = node;
}

RefPtr<UINode> AccessibilityProperty::GetAccessibilityVirtualNode()
{
    return accessibilityVirtualNode_;
}

NG::UINode* AccessibilityProperty::GetAccessibilityVirtualNodePtr()
{
    return Referenced::RawPtr(accessibilityVirtualNode_);
}

bool AccessibilityProperty::HasAccessibilityVirtualNode() const
{
    return accessibilityVirtualNode_ != nullptr;
}

std::string AccessibilityProperty::GetAccessibilityDescription() const
{
    return accessibilityDescription_.value_or("");
}

std::string AccessibilityProperty::GetTextType() const
{
    return textTypeHint_.value_or("");
}

void AccessibilityProperty::SetAccessibilityLevel(const std::string& accessibilityLevel)
{
    if (accessibilityLevel == Level::YES_STR ||
        accessibilityLevel == Level::NO_STR ||
        accessibilityLevel == Level::NO_HIDE_DESCENDANTS) {
        accessibilityLevel_ = accessibilityLevel;
    } else {
        accessibilityLevel_ = Level::AUTO;
    }
}

void AccessibilityProperty::SetRelatedElementInfoCallback(const GetRelatedElementInfoImpl& getRelatedElementInfoImpl)
{
    getRelatedElementInfoImpl_ = getRelatedElementInfoImpl;
}

void AccessibilityProperty::GetAllExtraElementInfo(Accessibility::ExtraElementInfo& extraElementInfo)
{
    if (getRelatedElementInfoImpl_) {
        getRelatedElementInfoImpl_(extraElementInfo);
    }
    GetExtraElementInfo(extraElementInfo);
}

void AccessibilityProperty::OnAccessibilityFocusCallback(bool isFocus)
{
    if (onAccessibilityFocusCallbackImpl_) {
        onAccessibilityFocusCallbackImpl_(isFocus);
    }
}

void AccessibilityProperty::SetGetWindowScenePosition(const GetWindowScenePositionImpl& getWindowScenePositionImpl)
    {
        getWindowScenePositionImpl_ = getWindowScenePositionImpl;
    }

void AccessibilityProperty::GetWindowScenePosition(int32_t& left, int32_t& top)
{
    if (getWindowScenePositionImpl_ == nullptr) {
        left = 0;
        top = 0;
        return;
    }
    getWindowScenePositionImpl_(left, top);
}

void AccessibilityProperty::SetOnAccessibilityFocusCallback(
    const OnAccessibilityFocusCallbackImpl& onAccessibilityFocusCallbackImpl)
{
    onAccessibilityFocusCallbackImpl_ = onAccessibilityFocusCallbackImpl;
}

bool AccessibilityProperty::ActActionClearSelection()
{
    if (actionClearSelectionImpl_) {
        actionClearSelectionImpl_();
        return true;
    }
    return false;
}

void AccessibilityProperty::SetActionClearSelection(const ActionClearSelectionImpl& actionClearSelectionImpl)
{
    actionClearSelectionImpl_ = actionClearSelectionImpl;
}

bool AccessibilityProperty::ActActionSelect()
{
    if (actionSelectImpl_) {
        actionSelectImpl_();
        return true;
    }
    return false;
}

void AccessibilityProperty::SetActionSelect(const ActionSelectImpl& actionSelectImpl)
{
    actionSelectImpl_ = actionSelectImpl;
}

bool AccessibilityProperty::ActActionClick()
{
    if (ActionsDefined(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_CLICK))) {
        actionsImpl_(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_CLICK));
        return true;
    }
    if (actionClickImpl_) {
        actionClickImpl_();
        return true;
    }
    return false;
}

void AccessibilityProperty::SetActionClick(const ActionClickImpl& actionClickImpl)
{
    actionClickImpl_ = actionClickImpl;
}

bool AccessibilityProperty::ActActionLongClick()
{
    if (ActionsDefined(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_LONG_CLICK))) {
        actionsImpl_(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_LONG_CLICK));
        return true;
    }
    if (actionLongClickImpl_) {
        actionLongClickImpl_();
        return true;
    }
    return false;
}

void AccessibilityProperty::SetActionLongClick(const ActionLongClickImpl& actionLongClickImpl)
{
    actionLongClickImpl_ = actionLongClickImpl;
}

bool AccessibilityProperty::ActActionPaste()
{
    if (ActionsDefined(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_PASTE))) {
        actionsImpl_(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_PASTE));
        return true;
    }
    if (actionPasteImpl_) {
        actionPasteImpl_();
        return true;
    }
    return false;
}

void AccessibilityProperty::SetActionPaste(const ActionPasteImpl& actionPasteImpl)
{
    actionPasteImpl_ = actionPasteImpl;
}

bool AccessibilityProperty::ActActionCut()
{
    if (ActionsDefined(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_CUT))) {
        actionsImpl_(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_CUT));
        return true;
    }
    if (actionCutImpl_) {
        actionCutImpl_();
        return true;
    }
    return false;
}

void AccessibilityProperty::SetActionCut(const ActionCutImpl& actionCutImpl)
{
    actionCutImpl_ = actionCutImpl;
}

bool AccessibilityProperty::ActActionCopy()
{
    if (ActionsDefined(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_COPY))) {
        actionsImpl_(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_COPY));
        return true;
    }
    if (actionCopyImpl_) {
        actionCopyImpl_();
        return true;
    }
    return false;
}
} // namespace OHOS::Ace::NG
