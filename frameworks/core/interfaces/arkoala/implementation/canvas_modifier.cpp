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
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/implementation/canvas_rendering_context2d_peer_impl.h"
#include "core/interfaces/arkoala/implementation/drawing_rendering_context_peer_impl.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"

namespace OHOS::Ace::NG::Converter {
template<>
GeneratedModifier::DrawingRenderingContextPeerImpl* Convert(const Ark_Materialized &src)
{
    return reinterpret_cast<GeneratedModifier::DrawingRenderingContextPeerImpl *>(src.ptr);
}
template<>
GeneratedModifier::CanvasRenderingContext2DPeerImpl* Convert(const Ark_Materialized &src)
{
    return reinterpret_cast<GeneratedModifier::CanvasRenderingContext2DPeerImpl *>(src.ptr);
}

} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasInterfaceModifier {

template<typename T>
void ContextSetOptionsHelper(FrameNode *frameNode, const T* context)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(context);
    auto renderingContext2D = Converter::OptConvert<CanvasRenderingContext2DPeerImpl*>(*context);
    auto renderingDrawing = Converter::OptConvert<DrawingRenderingContextPeerImpl*>(*context);

    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    CHECK_NULL_VOID(pattern);

    if (renderingContext2D) {
        CanvasRenderingContext2DPeerImpl* peerImplPtr = *renderingContext2D;
        CHECK_NULL_VOID(peerImplPtr);
        peerImplPtr->SetInstanceId(Container::CurrentId());
        peerImplPtr->SetCanvasPattern(pattern);
        peerImplPtr->UpdateAntiAlias();
        peerImplPtr->UpdateDensity();
    } else if (renderingDrawing) {
        DrawingRenderingContextPeerImpl* peerImplPtr = *renderingDrawing;
        CHECK_NULL_VOID(peerImplPtr);

        peerImplPtr->SetInstanceId(Container::CurrentId());
        peerImplPtr->SetCanvasPattern(pattern);
    } else {
        CanvasModelNG::DetachRenderContext(frameNode);
    }
}

void SetCanvasOptions0Impl(Ark_NativePointer node,
                           const Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext* context)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(context);

    ContextSetOptionsHelper(frameNode, context);

    LOGE("ARKOALA CanvasInterfaceModifier::SetCanvasOptions0Impl - CustomOject is not supported "
        "method DrawingRenderingContextAccessor::CtorImpl.");
}
void SetCanvasOptions1Impl(Ark_NativePointer node,
                           const Ark_Union_CanvasRenderingContext2D_DrawingRenderingContext* context,
                           const Ark_ImageAIOptions* imageAIOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID(imageAIOptions);

    ContextSetOptionsHelper(frameNode, context);

    LOGE("CanvasInterfaceModifier::SetCanvasOptions1Impl - Ark_ImageAIOptions is not supported.");
}
} // CanvasInterfaceModifier

namespace CanvasAttributeModifier {
void OnReadyImpl(Ark_NativePointer node,
                 Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCanvasEventsReceiver()->onReady(frameNode->GetId());
    };
    CanvasModelNG::SetOnReady(frameNode, std::move(onEvent));
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        Ark_Boolean enable)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CanvasModelNG::EnableAnalyzer(frameNode, Converter::Convert<bool>(enable));
}
} // CanvasAttributeModifier
const GENERATED_ArkUICanvasModifier* GetCanvasModifier()
{
    static const GENERATED_ArkUICanvasModifier ArkUICanvasModifierImpl {
        CanvasInterfaceModifier::SetCanvasOptions0Impl,
        CanvasInterfaceModifier::SetCanvasOptions1Impl,
        CanvasAttributeModifier::OnReadyImpl,
        CanvasAttributeModifier::EnableAnalyzerImpl,
    };
    return &ArkUICanvasModifierImpl;
}

}
