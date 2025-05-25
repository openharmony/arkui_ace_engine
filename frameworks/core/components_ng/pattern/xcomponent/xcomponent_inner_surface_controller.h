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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_INNER_SURFACE_CONTROLLER_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_INNER_SURFACE_CONTROLLER_NG_H

#include <string>
#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class XComponentInnerSurfaceController {
public:
    static int32_t SetRenderFitBySurfaceId(
        const std::string& surfaceId, RenderFit renderFit, bool isRenderFitNewVersionEnabled);
    static int32_t GetRenderFitBySurfaceId(
        const std::string& surfaceId, int32_t& renderFitNumber, bool& isRenderFitNewVersionEnabled);
    static void RegisterSurfaceRenderContext(
        const std::string& surfaceId, const WeakPtr<RenderContext>& renderContext);
    static void UnregisterSurfaceRenderContext(const std::string& surfaceId);
private:
    static std::unordered_map<std::string, WeakPtr<RenderContext>> SurfaceRenderContextMap;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_INNER_SURFACE_CONTROLLER_NG_H
