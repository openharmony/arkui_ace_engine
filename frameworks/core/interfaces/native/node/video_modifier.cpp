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
#include "core/interfaces/native/node/video_modifier.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/video/video_model_ng.h"

namespace OHOS::Ace::NG {
constexpr ArkUI_Bool DEFAULT_CONTROLS_VALUE = true;
constexpr ArkUI_Bool DEFAULT_LOOP = false;
constexpr ArkUI_Bool DEFAULT_MUTED = false;
constexpr ImageFit DEFAULT_OBJECT_FIT = ImageFit::COVER;

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

namespace NodeModifier {
const ArkUIVideoModifier* GetVideoModifier()
{
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
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIVideoModifier* GetCJUIVideoModifier()
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
