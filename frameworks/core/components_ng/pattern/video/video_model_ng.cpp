/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/video/video_event_hub.h"
#include "core/components_ng/pattern/video/video_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/video/video_controller_async.h"
#include "core/components_ng/pattern/video/video_node.h"
#include "core/components_ng/pattern/video/video_state_machine_pattern.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

static void UpdateControlsIfNeeded(FrameNode* frameNode, bool controls)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        auto layoutProperty = stateMachinePattern->GetLayoutProperty<VideoLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        if (!layoutProperty->HasControls() || controls != layoutProperty->GetControlsValue(true)) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(VideoLayoutProperty, Controls, controls, frameNode);
            stateMachinePattern->UpdateControllerBar();
        }
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    auto layoutProperty = videoPattern->GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->HasControls() || controls != layoutProperty->GetControlsValue(true)) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(VideoLayoutProperty, Controls, controls, frameNode);
        videoPattern->UpdateControllerBar();
    }
}

static void UpdateControllerBar(FrameNode* frameNode, bool controls)
{
    CHECK_NULL_VOID(frameNode);
    UpdateControlsIfNeeded(frameNode, controls);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        auto fullScreenNode = stateMachinePattern->GetFullScreenNode();
        UpdateControlsIfNeeded(fullScreenNode.GetRawPtr(), controls);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    auto fullScreenNode = videoPattern->GetFullScreenNode();
    UpdateControlsIfNeeded(fullScreenNode.GetRawPtr(), controls);
}

static RefPtr<FrameNode> CreateControlBarFromPattern(FrameNode* frameNode, int32_t controllerRowId)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        return stateMachinePattern->CreateControlBar(controllerRowId);
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_RETURN(videoPattern, nullptr);
    return videoPattern->CreateControlBar(controllerRowId);
}

