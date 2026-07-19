/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/video_modifier.h"

#include "core/common/container.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/video/bridge/video_controller_async_custom_modifier.h"
#include "core/components_ng/pattern/video/bridge/video_create_controller_param.h"
#include "core/components_ng/pattern/video/video_controller_async.h"
#include "core/components_ng/pattern/video/video_model_ng.h"

#ifndef CROSS_PLATFORM
namespace OHOS::Ace {
VideoModel* GetVideoModelImpl()
{
    return VideoModel::GetInstance();
}

namespace {
ViewAbstractModel* GetVideoViewAbstractModelImpl()
{
    return ViewAbstractModel::GetInstance();
}
} // namespace
} // namespace OHOS::Ace
#endif

namespace OHOS::Ace::NG {
constexpr ArkUI_Bool DEFAULT_CONTROLS_VALUE = true;
constexpr ArkUI_Bool DEFAULT_LOOP = false;
constexpr ArkUI_Bool DEFAULT_MUTED = false;
constexpr ImageFit DEFAULT_OBJECT_FIT = ImageFit::COVER;

namespace {
FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}
} // namespace

void CreateModel(void* controller)
{
    if (controller == nullptr) {
        VideoModelNG::CreateModelNG(RefPtr<VideoControllerV2>());
        return;
    }
    auto* createParam = reinterpret_cast<VideoCreateControllerParam*>(controller);
    switch (createParam->type) {
        case VideoCreateControllerType::ASYNC:
            VideoModelNG::CreateModelNG(createParam->controllerAsync);
            return;
        case VideoCreateControllerType::SYNC:
            VideoModelNG::CreateModelNG(createParam->controller);
            return;
        case VideoCreateControllerType::NONE:
        default:
            VideoModelNG::CreateModelNG(RefPtr<VideoControllerV2>());
            return;
    }
}

void SetSrc(ArkUI_CharPtr src, ArkUI_CharPtr bundleName, ArkUI_CharPtr moduleName)
{
    auto* frameNode = GetFrameNode(nullptr);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetSrc(frameNode, src ? src : "", bundleName ? bundleName : "", moduleName ? moduleName : "");
}

void SetShowFirstFrame(ArkUI_Bool showFirstFrame)
{
    auto* frameNode = GetFrameNode(nullptr);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetShowFirstFrame(frameNode, showFirstFrame);
}

void SetProgressRate(ArkUI_Float64 progressRate)
{
    auto* frameNode = GetFrameNode(nullptr);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetProgressRate(frameNode, progressRate);
}

void SetImageAIOptions(void* options)
{
    auto* frameNode = GetFrameNode(nullptr);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetImageAIOptions(frameNode, options);
}

void SetNodeImageAIOptions(ArkUINodeHandle node, void* options)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetImageAIOptions(frameNode, options);
}

void SetPosterSourceInfo(ArkUI_CharPtr posterUrl, ArkUI_CharPtr bundleName, ArkUI_CharPtr moduleName)
{
    auto* frameNode = GetFrameNode(nullptr);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetPosterSourceInfo(
        frameNode, posterUrl ? posterUrl : "", bundleName ? bundleName : "", moduleName ? moduleName : "");
}

void SetPosterSourceByPixelMap(void* pixelMap)
{
    CHECK_NULL_VOID(pixelMap);
    auto* frameNode = GetFrameNode(nullptr);
    CHECK_NULL_VOID(frameNode);
    auto* posterPixelMap = reinterpret_cast<RefPtr<PixelMap>*>(pixelMap);
    VideoModelNG::SetPosterSourceByPixelMap(frameNode, *posterPixelMap);
}

void SetAutoPlay(ArkUINodeHandle node, ArkUI_Uint32 autoPlay)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetAutoPlay(frameNode, static_cast<ArkUI_Bool>(autoPlay));
}

void ResetAutoPlay(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetAutoPlay(frameNode, false);
}

void SetVideoObjectFit(ArkUINodeHandle node, ArkUI_Int32 objectFit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetObjectFit(frameNode, static_cast<ImageFit>(objectFit));
}

