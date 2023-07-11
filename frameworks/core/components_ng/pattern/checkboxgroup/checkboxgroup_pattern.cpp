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

#include "core/components/checkable/checkable_component.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void CheckBoxGroupPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
}

void CheckBoxGroupPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_VOID(pageEventHub);
    auto checkBoxGroupEventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(checkBoxGroupEventHub);
    pageEventHub->RemoveCheckBoxFromGroup(checkBoxGroupEventHub->GetGroupName(), frameNode->GetId());
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
        checkboxPattern->OnClick();
    };
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
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
    isClick_ = true;
    UpdateState();
}

void CheckBoxGroupPattern::OnTouchDown()
{
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
    auto pattern = host->GetPattern<CheckBoxGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto eventHub = host->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_VOID(pageEventHub);

    auto preGroup = pattern->GetPreGroup();
    auto group = eventHub->GetGroupName();
    if (!preGroup.has_value()) {
        pageEventHub->AddCheckBoxGroupToGroup(group, host->GetId());
        auto paintProperty = host->GetPaintProperty<CheckBoxGroupPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        if (paintProperty->HasCheckBoxGroupSelect() && paintProperty->GetCheckBoxGroupSelectValue()) {
            auto selectAll = paintProperty->GetCheckBoxGroupSelectValue();
            if (selectAll) {
                paintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
            }
            if (selectAll || (!selectAll && !isFirstCreated_)) {
                UpdateUIStatus(selectAll);
            }
        }
        isFirstCreated_ = false;
        pattern->SetPreGroup(group);
        return;
    }
    if (preGroup.value() != group) {
        pageEventHub->RemoveCheckBoxFromGroup(preGroup.value(), host->GetId());
        pageEventHub->AddCheckBoxGroupToGroup(group, host->GetId());
        pattern->SetPreGroup(group);
        return;
    }
    auto paintProperty = host->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (!paintProperty->HasCheckBoxGroupSelect()) {
        return;
    }
    bool isSelected = paintProperty->GetCheckBoxGroupSelectValue();
    paintProperty->ResetCheckBoxGroupSelect();

    // Setting selectAll to false when clicked requires processing, changing selectAll to false dynamically does
    // not require processing
    if (isClick_ || isSelected) {
        if (pattern->GetIsAddToMap()) {
            UpdateGroupCheckStatus(host, isSelected);
        } else {
            UpdateRepeatedGroupStatus(host, isSelected);
        }
    }
    isClick_ = false;
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
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_VOID(pageEventHub);
    auto checkBoxGroupEventHub = GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(checkBoxGroupEventHub);
    auto checkBoxGroupMap = pageEventHub->GetCheckBoxGroupMap();
    auto group = checkBoxGroupEventHub->GetGroupName();
    UpdateCheckBoxStatus(frameNode, checkBoxGroupMap, group, select);
}

void CheckBoxGroupPattern::UpdateCheckBoxStatus(const RefPtr<FrameNode>& frameNode,
    std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>> checkBoxGroupMap, const std::string& group,
    bool select)
{
    std::vector<std::string> vec;
    auto status =
        select ? CheckBoxGroupPaintProperty::SelectStatus::ALL : CheckBoxGroupPaintProperty::SelectStatus::NONE;
    const auto& list = checkBoxGroupMap[group];
    for (auto&& item : list) {
        auto node = item.Upgrade();
        if (node == frameNode) {
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
        auto eventHub = node->GetEventHub<CheckBoxEventHub>();
        CHECK_NULL_VOID(eventHub);
        if (select) {
            vec.push_back(eventHub->GetName());
        }
    }
    CheckboxGroupResult groupResult(vec, int(status));
    auto eventHub = frameNode->GetEventHub<CheckBoxGroupEventHub>();
    eventHub->UpdateChangeEvent(&groupResult);
    for (auto&& item : list) {
        auto node = item.Upgrade();
        if (node == frameNode) {
            continue;
        }
        if (!node) {
            continue;
        }
        if (node->GetTag() == V2::CHECKBOXGROUP_ETS_TAG) {
            continue;
        } else {
            auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
            CHECK_NULL_VOID(paintProperty);
            auto eventHub = node->GetEventHub<CheckBoxEventHub>();
            CHECK_NULL_VOID(eventHub);

            if (!paintProperty->HasCheckBoxSelect()) {
                if (select) {
                    paintProperty->UpdateCheckBoxSelect(select);
                    auto pattern = node->GetPattern<CheckBoxPattern>();
                    pattern->UpdateUIStatus(select);
                    pattern->SetLastSelect(select);
                    eventHub->UpdateChangeEvent(select);
                }
            }
            if (paintProperty->HasCheckBoxSelect() && paintProperty->GetCheckBoxSelectValue() != select) {
                paintProperty->UpdateCheckBoxSelect(select);
                auto pattern = node->GetPattern<CheckBoxPattern>();
                pattern->UpdateUIStatus(select);
                pattern->SetLastSelect(select);
                eventHub->UpdateChangeEvent(select);
            }
        }
    }
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
    host->AddHotZoneRect(hotZoneRegion);
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
} // namespace OHOS::Ace::NG
