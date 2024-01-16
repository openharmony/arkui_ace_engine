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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RENDER_IMAGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RENDER_IMAGE_H

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components_ng/image_provider/image_loading_context.h"

namespace OHOS::Ace::Framework {
class JSCanvasRenderer;

void BindNativeFunction(napi_env env, napi_value object, const char* name, napi_callback func);
void* GetNapiCallbackInfoAndThis(napi_env env, napi_callback_info info);

class JSRenderImage : public Referenced {
public:
    JSRenderImage();
    ~JSRenderImage() override = default;

    static void JSBind(BindingTarget globalObj, void* nativeEngine = nullptr);

    static napi_value InitImageBitmap(napi_env env);
    static napi_value Constructor(napi_env env, napi_callback_info info);
    static napi_value JsClose(napi_env env, napi_callback_info info);
    static napi_value JsSetWidth(napi_env env, napi_callback_info info);
    static napi_value JsSetHeight(napi_env env, napi_callback_info info);
    static napi_value JsGetWidth(napi_env env, napi_callback_info info);
    static napi_value JsGetHeight(napi_env env, napi_callback_info info);

    double GetWidth();
    double GetHeight();
    std::string GetSrc();
    void SetCloseCallback(std::function<void()>&& callback);
    RefPtr<PixelMap> GetPixelMap()
    {
        return pixelMap_;
    }

    void SetInstanceId(int32_t instanceId)
    {
        instanceId_ = instanceId;
    }

    int32_t GetInstanceId()
    {
        return instanceId_;
    }

    ACE_DISALLOW_COPY_AND_MOVE(JSRenderImage);
private:
    napi_value OnClose();
    napi_value OnGetWidth(napi_env env);
    napi_value OnGetHeight(napi_env env);
    napi_value OnSetWidth();
    napi_value OnSetHeight();

    void LoadImage(const std::string& src);
    void LoadImage(const ImageSourceInfo& src);
    void OnImageDataReady();
    void OnImageLoadFail(const std::string& errorMsg);
    void OnImageLoadSuccess();

    RefPtr<NG::CanvasImage> image_;
    RefPtr<NG::ImageLoadingContext> loadingCtx_;
    RefPtr<PixelMap> pixelMap_;
    ImageSourceInfo sourfaceInfo_;

    std::string src_;
    std::list<std::function<void()>> closeCallbacks_;
    double width_ = 0;
    double height_ = 0;
    int32_t instanceId_ = 0;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RENDER_IMAGE_H