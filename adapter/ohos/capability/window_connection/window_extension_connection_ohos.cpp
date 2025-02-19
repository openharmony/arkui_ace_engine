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

#include "render_service_client/core/ui/rs_surface_node.h"

#include "core/common/ace_engine.h"
#include "frameworks/core/components_v2/ability_component/render_ability_component.h"

#ifdef OS_ACCOUNT_EXISTS
#include "os_account_manager.h"
#endif

namespace OHOS::Ace {

class ConnectionCallback : public Rosen::IWindowExtensionCallback {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ConnectionCallback);
    ConnectionCallback(WeakPtr<RenderNode> node, int32_t instanceId) : node_(std::move(node)), instanceId_(instanceId)
    {}
    ~ConnectionCallback() override = default;
    void OnWindowReady(const std::shared_ptr<Rosen::RSSurfaceNode>& rsSurfaceNode) override
    {
        LOGI("OnWindowReady and ready to connect extension");
        auto nodeStrong = node_.Upgrade();
        if (!nodeStrong || !rsSurfaceNode) {
            LOGW("cannot replace sureface node because the render node or surfacenode is empty");
            return;
        }
        rsSurfaceNode->CreateNodeInRenderThread();
        auto rect = nodeStrong->GetPaintRect();
        auto size = rect.GetSize();
        rsSurfaceNode->SetBounds(0, 0, static_cast<float>(size.Width()), static_cast<float>(size.Height()));
        if (!originNode_) {
            originNode_ = nodeStrong->GetRSNode();
        }
        nodeStrong->SyncRSNode(std::static_pointer_cast<RSNode>(rsSurfaceNode));
        nodeStrong->MarkNeedLayout();
        auto task = [weak = node_, instanceId = instanceId_]() {
            ContainerScope scope(instanceId);
            auto node = weak.Upgrade();
            CHECK_NULL_VOID(node);
            auto ability = AceType::DynamicCast<V2::RenderAbilityComponent>(node);
            if (ability) {
                ability->FireConnect();
            }
        };
        PostTaskToUI(std::move(task), "ArkUIWindowExtensionConnect");
    }

    void OnExtensionDisconnected() override
    {
        LOGI("window extension disconnect");
        auto ability = AceType::DynamicCast<V2::RenderAbilityComponent>(node_.Upgrade());
        CHECK_NULL_VOID(ability);
        if (originNode_) {
            ability->SyncRSNode(originNode_);
        }

        auto task = [weak = node_, instanceId = instanceId_]() {
            ContainerScope scope(instanceId);
            auto node = weak.Upgrade();
            CHECK_NULL_VOID(node);
            auto ability = AceType::DynamicCast<V2::RenderAbilityComponent>(node);
            if (ability) {
                ability->FireDisconnect();
            }
        };
        PostTaskToUI(std::move(task), "ArkUIWindowExtensionDisconnect");
    }

    void OnKeyEvent(const std::shared_ptr<MMI::KeyEvent>& event) override {}
    void OnPointerEvent(const std::shared_ptr<MMI::PointerEvent>& event) override {}
    void OnBackPress() override {}

private:
    void PostTaskToUI(const std::function<void()>&& task, const std::string& name) const
    {
        CHECK_NULL_VOID(task);
        auto container = AceEngine::Get().GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto context = container->GetPipelineContext();
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(task, TaskExecutor::TaskType::UI, name);
    }

    std::shared_ptr<RSNode> originNode_;
    WeakPtr<RenderNode> node_;
    int32_t instanceId_ = -1;
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
    element.SetAbilityName(json->GetValue("abilityName")->GetString());
    element.SetBundleName(json->GetValue("bundleName")->GetString());
}

void WindowExtensionConnectionAdapterOhos::ConnectExtension(
    const std::string& want, const Rect& rect, WeakPtr<RenderNode> node, int32_t windowId)
{
    LOGI("ConnectExtension rect: %{public}s", rect.ToString().c_str());
#if defined(ENABLE_ROSEN_BACKEND) && defined(OS_ACCOUNT_EXISTS)
    if (!windowExtension_) {
        windowExtension_ = std::make_unique<Rosen::WindowExtensionConnection>();
    }
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

    int32_t instanceId = -1;
    auto container = Container::Current();
    if (container) {
        instanceId = container->GetInstanceId();
    }
    sptr<Rosen::IWindowExtensionCallback> callback = new ConnectionCallback(node, instanceId);
    windowExtension_->ConnectExtension(element, rosenRect, userIds.front(), windowId, callback);
#endif
}

void WindowExtensionConnectionAdapterOhos::RemoveExtension()
{
    if (windowExtension_) {
        LOGI("remove extension");
        windowExtension_->DisconnectExtension();
    }
}

void WindowExtensionConnectionAdapterOhos::Show()
{
    LOGI("show WindowExtensionConnectionAdapterOhos");
    if (windowExtension_) {
        windowExtension_->Show();
    }
}

void WindowExtensionConnectionAdapterOhos::Hide()
{
    LOGI("hide WindowExtensionConnectionAdapterOhos");
    if (windowExtension_) {
        windowExtension_->Hide();
    }
}

void WindowExtensionConnectionAdapterOhos::UpdateRect(const Rect& rect)
{
    if (windowExtension_) {
        Rosen::Rect rosenRect;
        RectConverter(rect, rosenRect);
        LOGI("UpdateRect rect: %{public}s", rect.ToString().c_str());
        windowExtension_->SetBounds(rosenRect);
    }
}
} // namespace OHOS::Ace
