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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_NODE_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_NODE_BASE_H

#include <functional>
#include <list>
#include <string>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/custom/custom_node_pattern.h"
#include "core/components_ng/pattern/recycle_view/recycle_manager.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT CustomNodeBase : public virtual AceType {
    DECLARE_ACE_TYPE(CustomNodeBase, AceType);

public:
    CustomNodeBase() = default;
    ~CustomNodeBase() override;

    virtual void SetRenderFunction(const RenderFunction& renderFunction) {};
    virtual void SetCompleteReloadFunc(RenderFunction&& func) = 0;

    // called for Component Info
    void SetJSViewName(std::string&& name);
    std::string& GetJSViewName();

    void SetIsV2(bool isV2);
    bool GetIsV2();

    void SetThisFunc(std::function<void*()>&& getThisFunc);
    void* FireThisFunc();

    // called for Component life Cycle
    void Reset();
    void SetAppearFunction(std::function<void()>&& appearFunc);
    void FireOnAppear();
    bool CheckFireOnAppear();

    void SetDidBuildFunction(std::function<void()>&& didBuildFunc);
    void FireDidBuild();

    void SetDestroyFunction(std::function<void()>&& destroyFunc);
    void FireOnDisappear();

    // called for Component update
    void SetUpdateFunction(std::function<void()>&& updateFunc);
    void SetForceUpdateNodeFunc(std::function<void(int32_t)>&& forceNodeUpdateFunc);
    void FireNodeUpdateFunc(ElementIdType id);

    void SetHasNodeUpdateFunc(std::function<bool(int32_t)>&& hasNodeUpdateFunc);
    bool FireHasNodeUpdateFunc(ElementIdType id);

    void SetReloadFunction(std::function<void(bool)>&& reloadFunc);
    void FireReloadFunction(bool deep);

    void Update();  // called by pipeline in js thread of update.
    void MarkNeedUpdate();   // called by view in js thread

    // called for Component reuse
    void ResetRecycle();
    void SetOnRecycleFunc(std::function<void()>&& func);
    void FireRecycleSelf();

    void SetRecycleFunction(std::function<void(RefPtr<CustomNodeBase>)>&& recycleCustomNode);
    void FireOnRecycleFunc();

    void SetRecycleRenderFunc(std::function<void()>&& func);
    void FireRecycleRenderFunc();
    bool HasRecycleRenderFunc();

    void FireClearAllRecycleFunc();

    void SetOnReuseFunc(std::function<void(void*)>&& func);
    void FireOnReuseFunc(void* params);

    // called for Component freezing
    void SetSetActiveFunc(std::function<void(bool, bool)>&& func);
    void FireSetActiveFunc(bool active, bool isReuse = false);

    // called for DFX
    void SetExtraInfo(const ExtraInfo extraInfo);
    const ExtraInfo& GetExtraInfo() const;
    bool HasExtraInfo();

    void SetOnDumpInfoFunc(std::function<void(const std::vector<std::string>&)>&& func);
    void FireOnDumpInfoFunc(const std::vector<std::string>& params);

    void SetOnDumpInspectorFunc(std::function<std::string()>&& func);
    std::string FireOnDumpInspectorFunc();

    // called for PageTransition animation
    void SetPageTransitionFunction(std::function<void()>&& pageTransitionFunc);
    void CallPageTransitionFunction() const;
        
    void SetClearAllRecycleFunc(std::function<void()>&& func);

protected:
    std::string jsViewName_;
    ExtraInfo extraInfo_;
    bool isV2_ = false;
    bool executeFireOnAppear_ = false;

private:
    std::function<void()> updateFunc_;
    std::function<void()> appearFunc_;
    std::function<void()> didBuildFunc_;
    std::function<void()> destroyFunc_;
    std::function<void()> pageTransitionFunc_;
    std::function<void(bool)> reloadFunc_;
    std::function<void()> completeReloadFunc_;
    std::function<void(int32_t)> forceNodeUpdateFunc_;
    std::function<bool(int32_t)> hasNodeUpdateFunc_;
    std::function<void(RefPtr<CustomNodeBase>)> recycleCustomNodeFunc_;
    std::function<void()> recycleRenderFunc_;
    std::function<void(bool, bool)> setActiveFunc_;
    std::function<void(const std::vector<std::string>&)> onDumpInfoFunc_;
    std::function<std::string()> onDumpInspectorFunc_;
    std::function<void()> clearAllRecycleFunc_;
    std::function<void*()> getThisFunc_;
    std::function<void()> onRecycleFunc_;
    std::function<void(void*)> onReuseFunc_;
    bool needRebuild_ = false;
    RecycleNodeInfo recycleInfo_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_NODE_BASE_H
