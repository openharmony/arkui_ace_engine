/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023-2024. All rights reserved.
 */
 
#include "core/components_ng/pattern/cached_image/js_cached_image.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "core/common/container.h"
#include "ipc_skeleton.h"
#include "tokenid_kit.h"
#include "core/components_ng/pattern/cached_image/cached_image_model_ng.h"

namespace OHOS::Ace {

namespace {
ImageSourceInfo CreateSourceInfo(const std::string &src, RefPtr<PixelMap> &pixmap, const std::string &bundleName,
    const std::string &moduleName)
{
#if defined(PIXEL_MAP_SUPPORTED)
    if (pixmap) {
        return ImageSourceInfo(pixmap);
    }
#endif
    return { src, bundleName, moduleName };
}
} // namespace

std::unique_ptr<CachedImageModel> CachedImageModel::instance_ = nullptr;
std::mutex CachedImageModel::mutex_;

CachedImageModel* CachedImageModel::GetInstance()
{
    if (instance_ == nullptr) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance_ == nullptr) {
            instance_.reset(new NG::CachedImageModelNG());
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {


static bool CheckSystemApp()
{
    static bool isSys = Security::AccessToken::TokenIdKit::IsSystemAppByFullTokenID(IPCSkeleton::GetSelfTokenID());
    return isSys;
}

void JSCachedImage::Create(const JSCallbackInfo& info)
{
    if (!CheckSystemApp()) {
        return;
    }

    if (info.Length() < 1) {
        return;
    }

    std::vector<std::string> sources;
    int column = 0;
    if (IsASTCResource(info[0], sources, column)) {
        CachedImageModel::GetInstance()->Create(sources, column);
    } else {
        std::string src;
        RefPtr<PixelMap> pixmap = nullptr;
        bool isSrcValid = ParseJsMedia(info[0], src);
#if defined(PIXEL_MAP_SUPPORTED)
        if (!isSrcValid) {
            if (IsDrawable(info[0])) {
                pixmap = GetDrawablePixmap(info[0]);
            } else {
                pixmap = CreatePixelMapFromNapiValue(info[0]);
            }
        }
#endif
        CachedImageModel::GetInstance()->Create(src, pixmap);
    }
}

void JSCachedImage::SetSourceSize(const JSCallbackInfo& info)
{
    if (!CheckSystemApp()) {
        return;
    }
    CachedImageModel::GetInstance()->SetImageSourceSize(JSViewAbstract::ParseSize(info));
}

void JSCachedImage::SetAlt(const JSCallbackInfo& info)
{
    if (!CheckSystemApp()) {
        return;
    }
    if (info.Length() < 1) {
        return;
    }
 
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    bool isCard = context->IsFormRender();
 
    std::string src;
    bool srcValid = false;
    if (info[0]->IsString()) {
        src = info[0]->ToString();
    } else {
        srcValid = ParseJsMedia(info[0], src);
    }
 
    if (ImageSourceInfo::ResolveURIType(src) == SrcType::NETWORK) {
        return;
    }
    int32_t resId = 0;
    if (info[0]->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> tmp = jsObj->GetProperty("id");
        if (!tmp->IsNull() && tmp->IsNumber()) {
            resId = tmp->ToNumber<int32_t>();
        }
    }
 
    std::string bundleName;
    std::string moduleName;
    GetJsMediaBundleInfo(info[0], bundleName, moduleName);
    RefPtr<PixelMap> pixmap = nullptr;
 
    // input is Drawable
    if (!srcValid && !isCard) {
#if defined(PIXEL_MAP_SUPPORTED)
        pixmap = CreatePixelMapFromNapiValue(info[0]);
#endif
    }
    if (pixmap == nullptr) {
        return;
    }
    auto srcInfo = CreateSourceInfo(src, pixmap, bundleName, moduleName);
    srcInfo.SetIsUriPureNumber(resId == -1);
    CachedImageModel::GetInstance()->SetAlt(srcInfo);
}

void JSCachedImage::JSBind(BindingTarget globalObj)
{
    JSClass<JSCachedImage>::Declare("CachedImage");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSCachedImage>::StaticMethod("create", &JSCachedImage::Create, opt);
    JSClass<JSCachedImage>::StaticMethod("sourceSize", &JSCachedImage::SetSourceSize, opt);
    JSClass<JSCachedImage>::StaticMethod("alt", &JSCachedImage::SetAlt, opt);
    // override method
    JSClass<JSCachedImage>::InheritAndBind<JSImage>(globalObj);
}

void JSCachedImage::JSBindMediaCachedImage(BindingTarget globalObj)
{
    JSClass<JSCachedImage>::Declare("MediaCachedImage");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSCachedImage>::StaticMethod("create", &JSCachedImage::Create, opt);
    JSClass<JSCachedImage>::StaticMethod("sourceSize", &JSCachedImage::SetSourceSize, opt);
    JSClass<JSCachedImage>::StaticMethod("alt", &JSCachedImage::SetAlt, opt);
    // override method
    JSClass<JSCachedImage>::InheritAndBind<JSImage>(globalObj);
}

bool JSCachedImage::IsASTCResource(const JSRef<JSVal>& jsValue, std::vector<std::string>& uriList,
    int& column)
{
    if (!jsValue->IsObject()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    if (jsObj->IsUndefined()) {
        return false;
    }
    JSRef<JSVal> dataList = jsObj->GetProperty("sources");
    JSRef<JSVal> columnVal = jsObj->GetProperty("column");
    if (columnVal->IsEmpty() || !columnVal->IsNumber()) {
        LOGE("columnVal is null or is not Number");
        return false;
    }
    if (!dataList->IsArray()) {
        return false;
    }

    column = columnVal->ToNumber<int32_t>();
    JSRef<JSArray> params = JSRef<JSArray>::Cast(dataList);
    for (size_t i = 0; i < params->Length(); i++) {
        JSRef <JSVal> value = params->GetValueAt(i);
        if (value->IsString()) {
            uriList.emplace_back(value->ToString());
        }
    }
    return true;
}

} // namespace OHOS::Ace::Framework