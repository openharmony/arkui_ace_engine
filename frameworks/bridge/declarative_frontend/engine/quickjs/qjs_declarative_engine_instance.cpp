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

#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_declarative_engine_instance.h"

#include <cstdlib>
#include <fcntl.h>
#include <fstream>
#include <streambuf>
#include <sys/stat.h>
#include <unistd.h>

#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings_implementation.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_helpers.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"
#include "frameworks/bridge/js_frontend/engine/common/js_constants.h"
#include "frameworks/bridge/js_frontend/engine/common/runtime_constants.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_group_js_bridge.h"
#include "frameworks/core/common/ace_application_info.h"
#include "frameworks/core/image/image_cache.h"

extern const char _binary_jsproxyClass_js_start[];
extern const char _binary_jsproxyClass_js_end[];
namespace OHOS::Ace::Framework {

QJSDeclarativeEngineInstance* QJSDeclarativeEngineInstance::UnWrapEngineInstance(JSContext* ctx)
{
    auto* instance = static_cast<QJSDeclarativeEngineInstance*>(JS_GetContextOpaque(ctx));
    if (instance == nullptr) {
        LOGE("Can not unwrap ctx and obtain QJSDeclarativeEngineInstance object.");
    }
    return instance;
}

void QJSDeclarativeEngineInstance::SetRunningPage(const RefPtr<JsAcePage>& page)
{
    std::lock_guard<std::mutex> lock(mutex_);
    LOGD("new running page is %d.", (int)page->GetPageId());
    runningPage_ = page;
}

void QJSDeclarativeEngineInstance::SetStagingPage(const RefPtr<JsAcePage>& page)
{
    std::lock_guard<std::mutex> lock(mutex_);
    LOGD("new staging page is %d.", (int)page->GetPageId());
    stagingPage_ = page;
}

void QJSDeclarativeEngineInstance::ResetStagingPage(const RefPtr<JsAcePage>& page)
{
    std::lock_guard<std::mutex> lock(mutex_);
    LOGD("new staging page is %d.", (int)page->GetPageId());
    stagingPage_ = page;
}

RefPtr<JsAcePage> QJSDeclarativeEngineInstance::GetRunningPage(JSContext* ctx)
{
    auto* instance = QJSDeclarativeEngineInstance::UnWrapEngineInstance(ctx);
    if (instance != nullptr) {
        return instance->GetRunningPage();
    } else {
        LOGE("QJS context has no ref to engine instance. Failed!");
        return nullptr;
    }
}

void QJSDeclarativeEngineInstance::PushJSCommand(const RefPtr<JsCommand>& jsCommand, bool forcePush) const
{
    auto page = GetRunningPage();
    if (page == nullptr) {
        LOGE("Internal error: running page is null.");
        return;
    }

    ACE_SCOPED_TRACE("PushJSCommand");
    page->PushCommand(jsCommand);

    if (!page->CheckPageCreated() && (forcePush || (page->GetCommandSize() > (FRAGMENT_SIZE + 4)))) {
        page->FlushCommands();
    }
}

void QJSDeclarativeEngineInstance::PushJSCommand(JSContext* ctx, const RefPtr<JsCommand>& jsCommand, bool forceFlush)
{
    auto* instance = QJSDeclarativeEngineInstance::UnWrapEngineInstance(ctx);
    if (instance != nullptr) {
        instance->PushJSCommand(jsCommand, forceFlush);
    } else {
        LOGE("QJS context has no ref to engine instance. Failed!");
        return;
    }
}

void QJSDeclarativeEngineInstance::PostJsTask(JSContext* ctx, std::function<void()>&& task)
{
    auto* instance = QJSDeclarativeEngineInstance::UnWrapEngineInstance(ctx);
    if (instance != nullptr) {
        instance->GetDelegate()->PostJsTask(std::move(task));
    }
}

void QJSDeclarativeEngineInstance::TriggerPageUpdate(JSContext* ctx)
{
    auto* instance = QJSDeclarativeEngineInstance::UnWrapEngineInstance(ctx);
    if (instance != nullptr) {
        instance->GetDelegate()->TriggerPageUpdate(instance->GetRunningPage()->GetPageId());
        return;
    }
    LOGE("QJS context has no ref to instance. Failed!");
}

static int EvalBuf(JSContext* ctx, const char* buf, size_t bufLen, const char* filename, int evalFlags)
{
    JSValue val;
    int ret;

    val = JS_Eval(ctx, buf, bufLen, filename, evalFlags);
    if (JS_IsException(val)) {
        LOGE("[QJS Native EvalBuf()  FAILED FAILED FAILED!!!!\n\n");
        QjsUtils::JsStdDumpErrorAce(ctx);
        ret = -1;
    } else {
        ret = 0;
    }
    JS_FreeValue(ctx, val);
    return ret;
}

void QJSDeclarativeEngineInstance::output_object_code(JSContext* ctx, int fho, JSValueConst obj)
{
    uint8_t* out_buf;
    size_t out_buf_len;
    out_buf = JS_WriteObject(ctx, &out_buf_len, obj, JS_WRITE_OBJ_BYTECODE);
    if (!out_buf) {
        js_std_dump_error(ctx);
        return;
    }

    int count __attribute__((unused));
    count = write(fho, out_buf, out_buf_len);
    LOGD("Bytes written to file: %d vs. %zu", count, out_buf_len);

    js_free(ctx, out_buf);
}

JSValue QJSDeclarativeEngineInstance::eval_binary_buf(JSContext* ctx, const uint8_t* buf, size_t buf_len)
{
    JSValue obj;
    obj = JS_ReadObject(ctx, buf, buf_len, JS_READ_OBJ_BYTECODE);
    if (JS_IsException(obj)) {
        LOGE("eval_binary_buf (ReadObj) failed");
        js_std_dump_error(ctx);
        return obj;
    }
    return JS_EvalFunction(ctx, obj);
}

JSValue QJSDeclarativeEngineInstance::CompileSource(std::string url, const char* buf, size_t bufSize)
{
    LOGD("Compiling file url %s", url.c_str());

    ACE_SCOPED_TRACE("Compile JS");
    JSContext* ctx = GetQJSContext();

    std::size_t h1 = std::hash<std::string> {}(url);

    // temporary use image cache path to store the snapshot
    std::string separator = "/";
#if defined(WINDOWS_PLATFORM)
    separator = "\\";
#endif
    std::string filename = ImageCache::GetImageCacheFilePath() + separator;
    filename.append(std::to_string(h1));

    struct stat statbuf;
    int statres = stat(filename.c_str(), &statbuf);
    LOGD("Cache file stat result for %s, %d, errno %d, size %ld", filename.c_str(), statres, errno, statbuf.st_size);

    JSValue retVal = JS_NULL;
    int fhi;
    if (statres == 0 && (fhi = open(filename.c_str(), O_RDONLY)) != -1) {
        LOGD("Cache file open result for %s, fhi: %d, errno %d, reading", filename.c_str(), fhi, errno);
        uint8_t* in_buf = (uint8_t*)malloc(statbuf.st_size + 5);
        if (!in_buf) {
            close(fhi);
            return JS_NULL;
        }
        read(fhi, in_buf, statbuf.st_size);
        close(fhi);
        retVal = eval_binary_buf(GetQJSContext(), in_buf, statbuf.st_size);
        free(in_buf);
    } else {
        // Evaluate and write to the file
        LOGD("cache file does not exist, compiling source file");
        retVal = JS_Eval(GetQJSContext(), buf, bufSize, url.c_str(), JS_EVAL_TYPE_GLOBAL | JS_EVAL_FLAG_COMPILE_ONLY);
        if (JS_IsException(retVal)) {
            LOGE("Failed reading (source) JS file %s into QuickJS!", url.c_str());
            QjsUtils::JsStdDumpErrorAce(ctx);
            return JS_UNDEFINED;
        }

        int fho = creat(filename.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
        if (fho != -1) {
            LOGD("Compiled cache file opend for writing %s", filename.c_str());
            output_object_code(GetQJSContext(), fho, retVal);
            close(fho);
        } else {
            LOGE("Compiled cache file writing failed to %s", filename.c_str());
        }
    }
    return retVal;
}

void QJSDeclarativeEngineInstance::CallAnimationFinishJs(JSValue animationContext)
{
    JSContext* ctx = GetQJSContext();
    QjsHandleScope handleScope(ctx);
    auto proto = QjsUtils::GetPropertyStr(ctx, animationContext, "onfinish");
    if (!JS_IsFunction(ctx, proto)) {
        LOGE("cannot find 'CallAnimationFinishJs' function from global object, this should not happen!");
        return;
    }
    LOGD("animation onfinish event call");
    JSValue retVal = JS_Call(ctx, proto, animationContext, 0, {});
    JS_FreeValue(ctx, retVal);
    js_std_loop(ctx);
}

void QJSDeclarativeEngineInstance::CallAnimationCancelJs(JSValue animationContext)
{
    JSContext* ctx = GetQJSContext();
    QjsHandleScope handleScope(ctx);
    auto proto = QjsUtils::GetPropertyStr(ctx, animationContext, "oncancel");
    if (!JS_IsFunction(ctx, proto)) {
        return;
    }

    LOGD("animation oncancel event call");
    JSValue retVal = JS_Call(ctx, proto, animationContext, 0, {});
    JS_FreeValue(ctx, retVal);
    js_std_loop(ctx);
}

bool QJSDeclarativeEngineInstance::ExecuteDocumentJS(JSValue jsCode)
{
    LOGD("Executing JS ....");
    ACE_SCOPED_TRACE("Execute JS");

    JSContext* ctx = GetQJSContext();

    JSValue result = JS_EvalFunction(ctx, jsCode);
    if (JS_IsException(result)) {
        LOGD("Failed executing JS!");
        QjsUtils::JsStdDumpErrorAce(ctx);
        return false;
    }
    js_std_loop(ctx);
    LOGD("Executing JS -- DONE OK!");
    return true;
}

const JSCFunctionListEntry moduleFunctions[] = {};

int InitializeModules(JSContext* ctx, JSModuleDef* m)
{
    QJSContext::Scope scope(ctx);
    return JS_SetModuleExportList(ctx, m, moduleFunctions, countof(moduleFunctions));
}

JSModuleDef* JsInitModule(JSContext* ctx)
{
    LOGD("registering ace module methods\n");

    JSModuleDef* m = JS_NewCModule(ctx, "ace", InitializeModules);
    if (!m)
        return nullptr;

    JS_AddModuleExportList(ctx, m, moduleFunctions, countof(moduleFunctions));
    return m;
}

JSContext* InitJSContext(JSRuntime* rt, size_t maxStackSize, const RefPtr<FrontendDelegate>& delegate)
{
    LOGD("QJS Creating new JS context and loading HBS module");

    ACE_SCOPED_TRACE("Init JS Context");

    JSContext* ctx1 = JS_NewContext(rt);
    if (!ctx1) {
        LOGD("QJS cannot allocate JS context");
        return nullptr;
    }

    /*
     * Note: default 260k stack is not enough, lets use a value that should be enough
     *        for five cards 512k is too small, use 1MB
     */
    JS_SetMaxStackSize(ctx1, maxStackSize);

    js_std_add_helpers(ctx1, 0, NULL);

    InitConsole(ctx1);

    /* inject hbs native functions module */
    QJSContext::Scope scope(ctx1);
    JSValue globalObj = JS_GetGlobalObject(ctx1);
    JsRegisterViews(globalObj);

    /* make 'std' and 'os' visible to non module code */
    /* dito for hbs */
    const char* str = "// import ACE own functions in sce module \n"
                      "// QJS rel 1 Sept no longer defines global but globalThis object, fix it \n"
                      "var global = globalThis;\n";

    if (-1 == EvalBuf(ctx1, str, strlen(str), "JS Context initialize", JS_EVAL_TYPE_MODULE)) {
        LOGE("QJS created JS context but failed to init hbs, os, or std module.!");
    }
    NativeObjectInfo* nativeObjectInfo = new NativeObjectInfo();
    nativeObjectInfo->nativeObject = delegate->GetAbility();
    JSValue abilityValue = JS_NewExternal(ctx1, nativeObjectInfo, [](JSContext* ctx, void *data, void *hint) {
        NativeObjectInfo *info = (NativeObjectInfo *)data;
        if (info) {
            delete info;
        }
    }, nullptr);
    JS_SetPropertyStr(ctx1, globalObj, "ability", abilityValue);
    return ctx1;
}

bool QJSDeclarativeEngineInstance::InitJSEnv()
{
    ACE_SCOPED_TRACE("Init JS Env");
    runtime_ = JS_NewRuntime();
    if (!runtime_) {
        LOGE("QJS cannot allocate JS runtime");
        return false;
    }
    ACE_DCHECK(frontendDelegate_);
    context_ = InitJSContext(runtime_, MAX_STACK_SIZE, frontendDelegate_);
    if (!context_) {
        LOGE("QJS cannot allocate JS context");
        JS_FreeRuntime(runtime_);
        return false;
    }
    auto result = EvalBuf(context_, _binary_jsproxyClass_js_start,
        _binary_jsproxyClass_js_end - _binary_jsproxyClass_js_start, "jsproxyClass.js", JS_EVAL_TYPE_GLOBAL);
    if (result == -1) {
        EventInfo eventInfo;
        eventInfo.eventType = EXCEPTION_JS;
        eventInfo.errorType = static_cast<int32_t>(JsExcepType::JS_CONTEXT_INIT_ERR);
        EventReport::SendEvent(eventInfo);
        LOGW("JS Engine created JS context but failed to init proxy class!");
        return false;
    }
    // TODO: add js group function for js interface.

    // initialize native qjs engine.
    nativeEngine_ = new QuickJSNativeEngine(runtime_, context_);
    frontendDelegate_->AddTaskObserver([nativeEngine = nativeEngine_](){
        nativeEngine->Loop();
    });
    return true;
}

QJSDeclarativeEngineInstance::~QJSDeclarativeEngineInstance()
{
    if (context_) {
        JS_FreeContext(context_);
    }
    if (runtime_) {
        JS_FreeRuntime(runtime_);
    }
    if (nativeEngine_ != nullptr) {
        delete nativeEngine_;
    }
}

void QJSDeclarativeEngineInstance::FireAsyncEvent(const std::string& eventId, const std::string& param)
{
    LOGE("Not implemented!");
}

void QJSDeclarativeEngineInstance::RunGarbageCollection()
{
    if (runtime_) {
        JS_RunGC(runtime_);
    }
}

} // namespace OHOS::Ace::Framework
