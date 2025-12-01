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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_INTERFACES_INNER_API_UI_SERVICE_MANAGER_UI_SERVICE_MGR_CLIENT_IDL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_INTERFACES_INNER_API_UI_SERVICE_MANAGER_UI_SERVICE_MGR_CLIENT_IDL_H

#include <mutex>

#include "dialog_callback.h"
#include "iu_i_service_new.h"
#include "iu_i_service_mgr_new.h"
#include "iremote_object.h"
#include "ui_service_mgr_errors.h"
#include "wm_common.h"

#include "base/utils/macros.h"

namespace OHOS::Ace {
/**
 * @class UIServiceMgrClientIdl
 * UIServiceMgrClientIdl is used to access UIService manager services.
 */
class ACE_FORCE_EXPORT UIServiceMgrClientIdl {
public:
    UIServiceMgrClientIdl();
    virtual ~UIServiceMgrClientIdl();
    static std::shared_ptr<UIServiceMgrClientIdl> GetInstance();

    ErrCode RegisterCallBack(const AAFwk::Want& want, const sptr<IUIServiceNew>& uiService);

    ErrCode UnregisterCallBack(const AAFwk::Want& want);

    ErrCode Push(const AAFwk::Want& want,
        const std::string& name, const std::string& jsonPath, const std::string& data, const std::string& extraData);

    ErrCode Request(const AAFwk::Want& want, const std::string& name, const std::string& data);

    ErrCode ReturnRequest(
        const AAFwk::Want& want, const std::string& source,  const std::string& data,  const std::string& extraData);

    ErrCode ShowDialog(const std::string& name, const std::string& params, OHOS::Rosen::WindowType windowType,
        int32_t x, int32_t y, int32_t width, int32_t height, DialogCallback callback, int32_t* id = nullptr);

    ErrCode CancelDialog(int32_t id);

    ErrCode UpdateDialog(int32_t id, const std::string& data);

private:
    /**
     * Connect UIService manager service.
     *
     * @return Returns ERR_OK on success, others on failure.
     */
    ErrCode Connect();

    static std::mutex mutex_;
    sptr<IRemoteObject> remoteObject_;
};
} // namespace OHOS::Ace
#endif  // FOUNDATION_ARKUI_ACE_ENGINE_INTERFACES_INNER_API_UI_SERVICE_MANAGER_UI_SERVICE_MGR_CLIENT_IDL_H
