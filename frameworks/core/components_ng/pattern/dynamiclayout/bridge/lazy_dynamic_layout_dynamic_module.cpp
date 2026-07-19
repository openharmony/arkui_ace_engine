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

#include "core/components_ng/pattern/dynamiclayout/bridge/lazy_dynamic_layout_dynamic_module.h"
#include "core/components_ng/pattern/dynamiclayout/bridge/arkts_native_dynamic_layout_bridge.h"
#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_model_ng.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/ani/ani_api.h"

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUIDynamicLayoutModifier* GetDynamicLayoutDynamicModifier();
}
#ifdef INCLUDE_GENERATED_SOURCES
const ArkUIAniLazyDynamicLayoutModifier* GetArkUIAniLazyDynamicLayoutModifier();
#endif
} // namespace NG

void LazyDynamicLayoutDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::DynamicLayoutBridge::RegisterDynamicLayoutAttributes(object, vm);
}

const void* LazyDynamicLayoutDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetDynamicLayoutDynamicModifier();
}

const void* LazyDynamicLayoutDynamicModule::GetStaticModifier()
{
    return nullptr;
}

const void* LazyDynamicLayoutDynamicModule::GetCjModifier()
{
    return nullptr;
}

void* LazyDynamicLayoutDynamicModule::GetModel()
{
    static NG::LazyDynamicLayoutModelNG model;
    return &model;
}

const void* LazyDynamicLayoutDynamicModule::GetCustomModifier(const std::string& name)
{
    return nullptr;
}

const void* LazyDynamicLayoutDynamicModule::GetAniModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GetArkUIAniLazyDynamicLayoutModifier();
#else
    return nullptr;
#endif
}

} // namespace OHOS::Ace