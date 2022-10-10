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

#include "frameworks/base/i18n/localization.h"
#include "frameworks/base/utils/time_util.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/core/components/common/layout/constants.h"
#include "frameworks/core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "frameworks/core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t BASE_YEAR = 1900;
const char LAST_UPDATE_FORMAT[] = "yyyy/M/d HH:mm"; // Date format for last updated
constexpr float DIAMETER_HALF = 0.5;
constexpr float DEFAULT_SHOW_TIME_HEIGHT = 300.0;               // Default time show height for time
constexpr float PERCENT = 0.01;                                 // Percent
constexpr char REFRESH_LAST_UPDATED[] = "refresh.last_updated"; // I18n for last updated
constexpr int32_t DEFAULT_INDICATOR_OFFSET = 16.0;
constexpr int32_t CHILD_COUNT = 2;

} // namespace

void RefreshPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitPanEvent(gestureHub);
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetIsShowLastTimeValue()) {
        layoutProperty->UpdateTriggerRefreshDistance(
            layoutProperty->GetShowTimeDistanceValue(Dimension(0, DimensionUnit::VP)));
    } else {
        layoutProperty->UpdateTriggerRefreshDistance(layoutProperty->GetRefreshDistanceValue());
    }
    auto indicatorOffset = layoutProperty->GetIndicatorOffsetValue().ConvertToPx();
    layoutProperty->UpdateScrollableOffset(OffsetF(0, 0));
    layoutProperty->UpdateLoadingProcessOffset(OffsetF(0, static_cast<float>(indicatorOffset)));
    layoutProperty->UpdateShowTimeOffset(OffsetF(0, GetShowTimeOffset().GetY()));
    timeOffset_ = layoutProperty->GetShowTimeOffsetValue();
}

void RefreshPattern::OnAttachToFrameNode()
{
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateIndicatorOffset(Dimension(DEFAULT_INDICATOR_OFFSET, DimensionUnit::VP));
    layoutProperty->UpdateIsUseOffset(true);
    layoutProperty->UpdateIsShowLastTime(true);
    layoutProperty->UpdateScrollableOffset(OffsetF(0.0, 0.0));
    layoutProperty->UpdateShowTimeOffset(OffsetF(0.0, 0.0));
    layoutProperty->UpdateRefreshStatus(RefreshStatus::INACTIVE);
    auto renderProperty = GetPaintProperty<RefreshRenderProperty>();
    CHECK_NULL_VOID(renderProperty);
    auto lastTimeText = Localization::GetInstance()->GetEntryLetters(REFRESH_LAST_UPDATED);
    renderProperty->UpdateLastTimeText(lastTimeText);
    auto timeText = StringUtils::FormatString("");
    renderProperty->UpdateTimeText(timeText);
}

bool RefreshPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& /*dirty*/, bool /*skipMeasure*/, bool /*skipLayout*/)
{
    auto refreshLayoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_RETURN(refreshLayoutProperty, false);

    RefreshStatus nextStatus = GetNextStatus();
    refreshLayoutProperty->UpdateRefreshStatus(nextStatus);
    return false;
}

void RefreshPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& /*info*/) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragStart();
        }
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragUpdate(static_cast<float>(info.GetMainDelta()));
        }
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& /*info*/) {
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

    float distance = static_cast<float>(Dimension(DEFAULT_PAN_DISTANCE, DimensionUnit::VP).ConvertToPx());
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, distance);
}

