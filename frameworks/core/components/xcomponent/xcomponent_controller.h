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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_CONTROLLER_H

#include <algorithm>
#include <functional>
#include <list>
#include <string>

#include "base/geometry/size.h"
#include "base/utils/utils.h"
#include "core/pipeline/base/element.h"

namespace OHOS::Ace {
class XComponentController : public virtual AceType {
    DECLARE_ACE_TYPE(XComponentController, AceType);

public:
    using ConfigSurfaceImpl = std::function<void(uint32_t, uint32_t)>;

    std::string GetSurfaceId()
    {
        return surfaceId_;
    }

    void ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight)
    {
        if (ConfigSurfaceImpl_) {
            ConfigSurfaceImpl_(surfaceWidth, surfaceHeight);
        }
    }

    void SetConfigSurfaceImpl(ConfigSurfaceImpl&& ConfigSurfaceImpl)
    {
        ConfigSurfaceImpl_ = std::move(ConfigSurfaceImpl);
    }

    void AddXComponentController(const RefPtr<XComponentController>& xcomponentController)
    {
        auto it = std::find(controllers_.begin(), controllers_.end(), xcomponentController);
        if (it != controllers_.end()) {
            LOGW("Controller is already existed");
            return;
        }
        controllers_.emplace_back(xcomponentController);
    }

    void RemoveXComponentController(const RefPtr<XComponentController>& xcomponentController)
    {
        if (xcomponentController) {
            controllers_.remove(xcomponentController);
        }
    }

    void Clear()
    {
        controllers_.clear();
    }

    std::string surfaceId_ = "";

private:
    std::list<RefPtr<XComponentController>> controllers_;
    ConfigSurfaceImpl ConfigSurfaceImpl_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_CONTROLLER_H