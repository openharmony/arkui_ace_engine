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
#include "core/interfaces/native/implementation/linear_gradient_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LinearGradientAccessor {
void DestroyPeerImpl(Ark_LinearGradient peer)
{
}
Ark_LinearGradient CtorImpl(const Array_ColorStop* colorStops)
{
    CHECK_NULL_RETURN(colorStops, nullptr);
    auto colors = Converter::Convert<std::vector<std::pair<std::optional<Color>, Dimension>>>(*colorStops);
    return new LinearGradientPeer{colors};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
} // LinearGradientAccessor
const GENERATED_ArkUILinearGradientAccessor* GetLinearGradientAccessor()
{
    static const GENERATED_ArkUILinearGradientAccessor LinearGradientAccessorImpl {
        LinearGradientAccessor::DestroyPeerImpl,
        LinearGradientAccessor::CtorImpl,
        LinearGradientAccessor::GetFinalizerImpl,
    };
    return &LinearGradientAccessorImpl;
}

struct LinearGradientPeer {
    virtual ~LinearGradientPeer() = default;
};
}
