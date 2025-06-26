/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/node_api_multi_thread.h"

#include "core/common/multi_thread_build_manager.h"
#include "base/error/error_code.h"

namespace OHOS::Ace::NG {
void SetIsThreadSafeNodeScope(ArkUI_Bool isThreadSafeNodeScope)
{
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(isThreadSafeNodeScope);
}

int32_t CheckNodeOnValidThread(ArkUINodeHandle node)
{
    UINode* currentNode = reinterpret_cast<UINode*>(node);
    return static_cast<int32_t>(MultiThreadBuildManager::CheckNodeOnValidThread(currentNode));
}

int32_t CheckOnUIThread()
{
    return MultiThreadBuildManager::CheckOnUIThread();
}

int32_t PostAsyncUITask(ArkUI_Int32 contextId,
    void* asyncUITaskData, void (*asyncUITask)(void* asyncUITaskData), void(*onFinish)(void* asyncUITaskData))
{
    auto asyncUITaskFunc = [asyncUITaskData, asyncUITask]() {
        if (asyncUITask == nullptr) {
            return;
        }
        asyncUITask(asyncUITaskData);
    };
    auto onFinishFunc = [asyncUITaskData, onFinish]() {
        if (onFinish == nullptr) {
            return;
        }
        onFinish(asyncUITaskData);
    };
    if (!MultiThreadBuildManager::GetInstance().PostAsyncUITask(
        contextId, std::move(asyncUITaskFunc), std::move(onFinishFunc))) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t PostUITask(ArkUI_Int32 contextId, void* taskData, void(*task)(void* taskData))
{
    auto taskFunc = [taskData, task]() {
        if (task == nullptr) {
            return;
        }
        task(taskData);
    };
    if (!MultiThreadBuildManager::GetInstance().PostUITask(contextId, std::move(taskFunc))) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t PostUITaskAndWait(ArkUI_Int32 contextId, void* taskData, void(*task)(void* taskData))
{
    auto taskFunc = [taskData, task]() {
        if (task == nullptr) {
            return;
        }
        task(taskData);
    };
    if (!MultiThreadBuildManager::GetInstance().PostUITaskAndWait(contextId, std::move(taskFunc))) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

const ArkUIMultiThreadManagerAPI* GetMultiThreadManagerAPI()
{
    static const ArkUIMultiThreadManagerAPI multiThreadImpl = {
        .setIsThreadSafeNodeScope = SetIsThreadSafeNodeScope,
        .checkNodeOnValidThread = CheckNodeOnValidThread,
        .checkOnUIThread = CheckOnUIThread,
        .postAsyncUITask = PostAsyncUITask,
        .postUITask = PostUITask,
        .postUITaskAndWait = PostUITaskAndWait,
    };
    return &multiThreadImpl;
}
} // namespace OHOS::Ace::NG