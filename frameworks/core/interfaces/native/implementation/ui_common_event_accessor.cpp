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
#include "core/interfaces/native/implementation/ui_common_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace UICommonEventAccessor {
void DestroyPeerImpl(UICommonEventPeer* peer)
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
void SetOnClickImpl(UICommonEventPeer* peer,
                    const Opt_Callback_ClickEvent_Void* callback_)
{
}
void SetOnTouchImpl(UICommonEventPeer* peer,
                    const Opt_Callback_TouchEvent_Void* callback_)
{
}
void SetOnAppearImpl(UICommonEventPeer* peer,
                     const Opt_Callback_Void* callback_)
{
}
void SetOnDisappearImpl(UICommonEventPeer* peer,
                        const Opt_Callback_Void* callback_)
{
}
void SetOnKeyEventImpl(UICommonEventPeer* peer,
                       const Opt_Callback_KeyEvent_Void* callback_)
{
}
void SetOnFocusImpl(UICommonEventPeer* peer,
                    const Opt_Callback_Void* callback_)
{
}
void SetOnBlurImpl(UICommonEventPeer* peer,
                   const Opt_Callback_Void* callback_)
{
}
void SetOnHoverImpl(UICommonEventPeer* peer,
                    const Opt_HoverCallback* callback_)
{
}
void SetOnMouseImpl(UICommonEventPeer* peer,
                    const Opt_Callback_MouseEvent_Void* callback_)
{
}
void SetOnSizeChangeImpl(UICommonEventPeer* peer,
                         const Opt_SizeChangeCallback* callback_)
{
}
void SetOnVisibleAreaApproximateChangeImpl(UICommonEventPeer* peer,
                                           const Ark_VisibleAreaEventOptions* options,
                                           const Opt_VisibleAreaChangeCallback* event)
{
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
