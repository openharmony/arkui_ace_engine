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
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"

#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"

namespace OHOS::Ace::NG {
namespace {
const Color ITEM_FILL_COLOR = Color::TRANSPARENT;
}

void CheckBoxGroupPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
}

void CheckBoxGroupPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto groupManager = GetGroupManager();
    CHECK_NULL_VOID(groupManager);
    groupManager->RemoveCheckBoxGroup(GetGroupNameWithNavId(), frameNode->GetId());
}

void CheckBoxGroupPattern::OnModifyDone()
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
    if (!layoutProperty->GetMarginProperty()) {
        MarginProperty margin;
        margin.left = CalcLength(checkBoxTheme->GetHotZoneHorizontalPadding().Value());
        margin.right = CalcLength(checkBoxTheme->GetHotZoneHorizontalPadding().Value());
        margin.top = CalcLength(checkBoxTheme->GetHotZoneVerticalPadding().Value());
        margin.bottom = CalcLength(checkBoxTheme->GetHotZoneVerticalPadding().Value());
        layoutProperty->UpdateMargin(margin);
    }
    hotZoneHorizontalPadding_ = checkBoxTheme->GetHotZoneHorizontalPadding();
    hotZoneVerticalPadding_ = checkBoxTheme->GetHotZoneVerticalPadding();
    InitClickEvent();
    InitTouchEvent();
    InitMouseEvent();
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
    SetAccessibilityAction();
}

void CheckBoxGroupPattern::SetAccessibilityAction()
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

void CheckBoxGroupPattern::UpdateSelectStatus(bool isSelected)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    MarkIsSelected(isSelected);
    context->OnMouseSelectUpdate(isSelected, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
}

void CheckBoxGroupPattern::MarkIsSelected(bool isSelected)
{
    if (updateFlag_ == isSelected) {
        return;
    }
    updateFlag_ = isSelected;
    auto eventHub = GetEventHub<CheckBoxGroupEventHub>();
    std::vector<std::string> vec;
    CheckboxGroupResult groupResult(vec, int(isSelected));
    eventHub->UpdateChangeEvent(&groupResult);
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

void CheckBoxGroupPattern::InitClickEvent()
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
        if (info.GetSourceDevice() == SourceType::TOUCH &&
            (info.IsPreventDefault() || checkboxPattern->isTouchPreventDefault_)) {
            TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "checkboxGroup preventDefault successfully");
            checkboxPattern->isTouchPreventDefault_ = false;
            return;
        }
        checkboxPattern->OnClick();
    };
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickAfterEvent(clickListener_);
}

void CheckBoxGroupPattern::InitTouchEvent()
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
        if (info.GetSourceDevice() == SourceType::TOUCH && info.IsPreventDefault()) {
            checkboxPattern->isTouchPreventDefault_ = info.IsPreventDefault();
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
    gesture->AddTouchAfterEvent(touchListener_);
}

