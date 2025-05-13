/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/canvas/js_canvas_path.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_util.h"
#include "bridge/declarative_frontend/jsview/canvas/js_rendering_context.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {
constexpr size_t GCTHRESHOLD = 50;

JSCanvasPath::JSCanvasPath()
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        isJudgeSpecialValue_ = true;
    }
}

void JSCanvasPath::JsPath2DSetTransform(const JSCallbackInfo& info)
{
    double scaleX = 0.0;
    double skewX = 0.0;
    double skewY = 0.0;
    double scaleY = 0.0;
    double translateX = 0.0;
    double translateY = 0.0;
    if (info.GetDoubleArg(0, scaleX, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, skewX, isJudgeSpecialValue_) && // Index1: the 2nd arg.
        info.GetDoubleArg(2, skewY, isJudgeSpecialValue_) && // Index2: the 3rd arg.
        info.GetDoubleArg(3, scaleY, isJudgeSpecialValue_) && // Index3: the 4th arg.
        info.GetDoubleArg(4, translateX, isJudgeSpecialValue_) && // Index4: the 5th arg.
        info.GetDoubleArg(5, translateY, isJudgeSpecialValue_)) { // Index5: the 6th arg.
        double density = GetDensity();
        path2d_->SetTransform(scaleX, skewX, skewY, scaleY, translateX * density, translateY * density);
        SetPathSize(info);
    }
}

// moveTo(x: number, y: number): void
void JSCanvasPath::JsPath2DMoveTo(const JSCallbackInfo& info)
{
    double x = 0.0;
    double y = 0.0;
    if (info.GetDoubleArg(0, x, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, y, isJudgeSpecialValue_)) { // Index1: the 2nd arg.
        double density = GetDensity();
        path2d_->MoveTo(x * density, y * density);
        SetPathSize(info);
    }
}

// lineTo(x: number, y: number): void
void JSCanvasPath::JsPath2DLineTo(const JSCallbackInfo& info)
{
    double x = 0.0;
    double y = 0.0;
    if (info.GetDoubleArg(0, x, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, y, isJudgeSpecialValue_)) { // Index1: the 2nd arg.
        double density = GetDensity();
        path2d_->LineTo(x * density, y * density);
        SetPathSize(info);
    }
}

// arc(x: number, y: number, radius: number, startAngle: number, endAngle: number, counterclockwise?: boolean): void
void JSCanvasPath::JsPath2DArc(const JSCallbackInfo& info)
{
    double x = 0.0;
    double y = 0.0;
    double radius = 0.0;
    double startAngle = 0.0;
    double endAngle = 0.0;
    if (info.GetDoubleArg(0, x, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, y, isJudgeSpecialValue_) && // Index1: the 2nd arg.
        info.GetDoubleArg(2, radius, isJudgeSpecialValue_) && // Index2: the 3rd arg.
        info.GetDoubleArg(3, startAngle, isJudgeSpecialValue_) && // Index3: the 4th arg.
        info.GetDoubleArg(4, endAngle, isJudgeSpecialValue_)) { // Index4: the 5th arg.
        bool anticlockwise = false;
        info.GetBooleanArg(5, anticlockwise);
        double density = GetDensity();
        path2d_->Arc(x * density, y * density, radius * density, startAngle, endAngle, anticlockwise);
        SetPathSize(info);
    }
}

// arcTo(x1: number, y1: number, x2: number, y2: number, radius: number): void
void JSCanvasPath::JsPath2DArcTo(const JSCallbackInfo& info)
{
    double x1 = 0.0;
    double y1 = 0.0;
    double x2 = 0.0;
    double y2 = 0.0;
    double radius = 0.0;
    if (info.GetDoubleArg(0, x1, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, y1, isJudgeSpecialValue_) && // Index1: the 2nd arg.
        info.GetDoubleArg(2, x2, isJudgeSpecialValue_) && // Index2: the 3rd arg.
        info.GetDoubleArg(3, y2, isJudgeSpecialValue_) && // Index3: the 4th arg.
        info.GetDoubleArg(4, radius, isJudgeSpecialValue_)) { // Index4: the 5th arg.
        double density = GetDensity();
        path2d_->ArcTo(x1 * density, y1 * density, x2 * density, y2 * density, radius * density);
        SetPathSize(info);
    }
}

// quadraticCurveTo(cpx: number, cpy: number, x: number ,y: number): void
void JSCanvasPath::JsPath2DQuadraticCurveTo(const JSCallbackInfo& info)
{
    double cpx = 0.0;
    double cpy = 0.0;
    double x = 0.0;
    double y = 0.0;
    if (info.GetDoubleArg(0, cpx, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, cpy, isJudgeSpecialValue_) && // Index1: the 2nd arg.
        info.GetDoubleArg(2, x, isJudgeSpecialValue_) && // Index2: the 3rd arg.
        info.GetDoubleArg(3, y, isJudgeSpecialValue_)) { // Index3: the 4th arg.
        double density = GetDensity();
        path2d_->QuadraticCurveTo(cpx * density, cpy * density, x * density, y * density);
        SetPathSize(info);
    }
}

