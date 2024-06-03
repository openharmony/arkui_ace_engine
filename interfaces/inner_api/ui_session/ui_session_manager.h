/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_UI_SESSION_MANAGER_H
#define FOUNDATION_ACE_INTERFACE_UI_SESSION_MANAGER_H
#include <cstdint>
#include <iremote_object.h>

#include "ui_report_stub.h"

#include "base/utils/macros.h"
namespace OHOS::Ace {
class ACE_FORCE_EXPORT UiSessionManager {
public:
    /**
     * @description: Get ui_manager instance,this object process singleton
     * @return The return value is ui_manager singleton
     */
    static UiSessionManager& GetInstance();

    /**
     * @description: execute click callback when component click event occurs 
     */
    void ReportClickEvent();

    /**
     * @description: execute search callback when component search event occurs 
     */
    void ReportSearchEvent();

    /**
     * @description: execute switch callback when page switch to another page occurs 
     */
    void ReportRouterChangeEvent();

    /**
     * @description: execute click callback when page some component change occurs 
     */
    void ReportComponentChangeEvent();

    /**
     * @description: save report communication stub side 
     * @param reportStub report communication stub side
     */
    void SaveReportStub(sptr<IRemoteObject> reportStub);
    void SetClickEventRegistered(bool status);
    void SetSearchEventRegistered(bool status);
    void SetRouterChangeEventRegistered(bool status);
    void SetComponentChangeEventRegistered(bool status);
    bool GetClickEventRegistered();
    bool GetSearchEventRegistered();
    bool GetRouterChangeEventRegistered();
    bool GetComponentChangeEventRegistered();

private:
    sptr<IRemoteObject> reportObject_ = nullptr;
    bool isClickEventRegistered_ = false;
    bool isSearchEventRegistered_ = false;
    bool isRouterChangeEventRegistered_ = false;
    bool isComponentChangeEventRegistered_ = false;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_SESSION_MANAGER_H

