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
#include "core/components_ng/pattern/grid_row/grid_row_model_ng.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/components_ng/pattern/grid_row/grid_row_model_ng_static.h"

namespace OHOS::Ace::NG {
namespace {
constexpr size_t MAX_NUMBER_BREAKPOINT = 6;
constexpr size_t XS = 0;
constexpr size_t SM = 1;
constexpr size_t MD = 2;
constexpr size_t LG = 3;
constexpr size_t XL = 4;
constexpr size_t XXL = 5;
}
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
    static GridRowSizeOption GridRowSizeOptionFromDimension(const std::optional<Dimension>& optValue)
    {
        GridRowSizeOption toValue;
        toValue.xs = optValue;
        toValue.sm = optValue;
        toValue.md = optValue;
        toValue.lg = optValue;
        toValue.xl = optValue;
        toValue.xxl = optValue;
        return toValue;
    }
    template<>
    GridRowSizeOption Convert(const Ark_Number& value)
    {
        return GridRowSizeOptionFromDimension(OptConvert<Dimension>(value));
    }
    template<>
    GridRowSizeOption Convert(const Ark_Float64& value)
    {
        return GridRowSizeOptionFromDimension(OptConvert<Dimension>(value));
    }
    template<>
    GridRowSizeOption Convert(const Ark_String& value)
    {
        return GridRowSizeOptionFromDimension(OptConvert<Dimension>(value));
    }
    template<>
    GridRowSizeOption Convert(const Ark_Resource& value)
    {
        return GridRowSizeOptionFromDimension(OptConvert<Dimension>(value));
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
    V2::Gutter Convert(const Ark_Float64& value)
    {
        return V2::Gutter(Converter::Convert<Dimension>(value));
    }
    template<>
    void AssignCast(std::optional<V2::Gutter>& dst, const Ark_Resource& value)
    {
        auto dim = Converter::OptConvert<Dimension>(value);
        if (dim) {
            dst = V2::Gutter(*dim);
        }
    }
    template<>
    void AssignCast(std::optional<V2::Gutter>& dst, const Ark_String& value)
    {
        auto dim = Converter::OptConvert<Dimension>(value);
        if (dim) {
            dst = V2::Gutter(*dim);
        }
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
            toValue.xXs = valueX.xs.value_or(dimDefault);
            toValue.xSm = valueX.sm.value_or(toValue.xXs);
            toValue.xMd = valueX.md.value_or(toValue.xSm);
            toValue.xLg = valueX.lg.value_or(toValue.xMd);
            toValue.xXl = valueX.xl.value_or(toValue.xLg);
            toValue.xXXl = valueX.xxl.value_or(toValue.xXl);
        }
        if (y.has_value()) {
            auto valueY = y.value();
            toValue.yXs = valueY.xs.value_or(dimDefault);
            toValue.ySm = valueY.sm.value_or(toValue.yXs);
            toValue.yMd = valueY.md.value_or(toValue.ySm);
            toValue.yLg = valueY.lg.value_or(toValue.yMd);
            toValue.yXl = valueY.xl.value_or(toValue.yLg);
            toValue.yXXl = valueY.xxl.value_or(toValue.yXl);
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
        if (!optBreakpoints.has_value()) {
            return toValue;
        }
        toValue.breakpoints.clear();
        double width = -1.0;
        for (const auto &threshold : optBreakpoints.value()) {
            CalcDimension valueDimension = StringUtils::StringToCalcDimension(threshold, false, DimensionUnit::VP);
            if (GreatNotEqual(width, valueDimension.Value())) {
                break;
            }
            width = valueDimension.Value();
            toValue.breakpoints.emplace_back(threshold);
        }
        return toValue;
    }
    template<>
    V2::GridContainerSize Convert(const Ark_Int32& value);

    void InheritGridColumns(V2::GridContainerSize& gridContainerSize,
        std::optional<int32_t> (&containerSizeArray)[MAX_NUMBER_BREAKPOINT])
    {
        for (size_t i = 0; i < MAX_NUMBER_BREAKPOINT; ++i) {
            if (containerSizeArray[i].has_value()) {
                containerSizeArray[0] = containerSizeArray[i].value();
                break;
            }
        }
        CHECK_NULL_VOID(containerSizeArray[0].has_value());
        for (size_t i = 1; i < MAX_NUMBER_BREAKPOINT; ++i) {
            if (!containerSizeArray[i].has_value()) {
                containerSizeArray[i] = containerSizeArray[i - 1].value();
            }
        }
        gridContainerSize.xs = containerSizeArray[XS].value();
        gridContainerSize.sm = containerSizeArray[SM].value();
        gridContainerSize.md = containerSizeArray[MD].value();
        gridContainerSize.lg = containerSizeArray[LG].value();
        gridContainerSize.xl = containerSizeArray[XL].value();
        gridContainerSize.xxl = containerSizeArray[XXL].value();
    }

    template<>
    V2::GridContainerSize Convert(const Ark_GridRowColumnOption& value)
    {
        V2::GridContainerSize toValue;
        std::optional<int32_t> containerSizeArray[MAX_NUMBER_BREAKPOINT];
        containerSizeArray[XS] = Converter::OptConvert<int32_t>(value.xs);
        containerSizeArray[SM] = Converter::OptConvert<int32_t>(value.sm);
        containerSizeArray[MD] = Converter::OptConvert<int32_t>(value.md);
        containerSizeArray[LG] = Converter::OptConvert<int32_t>(value.lg);
        containerSizeArray[XL] = Converter::OptConvert<int32_t>(value.xl);
        containerSizeArray[XXL] = Converter::OptConvert<int32_t>(value.xxl);
        InheritGridColumns(toValue, containerSizeArray);
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
    auto convValue = Converter::OptConvertPtr<Ark_GridRowOptions>(option);
    auto nullGutter = Referenced::MakeRefPtr<V2::Gutter>();
    auto nullBreakPoints = Referenced::MakeRefPtr<V2::BreakPoints>();
    auto nullGridContainerSize = Referenced::MakeRefPtr<V2::GridContainerSize>();
    if (convValue.has_value()) {
        auto arkOptions = convValue.value();

        auto optGutter = Converter::OptConvert<V2::Gutter>(arkOptions.gutter);
        Validator::ValidateNonNegative(optGutter);
        auto gutter = optGutter.has_value() ? AceType::MakeRefPtr<V2::Gutter>(optGutter.value()) : nullGutter;
        GridRowModelNG::SetGutter(frameNode, gutter);

        auto direction = Converter::OptConvert<V2::GridRowDirection>(arkOptions.direction);
        GridRowModelNGStatic::SetDirection(frameNode, direction);

        auto optBreakPoints = Converter::OptConvert<V2::BreakPoints>(arkOptions.breakpoints);
        auto breakpoints = optBreakPoints.has_value()
            ? AceType::MakeRefPtr<V2::BreakPoints>(optBreakPoints.value()) : nullBreakPoints;
        breakpoints->userDefine = optBreakPoints.has_value();
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
void SetOnBreakpointChangeImpl(Ark_NativePointer node,
                               const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        GridRowModelNG::SetOnBreakPointChange(frameNode, nullptr);
        return;
    }
    auto onBreakpointChange = [arkCallback = CallbackHelper(*optValue)](const std::string& breakpoint) {
        arkCallback.Invoke(Converter::ArkValue<Ark_String>(breakpoint));
    };
    GridRowModelNG::SetOnBreakPointChange(frameNode, std::move(onBreakpointChange));
}
void SetAlignItemsImpl(Ark_NativePointer node,
                       const Opt_ItemAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<FlexAlign>(value);
    GridRowModelNGStatic::SetAlignItems(frameNode, convValue);
}
} // GridRowAttributeModifier
const GENERATED_ArkUIGridRowModifier* GetGridRowModifier()
{
    static const GENERATED_ArkUIGridRowModifier ArkUIGridRowModifierImpl {
        GridRowModifier::ConstructImpl,
        GridRowInterfaceModifier::SetGridRowOptionsImpl,
        GridRowAttributeModifier::SetOnBreakpointChangeImpl,
        GridRowAttributeModifier::SetAlignItemsImpl,
    };
    return &ArkUIGridRowModifierImpl;
}

}