void ResetVideoObjectFit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetObjectFit(frameNode, DEFAULT_OBJECT_FIT);
}

void SetVideoControls(ArkUINodeHandle node, ArkUI_Uint32 controlsValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetControls(frameNode, static_cast<ArkUI_Bool>(controlsValue));
}

void ResetVideoControls(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetControls(frameNode, DEFAULT_CONTROLS_VALUE);
}

void SetVideoLoop(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetLoop(frameNode, static_cast<ArkUI_Bool>(value));
}

void ResetVideoLoop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetLoop(frameNode, DEFAULT_LOOP);
}

void SetVideoMuted(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetMuted(frameNode, static_cast<ArkUI_Bool>(value));
}

void ResetVideoMuted(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetMuted(frameNode, DEFAULT_MUTED);
}

void SetVideoOpacity(ArkUINodeHandle node, ArkUI_Float32 opacity)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if ((LessNotEqual(opacity, 0.0)) || opacity > 1) {
        opacity = 1.0f;
    }
    ViewAbstract::SetOpacity(frameNode, opacity);
}

void ResetVideoOpacity(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetOpacity(frameNode, 1.0f);
}

void SetVideoSurfaceBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Color backgroundColor = Color(color);
    if (backgroundColor != Color::TRANSPARENT) {
        backgroundColor = Color::BLACK;
    }

    VideoModelNG::SetSurfaceBackgroundColor(frameNode, backgroundColor);
}

void ResetVideoSurfaceBackgroundColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetSurfaceBackgroundColor(frameNode, Color::BLACK);
}

void SetVideoShortcutKeyEnabled(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetShortcutKeyEnabled(frameNode, static_cast<ArkUI_Bool>(value));
}

void ResetVideoShortcutKeyEnabled(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetShortcutKeyEnabled(frameNode, false);
}

void SetOnStart(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onStart = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        VideoModelNG::SetOnStart(frameNode, std::move(*onStart));
    } else {
        VideoModelNG::SetOnStart(frameNode, nullptr);
    }
}

void ResetOnStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetOnStart(frameNode, nullptr);
}

void SetOnPause(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onPause = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        VideoModelNG::SetOnPause(frameNode, std::move(*onPause));
    } else {
        VideoModelNG::SetOnPause(frameNode, nullptr);
    }
}

void ResetOnPause(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetOnPause(frameNode, nullptr);
}

void SetOnFinish(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onFinish = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        VideoModelNG::SetOnFinish(frameNode, std::move(*onFinish));
    } else {
        VideoModelNG::SetOnFinish(frameNode, nullptr);
    }
}

void ResetOnFinish(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetOnFinish(frameNode, nullptr);
}

void SetOnFullscreenChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onFullscreenChange = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        VideoModelNG::SetOnFullScreenChange(frameNode, std::move(*onFullscreenChange));
    } else {
        VideoModelNG::SetOnFullScreenChange(frameNode, nullptr);
    }
}

void ResetOnFullscreenChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetOnFullScreenChange(frameNode, nullptr);
}

void SetOnPrepared(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onPrepared = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        VideoModelNG::SetOnPrepared(frameNode, std::move(*onPrepared));
    } else {
        VideoModelNG::SetOnPrepared(frameNode, nullptr);
    }
}

void ResetOnPrepared(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetOnPrepared(frameNode, nullptr);
}

void SetOnSeeking(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSeeking = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        VideoModelNG::SetOnSeeking(frameNode, std::move(*onSeeking));
    } else {
        VideoModelNG::SetOnSeeking(frameNode, nullptr);
    }
}

void ResetOnSeeking(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetOnSeeking(frameNode, nullptr);
}

void SetOnSeeked(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSeeked = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        VideoModelNG::SetOnSeeked(frameNode, std::move(*onSeeked));
    } else {
        VideoModelNG::SetOnSeeked(frameNode, nullptr);
    }
}

void ResetOnSeeked(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetOnSeeked(frameNode, nullptr);
}

