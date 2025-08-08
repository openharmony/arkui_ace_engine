/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/pipeline/pipeline_base.h"
#include "core/components_ng/manager/display_sync/ui_display_sync.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "transaction/rs_interfaces.h"
#endif

namespace OHOS::Ace {
void UIDisplaySync::CheckRate(int32_t vsyncRate, int32_t refreshRateMode)
{
    SetVsyncRate(vsyncRate);
    SetRefreshRateMode(refreshRateMode);

    CHECK_NULL_VOID(data_);
    CHECK_NULL_VOID(data_->rate_);
    CHECK_NULL_VOID(data_->rateRange_);
    drawFPS_ = FindMatchedRefreshRate(vsyncRate, data_->rateRange_->preferred_);
    if (drawFPS_ < data_->rateRange_->min_ ||
        drawFPS_ > data_->rateRange_->max_) {
        drawFPS_ = SearchMatchedRate(vsyncRate);
    }

    if (drawFPS_ == 0) {
        return;
    }

    int32_t curRate = vsyncRate / drawFPS_;
    if (data_->rate_ != curRate) {
        data_->rate_ = curRate;
        rateChanged_ = true;
        ACE_SCOPED_TRACE("[%s] Id[%" PRIu64 "] RateChangedTo: %d", __func__, GetId(), data_->rate_);
    }
    return;
}

void UIDisplaySync::UpdateData(int64_t nanoTimestamp, int32_t vsyncPeriod)
{
    SetTimestampData(nanoTimestamp);
    int64_t targetTimestamp = nanoTimestamp + static_cast<int64_t>(vsyncPeriod * data_->rate_);
    SetTargetTimestampData(targetTimestamp);
}

void UIDisplaySync::JudgeWhetherSkip()
{
    if (rateChanged_) {
        data_->count_ = 0;
        rateChanged_ = false;
    }

    if (data_->count_ == 0) {
        data_->noSkip_ = true;
    } else {
        data_->noSkip_ = false;
    }

    if (data_->rate_ && (data_->rate_ - data_->count_) == 1) {
        data_->count_ = -1;
    }
    data_->count_++;
}

void UIDisplaySync::OnFrame()
{
    ACE_SCOPED_TRACE("DisplaySyncId[%" PRIu64 "] Type[%d] Timestamp[%" PRIu64 "] TargetTimestamp[%" PRIu64 "]"
                     "FrameRateRange[%d, %d, %d] DrawFPS[%d] VSyncRate[%d] Rate[%d] noSkip[%d]",
                     GetId(), static_cast<int32_t>(uiObjectType_), data_->timestamp_, data_->targetTimestamp_,
                     data_->rateRange_->min_, data_->rateRange_->max_, data_->rateRange_->preferred_,
                     drawFPS_, sourceVsyncRate_, data_->rate_, data_->noSkip_);
    TAG_LOGD(AceLogTag::ACE_DISPLAY_SYNC, "Id[%{public}" PRIu64 "] Type[%{public}d] FrameRateRange[%{public}d, "
        "%{public}d, %{public}d], DrawFPS[%{public}d] VSyncRate[%{public}d] Rate[%{public}d] noSkip[%{public}d]",
        GetId(), static_cast<int32_t>(uiObjectType_), data_->rateRange_->min_, data_->rateRange_->max_,
        data_->rateRange_->preferred_, drawFPS_, sourceVsyncRate_, data_->rate_, data_->noSkip_);
    if (data_->noSkip_ && data_->onFrame_) {
        data_->onFrame_();
    }

    // Callback from JS_DisplaySync and Native_XComponent
    if (data_->noSkip_ && data_->onFrameWithData_) {
        data_->onFrameWithData_(data_);
    }

    // Callback from Animator
    if (data_->noSkip_ && data_->onFrameWithTimestamp_) {
        data_->onFrameWithTimestamp_(data_->timestamp_);
    }

    JudgeWhetherRequestFrame();
}

void UIDisplaySync::AddToPipeline(WeakPtr<PipelineBase>& pipelineContext)
{
    if (GetCurrentContext()) {
        TAG_LOGD(AceLogTag::ACE_DISPLAY_SYNC, "[DisplaySync] existed in Pipeline.");
        return;
    }

    auto context = pipelineContext.Upgrade();
    if (!context) {
        context = PipelineBase::GetCurrentContextSafelyWithCheck();
        if (!context) {
            TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[DisplaySync] AddToPipeline CurrentContext is nullptr.");
            return;
        }
        TAG_LOGD(AceLogTag::ACE_DISPLAY_SYNC, "[DisplaySync] Add to current context safely.");
    }

    context_ = context;
    RefPtr<UIDisplaySyncManager> dsm = context->GetOrCreateUIDisplaySyncManager();
    if (!dsm) {
        return;
    }
    dsm->AddDisplaySync(AceType::Claim(this));
}

void UIDisplaySync::DelFromPipeline(WeakPtr<PipelineBase>& pipelineContext)
{
    auto context = GetCurrentContext();
    if (!context) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[DisplaySync] DelFromPipeline CurrentContext is nullptr.");
        return;
    }

