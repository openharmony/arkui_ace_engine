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
#include "core/components_ng/pattern/shape/ellipse_model_ng.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
struct EllipseOptions {
    std::optional<Dimension> width;
    std::optional<Dimension> height;
};

template<>
inline EllipseOptions Convert(const Ark_EllipseOptions& src)
{
    EllipseOptions ellipseOptions;
    ellipseOptions.width = Converter::OptConvert<Dimension>(src.width);
    ellipseOptions.height = Converter::OptConvert<Dimension>(src.height);
    return ellipseOptions;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace EllipseModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    // auto frameNode = EllipseModelNG::CreateFrameNode(id);
    // CHECK_NULL_RETURN(frameNode, nullptr);
    // frameNode->IncRefCount();
    // return AceType::RawPtr(frameNode);
    return nullptr;
}
} // EllipseModifier
namespace EllipseInterfaceModifier {
void SetEllipseOptionsImpl(Ark_NativePointer node,
                           const Opt_EllipseOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto opt = options ? Converter::OptConvert<Converter::EllipseOptions>(*options) : std::nullopt;

    if (opt && opt->width) {
        ShapeAbstractModelNG::SetWidth(frameNode, *opt->width);
    }
    if (opt && opt->height) {
        ShapeAbstractModelNG::SetHeight(frameNode, *opt->height);
    }
}
} // EllipseInterfaceModifier
const GENERATED_ArkUIEllipseModifier* GetEllipseModifier()
{
    static const GENERATED_ArkUIEllipseModifier ArkUIEllipseModifierImpl {
        EllipseModifier::ConstructImpl,
        EllipseInterfaceModifier::SetEllipseOptionsImpl,
    };
    return &ArkUIEllipseModifierImpl;
}

}
