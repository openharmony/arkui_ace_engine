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

#include "base/geometry/calc_dimension.h"
#include "base/json/json_util.h"

namespace OHOS::Ace {
std::string CalcDimensionRect::ToString() const
{
    static const int32_t precision = 2;
    std::stringstream ss;
    ss << "Rect (" << std::fixed << std::setprecision(precision) << x_.ToString() << ", "
        << y_.ToString() << ") - [";
    ss << width_.ToString();
    ss << " x ";
    ss << height_.ToString();
    ss << "]";
    std::string output = ss.str();
    return output;
}

std::string CalcDimensionRect::ToJsonString() const
{
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("x", x_.ToString().c_str());
    jsonValue->Put("y", y_.ToString().c_str());
    jsonValue->Put("width", width_.ToString().c_str());
    jsonValue->Put("height", height_.ToString().c_str());
    return jsonValue->ToString();
}

} // namespace OHOS::Ace