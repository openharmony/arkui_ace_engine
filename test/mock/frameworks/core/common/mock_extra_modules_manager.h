/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_MOCK_FRAMEWORKS_CORE_COMMON_MOCK_EXTRA_MODULES_MANAGER_H
#define FOUNDATION_ACE_TEST_MOCK_FRAMEWORKS_CORE_COMMON_MOCK_EXTRA_MODULES_MANAGER_H

#include <cstdint>
#include <string>
#include <utility>

namespace OHOS::Ace::MockExtraModulesManager {
using AppSpaceCompConfigInitFunc = int32_t (*)(const std::string&);
using AppSpaceCompConfigGetConfigFunc = std::pair<int32_t, std::string> (*)(const std::string&);

void Reset();
void SetAppSpaceCompConfigFuncs(AppSpaceCompConfigInitFunc initFunc, AppSpaceCompConfigGetConfigFunc getConfigFunc);
} // namespace OHOS::Ace::MockExtraModulesManager

#endif // FOUNDATION_ACE_TEST_MOCK_FRAMEWORKS_CORE_COMMON_MOCK_EXTRA_MODULES_MANAGER_H
