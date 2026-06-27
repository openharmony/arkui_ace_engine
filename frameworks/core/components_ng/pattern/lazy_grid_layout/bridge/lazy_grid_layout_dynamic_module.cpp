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

#include "core/components_ng/pattern/lazy_grid_layout/bridge/arkts_native_lazy_grid_layout_bridge.h"
#include "core/components_ng/pattern/lazy_grid_layout/bridge/lazy_grid_layout_custom_modifier.h"
#include "core/components_ng/pattern/lazy_grid_layout/bridge/lazy_grid_layout_dynamic_module.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_model.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "arkoala_api_generated.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_LazyVGridLayout()
{
    return new OHOS::Ace::LazyGridLayoutDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUILazyGridLayoutModifier* GetLazyGridLayoutDynamicModifier();
const ArkUILazyGridLayoutCustomModifier* GetLazyGridLayoutCustomModifier();
constexpr const char* CUSTOM_MODIFIER = "customModifier";
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
struct LazyGridLayoutCombinedStaticModifiers {
    const void* attributeModifier;
    const void* vGridModifier;
};
const LazyGridLayoutCombinedStaticModifiers* GetLazyGridLayoutCombinedStaticModifiers();
}
#endif
} // namespace NG

void LazyGridLayoutDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::LazyGridLayoutBridge::RegisterLazyGridLayoutAttributes(object, vm);
    NG::LazyVGridLayoutBridge::RegisterLazyVGridLayoutAttributes(object, vm);
}

const void* LazyGridLayoutDynamicModule::GetDynamicModifier()
{
    return NG::GetLazyGridLayoutDynamicModifier();
}

const void* LazyGridLayoutDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetLazyGridLayoutCombinedStaticModifiers();
#else
    return nullptr;
#endif
}

const void* LazyGridLayoutDynamicModule::GetCjModifier()
{
    return nullptr;
}

void* LazyGridLayoutDynamicModule::GetModel()
{
    static NG::LazyVGridLayoutModel lazyVGridLayoutModel;
    return &lazyVGridLayoutModel;
}

const void* LazyGridLayoutDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == NG::CUSTOM_MODIFIER) {
        return NG::GetLazyGridLayoutCustomModifier();
    }
    return nullptr;
}
} // namespace OHOS::Ace
