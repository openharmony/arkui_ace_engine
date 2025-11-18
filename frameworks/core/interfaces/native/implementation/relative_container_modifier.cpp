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

#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/relative_container/relative_container_model_ng.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG::Converter {

template<>
void AssignCast(std::optional<BarrierDirection>& dst, const Ark_BarrierDirection& src)
{
    switch (src) {
        case ARK_BARRIER_DIRECTION_LEFT: dst = BarrierDirection::LEFT; break;
        case ARK_BARRIER_DIRECTION_RIGHT: dst = BarrierDirection::RIGHT; break;
        case ARK_BARRIER_DIRECTION_TOP: dst = BarrierDirection::TOP; break;
        case ARK_BARRIER_DIRECTION_BOTTOM: dst = BarrierDirection::BOTTOM; break;
        default: LOGE("Unexpected enum value in Ark_BarrierDirection: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<BarrierDirection>& dst, const Ark_LocalizedBarrierDirection& src)
{
    switch (src) {
        case ARK_LOCALIZED_BARRIER_DIRECTION_START: dst = BarrierDirection::START; break;
        case ARK_LOCALIZED_BARRIER_DIRECTION_END: dst = BarrierDirection::END; break;
        case ARK_LOCALIZED_BARRIER_DIRECTION_TOP: dst = BarrierDirection::TOP; break;
        case ARK_LOCALIZED_BARRIER_DIRECTION_BOTTOM: dst = BarrierDirection::BOTTOM; break;
        default: LOGE("Unexpected enum value in Ark_BarrierDirection: %{public}d", src);
    }
}

template<>
GuidelineInfo Convert(const Ark_GuideLineStyle& src)
{
    GuidelineInfo info;
    info.id = Convert<std::string>(src.id);
    auto direction = OptConvert<LineDirection>(src.direction);
    if (direction.has_value()) {
        info.direction = direction.value();
    }
    auto start = OptConvert<Dimension>(src.position.start);
    if (start.has_value()) {
        info.start = start.value();
    }
    auto end = OptConvert<Dimension>(src.position.end);
    if (end.has_value()) {
        info.end = end.value();
    }
    return info;
}

template<>
BarrierInfo Convert(const Ark_BarrierStyle& src)
{
    BarrierInfo info = {
        .id = Convert<std::string>(src.id),
        .referencedId = Convert<std::vector<std::string>>(src.referencedId)
    };
    auto direction = OptConvert<BarrierDirection>(src.direction);
    if (direction.has_value()) {
        info.direction = direction.value();
    }
    return info;
}

template<>
BarrierInfo Convert(const Ark_LocalizedBarrierStyle& src)
{
    BarrierInfo info = {
        .id = Converter::Convert<std::string>(src.id),
        .referencedId = Converter::Convert<std::vector<std::string>>(src.referencedId)
    };
    auto direction = OptConvert<BarrierDirection>(src.localizedDirection);
    if (direction.has_value()) {
        info.direction = direction.value();
    }
    return info;
}
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RelativeContainerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = RelativeContainerModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // RelativeContainerModifier
namespace RelativeContainerInterfaceModifier {
void SetRelativeContainerOptionsImpl(Ark_NativePointer node)
{
    // keep it empty because RelativeContainer doesn`t have any options
}
} // RelativeContainerInterfaceModifier
namespace RelativeContainerAttributeModifier {
void SetGuideLineImpl(Ark_NativePointer node,
                      const Opt_Array_GuideLineStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::vector<GuidelineInfo>>(*value);
    if (!convValue) {
        std::vector<GuidelineInfo> emptyVector;
        RelativeContainerModelNG::SetGuideline(frameNode, emptyVector);
        return;
    }
    RelativeContainerModelNG::SetGuideline(frameNode, *convValue);
}
void SetBarrierImpl(Ark_NativePointer node,
                    const Opt_Union_Array_BarrierStyle_Array_LocalizedBarrierStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<std::vector<BarrierInfo>>(*value) : std::nullopt;
    if (!convValue) {
        std::vector<BarrierInfo> emptyVector;
        RelativeContainerModelNG::SetBarrier(frameNode, emptyVector);
        return;
    }
    RelativeContainerModelNG::SetBarrier(frameNode, *convValue);
}
} // RelativeContainerAttributeModifier
const GENERATED_ArkUIRelativeContainerModifier* GetRelativeContainerModifier()
{
    static const GENERATED_ArkUIRelativeContainerModifier ArkUIRelativeContainerModifierImpl {
        RelativeContainerModifier::ConstructImpl,
        RelativeContainerInterfaceModifier::SetRelativeContainerOptionsImpl,
        RelativeContainerAttributeModifier::SetGuideLineImpl,
        RelativeContainerAttributeModifier::SetBarrierImpl,
    };
    return &ArkUIRelativeContainerModifierImpl;
}

}
