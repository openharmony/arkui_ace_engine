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
namespace TouchEventAccessor {
void DestroyPeerImpl(Ark_TouchEvent peer)
{
}
Ark_TouchEvent CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Array_HistoricalPoint GetHistoricalPointsImpl(Ark_TouchEvent peer)
{
    return {};
}
Ark_TouchType GetTypeImpl(Ark_TouchEvent peer)
{
    return {};
}
void SetTypeImpl(Ark_TouchEvent peer,
                 Ark_TouchType type)
{
}
Array_TouchObject GetTouchesImpl(Ark_TouchEvent peer)
{
    return {};
}
void SetTouchesImpl(Ark_TouchEvent peer,
                    const Array_TouchObject* touches)
{
}
Array_TouchObject GetChangedTouchesImpl(Ark_TouchEvent peer)
{
    return {};
}
void SetChangedTouchesImpl(Ark_TouchEvent peer,
                           const Array_TouchObject* changedTouches)
{
}
Callback_Void GetStopPropagationImpl(Ark_TouchEvent peer)
{
    return {};
}
void SetStopPropagationImpl(Ark_TouchEvent peer,
                            const Callback_Void* stopPropagation)
{
}
Callback_Void GetPreventDefaultImpl(Ark_TouchEvent peer)
{
    return {};
}
void SetPreventDefaultImpl(Ark_TouchEvent peer,
                           const Callback_Void* preventDefault)
{
}
} // TouchEventAccessor
const GENERATED_ArkUITouchEventAccessor* GetTouchEventAccessor()
{
    static const GENERATED_ArkUITouchEventAccessor TouchEventAccessorImpl {
        TouchEventAccessor::DestroyPeerImpl,
        TouchEventAccessor::CtorImpl,
        TouchEventAccessor::GetFinalizerImpl,
        TouchEventAccessor::GetHistoricalPointsImpl,
        TouchEventAccessor::GetTypeImpl,
        TouchEventAccessor::SetTypeImpl,
        TouchEventAccessor::GetTouchesImpl,
        TouchEventAccessor::SetTouchesImpl,
        TouchEventAccessor::GetChangedTouchesImpl,
        TouchEventAccessor::SetChangedTouchesImpl,
        TouchEventAccessor::GetStopPropagationImpl,
        TouchEventAccessor::SetStopPropagationImpl,
        TouchEventAccessor::GetPreventDefaultImpl,
        TouchEventAccessor::SetPreventDefaultImpl,
    };
    return &TouchEventAccessorImpl;
}

}
