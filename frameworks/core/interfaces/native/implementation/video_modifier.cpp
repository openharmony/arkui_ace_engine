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
}
} // VideoInterfaceModifier
namespace VideoAttributeModifier {
void MutedImpl(Ark_NativePointer node,
               const Opt_Boolean* value)
{
}
void AutoPlayImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
}
void ControlsImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
}
void LoopImpl(Ark_NativePointer node,
              const Opt_Boolean* value)
{
}
void ObjectFitImpl(Ark_NativePointer node,
                   const Opt_ImageFit* value)
{
}
void OnStartImpl(Ark_NativePointer node,
                 const Opt_VoidCallback* value)
{
}
void OnPauseImpl(Ark_NativePointer node,
                 const Opt_VoidCallback* value)
{
}
void OnFinishImpl(Ark_NativePointer node,
                  const Opt_VoidCallback* value)
{
}
void OnFullscreenChangeImpl(Ark_NativePointer node,
                            const Opt_Callback_FullscreenInfo_Void* value)
{
}
void OnPreparedImpl(Ark_NativePointer node,
                    const Opt_Callback_PreparedInfo_Void* value)
{
}
void OnSeekingImpl(Ark_NativePointer node,
                   const Opt_Callback_PlaybackInfo_Void* value)
{
}
void OnSeekedImpl(Ark_NativePointer node,
                  const Opt_Callback_PlaybackInfo_Void* value)
{
}
void OnUpdateImpl(Ark_NativePointer node,
                  const Opt_Callback_PlaybackInfo_Void* value)
{
}
void OnErrorImpl(Ark_NativePointer node,
                 const Opt_Callback_Void* value)
{
}
void OnStopImpl(Ark_NativePointer node,
                const Opt_Callback_Void* value)
{
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
}
void AnalyzerConfigImpl(Ark_NativePointer node,
                        const Opt_ImageAnalyzerConfig* value)
{
}
void SurfaceBackgroundColorImpl(Ark_NativePointer node,
                                const Opt_ColorMetrics* value)
{
}
void EnableShortcutKeyImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
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
