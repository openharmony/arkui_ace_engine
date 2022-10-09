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

#include "core/components_ng/pattern/custom/custom_node.h"

#include "base/log/dump_log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/custom/custom_node_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
RefPtr<CustomNode> CustomNode::CreateCustomNode(int32_t nodeId, const std::string& viewKey)
{
    auto node = MakeRefPtr<CustomNode>(nodeId, viewKey);
    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

CustomNode::CustomNode(int32_t nodeId, const std::string& viewKey)
    : UINode(V2::JS_VIEW_ETS_TAG, nodeId, MakeRefPtr<CustomNodePattern>()), viewKey_(viewKey)
{}

CustomNode::~CustomNode()
{
    if (destroyFunc_) {
        destroyFunc_();
    }
}

void CustomNode::AdjustLayoutWrapperTree(const RefPtr<LayoutWrapper>& parent, bool forceMeasure, bool forceLayout)
{
    if (renderFunction_) {
        {
            ACE_SCOPED_TRACE("CustomNode:OnAppear");
            FireOnAppear();
        }
        {
            ACE_SCOPED_TRACE("CustomNode:BuildItem");
            // first create child node and wrapper.
            auto child = renderFunction_();
            CHECK_NULL_VOID(child);
            child->MountToParent(Claim(this));
            child->AdjustLayoutWrapperTree(parent, true, true);
        }
        renderFunction_ = nullptr;
    } else {
        UINode::AdjustLayoutWrapperTree(parent, forceMeasure, forceLayout);
    }
}

void CustomNode::Update()
{
    if (updateFunc_) {
        updateFunc_();
    }
    needRebuild_ = false;
}

void CustomNode::MarkNeedUpdate()
{
    auto context = GetContext();
    if (!context) {
        LOGE("context is nullptr, fail to push async task");
        return;
    }
    if (needRebuild_) {
        return;
    }
    needRebuild_ = true;
    context->AddDirtyCustomNode(Claim(this));
}
} // namespace OHOS::Ace::NG
