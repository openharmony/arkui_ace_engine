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
#ifndef OHOS_ACE_FORM_SURFACE_INTERFACE_H
#define OHOS_ACE_FORM_SURFACE_INTERFACE_H

#include <iremote_broker.h>
#include "want.h"

#include "base/utils/macros.h"
#include "form_js_info.h"
#include "ui/rs_surface_node.h"
namespace OHOS {
namespace Ace {
class ACE_FORCE_EXPORT IFormSurfaceService : public OHOS::IRemoteBroker {
public:
    DECLARE_INTERFACE_DESCRIPTOR(u"ohos.ace.FormSurfaceService");

    IFormSurfaceService() = default;
    ~IFormSurfaceService() override = default;

    /**
     * @brief Called back to ProcessAddSurface
     *
     */
    virtual int32_t ProcessAddSurface(const AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo,
        const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode) = 0;

    enum class FormSurfaceServiceMessage {
        PROCESS_ADD_SURFACE = 0,
    };
};
}  // namespace Ace
}  // namespace OHOS
#endif  // OHOS_ACE_FORM_SURFACE_INTERFACE_H
