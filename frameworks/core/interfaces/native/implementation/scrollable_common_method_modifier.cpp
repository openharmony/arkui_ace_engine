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
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "arkoala_api_generated.h"


namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<ContentClipMode>& dst, const Ark_ContentClipMode& src)
{
    switch (src) {
        case ARK_CONTENT_CLIP_MODE_CONTENT_ONLY:dst = ContentClipMode::CONTENT_ONLY;break;
        case ARK_CONTENT_CLIP_MODE_BOUNDARY:dst = ContentClipMode::BOUNDARY;break;
        case ARK_CONTENT_CLIP_MODE_SAFE_AREA:dst = ContentClipMode::SAFE_AREA;break;
        default: LOGE("Unexpected enum value in Ark_ContentClipMode: %{public}d", src);break;
    }
}

template<>
void AssignCast(std::optional<Dimension>& dst, const Ark_FadingEdgeOptions& src)
{
    dst = OptConvert<Dimension>(src.fadingEdgeLength);
}

template<>
ScrollFrameResult Convert<ScrollFrameResult>(const Ark_OffsetResult& src)
{
    return { .offset = Convert<Dimension>(src.xOffset) };
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScrollableCommonMethodModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
void ScrollBarImpl(Ark_NativePointer node,
                   Ark_BarState value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<DisplayMode>(value);
    ScrollableModelNG::SetScrollBarMode(frameNode, convValue);
}
void ScrollBarColorImpl(Ark_NativePointer node,
                        const Ark_Union_Color_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    ScrollableModelNG::SetScrollBarColor(frameNode, convValue);
}
void ScrollBarWidthImpl(Ark_NativePointer node,
                        const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    ScrollableModelNG::SetScrollBarWidth(frameNode, convValue);
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Ark_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ScrollableModelNG::SetNestedScroll(frameNode, Converter::Convert<NestedScrollOptions>(*value));
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto scrollEnabled = Converter::Convert<bool>(value);
    auto layoutProp = frameNode->GetLayoutPropertyPtr<LayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    const auto id = AceType::TypeId(layoutProp);
    if (GridLayoutProperty::TypeId() == id) {
        GridModelNG::SetScrollEnabled(frameNode, scrollEnabled);
    } else if (ListLayoutProperty::TypeId() == id) {
        ListModelNG::SetScrollEnabled(frameNode, scrollEnabled);
    } else if (ScrollLayoutProperty::TypeId() == id) {
        ScrollModelNG::SetScrollEnabled(frameNode, scrollEnabled);
    } else if (WaterFlowLayoutProperty::TypeId() == id) {
        WaterFlowModelNG::SetScrollEnabled(frameNode, scrollEnabled);
    }
}
void FrictionImpl(Ark_NativePointer node,
                  const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<float>(*value);
    ScrollableModelNG::SetFriction(frameNode, convValue);
}
void OnScrollImpl(Ark_NativePointer node,
                  const Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ScrollableCommonMethodModifier::OnScrollImpl is not implemented");
}
void OnWillScrollImpl(Ark_NativePointer node,
                      const Opt_ScrollOnWillScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    std::optional<ScrollOnWillScrollCallback> arkCallback;
    if (value) {
        arkCallback = Converter::OptConvert<ScrollOnWillScrollCallback>(*value);
    }
    if (arkCallback) {
        auto modelCallback = [callback = CallbackHelper(*arkCallback)]
            (const Dimension& scrollOffset, const ScrollState& scrollState, const ScrollSource& scrollSource) ->
                ScrollFrameResult {
            auto arkScrollOffset = Converter::ArkValue<Ark_Number>(scrollOffset);
            auto arkScrollState = Converter::ArkValue<Ark_ScrollState>(scrollState);
            auto arkScrollSource = Converter::ArkValue<Ark_ScrollSource>(scrollSource);
            auto resultOpt =
                callback.InvokeWithOptConvertResult<ScrollFrameResult, Ark_OffsetResult, Callback_OffsetResult_Void>(
                    arkScrollOffset, arkScrollOffset, arkScrollState, arkScrollSource);
            ScrollFrameResult defResult = {scrollOffset};
            return resultOpt.value_or(defResult);
        };
        ScrollableModelNG::SetOnWillScroll(frameNode, std::move(modelCallback));
    } else {
        ScrollableModelNG::SetOnWillScroll(frameNode, nullptr);
    }
}

void OnDidScrollImpl(Ark_NativePointer node,
                     const ScrollOnScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto call = [arkCallback = CallbackHelper(*value)](
        Dimension offset, ScrollState stateIn) {
            auto state = Converter::ArkValue<Ark_ScrollState>(stateIn);
            auto offsetVal = Converter::ArkValue<Ark_Number>(offset);
            arkCallback.Invoke(offsetVal, offsetVal, state);
    };
    ScrollableModelNG::SetOnDidScroll(frameNode, std::move(call));
}
void OnReachStartImpl(Ark_NativePointer node,
                      const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto modelCallback = [callbackHelper = CallbackHelper(*value)]() {
        callbackHelper.Invoke();
    };
    ScrollableModelNG::SetOnReachStart(frameNode, std::move(modelCallback));
}
void OnReachEndImpl(Ark_NativePointer node,
                    const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto modelCallback = [callbackHelper = CallbackHelper(*value)]() {
        callbackHelper.Invoke();
    };
    ScrollableModelNG::SetOnReachEnd(frameNode, std::move(modelCallback));
}
void OnScrollStartImpl(Ark_NativePointer node,
                       const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto modelCallback = [callbackHelper = CallbackHelper(*value)]() {
        callbackHelper.Invoke();
    };
    ScrollableModelNG::SetOnScrollStart(frameNode, std::move(modelCallback));
}
void OnScrollStopImpl(Ark_NativePointer node,
                      const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto modelCallback = [callbackHelper = CallbackHelper(*value)]() {
        callbackHelper.Invoke();
    };
    ScrollableModelNG::SetOnScrollStop(frameNode, std::move(modelCallback));
}
void FlingSpeedLimitImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto dimension = Converter::Convert<Dimension>(*value);
    ScrollableModelNG::SetMaxFlingSpeed(frameNode, dimension.Value());
}
void ClipContentImpl(Ark_NativePointer node,
                     const Ark_Union_ContentClipMode_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    Converter::VisitUnion(*value,
        [frameNode](const Ark_ContentClipMode& arkMode) {
            auto mode = Converter::OptConvert<ContentClipMode>(arkMode);
            // mode cannot be nullopt, because in model created pair for lauout property
            ScrollableModelNG::SetContentClip(frameNode, mode.value_or(ContentClipMode::DEFAULT), nullptr);
        },
        [](const auto& value) {
            LOGE("ScrollableCommonMethodModifier::ClipContentImpl set RectShape is not supported");
        },
        []() {}
    );
}
void EdgeEffectImpl(Ark_NativePointer node,
                    Ark_EdgeEffect edgeEffect,
                    const Opt_EdgeEffectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convEdgeEffect = Converter::OptConvert<EdgeEffect>(edgeEffect);
    std::optional<bool> convOptions = options ? Converter::OptConvert<bool>(*options) : std::nullopt;
    // need check
    // ScrollableModelNG::SetEdgeEffect(frameNode, convEdgeEffect, convOptions);
}
void FadingEdgeImpl(Ark_NativePointer node,
                    const Opt_Boolean* enabled,
                    const Opt_FadingEdgeOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    std::optional<bool> fadingEdge;
    if (enabled) {
        fadingEdge = Converter::OptConvert<bool>(*enabled);
    }

    std::optional<Dimension> fadingEdgeLength;
    if (options) {
        fadingEdgeLength = Converter::OptConvert<Dimension>(*options);
    }
    Validator::ValidateNonNegative(fadingEdgeLength);
    // need check
    // ScrollableModelNG::SetFadingEdge(frameNode, fadingEdge, fadingEdgeLength);
}
} // ScrollableCommonMethodModifier
const GENERATED_ArkUIScrollableCommonMethodModifier* GetScrollableCommonMethodModifier()
{
    static const GENERATED_ArkUIScrollableCommonMethodModifier ArkUIScrollableCommonMethodModifierImpl {
        ScrollableCommonMethodModifier::ConstructImpl,
        ScrollableCommonMethodModifier::ScrollBarImpl,
        ScrollableCommonMethodModifier::ScrollBarColorImpl,
        ScrollableCommonMethodModifier::ScrollBarWidthImpl,
        ScrollableCommonMethodModifier::NestedScrollImpl,
        ScrollableCommonMethodModifier::EnableScrollInteractionImpl,
        ScrollableCommonMethodModifier::FrictionImpl,
        ScrollableCommonMethodModifier::OnScrollImpl,
        ScrollableCommonMethodModifier::OnReachStartImpl,
        ScrollableCommonMethodModifier::OnReachEndImpl,
        ScrollableCommonMethodModifier::OnScrollStartImpl,
        ScrollableCommonMethodModifier::OnScrollStopImpl,
        ScrollableCommonMethodModifier::FlingSpeedLimitImpl,
        ScrollableCommonMethodModifier::ClipContentImpl,
        ScrollableCommonMethodModifier::EdgeEffectImpl,
        ScrollableCommonMethodModifier::FadingEdgeImpl,
    };
    return &ArkUIScrollableCommonMethodModifierImpl;
}

}
