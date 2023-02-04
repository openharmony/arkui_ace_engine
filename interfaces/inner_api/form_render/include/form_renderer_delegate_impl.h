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

#include "form_surface_callback_interface.h"
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
     * @brief RegisterSurfaceCreateCallback.
     * @param formCallback The formCallback.
     * @param formId The formId.
     */
    void RegisterSurfaceCreateCallback(std::shared_ptr<FormSurfaceCallbackInterface> formCallback, int64_t formId);

private:
    mutable std::mutex callbackMutex_;
    std::map<int64_t, std::set<std::shared_ptr<FormSurfaceCallbackInterface>>> formCallbackMap_;
};
}  // namespace Ace
}  // namespace OHOS
#endif  // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DELEGATE_IMPL_H
