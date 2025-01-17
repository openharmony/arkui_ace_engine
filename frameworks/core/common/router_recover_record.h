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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ROUTER_RECOVER_RECORD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ROUTER_RECOVER_RECORD_H

#include <string>

namespace OHOS::Ace {
struct RouterRecoverRecord {
    std::string url;
    std::string params;
    bool isNamedRouter;

    RouterRecoverRecord() : url{}, params{}, isNamedRouter(false) {}
    RouterRecoverRecord(const std::string& url, const std::string& params, bool isNamedRouter)
        : url(url), params(params), isNamedRouter(isNamedRouter) {}
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ROUTER_RECOVER_RECORD_H