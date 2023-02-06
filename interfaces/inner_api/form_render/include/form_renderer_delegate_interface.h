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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DELEGATE_INTERFACE_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DELEGATE_INTERFACE_H

#include <ipc_types.h>
#include <iremote_broker.h>

#include "form_js_info.h"
#include "ui/rs_surface_node.h"
#include "want.h"

#include "base/utils/macros.h"

namespace OHOS {
namespace Ace {
/**
 * @class FormRendererDelegate
 * FormRendererDelegate interface is used to form renderer delegate.
 */
class ACE_EXPORT IFormRendererDelegate : public OHOS::IRemoteBroker {
public:
    DECLARE_INTERFACE_DESCRIPTOR(u"ohos.ace.FormRendererDelegate")

    IFormRendererDelegate() = default;
    ~IFormRendererDelegate() override = default;
    /**
     * @brief OnSurfaceCreate.
     * @param surfaceNode The surfaceNode.
     * @param formJsInfo The formJsInfo.
     * @param want The want.
     */
    virtual int32_t OnSurfaceCreate(
        const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode,
        const OHOS::AppExecFwk::FormJsInfo& formJsInfo,
        const AAFwk::Want& want) = 0;
    /**
     * @brief OnActionEvent.
     * @param action The action.
     */
    virtual int32_t OnActionEvent(const std::string& action) = 0;
    /**
     * @brief OnError.
     * @param action The action.
     */
    virtual int32_t OnError(const std::string& param) = 0;

    enum Message : uint32_t {
        ON_SURFACE_CREATE = 1,
        ON_ACTION_CREATE,
        ON_ERROR,
    };
};
}  // namespace Ace
}  // namespace OHOS
#endif  // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DELEGATE_INTERFACE_H
