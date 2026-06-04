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

#include "core/components_ng/pattern/text_picker/bridge/textpicker_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/text_picker/bridge/arkts_native_textpicker_bridge.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/text_picker/textpicker_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_TextPicker()
{
    return new OHOS::Ace::TextPickerDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUITextPickerModifier* GetTextPickerDynamicModifier();
const CJUITextPickerModifier* GetCJUITextPickerModifier();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUITextPickerModifier* GetTextPickerStaticModifier();
} // namespace GeneratedModifier
#endif
} // namespace NG

void TextPickerDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::TextPickerBridge::RegisterTextPickerAttributes(object, vm);
}

const void* TextPickerDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetTextPickerDynamicModifier();
}

const void* TextPickerDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetTextPickerStaticModifier();
#else
    return nullptr;
#endif
}

const void* TextPickerDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUITextPickerModifier();
}

void* TextPickerDynamicModule::GetModel()
{
    static NG::TextPickerModelNG model;
    return &model;
}

const void* TextPickerDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == "customModifier") {
        return NG::TextPickerUtil::GetTextPickerCustomModifier();
    }
    return nullptr;
}

} // namespace OHOS::Ace
