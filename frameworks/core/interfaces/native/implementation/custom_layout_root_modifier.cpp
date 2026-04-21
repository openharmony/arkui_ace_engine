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
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/interfaces/native/implementation/layoutable_peer.h"
#include "core/interfaces/native/implementation/measurable_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<>
SizeF Convert(const Ark_SizeResult& src)
{
    auto measureWidth = Converter::Convert<CalcDimension>(src.width);
    auto measureHeight = Converter::Convert<CalcDimension>(src.height);
    return { measureWidth.ConvertToPx(), measureHeight.ConvertToPx() };
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
const std::unique_ptr<NG::PaddingProperty> defaultPadding = std::make_unique<NG::PaddingProperty>();
Ark_GeometryInfo GenGeometryInfo(const RefPtr<OHOS::Ace::NG::LayoutProperty>& layoutProperty, double dipScale)
{
    auto host = layoutProperty->GetHost();
    NG::RectF originGeoRect;
    if (host) {
        originGeoRect = host->GetGeometryNode()->GetFrameRect();
    }
    auto width =
        GreatNotEqual(originGeoRect.Width(), 0.0f) ?
        (NearZero(dipScale) ? originGeoRect.Width() : originGeoRect.Width() / dipScale)
        : layoutProperty->GetLayoutConstraint()
            ? (NearZero(dipScale)
                ? layoutProperty->GetLayoutConstraint()->selfIdealSize.Width().value_or(0.0)
                : layoutProperty->GetLayoutConstraint()->selfIdealSize.Width().value_or(0.0) / dipScale)
            : 0.0f;
    auto height =
        GreatNotEqual(originGeoRect.Height(), 0.0f) ?
        (NearZero(dipScale) ? originGeoRect.Height() : originGeoRect.Height() / dipScale)
        : layoutProperty->GetLayoutConstraint()
            ? (NearZero(dipScale)
                ? layoutProperty->GetLayoutConstraint()->selfIdealSize.Height().value_or(0.0)
                : layoutProperty->GetLayoutConstraint()->selfIdealSize.Height().value_or(0.0) / dipScale)
            : 0.0f;
    const std::unique_ptr<NG::BorderWidthProperty>& borderWidth = layoutProperty->GetBorderWidthProperty();
    Ark_GeometryInfo selfLayoutInfo;
    selfLayoutInfo.width = Converter::ArkValue<Ark_Float64>((NearEqual(width, 0.0f) && !NearZero(dipScale))
        ? layoutProperty->GetLayoutConstraint()->percentReference.Width() / dipScale : width);
    selfLayoutInfo.height = Converter::ArkValue<Ark_Float64>((NearEqual(height, 0.0f) && !NearZero(dipScale))
        ? layoutProperty->GetLayoutConstraint()->percentReference.Height() / dipScale : height);
    selfLayoutInfo.borderWidth.left = Converter::ArkValue<Opt_Length>(borderWidth
        ? borderWidth->leftDimen->ConvertToVp() : 0.0f);
    selfLayoutInfo.borderWidth.top = Converter::ArkValue<Opt_Length>(borderWidth
        ? borderWidth->topDimen->ConvertToVp() : 0.0f);
    selfLayoutInfo.borderWidth.right = Converter::ArkValue<Opt_Length>(borderWidth
        ? borderWidth->rightDimen->ConvertToVp() : 0.0f);
    selfLayoutInfo.borderWidth.bottom = Converter::ArkValue<Opt_Length>(borderWidth
        ? borderWidth->bottomDimen->ConvertToVp() : 0.0f);
    selfLayoutInfo.margin = Converter::ArkValue<Ark_Padding>(*(layoutProperty->GetMarginProperty()
        ? layoutProperty->GetMarginProperty() : defaultPadding).get());
    selfLayoutInfo.padding = Converter::ArkValue<Ark_Padding>(*(layoutProperty->GetPaddingProperty()
        ? layoutProperty->GetPaddingProperty() : defaultPadding).get());
    return selfLayoutInfo;
}
} // namespace
namespace CustomLayoutRootModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto idStr = std::to_string(id);
    auto key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(idStr);
    auto customNode = NG::CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(id, key);
    CHECK_NULL_RETURN(customNode, nullptr);
    customNode->IncRefCount();
    return AceType::RawPtr(customNode);
}
void SetSubscribeOnMeasureSizeImpl(Ark_NativePointer node,
                                   const Callback_onMeasureSize_SizeResult* value)
{
    auto customNode = reinterpret_cast<NG::CustomMeasureLayoutNode *>(node);
    CHECK_NULL_VOID(customNode);
    CHECK_NULL_VOID(value);
    auto measureSizeFunc =
        [arkCallback = CallbackHelper(*value), customNode](NG::LayoutWrapper* layoutWrapper) -> void {
        auto layoutProperty = layoutWrapper && layoutWrapper->GetLayoutProperty()
            ? layoutWrapper->GetLayoutProperty() : AceType::MakeRefPtr<LayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto parentNode = AceType::DynamicCast<NG::FrameNode>(layoutProperty->GetHost()->GetParent());
        if (parentNode && parentNode->GetTag() == V2::COMMON_VIEW_ETS_TAG) {
            layoutProperty = parentNode->GetLayoutProperty();
        }
        // selfLayoutInfo
        Ark_GeometryInfo selfLayoutInfo = GenGeometryInfo(layoutProperty, pipeline->GetDipScale());
        // children
        auto measureLayoutParam = AceType::MakeRefPtr<MeasureLayoutParam>(layoutWrapper);
        auto childCount = measureLayoutParam->GetTotalChildCount();
        std::vector<Ark_Measurable> measurablePeerVec;
        measurablePeerVec.reserve(childCount);
        for (int i = 0; i < childCount; i++) {
            auto measurablePeer = PeerUtils::CreatePeer<MeasurablePeer>();
            CHECK_NULL_VOID(measurablePeer);
            measurablePeer->measureLayoutParam = measureLayoutParam;
            measurablePeer->index = i;
            measurablePeerVec.push_back(measurablePeer);
        }
        Array_Measurable children = Converter::ArkValue<Array_Measurable>(measurablePeerVec, Converter::FC);
        // constraint
        Ark_ConstraintSizeOptions constraint;
        auto parentConstraint = layoutProperty->GetLayoutConstraint();
        CHECK_NULL_VOID(parentConstraint);
        constraint.minWidth = Converter::ArkValue<Opt_Length>(parentConstraint->minSize.Width());
        constraint.minHeight = Converter::ArkValue<Opt_Length>(parentConstraint->minSize.Height());
        constraint.maxWidth = Converter::ArkValue<Opt_Length>(parentConstraint->maxSize.Width());
        constraint.maxHeight = Converter::ArkValue<Opt_Length>(parentConstraint->maxSize.Height());
        // sizeResult
        auto frameSize = arkCallback.InvokeWithConvertResult<SizeF, Ark_SizeResult, Callback_SizeResult_Void>(
            selfLayoutInfo, children, constraint);
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
    };
    customNode->SetMeasureFunction(std::move(measureSizeFunc));
}
void SetSubscribeOnPlaceChildrenImpl(Ark_NativePointer node,
                                     const Callback_onPlaceChildren_Void* value)
{
    auto customNode = reinterpret_cast<NG::CustomMeasureLayoutNode *>(node);
    CHECK_NULL_VOID(customNode);
    CHECK_NULL_VOID(value);
    auto placeChildrenFunc =
        [arkCallback = CallbackHelper(*value), customNode](NG::LayoutWrapper* layoutWrapper) -> void {
        auto layoutProperty = layoutWrapper && layoutWrapper->GetLayoutProperty()
            ? layoutWrapper->GetLayoutProperty() : AceType::MakeRefPtr<LayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto parentNode = AceType::DynamicCast<NG::FrameNode>(layoutProperty->GetHost()->GetParent());
        if (parentNode && parentNode->GetTag() == V2::COMMON_VIEW_ETS_TAG) {
            layoutProperty = parentNode->GetLayoutProperty();
        }
        // selfLayoutInfo
        Ark_GeometryInfo selfLayoutInfo = GenGeometryInfo(layoutProperty, pipeline->GetDipScale());
        // children
        auto measureLayoutParam = AceType::MakeRefPtr<MeasureLayoutParam>(layoutWrapper);
        auto childCount = measureLayoutParam->GetTotalChildCount();
        std::vector<Ark_Layoutable> layoutablePeerVec;
        for (int i = 0; i < childCount; i++) {
            auto layoutablePeer = PeerUtils::CreatePeer<LayoutablePeer>();
            CHECK_NULL_VOID(layoutablePeer);
            layoutablePeer->measureLayoutParam = measureLayoutParam;
            layoutablePeer->index = i;
            layoutablePeerVec.push_back(layoutablePeer);
        }
        Array_Layoutable children = Converter::ArkValue<Array_Layoutable>(layoutablePeerVec, Converter::FC);
        // constraint
        Ark_ConstraintSizeOptions constraint;
        auto parentConstraint = layoutProperty->GetLayoutConstraint();
        CHECK_NULL_VOID(parentConstraint);
        constraint.minWidth = Converter::ArkValue<Opt_Length>(parentConstraint->minSize.Width());
        constraint.minHeight = Converter::ArkValue<Opt_Length>(parentConstraint->minSize.Height());
        constraint.maxWidth = Converter::ArkValue<Opt_Length>(parentConstraint->maxSize.Width());
        constraint.maxHeight = Converter::ArkValue<Opt_Length>(parentConstraint->maxSize.Height());
        // InvokeSync because we need to handle callback immediately
        arkCallback.InvokeSync(selfLayoutInfo, children, constraint);
    };
    customNode->SetLayoutFunction(std::move(placeChildrenFunc));
}
} // CustomLayoutRootModifier
const GENERATED_ArkUICustomLayoutRootModifier* GetCustomLayoutRootModifier()
{
    static const GENERATED_ArkUICustomLayoutRootModifier ArkUICustomLayoutRootModifierImpl {
        CustomLayoutRootModifier::ConstructImpl,
        CustomLayoutRootModifier::SetSubscribeOnMeasureSizeImpl,
        CustomLayoutRootModifier::SetSubscribeOnPlaceChildrenImpl,
    };
    return &ArkUICustomLayoutRootModifierImpl;
}

}
