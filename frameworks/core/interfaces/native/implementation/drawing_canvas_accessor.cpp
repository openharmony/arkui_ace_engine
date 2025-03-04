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
#include "arkoala_api_generated.h"
#include "drawing_canvas_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DrawingCanvasAccessor {
void DestroyPeerImpl(Ark_DrawingCanvas peer)
{
    delete peer;
}
Ark_DrawingCanvas CtorImpl(Ark_PixelMap pixelmap)
{
    return new DrawingCanvasPeer(pixelmap->pixelMap);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void DrawRectImpl(Ark_DrawingCanvas peer,
                  const Ark_Number* left,
                  const Ark_Number* top,
                  const Ark_Number* right,
                  const Ark_Number* bottom)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(left && top && right && bottom);
    float x = Converter::Convert<float>(*left);
    float y = Converter::Convert<float>(*top);
    float w = Converter::Convert<float>(*right) - x;
    float h = Converter::Convert<float>(*bottom) - y;
    Rect rect(x, y, w, h);
    peer->FillRect(rect);
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