    RefPtr<UIDisplaySyncManager> dsm = context->GetOrCreateUIDisplaySyncManager();
    if (!dsm) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[DisplaySync] DSM is nullptr.");
        return;
    }
    dsm->RemoveDisplaySync(AceType::Claim(this));
    context_ = nullptr;
}

bool UIDisplaySync::IsAddToPipeline(WeakPtr<PipelineBase>& pipelineContext)
{
    auto context = GetCurrentContext();
    if (!context) {
        return false;
    }

    RefPtr<UIDisplaySyncManager> dsm = context->GetOrCreateUIDisplaySyncManager();
    if (!dsm) {
        return false;
    }
    return dsm->HasDisplaySync(AceType::Claim(this));
}

void UIDisplaySync::AddToPipelineOnContainer()
{
    WeakPtr<PipelineBase> pipeline = PipelineBase::GetCurrentContext();
    AddToPipeline(pipeline);
    return;
}

void UIDisplaySync::DelFromPipelineOnContainer()
{
    WeakPtr<PipelineBase> pipeline = PipelineBase::GetCurrentContext();
    DelFromPipeline(pipeline);
    return;
}

bool UIDisplaySync::IsOnPipeline()
{
    WeakPtr<PipelineBase> pipeline = PipelineBase::GetCurrentContext();
    return IsAddToPipeline(pipeline);
}

void UIDisplaySync::RequestFrame()
{
    auto context = GetCurrentContext();
    if (!context) {
        return;
    }
    context->RequestFrame();
}

void UIDisplaySync::JudgeWhetherRequestFrame()
{
    bool isNeedRequest = data_->onFrame_ || data_->onFrameWithData_ || data_->onFrameWithTimestamp_;
    if (isNeedRequest) {
        RequestFrame();
    }
}

void UIDisplaySync::RegisterOnFrame(OnFrameCallBack&& onFrameCallBack)
{
    data_->onFrame_ = std::move(onFrameCallBack);
}

void UIDisplaySync::RegisterOnFrameWithData(OnFrameCallBackWithData&& onFrameCallBack)
{
    data_->onFrameWithData_ = std::move(onFrameCallBack);
}

void UIDisplaySync::RegisterOnFrameWithTimestamp(OnFrameCallBackWithTimestamp&& onFrameCallBack)
{
    data_->onFrameWithTimestamp_ = std::move(onFrameCallBack);
}

void UIDisplaySync::UnregisterOnFrame()
{
    data_->onFrame_ = nullptr;
    data_->onFrameWithData_ = nullptr;
    data_->onFrameWithTimestamp_ = nullptr;
}

void UIDisplaySync::SetTimestampData(int64_t timestamp)
{
    data_->SetTimestamp(timestamp);
}

int64_t UIDisplaySync::GetTimestampData() const
{
    return data_->GetTimestamp();
}

void UIDisplaySync::SetTargetTimestampData(int64_t targetTimestamp)
{
    data_->SetTargetTimestamp(targetTimestamp);
}

int64_t UIDisplaySync::GetTargetTimestampData() const
{
    return data_->GetTargetTimestamp();
}

void UIDisplaySync::SetRefreshRateMode(int32_t refreshRateMode)
{
    refreshRateMode_ = refreshRateMode;
}

int32_t UIDisplaySync::GetRefreshRateMode() const
{
    return refreshRateMode_;
}

bool UIDisplaySync::IsAutoRefreshRateMode() const
{
    return refreshRateMode_ == static_cast<int32_t>(RefreshRateMode::REFRESHRATE_MODE_AUTO);
}

bool UIDisplaySync::IsNonAutoRefreshRateMode() const
{
    return refreshRateMode_ != static_cast<int32_t>(RefreshRateMode::REFRESHRATE_MODE_AUTO);
}

std::vector<int32_t> UIDisplaySync::FindRefreshRateFactors(int32_t refreshRate)
{
    std::vector<int32_t> refreshRateFactors;
    for (int32_t i = 1; i * i <= refreshRate; ++i) {
        if (refreshRate % i == 0) {
            refreshRateFactors.emplace_back(i);
            if (i != refreshRate / i) {
                refreshRateFactors.emplace_back(refreshRate / i);
            }
        }
    }
    sort(refreshRateFactors.begin(), refreshRateFactors.end());
    return refreshRateFactors;
}

int32_t UIDisplaySync::FindMatchedRefreshRate(int32_t vsyncRate, int32_t targetRate)
{
    if (targetRate == 0 || targetRate > vsyncRate) {
        return vsyncRate;
    }

    if (IsCommonDivisor(targetRate, vsyncRate)) {
        return targetRate;
    }

    if (!refreshRateToFactorsMap_.count(vsyncRate)) {
        refreshRateToFactorsMap_[vsyncRate] = FindRefreshRateFactors(vsyncRate);
    }

    std::vector<int32_t> refreshRateFactors = refreshRateToFactorsMap_[vsyncRate];
    if (refreshRateFactors.empty()) {
        return 0;
    }
    auto it = std::lower_bound(refreshRateFactors.begin(), refreshRateFactors.end(), targetRate);
    if (it == refreshRateFactors.begin()) {
        return *it;
    } else if (it == refreshRateFactors.end()) {
        return *(it - 1);
    }
    return std::abs(*it - targetRate) < std::abs(*(it - 1) - targetRate) ? *it : *(it - 1);
}

