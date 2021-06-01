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

#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_declarative_engine.h"

#include <cstdlib>

#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "frameworks/bridge/js_frontend/engine/common/js_constants.h"

namespace OHOS::Ace::Framework {

QJSDeclarativeEngine::~QJSDeclarativeEngine()
{
    JS_RunGC(engineInstance_->GetQJSRuntime());
}

bool QJSDeclarativeEngine::Initialize(const RefPtr<FrontendDelegate>& delegate)
{
    LOGD("QJSDeclarativeEngine initialize");
    engineInstance_ = AceType::MakeRefPtr<QJSDeclarativeEngineInstance>(delegate);
    bool res = engineInstance_->InitJSEnv();
    if (!res) {
        LOGE("QJSDeclarativeEngine initialize failed: %{public}d", instanceId_);
        return false;
    }

    return true;
}

void QJSDeclarativeEngine::LoadJs(const std::string& url, const RefPtr<JsAcePage>& page, bool isMainPage)
{
    LOGD("QJSDeclarativeEngine LoadJs");
    ACE_SCOPED_TRACE("QJSDeclarativeEngine::LoadJS");
    ACE_DCHECK(engineInstance_);

    engineInstance_->SetRunningPage(page);
    JSContext* ctx = engineInstance_->GetQJSContext();
    JS_SetContextOpaque(ctx, reinterpret_cast<void*>(AceType::RawPtr(engineInstance_)));

    std::string jsContent;
    if (!engineInstance_->GetDelegate()->GetAssetContent(url, jsContent)) {
        LOGE("js file load failed!");
        return;
    }

    if (jsContent.empty()) {
        LOGE("js file load failed! url=[%{public}s]", url.c_str());
        return;
    }

    JSValue compiled = engineInstance_->CompileSource(url, jsContent.c_str(), jsContent.size());
    if (JS_IsException(compiled)) {
        LOGE("js compilation failed url=[%{public}s]", url.c_str());
        return;
    }

    // Todo: check the fail.
    engineInstance_->ExecuteDocumentJS(compiled);

    js_std_loop(engineInstance_->GetQJSContext());
}

void QJSDeclarativeEngine::UpdateRunningPage(const RefPtr<JsAcePage>& page)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetRunningPage(page);
}

void QJSDeclarativeEngine::UpdateStagingPage(const RefPtr<JsAcePage>& page)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetStagingPage(page);
}

void QJSDeclarativeEngine::ResetStagingPage()
{
    ACE_DCHECK(engineInstance_);
    auto runningPage = engineInstance_->GetRunningPage();
    engineInstance_->ResetStagingPage(runningPage);
}

void QJSDeclarativeEngine::DestroyPageInstance(int32_t pageId)
{
    LOGE("Not implemented!");
}

void QJSDeclarativeEngine::DestroyApplication(const std::string& packageName)
{
    LOGE("Not implemented!");
}

void QJSDeclarativeEngine::TimerCallback(const std::string& callbackId, const std::string& delay, bool isInterval)
{
    // string with function source
    LOGD("CallbackId %s", callbackId.c_str());
    JSContext* ctx = engineInstance_->GetQJSContext();
    if (!ctx) {
        LOGE("TimerCallback no context");
        return;
    }
}

void QJSDeclarativeEngine::MediaQueryCallback(const std::string& callbackId, const std::string& args)
{
    LOGE("Not implemented!");
}

void QJSDeclarativeEngine::RequestAnimationCallback(const std::string& callbackId, uint64_t timeStamp)
{
    LOGD("Enter RequestAnimationCallback");
}

void QJSDeclarativeEngine::JsCallback(const std::string& callbackId, const std::string& args)
{
    LOGD("Enter JsCallback");
}

void QJSDeclarativeEngine::FireAsyncEvent(const std::string& eventId, const std::string& param)
{
    LOGD("FireAsyncEvent params: %{private}s", param.c_str());

    if (engineInstance_) {
        LOGD("FireAsyncEvent engineInstance_ OK");
        engineInstance_->FireAsyncEvent(eventId, param);
    }
}

void QJSDeclarativeEngine::FireSyncEvent(const std::string& eventId, const std::string& param)
{
    LOGE("Not implemented! eventId: %s param: %s ", eventId.c_str(), param.c_str());
}

void QJSDeclarativeEngine::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetJsMessageDispatcher(dispatcher);
}

void QJSDeclarativeEngine::RunGarbageCollection()
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->RunGarbageCollection();
}

RefPtr<GroupJsBridge> QJSDeclarativeEngine::GetGroupJsBridge()
{
    return nullptr;
}

} // namespace OHOS::Ace::Framework
