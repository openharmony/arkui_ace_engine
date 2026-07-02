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

#ifndef ARKTS_NATIVE_CANVAS_RENDERING_CONTEXT_BRIDGE_H
#define ARKTS_NATIVE_CANVAS_RENDERING_CONTEXT_BRIDGE_H

#include "ecmascript/napi/include/jsnapi.h"

namespace OHOS::Ace::NG {
using ArkUINativeModuleValue = panda::Local<panda::JSValueRef>;
using ArkUIRuntimeCallInfo = panda::JsiRuntimeCallInfo;
using panda::JSValueRef;
using panda::ObjectRef;
using panda::Local;
using panda::ecmascript::EcmaVM;
class CanvasRenderingContext2DBridge {
public:
    static void RegisterCanvasRenderingContext2DAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);

    // Path methods
    static ArkUINativeModuleValue BeginPath(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ClosePath(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue MoveTo(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue LineTo(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue BezierCurveTo(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue QuadraticCurveTo(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Arc(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ArcTo(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Ellipse(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Rect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue RoundRect(ArkUIRuntimeCallInfo* runtimeCallInfo);

    // Fill / Stroke
    static ArkUINativeModuleValue Fill(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Stroke(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Clip(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue FillRect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue StrokeRect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ClearRect(ArkUIRuntimeCallInfo* runtimeCallInfo);

    // Properties (setters)
    static ArkUINativeModuleValue FillStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue StrokeStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue LineWidth(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue LineCap(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue LineJoin(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue MiterLimit(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Font(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue TextAlign(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue TextBaseline(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GlobalAlpha(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GlobalCompositeOperation(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ShadowBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ShadowColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ShadowOffsetX(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ShadowOffsetY(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Filter(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Direction(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ImageSmoothingEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ImageSmoothingQuality(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue LetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue LineDashOffset(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AntiAlias(ArkUIRuntimeCallInfo* runtimeCallInfo);

    // Transform
    static ArkUINativeModuleValue Save(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Restore(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Scale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Rotate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Translate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Transform(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTransform(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTransform(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Reset(ArkUIRuntimeCallInfo* runtimeCallInfo);

    // Text
    static ArkUINativeModuleValue FillText(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue StrokeText(ArkUIRuntimeCallInfo* runtimeCallInfo);

    // Line dash
    static ArkUINativeModuleValue SetLineDash(ArkUIRuntimeCallInfo* runtimeCallInfo);

    // Layers
    static ArkUINativeModuleValue SaveLayer(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue RestoreLayer(ArkUIRuntimeCallInfo* runtimeCallInfo);

    // Image
    static ArkUINativeModuleValue DrawImage(ArkUIRuntimeCallInfo* runtimeCallInfo);

    // Image data
    static ArkUINativeModuleValue PutImageData(ArkUIRuntimeCallInfo* runtimeCallInfo);

    // Transfer
    static ArkUINativeModuleValue TransferFromImageBitmap(ArkUIRuntimeCallInfo* runtimeCallInfo);

    // Analyzer
    static ArkUINativeModuleValue StartImageAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue StopImageAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo);
};
} // namespace OHOS::Ace::NG

#endif
