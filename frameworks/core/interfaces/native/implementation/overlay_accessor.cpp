/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "bridge/arkts_frontend/arkts_frontend.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/event/gesture_event_hub.h"
#if !defined(PREVIEW)
#include "core/components_ng/syntax/static/detached_free_root_proxy_node.h"
#endif
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace OverlayOpsAccessor {
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

void SetOverlayAttributeImpl(Ark_NativePointer node, const Opt_Union_String_CustomBuilder* value,
    const Opt_OverlayOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    OverlayOptions overlay { .align = Alignment::TOP_LEFT};
    overlay = Converter::OptConvertPtr<OverlayOptions>(options).value_or(overlay);
    Converter::VisitUnionPtr(value, [frameNode, &overlay](const Ark_String& src) {
            overlay.content = Converter::Convert<std::string>(src);
            ViewAbstract::SetOverlay(frameNode, overlay);
        },
        [node, frameNode, &overlay](const CustomNodeBuilder& builder) {
            CallbackHelper(builder).BuildAsync([overlay, frameNode](const RefPtr<UINode>& uiNode) {
#if !defined(PREVIEW)
                ViewAbstract::SetOverlayBuilder(
                    frameNode, CreateProxyNode(uiNode), overlay.align, overlay.x, overlay.y);
#else
                ViewAbstract::SetOverlayBuilder(frameNode, uiNode, overlay.align, overlay.x, overlay.y);
#endif
                }, node);
        },
        [frameNode, &overlay]() {
            RefPtr<NG::UINode> node = nullptr;
            ViewAbstract::SetOverlayBuilder(frameNode, nullptr, overlay.align, overlay.x, overlay.y);
        });
}
} // DragDropOpsAccessor

const GENERATED_ArkUIOverlayOpsAccessor* GetOverlayOpsAccessor()
{
    static const GENERATED_ArkUIOverlayOpsAccessor OverlayOpsAccessorImpl {
    OverlayOpsAccessor::SetOverlayAttributeImpl,
    };
    return &OverlayOpsAccessorImpl;
}
}