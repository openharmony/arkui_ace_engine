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

#ifndef ACE_ENGINE_CJ_LAZYFOREACH_H
#define ACE_ENGINE_CJ_LAZYFOREACH_H

#include <string>

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "bridge/cj_frontend/cppview/lazy_foreach_func.h"
#include "bridge/cj_frontend/cppview/native_view.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_native_view_ffi.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_for_each_builder.h"

namespace OHOS {
namespace Ace {
namespace Framework {

class ACE_EXPORT CJLazyForEachBuilder : public NG::LazyForEachBuilder, public LazyForEachActuator {
    DECLARE_ACE_TYPE(CJLazyForEachBuilder, NG::LazyForEachBuilder, LazyForEachActuator);
public:
    explicit CJLazyForEachBuilder(sptr<LazyForEachFuncs>&& cjBuilder) : cjBuilder_(cjBuilder) {}
    int32_t OnGetTotalCount() override
    {
        return cjBuilder_->GetTotalCount();
    }
    void OnExpandChildrenOnInitialInNG() override;
    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, std::pair<int32_t, RefPtr<NG::UINode>>>& cachedItems) override;
    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndexNew(int32_t index,
        std::map<int32_t, NG::LazyForEachChild>& cachedItems,
        std::unordered_map<std::string, NG::LazyForEachCacheChild>& expiringItems) override;
    void ReleaseChildGroupById(const std::string& id) override;
    void RegisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) override;
    void UnregisterDataChangeListener(V2::DataChangeListener* listener) override;
    bool DeleteExpiringItemImmediately() override
    {
        return false;
    }
    void NotifyDataChanged(size_t index, const RefPtr<NG::UINode>& lazyForEachNode, bool isRebuild = true) override {};
    void NotifyDataDeleted(const RefPtr<NG::UINode>& lazyForEachNode, size_t index, bool removeIds) override {};
    void NotifyDataAdded(size_t index) override {};
    void KeepRemovedItemInCache(NG::LazyForEachChild node,
        std::unordered_map<std::string, NG::LazyForEachCacheChild>& cachedItems) override {}

private:
    sptr<LazyForEachFuncs> cjBuilder_;
    wptr<CJDataChangeListener> weakListenerManager_;
};

} // namespace Framework
} // namespace Ace
} // namespace OHOS

#endif // ACE_ENGINE_CJ_LAZYFOREACH_H
