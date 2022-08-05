/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_image.h"

#include "core/components_ng/pattern/image/image_view.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"

namespace OHOS::Ace::Framework {

void JSImage::SetAlt(const JSCallbackInfo& args) {}

void JSImage::SetObjectFit(int32_t value) {}

void JSImage::SetMatchTextDirection(bool value) {}

void JSImage::SetFitOriginalSize(bool value) {}

RefPtr<Decoration> JSImage::GetFrontDecoration()
{
    return nullptr;
}

const Border& JSImage::GetBorder()
{
    static Border border;
    return border;
}

void JSImage::SetBorder(const Border& border) {}

void JSImage::OnComplete(const JSCallbackInfo& args) {}

void JSImage::OnError(const JSCallbackInfo& args) {}

void JSImage::OnFinish(const JSCallbackInfo& info) {}

void JSImage::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    std::string src;
    auto noPixMap = ParseJsMedia(info[0], src);

    if (noPixMap) {
        NG::ImageView::Create(src);
    }
}

void JSImage::SetSourceSize(const JSCallbackInfo& info) {}

void JSImage::SetImageFill(const JSCallbackInfo& info) {}

void JSImage::SetImageRenderMode(int32_t imageRenderMode) {}

void JSImage::SetImageInterpolation(int32_t imageInterpolation) {}

void JSImage::SetImageRepeat(int32_t imageRepeat) {}

void JSImage::JsTransition(const JSCallbackInfo& info) {}

void JSImage::JsOpacity(const JSCallbackInfo& info) {}

void JSImage::SetAutoResize(bool autoResize) {}

void JSImage::SetSyncLoad(const JSCallbackInfo& info) {}

void JSImage::JsOnDragStart(const JSCallbackInfo& info) {}

void JSImage::JsOnDragEnter(const JSCallbackInfo& info) {}

void JSImage::JsOnDragMove(const JSCallbackInfo& info) {}

void JSImage::JsOnDragLeave(const JSCallbackInfo& info) {}

void JSImage::JsOnDrop(const JSCallbackInfo& info) {}

} // namespace OHOS::Ace::Framework
