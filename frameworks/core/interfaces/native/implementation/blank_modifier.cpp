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

#include "base/log/log_wrapper.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace BlankModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = BlankModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // BlankModifier
namespace BlankInterfaceModifier {
void SetBlankOptionsImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String* min)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto minDim = Converter::OptConvert<Dimension>(*min);
    Validator::ValidateNonNegative(minDim);
    Validator::ValidateNonPercent(minDim);
    BlankModelNG::SetBlankMin(frameNode, minDim.value_or(0.0_px));
}
} // BlankInterfaceModifier

namespace BlankAttributeModifier {
void ColorImpl(Ark_NativePointer node,
               const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto color = Converter::OptConvert<Color>(*value);
    if (color) {
        BlankModelNG::SetColor(frameNode, color.value());
    } else {
        LOGI("#### BlankAttribute::ColorImpl: color is empty");
    }
}
} // BlankAttributeModifier

const GENERATED_ArkUIBlankModifier* GetBlankModifier()
{
    static const GENERATED_ArkUIBlankModifier ArkUIBlankModifierImpl {
        BlankModifier::ConstructImpl,
        BlankInterfaceModifier::SetBlankOptionsImpl,
        BlankAttributeModifier::ColorImpl,
    };
    return &ArkUIBlankModifierImpl;
}

}