void CheckBoxGroupPattern::InitMouseEvent()
{
    if (mouseEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto eventHub = host->GetEventHub<CheckBoxGroupEventHub>();
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

void CheckBoxGroupPattern::HandleMouseEvent(bool isHover)
{
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

void CheckBoxGroupPattern::OnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    bool isSelected = false;
    auto status = paintProperty->GetSelectStatus();
    isSelected = status == CheckBoxGroupPaintProperty::SelectStatus::NONE;
    paintProperty->UpdateCheckBoxGroupSelect(isSelected);
    updateFlag_ = true;
    UpdateState();
}

void CheckBoxGroupPattern::OnTouchDown()
{
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "checkboxgroup touch down %{public}d", isHover_);
    if (isHover_) {
        touchHoverType_ = TouchHoverAnimationType::HOVER_TO_PRESS;
    } else {
        touchHoverType_ = TouchHoverAnimationType::PRESS;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxGroupPattern::OnTouchUp()
{
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "checkboxgroup touch up %{public}d", isHover_);
    if (isHover_) {
        touchHoverType_ = TouchHoverAnimationType::PRESS_TO_HOVER;
    } else {
        touchHoverType_ = TouchHoverAnimationType::NONE;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxGroupPattern::UpdateUnSelect()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->GetSelectStatus() == CheckBoxGroupPaintProperty::SelectStatus::NONE) {
        uiStatus_ = UIStatus::UNSELECTED;
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void CheckBoxGroupPattern::UpdateUIStatus(bool check)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto selectStatus = paintProperty->GetSelectStatus();
    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "checkboxgroup update status %{public}d %{public}d", check, selectStatus);
    if (selectStatus == CheckBoxGroupPaintProperty::SelectStatus::PART) {
        uiStatus_ = check ? UIStatus::PART_TO_ON : UIStatus::PART_TO_OFF;
    } else {
        uiStatus_ = check ? UIStatus::OFF_TO_ON : UIStatus::ON_TO_OFF;
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxGroupPattern::UpdateState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        UpdateCheckBoxStyle();
    }
    auto eventHub = host->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto preGroup = GetPreGroup();
    if (!preGroup.has_value()) {
        InitPreGroup();
        return;
    }
    auto groupManager = GetGroupManager();
    CHECK_NULL_VOID(groupManager);
    auto group = GetGroupNameWithNavId();
    if (preGroup.value() != group) {
        groupManager->RemoveCheckBoxGroup(preGroup.value(), host->GetId());
        groupManager->AddCheckBoxGroup(group, host);
        SetPreGroup(group);
        return;
    }
    auto paintProperty = host->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (!paintProperty->HasCheckBoxGroupSelect()) {
        return;
    }
    bool isSelected = paintProperty->GetCheckBoxGroupSelectValue();
    paintProperty->ResetCheckBoxGroupSelect();
    if (eventHub->HasChangeEvent() && skipFlag_) {
        skipFlag_ = false;
        return;
    }

    // Setting selectAll to false when clicked requires processing, changing selectAll to false dynamically does
    // not require processing
    if (updateFlag_ || isSelected) {
        if (GetIsAddToMap()) {
            UpdateGroupCheckStatus(host, isSelected);
        } else {
            UpdateRepeatedGroupStatus(host, isSelected);
        }
    }
    updateFlag_ = false;
}

void CheckBoxGroupPattern::InitPreGroup()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto groupManager = GetGroupManager();
    CHECK_NULL_VOID(groupManager);
    auto group = GetGroupNameWithNavId();
    groupManager->AddCheckBoxGroup(group, host);
    auto paintProperty = host->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->GetCheckBoxGroupSelect().value_or(false)) {
        paintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
        UpdateUIStatus(true);
        initSelected_ = true;
    }
    isFirstCreated_ = false;
    SetPreGroup(group);
}

void CheckBoxGroupPattern::OnAfterModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    if (inspectorId.empty()) {
        return;
    }

    auto eventHub = host->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);
    std::vector<std::string> vec;
    if (initSelected_) {
        auto groupManager = GetGroupManager();
        CHECK_NULL_VOID(groupManager);
        auto list = groupManager->GetCheckboxList(GetGroupNameWithNavId());
        for (auto node : list) {
            if (!node) {
                continue;
            }
            auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
            CHECK_NULL_VOID(paintProperty);
            auto eventHub = node->GetEventHub<CheckBoxEventHub>();
            CHECK_NULL_VOID(eventHub);
            vec.push_back(eventHub->GetName());
        }
    }
    Recorder::NodeDataCache::Get().PutMultiple(host, inspectorId, eventHub->GetGroupName(), vec);
}

void CheckBoxGroupPattern::UpdateGroupCheckStatus(const RefPtr<FrameNode>& frameNode, bool select)
{
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateUIStatus(select);
    if (select) {
        paintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
    } else {
        paintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::NONE);
    }
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    UpdateCheckBoxStatus(frameNode, select);
}

void CheckBoxGroupPattern::UpdateCheckBoxStatus(const RefPtr<FrameNode>& frameNode, bool select)
{
    auto groupManager = GetGroupManager();
    CHECK_NULL_VOID(groupManager);
    auto group = GetGroupNameWithNavId();
    auto list = groupManager->GetCheckboxList(group);
    std::vector<std::string> vec;
    auto status =
        select ? CheckBoxGroupPaintProperty::SelectStatus::ALL : CheckBoxGroupPaintProperty::SelectStatus::NONE;
    for (auto && node : list) {
        if (!node) {
            continue;
        }
        auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        auto eventHub = node->GetEventHub<CheckBoxEventHub>();
        CHECK_NULL_VOID(eventHub);
        if (select) {
            vec.push_back(eventHub->GetName());
        }
        if (paintProperty->GetCheckBoxSelectValue(false) != select) {
            paintProperty->UpdateCheckBoxSelect(select);
            auto pattern = node->GetPattern<CheckBoxPattern>();
            pattern->StartCustomNodeAnimation(select);
            pattern->UpdateUIStatus(select);
            pattern->SetLastSelect(select);
            eventHub->UpdateChangeEvent(select);
        }
    }
    CheckboxGroupResult groupResult(vec, int(status));
    auto eventHub = frameNode->GetEventHub<CheckBoxGroupEventHub>();
    eventHub->UpdateChangeEvent(&groupResult);
}

