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

#include "test/mock/core/animation/mock_implicit_animation.h"

#include "test/mock/core/animation/mock_animation_proxy.h"

#include "core/components_ng/base/modifier.h"

namespace OHOS::Ace {
void MockImplicitAnimation::UpdateProp(const WeakPtr<NG::PropertyBase>& propWk) const
{
#ifdef ENHANCED_ANIMATION
    if (auto prop = AceType::DynamicCast<NG::AnimatablePropertyFloat>(propWk.Upgrade()); prop) {
        NG::MockAnimationProxy<float>::GetInstance().Next(prop, remainingTicks_);
        auto cb = prop->GetUpdateCallback();
        if (cb) {
            cb(NG::MockAnimationProxy<float>::GetInstance().GetValue(prop));
        }
    }
    if (auto prop = AceType::DynamicCast<NG::AnimatablePropertyOffsetF>(propWk.Upgrade()); prop) {
        NG::MockAnimationProxy<NG::OffsetF>::GetInstance().Next(prop, remainingTicks_);
        auto cb = prop->GetUpdateCallback();
        if (cb) {
            cb(NG::MockAnimationProxy<NG::OffsetF>::GetInstance().GetValue(prop));
        }
    }
    /* add update code for other types */
#endif
}

void MockImplicitAnimation::Next()
{
    if (paused_ || Finished()) {
        return;
    }
    UpdateProp(prop_);
    if (cbs_.repeatCb) {
        cbs_.repeatCb();
    }
    if (--remainingTicks_ <= 0) {
        if (cbs_.finishCb) {
            cbs_.finishCb();
        }
    }
}

template<typename T>
void MockImplicitAnimation::ForceUpdate(const T& delta)
{
    auto prop = AceType::DynamicCast<NG::AnimatableProperty<T>>(prop_.Upgrade());
    CHECK_NULL_VOID(prop);
    NG::MockAnimationProxy<T>::GetInstance().ForceUpdate(prop, delta);
    auto cb = prop->GetUpdateCallback();
    if (cb) {
        cb(NG::MockAnimationProxy<T>::GetInstance().GetValue(prop));
    }
}
template void MockImplicitAnimation::ForceUpdate(const float& delta);
template void MockImplicitAnimation::ForceUpdate(const NG::OffsetF& delta);

void MockImplicitAnimation::End()
{
    remainingTicks_ = 0;
    if (cbs_.finishCb) {
        cbs_.finishCb();
    }
}

void MockImplicitAnimation::JumpToEnd()
{
    if (Finished()) {
        return;
    }
    remainingTicks_ = 1;
}
} // namespace OHOS::Ace