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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_SELECT_MOTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_SELECT_MOTION_H
#include "core/animation/motion.h"

namespace OHOS::Ace {
using CompleteCallbck = std::function<bool()>;
// scroll by offset on each frame before complete
class ACE_EXPORT SelectMotion : public Motion {
    DECLARE_ACE_TYPE(SelectMotion, Motion);

public:
    SelectMotion(float offset, CompleteCallbck&& complete) : offset_(offset), complete_(complete) {};
    double GetCurrentPosition() override
    {
        return offset_;
    };
    double GetCurrentVelocity() override
    {
        return 0.0f;
    };
    bool IsCompleted() override
    {
        if (complete_) {
            return complete_();
        }
        return true;
    };

    std::string GetMotionType() const override
    {
        return "select";
    }

    // Each subclass should override this method to perform motion in each timestamp.
    void Move(float offsetTime) override {};

    void Reset(float offset)
    {
        offset_ = offset;
    }

private:
    float offset_ = 0.0f;
    CompleteCallbck complete_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_SELECT_MOTION_H