void CheckBoxGroupPattern::UpdateRepeatedGroupStatus(const RefPtr<FrameNode>& frameNode, bool select)
{
    std::vector<std::string> vec;
    auto status =
        select ? CheckBoxGroupPaintProperty::SelectStatus::ALL : CheckBoxGroupPaintProperty::SelectStatus::NONE;
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateUIStatus(select);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->SetSelectStatus(
        select ? CheckBoxGroupPaintProperty::SelectStatus::ALL : CheckBoxGroupPaintProperty::SelectStatus::NONE);
    auto checkBoxGroupEventHub = GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(checkBoxGroupEventHub);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    CheckboxGroupResult groupResult(vec, int(status));
    auto eventHub = frameNode->GetEventHub<CheckBoxGroupEventHub>();
    eventHub->UpdateChangeEvent(&groupResult);
}

void CheckBoxGroupPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
}

void CheckBoxGroupPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto groupPaintProperty = GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(groupPaintProperty);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto checkboxGroupStyle = groupPaintProperty->GetCheckBoxGroupSelectedStyleValue(CheckBoxStyle::CIRCULAR_STYLE);
        if (checkboxGroupStyle == CheckBoxStyle::CIRCULAR_STYLE) {
            InnerFocusPaintCircle(paintRect);
            return;
        }
    }
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

void CheckBoxGroupPattern::InnerFocusPaintCircle(RoundRect& paintRect)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(radioTheme);
    auto focusPaintPadding = radioTheme->GetFocusPaintPadding().ConvertToPx();
    float outCircleRadius = size_.Width() / 2 + focusPaintPadding;
    float originX = offset_.GetX() - focusPaintPadding;
    float originY = offset_.GetY() - focusPaintPadding;
    float width = size_.Width() + 2 * focusPaintPadding;
    float height = size_.Height() + 2 * focusPaintPadding;
    paintRect.SetRect({ originX, originY, width, height });
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, outCircleRadius, outCircleRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, outCircleRadius, outCircleRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, outCircleRadius, outCircleRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, outCircleRadius, outCircleRadius);
}

FocusPattern CheckBoxGroupPattern::GetFocusPattern() const
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
void CheckBoxGroupPattern::AddHotZoneRect()
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

void CheckBoxGroupPattern::RemoveLastHotZoneRect() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveLastHotZoneRect();
}

void CheckBoxGroupPattern::InitializeModifierParam(CheckBoxGroupModifier::Parameters& paintParameters)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    paintParameters.borderWidth = checkBoxTheme->GetBorderWidth().ConvertToPx();
    paintParameters.borderRadius = checkBoxTheme->GetBorderRadius().ConvertToPx();
    paintParameters.checkStroke = checkBoxTheme->GetCheckStroke().ConvertToPx();
    paintParameters.pointColor = checkBoxTheme->GetPointColor();
    paintParameters.activeColor = checkBoxTheme->GetActiveColor();
    paintParameters.inactiveColor = checkBoxTheme->GetInactiveColor();
    paintParameters.inactivePointColor = checkBoxTheme->GetInactivePointColor();
    paintParameters.shadowColor = checkBoxTheme->GetShadowColor();
    paintParameters.clickEffectColor = checkBoxTheme->GetClickEffectColor();
    paintParameters.hoverColor = checkBoxTheme->GetHoverColor();
    paintParameters.hoverRadius = checkBoxTheme->GetHoverRadius();
    paintParameters.hotZoneHorizontalPadding = checkBoxTheme->GetHotZoneHorizontalPadding();
    paintParameters.hotZoneVerticalPadding = checkBoxTheme->GetHotZoneVerticalPadding();
    paintParameters.shadowWidth = checkBoxTheme->GetShadowWidth();
    paintParameters.checkMarkPaintSize = checkBoxTheme->GetDefaultWidth().ConvertToPx();
    paintParameters.hoverDuration = checkBoxTheme->GetHoverDuration();
    paintParameters.hoverToTouchDuration = checkBoxTheme->GetHoverToTouchDuration();
    paintParameters.uiStatus = UIStatus::UNSELECTED;
    paintParameters.status = CheckBoxGroupPaintProperty::SelectStatus::NONE;
    paintParameters.defaultPaddingSize = checkBoxTheme->GetDefaultPaddingSize();
}

