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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WaterFlowInterfaceModifier {
void SetWaterFlowOptionsImpl(Ark_NativePointer node,
                             const Opt_WaterFlowOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //WaterFlowModelNG::SetSetWaterFlowOptions(frameNode, convValue);
    LOGE("ARKOALA WaterFlow.SetWaterFlowOptionsImpl -> Method is not implemented. Ark_CustomObject is not supported!");
}
} // WaterFlowInterfaceModifier
namespace WaterFlowAttributeModifier {
void ColumnsTemplateImpl(Ark_NativePointer node,
                         const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    WaterFlowModelNG::SetColumnsTemplate(frameNode, convValue);
}
void ItemConstraintSizeImpl(Ark_NativePointer node,
                            const Ark_ConstraintSizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto minWidth = Converter::OptConvert<Dimension>(value->minWidth);
    Validator::ValidateNonNegative(minWidth);
    Validator::ValidateNonPercent(minWidth);
    WaterFlowModelNG::SetItemMinWidth(frameNode, minWidth);

    auto minHeight = Converter::OptConvert<Dimension>(value->minHeight);
    Validator::ValidateNonNegative(minHeight);
    Validator::ValidateNonPercent(minHeight);
    WaterFlowModelNG::SetItemMinHeight(frameNode, minHeight);

    auto maxWidth = Converter::OptConvert<Dimension>(value->maxWidth);
    Validator::ValidateNonNegative(maxWidth);
    Validator::ValidateNonPercent(maxWidth);
    WaterFlowModelNG::SetItemMaxWidth(frameNode, maxWidth);

    auto maxHeight = Converter::OptConvert<Dimension>(value->maxHeight);
    Validator::ValidateNonNegative(maxHeight);
    Validator::ValidateNonPercent(maxHeight);
    WaterFlowModelNG::SetItemMaxHeight(frameNode, maxHeight);
}

void RowsTemplateImpl(Ark_NativePointer node,
                      const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    WaterFlowModelNG::SetRowsTemplate(frameNode, convValue);
}
void ColumnsGapImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    WaterFlowModelNG::SetColumnsGap(frameNode, convValue);
}
void RowsGapImpl(Ark_NativePointer node,
                 const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    WaterFlowModelNG::SetRowsGap(frameNode, convValue);
}
void LayoutDirectionImpl(Ark_NativePointer node,
                         Ark_FlexDirection value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<FlexDirection>(value);
    WaterFlowModelNG::SetLayoutDirection(frameNode, convValue);
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Ark_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto forward = Converter::OptConvert<NestedScrollMode>(value->scrollForward);
    auto backward = Converter::OptConvert<NestedScrollMode>(value->scrollBackward);
    NestedScrollOptions options = {.forward = forward ? forward.value() : NestedScrollMode::SELF_ONLY,
        .backward = backward ? backward.value() : NestedScrollMode::SELF_ONLY};
    WaterFlowModelNG::SetNestedScroll(frameNode, options);
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WaterFlowModelNG::SetScrollEnabled(frameNode, convValue);
}
void FrictionImpl(Ark_NativePointer node,
                  const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<float>(*value);
    Validator::ValidateNonNegative(convValue);
    WaterFlowModelNG::SetFriction(frameNode, convValue);
}
void CachedCountImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    Validator::ValidateNonNegative(convValue);
    WaterFlowModelNG::SetCachedCount(frameNode, convValue);
}
void OnReachStartImpl(Ark_NativePointer node,
                      const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onReachStart = [arkCallback = CallbackHelper(*value)]() -> void {
        arkCallback.Invoke();
    };
    WaterFlowModelNG::SetOnReachStart(frameNode, std::move(onReachStart));
}
void OnReachEndImpl(Ark_NativePointer node,
                    const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onReachEnd = [arkCallback = CallbackHelper(*value)]() -> void {
        arkCallback.Invoke();
    };
    WaterFlowModelNG::SetOnReachEnd(frameNode, std::move(onReachEnd));
}
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            const Callback_Number_ScrollState_Literal_Number_offsetRemain* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WaterFlowModelNG::SetOnScrollFrameBegin(frameNode, convValue);
    LOGE("ARKOALA WaterFlow.OnScrollFrameBeginImpl -> Method is not implemented. Event with return value!");
}
void OnScrollIndexImpl(Ark_NativePointer node,
                       const Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScrollIndex = [arkCallback = CallbackHelper(*value)](const int32_t first, const int32_t last) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(first), Converter::ArkValue<Ark_Number>(last));
    };

    WaterFlowModelNG::SetOnScrollIndex(frameNode, std::move(onScrollIndex));
}
} // WaterFlowAttributeModifier
const GENERATED_ArkUIWaterFlowModifier* GetWaterFlowModifier()
{
    static const GENERATED_ArkUIWaterFlowModifier ArkUIWaterFlowModifierImpl {
        WaterFlowInterfaceModifier::SetWaterFlowOptionsImpl,
        WaterFlowAttributeModifier::ColumnsTemplateImpl,
        WaterFlowAttributeModifier::ItemConstraintSizeImpl,
        WaterFlowAttributeModifier::RowsTemplateImpl,
        WaterFlowAttributeModifier::ColumnsGapImpl,
        WaterFlowAttributeModifier::RowsGapImpl,
        WaterFlowAttributeModifier::LayoutDirectionImpl,
        WaterFlowAttributeModifier::NestedScrollImpl,
        WaterFlowAttributeModifier::EnableScrollInteractionImpl,
        WaterFlowAttributeModifier::FrictionImpl,
        WaterFlowAttributeModifier::CachedCountImpl,
        WaterFlowAttributeModifier::OnReachStartImpl,
        WaterFlowAttributeModifier::OnReachEndImpl,
        WaterFlowAttributeModifier::OnScrollFrameBeginImpl,
        WaterFlowAttributeModifier::OnScrollIndexImpl,
    };
    return &ArkUIWaterFlowModifierImpl;
}

}
