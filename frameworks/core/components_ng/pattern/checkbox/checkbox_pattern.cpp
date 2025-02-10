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

#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"

namespace OHOS::Ace::NG {
namespace {
const Color ITEM_FILL_COLOR = Color::TRANSPARENT;
constexpr int32_t DEFAULT_CHECKBOX_ANIMATION_DURATION = 100;
} // namespace

void CheckBoxPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
}

void CheckBoxPattern::SetBuilderNodeHidden()
{
    CHECK_NULL_VOID(builderNode_);
    auto layoutProperty = builderNode_->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::GONE);
}

void CheckBoxPattern::UpdateIndicator()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (builder_.has_value() && !UseContentModifier()) {
        LoadBuilder();
        auto paintProperty = host->GetPaintProperty<CheckBoxPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        bool isSelected = false;
        if (paintProperty->HasCheckBoxSelect()) {
            isSelected = paintProperty->GetCheckBoxSelectValue();
            if (!isSelected) {
                SetBuilderNodeHidden();
            }
        } else {
            SetBuilderNodeHidden();
        }
    } else if (builderNode_) {
        host->RemoveChildAndReturnIndex(builderNode_);
        builderNode_ = nullptr;
    }
}

void CheckBoxPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    FireBuilder();
    UpdateIndicator();
    UpdateState();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = GetContext();
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
        if (info.GetTouches().empty()) {
            return;
        }
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
    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "checkbox on hover %{public}d", isHover);
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
        CHECK_NULL_VOID(pattern);
        pattern->HandleFocusEvent();
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
    CHECK_NULL_VOID(paintMethod_);
    AddIsFocusActiveUpdateEvent();
    OnIsFocusActiveUpdate(true);
}

void CheckBoxPattern::HandleBlurEvent()
{
    CHECK_NULL_VOID(paintMethod_);
    RemoveIsFocusActiveUpdateEvent();
    OnIsFocusActiveUpdate(false);
}

void CheckBoxPattern::AddIsFocusActiveUpdateEvent()
{
    if (!isFocusActiveUpdateEvent_) {
        isFocusActiveUpdateEvent_ = [weak = WeakClaim(this)](bool isFocusAcitve) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnIsFocusActiveUpdate(isFocusAcitve);
        };
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipline);
    pipline->AddIsFocusActiveUpdateEvent(host, isFocusActiveUpdateEvent_);
}

void CheckBoxPattern::RemoveIsFocusActiveUpdateEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipline);
    pipline->RemoveIsFocusActiveUpdateEvent(host);
}

void CheckBoxPattern::OnIsFocusActiveUpdate(bool isFocusAcitve)
{
    CHECK_NULL_VOID(paintMethod_);
    auto modifier = paintMethod_->GetCheckBoxModifier();
    CHECK_NULL_VOID(modifier);
    modifier->SetIsFocused(isFocusAcitve);
}

void CheckBoxPattern::OnClick()
{
    if (UseContentModifier()) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "checkbox onclick");
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
    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "checkbox touch down %{public}d", isHover_);
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
    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "checkbox touch up %{public}d", isHover_);
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
    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "checkbox update status %{public}d", check);
    uiStatus_ = check ? UIStatus::OFF_TO_ON : UIStatus::ON_TO_OFF;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (UseContentModifier()) {
        auto paintProperty = host->GetPaintProperty<CheckBoxPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        paintProperty->UpdateCheckBoxSelect(check);
        FireBuilder();
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto groupManager = GetGroupManager();
    CHECK_NULL_VOID(groupManager);
    auto eventHub = frameNode->GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto group = eventHub->GetGroupName() + currentNavId_.value_or(groupManager->GetLastNavId());
    groupManager->RemoveCheckBoxFromGroup(group, frameNode->GetId());
    auto groupNode = groupManager->GetCheckboxGroup(group);
    CHECK_NULL_VOID(groupNode);
    auto checkboxList = groupManager->GetCheckboxList(group);
    UpdateCheckBoxGroupStatus(groupNode, checkboxList);
}

