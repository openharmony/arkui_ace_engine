/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
struct RawInputEventWrapperPeer {
    Ark_Union_MouseEvent_TouchEventProxy_KeyEvent event;
};

namespace RawInputEventWrapperAccessor {
namespace {
constexpr uint32_t MOUSE_EVENT_SELECTOR = 0;
constexpr uint32_t TOUCH_EVENT_SELECTOR = 1;
constexpr uint32_t KEY_EVENT_SELECTOR = 2;
} // namespace

void DestroyPeerImpl(Ark_RawInputEventWrapper peer)
{
    auto peerImpl = reinterpret_cast<RawInputEventWrapperPeer*>(peer);
    if (peerImpl) {
        delete peerImpl;
    }
}

Ark_RawInputEventWrapper ConstructImpl(const Ark_Union_MouseEvent_TouchEventProxy_KeyEvent* event)
{
    CHECK_NULL_RETURN(event, nullptr);
    auto* peer = new RawInputEventWrapperPeer();
    peer->event = *event;
    return reinterpret_cast<Ark_RawInputEventWrapper>(peer);
}

Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void*>(&DestroyPeerImpl);
}

Ark_Boolean IsMouseEventImpl(Ark_RawInputEventWrapper peer)
{
    auto peerImpl = reinterpret_cast<RawInputEventWrapperPeer*>(peer);
    return peerImpl != nullptr && peerImpl->event.selector == MOUSE_EVENT_SELECTOR;
}

Ark_Boolean IsTouchEventImpl(Ark_RawInputEventWrapper peer)
{
    auto peerImpl = reinterpret_cast<RawInputEventWrapperPeer*>(peer);
    return peerImpl != nullptr && peerImpl->event.selector == TOUCH_EVENT_SELECTOR;
}

Ark_Boolean IsKeyEventImpl(Ark_RawInputEventWrapper peer)
{
    auto peerImpl = reinterpret_cast<RawInputEventWrapperPeer*>(peer);
    return peerImpl != nullptr && peerImpl->event.selector == KEY_EVENT_SELECTOR;
}

Opt_MouseEvent AsMouseEventImpl(Ark_RawInputEventWrapper peer)
{
    auto peerImpl = reinterpret_cast<RawInputEventWrapperPeer*>(peer);
    if (peerImpl == nullptr || peerImpl->event.selector != MOUSE_EVENT_SELECTOR) {
        return Converter::ArkValue<Opt_MouseEvent>();
    }
    return Converter::ArkValue<Opt_MouseEvent>(peerImpl->event.value0);
}

Opt_TouchEventProxy AsTouchEventImpl(Ark_RawInputEventWrapper peer)
{
    auto peerImpl = reinterpret_cast<RawInputEventWrapperPeer*>(peer);
    if (peerImpl == nullptr || peerImpl->event.selector != TOUCH_EVENT_SELECTOR) {
        return Converter::ArkValue<Opt_TouchEventProxy>();
    }
    return Converter::ArkValue<Opt_TouchEventProxy>(peerImpl->event.value1);
}

Opt_KeyEvent AsKeyEventImpl(Ark_RawInputEventWrapper peer)
{
    auto peerImpl = reinterpret_cast<RawInputEventWrapperPeer*>(peer);
    if (peerImpl == nullptr || peerImpl->event.selector != KEY_EVENT_SELECTOR) {
        return Converter::ArkValue<Opt_KeyEvent>();
    }
    return Converter::ArkValue<Opt_KeyEvent>(peerImpl->event.value2);
}
} // namespace RawInputEventWrapperAccessor

const GENERATED_ArkUIRawInputEventWrapperAccessor* GetRawInputEventWrapperAccessor()
{
    static const GENERATED_ArkUIRawInputEventWrapperAccessor RawInputEventWrapperAccessorImpl {
        RawInputEventWrapperAccessor::DestroyPeerImpl,
        RawInputEventWrapperAccessor::ConstructImpl,
        RawInputEventWrapperAccessor::GetFinalizerImpl,
        RawInputEventWrapperAccessor::IsMouseEventImpl,
        RawInputEventWrapperAccessor::IsTouchEventImpl,
        RawInputEventWrapperAccessor::IsKeyEventImpl,
        RawInputEventWrapperAccessor::AsMouseEventImpl,
        RawInputEventWrapperAccessor::AsTouchEventImpl,
        RawInputEventWrapperAccessor::AsKeyEventImpl,
    };
    return &RawInputEventWrapperAccessorImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
