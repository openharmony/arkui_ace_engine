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

#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"

#include <algorithm>
#include <cmath>
#include <cstdint>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scrollable.h"
#include "core/components/test/unittest/image/image_test_utils.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_layout_algorithm.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
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
        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
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
    auto eventHub = GetHost()->GetEventHub<CheckBoxGroupEventHub>();
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isTouch_ = false;
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto originalPaintRect = renderContext->GetPaintRectWithoutTransform();
    auto frameSize = geometryNode->GetFrameSize();
    if (isHover_ && originalPaintRect.GetSize() == frameSize) {
        originalPaintRect = GetHotZoneRect(true);
        renderContext->SyncGeometryProperties(originalPaintRect);
    } else if (!isHover_ && originalPaintRect.GetSize() != frameSize) {
        originalPaintRect = GetHotZoneRect(false);
    }
    renderContext->SyncGeometryProperties(originalPaintRect);
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
    isSelected = status != CheckBoxGroupPaintProperty::SelectStatus::ALL;
    paintProperty->UpdateCheckBoxGroupSelect(isSelected);
    isClick_ = true;
    UpdateState();
}

void CheckBoxGroupPattern::OnTouchDown()
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

void CheckBoxGroupPattern::OnTouchUp()
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
    if (paintRect.GetSize() != frameSize && !isHover_) {
        paintRect = GetHotZoneRect(false);
    }
    renderContext->SyncGeometryProperties(paintRect);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxGroupPattern::UpdateAnimation(bool check)
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
    uiStatus_ = check ? UIStatus::OFF_TO_ON : UIStatus::ON_TO_OFF;
    shapeScale_ = 1.0f;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxGroupPattern::UpdateCheckBoxShape(const float value)
{
    if (value < DEFAULT_MIN_CHECKBOX_SHAPE_SCALE || value > DEFAULT_MAX_CHECKBOX_SHAPE_SCALE) {
        return;
    }
    shapeScale_ = value;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
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
    pattern->UpdateAnimation(select);
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
                    pattern->UpdateAnimation(select);
                    pattern->SetLastSelect(select);
                    eventHub->UpdateChangeEvent(select);
                }
            }
            if (paintProperty->HasCheckBoxSelect() && paintProperty->GetCheckBoxSelectValue() != select) {
                paintProperty->UpdateCheckBoxSelect(select);
                auto pattern = node->GetPattern<CheckBoxPattern>();
                pattern->UpdateUIStatus(select);
                pattern->UpdateAnimation(select);
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
    pattern->UpdateAnimation(select);
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

RectF CheckBoxGroupPattern::GetHotZoneRect(bool isOriginal) const
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

} // namespace OHOS::Ace::NG