void SetOnUpdate(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onUpdate = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        VideoModelNG::SetOnUpdate(frameNode, std::move(*onUpdate));
    } else {
        VideoModelNG::SetOnUpdate(frameNode, nullptr);
    }
}

void ResetOnUpdate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetOnUpdate(frameNode, nullptr);
}

void SetOnError(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onError = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        VideoModelNG::SetOnError(frameNode, std::move(*onError));
    } else {
        VideoModelNG::SetOnError(frameNode, nullptr);
    }
}

void ResetOnError(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetOnError(frameNode, nullptr);
}
void SetOnStop(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onStop = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        VideoModelNG::SetOnStop(frameNode, std::move(*onStop));
    } else {
        VideoModelNG::SetOnStop(frameNode, nullptr);
    }
}

void ResetOnStop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetOnStop(frameNode, nullptr);
}

void SetEnableAnalyzer(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::EnableAnalyzer(frameNode, static_cast<bool>(value));
}

void ResetEnableAnalyzer(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::EnableAnalyzer(frameNode, false);
}

void SetAnalyzerConfig(ArkUINodeHandle node, void* config)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetImageAnalyzerConfig(frameNode, config);
}

void ResetAnalyzerConfig(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetImageAnalyzerConfig(frameNode, nullptr);
}

#ifndef CROSS_PLATFORM
void CreateModelImpl(void* controller)
{
    if (controller == nullptr) {
        GetVideoModelImpl()->Create(RefPtr<VideoControllerV2>());
        return;
    }
    auto* createParam = reinterpret_cast<VideoCreateControllerParam*>(controller);
    switch (createParam->type) {
        case VideoCreateControllerType::SYNC:
            GetVideoModelImpl()->Create(createParam->controller);
            return;
        case VideoCreateControllerType::ASYNC:
            // Keep old-pipeline behavior aligned with base: async create has no compatible implementation.
            return;
        case VideoCreateControllerType::NONE:
        default:
            GetVideoModelImpl()->Create(RefPtr<VideoControllerV2>());
            return;
    }
}

void SetSrcImpl(ArkUI_CharPtr src, ArkUI_CharPtr bundleName, ArkUI_CharPtr moduleName)
{
    GetVideoModelImpl()->SetSrc(src ? src : "", bundleName ? bundleName : "", moduleName ? moduleName : "");
}

void SetShowFirstFrameImpl(ArkUI_Bool showFirstFrame) {}

void SetProgressRateImpl(ArkUI_Float64 progressRate)
{
    GetVideoModelImpl()->SetProgressRate(progressRate);
}

void SetImageAIOptionsImpl(void* options) {}

void SetPosterSourceInfoImpl(ArkUI_CharPtr posterUrl, ArkUI_CharPtr bundleName, ArkUI_CharPtr moduleName)
{
    GetVideoModelImpl()->SetPosterSourceInfo(
        posterUrl ? posterUrl : "", bundleName ? bundleName : "", moduleName ? moduleName : "");
}

void SetPosterSourceByPixelMapImpl(void* pixelMap)
{
    CHECK_NULL_VOID(pixelMap);
    auto* posterPixelMap = reinterpret_cast<RefPtr<PixelMap>*>(pixelMap);
    GetVideoModelImpl()->SetPosterSourceByPixelMap(*posterPixelMap);
}

void SetNodeImageAIOptionsImpl(ArkUINodeHandle node, void* options) {}

void SetAutoPlayImpl(ArkUINodeHandle node, ArkUI_Uint32 autoPlay)
{
    GetVideoModelImpl()->SetAutoPlay(static_cast<bool>(autoPlay));
}

void ResetAutoPlayImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetAutoPlay(false);
}

void SetVideoObjectFitImpl(ArkUINodeHandle node, ArkUI_Int32 objectFit)
{
    GetVideoModelImpl()->SetObjectFit(static_cast<ImageFit>(objectFit));
}

void ResetVideoObjectFitImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetObjectFit(DEFAULT_OBJECT_FIT);
}

