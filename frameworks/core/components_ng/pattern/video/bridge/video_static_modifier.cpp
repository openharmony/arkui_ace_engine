/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <algorithm>

#include "base/utils/string_utils.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/video/video_model_ng.h"
#include "core/components_ng/pattern/video/video_model_static.h"
#include "core/components_ng/pattern/video/video_node.h"
#include "core/components_ng/pattern/video/video_state_machine_pattern.h"
#include "core/interfaces/native/implementation/content_transition_effect_peer_impl.h"
#include "core/interfaces/native/implementation/video_controller_async_peer_impl.h"
#include "core/interfaces/native/implementation/video_controller_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/color_metrics_peer.h"
#if defined(PREVIEW)
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/interfaces/native/utility/preview_placeholder.h"
#endif
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
struct VideoOptions {
    std::string src;
    std::string bundleNameSrc;
    std::string moduleNameSrc;
    double currentProgressRate;
    ImageSourceInfo previewSourceInfo;
    RefPtr<VideoControllerV2> videoController;
    RefPtr<VideoControllerAsync> videoControllerAsync;
    bool showFirstFrame;
    ContentTransitionType contentTransitionType;
};

Ark_BusinessErrorInterface_Void ParseVideoBusinessError(const std::string& param)
{
    auto code = Converter::ArkValue<Ark_Int32>(0);
    auto name = Converter::ArkValue<Ark_String>(std::string(""));
    auto message = Converter::ArkValue<Ark_String>(std::string(""));
    auto stack = Converter::ArkValue<Opt_String>(std::nullopt);
    auto data = JsonUtil::ParseJsonString(param);
    if (data && !data->IsNull()) {
        code = Converter::ArkValue<Ark_Int32>(data->GetInt("code"));
        name = Converter::ArkValue<Ark_String>(data->GetString("name"));
        message = Converter::ArkValue<Ark_String>(data->GetString("message"));
    }
    return {
        .name = name,
        .message = message,
        .stack = stack,
        .code = code,
    };
}
} // OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
namespace {
constexpr float VALID_SPEEDS[] = { 0.125, 0.25, 0.50, 0.75, 1.00, 1.25, 1.50, 1.75, 2.00, 3.00 };

bool IsValidSpeed(float speed)
{
    return std::find(std::begin(VALID_SPEEDS), std::end(VALID_SPEEDS), speed) != std::end(VALID_SPEEDS);
}

std::optional<float> ParsePlaybackSpeed(const Ark_PlaybackSpeed& src)
{
    switch (src) {
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_0_75_X: return 0.75f;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_25_X: return 1.25f;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_75_X: return 1.75f;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_2_00_X: return 2.0f;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_00_X: return 1.0f;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_0_50_X: return 0.5f;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_50_X: return 1.5f;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_3_00_X: return 3.0f;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_0_25_X: return 0.25f;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_0_125_X: return 0.125f;
        default:
            LOGE("Unexpected enum value in Ark_PlaybackSpeed: %{public}d", src);
            return std::nullopt;
    }
}

std::optional<float> ParseCurrentProgressRate(const Ark_Union_F64_String_PlaybackSpeed& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0:
            return static_cast<float>(src.value0);
        case SELECTOR_ID_1: {
            auto value = Converter::Convert<std::string>(src.value1);
            double result = 0.0;
            if (StringUtils::StringToDouble(value, result)) {
                return static_cast<float>(result);
            }
            return std::nullopt;
        }
        case SELECTOR_ID_2:
            return ParsePlaybackSpeed(src.value2);
        default:
            LOGE("Unexpected currentProgressRate selector: %{public}d", src.selector);
            return std::nullopt;
    }
}

