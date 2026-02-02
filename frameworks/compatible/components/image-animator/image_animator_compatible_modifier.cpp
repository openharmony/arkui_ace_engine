/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "compatible/components/image-animator/image_animator_compatible_modifier.h"

#include "compatible/components/image-animator/dom_image_animator.h"

namespace OHOS::Ace::ImageAnimatorCompatibleModifier {
namespace {
const char* GetState(OHOS::Ace::Framework::DOMImageAnimator* imageAnimator)
{
    auto domImageAnimator = AceType::Claim(imageAnimator);
    auto state = domImageAnimator->GetState();
    return state;
}
} // namespace
const ArkUIImageAnimatorCompatibleModifier* GetImageAnimatorCompatibleModifier()
{
    static const ArkUIImageAnimatorCompatibleModifier instance = {
        .getState = GetState,
    };
    return &instance;
}
} // namespace OHOS::Ace::ImageAnimatorCompatibleModifier