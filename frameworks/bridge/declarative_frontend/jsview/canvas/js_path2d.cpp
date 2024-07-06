/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/canvas/js_path2d.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_renderer.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {
JSPath2D::JSPath2D() {}

void JSPath2D::Constructor(const JSCallbackInfo& args)
{
    auto jsPath2d = Referenced::MakeRefPtr<JSPath2D>();
    jsPath2d->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jsPath2d));
    int32_t unit = 0;
    if (args.GetInt32Arg(std::abs(args.Length() - 1), unit) && (static_cast<CanvasUnit>(unit) == CanvasUnit::PX)) {
        jsPath2d->SetUnit(CanvasUnit::PX);
    }
    jsPath2d->SetCanvasPath2d(JSCanvasRenderer::JsMakePath2D(args));
    args.SetSize(sizeof(JSPath2D));
    EcmaVM* vm = args.GetVm();
    CHECK_NULL_VOID(vm);
    Local<ObjectRef> pathCmdObj = ObjectRef::New(vm);
    pathCmdObj->SetNativePointerFieldCount(vm, 1);
    jsPath2d->pathCmdObj_ = panda::CopyableGlobal<panda::JSValueRef>(vm, pathCmdObj);
}

void JSPath2D::Destructor(JSPath2D* controller)
{
    if (controller != nullptr) {
        controller->DecRefCount();
    }
}

void JSPath2D::JSBind(BindingTarget globalObj)
{
    JSClass<JSPath2D>::Declare("Path2D");
    JSClass<JSPath2D>::CustomMethod("addPath", &JSPath2D::JsPath2DAddPath);
    JSClass<JSPath2D>::CustomMethod("setTransform", &JSCanvasPath::JsPath2DSetTransform);
    JSClass<JSPath2D>::CustomMethod("moveTo", &JSCanvasPath::JsPath2DMoveTo);
    JSClass<JSPath2D>::CustomMethod("lineTo", &JSCanvasPath::JsPath2DLineTo);
    JSClass<JSPath2D>::CustomMethod("arc", &JSCanvasPath::JsPath2DArc);
    JSClass<JSPath2D>::CustomMethod("arcTo", &JSCanvasPath::JsPath2DArcTo);
    JSClass<JSPath2D>::CustomMethod("quadraticCurveTo", &JSCanvasPath::JsPath2DQuadraticCurveTo);
    JSClass<JSPath2D>::CustomMethod("bezierCurveTo", &JSCanvasPath::JsPath2DBezierCurveTo);
    JSClass<JSPath2D>::CustomMethod("ellipse", &JSCanvasPath::JsPath2DEllipse);
    JSClass<JSPath2D>::CustomMethod("rect", &JSCanvasPath::JsPath2DRect);
    JSClass<JSPath2D>::CustomMethod("closePath", &JSCanvasPath::JsPath2DClosePath);
    JSClass<JSPath2D>::Bind(globalObj, JSPath2D::Constructor, JSPath2D::Destructor);
}

// addPath(path: path2D, transform?:Matrix2D): void
void JSPath2D::JsPath2DAddPath(const JSCallbackInfo& args)
{
    // one parameter
    auto* jsPath2d = args.UnwrapArg<JSPath2D>(0);
    CHECK_NULL_VOID(jsPath2d);
    auto canvasPath2D = jsPath2d->GetCanvasPath2d();
    path2d_->AddPath(canvasPath2D);
    SetPathSize(args);

    // two parameters
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TEN)) {
        auto* jsMatrix2d = args.UnwrapArg<JSMatrix2d>(1);
        if (jsMatrix2d) {
            path2d_->SetTransform(jsMatrix2d->JsGetScaleX(), jsMatrix2d->JsGetRotateX(), jsMatrix2d->JsGetRotateY(),
                jsMatrix2d->JsGetScaleY(), jsMatrix2d->JsGetTranslateX(), jsMatrix2d->JsGetTranslateY());
            SetPathSize(args);
        }
        return;
    }
    if (args[1]->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(args[1]);
        TransformParam param = JSMatrix2d::GetTransformInfo(jsObj);
        double density = GetDensity();
        param.translateX *= density;
        param.translateY *= density;
        path2d_->SetTransform(param.scaleX, param.skewX, param.skewY, param.scaleY, param.translateX, param.translateY);
        SetPathSize(args);
    }
}

} // namespace OHOS::Ace::Framework
