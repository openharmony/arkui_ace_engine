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

#include "core/components_ng/pattern/window_scene/host/host_window_pattern.h"

#include "render_service_client/core/ui/rs_surface_node.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void HostWindowPattern::InitContent()
{
    if (contentNode_) {
        // had initialized, should not initialize again
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto stack = ViewStackProcessor::GetInstance();
    startingNode_ = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    stack->Push(startingNode_);
    startingNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    startingNode_->GetRenderContext()->UpdateBackgroundColor(Color(0xffeeeeee));
    host->AddChild(startingNode_);

    contentNode_ = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    contentNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);

    CHECK_NULL_VOID(session_);
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);

    auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(surfaceNode);

    surfaceNode->SetBufferAvailableCallback([weak = WeakClaim(this)]() {
        LOGI("RSSurfaceNode buffer available callback");
        auto hostWindowPattern = weak.Upgrade();
        CHECK_NULL_VOID(hostWindowPattern);
        auto host = hostWindowPattern->GetHost();
        CHECK_NULL_VOID(host);

        auto stack = ViewStackProcessor::GetInstance();
        stack->Pop();
        stack->Push(hostWindowPattern->contentNode_);

        host->RemoveChild(hostWindowPattern->startingNode_);
        hostWindowPattern->startingNode_.Reset();
        host->AddChild(hostWindowPattern->contentNode_);
    });
    // session_->RegisterOnBackgroundCallback(&HostWindowPattern::OnBackground);
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
        .posX_ = windowRect.GetX(),
        .posY_ = windowRect.GetY(),
        .width_ = windowRect.Width(),
        .height_ = windowRect.Height()
    };
    LOGI("update session rect: [%{public}d, %{public}d, %{public}d, %{public}d]",
        rect.posX_, rect.posY_, rect.width_, rect.height_);
    session_->UpdateSessionRect(rect, Rosen::SessionSizeChangeReason::SHOW);
    return false;
}

void HostWindowPattern::OnBackground()
{
    // auto snapShot = session_->GetSnapShot();
    RefPtr<PixelMap> snapShot = nullptr;

    auto stack = ViewStackProcessor::GetInstance();
    startingNode_ = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = startingNode_->GetLayoutProperty<ImageLayoutProperty>();
    if (imageLayoutProperty) {
        imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(snapShot));
    }
    stack->Pop();
    stack->Push(startingNode_);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveChild(contentNode_);
    host->AddChild(startingNode_);
}

} // namespace OHOS::Ace::NG
