/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/property/accessibility_property.h"

#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint64_t ACTIONS = std::numeric_limits<uint64_t>::max();
} // namespace

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

void AccessibilityProperty::ResetSupportAction() {}

void AccessibilityProperty::NotifyComponentChangeEvent(AccessibilityEventType eventType) {}

void AccessibilityProperty::UpdateAccessibilityNextFocusIdMap(const std::string& nextFocusInspectorKey) {}

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

void AccessibilityProperty::GetGroupTextRecursive(
    bool forceGetChildren, std::string& text, bool preferAccessibilityText) const
{}

float AccessibilityProperty::GetScrollOffSet() const
{
    return 0.0;
}

AccessibilityHoverTestPath AccessibilityProperty::HoverTest(
    const PointF& point, const RefPtr<FrameNode>& root, std::unique_ptr<HoverTestDebugTraceInfo>& debugInfo)
{
    return {};
}

std::unique_ptr<JsonValue> AccessibilityProperty::CreateNodeSearchInfo(
    const RefPtr<FrameNode>& node, const PointF& parentPoint, bool& ancestorGroupFlag)
{
    return nullptr;
}

bool AccessibilityProperty::ProcessHoverTestRecursive(const PointF& noOffsetPoint, const RefPtr<FrameNode>& node,
    AccessibilityHoverTestPath& path, std::unique_ptr<HoverTestDebugTraceInfo>& debugInfo,
    RecursiveParam recursiveParam)
{
    return true;
}

bool AccessibilityProperty::IsAccessibilityCompInResponseRegion(const RectF& rect, const RectF& origRect)
{
    return true;
}

bool AccessibilityProperty::IsMatchAccessibilityResponseRegion(bool isAccessibilityVirtualNode)
{
    return true;
}

NG::RectT<int32_t> AccessibilityProperty::GetAccessibilityResponseRegionRect(bool isAccessibilityVirtualNode)
{
    return {};
}

NG::RectF AccessibilityProperty::UpdateHoverTestRect(const RefPtr<FrameNode>& node)
{
    return {};
}

bool AccessibilityProperty::HoverTestRecursive(const PointF& parentPoint, const RefPtr<FrameNode>& node,
    AccessibilityHoverTestPath& path, std::unique_ptr<HoverTestDebugTraceInfo>& debugInfo, bool& ancestorGroupFlag)
{
    return true;
}

void UpdateSearchStrategyByHitTestMode(HitTestMode hitTestMode, bool& shouldSearchSelf, bool& shouldSearchChildren)
{
}

bool AccessibilityProperty::IsTagInSubTreeComponent(const RefPtr<FrameNode>& node, const std::string& tag)
{
    return true;
}

bool AccessibilityProperty::IsTagInModalDialog(const RefPtr<FrameNode>& node)
{
    return true;
}

bool AccessibilityProperty::HitAccessibilityHoverPriority(const RefPtr<FrameNode>& node)
{
    return true;
}

bool AccessibilityProperty::NotConsumeByModal(const RefPtr<FrameNode>& node)
{
    return true;
}

bool AccessibilityProperty::CheckHoverConsumeByAccessibility(const RefPtr<FrameNode>& node)
{
    return true;
}

// hover hit but need be checked by component,
// false means self and descendants no need to be hovered, should search brothers
bool AccessibilityProperty::CheckHoverConsumeByComponent(const RefPtr<FrameNode>& node, const NG::PointF& point)
{
    return true;
}

std::tuple<bool, bool, bool> AccessibilityProperty::GetSearchStrategy(
    const RefPtr<FrameNode>& node, bool& ancestorGroupFlag)
{
    bool shouldSearchSelf = true;
    bool shouldSearchChildren = true;
    bool currentGroupFlag = false;

    return std::make_tuple(shouldSearchSelf, shouldSearchChildren, currentGroupFlag);
}

bool AccessibilityProperty::IsAccessibilityFocusableTag(const std::string& tag)
{
    return false;
}

bool AccessibilityProperty::IsAccessibilityFocusableDebug(
    const RefPtr<FrameNode>& node, std::unique_ptr<JsonValue>& info)
{
    return true;
}

bool AccessibilityProperty::IsAccessibilityFocusable(const RefPtr<FrameNode>& node)
{
    return true;
}

bool AccessibilityProperty::HasAccessibilityTextOrDescription() const
{
    return true;
}

