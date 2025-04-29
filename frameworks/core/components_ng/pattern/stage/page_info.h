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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PAGE_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PAGE_INFO_H

#include <cstdint>
#include <string>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components/dialog/dialog_properties.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT PageInfo : public AceType {
    DECLARE_ACE_TYPE(PageInfo, AceType);

public:
    PageInfo() = default;
    ~PageInfo() override = default;
    PageInfo(int32_t pageId, std::string url, std::string path)
        : pageId_(pageId), url_(std::move(url)), path_(std::move(path))
    {}
    int32_t GetPageId() const
    {
        return pageId_;
    }

    const std::string& GetPageUrl() const
    {
        return url_;
    }

    const std::string& GetPagePath() const
    {
        return path_;
    }

    const std::function<void(int32_t)>& GetAlertCallback() const
    {
        return alertCallback_;
    }

    const DialogProperties& GetDialogProperties() const
    {
        return dialogProperties_;
    }

    void SetAlertCallback(std::function<void(int32_t)>&& callback)
    {
        alertCallback_ = callback;
    }

    void SetDialogProperties(const DialogProperties& dialogProperties)
    {
        dialogProperties_ = dialogProperties;
    }

    void SetPageIndex(int32_t pageIndex)
    {
        pageIndex_ = pageIndex;
    }

    int32_t GetPageIndex() const
    {
        return pageIndex_;
    }

    void SetFullPath(const std::string& fullPath)
    {
        fullPath_ = fullPath;
    }

    const std::string& GetFullPath() const
    {
        return fullPath_;
    }

    std::optional<std::string> GetRouteName() const
    {
        return routeName_;
    }

    void SetRouteName(const std::optional<std::string>& name)
    {
        routeName_ = name;
    }

private:
    int32_t pageId_ = 0;
    int32_t pageIndex_ = -1;
    std::string url_;
    std::string path_;
    std::string fullPath_;

    std::optional<std::string> routeName_;

    std::function<void(int32_t)> alertCallback_;
    DialogProperties dialogProperties_;

    ACE_DISALLOW_COPY_AND_MOVE(PageInfo);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PAGE_INFO_H