void ParsePosterOptionsConvert(
    const Opt_PosterOptions& posterOptions, bool& showFirstFrame, ContentTransitionType& contentTransitionType)
{
    showFirstFrame = false;
    if (posterOptions.tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    if (posterOptions.value.showFirstFrame.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        showFirstFrame = Converter::Convert<bool>(posterOptions.value.showFirstFrame.value);
    }
    auto optValue = Converter::GetOptPtr(&posterOptions.value.contentTransitionEffect);
    if (optValue.has_value()) {
        auto* peer = optValue.value();
        if (peer) {
            contentTransitionType = peer->type_;
        }
    }
}

void ParseVideoControllers(const Ark_VideoOptions& src, VideoOptions& options)
{
    auto asyncPeerPtrOpt = Converter::OptConvert<Ark_VideoControllerAsync>(src.controllerAsync);
    if (asyncPeerPtrOpt) {
        auto asyncPeerImplPtr = asyncPeerPtrOpt.value();
        if (asyncPeerImplPtr) {
            asyncPeerImplPtr->SetInstanceId(OHOS::Ace::Container::CurrentId());
            options.videoControllerAsync = asyncPeerImplPtr->GetController();
        }
    }
    if (!options.videoControllerAsync) {
        auto abstPeerPtrOpt = Converter::OptConvert<Ark_VideoController>(src.controller);
        if (abstPeerPtrOpt) {
            auto peerImplPtr = abstPeerPtrOpt.value();
            if (peerImplPtr) {
                peerImplPtr->SetInstanceId(OHOS::Ace::Container::CurrentId());
                options.videoController = peerImplPtr->GetController();
            }
        }
    }
}
} // namespace

template<>
VideoOptions Convert(const Ark_VideoOptions& src)
{
    VideoOptions options{};

    // src
    auto sourceInfo = Converter::OptConvert<ImageSourceInfo>(src.src);
    if (sourceInfo) {
        options.src = sourceInfo.value().GetSrc();
        options.moduleNameSrc = sourceInfo.value().GetModuleName();
        options.bundleNameSrc = sourceInfo.value().GetBundleName();
    }

    options.currentProgressRate = 1.0;
    // currentProgressRate
    auto currentProgressRateValue = Converter::GetOpt(src.currentProgressRate);
    if (currentProgressRateValue) {
        auto currentProgressRate =
            ParseCurrentProgressRate(*currentProgressRateValue).value_or(options.currentProgressRate);
        if ((currentProgressRateValue->selector == SELECTOR_ID_0) || IsValidSpeed(currentProgressRate)) {
            options.currentProgressRate = currentProgressRate;
        }
    }

    // previewUri
    options.previewSourceInfo = Converter::OptConvert<ImageSourceInfo>(src.previewUri)
        .value_or(ImageSourceInfo("", "", ""));

    // controllerAsync (priority over controller)
    ParseVideoControllers(src, options);

    // posterOptions
    ParsePosterOptionsConvert(src.posterOptions, options.showFirstFrame, options.contentTransitionType);
    return options;
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace VideoModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
#ifdef VIDEO_SUPPORTED
    auto frameNode = VideoModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
#elif defined(PREVIEW)
    auto frameNode = CreatePreviewPlaceholder(V2::VIDEO_ETS_TAG, id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
#else
    return {};
#endif // VIDEO_SUPPORTED
}
} // VideoModifier
namespace VideoInterfaceModifier {
namespace {
void ApplyVideoController(FrameNode* frameNode, const VideoOptions& options)
{
    auto currentPattern = frameNode->GetPattern();
    bool isCurrentAsync = AceType::InstanceOf<VideoStateMachinePattern>(currentPattern);
    auto videoNode = AceType::DynamicCast<VideoNode>(frameNode);
    if (options.videoControllerAsync && isCurrentAsync) {
        CHECK_NULL_VOID(videoNode);
        auto stateMachinePattern = AceType::DynamicCast<VideoStateMachinePattern>(currentPattern);
        if (stateMachinePattern) {
            stateMachinePattern->SetVideoControllerAsync(options.videoControllerAsync);
        }
        return;
    }
    if (options.videoControllerAsync) {
        CHECK_NULL_VOID(videoNode);
        auto oldControllerRow = videoNode->GetControllerRow();
        if (oldControllerRow) {
            videoNode->RemoveChild(oldControllerRow);
        }
        auto newPattern = AceType::MakeRefPtr<VideoStateMachinePattern>(options.videoControllerAsync);
        videoNode->ReplacePattern(newPattern);
        auto controllerRowNode = newPattern->CreateControlBar(-1);
        if (controllerRowNode) {
            videoNode->AddChild(controllerRowNode);
        }
        return;
    }
    if (!videoNode || !isCurrentAsync) {
        if (options.videoController) {
            VideoModelStatic::SetVideoController(frameNode, options.videoController);
        }
        return;
    }
    auto oldControllerRow = videoNode->GetControllerRow();
    if (oldControllerRow) {
        videoNode->RemoveChild(oldControllerRow);
    }
    auto oldPattern = AceType::DynamicCast<VideoStateMachinePattern>(currentPattern);
    if (oldPattern) {
        oldPattern->OnControllerDestroyed();
    }
    auto newPattern = VideoModelStatic::CreateVideoStaticPattern(options.videoController);
    videoNode->ReplacePattern(newPattern);
    auto videoPattern = AceType::DynamicCast<VideoPattern>(newPattern);
    CHECK_NULL_VOID(videoPattern);
    auto controllerRowNode = videoPattern->CreateControlBar(-1);
    if (controllerRowNode) {
        videoNode->AddChild(controllerRowNode);
    }
}
} // namespace
void SetVideoOptionsImpl(Ark_NativePointer node,
                         const Ark_VideoOptions* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::Convert<VideoOptions>(*value);

    ApplyVideoController(frameNode, options);

    VideoModelStatic::SetSrc(frameNode, options.src, options.bundleNameSrc, options.moduleNameSrc);
    VideoModelStatic::SetProgressRate(frameNode, options.currentProgressRate);
    VideoModelStatic::SetPosterSourceInfo(frameNode, options.previewSourceInfo);
    VideoModelStatic::SetShowFirstFrame(frameNode, options.showFirstFrame);
    VideoModelStatic::SetContentTransition(frameNode, options.contentTransitionType);
}
} // VideoInterfaceModifier
namespace VideoAttributeModifier {
void SetMutedImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        VideoModelNG::SetMuted(frameNode, false);
        return;
    }
    VideoModelNG::SetMuted(frameNode, *convValue);
}
void SetAutoPlayImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        VideoModelNG::SetAutoPlay(frameNode, false);
        return;
    }
    VideoModelNG::SetAutoPlay(frameNode, *convValue);
}
void SetControlsImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        VideoModelNG::SetControls(frameNode, true);
        return;
    }
    VideoModelNG::SetControls(frameNode, *convValue);
}
void SetLoopImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        VideoModelNG::SetLoop(frameNode, false);
        return;
    }
    VideoModelNG::SetLoop(frameNode, *convValue);
}
void SetObjectFitImpl(Ark_NativePointer node,
                      const Opt_ImageFit* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelStatic::SetObjectFit(frameNode, Converter::OptConvertPtr<ImageFit>(value));
}
void SetOnStartImpl(Ark_NativePointer node,
                    const Opt_VoidCallback* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        VideoModelStatic::SetOnStart(frameNode, nullptr);
        return;
    }
    auto onStart = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
