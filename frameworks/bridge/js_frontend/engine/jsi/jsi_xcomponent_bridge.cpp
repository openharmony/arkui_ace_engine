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

#include "frameworks/bridge/js_frontend/engine/jsi/jsi_xcomponent_bridge.h"

#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_value.h"
#include "frameworks/core/common/ace_view.h"

namespace OHOS::Ace::Framework {
JsiXComponentBridge::JsiXComponentBridge()
{
    nativeXcomponentImpl_ = AceType::MakeRefPtr<NativeXComponentImpl>();
    nativeXComponent_ = new OH_NativeXComponent(AceType::RawPtr(nativeXcomponentImpl_));
}

JsiXComponentBridge::~JsiXComponentBridge()
{
    if (nativeXComponent_) {
        delete nativeXComponent_;
        nativeXComponent_ = nullptr;
    }
    // render context must be release on js thread.
    auto currentContainer = Container::Current();
    if (currentContainer) {
        auto taskExecutor = currentContainer->GetTaskExecutor();
        if (taskExecutor) {
            taskExecutor->PostTask([renderContext = std::move(renderContext_)]() mutable { renderContext.reset(); },
                TaskExecutor::TaskType::JS, "ArkUIXComponentRenderContextRelease");
        }
    }
}

void JsiXComponentBridge::HandleContext(const shared_ptr<JsRuntime>& runtime, NodeId id, const std::string& args)
{
    if (hasPluginLoaded_) {
        return;
    }

    if (!runtime) {
        LOGE("Runtime is null");
        return;
    }

    auto engineInstance = static_cast<JsiEngineInstance*>(runtime->GetEmbedderData());
    auto page = engineInstance->GetRunningPage();
    if (!page) {
        LOGE("JsiXComponentBridge page is null.");
        return;
    }
    auto domXcomponent = AceType::DynamicCast<DOMXComponent>(page->GetDomDocument()->GetDOMNodeById(id));
    if (!domXcomponent) {
        LOGE("JsiXComponentBridge domXcomponent is null.");
        return;
    }
    auto xcomponent = AceType::DynamicCast<XComponentComponent>(domXcomponent->GetSpecializedComponent());
    if (!xcomponent) {
        LOGE("JsiXComponentBridge xcomponent is null.");
        return;
    }

    auto container = Container::Current();
    if (!container) {
        LOGE("JsiXComponentBridge Current container null");
        return;
    }
    auto nativeView = container->GetAceView();
    if (!nativeView) {
        LOGE("JsiXComponentBridge nativeView null");
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
        LOGE("JsiXComponentBridge::HandleJsContext nativeWindow invalid");
        return;
    }
    nativeXcomponentImpl_->SetSurface(nativeWindow);
    nativeXcomponentImpl_->SetXComponentId(xcomponent->GetId());

    auto nativeEngine = static_cast<ArkNativeEngine*>(engineInstance->GetNativeEngine());
    if (!nativeEngine) {
        LOGE("NativeEngine is null");
        return;
    }

    auto arkObjectRef = nativeEngine->LoadModuleByName(xcomponent->GetLibraryName(), true,
                                                       args, OH_NATIVE_XCOMPONENT_OBJ,
                                                       reinterpret_cast<void*>(nativeXComponent_));

    shared_ptr<ArkJSRuntime> pandaRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkObjectRef.IsEmpty() || pandaRuntime->HasPendingException()) {
        LOGE("LoadModuleByName failed.");
        return;
    }
    renderContext_ = runtime->NewObject();
    auto renderContext = std::static_pointer_cast<ArkJSValue>(renderContext_);
    LocalScope scope(pandaRuntime->GetEcmaVm());
    Local<ObjectRef> obj = arkObjectRef->ToObject(pandaRuntime->GetEcmaVm());
    if (obj.IsEmpty() || pandaRuntime->HasPendingException()) {
        LOGE("Get local object failed.");
        renderContext_.reset();
        return;
    }
    renderContext->SetValue(pandaRuntime, obj);

