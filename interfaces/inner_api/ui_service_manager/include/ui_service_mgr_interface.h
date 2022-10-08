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

#ifndef OHOS_AAFWK_UI_SERVICE_MANAGER_INTERFACE_H
#define OHOS_AAFWK_UI_SERVICE_MANAGER_INTERFACE_H

#include <vector>

#include <ipc_types.h>
#include <iremote_broker.h>

#include "ui_service_interface.h"

#include "base/utils/macros.h"

namespace OHOS {
namespace Ace {
/**
 * @class IUIServiceMgr
 * IUIServiceMgr interface is used to access UIService manager services.
 */
class ACE_FORCE_EXPORT IUIServiceMgr : public OHOS::IRemoteBroker {
public:
    DECLARE_INTERFACE_DESCRIPTOR(u"ohos.ace.UIServiceMgr")

    IUIServiceMgr() = default;
    ~IUIServiceMgr() override = default;

    virtual int32_t RegisterCallBack(const AAFwk::Want& want, const sptr<IUIService>& uiService) = 0;

    virtual int32_t UnregisterCallBack(const AAFwk::Want& want) = 0;

    virtual int32_t Push(const AAFwk::Want& want, const std::string& name, const std::string& jsonPath,
        const std::string& data, const std::string& extraData) = 0;

    virtual int32_t Request(const AAFwk::Want& want, const std::string& name, const std::string& data) = 0;

    virtual int32_t ReturnRequest(const AAFwk::Want& want, const std::string& source,  const std::string& data,
        const std::string& extraData) = 0;

    enum {
        // ipc id 1-1000 for kit
        // ipc id for RegisterCallBack (1)
        REGISTER_CALLBACK = 1,
        // ipc id for UnregisterCallBack (2)
        UNREGISTER_CALLBACK,
        PUSH,
        REQUEST,
        RETURN_REQUEST,
    };
};
}  // namespace Ace
}  // namespace OHOS
#endif  // OHOS_AAFWK_UI_SERVICE_MANAGER_INTERFACE_H
