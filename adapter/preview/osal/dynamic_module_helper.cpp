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
namespace {
#ifdef WINDOWS_PLATFORM
#ifdef UNICODE
const std::wstring COMPATIABLE_LIB = L"libace_compatible_components.dll";
#else
const std::string COMPATIABLE_LIB = "libace_compatible_components.dll";
#endif
#elif MAC_PLATFORM
const std::string COMPATIABLE_LIB = "libace_compatible_components.dylib";
#else
const std::string COMPATIABLE_LIB = "libace_compatible_components.z.so";
#endif
} // namespace
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

DynamicModuleHelper::DynamicModuleHelper()
{
    DynamicLoadLibrary();
}

DynamicModuleHelper::~DynamicModuleHelper()
{
    CloseLibrary();
}

bool DynamicModuleHelper::DynamicLoadLibrary()
{
    if (!compatibleLibLoaded_) {
        compatibleLibHandle_ = LOADLIB(COMPATIABLE_LIB.c_str());
        CHECK_NULL_RETURN(compatibleLibHandle_, false);
        LOGI("Load compatible lib success.");
        compatibleLibLoaded_ = true;
    }
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

} // namespace OHOS::Ace
