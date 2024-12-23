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
#include "form_renderer_delegate_impl.h"

#include "form_renderer_hilog.h"

namespace OHOS {
namespace Ace {
int32_t FormRendererDelegateImpl::OnSurfaceCreate(const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode,
    const OHOS::AppExecFwk::FormJsInfo& formJsInfo, const AAFwk::Want& want)
{
    HILOG_DEBUG("%{public}s called.", __func__);
    if (!surfaceNode) {
        HILOG_ERROR("surface is invalid");
        return ERR_NULL_OBJECT;
    }
    int64_t formId = formJsInfo.formId;
    if (formId < 0) {
        HILOG_ERROR("%{public}s error, the passed form id can't be negative.", __func__);
        return ERR_INVALID_DATA;
    }

    if (!surfaceCreateEventHandler_) {
        HILOG_ERROR("surfaceCreateEventHandler_ is null");
        return ERR_INVALID_DATA;
    }
    surfaceCreateEventHandler_(surfaceNode, formJsInfo, want);
    return ERR_OK;
}

int32_t FormRendererDelegateImpl::OnActionEvent(const std::string& action)
{
    HILOG_INFO("OnActionEvent %{public}zu", action.length());
    if (!actionEventHandler_) {
        HILOG_ERROR("actionEventHandler_ is null,  %{public}zu", action.length());
        return ERR_INVALID_DATA;
    }

    actionEventHandler_(action);
    return ERR_OK;
}

int32_t FormRendererDelegateImpl::OnError(const std::string& code, const std::string& msg)
{
    HILOG_INFO("OnError code: %{public}s, msg: %{public}s", code.c_str(), msg.c_str());
    if (!errorEventHandler_) {
        HILOG_ERROR("errorEventHandler_ is null");
        return ERR_INVALID_DATA;
    }

    errorEventHandler_(code, msg);
    return ERR_OK;
}

int32_t FormRendererDelegateImpl::OnSurfaceChange(float width, float height, float borderWidth)
{
    HILOG_DEBUG("%{public}s called.", __func__);
    if (!surfaceChangeEventHandler_) {
        HILOG_ERROR("surfaceChangeEventHandler_ is null");
        return ERR_INVALID_DATA;
    }
    surfaceChangeEventHandler_(width, height, borderWidth);
    return ERR_OK;
}

int32_t FormRendererDelegateImpl::OnSurfaceDetach(uint64_t surfaceId)
{
    HILOG_DEBUG("%{public}s called.", __func__);
    if (!surfaceDetachEventHandler_) {
        HILOG_ERROR("surfaceDetachEventHandler_ is null");
        return ERR_INVALID_DATA;
    }
    surfaceDetachEventHandler_();
    return ERR_OK;
}

int32_t FormRendererDelegateImpl::OnFormLinkInfoUpdate(const std::vector<std::string>& formLinkInfos)
{
    HILOG_DEBUG("%{public}s called.", __func__);
    if (!formLinkInfoUpdateHandler_) {
        HILOG_ERROR("formLinkInfoUpdateHandler_ is null");
        return ERR_INVALID_DATA;
    }
    formLinkInfoUpdateHandler_(formLinkInfos);
    return ERR_OK;
}

int32_t FormRendererDelegateImpl::OnGetRectRelativeToWindow(AccessibilityParentRectInfo& parentRectInfo)
{
    HILOG_DEBUG("%{public}s called.", __func__);
    if (!getRectRelativeToWindowHandler_) {
        HILOG_ERROR("getRectRelativeToWindowHandler_ is null");
        return ERR_INVALID_DATA;
    }
    getRectRelativeToWindowHandler_(parentRectInfo);
    return ERR_OK;
}

int32_t FormRendererDelegateImpl::OnCheckManagerDelegate(bool &checkFlag)
{
    if (!checkManagerDelegate_) {
        HILOG_ERROR("checkManagerDelegate_ is null");
        return ERR_INVALID_DATA;
    }
    checkManagerDelegate_(checkFlag);
    return ERR_OK;
}

void FormRendererDelegateImpl::SetSurfaceCreateEventHandler(
    std::function<void(const std::shared_ptr<Rosen::RSSurfaceNode>&, const OHOS::AppExecFwk::FormJsInfo&,
        const AAFwk::Want&)>&& listener)
{
    surfaceCreateEventHandler_ = std::move(listener);
}

void FormRendererDelegateImpl::SetActionEventHandler(std::function<void(const std::string&)>&& listener)
{
    HILOG_INFO("EventHandle - SetActionEventHandler");
    actionEventHandler_ = std::move(listener);
}

void FormRendererDelegateImpl::SetErrorEventHandler(
    std::function<void(const std::string&, const std::string&)>&& listener)
{
    errorEventHandler_ = std::move(listener);
}

void FormRendererDelegateImpl::SetSurfaceChangeEventHandler(
    std::function<void(float width, float height, float borderWidth)>&& listener)
{
    surfaceChangeEventHandler_ = std::move(listener);
}

void FormRendererDelegateImpl::SetSurfaceDetachEventHandler(std::function<void()>&& listener)
{
    surfaceDetachEventHandler_ = std::move(listener);
}

void FormRendererDelegateImpl::SetFormLinkInfoUpdateHandler(
    std::function<void(const std::vector<std::string>&)>&& listener)
{
    formLinkInfoUpdateHandler_ = std::move(listener);
}

void FormRendererDelegateImpl::SetGetRectRelativeToWindowHandler(
    std::function<void(AccessibilityParentRectInfo& parentRectInfo)>&& listener)
{
    getRectRelativeToWindowHandler_ = std::move(listener);
}

void FormRendererDelegateImpl::SetCheckManagerDelegate(std::function<void(bool&)>&& listener)
{
    checkManagerDelegate_ = std::move(listener);
}
} // namespace Ace
} // namespace OHOS
