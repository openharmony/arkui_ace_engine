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

#include "core/components_ng/base/composed_node.h"

#include <utility>

#include "base/log/dump_log.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

ComposedNode::ComposedNode(const std::string& tag, std::string id) : ElementNode(tag), id_(std::move(id))
{
    type_ = ElementType::COMPOSED_ELEMENT;
}

ComposedNode::~ComposedNode() = default;

void ComposedNode::OnChildAdded(const RefPtr<ElementNode>& child)
{
    if (!child) {
        LOGE("ElementNode child is null");
        return;
    }

    if (!applyFunction_) {
        LOGE("No apply function");
        return;
    }

    if (child->GetType() == ElementType::RENDER_ELEMENT) {
        // Directly attach the FrameNode if child is FrameNode.
        applyFunction_(AceType::DynamicCast<FrameNode>(child));
    }
}

void ComposedNode::OnContextAttached()
{
    if (UpdateJsViewFunction_) {
        UpdateJsViewFunction_(WeakClaim(this));
    }
    if (appearFunction_) {
        appearFunction_();
    }
    MarkNeedRebuild();
}

void ComposedNode::OnMounted()
{
    auto parent = elementParent_.Upgrade();
    if (InstanceOf<FrameNode>(parent)) {
        applyFunction_ = [parent](const RefPtr<FrameNode>& renderChild) {
            auto renderElement = DynamicCast<FrameNode>(parent);
            if (renderElement) {
                renderElement->AddFrameChild(renderChild);
            }
        };
    }
    if (InstanceOf<ComposedNode>(parent)) {
        auto composedElement = DynamicCast<ComposedNode>(parent);
        if (composedElement) {
            applyFunction_ = composedElement->applyFunction_;
        }
    }
}

void ComposedNode::DumpInfo()
{
    DumpLog::GetInstance().AddDesc("name:" + name_);
    DumpLog::GetInstance().AddDesc("id:" + id_);
}

void ComposedNode::Rebuild()
{
    if (HasRenderFunction()) {
        FlushBuildTask(renderFunction_());
    }
    needRebuild_ = false;
}

void ComposedNode::FlushBuildTask(const RenderResult& renderResult)
{
    BuildChildren(renderResult.first);
    for (auto iter = renderResult.second.rbegin(); iter != renderResult.second.rend(); iter++) {
        if (*iter) {
            (*iter)();
        }
    }
}

void ComposedNode::BuildChildren(const RefPtr<ElementNode>& child)
{
    int32_t slot = 0;
    countRenderNode_ = 0;
    if (!child) {
        LOGE("the child is null");
        return;
    }
    child->MountToParent(Claim(this), slot);
    // TODO: Add patical update process.
}

void ComposedNode::MarkNeedRebuild()
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("context is nullptr, fail to push async task");
        return;
    }
    if (needRebuild_) {
        return;
    }
    needRebuild_ = true;
    context->AddDirtyComposedNode(Claim(this));
}

} // namespace OHOS::Ace::NG
