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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DELEGATE_IMPL_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DELEGATE_IMPL_H

#include <mutex>

#include "form_renderer_delegate_stub.h"

#include "base/utils/macros.h"

namespace OHOS {
namespace Ace {
/**
 * @class FormRendererDelegate
 * FormRendererDelegate interface is used to form renderer delegate.
 */
class ACE_EXPORT FormRendererDelegateImpl : public FormRendererDelegateStub {
public:
    FormRendererDelegateImpl() = default;
    ~FormRendererDelegateImpl() override = default;
    /**
     * @brief OnSurfaceCreate.
     * @param surfaceNode The surfaceNode.
     * @param formJsInfo The formJsInfo.
     * @param want The want.
     */
    int32_t OnSurfaceCreate(
        const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode,
        const OHOS::AppExecFwk::FormJsInfo& formJsInfo,
        const AAFwk::Want& want) override;
    /**
     * @brief OnActionEvent.
     * @param action The action.
     */
    int32_t OnActionEvent(const std::string& action) override;
    /**
     * @brief OnError.
     * @param param The param.
     */
    int32_t OnError(const std::string& param) override;

    void SetSurfaceCreateEventHandler(std::function<void(const std::shared_ptr<Rosen::RSSurfaceNode>&,
            const OHOS::AppExecFwk::FormJsInfo&, const AAFwk::Want&)>&& listener);
    void SetActionEventHandler(std::function<void(const std::string&)>&& listener);
    void SetErrorEventHandler(std::function<void(const std::string&)>&& listener);

private:
    std::function<void(
        const std::shared_ptr<Rosen::RSSurfaceNode>&, const OHOS::AppExecFwk::FormJsInfo&, const AAFwk::Want&)>
        surfaceCreateEventHandler_;
    std::function<void(const std::string&)> actionEventHandler_;
    std::function<void(const std::string&)> errorEventHandler_;
};
}  // namespace Ace
}  // namespace OHOS
#endif  // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DELEGATE_IMPL_H
