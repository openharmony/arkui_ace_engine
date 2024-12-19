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

void CustomNodeBase::FireOnAppear()
{
    if (appearFunc_) {
        appearFunc_();
    }
    executeFireOnAppear_ = true;
}

void CustomNodeBase::FireOnDisappear()
{
    if (destroyFunc_) {
        destroyFunc_();
    }
}

void CustomNodeBase::FireDidBuild()
{
    if (didBuildFunc_) {
        didBuildFunc_();
    }
}

void CustomNodeBase::SetAppearFunction(std::function<void()>&& appearFunc)
{
    appearFunc_ = std::move(appearFunc);
}

void CustomNodeBase::SetDidBuildFunction(std::function<void()>&& didBuildFunc)
{
    didBuildFunc_ = std::move(didBuildFunc);
}

void CustomNodeBase::SetUpdateFunction(std::function<void()>&& updateFunc)
{
    updateFunc_ = std::move(updateFunc);
}

void CustomNodeBase::SetDestroyFunction(std::function<void()>&& destroyFunc)
{
    destroyFunc_ = std::move(destroyFunc);
}

void CustomNodeBase::SetReloadFunction(std::function<void(bool)>&& reloadFunc)
{
    reloadFunc_ = std::move(reloadFunc);
}

void CustomNodeBase::FireReloadFunction(bool deep)
{
    if (reloadFunc_) {
        reloadFunc_(deep);
    }
}

void CustomNodeBase::Update()
{
    needRebuild_ = false;
    if (updateFunc_) {
        updateFunc_();
    }
}

void CustomNodeBase::SetPageTransitionFunction(std::function<void()>&& pageTransitionFunc)
{
    pageTransitionFunc_ = std::move(pageTransitionFunc);
}

void CustomNodeBase::CallPageTransitionFunction() const
{
    if (pageTransitionFunc_) {
        pageTransitionFunc_();
    }
}

void CustomNodeBase::SetForceUpdateNodeFunc(std::function<void(int32_t)>&& forceNodeUpdateFunc)
{
    forceNodeUpdateFunc_ = std::move(forceNodeUpdateFunc);
}

void CustomNodeBase::FireNodeUpdateFunc(ElementIdType id)
{
    if (forceNodeUpdateFunc_) {
        forceNodeUpdateFunc_(id);
    } else {
        LOGE("fail to find node update func to execute %{public}d node update", id);
    }
}

void CustomNodeBase::SetHasNodeUpdateFunc(std::function<bool(int32_t)>&& hasNodeUpdateFunc)
{
    hasNodeUpdateFunc_ = std::move(hasNodeUpdateFunc);
}

bool CustomNodeBase::FireHasNodeUpdateFunc(ElementIdType id)
{
    return hasNodeUpdateFunc_ && hasNodeUpdateFunc_(id);
}

void CustomNodeBase::SetRecycleFunction(std::function<void(RefPtr<CustomNodeBase>)>&& recycleCustomNode)
{
    recycleCustomNodeFunc_ = std::move(recycleCustomNode);
}

void CustomNodeBase::SetRecycleRenderFunc(std::function<void()>&& func)
{
    recycleRenderFunc_ = std::move(func);
}

bool CustomNodeBase::HasRecycleRenderFunc()
{
    return recycleRenderFunc_ != nullptr;
}

void CustomNodeBase::ResetRecycle()
{
    recycleRenderFunc_ = nullptr;
}

void CustomNodeBase::SetSetActiveFunc(std::function<void(bool)>&& func)
{
    setActiveFunc_ = std::move(func);
}

void CustomNodeBase::FireSetActiveFunc(bool active)
{
    if (setActiveFunc_) {
        setActiveFunc_(active);
    }
}

void CustomNodeBase::FireOnDumpInfoFunc(const std::vector<std::string>& params)
{
    if (onDumpInfoFunc_) {
        onDumpInfoFunc_(params);
    }
}

void CustomNodeBase::Reset()
{
    updateFunc_ = nullptr;
    appearFunc_ = nullptr;
    destroyFunc_ = nullptr;
    didBuildFunc_ = nullptr;
}

void CustomNodeBase::SetJSViewName(std::string&& name)
{
    jsViewName_ = name;
}

std::string& CustomNodeBase::GetJSViewName()
{
    return jsViewName_;
}

void CustomNodeBase::SetExtraInfo(const ExtraInfo extraInfo)
{
    extraInfo_ = std::move(extraInfo);
}

bool CustomNodeBase::GetIsV2()
{
    return isV2_;
}

void CustomNodeBase::SetIsV2(bool isV2)
{
    isV2_ = isV2;
}

const ExtraInfo& CustomNodeBase::GetExtraInfo() const
{
    return extraInfo_;
}

bool CustomNodeBase::HasExtraInfo()
{
    if (!extraInfo_.page.empty()) {
        return true;
    }
    return false;
}

void CustomNodeBase::SetThisFunc(std::function<void*()>&& getThisFunc)
{
    getThisFunc_ = std::move(getThisFunc);
}

void* CustomNodeBase::FireThisFunc()
{
    if (getThisFunc_) {
        return getThisFunc_();
    }
    return nullptr;
}

std::string CustomNodeBase::FireOnDumpInspectorFunc()
{
    if (onDumpInspectorFunc_) {
        return onDumpInspectorFunc_();
    }
    return "";
}

bool CustomNodeBase::CheckFireOnAppear()
{
    return executeFireOnAppear_;
}

void CustomNodeBase::MarkNeedUpdate()
{
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
