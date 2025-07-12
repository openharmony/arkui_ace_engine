/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/qrcode/qrcode_model_ng.h"
#include "core/components_ng/pattern/qrcode/qrcode_model_static.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace QRCodeModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = QRCodeModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // QRCodeModifier
namespace QRCodeInterfaceModifier {
void SetQRCodeOptionsImpl(Ark_NativePointer node,
                          const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    QRCodeModelNG::SetQRCodeValue(frameNode, convValue);
}
} // QRCodeInterfaceModifier
namespace QRCodeAttributeModifier {
void ColorImpl(Ark_NativePointer node,
               const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Color>(*value);
    if (!convValue) {
        return;
    }
    QRCodeModelStatic::SetQRCodeColor(frameNode, convValue);
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Color>(*value);
    if (!convValue) {
        return;
    }
    QRCodeModelStatic::SetQRBackgroundColor(frameNode, convValue);
}
void ContentOpacityImpl(Ark_NativePointer node,
                        const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<float>(*value);
    Validator::ValidateOpacity(convValue);
    if (!convValue) {
        return;
    }
    QRCodeModelStatic::SetContentOpacity(frameNode, convValue);
}
} // QRCodeAttributeModifier
const GENERATED_ArkUIQRCodeModifier* GetQRCodeModifier()
{
    static const GENERATED_ArkUIQRCodeModifier ArkUIQRCodeModifierImpl {
        QRCodeModifier::ConstructImpl,
        QRCodeInterfaceModifier::SetQRCodeOptionsImpl,
        QRCodeAttributeModifier::ColorImpl,
        QRCodeAttributeModifier::BackgroundColorImpl,
        QRCodeAttributeModifier::ContentOpacityImpl,
    };
    return &ArkUIQRCodeModifierImpl;
}

}
