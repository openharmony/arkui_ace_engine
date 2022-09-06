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

#include <functional>
#include <memory>

#include "common/rs_color.h"
#include "element_name.h"
#include "render_service_client/core/ui/rs_surface_node.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/ability_component/ability_component_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "frameworks/base/json/json_util.h"
#include "frameworks/core/components_v2/ability_component/render_ability_component.h"

#ifdef OS_ACCOUNT_EXISTS
#include "os_account_manager.h"
#endif

namespace OHOS::Ace {

class ConnectionCallback : public Rosen::IWindowExtensionCallback {
public:
    ConnectionCallback(WeakPtr<RenderNode> node, int32_t instanceId) : node_(std::move(node)), instanceId_(instanceId)
    {}
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
        auto size = rect.GetSize();
        rsSurfaceNode->SetBounds(0, 0, static_cast<float>(size.Width()), static_cast<float>(size.Height()));
        rsSurfaceNode->SetBackgroundColor(Color::WHITE.GetValue());
        if (!originNode_) {
            originNode_ = nodeStrong->GetRSNode();
        }
        nodeStrong->SyncRSNode(std::static_pointer_cast<RSNode>(rsSurfaceNode));
        nodeStrong->MarkNeedLayout();
        auto task = [weak = node_, instanceId = instanceId_]() {
            ContainerScope scope(instanceId);
            auto node = weak.Upgrade();
            if (!node) {
                return;
            }
            auto ability = AceType::DynamicCast<V2::RenderAbilityComponent>(node);
            if (ability) {
                ability->FireConnect();
            }
        };
        PostTaskToUI(std::move(task));
    }

    void OnExtensionDisconnected() override
    {
        LOGI("window extension disconnect");
        auto ability = AceType::DynamicCast<V2::RenderAbilityComponent>(node_.Upgrade());
        if (!ability) {
            return;
        }
        if (originNode_) {
            ability->SyncRSNode(originNode_);
        }

        auto task = [weak = node_, instanceId = instanceId_]() {
            ContainerScope scope(instanceId);
            auto node = weak.Upgrade();
            if (!node) {
                return;
            }
            auto ability = AceType::DynamicCast<V2::RenderAbilityComponent>(node);
            if (ability) {
                ability->FireDisconnect();
            }
        };
        PostTaskToUI(std::move(task));
    }

    void OnKeyEvent(const std::shared_ptr<MMI::KeyEvent>& event) override {}
    void OnPointerEvent(const std::shared_ptr<MMI::PointerEvent>& event) override {}
    void OnBackPress() override {}

private:
    void PostTaskToUI(const std::function<void()>&& task) const
    {
        if (!task) {
            LOGE("task is empty");
            return;
        }
        auto container = AceEngine::Get().GetContainer(instanceId_);
        if (!container) {
            LOGE("container is null");
            return;
        }
        auto context = container->GetPipelineContext();
        if (!context) {
            LOGE("context is null");
            return;
        }
        auto taskExecutor = context->GetTaskExecutor();
        if (!taskExecutor) {
            LOGE("task executor is null");
            return;
        }
        taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
    }

    std::shared_ptr<RSNode> originNode_;
    WeakPtr<RenderNode> node_;
    int32_t instanceId_ = -1;
};

class NGConnectionCallback : public Rosen::IWindowExtensionCallback {
public:
    NGConnectionCallback(NGConnectionCallback const&) = delete;
    NGConnectionCallback& operator=(NGConnectionCallback const&) = delete;
    NGConnectionCallback(NGConnectionCallback&&) = delete;
    NGConnectionCallback& operator=(NGConnectionCallback&&) = delete;
    NGConnectionCallback(const RefPtr<NG::FrameNode>& originNode, int32_t instanceId)
        : originNode_(originNode), instanceId_(instanceId)
    {}

    ~NGConnectionCallback() override = default;
    void OnWindowReady(const std::shared_ptr<Rosen::RSSurfaceNode>& rsSurfaceNode) override
    {
        if (!rsSurfaceNode || !originNode_) {
            LOGI("cannot replace sureface node because the render node or surfacenode is empty");
            return;
        }
        auto context = originNode_->GetRenderContext();
        if (!context) {
            LOGI("context is empty");
            return;
        }
        rsOriginNode_ = std::static_pointer_cast<Rosen::RSSurfaceNode>(
            AceType::DynamicCast<NG::RosenRenderContext>(context)->GetRSNode());
        auto task = [weak = AceType::WeakClaim(AceType::RawPtr(originNode_)), rsNode = rsSurfaceNode,
                        instanceId = instanceId_]() {
            ContainerScope scope(instanceId);
            auto node = weak.Upgrade();
            if (!node) {
                LOGI("node is empty");
                return;
            }
            UpdateFrameNodeTree(node, rsNode);
            auto pattern = AceType::DynamicCast<NG::AbilityComponentPattern>(node->GetPattern());
            if (pattern) {
                pattern->FireConnect();
            }
        };
        PostTaskToUI(std::move(task));
    }

    void OnExtensionDisconnected() override
    {
        LOGI("window extension disconnect");
        auto task = [weak = AceType::WeakClaim(AceType::RawPtr(originNode_)), rsNode = rsOriginNode_,
                        instanceId = instanceId_]() {
            ContainerScope scope(instanceId);
            auto node = weak.Upgrade();
            if (!node) {
                return;
            }
            UpdateFrameNodeTree(node, rsNode);
            auto pattern = AceType::DynamicCast<NG::AbilityComponentPattern>(node->GetPattern());
            if (pattern) {
                pattern->FireDisConnect();
            }
        };
        PostTaskToUI(std::move(task));
    }

