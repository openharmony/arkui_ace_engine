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

#include "core/components_ng/pattern/lazy_column_layout/bridge/lazy_column_layout_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/lazy_column_layout/bridge/arkts_native_lazy_column_layout_bridge.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_model.h"
#include "core/interfaces/ani/ani_api.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_LazyColumnLayout()
{
    return new OHOS::Ace::LazyColumnLayoutDynamicModule();
}

namespace OHOS::Ace {
namespace NG {
namespace NodeModifier {
const ArkUILazyColumnLayoutModifier* GetLazyColumnLayoutDynamicModifier();
}
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
constexpr const char* EXTENDER_ACCESSOR = "ExtenderAccessor";
const GENERATED_ArkUILazyColumnLayoutExtenderAccessor* GetLazyColumnLayoutStaticAccessor();
}
#endif
} // namespace NG

void LazyColumnLayoutDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::LazyColumnLayoutBridge::RegisterLazyColumnLayoutAttributes(object, vm);
}

const void* LazyColumnLayoutDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetLazyColumnLayoutDynamicModifier();
}

const void* LazyColumnLayoutDynamicModule::GetStaticModifier()
{
    return nullptr;
}

const void* LazyColumnLayoutDynamicModule::GetCjModifier()
{
    return nullptr;
}

void* LazyColumnLayoutDynamicModule::GetModel()
{
    static NG::LazyColumnLayoutModel lazyColumnLayoutModel;
    return &lazyColumnLayoutModel;
}

const void* LazyColumnLayoutDynamicModule::GetCustomModifier(const std::string& name)
{
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == NG::GeneratedModifier::EXTENDER_ACCESSOR) {
        return NG::GeneratedModifier::GetLazyColumnLayoutStaticAccessor();
    }
#endif
    return nullptr;
}

} // namespace OHOS::Ace
