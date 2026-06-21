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

#include "frameworks/core/components_ng/pattern/texttimer/bridge/text_timer_dynamic_module.h"
#include "frameworks/core/components_ng/pattern/texttimer/bridge/text_timer_dynamic_modifier.h"

#include "arkoala_api_generated.h"

#include "frameworks/core/components_ng/pattern/texttimer/bridge/arkts_native_text_timer_bridge.h"
#include "core/components_ng/pattern/texttimer/text_timer_model_ng.h"


#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/texttimer/text_timer_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_TextTimer()
{
    return new OHOS::Ace::TextTimerDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUITextTimerModifier* GetTextTimerDynamicModifier();
const CJUITextTimerModifier* GetCJUITextTimerModifier();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
ACE_FORCE_EXPORT const GENERATED_ArkUITextTimerModifier* GetTextTimerStaticModifier();
}
#endif
} // namespace NG

void TextTimerDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::TextTimerBridge::RegisterAttributes(object, vm);
}

const void* TextTimerDynamicModule::GetDynamicModifier()
{
    return NG::GetTextTimerDynamicModifier();
}

const void* TextTimerDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetTextTimerStaticModifier();
#else
    return nullptr;
#endif
}

const void* TextTimerDynamicModule::GetCjModifier()
{
    return NG::GetCJUITextTimerModifier();
}

void* TextTimerDynamicModule::GetModel()
{
    static NG::TextTimerModelNG model;
    return &model;
}

} // namespace OHOS::Ace
