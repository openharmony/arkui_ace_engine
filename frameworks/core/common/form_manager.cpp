/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/common/form_manager.h"

namespace OHOS::Ace {
FormManager::FormManager() {}

FormManager::~FormManager() {}

void FormManager::AddSubContainer(int64_t formId, const RefPtr<SubContainer>& subContainer)
{
    std::lock_guard<std::mutex> lock(mutex_);
    subContainerMap_.insert_or_assign(formId, subContainer);
}

void FormManager::RemoveSubContainer(int64_t formId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    subContainerMap_.erase(formId);
}

RefPtr<SubContainer> FormManager::GetSubContainer(int64_t formId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto subContainer = subContainerMap_.find(formId);
    if (subContainer != subContainerMap_.end()) {
        return subContainer->second;
    } else {
        return nullptr;
    }
}

void FormManager::SetFormUtils(const std::shared_ptr<FormUtils>& formUtils)
{
    std::lock_guard<std::mutex> lock(formUtilsMutex_);
    CHECK_NULL_VOID(formUtils);
    formUtils_ = formUtils;
}

std::shared_ptr<FormUtils> FormManager::GetFormUtils()
{
    std::lock_guard<std::mutex> lock(formUtilsMutex_);
    CHECK_NULL_RETURN(formUtils_, nullptr);
    return formUtils_;
}

void FormManager::NotifyIsSizeChangeByRotate(bool isRotate,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    rsTransaction_ = rsTransaction;
    isRotate_ = isRotate;
}

} // namespace OHOS::Ace
