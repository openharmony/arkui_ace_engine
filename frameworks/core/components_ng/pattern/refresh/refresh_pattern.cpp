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

#include "core/components_ng/pattern/refresh/refresh_pattern.h"

#include <stack>
#include <string>
#include <sys/time.h>
#include <utility>

#include "base/geometry/ng/offset_t.h"
#include "base/i18n/localization.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/components_ng/pattern/refresh/refresh_event_hub.h"
#include "core/components_ng/pattern/refresh/refresh_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/canvas.h"
#include "core/pipeline/base/render_context.h"

namespace OHOS::Ace::NG {

constexpr int32_t BASE_YEAR = 1900;

const char LAST_UPDATE_FORMAT[] = "yyyy/M/d HH:mm"; // Date format for last updated
constexpr float HALF = 0.5;
constexpr float DEFAULT_SHOW_TIME_HEIGHT = 24.0; // Default time show height for time
constexpr float PERCENT = 0.01;                 // Percent

void RefreshPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    animator_ = AceType::MakeRefPtr<Animator>(host->GetContext());
    InitPanEvent(gestureHub);
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    LOGI("zhangjian RefreshPattern 2");
    triggerLoadingDistance_ = NormalizeToPx(layoutProperty->GetLoadingDistanceValue(Dimension(0, DimensionUnit::VP)));
    triggerShowTimeDistance_ = NormalizeToPx(layoutProperty->GetShowTimeDistanceValue(Dimension(0, DimensionUnit::VP)));
    if (layoutProperty->GetIsShowLastTimeValue()) {
        timeDistance_ = NormalizeToPx(Dimension(DEFAULT_SHOW_TIME_HEIGHT, DimensionUnit::VP));
        triggerRefreshDistance_ = triggerShowTimeDistance_;
    } else {
        triggerRefreshDistance_ = NormalizeToPx(layoutProperty->GetRefreshDistanceValue());
        inspectorOffset_ = layoutProperty->GetRefreshDistanceValue();
    }
    loadingDiameter_ = NormalizeToPx(layoutProperty->GetProgressDiameterValue(Dimension(0, DimensionUnit::VP)));
    maxScrollOffset_ = NormalizeToPx(layoutProperty->GetMaxDistanceValue(Dimension(0, DimensionUnit::VP)));
    indicatorOffset_ = NormalizeToPx(layoutProperty->GetIndicatorOffsetValue());
    layoutProperty->UpdateScrollableOffset(OffsetF(0, indicatorOffset_));
    timeOffset_ = layoutProperty->GetShowTimeOffsetValue();
    frictionRatio_ = static_cast<float>(layoutProperty->GetFrictionValue()) * PERCENT;
}

bool RefreshPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool /*skipLayout*/)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pattern = host->GetPattern<RefreshPattern>();
    RefreshStatus nextState = GetNextStatus();

    auto refreshRenderProperty = host->GetPaintProperty<RefreshRenderProperty>();
    CHECK_NULL_RETURN(refreshRenderProperty, false);
    auto refreshLayoutProperty = host->GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_RETURN(refreshLayoutProperty, false);
    if (nextState == RefreshStatus::DONE || nextState == RefreshStatus::INACTIVE) {
        if (progressChild_) {
            progressChild_->SetVisible(false);
        }
        if (textChild_) {
            textChild_->SetVisible(false);
        }
    }
    return true;
}

float RefreshPattern::NormalizeToPx(Dimension value)
{
    float result = 0.0;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, result);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, result);
    result = static_cast<double>(context->NormalizeToPx(value));
    return result;
}

void RefreshPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragStart();
        }
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragUpdate(info.GetMainDelta());
        }
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragEnd();
        }
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragCancel();
        }
    };
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    if (panEvent_) {
        gestureHub->RemovePanEvent(panEvent_);
    }

    float distance = DEFAULT_PAN_DISTANCE;
    auto host = GetHost();
    if (host) {
        auto context = host->GetContext();
        if (context) {
            distance = NormalizeToPx(Dimension(DEFAULT_PAN_DISTANCE, DimensionUnit::VP));
        }
    }
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, distance);
}

