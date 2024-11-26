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
#include "arkoala_api.h"
#include "arkoala_api_generated.h"
#include "canvas_pattern_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasPatternAccessor {
static void DestroyPeer(CanvasPatternPeer* peer)
{
    if (peer) {
        delete peer;
    }
}
CanvasPatternPeer* CtorImpl()
{
    return new CanvasPatternPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeer);
}
void SetTransformImpl(CanvasPatternPeer* peer,
                      const Opt_Matrix2D* transform)
{
}
} // CanvasPatternAccessor
const GENERATED_ArkUICanvasPatternAccessor* GetCanvasPatternAccessor()
{
    static const GENERATED_ArkUICanvasPatternAccessor CanvasPatternAccessorImpl {
        CanvasPatternAccessor::CtorImpl,
        CanvasPatternAccessor::GetFinalizerImpl,
        CanvasPatternAccessor::SetTransformImpl,
    };
    return &CanvasPatternAccessorImpl;
}

}
