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
#include "arkoala_api_generated.h"
#include "canvas_pattern_peer.h"
#include "matrix2d_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasPatternAccessor {
const auto SCALE_LIMIT_MIN = 0.0;
void DestroyPeerImpl(CanvasPatternPeer* peer)
{
    if (peer) {
        delete peer;
    }
}
Ark_NativePointer CtorImpl()
{
    return new CanvasPatternPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetTransformImpl(CanvasPatternPeer* peer,
                      const Opt_Matrix2D* transform)
{
    CHECK_NULL_VOID(peer);
    auto opt = Converter::OptConvert<Ark_Matrix2D>(*transform);
    CHECK_NULL_VOID(opt);
    auto matrixPeer = reinterpret_cast<Matrix2DPeer*>(opt->ptr);
    CHECK_NULL_VOID(matrixPeer);
    auto param = matrixPeer->transform;
    if (LessNotEqual(param.scaleX, SCALE_LIMIT_MIN) || LessNotEqual(param.scaleY, SCALE_LIMIT_MIN)) {
        return;
    }
    peer->SetTransform(param);
}

} // CanvasPatternAccessor
const GENERATED_ArkUICanvasPatternAccessor* GetCanvasPatternAccessor()
{
    static const GENERATED_ArkUICanvasPatternAccessor CanvasPatternAccessorImpl {
        CanvasPatternAccessor::DestroyPeerImpl,
        CanvasPatternAccessor::CtorImpl,
        CanvasPatternAccessor::GetFinalizerImpl,
        CanvasPatternAccessor::SetTransformImpl,
    };
    return &CanvasPatternAccessorImpl;
}

}
