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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_LAZY_LAYOUT_WRAPPER_BUILDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_LAZY_LAYOUT_WRAPPER_BUILDER_H

#include <optional>

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/syntax/lazy_for_each_builder.h"

namespace OHOS::Ace::NG {
class LazyForEachNode;

class LazyLayoutWrapperBuilder : public LayoutWrapperBuilder {
    DECLARE_ACE_TYPE(LazyLayoutWrapperBuilder, LayoutWrapperBuilder);
public:
    LazyLayoutWrapperBuilder(const RefPtr<LazyForEachBuilder>& builder, const WeakPtr<LazyForEachNode>& host);
    ~LazyLayoutWrapperBuilder() override = default;

    void SwapDirtyAndUpdateBuildCache() override;

    void AdjustGridOffset() override;

    void UpdateIndexRange(int32_t startIndex, int32_t endIndex, const std::list<std::optional<std::string>>& ids)
    {
        auto size = static_cast<int32_t>(ids.size());
        if ((size != 0) && (size != (endIndex - startIndex + 1))) {
            LOGE("fail to update index range due to ides not match!, %{public}d, %{public}d, %{public}d", startIndex,
                endIndex, size);
            return;
        }

        preStartIndex_ = startIndex;
        preEndIndex_ = endIndex;
        preNodeIds_ = ids;
    }

    void UpdateForceFlag(bool forceMeasure, bool forceLayout)
    {
        forceMeasure_ = forceMeasure;
        forceLayout_ = forceLayout;
    }

    const std::list<RefPtr<LayoutWrapper>>& GetCachedChildLayoutWrapper() override;

    void SetLazySwiper(bool flag = true)
    {
        lazySwiper_ = flag;
    }

protected:
    int32_t OnGetTotalCount() override;
    RefPtr<LayoutWrapper> OnGetOrCreateWrapperByIndex(int32_t index) override;
    const std::list<RefPtr<LayoutWrapper>>& OnExpandChildLayoutWrapper() override;

private:
    RefPtr<LazyForEachBuilder> builder_;
    WeakPtr<LazyForEachNode> host_;

    int32_t preStartIndex_ = -1;
    int32_t preEndIndex_ = -1;
    std::list<std::optional<std::string>> preNodeIds_;

    std::optional<int32_t> startIndex_;
    std::optional<int32_t> endIndex_;
    std::list<std::optional<std::string>> nodeIds_;

    std::optional<std::string> GetKeyByIndexFromPreNodes(int32_t index);
    std::pair<RefPtr<UINode>, std::string> GetOrCreateFrameNode(int32_t index, int32_t totalCount);
    RefPtr<LayoutWrapper> OnGetOrCreateWrapperByIndexLegacy(int32_t index);

    std::list<RefPtr<LayoutWrapper>> childWrappers_;

    bool forceMeasure_ = false;
    bool forceLayout_ = false;
    bool lazySwiper_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(LazyLayoutWrapperBuilder);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_LAZY_LAYOUT_WRAPPER_BUILDER_H
