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

#include "core/components_ng/pattern/radio/radio_pattern.h"

#include "base/utils/utils.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/property/property.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int FOR_HOTZONESIZE_CALCULATE_MULTIPLY_TWO = 2;
} // namespace

void RadioPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
}

void RadioPattern::OnDetachFromFrameNode(FrameNode* frameNode)
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
    auto radioEventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(radioEventHub);
    pageEventHub->RemoveRadioFromGroup(radioEventHub->GetGroup(), frameNode->GetId());
}

void RadioPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    UpdateState();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(radioTheme);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    MarginProperty margin;
    margin.left = CalcLength(radioTheme->GetHotZoneHorizontalPadding().Value());
    margin.right = CalcLength(radioTheme->GetHotZoneHorizontalPadding().Value());
    margin.top = CalcLength(radioTheme->GetHotZoneVerticalPadding().Value());
    margin.bottom = CalcLength(radioTheme->GetHotZoneVerticalPadding().Value());
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
    hotZoneHorizontalPadding_ = radioTheme->GetHotZoneHorizontalPadding();
    hotZoneVerticalPadding_ = radioTheme->GetHotZoneVerticalPadding();
    InitClickEvent();
    InitTouchEvent();
    InitMouseEvent();
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
}

void RadioPattern::InitClickEvent()
{
    if (clickListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto radioPattern = weak.Upgrade();
        CHECK_NULL_VOID(radioPattern);
        radioPattern->OnClick();
    };
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void RadioPattern::InitTouchEvent()
{
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto radioPattern = weak.Upgrade();
        CHECK_NULL_VOID(radioPattern);
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            radioPattern->OnTouchDown();
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP ||
            info.GetTouches().front().GetTouchType() == TouchType::CANCEL) {
            radioPattern->OnTouchUp();
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void RadioPattern::InitMouseEvent()
{
    if (mouseEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto eventHub = host->GetEventHub<RadioEventHub>();
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

void RadioPattern::HandleMouseEvent(bool isHover)
{
    isHover_ = isHover;
    if (isHover) {
        touchHoverType_ = TouchHoverAnimationType::HOVER;
    } else {
        touchHoverType_ = TouchHoverAnimationType::NONE;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkNeedRenderOnly();
}

void RadioPattern::OnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    bool check = false;
    if (paintProperty->HasRadioCheck()) {
        check = paintProperty->GetRadioCheckValue();
    } else {
        paintProperty->UpdateRadioCheck(false);
    }
    if (!preCheck_ && !check) {
        paintProperty->UpdateRadioCheck(true);
        UpdateState();
    }
}

void RadioPattern::OnTouchDown()
{
    if (isHover_) {
        touchHoverType_ = TouchHoverAnimationType::HOVER_TO_PRESS;
    } else {
        touchHoverType_ = TouchHoverAnimationType::PRESS;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isTouch_ = true;
    host->MarkNeedRenderOnly();
}

void RadioPattern::OnTouchUp()
{
    if (isHover_) {
        touchHoverType_ = TouchHoverAnimationType::PRESS_TO_HOVER;
    } else {
        touchHoverType_ = TouchHoverAnimationType::NONE;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isTouch_ = false;
    host->MarkNeedRenderOnly();
}

void RadioPattern::CheckPageNode()
{
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
        auto eventHub = host->GetEventHub<RadioEventHub>();
        CHECK_NULL_VOID(eventHub);
        auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
        CHECK_NULL_VOID(pageEventHub);
        auto group = eventHub->GetGroup();

        pageEventHub->AddRadioToGroup(group, host->GetId());
        auto paintProperty = host->GetPaintProperty<RadioPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        bool check = false;
        if (paintProperty->HasRadioCheck()) {
            check = paintProperty->GetRadioCheckValue();
        }
        UpdateGroupCheckStatus(host, pageNode, check);
    }
}

void RadioPattern::UpdateState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<RadioEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_VOID(pageEventHub);
    auto preGroup = GetPreGroup();
    auto group = eventHub->GetGroup();
    if (!preGroup.has_value()) {
        pageEventHub->AddRadioToGroup(group, host->GetId());
        SetPrePageId(pageNode->GetId());
        auto callback = [weak = WeakClaim(this)]() {
            auto radio = weak.Upgrade();
            if (radio) {
                radio->CheckPageNode();
            }
        };
        pipelineContext->AddBuildFinishCallBack(callback);
    }
    if (preGroup.has_value() && preGroup.value() != group) {
        pageEventHub->RemoveRadioFromGroup(preGroup.value(), host->GetId());
        pageEventHub->AddRadioToGroup(group, host->GetId());
        SetPrePageId(pageNode->GetId());
        isGroupChanged_ = true;
    }
    SetPreGroup(group);

    auto paintProperty = host->GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    bool check = false;
    if (paintProperty->HasRadioCheck()) {
        check = paintProperty->GetRadioCheckValue();
        /*
         * Do not set isFirstCreated_ to false if the radio is set to true at creation time. The isFirstCreated_ is set
         * to false in UpdateGroupCheckStatus because isFirstCreated_ is also required to determine if an onChange event
         * needs to be triggered.
         */
        if (check) {
            UpdateUIStatus(true);
            isOnAnimationFlag_ = true;
        } else {
            // If the radio is set to false, set isFirstCreated_ to false.
            isFirstCreated_ = false;
        }
    } else {
        paintProperty->UpdateRadioCheck(false);
        // If the radio check is not set, set isFirstCreated_ to false.
        isFirstCreated_ = false;
    }
    if (preCheck_ != check || isGroupChanged_) {
        UpdateGroupCheckStatus(host, pageNode, check);
    }
    preCheck_ = check;
    isGroupChanged_ = false;
}

void RadioPattern::UpdateUncheckStatus(const RefPtr<FrameNode>& frameNode)
{
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(radioPaintProperty);
    radioPaintProperty->UpdateRadioCheck(false);
    frameNode->MarkNeedRenderOnly();

    if (preCheck_) {
        auto radioEventHub = GetEventHub<RadioEventHub>();
        CHECK_NULL_VOID(radioEventHub);
        radioEventHub->UpdateChangeEvent(false);
        isOnAnimationFlag_ = false;
    }
    preCheck_ = false;
}

void RadioPattern::UpdateGroupCheckStatus(
    const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& pageNode, bool check)
{
    frameNode->MarkNeedRenderOnly();

    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_VOID(pageEventHub);

    auto radioEventHub = GetEventHub<RadioEventHub>();
    CHECK_NULL_VOID(radioEventHub);
    if (check) {
        pageEventHub->UpdateRadioGroupValue(radioEventHub->GetGroup(), frameNode->GetId());
    } else {
        auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
        CHECK_NULL_VOID(radioPaintProperty);
        radioPaintProperty->UpdateRadioCheck(check);
        if (!isGroupChanged_) {
            isOnAnimationFlag_ = false;
        }
    }

    if (!isFirstCreated_) {
        radioEventHub->UpdateChangeEvent(check);
    }
}

void RadioPattern::UpdateUIStatus(bool check)
{
    uiStatus_ = check ? UIStatus::SELECTED : UIStatus::UNSELECTED;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkNeedRenderOnly();
}

void RadioPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (!pattern) {
            return false;
        }
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));

    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
}

bool RadioPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_ENTER) {
        OnClick();
        return true;
    }
    return false;
}

void RadioPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
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

FocusPattern RadioPattern::GetFocusPattern() const
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, FocusPattern());
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_RETURN(radioTheme, FocusPattern());
    auto activeColor = radioTheme->GetActiveColor();
    FocusPaintParam focusPaintParam;
    focusPaintParam.SetPaintColor(activeColor);
    return { FocusType::NODE, true, FocusStyleType::CUSTOM_REGION, focusPaintParam };
}

bool RadioPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& /*config*/)
{
    auto geometryNode = dirty->GetGeometryNode();
    auto offset = geometryNode->GetContentOffset();
    auto size = geometryNode->GetContentSize();
    if (!NearEqual(offset, offset_) || !NearEqual(size, size_)) {
        offset_ = offset;
        size_ = size;
        AddHotZoneRect();
    }
    return true;
}

// Set the default hot zone for the component.
void RadioPattern::AddHotZoneRect()
{
    hotZoneOffset_.SetX(offset_.GetX() - hotZoneHorizontalPadding_.ConvertToPx());
    hotZoneOffset_.SetY(offset_.GetY() - hotZoneVerticalPadding_.ConvertToPx());
    hotZoneSize_.SetWidth(
        size_.Width() + FOR_HOTZONESIZE_CALCULATE_MULTIPLY_TWO * hotZoneHorizontalPadding_.ConvertToPx());
    hotZoneSize_.SetHeight(
        size_.Height() + FOR_HOTZONESIZE_CALCULATE_MULTIPLY_TWO * hotZoneVerticalPadding_.ConvertToPx());
    DimensionRect hotZoneRegion;
    hotZoneRegion.SetSize(DimensionSize(Dimension(hotZoneSize_.Width()), Dimension(hotZoneSize_.Height())));
    hotZoneRegion.SetOffset(DimensionOffset(Dimension(hotZoneOffset_.GetX()), Dimension(hotZoneOffset_.GetY())));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->AddHotZoneRect(hotZoneRegion);
}

void RadioPattern::RemoveLastHotZoneRect() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveLastHotZoneRect();
}

std::string RadioPattern::ProvideRestoreInfo()
{
    auto jsonObj = JsonUtil::Create(true);
    auto radioPaintProperty = GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_RETURN(radioPaintProperty, "");
    jsonObj->Put("checked", radioPaintProperty->GetRadioCheck().value_or(false));
    return jsonObj->ToString();
}

void RadioPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    auto radioPaintProperty = GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(radioPaintProperty);
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info->IsValid() || !info->IsObject()) {
        return;
    }
    auto jsonChecked = info->GetValue("checked");
    radioPaintProperty->UpdateRadioCheck(jsonChecked->GetBool());
    OnModifyDone();
}
} // namespace OHOS::Ace::NG
