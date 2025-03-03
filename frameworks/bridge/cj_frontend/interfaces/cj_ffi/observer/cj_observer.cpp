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

#include "cj_observer.h"

#include <memory>
#include <string>

#include "observer.h"
#include "observer_listener.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/observer_handler.h"

namespace OHOS {
namespace Rosen {

ObserverProcess::ObserverProcess() {}

ObserverProcess& ObserverProcess::GetInstance()
{
    static ObserverProcess instance;
    return instance;
}

void ObserverProcess::ProcessScrollEventRegister(int64_t callbackId)
{
    if (!isScrollEventChangeFuncSetted_) {
        Ace::NG::UIObserverHandler::GetInstance().SetHandleScrollEventChangeFunc(
            &CJObserver::HandleScrollEventStateChange);
        isScrollEventChangeFuncSetted_ = true;
    }
    CJObserver::RegisterScrollEventCallback(callbackId);
}

void ObserverProcess::ProcessScrollEventUnRegister(int64_t callbackId)
{
    CJObserver::UnRegisterScrollEventCallback(callbackId);
}

void ObserverProcess::ProcessScrollEventRegisterWithOptions(const char* options, int64_t callbackId)
{
    if (!isScrollEventChangeFuncSetted_) {
        Ace::NG::UIObserverHandler::GetInstance().SetHandleScrollEventChangeFunc(
            &CJObserver::HandleScrollEventStateChange);
        isScrollEventChangeFuncSetted_ = true;
    }
    CJObserver::RegisterScrollEventCallback(options, callbackId);
}

void ObserverProcess::ProcessScrollEventUnRegisterWithOptions(const char* options, int64_t callbackId)
{
    CJObserver::UnRegisterScrollEventCallback(options, callbackId);
}

void ObserverProcess::ProcessTabContentUpdateRegister(int64_t callbackId)
{
    if (!isTabContentUpdateFuncSetted_) {
        Ace::NG::UIObserverHandler::GetInstance().SetHandleTabContentStateUpdateFunc(
            &CJObserver::HandleTabContentUpdateStateChange);
        isTabContentUpdateFuncSetted_ = true;
    }
    CJObserver::RegisterTabContentUpdateCallback(callbackId);
}

void ObserverProcess::ProcessTabContentUpdateUnRegister(int64_t callbackId)
{
    CJObserver::UnRegisterTabContentUpdateCallback(callbackId);
}

void ObserverProcess::ProcessTabContentUpdateRegisterWithOptions(const char* options, int64_t callbackId)
{
    if (!isTabContentUpdateFuncSetted_) {
        Ace::NG::UIObserverHandler::GetInstance().SetHandleTabContentStateUpdateFunc(
            &CJObserver::HandleTabContentUpdateStateChange);
        isTabContentUpdateFuncSetted_ = true;
    }
    CJObserver::RegisterTabContentUpdateCallback(options, callbackId);
}

void ObserverProcess::ProcessTabContentUpdateUnRegisterWithOptions(const char* options, int64_t callbackId)
{
    CJObserver::UnRegisterTabContentUpdateCallback(options, callbackId);
}

} // namespace Rosen
} // namespace OHOS