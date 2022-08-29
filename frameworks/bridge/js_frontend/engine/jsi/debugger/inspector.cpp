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

#include "inspector.h"

#include <chrono>
#include <shared_mutex>
#include <thread>
#include <unordered_map>

#include "hilog_wrapper.h"
#include "library_loader.h"

namespace OHOS::Ace::Framework {
namespace {
enum DispatchStatus : int32_t {
    UNKNOWN = 0,
    DISPATCHING,
    DISPATCHED
};

using InitializeDebugger = void(*)(void*, const std::function<void(const void*, const std::string&)>&);
using UninitializeDebugger = void(*)(void*);
using WaitForDebugger = void(*)(void*);
using OnMessage = void(*)(void*, std::string&&);
using ProcessMessage = void(*)(void*);
using GetDispatchStatus = int32_t(*)(void*);

OnMessage g_onMessage = nullptr;
InitializeDebugger g_initializeDebugger = nullptr;
UninitializeDebugger g_uninitializeDebugger = nullptr;
WaitForDebugger g_waitForDebugger = nullptr;
ProcessMessage g_processMessage = nullptr;
GetDispatchStatus g_getDispatchStatus = nullptr;

std::atomic<bool> g_hasArkFuncsInited = false;
std::unordered_map<const void*, Inspector*> g_inspectors;
std::shared_mutex g_mutex;

thread_local void* g_handle = nullptr;
thread_local void* g_vm = nullptr;

#if defined(WINDOWS_PLATFORM)
constexpr char ARK_DEBUGGER_SHARED_LIB[] = "libark_ecma_debugger.dll";
#elif defined(MAC_PLATFORM)
constexpr char ARK_DEBUGGER_SHARED_LIB[] = "libark_ecma_debugger.dylib";
#else
constexpr char ARK_DEBUGGER_SHARED_LIB[] = "libark_ecma_debugger.so";
#endif

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

bool LoadArkDebuggerLibrary()
{
    if (g_handle != nullptr) {
        LOGE("Already opened");
        return false;
    }
    g_handle = Load(ARK_DEBUGGER_SHARED_LIB);
    if (g_handle == nullptr) {
        return false;
    }
    return true;
}

void* GetArkDynFunction(const char* symbol)
{
    return ResolveSymbol(g_handle, symbol);
}

void SendReply(const void* vm, const std::string& message)
{
    std::shared_lock<std::shared_mutex> lock(g_mutex);
    auto iter = g_inspectors.find(vm);
    if (iter != g_inspectors.end() && iter->second != nullptr &&
        iter->second->websocketServer_ != nullptr) {
        iter->second->websocketServer_->SendReply(message);
    }
}

void ResetServiceLocked()
{
    auto iter = g_inspectors.find(g_vm);
    if (iter != g_inspectors.end() && iter->second != nullptr &&
        iter->second->websocketServer_ != nullptr) {
        iter->second->websocketServer_->StopServer();
        delete iter->second;
        iter->second = nullptr;
        g_inspectors.erase(iter);
    }
    if (g_handle != nullptr) {
        CloseHandle(g_handle);
        g_handle = nullptr;
    }
}

bool InitializeInspector(void* vm, const std::string& componentName, int32_t instanceId,
    const DebuggerPostTask& debuggerPostTask)
{
    std::unique_lock<std::shared_mutex> lock(g_mutex);
    auto iter = g_inspectors.find(vm);
    if (iter != g_inspectors.end()) {
        LOGE("Already have the same vm in the map");
        return false;
    }

    Inspector *newInspector = new Inspector();
    if (!g_inspectors.emplace(vm, newInspector).second) {
        delete newInspector;
        return false;
    }

    newInspector->tid_ = pthread_self();
    newInspector->vm_ = vm;
    newInspector->debuggerPostTask_ = debuggerPostTask;
    newInspector->websocketServer_ = std::make_unique<WsServer>(componentName,
        std::bind(&Inspector::OnMessage, newInspector, std::placeholders::_1), instanceId);

    pthread_t tid;
    if (pthread_create(&tid, nullptr, &HandleClient, static_cast<void *>(
        newInspector->websocketServer_.get())) != 0) {
        LOGE("Create inspector thread failed");
        return false;
    }

    return true;
}

bool InitializeArkFunctions()
{
    // no need to initialize again in case of multi-instance
    if (g_hasArkFuncsInited) {
        return true;
    }

    std::unique_lock<std::shared_mutex> lock(g_mutex);
    if (g_hasArkFuncsInited) {
        return true;
    }
    g_initializeDebugger = reinterpret_cast<InitializeDebugger>(
        GetArkDynFunction("InitializeDebugger"));
    if (g_initializeDebugger == nullptr) {
        ResetServiceLocked();
        return false;
    }
    g_uninitializeDebugger = reinterpret_cast<UninitializeDebugger>(
        GetArkDynFunction("UninitializeDebugger"));
    if (g_uninitializeDebugger == nullptr) {
        ResetServiceLocked();
        return false;
    }
    g_waitForDebugger = reinterpret_cast<WaitForDebugger>(
        GetArkDynFunction("WaitForDebugger"));
    if (g_waitForDebugger == nullptr) {
        ResetServiceLocked();
        return false;
    }
    g_onMessage = reinterpret_cast<OnMessage>(
        GetArkDynFunction("OnMessage"));
    if (g_onMessage == nullptr) {
        ResetServiceLocked();
        return false;
    }
    g_getDispatchStatus = reinterpret_cast<GetDispatchStatus>(
        GetArkDynFunction("GetDispatchStatus"));
    if (g_getDispatchStatus == nullptr) {
        ResetServiceLocked();
        return false;
    }
    g_processMessage = reinterpret_cast<ProcessMessage>(
        GetArkDynFunction("ProcessMessage"));
    if (g_processMessage == nullptr) {
        ResetServiceLocked();
        return false;
    }

    g_hasArkFuncsInited = true;
    return true;
}
} // namespace

void Inspector::OnMessage(std::string&& msg)
{
    g_onMessage(vm_, std::move(msg));

    // message will be processed soon if the debugger thread is in running or waiting status
    if (g_getDispatchStatus(vm_) != DispatchStatus::UNKNOWN) {
        return;
    }
    std::this_thread::sleep_for(std::chrono::microseconds(DELAY_CHECK_DISPATCH_STATUS));
    if (g_getDispatchStatus(vm_) != DispatchStatus::UNKNOWN) {
        return;
    }

    // the debugger thread maybe in idle status, so try to post a task to wake it up
    if (debuggerPostTask_ != nullptr) {
        debuggerPostTask_([tid = tid_, vm = vm_] {
            if (tid != pthread_self()) {
                LOGE("Task not in debugger thread");
                return;
            }
            g_processMessage(vm);
        });
    } else {
        LOGW("No debuggerPostTask provided");
    }
}

bool StartDebug(const std::string& componentName, void* vm, bool isDebugMode, int32_t instanceId,
    const DebuggerPostTask& debuggerPostTask)
{
    g_vm = vm;
    if (!LoadArkDebuggerLibrary()) {
        return false;
    }
    if (!InitializeArkFunctions()) {
        LOGE("Initialize ark functions failed");
        return false;
    }

    g_initializeDebugger(vm, std::bind(&SendReply, vm, std::placeholders::_2));

    if (!InitializeInspector(vm, componentName, instanceId, debuggerPostTask)) {
        LOGE("Initialize inspector failed");
        return false;
    }

    if (isDebugMode) {
        g_waitForDebugger(vm);
    }
    return true;
}

void StopDebug(const std::string& componentName)
{
    LOGI("StopDebug: %{private}s", componentName.c_str());
    std::unique_lock<std::shared_mutex> lock(g_mutex);
    auto iter = g_inspectors.find(g_vm);
    if (iter == g_inspectors.end() || iter->second == nullptr) {
        return;
    }

    g_uninitializeDebugger(g_vm);
    ResetServiceLocked();
    LOGI("StopDebug end");
}
} // namespace OHOS::Ace::Framework
