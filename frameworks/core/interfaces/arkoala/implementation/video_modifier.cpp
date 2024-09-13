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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace VideoInterfaceModifier {
void SetVideoOptionsImpl(Ark_NativePointer node,
                         const Ark_VideoOptions* value)
{
}
} // VideoInterfaceModifier
namespace VideoAttributeModifier {
void MutedImpl(Ark_NativePointer node,
               Ark_Boolean value)
{
}
void AutoPlayImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
}
void ControlsImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
}
void LoopImpl(Ark_NativePointer node,
              Ark_Boolean value)
{
}
void ObjectFitImpl(Ark_NativePointer node,
                   enum Ark_ImageFit value)
{
}
void OnStartImpl(Ark_NativePointer node,
                 Ark_Function event)
{
}
void OnPauseImpl(Ark_NativePointer node,
                 Ark_Function event)
{
}
void OnFinishImpl(Ark_NativePointer node,
                  Ark_Function event)
{
}
void OnFullscreenChangeImpl(Ark_NativePointer node,
                            Ark_Function callback)
{
}
void OnPreparedImpl(Ark_NativePointer node,
                    Ark_Function callback)
{
}
void OnSeekingImpl(Ark_NativePointer node,
                   Ark_Function callback)
{
}
void OnSeekedImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void OnUpdateImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void OnErrorImpl(Ark_NativePointer node,
                 Ark_Function event)
{
}
void OnStopImpl(Ark_NativePointer node,
                Ark_Function event)
{
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        Ark_Boolean enable)
{
}
void AnalyzerConfigImpl(Ark_NativePointer node,
                        const Ark_ImageAnalyzerConfig* config)
{
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
