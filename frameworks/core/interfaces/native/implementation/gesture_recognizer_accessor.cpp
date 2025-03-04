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
namespace GestureRecognizerAccessor {
void DestroyPeerImpl(Ark_GestureRecognizer peer)
{
}
Ark_GestureRecognizer CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetTagImpl(Ark_GestureRecognizer peer)
{
    return {};
}
Ark_GestureControl_GestureType GetTypeImpl(Ark_GestureRecognizer peer)
{
    return {};
}
Ark_Boolean IsBuiltInImpl(Ark_GestureRecognizer peer)
{
    return {};
}
void SetEnabledImpl(Ark_GestureRecognizer peer,
                    Ark_Boolean isEnabled)
{
}
Ark_Boolean IsEnabledImpl(Ark_GestureRecognizer peer)
{
    return {};
}
Ark_GestureRecognizerState GetStateImpl(Ark_GestureRecognizer peer)
{
    return {};
}
Ark_EventTargetInfo GetEventTargetInfoImpl(Ark_GestureRecognizer peer)
{
    return {};
}
Ark_Boolean IsValidImpl(Ark_GestureRecognizer peer)
{
    return {};
}
Ark_Number GetFingerCountImpl(Ark_GestureRecognizer peer)
{
    return {};
}
Ark_Boolean IsFingerCountLimitImpl(Ark_GestureRecognizer peer)
{
    return {};
}
} // GestureRecognizerAccessor
const GENERATED_ArkUIGestureRecognizerAccessor* GetGestureRecognizerAccessor()
{
    static const GENERATED_ArkUIGestureRecognizerAccessor GestureRecognizerAccessorImpl {
        GestureRecognizerAccessor::DestroyPeerImpl,
        GestureRecognizerAccessor::CtorImpl,
        GestureRecognizerAccessor::GetFinalizerImpl,
        GestureRecognizerAccessor::GetTagImpl,
        GestureRecognizerAccessor::GetTypeImpl,
        GestureRecognizerAccessor::IsBuiltInImpl,
        GestureRecognizerAccessor::SetEnabledImpl,
        GestureRecognizerAccessor::IsEnabledImpl,
        GestureRecognizerAccessor::GetStateImpl,
        GestureRecognizerAccessor::GetEventTargetInfoImpl,
        GestureRecognizerAccessor::IsValidImpl,
        GestureRecognizerAccessor::GetFingerCountImpl,
        GestureRecognizerAccessor::IsFingerCountLimitImpl,
    };
    return &GestureRecognizerAccessorImpl;
}

}
