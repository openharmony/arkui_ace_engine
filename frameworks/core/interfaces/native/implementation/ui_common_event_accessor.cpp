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
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace UICommonEventAccessor {
void DestroyPeerImpl(Ark_UICommonEvent peer)
{
}
Ark_UICommonEvent CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetOnClickImpl(Ark_UICommonEvent peer,
                    const Opt_Callback_ClickEvent_Void* callback_)
{
}
void SetOnTouchImpl(Ark_UICommonEvent peer,
                    const Opt_Callback_TouchEvent_Void* callback_)
{
}
void SetOnAppearImpl(Ark_UICommonEvent peer,
                     const Opt_Callback_Void* callback_)
{
}
void SetOnDisappearImpl(Ark_UICommonEvent peer,
                        const Opt_Callback_Void* callback_)
{
}
void SetOnKeyEventImpl(Ark_UICommonEvent peer,
                       const Opt_Callback_KeyEvent_Void* callback_)
{
}
void SetOnFocusImpl(Ark_UICommonEvent peer,
                    const Opt_Callback_Void* callback_)
{
}
void SetOnBlurImpl(Ark_UICommonEvent peer,
                   const Opt_Callback_Void* callback_)
{
}
void SetOnHoverImpl(Ark_UICommonEvent peer,
                    const Opt_HoverCallback* callback_)
{
}
void SetOnMouseImpl(Ark_UICommonEvent peer,
                    const Opt_Callback_MouseEvent_Void* callback_)
{
}
void SetOnSizeChangeImpl(Ark_UICommonEvent peer,
                         const Opt_SizeChangeCallback* callback_)
{
}
void SetOnVisibleAreaApproximateChangeImpl(Ark_UICommonEvent peer,
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
