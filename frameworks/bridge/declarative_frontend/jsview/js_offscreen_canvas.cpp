/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/jsview/js_offscreen_canvas.h"

namespace OHOS::Ace::Framework {
void JSOffscreenCanvas::JSBind(BindingTarget globalObj)
{
    JSClass<JSOffscreenCanvas>::Declare("OffscreenCanvas");
    JSClass<JSOffscreenCanvas>::CustomProperty("width", &JSOffscreenCanvas::JsGetWidth,
        &JSOffscreenCanvas::JsSetWidth);
    JSClass<JSOffscreenCanvas>::CustomProperty("height", &JSOffscreenCanvas::JsGetHeight,
        &JSOffscreenCanvas::JsSetHeight);
    JSClass<JSOffscreenCanvas>::CustomMethod("transferToImageBitmap",
        &JSOffscreenCanvas::JsTransferToImageBitmap);
    JSClass<JSOffscreenCanvas>::CustomMethod("getContext", &JSOffscreenCanvas::JsGetContext);

    JSClass<JSOffscreenCanvas>::CustomMethod("createRadialGradient",
        &JSOffscreenCanvas::JsCreateRadialGradient);
    JSClass<JSOffscreenCanvas>::CustomMethod("fillRect", &JSOffscreenCanvas::JsFillRect);
    JSClass<JSOffscreenCanvas>::CustomMethod("strokeRect", &JSOffscreenCanvas::JsStrokeRect);
    JSClass<JSOffscreenCanvas>::CustomMethod("clearRect", &JSOffscreenCanvas::JsClearRect);
    JSClass<JSOffscreenCanvas>::CustomMethod("createLinearGradient",
        &JSOffscreenCanvas::JsCreateLinearGradient);
    JSClass<JSOffscreenCanvas>::CustomMethod("fillText", &JSOffscreenCanvas::JsFillText);
    JSClass<JSOffscreenCanvas>::CustomMethod("strokeText", &JSOffscreenCanvas::JsStrokeText);
    JSClass<JSOffscreenCanvas>::CustomMethod("measureText", &JSOffscreenCanvas::JsMeasureText);
    JSClass<JSOffscreenCanvas>::CustomMethod("moveTo", &JSOffscreenCanvas::JsMoveTo);
    JSClass<JSOffscreenCanvas>::CustomMethod("lineTo", &JSOffscreenCanvas::JsLineTo);
    JSClass<JSOffscreenCanvas>::CustomMethod("bezierCurveTo", &JSOffscreenCanvas::JsBezierCurveTo);
    JSClass<JSOffscreenCanvas>::CustomMethod("quadraticCurveTo", &JSOffscreenCanvas::JsQuadraticCurveTo);
    JSClass<JSOffscreenCanvas>::CustomMethod("arcTo", &JSOffscreenCanvas::JsArcTo);
    JSClass<JSOffscreenCanvas>::CustomMethod("arc", &JSOffscreenCanvas::JsArc);
    JSClass<JSOffscreenCanvas>::CustomMethod("ellipse", &JSOffscreenCanvas::JsEllipse);
    JSClass<JSOffscreenCanvas>::CustomMethod("fill", &JSOffscreenCanvas::JsFill);
    JSClass<JSOffscreenCanvas>::CustomMethod("stroke", &JSOffscreenCanvas::JsStroke);
    JSClass<JSOffscreenCanvas>::CustomMethod("clip", &JSOffscreenCanvas::JsClip);
    JSClass<JSOffscreenCanvas>::CustomMethod("rect", &JSOffscreenCanvas::JsRect);
    JSClass<JSOffscreenCanvas>::CustomMethod("beginPath", &JSOffscreenCanvas::JsBeginPath);
    JSClass<JSOffscreenCanvas>::CustomMethod("closePath", &JSOffscreenCanvas::JsClosePath);
    JSClass<JSOffscreenCanvas>::CustomMethod("restore", &JSOffscreenCanvas::JsRestore);
    JSClass<JSOffscreenCanvas>::CustomMethod("save", &JSOffscreenCanvas::JsSave);
    JSClass<JSOffscreenCanvas>::CustomMethod("rotate", &JSOffscreenCanvas::JsRotate);
    JSClass<JSOffscreenCanvas>::CustomMethod("scale", &JSOffscreenCanvas::JsScale);
    JSClass<JSOffscreenCanvas>::CustomMethod("getTransform", &JSOffscreenCanvas::JsGetTransform);
    JSClass<JSOffscreenCanvas>::CustomMethod("setTransform", &JSOffscreenCanvas::JsSetTransform);
    JSClass<JSOffscreenCanvas>::CustomMethod("resetTransform", &JSOffscreenCanvas::JsResetTransform);
    JSClass<JSOffscreenCanvas>::CustomMethod("transform", &JSOffscreenCanvas::JsTransform);
    JSClass<JSOffscreenCanvas>::CustomMethod("translate", &JSOffscreenCanvas::JsTranslate);
    JSClass<JSOffscreenCanvas>::CustomMethod("setLineDash", &JSOffscreenCanvas::JsSetLineDash);
    JSClass<JSOffscreenCanvas>::CustomMethod("getLineDash", &JSOffscreenCanvas::JsGetLineDash);
    JSClass<JSOffscreenCanvas>::CustomMethod("drawImage", &JSOffscreenCanvas::JsDrawImage);
    JSClass<JSOffscreenCanvas>::CustomMethod("createPattern", &JSOffscreenCanvas::JsCreatePattern);
    JSClass<JSOffscreenCanvas>::CustomMethod("createImageData", &JSOffscreenCanvas::JsCreateImageData);
    JSClass<JSOffscreenCanvas>::CustomMethod("putImageData", &JSOffscreenCanvas::JsPutImageData);
    JSClass<JSOffscreenCanvas>::CustomMethod("getImageData", &JSOffscreenCanvas::JsGetImageData);
    JSClass<JSOffscreenCanvas>::CustomMethod("getJsonData", &JSOffscreenCanvas::JsGetJsonData);
    JSClass<JSOffscreenCanvas>::CustomMethod("getPixelMap", &JSOffscreenCanvas::JsGetPixelMap);
    JSClass<JSOffscreenCanvas>::CustomMethod("setPixelMap", &JSOffscreenCanvas::JsSetPixelMap);
    JSClass<JSOffscreenCanvas>::CustomMethod("createConicGradient", &JSOffscreenCanvas::JsCreateConicGradient);
    JSClass<JSOffscreenCanvas>::CustomMethod("transferFromImageBitmap", &JSOffscreenCanvas::JSTransferFromImageBitmap);
    JSClass<JSOffscreenCanvas>::CustomProperty("filter", &JSOffscreenCanvas::JsGetFilter,
        &JSOffscreenCanvas::JsSetFilter);
    JSClass<JSOffscreenCanvas>::CustomProperty("direction", &JSOffscreenCanvas::JsGetDirection,
        &JSOffscreenCanvas::JsSetDirection);
    JSClass<JSOffscreenCanvas>::CustomProperty("fillStyle", &JSOffscreenCanvas::JsGetFillStyle,
        &JSOffscreenCanvas::JsSetFillStyle);
    JSClass<JSOffscreenCanvas>::CustomProperty("strokeStyle", &JSOffscreenCanvas::JsGetStrokeStyle,
        &JSOffscreenCanvas::JsSetStrokeStyle);
    JSClass<JSOffscreenCanvas>::CustomProperty("lineCap", &JSOffscreenCanvas::JsGetLineCap,
        &JSOffscreenCanvas::JsSetLineCap);
    JSClass<JSOffscreenCanvas>::CustomProperty("lineJoin", &JSOffscreenCanvas::JsGetLineJoin,
        &JSOffscreenCanvas::JsSetLineJoin);
    JSClass<JSOffscreenCanvas>::CustomProperty("miterLimit", &JSOffscreenCanvas::JsGetMiterLimit,
        &JSOffscreenCanvas::JsSetMiterLimit);
    JSClass<JSOffscreenCanvas>::CustomProperty("lineWidth", &JSOffscreenCanvas::JsGetLineWidth,
        &JSOffscreenCanvas::JsSetLineWidth);
    JSClass<JSOffscreenCanvas>::CustomProperty("font", &JSOffscreenCanvas::JsGetFont,
        &JSOffscreenCanvas::JsSetFont);
    JSClass<JSOffscreenCanvas>::CustomProperty("textAlign", &JSOffscreenCanvas::JsGetTextAlign,
        &JSOffscreenCanvas::JsSetTextAlign);
    JSClass<JSOffscreenCanvas>::CustomProperty("textBaseline", &JSOffscreenCanvas::JsGetTextBaseline,
        &JSOffscreenCanvas::JsSetTextBaseline);
    JSClass<JSOffscreenCanvas>::CustomProperty("globalAlpha", &JSOffscreenCanvas::JsGetGlobalAlpha,
        &JSOffscreenCanvas::JsSetGlobalAlpha);
    JSClass<JSOffscreenCanvas>::CustomProperty("globalCompositeOperation",
        &JSOffscreenCanvas::JsGetGlobalCompositeOperation, &JSOffscreenCanvas::JsSetGlobalCompositeOperation);
    JSClass<JSOffscreenCanvas>::CustomProperty("lineDashOffset", &JSOffscreenCanvas::JsGetLineDashOffset,
        &JSOffscreenCanvas::JsSetLineDashOffset);
    JSClass<JSOffscreenCanvas>::CustomProperty("shadowBlur", &JSOffscreenCanvas::JsGetShadowBlur,
        &JSOffscreenCanvas::JsSetShadowBlur);
    JSClass<JSOffscreenCanvas>::CustomProperty("shadowColor", &JSOffscreenCanvas::JsGetShadowColor,
        &JSOffscreenCanvas::JsSetShadowColor);
    JSClass<JSOffscreenCanvas>::CustomProperty("shadowOffsetX", &JSOffscreenCanvas::JsGetShadowOffsetX,
        &JSOffscreenCanvas::JsSetShadowOffsetX);
    JSClass<JSOffscreenCanvas>::CustomProperty("shadowOffsetY", &JSOffscreenCanvas::JsGetShadowOffsetY,
        &JSOffscreenCanvas::JsSetShadowOffsetY);
    JSClass<JSOffscreenCanvas>::CustomProperty("imageSmoothingEnabled",
        &JSOffscreenCanvas::JsGetImageSmoothingEnabled, &JSOffscreenCanvas::JsSetImageSmoothingEnabled);
    JSClass<JSOffscreenCanvas>::CustomProperty("imageSmoothingQuality",
        &JSOffscreenCanvas::JsGetImageSmoothingQuality, &JSOffscreenCanvas::JsSetImageSmoothingQuality);
    JSClass<JSOffscreenCanvas>::Bind(globalObj, JSOffscreenCanvas::Constructor, JSOffscreenCanvas::Destructor);
}

void JSOffscreenCanvas::Constructor(const JSCallbackInfo& args)
{
    if (args.Length() < 2) {
        LOGE("The arg is wrong, it is supposed to have at least 2 argument");
        return;
    }
    if (Container::IsCurrentUseNewPipeline() && args[0]->IsNumber() && args[1]->IsNumber()) {
        auto offscreenCanvas = Referenced::MakeRefPtr<JSOffscreenCanvas>();
        CHECK_NULL_VOID(offscreenCanvas);
        offscreenCanvas->IncRefCount();
        double fWidth = 0.0;
        double fHeight = 0.0;
        if (JSViewAbstract::ParseJsDouble(args[0], fWidth)) {
            fWidth = SystemProperties::Vp2Px(fWidth);
            offscreenCanvas->SetWidth(round(fWidth));
        }
        if (JSViewAbstract::ParseJsDouble(args[1], fHeight)) {
            fHeight = SystemProperties::Vp2Px(fHeight);
            offscreenCanvas->SetHeight(round(fHeight));
        }
        args.SetReturnValue(Referenced::RawPtr(offscreenCanvas));
    }
}

void JSOffscreenCanvas::Destructor(JSOffscreenCanvas* context)
{
    if (context != nullptr) {
        context->DecRefCount();
    } else {
        LOGE("context is null");
        return;
    }
}

void JSOffscreenCanvas::JsGetWidth(const JSCallbackInfo& info)
{
    double fWidth = SystemProperties::Px2Vp(GetWidth());
    auto returnValue = JSVal(ToJSValue(fWidth));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSOffscreenCanvas::JsGetHeight(const JSCallbackInfo& info)
{
    double fHeight = SystemProperties::Px2Vp(GetHeight());
    auto returnValue = JSVal(ToJSValue(fHeight));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSOffscreenCanvas::JsSetWidth(const JSCallbackInfo& info)
{
    if (info.Length() != 1) {
        LOGE("The arg is wrong, it is supposed to have 1 argument");
        return;
    }
    if (info[0]->IsUndefined() || info[0]->IsNull()) {
        return;
    }
    double width = 0.0;
    if (JSViewAbstract::ParseJsDouble(info[0], width)) {
        width_ = SystemProperties::Vp2Px(width);
    } else {
        return;
    }

    if (contextType_ == ContextType::CONTEXT_2D) {
        CreateContext2d(width_, GetHeight());
    }
    return;
}

void JSOffscreenCanvas::JsSetHeight(const JSCallbackInfo& info)
{
    if (info.Length() != 1) {
        LOGE("The arg is wrong, it is supposed to have 1 argument");
        return;
    }

    if (info[0]->IsUndefined() || info[0]->IsNull()) {
        return;
    }
    double height = 0.0;
    if (JSViewAbstract::ParseJsDouble(info[0], height)) {
        height_ = SystemProperties::Vp2Px(height);
    } else {
        return;
    }

    if (contextType_ == ContextType::CONTEXT_2D) {
        CreateContext2d(GetWidth(), height_);
    }
    return;
}

void JSOffscreenCanvas::JsTransferToImageBitmap(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        CHECK_NULL_VOID(offscreenCanvasContext_);
        CHECK_NULL_VOID(offscreenCanvasPattern_);
        auto final_height = static_cast<uint32_t>(GetHeight());
        auto final_width = static_cast<uint32_t>(GetWidth());
        JSRef<JSObject> renderImage = JSRef<JSObject>::New();
        renderImage->SetProperty("__type", "ImageBitmap");
        renderImage->SetProperty("__id", offscreenCanvasContext_->GetId());
        renderImage->SetProperty("height", final_height);
        renderImage->SetProperty("width", final_width);
        info.SetReturnValue(renderImage);
    }
}

void JSOffscreenCanvas::JsGetContext(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info.Length() > 2) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument and at most 2 arguments");
        return;
    }
    if (info[0]->IsUndefined() || info[0]->IsNull()) {
        LOGE("Invalid arguments.");
        return;
    }
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    
    if (info[0]->IsString()) {
        std::string ruleStr;
        JSViewAbstract::ParseJsString(info[0], ruleStr);
        if (ruleStr == "2d") {
            contextType_ = ContextType::CONTEXT_2D;
            auto contextObj = CreateContext2d(GetWidth(), GetHeight());
            if (contextObj->IsEmpty()) {
                return;
            }
            JSRef<JSVal> isSucceed = contextObj->GetProperty("__isSucceed");
            if (isSucceed->IsBoolean() && !isSucceed->ToBoolean()) {
                return;
            }
            if (info[1]->IsObject()) {
                offscreenCanvasSettings_ = JSRef<JSObject>::Cast(info[1])->Unwrap<JSRenderingContextSettings>();
                CHECK_NULL_VOID(offscreenCanvasSettings_);
                bool anti = offscreenCanvasSettings_->GetAntialias();
                offscreenCanvasContext_->SetAnti(anti);
                offscreenCanvasContext_->SetAntiAlias();
            }
            info.SetReturnValue(contextObj);
        }
    }
}

