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

#include "core/common/resource/resource_parse_utils.h"
namespace OHOS::Ace {
bool ResourceParseUtilsBase::needReload_ = false;
bool ResourceParseUtilsBase::ParseResColor(const RefPtr<ResourceObject>& resObj, Color& result, bool adaptMaterial)
{
    return false;
}
bool ResourceParseUtilsBase::ParseResDimensionVp(const RefPtr<ResourceObject>& resObj, CalcDimension& result)
{
    return false;
}
bool ResourceParseUtilsBase::ParseResDimensionVpNG(
    const RefPtr<ResourceObject>& resObj, CalcDimension& result, bool isRound)
{
    return false;
}

bool ResourceParseUtilsBase::ParseResDouble(const RefPtr<ResourceObject>& resObj, double& result)
{
    return false;
}

bool ResourceParseUtilsBase::ParseResResource(const RefPtr<ResourceObject>& resObj, CalcDimension& result)
{
    return false;
}

} // namespace OHOS::Ace
