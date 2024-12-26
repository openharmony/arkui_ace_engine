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

#include "base/utils/utils.h"
#include "compatible/components/component_loader.h"

namespace OHOS::Ace {
namespace {
const std::string COMPATIABLE_LIB = "libace_compatible_components.z.so";
const std::string COMPATIABLE_COMPONENT_LOADER = "OHOS_ACE_Compatible_GetLoader";
const std::string COMPATIABLE_CANVAS_RENDERING_CONTEXT = "OHOS_ACE_Compatible_GetCanvasRenderingContext";
const std::string COMPATIABLE_CANVAS_BRIDGE = "OHOS_ACE_Compatible_CreateCanvasBridge";
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
    LoadLibrary();
}

DynamicModuleHelper::~DynamicModuleHelper()
{
    CloseLibrary();
}

bool DynamicModuleHelper::LoadLibrary()
{
    if (!compatibleLibLoaded_) {
        compatibleLibHandle_ = dlopen(COMPATIABLE_LIB.c_str(), RTLD_LAZY);
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

} // namespace OHOS::Ace
