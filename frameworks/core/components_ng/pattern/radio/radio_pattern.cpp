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
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/radio/radio_layout_algorithm.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/property/property.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int DEFAULT_RADIO_ANIMATION_DURATION = 300;
constexpr float DEFAULT_MID_TIME_SLOT = 0.5;
constexpr float DEFAULT_END_TIME_SLOT = 1.0;
constexpr float DEFAULT_SHRINK_TIME_SLOT = 0.9;
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
    UpdateState();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(radioTheme);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->GetMarginProperty()) {
        MarginProperty margin;
        margin.left = CalcLength(radioTheme->GetHotZoneHorizontalPadding().Value());
        margin.right = CalcLength(radioTheme->GetHotZoneHorizontalPadding().Value());
        margin.top = CalcLength(radioTheme->GetHotZoneVerticalPadding().Value());
        margin.bottom = CalcLength(radioTheme->GetHotZoneVerticalPadding().Value());
        layoutProperty->UpdateMargin(margin);
    }
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
    host->MarkNeedRenderOnly();
}

void RadioPattern::UpdateState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(pattern);
    auto eventHub = host->GetEventHub<RadioEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto preGroup = pattern->GetPreGroup();
    auto group = eventHub->GetGroup();
    if (!preGroup.has_value()) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto stageManager = pipelineContext->GetStageManager();
        CHECK_NULL_VOID(stageManager);
        auto pageNode = stageManager->GetLastPage();
        CHECK_NULL_VOID(pageNode);
        auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
        CHECK_NULL_VOID(pageEventHub);
        pageEventHub->AddRadioToGroup(group, host->GetId());
    } else {
        if (preGroup.value() != group) {
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto stageManager = pipelineContext->GetStageManager();
            CHECK_NULL_VOID(stageManager);
            auto pageNode = stageManager->GetLastPage();
            CHECK_NULL_VOID(pageNode);
            auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
            CHECK_NULL_VOID(pageEventHub);

            pageEventHub->RemoveRadioFromGroup(preGroup.value(), host->GetId());
            pageEventHub->AddRadioToGroup(group, host->GetId());
        }
    }
    pattern->SetPreGroup(group);

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
            if (!isFirstCreated_) {
                PlayAnimation(true);
            }
        } else {
            // If the radio is set to false, set isFirstCreated_ to false.
            isFirstCreated_ = false;
        }
    } else {
        paintProperty->UpdateRadioCheck(false);
        // If the radio check is not set, set isFirstCreated_ to false.
        isFirstCreated_ = false;
    }
    if (preCheck_ != check) {
        UpdateGroupCheckStatus(host, check);
    }
    preCheck_ = check;
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
        PlayAnimation(false);
    }
    preCheck_ = false;
}

void RadioPattern::UpdateGroupCheckStatus(const RefPtr<FrameNode>& frameNode, bool check)
{
    frameNode->MarkNeedRenderOnly();

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
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
        PlayAnimation(false);
    }

    if (!isFirstCreated_) {
        radioEventHub->UpdateChangeEvent(check);
    }
    // If the radio is set to true at creation time, set isFirstCreated_ to false here.
    isFirstCreated_ = false;
}

