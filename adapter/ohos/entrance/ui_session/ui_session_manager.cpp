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

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "adapter/ohos/entrance/ui_session/include/ui_service_hilog.h"
namespace OHOS::Ace {
std::mutex UiSessionManager::mutex_;

UiSessionManager& UiSessionManager::GetInstance()
{
    static UiSessionManager instance_;
    return instance_;
}

void UiSessionManager::ReportClickEvent(std::string data)
{
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->ReportClickEvent(data);
        } else {
            LOGW("report click event failed,process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManager::ReportSearchEvent(std::string data)
{
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->ReportSearchEvent(data);
        } else {
            LOGW("report search event failed,process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManager::ReportRouterChangeEvent(std::string data)
{
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->ReportRouterChangeEvent(data);
        } else {
            LOGW("report switch event failed,process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManager::ReportComponentChangeEvent(std::string data)
{
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->ReportComponentChangeEvent(data);
        } else {
            LOGW("report component event failed,process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManager::SaveReportStub(sptr<IRemoteObject> reportStub, int32_t processId)
{
    reportObjectMap_.emplace(processId, reportStub);
}

void UiSessionManager::SetClickEventRegistered(bool status)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (status) {
        clickEventRegisterProcesses_++;
    } else {
        clickEventRegisterProcesses_--;
    }
}

void UiSessionManager::SetSearchEventRegistered(bool status)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (status) {
        searchEventRegisterProcesses_++;
    } else {
        searchEventRegisterProcesses_--;
    }
}

void UiSessionManager::SetRouterChangeEventRegistered(bool status)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (status) {
        routerChangeEventRegisterProcesses_++;
    } else {
        routerChangeEventRegisterProcesses_--;
    }
}

void UiSessionManager::SetComponentChangeEventRegistered(bool status)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (status) {
        componentChangeEventRegisterProcesses_++;
    } else {
        componentChangeEventRegisterProcesses_--;
    }
}

bool UiSessionManager::GetClickEventRegistered()
{
    return clickEventRegisterProcesses_ > 0 ? true : false;
}

bool UiSessionManager::GetSearchEventRegistered()
{
    return searchEventRegisterProcesses_ > 0 ? true : false;
}

bool UiSessionManager::GetRouterChangeEventRegistered()
{
    return routerChangeEventRegisterProcesses_ > 0 ? true : false;
}

bool UiSessionManager::GetComponentChangeEventRegistered()
{
    return componentChangeEventRegisterProcesses_ > 0 ? true : false;
}
} // namespace OHOS::Ace
