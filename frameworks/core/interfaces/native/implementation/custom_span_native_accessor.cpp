/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

#include "custom_span_peer.h"
#include "core/components_ng/base/frame_node.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CustomSpanNativeAccessor {
void DestroyPeerImpl(Ark_CustomSpanNative peer)
{
    if (peer) {
        peer->DecRefCount();
    }
}
Ark_CustomSpanNative ConstructImpl()
{
    auto peer = AceType::MakeRefPtr<CustomSpanNativePeer>();
    peer->IncRefCount();
    return reinterpret_cast<CustomSpanNativePeer *>(Referenced::RawPtr(peer));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void InvalidateImpl(Ark_CustomSpanNative peer)
{
    CHECK_NULL_VOID(peer);
    peer->Invalidate();
}
} // CustomSpanNativeAccessor
const GENERATED_ArkUICustomSpanNativeAccessor* GetCustomSpanNativeAccessor()
{
    static const GENERATED_ArkUICustomSpanNativeAccessor CustomSpanNativeAccessorImpl {
        CustomSpanNativeAccessor::DestroyPeerImpl,
        CustomSpanNativeAccessor::ConstructImpl,
        CustomSpanNativeAccessor::GetFinalizerImpl,
        CustomSpanNativeAccessor::InvalidateImpl,
    };
    return &CustomSpanNativeAccessorImpl;
}
}