void SetVideoControlsImpl(ArkUINodeHandle node, ArkUI_Uint32 controlsValue)
{
    GetVideoModelImpl()->SetControls(static_cast<bool>(controlsValue));
}

void ResetVideoControlsImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetControls(DEFAULT_CONTROLS_VALUE);
}

void SetVideoLoopImpl(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    GetVideoModelImpl()->SetLoop(static_cast<bool>(value));
}

void ResetVideoLoopImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetLoop(DEFAULT_LOOP);
}

void SetVideoMutedImpl(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    GetVideoModelImpl()->SetMuted(static_cast<bool>(value));
}

void ResetVideoMutedImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetMuted(DEFAULT_MUTED);
}

void SetVideoOpacityImpl(ArkUINodeHandle node, ArkUI_Float32 opacity)
{
    if ((LessNotEqual(opacity, 0.0)) || opacity > 1) {
        opacity = 1.0f;
    }
    GetVideoViewAbstractModelImpl()->SetOpacity(opacity);
}

void ResetVideoOpacityImpl(ArkUINodeHandle node)
{
    GetVideoViewAbstractModelImpl()->SetOpacity(1.0f);
}

void SetVideoSurfaceBackgroundColorImpl(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    Color backgroundColor = Color(color);
    if (backgroundColor != Color::TRANSPARENT) {
        backgroundColor = Color::BLACK;
    }

    GetVideoModelImpl()->SetSurfaceBackgroundColor(backgroundColor);
}

void ResetVideoSurfaceBackgroundColorImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetSurfaceBackgroundColor(Color::BLACK);
}

void SetVideoShortcutKeyEnabledImpl(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    GetVideoModelImpl()->SetShortcutKeyEnabled(static_cast<bool>(value));
}

void ResetVideoShortcutKeyEnabledImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetShortcutKeyEnabled(false);
}

void SetOnStartImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onStart = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        GetVideoModelImpl()->SetOnStart(std::move(*onStart));
    } else {
        GetVideoModelImpl()->SetOnStart(nullptr);
    }
}

void ResetOnStartImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetOnStart(nullptr);
}

void SetOnPauseImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onPause = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        GetVideoModelImpl()->SetOnPause(std::move(*onPause));
    } else {
        GetVideoModelImpl()->SetOnPause(nullptr);
    }
}

void ResetOnPauseImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetOnPause(nullptr);
}

void SetOnFinishImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onFinish = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        GetVideoModelImpl()->SetOnFinish(std::move(*onFinish));
    } else {
        GetVideoModelImpl()->SetOnFinish(nullptr);
    }
}

void ResetOnFinishImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetOnFinish(nullptr);
}

void SetOnFullscreenChangeImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onFullscreenChange = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        GetVideoModelImpl()->SetOnFullScreenChange(std::move(*onFullscreenChange));
    } else {
        GetVideoModelImpl()->SetOnFullScreenChange(nullptr);
    }
}

void ResetOnFullscreenChangeImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetOnFullScreenChange(nullptr);
}

void SetOnPreparedImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onPrepared = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        GetVideoModelImpl()->SetOnPrepared(std::move(*onPrepared));
    } else {
        GetVideoModelImpl()->SetOnPrepared(nullptr);
    }
}

void ResetOnPreparedImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetOnPrepared(nullptr);
}

void SetOnSeekingImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onSeeking = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        GetVideoModelImpl()->SetOnSeeking(std::move(*onSeeking));
    } else {
        GetVideoModelImpl()->SetOnSeeking(nullptr);
    }
}

void ResetOnSeekingImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetOnSeeking(nullptr);
}

void SetOnSeekedImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onSeeked = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        GetVideoModelImpl()->SetOnSeeked(std::move(*onSeeked));
    } else {
        GetVideoModelImpl()->SetOnSeeked(nullptr);
    }
}

void ResetOnSeekedImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetOnSeeked(nullptr);
}

void SetOnUpdateImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onUpdate = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        GetVideoModelImpl()->SetOnUpdate(std::move(*onUpdate));
    } else {
        GetVideoModelImpl()->SetOnUpdate(nullptr);
    }
}

void ResetOnUpdateImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetOnUpdate(nullptr);
}

void SetOnErrorImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onError = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        GetVideoModelImpl()->SetOnError(std::move(*onError));
    } else {
        GetVideoModelImpl()->SetOnError(nullptr);
    }
}

void ResetOnErrorImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetOnError(nullptr);
}

void SetOnStopImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onStop = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        GetVideoModelImpl()->SetOnStop(std::move(*onStop));
    } else {
        GetVideoModelImpl()->SetOnStop(nullptr);
    }
}

void ResetOnStopImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetOnStop(nullptr);
}

void SetEnableAnalyzerImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    GetVideoModelImpl()->EnableAnalyzer(static_cast<bool>(value));
}

void ResetEnableAnalyzerImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->EnableAnalyzer(false);
}

void SetAnalyzerConfigImpl(ArkUINodeHandle node, void* config)
{
    GetVideoModelImpl()->SetImageAnalyzerConfig(config);
}

void ResetAnalyzerConfigImpl(ArkUINodeHandle node)
{
    GetVideoModelImpl()->SetImageAnalyzerConfig(nullptr);
}
#endif

