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
#include "arkoala_api.h"
#include "arkoala_api_generated.h"
#include "canvas_gradient_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasGradientAccessor {
static void DestroyPeer(CanvasGradientPeer* peer)
{
    if (peer) {
        delete peer;
    }
}
CanvasGradientPeer* CtorImpl()
{
    return new CanvasGradientPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeer);
}
void AddColorStopImpl(CanvasGradientPeer* peer,
                      const Ark_Number* offset,
                      const Ark_String* color)
{
}
} // CanvasGradientAccessor
const GENERATED_ArkUICanvasGradientAccessor* GetCanvasGradientAccessor()
{
    static const GENERATED_ArkUICanvasGradientAccessor CanvasGradientAccessorImpl {
        CanvasGradientAccessor::CtorImpl,
        CanvasGradientAccessor::GetFinalizerImpl,
        CanvasGradientAccessor::AddColorStopImpl,
    };
    return &CanvasGradientAccessorImpl;
}

}
