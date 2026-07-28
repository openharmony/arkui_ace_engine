/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstring>
#include <thread>
#include <napi/native_api.h>

#include "rendercapture.h"
#include "render_capture_device.h"
#include "file_utils.h"
#include "subscription_manager.h"

namespace {

using namespace rendercapture;

// ---------------------------------------------------------------------------
// Event bridge: render thread → JS thread via napi_threadsafe_function
// ---------------------------------------------------------------------------

/** Payload passed through the threadsafe function. Heap-allocated, freed in CallJsCallback. */
struct EventPayload {
    std::string event;
    std::vector<uint8_t> frameData;
    int32_t width = 0;
    int32_t height = 0;
};

/** A JS callback registered by onFrame/onIdle/onError. */
struct JsSubscription {
    napi_ref callbackRef;
    napi_env env;
    bool once = false;
    bool removed = false;
};

static std::vector<JsSubscription> g_jsSubs;
static std::mutex g_jsSubsMutex;

/** The single threadsafe function handle shared by all event types. */
static std::atomic<napi_threadsafe_function> g_tsfn{nullptr};

static void CallJsCallback(napi_env env, napi_value /*jsCallback*/,
                           void* context, void* data)
{
    auto* payload = static_cast<EventPayload*>(data);
    if (!payload) return;

    std::lock_guard<std::mutex> lock(g_jsSubsMutex);
    for (size_t i = 0; i < g_jsSubs.size(); ) {
        auto& sub = g_jsSubs[i];
        if (sub.removed || sub.env != env) { i++; continue; }
        napi_value cb;
        napi_get_reference_value(env, sub.callbackRef, &cb);

        napi_value args[1];
        napi_create_object(env, &args[0]);

        napi_value ev;
        napi_create_string_utf8(env, payload->event.c_str(),
                                NAPI_AUTO_LENGTH, &ev);
        napi_set_named_property(env, args[0], "type", ev);

        if (!payload->frameData.empty()) {
            napi_value buf;
            void* p = nullptr;
            napi_create_arraybuffer(env, payload->frameData.size(), &p, &buf);
            memcpy(p, payload->frameData.data(), payload->frameData.size());
            napi_set_named_property(env, args[0], "data", buf);
            napi_value w, h;
            napi_create_int32(env, payload->width, &w);
            napi_create_int32(env, payload->height, &h);
            napi_set_named_property(env, args[0], "width", w);
            napi_set_named_property(env, args[0], "height", h);
        }

        napi_call_function(env, nullptr, cb, 1, args, nullptr);

        if (sub.once) {
            sub.removed = true;
            napi_delete_reference(env, sub.callbackRef);
            g_jsSubs.erase(g_jsSubs.begin() + i);
        } else {
            i++;
        }
    }
    delete payload;
}

static void OnRenderEvent(const std::string& event, const void* /*data*/,
                          void* /*ctx*/)
{
    auto* tsfn = g_tsfn.load();
    if (!tsfn) return;
    auto* payload = new EventPayload{event, {}, 0, 0};
    napi_call_threadsafe_function(tsfn, payload, napi_tsfn_nonblocking);
}

// ---------------------------------------------------------------------------
// Exported functions — frame capture (convenience)
// ---------------------------------------------------------------------------

static napi_value CaptureFrame(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    int32_t timeoutMs = 5000;
    if (argc >= 1) {
        napi_get_value_int32(env, argv[0], &timeoutMs);
    }

    // Synchronous on JS thread — same as old working CaptureFrame.
    int64_t id = RenderCapture::Get().RequestFrame();
    bool ok = RenderCapture::Get().AwaitFrame(id, timeoutMs);
    Frame frame = RenderCapture::Get().CollectFrame(id);

    napi_value promise;
    napi_deferred deferred;
    napi_create_promise(env, &deferred, &promise);

    if (!ok || frame.data.empty()) {
        napi_value msg;
        napi_create_string_utf8(env, "frame capture failed", NAPI_AUTO_LENGTH, &msg);
        napi_value err;
        napi_create_error(env, nullptr, msg, &err);
        napi_reject_deferred(env, deferred, err);
        return promise;
    }

    napi_value result;
    napi_create_object(env, &result);
    napi_value dataBuf;
    void* dataPtr = nullptr;
    napi_create_arraybuffer(env, frame.data.size(), &dataPtr, &dataBuf);
    memcpy(dataPtr, frame.data.data(), frame.data.size());
    napi_set_named_property(env, result, "data", dataBuf);
    napi_value w, h;
    napi_create_int32(env, frame.width, &w);
    napi_create_int32(env, frame.height, &h);
    napi_set_named_property(env, result, "width", w);
    napi_set_named_property(env, result, "height", h);
    napi_resolve_deferred(env, deferred, result);
    return promise;
}

// ---------------------------------------------------------------------------
// Exported functions — frame capture (granular)
// ---------------------------------------------------------------------------

static napi_value RequestFrame(napi_env env, napi_callback_info /*info*/)
{
    int64_t id = RenderCapture::Get().RequestFrame();
    napi_value result;
    napi_create_int64(env, id, &result);
    return result;
}

static napi_value AwaitFrame(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value argv[2];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    int64_t requestId = 0;
    int32_t timeoutMs = 5000;
    napi_get_value_int64(env, argv[0], &requestId);
    if (argc >= 2) napi_get_value_int32(env, argv[1], &timeoutMs);

    bool ok = RenderCapture::Get().AwaitFrame(requestId, timeoutMs);
    napi_value result;
    napi_get_boolean(env, ok, &result);
    return result;
}

static napi_value CollectFrame(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    int64_t requestId = 0;
    napi_get_value_int64(env, argv[0], &requestId);

    Frame frame = RenderCapture::Get().CollectFrame(requestId);
    napi_value result;
    napi_create_object(env, &result);
    napi_value dataBuf;
    void* p = nullptr;
    napi_create_arraybuffer(env, frame.data.size(), &p, &dataBuf);
    if (!frame.data.empty()) {
        memcpy(p, frame.data.data(), frame.data.size());
    }
    napi_set_named_property(env, result, "data", dataBuf);
    napi_value w, h;
    napi_create_int32(env, frame.width, &w);
    napi_create_int32(env, frame.height, &h);
    napi_set_named_property(env, result, "width", w);
    napi_set_named_property(env, result, "height", h);
    return result;
}

static napi_value SkipFrames(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    int32_t count = 0;
    if (argc >= 1) napi_get_value_int32(env, argv[0], &count);
    RenderCapture::Get().SkipFrames(count);
    return nullptr;
}

static napi_value WaitForIdleNapi(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    int32_t timeoutMs = 5000;
    if (argc >= 1) napi_get_value_int32(env, argv[0], &timeoutMs);

    bool idle = RenderCapture::Get().WaitForIdle(timeoutMs);
    napi_value result;
    napi_get_boolean(env, idle, &result);
    return result;
}

// ---------------------------------------------------------------------------
// Idle detection orchestration
// ---------------------------------------------------------------------------

static int64_t GetTimestampMs()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
}