int32_t UIDisplaySync::SearchMatchedRate(int32_t vsyncRate, int32_t iterCount)
{
    if (vsyncRate != 0 && iterCount >= vsyncRate) {
        return FindMatchedRefreshRate(vsyncRate, data_->rateRange_->preferred_);
    }

    if (iterCount == 0 || vsyncRate == 0) {
        return vsyncRate;
    }

    int32_t expectedRate = vsyncRate / iterCount;
    if (data_->rateRange_->min_ <= expectedRate &&
        data_->rateRange_->max_ >= expectedRate) {
        return FindMatchedRefreshRate(vsyncRate, expectedRate);
    }

    return SearchMatchedRate(vsyncRate, ++iterCount);
}

RefPtr<PipelineBase> UIDisplaySync::GetCurrentContext()
{
    auto context = context_.Upgrade();
    return context;
}

UIDisplaySync::UIDisplaySync(UIObjectType uiObjectType)
    : uiObjectType_(uiObjectType)
{
    TAG_LOGD(AceLogTag::ACE_DISPLAY_SYNC, "Create UIDisplaySync, Type: %{public}d",
        static_cast<int32_t>(uiObjectType_));
}

UIDisplaySync::UIDisplaySync() {}

UIDisplaySync::~UIDisplaySync() noexcept {}

void UIDisplaySync::SetExpectedFrameRateRange(const FrameRateRange& range)
{
    data_->rateRange_->Set(range.min_, range.max_, range.preferred_);
}

bool UIDisplaySync::SetVsyncRate(int32_t vsyncRate)
{
    if (sourceVsyncRate_ == vsyncRate) {
        return false;
    }
    sourceVsyncRate_ = vsyncRate;
    return true;
}

RefPtr<DisplaySyncData> UIDisplaySync::GetDisplaySyncData() const
{
    return data_;
}

int32_t UIDisplaySync::GetAnimatorExpectedRate()
{
    // Callback from Animator
    if (data_ && data_->onFrameWithTimestamp_ == nullptr &&
        uiObjectType_ != UIObjectType::DISPLAYSYNC_ANIMATOR) {
        return INVALID_ANIMATOR_EXPECTED_RATE;
    }

    int32_t animatorExpectedRate = 0;
    if (data_ && data_->rateRange_) {
        animatorExpectedRate = data_->rateRange_->preferred_;
    }
    return animatorExpectedRate;
}

bool UIDisplaySync::IsCommonDivisor(int32_t expectedRate, int32_t vsyncRate)
{
    if (expectedRate == 0 || vsyncRate == 0) {
        return false;
    }

    int32_t n = vsyncRate / expectedRate;
    if (expectedRate * n == vsyncRate) {
        return true;
    }
    return false;
}

UIXComponentDisplaySync::~UIXComponentDisplaySync()
{
    if (lastFrameRateRange_.has_value()) {
        // -1 : means destroy
        NotifyXComponentExpectedFrameRate(lastId_, -1);
    }
}

void UIXComponentDisplaySync::NotifyXComponentExpectedFrameRate(const std::string& id)
{
    if (lastFrameRateRange_.has_value()) {
        NotifyXComponentExpectedFrameRate(id, lastFrameRateRange_->preferred_);
    }
}

void UIXComponentDisplaySync::NotifyXComponentExpectedFrameRate(const std::string& id, int32_t preferred)
{
    lastId_ = id;
    if (lastFrameRateRange_.has_value()) {
#ifdef ENABLE_ROSEN_BACKEND
        Rosen::RSInterfaces::GetInstance().NotifyXComponentExpectedFrameRate(lastId_, preferred);
#endif
    }
}

void UIXComponentDisplaySync::NotifyXComponentExpectedFrameRate(
    const std::string& id, bool isOnTree, const FrameRateRange& expectedFrameRate)
{
    SetExpectedFrameRateRange(expectedFrameRate);
    TAG_LOGD(AceLogTag::ACE_DISPLAY_SYNC, "Id: %{public}" PRIu64 " SetExpectedFrameRateRange"
        "{%{public}d, %{public}d, %{public}d}", GetId(),
        expectedFrameRate.min_, expectedFrameRate.max_, expectedFrameRate.preferred_);
    if (expectedFrameRate.preferred_ < 0 ||
        (lastFrameRateRange_.has_value() && lastFrameRateRange_->preferred_ == expectedFrameRate.preferred_)) {
        return;
    }
    lastFrameRateRange_.emplace(expectedFrameRate.min_, expectedFrameRate.max_, expectedFrameRate.preferred_);
    if (isOnTree) {
        NotifyXComponentExpectedFrameRate(id);
    }
}

} // namespace OHOS::Ace
