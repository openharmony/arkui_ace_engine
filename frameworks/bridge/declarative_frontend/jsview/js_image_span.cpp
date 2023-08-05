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

#if !defined(PREVIEW)
#include <dlfcn.h>
#endif

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
        LOGE("The arg is wrong, it is supposed to have 1 argument");
        return;
    }
    JSImage::Create(info);
}

void JSImageSpan::SetObjectFit(const JSCallbackInfo& info)
{
    if (info.Length() != 1) {
        LOGE("The arg is wrong, it is supposed to have 1 argument");
        return;
    }

    if (info[0]->IsNumber()) {
        auto fit = static_cast<ImageFit>(info[0]->ToNumber<int32_t>());
        if (fit < ImageFit::FILL || fit > ImageFit::SCALE_DOWN) {
            LOGW("The value of objectFit is out of range %{public}d", fit);
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
        LOGW("The value of verticalAlign is out of range %{public}d", verticalAlign);
        align = VerticalAlign::BOTTOM;
    }
    NG::ImageSpanView::SetVerticalAlign(align);
}

void JSImageSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSImageSpan>::Declare("ImageSpan");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSImageSpan>::StaticMethod("create", &JSImageSpan::Create, opt);
    JSClass<JSImageSpan>::StaticMethod("objectFit", &JSImageSpan::SetObjectFit);
    JSClass<JSImageSpan>::StaticMethod("verticalAlign", &JSImageSpan::SetVerticalAlign);
    JSClass<JSImageSpan>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
