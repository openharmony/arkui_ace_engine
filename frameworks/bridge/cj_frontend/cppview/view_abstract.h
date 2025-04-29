/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_VIEW_ABSTRACT_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_VIEW_ABSTRACT_H

#include <functional>
#include <optional>
#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/geometry/dimension_rect.h"
#include "base/json/json_util.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/common/container.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_object.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"
#include "core/components_ng/pattern/text/text_model.h"
#ifndef __OHOS_NG__
#include "core/components/box/box_component.h"
#include "core/components/display/display_component.h"
#include "core/components/menu/menu_component.h"
#include "core/components/theme/theme_manager.h"
#include "core/components/transform/transform_component.h"
#endif
#include "ffi_remote_data.h"

#include "core/gestures/tap_gesture.h"
#include "core/pipeline/base/component.h"

using VectorTextMenuItemHandle = void*;

extern "C" {
struct NativeResourceObject {
    const char* bundleName;
    const char* moduleName;
    int32_t id;
    int32_t type;
    const char* paramsJsonStr;
};

struct FfiTextMenuItem {
    ExternalString content;
    ExternalString icon;
    ExternalString id;
};
}

typedef VectorTextMenuItemHandle (*CjOnCreateMenu)(VectorTextMenuItemHandle);
typedef bool (*CjOnMenuItemClick)(FfiTextMenuItem, int32_t, int32_t);

namespace OHOS::Ace {
enum class ResourceType : uint32_t {
    COLOR = 10001,
    FLOAT,
    STRING,
    PLURAL,
    BOOLEAN,
    INTARRAY,
    INTEGER,
    PATTERN,
    STRARRAY,
    MEDIA = 20000,
    RAWFILE = 30000,
    SYMBOL = 40000
};
}

namespace OHOS::Ace::Framework {
RefPtr<ResourceObject> GetResourceObject(const NativeResourceObject& obj);
RefPtr<ResourceObject> GetResourceObjectByBundleAndModule(const NativeResourceObject& obj);
RefPtr<ResourceWrapper> CreateResourceWrapper(const NativeResourceObject& obj, RefPtr<ResourceObject>& resourceObject);
RefPtr<ResourceWrapper> CreateResourceWrapper();

enum class Align {
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    CENTER_LEFT,
    CENTER,
    CENTER_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT,
};

enum class CJResponseType : int32_t {
    RIGHT_CLICK = 0,
    LONGPRESS,
};

class ACE_EXPORT ViewAbstract : public OHOS::FFI::FFIData {
    DECL_TYPE(ViewAbstract, OHOS::FFI::FFIData)
public:
    ViewAbstract() : FFIData() {}

    template<typename T>
    static RefPtr<T> GetTheme()
    {
        auto currentObj = Container::Current();
        if (!currentObj) {
            LOGW("container is null");
            return nullptr;
        }
        auto pipelineContext = currentObj->GetPipelineContext();
        if (!pipelineContext) {
            LOGE("pipelineContext is null!");
            return nullptr;
        }
        auto themeManager = pipelineContext->GetThemeManager();
        if (!themeManager) {
            LOGE("themeManager is null!");
            return nullptr;
        }
        return themeManager->GetTheme<T>();
    }

    static RefPtr<ThemeConstants> GetThemeConstants(
        const std::string& bundleName = "", const std::string& moduleName = "");
    static void CjEnabled(bool enabled);

    static void CompleteResourceObject(NativeResourceObject& obj, std::string& bundleName, std::string& moduleName);
    static void CompleteResourceObjectWithBundleName(
        NativeResourceObject& obj, std::string& bundleName, std::string& moduleName, int32_t& resId);
    static bool ConvertResourceType(const std::string& typeName, ResourceType& resType);
    static bool ParseDollarResource(const std::string& resPath, std::string& targetModule, ResourceType& resType,
        std::string& resName, bool isParseType);

    static bool ParseCjString(NativeResourceObject& obj, std::string& result);
    static bool ParseCjMedia(NativeResourceObject& obj, std::string& result);
    static bool ParseCjSymbolId(NativeResourceObject& obj, uint32_t& result);
    static bool ParseCjColor(NativeResourceObject& obj, Color& result);
    static bool ParseCjDimension(
        NativeResourceObject& obj, CalcDimension& result, DimensionUnit defaultUnit, bool isSupportPercent = true);
    static bool ParseCjDimensionVP(NativeResourceObject& obj, CalcDimension& result, bool isSupportPercent = true);
    static bool ParseCjDimensionFP(NativeResourceObject& obj, CalcDimension& result, bool isSupportPercent = true);
    static bool ParseCjDouble(NativeResourceObject& obj, double& result);
    static bool ParseCjInteger(NativeResourceObject& obj, uint32_t& result);
    static bool ParseCjInteger(NativeResourceObject& obj, int32_t& result);
    static bool ParseCjBool(NativeResourceObject& obj, bool& result);
    static bool ParseCjIntegerArray(NativeResourceObject& obj, std::vector<uint32_t>& result);
    static bool ParseCjStringArray(NativeResourceObject& obj, std::vector<std::string>& result);

    template<typename T>
    static bool ParseCjInteger(NativeResourceObject& obj, T& result)
    {
        std::string bundleName;
        std::string moduleName;
        CompleteResourceObject(obj, bundleName, moduleName);
        if (obj.type == -1) {
            return false;
        }
        auto resourceObject = GetResourceObjectByBundleAndModule(obj);
        auto resourceWrapper = CreateResourceWrapper(obj, resourceObject);
        if (!resourceWrapper) {
            return false;
        }
        if (obj.id == -1) {
            if (!obj.paramsJsonStr) {
                return false;
            }
            auto params = JsonUtil::ParseJsonString(obj.paramsJsonStr);
            if (!params->IsArray()) {
                return false;
            }
            auto param = params->GetArrayItem(0);
            if (obj.type == static_cast<int32_t>(ResourceType::INTEGER)) {
                result = static_cast<T>(resourceWrapper->GetIntByName(param->GetString()));
                return true;
            }
            return false;
        }
        if (obj.type == static_cast<int32_t>(ResourceType::INTEGER)) {
            result = static_cast<T>(resourceWrapper->GetInt(static_cast<uint32_t>(obj.id)));
            return true;
        }
        return false;
    }

    static bool ParseEditMenuOptions(CjOnCreateMenu& cjOnCreateMenu, CjOnMenuItemClick& cjOnMenuItemClick,
        NG::OnCreateMenuCallback& onCreateMenuCallback, NG::OnMenuItemClickCallback& onMenuItemClick);

private:
    static void CompleteResourceObjectInner(
        NativeResourceObject& obj, std::string& bundleName, std::string& moduleName, int32_t& resIdValue);
    static bool ParseCjMediaInternal(NativeResourceObject& obj, std::string& result);
    static void ParseOnCreateMenu(CjOnCreateMenu& cjOnCreateMenu, NG::OnCreateMenuCallback& onCreateMenuCallback);
    static void ParseOnMenuItemClick(
        CjOnMenuItemClick& cjOnMenuItemClick, NG::OnMenuItemClickCallback& onMenuItemClick);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_VIEW_ABSTRACT_H