void RefreshPattern::HandleDragStart()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto refreshLayoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(refreshLayoutProperty);
    auto refreshStatus = refreshLayoutProperty->GetRefreshStatusValue();
    if (refreshStatus != RefreshStatus::DRAG) {
        refreshLayoutProperty->UpdateRefreshStatus(RefreshStatus::DRAG);
        FireStateChange(static_cast<int>(RefreshStatus::DRAG));
    }
    if (host->TotalChildCount() < CHILD_COUNT) {
        LOGI("%{public}s have %{public}d child", host->GetTag().c_str(), host->TotalChildCount());
        return;
    }
    if (!progressChild_) {
        progressChild_ = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(host->TotalChildCount() - 1));
    }
    if (!textChild_) {
        textChild_ = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(host->TotalChildCount() - 2));
    }
    refreshLayoutProperty->UpdateScrollableOffset(OffsetF(0, 0));
    refreshLayoutProperty->UpdateLoadingProcessOffset(OffsetF(0, 0));
    refreshLayoutProperty->UpdateShowTimeOffset(OffsetF(0, 0));
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
    UpdateScrollableOffset(delta);
    refreshLayoutProperty->UpdateLoadingProcessOffset(GetLoadingOffset());
    refreshLayoutProperty->UpdateShowTimeOffset(GetShowTimeOffset());
    auto lastTimeText = refreshRenderProperty->GetLastTimeTextValue();
    auto timeText = StringUtils::FormatString(lastTimeText.c_str(), GetFormatDateTime().c_str());
    refreshRenderProperty->UpdateTimeText(timeText);
    if (host->TotalChildCount() < CHILD_COUNT) {
        return;
    }
    if (!progressChild_ || !textChild_) {
        return;
    }
    auto diameter = static_cast<float>(GetLoadingDiameter());
    auto progressLayoutProperty = progressChild_->GetLayoutProperty<LoadingProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    progressLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(diameter), CalcLength(diameter)));
    auto triggerLoadingDistance =
        refreshLayoutProperty->GetLoadingDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx();
    auto triggerShowTimeDistance =
        refreshLayoutProperty->GetShowTimeDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx();
    auto scrollableOffset = refreshLayoutProperty->GetScrollableOffsetValue();
    auto progressChildLayoutProperty = progressChild_->GetLayoutProperty<LoadingProgressLayoutProperty>();
    auto textChildLayoutProperty = textChild_->GetLayoutProperty<TextLayoutProperty>();
    if (scrollableOffset.GetY() > triggerLoadingDistance &&
        progressChildLayoutProperty->GetVisibilityValue() == VisibleType::INVISIBLE) {
        progressChildLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    }
    if (scrollableOffset.GetY() > triggerShowTimeDistance && refreshLayoutProperty->GetIsShowLastTimeValue() &&
        textChildLayoutProperty->GetVisibilityValue() == VisibleType::INVISIBLE) {
        textChildLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    }

    if (textChild_) {
        auto textLayoutProperty = textChild_->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateContent(timeText);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void RefreshPattern::HandleDragEnd()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto refreshLayoutProperty = host->GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(refreshLayoutProperty);
    auto refreshRenderProperty = host->GetPaintProperty<RefreshRenderProperty>();
    CHECK_NULL_VOID(refreshLayoutProperty);
    auto refreshStatus = refreshLayoutProperty->GetRefreshStatusValue();
    if (refreshStatus != RefreshStatus::DONE && refreshStatus != RefreshStatus::INACTIVE) {
        auto scrollableOffset = refreshLayoutProperty->GetScrollableOffsetValue();
        auto triggerRefreshDistance = refreshLayoutProperty->GetTriggerRefreshDistanceValue();
        if (scrollableOffset.GetY() > triggerRefreshDistance.ConvertToPx()) {
            FireChangeEvent("true");
            FireRefreshing();
            FireStateChange(static_cast<int>(RefreshStatus::REFRESH));
            refreshLayoutProperty->UpdateRefreshStatus(RefreshStatus::REFRESH);
        } else {
            refreshLayoutProperty->UpdateRefreshStatus(RefreshStatus::INACTIVE);
            FireStateChange(static_cast<int>(RefreshStatus::INACTIVE));
        }
    } else {
        FireStateChange(static_cast<int>(refreshStatus));
    }
    if (host->TotalChildCount() < CHILD_COUNT) {
        LOGI("%{public}s have %{public}d child", host->GetTag().c_str(), host->TotalChildCount());
        return;
    }
    auto indicatorOffset = refreshLayoutProperty->GetIndicatorOffsetValue().ConvertToPx();
    auto triggerShowTimeDistance =
        refreshLayoutProperty->GetShowTimeDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx();
    refreshLayoutProperty->UpdateScrollableOffset(OffsetF(0, 0));
    refreshLayoutProperty->UpdateLoadingProcessOffset(OffsetF(0, static_cast<float>(indicatorOffset)));
    refreshLayoutProperty->UpdateShowTimeOffset(OffsetF(0, static_cast<float>(triggerShowTimeDistance)));
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    host->MarkNeedSyncRenderTree();
    host->RebuildRenderContextTree();
}

