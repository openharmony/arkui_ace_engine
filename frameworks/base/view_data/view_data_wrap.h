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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_VIEW_DATA_WRAP_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_VIEW_DATA_WRAP_H

#include "base/memory/ace_type.h"
#include "base/view_data/page_node_info_wrap.h"

namespace OHOS::AbilityBase {
struct ViewData;
enum class AutoFillType;
} // namespace OHOS::AbilityBase

namespace OHOS::Ace {
class ACE_EXPORT ViewDataWrap : public AceType {
    DECLARE_ACE_TYPE(ViewDataWrap, AceType);

public:
    static RefPtr<ViewDataWrap> CreateViewDataWrap();
    static RefPtr<ViewDataWrap> CreateViewDataWrap(const AbilityBase::ViewData& viewData);
    static AbilityBase::AutoFillType ViewDataToType(const AbilityBase::ViewData& viewData);
    static bool GetPlaceHolderValue(AbilityBase::ViewData& viewData);
    static bool LoadHint2Type(const std::vector<std::string>& placeHolder, std::vector<int>& type,
                                    std::vector<std::string>& metadata);
    static AbilityBase::AutoFillType HintToAutoFillType(const int& intType);

    virtual void SetBundleName(const std::string& bundleName) {}
    virtual const std::string& GetBundleName() const = 0;

    virtual void SetModuleName(const std::string& moduleName) {}
    virtual const std::string& GetModuleName() const = 0;

    virtual void SetAbilityName(const std::string& abilityName) {}
    virtual const std::string& GetAbilityName() const = 0;

    virtual void SetPageUrl(const std::string& pageUrl) {}
    virtual const std::string& GetPageUrl() const = 0;

    virtual void AddPageNodeInfoWrap(RefPtr<PageNodeInfoWrap> pageNodeInfoWrap) {}
    virtual const std::vector<RefPtr<PageNodeInfoWrap>>& GetPageNodeInfoWraps() = 0;

    virtual void SetPageRect(const NG::RectF& rect) {}
    virtual const NG::RectF& GetPageRect() const = 0;

    virtual void SetUserSelected(bool isUserSelected) {}
    virtual bool GetUserSelected() const = 0;

    virtual void SetOtherAccount(bool isOtherAccount) {}
    virtual bool GetOtherAccount() const = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_VIEW_DATA_WRAP_H
