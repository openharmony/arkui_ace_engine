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

#include "core/components_ng/pattern/custom/custom_node_base.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

CustomNodeBase::~CustomNodeBase()
{
    RecycleManager::Erase(recycleInfo_.elemtId);
    // appearFunc_ & destroyFunc_ should be executed in pairs
    if (!executeFireOnAppear_ && appearFunc_) {
        appearFunc_();
        if (didBuildFunc_) {
            didBuildFunc_();
        }
    }
    if (destroyFunc_) {
        ACE_SCOPED_TRACE("CustomNodeBase:Destroy [%s]", GetJSViewName().c_str());
        destroyFunc_();
    }
}

void CustomNodeBase::Update()
{
    needRebuild_ = false;
    if (updateFunc_) {
        updateFunc_();
    }
}

void CustomNodeBase::MarkNeedUpdate()
{
    if (recycleRenderFunc_) {
        TAG_LOGW(
            AceLogTag::ACE_STATE_MGMT, "[%{public}s] call markNeedUpdate in recycle/reuse", GetJSViewName().c_str());
        return;
    }
    auto context = PipelineContext::GetCurrentContext();
    if (!context) {
        TAG_LOGW(AceLogTag::ACE_STATE_MGMT, "context no longer exist when [%{public}s] call markNeedUpdate",
            GetJSViewName().c_str());
        return;
    }
    if (needRebuild_) {
        TAG_LOGW(AceLogTag::ACE_STATE_MGMT, "[%{public}s] call markNeedUpdate in rebuild", GetJSViewName().c_str());
        return;
    }
    needRebuild_ = true;
    context->AddDirtyCustomNode(AceType::DynamicCast<UINode>(Claim(this)));
}

void CustomNodeBase::FireRecycleSelf()
{
    auto uiNode = AceType::DynamicCast<UINode>(Claim(this));
    uiNode->OnRecycle();
    if (recycleCustomNodeFunc_) {
        recycleInfo_.Recycle(uiNode->GetId());
        RecycleManager::Push(uiNode->GetId(), AceType::WeakClaim(this));
        recycleCustomNodeFunc_(AceType::Claim<CustomNodeBase>(this));
    }
}

void CustomNodeBase::FireRecycleRenderFunc()
{
    if (recycleRenderFunc_) {
        ACE_SCOPED_TRACE("CustomNode:BuildRecycle %s", GetJSViewName().c_str());
        auto node = AceType::DynamicCast<UINode>(Claim(this));
        recycleInfo_.Reuse();
        RecycleManager::Pop(node->GetId());
        {
            ScopedViewStackProcessor scopedViewStackProcessor;
            recycleRenderFunc_();
        }
        node->OnReuse();
        node->SetJSViewActive(true);
        recycleRenderFunc_ = nullptr;
    }
}

void CustomNodeBase::SetOnDumpInfoFunc(std::function<void(const std::vector<std::string>&)>&& func)
{
    onDumpInfoFunc_ = func;
}

void CustomNodeBase::SetOnDumpInspectorFunc(std::function<std::string()>&& func)
{
    onDumpInspectorFunc_ = func;
}

void CustomNodeBase::SetOnRecycleFunc(std::function<void()>&& func)
{
    onRecycleFunc_ = func;
}

void CustomNodeBase::SetOnReuseFunc(std::function<void(void*)>&& func)
{
    onReuseFunc_ = func;
}

void CustomNodeBase::FireOnRecycleFunc()
{
    if (onRecycleFunc_) {
        onRecycleFunc_();
    }
}

void CustomNodeBase::FireOnReuseFunc(void* params)
{
    if (onReuseFunc_) {
        onReuseFunc_(params);
    }
}
} // namespace OHOS::Ace::NG
