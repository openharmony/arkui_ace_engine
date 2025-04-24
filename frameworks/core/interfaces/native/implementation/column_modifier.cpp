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

#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/ace_engine_types.h"


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

template<>
void AssignCast(std::optional<FlexAlign>& dst, const Ark_HorizontalAlign& src)
{
    switch (src) {
        case ARK_HORIZONTAL_ALIGN_START: dst = FlexAlign::FLEX_START; break;
        case ARK_HORIZONTAL_ALIGN_CENTER: dst = FlexAlign::CENTER; break;
        case ARK_HORIZONTAL_ALIGN_END: dst = FlexAlign::FLEX_END; break;
        default: LOGE("Unexpected enum value in Ark_HorizontalAlign: %{public}d", src);
    }
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ColumnModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id, Ark_Int32 flags)
{
    auto frameNode = ColumnModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    // auto layout = frameNode->GetLayoutProperty();
    // NG::CalcLength len = NG::CalcLength(100);
    // layout->UpdateUserDefinedIdealSize(NG::CalcSize(len, len));
    return AceType::RawPtr(frameNode);
}
} // namespace ColumnModifier
namespace ColumnInterfaceModifier {
void SetColumnOptions0Impl(Ark_NativePointer node,
                           const Opt_ColumnOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    if(options->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ColumnModelNG::SetSpace(frameNode, std::optional<Dimension>(0));
        return;
    }
    auto opts = Converter::OptConvert<ColumnOptions>(*options);
    if (opts) {
        ColumnModelNG::SetSpace(frameNode, opts->space);
    }
}
void SetColumnOptions1Impl(Ark_NativePointer node,
                           const Opt_Union_ColumnOptions_ColumnOptionsV2* options)
{
}
} // ColumnInterfaceModifier
namespace ColumnAttributeModifier {
void AlignItemsImpl(Ark_NativePointer node,
                    const Opt_HorizontalAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if(value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ColumnModelNG::SetAlignItems(frameNode, std::make_optional<FlexAlign>(FlexAlign::CENTER));
        return;
    }
    ColumnModelNG::SetAlignItems(frameNode, Converter::OptConvert<FlexAlign>(value->value));
    
}
void JustifyContentImpl(Ark_NativePointer node,
                        const Opt_FlexAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if(value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ColumnModelNG::SetJustifyContent(frameNode, std::make_optional<FlexAlign>(FlexAlign::FLEX_START));
        return;
    }
    ColumnModelNG::SetJustifyContent(frameNode, Converter::OptConvert<FlexAlign>(value->value));
}
void PointLightImpl(Ark_NativePointer node,
                    const Opt_PointLightStyle* value)
{
}
void ReverseImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if(value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ColumnModelNG::SetIsReverse(frameNode, false);
        return;
    }
    if (value) {
        if (auto reversed = Converter::OptConvert<bool>(*value); reversed) {
            ColumnModelNG::SetIsReverse(frameNode, *reversed);
        }
    }
    // auto reverse = Converter::OptConvert<bool>(*value);
    
}
} // ColumnAttributeModifier
const GENERATED_ArkUIColumnModifier* GetColumnModifier()
{
    static const GENERATED_ArkUIColumnModifier ArkUIColumnModifierImpl {
        ColumnModifier::ConstructImpl,
        ColumnInterfaceModifier::SetColumnOptions0Impl,
        ColumnInterfaceModifier::SetColumnOptions1Impl,
        ColumnAttributeModifier::AlignItemsImpl,
        ColumnAttributeModifier::JustifyContentImpl,
        ColumnAttributeModifier::PointLightImpl,
        ColumnAttributeModifier::ReverseImpl,
    };
    return &ArkUIColumnModifierImpl;
}

}
