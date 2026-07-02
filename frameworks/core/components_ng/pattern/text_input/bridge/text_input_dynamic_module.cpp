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

#include "core/components_ng/pattern/text_input/bridge/text_input_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/text_input/bridge/arkts_native_text_input_bridge.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/text_field/text_field_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_TextInput()
{
    return new OHOS::Ace::TextInputDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUITextInputModifier* GetTextInputDynamicModifier();
const CJUITextInputModifier* GetCJUITextInputDynamicModifier();
}

#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUITextInputModifier* GetTextInputStaticModifier();
} // namespace GeneratedModifier
#endif
} // namespace NG

void TextInputDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::TextInputBridge::RegisterTextInputAttributes(object, vm);
}

const void* TextInputDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetTextInputDynamicModifier();
}

const void* TextInputDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetTextInputStaticModifier();
#else
    return nullptr;
#endif
}

const void* TextInputDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUITextInputDynamicModifier();
}

void* TextInputDynamicModule::GetModel()
{
    static NG::TextFieldModelNG model;
    return &model;
}

const void* TextInputDynamicModule::GetCustomModifier(const std::string& name)
{
    return nullptr;
}

} // namespace OHOS::Ace