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

namespace OHOS::Ace {
void UIDisplaySync::CheckRate(int32_t vsyncRate, int32_t refreshRateMode)
{
    SetVsyncRate(vsyncRate);
    SetRefreshRateMode(refreshRateMode);

    if (IsCommonDivisor(data_->rateRange_->preferred_, vsyncRate)) {
        int32_t curRate = vsyncRate / data_->rateRange_->preferred_;
        if (data_->rate_ != curRate) {
            data_->rate_ = curRate;
            rateChanged_ = true;
            ACE_SCOPED_TRACE("[%s] Id[%" PRIu64 "] RateChangedTo: %d", __func__, GetId(), data_->rate_);
        }
    }
    return;
}

void UIDisplaySync::UpdateData(uint64_t nanoTimestamp, int32_t vsyncPeriod)
{
    SetTimestampData(nanoTimestamp);
    uint64_t targetTimestamp = nanoTimestamp + vsyncPeriod * data_->rate_;
    SetTargetTimestampData(targetTimestamp);
}

void UIDisplaySync::JudgeWhetherSkip()
{
    if (rateChanged_) {
        data_->count_ = 0;
        rateChanged_ = false;
    }

    data_->count_++;
    if (data_->count_ % data_->rate_ == 0) {
        data_->noSkip_ = true;
        data_->count_ = 0;
    } else {
        data_->noSkip_ = false;
    }
}

void UIDisplaySync::OnFrame()
{
    ACE_SCOPED_TRACE("DisplaySyncId[%" PRIu64 "] Timestamp[%" PRIu64 "] TargetTimestamp[%" PRIu64 "]"
                     "Preferred[%d] VSyncRate[%d] Rate[%d] noSkip[%d]",
                     GetId(), data_->timestamp_, data_->targetTimestamp_,
                     data_->rateRange_->preferred_, sourceVsyncRate_, data_->rate_, data_->noSkip_);
    if (IsEnabled() && data_->noSkip_ && data_->onFrame_) {
        data_->onFrame_();
    }

    if (IsEnabled() && data_->noSkip_ && data_->onFrameWithData_) {
        data_->onFrameWithData_(data_);
    }

    if (IsEnabled() && data_->noSkip_ && data_->onFrameWithTimestamp_) {
        data_->onFrameWithTimestamp_(data_->timestamp_);
    }

    RequestFrame();
}

void UIDisplaySync::AddToPipeline(WeakPtr<PipelineBase>& pipelineContext)
{
    auto context = pipelineContext.Upgrade();
    if (!context) {
        return;
    }

    RefPtr<UIDisplaySyncManager> dsm = context->GetOrCreateUIDisplaySyncManager();
    if (!dsm) {
        return;
    }
    dsm->AddDisplaySync(AceType::Claim(this));
}

void UIDisplaySync::DelFromPipeline(WeakPtr<PipelineBase>& pipelineContext)
{
    auto context = pipelineContext.Upgrade();
    if (!context) {
        return;
    }

    RefPtr<UIDisplaySyncManager> dsm = context->GetOrCreateUIDisplaySyncManager();
    if (!dsm) {
        return;
    }
    dsm->RemoveDisplaySync(AceType::Claim(this));
}

bool UIDisplaySync::IsAddToPipeline(WeakPtr<PipelineBase>& pipelineContext)
{
    auto context = pipelineContext.Upgrade();
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
    WeakPtr<PipelineBase> pipeline = PipelineBase::GetCurrentContext();
    auto context = pipeline.Upgrade();
    if (!context) {
        return;
    }
    context->RequestFrame();
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

void UIDisplaySync::UnRegisterOnFrame()
{
    data_->onFrame_ = nullptr;
    data_->onFrameWithData_ = nullptr;
    data_->onFrameWithTimestamp_ = nullptr;
}

void UIDisplaySync::SetTimestampData(uint64_t timestamp)
{
    data_->SetTimestamp(timestamp);
}

uint64_t UIDisplaySync::GetTimestampData() const
{
    return data_->GetTimestamp();
}

void UIDisplaySync::SetTargetTimestampData(uint64_t targetTimestamp)
{
    data_->SetTargetTimestamp(targetTimestamp);
}

uint64_t UIDisplaySync::GetTargetTimestampData() const
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

bool UIDisplaySync::IsEnabled() const
{
    return refreshRateMode_ == static_cast<int32_t>(RefreshRateMode::REFRESHRATE_MODE_AUTO);
}

bool UIDisplaySync::IsDisabled() const
{
    return refreshRateMode_ != static_cast<int32_t>(RefreshRateMode::REFRESHRATE_MODE_AUTO);
}

UIDisplaySync::UIDisplaySync() {}

UIDisplaySync::~UIDisplaySync() noexcept {}

void UIDisplaySync::SetExpectedFrameRateRange(FrameRateRange&& range)
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

bool UIDisplaySync::IsCommonDivisor(int32_t expectedRate, int32_t vsyncRate)
{
    if (expectedRate == 0) {
        return false;
    }

    int32_t n = vsyncRate / expectedRate;
    if (vsyncRate % n == 0) {
        return true;
    }
    return false;
}
} // namespace OHOS::Ace