    void OnKeyEvent(const std::shared_ptr<MMI::KeyEvent>& event) override {}
    void OnPointerEvent(const std::shared_ptr<MMI::PointerEvent>& event) override {}
    void OnBackPress() override {}

private:
    void PostTaskToUI(const std::function<void()>&& task) const
    {
        if (!task) {
            LOGE("task is empty");
            return;
        }
        auto container = AceEngine::Get().GetContainer(instanceId_);
        if (!container) {
            LOGE("container is null");
            return;
        }
        auto context = container->GetPipelineContext();
        if (!context) {
            LOGE("context is null");
            return;
        }
        auto taskExecutor = context->GetTaskExecutor();
        if (!taskExecutor) {
            LOGE("task executor is null");
            return;
        }
        taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
    }

    static void UpdateFrameNodeTree(
        const RefPtr<NG::FrameNode>& node, const std::shared_ptr<Rosen::RSSurfaceNode>& rsSurfaceNode)
    {
        rsSurfaceNode->CreateNodeInRenderThread();
        auto size = node->GetGeometryNode()->GetFrameSize();
        auto offset = node->GetGeometryNode()->GetFrameOffset();
        LOGI("OnWindowReady surface size:%{public}f %{public}f %{public}f %{public}f", offset.GetX(), offset.GetY(),
            size.Width(), size.Height());
        rsSurfaceNode->SetBounds(0, 0, size.Width(), size.Height());
        rsSurfaceNode->SetBackgroundColor(Color::WHITE.GetValue());
        auto context = node->GetRenderContext();
        if (!context) {
            LOGI("context is empty");
            return;
        }
        AceType::DynamicCast<NG::RosenRenderContext>(context)->SetRSNode(rsSurfaceNode);
        auto parent = node->GetParent();
        if (!parent) {
            LOGI("parent is empty");
            return;
        }
        auto children = parent->GetChildren();
        std::list<RefPtr<NG::FrameNode>> temp;
        for (const auto& child : children) {
            temp.emplace_back(AceType::DynamicCast<NG::FrameNode>(child));
        }
        auto parentContent = AceType::DynamicCast<NG::RosenRenderContext>(
            AceType::DynamicCast<NG::FrameNode>(parent)->GetRenderContext());
        parentContent->RebuildFrame(AceType::DynamicCast<NG::FrameNode>(AceType::RawPtr(parent)), temp);
        context->RequestNextFrame();
    }

    RefPtr<NG::FrameNode> originNode_;
    WeakPtr<RenderNode> node_;
    std::shared_ptr<Rosen::RSSurfaceNode> rsOriginNode_;
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
    element.SetAbilityName(json->GetValue("ability")->GetString());
    element.SetBundleName(json->GetValue("bundle")->GetString());
}

void WindowExtensionConnectionAdapterOhos::ConnectExtension(const RefPtr<NG::FrameNode>& node)
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
    RefPtr<NG::AbilityComponentRenderProperty> renderProperty =
        node->GetPaintProperty<NG::AbilityComponentRenderProperty>();
    Rosen::Rect rosenRect = {
        0,
        0,
        static_cast<uint32_t>(renderProperty->GetHeightValue().ConvertToPx()),
        static_cast<uint32_t>(renderProperty->GetWidthValue().ConvertToPx()),
    };
    std::string want = renderProperty->GetWantValue();
    AppExecFwk::ElementName element;
    WantConverter(want, element);

    int32_t instanceId = -1;
    auto container = Container::Current();
    if (container) {
        instanceId = container->GetInstanceId();
    }
    sptr<Rosen::IWindowExtensionCallback> callback = new NGConnectionCallback(node, instanceId);
    windowExtension_->ConnectExtension(element, rosenRect, userIds.front(), callback);
#else
    LOGI("unrosen engine doesn't support ability component");
#endif
}

void WindowExtensionConnectionAdapterOhos::ConnectExtension(
    const std::string& want, const Rect& rect, WeakPtr<RenderNode> node)
{
    LOGI("ConnectExtension rect: %{public}s", rect.ToString().c_str());
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

    int32_t instanceId = -1;
    auto container = Container::Current();
    if (container) {
        instanceId = container->GetInstanceId();
    }
    sptr<Rosen::IWindowExtensionCallback> callback = new ConnectionCallback(node, instanceId);
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
    } else {
        LOGI("ability doesn't connect to window extension. show extension fail");
    }
}

void WindowExtensionConnectionAdapterOhos::Hide()
{
    LOGI("hide WindowExtensionConnectionAdapterOhos");
    if (windowExtension_) {
        windowExtension_->Hide();
    } else {
        LOGI("ability doesn't connect to window extension. show extension fail");
    }
}

void WindowExtensionConnectionAdapterOhos::UpdateRect(const Rect& rect)
{
    if (windowExtension_) {
        Rosen::Rect rosenRect;
        RectConverter(rect, rosenRect);
        LOGI("UpdateRect rect: %{public}s", rect.ToString().c_str());
        windowExtension_->SetBounds(rosenRect);
    } else {
        LOGI("ability doesn't connect to window extension.cannot update rect region ");
    }
}
} // namespace OHOS::Ace
