/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_FORM_SURFACE_CLIENT_H
#define OHOS_ACE_FORM_SURFACE_CLIENT_H

#include <mutex>

#include "form_surface_callback_interface.h"
#include "form_surface_stub.h"
#include "iremote_object.h"
#include "form_surface_interface.h"

#include "base/utils/macros.h"

namespace OHOS::Ace {
/**
 * @class UIServiceMgrClient
 * UIServiceMgrClient is used to access UIService manager services.
 */
class ACE_FORCE_EXPORT FormSurfaceServiceClient : public FormSurfaceServiceStub{
public:
    FormSurfaceServiceClient() = default;
     ~FormSurfaceServiceClient() override = default;
    static std::shared_ptr<FormSurfaceServiceClient> GetInstance();
    int32_t ProcessAddSurface(const AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo,
        const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode) override;
    void AddForm(std::shared_ptr<FormSurfaceCallbackInterface> formCallback, int64_t formId);

private:
    static std::mutex mutex_;
    mutable std::mutex callbackMutex_;
    static std::shared_ptr<FormSurfaceServiceClient> instance_;
    std::map<int64_t, std::set<std::shared_ptr<FormSurfaceCallbackInterface>>> formCallbackMap_;
};
} // namespace OHOS::Ace
#endif  // OHOS_ACE_FORM_SURFACE_CLIENT_H