void VideoModelNG::Create(const RefPtr<VideoControllerV2>& videoController)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::VIDEO_ETS_TAG, nodeId);
    auto videoNode = VideoNode::GetOrCreateVideoNode(
        V2::VIDEO_ETS_TAG, nodeId, [videoController]() { return AceType::MakeRefPtr<VideoPattern>(videoController); });
    CHECK_NULL_VOID(videoNode);

    // If existing node has wrong pattern type, recreate it
    auto pattern = videoNode->GetPattern();
    if (!AceType::InstanceOf<VideoPattern>(pattern)) {
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = videoNode->GetParent();
        if (parent) {
            parent->RemoveChild(videoNode);
        }
        videoNode = VideoNode::GetOrCreateVideoNode(
            V2::VIDEO_ETS_TAG, nodeId, [videoController]() { return AceType::MakeRefPtr<VideoPattern>(videoController); });
        CHECK_NULL_VOID(videoNode);
    }

    auto videoFocusHub = videoNode->GetFocusHub();
    if (videoFocusHub) {
        videoFocusHub->SetIsFocusUnit(true);
    }
    stack->Push(videoNode);
    bool hasPreviewImageNode = videoNode->HasPreviewImageNode();
    bool hasControllerRowNode = videoNode->HasControllerRowNode();
    bool hasMediaColumnNode = videoNode->HasMediaColumnNode();
    if (!hasMediaColumnNode) {
        auto mediaColumnId = videoNode->GetMediaColumnId();
        ACE_UINODE_TRACE(nodeId);
        auto mediaColumNode = FrameNode::GetOrCreateFrameNode(
            V2::COLUMN_ETS_TAG, mediaColumnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        CHECK_NULL_VOID(mediaColumNode);
        videoNode->AddChild(mediaColumNode);
    }
    if (!hasPreviewImageNode) {
        auto previewImageId = videoNode->GetPreviewImageId();
        ACE_UINODE_TRACE(nodeId);
        auto previewImageNode = FrameNode::GetOrCreateFrameNode(
            V2::IMAGE_ETS_TAG, previewImageId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
        CHECK_NULL_VOID(previewImageNode);
        videoNode->AddChild(previewImageNode);
    }
    if (!hasControllerRowNode) {
        auto controllerRowId = videoNode->GetControllerRowId();
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto controllerRowNode = CreateControlBarFromPattern(frameNode, controllerRowId);
        CHECK_NULL_VOID(controllerRowNode);
        videoNode->AddChild(controllerRowNode);
    }
}

void VideoModelNG::Create(const RefPtr<VideoControllerAsync>& videoControllerAsync)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::VIDEO_ETS_TAG, nodeId);
    auto videoNode = VideoNode::GetOrCreateVideoNode(
        V2::VIDEO_ETS_TAG, nodeId,
        [videoControllerAsync]() { return AceType::MakeRefPtr<VideoStateMachinePattern>(videoControllerAsync); });
    CHECK_NULL_VOID(videoNode);

    // If existing node has wrong pattern type, recreate it
    auto pattern = videoNode->GetPattern();
    if (!AceType::InstanceOf<VideoStateMachinePattern>(pattern)) {
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = videoNode->GetParent();
        if (parent) {
            parent->RemoveChild(videoNode);
        }
        videoNode = VideoNode::GetOrCreateVideoNode(
            V2::VIDEO_ETS_TAG, nodeId,
            [videoControllerAsync]() { return AceType::MakeRefPtr<VideoStateMachinePattern>(videoControllerAsync); });
        CHECK_NULL_VOID(videoNode);
    }

    auto videoFocusHub = videoNode->GetFocusHub();
    if (videoFocusHub) {
        videoFocusHub->SetIsFocusUnit(true);
    }
    stack->Push(videoNode);
    bool hasPreviewImageNode = videoNode->HasPreviewImageNode();
    bool hasControllerRowNode = videoNode->HasControllerRowNode();
    bool hasMediaColumnNode = videoNode->HasMediaColumnNode();
    if (!hasMediaColumnNode) {
        auto mediaColumnId = videoNode->GetMediaColumnId();
        ACE_UINODE_TRACE(nodeId);
        auto mediaColumNode = FrameNode::GetOrCreateFrameNode(
            V2::COLUMN_ETS_TAG, mediaColumnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        CHECK_NULL_VOID(mediaColumNode);
        videoNode->AddChild(mediaColumNode);
    }
    if (!hasPreviewImageNode) {
        auto previewImageId = videoNode->GetPreviewImageId();
        ACE_UINODE_TRACE(nodeId);
        auto previewImageNode = FrameNode::GetOrCreateFrameNode(
            V2::IMAGE_ETS_TAG, previewImageId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
        CHECK_NULL_VOID(previewImageNode);
        videoNode->AddChild(previewImageNode);
    }
    if (!hasControllerRowNode) {
        auto controllerRowId = videoNode->GetControllerRowId();
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto controllerRowNode = CreateControlBarFromPattern(frameNode, controllerRowId);
        CHECK_NULL_VOID(controllerRowNode);
        videoNode->AddChild(controllerRowNode);
    }
}

void VideoModelNG::SetSrc(const std::string& src, const std::string& bundleName, const std::string& moduleName)
{
    VideoSourceInfo videoSrcInfo;
    videoSrcInfo.src_ = src;
    videoSrcInfo.bundleName_ = bundleName;
    videoSrcInfo.moduleName_ = moduleName;
    ACE_UPDATE_LAYOUT_PROPERTY(VideoLayoutProperty, VideoSource, videoSrcInfo);
}

void VideoModelNG::SetShowFirstFrame(bool showFirstFrame)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->UpdateShowFirstFrame(showFirstFrame);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->UpdateShowFirstFrame(showFirstFrame);
}

void VideoModelNG::SetProgressRate(double progressRate)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->UpdateProgressRate(progressRate);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->UpdateProgressRate(progressRate);
}

void VideoModelNG::SetPosterSourceInfo(const std::string& posterUrl, const std::string &bundleName,
    const std::string &moduleName)
{
    ImageSourceInfo posterSourceInfo(posterUrl, bundleName, moduleName);
    ACE_UPDATE_LAYOUT_PROPERTY(VideoLayoutProperty, PosterImageInfo, posterSourceInfo);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->UpdateShowImagePreview(!posterUrl.empty());
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->UpdateShowImagePreview(!posterUrl.empty());
}

void VideoModelNG::SetPosterSourceByPixelMap(RefPtr<PixelMap>& pixMap)
{
    ImageSourceInfo posterSourceInfo(pixMap);
    ACE_UPDATE_LAYOUT_PROPERTY(VideoLayoutProperty, PosterImageInfo, posterSourceInfo);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->UpdateShowImagePreview(pixMap);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->UpdateShowImagePreview(pixMap);
}

void VideoModelNG::SetMuted(bool muted)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->UpdateMuted(muted);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->UpdateMuted(muted);
}

void VideoModelNG::SetAutoPlay(bool autoPlay)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->UpdateAutoPlay(autoPlay);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->UpdateAutoPlay(autoPlay);
}

void VideoModelNG::SetControls(bool controls)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    UpdateControllerBar(frameNode, controls);
}

void VideoModelNG::SetObjectFit(ImageFit objectFit)
{
    ACE_UPDATE_LAYOUT_PROPERTY(VideoLayoutProperty, ObjectFit, objectFit);
}

void VideoModelNG::SetLoop(bool loop)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->UpdateLoop(loop);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->UpdateLoop(loop);
}

