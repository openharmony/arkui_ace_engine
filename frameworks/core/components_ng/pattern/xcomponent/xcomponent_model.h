/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_XCOMPONENT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_XCOMPONENT_MODEL_H

#include <mutex>
#include <optional>

#include "base/memory/ace_type.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/xcomponent/inner_xcomponent_controller.h"

namespace OHOS::Ace {
using LoadEvent = std::function<void(const std::string&)>;
using DestroyEvent = std::function<void(const std::string&)>;
using DetachCallback = std::function<void(const std::string&)>;
using SurfaceCreatedEvent = std::function<void(const std::string&, const std::string&)>;
using SurfaceChangedEvent = std::function<void(const std::string&, const NG::RectF&)>;
using SurfaceDestroyedEvent = std::function<void(const std::string&, const std::string&)>;

class XComponentModel {
public:
    static XComponentModel* GetInstance();
    static bool IsBackGroundColorAvailable(const XComponentType& type)
    {
        return type == XComponentType::TEXTURE || type == XComponentType::NODE ||
               (type == XComponentType::SURFACE && Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN));
    }
    static bool IsCommonEventAvailable(const XComponentType& type, std::optional<std::string>& libraryName)
    {
        return type == XComponentType::NODE ||
               (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE) && !libraryName.has_value());
    }
    virtual ~XComponentModel() = default;

    virtual void Create(const std::optional<std::string>& id, XComponentType type,
        const std::optional<std::string>& libraryname,
        const std::shared_ptr<InnerXComponentController>& xcomponentController) = 0;
    virtual RefPtr<AceType> Create(int32_t /* nodeId */, float /* width */, float /* height */,
        const std::string& /* id */, XComponentType /* type */, const std::string& /* libraryname */,
        const std::shared_ptr<InnerXComponentController>& /* xcomponentController */)
    {
        return nullptr;
    };
    virtual void SetSoPath(const std::string& soPath) = 0;
    virtual void SetOnLoad(LoadEvent&& onLoad) = 0;
    virtual void SetOnDestroy(DestroyEvent&& onDestroy) = 0;
    virtual void RegisterOnCreate(const RefPtr<AceType>& node, LoadEvent&& onLoad) {};
    virtual void RegisterOnDestroy(const RefPtr<AceType>& node, DestroyEvent&& onDestroy) {};
    virtual bool IsTexture()
    {
        return false;
    }
    virtual void SetDetachCallback(DetachCallback&& onDetach) {}
    virtual XComponentType GetType()
    {
        return XComponentType::UNKNOWN;
    }
    virtual std::optional<std::string> GetLibraryName()
    {
        return std::nullopt;
    }
    virtual void EnableAnalyzer(bool enable) {}
    virtual void SetImageAIOptions(void* options) {}
    virtual void SetControllerOnCreated(SurfaceCreatedEvent&& onCreated) {}
    virtual void SetControllerOnChanged(SurfaceChangedEvent&& onChanged) {}
    virtual void SetControllerOnDestroyed(SurfaceDestroyedEvent&& onDestroyed) {}
    virtual void SetRenderFit(RenderFit renderFit) {}
    virtual void EnableSecure(bool isSecure) {}
    virtual void HdrBrightness(float hdrBrightness) {}
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_XCOMPONENT_MODEL_H
