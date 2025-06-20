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
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DragDropOpsAccessor {
void RegisterOnDragStartImpl(Ark_NativePointer node, const Callback_onDragStart* onDragStart)
{
    auto frameNode = reinterpret_cast<OHOS::Ace::NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onDragStartLambda = [arkCallback = CallbackHelper(*onDragStart), weak = weakNode, node]
        (const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)-> DragDropInfo {
        PipelineContext::SetCallBackNode(weak);
        auto arkDragInfo = Converter::ArkValue<Ark_DragEvent>(info);
        auto arkExtraParam = Converter::ArkValue<Ark_String>(extraParams);
        arkCallback.InvokeSync(node, arkDragInfo, arkExtraParam);
        DragDropInfo dragDropInfo;
        CHECK_NULL_RETURN(info, dragDropInfo);
        dragDropInfo.pixelMap = info->GetDragDropInfoPixelMap();
        dragDropInfo.extraInfo = info->GetDragDropInfoExtraInfo();
        auto node = reinterpret_cast<OHOS::Ace::NG::FrameNode*>(info->GetDragDropInfoCustomNode());
        auto customNodeWeak = AceType::WeakClaim(node);
        auto customNode = customNodeWeak.Upgrade();
        CHECK_NULL_RETURN(customNode, dragDropInfo);
        dragDropInfo.customNode = customNode;
        return dragDropInfo;
    };
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDragStart(std::move(onDragStartLambda));
}
}// DragDropOpsAccessor

const GENERATED_ArkUIDragDropOpsAccessor* GetDragDropOpsAccessor()
{
    static const GENERATED_ArkUIDragDropOpsAccessor DragDropOpsAccessorImpl {
        DragDropOpsAccessor::RegisterOnDragStartImpl,
    };
    return &DragDropOpsAccessorImpl;
}
}