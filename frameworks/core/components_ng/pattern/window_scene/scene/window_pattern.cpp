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

#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"

#include "ui/rs_surface_node.h"

#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
class LifecycleListener : public Rosen::ILifecycleListener {
public:
    explicit LifecycleListener(const WeakPtr<WindowPattern>& windowPattern)
        : windowPattern_(windowPattern) {}
    virtual ~LifecycleListener() = default;

    void OnConnect() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnConnect();
    }

    void OnForeground() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnForeground();
    }

    void OnBackground() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnBackground();
    }

private:
    WeakPtr<WindowPattern> windowPattern_;
};

WindowPattern::WindowPattern()
{
    instanceId_ = Container::CurrentId();
}

void WindowPattern::RegisterLifecycleListener()
{
    CHECK_NULL_VOID(session_);
    lifecycleListener_ = std::make_shared<LifecycleListener>(WeakClaim(this));
    session_->RegisterLifecycleListener(lifecycleListener_);
}

void WindowPattern::UnregisterLifecycleListener()
{
    CHECK_NULL_VOID(session_);
    session_->UnregisterLifecycleListener(lifecycleListener_);
}

void WindowPattern::InitContent()
{
    contentNode_ = FrameNode::CreateFrameNode(
        V2::WINDOW_SCENE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
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

void WindowPattern::CreateStartingNode()
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

void WindowPattern::CreateSnapshotNode()
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

void WindowPattern::OnConnect()
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
        auto windowPattern = weak.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->BufferAvailableCallback();
    });
}

void WindowPattern::BufferAvailableCallback()
{
    ContainerScope scope(instanceId_);

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    host->RemoveChild(startingNode_);
    startingNode_.Reset();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void WindowPattern::OnAttachToFrameNode()
{
    InitContent();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

bool WindowPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
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
    session_->UpdateRect(rect, Rosen::SizeChangeReason::UNDEFINED);
    return false;
}

void WindowPattern::DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(session_);
    session_->TransferPointerEvent(pointerEvent);
}

void WindowPattern::DispatchKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    CHECK_NULL_VOID(session_);
    session_->TransferKeyEvent(keyEvent);
}
} // namespace OHOS::Ace::NG
