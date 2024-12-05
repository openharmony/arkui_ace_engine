/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/video/video_model_ng.h"
#include "core/interfaces/native/implementation/video_controller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG {
struct VideoOptions {
    std::string src;
    std::string bundleNameSrc;
    std::string moduleNameSrc;
    double currentProgressRate;
    ImageSourceInfo previewSourceInfo;
    RefPtr<VideoControllerV2> videoController;
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
    VideoOptions options;

    // src
    auto sourceInfo = Converter::OptConvert<ImageSourceInfo>(src.src);
    if (sourceInfo) {
        options.src = sourceInfo.value().GetSrc();
        options.moduleNameSrc = sourceInfo.value().GetModuleName();
        options.bundleNameSrc = sourceInfo.value().GetBundleName();
    }

    // currentProgressRate
    options.currentProgressRate = static_cast<double>(
        Converter::OptConvert<float>(src.currentProgressRate).value_or(1.0f));

    // previewUri
    options.previewSourceInfo = Converter::OptConvert<ImageSourceInfo>(src.previewUri)
        .value_or(ImageSourceInfo("", "", ""));

    // controller
    auto abstPeerPtrOpt = Converter::OptConvert<Ark_NativePointer>(src.controller);
    CHECK_NULL_RETURN(abstPeerPtrOpt, options);
    auto peerImplPtr = reinterpret_cast<GeneratedModifier::VideoControllerPeerImpl *>(*abstPeerPtrOpt);
    CHECK_NULL_RETURN(peerImplPtr, options);
    options.videoController = peerImplPtr->GetController();
    return options;
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace VideoModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
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
    VideoModelNG::SetSrc(frameNode, options.src, options.bundleNameSrc, options.moduleNameSrc);
    VideoModelNG::SetProgressRate(frameNode, options.currentProgressRate);
    VideoModelNG::SetPosterSourceInfo(frameNode, options.previewSourceInfo);
    if (options.videoController) {
        VideoModelNG::SetVideoController(frameNode, options.videoController);
    }
    LOGE("ARKOALA VideoInterface::SetVideoOptionsImpl -> imageAIOptions is not supported.");
}
} // VideoInterfaceModifier
namespace VideoAttributeModifier {
void MutedImpl(Ark_NativePointer node,
               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetMuted(frameNode, Converter::Convert<bool>(value));
}
void AutoPlayImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetAutoPlay(frameNode, Converter::Convert<bool>(value));
}
void ControlsImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetControls(frameNode, Converter::Convert<bool>(value));
}
void LoopImpl(Ark_NativePointer node,
              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetLoop(frameNode, Converter::Convert<bool>(value));
}
void ObjectFitImpl(Ark_NativePointer node,
                   Ark_ImageFit value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetObjectFit(frameNode, Converter::OptConvert<ImageFit>(value));
}
void OnStartImpl(Ark_NativePointer node,
                 const VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onStart = [frameNode](const std::string& param) {
        GetFullAPI()->getEventsAPI()->getVideoEventsReceiver()->onStart(frameNode->GetId());
    };
    VideoModelNG::SetOnStart(frameNode, onStart);
}
void OnPauseImpl(Ark_NativePointer node,
                 const VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onPause = [frameNode](const std::string& param) {
        GetFullAPI()->getEventsAPI()->getVideoEventsReceiver()->onPause(frameNode->GetId());
    };
    VideoModelNG::SetOnPause(frameNode, onPause);
}
void OnFinishImpl(Ark_NativePointer node,
                  const VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onFinish = [frameNode](const std::string& param) {
        GetFullAPI()->getEventsAPI()->getVideoEventsReceiver()->onFinish(frameNode->GetId());
    };
    VideoModelNG::SetOnFinish(frameNode, onFinish);
}
void OnFullscreenChangeImpl(Ark_NativePointer node,
                            const Callback_FullscreenInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onFullscreenChange = [frameNode](const std::string& param) {
        auto data = JsonUtil::ParseJsonString(param);
        auto fullscreen = data->GetValue("fullscreen")->GetBool();
        Ark_FullscreenInfo event = {
            .fullscreen = Converter::ArkValue<Ark_Boolean>(fullscreen)
        };
        GetFullAPI()->getEventsAPI()->getVideoEventsReceiver()->onFullscreenChange(frameNode->GetId(), event);
    };
    VideoModelNG::SetOnFullScreenChange(frameNode, onFullscreenChange);
}
void OnPreparedImpl(Ark_NativePointer node,
                    const Callback_PreparedInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onPrepared = [frameNode](const std::string& param) {
        auto data = JsonUtil::ParseJsonString(param);
        auto duration = data->GetValue("duration")->GetDouble();
        Ark_PreparedInfo event = {
            .duration = Converter::ArkValue<Ark_Number>(static_cast<float>(duration))
        };
        GetFullAPI()->getEventsAPI()->getVideoEventsReceiver()->onPrepared(frameNode->GetId(), event);
    };
    VideoModelNG::SetOnPrepared(frameNode, onPrepared);
}
void OnSeekingImpl(Ark_NativePointer node,
                   const Callback_PlaybackInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onSeeking = [frameNode](const std::string& param) {
        auto data = JsonUtil::ParseJsonString(param);
        auto time = data->GetValue("time")->GetDouble();
        Ark_PlaybackInfo event = {
            .time = Converter::ArkValue<Ark_Number>(static_cast<float>(time))
        };
        GetFullAPI()->getEventsAPI()->getVideoEventsReceiver()->onSeeking(frameNode->GetId(), event);
    };
    VideoModelNG::SetOnSeeking(frameNode, onSeeking);
}
void OnSeekedImpl(Ark_NativePointer node,
                  const Callback_PlaybackInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onSeeked = [frameNode](const std::string& param) {
        auto data = JsonUtil::ParseJsonString(param);
        auto time = data->GetValue("time")->GetDouble();
        Ark_PlaybackInfo event = {
            .time = Converter::ArkValue<Ark_Number>(static_cast<float>(time))
        };
        GetFullAPI()->getEventsAPI()->getVideoEventsReceiver()->onSeeked(frameNode->GetId(), event);
    };
    VideoModelNG::SetOnSeeked(frameNode, onSeeked);
}
void OnUpdateImpl(Ark_NativePointer node,
                  const Callback_PlaybackInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onUpdate = [frameNode](const std::string& param) {
        auto data = JsonUtil::ParseJsonString(param);
        auto time = data->GetValue("time")->GetDouble();
        Ark_PlaybackInfo event = {
            .time = Converter::ArkValue<Ark_Number>(static_cast<float>(time))
        };
        GetFullAPI()->getEventsAPI()->getVideoEventsReceiver()->onUpdate(frameNode->GetId(), event);
    };
    VideoModelNG::SetOnUpdate(frameNode, onUpdate);
}
void OnErrorImpl(Ark_NativePointer node,
                 const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onError = [frameNode](const std::string& param) {
        GetFullAPI()->getEventsAPI()->getVideoEventsReceiver()->onError(frameNode->GetId());
    };
    VideoModelNG::SetOnError(frameNode, onError);
}
void OnStopImpl(Ark_NativePointer node,
                const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onStop = [frameNode](const std::string& param) {
        GetFullAPI()->getEventsAPI()->getVideoEventsReceiver()->onStop(frameNode->GetId());
    };
    VideoModelNG::SetOnStop(frameNode, onStop);
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::EnableAnalyzer(frameNode, Converter::Convert<bool>(value));
}
void AnalyzerConfigImpl(Ark_NativePointer node,
                        const Ark_ImageAnalyzerConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //VideoModelNG::SetAnalyzerConfig(frameNode, convValue);
    LOGE("ARKOALA VideoInterface::AnalyzerConfigImpl -> method is not implemented.");
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
    };
    return &ArkUIVideoModifierImpl;
}

}
