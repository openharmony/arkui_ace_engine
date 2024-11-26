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
#include "core/interfaces/native/utility/converter.h"

#include "drawing_rendering_context_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DrawingRenderingContextAccessor {
static void DestroyPeer(DrawingRenderingContextPeerImpl* peerImpl)
{
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
DrawingRenderingContextPeer* CtorImpl(const Opt_CustomObject* unit)
{
    auto peerImpl = Referenced::MakeRefPtr<DrawingRenderingContextPeerImpl>();
    peerImpl->IncRefCount();

    LOGE("ARKOALA DrawingRenderingContextAccessor::CtorImpl -> CustomObject is not supported.");
    return reinterpret_cast<DrawingRenderingContextPeer *>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<Ark_NativePointer>(&DestroyPeer);
}
void InvalidateImpl(DrawingRenderingContextPeer* peer)
{
    auto peerImpl = reinterpret_cast<DrawingRenderingContextPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerInvalidate();
}
} // DrawingRenderingContextAccessor
const GENERATED_ArkUIDrawingRenderingContextAccessor* GetDrawingRenderingContextAccessor()
{
    static const GENERATED_ArkUIDrawingRenderingContextAccessor DrawingRenderingContextAccessorImpl {
        DrawingRenderingContextAccessor::CtorImpl,
        DrawingRenderingContextAccessor::GetFinalizerImpl,
        DrawingRenderingContextAccessor::InvalidateImpl,
    };
    return &DrawingRenderingContextAccessorImpl;
}

}
