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

#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_xcomponent_bridge.h"

#include "base/utils/string_utils.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_engine.h"
#include "frameworks/bridge/js_frontend/js_command.h"
#include "frameworks/core/common/ace_view.h"
#include "frameworks/core/common/container.h"

namespace OHOS::Ace::Framework {
QjsXComponentBridge::QjsXComponentBridge()
{
    nativeXComponentImpl_ = AceType::MakeRefPtr<NativeXComponentImpl>();
    nativeXComponent_ = new OH_NativeXComponent(AceType::RawPtr(nativeXComponentImpl_));
    renderContext_ = JS_NULL;
}

QjsXComponentBridge::~QjsXComponentBridge()
{
    if (nativeXComponent_) {
        delete nativeXComponent_;
        nativeXComponent_ = nullptr;
    }
}

void QjsXComponentBridge::HandleContext(JSContext* ctx, NodeId id, const std::string& args)
{
    if (hasPluginLoaded_) {
        return;
    }

    auto engine = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    if (engine == nullptr) {
        LOGE("QjsXComponentBridge::HandleJsContext, engine is null.");
        return;
    }

    auto page = engine->GetRunningPage();
    if (!page) {
        LOGE("QjsXComponentBridge page is null.");
        return;
    }
    auto domXcomponent = AceType::DynamicCast<DOMXComponent>(page->GetDomDocument()->GetDOMNodeById(id));
    if (!domXcomponent) {
        LOGE("QjsXComponentBridge domXcomponent is null.");
        return;
    }
    auto xcomponent = AceType::DynamicCast<XComponentComponent>(domXcomponent->GetSpecializedComponent());
    if (!xcomponent) {
        LOGE("QjsXComponentBridge xcomponent is null.");
        return;
    }

    auto container = Container::Current();
    if (!container) {
        LOGE("QjsXComponentBridge Current container null");
        return;
    }
    auto nativeView = static_cast<AceView*>(container->GetView());
    if (!nativeView) {
        LOGE("QjsXComponentBridge nativeView null");
        return;
    }

    void* nativeWindow = nullptr;
#ifdef OHOS_STANDARD_SYSTEM
    nativeWindow = const_cast<void*>(xcomponent->GetNativeWindow());
#else
    auto textureId = static_cast<int64_t>(xcomponent->GetTextureId());
    nativeWindow = const_cast<void*>(nativeView->GetNativeWindowById(textureId));
#endif
    if (!nativeWindow) {
        LOGE("QjsXComponentBridge::HandleJsContext nativeWindow invalid");
        return;
    }

    nativeXComponentImpl_->SetSurface(nativeWindow);
    nativeXComponentImpl_->SetXComponentId(xcomponent->GetId());

#ifdef XCOMPONENT_SUPPORTED
    auto nativeEngine = static_cast<QuickJSNativeEngine*>(engine->GetQuickJSNativeEngine());
    if (nativeEngine == nullptr) {
        LOGE("nativeEngine is null");
        return;
    }

    renderContext_ = nativeEngine->LoadModuleByName(xcomponent->GetLibraryName(), true,
                                                    args, OH_NATIVE_XCOMPONENT_OBJ,
                                                    reinterpret_cast<void*>(nativeXComponent_));

    auto delegate = engine->GetDelegate();
    if (delegate == nullptr) {
        LOGE("delegate is null.");
        return;
    }
    auto task = [weak = WeakClaim(this), xcomponent]() {
        auto pool = xcomponent->GetTaskPool();
        if (!pool) {
            return;
        }
        auto bridge = weak.Upgrade();
        if (bridge) {
            pool->NativeXComponentInit(bridge->nativeXComponent_,
                                       AceType::WeakClaim(AceType::RawPtr(bridge->nativeXComponentImpl_)));
        }
    };
    delegate->PostSyncTaskToPage(task);
#endif
    hasPluginLoaded_ = true;
    return;
}

JSValue QjsXComponentBridge::JsGetXComponentSurfaceId(JSContext* ctx, NodeId nodeId)
{
#ifdef XCOMPONENT_SUPPORTED
    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    if (instance == nullptr) {
        LOGE("JsGetXComponentSurfaceId instance is null");
        return JS_NULL;
    }
    auto page = instance->GetRunningPage();
    if (!page) {
        LOGE("JsGetXComponentSurfaceId page is null");
        return JS_NULL;
    }

    std::string surfaceId = "";
    auto task = [nodeId, page, &surfaceId]() {
        auto domDoc = page->GetDomDocument();
        if (!domDoc) {
            return;
        }
        auto domXComponent = AceType::DynamicCast<DOMXComponent>(domDoc->GetDOMNodeById(nodeId));
        if (!domXComponent) {
            return;
        }
        surfaceId = domXComponent->GetSurfaceId();
    };

    auto delegate = instance->GetDelegate();
    if (!delegate) {
        LOGE("JsGetXComponentSurfaceId delegate is null");
        return JS_NULL;
    }
    delegate->PostSyncTaskToPage(task);
    JSValue result = JS_NewString(ctx, surfaceId.c_str());
    return result;
#else
    return JS_NULL;
#endif
}

void QjsXComponentBridge::JsSetXComponentSurfaceSize(JSContext* ctx, const std::string& args, NodeId nodeId)
{
#ifdef XCOMPONENT_SUPPORTED
    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    if (instance == nullptr) {
        LOGE("JsSetXComponentSurfaceSize instance is null");
        return;
    }
    auto page = instance->GetRunningPage();
    if (!page) {
        LOGE("JsSetXComponentSurfaceSize page is null");
        return;
    }

    auto task = [nodeId, page, args]() {
        auto domDoc = page->GetDomDocument();
        if (!domDoc) {
            return;
        }
        auto domXComponent = AceType::DynamicCast<DOMXComponent>(domDoc->GetDOMNodeById(nodeId));
        if (!domXComponent) {
            return;
        }

        std::unique_ptr<JsonValue> argsValue = JsonUtil::ParseJsonString(args);
        if (!argsValue || !argsValue->IsArray() || argsValue->GetArraySize() < 1) {
            LOGE("JsSetXComponentSurfaceSize failed. parse args error");
            return;
        }
        std::unique_ptr<JsonValue> surfaceSizePara = argsValue->GetArrayItem(0);
        uint32_t surfaceWidth = surfaceSizePara->GetUInt("surfaceWidth", 0);
        uint32_t surfaceHeight = surfaceSizePara->GetUInt("surfaceHeight", 0);
        domXComponent->SetSurfaceSize(surfaceWidth, surfaceHeight);
    };

    auto delegate = instance->GetDelegate();
    if (!delegate) {
        LOGE("JsSetXComponentSurfaceSize delegate is null");
        return;
    }
    delegate->PostSyncTaskToPage(task);
#endif
}
} // namespace OHOS::Ace::Framework