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
#include "window_extension_connection_ohos.h"

#include <memory>

#include "common/rs_color.h"
#include "element_name.h"
#include "render_service_client/core/ui/rs_surface_node.h"

#include "base/memory/ace_type.h"
#include "frameworks/base/json/json_util.h"
#include "frameworks/core/components_v2/ability_component/render_ability_component.h"

#ifdef OS_ACCOUNT_EXISTS
#include "os_account_manager.h"
#endif

namespace OHOS::Ace {
class ConnectionCallback : public Rosen::IWindowExtensionCallback {
public:
    explicit ConnectionCallback(WeakPtr<RenderNode> node) : node_(std::move(node)) {}
    ~ConnectionCallback() override = default;
    void OnWindowReady(const std::shared_ptr<Rosen::RSSurfaceNode>& rsSurfaceNode) override
    {
        LOGI("OnWindowReady and ready to connect extension");
        auto nodeStrong = node_.Upgrade();
        if (!nodeStrong || !rsSurfaceNode) {
            LOGI("cannot replace sureface node because the render node or surfacenode is empty");
            return;
        }
        rsSurfaceNode->CreateNodeInRenderThread();
        auto rect = nodeStrong->GetPaintRect();
        auto offset = rect.GetOffset();
        auto size = rect.GetSize();
        rsSurfaceNode->SetBounds(static_cast<float>(offset.GetX()), static_cast<float>(offset.GetY()),
            static_cast<float>(size.Width()), static_cast<float>(size.Height()));
        rsSurfaceNode->SetBackgroundColor(Color::WHITE.GetValue());
        nodeStrong->SyncRSNode(std::static_pointer_cast<RSNode>(rsSurfaceNode));
        nodeStrong->MarkNeedLayout();
        auto ability = AceType::DynamicCast<V2::RenderAbilityComponent>(nodeStrong);
        if (ability) {
            ability->FireConnect();
        }
    }

    void OnExtensionDisconnected() override
    {
        auto ability = AceType::DynamicCast<V2::RenderAbilityComponent>(node_.Upgrade());
        if (ability) {
            ability->FireDisconnect();
        }
    }

    void OnKeyEvent(const std::shared_ptr<MMI::KeyEvent>& event) override {}
    void OnPointerEvent(const std::shared_ptr<MMI::PointerEvent>& event) override {}
    void OnBackPress() override {}

private:
    WeakPtr<RenderNode> node_;
};

void RectConverter(const Rect& rect, Rosen::Rect& rosenRect)
{
    rosenRect.posX_ = static_cast<int>(rect.GetOffset().GetX());
    rosenRect.posY_ = static_cast<int>(rect.GetOffset().GetY());
    rosenRect.width_ = static_cast<uint32_t>(rect.GetSize().Width());
    rosenRect.height_ = static_cast<uint32_t>(rect.GetSize().Height());
}

void WantConverter(const std::string& want, AppExecFwk::ElementName& element)
{
    auto json = JsonUtil::ParseJsonString(want);
    element.SetAbilityName(json->GetValue("ability")->GetString());
    element.SetBundleName(json->GetValue("bundle")->GetString());
}

void WindowExtensionConnectionAdapterOhos::ConnectExtension(
    const std::string& want, const Rect& rect, WeakPtr<RenderNode> node)
{
#if defined(ENABLE_ROSEN_BACKEND) && defined(OS_ACCOUNT_EXISTS)
    LOGI("connect to windows extension begin");
    windowExtension_ = std::make_unique<Rosen::WindowExtensionConnection>();
    std::vector<int32_t> userIds;
    ErrCode code = AccountSA::OsAccountManager::QueryActiveOsAccountIds(userIds);
    if (code != ERR_OK) {
        LOGE("fail to queryAccountId, so cannot connect extension");
        return;
    }
    Rosen::Rect rosenRect;
    RectConverter(rect, rosenRect);
    AppExecFwk::ElementName element;
    WantConverter(want, element);
    sptr<Rosen::IWindowExtensionCallback> callback = new ConnectionCallback(node);
    windowExtension_->ConnectExtension(element, rosenRect, userIds.front(), callback);
#else
    LOGI("unrosen engine doesn't support ability component");
#endif
}

void WindowExtensionConnectionAdapterOhos::RemoveExtension()
{
    if (windowExtension_) {
        LOGI("remove extension");
        windowExtension_->DisconnectExtension();
    } else {
        LOGI("ability doesn't connect to window extension. remove extension fail");
    }
}

void WindowExtensionConnectionAdapterOhos::Show()
{
    LOGI("show WindowExtensionConnectionAdapterOhos");
    if (windowExtension_) {
        windowExtension_->Show();
        LOGI("no implement for remove");
    } else {
        LOGI("ability doesn't connect to window extension. show extension fail");
    }
}

void WindowExtensionConnectionAdapterOhos::Hide()
{
    LOGI("hide WindowExtensionConnectionAdapterOhos");
    if (windowExtension_) {
        windowExtension_->Hide();
        LOGI("no implement for remove");
    } else {
        LOGI("ability doesn't connect to window extension. show extension fail");
    }
}

void WindowExtensionConnectionAdapterOhos::UpdateRect(const Rect& rect)
{
    if (windowExtension_) {
        Rosen::Rect rosenRect;
        RectConverter(rect, rosenRect);
        windowExtension_->SetBounds(rosenRect);
    } else {
        LOGI("ability doesn't connect to window extension.cannot update rect region ");
    }
}
} // namespace OHOS::Ace
