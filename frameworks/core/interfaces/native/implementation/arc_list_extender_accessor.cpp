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
#include "children_main_size_peer.h"
#include "color_metrics_peer.h"
#include "list_scroller_peer_impl.h"

#include "base/geometry/axis.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_model_static.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/interfaces/native/generated/interface/ui_node_api.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "frameworks/core/components/list/list_theme.h"
#include "frameworks/core/components_ng/pattern/scrollable/scrollable_model_static.h"
#include "frameworks/core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "frameworks/core/components_ng/pattern/list/list_properties.h"

namespace OHOS::Ace::NG::Converter {
    struct ArkListOptions {
        std::optional<int> initialIndex;
        std::optional<Ark_Scroller> scroller;
    };

    template<>
    ArkListOptions Convert(const Ark_ArkListOptions& src)
    {
        return {
            .initialIndex = OptConvert<int>(src.initialIndex),
            .scroller = OptConvert<Ark_Scroller>(src.scroller)
        };
    }
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ArcListExtenderAccessor {
Ark_NativePointer ArcListConstructorImpl(Ark_Int32 id)
{
    auto frameNode = ListModelStatic::CreateFrameNode(id, true);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
void SetArkListOptionsImpl(Ark_NativePointer node, const Opt_ArkListOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);

    auto optionsOpt = Converter::OptConvert<Converter::ArkListOptions>(*options);
    if (!optionsOpt.has_value()) {
        return;
    }

    auto initialIndex = optionsOpt.value().initialIndex;
    ListModelStatic::SetInitialIndex(frameNode, initialIndex);

    RefPtr<ScrollControllerBase> positionController = ListModelStatic::GetOrCreateController(frameNode);
    RefPtr<ScrollProxy> scrollBarProxy = ListModelStatic::GetOrCreateScrollBarProxy(frameNode);
    auto abstPeerPtrOpt = optionsOpt.value().scroller;
    CHECK_NULL_VOID(abstPeerPtrOpt);
    auto peerImplPtr = *abstPeerPtrOpt;
    CHECK_NULL_VOID(peerImplPtr);
    peerImplPtr->SetController(positionController);
    peerImplPtr->SetScrollBarProxy(scrollBarProxy);
}
void DigitalCrownSensitivityImpl(Ark_NativePointer node, const Opt_CrownSensitivity* sensitivity)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = sensitivity ? Converter::OptConvert<CrownSensitivity>(*sensitivity) : std::nullopt;
    ScrollableModelStatic::SetDigitalCrownSensitivity(frameNode, convValue);
#endif
}
void SpaceImpl(Ark_NativePointer node, const Opt_LengthMetrics* space)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto spaceOpt = Converter::OptConvert<Dimension>(*space);
    ListModelStatic::SetListSpace(frameNode, spaceOpt);
}
void ScrollBarImpl(Ark_NativePointer node, const Opt_BarState* status)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<DisplayMode> mode = Converter::OptConvert<DisplayMode>(*status);
    ListModelStatic::SetListScrollBar(frameNode, EnumToInt(mode));
}
void ScrollBarColorImpl(Ark_NativePointer node, const Opt_ColorMetrics* color)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> barColor = color ? Converter::OptConvert<Color>(*color) : std::nullopt;
    ScrollableModelStatic::SetScrollBarColor(frameNode, barColor);
}
void ScrollBarWidthImpl(Ark_NativePointer node, const Opt_LengthMetrics* width)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*width);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    ScrollableModelStatic::SetScrollBarWidth(frameNode, convValue);
}
void CachedCountImpl(Ark_NativePointer node, const Opt_Int32* count)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int>(*count);
    if (!convValue) {
        return;
    }
    ListModelStatic::SetCachedCount(frameNode, *convValue);
}
void ChainAnimationImpl(Ark_NativePointer node, const Opt_Boolean* enable)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*enable);
    if (!convValue) {
        return;
    }
    ListModelStatic::SetChainAnimation(frameNode, *convValue);
}
void ChildrenMainSizeImpl(Ark_NativePointer node, const Opt_ChildrenMainSize* size)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(size);
    if (!optValue) {
        return;
    }
    auto peer = *optValue;
    CHECK_NULL_VOID(peer);
    RefPtr<ListChildrenMainSize> handler = ListModelStatic::GetOrCreateListChildrenMainSize(frameNode);
    peer->SetHandler(handler);
}
void EnableScrollInteractionImpl(Ark_NativePointer node, const Opt_Boolean* enable)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*enable);
    if (!convValue) {
        return;
    }
    ListModelStatic::SetScrollEnabled(frameNode, *convValue);
}
void FadingEdgeImpl(Ark_NativePointer node, const Opt_Boolean* enable)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    std::optional<bool> fadingEdge;
    if (enable) {
        fadingEdge = Converter::OptConvert<bool>(*enable);
    }

    std::optional<Dimension> fadingEdgeLength;
    ScrollableModelStatic::SetFadingEdge(frameNode, fadingEdge, fadingEdgeLength);
}
void FrictionImpl(Ark_NativePointer node, const Opt_Float64* friction)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelStatic::SetListFriction(frameNode, Converter::OptConvert<float>(*friction));
}
void FlingSpeedLimitImpl(Ark_NativePointer node, const Opt_Float64* speed)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<double>(speed);
    if (!convValue) {
        return;
    }
    ScrollableModelStatic::SetMaxFlingSpeed(frameNode, *convValue);
}
void OnScrollIndexImpl(Ark_NativePointer node, const Opt_ArcScrollIndexHandler* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(handler);
    if (!optValue) {
        return;
    }
    auto onScrollIndex = [arkCallback = CallbackHelper(*optValue)]
            (const int32_t start, const int32_t end, const int32_t center) {
        auto arkStart = Converter::ArkValue<Ark_Int32>(start);
        auto arkEnd = Converter::ArkValue<Ark_Int32>(end);
        auto arkCenter = Converter::ArkValue<Ark_Int32>(center);
        arkCallback.Invoke(arkStart, arkEnd, arkCenter);
    };
    ListModelStatic::SetOnScrollIndex(frameNode, std::move(onScrollIndex));
}
void OnReachStartImpl(Ark_NativePointer node, const Opt_VoidCallback* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(handler);
    if (!optValue) {
        return;
    }
    auto onReachStart = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    ListModelStatic::SetOnReachStart(frameNode, std::move(onReachStart));
}
void OnReachEndImpl(Ark_NativePointer node, const Opt_VoidCallback* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(handler);
    if (!optValue) {
        return;
    }
    auto onReachEnd = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    ListModelStatic::SetOnReachEnd(frameNode, std::move(onReachEnd));
}
void OnScrollStartImpl(Ark_NativePointer node, const Opt_VoidCallback* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(handler);
    if (!optValue) {
        return;
    }
    auto onScrollStart = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    ListModelStatic::SetOnScrollStart(frameNode, std::move(onScrollStart));
}
void OnScrollStopImpl(Ark_NativePointer node, const Opt_VoidCallback* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(handler);
    if (!optValue) {
        return;
    }
    auto onScrollStop = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    ListModelStatic::SetOnScrollStop(frameNode, std::move(onScrollStop));
}
void OnWillScrollImpl(Ark_NativePointer node, const Opt_OnWillScrollCallback* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkCallback = Converter::OptConvertPtr<OnWillScrollCallback>(handler);
    if (arkCallback) {
        auto modelCallback = [callback = CallbackHelper(arkCallback.value())]
            (const Dimension& scrollOffset, const ScrollState& scrollState, const ScrollSource& scrollSource) ->
                ScrollFrameResult {
            auto arkScrollOffset = Converter::ArkValue<Ark_Float64>(scrollOffset);
            auto arkScrollState = Converter::ArkValue<Ark_ScrollState>(scrollState);
            auto arkScrollSource = Converter::ArkValue<Ark_ScrollSource>(scrollSource);
            auto resultOpt = callback.InvokeWithOptConvertResult<ScrollFrameResult, Opt_ScrollResult,
                Callback_Opt_ScrollResult_Void>(arkScrollOffset, arkScrollState, arkScrollSource);
            return resultOpt.value_or(ScrollFrameResult());
        };
        ScrollableModelStatic::SetOnWillScroll(frameNode, std::move(modelCallback));
    } else {
        ScrollableModelStatic::SetOnWillScroll(frameNode, nullptr);
    }
}
void OnDidScrollImpl(Ark_NativePointer node, const Opt_OnScrollCallback* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(handler);
    auto callValue = Converter::OptConvert<OnScrollCallback>(*handler);
    if (!callValue.has_value()) {
        return;
    }
    auto onDidScroll = [arkCallback = CallbackHelper(callValue.value())](
        Dimension oIn, ScrollState stateIn) {
            auto state = Converter::ArkValue<Ark_ScrollState>(stateIn);
            auto scrollOffset = Converter::ArkValue<Ark_Float64>(oIn);
            arkCallback.Invoke(scrollOffset, state);
    };
    ScrollableModelStatic::SetOnDidScroll(frameNode, std::move(onDidScroll));
}
} // ArcListExtenderAccessor
const GENERATED_ArkUIArcListExtenderAccessor* GetArcListExtenderAccessor()
{
    static const GENERATED_ArkUIArcListExtenderAccessor ArcListExtenderAccessorImpl {
        ArcListExtenderAccessor::ArcListConstructorImpl,
        ArcListExtenderAccessor::SetArkListOptionsImpl,
        ArcListExtenderAccessor::DigitalCrownSensitivityImpl,
        ArcListExtenderAccessor::SpaceImpl,
        ArcListExtenderAccessor::ScrollBarImpl,
        ArcListExtenderAccessor::ScrollBarColorImpl,
        ArcListExtenderAccessor::ScrollBarWidthImpl,
        ArcListExtenderAccessor::CachedCountImpl,
        ArcListExtenderAccessor::ChainAnimationImpl,
        ArcListExtenderAccessor::ChildrenMainSizeImpl,
        ArcListExtenderAccessor::EnableScrollInteractionImpl,
        ArcListExtenderAccessor::FadingEdgeImpl,
        ArcListExtenderAccessor::FrictionImpl,
        ArcListExtenderAccessor::FlingSpeedLimitImpl,
        ArcListExtenderAccessor::OnScrollIndexImpl,
        ArcListExtenderAccessor::OnReachStartImpl,
        ArcListExtenderAccessor::OnReachEndImpl,
        ArcListExtenderAccessor::OnScrollStartImpl,
        ArcListExtenderAccessor::OnScrollStopImpl,
        ArcListExtenderAccessor::OnWillScrollImpl,
        ArcListExtenderAccessor::OnDidScrollImpl,
    };
    return &ArcListExtenderAccessorImpl;
}

}
