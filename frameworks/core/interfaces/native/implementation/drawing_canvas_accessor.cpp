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

struct DrawingCanvasPeer {
    explicit DrawingCanvasPeer(const Ark_PixelMap* pixelmap) {}
    virtual ~DrawingCanvasPeer() = default;
};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DrawingCanvasAccessor {
void DestroyPeerImpl(DrawingCanvasPeer* peer)
{
    delete peer;
}
Ark_NativePointer CtorImpl(const Ark_PixelMap* pixelmap)
{
    return new DrawingCanvasPeer(pixelmap);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void DrawRectImpl(DrawingCanvasPeer* peer,
                  const Ark_Number* left,
                  const Ark_Number* top,
                  const Ark_Number* right,
                  const Ark_Number* bottom)
{
}
} // DrawingCanvasAccessor
const GENERATED_ArkUIDrawingCanvasAccessor* GetDrawingCanvasAccessor()
{
    static const GENERATED_ArkUIDrawingCanvasAccessor DrawingCanvasAccessorImpl {
        DrawingCanvasAccessor::DestroyPeerImpl,
        DrawingCanvasAccessor::CtorImpl,
        DrawingCanvasAccessor::GetFinalizerImpl,
        DrawingCanvasAccessor::DrawRectImpl,
    };
    return &DrawingCanvasAccessorImpl;
}

}
