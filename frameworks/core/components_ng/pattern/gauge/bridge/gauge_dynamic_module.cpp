/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/gauge/bridge/gauge_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/gauge/bridge/arkts_native_gauge_bridge.h"
#include "core/components_ng/pattern/gauge/bridge/content_modifier_helper.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/gauge/gauge_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create()
{
    return new OHOS::Ace::GaugeDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUIGaugeModifier* GetGaugeDynamicModifier();
const CJUIGaugeModifier* GetCJUIGaugeModifier();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIGaugeModifier* GetGaugeStaticModifier();
const GENERATED_ArkUIGaugeContentModifier* GetGaugeStaticContentModifier();
} // namespace GeneratedModifier
#endif
} // namespace NG

void GaugeDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::GaugeBridge::RegisterGaugeAttributes(object, vm);
}

const void* GaugeDynamicModule::GetDynamicModifier()
{
    return NG::GetGaugeDynamicModifier();
}

const void* GaugeDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetGaugeStaticModifier();
#else
    return nullptr;
#endif
}

const void* GaugeDynamicModule::GetCjModifier()
{
    return NG::GetCJUIGaugeModifier();
}

void* GaugeDynamicModule::GetModel()
{
    static NG::GaugeModelNG model;
    return &model;
}

const void* GaugeDynamicModule::GetCustomModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetGaugeStaticContentModifier();
#else
    return nullptr;
#endif
}

} // namespace OHOS::Ace
