/*
* Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/custom/custom_node_static.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/arkts_frontend/arkts_frontend.h"
#include "core/common/container.h"
#include "core/common/frontend.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {
CustomNode* CustomNodeStatic::ConstructCustomNode(int32_t id, NodeKoalaInfo&& info)
{
    auto customNode = NG::CustomNode::CreateCustomNode(id, info.jsViewName);
    customNode->IncRefCount();

    customNode->SetOnPageShowFunc(std::move(info.onPageShowFunc));
    customNode->SetOnPageHideFunc(std::move(info.onPageHideFunc));
    customNode->SetOnBackPressedFunc(std::move(info.onBackPressedFunc));
    customNode->SetPageTransitionFunc(std::move(info.pageTransitionFunc));
    customNode->SetOnCleanupFunc(std::move(info.onCleanupFunc));
    customNode->SetOnDumpInspectorFunc(std::move(info.onDumpInspectorFunc));

    return AceType::RawPtr(customNode);
}

CustomMeasureLayoutNode* CustomNodeStatic::ConstructCustomNode(int32_t id,
    std::function<void(NG::LayoutWrapper* layoutWrapper)>&& onMeasureSize,
    std::function<void(NG::LayoutWrapper* layoutWrapper)>&& onPlaceChildren)
{
    auto customNode = NG::CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(id, "");
    customNode->IncRefCount();
    if (onMeasureSize) {
        auto customMeasureLayoutNode = AceType::DynamicCast<NG::CustomMeasureLayoutNode>(customNode);
        customMeasureLayoutNode->SetMeasureFunction(std::move(onMeasureSize));
    } else {
        TAG_LOGI(AceLogTag::ACE_NATIVE_NODE, "onMeasureSize null");
    }

    if (onPlaceChildren) {
        auto customMeasureLayoutNode = AceType::DynamicCast<NG::CustomMeasureLayoutNode>(customNode);
        customMeasureLayoutNode->SetLayoutFunction(std::move(onPlaceChildren));
    } else {
        TAG_LOGI(AceLogTag::ACE_NATIVE_NODE, "onPlaceChildren null");
    }
    
    return AceType::RawPtr(customNode);
}
} // namespace OHOS::Ace::NG