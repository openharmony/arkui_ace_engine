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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_COLOR_SAMPLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_COLOR_SAMPLER_H

#include <cstdint>
#include <functional>
#include <memory>

#include "interfaces/inner_api/ace_kit/include/ui/base/macros.h"

namespace OHOS::Ace::NG::ColorSampler {
using ColorSamplerCallback = std::function<void(uint32_t color, int32_t errCode)>;

ACE_FORCE_EXPORT bool RegisterColorSampler(
    const std::string& componentId, uint64_t interval, ColorSamplerCallback callback, uint32_t notifyThreshold);

ACE_FORCE_EXPORT bool UnregisterColorSampler(const std::string& componentId);
} // namespace OHOS::Ace::NG::ColorSampler

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_COLOR_SAMPLER_H