void VideoModelNG::SetSurfaceBackgroundColor(Color color)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->SetSurfaceBackgroundColor(color);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->SetSurfaceBackgroundColor(color);
}

void VideoModelNG::SetShortcutKeyEnabled(bool isEnableShortcutKey)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->SetShortcutKeyEnabled(isEnableShortcutKey);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->SetShortcutKeyEnabled(isEnableShortcutKey);
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

void VideoModelNG::SetOnStop(VideoEventFunc&& onStop)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStop(std::move(onStop));
}

void VideoModelNG::SetOnFullScreenChange(VideoEventFunc&& onFullScreenChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFullScreenChange(std::move(onFullScreenChange));
}

void VideoModelNG::SetAutoPlay(FrameNode* frameNode, bool autoPlay)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->UpdateAutoPlay(autoPlay);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->UpdateAutoPlay(autoPlay);
}

void VideoModelNG::SetControls(FrameNode* frameNode, bool controls)
{
    UpdateControllerBar(frameNode, controls);
}

void VideoModelNG::SetObjectFit(FrameNode* frameNode, ImageFit objectFit)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(VideoLayoutProperty, ObjectFit, objectFit, frameNode);
}

void VideoModelNG::SetMuted(FrameNode* frameNode, bool muted)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->UpdateMuted(muted);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->UpdateMuted(muted);
}

void VideoModelNG::SetSurfaceBackgroundColor(FrameNode* frameNode, Color color)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->SetSurfaceBackgroundColor(color);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->SetSurfaceBackgroundColor(color);
}

void VideoModelNG::SetLoop(FrameNode* frameNode, bool loop)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->UpdateLoop(loop);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->UpdateLoop(loop);
}

void VideoModelNG::SetShortcutKeyEnabled(FrameNode* frameNode, bool isEnableShortcutKey)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->SetShortcutKeyEnabled(isEnableShortcutKey);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->SetShortcutKeyEnabled(isEnableShortcutKey);
}

void VideoModelNG::EnableAnalyzer(bool enable)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->EnableAnalyzer(enable);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->EnableAnalyzer(enable);
}

void VideoModelNG::SetImageAnalyzerConfig(void* config)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->SetImageAnalyzerConfig(config);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->SetImageAnalyzerConfig(config);
}

void VideoModelNG::SetImageAIOptions(void *options)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->SetImageAIOptions(options);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->SetImageAIOptions(options);
}

void VideoModelNG::SetContentTransition(ContentTransitionType contentTransition)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->SetContentTransition(contentTransition);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->SetContentTransition(contentTransition);
}

void VideoModelNG::SetOnStart(FrameNode* frameNode, VideoEventFunc&& onStart)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStart(std::move(onStart));
}

void VideoModelNG::SetOnPause(FrameNode* frameNode, VideoEventFunc&& onPause)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPause(std::move(onPause));
}

void VideoModelNG::SetOnFinish(FrameNode* frameNode, VideoEventFunc&& onFinish)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFinish(std::move(onFinish));
}

void VideoModelNG::SetOnError(FrameNode* frameNode, VideoEventFunc&& onError)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnError(std::move(onError));
}

void VideoModelNG::SetOnPrepared(FrameNode* frameNode, VideoEventFunc&& onPrepared)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPrepared(std::move(onPrepared));
}

void VideoModelNG::SetOnSeeking(FrameNode* frameNode, VideoEventFunc&& onSeeking)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSeeking(std::move(onSeeking));
}

void VideoModelNG::SetOnSeeked(FrameNode* frameNode, VideoEventFunc&& onSeeked)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSeeked(std::move(onSeeked));
}

void VideoModelNG::SetOnUpdate(FrameNode* frameNode, VideoEventFunc&& onUpdate)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnUpdate(std::move(onUpdate));
}

void VideoModelNG::SetOnFullScreenChange(FrameNode* frameNode, VideoEventFunc&& onFullScreenChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFullScreenChange(std::move(onFullScreenChange));
}

void VideoModelNG::SetOnStop(FrameNode* frameNode, VideoEventFunc&& onStop)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStop(std::move(onStop));
}

void VideoModelNG::EnableAnalyzer(FrameNode* frameNode, bool enable)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->EnableAnalyzer(enable);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->EnableAnalyzer(enable);
}

void VideoModelNG::SetImageAnalyzerConfig(FrameNode* frameNode, void* config)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        stateMachinePattern->SetImageAnalyzerConfig(config);
        return;
    }
    auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
    CHECK_NULL_VOID(videoPattern);
    videoPattern->SetImageAnalyzerConfig(config);
}

} // namespace OHOS::Ace::NG