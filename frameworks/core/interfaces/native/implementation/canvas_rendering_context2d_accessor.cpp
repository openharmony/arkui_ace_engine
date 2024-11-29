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
namespace CanvasRenderingContext2DAccessor {
void DestroyPeerImpl(CanvasRenderingContext2DPeer* peer)
{
}
CanvasRenderingContext2DPeer* CtorImpl(const Opt_RenderingContextSettings* settings)
{
    return new CanvasRenderingContext2DPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ToDataURLImpl(CanvasRenderingContext2DPeer* peer,
                   const Opt_String* type,
                   const Opt_CustomObject* quality)
{
}
void StartImageAnalyzerImpl(CanvasRenderingContext2DPeer* peer,
                            const Ark_ImageAnalyzerConfig* config,
                            const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void StopImageAnalyzerImpl(CanvasRenderingContext2DPeer* peer)
{
}
void OnOnAttachImpl(CanvasRenderingContext2DPeer* peer,
                    const Callback_Void* callback)
{
}
void OffOnAttachImpl(CanvasRenderingContext2DPeer* peer,
                     const Opt_Callback_Void* callback)
{
}
void OnOnDetachImpl(CanvasRenderingContext2DPeer* peer,
                    const Callback_Void* callback)
{
}
void OffOnDetachImpl(CanvasRenderingContext2DPeer* peer,
                     const Opt_Callback_Void* callback)
{
}
Ark_Int32 GetHeightImpl(CanvasRenderingContext2DPeer* peer)
{
    return 0;
}
Ark_Int32 GetWidthImpl(CanvasRenderingContext2DPeer* peer)
{
    return 0;
}
} // CanvasRenderingContext2DAccessor
const GENERATED_ArkUICanvasRenderingContext2DAccessor* GetCanvasRenderingContext2DAccessor()
{
    static const GENERATED_ArkUICanvasRenderingContext2DAccessor CanvasRenderingContext2DAccessorImpl {
        CanvasRenderingContext2DAccessor::DestroyPeerImpl,
        CanvasRenderingContext2DAccessor::CtorImpl,
        CanvasRenderingContext2DAccessor::GetFinalizerImpl,
        CanvasRenderingContext2DAccessor::ToDataURLImpl,
        CanvasRenderingContext2DAccessor::StartImageAnalyzerImpl,
        CanvasRenderingContext2DAccessor::StopImageAnalyzerImpl,
        CanvasRenderingContext2DAccessor::OnOnAttachImpl,
        CanvasRenderingContext2DAccessor::OffOnAttachImpl,
        CanvasRenderingContext2DAccessor::OnOnDetachImpl,
        CanvasRenderingContext2DAccessor::OffOnDetachImpl,
        CanvasRenderingContext2DAccessor::GetHeightImpl,
        CanvasRenderingContext2DAccessor::GetWidthImpl,
    };
    return &CanvasRenderingContext2DAccessorImpl;
}

}
