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

#include "frameworks/bridge/js_frontend/engine/jsi/debugger/inspector.h"

#include <dlfcn.h>
#include <shared_mutex>
#include <unordered_map>

#include "base/log/log.h"
#include "frameworks/bridge/js_frontend/engine/jsi/debugger/ws_server.h"

namespace OHOS::Ace::Framework {
namespace {
std::unordered_map<const void *, Inspector *> g_inspector;
std::shared_mutex g_mutex;

thread_local void* g_handle = nullptr;
thread_local void* g_vm = nullptr;

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
        g_handle = dlopen(ARK_DEBUGGER_SHARED_LIB, RTLD_LAZY);
        if (g_handle == nullptr) {
            LOGE("Failed to open shared library %{public}s, reason: %{public}sn", ARK_DEBUGGER_SHARED_LIB, dlerror());
            return nullptr;
        }
    }

    auto function = dlsym(g_handle, symbol);
    if (function == nullptr) {
        LOGE("Failed to get symbol %{public}s in %{public}s", symbol, ARK_DEBUGGER_SHARED_LIB);
    }
    return function;
}

void DispatchMsgToArk(int sign)
{
    std::shared_lock<std::shared_mutex> lock(g_mutex);
    auto iter = g_inspector.find(g_vm);
    if (iter == g_inspector.end()) {
        return;
    }
    auto* inspector = iter->second;
    if (inspector == nullptr || inspector->websocketServer_ == nullptr || inspector->isDispatchingMsg_) {
        return;
    }
    auto processMsg = reinterpret_cast<void (*)(void *, const std::string &)>(
        GetArkDynFunction("DispatchProtocolMessage"));
    if (processMsg == nullptr) {
        LOGE("processMessage is empty");
        return;
    }
    inspector->isDispatchingMsg_ = true;
    while (!inspector->websocketServer_->ideMsgQueue.empty()) {
        const std::string message = inspector->websocketServer_->ideMsgQueue.front();
        inspector->websocketServer_->ideMsgQueue.pop();
        processMsg(inspector->vm_, message);
        std::string startDebugging("Runtime.runIfWaitingForDebugger");
        if (message.find(startDebugging, 0) != std::string::npos) {
            inspector->waitingForDebugger_ = false;
        }
    }
    inspector->isDispatchingMsg_ = false;
}

void SendReply(const void *vm, const std::string& message)
{
    std::shared_lock<std::shared_mutex> lock(g_mutex);
    auto iter = g_inspector.find(vm);
    if (iter != g_inspector.end() && iter->second != nullptr &&
        iter->second->websocketServer_ != nullptr) {
        iter->second->websocketServer_->SendReply(message);
    }
}

void ResetService()
{
    auto iter = g_inspector.find(g_vm);
    if (iter != g_inspector.end() && iter->second != nullptr &&
        iter->second->websocketServer_ != nullptr) {
        iter->second->websocketServer_->StopServer();
        delete iter->second;
        iter->second = nullptr;
        g_inspector.erase(iter);
    }
    if (g_handle != nullptr) {
        dlclose(g_handle);
        g_handle = nullptr;
    }
}

} // namespace

void Inspector::OnMessage()
{
    pthread_kill(tid_, SIGALRM);
    return;
}

void Inspector::InitializeInspector(const std::string& componentName, int32_t instanceId)
{
    websocketServer_ = std::make_unique<WsServer>(componentName, std::bind(&Inspector::OnMessage, this), instanceId);
}

bool StartDebug(const std::string& componentName, void *vm, bool isDebugMode, int32_t instanceId)
{
    LOGI("StartDebug: %{private}s", componentName.c_str());
    auto initialize = reinterpret_cast<void (*)(const std::function<void(
        const void *, const std::string &)> &, void *)>(GetArkDynFunction("InitializeDebugger"));
    std::unordered_map<const void *, Inspector *>::iterator iter;
    {
        std::unique_lock<std::shared_mutex> lock(g_mutex);
        if (initialize == nullptr) {
            ResetService();
            return false;
        }
        if (!g_inspector.try_emplace(vm, new Inspector()).second) {
            LOGE("Already have the same vm in the map");
            return false;
        }
        iter = g_inspector.find(vm);
        if (iter == g_inspector.end()) {
            return false;
        }
        iter->second->InitializeInspector(componentName, instanceId);
        iter->second->tid_ = pthread_self();
        iter->second->waitingForDebugger_ = isDebugMode;
        iter->second->vm_ = vm;
    }

    g_vm = vm;
    g_handle = dlopen(ARK_DEBUGGER_SHARED_LIB, RTLD_LAZY);
    if (g_handle == nullptr) {
        LOGE("handle is empty");
        return false;
    }

    initialize(std::bind(&SendReply, vm, std::placeholders::_2), vm);
    signal(SIGALRM, &DispatchMsgToArk);

    std::shared_lock<std::shared_mutex> lock(g_mutex);
    pthread_t tid;
    if (pthread_create(&tid, nullptr, &HandleClient, static_cast<void *>(
        iter->second->websocketServer_.get())) != 0) {
        LOGE("pthread_create fail!");
        return false;
    }

    while (iter->second->waitingForDebugger_) {
        usleep(iter->second->DEBUGGER_WAIT_SLEEP_TIME);
    }
    LOGI("StartDebug Continue");
    return true;
}

void StopDebug(const std::string& componentName)
{
    std::unique_lock<std::shared_mutex> lock(g_mutex);
    LOGI("StopDebug: %{private}s", componentName.c_str());
    auto iter = g_inspector.find(g_vm);
    if (iter == g_inspector.end() || iter->second == nullptr) {
        return;
    }
    auto uninitialize = reinterpret_cast<void (*)(void *)>(GetArkDynFunction("UninitializeDebugger"));
    if (uninitialize == nullptr) {
        return;
    }
    uninitialize(g_vm);
    ResetService();
    LOGI("StopDebug end");
}

} // namespace OHOS::Ace::Framework
