/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_INNERAPI_DRAWABLE_BRIDGE_H
#define FOUNDATION_ACE_INTERFACE_INNERAPI_DRAWABLE_BRIDGE_H

#include <cstdint>
#include <memory>
#include <vector>

#include "drawable_api.h"
#include "resource_manager.h"

namespace OHOS::Ace {
void* ParseResourceObject(void* object);
std::shared_ptr<Global::Resource::ResourceManager> GetResourceManager();
const ArkUIDrawableDescriptor* GetArkUIDrawableModifier();
int32_t ParseDimensionToPx(void* value);
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERAPI_DRAWABLE_BRIDGE_H