struct IdleOrchestrator {
    napi_deferred deferred;
    int32_t timeoutMs;
    int64_t startMs;
};

static void IdleExecute(napi_env /*env*/, void* data)
{
    auto* orch = static_cast<IdleOrchestrator*>(data);
    RenderCapture::Get().WaitForIdle(orch->timeoutMs);
}

static void IdleComplete(napi_env env, napi_status /*status*/, void* data)
{
    auto* orch = static_cast<IdleOrchestrator*>(data);
    // WaitForIdle returned. Resolve (the call itself handles stability).
    napi_value undef;
    napi_get_undefined(env, &undef);
    napi_resolve_deferred(env, orch->deferred, undef);
    delete orch;
}

static napi_value AwaitIdle(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    int32_t timeoutMs = 2000;
    if (argc >= 1) napi_get_value_int32(env, argv[0], &timeoutMs);

    // Simple implementation: request render stability, then poll
    // via CaptureFrame on the JS thread. Worker threads can't access
    // PipelineContext::GetCurrentContext().
    RenderCapture::Get().RequestRenderStable();

    napi_value promise;
    napi_deferred deferred;
    napi_create_promise(env, &deferred, &promise);

    auto* orch = new IdleOrchestrator;
    orch->deferred = deferred;
    orch->timeoutMs = timeoutMs;
    orch->startMs = GetTimestampMs();

    napi_value workName;
    napi_create_string_utf8(env, "awaitIdle", NAPI_AUTO_LENGTH, &workName);
    napi_async_work work;
    napi_create_async_work(env, nullptr, workName, IdleExecute, IdleComplete, orch, &work);
    napi_queue_async_work(env, work);

    return promise;
}

