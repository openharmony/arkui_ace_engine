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

#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"

#include "core/common/recorder/node_data_cache.h"
#include "core/components/checkable/checkable_component.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/checkbox/checkbox_layout_algorithm.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const Color ITEM_FILL_COLOR = Color::TRANSPARENT;
}

void CheckBoxPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
}

void CheckBoxPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    UpdateState();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    MarginProperty margin;
    margin.left = CalcLength(checkBoxTheme->GetHotZoneHorizontalPadding().Value());
    margin.right = CalcLength(checkBoxTheme->GetHotZoneHorizontalPadding().Value());
    margin.top = CalcLength(checkBoxTheme->GetHotZoneVerticalPadding().Value());
    margin.bottom = CalcLength(checkBoxTheme->GetHotZoneVerticalPadding().Value());
    auto& setMargin = layoutProperty->GetMarginProperty();
    if (setMargin) {
        if (setMargin->left.has_value()) {
            margin.left = setMargin->left;
        }
        if (setMargin->right.has_value()) {
            margin.right = setMargin->right;
        }
        if (setMargin->top.has_value()) {
            margin.top = setMargin->top;
        }
        if (setMargin->bottom.has_value()) {
            margin.bottom = setMargin->bottom;
        }
    }
    layoutProperty->UpdateMargin(margin);
    hotZoneHorizontalPadding_ = checkBoxTheme->GetHotZoneHorizontalPadding();
    hotZoneVerticalPadding_ = checkBoxTheme->GetHotZoneVerticalPadding();
    InitClickEvent();
    InitTouchEvent();
    InitMouseEvent();
    InitFocusEvent();
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
    SetAccessibilityAction();
    FireBuilder();
}

void CheckBoxPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionSelect([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->UpdateSelectStatus(true);
    });

    accessibilityProperty->SetActionClearSelection([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->UpdateSelectStatus(false);
    });
}

void CheckBoxPattern::UpdateSelectStatus(bool isSelected)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    MarkIsSelected(isSelected);
    context->OnMouseSelectUpdate(isSelected, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
}

void CheckBoxPattern::MarkIsSelected(bool isSelected)
{
    if (lastSelect_ == isSelected) {
        return;
    }
    lastSelect_ = isSelected;
    auto eventHub = GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->UpdateChangeEvent(isSelected);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (isSelected) {
        eventHub->UpdateCurrentUIState(UI_STATE_SELECTED);
        host->OnAccessibilityEvent(AccessibilityEventType::SELECTED);
    } else {
        eventHub->ResetCurrentUIState(UI_STATE_SELECTED);
        host->OnAccessibilityEvent(AccessibilityEventType::CHANGE);
    }
}

void CheckBoxPattern::OnAfterModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    if (inspectorId.empty()) {
        return;
    }
    auto eventHub = host->GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    Recorder::NodeDataCache::Get().PutMultiple(host, inspectorId, eventHub->GetName(), lastSelect_);
}