void CheckBoxPattern::CheckPageNode()
{
    if (Container::IsInSubContainer()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto prePageId = GetPrePageId();
    auto pipelineContext = GetContext();
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
        groupManager->AddCheckBoxToGroup(group, host);
        SetPrePageId(pageNode->GetId());
    }
}

void CheckBoxPattern::UpdateState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto groupManager = GetGroupManager();
    CHECK_NULL_VOID(groupManager);
    auto paintProperty = host->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto preGroup = GetPreGroup();
    auto group = GetGroupNameWithNavId();
    if (!preGroup.has_value()) {
        groupManager->AddCheckBoxToGroup(group, host);
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
        groupManager->AddCheckBoxToGroup(group, host);
        SetPrePageIdToLastPageId();
    }
    SetPreGroup(group);
    ChangeSelfStatusAndNotify(paintProperty);
    auto groupNode = groupManager->GetCheckboxGroup(group);
    CHECK_NULL_VOID(groupNode);
    auto checkboxList = groupManager->GetCheckboxList(group);
    UpdateCheckBoxGroupStatus(groupNode, checkboxList);
}

void CheckBoxPattern::ChangeSelfStatusAndNotify(const RefPtr<CheckBoxPaintProperty>& paintProperty)
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
            TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "checkbox node %{public}d update change event %{public}d",
                host->GetId(), isSelected);
            checkboxEventHub->UpdateChangeEvent(isSelected);
        }
    }
    StartCustomNodeAnimation(isSelected);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    FireBuilder();
}

void CheckBoxPattern::StartEnterAnimation()
{
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(DEFAULT_CHECKBOX_ANIMATION_DURATION);
    CHECK_NULL_VOID(builderNode_);
    const auto& renderContext = builderNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateOpacity(0);
    const auto& layoutProperty = builderNode_->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    const auto& eventHub = builderNode_->GetEventHub<EventHub>();
    if (eventHub) {
        eventHub->SetEnabled(true);
    }
    AnimationUtils::Animate(
        option,
        [&]() {
            TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "check enter animation");
            renderContext->UpdateOpacity(1);
        },
        nullptr);
}

void CheckBoxPattern::StartExitAnimation()
{
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(DEFAULT_CHECKBOX_ANIMATION_DURATION);
    CHECK_NULL_VOID(builderNode_);
    const auto& renderContext = builderNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationUtils::Animate(
        option,
        [&]() {
            TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "check exit animation");
            renderContext->UpdateOpacity(0);
        },
        nullptr);
    const auto& eventHub = builderNode_->GetEventHub<EventHub>();
    if (eventHub) {
        eventHub->SetEnabled(false);
    }
}

