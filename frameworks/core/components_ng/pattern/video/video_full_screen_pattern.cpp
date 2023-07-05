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

# include "core/components_ng/pattern/video/video_full_screen_pattern.h"

#include "core/components_ng/pattern/video/video_full_screen_node.h"
#include "core/components_ng/pattern/image/image_pattern.h"

namespace OHOS::Ace::NG {
void VideoFullScreenPattern::InitFullScreenParam(const RefPtr<VideoPattern>& videoPattern,
                                                 const RefPtr<RenderSurface>& renderSurface,
                                                 const RefPtr<MediaPlayer>& mediaPlayer,
                                                 const RefPtr<RenderContext>& context)
{
    UpdateMediaParam(mediaPlayer, renderSurface, context);
    videoPattern->ResetMediaParam();
    videoPattern_ = AceType::WeakClaim(AceType::RawPtr(videoPattern));
    auto video = videoPattern->GetHost();
    CHECK_NULL_VOID(video);
    SetEventHub(video->GetEventHub<EventHub>());
}

void VideoFullScreenPattern::RequestFullScreen(const RefPtr<VideoNode>& videoNode)
{
    auto fullScreenNode = AceType::DynamicCast<VideoFullScreenNode>(GetHost());
    CHECK_NULL_VOID(fullScreenNode);
    fullScreenNode->InitVideoFullScreenNode(videoNode);
    // add node to root
    int32_t rootId = videoNode->GetRootId();
    auto rootNode = FrameNode::GetFrameNode(V2::ROOT_ETS_TAG, rootId);
    CHECK_NULL_VOID(rootNode);
    fullScreenNode->MountToParent(rootNode);
    // set video size all window
    LayoutConstraintF parentConstraint;
    float rootWidth = PipelineContext::GetCurrentRootWidth();
    float rootHeight = PipelineContext::GetCurrentRootHeight();
    parentConstraint.maxSize.SetWidth(rootWidth);
    parentConstraint.maxSize.SetHeight(rootHeight);
    auto geometryNode = fullScreenNode->GetGeometryNode();
    geometryNode->SetParentLayoutConstraint(parentConstraint);
    geometryNode->SetMarginFrameOffset(OffsetF {0.0f, 0.0f});
    auto videoPattern = AceType::DynamicCast<VideoPattern>(videoNode->GetPattern());
    RecoverState(videoPattern);
    fullScreenNode->MarkModifyDone();
    fullScreenNode->RebuildRenderContextTree();
    fullScreenNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    rootNode->RebuildRenderContextTree();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    OnFullScreenChange(true);
}

void VideoFullScreenPattern::ExitFullScreen()
{
    auto videoPattern = videoPattern_.Upgrade();
    CHECK_NULL_VOID(videoPattern);
    videoPattern->UpdateMediaParam(mediaPlayer_, renderSurface_, renderContextForMediaPlayer_);
    ResetMediaParam();
    // remove full screen node
    auto fullScreenNode = GetHost();
    CHECK_NULL_VOID(fullScreenNode);
    auto rootNode = fullScreenNode->GetParent();
    CHECK_NULL_VOID(rootNode);
    rootNode->RemoveChild(fullScreenNode);
    rootNode->RebuildRenderContextTree();

    auto videoNode = AceType::DynamicCast<VideoNode>(videoPattern->GetHost());
    CHECK_NULL_VOID(videoNode);
    // change value about time and playing status
    videoPattern->RecoverState(AceType::Claim(this));
    // change full screen button
    videoPattern->OnFullScreenChange(false);
    videoNode->MarkModifyDone();
}

void VideoFullScreenPattern::UpdateState()
{
    auto videoPattern = videoPattern_.Upgrade();
    CHECK_NULL_VOID(videoPattern);
    UpdateLoop(videoPattern->GetLoop());
    UpdateMuted(videoPattern->GetMuted());
    UpdateAutoPlay(videoPattern->GetAutoPlay());
    UpdateProgressRate(videoPattern->GetProgressRate());

    // update full screen layout
    auto fullScreenNode = GetHost();
    CHECK_NULL_VOID(fullScreenNode);
    auto fullScreenLayout = fullScreenNode->GetLayoutProperty<VideoLayoutProperty>();
    auto videoNode = videoPattern->GetHost();
    CHECK_NULL_VOID(videoNode);
    auto videoLayout = videoNode->GetLayoutProperty<VideoLayoutProperty>();
    bool isChanged = false;
    if (videoLayout->HasObjectFit() &&
        (fullScreenLayout->GetObjectFit() != videoLayout->GetObjectFit())) {
        isChanged = true;
        fullScreenLayout->UpdateObjectFit(videoLayout->GetObjectFit().value());
    }
    if (videoLayout->HasVideoSource() &&
        (fullScreenLayout->GetVideoSource() != videoLayout->GetVideoSource())) {
        isChanged = true;
        fullScreenLayout->UpdateVideoSource(videoLayout->GetVideoSource().value());
    }
    if (videoLayout->HasPosterImageInfo() &&
        (fullScreenLayout->GetPosterImageInfo() != videoLayout->GetPosterImageInfo())) {
        isChanged = true;
        fullScreenLayout->UpdatePosterImageInfo(videoLayout->GetPosterImageInfo().value());
    }
    if (videoLayout->HasControls() && (
        fullScreenLayout->GetControls() != videoLayout->GetControls())) {
        isChanged = true;
        fullScreenLayout->UpdateControls(videoLayout->GetControls().value());
    }
    if (isChanged) {
        fullScreenNode->MarkModifyDone();
        fullScreenNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
}
} // namespace OHOS::Ace::NG