void CheckBoxPattern::InitClickEvent()
{
    if (clickListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto checkboxPattern = weak.Upgrade();
        CHECK_NULL_VOID(checkboxPattern);
        checkboxPattern->OnClick();
    };
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void CheckBoxPattern::InitTouchEvent()
{
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto checkboxPattern = weak.Upgrade();
        CHECK_NULL_VOID(checkboxPattern);
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            checkboxPattern->OnTouchDown();
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP ||
            info.GetTouches().front().GetTouchType() == TouchType::CANCEL) {
            checkboxPattern->OnTouchUp();
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void CheckBoxPattern::InitMouseEvent()
{
    if (mouseEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto eventHub = host->GetEventHub<CheckBoxEventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();

    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(isHover);
        }
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(mouseEvent_);
}

void CheckBoxPattern::HandleMouseEvent(bool isHover)
{
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "checkbox on hover %{public}d", isHover);
    isHover_ = isHover;
    if (isHover) {
        touchHoverType_ = TouchHoverAnimationType::HOVER;
    } else {
        touchHoverType_ = TouchHoverAnimationType::NONE;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxPattern::InitFocusEvent()
{
    if (focusEventInitialized_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    auto focusTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleFocusEvent();
        }
    };
    focusHub->SetOnFocusInternal(focusTask);
    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(blurTask);

    focusEventInitialized_ = true;
}

void CheckBoxPattern::HandleFocusEvent()
{
    CHECK_NULL_VOID(checkboxModifier_);
    checkboxModifier_->SetIsFocused(true);
}

void CheckBoxPattern::HandleBlurEvent()
{
    CHECK_NULL_VOID(checkboxModifier_);
    checkboxModifier_->SetIsFocused(false);
}

void CheckBoxPattern::OnClick()
{
    if (UseContentModifier()) {
        return;
    }
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "checkbox onclick");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    bool isSelected = false;
    if (paintProperty->HasCheckBoxSelect()) {
        isSelected = paintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    paintProperty->UpdateCheckBoxSelect(!isSelected);
    UpdateState();
}

void CheckBoxPattern::OnTouchDown()
{
    if (UseContentModifier()) {
        return;
    }
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "checkbox touch down %{public}d", isHover_);
    if (isHover_) {
        touchHoverType_ = TouchHoverAnimationType::HOVER_TO_PRESS;
    } else {
        touchHoverType_ = TouchHoverAnimationType::PRESS;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isTouch_ = true;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxPattern::OnTouchUp()
{
    if (UseContentModifier()) {
        return;
    }
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "checkbox touch up %{public}d", isHover_);
    if (isHover_) {
        touchHoverType_ = TouchHoverAnimationType::PRESS_TO_HOVER;
    } else {
        touchHoverType_ = TouchHoverAnimationType::NONE;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isTouch_ = false;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxPattern::UpdateUnSelect()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->HasCheckBoxSelect() && !paintProperty->GetCheckBoxSelectValue()) {
        uiStatus_ = UIStatus::UNSELECTED;
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void CheckBoxPattern::UpdateUIStatus(bool check)
{
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "checkbox update ui status %{public}d", check);
    uiStatus_ = check ? UIStatus::OFF_TO_ON : UIStatus::ON_TO_OFF;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto groupManager = groupManager_.Upgrade();
    CHECK_NULL_VOID(groupManager);
    auto checkBoxGroupMap = groupManager->GetCheckBoxGroupMap();
    UpdateCheckBoxGroupStatusWhenDetach(frameNode, checkBoxGroupMap);
    groupManager->RemoveCheckBoxFromGroup(GetGroupNameWithNavId(), frameNode->GetId());
}

void CheckBoxPattern::CheckPageNode()
{
    if (Container::IsInSubContainer()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto prePageId = GetPrePageId();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetPageById(host->GetPageId());
    CHECK_NULL_VOID(pageNode);
    if (pageNode->GetId() != prePageId) {
        auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
        CHECK_NULL_VOID(pageEventHub);
        auto groupManager = pageEventHub->GetGroupManager();
        CHECK_NULL_VOID(groupManager);
        groupManager_ = groupManager;
        auto group = GetGroupNameWithNavId();
        groupManager->AddCheckBoxToGroup(group, host->GetId());
        SetPrePageId(pageNode->GetId());
    }
}

void CheckBoxPattern::UpdateState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    if (!groupManager_.Upgrade()) {
        groupManager_ = GroupManager::GetGroupManager();
    }
    auto groupManager = groupManager_.Upgrade();
    CHECK_NULL_VOID(groupManager);
    auto paintProperty = host->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto checkBoxGroupMap = groupManager->GetCheckBoxGroupMap();
    auto preGroup = GetPreGroup();
    auto group = GetGroupNameWithNavId();
    if (!preGroup.has_value()) {
        groupManager->AddCheckBoxToGroup(group, host->GetId());
        SetPrePageIdToLastPageId();
        auto callback = [weak = WeakClaim(this)]() {
            auto checkbox = weak.Upgrade();
            if (checkbox) {
                checkbox->CheckPageNode();
                checkbox->CheckBoxGroupIsTrue();
            }
        };
        pipelineContext->AddBuildFinishCallBack(callback);
        if (paintProperty->HasCheckBoxSelect()) {
            auto isSelected = paintProperty->GetCheckBoxSelectValue();
            SetLastSelect(isSelected);
        }
        isFirstCreated_ = false;
        SetPreGroup(group);
        return;
    }
    if (preGroup.has_value() && preGroup.value() != group) {
        groupManager->RemoveCheckBoxFromGroup(preGroup.value(), host->GetId());
        groupManager->AddCheckBoxToGroup(group, host->GetId());
        SetPrePageIdToLastPageId();
    }
    SetPreGroup(group);
    ChangeSelfStatusAndNotify(paintProperty, checkBoxGroupMap);
}

void CheckBoxPattern::ChangeSelfStatusAndNotify(const RefPtr<CheckBoxPaintProperty>& paintProperty,
    std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>> checkBoxGroupMap)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    bool isSelected = false;
    if (paintProperty->HasCheckBoxSelect()) {
        isSelected = paintProperty->GetCheckBoxSelectValue();
        if (lastSelect_ != isSelected) {
            UpdateUIStatus(isSelected);
            SetLastSelect(isSelected);
            auto checkboxEventHub = GetEventHub<CheckBoxEventHub>();
            CHECK_NULL_VOID(checkboxEventHub);
            TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "checkbox update change event %{public}d", isSelected);
            checkboxEventHub->UpdateChangeEvent(isSelected);
        }
    }
    UpdateCheckBoxGroupStatus(host, checkBoxGroupMap, isSelected);
    FireBuilder();
}

void CheckBoxPattern::UpdateCheckBoxGroupStatus(const RefPtr<FrameNode>& checkBoxFrameNode,
    std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>>& checkBoxGroupMap, bool select)
{
    checkBoxFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto group = GetGroupNameWithNavId();
    std::vector<std::string> vec;
    RefPtr<FrameNode> checkBoxGroupNode;
    bool isSameAsSelf = true;
    const auto& list = checkBoxGroupMap[group];
    for (auto&& item : list) {
        auto node = item.Upgrade();
        if (!node) {
            continue;
        }
        if (node == checkBoxFrameNode) {
            if (select) {
                auto eventHub = node->GetEventHub<CheckBoxEventHub>();
                CHECK_NULL_VOID(eventHub);
                vec.push_back(eventHub->GetName());
            }
            continue;
        }
        if (node->GetTag() == V2::CHECKBOXGROUP_ETS_TAG) {
            checkBoxGroupNode = node;
            continue;
        }
        auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        if (!paintProperty->HasCheckBoxSelect()) {
            if (select) {
                isSameAsSelf = false;
            }
        }
        if (paintProperty->HasCheckBoxSelect() && paintProperty->GetCheckBoxSelectValue() != select) {
            isSameAsSelf = false;
        }
        if (paintProperty->HasCheckBoxSelect() && paintProperty->GetCheckBoxSelectValue()) {
            auto eventHub = node->GetEventHub<CheckBoxEventHub>();
            CHECK_NULL_VOID(eventHub);
            vec.push_back(eventHub->GetName());
        }
    }
    NotifyCheckboxGroupStatusChange(checkBoxGroupNode, vec, isSameAsSelf, select);
}

void CheckBoxPattern::NotifyCheckboxGroupStatusChange(
    const RefPtr<FrameNode>& checkBoxGroupNode, std::vector<std::string> vec, bool isSameAsSelf, bool select)
{
    CHECK_NULL_VOID(checkBoxGroupNode);
    auto groupPaintProperty = checkBoxGroupNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(groupPaintProperty);
    auto pattern = checkBoxGroupNode->GetPattern<CheckBoxGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto preStatus = groupPaintProperty->GetSelectStatus();
    if (isSameAsSelf) {
        if (select) {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
            pattern->UpdateUIStatus(select);
        } else {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::NONE);
            pattern->ResetUIStatus();
        }
        checkBoxGroupNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    } else {
        auto checkBoxGroupStatus = groupPaintProperty->GetSelectStatus();
        if (checkBoxGroupStatus == CheckBoxGroupPaintProperty::SelectStatus::ALL ||
            checkBoxGroupStatus == CheckBoxGroupPaintProperty::SelectStatus::NONE) {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::PART);
            checkBoxGroupNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }

    auto status = groupPaintProperty->GetSelectStatus();
    if (preStatus != status && (preStatus == CheckBoxGroupPaintProperty::SelectStatus::ALL ||
                                   status == CheckBoxGroupPaintProperty::SelectStatus::ALL)) {
        pattern->SetSkipFlag(true);
    }
    CheckboxGroupResult groupResult(vec, int(status));
    auto eventHub = checkBoxGroupNode->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "update checkboxgroup result %d", groupResult.GetStatus());
    eventHub->UpdateChangeEvent(&groupResult);
}

