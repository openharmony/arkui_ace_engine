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

#include "core/components_ng/pattern/lazy_grid_layout/bridge/lazy_grid_layout_custom_modifier.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_pattern.h"

namespace OHOS::Ace::NG {
void* GetLazyGridLayoutPattern()
{
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();
    pattern->IncRefCount();
    return AceType::RawPtr(pattern);
}

namespace NodeModifier {
const ArkUILazyGridLayoutCustomModifier* GetLazyGridLayoutCustomModifier()
{
    static const ArkUILazyGridLayoutCustomModifier modifier = {
        .getLazyGridLayoutPattern = GetLazyGridLayoutPattern,
    };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG