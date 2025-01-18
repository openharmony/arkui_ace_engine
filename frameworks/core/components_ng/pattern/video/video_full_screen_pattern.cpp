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

#include "core/components_ng/pattern/video/video_full_screen_pattern.h"

#include "core/components_ng/pattern/video/video_full_screen_node.h"

namespace OHOS::Ace::NG {
void VideoFullScreenPattern::InitFullScreenParam(const RefPtr<VideoPattern>& videoPattern,
    const RefPtr<RenderSurface>& renderSurface, const RefPtr<MediaPlayer>& mediaPlayer,
    const RefPtr<RenderContext>& context)
{
    UpdateMediaParam(mediaPlayer, renderSurface, context);
    videoPattern->ResetMediaParam();
    videoPattern_ = AceType::WeakClaim(AceType::RawPtr(videoPattern));
    RecoverState(videoPattern);
    auto video = videoPattern->GetHost();
    CHECK_NULL_VOID(video);
    SetEventHub(video->GetEventHub<EventHub>());
}

void VideoFullScreenPattern::SetEventHub(const RefPtr<EventHub>& eventHub)
{
    eventHub_ = eventHub;
    originGestureEventHub_ = eventHub->GetGestureEventHub();
    // create a new gestureEventHub and copy original event
    auto gestureEventHub = MakeRefPtr<GestureEventHub>(eventHub);
    gestureEventHub->CopyEvent(originGestureEventHub_);
    gestureEventHub->CopyGestures(originGestureEventHub_);
    eventHub_->SetGestureEventHub(gestureEventHub);
    eventHub_->AttachHost(GetHost());
}

void VideoFullScreenPattern::RequestFullScreen(const RefPtr<VideoNode>& videoNode)
{
    ContainerScope scope(instanceId_);
    auto fullScreenNode = AceType::DynamicCast<VideoFullScreenNode>(GetHost());
    CHECK_NULL_VOID(fullScreenNode);
    fullScreenNode->InitVideoFullScreenNode(videoNode);
    // add node to root
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelienContext = host->GetContext();
    CHECK_NULL_VOID(pipelienContext);
    auto rootNode = pipelienContext->GetRootElement();
    if (!rootNode) {
        auto videoPattern = AceType::DynamicCast<VideoPattern>(videoNode->GetPattern());
        videoPattern->UpdateMediaParam(mediaPlayer_, renderSurface_, renderContextForMediaPlayer_);
        ResetMediaParam();
        return;
    }
    fullScreenNode->MountToParent(rootNode);
    // set video size all window
    LayoutConstraintF parentConstraint;
    float rootWidth = PipelineContext::GetCurrentRootWidth();
    float rootHeight = PipelineContext::GetCurrentRootHeight();
    parentConstraint.maxSize.SetWidth(rootWidth);
    parentConstraint.maxSize.SetHeight(rootHeight);
    auto geometryNode = fullScreenNode->GetGeometryNode();
    geometryNode->SetParentLayoutConstraint(parentConstraint);
    geometryNode->SetMarginFrameOffset(OffsetF { 0.0f, 0.0f });
    fullScreenNode->MarkModifyDone();
    fullScreenNode->RebuildRenderContextTree();
    fullScreenNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    rootNode->RebuildRenderContextTree();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FocusViewShow();
    OnFullScreenChange(true);
}

bool VideoFullScreenPattern::ExitFullScreen()
{
    auto videoPattern = videoPattern_.Upgrade();
    CHECK_NULL_RETURN(videoPattern, false);
    videoPattern->UpdateMediaParam(mediaPlayer_, renderSurface_, renderContextForMediaPlayer_);
    ResetMediaParam();
    // remove full screen node
    auto fullScreenNode = GetHost();
    CHECK_NULL_RETURN(fullScreenNode, false);
    auto rootNode = fullScreenNode->GetParent();
    CHECK_NULL_RETURN(rootNode, false);
    rootNode->RemoveChild(fullScreenNode);
    rootNode->RebuildRenderContextTree();

    auto videoNode = AceType::DynamicCast<VideoNode>(videoPattern->GetHost());
    CHECK_NULL_RETURN(videoNode, false);
    // change value about time and playing status
    videoPattern->RecoverState(AceType::Claim(this));
    // change full screen button
    videoPattern->OnFullScreenChange(false);
    // recover gestureEventHub
    eventHub_->SetGestureEventHub(originGestureEventHub_);
    eventHub_->AttachHost(videoPattern->GetHost());
    videoNode->MarkModifyDone();
    FocusViewClose();
    return true;
}

void VideoFullScreenPattern::UpdateState()
{
    auto videoPattern = videoPattern_.Upgrade();
    CHECK_NULL_VOID(videoPattern);
    UpdateLoop(videoPattern->GetLoop());
    UpdateMuted(videoPattern->GetMuted());
    UpdateAutoPlay(videoPattern->GetAutoPlay());
    UpdateProgressRate(videoPattern->GetProgressRate());
    UpdateAnalyzerState(videoPattern->GetAnalyzerState());
    SetShortcutKeyEnabled(videoPattern->GetShortcutKeyEnabled());
    SetCurrentVolume(videoPattern->GetCurrentVolume());

    // update full screen layout
    auto fullScreenNode = GetHost();
    CHECK_NULL_VOID(fullScreenNode);
    auto fullScreenLayout = fullScreenNode->GetLayoutProperty<VideoLayoutProperty>();
    auto videoNode = videoPattern->GetHost();
    CHECK_NULL_VOID(videoNode);
    auto videoLayout = videoNode->GetLayoutProperty<VideoLayoutProperty>();
    if (videoLayout->HasObjectFit() && (fullScreenLayout->GetObjectFit() != videoLayout->GetObjectFit())) {
        fullScreenLayout->UpdateObjectFit(videoLayout->GetObjectFit().value());
    }
    if (videoLayout->HasVideoSource() && (fullScreenLayout->GetVideoSource() != videoLayout->GetVideoSource())) {
        fullScreenLayout->UpdateVideoSource(videoLayout->GetVideoSource().value());
    }
    if (videoLayout->HasPosterImageInfo() &&
        (fullScreenLayout->GetPosterImageInfo() != videoLayout->GetPosterImageInfo())) {
        fullScreenLayout->UpdatePosterImageInfo(videoLayout->GetPosterImageInfo().value());
    }
    if (videoLayout->HasControls() && (fullScreenLayout->GetControls() != videoLayout->GetControls())) {
        fullScreenLayout->UpdateControls(videoLayout->GetControls().value());
    }
    fullScreenNode->MarkModifyDone();
    fullScreenNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}
} // namespace OHOS::Ace::NG
