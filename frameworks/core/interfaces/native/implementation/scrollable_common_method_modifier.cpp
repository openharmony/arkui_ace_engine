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
#include "core/components_ng/pattern/scroll/scroll_model_static.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_static.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
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
    return { .offset = Convert<Dimension>(src.xOffset)
    };
}

template<>
RefPtr<ShapeRect> Convert(const Ark_RectShape& src)
{
    CHECK_NULL_RETURN(src, nullptr);
    return src->rectShape;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScrollableCommonMethodModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
void SetScrollBarImpl(Ark_NativePointer node,
                      const Opt_BarState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<DisplayMode>(value);
    ScrollableModelStatic::SetScrollBarMode(frameNode, convValue);
}
void SetScrollBarColorImpl(Ark_NativePointer node,
                           const Opt_Union_Color_I32_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    ScrollableModelStatic::SetScrollBarColor(frameNode, convValue);
}
void SetScrollBarWidthImpl(Ark_NativePointer node,
                           const Opt_Union_F64_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    ScrollableModelStatic::SetScrollBarWidth(frameNode, convValue);
}
void SetNestedScrollImpl(Ark_NativePointer node,
                         const Opt_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::GetOptPtr(value);
    if (!convValue) {
        ScrollableModelStatic::SetNestedScroll(frameNode, std::nullopt, std::nullopt);
        return;
    }
    auto forward = Converter::OptConvert<NestedScrollMode>(convValue->scrollForward);
    auto backward = Converter::OptConvert<NestedScrollMode>(convValue->scrollBackward);
    ScrollableModelStatic::SetNestedScroll(frameNode, forward, backward);
}
void SetEnableScrollInteractionImpl(Ark_NativePointer node,
                                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    auto layoutProp = frameNode->GetLayoutPropertyPtr<LayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    const auto id = AceType::TypeId(layoutProp);
    if (GridLayoutProperty::TypeId() == id) {
        GridModelNG::SetScrollEnabled(frameNode, convValue.value_or(true));
    } else if (ListLayoutProperty::TypeId() == id) {
        ListModelNG::SetScrollEnabled(frameNode, convValue.value_or(true));
    } else if (ScrollLayoutProperty::TypeId() == id) {
        ScrollModelStatic::SetScrollEnabled(frameNode, convValue.value_or(true));
    } else if (WaterFlowLayoutProperty::TypeId() == id) {
        WaterFlowModelNG::SetScrollEnabled(frameNode, convValue.value_or(true));
    }
}
void SetFrictionImpl(Ark_NativePointer node,
                     const Opt_Union_F64_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    ScrollableModelStatic::SetFriction(frameNode, convValue);
}
void SetOnReachStartImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ScrollableModelStatic::SetOnReachStart(frameNode, nullptr);
        return;
    }
    auto modelCallback = [callbackHelper = CallbackHelper(*optValue)]() {
        callbackHelper.Invoke();
    };
    ScrollableModelStatic::SetOnReachStart(frameNode, std::move(modelCallback));
}
void SetOnReachEndImpl(Ark_NativePointer node,
                       const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ScrollableModelStatic::SetOnReachEnd(frameNode, nullptr);
        return;
    }
    auto modelCallback = [callbackHelper = CallbackHelper(*optValue)]() {
        callbackHelper.Invoke();
    };
    ScrollableModelStatic::SetOnReachEnd(frameNode, std::move(modelCallback));
}
void SetOnScrollStartImpl(Ark_NativePointer node,
                          const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ScrollableModelStatic::SetOnScrollStart(frameNode, nullptr);
        return;
    }
    auto modelCallback = [callbackHelper = CallbackHelper(*optValue)]() {
        callbackHelper.Invoke();
    };
    ScrollableModelStatic::SetOnScrollStart(frameNode, std::move(modelCallback));
}
void SetOnScrollStopImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ScrollableModelStatic::SetOnScrollStop(frameNode, nullptr);
        return;
    }
    auto modelCallback = [callbackHelper = CallbackHelper(*optValue)]() {
        callbackHelper.Invoke();
    };
    ScrollableModelStatic::SetOnScrollStop(frameNode, std::move(modelCallback));
}
void SetFlingSpeedLimitImpl(Ark_NativePointer node,
                            const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<double>(value);
    ScrollableModelStatic::SetMaxFlingSpeed(frameNode, *convValue);
}
void SetClipContentImpl(Ark_NativePointer node,
                        const Opt_Union_ContentClipMode_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    Converter::VisitUnion(*value,
        [frameNode](const Ark_ContentClipMode& arkMode) {
            auto mode = Converter::OptConvert<ContentClipMode>(arkMode);
            // mode cannot be nullopt, because in model created pair for lauout property
            ScrollableModelStatic::SetContentClip(frameNode, mode.value_or(ContentClipMode::DEFAULT), nullptr);
        },
        [frameNode](const Ark_RectShape& value) {
            auto rectShape = Converter::Convert<RefPtr<ShapeRect>>(value);
            if (rectShape) {
                ScrollableModelStatic::SetContentClip(frameNode, ContentClipMode::CUSTOM, rectShape);
            } else {
                ScrollableModelStatic::SetContentClip(frameNode, ContentClipMode::DEFAULT, nullptr);
            }
        },
        [frameNode]() {
            ScrollableModelStatic::SetContentClip(frameNode, ContentClipMode::DEFAULT, nullptr);
        });
}
void SetDigitalCrownSensitivityImpl(Ark_NativePointer node,
                                    const Opt_CrownSensitivity* value)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<CrownSensitivity>(value);
    ScrollableModelStatic::SetDigitalCrownSensitivity(frameNode, convValue);
