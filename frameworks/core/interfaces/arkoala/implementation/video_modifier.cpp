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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
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
void MutedImpl(Ark_NativePointer node,
               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //VideoModelNG::SetMuted(frameNode, convValue);
}
void AutoPlayImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //VideoModelNG::SetAutoPlay(frameNode, convValue);
}
void ControlsImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //VideoModelNG::SetControls(frameNode, convValue);
}
void LoopImpl(Ark_NativePointer node,
              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //VideoModelNG::SetLoop(frameNode, convValue);
}
void ObjectFitImpl(Ark_NativePointer node,
                   Ark_ImageFit value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //VideoModelNG::SetObjectFit(frameNode, convValue);
}
void OnStartImpl(Ark_NativePointer node,
                 Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //VideoModelNG::SetOnStart(frameNode, convValue);
}
void OnPauseImpl(Ark_NativePointer node,
                 Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //VideoModelNG::SetOnPause(frameNode, convValue);
}
void OnFinishImpl(Ark_NativePointer node,
                  Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //VideoModelNG::SetOnFinish(frameNode, convValue);
}
void OnFullscreenChangeImpl(Ark_NativePointer node,
                            Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //VideoModelNG::SetOnFullscreenChange(frameNode, convValue);
}
void OnPreparedImpl(Ark_NativePointer node,
                    Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //VideoModelNG::SetOnPrepared(frameNode, convValue);
}
void OnSeekingImpl(Ark_NativePointer node,
                   Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //VideoModelNG::SetOnSeeking(frameNode, convValue);
}
void OnSeekedImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //VideoModelNG::SetOnSeeked(frameNode, convValue);
}
void OnUpdateImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //VideoModelNG::SetOnUpdate(frameNode, convValue);
}
void OnErrorImpl(Ark_NativePointer node,
                 Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //VideoModelNG::SetOnError(frameNode, convValue);
}
void OnStopImpl(Ark_NativePointer node,
                Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //VideoModelNG::SetOnStop(frameNode, convValue);
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        Ark_Boolean enable)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(enable);
    //VideoModelNG::SetEnableAnalyzer(frameNode, convValue);
}
void AnalyzerConfigImpl(Ark_NativePointer node,
                        const Ark_ImageAnalyzerConfig* config)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(config);
    //auto convValue = Converter::OptConvert<type_name>(*config);
    //VideoModelNG::SetAnalyzerConfig(frameNode, convValue);
}
} // VideoAttributeModifier
const GENERATED_ArkUIVideoModifier* GetVideoModifier()
{
    static const GENERATED_ArkUIVideoModifier ArkUIVideoModifierImpl {
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