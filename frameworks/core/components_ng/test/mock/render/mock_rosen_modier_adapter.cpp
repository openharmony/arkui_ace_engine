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
#include <mutex>
#include <unordered_map>

#include "base/utils/utils.h"
#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"
#include "core/components_ng/render/modifier_adapter.h"

namespace OHOS::Ace::NG {
std::shared_ptr<RSModifier> ConvertModifier(const RefPtr<Modifier>& modifier)
{
    return nullptr;
}

void ModifierAdapter::RemoveModifier(int32_t modifierId) {}
void ContentModifierAdapter::Draw(RSDrawingContext& context) const {}

inline std::shared_ptr<RSPropertyBase> ConvertToRSProperty(const RefPtr<AnimatablePropertyBase>& property)
{
    return nullptr;
}

void ContentModifierAdapter::AttachProperties() {}
} // namespace OHOS::Ace::NG