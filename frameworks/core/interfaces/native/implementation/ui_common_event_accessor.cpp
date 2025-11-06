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
#include "core/components_ng/base/view_abstract.h"
#include "core/interfaces/native/implementation/ui_common_event_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUIUICommonEventAccessor* GetUICommonEventAccessor();
namespace UICommonEventAccessor {
void DestroyPeerImpl(Ark_UICommonEvent peer)
{
    delete peer;
}
Ark_UICommonEvent ConstructImpl()
{
    return new UICommonEventPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void*>(&DestroyPeerImpl);
}
void SetOnClickImpl(Ark_UICommonEvent peer, const Opt_Callback_ClickEvent_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnClick = Converter::GetOptPtr(callback_);
    if (arkOnClick) {
        auto onClick = [arkCallback = CallbackHelper(arkOnClick.value())](GestureEvent& info) {
            auto clickEvent = Converter::ArkClickEventSync(info);
            arkCallback.InvokeSync(clickEvent.ArkValue());
        };
        ViewAbstract::SetJSFrameNodeOnClick(rawPtr, std::move(onClick));
    } else {
        ViewAbstract::ClearJSFrameNodeOnClick(rawPtr);
    }
}
void SetOnTouchImpl(Ark_UICommonEvent peer, const Opt_Callback_TouchEvent_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnTouch = Converter::GetOptPtr(callback_);
    if (arkOnTouch) {
        auto onTouch = [arkCallback = CallbackHelper(arkOnTouch.value())](TouchEventInfo& info) {
            auto touchEvent = Converter::ArkTouchEventSync(info);
            arkCallback.InvokeSync(touchEvent.ArkValue());
        };
        ViewAbstract::SetJSFrameNodeOnTouch(rawPtr, std::move(onTouch));
    } else {
        ViewAbstract::ClearJSFrameNodeOnTouch(rawPtr);
    }
}
void SetOnAppearImpl(Ark_UICommonEvent peer, const Opt_Callback_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnAppear = Converter::GetOptPtr(callback_);
    if (arkOnAppear) {
        auto onAppear = [arkCallback = CallbackHelper(arkOnAppear.value())]() { arkCallback.InvokeSync(); };
        ViewAbstract::SetJSFrameNodeOnAppear(rawPtr, std::move(onAppear));
    } else {
        ViewAbstract::ClearJSFrameNodeOnAppear(rawPtr);
    }
}
void SetOnDisappearImpl(Ark_UICommonEvent peer, const Opt_Callback_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnDisAppear = Converter::GetOptPtr(callback_);
    if (arkOnDisAppear) {
        auto onDisAppear = [arkCallback = CallbackHelper(arkOnDisAppear.value())]() { arkCallback.InvokeSync(); };
        ViewAbstract::SetJSFrameNodeOnDisappear(rawPtr, std::move(onDisAppear));
    } else {
        ViewAbstract::ClearJSFrameNodeOnDisappear(rawPtr);
    }
}
void SetOnKeyEventImpl(Ark_UICommonEvent peer, const Opt_Callback_KeyEvent_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);

