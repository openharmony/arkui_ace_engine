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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_AXIS_AXIS_ANIMATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_AXIS_AXIS_ANIMATOR_H

#include "base/memory/ace_type.h"
#include "core/components_ng/base/modifier.h"
#include "frameworks/core/components_ng/pattern/scrollable/axis/axis_scroll_motion.h"
#include "frameworks/core/components_ng/render/animation_utils.h"

namespace OHOS::Ace {
class Animator;
}

namespace OHOS::Ace::NG {

using AxisAnimationCallback = std::function<void(float)>;
using AxisAnimationStartCallback = std::function<void(float)>;
using AxisAnimationFinishCallback = std::function<void()>;

class AxisAnimator : public AceType {
    DECLARE_ACE_TYPE(AxisAnimator, AceType);

public:
    AxisAnimator() = default;
    AxisAnimator(AxisAnimationCallback&& axisAnimationCallback, AxisAnimationStartCallback&& axisAnimationStartCallback,
        AxisAnimationFinishCallback&& axisAnimationFinishCallback)
        : axisAnimationCallback_(std::move(axisAnimationCallback)),
          axisAnimationStartCallback_(std::move(axisAnimationStartCallback)),
          axisAnimationFinishCallback_(std::move(axisAnimationFinishCallback))
    {
        CreateAnimator();
    }

    ~AxisAnimator() override = default;

    void Initialize(const WeakPtr<PipelineBase>& context);

    void OnAxis(float mainDelta, float currentPos);

    void CreateAnimator();

    bool IsRunning();

    RefPtr<AxisScrollMotion> GeAxisScrollMotion() const
    {
        return axisScrollMotion_;
    }

    void StopAxisAnimation();

private:
    WeakPtr<PipelineBase> context_;

    AxisAnimationCallback axisAnimationCallback_;
    AxisAnimationStartCallback axisAnimationStartCallback_;
    AxisAnimationFinishCallback axisAnimationFinishCallback_;

    RefPtr<AxisScrollMotion> axisScrollMotion_;
    RefPtr<Animator> axisScrollAnimator_;
    
    ACE_DISALLOW_COPY_AND_MOVE(AxisAnimator);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_AXIS_AXIS_ANIMATOR_H