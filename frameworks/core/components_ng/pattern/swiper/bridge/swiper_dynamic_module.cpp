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

#include "core/components_ng/pattern/swiper/bridge/swiper_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/swiper/bridge/arkts_native_swiper_bridge.h"
#include "core/components_ng/pattern/swiper/bridge/swiper_custom_modifier.h"
#include "core/components_ng/pattern/swiper/bridge/swiper_controller_modifier_api.h"
#include "core/components_ng/pattern/swiper/bridge/swiper_transition_proxy_modifier_api.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Swiper()
{
    return new OHOS::Ace::SwiperDynamicModule();
}

namespace OHOS::Ace {
namespace NG {
namespace NodeModifier {
const ArkUISwiperModifier* GetSwiperModifier();
const ArkUIArcSwiperModifier* GetArcSwiperModifier();
const CJUISwiperModifier* GetCJUISwiperModifier();
const CJUISwiperControllerModifier* GetCJUISwiperControllerModifier();
const ArkUISwiperControllerModifier* GetSwiperControllerModifier();
const ArkUISwiperCustomModifier* GetSwiperCustomModifier();
} // namespace NodeModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUISwiperModifier* GetSwiperModifier();
const GENERATED_ArkUISwiperControllerAccessor* GetSwiperControllerAccessor();
const GENERATED_ArkUISwiperContentTransitionProxyAccessor* GetSwiperContentTransitionProxyAccessor();
} // namespace GeneratedModifier
#endif
} // namespace NG

void SwiperDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::SwiperBridge::RegisterSwiperAttributes(object, vm);
}

const void* SwiperDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetSwiperModifier();
}

const void* SwiperDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetSwiperModifier();
#else
    return nullptr;
#endif
}

const void* SwiperDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUISwiperModifier();
}

void* SwiperDynamicModule::GetModel()
{
    static NG::SwiperModelNG model;
    return &model;
}

const void* SwiperDynamicModule::GetCustomModifier(const std::string& name)
{
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == "swiperModifier") {
        return NG::GeneratedModifier::GetSwiperModifier();
    }
    if (name == "swiperControllerAccessor") {
        return NG::GeneratedModifier::GetSwiperControllerAccessor();
    }
    if (name == "swiperContentTransitionProxyAccessor") {
        return NG::GeneratedModifier::GetSwiperContentTransitionProxyAccessor();
    }
#endif
    if (name == "swiperCustomModifier") {
        return NG::NodeModifier::GetSwiperCustomModifier();
    }
    if (name == "swiperController") {
        return NG::NodeModifier::GetCustomSwiperControllerModifier();
    }
    if (name == "swiperCjController") {
        return NG::NodeModifier::GetCJUISwiperControllerModifier();
    }
    if (name == "swiperArkController") {
        return NG::NodeModifier::GetSwiperControllerModifier();
    }
    if (name == "swiperTransitionProxy") {
        return NG::NodeModifier::GetSwiperTransitionProxyModifier();
    }
    if (name == "swiperArcModifier") {
        return NG::NodeModifier::GetArcSwiperModifier();
    }
    return nullptr;
}
} // namespace OHOS::Ace
