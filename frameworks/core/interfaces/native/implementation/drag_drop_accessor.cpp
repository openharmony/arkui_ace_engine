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

#include "arkoala_api_generated.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/event/gesture_event_hub.h"
#if !defined(PREVIEW)
#include "core/components_ng/syntax/static/detached_free_root_proxy_node.h"
#endif
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DragDropOpsAccessor {
#if !defined(PREVIEW)
RefPtr<OHOS::Ace::NG::DetachedFreeRootProxyNode> CreateProxyNode(const RefPtr<UINode>& uiNode)
{
    CHECK_NULL_RETURN(uiNode, nullptr);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto instanceId = container->GetInstanceId();
    auto proxyNode = AceType::MakeRefPtr<DetachedFreeRootProxyNode>(instanceId);
    CHECK_NULL_RETURN(proxyNode, nullptr);
    proxyNode->AddChild(uiNode);
    return proxyNode;
}
#endif

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
#if !defined(PREVIEW)
        dragDropInfo.customNode = CreateProxyNode(customNode);
#else
        dragDropInfo.customNode = customNode;
#endif
        return dragDropInfo;
    };
    ViewAbstract::SetOnDragStart(frameNode, std::move(onDragStartLambda));
}

void RegisterDragPreviewImpl(Ark_NativePointer node, const Opt_Union_CustomNodeBuilder_DragItemInfo_String* preview,
    const Opt_PreviewConfiguration* config)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(config);
    bool onlyForLifting = optValue ? Converter::OptConvert<bool>(optValue->onlyForLifting).value_or(false) : false;
    bool delayCreating = optValue ? Converter::OptConvert<bool>(optValue->delayCreating).value_or(false) : false;
    Converter::VisitUnionPtr(preview,
        [frameNode, onlyForLifting, delayCreating](const Ark_String& val) {
            ViewAbstract::SetDragPreview(frameNode,
                DragDropInfo { .inspectorId = Converter::Convert<std::string>(val),
                               .onlyForLifting = onlyForLifting, .delayCreating = delayCreating });
        },
        [node, frameNode, onlyForLifting, delayCreating](const CustomNodeBuilder& val) {
            CallbackHelper(val).BuildAsync([frameNode, onlyForLifting, delayCreating](const RefPtr<UINode>& uiNode) {
                ViewAbstract::SetDragPreview(frameNode, DragDropInfo { .customNode = uiNode,
                                                                       .onlyForLifting = onlyForLifting,
                                                                       .delayCreating = delayCreating  });
                }, node);
        },
        [node, frameNode, onlyForLifting, delayCreating](const Ark_DragItemInfo& value) {
            auto builder = Converter::OptConvert<CustomNodeBuilder>(value.builder);
            DragDropInfo dragDropInfo {
                .extraInfo = Converter::OptConvert<std::string>(value.extraInfo).value_or(std::string()),
                .onlyForLifting = onlyForLifting, .delayCreating = delayCreating };
            if (builder) {
                CallbackHelper(builder.value()).BuildAsync([frameNode, dragDropInfo = std::move(dragDropInfo)](
                    const RefPtr<UINode>& uiNode) {
                    DragDropInfo info;
                    info.customNode = uiNode;
                    info.onlyForLifting = dragDropInfo.onlyForLifting;
                    info.delayCreating = dragDropInfo.delayCreating;
                    ViewAbstract::SetDragPreview(frameNode, info);
                    }, node);
            } else {
                ViewAbstract::SetDragPreview(frameNode, DragDropInfo {
                    .onlyForLifting = onlyForLifting, .delayCreating = delayCreating });
            }
        },
        [frameNode]() {
            ViewAbstract::SetDragPreview(frameNode, DragDropInfo {});
        });
}

void RegisterOnDropImpl(Ark_NativePointer node, const Opt_OnDragEventCallback* eventCallback,
    const Opt_DropOptions* dropOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(eventCallback);
    if (!optValue) {
        return;
    }
    auto onDrop = [callback = CallbackHelper(*optValue)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent,
        const std::string& extraParams) {
        CHECK_NULL_VOID(dragEvent);
        Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
        callback.InvokeSync(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    };
    ViewAbstract::SetOnDrop(frameNode, std::move(onDrop));

    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto optValueDropOption = Converter::GetOptPtr(dropOptions);
    if (!optValueDropOption) {
        eventHub->SetDisableDataPrefetch(false);
        return;
    }
    auto disableDataPrefetch = Converter::OptConvert<bool>(optValueDropOption->disableDataPrefetch).value_or(false);
    eventHub->SetDisableDataPrefetch(disableDataPrefetch);
}
}// DragDropOpsAccessor

const GENERATED_ArkUIDragDropOpsAccessor* GetDragDropOpsAccessor()
{
    static const GENERATED_ArkUIDragDropOpsAccessor DragDropOpsAccessorImpl {
        DragDropOpsAccessor::RegisterOnDragStartImpl,
        DragDropOpsAccessor::RegisterDragPreviewImpl,
        DragDropOpsAccessor::RegisterOnDropImpl
    };
    return &DragDropOpsAccessorImpl;
}
}