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

#include "form_renderer_delegate_stub.h"
#include "core/accessibility/accessibility_manager.h"

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
    int32_t OnSurfaceCreate(const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode,
        const OHOS::AppExecFwk::FormJsInfo& formJsInfo, const AAFwk::Want& want) override;
    /**
     * @brief OnActionEvent.
     * @param action The action.
     */
    int32_t OnActionEvent(const std::string& action) override;
    /**
     * @brief OnError.
     * @param code The code.
     * @param msg The msg.
     */
    int32_t OnError(const std::string& code, const std::string& msg) override;
    /**
     * @brief OnSurfaceChange.
     * @param width
     * @param height
     */
    int32_t OnSurfaceChange(float width, float height, float borderWidth = 0.0) override;
    /**
     * @brief OnSurfaceDetach.
     * @param surfaceId The surfaceNode ID.
     */
    int32_t OnSurfaceDetach(uint64_t surfaceId) override;

    int32_t OnFormLinkInfoUpdate(const std::vector<std::string>& formLinkInfos) override;

    int32_t OnGetRectRelativeToWindow(AccessibilityParentRectInfo& parentRectInfo) override;

    int32_t OnCheckManagerDelegate(bool &checkFlag) override;

    void SetSurfaceCreateEventHandler(std::function<void(const std::shared_ptr<Rosen::RSSurfaceNode>&,
            const OHOS::AppExecFwk::FormJsInfo&, const AAFwk::Want&)>&& listener);
    void SetActionEventHandler(std::function<void(const std::string&)>&& listener);
    void SetErrorEventHandler(std::function<void(const std::string&, const std::string&)>&& listener);
    void SetSurfaceChangeEventHandler(std::function<void(float width, float height, float borderWidth)>&& listener);
    void SetSurfaceDetachEventHandler(std::function<void()>&& listener);
    void SetFormLinkInfoUpdateHandler(std::function<void(const std::vector<std::string>&)>&& listener);
    void SetGetRectRelativeToWindowHandler(std::function<void(AccessibilityParentRectInfo& parentRectInfo)>&& listener);
    void SetCheckManagerDelegate(std::function<void(bool&)>&& listener);
private:
    std::function<void(
        const std::shared_ptr<Rosen::RSSurfaceNode>&, const OHOS::AppExecFwk::FormJsInfo&, const AAFwk::Want&)>
        surfaceCreateEventHandler_;
    std::function<void(const std::string&)> actionEventHandler_;
    std::function<void(const std::string&, const std::string&)> errorEventHandler_;
    std::function<void(float width, float height, float borderWidth)> surfaceChangeEventHandler_;
    std::function<void()> surfaceDetachEventHandler_;
    std::function<void(const std::vector<std::string>&)> formLinkInfoUpdateHandler_;
    std::function<void(AccessibilityParentRectInfo& parentRectInfo)> getRectRelativeToWindowHandler_;
    std::function<void(bool&)> checkManagerDelegate_;
};
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DELEGATE_IMPL_H