#endif
}
void SetBackToTopImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ScrollableModelStatic::ResetBackToTop(frameNode);
        return;
    }
    ScrollableModelStatic::SetBackToTop(frameNode, *convValue);
}
void SetEdgeEffectImpl(Ark_NativePointer node,
                       const Opt_EdgeEffect* edgeEffect,
                       const Opt_EdgeEffectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convEdgeEffect = Converter::OptConvert<EdgeEffect>(*edgeEffect);

    bool alwaysEnabled = true;
    EffectEdge edge = EffectEdge::ALL;
    auto edgeEffectOptions = options ? Converter::GetOpt(*options) : std::nullopt;
    if (edgeEffectOptions) {
        alwaysEnabled = Converter::Convert<bool>(edgeEffectOptions.value().alwaysEnabled);
        auto value = Converter::OptConvert<int32_t>(edgeEffectOptions.value().effectEdge);
        if (value.has_value()) {
            edge = static_cast<EffectEdge>(value.value());
        }
    }
    ScrollableModelStatic::SetEdgeEffect(frameNode, convEdgeEffect, alwaysEnabled, edge);
}
void SetFadingEdgeImpl(Ark_NativePointer node,
                       const Opt_Boolean* enabled,
                       const Opt_FadingEdgeOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fadingEdge = Converter::OptConvertPtr<bool>(enabled);
    auto fadingEdgeLength = Converter::OptConvertPtr<Dimension>(options);
    Validator::ValidateNonNegative(fadingEdgeLength);
    ScrollableModelStatic::SetFadingEdge(frameNode, fadingEdge, fadingEdgeLength);
}
} // ScrollableCommonMethodModifier
const GENERATED_ArkUIScrollableCommonMethodModifier* GetScrollableCommonMethodModifier()
{
    static const GENERATED_ArkUIScrollableCommonMethodModifier ArkUIScrollableCommonMethodModifierImpl {
        ScrollableCommonMethodModifier::ConstructImpl,
        ScrollableCommonMethodModifier::SetScrollBarImpl,
        ScrollableCommonMethodModifier::SetScrollBarColorImpl,
        ScrollableCommonMethodModifier::SetScrollBarWidthImpl,
        ScrollableCommonMethodModifier::SetNestedScrollImpl,
        ScrollableCommonMethodModifier::SetEnableScrollInteractionImpl,
        ScrollableCommonMethodModifier::SetFrictionImpl,
        ScrollableCommonMethodModifier::SetOnReachStartImpl,
        ScrollableCommonMethodModifier::SetOnReachEndImpl,
        ScrollableCommonMethodModifier::SetOnScrollStartImpl,
        ScrollableCommonMethodModifier::SetOnScrollStopImpl,
        ScrollableCommonMethodModifier::SetFlingSpeedLimitImpl,
        ScrollableCommonMethodModifier::SetClipContentImpl,
        ScrollableCommonMethodModifier::SetDigitalCrownSensitivityImpl,
        ScrollableCommonMethodModifier::SetBackToTopImpl,
        ScrollableCommonMethodModifier::SetEdgeEffectImpl,
        ScrollableCommonMethodModifier::SetFadingEdgeImpl,
    };
    return &ArkUIScrollableCommonMethodModifierImpl;
}

}
