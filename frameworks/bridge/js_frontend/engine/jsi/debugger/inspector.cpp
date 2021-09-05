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

#include "frameworks/bridge/js_frontend/engine/jsi/debugger/inspector.h"

#include <dlfcn.h>

#include "base/log/log.h"
#include "frameworks/bridge/js_frontend/engine/jsi/debugger/ws_server.h"

namespace OHOS::Ace::Framework {
namespace {
std::unique_ptr<WsServer> g_websocketServer = nullptr;
void* g_handle = nullptr;
constexpr char ARK_DEBUGGER_SHARED_LIB[] = "libark_ecma_debugger.so";

void* HandleClient(void* const server)
{
    LOGI("HandleClient");
    if (server == nullptr) {
        LOGE("HandleClient server nullptr");
        return nullptr;
    }
    static_cast<WsServer*>(server)->RunServer();
    return nullptr;
}

void* GetArkDynFunction(const char* symbol)
{
    if (g_handle == nullptr) {
        LOGE("Failed to open shared library %{public}s, reason: %{public}sn", ARK_DEBUGGER_SHARED_LIB, dlerror());
        return nullptr;
    }

    auto function = dlsym(g_handle, symbol);
    if (function == nullptr) {
        LOGE("Failed to get symbol %{public}s in %{public}s", symbol, ARK_DEBUGGER_SHARED_LIB);
    }
    return function;
}

void OnMessage(const std::string& message)
{
    if (message.empty()) {
        LOGE("message is empty");
        return;
    }
    auto dispatch = reinterpret_cast<void (*)(const std::string&)>(GetArkDynFunction("DispatchProtocolMessage"));
    if (dispatch == nullptr) {
        LOGE("dispatch is empty");
        return;
    }
    dispatch(message);
}

void SendReply(const std::string& message)
{
    if (g_websocketServer != nullptr) {
        g_websocketServer->SendReply(message);
    }
}

void ResetService()
{
    if (g_handle != nullptr) {
        dlclose(g_handle);
        g_handle = nullptr;
    }
    if (g_websocketServer != nullptr) {
        g_websocketServer->StopServer();
        g_websocketServer.reset();
    }
}

} // namespace

bool StartDebug(const std::string& componentName, const EcmaVM *vm)
{
    LOGI("StartDebug: %{private}s", componentName.c_str());
    g_handle = dlopen(ARK_DEBUGGER_SHARED_LIB, RTLD_LAZY);
    if (g_handle == nullptr) {
        LOGE("handle is empty");
        return false;
    }
    g_websocketServer = std::make_unique<WsServer>(componentName, std::bind(&OnMessage, std::placeholders::_1));
    auto initialize = reinterpret_cast<void (*)(const std::function<void(std::string)> &,
        const EcmaVM *)>(GetArkDynFunction("InitializeDebugger"));
    if (initialize == nullptr) {
        ResetService();
        return false;
    }
    initialize(std::bind(&SendReply, std::placeholders::_1), vm);

    pthread_t tid;
    if (pthread_create(&tid, nullptr, &HandleClient, static_cast<void*>(g_websocketServer.get())) != 0) {
        LOGE("pthread_create fail!");
        ResetService();
        return false;
    }
    return true;
}

void StopDebug(const std::string& componentName)
{
    LOGI("StopDebug: %{private}s", componentName.c_str());
    if (g_handle != nullptr) {
        dlclose(g_handle);
        g_handle = nullptr;
    }
    if (g_websocketServer != nullptr) {
        g_websocketServer->StopServer();
        g_websocketServer.reset();
    }
    auto uninitialize = reinterpret_cast<void (*)()>(GetArkDynFunction("UninitializeDebugger"));
    if (uninitialize == nullptr) {
        return;
    }
    uninitialize();
    LOGI("StopDebug end");
}

} // namespace OHOS::Ace::Framework
