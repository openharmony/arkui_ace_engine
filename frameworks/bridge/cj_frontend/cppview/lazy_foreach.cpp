/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/cppview/lazy_foreach.h"

#include "bridge/cj_frontend/cppview/data_change_listener.h"
#include "core/components_ng/base/view_stack_model.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::Framework {

void CJLazyForEachBuilder::OnExpandChildrenOnInitialInNG()
{
    auto totalIndex = cjBuilder_->GetTotalCount();
    for (auto index = 0; index < totalIndex; index++) {
        auto key = cjBuilder_->GenerateKey(index);
        ViewStackModel::GetInstance()->PushKey(key);
        cjBuilder_->GenerateItem(index);
        ViewStackModel::GetInstance()->PopKey();
    }
}

std::pair<std::string, RefPtr<NG::UINode>> CJLazyForEachBuilder::OnGetChildByIndex(
    int32_t index, std::unordered_map<std::string, std::pair<int32_t, RefPtr<NG::UINode>>>& cachedItems)
{
    std::pair<std::string, RefPtr<NG::UINode>> result;
    auto key = cjBuilder_->GenerateKey(index);
    auto cachedIter = cachedItems.find(key);
    if (cachedIter != cachedItems.end()) {
        result.first = key;
        result.second = cachedIter->second.second;
        return result;
    }
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    auto* viewStack = ViewStackModel::GetInstance();
    cjBuilder_->MarkLazyForEachProcess(key);
    viewStack->PushKey(key);
    cjBuilder_->GenerateItem(index);
    viewStack->PopKey();
    cjBuilder_->ResetLazyForEachProcess();
    result.first = key;
    auto view = ViewStackModel::GetInstance()->Finish();
    result.second = AceType::DynamicCast<NG::UINode>(view);

    return result;
}

std::pair<std::string, RefPtr<NG::UINode>> CJLazyForEachBuilder::OnGetChildByIndexNew(int32_t index,
    std::map<int32_t, NG::LazyForEachChild>& cachedItems,
    std::unordered_map<std::string, NG::LazyForEachCacheChild>& expiringItems)
{
    std::pair<std::string, RefPtr<NG::UINode>> result;
    auto key = cjBuilder_->GenerateKey(index);
    auto cachedIter = cachedItems.find(index);
    if (cachedIter != cachedItems.end()) {
        result.first = key;
        result.second = cachedIter->second.second;
        return result;
    }
    auto expiringIter = expiringItems.find(key);
    if (expiringIter != expiringItems.end()) {
        result.first = key;
        result.second = expiringIter->second.second;
        expiringItems.erase(expiringIter);
        return result;
    }
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    auto* viewStack = ViewStackModel::GetInstance();
    cjBuilder_->MarkLazyForEachProcess(key);
    viewStack->PushKey(key);
    cjBuilder_->GenerateItem(index);
    viewStack->PopKey();
    cjBuilder_->ResetLazyForEachProcess();
    result.first = key;
    auto view = ViewStackModel::GetInstance()->Finish();
    result.second = AceType::DynamicCast<NG::UINode>(view);

    return result;
}

void CJLazyForEachBuilder::ReleaseChildGroupById(const std::string& id)
{
    cjBuilder_->RemoveChildGroupById(id);
}

void CJLazyForEachBuilder::RegisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener)
{
    if (!listener) {
        return;
    }
    auto listenerManager = weakListenerManager_.promote();
    if (listenerManager) {
        listenerManager->AddListener(listener);
        return;
    }
    listenerManager = FFIData::Create<CJDataChangeListener>();
    listenerManager->AddListener(listener);
    weakListenerManager_ = listenerManager;
    cjBuilder_->RegisterListenerFunc(listenerManager);
}

void CJLazyForEachBuilder::UnregisterDataChangeListener(V2::DataChangeListener* listener)
{
    if (!listener) {
        LOGW("CJLazyForEachBuilder listener is null");
        return;
    }
    auto listenerManager = weakListenerManager_.promote();
    if (!listenerManager) {
        // this would happen before first RegisterDataChangeListener called
        // this would happen after cj released listenerManager
        LOGW("LazyForEach::UnregisterDataChangeListener fail, listenerManager is null.");
        return;
    }
    listenerManager->RemoveListener(WeakClaim(listener));
}

} // namespace OHOS::Ace::Framework
