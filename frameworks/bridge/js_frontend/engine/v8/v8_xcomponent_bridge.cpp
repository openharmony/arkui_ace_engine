/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include <memory>

#include "frameworks/bridge/js_frontend/engine/v8/v8_xcomponent_bridge.h"

#include "base/utils/string_utils.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/js_frontend/engine/v8/v8_engine.h"
#include "frameworks/bridge/js_frontend/js_command.h"
#include "frameworks/core/common/ace_view.h"
#include "frameworks/core/common/container.h"

namespace OHOS::Ace::Framework {
namespace {
void PushAsyncTaskToPageById(const v8::Local<v8::Context>& context, NodeId id,
                             const std::function<void(const RefPtr<XComponentTaskPool>&)>& task)
{
    v8::Isolate* isolate = context->GetIsolate();
    if (!isolate) {
        LOGE("PushAsyncTaskToPageById handleScope. isolate = null");
        return;
    }
    v8::HandleScope handleScope(isolate);

    auto command = Referenced::MakeRefPtr<JsCommandXComponentOperation>(id, task);
    auto page = static_cast<RefPtr<JsAcePage>*>(isolate->GetData(V8EngineInstance::RUNNING_PAGE));
    if (!page) {
        LOGE("page is null.");
        return;
    }
    (*page)->PushCommand(command);
}
} // namespace

void V8XComponentBridge::HandleContext(const v8::Local<v8::Context>& ctx, NodeId id,
                                       const std::string& args, JsEngineInstance* engine)
{
    isolate_ = ctx->GetIsolate();
    if (!isolate_) {
        LOGE("V8XComponentBridge isolate_ is null.");
        return;
    }
    ctx_.Reset(isolate_, ctx);

    if (hasPluginLoaded_) {
        return;
    }

    auto page = static_cast<RefPtr<JsAcePage>*>(ctx->GetIsolate()->GetData(V8EngineInstance::RUNNING_PAGE));
    if (!page) {
        LOGE("V8XComponentBridge page is null.");
        return;
    }
    auto domXcomponent = AceType::DynamicCast<DOMXComponent>((*page)->GetDomDocument()->GetDOMNodeById(id));
    if (!domXcomponent) {
        LOGE("V8XComponentBridge domXcomponent is null.");
        return;
    }
    auto xcomponent = AceType::DynamicCast<XComponentComponent>(domXcomponent->GetSpecializedComponent());
    if (!xcomponent) {
        LOGE("V8XComponentBridge xcomponent is null.");
        return;
    }
    auto textureId = static_cast<int64_t>(xcomponent->GetTextureId());

    auto container = Container::Current();
    if (!container) {
        LOGE("V8XComponentBridge Current container null");
        return;
    }
    auto nativeView = static_cast<AceView*>(container->GetView());
    if (!nativeView) {
        LOGE("V8XComponentBridge nativeView null");
        return;
    }
    nativeWindow_ = const_cast<void*>(nativeView->GetNativeWindowById(textureId));
    if (!nativeWindow_) {
        LOGE("V8XComponentBridge::HandleJsContext nativeWindow invalid");
        return;
    }

    std::shared_ptr<V8NativeEngine> nativeEngine = static_cast<V8EngineInstance*>(engine)->GetV8NativeEngine();
    if (!nativeEngine) {
        LOGE("nativeEngine is null");
        return;
    }

    auto renderContext = nativeEngine->GetModuleFromName(xcomponent->GetLibraryName(), true, xcomponent->GetId(),
                                                         args, NATIVE_RENDER_TAG,
                                                         reinterpret_cast<void**>(&nativeRenderContext_));
    renderContext_.Reset(isolate_, renderContext);
    if (!nativeRenderContext_) {
        LOGE("V8XComponentBridge invalid native render context");
        return;
    }

    nativeRenderContext_->OnNativeWindowInit(nativeWindow_);

    nativeRenderContext_->OnGLContextInit();

    auto delegate = static_cast<RefPtr<FrontendDelegate>*>(isolate_->GetData(V8EngineInstance::FRONTEND_DELEGATE));
    auto task = [weak = WeakClaim(this), xcomponent]() {
        auto pool = xcomponent->GetTaskPool();
        if (!pool) {
            return;
        }
        auto bridge = weak.Upgrade();
        if (bridge) {
            pool->PluginContextInit(bridge->nativeRenderContext_);
        }
    };
    if (*delegate == nullptr) {
        LOGE("delegate is null.");
        return;
    }
    (*delegate)->PostSyncTaskToPage(task);

    auto onPluginUpdateCallback = [weak = WeakClaim(this), id]() {
        auto bridge = weak.Upgrade();
        if (bridge) {
            auto ctx = bridge->GetContext();
            auto task = [](const RefPtr<XComponentTaskPool>& pool) {
                pool->PluginUpdate();
            };
            PushAsyncTaskToPageById(ctx, id, task);
        }
    };
    nativeRenderContext_->OnRenderDoneCallbackCreated(onPluginUpdateCallback);

    hasPluginLoaded_ = true;
    return;
}
} // namespace OHOS::Ace::Framework