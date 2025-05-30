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
#include "arkoala_api_generated.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/components_ng/pattern/grid_row/grid_row_model_ng.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/components_ng/pattern/grid_row/grid_row_model_ng_static.h"

namespace OHOS::Ace::NG {
    struct GridRowSizeOption {
        std::optional<Dimension> xs;
        std::optional<Dimension> sm;
        std::optional<Dimension> md;
        std::optional<Dimension> lg;
        std::optional<Dimension> xl;
        std::optional<Dimension> xxl;
    };
}
namespace OHOS::Ace::NG::Converter {
    template<>
    GridRowSizeOption Convert(const Ark_Length& value)
    {
        GridRowSizeOption toValue;
        auto optValue = std::optional<Dimension>(Converter::Convert<Dimension>(value));
        toValue.xs = optValue;
        toValue.sm = optValue;
        toValue.md = optValue;
        toValue.lg = optValue;
        toValue.xl = optValue;
        toValue.xxl = optValue;
        return toValue;
    }
    template<>
    GridRowSizeOption Convert(const Ark_GridRowSizeOption& value)
    {
        GridRowSizeOption toValue;
        toValue.xs = Converter::OptConvert<Dimension>(value.xs);
        toValue.sm = Converter::OptConvert<Dimension>(value.sm);
        toValue.md = Converter::OptConvert<Dimension>(value.md);
        toValue.lg = Converter::OptConvert<Dimension>(value.lg);
        toValue.xl = Converter::OptConvert<Dimension>(value.xl);
        toValue.xxl = Converter::OptConvert<Dimension>(value.xxl);
        return toValue;
    }
    template<>
    V2::Gutter Convert(const Ark_Length& value)
    {
        return V2::Gutter(Converter::Convert<Dimension>(value));
    }
    template<>
    V2::Gutter Convert(const Ark_GutterOption& value)
    {
        auto x = Converter::OptConvert<GridRowSizeOption>(value.x);
        auto y = Converter::OptConvert<GridRowSizeOption>(value.y);
        Dimension dimDefault;
        dimDefault.Reset();
        auto toValue {V2::Gutter(dimDefault)};
        if (x.has_value()) {
            auto valueX = x.value();
            toValue.xXs = valueX.xs.has_value() ? valueX.xs.value() : dimDefault;
            toValue.xSm = valueX.sm.has_value() ?  valueX.sm.value() : dimDefault;
            toValue.xMd = valueX.md.has_value() ?  valueX.md.value() : dimDefault;
            toValue.xLg = valueX.lg.has_value() ?  valueX.lg.value() : dimDefault;
            toValue.xXl = valueX.xl.has_value() ?  valueX.xl.value() : dimDefault;
            toValue.xXXl = valueX.xxl.has_value() ?  valueX.xxl.value() : dimDefault;
        }
        if (y.has_value()) {
            auto valueY = y.value();
            toValue.yXs = valueY.xs.has_value() ?  valueY.xs.value() : dimDefault;
            toValue.ySm = valueY.sm.has_value() ?  valueY.sm.value() : dimDefault;
            toValue.yMd = valueY.md.has_value() ?  valueY.md.value() : dimDefault;
            toValue.yLg = valueY.lg.has_value() ?  valueY.lg.value() : dimDefault;
            toValue.yXl = valueY.xl.has_value() ?  valueY.xl.value() : dimDefault;
            toValue.yXXl = valueY.xxl.has_value() ?  valueY.xxl.value() : dimDefault;
        }
        return toValue;
    }
    template<>
    V2::GridRowDirection Convert(const Ark_GridRowDirection& value)
    {
        switch (value) {
            case ARK_GRID_ROW_DIRECTION_ROW:
                return V2::GridRowDirection::Row;
            case ARK_GRID_ROW_DIRECTION_ROW_REVERSE:
                return V2::GridRowDirection::RowReverse;
            default:
                break;
        }
    }
    template<>
    V2::BreakPointsReference Convert(const Ark_BreakpointsReference& value)
    {
        switch (value) {
            case Ark_BreakpointsReference::ARK_BREAKPOINTS_REFERENCE_WINDOW_SIZE:
                return V2::BreakPointsReference::WindowSize;
            case Ark_BreakpointsReference::ARK_BREAKPOINTS_REFERENCE_COMPONENT_SIZE:
                return V2::BreakPointsReference::ComponentSize;
            default:
                break;
        }
    }
    template<>
    V2::BreakPoints Convert(const Ark_BreakPoints& fromValue)
    {
        auto optReference = Converter::OptConvert<V2::BreakPointsReference>(fromValue.reference);
        auto optBreakpoints = Converter::OptConvert<std::vector<std::string>>(fromValue.value);
        V2::BreakPoints toValue;
        if (optReference.has_value()) {
            toValue.reference = optReference.value();
        }
        if (optBreakpoints.has_value()) {
            toValue.breakpoints = optBreakpoints.value();
        }
        return toValue;
    }
    template<>
    V2::GridContainerSize Convert(const Ark_Number& value);
    template<>
    V2::GridContainerSize Convert(const Ark_GridRowColumnOption& value)
    {
        V2::GridContainerSize toValue;
        auto optVal = Converter::OptConvert<int32_t>(value.xs);
        toValue.xs = optVal.has_value() ? optVal.value() : V2::DEFAULT_COLUMN_NUMBER;
        optVal = Converter::OptConvert<int32_t>(value.sm);
        toValue.sm = optVal.has_value() ? optVal.value() : V2::DEFAULT_COLUMN_NUMBER;
        optVal = Converter::OptConvert<int32_t>(value.md);
        toValue.md = optVal.has_value() ? optVal.value() : V2::DEFAULT_COLUMN_NUMBER;
        optVal = Converter::OptConvert<int32_t>(value.lg);
        toValue.lg = optVal.has_value() ? optVal.value() : V2::DEFAULT_COLUMN_NUMBER;
        optVal = Converter::OptConvert<int32_t>(value.xl);
        toValue.xl = optVal.has_value() ? optVal.value() : V2::DEFAULT_COLUMN_NUMBER;
        optVal = Converter::OptConvert<int32_t>(value.xxl);
        toValue.xxl = optVal.has_value() ? optVal.value() : V2::DEFAULT_COLUMN_NUMBER;
        return toValue;
    }
} // Converter
namespace OHOS::Ace::NG::Validator {
    void ValidateNonNegative(std::optional<V2::Gutter>& value)
    {
        if (value.has_value()) {
            auto val = value.value();
            bool fail = val.xLg.IsNegative() || val.yLg.IsNegative()
                || val.xMd.IsNegative() || val.yMd.IsNegative()
                || val.xSm.IsNegative() || val.ySm.IsNegative()
                || val.xXl.IsNegative() || val.yXl.IsNegative()
                || val.xXs.IsNegative() || val.yXs.IsNegative()
                || val.xXXl.IsNegative() || val.yXXl.IsNegative();
            if (fail) {
                value.reset();
            }
        }
    }
}
namespace OHOS::Ace::NG::GeneratedModifier {
namespace GridRowModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = GridRowModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // GridRowModifier
namespace GridRowInterfaceModifier {
void SetGridRowOptionsImpl(Ark_NativePointer node,
                           const Opt_GridRowOptions* option)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = option ? Converter::OptConvert<Ark_GridRowOptions>(*option) : std::nullopt;
    auto nullGutter = Referenced::MakeRefPtr<V2::Gutter>();
    auto nullBreakPoints = Referenced::MakeRefPtr<V2::BreakPoints>();
    auto nullGridContainerSize = Referenced::MakeRefPtr<V2::GridContainerSize>();
    if (convValue.has_value()) {
        auto arkOptions = convValue.value();

        auto optGutter = Converter::OptConvert<V2::Gutter>(arkOptions.gutter);
        Validator::ValidateNonNegative(optGutter);
        auto gutter = optGutter.has_value() ? AceType::MakeRefPtr<V2::Gutter>(optGutter.value()) : nullGutter;
        GridRowModelNG::SetGutter(frameNode, gutter);

        auto optDirection = Converter::OptConvert<V2::GridRowDirection>(arkOptions.direction);
        auto direction = optDirection.has_value() ? optDirection : std::nullopt;
        GridRowModelNGStatic::SetDirection(frameNode, direction);

        auto optBreakPoints = Converter::OptConvert<V2::BreakPoints>(arkOptions.breakpoints);
        auto breakpoints = optBreakPoints.has_value()
            ? AceType::MakeRefPtr<V2::BreakPoints>(optBreakPoints.value()) : nullBreakPoints;
        GridRowModelNG::SetBreakpoints(frameNode, breakpoints);

        auto optColumns = Converter::OptConvert<V2::GridContainerSize>(arkOptions.columns);
        Validator::ValidateNonNegative(optColumns);
        auto columns = optColumns.has_value()
            ? AceType::MakeRefPtr<V2::GridContainerSize>(optColumns.value()) : nullGridContainerSize;
        GridRowModelNG::SetColumns(frameNode, columns);
    } else {
        GridRowModelNG::SetGutter(frameNode, nullGutter);
        GridRowModelNGStatic::SetDirection(frameNode, std::nullopt);
        GridRowModelNG::SetBreakpoints(frameNode, nullBreakPoints);
        GridRowModelNG::SetColumns(frameNode, nullGridContainerSize);
    }
}
} // GridRowInterfaceModifier
namespace GridRowAttributeModifier {
void OnBreakpointChangeImpl(Ark_NativePointer node,
                            const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onBreakpointChange = [arkCallback = CallbackHelper(*optValue)](const std::string& breakpoint) {
        arkCallback.Invoke(Converter::ArkValue<Ark_String>(breakpoint));
    };
    GridRowModelNG::SetOnBreakPointChange(frameNode, std::move(onBreakpointChange));
}
void AlignItemsImpl(Ark_NativePointer node,
                    const Opt_ItemAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<FlexAlign>(*value);
    GridRowModelNGStatic::SetAlignItems(frameNode, convValue);
}
} // GridRowAttributeModifier
const GENERATED_ArkUIGridRowModifier* GetGridRowModifier()
{
    static const GENERATED_ArkUIGridRowModifier ArkUIGridRowModifierImpl {
        GridRowModifier::ConstructImpl,
        GridRowInterfaceModifier::SetGridRowOptionsImpl,
        GridRowAttributeModifier::OnBreakpointChangeImpl,
        GridRowAttributeModifier::AlignItemsImpl,
    };
    return &ArkUIGridRowModifierImpl;
}

}
