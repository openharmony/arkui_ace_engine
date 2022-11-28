/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "base/geometry/animatable_dimension.h"

namespace OHOS::Ace {
AnimatableDimension& AnimatableDimension::operator=(const Dimension& newDimension)
{
    return *this;
}

AnimatableDimension& AnimatableDimension::operator=(const CalcDimension& newDimension)
{
    return *this;
}

AnimatableDimension& AnimatableDimension::operator=(const AnimatableDimension& newDimension)
{
    return *this;
}

void AnimatableDimension::AnimateTo(double endValue) {}

void AnimatableDimension::ResetController() {}

void AnimatableDimension::OnAnimationCallback(double value) {}

void AnimatableDimension::MoveTo(double target) {}

void AnimatableDimension::ResetAnimatableDimension() {}
} // namespace OHOS::Ace