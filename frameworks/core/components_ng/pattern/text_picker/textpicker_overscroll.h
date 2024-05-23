/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_OVERSCROLL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_OVERSCROLL_H

#include "core/components_ng/pattern/pattern.h"
#include "core/gestures/velocity_tracker.h"
#include "frameworks/base/memory/ace_type.h"

namespace OHOS::Ace::NG {

class TextPickerOverscroller final {
public:
    TextPickerOverscroller() {}

    bool ApplyCurrentOffset(float yLast, float offsetY, float scrollDelta);

    void SetColumn(const WeakPtr<Pattern>& value)
    {
        column_ = value;
    }

    void SetOverScroll(float overScroll)
    {
        overScroll_ = overScroll;
    }

    float GetOverScroll() const
    {
        return overScroll_;
    }

    float GetBackScroll() const
    {
        return backScrollOffset_;
    }

    void SetStart(float offsetY)
    {
        overScrollStartOffsetY_ = offsetY;
    }

    bool InMaxOverScroll() const;
    bool IsOverScroll() const;
    bool IsBackOverScroll() const;

    void Reset();
    void UpdateTossSpring(float offsetY);
    bool ShouldStartRebound();

    void ResetVelocity()
    {
        velocityTracker_.Reset();
    }

    void SetLoopTossOffset(float offset)
    {
        loopTossOffset_ = offset;
    }

    RefPtr<Curve> GetReboundCurve() const;

private:
    float GetOverScrollOffset(float yLast, float offsetY) const;
    bool CanOverScroll(float scrollDelta) const;

    float height_ = 0.0;
    float overScroll_ = 0.0;
    float backScrollOffset_ = 0.0;
    float deltaScrollOffset_ = 0.0;
    float overScrollStartOffsetY_ = 0.0;
    float loopTossOffset_ = 0.0;
    bool isFirstStart_ = false;

    WeakPtr<Pattern> column_;
    VelocityTracker velocityTracker_;
    ACE_DISALLOW_COPY_AND_MOVE(TextPickerOverscroller);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_OVERSCROLL_H