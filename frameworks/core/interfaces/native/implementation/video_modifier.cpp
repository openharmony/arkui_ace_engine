/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "base/utils/string_utils.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/video/video_model_ng.h"
#include "core/components_ng/pattern/video/video_model_static.h"
#include "core/interfaces/native/implementation/video_controller_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "color_metrics_peer.h"
#include "core/interfaces/native/generated/interface/ui_node_api.h"

namespace OHOS::Ace::NG {
struct VideoOptions {
    std::string src;
    std::string bundleNameSrc;
    std::string moduleNameSrc;
    double currentProgressRate;
    ImageSourceInfo previewSourceInfo;
    RefPtr<VideoControllerV2> videoController;
    bool showFirstFrame;
};
namespace {
const float SPEED_0_75_X = 0.75f;
const float SPEED_1_00_X = 1.0f;
const float SPEED_1_25_X = 1.25f;
const float SPEED_1_75_X = 1.75f;
const float SPEED_2_00_X = 2.0f;
float ConvertVideoPorgressRateNumber(const Ark_PlaybackSpeed& rate)
{
    switch (static_cast<int32_t>(rate)) {
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_0_75_X: return SPEED_0_75_X;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_00_X: return SPEED_1_00_X;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_25_X: return SPEED_1_25_X;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_75_X: return SPEED_1_75_X;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_2_00_X: return SPEED_2_00_X;
        default: return SPEED_1_00_X;
    }
}
}
} // OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<float>& dst, const Ark_PlaybackSpeed& src)
{
    switch (src) {
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_0_75_X: dst = 0.75f; break;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_25_X: dst = 1.25f; break;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_75_X: dst = 1.75f; break;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_2_00_X: dst = 2.0f; break;
        case ARK_PLAYBACK_SPEED_SPEED_FORWARD_1_00_X: dst = 1.0f; break;
        default: LOGE("Unexpected enum value in Ark_PlaybackSpeed: %{public}d", src);
    }
}

