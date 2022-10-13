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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_WRAPPER_BUILDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_WRAPPER_BUILDER_H

#include <list>
#include <map>
#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace::NG {

class LayoutWrapper;

class LayoutWrapperBuilder : public AceType {
    DECLARE_ACE_TYPE(LayoutWrapperBuilder, AceType)
public:
    LayoutWrapperBuilder() = default;
    ~LayoutWrapperBuilder() override = default;

    RefPtr<LayoutWrapper> GetOrCreateWrapperByIndex(int32_t index);

    virtual const std::list<RefPtr<LayoutWrapper>>& GetCachedChildLayoutWrapper() = 0;

    const std::list<RefPtr<LayoutWrapper>>& ExpandAllChildWrappers();

    int32_t GetTotalCount()
    {
        return OnGetTotalCount();
    }

    void SetStartIndex(int32_t startIndex)
    {
        startIndex_ = startIndex;
    }

    int32_t GetStartIndex() const
    {
        return startIndex_;
    }

    void SetCacheCount(int32_t cacheCount)
    {
        cacheCount_ = cacheCount;
    }

    virtual void SwapDirtyAndUpdateBuildCache() {}

protected:
    virtual int32_t OnGetTotalCount() = 0;
    virtual RefPtr<LayoutWrapper> OnGetOrCreateWrapperByIndex(int32_t index) = 0;
    virtual const std::list<RefPtr<LayoutWrapper>>& OnExpandChildLayoutWrapper() = 0;

    std::unordered_map<int32_t, RefPtr<LayoutWrapper>> wrapperMap_;

    int32_t startIndex_ = 0;
    int32_t cacheCount_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(LayoutWrapperBuilder);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_WRAPPER_BUILDER_H
