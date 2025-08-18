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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_POSITION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_POSITION_H

#include "base/memory/ace_type.h"
#include "base/geometry/animatable_float.h"

namespace OHOS::Ace::NG {
class ModelPosition : public virtual AceType {
    DECLARE_ACE_TYPE(ModelPosition, AceType);
public:
    ModelPosition() = default;
    ~ModelPosition() override = default;

    ModelPosition(const ModelPosition& src)
    {
        pos_ = Vec3(src.GetX(), src.GetY(), src.GetZ(), src.GetPosition().GetAnimationOption());
        distance_ = src.GetDistance();
        isAngular_ = src.GetIsAngular();
    }

    using RenderNodeAnimationCallback = std::function<void()>;
    void SetContextAndCallbacks(
        const WeakPtr<PipelineBase>& context,
        RenderNodeAnimationCallback&& callback)
    {
        pos_.SetContextAndCallbacks(context, std::forward<RenderNodeAnimationCallback>(callback));
        distance_.SetContextAndCallback(context, std::forward<RenderNodeAnimationCallback>(callback));
    }

    void Set(const Vec3& pos, AnimatableFloat distance, bool isAngular)
    {
        pos_ = pos;
        distance_ = distance;
        isAngular_ = isAngular;
    }

    void SetPosition(const Vec3& pos)
    {
        pos_ = pos;
    }

    void SetDistance(const AnimatableFloat& distance)
    {
        distance_ = distance;
    }

    void SetIsAngular(bool isAngular)
    {
        isAngular_ = isAngular;
    }

    const Vec3& GetPosition() const
    {
        return pos_;
    }

    float GetX() const
    {
        return pos_.GetX();
    }

    float GetY() const
    {
        return pos_.GetY();
    }

    float GetZ() const
    {
        return pos_.GetZ();
    }

    const AnimatableFloat& GetDistance() const
    {
        return distance_;
    }

    bool GetIsAngular() const
    {
        return isAngular_;
    }

private:
    Vec3 pos_ { 0.0f, 0.0f, 4.0f };
    AnimatableFloat distance_ { std::numeric_limits<float>::max() };
    bool isAngular_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_POSITION_H
