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
    auto pipeline = host->GetContext();
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
    InitClickEvent();
    InitTouchEvent();
    InitMouseEvent();
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
        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
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
    auto eventHub = GetHost()->GetEventHub<RadioEventHub>();
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isTouch_ = false;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
    if (preCheck_ && check) {
        UpdateUIStatus(true);
        PlayAnimation(true);
    }
    if (!preCheck_ && !check) {
        paintProperty->UpdateRadioCheck(true);
        UpdateState();
    }
}

void RadioPattern::OnTouchDown()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isTouch_ = true;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RadioPattern::OnTouchUp()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isTouch_ = false;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
        if (check) {
            UpdateUIStatus(true);
            PlayAnimation(true);
        } else {
            isFirstCreated_ = false;
        }
    } else {
        paintProperty->UpdateRadioCheck(false);
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
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

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
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

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
    if (!isFirstCreated_) {
        radioEventHub->UpdateChangeEvent(check);
    }
    isFirstCreated_ = false;
    if (check) {
        pageEventHub->UpdateRadioGroupValue(radioEventHub->GetGroup(), frameNode->GetId());
    } else {
        auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
        CHECK_NULL_VOID(radioPaintProperty);
        radioPaintProperty->UpdateRadioCheck(check);
    }
}

void RadioPattern::PlayAnimation(bool isOn)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!onController_) {
        onController_ = AceType::MakeRefPtr<Animator>(host->GetContext());
    }
    if (!offController_) {
        offController_ = AceType::MakeRefPtr<Animator>(host->GetContext());
    }
    RefPtr<KeyframeAnimation<float>> shrinkEngine = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    RefPtr<KeyframeAnimation<float>> selectEngine = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    onController_->ClearInterpolators();
    offController_->ClearInterpolators();
    auto shrinkFrameStart = AceType::MakeRefPtr<Keyframe<float>>(0.0, 1.0);
    auto shrinkFrameMid = AceType::MakeRefPtr<Keyframe<float>>(DEFAULT_MID_TIME_SLOT, DEFAULT_SHRINK_TIME_SLOT);
    shrinkFrameMid->SetCurve(Curves::FRICTION);
    auto shrinkFrameEnd = AceType::MakeRefPtr<Keyframe<float>>(DEFAULT_END_TIME_SLOT, 1.0);
    shrinkFrameEnd->SetCurve(Curves::FRICTION);
    shrinkEngine->AddKeyframe(shrinkFrameStart);
    shrinkEngine->AddKeyframe(shrinkFrameMid);
    shrinkEngine->AddKeyframe(shrinkFrameEnd);
    shrinkEngine->AddListener(Animation<float>::ValueCallback([weak = AceType::WeakClaim(this)](float value) {
        auto radio = weak.Upgrade();
        if (radio) {
            radio->UpdateTotalScale(value);
        }
    }));

    auto selectFrameStart = AceType::MakeRefPtr<Keyframe<float>>(0.0, isOn ? 1.0 : 0.5);
    auto selectFrameMid = AceType::MakeRefPtr<Keyframe<float>>(DEFAULT_MID_TIME_SLOT, 0.0);
    selectFrameMid->SetCurve(Curves::FRICTION);
    auto selectFrameEnd = AceType::MakeRefPtr<Keyframe<float>>(DEFAULT_END_TIME_SLOT, isOn ? 0.5 : 1.0);
    selectFrameEnd->SetCurve(Curves::FRICTION);
    selectEngine->AddKeyframe(selectFrameStart);
    selectEngine->AddKeyframe(selectFrameMid);
    selectEngine->AddKeyframe(selectFrameEnd);
    selectEngine->AddListener(Animation<float>::ValueCallback([weak = AceType::WeakClaim(this)](float value) {
        auto radio = weak.Upgrade();
        if (radio) {
            radio->UpdatePointScale(value);
        }
    }));
    if (isOn) {
        onController_->AddInterpolator(shrinkEngine);
        onController_->AddInterpolator(selectEngine);
        onController_->SetDuration(DEFAULT_RADIO_ANIMATION_DURATION);
        onController_->Play();
    } else {
        offController_->AddStopListener(Animator::StatusCallback([weak = AceType::WeakClaim(this)]() {
            auto radio = weak.Upgrade();
            if (radio) {
                radio->UpdateUIStatus(false);
            }
        }));
        offController_->AddInterpolator(shrinkEngine);
        offController_->AddInterpolator(selectEngine);
        offController_->SetDuration(DEFAULT_RADIO_ANIMATION_DURATION);
        offController_->Play();
    }
}

void RadioPattern::UpdateUIStatus(bool check)
{
    uiStatus_ = check ? UIStatus::SELECTED : UIStatus::UNSELECTED;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RadioPattern::UpdateTotalScale(float scale)
{
    totalScale_ = scale;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RadioPattern::UpdatePointScale(float scale)
{
    pointScale_ = scale;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

} // namespace OHOS::Ace::NG