void RefreshPattern::HandleDragCancel()
{
    auto refreshLayoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(refreshLayoutProperty);
    auto scrollableOffset = refreshLayoutProperty->GetScrollableOffsetValue();
    scrollableOffset.Reset();
    refreshLayoutProperty->UpdateScrollableOffset(scrollableOffset);
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

RefreshStatus RefreshPattern::GetNextStatus()
{
    RefreshStatus nextStatus;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, RefreshStatus::INACTIVE);
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, RefreshStatus::INACTIVE);
    auto renderProperty = GetPaintProperty<RefreshRenderProperty>();
    CHECK_NULL_RETURN(layoutProperty, RefreshStatus::INACTIVE);
    auto triggerRefreshDistance = layoutProperty->GetTriggerRefreshDistanceValue().ConvertToPx();
    RefreshStatus refreshStatus = layoutProperty->GetRefreshStatusValue();
    auto scrollableOffset = layoutProperty->GetScrollableOffsetValue();
    switch (refreshStatus) {
        case RefreshStatus::INACTIVE:
            nextStatus = RefreshStatus::INACTIVE;
            FireStateChange(static_cast<int>(nextStatus));
            if (progressChild_ && textChild_) {
                auto textChildLayoutProperty = textChild_->GetLayoutProperty<TextLayoutProperty>();
                if (textChildLayoutProperty->GetVisibilityValue() == VisibleType::VISIBLE) {
                    textChildLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
                }
                auto progressChildLayoutProperty = progressChild_->GetLayoutProperty<LoadingProgressLayoutProperty>();
                if (progressChildLayoutProperty->GetVisibilityValue() == VisibleType::VISIBLE) {
                    progressChildLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
                    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
                    host->MarkNeedSyncRenderTree();
                    host->RebuildRenderContextTree();
                }
            }
            break;
        case RefreshStatus::DRAG:
            if (LessOrEqual(scrollableOffset.GetY(), 0.0)) {
                nextStatus = RefreshStatus::INACTIVE;
            } else if (scrollableOffset.GetY() < triggerRefreshDistance) {
                nextStatus = RefreshStatus::DRAG;
            } else {
                nextStatus = RefreshStatus::OVER_DRAG;
            }
            break;
        case RefreshStatus::OVER_DRAG:
            if (scrollableOffset.GetY() > triggerRefreshDistance) {
                nextStatus = RefreshStatus::OVER_DRAG;
            } else {
                nextStatus = RefreshStatus::DRAG;
            }
            break;
        case RefreshStatus::REFRESH:
            if (!renderProperty->GetIsRefreshingValue()) {
                auto refreshRenderProperty = GetHost()->GetPaintProperty<RefreshRenderProperty>();
                auto timeText = StringUtils::FormatString(
                    refreshRenderProperty->GetLastTimeTextValue().c_str(), GetFormatDateTime().c_str());
                refreshRenderProperty->UpdateTimeText(timeText);
                nextStatus = RefreshStatus::DONE;
                break;
            }
            nextStatus = RefreshStatus::REFRESH;
            FireStateChange(static_cast<int>(nextStatus));
            break;
        case RefreshStatus::DONE:
        default:
            nextStatus = RefreshStatus::INACTIVE;
            break;
    }
    if (refreshStatus != nextStatus) {
        FireStateChange(static_cast<int>(nextStatus));
        host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    }
    return nextStatus;
}

float RefreshPattern::GetFriction(float percentage) const
{
    if (NearEqual(percentage, 1.0)) {
        return 0.0;
    }
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0);
    auto frictionRatio = static_cast<float>(layoutProperty->GetFrictionValue()) * PERCENT;
    return static_cast<float>(frictionRatio * std::pow(1.0 - percentage, SQUARE));
}

float RefreshPattern::GetOffset(float delta) const
{
    auto size = GetHost()->GetGeometryNode()->GetFrameSize();
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    auto scrollableOffset = layoutProperty->GetScrollableOffsetValue();
    float height = size.Height();
    if (!NearZero(height)) {
        float friction = GetFriction(std::abs(scrollableOffset.GetY() / height));
        return friction * delta;
    }
    return delta;
}

float RefreshPattern::MaxScrollableHeight() const
{
    auto size = GetHost()->GetGeometryNode()->GetFrameSize();
    return size.Height();
}

double RefreshPattern::GetLoadingDiameter() const
{
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    double diameter = 0.0;
    auto triggerLoadingDistance =
        layoutProperty->GetLoadingDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx();
    auto triggerRefreshDistance = layoutProperty->GetTriggerRefreshDistanceValue().ConvertToPx();
    auto loadingDiameter = layoutProperty->GetProgressDiameterValue(Dimension(0, DimensionUnit::VP)).ConvertToPx();
    auto scrollableOffset = layoutProperty->GetScrollableOffsetValue();
    if (scrollableOffset.GetY() < triggerLoadingDistance) {
        return diameter;
    }
    if (scrollableOffset.GetY() < triggerRefreshDistance) {
        double maxDistance = triggerRefreshDistance - triggerLoadingDistance;
        double actualDistance = scrollableOffset.GetY() - triggerLoadingDistance;
        // Get the diameter by actual distance
        diameter = ((actualDistance * loadingDiameter * DIAMETER_HALF) / maxDistance) + loadingDiameter * DIAMETER_HALF;
    } else {
        diameter = loadingDiameter;
    }
    return diameter;
}

