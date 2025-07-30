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
#include "core/components_ng/pattern/linear_layout/row_model_ng_static.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_abstract_model_static.h"

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
void SetRowOptions0Impl(Ark_NativePointer node,
                        const Opt_RowOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto opts = Converter::OptConvert<RowOptions>(*options);
    auto space = opts ? opts->space : std::nullopt;
    RowModelNG::SetSpace(frameNode, space.value_or(0.0_px));
}
void SetRowOptions1Impl(Ark_NativePointer node,
                        const Opt_Union_RowOptions_RowOptionsV2* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkUnion = options ? Converter::GetOpt(*options) : std::nullopt;
    if (!arkUnion.has_value()) {
        //RowModelNG::SetSpace(frameNode, Dimension());
        return;
    }
    Converter::VisitUnion(arkUnion.value(),
        [frameNode](const Ark_RowOptions& value) {
        },
        [frameNode](const Ark_RowOptionsV2& value) {
            LOGE("ARKOALA RowInterfaceModifier::SetRowOptions1Impl  Ark_RowOptionsV2 is not implemented.");
        },
        []() {}
    );
}
} // RowInterfaceModifier
namespace RowAttributeModifier {
void AlignItemsImpl(Ark_NativePointer node,
                    const Opt_VerticalAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto flexAlign = Converter::OptConvert<FlexAlign>(*value);
    RowModelNGStatic::SetAlignItems(frameNode, flexAlign);
}
void JustifyContentImpl(Ark_NativePointer node,
                        const Opt_FlexAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto flexAlign = Converter::OptConvert<FlexAlign>(*value);
    RowModelNGStatic::SetJustifyContent(frameNode, flexAlign);
}
void PointLightImpl(Ark_NativePointer node,
                    const Opt_PointLightStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef POINT_LIGHT_ENABLE
    auto pointLightStyle = Converter::OptConvert<Converter::PointLightStyle>(*value);
    auto uiNode = reinterpret_cast<Ark_NodeHandle>(node);
    auto themeConstants = Converter::GetThemeConstants(uiNode, "", "");
    CHECK_NULL_VOID(themeConstants);
    if (pointLightStyle) {
        if (pointLightStyle->lightSource) {
            ViewAbstractModelStatic::SetLightPosition(frameNode, pointLightStyle->lightSource->x,
                pointLightStyle->lightSource->y,
                pointLightStyle->lightSource->z);
            ViewAbstractModelStatic::SetLightIntensity(frameNode,
                pointLightStyle->lightSource->intensity);
            ViewAbstractModelStatic::SetLightColor(frameNode, pointLightStyle->lightSource->lightColor);
        } else {
            ViewAbstractModelStatic::SetLightPosition(frameNode, std::nullopt, std::nullopt, std::nullopt);
            ViewAbstractModelStatic::SetLightIntensity(frameNode, std::nullopt);
            ViewAbstractModelStatic::SetLightColor(frameNode, std::nullopt);
        }
        // illuminated
        ViewAbstractModelStatic::SetLightIlluminated(frameNode, pointLightStyle->illuminationType, themeConstants);
        // bloom
        ViewAbstractModelStatic::SetBloom(frameNode, pointLightStyle->bloom, themeConstants);
    } else {
        ViewAbstractModelStatic::SetLightPosition(frameNode, std::nullopt, std::nullopt, std::nullopt);
        ViewAbstractModelStatic::SetLightIntensity(frameNode, std::nullopt);
        ViewAbstractModelStatic::SetLightColor(frameNode, std::nullopt);
        ViewAbstractModelStatic::SetLightIlluminated(frameNode, std::nullopt, themeConstants);
        ViewAbstractModelStatic::SetBloom(frameNode, std::nullopt, themeConstants);
    }
#endif
}
void ReverseImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RowModelNGStatic::SetIsReverse(frameNode, value ? Converter::OptConvert<bool>(*value) : std::nullopt);
}
} // RowAttributeModifier
const GENERATED_ArkUIRowModifier* GetRowModifier()
{
    static const GENERATED_ArkUIRowModifier ArkUIRowModifierImpl {
        RowModifier::ConstructImpl,
        RowInterfaceModifier::SetRowOptions0Impl,
        RowInterfaceModifier::SetRowOptions1Impl,
        RowAttributeModifier::AlignItemsImpl,
        RowAttributeModifier::JustifyContentImpl,
        RowAttributeModifier::PointLightImpl,
        RowAttributeModifier::ReverseImpl,
    };
    return &ArkUIRowModifierImpl;
}

}