void CheckBoxPattern::UpdateCheckBoxGroupStatusWhenDetach(const FrameNode* checkBoxFrameNode,
    std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>>& checkBoxGroupMap)
{
    auto group = GetGroupNameWithNavId();
    std::vector<std::string> vec;
    RefPtr<FrameNode> checkBoxGroupNode;
    bool haveCheckBoxSelected = false;
    bool isAllCheckBoxSelected = true;
    const auto& list = checkBoxGroupMap[group];
    for (auto&& item : list) {
        auto node = item.Upgrade();
        if (!node) {
            continue;
        }
        if (node->GetTag() == V2::CHECKBOXGROUP_ETS_TAG) {
            checkBoxGroupNode = node;
            continue;
        }
        auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        if (paintProperty->HasCheckBoxSelect() && paintProperty->GetCheckBoxSelectValue()) {
            auto eventHub = node->GetEventHub<CheckBoxEventHub>();
            CHECK_NULL_VOID(eventHub);
            vec.push_back(eventHub->GetName());
            haveCheckBoxSelected = true;
        } else {
            isAllCheckBoxSelected = false;
        }
    }
    ChangeGroupStatusAndNotify(checkBoxGroupNode, vec, haveCheckBoxSelected, isAllCheckBoxSelected);
}

void CheckBoxPattern::ChangeGroupStatusAndNotify(const RefPtr<FrameNode>& checkBoxGroupNode,
    const std::vector<std::string>& vec, bool haveCheckBoxSelected, bool isAllCheckBoxSelected)
{
    CHECK_NULL_VOID(checkBoxGroupNode);
    auto groupPaintProperty = checkBoxGroupNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(groupPaintProperty);
    auto pattern = checkBoxGroupNode->GetPattern<CheckBoxGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto preStatus = groupPaintProperty->GetSelectStatus();
    if (haveCheckBoxSelected) {
        if (isAllCheckBoxSelected) {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
            pattern->UpdateUIStatus(true);
        } else {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::PART);
            pattern->ResetUIStatus();
        }
    } else {
        groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::NONE);
        pattern->UpdateUIStatus(false);
    }
    checkBoxGroupNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto status = groupPaintProperty->GetSelectStatus();
    if (preStatus != status && (preStatus == CheckBoxGroupPaintProperty::SelectStatus::ALL ||
                                   status == CheckBoxGroupPaintProperty::SelectStatus::ALL)) {
        pattern->SetSkipFlag(true);
    }
    CheckboxGroupResult groupResult(vec, int(status));
    auto eventHub = checkBoxGroupNode->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "update checkboxgroup result %d", groupResult.GetStatus());
    eventHub->UpdateChangeEvent(&groupResult);
}

