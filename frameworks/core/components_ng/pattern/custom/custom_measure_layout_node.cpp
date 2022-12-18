/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"

#include "base/log/dump_log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/custom/custom_node_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

RefPtr<CustomMeasureLayoutNode> CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(
    int32_t nodeId, const std::string& viewKey)
{
    auto node = MakeRefPtr<CustomMeasureLayoutNode>(nodeId, viewKey);
    node->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

CustomMeasureLayoutNode::CustomMeasureLayoutNode(int32_t nodeId, const std::string& viewKey)
    : FrameNode(V2::JS_VIEW_ETS_TAG, nodeId, MakeRefPtr<CustomNodePattern>()), viewKey_(viewKey)
{}

bool CustomMeasureLayoutNode::FireOnMeasure(NG::LayoutWrapper* layoutWrapper)
{
    if (measureFunc_) {
        measureFunc_(layoutWrapper);
        return true;
    }
    return false;
}

bool CustomMeasureLayoutNode::FireOnLayout(NG::LayoutWrapper* layoutWrapper)
{
    if (layoutFunc_) {
        layoutFunc_(layoutWrapper);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
