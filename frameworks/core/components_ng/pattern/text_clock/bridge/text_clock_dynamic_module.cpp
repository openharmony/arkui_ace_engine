/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_clock/bridge/text_clock_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/text_clock/bridge/arkts_native_text_clock_bridge.h"
#include "core/components_ng/pattern/text_clock/bridge/text_clock_custom_modifier.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/text_clock/bridge/text_clock_content_modifier_helper.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_TextClock()
{
    return new OHOS::Ace::TextClockDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUITextClockModifier* GetTextClockDynamicModifier();
const CJUITextClockModifier* GetCJUITextClockModifier();
const ArkUITextClockCustomModifier* GetTextClockCustomModifier();
constexpr const char* CUSTOM_MODIFIER = "customModifier";
#ifdef INCLUDE_GENERATED_SOURCES
constexpr const char* CONTENT_MODIFIER = "contentModifier";
namespace GeneratedModifier {
const GENERATED_ArkUITextClockModifier* GetTextClockStaticModifier();
const GENERATED_ArkUITextClockContentModifier* GetTextClockStaticContentModifier();
} // namespace GeneratedModifier
#endif
} // namespace NG

void TextClockDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::TextClockBridge::RegisterTextClockAttributes(object, vm);
}

const void* TextClockDynamicModule::GetDynamicModifier()
{
    return NG::GetTextClockDynamicModifier();
}

const void* TextClockDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetTextClockStaticModifier();
#else
    return nullptr;
#endif
}

const void* TextClockDynamicModule::GetCjModifier()
{
    return NG::GetCJUITextClockModifier();
}

void* TextClockDynamicModule::GetModel()
{
    static NG::TextClockModelNG model;
    return &model;
}

const void* TextClockDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == NG::CUSTOM_MODIFIER) {
        return NG::GetTextClockCustomModifier();
    }
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == NG::CONTENT_MODIFIER) {
        return NG::GeneratedModifier::GetTextClockStaticContentModifier();
    }
#endif
    return nullptr;
}

} // namespace OHOS::Ace