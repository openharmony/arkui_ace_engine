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
#include <set>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "base/log/log.h"
#include "base/utils/base_id.h"
#include "base/log/ace_trace.h"
#include "ui/animation/frame_rate_range.h"

namespace OHOS::Ace {
enum class RefreshRateMode : int32_t {
    REFRESHRATE_MODE_AUTO = -1,
};
enum class UIObjectType : int32_t {
    DISPLAYSYNC_OTHERS = -1,
    DISPLAYSYNC_ANIMATOR = 0,
    DISPLAYSYNC_XCOMPONENT = 1,
};
constexpr int32_t INVALID_ANIMATOR_EXPECTED_RATE = -1;

class PipelineBase;

class DisplaySyncData;
using OnFrameCallBack = std::function<void()>;
using OnFrameCallBackWithData = std::function<void(const RefPtr<DisplaySyncData>&)>;
using OnFrameCallBackWithTimestamp = std::function<void(uint64_t)>;

class DisplaySyncData : public AceType {
    DECLARE_ACE_TYPE(DisplaySyncData, AceType)
public:
    void SetTimestamp(int64_t timestamp)
    {
        timestamp_ = timestamp;
    }

    int64_t GetTimestamp() const
    {
        return timestamp_;
    }

    void SetTargetTimestamp(int64_t targetTimestamp)
    {
        targetTimestamp_ = targetTimestamp;
    }

    int64_t GetTargetTimestamp() const
    {
        return targetTimestamp_;
    }

    OnFrameCallBack onFrame_ = nullptr;
    OnFrameCallBackWithData onFrameWithData_ = nullptr;
    OnFrameCallBackWithTimestamp onFrameWithTimestamp_ = nullptr;

    int64_t timestamp_ = 0;
    int64_t targetTimestamp_ = 0;

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
    void JudgeWhetherRequestFrame();

    void RegisterOnFrame(OnFrameCallBack&& onFrameCallBack);
    void RegisterOnFrameWithData(OnFrameCallBackWithData&& onFrameCallBack);
    void RegisterOnFrameWithTimestamp(OnFrameCallBackWithTimestamp&& onFrameCallBack);

    void UnregisterOnFrame();

    void CheckRate(int32_t vsyncRate, int32_t refreshRateMode);
    void UpdateData(int64_t nanoTimestamp, int32_t vsyncPeriod);
    void JudgeWhetherSkip();
    void OnFrame();

    void SetExpectedFrameRateRange(const FrameRateRange& frameRateRange);
    bool SetVsyncRate(int32_t vsyncRate);
    bool IsCommonDivisor(int32_t expectedRate, int32_t vsyncRate);

    void SetTimestampData(int64_t timestamp);
    int64_t GetTimestampData() const;
    void SetTargetTimestampData(int64_t targetTimestamp);
    int64_t GetTargetTimestampData() const;

    RefPtr<DisplaySyncData> GetDisplaySyncData() const;
    int32_t GetAnimatorExpectedRate();

    void SetRefreshRateMode(int32_t refreshRateMode);
    int32_t GetRefreshRateMode() const;
    bool IsAutoRefreshRateMode() const;
    bool IsNonAutoRefreshRateMode() const;

    std::vector<int32_t> FindRefreshRateFactors(int32_t refreshRate);
    int32_t FindMatchedRefreshRate(int32_t vsyncRate, int32_t targetRate);
    int32_t SearchMatchedRate(int32_t vsyncRate, int32_t iterCount = 1);
    RefPtr<PipelineBase> GetCurrentContext();

    UIDisplaySync();
    UIDisplaySync(UIObjectType uiObjectType);
    ~UIDisplaySync() noexcept override;

private:
    UIObjectType uiObjectType_ = UIObjectType::DISPLAYSYNC_OTHERS;
    RefPtr<DisplaySyncData> data_ = AceType::MakeRefPtr<DisplaySyncData>();
    int32_t sourceVsyncRate_ = 0;
    bool rateChanged_ = true;
    int32_t refreshRateMode_ = 0;
    WeakPtr<PipelineBase> context_;
    int32_t drawFPS_ = 0;
    std::unordered_map<int32_t, std::vector<int32_t>> refreshRateToFactorsMap_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_UI_DISPLAY_SYNC_H
