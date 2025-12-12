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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PARALLEL_PAGE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PARALLEL_PAGE_PATTERN_H

#include <functional>

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/stage/page_info.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {

enum class RouterPageType : int32_t {
    PRIMARY_PAGE = 0,
    SECONDARY_PAGE = 1,
    PLACEHOLDER_PAGE = 2,
    RELATED_PAGE = 3
};

// ParallelPagePattern is the base class for page root render node.
class ParallelPagePattern : public PagePattern {
    DECLARE_ACE_TYPE(ParallelPagePattern, PagePattern);

public:
    explicit ParallelPagePattern(const RefPtr<PageInfo>& pageInfo) : PagePattern(pageInfo) {}
    ~ParallelPagePattern() = default;

    void OnShow(bool isAppStateChange = false) override;

    void OnHide(bool isAppStateChange = false) override;

    void SetPageType(RouterPageType type)
    {
        type_ = type;
        if (type == RouterPageType::PLACEHOLDER_PAGE) {
            needFireObserver_ = false;
        }
    }

    RouterPageType GetPageType() const
    {
        return type_;
    }

    bool IsPageBuildCompleted() const
    {
        return isPageBuildCompleted_;
    }

    void SetIsPageBuildCompleted(bool completed)
    {
        isPageBuildCompleted_ = completed;
    }

    bool GetIsShow() const
    {
        return isOnShow_;
    }

    void InitOnTouchEvent();

    void RemoveOnTouchEvent();

    void NotifyAboutToDisappear();
    void SetNeedNotifyRelatedPageAboutToDisappear(bool need)
    {
        needNotifyRelatedPageAboutToDisappear_ = need;
    }

private:
    bool IsShowOrHideAllowed();
    void BeforeCreateLayoutWrapper() override;
    void OnAttachToMainTree() override;
    void OnDetachFromMainTree() override;

    RouterPageType type_ = RouterPageType::SECONDARY_PAGE;
    bool isPageBuildCompleted_ = false;
    RefPtr<TouchEventImpl> touchListener_ = nullptr;
    bool needNotifyRelatedPageAboutToAppear_ = true;
    bool needNotifyRelatedPageAboutToDisappear_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(ParallelPagePattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PARALLEL_PAGE_PATTERN_H
