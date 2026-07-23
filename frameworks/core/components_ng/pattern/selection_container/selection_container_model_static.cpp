/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/selection_container/selection_container_model_static.h"

#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/selection_container/selection_container_model_ng.h"
#include "core/components_ng/pattern/selection_container/selection_container_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> SelectionContainerModelStatic::CreateFrameNode(int32_t nodeId)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::SELECTION_CONTAINER_ETS_TAG, nodeId);
    ACE_UINODE_TRACE(nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SELECTION_CONTAINER_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<SelectionContainerPattern>(); });
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->SetSelectionContainerId(nodeId);
    auto layoutProp = frameNode->GetLayoutPropertyPtr<LayoutProperty>();
    if (layoutProp) {
        layoutProp->UpdateAlignment(Alignment::CENTER);
    }
    frameNode->SetExclusiveEventForChild(true);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto selectOverlayManager = pipeline->GetSelectOverlayManager();
    CHECK_NULL_RETURN(selectOverlayManager, nullptr);
    auto selectionContainerManager = selectOverlayManager->GetSelectionContainerManager();
    CHECK_NULL_RETURN(selectionContainerManager, nullptr);
    auto pattern = frameNode->GetPattern<SelectionContainerPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    selectionContainerManager->RegisterSelectionContainer(nodeId, pattern);
    frameNode->AddNodeDestroyCallback("SelectionContainerManager",
        [weakManager = WeakPtr<SelectionContainerManager>(selectionContainerManager),
         selectionContainerId = nodeId]() {
            auto manager = weakManager.Upgrade();
            CHECK_NULL_VOID(manager);
            manager->UnregisterSelectionContainer(selectionContainerId);
        });
    return frameNode;
}

} // namespace OHOS::Ace::NG
