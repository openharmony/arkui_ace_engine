/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <ability_connect_callback_stub.h>
#include <ability_manager_client.h>
#include <element_name.h>
#include <hitrace_meter.h>
#include <iremote_object.h>

#include "window_extension_client_stub_impl.h"
#include "window_extension_connection.h"
#include "window_extension_proxy.h"
#include "window_manager_hilog.h"
#include "wm_common.h"
#include "wm_common_inner.h"

namespace OHOS {
namespace Rosen {

class WindowExtensionConnection::Impl : public AAFwk::AbilityConnectionStub {
public:
    Impl() = default;
    ~Impl() = default;
    void OnAbilityConnectDone(
        const AppExecFwk::ElementName& element, const sptr<IRemoteObject>& remoteObject, int resultCode) override;
    void OnAbilityDisconnectDone(const AppExecFwk::ElementName& element, int resultCode) override;
    int ConnectExtension(const AppExecFwk::ElementName& element, const Rect& rect, uint32_t uid, uint32_t windowId,
        const sptr<IWindowExtensionCallback>& callback);
    void Show() const;
    void Hide() const;
    void SetBounds(const Rect& rect) const;
    void RequestFocus() const;
    void DisconnectExtension();

private:
    class WindowExtensionClientRecipient final : public IRemoteObject::DeathRecipient {
    public:
        explicit WindowExtensionClientRecipient(sptr<IWindowExtensionCallback> callback);
        ~WindowExtensionClientRecipient() = default;
        void OnRemoteDied(const wptr<IRemoteObject>& remote);

    private:
        sptr<IWindowExtensionCallback> callback_;
    };

    sptr<IWindowExtensionCallback> componentCallback_;
    sptr<IWindowExtension> proxy_;
    sptr<WindowExtensionClientRecipient> deathRecipient_;
};

WindowExtensionConnection::WindowExtensionConnection() : pImpl_(new Impl()) {}

WindowExtensionConnection::~WindowExtensionConnection()
{
    DisconnectExtension();
}

void WindowExtensionConnection::Impl::OnAbilityConnectDone(
    const AppExecFwk::ElementName& element, const sptr<IRemoteObject>& remoteObject, int resultCode)
{}

WindowExtensionConnection::Impl::WindowExtensionClientRecipient::WindowExtensionClientRecipient(
    sptr<IWindowExtensionCallback> callback)
    : callback_(callback)
{}

void WindowExtensionConnection::Impl::WindowExtensionClientRecipient::OnRemoteDied(const wptr<IRemoteObject>& wptrDeath)
{}

int WindowExtensionConnection::Impl::ConnectExtension(const AppExecFwk::ElementName& element, const Rect& rect,
    uint32_t uid, uint32_t windowId, const sptr<IWindowExtensionCallback>& callback)
{
    componentCallback_ = callback;
    std::shared_ptr<Rosen::RSSurfaceNode> rsSurfaceNode = nullptr;
    componentCallback_->OnWindowReady(rsSurfaceNode);
    return -1;
}

void WindowExtensionConnection::Impl::Show() const {}

void WindowExtensionConnection::Impl::Hide() const {}

void WindowExtensionConnection::Impl::RequestFocus() const {}

void WindowExtensionConnection::Impl::SetBounds(const Rect& rect) const {}

void WindowExtensionConnection::Impl::DisconnectExtension()
{
    componentCallback_->OnExtensionDisconnected();
}

int WindowExtensionConnection::ConnectExtension(const AppExecFwk::ElementName& element, const Rect& rect, uint32_t uid,
    uint32_t windowId, const sptr<IWindowExtensionCallback>& callback) const
{
    return pImpl_->ConnectExtension(element, rect, uid, windowId, callback);
}

void WindowExtensionConnection::Show() const
{
    pImpl_->Show();
}

void WindowExtensionConnection::Hide() const
{
    pImpl_->Hide();
}

void WindowExtensionConnection::RequestFocus() const
{
    pImpl_->RequestFocus();
}

void WindowExtensionConnection::SetBounds(const Rect& rect) const
{
    pImpl_->SetBounds(rect);
}

void WindowExtensionConnection::DisconnectExtension() const
{
    pImpl_->DisconnectExtension();
}
} // namespace Rosen
} // namespace OHOS