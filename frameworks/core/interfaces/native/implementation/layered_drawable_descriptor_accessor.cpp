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
#include "layered_drawable_descriptor_peer.h"
#include "arkoala_api_generated.h"

using namespace OHOS::Ace::NG::Converter;
namespace OHOS::Ace::NG::GeneratedModifier {
namespace LayeredDrawableDescriptorAccessor {
void DestroyPeerImpl(Ark_LayeredDrawableDescriptor peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_LayeredDrawableDescriptor CtorImpl(const Opt_DrawableDescriptor* foreground,
                                       const Opt_DrawableDescriptor* background,
                                       const Opt_DrawableDescriptor* mask)
{
    std::optional<Ark_DrawableDescriptor> foregroundDescriptor = foreground ? GetOpt(*foreground) : std::nullopt;
    std::optional<Ark_DrawableDescriptor> backgroundDescriptor = background ? GetOpt(*background) : std::nullopt;
    std::optional<Ark_DrawableDescriptor> maskDescriptor = mask ? GetOpt(*mask) : std::nullopt;
    auto foregroundPixelMap = foregroundDescriptor ? foregroundDescriptor.value()->GetPixelMap() : nullptr;
    auto backgroundPixelMap = backgroundDescriptor ? backgroundDescriptor.value()->GetPixelMap() : nullptr;
    auto maskPixelMap = maskDescriptor ? maskDescriptor.value()->GetPixelMap() : nullptr;
    return PeerUtils::CreatePeer<LayeredDrawableDescriptorPeer>(
        foregroundPixelMap, backgroundPixelMap, maskPixelMap);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_DrawableDescriptor GetForegroundImpl(Ark_LayeredDrawableDescriptor peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    return peer->GetForeground();
}
Ark_DrawableDescriptor GetBackgroundImpl(Ark_LayeredDrawableDescriptor peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    return peer->GetBackground();
}
Ark_DrawableDescriptor GetMaskImpl(Ark_LayeredDrawableDescriptor peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    return peer->GetMask();
}
Ark_String GetMaskClipPathImpl()
{
    return ArkValue<Ark_String>(LayeredDrawableDescriptorPeer::GetStaticMaskClipPath(), Converter::FC);
}
} // LayeredDrawableDescriptorAccessor
const GENERATED_ArkUILayeredDrawableDescriptorAccessor* GetLayeredDrawableDescriptorAccessor()
{
    static const GENERATED_ArkUILayeredDrawableDescriptorAccessor LayeredDrawableDescriptorAccessorImpl {
        LayeredDrawableDescriptorAccessor::DestroyPeerImpl,
        LayeredDrawableDescriptorAccessor::CtorImpl,
        LayeredDrawableDescriptorAccessor::GetFinalizerImpl,
        LayeredDrawableDescriptorAccessor::GetForegroundImpl,
        LayeredDrawableDescriptorAccessor::GetBackgroundImpl,
        LayeredDrawableDescriptorAccessor::GetMaskImpl,
        LayeredDrawableDescriptorAccessor::GetMaskClipPathImpl,
    };
    return &LayeredDrawableDescriptorAccessorImpl;
}

}
