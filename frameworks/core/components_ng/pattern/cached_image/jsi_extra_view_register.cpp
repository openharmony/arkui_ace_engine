/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023-2024. All rights reserved.
 */

#include "jsi_extra_view_register.h"
#include "js_cached_image.h"
#include "core/components_ng/pattern/cached_image/arkts_native_media_cached_image_bridge.h"
#include "core/components_ng/pattern/cached_image/cached_image_model_ng.h"

namespace OHOS::Ace::Framework {

static const std::unordered_map<std::string, std::function<void(BindingTarget)>> extraBindFuncs = {
    { "CachedImage", JSCachedImage::JSBind },
    { "MediaCachedImage", JSCachedImage::JSBindMediaCachedImage },
};

panda::Local<panda::JSValueRef> GetArkUIAdvancedModule(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto object = panda::ObjectRef::New(vm);

    auto mediaCachedImage = panda::ObjectRef::New(vm);
    mediaCachedImage->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMediaCachedImageSrc"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm),
        OHOS::Ace::NG::MediaCachedImageBridge::SetMediaCachedImageSrc));

    mediaCachedImage->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlt"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm),
        OHOS::Ace::NG::MediaCachedImageBridge::SetAlt));

    mediaCachedImage->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlt"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm),
        OHOS::Ace::NG::MediaCachedImageBridge::ResetAlt));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "mediaCachedImage"), mediaCachedImage);

    return object;
}

void RegisterExtraViews(BindingTarget globalObj)
{
    for (const auto& iter : extraBindFuncs) {
        iter.second(globalObj);
    }

    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (!runtime) {
        return;
    }
    auto vm = runtime->GetEcmaVm();
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getArkUIAdvancedModule"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GetArkUIAdvancedModule));
}

void RegisterExtraViewByName(BindingTarget globalObj, const std::string& moduleName)
{
    auto func = extraBindFuncs.find(moduleName);
    if (func == extraBindFuncs.end()) {
        LOGW("JS module not exist in extra, name: %{public}s", moduleName.c_str());
        return;
    }
    (*func).second(globalObj);
}

} // namespace OHOS::Ace::Framework