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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter_union.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/canvas_rendering_context2d_peer_impl.h"
#include "core/interfaces/native/implementation/drawing_rendering_context_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id, Ark_Int32 flags)
{
    auto frameNode = CanvasModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // CanvasModifier
namespace CanvasInterfaceModifier {
template<typename T>
void ContextSetOptions0Helper(FrameNode* frameNode, const T* context)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(context);

    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    CHECK_NULL_VOID(pattern);

    Converter::VisitUnion(
        *context,
        [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](const Ark_CanvasRenderingContext2D& peer) {
            auto canvasPattern = weak.Upgrade();
            CHECK_NULL_VOID(canvasPattern);
            CHECK_NULL_VOID(peer);
            if (peer->IsBuiltIn()) {
                DrawingRenderingContextPeerImpl::ThrowError(ERROR_CODE_CANVAS_ERROR_CONTEXT,
                    "The context created in system cannot be bound to other canvas component");
                return;
            }
            peer->SetInstanceId(Container::CurrentId());
            peer->SetCanvasPattern(canvasPattern);
            peer->CanvasRendererPeerImpl::SetAntiAlias();
            peer->CanvasRendererPeerImpl::SetDensity();
        },
        [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](const Ark_DrawingRenderingContext& peer) {
            auto canvasPattern = weak.Upgrade();
            CHECK_NULL_VOID(canvasPattern);
            DrawingRenderingContextPeerImpl* peerImplPtr = reinterpret_cast<DrawingRenderingContextPeerImpl*>(peer);
            CHECK_NULL_VOID(peerImplPtr);
            if (peerImplPtr->IsBuiltIn()) {
                DrawingRenderingContextPeerImpl::ThrowError(ERROR_CODE_CANVAS_ERROR_CONTEXT,
                    "The context created in system cannot be bound to other canvas component.");
                return;
            }
            peerImplPtr->SetInstanceId(Container::CurrentId());
            peerImplPtr->SetCanvasPattern(canvasPattern);
        },
        [weak = AceType::WeakClaim(frameNode)]() {
            auto node = weak.Upgrade();
            CanvasModelNG::DetachRenderContext(AceType::RawPtr(node));
        });
}
void SetCanvasOptions0Impl(Ark_NativePointer node,
    const Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext* context, const Opt_ImageAIOptions* imageAIOptions)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(context);
    CanvasModelNG::SetImmediateRender(frameNode, false);
    ContextSetOptions0Helper(frameNode, context);
}
void SetCanvasOptions1Impl(Ark_NativePointer node, const Ark_CanvasParams* params)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(params);
    auto lengthMetricsUnitValue = Converter::OptConvert<Ace::CanvasUnit>(params->unit).value_or(CanvasUnit::DEFAULT);
    CanvasModelNG::UpdateUnit(frameNode, lengthMetricsUnitValue);
    CanvasModelNG::SetImmediateRender(frameNode, true);
}
} // namespace CanvasInterfaceModifier
namespace CanvasAttributeModifier {
void SetOnReadyImpl(Ark_NativePointer node, const Opt_Callback_Union_DrawingRenderingContext_Undefined_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::GetOptPtr(value);
    if (!convValue) {
        CanvasModelNG::ResetOnReady(frameNode);
    } else {
        auto pattern = frameNode->GetPatternPtr<CanvasPattern>();
        auto onReadyEvent = [arkCallback = CallbackHelper(*convValue), weak = AceType::WeakClaim(pattern)](
                                bool needDrawingContext, CanvasUnit unit) {
            if (!needDrawingContext) {
                auto invalid = Converter::ArkValue<Opt_DrawingRenderingContext>();
                arkCallback.InvokeSync(invalid);
                return;
            }
            auto canvasPattern = weak.Upgrade();
            CHECK_NULL_VOID(canvasPattern);
            auto drawingContext = new DrawingRenderingContextPeerImpl();
            drawingContext->IncRefCount();
            drawingContext->SetOptions(unit);
            drawingContext->SetInstanceId(Container::CurrentId());
            drawingContext->SetCanvasPattern(canvasPattern);
            drawingContext->SetUnit(unit);
            drawingContext->SetBuiltIn(true);
            canvasPattern->SetRSCanvasForDrawingContext();
            canvasPattern->SetUpdateContextCallback(
                [drawingContext = drawingContext](CanvasUnit unit) { drawingContext->SetUnit(unit); });
            auto arkDrawingContext = reinterpret_cast<DrawingRenderingContextPeer*>(drawingContext);
            auto optDrawingContext = Converter::ArkValue<Opt_DrawingRenderingContext>(arkDrawingContext);
            arkCallback.InvokeSync(optDrawingContext);
        };
        CanvasModelNG::SetOnReady(frameNode, std::move(onReadyEvent));
    }
}
void SetEnableAnalyzerImpl(Ark_NativePointer node, const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        CanvasModelNG::EnableAnalyzer(frameNode, false);
        return;
    }
    CanvasModelNG::EnableAnalyzer(frameNode, *convValue);
}
} // namespace CanvasAttributeModifier
const GENERATED_ArkUICanvasModifier* GetCanvasModifier()
{
    static const GENERATED_ArkUICanvasModifier ArkUICanvasModifierImpl {
        CanvasModifier::ConstructImpl,
        CanvasInterfaceModifier::SetCanvasOptions0Impl,
        CanvasInterfaceModifier::SetCanvasOptions1Impl,
        CanvasAttributeModifier::SetOnReadyImpl,
        CanvasAttributeModifier::SetEnableAnalyzerImpl,
    };
    return &ArkUICanvasModifierImpl;
}

}
