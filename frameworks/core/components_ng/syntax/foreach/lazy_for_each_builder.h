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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_LAZY_FOR_EACH_BUILDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_LAZY_FOR_EACH_BUILDER_H

#include <list>

#include "core/components_ng/syntax/foreach/for_each_builder.h"
#include "core/components_v2/foreach/lazy_foreach_component.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT LazyForEachBuilder : public ForEachBuilder, public V2::DataChangeListener {
    DECLARE_ACE_TYPE(NG::LazyForEachBuilder, ForEachBuilder)
public:
    LazyForEachBuilder() = default;
    ~LazyForEachBuilder() override = default;

    void OnDataReloaded() override {}
    void OnDataAdded(size_t index) override {}
    void OnDataDeleted(size_t index) override {}
    void OnDataChanged(size_t index) override {}
    void OnDataMoved(size_t from, size_t to) override {}

    virtual void ReleaseChildGroupById(const std::string& id) = 0;
    virtual void RegisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) = 0;
    virtual void UnregisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_LAZY_FOR_EACH_BUILDER_H
