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

class FrameRateRange : public AceType {
    DECLARE_ACE_TYPE(FrameRateRange, AceType)
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
    int componentScene_ = 0;
    const int32_t rangeMaxRefreshrate = 144;
};
    
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_FRAME_RATE_RANGE_H
