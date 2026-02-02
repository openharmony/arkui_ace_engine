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

#include "core/components_ng/pattern/waterflow/bridge/waterflow/water_flow_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/waterflow/bridge/waterflow/arkts_native_water_flow_bridge.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/interfaces/ani/ani_api.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_WaterFlow()
{
    return new OHOS::Ace::WaterFlowDynamicModule();
}

namespace OHOS::Ace {
namespace NG {
namespace NodeModifier {
const ArkUIWaterFlowModifier* GetWaterFlowDynamicModifier();
const CJUIWaterFlowModifier* GetCJUIWaterFlowModifier();
} // namespace NodeModifier

#ifdef INCLUDE_GENERATED_SOURCES
const ArkUIAniWaterFlowModifier* GetArkUIAniWaterFlowModifier();
namespace GeneratedModifier {
const GENERATED_ArkUIWaterFlowModifier* GetWaterFlowStaticModifier();
const GENERATED_ArkUIWaterFlowSectionsAccessor* GetWaterFlowSectionsStaticAccessor();
const GENERATED_ArkUIUIWaterFlowEventAccessor* GetUIWaterFlowEventStaticAccessor();
}
#endif
} // namespace NG

void WaterFlowDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::WaterFlowBridge::RegisterWaterFlowAttributes(object, vm);
}

const void* WaterFlowDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetWaterFlowDynamicModifier();
}

const void* WaterFlowDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetWaterFlowStaticModifier();
#else
    return nullptr;
#endif
}

const void* WaterFlowDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIWaterFlowModifier();
}


const void* WaterFlowDynamicModule::GetAniModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GetArkUIAniWaterFlowModifier();
#else
    return nullptr;
#endif
}

void* WaterFlowDynamicModule::GetModel()
{
    static NG::WaterFlowModelNG waterFlowModel;
    return &waterFlowModel;
}

const void* WaterFlowDynamicModule::GetCustomModifier(const std::string& name)
{
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == "WaterFlowSectionsAccessor") {
        return NG::GeneratedModifier::GetWaterFlowSectionsStaticAccessor();
    } else if (name == "UIWaterFlowEventAccessor") {
        return NG::GeneratedModifier::GetUIWaterFlowEventStaticAccessor();
    } else {
        return nullptr;
    }
#else
    return nullptr;
#endif
}
} // namespace OHOS::Ace