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
#include "core/interfaces/native/utility/callback_helper.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/interfaces/native/utility/validators.h"
#include "water_flow_scroller_peer_impl.h"
#include "water_flow_sections_accessor_peer_impl.h"

namespace OHOS::Ace::NG {
namespace Converter {
template<>
void AssignCast(std::optional<WaterFlowLayoutMode>& dst, const Ark_WaterFlowLayoutMode& src)
{
    switch (src) {
        case ARK_WATER_FLOW_LAYOUT_MODE_ALWAYS_TOP_DOWN: dst = WaterFlowLayoutMode::TOP_DOWN; break;
        case ARK_WATER_FLOW_LAYOUT_MODE_SLIDING_WINDOW: dst = WaterFlowLayoutMode::SLIDING_WINDOW; break;
        default: LOGE("Unexpected enum value in Ark_WaterFlowLayoutMode: %{public}d", src);
    }
}

template<>
void AssignTo(std::optional<ScrollFrameResult>& dst, const Ark_Literal_Number_offsetRemain& from)
{
    auto offset = Converter::OptConvert<Dimension>(from.offsetRemain);
    if (offset) {
        ScrollFrameResult ret;
        ret.offset = offset.value();
        dst = ret;
    }
}
} // Converter
} // OHOS::Ace::NG
namespace OHOS::Ace::NG::GeneratedModifier {
namespace WaterFlowModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = WaterFlowModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // WaterFlowModifier
namespace WaterFlowInterfaceModifier {
void SetWaterFlowOptionsImpl(Ark_NativePointer node,
                             const Opt_WaterFlowOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = options ? Converter::OptConvert<Ark_WaterFlowOptions>(*options) : std::nullopt;
    if (convValue) {
        auto optFooter = Converter::OptConvert<CustomNodeBuilder>(convValue.value().footer);
        if (optFooter) {
            CallbackHelper(optFooter.value()).BuildAsync([frameNode](const RefPtr<UINode>& uiNode) {
                WaterFlowModelNG::SetFooter(frameNode, uiNode);
                }, node);
        }
        auto optScroller = Converter::OptConvert<Ark_Scroller>(convValue.value().scroller);
        if (optScroller) {
            RefPtr<ScrollControllerBase> positionController = WaterFlowModelNG::GetOrCreateController(frameNode);
            RefPtr<ScrollProxy> scrollBarProxy = WaterFlowModelNG::GetOrCreateScrollBarProxy(frameNode);
            auto peerImplPtr = optScroller.value();
            CHECK_NULL_VOID(peerImplPtr);
            peerImplPtr->SetController(positionController);
            peerImplPtr->SetScrollBarProxy(scrollBarProxy);
        }
        auto optArkSections = Converter::OptConvert<Ark_WaterFlowSections>(convValue.value().sections);
        if (optArkSections) {
            auto peerImplPtr = optArkSections.value();
            CHECK_NULL_VOID(peerImplPtr);
            RefPtr<WaterFlowSections> sections = WaterFlowModelNG::GetOrCreateWaterFlowSections(frameNode);
            peerImplPtr->SetController(sections);
        }
        auto optArkLayoutMode = Converter::OptConvert<Ark_WaterFlowLayoutMode>(convValue.value().layoutMode);
        if (optArkLayoutMode) {
            auto optlayoutMode = Converter::OptConvert<WaterFlowLayoutMode>(optArkLayoutMode.value());
            if (optlayoutMode) {
                WaterFlowModelNG::SetLayoutMode(frameNode, optlayoutMode.value());
            }
        }
    }
}
} // WaterFlowInterfaceModifier
namespace WaterFlowAttributeModifier {
void ColumnsTemplateImpl(Ark_NativePointer node,
                         const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    WaterFlowModelNG::SetColumnsTemplate(frameNode, *convValue);
}
void ItemConstraintSizeImpl(Ark_NativePointer node,
                            const Opt_ConstraintSizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto minWidth = Converter::OptConvert<Dimension>(optValue->minWidth);
    Validator::ValidateNonNegative(minWidth);
    Validator::ValidateNonPercent(minWidth);
    WaterFlowModelNG::SetItemMinWidth(frameNode, minWidth);

    auto minHeight = Converter::OptConvert<Dimension>(optValue->minHeight);
    Validator::ValidateNonNegative(minHeight);
    Validator::ValidateNonPercent(minHeight);
    WaterFlowModelNG::SetItemMinHeight(frameNode, minHeight);

    auto maxWidth = Converter::OptConvert<Dimension>(optValue->maxWidth);
    Validator::ValidateNonNegative(maxWidth);
    Validator::ValidateNonPercent(maxWidth);
    WaterFlowModelNG::SetItemMaxWidth(frameNode, maxWidth);

    auto maxHeight = Converter::OptConvert<Dimension>(optValue->maxHeight);
    Validator::ValidateNonNegative(maxHeight);
    Validator::ValidateNonPercent(maxHeight);
    WaterFlowModelNG::SetItemMaxHeight(frameNode, maxHeight);
}

void RowsTemplateImpl(Ark_NativePointer node,
                      const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    WaterFlowModelNG::SetRowsTemplate(frameNode, *convValue);
}
void ColumnsGapImpl(Ark_NativePointer node,
                    const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    WaterFlowModelNG::SetColumnsGap(frameNode, convValue);
}
void RowsGapImpl(Ark_NativePointer node,
                 const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    WaterFlowModelNG::SetRowsGap(frameNode, convValue);
}
void LayoutDirectionImpl(Ark_NativePointer node,
                         const Opt_FlexDirection* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<FlexDirection>(*value);
    WaterFlowModelNG::SetLayoutDirection(frameNode, convValue);
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Opt_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto forward = Converter::OptConvert<NestedScrollMode>(optValue->scrollForward);
    auto backward = Converter::OptConvert<NestedScrollMode>(optValue->scrollBackward);
    NestedScrollOptions options = {.forward = forward ? forward.value() : NestedScrollMode::SELF_ONLY,
        .backward = backward ? backward.value() : NestedScrollMode::SELF_ONLY};
    WaterFlowModelNG::SetNestedScroll(frameNode, options);
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    WaterFlowModelNG::SetScrollEnabled(frameNode, *convValue);
}
void FrictionImpl(Ark_NativePointer node,
                  const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<float>(*value);
    Validator::ValidateNonNegative(convValue);
    WaterFlowModelNG::SetFriction(frameNode, convValue);
}
void CachedCount0Impl(Ark_NativePointer node,
                      const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    Validator::ValidateNonNegative(convValue);
    WaterFlowModelNG::SetCachedCount(frameNode, convValue);
}
void CachedCount1Impl(Ark_NativePointer node,
                      const Opt_Number* count,
                      const Opt_Boolean* show)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(count);
    //auto convValue = Converter::OptConvert<type>(count); // for enums
    //WaterFlowModelNG::SetCachedCount1(frameNode, convValue);
}
void OnReachStartImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onReachStart = [arkCallback = CallbackHelper(*optValue)]() -> void {
        arkCallback.Invoke();
    };
    WaterFlowModelNG::SetOnReachStart(frameNode, std::move(onReachStart));
}
void OnReachEndImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onReachEnd = [arkCallback = CallbackHelper(*optValue)]() -> void {
        arkCallback.Invoke();
    };
    WaterFlowModelNG::SetOnReachEnd(frameNode, std::move(onReachEnd));
}
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            const Opt_Callback_Number_ScrollState_Literal_Number_offsetRemain* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onScrollFrameEvent = [callback = CallbackHelper(*optValue)](
        Dimension offset, ScrollState state) -> ScrollFrameResult {
        ScrollFrameResult result;
        Ark_Number arkOffset = Converter::ArkValue<Ark_Number>(offset);
        Ark_ScrollState arkState = Converter::ArkValue<Ark_ScrollState>(state);
        return callback.InvokeWithOptConvertResult<
            ScrollFrameResult, Ark_Literal_Number_offsetRemain,
            Callback_Literal_Number_offsetRemain_Void>(arkOffset, arkState)
            .value_or(result);
    };

    WaterFlowModelNG::SetOnScrollFrameBegin(frameNode, std::move(onScrollFrameEvent));
}
void OnScrollIndexImpl(Ark_NativePointer node,
                       const Opt_Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onScrollIndex = [arkCallback = CallbackHelper(*optValue)](const int32_t first, const int32_t last) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(first), Converter::ArkValue<Ark_Number>(last));
    };

    WaterFlowModelNG::SetOnScrollIndex(frameNode, std::move(onScrollIndex));
}
} // WaterFlowAttributeModifier
const GENERATED_ArkUIWaterFlowModifier* GetWaterFlowModifier()
{
    static const GENERATED_ArkUIWaterFlowModifier ArkUIWaterFlowModifierImpl {
        WaterFlowModifier::ConstructImpl,
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
        WaterFlowAttributeModifier::CachedCount0Impl,
        WaterFlowAttributeModifier::CachedCount1Impl,
        WaterFlowAttributeModifier::OnReachStartImpl,
        WaterFlowAttributeModifier::OnReachEndImpl,
        WaterFlowAttributeModifier::OnScrollFrameBeginImpl,
        WaterFlowAttributeModifier::OnScrollIndexImpl,
    };
    return &ArkUIWaterFlowModifierImpl;
}

}
