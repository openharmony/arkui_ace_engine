/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_utils.h"

#include "scope_manager/native_scope_manager.h"

#if !defined(PREVIEW)
#include <dlfcn.h>
#endif

#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
#include "pixel_map_napi.h"
#endif
#include "base/image/pixel_map.h"
#include "base/log/ace_trace.h"
#include "base/want/want_wrap.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"

namespace OHOS::Ace::Framework {
namespace {} // namespace

#if !defined(PREVIEW)
RefPtr<PixelMap> CreatePixelMapFromNapiValue(JSRef<JSVal> obj)
{
    if (!obj->IsObject()) {
        LOGE("info[0] is not an object when try CreatePixelMapFromNapiValue");
        return nullptr;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    if (!engine) {
        LOGE("CreatePixelMapFromNapiValue engine is null");
        return nullptr;
    }
    auto* nativeEngine = engine->GetNativeEngine();
    if (nativeEngine == nullptr) {
        LOGE("nativeEngine is nullptr.");
        return nullptr;
    }
#ifdef USE_ARK_ENGINE
    panda::Local<JsiValue> value = obj.Get().GetLocalHandle();
#endif
    JSValueWrapper valueWrapper = value;

    ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value napiValue = nativeEngine->ValueToNapiValue(valueWrapper);

    PixelMapNapiEntry pixelMapNapiEntry = JsEngine::GetPixelMapNapiEntry();
    if (!pixelMapNapiEntry) {
        LOGE("pixelMapNapiEntry is null");
        return nullptr;
    }

    void* pixmapPtrAddr = pixelMapNapiEntry(reinterpret_cast<napi_env>(nativeEngine), napiValue);
    if (pixmapPtrAddr == nullptr) {
        LOGE("Failed to get pixmap pointer");
        return nullptr;
    }
    return PixelMap::CreatePixelMap(pixmapPtrAddr);
}

namespace {
void* UnwrapNapiValue(const JSRef<JSVal>& obj)
{
#ifdef ENABLE_ROSEN_BACKEND
    if (!obj->IsObject()) {
        LOGE("info[0] is not an object when try CreateFromNapiValue");
        return nullptr;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, nullptr);
    auto nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, nullptr);
#ifdef USE_ARK_ENGINE
    panda::Local<JsiValue> value = obj.Get().GetLocalHandle();
#endif
    JSValueWrapper valueWrapper = value;

    ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value napiValue = nativeEngine->ValueToNapiValue(valueWrapper);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, napiValue, &valueType);
    if (valueType != napi_object) {
        LOGE("napiValue is not napi_object");
        return nullptr;
    }
    void* objectNapi = nullptr;
    napi_unwrap(env, napiValue, &objectNapi);
    return objectNapi;
}
} // namespace

RefPtr<PixelMap> GetDrawablePixmap(JSRef<JSVal> obj)
{
    return PixelMap::GetFromDrawable(UnwrapNapiValue(obj));
}

const std::shared_ptr<Rosen::RSNode> CreateRSNodeFromNapiValue(JSRef<JSVal> obj)
{
    auto nodePtr = static_cast<std::shared_ptr<Rosen::RSNode>*>(UnwrapNapiValue(obj));
    if (nodePtr == nullptr) {
        return nullptr;
    }
    return *nodePtr;
#else
    return nullptr;
}
#endif
} // namespace

RefPtr<OHOS::Ace::WantWrap> CreateWantWrapFromNapiValue(JSRef<JSVal> obj)
{
    if (!obj->IsObject()) {
        LOGE("invalid object when try CreateWantWrapFromNapiValue");
        return nullptr;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, nullptr);

    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, nullptr);

#ifdef USE_ARK_ENGINE
    panda::Local<JsiValue> value = obj.Get().GetLocalHandle();
#endif
    JSValueWrapper valueWrapper = value;
    ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value nativeValue = nativeEngine->ValueToNapiValue(valueWrapper);
    return WantWrap::CreateWantWrap(reinterpret_cast<napi_env>(nativeEngine), nativeValue);
}

#endif

// When the api version >= 10, it is disable event version.
bool IsDisableEventVersion()
{
    return Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN);
}

#ifdef PIXEL_MAP_SUPPORTED
JSRef<JSVal> ConvertPixmap(const RefPtr<PixelMap>& pixelMap)
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, {});
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    auto* env = reinterpret_cast<napi_env>(nativeEngine);
    napi_value napiValue = OHOS::Media::PixelMapNapi::CreatePixelMap(env, pixelMap->GetPixelMapSharedPtr());
    return JsConverter::ConvertNapiValueToJsVal(napiValue);
}
#endif
} // namespace OHOS::Ace::Framework