#ifndef ACE_UNITTEST
        CHECK_NULL_VOID(CallbackHelper<VoidCallback>::GetVMContext());
#endif
        arkCallback.InvokeSync();
    };
    VideoModelStatic::SetOnStart(frameNode, onStart);
}
void SetOnPauseImpl(Ark_NativePointer node,
                    const Opt_VoidCallback* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        VideoModelStatic::SetOnPause(frameNode, nullptr);
        return;
    }
    auto onPause = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
#ifndef ACE_UNITTEST
        CHECK_NULL_VOID(CallbackHelper<VoidCallback>::GetVMContext());
#endif
        arkCallback.InvokeSync();
    };
    VideoModelStatic::SetOnPause(frameNode, onPause);
}
void SetOnFinishImpl(Ark_NativePointer node,
                     const Opt_VoidCallback* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        VideoModelStatic::SetOnFinish(frameNode, nullptr);
        return;
    }
    auto onFinish = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
#ifndef ACE_UNITTEST
        CHECK_NULL_VOID(CallbackHelper<VoidCallback>::GetVMContext());
#endif
        arkCallback.InvokeSync();
    };
    VideoModelStatic::SetOnFinish(frameNode, onFinish);
}
void SetOnFullscreenChangeImpl(Ark_NativePointer node,
                               const Opt_Callback_FullscreenInfo_Void* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        VideoModelStatic::SetOnFullScreenChange(frameNode, nullptr);
        return;
    }
    auto onFullscreenChange = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
