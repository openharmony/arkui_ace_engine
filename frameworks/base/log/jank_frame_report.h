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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_JANK_FRAME_REPORT_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_JANK_FRAME_REPORT_H

#include "base/utils/macros.h"

#include <string>
#include <vector>

namespace OHOS::Ace {
using JankFrameFlag = uint32_t;

inline constexpr JankFrameFlag JANK_IDLE = 0;
inline constexpr JankFrameFlag JANK_RUNNING_SCROLL = 1;
inline constexpr JankFrameFlag JANK_RUNNING_ANIMATOR = 1 << 1;
inline constexpr JankFrameFlag JANK_RUNNING_SWIPER = 1 << 2;

class ACE_FORCE_EXPORT JankFrameReport {
public:
    static JankFrameReport& GetInstance();
    JankFrameReport();
    ~JankFrameReport() = default;
    void JankFrameRecord(int64_t timeStampNanos, const std::string& windowName);
    void SetFrameJankFlag(JankFrameFlag flag);
    void ClearFrameJankFlag(JankFrameFlag flag);
    void StartRecord(const std::string& pageUrl);
    void FlushRecord();
    void RecordFrameUpdate();
    void ReportJSAnimation();
    void JsAnimationToRsRecord();
    void RecordAnimateEnd();

private:
    void ClearFrameJankRecord();
    void ResetFrameJankClock();
    void RecordPreviousEnd();
    void RecordJankStatus(double jank);

    std::vector<uint16_t> frameJankRecord_;
    int32_t jankFrameCount_;
    int32_t prevFrameUpdateCount_;
    int32_t currentFrameUpdateCount_;
    JankFrameFlag recordStatus_;
    int64_t startTime_;
    int64_t prevEndTimeStamp_;
    int64_t refreshPeriod_;
    std::string pageUrl_;
    bool needReport_;
    bool hasJsAnimation_;
    int64_t animatorEndTime_;
    double jsAnimationDelayJank_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_JANK_FRAME_REPORT_H