void RadioPattern::PlayAnimation(bool isOn)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!onController_) {
        onController_ = AceType::MakeRefPtr<Animator>(host->GetContext());
        onController_->AddStopListener(Animator::StatusCallback([weak = AceType::WeakClaim(this)]() {
            auto radio = weak.Upgrade();
            if (radio) {
                radio->UpdateUIStatus(true);
            }
        }));
    }
    if (!offController_) {
        offController_ = AceType::MakeRefPtr<Animator>(host->GetContext());
        offController_->AddStopListener(Animator::StatusCallback([weak = AceType::WeakClaim(this)]() {
            auto radio = weak.Upgrade();
            if (radio) {
                radio->UpdateUIStatus(false);
            }
        }));
    }
    StopTranslateAnimation();
    RefPtr<KeyframeAnimation<float>> shrinkEngine = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    RefPtr<KeyframeAnimation<float>> selectEngine = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    RefPtr<KeyframeAnimation<float>> selectRingEngine = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    onController_->ClearInterpolators();
    offController_->ClearInterpolators();
    auto shrinkFrameStart = AceType::MakeRefPtr<Keyframe<float>>(0.0, 1.0);
    auto shrinkFrameMid = AceType::MakeRefPtr<Keyframe<float>>(DEFAULT_MID_TIME_SLOT, DEFAULT_SHRINK_TIME_SLOT);
    auto shrinkFrameEnd = AceType::MakeRefPtr<Keyframe<float>>(DEFAULT_END_TIME_SLOT, 1.0);
    shrinkEngine->AddKeyframe(shrinkFrameStart);
    shrinkEngine->AddKeyframe(shrinkFrameMid);
    shrinkEngine->AddKeyframe(shrinkFrameEnd);
    shrinkEngine->SetCurve(Curves::FRICTION);
    shrinkEngine->AddListener(Animation<float>::ValueCallback([weak = AceType::WeakClaim(this)](float value) {
        auto radio = weak.Upgrade();
        if (radio) {
            radio->UpdateTotalScale(value);
        }
    }));

    auto selectFrameStart = AceType::MakeRefPtr<Keyframe<float>>(0.0, isOn ? 0.0 : 0.5);
    auto selectFrameMid = AceType::MakeRefPtr<Keyframe<float>>(DEFAULT_MID_TIME_SLOT, 0.0);
    auto selectFrameEnd = AceType::MakeRefPtr<Keyframe<float>>(DEFAULT_END_TIME_SLOT, isOn ? 0.5 : 0.0);
    selectEngine->AddKeyframe(selectFrameStart);
    selectEngine->AddKeyframe(selectFrameMid);
    selectEngine->AddKeyframe(selectFrameEnd);
    selectEngine->SetCurve(Curves::FRICTION);
    selectEngine->AddListener(Animation<float>::ValueCallback([weak = AceType::WeakClaim(this)](float value) {
        auto radio = weak.Upgrade();
        if (radio) {
            radio->UpdatePointScale(value);
        }
    }));

    auto selectRingFrameStart = AceType::MakeRefPtr<Keyframe<float>>(0.0, isOn ? 1.0 : 0.0);
    auto selectRingFrameMid = AceType::MakeRefPtr<Keyframe<float>>(DEFAULT_MID_TIME_SLOT, 0.0);
    auto selectRingFrameEnd = AceType::MakeRefPtr<Keyframe<float>>(DEFAULT_END_TIME_SLOT, isOn ? 0.0 : 1.0);
    selectRingEngine->AddKeyframe(selectRingFrameStart);
    selectRingEngine->AddKeyframe(selectRingFrameMid);
    selectRingEngine->AddKeyframe(selectRingFrameEnd);
    selectRingEngine->SetCurve(Curves::FRICTION);
    selectRingEngine->AddListener(Animation<float>::ValueCallback([weak = AceType::WeakClaim(this)](float value) {
        auto radio = weak.Upgrade();
        if (radio) {
            radio->UpdateRingPointScale(value);
        }
    }));

    if (isOn) {
        onController_->AddInterpolator(shrinkEngine);
        onController_->AddInterpolator(selectEngine);
        onController_->AddInterpolator(selectRingEngine);
        onController_->SetDuration(DEFAULT_RADIO_ANIMATION_DURATION);
        onController_->Play();
    } else {
        offController_->AddInterpolator(shrinkEngine);
        offController_->AddInterpolator(selectEngine);
        offController_->AddInterpolator(selectRingEngine);
        offController_->SetDuration(DEFAULT_RADIO_ANIMATION_DURATION);
        offController_->Play();
    }
}

void RadioPattern::StopTranslateAnimation()
{
    if (offController_ && !offController_->IsStopped()) {
        offController_->Stop();
    }
    if (onController_ && !onController_->IsStopped()) {
        onController_->Stop();
    }
}

void RadioPattern::UpdateUIStatus(bool check)
{
    uiStatus_ = check ? UIStatus::SELECTED : UIStatus::UNSELECTED;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkNeedRenderOnly();
}

void RadioPattern::UpdateTotalScale(float scale)
{
    totalScale_ = scale;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkNeedRenderOnly();
}

void RadioPattern::UpdatePointScale(float scale)
{
    pointScale_ = scale;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkNeedRenderOnly();
}

void RadioPattern::UpdateRingPointScale(float scale)
{
    ringPointScale_ = scale;
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
    offset_ = geometryNode->GetContentOffset();
    size_ = geometryNode->GetContentSize();
    
    auto offset = geometryNode->GetContentOffset();
    auto size = geometryNode->GetContentSize();
    if (offset != offset_ || size != size_) {
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
    hotZoneSize_.SetWidth(size_.Width() + 2 * hotZoneHorizontalPadding_.ConvertToPx());
    hotZoneSize_.SetHeight(size_.Height() + 2 * hotZoneVerticalPadding_.ConvertToPx());
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

} // namespace OHOS::Ace::NG