JSRef<JSObject> JSOffscreenCanvas::CreateContext2d(double width, double height)
{
    JSRef<JSObject> contextObj = JSClass<JSOffscreenRenderingContext>::NewInstance();
    if (contextObj->IsEmpty()) {
        return contextObj;
    }
    contextObj->SetProperty("__type", "OffscreenCanvasRenderingContext2D");
    offscreenCanvasContext_ = Referenced::Claim(contextObj->Unwrap<JSOffscreenRenderingContext>());
    offscreenCanvasPattern_ = AceType::MakeRefPtr<NG::OffscreenCanvasPattern>(
        static_cast<int32_t>(width), static_cast<int32_t>(height));
    CHECK_NULL_RETURN(offscreenCanvasPattern_, contextObj);
    if (!offscreenCanvasPattern_->IsSucceed()) {
        contextObj->SetProperty("__isSucceed", false);
        return contextObj;
    }
    contextObj->SetProperty("__isSucceed", true);
    offscreenCanvasContext_->SetOffscreenPattern(offscreenCanvasPattern_);
    offscreenCanvasContext_->AddOffscreenCanvasPattern(offscreenCanvasPattern_);
    CHECK_NULL_RETURN(offscreenCanvasSettings_, contextObj);
    bool anti = offscreenCanvasSettings_->GetAntialias();
    offscreenCanvasContext_->SetAnti(anti);
    offscreenCanvasContext_->SetAntiAlias();
    return contextObj;
}
} // namespace OHOS::Ace::Framework
