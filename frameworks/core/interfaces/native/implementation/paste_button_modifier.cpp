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
namespace PasteButtonModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // PasteButtonModifier
namespace PasteButtonInterfaceModifier {
void SetPasteButtonOptions0Impl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //PasteButtonModelNG::SetSetPasteButtonOptions0(frameNode, convValue);
}
void SetPasteButtonOptions1Impl(Ark_NativePointer node,
                                const Ark_PasteButtonOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    //auto convValue = Converter::OptConvert<type_name>(*options);
    //PasteButtonModelNG::SetSetPasteButtonOptions1(frameNode, convValue);
}
} // PasteButtonInterfaceModifier
namespace PasteButtonAttributeModifier {
void OnClickImpl(Ark_NativePointer node,
                 const Callback_ClickEvent_PasteButtonOnClickResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PasteButtonModelNG::SetOnClick(frameNode, convValue);
}
} // PasteButtonAttributeModifier
const GENERATED_ArkUIPasteButtonModifier* GetPasteButtonModifier()
{
    static const GENERATED_ArkUIPasteButtonModifier ArkUIPasteButtonModifierImpl {
        PasteButtonModifier::ConstructImpl,
        PasteButtonInterfaceModifier::SetPasteButtonOptions0Impl,
        PasteButtonInterfaceModifier::SetPasteButtonOptions1Impl,
        PasteButtonAttributeModifier::OnClickImpl,
    };
    return &ArkUIPasteButtonModifierImpl;
}

}
