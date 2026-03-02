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

#include "napi/napi_parser.h"
namespace OHOS::Ace::Kit {
bool ACE_FORCE_EXPORT ParseColor(napi_env env, napi_value value, Color& info)
{
    return true;
}

bool ACE_FORCE_EXPORT ParseDimension(
    napi_env env, CalcDimension& result, napi_value napiValue, DimensionUnit defaultUnit, bool isSupportPercent)
{
    return true;
}
} // namespace OHOS::Ace::Kit
