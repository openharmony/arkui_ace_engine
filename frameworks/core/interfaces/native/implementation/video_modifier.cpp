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
    options.currentProgressRate =
        Converter::OptConvert<float>(src.currentProgressRate).value_or(options.currentProgressRate);

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
void SetMutedImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelStatic::SetObjectFit(frameNode, Converter::OptConvertPtr<ImageFit>(value));
}
void SetOnStartImpl(Ark_NativePointer node,
                    const Opt_VoidCallback* value)
{
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
                    const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        VideoModelStatic::SetOnError(frameNode, nullptr);
        return;
    }
    auto onError = [arkCallback = CallbackHelper(*optValue)](const std::string& param) {
#ifndef ACE_UNITTEST
        CHECK_NULL_VOID(CallbackHelper<VoidCallback>::GetVMContext());
#endif
        arkCallback.InvokeSync();
    };
    VideoModelStatic::SetOnError(frameNode, onError);
}
void SetOnStopImpl(Ark_NativePointer node,
                   const Opt_VoidCallback* value)
{
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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA VideoInterface::AnalyzerConfigImpl -> method is not implemented.");
}
void SetSurfaceBackgroundColorImpl(Ark_NativePointer node,
                                   const Opt_ColorMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto colorValue = Converter::OptConvertPtr<Color>(value);
    auto color = colorValue.value_or(Color::BLACK);
    VideoModelNG::SetSurfaceBackgroundColor(frameNode, (color == Color::TRANSPARENT ? color : Color::BLACK));
}
void SetEnableShortcutKeyImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
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
const GENERATED_ArkUIVideoModifier* GetVideoModifier()
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
