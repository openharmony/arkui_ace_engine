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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_DYNAMIC_MODULE_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_DYNAMIC_MODULE_HELPER_H

#include <memory>
#include <string>
#include <unordered_map>

#include "compatible/components/component_loader.h"
#include "interfaces/inner_api/ace/utils.h"

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/common/dynamic_module.h"
#include "interfaces/inner_api/ace/utils.h"

namespace OHOS::Ace {

using ComponentLoaderFunc = ComponentLoader* (*)(const char* name);
using CanvasLoaderFunc = void* (*)(bool offscreen);
using CanvasBridgeFunc = void* (*)(CanvasBridgeParams& params);
using DynamicModuleCreateFunc = DynamicModule* (*)();

#ifdef WINDOWS_PLATFORM
#ifdef UNICODE
const std::wstring COMPATIABLE_LIB = L"libace_compatible_components.dll";
const std::wstring DYNAMIC_MODULE_LIB_PREFIX = L"libarkui_";
const std::wstring DYNAMIC_MODULE_LIB_POSTFIX = L".dll";
#else
const std::string COMPATIABLE_LIB = "libace_compatible_components.dll";
const std::string DYNAMIC_MODULE_LIB_PREFIX = "libarkui_";
const std::string DYNAMIC_MODULE_LIB_POSTFIX = ".dll";
#endif
#else
const std::string COMPATIABLE_LIB = "libace_compatible_components.z.so";
const std::string DYNAMIC_MODULE_LIB_PREFIX = "libarkui_";
const std::string DYNAMIC_MODULE_LIB_POSTFIX = ".z.so";
#endif
const std::string COMPATIABLE_COMPONENT_LOADER = "OHOS_ACE_Compatible_GetLoader";
const std::string COMPATIABLE_CANVAS_RENDERING_CONTEXT = "OHOS_ACE_Compatible_GetCanvasRenderingContext";
const std::string COMPATIABLE_CANVAS_BRIDGE = "OHOS_ACE_Compatible_CreateCanvasBridge";
const std::string DYNAMIC_MODULE_CREATE = "OHOS_ACE_DynamicModule_Create";

class ACE_FORCE_EXPORT DynamicModuleHelper final {
public:
    static DynamicModuleHelper& GetInstance();
    std::unique_ptr<ComponentLoader> GetLoaderByName(const char* name);
    void* CreateCanvasRenderingContextModel(bool isOffscreen);
    void* CreateCanvasBridge(CanvasBridgeParams& params);

    DynamicModule* GetDynamicModule(const std::string& name);
private:
    DynamicModuleHelper();
    ~DynamicModuleHelper();
    bool DynamicLoadLibrary();
    void CloseLibrary();
    void* LoadSymbol(const char* symName);

    LIBHANDLE compatibleLibHandle_ = nullptr;
    bool compatibleLibLoaded_ = false;

    ComponentLoaderFunc componentLoaderFunc_ = nullptr;
    CanvasLoaderFunc canvasRenderingContextLoaderFunc_ = nullptr;
    CanvasBridgeFunc canvasBridgeLoaderFunc_ = nullptr;

    std::unordered_map<std::string, std::unique_ptr<DynamicModule>> moduleMap_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_DYNAMIC_MODULE_HELPER_H
