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

#include "core/components_ng/pattern/window_scene/scene/host/host_window_pattern.h"

#include "render_service_client/core/ui/rs_surface_node.h"
#include "interfaces/include/ws_common.h"

#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
class LifecycleListener : public Rosen::ILifecycleListener {
public:
    explicit LifecycleListener(const WeakPtr<HostWindowPattern>& hostWindowPattern)
        : hostWindowPattern_(hostWindowPattern) {}
    virtual ~LifecycleListener() = default;

    void OnConnect()
    {
        auto hostWindowPattern = hostWindowPattern_.Upgrade();
        CHECK_NULL_VOID(hostWindowPattern);
        hostWindowPattern->OnConnect();
    }

    void OnForeground() override
    {
        auto hostWindowPattern = hostWindowPattern_.Upgrade();
        CHECK_NULL_VOID(hostWindowPattern);
        hostWindowPattern->OnForeground();
    }

    void OnBackground() override
    {
        auto hostWindowPattern = hostWindowPattern_.Upgrade();
        CHECK_NULL_VOID(hostWindowPattern);
        hostWindowPattern->OnBackground();
    }

private:
    WeakPtr<HostWindowPattern> hostWindowPattern_;
};

HostWindowPattern::HostWindowPattern()
{
    instanceId_ = Container::CurrentId();
}

void HostWindowPattern::RegisterLifecycleListener()
{
    CHECK_NULL_VOID(session_);
    lifecycleListener_ = std::make_shared<LifecycleListener>(WeakClaim(this));
    session_->RegisterLifecycleListener(lifecycleListener_);
}

void HostWindowPattern::UnregisterLifecycleListener()
{
    CHECK_NULL_VOID(session_);
    session_->UnregisterLifecycleListener(lifecycleListener_);
}

void HostWindowPattern::InitContent()
{
    contentNode_ = FrameNode::CreateFrameNode(
        V2::HOST_WINDOW_SCENE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    contentNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);

    CHECK_NULL_VOID(session_);
    auto surfaceNode = session_->GetSurfaceNode();
    if (surfaceNode) {
        auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
        CHECK_NULL_VOID(context);
        context->SetRSNode(surfaceNode);
    }

    auto state = session_->GetSessionState();
    LOGI("Session state is %{public}u.", state);
    switch (state) {
        case Rosen::SessionState::STATE_DISCONNECT: {
            CreateStartingNode();
            break;
        }
        case Rosen::SessionState::STATE_BACKGROUND: {
            CreateSnapshotNode();
            break;
        }
        default: {
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            host->AddChild(contentNode_);
            break;
        }
    }
}

void HostWindowPattern::CreateStartingNode()
{
    if (!HasStartingPage()) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    startingNode_ = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    startingNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    startingNode_->GetRenderContext()->UpdateBackgroundColor(Color::WHITE);
    host->AddChild(startingNode_);
}

void HostWindowPattern::CreateSnapshotNode()
{
    snapshotNode_ = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = snapshotNode_->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    snapshotNode_->GetRenderContext()->UpdateBackgroundColor(Color::WHITE);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->AddChild(snapshotNode_);

    CHECK_NULL_VOID(session_);
    auto snapshot = session_->GetSnapshot();
    auto pixelMap = PixelMap::CreatePixelMap(&snapshot);

    CHECK_NULL_VOID(pixelMap);
    imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    snapshotNode_->MarkModifyDone();
}

void HostWindowPattern::OnConnect()
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(session_);
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);

    CHECK_NULL_VOID(contentNode_);
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(surfaceNode);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->AddChild(contentNode_, 0);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    if (!HasStartingPage()) {
        return;
    }
    surfaceNode->SetBufferAvailableCallback([weak = WeakClaim(this)]() {
        LOGI("RSSurfaceNode buffer available callback");
        auto hostWindowPattern = weak.Upgrade();
        CHECK_NULL_VOID(hostWindowPattern);
        hostWindowPattern->BufferAvailableCallback();
    });
}

void HostWindowPattern::BufferAvailableCallback()
{
    ContainerScope scope(instanceId_);

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    host->RemoveChild(startingNode_);
    startingNode_.Reset();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void HostWindowPattern::OnAttachToFrameNode()
{
    InitContent();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

bool HostWindowPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (!config.frameSizeChange) {
        LOGI("frame size not changed, just return");
        return false;
    }
    CHECK_NULL_RETURN(dirty, false);
    auto geometryNode = dirty->GetGeometryNode();
    auto windowRect = geometryNode->GetFrameRect();
    Rosen::WSRect rect = {
        .posX_ = std::round(windowRect.GetX()),
        .posY_ = std::round(windowRect.GetY()),
        .width_ = std::round(windowRect.Width()),
        .height_ = std::round(windowRect.Height())
    };

    CHECK_NULL_RETURN(session_, false);
    session_->UpdateRect(rect, Rosen::SizeChangeReason::SHOW);
    return false;
}

void HostWindowPattern::DispatchPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(session_);
    auto errCode = session_->TransferPointerEvent(pointerEvent);
    if (errCode != Rosen::WSError::WS_OK) {
        LOGE("DispatchPointerEvent failed, errCode=%{public}d", static_cast<int>(errCode));
    }
}

void HostWindowPattern::DispatchKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent)
{
    CHECK_NULL_VOID(session_);
    auto errCode = session_->TransferKeyEvent(keyEvent);
    if (errCode != Rosen::WSError::WS_OK) {
        LOGE("DispatchPointerEvent failed, errCode=%{public}d", static_cast<int>(errCode));
    }
}
} // namespace OHOS::Ace::NG
