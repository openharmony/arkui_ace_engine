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

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "compatible/components/component_loader.h"

namespace OHOS::Ace {

using ComponentLoaderFunc = ComponentLoader* (*)(const char* name);
using CanvasLoaderFunc = void* (*)(bool offscreen);
using CanvasBridgeFunc = void* (*)(CanvasBridgeParams& params);

class ACE_EXPORT DynamicModuleHelper final {
public:
    static DynamicModuleHelper& GetInstance();
    std::unique_ptr<ComponentLoader> GetLoaderByName(const char* name);
    void* CreateCanvasRenderingContextModel(bool isOffscreen);
    void* CreateCanvasBridge(CanvasBridgeParams& params);

private:
    DynamicModuleHelper();
    ~DynamicModuleHelper();
    bool LoadLibrary();
    void CloseLibrary();
    void* LoadSymbol(const char* symName);

    void* compatibleLibHandle_ = nullptr;
    bool compatibleLibLoaded_ = false;

    ComponentLoaderFunc componentLoaderFunc_ = nullptr;
    CanvasLoaderFunc canvasRenderingContextLoaderFunc_ = nullptr;
    CanvasBridgeFunc canvasBridgeLoaderFunc_ = nullptr;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_DYNAMIC_MODULE_HELPER_H
