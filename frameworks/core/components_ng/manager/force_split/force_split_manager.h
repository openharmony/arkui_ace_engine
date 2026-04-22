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
#include "core/common/force_split/force_split_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components/common/layout/constants.h"
#include "interfaces/inner_api/ace/viewport_config.h"

namespace OHOS::Ace::NG {

using OHOS::Ace::ForceSplitMode;

class ForceSplitManager : public virtual AceType {
    DECLARE_ACE_TYPE(ForceSplitManager, AceType);
public:
    ForceSplitManager();
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
    bool IsRouterForceSplit() const
    {
        return isRouter_;
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
    void SetForceSplitEnable(bool isForceSplit, ForceSplitMode mode, bool needUpdateViewport = false);
    bool IsForceSplitEnable(bool isRouter) const;
    void SetNavigationForceSplitEnableInternal(bool enableSplit);
    bool GetDisableNavForceSplitInternal() const
    {
        return disableNavForceSplitInternal_;
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
    
    void SetFullScreenPages(std::unordered_set<std::string>&& pages)
    {
        fullScreenPages_ = std::move(pages);
    }
    bool IsFullScreenPage(const std::string& name) const
    {
        return fullScreenPages_.find(name) != fullScreenPages_.end();
    }

    void SetSplitDividerColor(std::optional<Color> light, std::optional<Color> dark)
    {
        splitDividerColorLight_ = light;
        splitDividerColorDark_ = dark;
    }
 
    std::pair<std::optional<Color>, std::optional<Color>> GetSplitDividerColor() const
    {
        return { splitDividerColorLight_, splitDividerColorDark_ };
    }

    void NotifyForceFullScreenChange(bool isForceFullScreen);

    void AddForceSplitStateListener(int32_t nodeId, std::function<void()>&& listener);
    void RemoveForceSplitStateListener(int32_t nodeId);
    void NotifyForceSplitStateChange();
    void OnForceSplitEnableChange();

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

    void SetDialogSupportSplit(bool dialogSupportSplit)
    {
        dialogSupportSplit_ = dialogSupportSplit;
    }

    bool GetDialogSupportSplit() const
    {
        return dialogSupportSplit_;
    }

    void SetWideSplitRatio(const std::optional<float> ratio)
    {
        wideSplitRatio_ = ratio;
    }
    void SetSquareSplitRatio(const std::optional<float> ratio)
    {
        squareSplitRatio_ = ratio;
    }
    float GetSplitRatio() const
    {
        return splitRatio_;
    }
    void UpdateForceSplitRatio();
    void AddForceSplitRatioListener(int32_t nodeId, std::function<void(float)>&& listener);
    void RemoveForceSplitRatioListener(int32_t nodeId);

    void SetBehaviorMode(ForceSplitBehaviorMode mode)
    {
        behaviorMode_ = mode;
    }
    ForceSplitBehaviorMode GetBehaviorMode() const
    {
        return behaviorMode_;
    }
    void SetPagePairs(std::unordered_map<std::string, std::unordered_set<std::string>>&& pagePairs)
    {
        pagePairs_ = std::move(pagePairs);
    }
    bool IsPagePair(const std::string& from, const std::string& to) const;
    void SetTransPages(std::unordered_set<std::string>&& transPages)
    {
        transPages_ = std::move(transPages);
    }
    bool IsTransPage(const std::string& name) const;
    bool CanPushPageToPrimary() const;
    bool IsTransitionShouldMovePageToPrimary(const std::string& from, const std::string& to) const;

private:
    bool IsTopFullScreenPage();
    bool IsWindowConditionMatched();
    bool HasForceSplitTargetNavigation();
    void RegisterSurfaceChangeCallbackIfNeeded();
    void ChangeForceSplitModeIfNeeded();
    void FlushArkUIHook();
    float CalcCurrentSplitRatio();
    void OnForceSplitRatioUpdate(float ratio);

    WeakPtr<PipelineContext> pipeline_;
    bool hasSetForceSplitConfig_ = false;
    bool isForceSplitSupported_ = false;
    bool isForceSplitEnable_ = false;
    bool isRouter_ = false;
    bool dialogSupportSplit_ = true;
    std::unordered_set<std::string> fullScreenPages_;
    std::string homePageName_;
    std::string relatedPageName_;
    std::optional<float> wideSplitRatio_;
    std::optional<float> squareSplitRatio_;
    float splitRatio_;
    ForceSplitMode mode_;
    ForceSplitBehaviorMode behaviorMode_ = ForceSplitBehaviorMode::NAVIGATION;
    std::unordered_map<std::string, std::unordered_set<std::string>> pagePairs_;
    std::unordered_set<std::string> transPages_;
    std::unordered_map<int32_t, std::function<void()>> forceSplitListeners_;
    std::unordered_map<int32_t, std::function<void(float)>> forceSplitRatioListeners_;
    int32_t appIconId_ = 0;
    // for navigation force split, we need disable forcesplit before router transition.
    bool disableNavForceSplitInternal_ = false;
    // When the window actively notifies ArkUI to enable/disable force split, it may need to work
    // in coordination with subsequent UpdateViewportConfig. For example, in rotation scenarios,
    // the application rotation animation may include a split/stack switching animation.
    std::optional<int32_t> surfaceChangeCallbackId_;
    std::optional<bool> delayedIsForceSplitEnable_;
    std::optional<Color> splitDividerColorLight_;
    std::optional<Color> splitDividerColorDark_;
    std::optional<ForceSplitMode> delayedMode_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FORCE_SPLIT_FORCE_SPLIT_MANAGER_H