// ---------------------------------------------------------------------------
// Exported functions — touch
// ---------------------------------------------------------------------------

static napi_value TouchDown(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value argv[2];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    double x = 0, y = 0;
    if (argc >= 2) {
        napi_get_value_double(env, argv[0], &x);
        napi_get_value_double(env, argv[1], &y);
    }
    RenderCapture::Get().TouchDown(static_cast<float>(x), static_cast<float>(y));
    return nullptr;
}

static napi_value TouchMove(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value argv[2];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    double x = 0, y = 0;
    if (argc >= 2) {
        napi_get_value_double(env, argv[0], &x);
        napi_get_value_double(env, argv[1], &y);
    }
    RenderCapture::Get().TouchMove(static_cast<float>(x), static_cast<float>(y));
    return nullptr;
}

static napi_value TouchUp(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value argv[2];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    double x = 0, y = 0;
    if (argc >= 2) {
        napi_get_value_double(env, argv[0], &x);
        napi_get_value_double(env, argv[1], &y);
    }
    RenderCapture::Get().TouchUp(static_cast<float>(x), static_cast<float>(y));
    return nullptr;
}

// ---------------------------------------------------------------------------
// Exported functions — events
// ---------------------------------------------------------------------------

static napi_value SubscribeEvent(napi_env env, napi_callback_info info,
                                 const std::string& event, bool once)
{
    size_t argc = 1;
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    JsSubscription sub;
    sub.env = env;
    sub.once = once;
    napi_create_reference(env, argv[0], 1, &sub.callbackRef);

    std::lock_guard<std::mutex> lock(g_jsSubsMutex);
    g_jsSubs.push_back(sub);

    napi_value result;
    napi_create_object(env, &result);

    size_t idx = g_jsSubs.size() - 1;
    RenderCapture::Get()
        .GetSubscriptionManager()
        .Add(event, OnRenderEvent, reinterpret_cast<void*>(idx));

    return result;
}

static napi_value OnFrame(napi_env env, napi_callback_info info)
{
    return SubscribeEvent(env, info, "frame", false);
}

static napi_value OnceFrame(napi_env env, napi_callback_info info)
{
    return SubscribeEvent(env, info, "frame", true);
}

static napi_value OnIdle(napi_env env, napi_callback_info info)
{
    return SubscribeEvent(env, info, "idle", false);
}

static napi_value OnceIdle(napi_env env, napi_callback_info info)
{
    return SubscribeEvent(env, info, "idle", true);
}

static napi_value Abort(napi_env env, napi_callback_info /*info*/)
{
    RenderCapture::Get().SkipFrames(INT32_MAX);
    return nullptr;
}

// ---------------------------------------------------------------------------
// Exported functions — environment / lifecycle
// ---------------------------------------------------------------------------

static napi_value IsPreviewer(napi_env env, napi_callback_info /*info*/)
{
    napi_value result;
    napi_get_boolean(env, RenderCapture::Get().IsPreviewer(), &result);
    return result;
}

static napi_value IsHeadless(napi_env env, napi_callback_info /*info*/)
{
    napi_value result;
    napi_get_boolean(env, RenderCapture::Get().IsHeadless(), &result);
    return result;
}

static napi_value GetScreenSize(napi_env env, napi_callback_info /*info*/)
{
    int32_t w = 0, h = 0;
    RenderCapture::Get().GetScreenSize(&w, &h);
    napi_value result;
    napi_create_object(env, &result);
    napi_value wv, hv;
    napi_create_int32(env, w, &wv);
    napi_create_int32(env, h, &hv);
    napi_set_named_property(env, result, "width", wv);
    napi_set_named_property(env, result, "height", hv);
    return result;
}

