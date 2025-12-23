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

#include "core/common/dynamic_module_helper.h"

#include "compatible/components/component_loader.h"

#include "base/utils/utils.h"

namespace OHOS::Ace {
DynamicModuleHelper& DynamicModuleHelper::GetInstance()
{
    static DynamicModuleHelper instance;
    return instance;
}

std::unique_ptr<ComponentLoader> DynamicModuleHelper::GetLoaderByName(const char* name)
{
    if (!componentLoaderFunc_) {
        componentLoaderFunc_ = reinterpret_cast<ComponentLoaderFunc>(LoadSymbol(COMPATIABLE_COMPONENT_LOADER.c_str()));
    }

    CHECK_NULL_RETURN(componentLoaderFunc_, nullptr);
    return std::unique_ptr<ComponentLoader>(componentLoaderFunc_(name));
}

void* DynamicModuleHelper::CreateCanvasRenderingContextModel(bool isOffscreen)
{
    if (!canvasRenderingContextLoaderFunc_) {
        canvasRenderingContextLoaderFunc_ =
            reinterpret_cast<CanvasLoaderFunc>(LoadSymbol(COMPATIABLE_CANVAS_RENDERING_CONTEXT.c_str()));
    }

    CHECK_NULL_RETURN(canvasRenderingContextLoaderFunc_, nullptr);
    return canvasRenderingContextLoaderFunc_(isOffscreen);
}

void* DynamicModuleHelper::CreateCanvasBridge(CanvasBridgeParams& params)
{
    if (!canvasBridgeLoaderFunc_) {
        canvasBridgeLoaderFunc_ = reinterpret_cast<CanvasBridgeFunc>(LoadSymbol(COMPATIABLE_CANVAS_BRIDGE.c_str()));
    }

    CHECK_NULL_RETURN(canvasBridgeLoaderFunc_, nullptr);
    return canvasBridgeLoaderFunc_(params);
}

DynamicModuleHelper::DynamicModuleHelper() {}

DynamicModuleHelper::~DynamicModuleHelper()
{
    CloseLibrary();
}

bool DynamicModuleHelper::DynamicLoadLibrary()
{
    return true;
}

void DynamicModuleHelper::CloseLibrary()
{
    if (FREELIB(compatibleLibHandle_) != 0) {
        return;
    }
    compatibleLibHandle_ = nullptr;
    compatibleLibLoaded_ = false;
}

void* DynamicModuleHelper::LoadSymbol(const char* symName)
{
    CHECK_NULL_RETURN(compatibleLibHandle_, nullptr);
#ifdef WINDOWS_PLATFORM
    return reinterpret_cast<void*>(LOADSYM(compatibleLibHandle_, symName));
#else
    return LOADSYM(compatibleLibHandle_, symName);
#endif
}

DynamicModule* DynamicModuleHelper::GetDynamicModule(const std::string& name)
{
    auto iter = moduleMap_.find(name);
    if (iter != moduleMap_.end()) {
        return iter->second.get();
    } else {
#ifdef WINDOWS_PLATFORM
        std::wstring nameW = std::wstring(name.begin(), name.end());
        auto libName = DYNAMIC_MODULE_LIB_PREFIX + nameW + DYNAMIC_MODULE_LIB_POSTFIX;
#else
        auto libName = DYNAMIC_MODULE_LIB_PREFIX + name + DYNAMIC_MODULE_LIB_POSTFIX;
#endif
        LIBHANDLE handle = LOADLIB(libName.c_str());
        CHECK_NULL_RETURN(handle, nullptr);
        auto* createSym =  reinterpret_cast<DynamicModuleCreateFunc>(LOADSYM(handle, DYNAMIC_MODULE_CREATE.c_str()));
        CHECK_NULL_RETURN(createSym, nullptr);
        DynamicModule* module = createSym();
        CHECK_NULL_RETURN(module, nullptr);
        LOGI("First load %{public}s nativeModule finish", name.c_str());
        moduleMap_.emplace(name, std::unique_ptr<DynamicModule>(module));
        return module;
    }
}

} // namespace OHOS::Ace