/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ARKTS_NATIVE_OFFSCREEN_CANVAS_RENDERING_CONTEXT_BRIDGE_H
#define ARKTS_NATIVE_OFFSCREEN_CANVAS_RENDERING_CONTEXT_BRIDGE_H

#include "frameworks/core/components_ng/pattern/canvas/bridge/arkts_native_canvas_rendering_context_bridge.h"

namespace OHOS::Ace::NG {

class OffscreenCanvasRenderingContext2DBridge {
public:
    static void RegisterOffscreenCanvasRenderingContext2DAttributes(
        Local<panda::ObjectRef> object, EcmaVM* vm);

    // Drawing methods (same as CanvasRenderingContext2D — inherited from CanvasPath + CanvasRenderer)
    static ArkUINativeModuleValue BeginPath(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ClosePath(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue MoveTo(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue LineTo(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Arc(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Fill(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Stroke(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue FillStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue StrokeStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue LineWidth(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GlobalAlpha(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue FillRect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue FillText(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Save(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Restore(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Scale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Rotate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Translate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Reset(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AntiAlias(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue StrokeRect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ClearRect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Clip(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Rect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Ellipse(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue BezierCurveTo(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue QuadraticCurveTo(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ArcTo(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue RoundRect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Transform(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTransform(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTransform(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetLineDash(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SaveLayer(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue RestoreLayer(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue DrawImage(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue PutImageData(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue TransferFromImageBitmap(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue StartImageAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue StopImageAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo);
};
} // namespace OHOS::Ace::NG

#endif
