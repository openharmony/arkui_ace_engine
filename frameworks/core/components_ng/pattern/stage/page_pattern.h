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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PAGE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PAGE_PATTERN_H

#include <functional>

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/animation/animator_info.h"
#include "core/animation/page_transition_common.h"
#include "core/common/autofill/auto_fill_trigger_state_holder.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/pattern/stage/content_root_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/pattern/stage/page_info.h"
#include "core/components_ng/pattern/stage/page_transition_effect.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

using SharedTransitionMap = std::unordered_map<ShareId, WeakPtr<FrameNode>>;
using JSAnimatorMap = std::unordered_map<std::string, RefPtr<Framework::AnimatorInfo>>;

using DynamicPageSizeCallback = std::function<void(const SizeF& size)>;
/**
 * When the page triggers 'onHide' or 'onShow', the callback is called,
 * and the input parameter is 'true' for onHide and false for onShow.
 */
using PageVisibilityChangeCallback = std::function<void(bool)>;

enum class RouterPageState {
    ABOUT_TO_APPEAR = 0,
    ABOUT_TO_DISAPPEAR = 1,
    ON_PAGE_SHOW = 2,
    ON_PAGE_HIDE = 3,
    ON_BACK_PRESS = 4,
};

// PagePattern is the base class for page root render node.
class ACE_FORCE_EXPORT PagePattern : public ContentRootPattern, public FocusView, public AutoFillTriggerStateHolder {
    DECLARE_ACE_TYPE(PagePattern, ContentRootPattern, FocusView, AutoFillTriggerStateHolder);

public:
    explicit PagePattern(const RefPtr<PageInfo>& pageInfo) : pageInfo_(pageInfo) {}
    ~PagePattern() override = default;

    bool IsMeasureBoundary() const override
    {
        return true;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    const RefPtr<PageInfo>& GetPageInfo() const
    {
        return pageInfo_;
    }

    std::string GetPageUrl() const
    {
        return pageInfo_ ? pageInfo_->GetPageUrl() : "";
    }

    virtual void OnShow(bool isFromWindow = false);

    virtual void OnHide(bool isFromWindow = false);

    bool OnBackPressed();

    RouterPageState GetPageState() const
    {
        return state_;
    }

    void SetOnPageShow(std::function<void()>&& onPageShow)
    {
        onPageShow_ = std::move(onPageShow);
    }

    void SetOnPageHide(std::function<void()>&& onPageHide)
    {
        onPageHide_ = std::move(onPageHide);
    }

    void SetOnBackPressed(std::function<bool()>&& OnBackPressed)
    {
        onBackPressed_ = std::move(OnBackPressed);
    }

    void SetPageTransitionFunc(std::function<void()>&& pageTransitionFunc)
    {
        pageTransitionFunc_ = std::move(pageTransitionFunc);
    }

    void RegisterDumpInfoListener(const std::function<void(const std::vector<std::string>&)>&& callback)
    {
        dumpListener_ = std::move(callback);
    }

    void FireDumpListener(const std::vector<std::string>& params)
    {
        CHECK_NULL_VOID(dumpListener_);
        auto dumpListener = dumpListener_;
        dumpListener(params);
    }

    // find pageTransition effect according to transition type
    RefPtr<PageTransitionEffect> FindPageTransitionEffect(PageTransitionType type);

    void ClearPageTransitionEffect();

    RefPtr<PageTransitionEffect> GetTopTransition() const;

    void AddPageTransition(const RefPtr<PageTransitionEffect>& effect);

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<PageEventHub>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    std::list<int32_t> GetRouteOfFirstScope() override
    {
        return { 0 };
    }

    const SharedTransitionMap& GetSharedTransitionMap() const
    {
        return sharedTransitionMap_;
    }

    void AddJsAnimator(const std::string& animatorId, const RefPtr<Framework::AnimatorInfo>& animatorInfo);
    RefPtr<Framework::AnimatorInfo> GetJsAnimator(const std::string& animatorId);

    void BuildSharedTransitionMap();

    void ReloadPage();

    void SetFirstBuildCallback(std::function<void()>&& buildCallback);

    void SetPageInTransition(bool pageTransition)
    {
        isPageInTransition_ = pageTransition;
    }

    bool GetPageInTransition() const
    {
        return isPageInTransition_;
    }

    // Mark current page node invisible in render tree.
    void ProcessHideState();
    // Mark current page node visible in render tree.
    void ProcessShowState();

    bool ProcessAutoSave(const std::function<void()>& onFinish = nullptr,
        const std::function<void()>& onUIExtNodeBindingCompleted = nullptr);

    void MarkRenderDone()
    {
        isRenderDone_ = true;
    }

    void StopPageTransition();

    void SetDynamicPageSizeCallback(DynamicPageSizeCallback&& dynamicPageSizeCallback)
    {
        dynamicPageSizeCallback_ = std::move(dynamicPageSizeCallback);
    }

    void AddOnHiddenChange(int32_t id, PageVisibilityChangeCallback&& onHiddenChange)
    {
        onHiddenChange_[id] = std::move(onHiddenChange);
    }

    void FireOnHiddenChange(bool flag)
    {
        for (auto& onHiddenChangeInfo : onHiddenChange_) {
            if (onHiddenChangeInfo.second) {
                auto onHiddenChange = onHiddenChangeInfo.second;
                onHiddenChange(flag);
            }
        }
    }

    void UpdatePageParam()
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->SetAccessibilityVisible(true);
        host->SetJSViewActive(true);
    }

    void RemoveOnHiddenChange(int32_t id)
    {
        auto iter = onHiddenChange_.find(id);
        if (iter != onHiddenChange_.end()) {
            onHiddenChange_.erase(iter);
        }
    }

