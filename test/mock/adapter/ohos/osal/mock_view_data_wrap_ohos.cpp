/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "base/view_data/view_data_wrap.h"

namespace OHOS::Ace {

class ViewDataWrapOhos : public OHOS::Ace::ViewDataWrap {
public:
    ViewDataWrapOhos() {}
    explicit ViewDataWrapOhos(const OHOS::AbilityBase::ViewData& viewData);
    ~ViewDataWrapOhos() = default;

    const OHOS::AbilityBase::ViewData& GetViewData();

    void SetBundleName(const std::string& bundleName) override
    {
        return;
    }

    const std::string& GetBundleName() const override
    {
        return name_;
    }

    void SetModuleName(const std::string& moduleName) override
    {
        return;
    }

    const std::string& GetModuleName() const override
    {
        return name_;
    }

    void SetAbilityName(const std::string& abilityName) override
    {
        return;
    }

    const std::string& GetAbilityName() const override
    {
        return name_;
    }

    void SetPageUrl(const std::string& pageUrl) override
    {
        return ;
    }

    const std::string& GetPageUrl() const override
    {
        return name_;
    }

    void AddPageNodeInfoWrap(OHOS::Ace::RefPtr<OHOS::Ace::PageNodeInfoWrap> pageNodeInfoWrap) override
    {
        return;
    }

    const std::vector<OHOS::Ace::RefPtr<OHOS::Ace::PageNodeInfoWrap>>& GetPageNodeInfoWraps() override
    {
        return pageNodeInfoWraps_;
    }

    void SetPageRect(const OHOS::Ace::NG::RectF& rect) override
    {
        return;
    }

    const OHOS::Ace::NG::RectF& GetPageRect() const override
    {
        return pageRect_;
    }

    void SetUserSelected(bool isUserSelected) override
    {
        return;
    }

    bool GetUserSelected() const override
    {
        return isUserSelected_;
    }

    void SetOtherAccount(bool isOtherAccount) override
    {
        return;
    }

    bool GetOtherAccount() const override
    {
        return true;
    }

private:
    std::vector<OHOS::Ace::RefPtr<OHOS::Ace::PageNodeInfoWrap>> pageNodeInfoWraps_;
    OHOS::Ace::NG::RectF pageRect_;
    bool isUserSelected_ = false;
    std::string name_;
};
    
class PageNodeInfoWrapOhos : public OHOS::Ace::PageNodeInfoWrap {
public:
    PageNodeInfoWrapOhos() {}
    ~PageNodeInfoWrapOhos() = default;

    const OHOS::AbilityBase::PageNodeInfo& GetPageNodeInfo() const;

    void SetId(int32_t id) override
    {
        return;
    }

    int32_t GetId() const override
    {
        return 0;
    }

    void SetDepth(int32_t depth) override
    {
        return;
    }

    int32_t GetDepth() const override
    {
        return 0;
    }

    void SetAutoFillType(OHOS::Ace::AceAutoFillType autoFillType) override
    {
        return;
    }

    OHOS::Ace::AceAutoFillType GetAutoFillType() const override
    {
        return static_cast<OHOS::Ace::AceAutoFillType>(autoFillType);
    }

    void SetTag(const std::string& tag) override
    {
        return;
    }

    const std::string& GetTag() const override
    {
        return str_;
    }

    void SetValue(const std::string& value) override
    {
        return;
    }

    const std::string& GetValue() const override
    {
        return str_;
    }

    void SetPlaceholder(const std::string& placeholder) override
    {
        return;
    }

    const std::string& GetPlaceholder() const override
    {
        return str_;
    }

    void SetMetadata(const std::string& metadata) override
    {
        return;
    }

    const std::string& GetMetadata() const override
    {
        return str_;
    }

    void SetPasswordRules(const std::string& passwordRules) override
    {
        return;
    }

    const std::string& GetPasswordRules() const override
    {
        return str_;
    }

    void SetEnableAutoFill(bool enableAutoFill) override
    {
        return;
    }

    bool GetEnableAutoFill() const override
    {
        return false;
    }

    void SetIsFocus(bool isFocus) override
    {
        return;
    }

    bool GetIsFocus() const override
    {
        return false;
    }

    void SetPageNodeRect(const OHOS::Ace::NG::RectF& rect) override
    {
        pageNodeRect_ = rect;
    }

    const OHOS::Ace::NG::RectF& GetPageNodeRect() const override
    {
        return pageNodeRect_;
    }

private:
    OHOS::Ace::AceAutoFillType autoFillType;
    OHOS::Ace::NG::RectF pageNodeRect_;
    std::string str_;
};

RefPtr<PageNodeInfoWrap> PageNodeInfoWrap::CreatePageNodeInfoWrap()
{
    return AceType::MakeRefPtr<PageNodeInfoWrapOhos>();
}

RefPtr<ViewDataWrap> ViewDataWrap::CreateViewDataWrap()
{
    return AceType::MakeRefPtr<ViewDataWrapOhos>();
}

RefPtr<ViewDataWrap> ViewDataWrap::CreateViewDataWrap(const AbilityBase::ViewData& viewData)
{
    return nullptr;
}
} // namespace OHOS::Ace