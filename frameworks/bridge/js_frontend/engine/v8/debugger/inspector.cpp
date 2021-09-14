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

#include "frameworks/bridge/js_frontend/engine/v8/debugger/inspector.h"

namespace V8Debugger {

static std::unique_ptr<Inspector> g_inspector = nullptr;

static void* HandleClient(void* inspector)
{
    LOGI("HandleClient");
    if (inspector == nullptr) {
        LOGE("inspector=nullptr");
        return nullptr;
    }
    reinterpret_cast<Inspector*>(inspector)->StartAgent();
    return nullptr;
}

void DispatchMsgToV8(int sign)
{
    if ((g_inspector == nullptr) || (g_inspector->isDispatchingMsg)) {
        return;
    }
    g_inspector->isDispatchingMsg = true;
    while (!g_inspector->ideMsgQueue.empty()) {
        const std::string message = g_inspector->ideMsgQueue.front();
        g_inspector->ideMsgQueue.pop();
        v8_inspector::StringView protocolMessage = ConvertToStringView(message);
        g_inspector->inspectorClient->DispatchProtocolMessage(protocolMessage);

        std::string startDebugging("Runtime.runIfWaitingForDebugger");
        if (message.find(startDebugging, 0) != std::string::npos) {
            g_inspector->waitingForDebugger = false;
        }
    }
    g_inspector->isDispatchingMsg = false;
}

void StartDebug(
    const std::unique_ptr<v8::Platform>& platform,
    const v8::Local<v8::Context>& context,
    const std::string& componentName)
{
    LOGI("StartDebug!");
    g_inspector = std::make_unique<Inspector>();
    if (g_inspector == nullptr) {
        LOGE("g_inspector = nullptr!");
        return;
    }
    g_inspector->InitializeInspector(platform, context);
    g_inspector->waitingForDebugger = true;
    pthread_t tid;
    if (pthread_create(&tid, nullptr, &HandleClient, reinterpret_cast<void*>(g_inspector.get())) != 0) {
        LOGE("pthread_create fail!");
        return;
    }
    g_inspector->websocketServer->tid = pthread_self();
    g_inspector->websocketServer->componentName = componentName;
    signal(SIGALRM, &DispatchMsgToV8);
    while (g_inspector->waitingForDebugger) {
        usleep(g_inspector->DEBUGGER_WAIT_SLEEP_TIME);
    }
}

void WaitingForIde()
{
    LOGI("WaitingForIde");
    g_inspector->inspectorClient->SchedulePauseOnNextStatement(ConvertToStringView("Break on start"));
    g_inspector->inspectorClient->WaitFrontendMessageOnPause();
}

void Inspector::OnMessage(const std::string& message)
{
    if (message.empty()) {
        LOGE("message is empty");
        return;
    }
    LOGI("push to queue, msg = %s", message.c_str());
    ideMsgQueue.push(message);

    std::string startDebugging("Runtime.runIfWaitingForDebugger");
    if (message.find(startDebugging, 0) != std::string::npos) {
        waitingForDebugger = false;
        return;
    }

    if (inspectorClient->GetPausedFlag()) {
        pthread_kill(websocketServer->tid, SIGALRM);
        return;
    }
}

void Inspector::SendMessage(const std::string& message) const
{
    websocketServer->SendMessage(message);
}

void Inspector::InitializeInspector(
    const std::unique_ptr<v8::Platform>& platform, const v8::Local<v8::Context>& context)
{
    websocketServer = std::make_unique<WsServer>(std::bind(&Inspector::OnMessage, this, std::placeholders::_1));

    inspectorClient = std::make_unique<V8InspectorClient>();
    inspectorClient->InitializeClient(
        platform, context, std::bind(&Inspector::SendMessage, this, std::placeholders::_1));
    isDispatchingMsg = false;
}

void Inspector::StartAgent() const
{
    websocketServer->RunServer();
}

} // namespace V8Debugger
