/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/union_effect_container/union_effect_container_pattern.h"

namespace OHOS::Ace::NG {
void UnionEffectContainerPattern::SetSpacing(const float& spacing)
{
    constexpr float MIN_SPACING = 0.0f;
    if (std::isnan(spacing) || LessOrEqual(spacing, MIN_SPACING)) {
        spacing_ = MIN_SPACING;
    } else {
        spacing_ = spacing;
    }
}
} // namespace OHOS::Ace::NG
