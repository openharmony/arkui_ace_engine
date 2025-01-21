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
namespace GlobalScope_commonAccessor {
void DestroyPeerImpl(GlobalScope_commonPeer* peer)
{
}
Ark_NativePointer CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_NativePointer GetContextImpl(const Opt_CustomObject* component)
{
    return nullptr;
}
void PostCardActionImpl(const Ark_CustomObject* component,
                        const Ark_CustomObject* action)
{
}
Ark_NativePointer Dollar_rImpl(const Ark_String* value,
                               const Array_CustomObject* params)
{
    return nullptr;
}
Ark_NativePointer Dollar_rawfileImpl(const Ark_String* value)
{
    return nullptr;
}
void AnimateToImpl(const Ark_AnimateParam* value,
                   const Callback_Void* event)
{
}
void AnimateToImmediatelyImpl(const Ark_AnimateParam* value,
                              const Callback_Void* event)
{
}
Ark_Int32 Vp2pxImpl(const Ark_Number* value)
{
    return 0;
}
Ark_Int32 Px2vpImpl(const Ark_Number* value)
{
    return 0;
}
Ark_Int32 Fp2pxImpl(const Ark_Number* value)
{
    return 0;
}
Ark_Int32 Px2fpImpl(const Ark_Number* value)
{
    return 0;
}
Ark_Int32 Lpx2pxImpl(const Ark_Number* value)
{
    return 0;
}
Ark_Int32 Px2lpxImpl(const Ark_Number* value)
{
    return 0;
}
Ark_Boolean RequestFocusImpl(const Ark_String* value)
{
    return 0;
}
void SetCursorImpl(Ark_PointerStyle value)
{
}
void RestoreDefaultImpl()
{
}
} // GlobalScope_commonAccessor
const GENERATED_ArkUIGlobalScope_commonAccessor* GetGlobalScope_commonAccessor()
{
    static const GENERATED_ArkUIGlobalScope_commonAccessor GlobalScope_commonAccessorImpl {
        GlobalScope_commonAccessor::DestroyPeerImpl,
        GlobalScope_commonAccessor::CtorImpl,
        GlobalScope_commonAccessor::GetFinalizerImpl,
        GlobalScope_commonAccessor::GetContextImpl,
        GlobalScope_commonAccessor::PostCardActionImpl,
        GlobalScope_commonAccessor::Dollar_rImpl,
        GlobalScope_commonAccessor::Dollar_rawfileImpl,
        GlobalScope_commonAccessor::AnimateToImpl,
        GlobalScope_commonAccessor::AnimateToImmediatelyImpl,
        GlobalScope_commonAccessor::Vp2pxImpl,
        GlobalScope_commonAccessor::Px2vpImpl,
        GlobalScope_commonAccessor::Fp2pxImpl,
        GlobalScope_commonAccessor::Px2fpImpl,
        GlobalScope_commonAccessor::Lpx2pxImpl,
        GlobalScope_commonAccessor::Px2lpxImpl,
        GlobalScope_commonAccessor::RequestFocusImpl,
        GlobalScope_commonAccessor::SetCursorImpl,
        GlobalScope_commonAccessor::RestoreDefaultImpl,
    };
    return &GlobalScope_commonAccessorImpl;
}

struct GlobalScope_commonPeer {
    virtual ~GlobalScope_commonPeer() = default;
};
}