bool AccessibilityProperty::HasAction() const
{
    return true;
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

void AccessibilityProperty::SetAccessibilityCustomRole(const std::string& role)
{
    accessibilityCustomRole_ = role;
}

void AccessibilityProperty::ResetAccessibilityCustomRole()
{
    accessibilityCustomRole_ = "";
}

bool AccessibilityProperty::HasAccessibilityCustomRole()
{
    return accessibilityCustomRole_.has_value();
}

std::string AccessibilityProperty::GetAccessibilityCustomRole() const
{
    return accessibilityCustomRole_.value_or("");
}

void AccessibilityProperty::SetAccessibilitySamePage(const std::string& pageMode)
{
    accessibilityUseSamePage_ = pageMode;
}

bool AccessibilityProperty::HasAccessibilitySamePage()
{
    return accessibilityUseSamePage_.has_value();
}

std::string AccessibilityProperty::GetAccessibilitySamePage()
{
    return accessibilityUseSamePage_.value_or("");
}

void AccessibilityProperty::SetAccessibilityStateDescription(const std::string& stateDescription)
{
    accessibilityStateDescription_ = stateDescription;
}

std::string AccessibilityProperty::GetAccessibilityStateDescription() const
{
    return accessibilityStateDescription_.value_or("");
}

bool AccessibilityProperty::HasAccessibilityStateDescription() const
{
    return accessibilityStateDescription_.has_value();
}

void AccessibilityProperty::SetActions(const ActionsImpl& actionsImpl)
{
    actionsImpl_ = actionsImpl;
}

bool AccessibilityProperty::ActionsDefined(uint32_t action)
{
    return action;
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

void AccessibilityProperty::SetUserScrollTriggerable(const bool& triggerable)
{
    isUserScrollTriggerable_ = triggerable;
}

bool AccessibilityProperty::HasUserScrollTriggerable()
{
    return isUserScrollTriggerable_.has_value();
}

bool AccessibilityProperty::IsUserScrollTriggerable()
{
    return isUserScrollTriggerable_.value_or(true);
}

void AccessibilityProperty::ResetUserScrollTriggerable()
{
    isUserScrollTriggerable_ = true;
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

void AccessibilityProperty::SetUserRangeMinValue(const int32_t rangeMinValue)
{
    rangeMinValue_ = rangeMinValue;
}

bool AccessibilityProperty::HasUserRangeMinValue() const
{
    return rangeMinValue_.has_value();
}

int32_t AccessibilityProperty::GetUserRangeMinValue() const
{
    return rangeMinValue_.value_or(-1);
}

void AccessibilityProperty::SetUserRangeMaxValue(const int32_t rangeMaxValue)
{
    rangeMaxValue_ = rangeMaxValue;
}

bool AccessibilityProperty::HasUserRangeMaxValue() const
{
    return rangeMaxValue_.has_value();
}

int32_t AccessibilityProperty::GetUserRangeMaxValue() const
{
    return rangeMaxValue_.value_or(-1);
}

void AccessibilityProperty::SetUserRangeCurrentValue(const int32_t rangeCurrentValue)
{
    rangeCurrentValue_ = rangeCurrentValue;
}

bool AccessibilityProperty::HasUserRangeCurrentValue() const
{
    return rangeCurrentValue_.has_value();
}

int32_t AccessibilityProperty::GetUserRangeCurrentValue() const
{
    return rangeCurrentValue_.value_or(-1);
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

void AccessibilityProperty::SetAccessibilityGroup(bool accessibilityGroup) {}

void AccessibilityProperty::SetAccessibilityTextPreferred(bool accessibilityTextPreferred)
{
    accessibilityTextPreferred_ = accessibilityTextPreferred;
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

void AccessibilityProperty::SetAccessibilityNextFocusInspectorKey(const std::string& accessibilityNextFocusInspectorKey)
{
    accessibilityNextFocusInspectorKey_ = accessibilityNextFocusInspectorKey;
}

void AccessibilityProperty::SetAccessibilityTextWithEvent(const std::string& text)
{
    accessibilityText_ = text;
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
    accessibilityDescription_ = accessibilityDescription;
}

bool AccessibilityProperty::IsAccessibilityGroup() const
{
    return accessibilityGroup_;
}

bool AccessibilityProperty::IsAccessibilityTextPreferred() const
{
    return accessibilityTextPreferred_;
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
}

const RefPtr<UINode>& AccessibilityProperty::GetAccessibilityVirtualNode() const
{
    return accessibilityVirtualNode_;
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
    auto backupLevel = accessibilityLevel_.value_or("");

    if (accessibilityLevel == Level::YES_STR || accessibilityLevel == Level::NO_STR ||
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

void AccessibilityProperty::GetAllExtraElementInfo(Accessibility::ExtraElementInfo& extraElementInfo) {}

void AccessibilityProperty::OnAccessibilityFocusCallback(bool isFocus) {}

void AccessibilityProperty::SetGetWindowScenePosition(const GetWindowScenePositionImpl& getWindowScenePositionImpl)
{
    getWindowScenePositionImpl_ = getWindowScenePositionImpl;
}

void AccessibilityProperty::GetWindowScenePosition(WindowSceneInfo& windowSceneInfo) {}

void AccessibilityProperty::SetOnAccessibilityFocusCallback(
    const OnAccessibilityFocusCallbackImpl& onAccessibilityFocusCallbackImpl)
{
    onAccessibilityFocusCallbackImpl_ = onAccessibilityFocusCallbackImpl;
}

void AccessibilityProperty::SetUserOnAccessibilityFocusCallback(
    const OnAccessibilityFocusCallbackImpl& onUserAccessibilityFocusCallbackImpl)
{
    onUserAccessibilityFocusCallbackImpl_ = onUserAccessibilityFocusCallbackImpl;
}

void AccessibilityProperty::ResetUserOnAccessibilityFocusCallback()
{
    onUserAccessibilityFocusCallbackImpl_ = nullptr;
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
    return true;
}

void AccessibilityProperty::SetActionClick(const ActionClickImpl& actionClickImpl)
{
    actionClickImpl_ = actionClickImpl;
}

bool AccessibilityProperty::ActActionLongClick()
{
    return true;
}

void AccessibilityProperty::SetActionLongClick(const ActionLongClickImpl& actionLongClickImpl)
{
    actionLongClickImpl_ = actionLongClickImpl;
}

bool AccessibilityProperty::ActActionPaste()
{
    return true;
}

void AccessibilityProperty::SetActionPaste(const ActionPasteImpl& actionPasteImpl)
{
    actionPasteImpl_ = actionPasteImpl;
}

bool AccessibilityProperty::ActActionCut()
{
    return true;
}

void AccessibilityProperty::SetActionCut(const ActionCutImpl& actionCutImpl)
{
    actionCutImpl_ = actionCutImpl;
}

bool AccessibilityProperty::ActActionCopy()
{
    return true;
}

bool AccessibilityProperty::IsAccessibilityHoverPriority() const
{
    return accessibilityHoverPriority_;
}

void AccessibilityProperty::SetAccessibilityHoverPriority(bool hoverPriority)
{
    // true means node consume barrierfree hover event prior to brothers
    accessibilityHoverPriority_ = hoverPriority;
}

void AccessibilityProperty::SetAccessibilityZIndex(const int32_t& accessibilityZIndex)
{
    accessibilityZIndex_ = accessibilityZIndex;
}

int32_t AccessibilityProperty::GetAccessibilityZIndex() const
{
    return accessibilityZIndex_;
}

void AccessibilityProperty::OnAccessibilityDetachFromMainTree() {}

void AccessibilityProperty::SetFocusDrawLevel(int32_t drawLevel)
{
    focusDrawLevel_ = static_cast<FocusDrawLevel>(drawLevel);
}

int32_t AccessibilityProperty::GetFocusDrawLevel()
{
    return static_cast<int32_t>(focusDrawLevel_);
}

void AccessibilityProperty::SetAccessibilityGroupOptions(const AccessibilityGroupOptions& accessibilityGroupOptions)
{
    accessibilityGroupOptions_ = accessibilityGroupOptions;
}

bool AccessibilityProperty::HasAccessibilityGroupOptions()
{
    return accessibilityGroupOptions_.has_value();
}

AccessibilityGroupOptions AccessibilityProperty::GetAccessibilityGroupOptions()
{
    return accessibilityGroupOptions_.value_or(AccessibilityGroupOptions {});
}

void AccessibilityProperty::ResetAccessibilityGroupOptions()
{
    accessibilityGroupOptions_.reset();
}

void AccessibilityProperty::SetIsAccessibilityModal(bool isModal) {}

bool AccessibilityProperty::IsAccessibilityModal() const
{
    return true;
}

void AccessibilityProperty::SetIsHeaderOrFooter(bool isFlag) {}
bool AccessibilityProperty::IsHeaderOrFooter() const
{
    return isHeaderOrFooter_.value_or(false);
}

void AccessibilityProperty::SetAccessibilityActionOptions(const AccessibilityActionOptions& accessibilityActionOptions)
{
    accessibilityActionOptions_ = accessibilityActionOptions;
}

AccessibilityActionOptions AccessibilityProperty::GetAccessibilityActionOptions()
{
    return accessibilityActionOptions_.value_or(AccessibilityActionOptions {});
}

void AccessibilityProperty::ResetAccessibilityActionOptions()
{
    accessibilityActionOptions_.reset();
}

void AccessibilityProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}
} // namespace OHOS::Ace::NG
