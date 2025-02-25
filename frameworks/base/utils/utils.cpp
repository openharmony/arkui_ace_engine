/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "base/utils/utils.h"
#ifdef WINDOWS_PLATFORM
#include <shlwapi.h>
#endif
namespace OHOS::Ace {
    bool RealPath(const std::string& fileName, char* realPath)
{
#if defined(WINDOWS_PLATFORM)
        return PathCanonicalize(realPath, fileName.c_str()) != 0;
#else
        return realpath(fileName.c_str(), realPath) != nullptr;
#endif
}

double RoundToMaxPrecision(double value)
{
    int precision = std::numeric_limits<double>::digits10;
    double factor = std::pow(10, precision - 2);
    if (NearZero(factor)) {
        return value;
    }
    return std::round(value * factor) / factor;
}
}