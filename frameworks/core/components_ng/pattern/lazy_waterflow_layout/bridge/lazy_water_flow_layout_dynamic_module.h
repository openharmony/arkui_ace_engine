/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_DYNAMIC_MODULE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_DYNAMIC_MODULE_H

#include "core/common/dynamic_module.h"

namespace OHOS::Ace {

// Bridge module for LazyVWaterFlow exposed to Dynamic Import / NodeAPI / CJ loaders. The implementation publishes
// the ArkUI Native modifier table to the panda VM so the ArkTS side can bind properties on demand.
class LazyWaterFlowLayoutDynamicModule : public DynamicModule {
public:
    LazyWaterFlowLayoutDynamicModule() = default;
    ~LazyWaterFlowLayoutDynamicModule() override = default;

    // Register the attribute set exported by this module onto the target panda VM object.
    void RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm) override;
    // Return the modifier table used by ArkTS dynamic binding (a C-ABI function pointer table).
    const void* GetDynamicModifier() override;
    // NodeAPI static binding is unsupported in this module; logs an error and returns nullptr.
    const void* GetStaticModifier() override;
    // CJ (Cangjie) binding is unsupported in this module; logs an error and returns nullptr.
    const void* GetCjModifier() override;
    // Return a Model singleton pointer used by the bridge layer when creating nodes / handling property changes.
    void* GetModel() override;
    const void* GetCustomModifier(const std::string& name = "") override;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_DYNAMIC_MODULE_H
