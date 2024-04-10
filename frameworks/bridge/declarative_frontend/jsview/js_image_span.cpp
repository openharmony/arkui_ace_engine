/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_image_span.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_span.h"

#if !defined(PREVIEW)
#include <dlfcn.h>
#endif

#include "base/log/ace_scoring_log.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/image/image_model.h"
#include "core/components_ng/pattern/text/image_span_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_image.h"

namespace OHOS::Ace::Framework {
void JSImageSpan::Create(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    if (info.Length() != 1) {
        return;
    }
    JSImage::Create(info);
    NG::ImageSpanView::Create();
}

void JSImageSpan::SetAlt(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    if (info.Length() < 1) {
        return;
    }
    JSImage::SetAlt(info);
}

void JSImageSpan::SetObjectFit(const JSCallbackInfo& info)
{
    if (info.Length() != 1) {
        return;
    }

    JSRef<JSVal> args = info[0];
    if (args->IsNumber()) {
        auto fit = static_cast<ImageFit>(args->ToNumber<int32_t>());
        if (fit < ImageFit::FILL || fit > ImageFit::SCALE_DOWN) {
            fit = ImageFit::COVER;
        }
        ImageModel::GetInstance()->SetImageFit(fit);
    } else {
        ImageModel::GetInstance()->SetImageFit(ImageFit::COVER);
    }
}

void JSImageSpan::SetVerticalAlign(int32_t verticalAlign)
{
    auto align = static_cast<VerticalAlign>(verticalAlign);
    if (align < VerticalAlign::TOP || align > VerticalAlign::NONE) {
        align = VerticalAlign::BOTTOM;
    }
    NG::ImageSpanView::SetVerticalAlign(align);
}

void JSImageSpan::SetTextBackgroundStyle(const JSCallbackInfo& info)
{
    auto textBackgroundStyle = JSContainerSpan::ParseTextBackgroundStyle(info);
    NG::ImageSpanView::SetPlaceHolderStyle(textBackgroundStyle);
}

void JSImageSpan::OnComplete(const JSCallbackInfo& args)
{
    JSRef<JSVal> arg = args[0];
    if (arg->IsFunction()) {
        auto jsLoadSuccFunc = AceType::MakeRefPtr<JsEventFunction<LoadImageSuccessEvent, 1>>(
            JSRef<JSFunc>::Cast(arg), LoadImageSuccEventToJSValue);

        auto onComplete = [execCtx = args.GetExecutionContext(), func = std::move(jsLoadSuccFunc)](
                              const LoadImageSuccessEvent& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("ImageSpan.onComplete");
            func->Execute(info);
        };
        ImageModel::GetInstance()->SetOnComplete(std::move(onComplete));
    }
}

void JSImageSpan::OnError(const JSCallbackInfo& args)
{
    JSRef<JSVal> arg = args[0];
    if (arg->IsFunction()) {
        auto jsLoadFailFunc = AceType::MakeRefPtr<JsEventFunction<LoadImageFailEvent, 1>>(
            JSRef<JSFunc>::Cast(arg), LoadImageFailEventToJSValue);
        auto onError = [execCtx = args.GetExecutionContext(), func = std::move(jsLoadFailFunc)](
                           const LoadImageFailEvent& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("ImageSpan.onError");
            func->Execute(info);
        };
        ImageModel::GetInstance()->SetOnError(onError);
    }
}

void JSImageSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSImageSpan>::Declare("ImageSpan");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSImageSpan>::StaticMethod("create", &JSImageSpan::Create, opt);
    JSClass<JSImageSpan>::StaticMethod("alt", &JSImageSpan::SetAlt, opt);
    JSClass<JSImageSpan>::StaticMethod("objectFit", &JSImageSpan::SetObjectFit);
    JSClass<JSImageSpan>::StaticMethod("verticalAlign", &JSImageSpan::SetVerticalAlign);
    JSClass<JSImageSpan>::StaticMethod("textBackgroundStyle", &JSImageSpan::SetTextBackgroundStyle);
    JSClass<JSImageSpan>::StaticMethod("onComplete", &JSImageSpan::OnComplete);
    JSClass<JSImageSpan>::StaticMethod("onError", &JSImageSpan::OnError);
    JSClass<JSImageSpan>::StaticMethod("border", &JSImage::JsBorder);
    JSClass<JSImageSpan>::StaticMethod("borderRadius", &JSImage::JsBorderRadius);
    JSClass<JSImageSpan>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
