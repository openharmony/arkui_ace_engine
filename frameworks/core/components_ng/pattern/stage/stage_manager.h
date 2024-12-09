/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_STAGE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_STAGE_MANAGER_H

#include <cstdint>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/animation/page_transition_common.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/stage/page_transition_effect.h"

namespace OHOS::Ace::NG {
class FrameNode;
class OverlayManager;

// StageManager is the base class for root render node to perform page switch.
class ACE_FORCE_EXPORT StageManager : public virtual AceType {
    DECLARE_ACE_TYPE(StageManager, AceType);

public:
    explicit StageManager(const RefPtr<FrameNode>& stage);
    ~StageManager() override = default;

    // PushUrl and ReplaceUrl both use PushPage function
    virtual bool PushPage(const RefPtr<FrameNode>& node, bool needHideLast = true, bool needTransition = true);
    virtual bool InsertPage(const RefPtr<FrameNode>& node, bool bellowTopOrBottom);
    virtual bool PopPage(const RefPtr<FrameNode>& inPageNode, bool needShowNext = true, bool needTransition = true);
    virtual bool PopPageToIndex(int32_t index, bool needShowNext = true, bool needTransition = true);
    virtual bool CleanPageStack();
    virtual bool MovePageToFront(const RefPtr<FrameNode>& node, bool needHideLast = true, bool needTransition = true);

    virtual void StartTransition(const RefPtr<FrameNode>& srcPage, const RefPtr<FrameNode>& destPage, RouteType type);

    void PageChangeCloseKeyboard();

    static void FirePageHide(const RefPtr<UINode>& node, PageTransitionType transitionType = PageTransitionType::NONE);
    static void FirePageShow(const RefPtr<UINode>& node, PageTransitionType transitionType = PageTransitionType::NONE,
        bool needFocus = true);

    virtual RefPtr<FrameNode> GetLastPage() const;
    RefPtr<FrameNode> GetPageById(int32_t pageId);
    const RefPtr<FrameNode> GetStageNode() const
    {
        return stageNode_;
    }

    void ReloadStage();

    virtual RefPtr<FrameNode> GetLastPageWithTransition() const;
    virtual RefPtr<FrameNode> GetPrevPageWithTransition() const;

    virtual RefPtr<FrameNode> GetFocusPage() const
    {
        return nullptr;
    }

    void SetStageInTrasition (bool stageInTrasition) {
        stageInTrasition_ = stageInTrasition;
    }

#if defined(ENABLE_SPLIT_MODE)
    bool IsNewPageReplacing() const
    {
        return isNewPageReplacing_;
    }

    void SetIsNewPageReplacing(bool replacing)
    {
        isNewPageReplacing_ = replacing;
    }
#endif

    virtual void SyncPageSafeArea(bool keyboardSafeArea);
    
    virtual bool CheckPageFocus();

    void SetSrcPage(const RefPtr<FrameNode>& pageNode)
    {
        srcPageNode_ = pageNode;
    }

    void AddAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation, bool isPush)
    {
        if (isPush) {
            pushAnimations_.emplace_back(animation);
            return;
        }
        popAnimations_.emplace_back(animation);
    }

    void AbortAnimation();

    int32_t GetAnimationId() const
    {
        return animationId_;
    }

protected:
    // ace performance check
    void PerformanceCheck(const RefPtr<FrameNode>& pageNode, int64_t vsyncTimeout, std::string path);
    void FireAutoSave(const RefPtr<FrameNode>& outPageNode, const RefPtr<FrameNode>& inPageNode);
    void AddPageTransitionTrace(const RefPtr<FrameNode>& srcPage, const RefPtr<FrameNode>& destPage);
    std::string GetSrcPageInfo(const RefPtr<FrameNode>& srcPage);
    void UpdatePageNeedRemove(const RefPtr<UINode>& pageNode);
    bool CheckPageInTransition(const RefPtr<UINode>& pageNode);

    std::list<std::shared_ptr<AnimationUtils::Animation>> pushAnimations_;
    std::list<std::shared_ptr<AnimationUtils::Animation>> popAnimations_;

    RefPtr<FrameNode> stageNode_;
    RefPtr<StagePattern> stagePattern_;
    WeakPtr<FrameNode> destPageNode_;
    WeakPtr<FrameNode> srcPageNode_;
    int32_t animationId_ = -1;
    bool stageInTrasition_ = false;
#if defined(ENABLE_SPLIT_MODE)
    bool isNewPageReplacing_ = false;
#endif
    std::string replaceSrcPageInfo_;

    ACE_DISALLOW_COPY_AND_MOVE(StageManager);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_STAGE_MANAGER_H
