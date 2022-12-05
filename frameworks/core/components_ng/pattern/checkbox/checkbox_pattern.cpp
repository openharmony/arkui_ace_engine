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

#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"

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
constexpr int32_t DEFUALT_CHECKBOX_ANIMATION_DURATION = 150;
constexpr float DEFAULT_MAX_CHECKBOX_SHAPE_SCALE = 1.0;
constexpr float DEFAULT_MIN_CHECKBOX_SHAPE_SCALE = 0.0;
} // namespace

void CheckBoxPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
}

void CheckBoxPattern::OnModifyDone()
{
    UpdateState();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->GetMarginProperty()) {
        MarginProperty margin;
        margin.left = CalcLength(checkBoxTheme->GetHotZoneHorizontalPadding());
        margin.right = CalcLength(checkBoxTheme->GetHotZoneHorizontalPadding());
        margin.top = CalcLength(checkBoxTheme->GetHotZoneVerticalPadding());
        margin.bottom = CalcLength(checkBoxTheme->GetHotZoneVerticalPadding());
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
        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
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
    isHover_ = isHover;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxPattern::OnClick()
{
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
    auto checkboxEventHub = GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(checkboxEventHub);
    checkboxEventHub->UpdateChangeEvent(!isSelected);
}

void CheckBoxPattern::OnTouchDown()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isTouch_ = true;
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto originalPaintRect = renderContext->GetPaintRectWithoutTransform();
    auto frameSize = geometryNode->GetFrameSize();
    if (originalPaintRect.GetSize() == frameSize) {
        originalPaintRect = GetHotZoneRect(true);
    }
    renderContext->SyncGeometryProperties(originalPaintRect);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxPattern::OnTouchUp()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isTouch_ = false;
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    auto frameSize = geometryNode->GetFrameSize();
    if (paintRect.GetSize() != frameSize) {
        paintRect = GetHotZoneRect(false);
    }
    renderContext->SyncGeometryProperties(paintRect);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxPattern::UpdateAnimation(bool check)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!controller_) {
        controller_ = AceType::MakeRefPtr<Animator>(host->GetContext());
        auto weak = AceType::WeakClaim(this);
        controller_->AddStopListener(Animator::StatusCallback([weak]() {
            auto checkBox = weak.Upgrade();
            if (checkBox) {
                checkBox->UpdateUnSelect();
            }
        }));
    }
    float from = 0.0;
    float to = 0.0;
    if (!check) {
        from = DEFAULT_MAX_CHECKBOX_SHAPE_SCALE;
        to = DEFAULT_MIN_CHECKBOX_SHAPE_SCALE;
    } else {
        from = DEFAULT_MIN_CHECKBOX_SHAPE_SCALE;
        to = DEFAULT_MAX_CHECKBOX_SHAPE_SCALE;
    }

    if (translate_) {
        controller_->RemoveInterpolator(translate_);
    }
    translate_ = AceType::MakeRefPtr<CurveAnimation<float>>(from, to, Curves::FRICTION);
    auto weak = AceType::WeakClaim(this);
    translate_->AddListener(Animation<float>::ValueCallback([weak](float value) {
        auto checkBox = weak.Upgrade();
        if (checkBox) {
            checkBox->UpdateCheckBoxShape(value);
        }
    }));
    controller_->SetDuration(DEFUALT_CHECKBOX_ANIMATION_DURATION);
    controller_->AddInterpolator(translate_);
    controller_->Play();
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
    uiStatus_ = check ? UIStatus::OFF_TO_ON : UIStatus::ON_TO_OFF;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxPattern::UpdateCheckBoxShape(const float value)
{
    if (value < DEFAULT_MIN_CHECKBOX_SHAPE_SCALE || value > DEFAULT_MAX_CHECKBOX_SHAPE_SCALE) {
        return;
    }
    shapeScale_ = value;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxPattern::OnDetachFromFrameNode(FrameNode* frameNode)
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
    auto checkBoxEventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(checkBoxEventHub);
    pageEventHub->RemoveCheckBoxFromGroup(checkBoxEventHub->GetGroupName(), frameNode->GetId());
}