static napi_value WriteFile(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value argv[2];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    if (argc < 2) {
        napi_throw_error(env, nullptr, "writeFile requires path and data");
        return nullptr;
    }

    size_t pathLen = 0;
    napi_get_value_string_utf8(env, argv[0], nullptr, 0, &pathLen);
    std::string path(pathLen, '\0');
    napi_get_value_string_utf8(env, argv[0], path.data(), pathLen + 1, &pathLen);

    void* data = nullptr;
    size_t dataLen = 0;
    napi_get_arraybuffer_info(env, argv[1], &data, &dataLen);

    bool ok = rendercapture::WriteFile(path, static_cast<const uint8_t*>(data), dataLen);
    napi_value result;
    napi_get_boolean(env, ok, &result);
    return result;
}

// ---------------------------------------------------------------------------
// Exported functions — lifecycle
// ---------------------------------------------------------------------------

static napi_value StartIdleDetection(napi_env /*env*/, napi_callback_info /*info*/)
{
    RenderCapture::Get().StartIdleDetection();
    return nullptr;
}

#ifdef PREVIEW
static napi_value ExitHeadlessTest(napi_env env, napi_callback_info /*info*/)
{
    RenderCapture::Get().SetVisualTestDone();
    return nullptr;
}
#endif

static napi_value SetHapDir(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    size_t len = 0;
    napi_get_value_string_utf8(env, argv[0], nullptr, 0, &len);
    std::string dir(len, '\0');
    napi_get_value_string_utf8(env, argv[0], dir.data(), len + 1, &len);
    RenderCapture::Get().SetHapDir(dir);
    return nullptr;
}

// ---------------------------------------------------------------------------
// Module registration
// ---------------------------------------------------------------------------

napi_value SetOutputDir(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    size_t len = 0;
    napi_get_value_string_utf8(env, argv[0], nullptr, 0, &len);
    std::string dir(len, '\0');
    napi_get_value_string_utf8(env, argv[0], dir.data(), len + 1, &len);
    RenderCapture::Get().SetOutputDir(dir);
    return nullptr;
}

static napi_value RequestRenderStableNapi(napi_env env, napi_callback_info /*info*/)
{
    RenderCapture::Get().RequestRenderStable();
    return nullptr;
}

static napi_value IsRenderStableNapi(napi_env env, napi_callback_info /*info*/)
{
    napi_value result;
    napi_get_boolean(env, RenderCapture::Get().IsRenderStable(), &result);
    return result;
}