void RefreshPattern::HandleDragStart()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto refreshLayoutProperty = host->GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(refreshLayoutProperty);
    auto refreshStatus = refreshLayoutProperty->GetRefreshStatus();
    if (refreshStatus != RefreshStatus::DRAG) {
        refreshLayoutProperty->UpdateRefreshStatus(RefreshStatus::DRAG);
    }
    if (host->TotalChildCount() < 2) {
        LOGI("%{public}s have %{public}d child", host->GetTag().c_str(), host->TotalChildCount());
        return;
    }
    if (progressChild_) {
        progressChild_->SetVisible(true);
    } else {
        progressChild_ = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(host->TotalChildCount() - 1));
        progressChild_->SetVisible(true);
    }
    if (textChild_) {
        textChild_->SetVisible(true);
    } else {
        textChild_ = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(host->TotalChildCount() - 2));
        textChild_->SetVisible(true);
    }
    host->MarkNeedSyncRenderTree();
    host->RebuildRenderContextTree();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void RefreshPattern::HandleDragUpdate(float delta)
{
    if (NearZero(delta)) {
        LOGI("Delta is near zero!");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto refreshLayoutProperty = host->GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(refreshLayoutProperty);
    auto refreshRenderProperty = host->GetPaintProperty<RefreshRenderProperty>();
    CHECK_NULL_VOID(refreshLayoutProperty);
    auto refreshStatus = refreshLayoutProperty->GetRefreshStatus();

    if (refreshStatus == RefreshStatus::REFRESH && delta > 0.0) {
        LOGI("The refresh status is refreshing!");
        return;
    }
    OffsetF deltaOffset(0, delta);
    if (refreshStatus == RefreshStatus::DRAG || refreshStatus == RefreshStatus::OVER_DRAG ||
        refreshStatus == RefreshStatus::DONE) {
        deltaOffset.SetY(GetOffset(delta));
    }
    scrollableOffset_ += deltaOffset;
    scrollableOffset_.SetY(clamp(scrollableOffset_.GetY(), 0.0, maxScrollOffset_));
    refreshLayoutProperty->UpdateScrollableOffset(GetLoadingOffset());
    refreshLayoutProperty->UpdateShowTimeOffset(GetShowTimeOffset());
    auto lastTimeText = refreshRenderProperty->GetLastTimeTextValue();
    auto timeText = StringUtils::FormatString(lastTimeText.c_str(), GetFormatDateTime().c_str());
    refreshRenderProperty->UpdateTimeText(timeText);
    if (host->TotalChildCount() < 2) {
        LOGI("HandleDragUpdate err %{public}s have %{public}d child", host->GetTag().c_str(), host->TotalChildCount());
        return;
    }
    if (textChild_) {
        auto textLayoutProperty = textChild_->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateContent(timeText);
    }

    host->MarkNeedSyncRenderTree();
    host->RebuildRenderContextTree();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void RefreshPattern::HandleDragEnd()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    FireChangeEvent("true");
    FireRefreshing();
    UpdateScrollOffset(0);
    if (host->TotalChildCount() < 2) {
        LOGI("%{public}s have %{public}d child", host->GetTag().c_str(), host->TotalChildCount());
        return;
    }
    host->MarkNeedSyncRenderTree();
    host->RebuildRenderContextTree();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void RefreshPattern::HandleDragCancel()
{
    scrollableOffset_.Reset();
}

void RefreshPattern::FireStateChange(int32_t value)
{
    auto refreshEventHub = GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(refreshEventHub);
    refreshEventHub->FireOnStateChange(value);
}

void RefreshPattern::FireRefreshing()
{
    auto refreshEventHub = GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(refreshEventHub);
    refreshEventHub->FireOnRefreshing();
}

void RefreshPattern::FireChangeEvent(const std::string& value)
{
    auto refreshEventHub = GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(refreshEventHub);
    refreshEventHub->FireChangeEvent(value);
}

void RefreshPattern::UpdateScrollOffset(float value)
{
    scrollableOffset_.SetY(value);
}

RefreshStatus RefreshPattern::GetNextStatus()
{
    RefreshStatus nextStatus;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, RefreshStatus::INACTIVE);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, RefreshStatus::INACTIVE);
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, RefreshStatus::INACTIVE);
    RefreshStatus refreshStatus = layoutProperty->GetRefreshStatusValue();
    switch (refreshStatus) {
        case RefreshStatus::INACTIVE:
            if (layoutProperty->GetIsRefreshingValue()) {
                nextStatus = RefreshStatus::REFRESH;
                break;
            }
            if (LessOrEqual(scrollableOffset_.GetY(), 0.0)) {
                nextStatus = RefreshStatus::INACTIVE;
                if (!progressChild_ || !progressChild_) {
                    break;
                }
                if (progressChild_->GetVisible() || progressChild_->GetVisible()) {
                    progressChild_->SetVisible(false);
                    textChild_->SetVisible(false);
                    host->MarkNeedSyncRenderTree();
                    host->RebuildRenderContextTree();
                    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
                }
                break;
            }
            // No break here, continue next case
            [[fallthrough]];
        case RefreshStatus::DRAG:
            if (LessOrEqual(scrollableOffset_.GetY(), 0.0)) {
                nextStatus = RefreshStatus::INACTIVE;
            } else if (scrollableOffset_.GetY() < triggerRefreshDistance_) {
                nextStatus = RefreshStatus::DRAG;
            } else {
                nextStatus = RefreshStatus::OVER_DRAG;
            }
            break;
        case RefreshStatus::OVER_DRAG:
            if (scrollableOffset_.GetY() > triggerRefreshDistance_) {
                nextStatus = RefreshStatus::OVER_DRAG;
                break;
            }
            // No break here, continue get next status.
            [[fallthrough]];
        case RefreshStatus::REFRESH:
            LOGI("RefreshPattern zhangjian GetNextStatus 11");
            if (!layoutProperty->GetIsRefreshingValue()) {
                LOGI("RefreshPattern zhangjian GetNextStatus 12");
                auto refreshRenderProperty = GetHost()->GetPaintProperty<RefreshRenderProperty>();
                auto timeText = StringUtils::FormatString(
                    refreshRenderProperty->GetLastTimeTextValue().c_str(), GetFormatDateTime().c_str());
                refreshRenderProperty->UpdateTimeText(timeText);
                nextStatus = RefreshStatus::DONE;
                break;
            }
            nextStatus = RefreshStatus::REFRESH;
            break;
        case RefreshStatus::DONE:
            if (scrollableOffset_.GetY() > 0.0) {
                nextStatus = RefreshStatus::DONE;
            } else {
                nextStatus = RefreshStatus::INACTIVE;
            }
            break;
        default:
            nextStatus = RefreshStatus::INACTIVE;
            break;
    }
    if (refreshStatus != nextStatus) {
        FireStateChange(static_cast<int>(nextStatus));
        layoutProperty->UpdateRefreshStatus(nextStatus);
    }
    return nextStatus;
}