void CheckBoxPattern::UpdateState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<CheckBoxPattern>();
    CHECK_NULL_VOID(pattern);
    auto eventHub = host->GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_VOID(pageEventHub);
    auto paintProperty = host->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto checkBoxGroupMap = pageEventHub->GetCheckBoxGroupMap();
    auto preGroup = pattern->GetPreGroup();
    auto group = eventHub->GetGroupName();
    if (!preGroup.has_value()) {
        pageEventHub->AddCheckBoxToGroup(group, host->GetId());
        auto callback = [weak = WeakClaim(this)]() {
            auto checkbox = weak.Upgrade();
            if (checkbox) {
                checkbox->CheckBoxGroupIsTrue();
            }
        };
        PipelineContext::GetCurrentContext()->AddBuildFinishCallBack(callback);
        if (paintProperty->HasCheckBoxSelect()) {
            auto isSelected = paintProperty->GetCheckBoxSelectValue();
            if (isSelected || (!isSelected && !isFirstCreated_)) {
                UpdateUIStatus(isSelected);
            }
            SetLastSelect(isSelected);
        }
        isFirstCreated_ = false;
        pattern->SetPreGroup(group);
        return;
    }
    if (preGroup.has_value() && preGroup.value() != group) {
        pageEventHub->RemoveCheckBoxFromGroup(preGroup.value(), host->GetId());
        pageEventHub->AddCheckBoxToGroup(group, host->GetId());
    }
    pattern->SetPreGroup(group);
    bool isSelected = false;
    if (paintProperty->HasCheckBoxSelect()) {
        isSelected = paintProperty->GetCheckBoxSelectValue();
        if (lastSelect_ != isSelected) {
            UpdateUIStatus(isSelected);
            UpdateAnimation(isSelected);
            SetLastSelect(isSelected);
        }
    }
    UpdateCheckBoxGroupStatus(host, checkBoxGroupMap, isSelected);
}

void CheckBoxPattern::UpdateCheckBoxGroupStatus(const RefPtr<FrameNode>& checkBoxFrameNode,
    std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>>& checkBoxGroupMap, bool select)
{
    checkBoxFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto checkBoxEventHub = checkBoxFrameNode->GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(checkBoxEventHub);
    auto group = checkBoxEventHub->GetGroupName();
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
    CHECK_NULL_VOID(checkBoxGroupNode);
    auto groupPaintProperty = checkBoxGroupNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(groupPaintProperty);
    auto pattern = checkBoxGroupNode->GetPattern<CheckBoxGroupPattern>();
    CHECK_NULL_VOID(pattern);
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
    CheckboxGroupResult groupResult(vec, int(status));
    auto eventHub = checkBoxGroupNode->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->UpdateChangeEvent(&groupResult);
}

void CheckBoxPattern::CheckBoxGroupIsTrue()
{
    auto checkBoxFrameNode = GetHost();
    CHECK_NULL_VOID(checkBoxFrameNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_VOID(pageEventHub);
    auto paintProperty = checkBoxFrameNode->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto checkBoxGroupMap = pageEventHub->GetCheckBoxGroupMap();
    auto checkBoxEventHub = checkBoxFrameNode->GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(checkBoxEventHub);
    auto group = checkBoxEventHub->GetGroupName();
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

    CHECK_NULL_VOID_NOLOG(checkBoxGroupNode);
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

RectF CheckBoxPattern::GetHotZoneRect(bool isOriginal) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, {});
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, {});
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, {});
    auto originalPaintRect = renderContext->GetPaintRectWithoutTransform();
    auto offset = originalPaintRect.GetOffset();
    double actualWidth = 0.0;
    double actualHeight = 0.0;
    if (isOriginal) {
        actualWidth = geometryNode->GetFrameSize().Width() + hotZoneHorizontalPadding_.ConvertToPx() * 2;
        actualHeight = geometryNode->GetFrameSize().Height() + hotZoneVerticalPadding_.ConvertToPx() * 2;
        offset.SetX(offset.GetX() - hotZoneHorizontalPadding_.ConvertToPx());
        offset.SetY(offset.GetY() - hotZoneVerticalPadding_.ConvertToPx());
    } else {
        actualWidth = geometryNode->GetFrameSize().Width();
        actualHeight = geometryNode->GetFrameSize().Height();
        offset.SetX(offset.GetX() + hotZoneHorizontalPadding_.ConvertToPx());
        offset.SetY(offset.GetY() + hotZoneVerticalPadding_.ConvertToPx());
    }
    return RectF(offset, SizeF(actualWidth, actualHeight));
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
    auto borderRadius = checkBoxTheme->GetBorderRadius().ConvertToPx();
    auto paintSize = size_;
    auto paintOffset = offset_;
    auto focusPaintPadding = checkBoxTheme->GetFocusPaintPadding().ConvertToPx();
    float originX = paintOffset.GetX() - focusPaintPadding;
    float originY = paintOffset.GetY() - focusPaintPadding;
    float endX = paintSize.Width() + originX + 2 * focusPaintPadding;
    float endY = paintSize.Height() + originY + 2 * focusPaintPadding;
    paintRect.SetRect({ originX, originY, endX - originX, endY - originY });
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
    auto activeColor = checkBoxTheme->GetFocusColor();
    FocusPaintParam focusPaintParam;
    focusPaintParam.SetPaintColor(activeColor);
    return { FocusType::NODE, true, FocusStyleType::CUSTOM_REGION, focusPaintParam };
}

} // namespace OHOS::Ace::NG
