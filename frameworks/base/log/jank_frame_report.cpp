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

#include "base/log/event_report.h"
#include "base/log/jank_frame_report.h"

#include <algorithm>
#include <chrono>
#include <string>

namespace OHOS::Ace {
enum {
    JANK_FRAME_6_FREQ = 0,
    JANK_FRAME_15_FREQ,
    JANK_FRAME_20_FREQ,
    JANK_FRAME_36_FREQ,
    JANK_FRAME_48_FREQ,
    JANK_FRAME_60_FREQ,
    JANK_FRAME_120_FREQ,
    JANK_FRAME_180_FREQ,
    JANK_SIZE,
};

std::vector<uint16_t> JankFrameReport::frameJankRecord_(JANK_SIZE, 0);
JankFrameFlag JankFrameReport::recordStatus_ = JANK_IDLE;
int64_t JankFrameReport::startTime_ = 0;
std::string JankFrameReport::pageUrl_;
bool JankFrameReport::needReport_ = false;

void JankFrameReport::JankFrameRecord(double jank)
{
    if (!recordStatus_) {
        return;
    }
    needReport_ = true;
    if (jank < 6.0f) {
        frameJankRecord_[JANK_FRAME_6_FREQ]++;
    } else if (jank < 15.0f) {
        frameJankRecord_[JANK_FRAME_15_FREQ]++;
    } else if (jank < 20.0f) {
        frameJankRecord_[JANK_FRAME_20_FREQ]++;
    } else if (jank < 36.0f) {
        frameJankRecord_[JANK_FRAME_36_FREQ]++;
    } else if (jank < 48.0f) {
        frameJankRecord_[JANK_FRAME_48_FREQ]++;
    } else if (jank < 60.0f) {
        frameJankRecord_[JANK_FRAME_60_FREQ]++;
    } else if (jank < 120.0f) {
        frameJankRecord_[JANK_FRAME_120_FREQ]++;
    } else {
        frameJankRecord_[JANK_FRAME_180_FREQ]++;
    }
}

void JankFrameReport::ClearFrameJankRecord()
{
    std::fill(frameJankRecord_.begin(), frameJankRecord_.end(), 0);
    recordStatus_ = JANK_IDLE;
}

void JankFrameReport::SetFrameJankFlag(JankFrameFlag flag)
{
    recordStatus_ |= flag;
}

void JankFrameReport::ClearFrameJankFlag(JankFrameFlag flag)
{
    recordStatus_ &= (~flag);
}

void JankFrameReport::StartRecord(const std::string& pageUrl)
{
    startTime_ =
        std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch())
            .count();
    pageUrl_ = pageUrl;
}

int64_t JankFrameReport::GetDuration()
{
    auto now = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch())
                   .count();
    return now - startTime_;
}

void JankFrameReport::FlushRecord()
{
    if (!needReport_) {
        ClearFrameJankRecord();
        return;
    }
    EventReport::JankFrameReport(startTime_, GetDuration(), frameJankRecord_, pageUrl_);
    ClearFrameJankRecord();
}

} // namespace OHOS::Ace