#ifndef ACE_UNITTEST
        CHECK_NULL_VOID(CallbackHelper<Callback_FullscreenInfo_Void>::GetVMContext());
#endif
        auto data = JsonUtil::ParseJsonString(param);
        CHECK_NULL_VOID(data);
        auto fullscreen = data->GetValue("fullscreen")->GetBool();
        Ark_FullscreenInfo event = {
            .fullscreen = Converter::ArkValue<Ark_Boolean>(fullscreen)
        };
        arkCallback.InvokeSync(event);
    };
    VideoModelStatic::SetOnFullScreenChange(frameNode, onFullscreenChange);
}
void SetOnPreparedImpl(Ark_NativePointer node,
                       const Opt_Callback_PreparedInfo_Void* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        VideoModelStatic::SetOnPrepared(frameNode, nullptr);
        return;
    }
    auto onPrepared = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
#ifndef ACE_UNITTEST
        CHECK_NULL_VOID(CallbackHelper<Callback_PreparedInfo_Void>::GetVMContext());
#endif
        auto data = JsonUtil::ParseJsonString(param);
        CHECK_NULL_VOID(data);
        auto duration = data->GetValue("duration")->GetDouble();
        Ark_PreparedInfo event = {
            .duration = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(duration))
        };
        arkCallback.InvokeSync(event);
    };
    VideoModelStatic::SetOnPrepared(frameNode, onPrepared);
}
void SetOnSeekingImpl(Ark_NativePointer node,
                      const Opt_Callback_PlaybackInfo_Void* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        VideoModelStatic::SetOnSeeking(frameNode, nullptr);
        return;
    }
    auto onSeeking = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
#ifndef ACE_UNITTEST
        CHECK_NULL_VOID(CallbackHelper<Callback_PlaybackInfo_Void>::GetVMContext());
#endif
        auto data = JsonUtil::ParseJsonString(param);
        auto time = data->GetValue("time")->GetDouble();
        Ark_PlaybackInfo event = {
            .time = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(time))
        };
        arkCallback.InvokeSync(event);
    };
    VideoModelStatic::SetOnSeeking(frameNode, onSeeking);
}
void SetOnSeekedImpl(Ark_NativePointer node,
                     const Opt_Callback_PlaybackInfo_Void* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        VideoModelStatic::SetOnSeeked(frameNode, nullptr);
        return;
    }
    auto onSeeked = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
#ifndef ACE_UNITTEST
        CHECK_NULL_VOID(CallbackHelper<Callback_PlaybackInfo_Void>::GetVMContext());
#endif
        auto data = JsonUtil::ParseJsonString(param);
        auto time = data->GetValue("time")->GetDouble();
        Ark_PlaybackInfo event = {
            .time = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(time))
        };
        arkCallback.InvokeSync(event);
    };
    VideoModelStatic::SetOnSeeked(frameNode, onSeeked);
}
void SetOnUpdateImpl(Ark_NativePointer node,
                     const Opt_Callback_PlaybackInfo_Void* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        VideoModelStatic::SetOnUpdate(frameNode, nullptr);
        return;
    }
    auto onUpdate = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
#ifndef ACE_UNITTEST
        CHECK_NULL_VOID(CallbackHelper<Callback_PlaybackInfo_Void>::GetVMContext());
