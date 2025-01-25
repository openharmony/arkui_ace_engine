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

#include <memory>
#include <string>

#include "compatible/components/component_loader.h"
#include "ui/base/utils/utils.h"

#include "base/json/json_util.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
DynamicModuleHelper& DynamicModuleHelper::GetInstance()
{
    static DynamicModuleHelper instance;
    return instance;
}

std::unique_ptr<ComponentLoader> DynamicModuleHelper::GetLoaderByName(const char* name)
{
    CHECK_NULL_RETURN(componentLoaderFunc_, nullptr);
    return nullptr;
}

void* DynamicModuleHelper::CreateCanvasRenderingContextModel(bool isOffscreen)
{
    CHECK_NULL_RETURN(canvasRenderingContextLoaderFunc_, nullptr);
    return nullptr;
}

void* DynamicModuleHelper::CreateCanvasBridge(CanvasBridgeParams& params)
{
    CHECK_NULL_RETURN(canvasBridgeLoaderFunc_, nullptr);
    return nullptr;
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
        compatibleLibLoaded_ = true;
    }
    return compatibleLibHandle_ != nullptr;
}

void DynamicModuleHelper::CloseLibrary() {}

void* DynamicModuleHelper::LoadSymbol(const char* symName)
{
    return nullptr;
}

} // namespace OHOS::Ace
