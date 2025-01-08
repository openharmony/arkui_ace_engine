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

#include "core/common/dynamic_module_helper.h"

#include <dlfcn.h>
#include <memory>
#include <string>

#include "ui/base/utils/utils.h"

#include "adapter/ohos/entrance/utils.h"
#include "base/json/json_util.h"
#include "base/utils/utils.h"
#include "compatible/components/component_loader.h"

namespace OHOS::Ace {
namespace {
const char COMPATIABLE_LIB[] = "libace_compatible_components.z.so";
const char COMPATIABLE_COMPONENT_LOADER[] = "OHOS_ACE_Compatible_GetLoader";
const char COMPATIABLE_CANVAS_RENDERING_CONTEXT[] = "OHOS_ACE_Compatible_GetCanvasRenderingContext";
const char COMPATIABLE_CANVAS_BRIDGE[] = "OHOS_ACE_Compatible_CreateCanvasBridge";
const char VENDOR_CONFIG_PATH[] = "/etc/abc/arkui/";
const char VENDOR_CONFIG_FILE[] = "vendor_config.json";
const char SO_POSTFIX[] = ".z.so";
} // namespace
DynamicModuleHelper& DynamicModuleHelper::GetInstance()
{
    static DynamicModuleHelper instance;
    return instance;
}

std::unique_ptr<ComponentLoader> DynamicModuleHelper::GetLoaderByName(const char* name)
{
    if (!componentLoaderFunc_) {
        componentLoaderFunc_ = reinterpret_cast<ComponentLoaderFunc>(LoadSymbol(COMPATIABLE_COMPONENT_LOADER));
    }

    CHECK_NULL_RETURN(componentLoaderFunc_, nullptr);
    return std::unique_ptr<ComponentLoader>(componentLoaderFunc_(name));
}

void* DynamicModuleHelper::CreateCanvasRenderingContextModel(bool isOffscreen)
{
    if (!canvasRenderingContextLoaderFunc_) {
        canvasRenderingContextLoaderFunc_ =
            reinterpret_cast<CanvasLoaderFunc>(LoadSymbol(COMPATIABLE_CANVAS_RENDERING_CONTEXT));
    }

    CHECK_NULL_RETURN(canvasRenderingContextLoaderFunc_, nullptr);
    return canvasRenderingContextLoaderFunc_(isOffscreen);
}

void* DynamicModuleHelper::CreateCanvasBridge(CanvasBridgeParams& params)
{
    if (!canvasBridgeLoaderFunc_) {
        canvasBridgeLoaderFunc_ = reinterpret_cast<CanvasBridgeFunc>(LoadSymbol(COMPATIABLE_CANVAS_BRIDGE));
    }

    CHECK_NULL_RETURN(canvasBridgeLoaderFunc_, nullptr);
    return canvasBridgeLoaderFunc_(params);
}

DynamicModuleHelper::DynamicModuleHelper()
{
    LoadLibrary();
}

DynamicModuleHelper::~DynamicModuleHelper()
{
    CloseLibrary();
}

bool DynamicModuleHelper::LoadLibrary()
{
    if (!compatibleLibLoaded_) {
        compatibleLibHandle_ = dlopen(COMPATIABLE_LIB, RTLD_LAZY);
        CHECK_NULL_RETURN(compatibleLibHandle_, false);

        compatibleLibLoaded_ = true;
    }
    return true;
}

void DynamicModuleHelper::CloseLibrary()
{
    if (dlclose(compatibleLibHandle_) != 0) {
        return;
    }
    compatibleLibHandle_ = nullptr;
    compatibleLibLoaded_ = false;
}

void* DynamicModuleHelper::LoadSymbol(const char* symName)
{
    CHECK_NULL_RETURN(compatibleLibHandle_, nullptr);
    return dlsym(compatibleLibHandle_, symName);
}

void DynamicModuleHelper::LoadVendorConfig()
{
    std::string path(VENDOR_CONFIG_PATH);
    std::string config(VENDOR_CONFIG_FILE);
    std::string jsonStr = GetStringFromFile(path, config);
    vendorConfig_ = JsonUtil::ParseJsonString(jsonStr);
}

std::unique_ptr<JsonValue> DynamicModuleHelper::GetVendorFeatures()
{
    if (vendorConfig_) {
        return vendorConfig_->GetObject("features");
    }
    return nullptr;
}

CreatorFunc DynamicModuleHelper::GetCreatorByFeatureName(const std::string& feature)
{
    auto iter = vendorSymbolMap_.find(feature);
    if (iter != vendorSymbolMap_.end()) {
        return iter->second;
    } else {
        auto features = GetVendorFeatures();
        CHECK_NULL_RETURN(features, nullptr);
        auto featureObj = features->GetObject(feature);
        CHECK_NULL_RETURN(featureObj, nullptr);
        auto library = featureObj->GetString("library");
        library.append(SO_POSTFIX);
        auto symbol = featureObj->GetString("symbol");
        LOGI("DynamicModuleHelper::GetCreatorByFeatureName feature:%{public}s library:%{public}s symbol:%{public}s",
            feature.c_str(), library.c_str(), symbol.c_str());
        CHECK_NULL_RETURN(!library.empty() && !symbol.empty(), nullptr);
        auto libHandle = dlopen(library.c_str(), RTLD_LAZY);
        CHECK_NULL_RETURN(libHandle, nullptr);
        vendorHandleMap_.emplace(feature, libHandle);
        void* libSymbol = dlsym(libHandle, symbol.c_str());
        CHECK_NULL_RETURN(libSymbol, nullptr);
        CreatorFunc result = reinterpret_cast<CreatorFunc>(libSymbol);
        vendorSymbolMap_.emplace(feature, result);
        return result;
    }
    return nullptr;
}

} // namespace OHOS::Ace
