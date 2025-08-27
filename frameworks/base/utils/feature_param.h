/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_FEATURE_PARAM_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_FEATURE_PARAM_IMPL_H

#include <string>

#include "ui/base/macros.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT FeatureParam {
public:
    FeatureParam() = default;
    ~FeatureParam() = default;

    // SyncLoadParser
    static bool IsSyncLoadEnabled();
    static uint32_t GetSyncloadResponseDeadline();
    // UINodeGcParamParser
    static bool IsUINodeGcEnabled();
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_FEATURE_PARAM_IMPL_H