template<>
VideoOptions Convert(const Ark_VideoOptions& src)
{
    VideoOptions options;

    // src
    auto sourceInfo = Converter::OptConvert<ImageSourceInfo>(src.src);
    if (sourceInfo) {
        options.src = sourceInfo.value().GetSrc();
        options.moduleNameSrc = sourceInfo.value().GetModuleName();
        options.bundleNameSrc = sourceInfo.value().GetBundleName();
    }

    // currentProgressRate
    options.currentProgressRate = 1.0;

    if (src.currentProgressRate.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        Converter::VisitUnion(
            src.currentProgressRate.value,
            [&options](const Ark_Number& value) {
                options.currentProgressRate = Converter::Convert<float>(value);
            },
            [&options](const Ark_String& value) {
                auto rateString = Converter::Convert<std::string>(value);
                options.currentProgressRate = StringUtils::StringToDouble(rateString);
            },
            [&options](const Ark_PlaybackSpeed& value) {
                options.currentProgressRate = ConvertVideoPorgressRateNumber(value);
            },
            []() {});
    }

    // previewUri
    options.previewSourceInfo = Converter::OptConvert<ImageSourceInfo>(src.previewUri)
        .value_or(ImageSourceInfo("", "", ""));

    // controller
    auto abstPeerPtrOpt = Converter::OptConvert<Ark_VideoController>(src.controller);
    CHECK_NULL_RETURN(abstPeerPtrOpt, options);
    auto peerImplPtr = abstPeerPtrOpt.value();
    CHECK_NULL_RETURN(peerImplPtr, options);
    peerImplPtr->SetInstanceId(OHOS::Ace::Container::CurrentId());
    options.videoController = peerImplPtr->GetController();

    // posterOptions
    options.showFirstFrame = false;
    auto optPosterOptions = src.posterOptions;
    if (optPosterOptions.tag != InteropTag::INTEROP_TAG_UNDEFINED &&
        optPosterOptions.value.showFirstFrame.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        options.showFirstFrame = Converter::Convert<bool>(optPosterOptions.value.showFirstFrame.value);
    }
    return options;
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace VideoModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = VideoModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // VideoModifier
namespace VideoInterfaceModifier {
void SetVideoOptionsImpl(Ark_NativePointer node,
                         const Ark_VideoOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::Convert<VideoOptions>(*value);
    VideoModelStatic::SetSrc(frameNode, options.src, options.bundleNameSrc, options.moduleNameSrc);
    VideoModelStatic::SetProgressRate(frameNode, options.currentProgressRate);
    VideoModelStatic::SetPosterSourceInfo(frameNode, options.previewSourceInfo);
    VideoModelStatic::SetShowFirstFrame(frameNode, options.showFirstFrame);
    if (options.videoController) {
        VideoModelStatic::SetVideoController(frameNode, options.videoController);
    }
    LOGE("ARKOALA VideoInterface::SetVideoOptionsImpl -> imageAIOptions is not supported.");
}
} // VideoInterfaceModifier
namespace VideoAttributeModifier {
void MutedImpl(Ark_NativePointer node,
               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        VideoModelNG::SetMuted(frameNode, false);
        return;
    }
    VideoModelNG::SetMuted(frameNode, *convValue);
}
void AutoPlayImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        VideoModelNG::SetAutoPlay(frameNode, false);
        return;
    }
    VideoModelNG::SetAutoPlay(frameNode, *convValue);
}
void ControlsImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        VideoModelNG::SetControls(frameNode, true);
        return;
    }
    VideoModelNG::SetControls(frameNode, *convValue);
}
void LoopImpl(Ark_NativePointer node,
              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        VideoModelNG::SetLoop(frameNode, false);
        return;
    }
    VideoModelNG::SetLoop(frameNode, *convValue);
}
void ObjectFitImpl(Ark_NativePointer node,
                   const Opt_ImageFit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    VideoModelStatic::SetObjectFit(frameNode, Converter::OptConvert<ImageFit>(*value));
}
void OnStartImpl(Ark_NativePointer node,
                 const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onStart = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
        arkCallback.InvokeSync();
    };
    VideoModelStatic::SetOnStart(frameNode, onStart);
}
void OnPauseImpl(Ark_NativePointer node,
                 const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onPause = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
        arkCallback.InvokeSync();
    };
    VideoModelStatic::SetOnPause(frameNode, onPause);
}
void OnFinishImpl(Ark_NativePointer node,
                  const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onFinish = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
        arkCallback.InvokeSync();
    };
    VideoModelStatic::SetOnFinish(frameNode, onFinish);
}
void OnFullscreenChangeImpl(Ark_NativePointer node,
                            const Opt_Callback_FullscreenInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onFullscreenChange = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
        auto data = JsonUtil::ParseJsonString(param);
        auto fullscreen = data->GetValue("fullscreen")->GetBool();
        Ark_FullscreenInfo event = {
            .fullscreen = Converter::ArkValue<Ark_Boolean>(fullscreen)
        };
        arkCallback.InvokeSync(event);
    };
    VideoModelStatic::SetOnFullScreenChange(frameNode, onFullscreenChange);
}
void OnPreparedImpl(Ark_NativePointer node,
                    const Opt_Callback_PreparedInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onPrepared = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
        auto data = JsonUtil::ParseJsonString(param);
        auto duration = data->GetValue("duration")->GetDouble();
        Ark_PreparedInfo event = {
            .duration = Converter::ArkValue<Ark_Number>(static_cast<float>(duration))
        };
        arkCallback.InvokeSync(event);
    };
    VideoModelStatic::SetOnPrepared(frameNode, onPrepared);
}
void OnSeekingImpl(Ark_NativePointer node,
                   const Opt_Callback_PlaybackInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onSeeking = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
        auto data = JsonUtil::ParseJsonString(param);
        auto time = data->GetValue("time")->GetDouble();
        Ark_PlaybackInfo event = {
            .time = Converter::ArkValue<Ark_Number>(static_cast<float>(time))
        };
        arkCallback.InvokeSync(event);
    };
    VideoModelStatic::SetOnSeeking(frameNode, onSeeking);
}
void OnSeekedImpl(Ark_NativePointer node,
                  const Opt_Callback_PlaybackInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onSeeked = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
        auto data = JsonUtil::ParseJsonString(param);
        auto time = data->GetValue("time")->GetDouble();
        Ark_PlaybackInfo event = {
            .time = Converter::ArkValue<Ark_Number>(static_cast<float>(time))
        };
        arkCallback.InvokeSync(event);
    };
    VideoModelStatic::SetOnSeeked(frameNode, onSeeked);
}
void OnUpdateImpl(Ark_NativePointer node,
                  const Opt_Callback_PlaybackInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onUpdate = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
        auto data = JsonUtil::ParseJsonString(param);
        auto time = data->GetValue("time")->GetDouble();
        Ark_PlaybackInfo event = {
            .time = Converter::ArkValue<Ark_Number>(static_cast<float>(time))
        };
        arkCallback.InvokeSync(event);
    };
    VideoModelStatic::SetOnUpdate(frameNode, onUpdate);
}
void OnErrorImpl(Ark_NativePointer node,
                 const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onError = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
        arkCallback.InvokeSync();
    };
    VideoModelStatic::SetOnError(frameNode, onError);
}
void OnStopImpl(Ark_NativePointer node,
                const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onStop = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
        arkCallback.InvokeSync();
    };
    VideoModelStatic::SetOnStop(frameNode, onStop);
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        VideoModelStatic::EnableAnalyzer(frameNode, false);
        return;
    }
    VideoModelStatic::EnableAnalyzer(frameNode, *convValue);
}
void AnalyzerConfigImpl(Ark_NativePointer node,
                        const Opt_ImageAnalyzerConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA VideoInterface::AnalyzerConfigImpl -> method is not implemented.");
}
void SurfaceBackgroundColorImpl(Ark_NativePointer node,
                                const Opt_ColorMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        VideoModelStatic::SetSurfaceBackgroundColor(frameNode, Color::BLACK);
        return;
    }
    auto peer = *optValue;
    Color backgroundColor = Color::BLACK;
    backgroundColor.SetValue(peer->colorValue.value);
    if (backgroundColor != Color::TRANSPARENT) {
        backgroundColor = Color::BLACK;
    }
    VideoModelStatic::SetSurfaceBackgroundColor(frameNode, backgroundColor);
}
void EnableShortcutKeyImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        VideoModelNG::SetShortcutKeyEnabled(frameNode, false);
        return;
    }
    VideoModelNG::SetShortcutKeyEnabled(frameNode, *convValue);
}
} // VideoAttributeModifier
const GENERATED_ArkUIVideoModifier* GetVideoModifier()
{
    static const GENERATED_ArkUIVideoModifier ArkUIVideoModifierImpl {
        VideoModifier::ConstructImpl,
        VideoInterfaceModifier::SetVideoOptionsImpl,
        VideoAttributeModifier::MutedImpl,
        VideoAttributeModifier::AutoPlayImpl,
        VideoAttributeModifier::ControlsImpl,
        VideoAttributeModifier::LoopImpl,
        VideoAttributeModifier::ObjectFitImpl,
        VideoAttributeModifier::OnStartImpl,
        VideoAttributeModifier::OnPauseImpl,
        VideoAttributeModifier::OnFinishImpl,
        VideoAttributeModifier::OnFullscreenChangeImpl,
        VideoAttributeModifier::OnPreparedImpl,
        VideoAttributeModifier::OnSeekingImpl,
        VideoAttributeModifier::OnSeekedImpl,
        VideoAttributeModifier::OnUpdateImpl,
        VideoAttributeModifier::OnErrorImpl,
        VideoAttributeModifier::OnStopImpl,
        VideoAttributeModifier::EnableAnalyzerImpl,
        VideoAttributeModifier::AnalyzerConfigImpl,
        VideoAttributeModifier::SurfaceBackgroundColorImpl,
        VideoAttributeModifier::EnableShortcutKeyImpl,
    };
    return &ArkUIVideoModifierImpl;
}

}