#endif
        auto data = JsonUtil::ParseJsonString(param);
        auto time = data->GetValue("time")->GetDouble();
        Ark_PlaybackInfo event = {
            .time = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(time))
        };
        arkCallback.InvokeSync(event);
    };
    VideoModelStatic::SetOnUpdate(frameNode, onUpdate);
}
void SetOnErrorImpl(Ark_NativePointer node,
                    const Opt_Union_VoidCallback_ErrorCallback_BusinessErrorInterface_Void* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        VideoModelStatic::SetOnError(frameNode, nullptr);
        return;
    }
    Converter::VisitUnion(optValue.value(),
        [frameNode](const VoidCallback& src) {
                auto onError = [arkCallback = CallbackHelper(src)](const std::string& param) {
#ifndef ACE_UNITTEST
                CHECK_NULL_VOID(CallbackHelper<VoidCallback>::GetVMContext());
#endif // ACE_UNITTEST
                arkCallback.InvokeSync();
            };
            VideoModelStatic::SetOnError(frameNode, onError);
        },
        [frameNode](const ErrorCallback_BusinessErrorInterface_Void& src) {
            auto onError = [arkCallback = CallbackHelper(src)](const std::string& param) {
#ifndef ACE_UNITTEST
                CHECK_NULL_VOID(CallbackHelper<ErrorCallback_BusinessErrorInterface_Void>::GetVMContext());
#endif // ACE_UNITTEST
                auto error = ParseVideoBusinessError(param);
                arkCallback.InvokeSync(error);
            };
            VideoModelStatic::SetOnError(frameNode, onError);
        },
        [] {});
}
void SetOnStopImpl(Ark_NativePointer node,
                   const Opt_VoidCallback* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        VideoModelStatic::SetOnStop(frameNode, nullptr);
        return;
    }
    auto onStop = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
#ifndef ACE_UNITTEST
        CHECK_NULL_VOID(CallbackHelper<VoidCallback>::GetVMContext());
#endif
        arkCallback.InvokeSync();
    };
    VideoModelStatic::SetOnStop(frameNode, onStop);
}
void SetEnableAnalyzerImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        VideoModelStatic::EnableAnalyzer(frameNode, false);
        return;
    }
    VideoModelStatic::EnableAnalyzer(frameNode, *convValue);
}
void SetAnalyzerConfigImpl(Ark_NativePointer node,
                           const Opt_ImageAnalyzerConfig* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::GetOptPtr(value);
    CHECK_NULL_VOID(optValue);
    VideoModelNG::SetImageAnalyzerConfig(frameNode, reinterpret_cast<void*>(optValue->types.array));
}
void SetSurfaceBackgroundColorImpl(Ark_NativePointer node,
                                   const Opt_ColorMetricsExt* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto colorValue = Converter::OptConvertPtr<Color>(value);
    auto color = colorValue.value_or(Color::BLACK);
    VideoModelNG::SetSurfaceBackgroundColor(frameNode, (color == Color::TRANSPARENT ? color : Color::BLACK));
}
void SetEnableShortcutKeyImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
#if defined(PREVIEW) && !defined(VIDEO_SUPPORTED)
    return;
#endif
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        VideoModelNG::SetShortcutKeyEnabled(frameNode, false);
        return;
    }
    VideoModelNG::SetShortcutKeyEnabled(frameNode, *convValue);
}
} // VideoAttributeModifier
const GENERATED_ArkUIVideoModifier* GetVideoStaticModifier()
{
    static const GENERATED_ArkUIVideoModifier ArkUIVideoModifierImpl {
        VideoModifier::ConstructImpl,
        VideoInterfaceModifier::SetVideoOptionsImpl,
        VideoAttributeModifier::SetMutedImpl,
        VideoAttributeModifier::SetAutoPlayImpl,
        VideoAttributeModifier::SetControlsImpl,
        VideoAttributeModifier::SetLoopImpl,
        VideoAttributeModifier::SetObjectFitImpl,
        VideoAttributeModifier::SetOnStartImpl,
        VideoAttributeModifier::SetOnPauseImpl,
        VideoAttributeModifier::SetOnFinishImpl,
        VideoAttributeModifier::SetOnFullscreenChangeImpl,
        VideoAttributeModifier::SetOnPreparedImpl,
        VideoAttributeModifier::SetOnSeekingImpl,
        VideoAttributeModifier::SetOnSeekedImpl,
        VideoAttributeModifier::SetOnUpdateImpl,
        VideoAttributeModifier::SetOnErrorImpl,
        VideoAttributeModifier::SetOnStopImpl,
        VideoAttributeModifier::SetEnableAnalyzerImpl,
        VideoAttributeModifier::SetAnalyzerConfigImpl,
        VideoAttributeModifier::SetEnableShortcutKeyImpl,
        VideoAttributeModifier::SetSurfaceBackgroundColorImpl,
    };
    return &ArkUIVideoModifierImpl;
}

}
