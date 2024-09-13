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
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {
namespace {
struct ColumnOptions {
    std::optional<Dimension> space;
};
}

namespace Converter {
template<>
ColumnOptions Convert(const Ark_ColumnOptions& src)
{
    return {
        .space = OptConvert<Dimension>(src.space),
    };
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ColumnInterfaceModifier {
void SetColumnOptionsImpl(Ark_NativePointer node,
                          const Opt_ColumnOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    auto opts = Converter::OptConvert<ColumnOptions>(*options);
    auto space = opts ? opts->space : std::nullopt;
    ColumnModelNG::SetSpace(frameNode, space.value_or(0.0_px));
}
} // ColumnInterfaceModifier
namespace ColumnAttributeModifier {
void AlignItemsImpl(Ark_NativePointer node,
                    Ark_HorizontalAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    ColumnModelNG::SetAlignItems(frameNode, static_cast<FlexAlign>(value + 1));
}
void JustifyContentImpl(Ark_NativePointer node,
                        Ark_FlexAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    ColumnModelNG::SetJustifyContent(frameNode, static_cast<FlexAlign>(value));
}
void PointLightImpl(Ark_NativePointer node,
                    const Ark_PointLightStyle* value)
{
    LOGE("ARKOALA ColumnAttribute_PointLightImpl -> Method is not FULLY "
        "implemented.");
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    ACE_UPDATE_NODE_RENDER_CONTEXT(LightIlluminated,
        (float)Converter::ConvertOrDefault(value->illuminated, 0), frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(Bloom, (float)Converter::ConvertOrDefault(value->bloom, 0), frameNode);
}
void ReverseImpl(Ark_NativePointer node,
                 const Opt_Boolean* isReversed)
{
}
} // ColumnAttributeModifier
const GENERATED_ArkUIColumnModifier* GetColumnModifier()
{
    static const GENERATED_ArkUIColumnModifier ArkUIColumnModifierImpl {
        ColumnInterfaceModifier::SetColumnOptionsImpl,
        ColumnAttributeModifier::AlignItemsImpl,
        ColumnAttributeModifier::JustifyContentImpl,
        ColumnAttributeModifier::PointLightImpl,
        ColumnAttributeModifier::ReverseImpl,
    };
    return &ArkUIColumnModifierImpl;
}

}