void CheckBoxGroupPattern::UpdateModifierParam(CheckBoxGroupModifier::Parameters& paintParameters)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto contentSize = geometryNode->GetContentSize();

    if (paintProperty->HasCheckBoxGroupSelectedColor()) {
        paintParameters.activeColor = paintProperty->GetCheckBoxGroupSelectedColorValue();
    }
    if (paintProperty->HasCheckBoxGroupUnSelectedColor()) {
        paintParameters.inactiveColor = paintProperty->GetCheckBoxGroupUnSelectedColorValue();
    }
    if (paintProperty->HasCheckBoxGroupCheckMarkColor()) {
        paintParameters.pointColor = paintProperty->GetCheckBoxGroupCheckMarkColorValue();
    }
    if (paintProperty->HasCheckBoxGroupCheckMarkSize()) {
        if (paintProperty->GetCheckBoxGroupCheckMarkSizeValue().ConvertToPx() >= 0) {
            paintParameters.checkMarkPaintSize = paintProperty->GetCheckBoxGroupCheckMarkSizeValue().ConvertToPx();
        } else {
            paintParameters.checkMarkPaintSize = contentSize.Width();
        }
    }
    if (paintProperty->HasCheckBoxGroupCheckMarkWidth()) {
        paintParameters.checkStroke =
            static_cast<float>(paintProperty->GetCheckBoxGroupCheckMarkWidthValue().ConvertToPx());
    }
}

void CheckBoxGroupPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto renderContext = host->GetRenderContext();
    auto checkBoxGroupPaintProperty = host->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(checkBoxGroupPaintProperty);
    checkBoxGroupPaintProperty->UpdateCheckBoxGroupSelectedColor(checkBoxTheme->GetActiveColor());
    checkBoxGroupPaintProperty->UpdateCheckBoxGroupUnSelectedColor(checkBoxTheme->GetInactiveColor());
    checkBoxGroupPaintProperty->UpdateCheckBoxGroupCheckMarkColor(checkBoxTheme->GetPointColor());
    host->MarkModifyDone();
    host->MarkDirtyNode();
}

void CheckBoxGroupPattern::OnAttachToMainTree()
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

std::string CheckBoxGroupPattern::GetGroupNameWithNavId()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto eventHub = host->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_RETURN(eventHub, "");
    if (currentNavId_.has_value()) {
        return eventHub->GetGroupName() + currentNavId_.value();
    }
    auto groupManager = GetGroupManager();
    CHECK_NULL_RETURN(groupManager, eventHub->GetGroupName());
    return eventHub->GetGroupName() + groupManager->GetLastNavId();
}

RefPtr<GroupManager> CheckBoxGroupPattern::GetGroupManager()
{
    auto manager = groupManager_.Upgrade();
    if (manager) {
        return manager;
    }
    groupManager_ = GroupManager::GetGroupManager();
    return groupManager_.Upgrade();
}

void CheckBoxGroupPattern::UpdateCheckBoxStyle()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto groupManager = GetGroupManager();
    CHECK_NULL_VOID(groupManager);
    auto checkBoxGroupEventHub = GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(checkBoxGroupEventHub);
    auto group = checkBoxGroupEventHub->GetGroupName();
    auto list = groupManager->GetCheckboxList(group);
    CheckBoxStyle groupStyle;
    GetCheckBoxGroupStyle(host, groupStyle);
    for (auto node : list) {
        if (!node) {
            continue;
        }
        auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        SetCheckBoxStyle(paintProperty, node, groupStyle);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxGroupPattern::GetCheckBoxGroupStyle(const RefPtr<FrameNode>& frameNode, CheckBoxStyle& checkboxGroupStyle)
{
    auto groupPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(groupPaintProperty);
    checkboxGroupStyle = groupPaintProperty->GetCheckBoxGroupSelectedStyleValue(CheckBoxStyle::CIRCULAR_STYLE);
}

void CheckBoxGroupPattern::SetCheckBoxStyle(const RefPtr<CheckBoxPaintProperty>& paintProperty,
    const RefPtr<FrameNode>& checkboxNode, CheckBoxStyle checkBoxGroupStyle)
{
    CHECK_NULL_VOID(paintProperty);
    CHECK_NULL_VOID(checkboxNode);
    auto pattern = checkboxNode->GetPattern<CheckBoxPattern>();
    CHECK_NULL_VOID(pattern);
    if (!paintProperty->HasCheckBoxSelectedStyle() ||
        pattern->GetOriginalCheckboxStyle() == OriginalCheckBoxStyle::NONE) {
        pattern->SetOriginalCheckboxStyle(OriginalCheckBoxStyle::NONE);
        paintProperty->UpdateCheckBoxSelectedStyle(checkBoxGroupStyle);
        checkboxNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}
} // namespace OHOS::Ace::NG
