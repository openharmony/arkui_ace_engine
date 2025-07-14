/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/video/video_model_static.h"

#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/video/video_node.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> VideoModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto videoNode = VideoNode::GetOrCreateVideoNode(
        V2::VIDEO_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<VideoPattern>(nullptr); });
    auto videoFocusHub = videoNode->GetFocusHub();
    if (videoFocusHub) {
        videoFocusHub->SetIsFocusUnit(true);
    }
    bool hasPreviewImageNode = videoNode->HasPreviewImageNode();
    bool hasControllerRowNode = videoNode->HasControllerRowNode();
    bool hasMediaColumnNode = videoNode->HasMediaColumnNode();
    if (!hasMediaColumnNode) {
        auto mediaColumnId = videoNode->GetMediaColumnId();
        auto mediaColumNode = FrameNode::GetOrCreateFrameNode(
            V2::COLUMN_ETS_TAG, mediaColumnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        CHECK_NULL_RETURN(mediaColumNode, videoNode);
        videoNode->AddChild(mediaColumNode);
    }
    if (!hasPreviewImageNode) {
        auto previewImageId = videoNode->GetPreviewImageId();
        auto previewImageNode = FrameNode::GetOrCreateFrameNode(
            V2::IMAGE_ETS_TAG, previewImageId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
        CHECK_NULL_RETURN(previewImageNode, videoNode);
        videoNode->AddChild(previewImageNode);
    }
    if (!hasControllerRowNode) {
        auto controllerRowId = videoNode->GetControllerRowId();
        auto videoPattern = AceType::DynamicCast<VideoPattern>(videoNode->GetPattern());
        CHECK_NULL_RETURN(videoPattern, videoNode);
        auto controllerRowNode = videoPattern->CreateControlBar(controllerRowId);
        CHECK_NULL_RETURN(controllerRowNode, videoNode);
        videoNode->AddChild(controllerRowNode);
    }
    return videoNode;
}

void VideoModelStatic::SetSrc(FrameNode* frameNode,
    const std::string& src, const std::string& bundleName, const std::string& moduleName)
{
    VideoSourceInfo videoSrcInfo;
    videoSrcInfo.src_ = src;
    videoSrcInfo.bundleName_ = bundleName;
    videoSrcInfo.moduleName_ = moduleName;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(VideoLayoutProperty, VideoSource, videoSrcInfo, frameNode);
}

void VideoModelStatic::SetShowFirstFrame(FrameNode* frameNode, bool showFirstFrame)
{
    CHECK_NULL_VOID(frameNode);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(videoPattern);
    videoPattern->UpdateShowFirstFrame(showFirstFrame);
}

void VideoModelStatic::SetProgressRate(FrameNode* frameNode, double progressRate)
{
    CHECK_NULL_VOID(frameNode);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    videoPattern->UpdateProgressRate(progressRate);
}

void VideoModelStatic::SetPosterSourceInfo(FrameNode* frameNode, const ImageSourceInfo& posterSourceInfo)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(VideoLayoutProperty, PosterImageInfo, posterSourceInfo, frameNode);
}

void VideoModelStatic::SetVideoController(FrameNode* frameNode, const RefPtr<VideoControllerV2>& videoController)
{
    CHECK_NULL_VOID(frameNode);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    videoPattern->SetVideoController(videoController);
}

void VideoModelStatic::SetObjectFit(FrameNode* frameNode, std::optional<ImageFit> objectFit)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(VideoLayoutProperty, ObjectFit, objectFit.value_or(ImageFit::COVER), frameNode);
}

void VideoModelStatic::SetSurfaceBackgroundColor(FrameNode* frameNode, const std::optional<Color>& optColor)
{
    CHECK_NULL_VOID(frameNode);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(videoPattern);
    videoPattern->SetSurfaceBackgroundColor(optColor.value_or(Color::BLACK));
}

void VideoModelStatic::EnableAnalyzer(FrameNode* frameNode, bool enable)
{
    CHECK_NULL_VOID(frameNode);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    videoPattern->EnableAnalyzer(enable);
}

void VideoModelStatic::SetOnStart(FrameNode* frameNode, VideoEventFunc&& onStart)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStart(std::move(onStart));
}

void VideoModelStatic::SetOnPause(FrameNode* frameNode, VideoEventFunc&& onPause)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPause(std::move(onPause));
}

void VideoModelStatic::SetOnFinish(FrameNode* frameNode, VideoEventFunc&& onFinish)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFinish(std::move(onFinish));
}

void VideoModelStatic::SetOnFullScreenChange(FrameNode* frameNode, VideoEventFunc&& onFullScreenChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFullScreenChange(std::move(onFullScreenChange));
}

void VideoModelStatic::SetOnSeeking(FrameNode* frameNode, VideoEventFunc&& onSeeking)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSeeking(std::move(onSeeking));
}

void VideoModelStatic::SetOnPrepared(FrameNode* frameNode, VideoEventFunc&& onPrepared)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPrepared(std::move(onPrepared));
}

void VideoModelStatic::SetOnSeeked(FrameNode* frameNode, VideoEventFunc&& onSeeked)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSeeked(std::move(onSeeked));
}

void VideoModelStatic::SetOnUpdate(FrameNode* frameNode, VideoEventFunc&& onUpdate)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnUpdate(std::move(onUpdate));
}

void VideoModelStatic::SetOnError(FrameNode* frameNode, VideoEventFunc&& onError)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnError(std::move(onError));
}

void VideoModelStatic::SetOnStop(FrameNode* frameNode, VideoEventFunc&& onStop)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStop(std::move(onStop));
}

void VideoModelStatic::SetPosterSourceByPixelMap(FrameNode* frameNode, RefPtr<PixelMap>& pixMap)
{
    ImageSourceInfo posterSourceInfo(pixMap);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(VideoLayoutProperty, PosterImageInfo, posterSourceInfo, frameNode);
}
} // namespace OHOS::Ace::NG