    std::optional<Callback_KeyEvent_Void> arkOnKey = callback_ ? Converter::GetOpt(*callback_) : std::nullopt;
    if (arkOnKey) {
        auto onKey = [arkCallback = CallbackHelper(arkOnKey.value())](KeyEventInfo& info) {
            auto keyEvent = Converter::ArkKeyEventSync(info);
            arkCallback.InvokeSync(keyEvent.ArkValue());
            LOGW("arkCallback does not return value");
            return false;
        };
        ViewAbstract::SetJSFrameNodeOnKeyCallback(rawPtr, std::move(onKey));
    } else {
        ViewAbstract::ClearJSFrameNodeOnKeyCallback(rawPtr);
    }
}
void SetOnFocusImpl(Ark_UICommonEvent peer, const Opt_Callback_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnFocus = Converter::GetOptPtr(callback_);
    if (arkOnFocus) {
        auto onFocus = [arkCallback = CallbackHelper(arkOnFocus.value())]() { arkCallback.Invoke(); };
        ViewAbstract::SetJSFrameNodeOnFocusCallback(rawPtr, std::move(onFocus));
    } else {
        ViewAbstract::ClearJSFrameNodeOnFocusCallback(rawPtr);
    }
}
void SetOnBlurImpl(Ark_UICommonEvent peer, const Opt_Callback_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnBlur = Converter::GetOptPtr(callback_);
    if (arkOnBlur) {
        auto onBlur = [arkCallback = CallbackHelper(arkOnBlur.value())]() { arkCallback.Invoke(); };
        ViewAbstract::SetJSFrameNodeOnBlurCallback(rawPtr, std::move(onBlur));
    } else {
        ViewAbstract::ClearJSFrameNodeOnBlurCallback(rawPtr);
    }
}
void SetOnHoverImpl(Ark_UICommonEvent peer, const Opt_HoverCallback* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnHover = Converter::GetOptPtr(callback_);
    if (arkOnHover) {
        auto onHover = [arkCallback = CallbackHelper(arkOnHover.value())](bool isHover, HoverInfo& info) {
            auto hoverEvent = Converter::ArkHoverEventSync(info);
            auto arkIsHover = Converter::ArkValue<Ark_Boolean>(isHover);
            arkCallback.InvokeSync(arkIsHover, hoverEvent.ArkValue());
        };
        ViewAbstract::SetJSFrameNodeOnHover(rawPtr, std::move(onHover));
    } else {
        ViewAbstract::ClearJSFrameNodeOnHover(rawPtr);
    }
}
void SetOnMouseImpl(Ark_UICommonEvent peer, const Opt_Callback_MouseEvent_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnMouse = Converter::GetOptPtr(callback_);
    if (arkOnMouse) {
        auto onMouse = [arkCallback = CallbackHelper(arkOnMouse.value())](MouseInfo& info) {
            auto mouseEvent = Converter::ArkMouseEventSync(info);
            arkCallback.InvokeSync(mouseEvent.ArkValue());
        };
        ViewAbstract::SetJSFrameNodeOnMouse(rawPtr, std::move(onMouse));
    } else {
        ViewAbstract::ClearJSFrameNodeOnMouse(rawPtr);
    }
}
void SetOnSizeChangeImpl(Ark_UICommonEvent peer, const Opt_SizeChangeCallback* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnSizeChanged = Converter::GetOptPtr(callback_);
    if (arkOnSizeChanged) {
        auto onSizeChanged = [arkCallback = CallbackHelper(arkOnSizeChanged.value())](
                                 const RectF& oldRect, const RectF& rect) {
            Converter::ConvContext ctx;
            Ark_SizeOptions oldValue;
            oldValue.height = Converter::ArkValue<Opt_Length>(PipelineBase::Px2VpWithCurrentDensity(oldRect.Height()),
                &ctx);
            oldValue.width = Converter::ArkValue<Opt_Length>(PipelineBase::Px2VpWithCurrentDensity(oldRect.Width()),
                &ctx);
            Ark_SizeOptions newValue;
            newValue.height = Converter::ArkValue<Opt_Length>(PipelineBase::Px2VpWithCurrentDensity(rect.Height()),
                &ctx);
            newValue.width = Converter::ArkValue<Opt_Length>(PipelineBase::Px2VpWithCurrentDensity(rect.Width()),
                &ctx);
            arkCallback.Invoke(oldValue, newValue);
        };
        ViewAbstract::SetJSFrameNodeOnSizeChange(rawPtr, std::move(onSizeChanged));
    } else {
        ViewAbstract::ClearJSFrameNodeOnSizeChange(rawPtr);
    }
}
void SetOnVisibleAreaApproximateChangeImpl(
    Ark_UICommonEvent peer, const Ark_VisibleAreaEventOptions* options, const Opt_VisibleAreaChangeCallback* event)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(options);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnVisibleChange = Converter::OptConvertPtr<VisibleAreaChangeCallback>(event);
    if (!arkOnVisibleChange.has_value()) {
        ViewAbstract::ClearJSFrameNodeOnVisibleAreaApproximateChange(rawPtr);
        return;
    }
    auto onVisibleChange = [arkCallback = CallbackHelper(arkOnVisibleChange.value())](
                               bool isExpanding, double currentRatio) {
        auto arkIsExpanding = Converter::ArkValue<Ark_Boolean>(isExpanding);
        auto arkCurrentRatio = Converter::ArkValue<Ark_Float64>(currentRatio);
        arkCallback.Invoke(arkIsExpanding, arkCurrentRatio);
    };
    std::vector<double> ratioList = Converter::Convert<std::vector<double>>(options->ratios);
    auto expectedUpdateIntervalValue = Converter::OptConvert<int32_t>(options->expectedUpdateInterval);
    if (expectedUpdateIntervalValue.has_value()) {
        ViewAbstract::SetJSFrameNodeOnVisibleAreaApproximateChange(
            rawPtr, std::move(onVisibleChange), ratioList, expectedUpdateIntervalValue.value());
    } else {
        ViewAbstract::SetJSFrameNodeOnVisibleAreaApproximateChange(rawPtr, std::move(onVisibleChange), ratioList);
    }
}
} // namespace UICommonEventAccessor
const GENERATED_ArkUIUICommonEventAccessor* GetUICommonEventAccessor()
{
    static const GENERATED_ArkUIUICommonEventAccessor UICommonEventAccessorImpl {
        UICommonEventAccessor::DestroyPeerImpl,
        UICommonEventAccessor::ConstructImpl,
        UICommonEventAccessor::GetFinalizerImpl,
        UICommonEventAccessor::SetOnClickImpl,
        UICommonEventAccessor::SetOnTouchImpl,
        UICommonEventAccessor::SetOnAppearImpl,
        UICommonEventAccessor::SetOnDisappearImpl,
        UICommonEventAccessor::SetOnKeyEventImpl,
        UICommonEventAccessor::SetOnFocusImpl,
        UICommonEventAccessor::SetOnBlurImpl,
        UICommonEventAccessor::SetOnHoverImpl,
        UICommonEventAccessor::SetOnMouseImpl,
        UICommonEventAccessor::SetOnSizeChangeImpl,
        UICommonEventAccessor::SetOnVisibleAreaApproximateChangeImpl,
    };
    return &UICommonEventAccessorImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
