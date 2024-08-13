/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_PAGE_NODE_INFO_WRAP_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_PAGE_NODE_INFO_WRAP_H

#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "base/view_data/ace_auto_fill_type.h"

namespace OHOS::AbilityBase {
struct Rect;
struct PageNodeInfo;
} // namespace OHOS::AbilityBase

namespace OHOS::Ace {
class PageNodeInfoWrap : public AceType {
    DECLARE_ACE_TYPE(PageNodeInfoWrap, AceType);

public:
    static RefPtr<PageNodeInfoWrap> CreatePageNodeInfoWrap();

    virtual void SetId(int32_t id) {}
    virtual int32_t GetId() const
    {
        return 0;
    }

    virtual void SetDepth(int32_t depth) {}
    virtual int32_t GetDepth() const
    {
        return 0;
    }

    virtual void SetAutoFillType(AceAutoFillType autoFillType) {}
    virtual AceAutoFillType GetAutoFillType() const
    {
        return AceAutoFillType::ACE_UNSPECIFIED;
    }

    virtual void SetTag(const std::string& tag) {}
    virtual const std::string& GetTag() const = 0;

    virtual void SetValue(const std::string& value) {}
    virtual const std::string& GetValue() const = 0;

    virtual void SetPlaceholder(const std::string& placeholder) {}
    virtual const std::string& GetPlaceholder() const = 0;

    virtual void SetMetadata(const std::string& metadata) {}
    virtual const std::string& GetMetadata() const = 0;

    virtual void SetPasswordRules(const std::string& passwordRules) {}
    virtual const std::string& GetPasswordRules() const = 0;

    virtual void SetEnableAutoFill(bool enableAutoFill) {}
    virtual bool GetEnableAutoFill() const
    {
        return false;
    }

    virtual void SetIsFocus(bool isFocus) {}
    virtual bool GetIsFocus() const
    {
        return false;
    }

    virtual void SetPageNodeRect(const NG::RectF& rect) {}
    virtual const NG::RectF& GetPageNodeRect() const = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_PAGE_NODE_INFO_WRAP_H