float RefreshPattern::GetFriction(float percentage) const
{
    if (NearEqual(percentage, 1.0)) {
        return 0.0;
    }
    return static_cast<float>(frictionRatio_ * std::pow(1.0 - percentage, SQUARE));
}

float RefreshPattern::GetOffset(float delta) const
{
    auto size = GetHost()->GetGeometryNode()->GetFrameSize();

    float height = size.Height();
    if (!NearZero(height)) {
        float friction = GetFriction(std::abs(scrollableOffset_.GetY() / height));
        return friction * delta;
    }
    return delta;
}

float RefreshPattern::MaxScrollableHeight() const
{
    auto size = GetHost()->GetGeometryNode()->GetFrameSize();
    return size.Height();
}

float RefreshPattern::GetLoadingDiameter() const
{
    float diameter = 0.0;
    if (scrollableOffset_.GetY() < triggerLoadingDistance_) {
        return diameter;
    }
    if (scrollableOffset_.GetY() < triggerRefreshDistance_) {
        float maxDistance = triggerRefreshDistance_ - triggerLoadingDistance_;
        float actualDistance = scrollableOffset_.GetY() - triggerLoadingDistance_;
        // Get the diameter by actual distance
        diameter = ((actualDistance * loadingDiameter_ * HALF) / maxDistance) + loadingDiameter_ * HALF;
    } else {
        diameter = loadingDiameter_;
    }
    return diameter;
}

