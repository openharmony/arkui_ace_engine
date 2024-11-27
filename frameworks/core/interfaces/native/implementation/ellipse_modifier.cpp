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
#include "core/interfaces/native/utility/converter.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
struct EllipseOptions {
    std::optional<Dimension> width;
    std::optional<Dimension> height;
};

template<>
inline EllipseOptions Convert(const Ark_Literal_Union_String_Number_height_width& src)
{
    EllipseOptions ellipseOptions;
    ellipseOptions.width = Converter::OptConvert<Dimension>(src.width);
    ellipseOptions.height = Converter::OptConvert<Dimension>(src.height);
    return ellipseOptions;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace EllipseInterfaceModifier {
void SetEllipseOptionsImpl(Ark_NativePointer node,
                           const Opt_Literal_Union_String_Number_height_width* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto options = value ? Converter::OptConvert<Converter::EllipseOptions>(*value) : std::nullopt;
    
    if (options && options->width) {
        ShapeAbstractModelNG::SetWidth(frameNode, *options->width);
    }
    if (options && options->height) {
        ShapeAbstractModelNG::SetHeight(frameNode, *options->height);
    }
}
} // EllipseInterfaceModifier
const GENERATED_ArkUIEllipseModifier* GetEllipseModifier()
{
    static const GENERATED_ArkUIEllipseModifier ArkUIEllipseModifierImpl {
        EllipseInterfaceModifier::SetEllipseOptionsImpl,
    };
    return &ArkUIEllipseModifierImpl;
}

}
