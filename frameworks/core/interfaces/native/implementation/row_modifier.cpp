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

#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/components_ng/base/view_abstract_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
struct RowOptions {
    std::optional<Dimension> space;
};
}

namespace Converter {
template<>
RowOptions Convert(const Ark_RowOptions& src)
{
    return {
        .space = OptConvert<Dimension>(src.space),
    };
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RowModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = RowModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // RowModifier
namespace RowInterfaceModifier {
void SetRowOptionsImpl(Ark_NativePointer node,
                       const Opt_RowOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto opts = Converter::OptConvert<RowOptions>(*options);
    auto space = opts ? opts->space : std::nullopt;
    RowModelNG::SetSpace(frameNode, space.value_or(0.0_px));
}
} // RowInterfaceModifier
namespace RowAttributeModifier {
void AlignItemsImpl(Ark_NativePointer node,
                    Ark_VerticalAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto flexAlign = Converter::OptConvert<FlexAlign>(value);
    RowModelNG::SetAlignItems(frameNode, flexAlign);
}
void JustifyContentImpl(Ark_NativePointer node,
                        Ark_FlexAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto flexAlign = Converter::OptConvert<FlexAlign>(value);
    RowModelNG::SetJustifyContent(frameNode, flexAlign);
}
void PointLightImpl(Ark_NativePointer node,
                    const Ark_PointLightStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
#ifdef POINT_LIGHT_ENABLE
    // auto pointLightStyle = Converter::OptConvert<Converter::PointLightStyle>(*value);
    // auto uiNode = reinterpret_cast<Ark_NodeHandle>(node);
    // auto themeConstants = Converter::GetThemeConstants(uiNode, "", "");
    // CHECK_NULL_VOID(themeConstants);
    // if (pointLightStyle) {
    //     if (pointLightStyle->lightSource) {
    //         ViewAbstractModelNG::SetLightPosition(frameNode, pointLightStyle->lightSource->x,
    //             pointLightStyle->lightSource->y,
    //             pointLightStyle->lightSource->z);
    //         ViewAbstractModelNG::SetLightIntensity(frameNode,
    //             pointLightStyle->lightSource->intensity);
    //         ViewAbstractModelNG::SetLightColor(frameNode, pointLightStyle->lightSource->lightColor);
    //     } else {
    //         ViewAbstractModelNG::SetLightPosition(frameNode, std::nullopt, std::nullopt, std::nullopt);
    //         ViewAbstractModelNG::SetLightIntensity(frameNode, std::nullopt);
    //         ViewAbstractModelNG::SetLightColor(frameNode, std::nullopt);
    //     }
    //     // illuminated
    //     ViewAbstractModelNG::SetLightIlluminated(frameNode, pointLightStyle->illuminationType, themeConstants);
    //     // bloom
    //     ViewAbstractModelNG::SetBloom(frameNode, pointLightStyle->bloom, themeConstants);
    // } else {
    //     ViewAbstractModelNG::SetLightPosition(frameNode, std::nullopt, std::nullopt, std::nullopt);
    //     ViewAbstractModelNG::SetLightIntensity(frameNode, std::nullopt);
    //     ViewAbstractModelNG::SetLightColor(frameNode, std::nullopt);
    //     ViewAbstractModelNG::SetLightIlluminated(frameNode, std::nullopt, themeConstants);
    //     ViewAbstractModelNG::SetBloom(frameNode, std::nullopt, themeConstants);
    // }
#endif
}
void ReverseImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    // RowModelNG::SetIsReverse(frameNode, value ? Converter::OptConvert<bool>(*value) : std::nullopt);
}
} // RowAttributeModifier
const GENERATED_ArkUIRowModifier* GetRowModifier()
{
    static const GENERATED_ArkUIRowModifier ArkUIRowModifierImpl {
        RowModifier::ConstructImpl,
        RowInterfaceModifier::SetRowOptionsImpl,
        RowAttributeModifier::AlignItemsImpl,
        RowAttributeModifier::JustifyContentImpl,
        RowAttributeModifier::PointLightImpl,
        RowAttributeModifier::ReverseImpl,
    };
    return &ArkUIRowModifierImpl;
}

}
