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
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter_union.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/canvas_rendering_context2d_peer_impl.h"
#include "core/interfaces/native/implementation/drawing_rendering_context_peer_impl.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = CanvasModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // CanvasModifier
namespace CanvasInterfaceModifier {

template<typename T>
void ContextSetOptionsHelper(FrameNode *frameNode, const T* context)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(context);

    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    CHECK_NULL_VOID(pattern);

    Converter::VisitUnion(*context,
        [pattern](const Ark_CanvasRenderingContext2D& peer) {
            CanvasRenderingContext2DPeerImpl* peerImplPtr = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
            CHECK_NULL_VOID(peerImplPtr);
            peerImplPtr->SetInstanceId(Container::CurrentId());
            peerImplPtr->SetCanvasPattern(pattern);
            peerImplPtr->CanvasRendererPeerImpl::SetAntiAlias();
            peerImplPtr->CanvasRendererPeerImpl::SetDensity();
        },
        [pattern](const Ark_DrawingRenderingContext &peer) {
            DrawingRenderingContextPeerImpl* peerImplPtr = reinterpret_cast<DrawingRenderingContextPeerImpl*>(peer);
            CHECK_NULL_VOID(peerImplPtr);
            peerImplPtr->SetInstanceId(Container::CurrentId());
            peerImplPtr->SetCanvasPattern(pattern);
        },
        []() {
            // CanvasModelNG::DetachRenderContext(frameNode);
        });
}

void SetCanvasOptions0Impl(Ark_NativePointer node,
                           const Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext* context)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(context);

    ContextSetOptionsHelper(frameNode, context);

    LOGE("ARKOALA CanvasInterfaceModifier::SetCanvasOptions0Impl - CustomObject is not supported "
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
                 const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)]() { arkCallback.Invoke(); };
    CanvasModelNG::SetOnReady(frameNode, std::move(onEvent));
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    CanvasModelNG::EnableAnalyzer(frameNode, *convValue);
}
} // CanvasAttributeModifier
const GENERATED_ArkUICanvasModifier* GetCanvasModifier()
{
    static const GENERATED_ArkUICanvasModifier ArkUICanvasModifierImpl {
        CanvasModifier::ConstructImpl,
        CanvasInterfaceModifier::SetCanvasOptions0Impl,
        CanvasInterfaceModifier::SetCanvasOptions1Impl,
        CanvasAttributeModifier::OnReadyImpl,
        CanvasAttributeModifier::EnableAnalyzerImpl,
    };
    return &ArkUICanvasModifierImpl;
}

}
