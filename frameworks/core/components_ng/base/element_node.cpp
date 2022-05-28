/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/element_node.h"

#include "base/log/dump_log.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

ElementNode::~ElementNode()
{
    for (const auto& child : elementChildren_) {
        if (child) {
            DetachChild(child);
        }
    }
    elementChildren_.clear();
}

void ElementNode::AddChild(const RefPtr<ElementNode>& child, int32_t slot)
{
    if (!child) {
        return;
    }

    auto it = std::find(elementChildren_.begin(), elementChildren_.end(), child);
    if (it != elementChildren_.end()) {
        LOGW("Child element is already existed");
        return;
    }

    it = elementChildren_.begin();
    std::advance(it, slot);
    auto result = elementChildren_.insert(it, child);
    child->SetSlot(std::distance(elementChildren_.begin(), result));
    OnChildAdded(child);
}

void ElementNode::RemoveChild(const RefPtr<ElementNode>& child)
{
    if (child) {
        DetachChild(child);
        elementChildren_.remove(child);
    }
}

RefPtr<ElementNode> ElementNode::GetChildBySlot(int32_t slot)
{
    for (auto& iter : elementChildren_) {
        if (slot == iter->GetSlot()) {
            return iter;
        }
    }
    return nullptr;
}

void ElementNode::DetachChild(const RefPtr<ElementNode>& child)
{
    child->OnDetached();
}

void ElementNode::DumpTree(int32_t depth)
{
    if (DumpLog::GetInstance().GetDumpFile()) {
        DumpInfo();
        DumpLog::GetInstance().Print(depth, AceType::TypeName(this), static_cast<int32_t>(elementChildren_.size()));
    }

    for (const auto& item : elementChildren_) {
        item->DumpTree(depth + 1);
    }
}

void ElementNode::MountToParent(const RefPtr<ElementNode>& parent, int32_t slot)
{
    SetElementParent(parent);
    SetDepth(parent != nullptr ? parent->GetDepth() + 1 : 1);
    if (parent) {
        if (parent->tag_ != V2::ROOT_ETS_TAG) {
            SetHostPageId(parent->GetPageId());
            SetHostRootId(parent->GetRootId());
        }
        parent->AddChild(AceType::Claim(this), slot);
    }
    AttachContextrecursively(parent != nullptr ? parent->context_.Upgrade() : nullptr);
    OnMounted();
}

const std::list<RefPtr<ElementNode>>& ElementNode::GetElementChildren() const
{
    return elementChildren_;
}

void ElementNode::SetPipelineContext(const RefPtr<PipelineContext>& context)
{
    if (!context) {
        return;
    }
    context_ = context;
    OnContextAttached();
}

void ElementNode::AttachContextrecursively(const RefPtr<PipelineContext>& context)
{
    if (!context) {
        return;
    }
    context_ = context;
    OnContextAttached();
    for (auto& child : elementChildren_) {
        child->AttachContextrecursively(context);
    }
}

} // namespace OHOS::Ace::NG
