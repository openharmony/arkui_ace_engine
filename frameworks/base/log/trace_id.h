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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_TRACE_ID_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_TRACE_ID_H

#include <memory>

namespace OHOS::Ace {

class TraceId {
public:
    TraceId() = default;
    virtual ~TraceId() = default;
    static std::shared_ptr<TraceId> CreateTraceId();
    virtual void SetTraceId() {}
    virtual void ClearTraceId() {}
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_TRACE_ID_H