namespace NodeModifier {
const ArkUIVideoModifier* GetVideoDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIVideoModifier modifier = {
            .setAutoPlay = SetAutoPlayImpl,
            .resetAutoPlay = ResetAutoPlayImpl,
            .setVideoObjectFit = SetVideoObjectFitImpl,
            .resetVideoObjectFit = ResetVideoObjectFitImpl,
            .setVideoControls = SetVideoControlsImpl,
            .resetVideoControls = ResetVideoControlsImpl,
            .setVideoLoop = SetVideoLoopImpl,
            .resetVideoLoop = ResetVideoLoopImpl,
            .setVideoMuted = SetVideoMutedImpl,
            .resetVideoMuted = ResetVideoMutedImpl,
            .setVideoOpacity = SetVideoOpacityImpl,
            .resetVideoOpacity = ResetVideoOpacityImpl,
            .setVideoSurfaceBackgroundColor = SetVideoSurfaceBackgroundColorImpl,
            .resetVideoSurfaceBackgroundColor = ResetVideoSurfaceBackgroundColorImpl,
            .setVideoShortcutKeyEnabled = SetVideoShortcutKeyEnabledImpl,
            .resetVideoShortcutKeyEnabled = ResetVideoShortcutKeyEnabledImpl,
            .setOnStart = SetOnStartImpl,
            .resetOnStart = ResetOnStartImpl,
            .setOnPause = SetOnPauseImpl,
            .resetOnPause = ResetOnPauseImpl,
            .setOnFinish = SetOnFinishImpl,
            .resetOnFinish = ResetOnFinishImpl,
            .setOnFullscreenChange = SetOnFullscreenChangeImpl,
            .resetOnFullscreenChange = ResetOnFullscreenChangeImpl,
            .setOnPrepared = SetOnPreparedImpl,
            .resetOnPrepared = ResetOnPreparedImpl,
            .setOnSeeking = SetOnSeekingImpl,
            .resetOnSeeking = ResetOnSeekingImpl,
            .setOnSeeked = SetOnSeekedImpl,
            .resetOnSeeked = ResetOnSeekedImpl,
            .setOnUpdate = SetOnUpdateImpl,
            .resetOnUpdate = ResetOnUpdateImpl,
            .setOnError = SetOnErrorImpl,
            .resetOnError = ResetOnErrorImpl,
            .setOnStop = SetOnStopImpl,
            .resetOnStop = ResetOnStopImpl,
            .setEnableAnalyzer = SetEnableAnalyzerImpl,
            .resetEnableAnalyzer = ResetEnableAnalyzerImpl,
            .setAnalyzerConfig = SetAnalyzerConfigImpl,
            .resetAnalyzerConfig = ResetAnalyzerConfigImpl,
            .createModel = CreateModelImpl,
            .setSrc = SetSrcImpl,
            .setShowFirstFrame = SetShowFirstFrameImpl,
            .setProgressRate = SetProgressRateImpl,
            .setImageAIOptions = SetImageAIOptionsImpl,
            .setPosterSourceInfo = SetPosterSourceInfoImpl,
            .setPosterSourceByPixelMap = SetPosterSourceByPixelMapImpl,
            .setNodeImageAIOptions = SetNodeImageAIOptionsImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIVideoModifier modifier = {
        .setAutoPlay = SetAutoPlay,
        .resetAutoPlay = ResetAutoPlay,
        .setVideoObjectFit = SetVideoObjectFit,
        .resetVideoObjectFit = ResetVideoObjectFit,
        .setVideoControls = SetVideoControls,
        .resetVideoControls = ResetVideoControls,
        .setVideoLoop = SetVideoLoop,
        .resetVideoLoop = ResetVideoLoop,
        .setVideoMuted = SetVideoMuted,
        .resetVideoMuted = ResetVideoMuted,
        .setVideoOpacity = SetVideoOpacity,
        .resetVideoOpacity = ResetVideoOpacity,
        .setVideoSurfaceBackgroundColor = SetVideoSurfaceBackgroundColor,
        .resetVideoSurfaceBackgroundColor = ResetVideoSurfaceBackgroundColor,
        .setVideoShortcutKeyEnabled = SetVideoShortcutKeyEnabled,
        .resetVideoShortcutKeyEnabled = ResetVideoShortcutKeyEnabled,
        .setOnStart = SetOnStart,
        .resetOnStart = ResetOnStart,
        .setOnPause = SetOnPause,
        .resetOnPause = ResetOnPause,
        .setOnFinish = SetOnFinish,
        .resetOnFinish = ResetOnFinish,
        .setOnFullscreenChange = SetOnFullscreenChange,
        .resetOnFullscreenChange = ResetOnFullscreenChange,
        .setOnPrepared = SetOnPrepared,
        .resetOnPrepared = ResetOnPrepared,
        .setOnSeeking = SetOnSeeking,
        .resetOnSeeking = ResetOnSeeking,
        .setOnSeeked = SetOnSeeked,
        .resetOnSeeked = ResetOnSeeked,
        .setOnUpdate = SetOnUpdate,
        .resetOnUpdate = ResetOnUpdate,
        .setOnError = SetOnError,
        .resetOnError = ResetOnError,
        .setOnStop = SetOnStop,
        .resetOnStop = ResetOnStop,
        .setEnableAnalyzer = SetEnableAnalyzer,
        .resetEnableAnalyzer = ResetEnableAnalyzer,
        .setAnalyzerConfig = SetAnalyzerConfig,
        .resetAnalyzerConfig = ResetAnalyzerConfig,
        .createModel = CreateModel,
        .setSrc = SetSrc,
        .setShowFirstFrame = SetShowFirstFrame,
        .setProgressRate = SetProgressRate,
        .setImageAIOptions = SetImageAIOptions,
        .setPosterSourceInfo = SetPosterSourceInfo,
        .setPosterSourceByPixelMap = SetPosterSourceByPixelMap,
        .setNodeImageAIOptions = SetNodeImageAIOptions,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}


const CJUIVideoModifier* GetCJUIVideoDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIVideoModifier modifier = {
        .setAutoPlay = SetAutoPlay,
        .resetAutoPlay = ResetAutoPlay,
        .setVideoObjectFit = SetVideoObjectFit,
        .resetVideoObjectFit = ResetVideoObjectFit,
        .setVideoControls = SetVideoControls,
        .resetVideoControls = ResetVideoControls,
        .setVideoLoop = SetVideoLoop,
        .resetVideoLoop = ResetVideoLoop,
        .setVideoMuted = SetVideoMuted,
        .resetVideoMuted = ResetVideoMuted,
        .setVideoOpacity = SetVideoOpacity,
        .resetVideoOpacity = ResetVideoOpacity,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
