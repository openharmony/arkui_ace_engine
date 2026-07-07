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

#include "core/components_ng/pattern/swiper_indicator/bridge/indicator_component_dynamic_module.h"

#include "core/interfaces/arkoala/arkoala_api.h"
#include "arkoala_api_generated.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

#include "core/components_ng/pattern/swiper_indicator/bridge/arkts_native_indicator_component_bridge.h"
#include "core/components_ng/pattern/swiper_indicator/bridge/indicator_controller_modifier_api.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model_ng.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_IndicatorComponent()
{
    return new OHOS::Ace::IndicatorComponentDynamicModule();
}

namespace OHOS::Ace {
namespace NG {
namespace NodeModifier {
const ArkUIIndicatorComponentModifier* GetIndicatorComponentModifier();
} // namespace NodeModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIIndicatorComponentModifier* GetIndicatorComponentModifier();
} // namespace GeneratedModifier
#endif
} // namespace NG

void IndicatorComponentDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::IndicatorComponentBridge::RegisterIndicatorComponentAttributes(object, vm);
}

const void* IndicatorComponentDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetIndicatorComponentModifier();
}

const void* IndicatorComponentDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetIndicatorComponentModifier();
#else
    return nullptr;
#endif
}

const void* IndicatorComponentDynamicModule::GetCjModifier()
{
    return nullptr;
}

void* IndicatorComponentDynamicModule::GetModel()
{
    static NG::IndicatorModelNG model;
    return &model;
}

const void* IndicatorComponentDynamicModule::GetCustomModifier(const std::string& name)
{
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == "indicatorComponentModifier") {
        return NG::GeneratedModifier::GetIndicatorComponentModifier();
    }
#endif
    if (name == "indicator_controller") {
        return NG::GetIndicatorControllerModifier();
    }
    return nullptr;
}
} // namespace OHOS::Ace
