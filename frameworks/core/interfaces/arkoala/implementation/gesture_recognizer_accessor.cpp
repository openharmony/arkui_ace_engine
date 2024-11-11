/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GestureRecognizerAccessor {
GestureRecognizerPeer* CtorImpl()
{
    return 0;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
void GetTagImpl(GestureRecognizerPeer* peer)
{
}
Ark_NativePointer GetTypeImpl(GestureRecognizerPeer* peer)
{
    return 0;
}
Ark_Boolean IsBuiltInImpl(GestureRecognizerPeer* peer)
{
    return 0;
}
void SetEnabledImpl(GestureRecognizerPeer* peer,
                    Ark_Boolean isEnabled)
{
}
Ark_Boolean IsEnabledImpl(GestureRecognizerPeer* peer)
{
    return 0;
}
Ark_NativePointer GetStateImpl(GestureRecognizerPeer* peer)
{
    return 0;
}
Ark_NativePointer GetEventTargetInfoImpl(GestureRecognizerPeer* peer)
{
    return 0;
}
Ark_Boolean IsValidImpl(GestureRecognizerPeer* peer)
{
    return 0;
}
} // GestureRecognizerAccessor
const GENERATED_ArkUIGestureRecognizerAccessor* GetGestureRecognizerAccessor()
{
    static const GENERATED_ArkUIGestureRecognizerAccessor GestureRecognizerAccessorImpl {
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
    };
    return &GestureRecognizerAccessorImpl;
}

}
