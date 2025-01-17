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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_NG_ENTRY_PAGE_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_NG_ENTRY_PAGE_INFO_H

#include <cstdint>
#include <string>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "bridge/common/utils/source_map.h"
#include "core/components_ng/pattern/stage/page_info.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT EntryPageInfo : public PageInfo {
    DECLARE_ACE_TYPE(EntryPageInfo, PageInfo)
public:
    EntryPageInfo(int32_t pageId, const std::string& url, const std::string& path, std::string params,
        bool recoverable = true, bool isCreateByNamedRouter = false)
        : PageInfo(pageId, url, path), params_(std::move(params)), recoverable_(recoverable),
        isCreateByNamedRouter_(isCreateByNamedRouter)
    {}
    ~EntryPageInfo() override = default;

    const std::string& GetPageParams() const
    {
        return params_;
    }

    std::string ReplacePageParams(const std::string& param)
    {
        std::string old(std::move(params_));
        params_ = param;
        return old;
    }

    bool IsRecoverable() const
    {
        return recoverable_;
    }

    bool ReplaceRecoverable(bool recoverable)
    {
        bool old = recoverable_;
        recoverable_ = recoverable;
        return old;
    }

    bool IsCreateByNamedRouter() const
    {
        return isCreateByNamedRouter_;
    }

    void SetPageMap(const RefPtr<Framework::RevSourceMap>& pageMap)
    {
        pageMap_ = pageMap;
    }

    const RefPtr<Framework::RevSourceMap>& GetPageMap() const
    {
        return pageMap_;
    }

    void SetShowTime(int64_t time)
    {
        showTime_ = time;
    }

    int64_t GetShowTime() const
    {
        return showTime_;
    }

private:
    std::string params_;
    bool recoverable_ = true;
    bool isCreateByNamedRouter_ = false;
    int64_t showTime_ = 0;
    RefPtr<Framework::RevSourceMap> pageMap_;

    ACE_DISALLOW_COPY_AND_MOVE(EntryPageInfo);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_NG_ENTRY_PAGE_INFO_H