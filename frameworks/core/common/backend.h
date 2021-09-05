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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_BACKEND_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_BACKEND_H

#include "base/memory/ace_type.h"
#include "base/thread/task_executor.h"
#include "core/common/js_message_dispatcher.h"

#include "abs_shared_result_set.h"
#include "data_ability_predicates.h"
#include "result_set.h"
#include "uri.h"
#include "values_bucket.h"

namespace OHOS::Ace {

enum class BackendType { SERVICE, DATA, FORM };

class ACE_EXPORT Backend : public AceType {
    DECLARE_ACE_TYPE(Backend, AceType);

public:
    Backend() = default;
    ~Backend() override = default;

    enum class State {
        ON_CREATE,
        ON_DESTROY,
    };

    static RefPtr<Backend> Create();
    static RefPtr<Backend> CreateDefault();

    virtual bool Initialize(BackendType type, const RefPtr<TaskExecutor>& taskExecutor) = 0;

    virtual void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher> &transfer) const = 0;

    virtual BackendType GetType() = 0;

    // inform the frontend that onCreate or onDestroy
    virtual void UpdateState(State) = 0;

    virtual int32_t Insert(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value) = 0;
    virtual std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> Query(
        const Uri& uri, const std::vector<std::string>& columns,
        const OHOS::NativeRdb::DataAbilityPredicates& predicates) = 0;
    virtual int32_t Update(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value,
        const OHOS::NativeRdb::DataAbilityPredicates& predicates) = 0;
    virtual int32_t Delete(const Uri& uri, const OHOS::NativeRdb::DataAbilityPredicates& predicates) = 0;

    virtual int32_t BatchInsert(const Uri& uri, const std::vector<OHOS::NativeRdb::ValuesBucket>& values) = 0;
    virtual std::string GetType(const Uri& uri) = 0;
    virtual std::vector<std::string> GetFileTypes(const Uri& uri, const std::string& mimeTypeFilter) = 0;
    virtual int32_t OpenFile(const Uri& uri, const std::string& mode) = 0;
    virtual int32_t OpenRawFile(const Uri& uri, const std::string& mode) = 0;
    virtual Uri NormalizeUri(const Uri& uri) = 0;
    virtual Uri DenormalizeUri(const Uri& uri) = 0;

};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_BACKEND_H
