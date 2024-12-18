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
struct AccessibilityParentRectInfo;
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
    virtual int32_t OnSurfaceCreate(const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode,
        const OHOS::AppExecFwk::FormJsInfo& formJsInfo, const AAFwk::Want& want) = 0;
    /**
     * @brief OnSurfaceReuse.
     * @param surfaceId The surfaceNode ID.
     * @param formJsInfo The formJsInfo.
     * @param want The want.
     */
    virtual int32_t OnSurfaceReuse(
        uint64_t surfaceId, const OHOS::AppExecFwk::FormJsInfo& formJsInfo, const AAFwk::Want& want)
    {
        return ERR_OK;
    }
    /**
     * @brief OnSurfaceRelease.
     * @param surfaceId The surfaceNode ID.
     */
    virtual int32_t OnSurfaceRelease(uint64_t surfaceId)
    {
        return ERR_OK;
    }
    /**
     * @brief OnActionEvent.
     * @param action The action.
     */
    virtual int32_t OnActionEvent(const std::string& action) = 0;
    /**
     * @brief OnError.
     * @param code The code.
     * @param msg The msg.
     */
    virtual int32_t OnError(const std::string& code, const std::string& msg) = 0;
    /**
     * @brief OnSurfaceChange.
     * @param width
     * @param height
     */
    virtual int32_t OnSurfaceChange(float width, float height, float borderWidth = 0.0) = 0;
    /**
     * @brief OnSurfaceDetach.
     * @param surfaceId The surfaceNode ID.
     */
    virtual int32_t OnSurfaceDetach(uint64_t surfaceId) = 0;
    /**
     * @brief OnFormLinkInfoUpdate.
     * @param formLinkInfos
     */
    virtual int32_t OnFormLinkInfoUpdate(const std::vector<std::string>& formLinkInfos) = 0;

    /**
     * @brief OnGetRectRelativeToWindow.
     * @param rectF
     */
    virtual int32_t OnGetRectRelativeToWindow(AccessibilityParentRectInfo& parentRectInfo) = 0;

    enum Message : uint32_t {
        ON_SURFACE_CREATE = 1,
        ON_SURFACE_REUSE,
        ON_SURFACE_RELEASE,
        ON_ACTION_CREATE,
        ON_ERROR,
        ON_SURFACE_CHANGE,
        ON_FORM_LINK_INFO_UPDATE,
        ON_FORMSURFACE_DETACH,
        ON_GET_RECT_RELATIVE_TO_WINDOW,
    };
};
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DELEGATE_INTERFACE_H
