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

#include "core/components_ng/pattern/waterflow/bridge/flowitem/water_flow_item_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/waterflow/bridge/flowitem/arkts_native_water_flow_item_bridge.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"
#include "core/interfaces/ani/ani_api.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_FlowItem()
{
    return new OHOS::Ace::WaterFlowItemDynamicModule();
}

namespace OHOS::Ace {
namespace NG {
namespace NodeModifier {
const ArkUIWaterFlowItemModifier* GetFlowItemDynamicModifier();
} // namespace NodeModifier

#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIFlowItemModifier* GetFlowItemStaticModifier();
}
#endif
} // namespace NG

void WaterFlowItemDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::WaterFlowItemBridge::RegisterWaterFlowItemAttributes(object, vm);
}

const void* WaterFlowItemDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetFlowItemDynamicModifier();
}

const void* WaterFlowItemDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetFlowItemStaticModifier();
#else
    return nullptr;
#endif
}

void* WaterFlowItemDynamicModule::GetModel()
{
    static NG::WaterFlowItemModelNG waterFlowItemModel;
    return &waterFlowItemModel;
}

} // namespace OHOS::Ace