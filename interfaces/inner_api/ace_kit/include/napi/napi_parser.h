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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_NAPI_NAPI_PARSER_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_NAPI_NAPI_PARSER_H

#include "native_engine/native_value.h"
#include "ui/base/geometry/calc_dimension.h"
#include "ui/base/macros.h"
#include "ui/properties/color.h"

namespace OHOS::Ace::Kit {

bool ACE_FORCE_EXPORT ParseColor(napi_env env, napi_value value, Color& info);
bool ACE_FORCE_EXPORT ParseDimension(
    napi_env env, CalcDimension& result, napi_value napiValue, DimensionUnit defaultUnit, bool isSupportPercent);

} // namespace OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_NAPI_NAPI_PARSER_H
