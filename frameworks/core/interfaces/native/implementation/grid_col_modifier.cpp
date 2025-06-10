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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/grid_col/grid_col_model_ng.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
namespace Converter {
    template<>
    V2::GridContainerSize Convert(const Ark_GridColColumnOption& value)
    {
        V2::GridContainerSize toValue;
        toValue.lg = Converter::OptConvert<int32_t>(value.lg).value();
        toValue.md = Converter::OptConvert<int32_t>(value.md).value();
        toValue.sm = Converter::OptConvert<int32_t>(value.sm).value();
        toValue.xl = Converter::OptConvert<int32_t>(value.xl).value();
        toValue.xs = Converter::OptConvert<int32_t>(value.xs).value();
        toValue.xxl = Converter::OptConvert<int32_t>(value.xxl).value();
        return toValue;
    }
    template<>
    V2::GridContainerSize Convert(const Ark_Number& value)
    {
        V2::GridContainerSize toValue;
        int32_t iValue = Converter::Convert<int32_t>(value);
        toValue.lg = iValue;
        toValue.md = iValue;
        toValue.sm = iValue;
        toValue.xl = iValue;
        toValue.xs = iValue;
        toValue.xxl = iValue;
        return toValue;
    }
} // namespace Converter
} // namespace OHOS::Ace::NG
namespace OHOS::Ace::NG::GeneratedModifier {
namespace GridColModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = GridColModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // GridColModifier
namespace GridColInterfaceModifier {
void SetGridColOptionsImpl(Ark_NativePointer node,
                           const Opt_GridColOptions* option)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<V2::GridContainerSize> gcSizeValue {std::nullopt};
    bool reset {false};
    if (option) {
        auto optGridColOptions = Converter::OptConvert<Ark_GridColOptions>(*option);
        if (optGridColOptions) {
            Ark_GridColOptions arkGridColOptions = optGridColOptions.value();
            gcSizeValue = Converter::OptConvert<V2::GridContainerSize>(arkGridColOptions.span);
            Validator::ValidateNonNegative(gcSizeValue);
            GridColModelNG::SetSpan(frameNode, gcSizeValue);
            gcSizeValue = Converter::OptConvert<V2::GridContainerSize>(arkGridColOptions.offset);
            Validator::ValidateNonNegative(gcSizeValue);
            GridColModelNG::SetOffset(frameNode, gcSizeValue);
            gcSizeValue = Converter::OptConvert<V2::GridContainerSize>(arkGridColOptions.order);
            Validator::ValidateNonNegative(gcSizeValue);
            GridColModelNG::SetOrder(frameNode, gcSizeValue);
        } else {
            reset = true;
        }
    } else {
        reset = true;
    }
    if (reset) {
        GridColModelNG::SetSpan(frameNode, std::nullopt);
        GridColModelNG::SetOffset(frameNode, std::nullopt);
        GridColModelNG::SetOrder(frameNode, std::nullopt);
    }
}
} // GridColInterfaceModifier
namespace GridColAttributeModifier {
void SpanImpl(Ark_NativePointer node,
              const Ark_Union_Number_GridColColumnOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::optional<V2::GridContainerSize> gcSizeValue {std::nullopt};
    if (value) {
        gcSizeValue = Converter::OptConvert<V2::GridContainerSize>(*value);
        Validator::ValidateNonNegative(gcSizeValue);
        GridColModelNG::SetSpan(frameNode, gcSizeValue);
    } else {
        GridColModelNG::SetSpan(frameNode, std::nullopt);
    }
}
void GridColOffsetImpl(Ark_NativePointer node,
                       const Ark_Union_Number_GridColColumnOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value) {
        auto gcSizeValue = Converter::OptConvert<V2::GridContainerSize>(*value);
        CHECK_NULL_VOID(gcSizeValue);
        Validator::ValidateNonNegative(gcSizeValue);
        GridColModelNG::SetOffset(frameNode, gcSizeValue);
    } else {
        GridColModelNG::SetOffset(frameNode, std::nullopt);
    }
}
void OrderImpl(Ark_NativePointer node,
               const Ark_Union_Number_GridColColumnOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value) {
        auto gcSizeValue = Converter::OptConvert<V2::GridContainerSize>(*value);
        CHECK_NULL_VOID(gcSizeValue);
        Validator::ValidateNonNegative(gcSizeValue);
        GridColModelNG::SetOrder(frameNode, gcSizeValue);
    } else {
        GridColModelNG::SetOrder(frameNode, std::nullopt);
    }
}
} // GridColAttributeModifier
const GENERATED_ArkUIGridColModifier* GetGridColModifier()
{
    static const GENERATED_ArkUIGridColModifier ArkUIGridColModifierImpl {
        GridColModifier::ConstructImpl,
        GridColInterfaceModifier::SetGridColOptionsImpl,
        GridColAttributeModifier::SpanImpl,
        GridColAttributeModifier::GridColOffsetImpl,
        GridColAttributeModifier::OrderImpl,
    };
    return &ArkUIGridColModifierImpl;
}

}
