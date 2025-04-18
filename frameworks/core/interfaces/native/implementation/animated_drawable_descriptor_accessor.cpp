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
#include "animated_drawable_descriptor_peer.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
struct AnimationOptions {
    std::optional<int32_t> duration;
    std::optional<int32_t> iterations;
};

template<>
AnimationOptions Convert(const Ark_AnimationOptions& options)
{
    return {
        .duration = OptConvert<int32_t>(options.duration),
        .iterations = OptConvert<int32_t>(options.iterations),
    };
}
} // namespace OHOS::Ace::NG::Converter

using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG::GeneratedModifier {
namespace AnimatedDrawableDescriptorAccessor {
void DestroyPeerImpl(Ark_AnimatedDrawableDescriptor peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_AnimatedDrawableDescriptor CtorImpl(const Array_PixelMap* pixelMaps,
                                        const Opt_AnimationOptions* options)
{
    std::vector<RefPtr<PixelMap>> arrayPixelMaps;
    if (pixelMaps) {
        arrayPixelMaps = Convert<std::vector<RefPtr<PixelMap>>>(*pixelMaps);
    }
    auto animationOptions = options ? OptConvert<AnimationOptions>(*options) : std::nullopt;
    return PeerUtils::CreatePeer<AnimatedDrawableDescriptorPeer>(arrayPixelMaps,
        animationOptions ? animationOptions->duration : std::nullopt,
        animationOptions ? animationOptions->iterations : std::nullopt);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
} // AnimatedDrawableDescriptorAccessor
const GENERATED_ArkUIAnimatedDrawableDescriptorAccessor* GetAnimatedDrawableDescriptorAccessor()
{
    static const GENERATED_ArkUIAnimatedDrawableDescriptorAccessor AnimatedDrawableDescriptorAccessorImpl {
        AnimatedDrawableDescriptorAccessor::DestroyPeerImpl,
        AnimatedDrawableDescriptorAccessor::CtorImpl,
        AnimatedDrawableDescriptorAccessor::GetFinalizerImpl,
    };
    return &AnimatedDrawableDescriptorAccessorImpl;
}

}
