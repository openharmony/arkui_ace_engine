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

#include "core/interfaces/native/node/node_api.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/interfaces/arkoala/utility/validators.h"

namespace OHOS::Ace::NG {
namespace {
struct RowOptions {
    std::optional<Dimension> space;
};

struct PointLightStyle {
    std::optional<uint32_t> illuminated;
    std::optional<float_t> bloom;
    std::optional<float_t> x;
    std::optional<float_t> y;
    std::optional<float_t> z;
    std::optional<float_t> intensity;
    std::optional<Color> color;
};
}

namespace Converter {
template<>
void AssignCast(std::optional<FlexAlign>& dst, const Ark_VerticalAlign& src)
{
    switch (src) {
        case ARK_VERTICAL_ALIGN_TOP: dst = FlexAlign::FLEX_START; break;
        case ARK_VERTICAL_ALIGN_CENTER: dst = FlexAlign::CENTER; break;
        case ARK_VERTICAL_ALIGN_BOTTOM: dst = FlexAlign::FLEX_END; break;
        default: LOGE("Unexpected enum value in Ark_VerticalAlign: %{public}d", src);
    }
}

template<>
RowOptions Convert(const Ark_RowOptions& src)
{
    return {
        .space = OptConvert<Dimension>(src.space),
    };
}

template<>
PointLightStyle Convert(const Ark_PointLightStyle& src)
{
    PointLightStyle options;
    options.bloom = (float)Converter::ConvertOrDefault(src.bloom, 0);
    options.illuminated = (uint32_t)Converter::ConvertOrDefault(src.illuminated, 0);
    Ark_LightSource lightSource = src.lightSource.value;
    options.x = Converter::OptConvert<float_t>(lightSource.positionX.value);
    options.y = Converter::OptConvert<float_t>(lightSource.positionY.value);
    options.z = Converter::OptConvert<float_t>(lightSource.positionZ.value);
    options.intensity = (float)Converter::ConvertOrDefault(lightSource.intensity, 0);
    options.color = Converter::OptConvert<Color>(lightSource.color);
    return options;
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
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
    auto pointLightStyle = Converter::Convert<PointLightStyle>(*value);
    RowModelNG::SetPointLightBloom(frameNode, pointLightStyle.bloom);
    RowModelNG::SetPointLightIlluminated(frameNode, pointLightStyle.illuminated);
    RowModelNG::SetPointLightSourcePosition(frameNode, pointLightStyle.x, pointLightStyle.y, pointLightStyle.z);
    RowModelNG::SetPointLightSourceIntensity(frameNode, pointLightStyle.intensity);
    RowModelNG::SetPointLightSourceColor(frameNode, pointLightStyle.color);
}
void ReverseImpl(Ark_NativePointer node,
                 const Ark_Union_Boolean_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RowModelNG::SetIsReverse(frameNode, value ? Converter::OptConvert<bool>(*value) : std::nullopt);
}
} // RowAttributeModifier
const GENERATED_ArkUIRowModifier* GetRowModifier()
{
    static const GENERATED_ArkUIRowModifier ArkUIRowModifierImpl {
        RowInterfaceModifier::SetRowOptionsImpl,
        RowAttributeModifier::AlignItemsImpl,
        RowAttributeModifier::JustifyContentImpl,
        RowAttributeModifier::PointLightImpl,
        RowAttributeModifier::ReverseImpl,
    };
    return &ArkUIRowModifierImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
