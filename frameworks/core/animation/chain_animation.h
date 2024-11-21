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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_CHAIN_ANIMATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_CHAIN_ANIMATION_H

#include <functional>
#include <map>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/animation/scheduler.h"
#include "core/animation/spring_motion.h"

namespace OHOS::Ace {
enum class ChainEdgeEffect {
    DEFAULT,
    STRETCH,
};

class ChainAnimationNode : public AceType {
    DECLARE_ACE_TYPE(ChainAnimationNode, AceType);

public:
    ChainAnimationNode(
        int32_t index, float space, float maxSpace, float minSpace, RefPtr<SpringProperty> springProperty);
    void SetDelta(float delta, float spaceDelta, float duration);
    float GetDelta() const;
    float GetDeltaPredict(float delta, float duration);
    bool TickAnimation(float duration);
    void SetIndex(int32_t index)
    {
        index_ = index;
    }
    void SetSpace(float space, float maxSpace, float minSpace)
    {
        space_ = space;
        maxSpace_ = maxSpace;
        minSpace_ = minSpace;
    }

private:
    RefPtr<SpringMotion> spring_;
    RefPtr<SpringProperty> springProperty_;
    int32_t index_;
    float space_;
    float maxSpace_;
    float minSpace_;
    float spaceDelta_ = 0.0f;
    float curPosition_ = 0.0f;
    float curVelocity_ = 0.0f;
};

class ChainAnimation : public AceType {
    DECLARE_ACE_TYPE(ChainAnimation, AceType);

public:
    ChainAnimation(float space, float maxSpace, float minSpace, RefPtr<SpringProperty> springProperty);
    void SetDelta(float delta, float overOffset);
    float GetValue(int32_t index);
    float GetValuePredict(int32_t index, float delta);
    float SetControlIndex(int32_t index);
    int32_t GetControlIndex()
    {
        return controlIndex_;
    }
    void SetMaxIndex(int32_t index)
    {
        maxIndex_ = index;
    }
    void SetAnimationCallback(std::function<void()> callback)
    {
        animationCallback_ = std::move(callback);
    }
    void SetConductivity(float value)
    {
        conductivity_ = value;
    }
    void SetIntensity(float value)
    {
        intensity_ = value;
    }
    void SetEdgeEffectIntensity(float value)
    {
        edgeEffectIntensity_ = value;
    }
    void SetEdgeEffect(ChainEdgeEffect edgeEffect)
    {
        edgeEffect_ = edgeEffect;
    }
    void SetSpace(float space, float maxSpace, float minSpace);
    float GetSpace() const
    {
        return space_;
    }

    static constexpr float DEFAULT_CONDUCTIVITY = 0.7f;
    static constexpr float DEFAULT_INTENSITY = 0.3f;
    static constexpr float DEFAULT_EDGE_EFFECT_INTENSITY = 0.04f;

private:
    void TickAnimation();

    std::function<void()> animationCallback_;
    std::map<int32_t, RefPtr<ChainAnimationNode>> nodes_;
    RefPtr<SpringProperty> springProperty_;
    RefPtr<Scheduler> scheduler_;
    uint64_t timestamp_ = 0;
    float space_;
    float maxSpace_;
    float minSpace_;
    int32_t controlIndex_ = 0;
    int32_t maxIndex_ = 0;
    float conductivity_ = DEFAULT_CONDUCTIVITY;
    float intensity_ = DEFAULT_INTENSITY;
    float edgeEffectIntensity_ = DEFAULT_EDGE_EFFECT_INTENSITY;
    ChainEdgeEffect edgeEffect_ = ChainEdgeEffect::DEFAULT;
};
} // namespace OHOS::Ace
#endif