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

#include "core/components_ng/pattern/video/video_view.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/video/video_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {

void VideoView::Create(const RefPtr<VideoControllerV2>& videoController)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::VIDEO_ETS_TAG, nodeId, [videoController]() { return AceType::MakeRefPtr<VideoPattern>(videoController); });
    stack->Push(frameNode);
}

void VideoView::SetSrc(const std::string& src)
{
    ACE_UPDATE_LAYOUT_PROPERTY(VideoLayoutProperty, VideoSource, src);
}

void VideoView::SetProgressRate(double progressRate)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    videoPattern->UpdateProgressRate(progressRate);
}

void VideoView::SetPosterSourceInfo(const std::string& posterUrl)
{
    ImageSourceInfo posterSourceInfo(posterUrl);
    ACE_UPDATE_LAYOUT_PROPERTY(VideoLayoutProperty, PosterImageInfo, posterSourceInfo);
}

void VideoView::SetMuted(bool muted)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    videoPattern->UpdateMuted(muted);
}

void VideoView::SetAutoPlay(bool autoPlay)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    videoPattern->UpdateAutoPlay(autoPlay);
}

void VideoView::SetControls(bool controls)
{
    ACE_UPDATE_LAYOUT_PROPERTY(VideoLayoutProperty, Controls, controls);
}

void VideoView::SetObjectFit(ImageFit objectFit)
{
    ACE_UPDATE_LAYOUT_PROPERTY(VideoLayoutProperty, ObjectFit, objectFit);
}

void VideoView::SetLoop(bool loop)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(frameNode->GetPattern());
    videoPattern->UpdateLoop(loop);
}

void VideoView::SetOnStart(EventCallback&& onStart)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStart(std::move(onStart));
}

void VideoView::SetOnPause(EventCallback&& onPause)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPause(std::move(onPause));
}

void VideoView::SetOnFinish(EventCallback&& onFinish)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFinish(std::move(onFinish));
}

void VideoView::SetOnError(EventCallback&& onError)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnError(std::move(onError));
}

void VideoView::SetOnPrepared(EventCallback&& onPrepared)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPrepared(std::move(onPrepared));
}

void VideoView::SetOnSeeking(EventCallback&& onSeeking)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSeeking(std::move(onSeeking));
}

void VideoView::SetOnSeeked(EventCallback&& onSeeked)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSeeked(std::move(onSeeked));
}

void VideoView::SetOnUpdate(EventCallback&& onUpdate)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnUpdate(std::move(onUpdate));
}

void VideoView::SetOnFullScreenChange(EventCallback&& onFullScreenChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFullScreenChange(std::move(onFullScreenChange));
}

} // namespace OHOS::Ace::NG