OffsetF RefreshPattern::GetLoadingOffset() const
{
    OffsetF offset;
    offset.Reset();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, offset);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, offset);
    CHECK_NULL_RETURN(scrollableOffset_.GetY() >= triggerLoadingDistance_, offset);
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    if (!layoutProperty->GetIsUseOffsetValue()) {
        return scrollableOffset_ * HALF - OffsetF(0.0, GetLoadingDiameter() * HALF);
    }

    float factor =
        (scrollableOffset_.GetY() - triggerLoadingDistance_) / (triggerRefreshDistance_ - triggerLoadingDistance_);
    return OffsetF(0.0, indicatorOffset_ * factor);
}

OffsetF RefreshPattern::GetShowTimeOffset() const
{
    OffsetF offset;
    offset.Reset();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, offset);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, offset);
    auto size = host->GetGeometryNode()->GetFrameSize();
    float bottomOffset = pipelineContext->NormalizeToPx(Dimension(DEFAULT_SHOW_TIME_HEIGHT, DimensionUnit::VP));
    return scrollableOffset_ - OffsetF(0.0, bottomOffset) ;
}

float RefreshPattern::GetOpacity() const
{
    float factor = 0.0;
    if (scrollableOffset_.GetY() < triggerRefreshDistance_ - timeDistance_) {
        factor = 0.0;
    } else if (scrollableOffset_.GetY() < triggerRefreshDistance_) {
        float actualDistance = scrollableOffset_.GetY() - triggerRefreshDistance_ + timeDistance_;
        // Get the factor, timeDistance_ never be zero
        if (!NearZero(timeDistance_)) {
            factor = actualDistance / timeDistance_;
        }
    } else {
        factor = 1.0;
    }
    return factor;
}

std::string RefreshPattern::GetFormatDateTime()
{
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto local = std::localtime(&now);
    CHECK_NULL_RETURN(local, "");
    // This is for i18n date time
    DateTime dateTime;
    dateTime.year = static_cast<uint32_t>(local->tm_year + BASE_YEAR);
    dateTime.month = static_cast<uint32_t>(local->tm_mon);
    dateTime.day = static_cast<uint32_t>(local->tm_mday);
    dateTime.hour = static_cast<uint32_t>(local->tm_hour);
    dateTime.minute = static_cast<uint32_t>(local->tm_min);
    std::string time = Localization::GetInstance()->FormatDateTime(dateTime, LAST_UPDATE_FORMAT);
    LOGI("Last update refresh time is %{public}s", time.c_str());
    return time;
}

void RefreshPattern::UpdateScrollableOffset(float delta)
{
    LOGI("Update offset is %{public}lf", delta);
    if (NearZero(delta)) {
        LOGE("Delta is near zero!");
        return;
    }
    auto refreshLayoutProperty = GetHost()->GetLayoutProperty<RefreshLayoutProperty>();
    auto refreshStatus = refreshLayoutProperty->GetRefreshStatus();
    if (refreshStatus == RefreshStatus::REFRESH) {
        LOGE("The refresh status is refreshing!");
        return;
    }
    OffsetF offset = OffsetF(0.0, GetOffset(delta));
    scrollableOffset_ = scrollableOffset_ + offset;
    scrollableOffset_.SetY(std::min(scrollableOffset_.GetY(), maxScrollOffset_));
}

void RefreshPattern::OnInActive()
{
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    layoutProperty->UpdateIsRefreshing(false);
    FireChangeEvent("false");
    auto refreshLayoutProperty = GetHost()->GetLayoutProperty<RefreshLayoutProperty>();
    refreshLayoutProperty->UpdateRefreshStatus(RefreshStatus::INACTIVE);
    scrollableOffset_.Reset();
}

} // namespace OHOS::Ace::NG
