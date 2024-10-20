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
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasInterfaceModifier {
void SetCanvasOptions0Impl(Ark_NativePointer node,
                           const Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext* context)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    // if(context == nullptr){
    //     return;
    // }
    // std::optional<void *> options = Converter::OptConvert<void*>(*context)
    // if(options && options->hasValue) {
    //    CanvasModelNG::SetImageAIOptions(frameNode, options);
    // }

    LOGE("Arkoala: Canvas.SetCanvasOptions0Impl - method not implemented");
}
void SetCanvasOptions1Impl(Ark_NativePointer node,
                           const Ark_Union_CanvasRenderingContext2D_DrawingRenderingContext* context,
                           const Ark_ImageAIOptions* imageAIOptions)
{
   
    //auto convValue = Converter::Convert<type>(context);
    //auto convValue = Converter::OptConvert<type>(context); // for enums
    //CanvasModelNG::SetSetCanvasOptions1(frameNode, convValue);
    LOGE("Arkoala: Canvas.SetCanvasOptions1Impl - method not implemented");
   
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);

    // if(context == nullptr){
    //     return;
    // }
    // std::optional<void *> options = Converter::OptConvert<void*>(*imageAIOptions)
    // if(options && options->hasValue) {
    //    CanvasModelNG::SetImageAIOptions(frameNode, options);
    // }

    // ark
    // typedef struct Ark_ImageAIOptions {
    //     Opt_Array_ImageAnalyzerType types;
    //     typedef struct Array_ImageAnalyzerType {
    //          Ark_ImageAnalyzerType* array;
    //             typedef enum Ark_ImageAnalyzerType {
    //                 ARK_IMAGE_ANALYZER_TYPE_SUBJECT = 0,
    //                 ARK_IMAGE_ANALYZER_TYPE_TEXT,
    //                 ARK_IMAGE_ANALYZER_TYPE_OBJECT_LOOKUP,
    //             } Ark_ImageAnalyzerType;
    //         Ark_Int32 length;
    //     } Array_ImageAnalyzerType;
    //     Opt_ImageAnalyzerController aiController;
    //         typedef Ark_Materialized Ark_ImageAnalyzerController;
    // } Ark_ImageAIOptions;

    // to


    //void CanvasModelNG::SetImageAIOptions(void* options)

    //auto convValue = Converter::Convert<type>(context);
    //auto convValue = Converter::OptConvert<type>(context); // for enums
    //CanvasModelNG::SetSetCanvasOptions1(frameNode, convValue);
}
} // CanvasInterfaceModifier
namespace CanvasAttributeModifier {
void OnReadyImpl(Ark_NativePointer node,
                 Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCanvasEventsReceiver()->onFinish(frameNode->GetId());
    };
    SetOnReady(frameNode, std::move(onEvent));
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        Ark_Boolean enable)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
     CanvasModelNG::EnableAnalyzer(FrameNode* frameNode, Converter::Convert<bool>(enable));
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
