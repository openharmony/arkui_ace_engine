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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

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
