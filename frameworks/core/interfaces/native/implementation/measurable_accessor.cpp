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
#include "core/interfaces/native/implementation/measurable_peer.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
Ark_DirectionalEdgesT_F64 GenEdgesGlobalized(const NG::PaddingPropertyT<float>& edgeNative, TextDirection direction)
{
    Ark_DirectionalEdgesT_F64 edges;
    auto pipeline = PipelineBase::GetCurrentContext();
    double px2vpScale = pipeline ? 1.0 / pipeline->GetDipScale() : 1.0;
    edges.top = Converter::ArkValue<Ark_Float64>(edgeNative.top.value_or(0) * px2vpScale);
    edges.bottom = Converter::ArkValue<Ark_Float64>(edgeNative.bottom.value_or(0) * px2vpScale);
    if (direction != TextDirection::RTL) {
        edges.start = Converter::ArkValue<Ark_Float64>(edgeNative.left.value_or(0) * px2vpScale);
        edges.end = Converter::ArkValue<Ark_Float64>(edgeNative.right.value_or(0) * px2vpScale);
    } else {
        edges.start = Converter::ArkValue<Ark_Float64>(edgeNative.right.value_or(0) * px2vpScale);
        edges.end = Converter::ArkValue<Ark_Float64>(edgeNative.left.value_or(0) * px2vpScale);
    }
    return edges;
}
Ark_DirectionalEdgesT_F64 GenBorderWidthGlobalized(const NG::BorderWidthPropertyT<float>& edgeNative,
    TextDirection direction)
{
    Ark_DirectionalEdgesT_F64 edges;
    auto pipeline = PipelineBase::GetCurrentContext();
    double px2vpScale = pipeline ? 1.0 / pipeline->GetDipScale() : 1.0;
    edges.top = Converter::ArkValue<Ark_Float64>(edgeNative.topDimen.value_or(0) * px2vpScale);
    edges.bottom = Converter::ArkValue<Ark_Float64>(edgeNative.bottomDimen.value_or(0) * px2vpScale);
    if (direction != TextDirection::RTL) {
        edges.start = Converter::ArkValue<Ark_Float64>(edgeNative.leftDimen.value_or(0) * px2vpScale);
        edges.end = Converter::ArkValue<Ark_Float64>(edgeNative.rightDimen.value_or(0) * px2vpScale);
    } else {
        edges.start = Converter::ArkValue<Ark_Float64>(edgeNative.rightDimen.value_or(0) * px2vpScale);
        edges.end = Converter::ArkValue<Ark_Float64>(edgeNative.leftDimen.value_or(0) * px2vpScale);
    }
    return edges;
}
void ProcessMinWidth(const CalcDimension& minWidth, RefPtr<LayoutProperty>& layoutProperty,
    LayoutConstraintF& childLayoutConstraint)
{
    if (layoutProperty) {
        layoutProperty->UpdateCalcMinSize(NG::CalcSize(NG::CalcLength(minWidth), std::nullopt));
    } else {
        auto length = ConvertToPx(NG::CalcLength(minWidth), childLayoutConstraint.scaleProperty,
            childLayoutConstraint.percentReference.Width());
        if (length) {
            childLayoutConstraint.minSize.SetWidth(length.value());
        }
    }
}
void ProcessMaxWidth(const CalcDimension& maxWidth, RefPtr<LayoutProperty>& layoutProperty,
    LayoutConstraintF& childLayoutConstraint)
{
    if (layoutProperty) {
        layoutProperty->UpdateCalcMaxSize(NG::CalcSize(NG::CalcLength(maxWidth), std::nullopt));
    } else {
        auto length = ConvertToPx(NG::CalcLength(maxWidth), childLayoutConstraint.scaleProperty,
            childLayoutConstraint.percentReference.Width());
        if (length) {
            childLayoutConstraint.maxSize.SetWidth(length.value());
        }
    }
}
void ProcessMinHeight(const CalcDimension& minHeight, RefPtr<LayoutProperty>& layoutProperty,
    LayoutConstraintF& childLayoutConstraint)
{
    if (layoutProperty) {
        layoutProperty->UpdateCalcMinSize(NG::CalcSize(std::nullopt, NG::CalcLength(minHeight)));
    } else {
        auto length = ConvertToPx(NG::CalcLength(minHeight), childLayoutConstraint.scaleProperty,
            childLayoutConstraint.percentReference.Height());
        if (length) {
            childLayoutConstraint.minSize.SetHeight(length.value());
        }
    }
}
void ProcessMaxHeight(const CalcDimension& maxHeight, RefPtr<LayoutProperty>& layoutProperty,
    LayoutConstraintF& childLayoutConstraint)
{
    if (layoutProperty) {
        layoutProperty->UpdateCalcMaxSize(NG::CalcSize(std::nullopt, NG::CalcLength(maxHeight)));
    } else {
        auto length = ConvertToPx(NG::CalcLength(maxHeight), childLayoutConstraint.scaleProperty,
            childLayoutConstraint.percentReference.Height());
        if (length) {
            childLayoutConstraint.maxSize.SetHeight(length.value());
        }
    }
}
const Ark_DirectionalEdgesT_F64 DEFAULT_EDGES = {
    .start = Converter::ArkValue<Ark_Float64>(0.0f),
    .end = Converter::ArkValue<Ark_Float64>(0.0f),
    .top = Converter::ArkValue<Ark_Float64>(0.0f),
    .bottom = Converter::ArkValue<Ark_Float64>(0.0f),
};
const Ark_MeasureResult DEFAULT_MEASURE_RESULT = {
    .width = Converter::ArkValue<Ark_Float64>(0.0f),
    .height = Converter::ArkValue<Ark_Float64>(0.0f),
};
}  // namespace
namespace MeasurableAccessor {
void DestroyPeerImpl(Ark_Measurable peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_Measurable ConstructImpl()
{
    return PeerUtils::CreatePeer<MeasurablePeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_MeasureResult MeasureImpl(Ark_Measurable peer,
                              const Ark_ConstraintSizeOptions* constraint)
{
    CHECK_NULL_RETURN(
        peer && peer->measureLayoutParam && constraint, Converter::ArkValue<Opt_MeasureResult>(Ark_Empty()));
    auto child = peer->measureLayoutParam->GetOrCreateChildByIndex(peer->index);
    CHECK_NULL_RETURN(child, Converter::ArkValue<Opt_MeasureResult>(Ark_Empty()));
    auto childLayoutConstraint = peer->measureLayoutParam->CreateChildConstraint();
    auto layoutProperty = child->GetLayoutProperty();

    auto minWidth = Converter::OptConvert<CalcDimension>(constraint->minWidth);
    if (minWidth.has_value()) {
        ProcessMinWidth(minWidth.value(), layoutProperty, childLayoutConstraint);
    }

    auto maxWidth = Converter::OptConvert<CalcDimension>(constraint->maxWidth);
    if (maxWidth.has_value()) {
        ProcessMaxWidth(maxWidth.value(), layoutProperty, childLayoutConstraint);
    }

    auto minHeight = Converter::OptConvert<CalcDimension>(constraint->minHeight);
    if (minHeight.has_value()) {
        ProcessMinHeight(minHeight.value(), layoutProperty, childLayoutConstraint);
    }

    auto maxHeight = Converter::OptConvert<CalcDimension>(constraint->maxHeight);
    if (maxHeight.has_value()) {
        ProcessMaxHeight(maxHeight.value(), layoutProperty, childLayoutConstraint);
    }

    child->Measure(childLayoutConstraint);

    auto geometryNode = child->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, Converter::ArkValue<Opt_MeasureResult>(Ark_Empty()));
    auto size = geometryNode->GetFrameSize();
    Dimension measureWidth(size.Width(), DimensionUnit::PX);
    Dimension measureHeight(size.Height(), DimensionUnit::PX);
    Ark_MeasureResult measureResult = {
        .width = Converter::ArkValue<Ark_Float64>(measureWidth.ConvertToVp()),
        .height = Converter::ArkValue<Ark_Float64>(measureHeight.ConvertToVp()),
    };
    return Converter::ArkValue<Opt_MeasureResult>(measureResult);
}
Opt_DirectionalEdgesT_F64 GetMarginImpl(Ark_Measurable peer)
{
    CHECK_NULL_RETURN(peer && peer->measureLayoutParam, Converter::ArkValue<Opt_DirectionalEdgesT_F64>(Ark_Empty()));
    auto child = peer->measureLayoutParam->GetOrCreateChildByIndex(peer->index);
    CHECK_NULL_RETURN(child, Converter::ArkValue<Opt_DirectionalEdgesT_F64>(Ark_Empty()));
    auto layoutProperty = child->GetLayoutProperty();
    CHECK_NULL_RETURN(child->GetLayoutProperty(), Converter::ArkValue<Opt_DirectionalEdgesT_F64>(Ark_Empty()));
    auto direction = layoutProperty->GetNonAutoLayoutDirection();
    auto result = GenEdgesGlobalized(layoutProperty->CreateMarginWithoutCache(), direction);
    return Converter::ArkValue<Opt_DirectionalEdgesT_F64>(result);
}
Opt_DirectionalEdgesT_F64 GetPaddingImpl(Ark_Measurable peer)
{
    CHECK_NULL_RETURN(peer && peer->measureLayoutParam, Converter::ArkValue<Opt_DirectionalEdgesT_F64>(Ark_Empty()));
    auto child = peer->measureLayoutParam->GetOrCreateChildByIndex(peer->index);
    CHECK_NULL_RETURN(child, Converter::ArkValue<Opt_DirectionalEdgesT_F64>(Ark_Empty()));
    auto layoutProperty = child->GetLayoutProperty();
    CHECK_NULL_RETURN(child->GetLayoutProperty(), Converter::ArkValue<Opt_DirectionalEdgesT_F64>(Ark_Empty()));
    auto direction = layoutProperty->GetNonAutoLayoutDirection();
    auto result = GenEdgesGlobalized(layoutProperty->CreatePaddingWithoutBorder(false, false), direction);
    return Converter::ArkValue<Opt_DirectionalEdgesT_F64>(result);
}
Opt_DirectionalEdgesT_F64 GetBorderWidthImpl(Ark_Measurable peer)
{
    CHECK_NULL_RETURN(peer && peer->measureLayoutParam, Converter::ArkValue<Opt_DirectionalEdgesT_F64>(Ark_Empty()));
    auto child = peer->measureLayoutParam->GetOrCreateChildByIndex(peer->index);
    CHECK_NULL_RETURN(child, Converter::ArkValue<Opt_DirectionalEdgesT_F64>(Ark_Empty()));
    auto layoutProperty = child->GetLayoutProperty();
    CHECK_NULL_RETURN(child->GetLayoutProperty(), Converter::ArkValue<Opt_DirectionalEdgesT_F64>(Ark_Empty()));
    auto direction = layoutProperty->GetNonAutoLayoutDirection();
    auto result = GenBorderWidthGlobalized(layoutProperty->CreateBorder(), direction);
    return Converter::ArkValue<Opt_DirectionalEdgesT_F64>(result);
}
Opt_Int64 GetUniqueIdImpl(Ark_Measurable peer)
{
    auto invalid = Converter::ArkValue<Opt_Int64>(Ark_Empty());
    CHECK_NULL_RETURN(peer && peer->measureLayoutParam, invalid);
    auto child = peer->measureLayoutParam->GetOrCreateChildByIndex(peer->index);
    CHECK_NULL_RETURN(child, invalid);
    auto uniqueId = child->GetHostNode()->GetId();
    return Converter::ArkValue<Opt_Int64>(uniqueId);
}
void SetUniqueIdImpl(Ark_Measurable peer,
                     const Opt_Int64* uniqueId)
{
    LOGE("MeasurableAccessor::SetUniqueIdImpl is not implemented, only getter is supported");
}
} // MeasurableAccessor
const GENERATED_ArkUIMeasurableAccessor* GetMeasurableAccessor()
{
    static const GENERATED_ArkUIMeasurableAccessor MeasurableAccessorImpl {
        MeasurableAccessor::DestroyPeerImpl,
        MeasurableAccessor::ConstructImpl,
        MeasurableAccessor::GetFinalizerImpl,
        MeasurableAccessor::MeasureImpl,
        MeasurableAccessor::GetMarginImpl,
        MeasurableAccessor::GetPaddingImpl,
        MeasurableAccessor::GetBorderWidthImpl,
        MeasurableAccessor::GetUniqueIdImpl,
        MeasurableAccessor::SetUniqueIdImpl,
    };
    return &MeasurableAccessorImpl;
}

}