void CheckBoxPattern::CheckBoxGroupIsTrue()
{
    auto checkBoxFrameNode = GetHost();
    CHECK_NULL_VOID(checkBoxFrameNode);
    auto groupManager = groupManager_.Upgrade();
    CHECK_NULL_VOID(groupManager);
    auto paintProperty = checkBoxFrameNode->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto checkBoxGroupMap = groupManager->GetCheckBoxGroupMap();
    auto group = GetGroupNameWithNavId();
    std::vector<std::string> vec;
    RefPtr<FrameNode> checkBoxGroupNode;
    bool allSelectIsNull = true;
    const auto& list = checkBoxGroupMap[group];
    for (auto&& item : list) {
        auto node = item.Upgrade();
        if (!node) {
            continue;
        }
        if (node->GetTag() == V2::CHECKBOXGROUP_ETS_TAG) {
            checkBoxGroupNode = node;
            continue;
        }
        auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
        CHECK_NULL_VOID(paintProperty);

        if (paintProperty->HasCheckBoxSelect()) {
            allSelectIsNull = false;
        } else {
            paintProperty->UpdateCheckBoxSelect(false);
        }
    }

    CHECK_NULL_VOID(checkBoxGroupNode);
    auto groupPaintProperty = checkBoxGroupNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    if (groupPaintProperty->GetIsCheckBoxCallbackDealed()) {
        return;
    }
    // All checkboxes do not set select status.
    if (allSelectIsNull) {
        if (groupPaintProperty->HasCheckBoxGroupSelect() && groupPaintProperty->GetCheckBoxGroupSelectValue()) {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
            groupPaintProperty->UpdateCheckBoxGroupSelect(true);
            checkBoxGroupNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
            for (auto&& item : list) {
                auto node = item.Upgrade();
                if (!node) {
                    continue;
                }
                if (node->GetTag() == V2::CHECKBOXGROUP_ETS_TAG) {
                    continue;
                }
                auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
                CHECK_NULL_VOID(paintProperty);
                paintProperty->UpdateCheckBoxSelect(true);
                auto checkBoxPattern = node->GetPattern<CheckBoxPattern>();
                CHECK_NULL_VOID(checkBoxPattern);
                checkBoxPattern->UpdateUIStatus(true);
                checkBoxPattern->SetLastSelect(true);
            }
        }
    }
    // Some checkboxes set select status.
    if (!allSelectIsNull) {
        bool allIsSame = true;
        bool selfSelect = paintProperty->GetCheckBoxSelectValue();
        for (auto&& item : list) {
            auto node = item.Upgrade();
            if (node == checkBoxFrameNode) {
                continue;
            }
            if (!node) {
                continue;
            }
            if (node->GetTag() == V2::CHECKBOXGROUP_ETS_TAG) {
                continue;
            }
            auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
            CHECK_NULL_VOID(paintProperty);
            if (selfSelect != paintProperty->GetCheckBoxSelectValue()) {
                allIsSame = false;
            }
            node->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
        auto checkBoxGroupPattern = checkBoxGroupNode->GetPattern<CheckBoxGroupPattern>();
        CHECK_NULL_VOID(checkBoxGroupPattern);
        if (allIsSame && paintProperty->GetCheckBoxSelectValue()) {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
            checkBoxGroupPattern->UpdateUIStatus(true);
        } else if (allIsSame && !paintProperty->GetCheckBoxSelectValue()) {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::NONE);
            checkBoxGroupPattern->ResetUIStatus();
        } else {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::PART);
            checkBoxGroupPattern->ResetUIStatus();
        }
        checkBoxGroupNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    groupPaintProperty->SetIsCheckBoxCallbackDealed(true);
}

void CheckBoxPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
}

void CheckBoxPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto checkBoxTheme = pipelineContext->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto borderRadius = checkBoxTheme->GetFocusRadius().ConvertToPx();
    auto focusPaintPadding = checkBoxTheme->GetFocusPaintPadding().ConvertToPx();
    float originX = offset_.GetX() - focusPaintPadding;
    float originY = offset_.GetY() - focusPaintPadding;
    float width = size_.Width() + 2 * focusPaintPadding;
    float height = size_.Height() + 2 * focusPaintPadding;
    paintRect.SetRect({ originX, originY, width, height });
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, borderRadius, borderRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, borderRadius, borderRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, borderRadius, borderRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, borderRadius, borderRadius);
}

FocusPattern CheckBoxPattern::GetFocusPattern() const
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, FocusPattern());
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_RETURN(checkBoxTheme, FocusPattern());
    auto activeColor = checkBoxTheme->GetActiveColor();
    FocusPaintParam focusPaintParam;
    focusPaintParam.SetPaintColor(activeColor);
    return { FocusType::NODE, true, FocusStyleType::CUSTOM_REGION, focusPaintParam };
}

// Set the default hot zone for the component.
void CheckBoxPattern::AddHotZoneRect()
{
    hotZoneOffset_.SetX(offset_.GetX() - hotZoneHorizontalPadding_.ConvertToPx());
    hotZoneOffset_.SetY(offset_.GetY() - hotZoneVerticalPadding_.ConvertToPx());
    hotZoneSize_.SetWidth(size_.Width() + 2 * hotZoneHorizontalPadding_.ConvertToPx());
    hotZoneSize_.SetHeight(size_.Height() + 2 * hotZoneVerticalPadding_.ConvertToPx());
    DimensionRect hotZoneRegion;
    hotZoneRegion.SetSize(DimensionSize(Dimension(hotZoneSize_.Width()), Dimension(hotZoneSize_.Height())));
    hotZoneRegion.SetOffset(DimensionOffset(Dimension(hotZoneOffset_.GetX()), Dimension(hotZoneOffset_.GetY())));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    std::vector<DimensionRect> hotZoneRegions;
    hotZoneRegions.emplace_back(hotZoneRegion);
    gestureHub->SetResponseRegion(hotZoneRegions);
}

