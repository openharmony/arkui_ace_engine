/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <dlfcn.h>
#include "view_data_wrap_ohos.h"

namespace OHOS::Ace {
#ifdef APP_USE_ARM
constexpr char LIB_HINT2_TYPE_Z_SO_NAME[] = "/system/lib/module/core/atomicservicecomponent/libhint2type.z.so";
#elif defined(APP_USE_X86_64)
constexpr char LIB_HINT2_TYPE_Z_SO_NAME[] = "/system/lib64/module/core/atomicservicecomponent/libhint2type.z.so";
#else
constexpr char LIB_HINT2_TYPE_Z_SO_NAME[] = "/system/lib64/module/core/atomicservicecomponent/libhint2type.z.so";
#endif
constexpr char HINT_2_TYPE[] = "Hint2Type";
using Hint2Type = int (*) (std::vector<std::string>, std::vector<int>&, std::vector<std::string>&);

RefPtr<PageNodeInfoWrap> PageNodeInfoWrap::CreatePageNodeInfoWrap()
{
    return AceType::MakeRefPtr<PageNodeInfoWrapOhos>();
}

const AbilityBase::PageNodeInfo& PageNodeInfoWrapOhos::GetPageNodeInfo() const
{
    return pageNodeInfo_;
}

RefPtr<ViewDataWrap> ViewDataWrap::CreateViewDataWrap()
{
    return AceType::MakeRefPtr<ViewDataWrapOhos>();
}

AbilityBase::AutoFillType ViewDataWrap::ViewDataToType(const AbilityBase::ViewData& viewData)
{
    auto type = AbilityBase::AutoFillType::UNSPECIFIED;
    for (auto it = viewData.nodes.begin(); it != viewData.nodes.end(); ++it) {
        if (!it->value.empty()) {
            if (type < it->autoFillType && it->autoFillType < AbilityBase::AutoFillType::FULL_STREET_ADDRESS) {
                return it->autoFillType;
            }
        }
    }
    for (auto it = viewData.nodes.begin(); it != viewData.nodes.end(); ++it) {
        if (!it->value.empty()) {
            if (AbilityBase::AutoFillType::FULL_STREET_ADDRESS <= it->autoFillType &&
                it->autoFillType <= AbilityBase::AutoFillType::FORMAT_ADDRESS) {
                return it->autoFillType;
            }
        }
    }
    return type;
}

bool ViewDataWrap::LoadHint2Type(const std::vector<std::string>& placeHolder, std::vector<int>& intType,
                                 std::vector<std::string>& metadata)
{
    void* handle = dlopen(LIB_HINT2_TYPE_Z_SO_NAME, RTLD_LAZY);
    if (handle == nullptr) {
        LOGE("Failed to open libhint2type library %{public}s, reason: %{public}sn",
            LIB_HINT2_TYPE_Z_SO_NAME, dlerror());
        return false;
    }
    Hint2Type hintFun = reinterpret_cast<Hint2Type>(dlsym(handle, HINT_2_TYPE));
    if (hintFun == nullptr) {
        dlclose(handle);
        LOGE("Failed to get symbol %{public}s in %{public}s", HINT_2_TYPE, LIB_HINT2_TYPE_Z_SO_NAME);
        return false;
    }
    if (hintFun(placeHolder, intType, metadata)) {
        LOGE("Failed to Hint 2 intType");
        dlclose(handle);
        return false;
    }
    dlclose(handle);
    return true;
}

bool ViewDataWrap::GetPlaceHolderValue(AbilityBase::ViewData& viewData)
{
    std::vector<std::string> placeHolder;
    std::vector<int> intType;
    std::vector<std::string> metadata;
    for (auto it = viewData.nodes.begin(); it != viewData.nodes.end(); ++it) {
        if (it->autoFillType == AbilityBase::AutoFillType::UNSPECIFIED) {
            placeHolder.push_back(it->placeholder);
        }
    }
    auto isSuccessLoadHint2Type = LoadHint2Type(placeHolder, intType, metadata);
    if (!isSuccessLoadHint2Type) {
        LOGE("Load Hint2Type Failed !");
        return false;
    }
    size_t  index = 0;
    for (auto it = viewData.nodes.begin(); it != viewData.nodes.end(); ++it) {
        if (index >= intType.size()) {
            LOGE("intType size err !");
            break;
        }
        if (it->autoFillType == AbilityBase::AutoFillType::UNSPECIFIED) {
            it->autoFillType = HintToAutoFillType(intType[index]);
            ++index;
        }
    }
    return true;
}

AbilityBase::AutoFillType ViewDataWrap::HintToAutoFillType(const int& intType)
{
    std::vector<AbilityBase::AutoFillType> hintVector = {
        AbilityBase::AutoFillType::UNSPECIFIED,
        AbilityBase::AutoFillType::NICKNAME,
        AbilityBase::AutoFillType::PERSON_FULL_NAME,
        AbilityBase::AutoFillType::PERSON_LAST_NAME,
        AbilityBase::AutoFillType::PERSON_FIRST_NAME,
        AbilityBase::AutoFillType::PHONE_NUMBER,
        AbilityBase::AutoFillType::PHONE_COUNTRY_CODE,
        AbilityBase::AutoFillType::FULL_PHONE_NUMBER,
        AbilityBase::AutoFillType::EMAIL_ADDRESS,
        AbilityBase::AutoFillType::ID_CARD_NUMBER,
        AbilityBase::AutoFillType::FORMAT_ADDRESS,
        AbilityBase::AutoFillType::COUNTRY_ADDRESS,
        AbilityBase::AutoFillType::PROVINCE_ADDRESS,
        AbilityBase::AutoFillType::CITY_ADDRESS,
        AbilityBase::AutoFillType::DISTRICT_ADDRESS,
        AbilityBase::AutoFillType::FULL_STREET_ADDRESS,
        AbilityBase::AutoFillType::DETAIL_INFO_WITHOUT_STREET,
        AbilityBase::AutoFillType::HOUSE_NUMBER,
        AbilityBase::AutoFillType::BANK_CARD_NUMBER };

    if (intType < 0 || (size_t)intType >= hintVector.size()) {
        return hintVector[0];
    }
    return hintVector[intType];
}

RefPtr<ViewDataWrap> ViewDataWrap::CreateViewDataWrap(const AbilityBase::ViewData& viewData)
{
    return AceType::MakeRefPtr<ViewDataWrapOhos>(viewData);
}

ViewDataWrapOhos::ViewDataWrapOhos(const AbilityBase::ViewData& viewData): viewData_(viewData)
{
    for (const auto& node: viewData.nodes) {
        pageNodeInfoWraps_.emplace_back(AceType::MakeRefPtr<PageNodeInfoWrapOhos>(node));
    }
}

const AbilityBase::ViewData& ViewDataWrapOhos::GetViewData()
{
    viewData_.nodes.clear();
    for (const auto& nodeWrap: pageNodeInfoWraps_) {
        auto nodeWrapOhos = AceType::DynamicCast<PageNodeInfoWrapOhos>(nodeWrap);
        if (nodeWrapOhos) {
            viewData_.nodes.emplace_back(nodeWrapOhos->GetPageNodeInfo());
        }
    }
    return viewData_;
}
} // namespace OHOS::Ace
