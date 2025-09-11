/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_FRAME_RATE_RANGE_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_FRAME_RATE_RANGE_H

#include "ui/base/ace_type.h"

namespace OHOS::Ace {
constexpr uint32_t UNKNOWN_FRAME_RATE_TYPE = 0;
// ace scene
constexpr uint32_t REFRESH_DRAG_FRAME_RATE_TYPE = (1 << 0);
constexpr uint32_t SWIPER_DRAG_FRAME_RATE_TYPE = (1 << 1);
constexpr uint32_t SCROLLABLE_DRAG_FRAME_RATE_TYPE = (1 << 2);
constexpr uint32_t SCROLLBAR_DRAG_FRAME_RATE_TYPE = (1 << 3);
constexpr uint32_t SPLIT_DRAG_FRAME_RATE_TYPE = (1 << 4);
constexpr uint32_t PICKER_DRAG_FRAME_RATE_TYPE = (1 << 5);
constexpr uint32_t SCROLLABLE_MULTI_TASK_FRAME_RATE_TYPE = (1 << 6);
constexpr uint32_t ACE_COMPONENT_FRAME_RATE_TYPE = 0b1111111;
// animator
constexpr uint32_t ANIMATION_STATE_FIRST_FRAME = (1 << 12);
constexpr uint32_t RS_ANIMATION_FRAME_RATE_TYPE = (1 << 13);
constexpr uint32_t UI_ANIMATION_FRAME_RATE_TYPE = (1 << 14);
constexpr uint32_t ANIMATION_FRAME_RATE_TYPE = (0b111 << 12);
// developer's voter
constexpr uint32_t DISPLAY_SOLOIST_FRAME_RATE_TYPE = (1 << 20);
constexpr uint32_t NATIVE_VSYNC_FRAME_RATE_TYPE = (1 << 21);
constexpr uint32_t XCOMPONENT_FRAME_RATE_TYPE = (1 << 22);
constexpr uint32_t ANIMATOR_DISPLAY_SYNC_FRAME_RATE_TYPE = (1 << 23);
constexpr uint32_t OTHER_DISPLAY_SYNC_FRAME_RATE_TYPE = (1 << 24);
constexpr uint32_t DISPLAY_SYNC_FRAME_RATE_TYPE = (0b111 << 22);

class FrameRateRange : public AceType {
    DECLARE_ACE_TYPE(FrameRateRange, AceType);
public:
    FrameRateRange() : min_(0), max_(0), preferred_(0), componentScene_(0) {}

    FrameRateRange(int min, int max, int preferred) : min_(min), max_(max), preferred_(preferred) {}

    FrameRateRange(int min, int max, int preferred, int componentScene)
        : min_(min), max_(max), preferred_(preferred), componentScene_(componentScene) {}

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
        this->componentScene_ = 0;
    }

    void Set(int min, int max, int preferred)
    {
        this->min_ = min;
        this->max_ = max;
        this->preferred_ = preferred;
    }

    void Set(int min, int max, int preferred, uint32_t type)
    {
        Set(min, max, preferred);
        this->type_ = type;
    }

    void Merge(const FrameRateRange& other)
    {
        if (this->preferred_ < other.preferred_) {
            this->Set(other.min_, other.max_, other.preferred_);
        }
        if (other.IsValid()) {
            type_ |= other.type_;
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
    int componentScene_ = 0;
    uint32_t type_ = 0;
    const int32_t rangeMaxRefreshrate = 144;
};
    
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_FRAME_RATE_RANGE_H