void CheckBoxPattern::LoadBuilder()
{
    RefPtr<UINode> customNode;
    if (builder_.has_value()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        if (builderNode_) {
            host->RemoveChildAndReturnIndex(builderNode_);
        }
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        builder_.value()();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        CHECK_NULL_VOID(customNode);
        builderNode_ = AceType::DynamicCast<FrameNode>(customNode);
        CHECK_NULL_VOID(builderNode_);
        builderNode_->MountToParent(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    }
}

void CheckBoxPattern::StartCustomNodeAnimation(bool select)
{
    if (!isFirstCreated_ && builder_.has_value()) {
        if (select) {
            StartEnterAnimation();
        } else {
            StartExitAnimation();
        }
    }
}

void CheckBoxPattern::UpdateCheckBoxGroupStatus(
    RefPtr<FrameNode> checkBoxGroupNode, const std::list<RefPtr<FrameNode>>& list)
{
    std::vector<std::string> vec;
    bool haveCheckBoxSelected = false;
    bool isAllCheckBoxSelected = true;
    for (auto node : list) {
        if (!node) {
            continue;
        }
        auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        if (paintProperty->GetCheckBoxSelectValue(false)) {
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
    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "update checkboxgroup result %d", groupResult.GetStatus());
    eventHub->UpdateChangeEvent(&groupResult);
}

void CheckBoxPattern::CheckBoxGroupIsTrue()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto groupManager = GetGroupManager();
    CHECK_NULL_VOID(groupManager);
    auto paintProperty = host->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto group = GetGroupNameWithNavId();
    RefPtr<FrameNode> checkBoxGroupNode = groupManager->GetCheckboxGroup(group);
    CHECK_NULL_VOID(checkBoxGroupNode);
    std::vector<std::string> vec;
    bool allSelectIsNull = true;
    const auto& list = groupManager->GetCheckboxList(group);
    for (auto node : list) {
        if (!node) {
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
    const auto& groupPaintProperty = checkBoxGroupNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(groupPaintProperty);
    if (!groupManager->GetCheckboxGroupIsChange(group) && groupPaintProperty->GetIsCheckBoxCallbackDealed()) {
        return;
    }
    // All checkboxes do not set select status.
    if (allSelectIsNull && groupPaintProperty->GetCheckBoxGroupSelectValue(false)) {
        InitCheckBoxStatusByGroup(checkBoxGroupNode, groupPaintProperty, list);
    }
    // Some checkboxes set select status.
    if (!allSelectIsNull) {
        UpdateCheckBoxGroupStatus(checkBoxGroupNode, list);
    }
    groupPaintProperty->SetIsCheckBoxCallbackDealed(true);
    groupManager->SetCheckboxGroupIsChange(group, false);
}

void CheckBoxPattern::InitCheckBoxStatusByGroup(RefPtr<FrameNode> checkBoxGroupNode,
    const RefPtr<CheckBoxGroupPaintProperty>& groupPaintProperty, const std::list<RefPtr<FrameNode>>& list)
{
    if (groupPaintProperty->GetCheckBoxGroupSelectValue(false)) {
        groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
        groupPaintProperty->UpdateCheckBoxGroupSelect(true);
        checkBoxGroupNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        for (auto node : list) {
            if (!node) {
                continue;
            }
            auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
            CHECK_NULL_VOID(paintProperty);
            paintProperty->UpdateCheckBoxSelect(true);
            auto checkBoxPattern = node->GetPattern<CheckBoxPattern>();
            CHECK_NULL_VOID(checkBoxPattern);
            checkBoxPattern->StartCustomNodeAnimation(true);
            checkBoxPattern->UpdateUIStatus(true);
            checkBoxPattern->SetLastSelect(true);
        }
    }
}

void CheckBoxPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    CHECK_NULL_VOID(focusHub);
    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);

    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            return pattern->OnKeyEvent(event);
        }
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool CheckBoxPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action == KeyAction::DOWN && event.code == KeyCode::KEY_FUNCTION) {
        OnClick();
        return true;
    }
    return false;
}

bool CheckBoxPattern::IsSquareStyleBox()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto paintProperty = host->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    CheckBoxStyle checkboxStyle = CheckBoxStyle::CIRCULAR_STYLE;
    if (paintProperty->HasCheckBoxSelectedStyle()) {
        checkboxStyle = paintProperty->GetCheckBoxSelectedStyleValue(CheckBoxStyle::CIRCULAR_STYLE);
    } else {
        checkboxStyle = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) ?
            CheckBoxStyle::CIRCULAR_STYLE : CheckBoxStyle::SQUARE_STYLE;
    }
    return checkboxStyle == CheckBoxStyle::SQUARE_STYLE;
}

void CheckBoxPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto* pipelineContext = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto checkBoxTheme = pipelineContext->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto borderRadius = checkBoxTheme->GetFocusRadius().ConvertToPx();
    auto focusPaintPadding = checkBoxTheme->GetFocusPaintPadding().ConvertToPx();
    auto isSquare = IsSquareStyleBox();
    auto squareFocusBoardSize = checkBoxTheme->GetFocusBoardSize();
    auto roundFocusBoardSize = checkBoxTheme->GetRoundFocusBoardSize();
    if ((squareFocusBoardSize > roundFocusBoardSize) && isSquare) {
        focusPaintPadding += (squareFocusBoardSize.ConvertToPx() - roundFocusBoardSize.ConvertToPx());
    }
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
    auto host = GetHost();
    CHECK_NULL_RETURN(host, FocusPattern());
    auto* pipeline = host->GetContextWithCheck();
    CHECK_NULL_RETURN(pipeline, FocusPattern());
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_RETURN(checkBoxTheme, FocusPattern());
    auto activeColor = checkBoxTheme->GetFocusLineColor();
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!makeFunc_.has_value() && !toggleMakeFunc_.has_value()) {
        host->RemoveChildAndReturnIndex(contentModifierNode_);
        contentModifierNode_ = nullptr;
        host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
        return;
    }
    auto node = BuildContentModifierNode();
    if (contentModifierNode_ == node) {
        return;
    }
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    host->RemoveChildAndReturnIndex(contentModifierNode_);
    contentModifierNode_ = node;
    CHECK_NULL_VOID(contentModifierNode_);
    host->AddChild(contentModifierNode_, 0);
    host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
}

RefPtr<FrameNode> CheckBoxPattern::BuildContentModifierNode()
{
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
    if (host->GetHostTag() == V2::CHECKBOX_ETS_TAG && toggleMakeFunc_.has_value()) {
        return (toggleMakeFunc_.value())(ToggleConfiguration(enabled, isSelected));
    }
    CheckBoxConfiguration checkBoxConfiguration(name, isSelected, enabled);
    return (makeFunc_.value())(checkBoxConfiguration);
}

void CheckBoxPattern::UpdatePaintPropertyBySettingData(RefPtr<CheckBoxPaintProperty> paintProp)
{
    if (checkboxSettingData_.selectedColor.has_value()) {
        paintProp->UpdateCheckBoxSelectedColor(checkboxSettingData_.selectedColor.value());
    }
    if (checkboxSettingData_.unselectedColor.has_value()) {
        paintProp->UpdateCheckBoxUnSelectedColor(checkboxSettingData_.unselectedColor.value());
    }
    if (checkboxSettingData_.strokeColor.has_value()) {
        paintProp->UpdateCheckBoxCheckMarkColor(checkboxSettingData_.strokeColor.value());
    }
}

void CheckBoxPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto* pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto checkBoxPaintProperty = host->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(checkBoxPaintProperty);
    checkBoxPaintProperty->UpdateCheckBoxSelectedColor(checkBoxTheme->GetActiveColor());
    checkBoxPaintProperty->UpdateCheckBoxUnSelectedColor(checkBoxTheme->GetInactiveColor());
    checkBoxPaintProperty->UpdateCheckBoxCheckMarkColor(checkBoxTheme->GetPointColor());
    UpdatePaintPropertyBySettingData(checkBoxPaintProperty);
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
    auto groupManager = GetGroupManager();
    CHECK_NULL_VOID(groupManager);
    auto parent = host->GetParent();
    while (parent) {
        if (parent->GetTag() == V2::NAVDESTINATION_CONTENT_ETS_TAG) {
            currentNavId_ = std::to_string(parent->GetId());
            groupManager->SetLastNavId(currentNavId_);
            UpdateState();
            return;
        }
        parent = parent->GetParent();
    }
    if (!currentNavId_.value_or("").empty()) {
        currentNavId_ = "";
        groupManager->SetLastNavId(std::nullopt);
        UpdateState();
    }
}

std::string CheckBoxPattern::GetGroupNameWithNavId()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto eventHub = host->GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_RETURN(eventHub, "");
    if (currentNavId_.has_value()) {
        return eventHub->GetGroupName() + currentNavId_.value();
    }
    auto groupManager = GetGroupManager();
    CHECK_NULL_RETURN(groupManager, eventHub->GetGroupName());
    return eventHub->GetGroupName() + groupManager->GetLastNavId();
}

RefPtr<GroupManager> CheckBoxPattern::GetGroupManager()
{
    auto manager = groupManager_.Upgrade();
    if (manager) {
        return manager;
    }
    groupManager_ = GroupManager::GetGroupManager();
    return groupManager_.Upgrade();
}
} // namespace OHOS::Ace::NG
