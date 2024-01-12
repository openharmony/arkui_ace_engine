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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_UI_DISPLAY_SYNC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_UI_DISPLAY_SYNC_H

#include <unordered_map>
#include <string>
#include <functional>
#include <mutex>
#include <iostream>
#include <atomic>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "base/log/log.h"
#include "base/utils/base_id.h"
#include "base/log/ace_trace.h"

namespace OHOS::Ace {
enum class RefreshRateMode : int32_t {
    REFRESHRATE_MODE_AUTO = -1,
    REFRESHRATE_MODE_NULL = 0,
    REFRESHRATE_MODE_LOW = 1,
    REFRESHRATE_MODE_MEDIUM,
    REFRESHRATE_MODE_HIGH,
};
class PipelineBase;

class FrameRateRange : public AceType {
    DECLARE_ACE_TYPE(FrameRateRange, AceType)
public:
    FrameRateRange() : min_(0), max_(0), preferred_(0) {}

    FrameRateRange(int min, int max, int preferred) : min_(min), max_(max), preferred_(preferred) {}

    bool IsZero() const
    {
        return this->preferred_ == 0;
    }

    bool IsValid() const
    {
        return !this->IsZero() && this->min_ <= this->preferred_ && this->preferred_ <= this->max_ &&
            this->min_ >= 0 && this->max_ <= rangeMaxRefreshrate;
    }

    bool IsDynamic() const
    {
        return IsValid() && this->min_ != this->max_;
    }

    void Reset()
    {
        this->min_ = 0;
        this->max_ = 0;
        this->preferred_ = 0;
    }

    void Set(int min, int max, int preferred)
    {
        this->min_ = min;
        this->max_ = max;
        this->preferred_ = preferred;
    }

    void Merge(const FrameRateRange& other)
    {
        if (this->preferred_ < other.preferred_) {
            this->Set(other.min_, other.max_, other.preferred_);
        }
    }

    bool operator==(const FrameRateRange& other)
    {
        return this->min_ == other.min_ && this->max_ == other.max_ &&
            this->preferred_ == other.preferred_;
    }

    bool operator!=(const FrameRateRange& other)
    {
        return this->min_ != other.min_ || this->max_ != other.max_ ||
            this->preferred_ != other.preferred_;
    }

    int min_ = 0;
    int max_ = 0;
    int preferred_ = 0;
    const int32_t rangeMaxRefreshrate = 144;
};

class DisplaySyncData;
using OnFrameCallBack = std::function<void()>;
using OnFrameCallBackWithData = std::function<void(const RefPtr<DisplaySyncData>&)>;
using OnFrameCallBackWithTimestamp = std::function<void(uint64_t)>;

class DisplaySyncData : public AceType {
    DECLARE_ACE_TYPE(DisplaySyncData, AceType)
public:
    void SetTimestamp(uint64_t timestamp)
    {
        timestamp_ = timestamp;
    }

    uint64_t GetTimestamp() const
    {
        return timestamp_;
    }

    void SetTargetTimestamp(uint64_t targetTimestamp)
    {
        targetTimestamp_ = targetTimestamp;
    }

    uint64_t GetTargetTimestamp() const
    {
        return targetTimestamp_;
    }

    OnFrameCallBack onFrame_ = nullptr;
    OnFrameCallBackWithData onFrameWithData_ = nullptr;
    OnFrameCallBackWithTimestamp onFrameWithTimestamp_ = nullptr;

    uint64_t timestamp_ = 0;
    uint64_t targetTimestamp_ = 0;

    int32_t rate_ = 1;
    bool noSkip_ = true;
    int32_t count_ = 0;
    RefPtr<FrameRateRange> rateRange_ = AceType::MakeRefPtr<FrameRateRange>();
};

class ACE_FORCE_EXPORT UIDisplaySync : public AceType, public BaseId {
    DECLARE_ACE_TYPE(UIDisplaySync, AceType)
public:
    void AddToPipeline(WeakPtr<PipelineBase>& pipelineContext);
    void DelFromPipeline(WeakPtr<PipelineBase>& pipelineContext);
    void AddToPipelineOnContainer();
    void DelFromPipelineOnContainer();
    bool IsAddToPipeline(WeakPtr<PipelineBase>& pipelineContext);
    bool IsOnPipeline();
    void RequestFrame();

    void RegisterOnFrame(OnFrameCallBack&& onFrameCallBack);
    void RegisterOnFrameWithData(OnFrameCallBackWithData&& onFrameCallBack);
    void RegisterOnFrameWithTimestamp(OnFrameCallBackWithTimestamp&& onFrameCallBack);

    void UnRegisterOnFrame();

    void CheckRate(int32_t vsyncRate, int32_t refreshRateMode);
    void UpdateData(uint64_t nanoTimestamp, int32_t vsyncPeriod);
    void JudgeWhetherSkip();
    void OnFrame();

    void SetExpectedFrameRateRange(FrameRateRange&& frameRateRange);
    bool SetVsyncRate(int32_t vsyncRate);
    bool IsCommonDivisor(int32_t expectedRate, int32_t vsyncRate);

    void SetTimestampData(uint64_t timestamp);
    uint64_t GetTimestampData() const;
    void SetTargetTimestampData(uint64_t targetTimestamp);
    uint64_t GetTargetTimestampData() const;

    RefPtr<DisplaySyncData> GetDisplaySyncData() const;

    void SetRefreshRateMode(int32_t refreshRateMode);
    int32_t GetRefreshRateMode() const;
    bool IsAutoRefreshRateMode() const;
    bool IsNonAutoRefreshRateMode() const;

    UIDisplaySync();
    ~UIDisplaySync() noexcept override;

private:
    RefPtr<DisplaySyncData> data_ = AceType::MakeRefPtr<DisplaySyncData>();
    int32_t sourceVsyncRate_ = 0;
    bool rateChanged_ = true;
    int32_t refreshRateMode_ = 0;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_UI_DISPLAY_SYNC_H
