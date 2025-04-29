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

#include "frameworks/core/components/image/image_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/color_filter_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {

using namespace Converter;
namespace ColorFilterAccessor {
void DestroyPeerImpl(Ark_ColorFilter peer)
{
    if (peer) {
        delete peer;
        peer = nullptr;
    }
}
Ark_ColorFilter CtorImpl(const Array_Number* value)
{
    auto peer = new ColorFilterPeer();
    CHECK_NULL_RETURN(value, peer);
    auto colorfiltermatrix = OptConvert<std::vector<float>>(*value);
    if (colorfiltermatrix && colorfiltermatrix->size() == COLOR_FILTER_MATRIX_SIZE) {
        peer->SetColorFilterMatrix(std::move(*colorfiltermatrix));
    }
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
} // ColorFilterAccessor
const GENERATED_ArkUIColorFilterAccessor* GetColorFilterAccessor()
{
    static const GENERATED_ArkUIColorFilterAccessor ColorFilterAccessorImpl {
        ColorFilterAccessor::DestroyPeerImpl,
        ColorFilterAccessor::CtorImpl,
        ColorFilterAccessor::GetFinalizerImpl,
    };
    return &ColorFilterAccessorImpl;
}
}
