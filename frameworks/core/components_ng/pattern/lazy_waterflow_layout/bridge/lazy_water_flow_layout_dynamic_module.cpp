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

#include "core/components_ng/pattern/lazy_waterflow_layout/bridge/lazy_water_flow_layout_dynamic_module.h"

// Defining RegisterAttributes needs the full panda::Local<panda::ObjectRef> template
// definition (not just the forward declaration in dynamic_module.h) because the override
// takes panda::Local<panda::ObjectRef> by value. jsnapi.h is the minimal panda header that
// provides it, without dragging in declarative_frontend.
#include "ecmascript/napi/include/jsnapi.h"

#include "base/log/log_wrapper.h"

struct ArkUILazyWaterFlowLayoutModifier;

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_LazyVWaterFlowLayout()
{
    return new OHOS::Ace::LazyWaterFlowLayoutDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
void* GetLazyVWaterFlowLayoutModel();

// Avoid pulling arkts_native_lazy_water_flow_layout_bridge.h (and its transitive
// declarative_frontend.h) into this dynamic-module TU; panda forward declarations
// in dynamic_module.h give us the signatures we need.
class LazyVWaterFlowLayoutBridge {
public:
    static void RegisterLazyVWaterFlowLayoutAttributes(
        panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm);
};

namespace NodeModifier {
const ArkUILazyWaterFlowLayoutModifier* GetLazyWaterFlowLayoutDynamicModifier();
} // namespace NodeModifier
} // namespace NG

void LazyWaterFlowLayoutDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    // Intentionally rely only on panda forward declarations here to avoid pulling in
    // declarative_frontend.h. Calling object.IsEmpty() would force the full panda::Local template
    // definition into this TU; the bridge Register functions already perform that validation
    // (see arkts_native_lazy_water_flow_layout_bridge.cpp), so we can forward unconditionally.
    if (!vm) {
        return;
    }
    NG::LazyVWaterFlowLayoutBridge::RegisterLazyVWaterFlowLayoutAttributes(object, vm);
}

const void* LazyWaterFlowLayoutDynamicModule::GetDynamicModifier()
{
    // The concrete modifier table is provided by the lazywaterflowlayout component library.
    return NG::NodeModifier::GetLazyWaterFlowLayoutDynamicModifier();
}

const void* LazyWaterFlowLayoutDynamicModule::GetStaticModifier()
{
    TAG_LOGE(AceLogTag::ACE_LAZY_WATER_FLOW, "LazyWaterFlowLayout static modifier is not supported in this module");
    return nullptr;
}

const void* LazyWaterFlowLayoutDynamicModule::GetCjModifier()
{
    TAG_LOGE(AceLogTag::ACE_LAZY_WATER_FLOW, "LazyWaterFlowLayout Cj modifier is not supported in this module");
    return nullptr;
}

void* LazyWaterFlowLayoutDynamicModule::GetModel()
{
    return NG::GetLazyVWaterFlowLayoutModel();
}

} // namespace OHOS::Ace
