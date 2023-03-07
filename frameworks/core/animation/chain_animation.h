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
class ChainAnimationNode : public AceType {
    DECLARE_ACE_TYPE(ChainAnimationNode, AceType);

public:
    ChainAnimationNode(
        int32_t index, float space, float maxSpace, float minSpace, RefPtr<SpringProperty> springProperty);
    void SetDelta(float delta, float duration);
    float GetDelta() const;
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
    float curPosition_ = 0.0f;
    float curVelocity_ = 0.0f;
};

class ChainAnimation : public AceType {
    DECLARE_ACE_TYPE(ChainAnimation, AceType);

public:
    ChainAnimation(float space, float maxSpace, float minSpace, RefPtr<SpringProperty> springProperty);
    void SetDelta(float delta, bool isOverDrag);
    float GetValue(int32_t index);
    float SetControlIndex(int32_t index);
    void SetMaxIndex(int32_t index)
    {
        maxIndex_ = index;
    }
    void SetAnimationCallback(std::function<void()> callback)
    {
        animationCallback_ = std::move(callback);
    }
    void SetConductionCoefficient(float value)
    {
        conductionCoefficient_ = value;
    }
    void SetLinkageCoefficient(float value)
    {
        linkageCoefficient_ = value;
    }
    void SetSpace(float space, float maxSpace, float minSpace);
    void SetOverDrag(bool isOverDrag);

private:
    void TickAnimation();

    static constexpr float DEFAULT_CONDUCTION = 0.3f;
    static constexpr float DEFAULT_LINKAGE = 0.3f;

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
    float conductionCoefficient_ = DEFAULT_CONDUCTION;
    float linkageCoefficient_ = DEFAULT_LINKAGE;
    bool isOverDrag_ = false;
};
} // namespace OHOS::Ace
#endif