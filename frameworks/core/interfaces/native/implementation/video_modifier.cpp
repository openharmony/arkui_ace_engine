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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "color_metrics_peer.h"
#include "core/interfaces/native/generated/interface/node_api.h"

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
    return {};
}
} // VideoModifier
namespace VideoInterfaceModifier {
void SetVideoOptionsImpl(Ark_NativePointer node,
                         const Ark_VideoOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //VideoModelNG::SetSetVideoOptions(frameNode, convValue);
}
} // VideoInterfaceModifier
namespace VideoAttributeModifier {
void SetMutedImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetMuted(frameNode, convValue);
}
void SetAutoPlayImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetAutoPlay(frameNode, convValue);
}
void SetControlsImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetControls(frameNode, convValue);
}
void SetLoopImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetLoop(frameNode, convValue);
}
void SetObjectFitImpl(Ark_NativePointer node,
                      const Opt_ImageFit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetObjectFit(frameNode, convValue);
}
void SetOnStartImpl(Ark_NativePointer node,
                    const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetOnStart(frameNode, convValue);
}
void SetOnPauseImpl(Ark_NativePointer node,
                    const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetOnPause(frameNode, convValue);
}
void SetOnFinishImpl(Ark_NativePointer node,
                     const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetOnFinish(frameNode, convValue);
}
void SetOnFullscreenChangeImpl(Ark_NativePointer node,
                               const Opt_Callback_FullscreenInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetOnFullscreenChange(frameNode, convValue);
}
void SetOnPreparedImpl(Ark_NativePointer node,
                       const Opt_Callback_PreparedInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetOnPrepared(frameNode, convValue);
}
void SetOnSeekingImpl(Ark_NativePointer node,
                      const Opt_Callback_PlaybackInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetOnSeeking(frameNode, convValue);
}
void SetOnSeekedImpl(Ark_NativePointer node,
                     const Opt_Callback_PlaybackInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetOnSeeked(frameNode, convValue);
}
void SetOnUpdateImpl(Ark_NativePointer node,
                     const Opt_Callback_PlaybackInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetOnUpdate(frameNode, convValue);
}
void SetOnErrorImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetOnError(frameNode, convValue);
}
void SetOnStopImpl(Ark_NativePointer node,
                   const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetOnStop(frameNode, convValue);
}
void SetEnableAnalyzerImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetEnableAnalyzer(frameNode, convValue);
}
void SetAnalyzerConfigImpl(Ark_NativePointer node,
                           const Opt_ImageAnalyzerConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetAnalyzerConfig(frameNode, convValue);
}
void SetSurfaceBackgroundColorImpl(Ark_NativePointer node,
                                   const Opt_ColorMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetSurfaceBackgroundColor(frameNode, convValue);
}
void SetEnableShortcutKeyImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //VideoModelNG::SetSetEnableShortcutKey(frameNode, convValue);
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
        VideoAttributeModifier::SetSurfaceBackgroundColorImpl,
        VideoAttributeModifier::SetEnableShortcutKeyImpl,
    };
    return &ArkUIVideoModifierImpl;
}

}
