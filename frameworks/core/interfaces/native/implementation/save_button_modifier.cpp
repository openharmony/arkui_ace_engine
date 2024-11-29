/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SaveButtonModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // SaveButtonModifier
namespace SaveButtonInterfaceModifier {
void SetSaveButtonOptions0Impl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //SaveButtonModelNG::SetSetSaveButtonOptions0(frameNode, convValue);
}
void SetSaveButtonOptions1Impl(Ark_NativePointer node,
                               const Ark_SaveButtonOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    //auto convValue = Converter::OptConvert<type_name>(*options);
    //SaveButtonModelNG::SetSetSaveButtonOptions1(frameNode, convValue);
}
} // SaveButtonInterfaceModifier
namespace SaveButtonAttributeModifier {
void OnClickImpl(Ark_NativePointer node,
                 const Callback_ClickEvent_SaveButtonOnClickResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SaveButtonModelNG::SetOnClick(frameNode, convValue);
}
} // SaveButtonAttributeModifier
const GENERATED_ArkUISaveButtonModifier* GetSaveButtonModifier()
{
    static const GENERATED_ArkUISaveButtonModifier ArkUISaveButtonModifierImpl {
        SaveButtonModifier::ConstructImpl,
        SaveButtonInterfaceModifier::SetSaveButtonOptions0Impl,
        SaveButtonInterfaceModifier::SetSaveButtonOptions1Impl,
        SaveButtonAttributeModifier::OnClickImpl,
    };
    return &ArkUISaveButtonModifierImpl;
}

}
