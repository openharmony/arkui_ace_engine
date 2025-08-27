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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_VIEW_DATA_WRAP_OHOS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_VIEW_DATA_WRAP_OHOS_H

#include "base/view_data/view_data_wrap.h"

#include <string>
#include <vector>

#include "view_data.h"

namespace OHOS::Ace {
class PageNodeInfoWrapOhos : public PageNodeInfoWrap {
    DECLARE_ACE_TYPE(PageNodeInfoWrapOhos, PageNodeInfoWrap);

public:
    PageNodeInfoWrapOhos() {}
    PageNodeInfoWrapOhos(const AbilityBase::PageNodeInfo& pageNodeInfo): pageNodeInfo_(pageNodeInfo) {}
    ~PageNodeInfoWrapOhos() = default;

    const AbilityBase::PageNodeInfo& GetPageNodeInfo() const;

    void SetId(int32_t id) override
    {
        pageNodeInfo_.id = id;
    }

    int32_t GetId() const override
    {
        return pageNodeInfo_.id;
    }

    void SetDepth(int32_t depth) override
    {
        pageNodeInfo_.depth = depth;
    }

    int32_t GetDepth() const override
    {
        return pageNodeInfo_.depth;
    }

    void SetAutoFillType(AceAutoFillType autoFillType) override
    {
        pageNodeInfo_.autoFillType = static_cast<AbilityBase::AutoFillType>(autoFillType);
    }

    AceAutoFillType GetAutoFillType() const override
    {
        return static_cast<AceAutoFillType>(pageNodeInfo_.autoFillType);
    }

    void SetTag(const std::string& tag) override
    {
        pageNodeInfo_.tag = tag;
    }

    const std::string& GetTag() const override
    {
        return pageNodeInfo_.tag;
    }

    void SetValue(const std::string& value) override
    {
        pageNodeInfo_.value = value;
    }

    const std::string& GetValue() const override
    {
        return pageNodeInfo_.value;
    }

    void SetPlaceholder(const std::string& placeholder) override
    {
        pageNodeInfo_.placeholder = placeholder;
    }

    const std::string& GetPlaceholder() const override
    {
        return pageNodeInfo_.placeholder;
    }

    void SetMetadata(const std::string& metadata) override
    {
        pageNodeInfo_.metadata = metadata;
    }

    const std::string& GetMetadata() const override
    {
        return pageNodeInfo_.metadata;
    }

    void SetPasswordRules(const std::string& passwordRules) override
    {
        pageNodeInfo_.passwordRules = passwordRules;
    }

    const std::string& GetPasswordRules() const override
    {
        return pageNodeInfo_.passwordRules;
    }

    void SetEnableAutoFill(bool enableAutoFill) override
    {
        pageNodeInfo_.enableAutoFill = enableAutoFill;
    }

    bool GetEnableAutoFill() const override
    {
        return pageNodeInfo_.enableAutoFill;
    }

    void SetIsFocus(bool isFocus) override
    {
        pageNodeInfo_.isFocus = isFocus;
    }

    bool GetIsFocus() const override
    {
        return pageNodeInfo_.isFocus;
    }

    void SetPageNodeRect(const NG::RectF& rect) override
    {
        pageNodeInfo_.rect.left = rect.GetX();
        pageNodeInfo_.rect.top = rect.GetY();
        pageNodeInfo_.rect.width = rect.Width();
        pageNodeInfo_.rect.height = rect.Height();
        pageNodeRect_ = rect;
    }

    const NG::RectF& GetPageNodeRect() const override
    {
        return pageNodeRect_;
    }

private:
    AbilityBase::PageNodeInfo pageNodeInfo_;
    NG::RectF pageNodeRect_;
};

class ViewDataWrapOhos : public ViewDataWrap {
    DECLARE_ACE_TYPE(ViewDataWrapOhos, ViewDataWrap);

public:
    ViewDataWrapOhos() {}
    ViewDataWrapOhos(const AbilityBase::ViewData& viewData);
    ~ViewDataWrapOhos() = default;

    const AbilityBase::ViewData& GetViewData();

    void SetBundleName(const std::string& bundleName) override
    {
        viewData_.bundleName = bundleName;
    }

    const std::string& GetBundleName() const override
    {
        return viewData_.bundleName;
    }

    void SetModuleName(const std::string& moduleName) override
    {
        viewData_.moduleName = moduleName;
    }

    const std::string& GetModuleName() const override
    {
        return viewData_.moduleName;
    }

    void SetAbilityName(const std::string& abilityName) override
    {
        viewData_.abilityName = abilityName;
    }

    const std::string& GetAbilityName() const override
    {
        return viewData_.abilityName;
    }

    void SetPageUrl(const std::string& pageUrl) override
    {
        viewData_.pageUrl = pageUrl;
    }

    const std::string& GetPageUrl() const override
    {
        return viewData_.pageUrl;
    }

    void AddPageNodeInfoWrap(RefPtr<PageNodeInfoWrap> pageNodeInfoWrap) override
    {
        pageNodeInfoWraps_.emplace_back(pageNodeInfoWrap);
    }

    const std::vector<RefPtr<PageNodeInfoWrap>>& GetPageNodeInfoWraps() override
    {
        return pageNodeInfoWraps_;
    }

    void SetPageRect(const NG::RectF& rect) override
    {
        viewData_.pageRect.left = rect.GetX();
        viewData_.pageRect.top = rect.GetY();
        viewData_.pageRect.width = rect.Width();
        viewData_.pageRect.height = rect.Height();
        pageRect_ = rect;
    }

    const NG::RectF& GetPageRect() const override
    {
        return pageRect_;
    }

    void SetUserSelected(bool isUserSelected) override
    {
        viewData_.isUserSelected = isUserSelected;
    }

    bool GetUserSelected() const override
    {
        return viewData_.isUserSelected;
    }

    void SetOtherAccount(bool isOtherAccount) override
    {
        viewData_.isOtherAccount = isOtherAccount;
    }

    bool GetOtherAccount() const override
    {
        return viewData_.isOtherAccount;
    }

private:
    std::vector<RefPtr<PageNodeInfoWrap>> pageNodeInfoWraps_;
    AbilityBase::ViewData viewData_;
    NG::RectF pageRect_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_VIEW_DATA_WRAP_OHOS_H