    auto task = [weak = WeakClaim(this), xcomponent]() {
        auto pool = xcomponent->GetTaskPool();
        if (!pool) {
            return;
        }
        auto bridge = weak.Upgrade();
        if (bridge) {
            pool->NativeXComponentInit(
                bridge->nativeXComponent_,
                AceType::WeakClaim(AceType::RawPtr(bridge->nativeXcomponentImpl_)));
        }
    };

    auto delegate = engineInstance->GetFrontendDelegate();
    if (!delegate) {
        LOGE("Delegate is null");
        return;
    }
    delegate->PostSyncTaskToPage(task, "ArkUIXComponentNativeInit");

    hasPluginLoaded_ = true;
    return;
}

shared_ptr<JsValue> JsiXComponentBridge::JsGetXComponentSurfaceId(const shared_ptr<JsRuntime>& runtime, NodeId nodeId)
{
    if (!runtime) {
        LOGE("JsGetXComponentSurfaceId failed. runtime is null.");
        return nullptr;
    }
    auto engine = static_cast<JsiEngineInstance*>(runtime->GetEmbedderData());
    if (!engine) {
        LOGE("JsGetXComponentSurfaceId failed. engine is null.");
        return runtime->NewUndefined();
    }
    auto page = engine->GetRunningPage();
    if (!page) {
        LOGE("JsGetXComponentSurfaceId failed. page is null.");
        return runtime->NewUndefined();
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
    auto delegate = engine->GetFrontendDelegate();
    if (!delegate) {
        LOGE("JsGetXComponentSurfaceId failed. delegate is null.");
        return runtime->NewUndefined();
    }
    delegate->PostSyncTaskToPage(task, "ArkUIXComponentGetSurfaceId");
    return runtime->NewString(surfaceId);
}

void JsiXComponentBridge::JsSetXComponentSurfaceSize(
    const shared_ptr<JsRuntime>& runtime, const std::string& arguments, NodeId nodeId)
{
    if (!runtime) {
        LOGE("JsSetXComponentSurfaceSize failed. runtime is null.");
        return;
    }
    auto engine = static_cast<JsiEngineInstance*>(runtime->GetEmbedderData());
    if (!engine) {
        LOGE("JsSetXComponentSurfaceSize failed. engine is null.");
        return;
    }
    auto page = engine->GetRunningPage();
    if (!page) {
        LOGE("JsSetXComponentSurfaceSize failed. page is null.");
        return;
    }
    auto task = [nodeId, page, arguments]() {
        auto domDoc = page->GetDomDocument();
        if (!domDoc) {
            return;
        }
        auto domXComponent = AceType::DynamicCast<DOMXComponent>(domDoc->GetDOMNodeById(nodeId));
        if (!domXComponent) {
            return;
        }

        std::unique_ptr<JsonValue> argsValue = JsonUtil::ParseJsonString(arguments);
        if (!argsValue || !argsValue->IsArray() || argsValue->GetArraySize() < 1) {
            LOGE("JsSetXComponentSurfaceSize failed. parse args error");
            return;
        }
        std::unique_ptr<JsonValue> surfaceSizePara = argsValue->GetArrayItem(0);
        uint32_t surfaceWidth = surfaceSizePara->GetUInt("surfaceWidth", 0);
        uint32_t surfaceHeight = surfaceSizePara->GetUInt("surfaceHeight", 0);
        domXComponent->SetSurfaceSize(surfaceWidth, surfaceHeight);
    };
    auto delegate = engine->GetFrontendDelegate();
    if (!delegate) {
        LOGE("JsSetXComponentSurfaceSize failed. delegate is null.");
        return;
    }
    delegate->PostSyncTaskToPage(task, "ArkUIXComponentSetSurfaceSize");
}
} // namespace OHOS::Ace::Framework