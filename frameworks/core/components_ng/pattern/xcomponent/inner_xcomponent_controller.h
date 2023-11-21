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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_INNER_XCOMPONENT_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_INNER_XCOMPONENT_CONTROLLER_H

#include <functional>
#include <string>

#include "interfaces/inner_api/xcomponent_controller/xcomponent_controller.h"

namespace OHOS::Ace {
class InnerXComponentController : public OHOS::Ace::XComponentController {
public:
    InnerXComponentController() = default;
    ~InnerXComponentController() override = default;

    using ConfigSurfaceImpl = std::function<void(uint32_t, uint32_t)>;

    std::string GetSurfaceId()
    {
        return surfaceId_;
    }

    void SetSurfaceId(const std::string& surfaceId)
    {
        surfaceId_ = surfaceId;
    }

    void ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight)
    {
        if (configSurfaceImpl_) {
            configSurfaceImpl_(surfaceWidth, surfaceHeight);
        }
    }

    void SetConfigSurfaceImpl(ConfigSurfaceImpl&& ConfigSurfaceImpl)
    {
        configSurfaceImpl_ = std::move(ConfigSurfaceImpl);
    }

private:
    ConfigSurfaceImpl configSurfaceImpl_;
    std::string surfaceId_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_INNER_XCOMPONENT_CONTROLLER_H