// bezierCurveTo(cp1x: number, cp1y: number, cp2x: number, cp2y: number, x: number, y: number): void
void JSCanvasPath::JsPath2DBezierCurveTo(const JSCallbackInfo& info)
{
    double cp1x = 0.0;
    double cp1y = 0.0;
    double cp2x = 0.0;
    double cp2y = 0.0;
    double x = 0.0;
    double y = 0.0;
    if (info.GetDoubleArg(0, cp1x, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, cp1y, isJudgeSpecialValue_) && // Index1: the 2nd arg.
        info.GetDoubleArg(2, cp2x, isJudgeSpecialValue_) && // Index2: the 3rd arg.
        info.GetDoubleArg(3, cp2y, isJudgeSpecialValue_) && // Index3: the 4th arg.
        info.GetDoubleArg(4, x, isJudgeSpecialValue_) && // Index4: the 5th arg.
        info.GetDoubleArg(5, y, isJudgeSpecialValue_)) { // Index5: the 6th arg.
        double density = GetDensity();
        path2d_->BezierCurveTo(
            cp1x * density, cp1y * density, cp2x * density, cp2y * density, x * density, y * density);
        SetPathSize(info);
    }
}

// ellipse(x: number, y: number, radiusX: number, radiusY: number, rotation: number, startAngle: number,
//         endAngle: number, counterclockwise?: boolean): void
void JSCanvasPath::JsPath2DEllipse(const JSCallbackInfo& info)
{
    double x = 0.0;
    double y = 0.0;
    double radiusX = 0.0;
    double radiusY = 0.0;
    double rotation = 0.0;
    double startAngle = 0.0;
    double endAngle = 0.0;
    if (info.GetDoubleArg(0, x, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, y, isJudgeSpecialValue_) && // Index1: the 2nd arg.
        info.GetDoubleArg(2, radiusX, isJudgeSpecialValue_) && // Index2: the 3rd arg.
        info.GetDoubleArg(3, radiusY, isJudgeSpecialValue_) && // Index3: the 4th arg.
        info.GetDoubleArg(4, rotation, isJudgeSpecialValue_) && // Index4: the 5th arg.
        info.GetDoubleArg(5, startAngle, isJudgeSpecialValue_) && // Index5: the 6th arg.
        info.GetDoubleArg(6, endAngle, isJudgeSpecialValue_)) { // Index6: the 7th arg.
        bool anticlockwise = false;
        info.GetBooleanArg(7, anticlockwise);
        double density = GetDensity();
        path2d_->Ellipse(x * density, y * density, radiusX * density, radiusY * density, rotation,
            startAngle, endAngle, anticlockwise);
        SetPathSize(info);
    }
}

// rect(x: number, y: number, w: number, h: number): void
void JSCanvasPath::JsPath2DRect(const JSCallbackInfo& info)
{
    double x = 0.0;
    double y = 0.0;
    double width = 0.0;
    double height = 0.0;
    if (info.GetDoubleArg(0, x, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, y, isJudgeSpecialValue_) && // Index1: the 2nd arg.
        info.GetDoubleArg(2, width, isJudgeSpecialValue_) && // Index2: the 3rd arg.
        info.GetDoubleArg(3, height, isJudgeSpecialValue_)) { // Index3: the 4th arg.
        double density = GetDensity();
        path2d_->Rect(x * density, y * density, width * density, height * density);
        SetPathSize(info);
    }
}

// roundRect(x: number, y: number, width: number, height: number, radius: number|Array<number>): void
void JSCanvasPath::JsPath2DRoundRect(const JSCallbackInfo& info)
{
    Rect rect;
    std::vector<double> radii;
    double density = GetDensity();
    if (!ParseRoundRect(info, rect, radii, density, isJudgeSpecialValue_)) {
        return;
    }
    path2d_->RoundRect(rect * density, radii);
    SetPathSize(info);
}

// closePath(): void
void JSCanvasPath::JsPath2DClosePath(const JSCallbackInfo& info)
{
    path2d_->ClosePath();
    SetPathSize(info);
}

void JSCanvasPath::SetPathSize(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(path2d_);
    const std::vector<std::pair<PathCmd, PathArgs>> caches = path2d_->GetCaches();
    size_t pathSize = caches.size();
    if (pathSize - lastPathSize_ > GCTHRESHOLD) {
        EcmaVM* vm = info.GetVm();
        CHECK_NULL_VOID(vm);
        panda::CopyableGlobal<ObjectRef> pathCmdObj = panda::CopyableGlobal<ObjectRef>(pathCmdObj_);
        if (!pathCmdObj.IsEmpty()) {
            pathCmdObj->SetNativePointerField(
                vm, 0, nullptr, &JSCanvasPath::DestructorInterceptor, nullptr,
                (pathSize - lastPathSize_) * sizeof(std::pair<PathCmd, PathArgs>));
            lastPathSize_ = pathSize;
        }
    }
}
} // namespace OHOS::Ace::Framework
