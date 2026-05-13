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
#include "core/common/premake_scope.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t DEFAULT_ID = 0;
static thread_local int32_t isPreMake_(DEFAULT_ID);
}

bool PreMakeScope::IsPreMake()
{
    return isPreMake_ > 0;
}

void PreMakeScope::SetPreMake(bool isPreMake)
{
    if (isNodePreMake_.has_value() && !isNodePreMake_.value()) {
        return;
    }
    if (isPreMake) {
        ++isPreMake_;
        return;
    }
    --isPreMake_;
}

int32_t PreMakeScope::Count()
{
    return isPreMake_;
}
} // namespace OHOS::Ace
