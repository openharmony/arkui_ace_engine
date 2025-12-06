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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FORCE_SPLIT_FORCE_SPLIT_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FORCE_SPLIT_FORCE_SPLIT_MANAGER_H

#include <cstdint>
#include <optional>
#include <unordered_map>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {

class ForceSplitManager : public virtual AceType {
    DECLARE_ACE_TYPE(ForceSplitManager, AceType);
public:
    ForceSplitManager() = default;
    ~ForceSplitManager() = default;

    void SetPipelineContext(const WeakPtr<PipelineContext>& pipeline)
    {
        pipeline_ = pipeline;
    }
    bool HasSetForceSplitConfig() const
    {
        return hasSetForceSplitConfig_;
    }
    void SetIsRouter(bool isRouter)
    {
        isRouter_ = isRouter;
    }

    void SetForceSplitSupported(bool isForceSplitSupported)
    {
        isForceSplitSupported_ = isForceSplitSupported;
        hasSetForceSplitConfig_ = true;
    }
    bool IsForceSplitSupported(bool isRouter) const
    {
        return isForceSplitSupported_ && isRouter_ == isRouter;
    }
    void SetForceSplitEnable(bool isForceSplit);
    bool IsForceSplitEnable(bool isRouter) const
    {
        return isForceSplitEnable_ && isRouter_ == isRouter;
    }

    void UpdateIsInForceSplitMode();

    void SetHomePageName(const std::string& homePage)
    {
        homePageName_ = homePage;
    }
    void SetRelatedPageName(const std::string& relatedPage)
    {
        relatedPageName_ = relatedPage;
    }
    const std::string& GetHomePageName() const
    {
        return homePageName_;
    }
    const std::string& GetRelatedPageName() const
    {
        return relatedPageName_;
    }
    
    void SetFullScreenPages(std::set<std::string>&& pages)
    {
        fullScreenPages_ = std::move(pages);
    }
    bool IsFullScreenPage(const std::string& name) const
    {
        return fullScreenPages_.find(name) != fullScreenPages_.end();
    }

    void NotifyForceFullScreenChange(bool isForceFullScreen);

    void AddForceSplitStateListener(int32_t nodeId, std::function<void()>&& listener);
    void RemoveForceSplitStateListener(int32_t nodeId);
    void NotifyForceSplitStateChange();

    bool HasRelatedPage() const
    {
        return !relatedPageName_.empty();
    }
    int32_t GetAppIconId() const
    {
        return appIconId_;
    }
    void SetAppIconId(int32_t id)
    {
        appIconId_ = id;
    }

private:
    WeakPtr<PipelineContext> pipeline_;
    bool hasSetForceSplitConfig_ = false;
    bool isForceSplitSupported_ = false;
    bool isForceSplitEnable_ = false;
    bool isRouter_ = false;
    std::set<std::string> fullScreenPages_;
    std::string homePageName_;
    std::string relatedPageName_;
    std::unordered_map<int32_t, std::function<void()>> forceSplitListeners_;
    int32_t appIconId_ = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FORCE_SPLIT_FORCE_SPLIT_MANAGER_H