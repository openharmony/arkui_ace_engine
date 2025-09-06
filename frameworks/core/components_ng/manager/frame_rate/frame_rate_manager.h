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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FRAME_RATE_FRAME_RATE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FRAME_RATE_FRAME_RATE_MANAGER_H

#include <unordered_map>
#include <algorithm>

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "ui/animation/frame_rate_range.h"

namespace OHOS::Ace::NG {
class FrameRateManager : public virtual AceType {
    DECLARE_ACE_TYPE(FrameRateManager, AceType);

public:
    FrameRateManager() = default;
    ~FrameRateManager() override = default;

    bool IsRateChanged();

    void SetIsRateChanged(bool isChanged);

    void AddNodeRate(int32_t nodeId, const std::string& scene, int32_t rate = 0);

    void RemoveNodeRate(int32_t nodeId);

    void UpdateNodeRate(int32_t nodeId, int32_t rate);

    void SetAnimateRate(int32_t rate, bool hasFirstFrameAnimation);

    void SetDisplaySyncRate(int32_t displaySyncRate, uint32_t displaySyncType);

    int32_t GetDisplaySyncRate() const;

    std::pair<int32_t, int32_t> GetExpectedRate();

private:
    std::unordered_map<int32_t, std::pair<std::string, int32_t>> nodeRateMap_;
    bool isRateChanged_ = false;
    int32_t displaySyncRate_ = 0;
    uint32_t displaySyncType_ = UNKNOWN_FRAME_RATE_TYPE;
    int32_t animateRate_ = 0;
    bool hasFirstFrameAnimation_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(FrameRateManager);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FRAME_RATE_FRAME_RATE_MANAGER_H
