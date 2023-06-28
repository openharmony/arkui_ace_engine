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

#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"

#include "scope_manager/native_scope_manager.h"

#if !defined(PREVIEW)
#include <dlfcn.h>
#endif

#include "base/image/pixel_map.h"
#include "base/log/ace_trace.h"
#include "base/want/want_wrap.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"

namespace OHOS::Ace::Framework {
namespace {
// Min disable event api version.
constexpr int32_t MIN_DISABLE_EVENT_VERSION = 10;
} // namespace

#if !defined(PREVIEW)
class ScopeRAII {
public:
    explicit ScopeRAII(NativeScopeManager* manager) : manager_(manager)
    {
        scope_ = manager_->Open();
    }
    ~ScopeRAII()
    {
        manager_->Close(scope_);
    }

private:
    NativeScopeManager* manager_;
    NativeScope* scope_;
};

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

    ScopeRAII scope(nativeEngine->GetScopeManager());
    NativeValue* nativeValue = nativeEngine->ValueToNativeValue(valueWrapper);

    PixelMapNapiEntry pixelMapNapiEntry = JsEngine::GetPixelMapNapiEntry();
    if (!pixelMapNapiEntry) {
        LOGE("pixelMapNapiEntry is null");
        return nullptr;
    }

    void* pixmapPtrAddr =
        pixelMapNapiEntry(reinterpret_cast<napi_env>(nativeEngine), reinterpret_cast<napi_value>(nativeValue));
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

    ScopeRAII scope(nativeEngine->GetScopeManager());
    NativeValue* nativeValue = nativeEngine->ValueToNativeValue(valueWrapper);
    CHECK_NULL_RETURN(nativeValue, nullptr);
    NativeObject* object = static_cast<NativeObject*>(nativeValue->GetInterface(NativeObject::INTERFACE_ID));
    CHECK_NULL_RETURN(object, nullptr);
    return object->GetNativePointer();
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

    ScopeRAII scope(nativeEngine->GetScopeManager());
    NativeValue* nativeValue = nativeEngine->ValueToNativeValue(valueWrapper);

    return WantWrap::CreateWantWrap(reinterpret_cast<void*>(nativeEngine), reinterpret_cast<void*>(nativeValue));
}

#endif

// When the api version >= 10, it is disable event version.
bool IsDisableEventVersion()
{
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return false;
    }
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext) {
        LOGW("pipelineContext is null!");
        return false;
    }
    if (pipelineContext->GetMinPlatformVersion() >= MIN_DISABLE_EVENT_VERSION) {
        LOGD("The version supports disable event callback.");
        return true;
    }
    LOGW("The version doesn't support disable event callback.");
    return false;
}
} // namespace OHOS::Ace::Framework