    void CreateOverlayManager(bool isShow)
    {
        if (!overlayManager_ && isShow) {
            overlayManager_ = MakeRefPtr<OverlayManager>(GetHost());
        }
    }

    const RefPtr<OverlayManager>& GetOverlayManager()
    {
        return overlayManager_;
    }

    void DeleteOverlayManager()
    {
        overlayManager_.Reset();
    }

    bool RemoveOverlay();
    void MarkDirtyOverlay();

    bool IsOnShow()
    {
        return isOnShow_;
    }

    bool GetIsModalCovered() const
    {
        return isModalCovered_;
    }

    void SetIsModalCovered(bool isModalCovered)
    {
        isModalCovered_ = isModalCovered;
    }

    void SetPageVisibilityChangeCallback(PageVisibilityChangeCallback&& callback)
    {
        visibilityChangeCallback_ = std::move(callback);
    }

    void SetAnimationId(int32_t animationId)
    {
        animationId_ = animationId;
    }

    int32_t GetAnimationId() const
    {
        return animationId_;
    }

    void InitTransitionIn(const RefPtr<PageTransitionEffect>& effect, PageTransitionType type);

    void InitTransitionOut(const RefPtr<PageTransitionEffect>& effect, PageTransitionType type);

    void TransitionInFinish(const RefPtr<PageTransitionEffect>& effect, PageTransitionType type);

    void TransitionOutFinish(const RefPtr<PageTransitionEffect>& effect, PageTransitionType type);

    void FinishOutPage(const int32_t animationId, PageTransitionType type);

    void FinishInPage(const int32_t animationId, PageTransitionType type);

    RefPtr<PageTransitionEffect> GetDefaultPageTransition(PageTransitionType type);

    void ResetPageTransitionEffect();

    void TriggerPageTransition(const std::function<void()>& onFinish, PageTransitionType type);

    void OnDetachFromFrameNode(FrameNode* frameNode) override;

    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;

    void SetIsNeedRemove(bool isNeedRemove)
    {
        isNeedRemove_ = isNeedRemove;
    }
    void CheckIsNeedForceExitWindow(bool result);
    void RemoveJsChildImmediately(const RefPtr<FrameNode>& page, PageTransitionType transactionType);

    bool IsNeedCallbackBackPressed();

protected:
    void OnAttachToFrameNode() override;
    void BeforeCreateLayoutWrapper() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& wrapper, const DirtySwapConfig& config) override;
    void BeforeSyncGeometryProperties(const DirtySwapConfig& config) override;
    void FirePageTransitionFinish();

    void OnAttachToMainTree() override;
    void OnDetachFromMainTree() override;

    bool AvoidKeyboard() const override;
    bool AvoidTop() const override
    {
        return true;
    }
    bool AvoidBottom() const override
    {
        return true;
    }

    bool AvoidCutout() const override
    {
        return true;
    }

    void NotifyPerfMonitorPageMsg(const std::string& pageUrl, const std::string& bundleName);

    RefPtr<PageTransitionEffect> GetPageTransitionEffect(const RefPtr<PageTransitionEffect>& transition);

    void SlideTransitionEffect(const SlideEffect& effect, const RectF& rect, TranslateOptions& translate);

    void UpdateDefaultEnterPopEffect(RefPtr<PageTransitionEffect>& effect, float statusHeight);

    void UpdateEnterPushEffect(RefPtr<PageTransitionEffect>& effect, float statusHeight);

    void UpdateExitPushEffect(RefPtr<PageTransitionEffect>& effect, float statusHeight);

    void UpdateAnimationOption(const RefPtr<PageTransitionEffect>& transition,
        RefPtr<PageTransitionEffect>& effect, AnimationOption& option, PageTransitionType type);

    virtual void TriggerDefaultTransition(const std::function<void()>& onFinish, PageTransitionType type);

    void MaskAnimation(const Color& initialBackgroundColor, const Color& backgroundColor);

    void NotifyNavigationLifecycle(bool isShow, bool isFromWindow);

    void RecordPageEvent(bool isShow);

    RefPtr<PageInfo> pageInfo_;
    RefPtr<OverlayManager> overlayManager_;

    std::function<void()> onPageShow_;
    std::function<void()> onPageHide_;
    std::function<bool()> onBackPressed_;
    std::function<void()> pageTransitionFunc_;
    std::function<void()> firstBuildCallback_;
    std::unordered_map<int32_t, PageVisibilityChangeCallback> onHiddenChange_;
    DynamicPageSizeCallback dynamicPageSizeCallback_;
    PageVisibilityChangeCallback visibilityChangeCallback_;
    std::shared_ptr<std::function<void()>> pageTransitionFinish_;
    std::list<RefPtr<PageTransitionEffect>> pageTransitionEffects_;
    std::function<void(const std::vector<std::string>&)> dumpListener_;

    int32_t animationId_ = -1;
    bool isOnShow_ = false;
    bool isFirstLoad_ = true;
    bool isPageInTransition_ = false;
    bool isRenderDone_ = false;
    bool isModalCovered_ = false;
    bool isNeedRemove_ = false;

#if defined(ENABLE_SPLIT_MODE)
    bool needFireObserver_ = true;
#endif

    SharedTransitionMap sharedTransitionMap_;
    JSAnimatorMap jsAnimatorMap_;
    RouterPageState state_ = RouterPageState::ABOUT_TO_APPEAR;
    std::shared_ptr<AnimationUtils::Animation> currCustomAnimation_;

    ACE_DISALLOW_COPY_AND_MOVE(PagePattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PAGE_PATTERN_H