void RefreshPattern::UpdateScrollableOffset(float delta)
{
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    auto refreshStatus = layoutProperty->GetRefreshStatusValue();
    if (refreshStatus == RefreshStatus::REFRESH && delta > 0.0) {
        LOGI("The refresh status is refreshing!");
        return;
    }
    OffsetF deltaOffset(0, delta);
    if (refreshStatus == RefreshStatus::DRAG || refreshStatus == RefreshStatus::OVER_DRAG ||
        refreshStatus == RefreshStatus::DONE) {
        deltaOffset.SetY(GetOffset(delta));
    }
    auto scrollableOffset = layoutProperty->GetScrollableOffsetValue();
    auto maxScrollOffset = layoutProperty->GetMaxDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx();
    scrollableOffset += deltaOffset;
    scrollableOffset.SetY(
        std::clamp(scrollableOffset.GetY(), static_cast<float>(0.0), static_cast<float>(maxScrollOffset)));
    layoutProperty->UpdateScrollableOffset(scrollableOffset);
}

OffsetF RefreshPattern::GetLoadingOffset() const
{
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    auto indicatorOffset = layoutProperty->GetIndicatorOffsetValue().ConvertToPx();
    OffsetF offset(0, 0);
    auto triggerLoadingDistance =
        layoutProperty->GetLoadingDistanceValue(Dimension(0, DimensionUnit::VP)).ConvertToPx();
    auto triggerRefreshDistance = layoutProperty->GetTriggerRefreshDistanceValue().ConvertToPx();

    auto scrollableOffset = layoutProperty->GetScrollableOffsetValue();
    if (scrollableOffset.GetY() < triggerLoadingDistance) {
        return offset;
    }
    if (!layoutProperty->GetIsUseOffsetValue()) {
        return scrollableOffset * DIAMETER_HALF -
               OffsetF(0.0, static_cast<float>(GetLoadingDiameter()) * DIAMETER_HALF);
    }
    double factor =
        (scrollableOffset.GetY() - triggerLoadingDistance) / (triggerRefreshDistance - triggerLoadingDistance);
    return OffsetF(0.0, static_cast<float>(indicatorOffset * factor));
}

OffsetF RefreshPattern::GetShowTimeOffset() const
{
    auto loadingOffset = GetLoadingOffset();
    float bottomOffset = static_cast<float>(Dimension(DEFAULT_SHOW_TIME_HEIGHT, DimensionUnit::VP).ConvertToPx());
    return loadingOffset - OffsetF(0.0, bottomOffset);
}

float RefreshPattern::GetOpacity() const
{
    double factor = 0.0;
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, factor);
    auto triggerRefreshDistance = layoutProperty->GetTriggerRefreshDistanceValue().ConvertToPx();
    auto timeDistance = layoutProperty->GetShowTimeDistance()->ConvertToPx();
    auto scrollableOffset = layoutProperty->GetScrollableOffsetValue();
    if (scrollableOffset.GetY() < triggerRefreshDistance - timeDistance) {
        factor = 0.0;
    } else if (scrollableOffset.GetY() < triggerRefreshDistance) {
        double actualDistance = scrollableOffset.GetY() - triggerRefreshDistance + timeDistance;
        // Get the factor, timeDistance_ never be zero
        if (!NearZero(timeDistance)) {
            factor = actualDistance / timeDistance;
        }
    } else {
        factor = 1.0;
    }
    return static_cast<float>(factor);
}

std::string RefreshPattern::GetFormatDateTime()
{
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto* local = std::localtime(&now);
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

void RefreshPattern::OnInActive()
{
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    auto renderProperty = GetPaintProperty<RefreshRenderProperty>();
    renderProperty->UpdateIsRefreshing(false);
    FireChangeEvent("false");
    layoutProperty->UpdateRefreshStatus(RefreshStatus::INACTIVE);

    auto scrollableOffset = layoutProperty->GetScrollableOffsetValue();
    scrollableOffset.Reset();
    layoutProperty->UpdateScrollableOffset(scrollableOffset);
}

} // namespace OHOS::Ace::NG
