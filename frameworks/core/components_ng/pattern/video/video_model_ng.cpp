/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/video/video_model_ng.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/video/video_node.h"
#include "core/components_ng/pattern/video/video_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void VideoModelNG::Create(const RefPtr<VideoControllerV2>& videoController)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto videoNode = VideoNode::GetOrCreateVideoNode(
        V2::VIDEO_ETS_TAG, nodeId, [videoController]() { return AceType::MakeRefPtr<VideoPattern>(videoController); });
    CHECK_NULL_VOID(videoNode);
    stack->Push(videoNode);
    bool hasPreviewImageNode = videoNode->HasPreviewImageNode();
    bool hasControllerRowNode = videoNode->HasControllerRowNode();
    LOGI("Preview image is %{public}d, controller is %{public}d.", hasPreviewImageNode, hasControllerRowNode);
    if (!hasPreviewImageNode) {
        auto previewImageId = videoNode->GetPreviewImageId();
        auto previewImageNode = FrameNode::GetOrCreateFrameNode(
            V2::IMAGE_ETS_TAG, previewImageId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
        CHECK_NULL_VOID(previewImageNode);
        videoNode->AddChild(previewImageNode);
    }
    if (!hasControllerRowNode) {
        auto controllerRowId = videoNode->GetControllerRowId();
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
        CHECK_NULL_VOID(videoPattern);
        auto controllerRowNode = videoPattern->CreateControlBar(controllerRowId);
        CHECK_NULL_VOID(controllerRowNode);
        videoNode->AddChild(controllerRowNode);
    }
    AddDragFrameNodeToManager();
}

void VideoModelNG::SetSrc(const std::string& src)
{
    ACE_UPDATE_LAYOUT_PROPERTY(VideoLayoutProperty, VideoSource, src);
}

void VideoModelNG::SetProgressRate(double progressRate)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    videoPattern->UpdateProgressRate(progressRate);
}

void VideoModelNG::SetPosterSourceInfo(const std::string& posterUrl)
{
    ImageSourceInfo posterSourceInfo(posterUrl);
    ACE_UPDATE_LAYOUT_PROPERTY(VideoLayoutProperty, PosterImageInfo, posterSourceInfo);
}

void VideoModelNG::SetPosterSourceByPixelMap(RefPtr<PixelMap>& pixMap)
{
    ImageSourceInfo posterSourceInfo(pixMap);
    ACE_UPDATE_LAYOUT_PROPERTY(VideoLayoutProperty, PosterImageInfo, posterSourceInfo);
}

void VideoModelNG::SetMuted(bool muted)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    videoPattern->UpdateMuted(muted);
}

void VideoModelNG::SetAutoPlay(bool autoPlay)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    videoPattern->UpdateAutoPlay(autoPlay);
}

void VideoModelNG::SetControls(bool controls)
{
    ACE_UPDATE_LAYOUT_PROPERTY(VideoLayoutProperty, Controls, controls);
}

void VideoModelNG::SetObjectFit(ImageFit objectFit)
{
    ACE_UPDATE_LAYOUT_PROPERTY(VideoLayoutProperty, ObjectFit, objectFit);
}

void VideoModelNG::SetLoop(bool loop)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    videoPattern->UpdateLoop(loop);
}

void VideoModelNG::SetOnStart(VideoEventFunc&& onStart)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStart(std::move(onStart));
}

void VideoModelNG::SetOnPause(VideoEventFunc&& onPause)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPause(std::move(onPause));
}

void VideoModelNG::SetOnFinish(VideoEventFunc&& onFinish)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFinish(std::move(onFinish));
}

void VideoModelNG::SetOnError(VideoEventFunc&& onError)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnError(std::move(onError));
}

void VideoModelNG::SetOnPrepared(VideoEventFunc&& onPrepared)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPrepared(std::move(onPrepared));
}

void VideoModelNG::SetOnSeeking(VideoEventFunc&& onSeeking)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSeeking(std::move(onSeeking));
}

void VideoModelNG::SetOnSeeked(VideoEventFunc&& onSeeked)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSeeked(std::move(onSeeked));
}

void VideoModelNG::SetOnUpdate(VideoEventFunc&& onUpdate)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnUpdate(std::move(onUpdate));
}

void VideoModelNG::SetOnFullScreenChange(VideoEventFunc&& onFullScreenChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFullScreenChange(std::move(onFullScreenChange));
}

void VideoModelNG::AddDragFrameNodeToManager() const
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    dragDropManager->AddDragFrameNode(frameNode);
}
} // namespace OHOS::Ace::NG
