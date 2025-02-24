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

namespace OHOS::Ace {
class JsonValue;

DynamicModuleHelper& DynamicModuleHelper::GetInstance()
{
    static DynamicModuleHelper instance;
    return instance;
}

DynamicModuleHelper::DynamicModuleHelper() {}

DynamicModuleHelper::~DynamicModuleHelper() {}

std::unique_ptr<ComponentLoader> DynamicModuleHelper::GetLoaderByName(const char* name)
{
    return nullptr;
}

void* DynamicModuleHelper::CreateCanvasRenderingContextModel(bool isOffscreen)
{
    return nullptr;
}

void* DynamicModuleHelper::CreateCanvasBridge(CanvasBridgeParams& params)
{
    return nullptr;
}

bool DynamicModuleHelper::LoadLibrary()
{
    return false;
}

void DynamicModuleHelper::CloseLibrary() {}

void* DynamicModuleHelper::LoadSymbol(const char* symName)
{
    return nullptr;
}
} // namespace OHOS::Ace
