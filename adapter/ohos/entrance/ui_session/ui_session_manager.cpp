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

UiSessionManager& UiSessionManager::GetInstance()
{
    static UiSessionManager instance_;
    return instance_;
}

void UiSessionManager::ReportClickEvent()
{
    auto reportService = iface_cast<ReportService>(reportObject_);
    if (reportService != nullptr) {
        reportService->ReportClickEvent();
    } else {
        LOGW("report click event failed");
    }
}

void UiSessionManager::ReportSearchEvent()
{
    auto reportService = iface_cast<ReportService>(reportObject_);
    if (reportService != nullptr) {
        reportService->ReportClickEvent();
    } else {
        LOGW("report search event failed");
    }
}

void UiSessionManager::ReportRouterChangeEvent()
{
    auto reportService = iface_cast<ReportService>(reportObject_);
    if (reportService != nullptr) {
        reportService->ReportClickEvent();
    } else {
        LOGW("report switch event failed");
    }
}

void UiSessionManager::ReportComponentChangeEvent()
{
    auto reportService = iface_cast<ReportService>(reportObject_);
    if (reportService != nullptr) {
        reportService->ReportClickEvent();
    } else {
        LOGW("report component event failed");
    }
}

void UiSessionManager::SaveReportStub(sptr<IRemoteObject> reportStub)
{
    reportObject_ = reportStub;
}

void UiSessionManager::SetClickEventRegistered(bool status)
{
    isClickEventRegistered_ = status;
}

void UiSessionManager::SetSearchEventRegistered(bool status)
{
    isSearchEventRegistered_ = status;
}

void UiSessionManager::SetRouterChangeEventRegistered(bool status)
{
    isRouterChangeEventRegistered_ = status;
}

void UiSessionManager::SetComponentChangeEventRegistered(bool status)
{
    isComponentChangeEventRegistered_ = status;
}

bool UiSessionManager::GetClickEventRegistered()
{
    return isClickEventRegistered_;
}

bool UiSessionManager::GetSearchEventRegistered()
{
    return isSearchEventRegistered_;
}

bool UiSessionManager::GetRouterChangeEventRegistered()
{
    return isRouterChangeEventRegistered_;
}

bool UiSessionManager::GetComponentChangeEventRegistered()
{
    return isComponentChangeEventRegistered_;
}
} // namespace OHOS::Ace
