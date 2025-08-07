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

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/components_ng/pattern/flex/flex_model_ng.h"
#include "core/components_ng/pattern/flex/flex_model_ng_static.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_abstract_model_static.h"

namespace OHOS::Ace::NG {

constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;

struct FlexOptions {
    std::optional<FlexDirection> direction;
    std::optional<FlexWrap> wrap;
    std::optional<FlexAlign> align;
    std::optional<WrapAlignment> wrapAlignment;
    std::optional<FlexAlign> alignItems;
    std::optional<WrapAlignment> wrapAlignItems;
    std::optional<WrapAlignment> alignContent;
    std::optional<Dimension> crossSpace;
    std::optional<Dimension> mainSpace;
};
} // OHOS::Ace::NG

namespace OHOS::Ace::NG {
namespace Converter {

template<>
void AssignCast(std::optional<FlexWrap>& dst, const Ark_FlexWrap& src)
{
    switch (src) {
        case ARK_FLEX_WRAP_NO_WRAP: dst = FlexWrap::NO_WRAP; break;
        case ARK_FLEX_WRAP_WRAP: dst = FlexWrap::WRAP; break;
        case ARK_FLEX_WRAP_WRAP_REVERSE: dst = FlexWrap::WRAP_REVERSE; break;
        default: LOGE("Unexpected enum value in Ark_FlexWrap: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<WrapAlignment>& dst, const Ark_FlexAlign& src)
{
    switch (src) {
        case ARK_FLEX_ALIGN_START: dst = WrapAlignment::START; break;
        case ARK_FLEX_ALIGN_CENTER: dst = WrapAlignment::CENTER; break;
        case ARK_FLEX_ALIGN_END: dst = WrapAlignment::END; break;
        case ARK_FLEX_ALIGN_SPACE_BETWEEN: dst = WrapAlignment::SPACE_BETWEEN; break;
        case ARK_FLEX_ALIGN_SPACE_AROUND: dst = WrapAlignment::SPACE_AROUND; break;
        case ARK_FLEX_ALIGN_SPACE_EVENLY: dst = WrapAlignment::SPACE_EVENLY; break;
        default: LOGE("Unexpected enum value in Ark_FlexAlign: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<WrapAlignment>& dst, const Ark_ItemAlign& src)
{
    switch (src) {
        case ARK_ITEM_ALIGN_AUTO: dst = WrapAlignment::START; break;
        case ARK_ITEM_ALIGN_START: dst = WrapAlignment::START; break;
        case ARK_ITEM_ALIGN_CENTER: dst = WrapAlignment::CENTER; break;
        case ARK_ITEM_ALIGN_END: dst = WrapAlignment::END; break;
        case ARK_ITEM_ALIGN_BASELINE: dst = WrapAlignment::BASELINE; break;
        case ARK_ITEM_ALIGN_STRETCH: dst = WrapAlignment::STRETCH; break;
        default: LOGE("Unexpected enum value in Ark_ItemAlign: %{public}d", src);
    }
}

} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
template<>
FlexOptions Convert(
    const Ark_FlexOptions& src)
{
    FlexOptions flexOptions;
    flexOptions.direction = Converter::OptConvert<FlexDirection>(src.direction);
    flexOptions.wrap = Converter::OptConvert<FlexWrap>(src.wrap);
    if (src.wrap.value != Ark_FlexWrap::ARK_FLEX_WRAP_NO_WRAP) {
        flexOptions.wrapAlignment = Converter::OptConvert<WrapAlignment>(src.justifyContent);
        flexOptions.wrapAlignItems = Converter::OptConvert<WrapAlignment>(src.alignItems);
        flexOptions.alignContent = Converter::OptConvert<WrapAlignment>(src.alignContent);
    } else {
        flexOptions.align = Converter::OptConvert<FlexAlign>(src.justifyContent);
        flexOptions.alignItems = Converter::OptConvert<FlexAlign>(src.alignItems);
    }

    auto space = Converter::OptConvert<Ark_FlexSpaceOptions>(src.space);
    if (space) {
        flexOptions.crossSpace = Converter::OptConvert<Dimension>(space.value().cross);
        flexOptions.mainSpace = Converter::OptConvert<Dimension>(space.value().main);
    }
    return flexOptions;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace FlexModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = FlexModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // FlexModifier
namespace FlexInterfaceModifier {
void SetFlexOptionsImpl(Ark_NativePointer node,
                        const Opt_FlexOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::OptConvert<FlexOptions>(*value);
    CHECK_NULL_VOID(options);

    if (!options->wrap.has_value() || options->wrap.value() == FlexWrap::NO_WRAP) {
        FlexModelNG::SetFlexRow(frameNode);
        FlexModelNGStatic::SetFlexDirection(frameNode, options->direction);
        FlexModelNGStatic::SetMainAxisAlign(frameNode, options->align);
        FlexModelNGStatic::SetCrossAxisAlign(frameNode, options->alignItems);
    } else if (options->wrap.value() == FlexWrap::WRAP || options->wrap.value() == FlexWrap::WRAP_REVERSE) {
        FlexModelNG::SetFlexWrap(frameNode);
        int32_t wrap = static_cast<int32_t>(options->wrap.value());
        if (options->direction.has_value()) {
            int32_t direction = static_cast<int32_t>(options->direction.value());
            FlexModelNGStatic::SetFlexDirection(frameNode, options->direction);
            // WrapReverse means wrapVal = 2. Wrap means wrapVal = 1.
            direction <= 1 ? direction += NUM_2 * (wrap - NUM_1) : direction -= NUM_2 * (wrap - NUM_1);
            FlexModelNG::SetFlexWrapDirection(frameNode, static_cast<WrapDirection>(direction));
        } else {
            // No direction set case: wrapVal == 2 means FlexWrap.WrapReverse.
            WrapDirection wrapDirection = wrap == NUM_2 ?
             WrapDirection::HORIZONTAL_REVERSE : WrapDirection::HORIZONTAL;
            FlexModelNG::SetFlexWrapDirection(frameNode, wrapDirection);
        }
        FlexModelNGStatic::SetWrapMainAlignment(frameNode, options->wrapAlignment);
        FlexModelNGStatic::SetWrapCrossAlignment(frameNode, options->wrapAlignItems);
        FlexModelNGStatic::SetFlexAlignContent(frameNode, options->alignContent);
        if (options->crossSpace) {
            FlexModelNG::SetCrossSpace(frameNode, options->crossSpace);
        }
    }
    if (options->mainSpace) {
        FlexModelNG::SetMainSpace(frameNode, options->mainSpace);
    }
}
} // FlexInterfaceModifier
namespace FlexAttributeModifier {
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
} // FlexAttributeModifier
const GENERATED_ArkUIFlexModifier* GetFlexModifier()
{
    static const GENERATED_ArkUIFlexModifier ArkUIFlexModifierImpl {
        FlexModifier::ConstructImpl,
        FlexInterfaceModifier::SetFlexOptionsImpl,
        FlexAttributeModifier::PointLightImpl,
    };
    return &ArkUIFlexModifierImpl;
}

}