napi_value RenderCaptureExport(napi_env env, napi_value exports)
{
    // Create the threadsafe function for render→JS event delivery.
    napi_value tsfnName;
    napi_create_string_utf8(env, "headlessTest_events", NAPI_AUTO_LENGTH, &tsfnName);
    napi_threadsafe_function tsfn = nullptr;
    napi_create_threadsafe_function(env,
        nullptr, nullptr, tsfnName,
        64, 1, nullptr, nullptr, nullptr,
        CallJsCallback, &tsfn);
    g_tsfn.store(tsfn);
    napi_unref_threadsafe_function(env, tsfn);

    RenderCapture::Get().GetSubscriptionManager().Add("frame", OnRenderEvent, nullptr);
    RenderCapture::Get().GetSubscriptionManager().Add("idle", OnRenderEvent, nullptr);
    RenderCapture::Get().GetSubscriptionManager().Add("error", OnRenderEvent, nullptr);
    RenderCapture::Get().GetSubscriptionManager().Add("scroll.end", OnRenderEvent, nullptr);
    RenderCapture::Get().GetSubscriptionManager().Add("animation.end", OnRenderEvent, nullptr);

    napi_property_descriptor desc[] = {
        {"captureFrame",   nullptr, CaptureFrame,   nullptr, nullptr, nullptr, napi_default, nullptr},
        {"requestFrame",   nullptr, RequestFrame,   nullptr, nullptr, nullptr, napi_default, nullptr},
        {"awaitFrame",     nullptr, AwaitFrame,     nullptr, nullptr, nullptr, napi_default, nullptr},
        {"collectFrame",   nullptr, CollectFrame,   nullptr, nullptr, nullptr, napi_default, nullptr},
        {"skipFrames",     nullptr, SkipFrames,     nullptr, nullptr, nullptr, napi_default, nullptr},
        {"waitForIdle",    nullptr, WaitForIdleNapi, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"awaitIdle",      nullptr, AwaitIdle,      nullptr, nullptr, nullptr, napi_default, nullptr},
        {"touchDown",      nullptr, TouchDown,      nullptr, nullptr, nullptr, napi_default, nullptr},
        {"touchMove",      nullptr, TouchMove,      nullptr, nullptr, nullptr, napi_default, nullptr},
        {"touchUp",        nullptr, TouchUp,        nullptr, nullptr, nullptr, napi_default, nullptr},
        {"onFrame",        nullptr, OnFrame,        nullptr, nullptr, nullptr, napi_default, nullptr},
        {"onceFrame",      nullptr, OnceFrame,      nullptr, nullptr, nullptr, napi_default, nullptr},
        {"onIdle",         nullptr, OnIdle,         nullptr, nullptr, nullptr, napi_default, nullptr},
        {"onceIdle",       nullptr, OnceIdle,       nullptr, nullptr, nullptr, napi_default, nullptr},
        {"abort",          nullptr, Abort,          nullptr, nullptr, nullptr, napi_default, nullptr},
        {"isPreviewer",    nullptr, IsPreviewer,    nullptr, nullptr, nullptr, napi_default, nullptr},
        {"isHeadless",     nullptr, IsHeadless,     nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getScreenSize",  nullptr, GetScreenSize,  nullptr, nullptr, nullptr, napi_default, nullptr},
        {"writeFile",      nullptr, WriteFile,      nullptr, nullptr, nullptr, napi_default, nullptr},
#ifdef PREVIEW
        {"exit",           nullptr, ExitHeadlessTest,nullptr, nullptr, nullptr, napi_default, nullptr},
#endif
        {"setOutputDir",   nullptr, SetOutputDir,   nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setHapDir",      nullptr, SetHapDir,      nullptr, nullptr, nullptr, napi_default, nullptr},
        {"startIdleDetection", nullptr, StartIdleDetection, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"requestRenderStable", nullptr, RequestRenderStableNapi, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"isRenderStable", nullptr, IsRenderStableNapi, nullptr, nullptr, nullptr, napi_default, nullptr},
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);

    napi_value envObj;
    napi_create_object(env, &envObj);

    napi_value isPV, isHL;
    napi_get_boolean(env, RenderCapture::Get().IsPreviewer(), &isPV);
    napi_get_boolean(env, RenderCapture::Get().IsHeadless(), &isHL);
    napi_set_named_property(env, envObj, "isPreviewer", isPV);
    napi_set_named_property(env, envObj, "isHeadless", isHL);

    napi_value screenSize;
    napi_create_object(env, &screenSize);
    int32_t sw = 0, sh = 0;
    RenderCapture::Get().GetScreenSize(&sw, &sh);
    napi_value wv, hv;
    napi_create_int32(env, sw, &wv);
    napi_create_int32(env, sh, &hv);
    napi_set_named_property(env, screenSize, "width", wv);
    napi_set_named_property(env, screenSize, "height", hv);
    napi_set_named_property(env, envObj, "screenSize", screenSize);
    napi_set_named_property(env, exports, "env", envObj);

    printf("[RenderCapture] event bridge initialized (tsfn=%p)\n", (void*)g_tsfn.load());

    return exports;
}

static napi_module captureModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = nullptr,
    .nm_modname = "arkui.visualtest.capture",
    .nm_priv = nullptr,
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RenderCaptureRegister()
{
    captureModule.nm_register_func = RenderCaptureExport;
    napi_module_register(&captureModule);
    printf("[RenderCapture] NAPI module 'arkui.visualtest.capture' registered\n");
}

}  // namespace
