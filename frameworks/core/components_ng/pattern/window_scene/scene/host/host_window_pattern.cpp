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

#include "core/components_ng/pattern/window_scene/scene/host/host_window_pattern.h"

#include "render_service_client/core/ui/rs_surface_node.h"

#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

class LifecycleListener : public Rosen::ILifecycleListener {
public:
    LifecycleListener(const WeakPtr<HostWindowPattern>& hostWindowPattern) : hostWindowPattern_(hostWindowPattern) {}
    virtual ~LifecycleListener() = default;

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
    auto lifecycleListener = std::make_shared<LifecycleListener>(WeakClaim(this));
    session_->RegisterLifecycleListener(lifecycleListener);
}

void HostWindowPattern::InitContent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    contentNode_ = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    contentNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);

    CHECK_NULL_VOID(session_);
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);

    auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(surfaceNode);

    if (!HasStartingPage()) {
        host->AddChild(contentNode_);
    } else {
        startingNode_ = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        startingNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
        startingNode_->GetRenderContext()->UpdateBackgroundColor(Color(0xffffffff));
        host->AddChild(startingNode_);

        surfaceNode->SetBufferAvailableCallback([weak = WeakClaim(this)]() {
            LOGI("RSSurfaceNode buffer available callback");
            auto hostWindowPattern = weak.Upgrade();
            CHECK_NULL_VOID(hostWindowPattern);
            hostWindowPattern->BufferAvailableCallback();
        });
    }
}

void HostWindowPattern::BufferAvailableCallback()
{
    auto uiTask = [this]() {
        auto host = GetHost();
        CHECK_NULL_VOID(host);

        host->RemoveChild(startingNode_);
        startingNode_.Reset();

        contentNode_->SetActive(true);
        contentNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

        host->AddChild(contentNode_);
        host->RebuildRenderContextTree();
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), TaskExecutor::TaskType::UI);
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
    LOGI("update session rect: [%{public}d, %{public}d, %{public}d, %{public}d]",
        rect.posX_, rect.posY_, rect.width_, rect.height_);
    session_->UpdateRect(rect, Rosen::SizeChangeReason::SHOW);
    return false;
}

void HostWindowPattern::OnAttachToFrameNode()
{
    InitContent();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    auto renderContext = AceType::DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
    renderContext->SetClipToBounds(true);
}

} // namespace OHOS::Ace::NG
