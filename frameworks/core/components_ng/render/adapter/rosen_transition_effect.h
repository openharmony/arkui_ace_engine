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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_TRANSITION_EFFECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_TRANSITION_EFFECT_H

#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components_ng/property/transition_property.h"

namespace OHOS::Ace::NG {
class RosenRenderContext;

// Base class for transition effect, providing basic functions for transition effect.
// Implementations of transition effect should inherit from this class, see rosen_transition_effect_impl.h for details.
class RosenTransitionEffect : public AceType {
public:
    RosenTransitionEffect() = default;
    ~RosenTransitionEffect() override = default;

    void Attach(const RefPtr<RosenRenderContext>& context, bool activeTransition);
    void Detach(RosenRenderContext* context);

    void UpdateTransitionContext(
        const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize);

    void Appear();
    void Disappear(bool activeTransition = true);

    // Chain with another transition effect, the chained effect will be applied after this effect.
    void CombineWith(const RefPtr<RosenTransitionEffect>& effect);
    virtual void SetAnimationOption(const std::shared_ptr<AnimationOption>& option);

    // If disappearing effect is non Identity, return true
    virtual bool HasDisappearTransition() const
    {
        return true;
    }

    static RefPtr<RosenTransitionEffect> ConvertToRosenTransitionEffect(const RefPtr<ChainedTransitionEffect>& effect);
    static bool UpdateRosenTransitionEffect(
        const RefPtr<RosenTransitionEffect>& rosenEffect, const RefPtr<ChainedTransitionEffect>& chainedEffect);

    static RefPtr<RosenTransitionEffect> CreateDefaultRosenTransitionEffect();

protected:
    virtual void OnAttach(const RefPtr<RosenRenderContext>& context, bool activeTransition) {}
    virtual void OnDetach(RosenRenderContext* context) {}
    virtual void OnAppear() {}
    virtual void OnDisappear(bool activeTransition) {}
    virtual void OnUpdateTransitionContext(
        const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize)
    {}

private:
    RefPtr<RosenTransitionEffect> chainedEffect_ = nullptr;
    std::shared_ptr<AnimationOption> animationOption_ = nullptr;

    void ApplyAnimationOption(const std::function<void()>& func, bool withAnimation = true);

    DECLARE_ACE_TYPE(RosenTransitionEffect, AceType);
    ACE_DISALLOW_COPY_AND_MOVE(RosenTransitionEffect);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_TRANSITION_EFFECT_H
