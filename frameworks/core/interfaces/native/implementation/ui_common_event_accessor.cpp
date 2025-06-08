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
#include "core/components_ng/base/view_abstract.h"
#include "core/interfaces/native/implementation/ui_common_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace UICommonEventAccessor {
void DestroyPeerImpl(Ark_UICommonEvent peer)
{
    delete peer;
}
Ark_UICommonEvent CtorImpl()
{
    return new UICommonEventPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetOnClickImpl(Ark_UICommonEvent peer,
                    const Opt_Callback_ClickEvent_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = AceType::RawPtr(refPtr);
    auto arkOnClick = callback_ ? Converter::OptConvert<Callback_ClickEvent_Void>(*callback_) : std::nullopt;
    
    std::function<void(GestureEvent&)> onClick = nullptr;
    if (arkOnClick) {
        onClick = [arkCallback = CallbackHelper(arkOnClick.value())](GestureEvent& info) {
            auto clickEvent = Converter::ArkClickEventSync(info);
            arkCallback.InvokeSync(clickEvent.ArkValue());
        };
    }
    ViewAbstract::SetOnClick(rawPtr, std::move(onClick));
}
void SetOnTouchImpl(Ark_UICommonEvent peer,
                    const Opt_Callback_TouchEvent_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = AceType::RawPtr(refPtr);
    auto arkOnTouch = callback_ ? Converter::OptConvert<Callback_TouchEvent_Void>(*callback_) : std::nullopt;
    std::function<void(TouchEventInfo&)> onTouch = nullptr;
    if (arkOnTouch) {
        onTouch = [arkCallback = CallbackHelper(arkOnTouch.value())](TouchEventInfo& info) {
            auto touchEvent = Converter::ArkTouchEventSync(info);
            arkCallback.InvokeSync(touchEvent.ArkValue());
        };
    }
    ViewAbstract::SetOnTouch(rawPtr, std::move(onTouch));
}
void SetOnAppearImpl(Ark_UICommonEvent peer,
                     const Opt_Callback_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = AceType::RawPtr(refPtr);
    auto arkOnAppear = callback_ ? Converter::OptConvert<Callback_Void>(*callback_) : std::nullopt;
    std::function<void()> onAppear = nullptr;
    if (arkOnAppear) {
        onAppear = [arkCallback = CallbackHelper(arkOnAppear.value())]() {
            arkCallback.Invoke();
        };
    }
    ViewAbstract::SetOnAppear(rawPtr, std::move(onAppear));
}
void SetOnDisappearImpl(Ark_UICommonEvent peer,
                        const Opt_Callback_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = AceType::RawPtr(refPtr);
    auto arkOnDisAppear = callback_ ? Converter::OptConvert<Callback_Void>(*callback_) : std::nullopt;
    std::function<void()> onDisAppear = nullptr;
    if (arkOnDisAppear) {
        onDisAppear = [arkCallback = CallbackHelper(arkOnDisAppear.value())]() {
            arkCallback.Invoke();
        };
    }
    ViewAbstract::SetOnDisappear(rawPtr, std::move(onDisAppear));
}
void SetOnKeyEventImpl(Ark_UICommonEvent peer,
                       const Opt_Callback_KeyEvent_Void* callback_)
{
}
void SetOnFocusImpl(Ark_UICommonEvent peer,
                    const Opt_Callback_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = AceType::RawPtr(refPtr);
    auto arkOnFocus = callback_ ? Converter::OptConvert<Callback_Void>(*callback_) : std::nullopt;
    std::function<void()> onFocus = nullptr;
    if (arkOnFocus) {
        onFocus = [arkCallback = CallbackHelper(arkOnFocus.value())]() {
            arkCallback.Invoke();
        };
    }
    ViewAbstract::SetOnFocus(rawPtr, std::move(onFocus));
}
void SetOnBlurImpl(Ark_UICommonEvent peer,
                   const Opt_Callback_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = AceType::RawPtr(refPtr);
    auto arkOnBlur = callback_ ? Converter::OptConvert<Callback_Void>(*callback_) : std::nullopt;
    std::function<void()> onBlur = nullptr;
    if (arkOnBlur) {
        onBlur = [arkCallback = CallbackHelper(arkOnBlur.value())]() {
            arkCallback.Invoke();
        };
    }
    ViewAbstract::SetOnBlur(rawPtr, std::move(onBlur));
}
void SetOnHoverImpl(Ark_UICommonEvent peer,
                    const Opt_HoverCallback* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = AceType::RawPtr(refPtr);
    auto arkOnHover = callback_ ? Converter::OptConvert<HoverCallback>(*callback_) : std::nullopt;
    std::function<void(bool, HoverInfo&)> onHover = nullptr;
    if (arkOnHover) {
        onHover = [arkCallback = CallbackHelper(arkOnHover.value())](bool isHover, HoverInfo& info) {
            auto hoverEvent = Converter::ArkHoverEventSync(info);
            auto arkIsHover = Converter::ArkValue<Ark_Boolean>(isHover);
            arkCallback.InvokeSync(arkIsHover, hoverEvent.ArkValue());
        };
    }
    ViewAbstract::SetOnHover(rawPtr, std::move(onHover));
}
void SetOnMouseImpl(Ark_UICommonEvent peer,
                    const Opt_Callback_MouseEvent_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = AceType::RawPtr(refPtr);
    auto arkOnMouse = callback_ ? Converter::OptConvert<Callback_MouseEvent_Void>(*callback_) : std::nullopt;
    std::function<void(MouseInfo&)> onMouse = nullptr;
    if (arkOnMouse) {
        onMouse = [arkCallback = CallbackHelper(arkOnMouse.value())](MouseInfo& info) {
            auto mouseEvent = Converter::ArkMouseEventSync(info);
            arkCallback.InvokeSync(mouseEvent.ArkValue());
        };
    }
    ViewAbstract::SetOnMouse(rawPtr, std::move(onMouse));
}
void SetOnSizeChangeImpl(Ark_UICommonEvent peer,
                         const Opt_SizeChangeCallback* callback_)
{
}
void SetOnVisibleAreaApproximateChangeImpl(Ark_UICommonEvent peer,
                                           const Ark_VisibleAreaEventOptions* options,
                                           const Opt_VisibleAreaChangeCallback* event)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(options);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = AceType::RawPtr(refPtr);
    auto arkOnVisibleChange = event ? Converter::OptConvert<VisibleAreaChangeCallback>(*event) : std::nullopt;
    CHECK_NULL_VOID(arkOnVisibleChange);
    std::function<void(bool, double)> onVisibleChange = nullptr;
    if (arkOnVisibleChange) {
        onVisibleChange = [arkCallback = CallbackHelper(arkOnVisibleChange.value())]
        (bool isExpanding, double currentRatio) {
            auto arkIsExpanding = Converter::ArkValue<Ark_Boolean>(isExpanding);
            auto arkCurrentRatio = Converter::ArkValue<Ark_Number>(currentRatio);
            arkCallback.Invoke(arkIsExpanding, arkCurrentRatio);
        };
    }
    std::vector<double> ratioList = Converter::Convert<std::vector<double>>(options->ratios);
    ViewAbstract::SetOnVisibleChange(rawPtr, std::move(onVisibleChange), ratioList);
}
} // UICommonEventAccessor
const GENERATED_ArkUIUICommonEventAccessor* GetUICommonEventAccessor()
{
    static const GENERATED_ArkUIUICommonEventAccessor UICommonEventAccessorImpl {
        UICommonEventAccessor::DestroyPeerImpl,
        UICommonEventAccessor::CtorImpl,
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
}
