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

#include "core/components_ng/pattern/slider/bridge/slider_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "frameworks/core/components_ng/pattern/slider/bridge/slider_custom_modifier.h"
#include "core/components_ng/pattern/slider/bridge/arkts_native_slider_bridge.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/slider/slider_model_static.h"
#include "core/components_ng/pattern/slider/bridge/slider_content_modifier_helper.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Slider()
{
    return new OHOS::Ace::SliderDynamicModule();
}

namespace OHOS::Ace {
namespace NG {
const ArkUISliderModifier* GetSliderDynamicModifier();
const CJUISliderModifier* GetCJUISliderModifier();
namespace CustomModifier {
    constexpr const char* CUSTOM_MODIFIER = "customModifier";
    const ArkUISliderCustomModifier* GetSliderCustomModifier();
}
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
constexpr const char* CONTENT_MODIFIER = "contentModifier";
constexpr const char* SLIDER_SECTIONS_ACCESSOR = "sliderSectionsAccessor";
const GENERATED_ArkUISliderModifier* GetSliderStaticModifier();
const GENERATED_ArkUISliderExtenderAccessor* GetSliderExtenderAccessorModifier();
const GENERATED_ArkUISliderContentModifier* GetSliderStaticContentModifier();
} // namespace GeneratedModifier
#endif
} // namespace NG

void SliderDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::SliderBridge::RegisterSliderAttributes(object, vm);
}

const void* SliderDynamicModule::GetDynamicModifier()
{
    return NG::GetSliderDynamicModifier();
}

const void* SliderDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetSliderStaticModifier();
#else
    return nullptr;
#endif
}

const void* SliderDynamicModule::GetCjModifier()
{
    return NG::GetCJUISliderModifier();
}

void* SliderDynamicModule::GetModel()
{
    static NG::SliderModelNG model;
    return &model;
}

const void* SliderDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == NG::CustomModifier::CUSTOM_MODIFIER) {
        return NG::CustomModifier::GetSliderCustomModifier();
    }
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == NG::GeneratedModifier::CONTENT_MODIFIER) {
        return NG::GeneratedModifier::GetSliderStaticContentModifier();
    } else if (name == NG::GeneratedModifier::SLIDER_SECTIONS_ACCESSOR) {
        return NG::GeneratedModifier::GetSliderExtenderAccessorModifier();
    } else {
        return nullptr;
    }
#else
    return nullptr;
#endif
}
} // namespace OHOS::Ace