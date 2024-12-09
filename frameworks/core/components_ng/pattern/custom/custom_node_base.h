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

    void FireOnAppear()
    {
        if (appearFunc_) {
            appearFunc_();
        }
        executeFireOnAppear_ = true;
    }

    void FireOnDisappear()
    {
        if (destroyFunc_) {
            destroyFunc_();
        }
    }

    void FireDidBuild()
    {
        if (didBuildFunc_) {
            didBuildFunc_();
        }
    }

    virtual void SetRenderFunction(const RenderFunction& renderFunction) {}

    void SetAppearFunction(std::function<void()>&& appearFunc)
    {
        appearFunc_ = std::move(appearFunc);
    }

    void SetDidBuildFunction(std::function<void()>&& didBuildFunc)
    {
        didBuildFunc_ = std::move(didBuildFunc);
    }

    void SetUpdateFunction(std::function<void()>&& updateFunc)
    {
        updateFunc_ = std::move(updateFunc);
    }

    void SetDestroyFunction(std::function<void()>&& destroyFunc)
    {
        destroyFunc_ = std::move(destroyFunc);
    }

    void SetReloadFunction(std::function<void(bool)>&& reloadFunc)
    {
        reloadFunc_ = std::move(reloadFunc);
    }

    void FireReloadFunction(bool deep)
    {
        if (reloadFunc_) {
            reloadFunc_(deep);
        }
    }

    virtual void SetCompleteReloadFunc(RenderFunction&& func) = 0;

    void SetPageTransitionFunction(std::function<void()>&& pageTransitionFunc)
    {
        pageTransitionFunc_ = std::move(pageTransitionFunc);
    }

    void CallPageTransitionFunction() const
    {
        if (pageTransitionFunc_) {
            pageTransitionFunc_();
        }
    }

    void SetForceUpdateNodeFunc(std::function<void(int32_t)>&& forceNodeUpdateFunc)
    {
        forceNodeUpdateFunc_ = std::move(forceNodeUpdateFunc);
    }

    void FireNodeUpdateFunc(ElementIdType id)
    {
        if (forceNodeUpdateFunc_) {
            forceNodeUpdateFunc_(id);
        } else {
            LOGE("fail to find node update func to execute %{public}d node update", id);
        }
    }

    void SetHasNodeUpdateFunc(std::function<bool(int32_t)>&& hasNodeUpdateFunc)
    {
        hasNodeUpdateFunc_ = std::move(hasNodeUpdateFunc);
    }

    bool FireHasNodeUpdateFunc(ElementIdType id)
    {
        return hasNodeUpdateFunc_ && hasNodeUpdateFunc_(id);
    }

    void FireRecycleSelf();

    void SetRecycleFunction(std::function<void(RefPtr<CustomNodeBase>)>&& recycleCustomNode)
    {
        recycleCustomNodeFunc_ = std::move(recycleCustomNode);
    }

    void SetRecycleRenderFunc(std::function<void()>&& func)
    {
        recycleRenderFunc_ = std::move(func);
    }

    void FireRecycleRenderFunc();

    bool HasRecycleRenderFunc()
    {
        return recycleRenderFunc_ != nullptr;
    }

    void ResetRecycle()
    {
        recycleRenderFunc_ = nullptr;
    }

    void SetSetActiveFunc(std::function<void(bool)>&& func)
    {
        setActiveFunc_ = std::move(func);
    }

    void SetOnDumpInfoFunc(std::function<void(const std::vector<std::string>&)>&& func);

    void FireSetActiveFunc(bool active)
    {
        if (setActiveFunc_) {
            setActiveFunc_(active);
        }
    }

    void FireOnDumpInfoFunc(const std::vector<std::string>& params)
    {
        if (onDumpInfoFunc_) {
            onDumpInfoFunc_(params);
        }
    }

    void Reset()
    {
        updateFunc_ = nullptr;
        appearFunc_ = nullptr;
        destroyFunc_ = nullptr;
        didBuildFunc_ = nullptr;
    }

    // called by view in js thread
    void MarkNeedUpdate();

    // called by pipeline in js thread of update.
    void Update();

    void SetJSViewName(std::string&& name)
    {
        jsViewName_ = name;
    }

    std::string& GetJSViewName()
    {
        return jsViewName_;
    }

    void SetExtraInfo(const ExtraInfo extraInfo)
    {
        extraInfo_ = std::move(extraInfo);
    }

    bool GetIsV2()
    {
        return isV2_;
    }

    void SetIsV2(bool isV2)
    {
        isV2_ = isV2;
    }

    const ExtraInfo& GetExtraInfo() const
    {
        return extraInfo_;
    }

    bool HasExtraInfo() {
        if (!extraInfo_.page.empty()) {
            return true;
        }
        return false;
    }

    void SetThisFunc(std::function<void*()>&& getThisFunc)
    {
        getThisFunc_ = std::move(getThisFunc);
    }

    void* FireThisFunc()
    {
        if (getThisFunc_) {
            return getThisFunc_();
        }
        return nullptr;
    }

    void SetOnDumpInspectorFunc(std::function<std::string()>&& func);

    std::string FireOnDumpInspectorFunc()
    {
        if (onDumpInspectorFunc_) {
            return onDumpInspectorFunc_();
        }
        return "";
    }

    bool CheckFireOnAppear()
    {
        return executeFireOnAppear_;
    }

    // used By BuilderNode
    void SetOnRecycleFunc(std::function<void()>&& func);
    void FireOnRecycleFunc();
    void SetOnReuseFunc(std::function<void(void*)>&& func);
    void FireOnReuseFunc(void* params);
        
protected:
    std::string jsViewName_;
    ExtraInfo extraInfo_;
    bool isV2_ = false;

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
    std::function<void(bool)> setActiveFunc_;
    std::function<void(const std::vector<std::string>&)> onDumpInfoFunc_;
    std::function<std::string()> onDumpInspectorFunc_;
    std::function<void*()> getThisFunc_;
    std::function<void()> onRecycleFunc_;
    std::function<void(void*)> onReuseFunc_;
    bool needRebuild_ = false;
    bool executeFireOnAppear_ = false;
    RecycleNodeInfo recycleInfo_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_NODE_BASE_H