void CheckBoxPattern::RemoveLastHotZoneRect() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveLastHotZoneRect();
}

std::string CheckBoxPattern::ProvideRestoreInfo()
{
    auto jsonObj = JsonUtil::Create(true);
    auto checkBoxPaintProperty = GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_RETURN(checkBoxPaintProperty, "");
    jsonObj->Put("isOn", checkBoxPaintProperty->GetCheckBoxSelect().value_or(false));
    return jsonObj->ToString();
}

void CheckBoxPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    auto checkBoxPaintProperty = GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(checkBoxPaintProperty);
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info->IsValid() || !info->IsObject()) {
        return;
    }
    auto jsonCheckBoxSelect = info->GetValue("isOn");
    checkBoxPaintProperty->UpdateCheckBoxSelect(jsonCheckBoxSelect->GetBool());
}


void CheckBoxPattern::SetCheckBoxSelect(bool select)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    if (!enabled) {
        return;
    }
    auto paintProperty = host->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateCheckBoxSelect(select);
    UpdateState();
    OnModifyDone();
}

void CheckBoxPattern::FireBuilder()
{
    if (!makeFunc_.has_value()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveChildAtIndex(0);
    contentModifierNode_ = BuildContentModifierNode();
    CHECK_NULL_VOID(contentModifierNode_);
    host->AddChild(contentModifierNode_, 0);
    host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
}

RefPtr<FrameNode> CheckBoxPattern::BuildContentModifierNode()
{
    if (!makeFunc_.has_value()) {
        return nullptr;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto eventHub = host->GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    auto name = eventHub->GetName();
    auto enabled = eventHub->IsEnabled();
    auto paintProperty = host->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    bool isSelected = false;
    if (paintProperty->HasCheckBoxSelect()) {
        isSelected = paintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    CheckBoxConfiguration checkBoxConfiguration(name, isSelected, enabled);
    return (makeFunc_.value())(checkBoxConfiguration);
}

void CheckBoxPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto checkBoxPaintProperty = host->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(checkBoxPaintProperty);
    checkBoxPaintProperty->UpdateCheckBoxSelectedColor(checkBoxTheme->GetActiveColor());
    checkBoxPaintProperty->UpdateCheckBoxUnSelectedColor(checkBoxTheme->GetInactiveColor());
    checkBoxPaintProperty->UpdateCheckBoxCheckMarkColor(checkBoxTheme->GetPointColor());
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxPattern::SetPrePageIdToLastPageId()
{
    if (!Container::IsInSubContainer()) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto stageManager = pipelineContext->GetStageManager();
        CHECK_NULL_VOID(stageManager);
        auto pageNode = stageManager->GetLastPage();
        CHECK_NULL_VOID(pageNode);
        SetPrePageId(pageNode->GetId());
    }
}

void CheckBoxPattern::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto parent = host->GetParent();
    while (parent) {
        if (parent->GetTag() == V2::NAVDESTINATION_CONTENT_ETS_TAG) {
            navId_ = std::to_string(parent->GetId());
            UpdateState();
            return;
        }
        parent = parent->GetParent();
    }
}

std::string CheckBoxPattern::GetGroupNameWithNavId()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto eventHub = host->GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_RETURN(eventHub, "");
    return eventHub->GetGroupName() + navId_;
}
} // namespace OHOS::Ace::NG
