/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_VEC3_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_VEC3_H

#include "base/geometry/animatable_float.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {

class ACE_EXPORT Vec3 {
public:
    Vec3() = default;
    ~Vec3() = default;
    Vec3(float x, float y, float z, const AnimationOption& option = AnimationOption()) {
        x_ = AnimatableFloat(x, option);
        y_ = AnimatableFloat(y, option);
        z_ = AnimatableFloat(z, option);
        animationOption_ = option;
    }
    Vec3(AnimatableFloat x, AnimatableFloat y, AnimatableFloat z) {
        x_ = x;
        y_ = y;
        z_ = z;
        animationOption_ = x_.GetAnimationOption();
    }

    using RenderNodeAnimationCallback = std::function<void()>;

    void SetContextAndCallbacks(
      const WeakPtr<PipelineBase>& context,
      RenderNodeAnimationCallback&& callback)
    {
        x_.SetContextAndCallback(context, std::forward<RenderNodeAnimationCallback>(callback));
        y_.SetContextAndCallback(context, std::forward<RenderNodeAnimationCallback>(callback));
        z_.SetContextAndCallback(context, std::forward<RenderNodeAnimationCallback>(callback));
    }

    float GetX() const
    {
        return x_.GetValue();
    }

    float GetY() const
    {
        return y_.GetValue();
    }

    float GetZ() const
    {
        return z_.GetValue();
    }

    AnimationOption GetAnimationOption() const
    {
        return animationOption_;
    }

    void SetX(float x)
    {
        x_ = AnimatableFloat(x);
    }

    void SetY(float y)
    {
        y_ = AnimatableFloat(y);
    }

    void SetZ(float z)
    {
        z_ = AnimatableFloat(z);
    }

    bool operator==(const Vec3& vec) const
    {
        return NearEqual(x_.GetValue(), vec.x_.GetValue())
          && NearEqual(y_.GetValue(), vec.y_.GetValue())
          && NearEqual(z_.GetValue(), vec.z_.GetValue());
    }

    bool operator!=(const Vec3& vec) const
    {
        return !operator==(vec);
    }

    Vec3& operator=(const Vec3& newValue)
    {
        animationOption_ = newValue.GetAnimationOption();
        x_ = AnimatableFloat(newValue.GetX(), animationOption_);
        y_ = AnimatableFloat(newValue.GetY(), animationOption_);
        z_ = AnimatableFloat(newValue.GetZ(), animationOption_);
        return *this;
    }

private:
    AnimatableFloat x_;
    AnimatableFloat y_;
    AnimatableFloat z_;
    // Same animation option is applied to x, y, z currently.
    AnimationOption animationOption_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_VEC3_H
