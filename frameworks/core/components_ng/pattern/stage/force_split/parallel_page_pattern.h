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
};

using LoadPlaceHolderPageCallback = std::function<RefPtr<FrameNode>()>;

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

    bool IsPlaceHolderPageBuildCompleted() const
    {
        return isPHPagedBuildCompleted_;
    }

    void SetIsPlaceHolderPageBuildCompleted(bool completed)
    {
        isPHPagedBuildCompleted_ = completed;
    }

    void SetPrimaryPage(const WeakPtr<FrameNode>& primaryPage)
    {
        primaryPage_ = primaryPage;
    }

    RefPtr<FrameNode> GetPrimaryPage() const
    {
        return primaryPage_.Upgrade();
    }

    void SetPrePrimaryPage(const WeakPtr<FrameNode>& prePrimaryPage)
    {
        prePrimaryPage_ = prePrimaryPage;
    }

    RefPtr<FrameNode> GetPrePrimaryPage() const
    {
        return prePrimaryPage_.Upgrade();
    }

    RefPtr<FrameNode> GetOrCreatePlaceHolderPage();

    void SetLoadPlaceHolderPageCallback(LoadPlaceHolderPageCallback&& callback)
    {
        loadPlaceHolderPageCallback_ = std::move(callback);
    }

    bool GetIsShow() const
    {
        return isOnShow_;
    }

    void InitOnTouchEvent();

    void RemoveOnTouchEvent();

private:
    bool IsShowOrHideAllowed();
    void BeforeCreateLayoutWrapper() override;

    RouterPageType type_ = RouterPageType::SECONDARY_PAGE;
    RefPtr<FrameNode> placeHolderPage_;
    bool isPHPagedBuildCompleted_ = false;
    WeakPtr<FrameNode> primaryPage_;
    WeakPtr<FrameNode> prePrimaryPage_;
    LoadPlaceHolderPageCallback loadPlaceHolderPageCallback_;
    RefPtr<TouchEventImpl> touchListener_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(ParallelPagePattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PARALLEL_PAGE_PATTERN_H
