/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_ENTRANCE_UTILS_H
#define FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_ENTRANCE_UTILS_H

#include <string>

#include "base/log/log.h"
#include "base/geometry/rect.h"
#include "core/common/asset_manager_impl.h"
#include "core/components_ng/property/safe_area_insets.h"

namespace OHOS::Rosen {
    class AvoidArea;
    struct DMRect;
}
namespace OHOS::Ace {

std::string GetStringFromFile(const std::string& packagePathStr, const std::string& fileName);
std::string GetStringFromHap(const std::string& hapPath, const std::string& fileName);
bool CheckUrlValid(const std::string& url, const std::string& hapPath);

RefPtr<AssetProviderImpl> CreateAssetProviderImpl(
    const std::string& packagePath, const std::vector<std::string>& assetBasePaths, bool useCache = true);

inline const std::string GenerateFullPath(const std::string& prePath, const std::string& postPath)
{
    if (prePath.empty() && postPath.empty()) {
        return "";
    }
    std::string tmpPostPath = postPath;
    if (tmpPostPath.back() == '/') {
        tmpPostPath.pop_back();
    }
    std::string fullPath = prePath;
    if (fullPath.empty() || fullPath.back() == '/') {
        fullPath += tmpPostPath;
    } else {
        fullPath += "/" + tmpPostPath;
    }
    return fullPath;
}

enum class ResultSetDataType {
    TYPE_NULL = 0,
    TYPE_STRING,
    TYPE_INT32,
    TYPE_INT64,
    TYPE_DOUBLE
};

class ResultSetUtils {
public:
    template<typename T>
    static std::variant<int32_t, std::string, int64_t, double> GetValFromColumn(const std::string &columnName,
        T &resultSet, ResultSetDataType type)
    {
        if (resultSet == nullptr) {
            return DefaultVariantVal(type);
        }

        int32_t err = 0;
        int32_t index = 0;
        err = resultSet->GetColumnIndex(columnName, index);
        if (err) {
            return DefaultVariantVal(type);
        }

        std::variant<int32_t, std::string, int64_t, double> data;
        switch (type) {
            case ResultSetDataType::TYPE_STRING: {
                data = GetStringValFromColumn(index, resultSet);
                break;
            }
            case ResultSetDataType::TYPE_INT32: {
                data = GetIntValFromColumn(index, resultSet);
                break;
            }
            case ResultSetDataType::TYPE_INT64: {
                data = GetLongValFromColumn(index, resultSet);
                break;
            }
            case ResultSetDataType::TYPE_DOUBLE: {
                data = GetDoubleValFromColumn(index, resultSet);
                break;
            }
            default: {
                return DefaultVariantVal(type);
                break;
            }
        }

        return data;
    }

    template<typename T>
    static inline std::string GetStringValFromColumn(int index, T &resultSet)
    {
        std::string stringVal;
        if (resultSet->GetString(index, stringVal)) {
            return "";
        }
        return stringVal;
    }

    template<typename T>
    static inline int32_t GetIntValFromColumn(int index, T &resultSet)
    {
        int32_t integerVal;
        if (resultSet->GetInt(index, integerVal)) {
            return 0;
        }
        return integerVal;
    }

    template<typename T>
    static inline int64_t GetLongValFromColumn(int index, T &resultSet)
    {
        int64_t integer64Val;
        if (resultSet->GetLong(index, integer64Val)) {
            return 0;
        }
        return integer64Val;
    }

    template<typename T>
    static inline double GetDoubleValFromColumn(int index, T &resultSet)
    {
        double doubleVal;
        if (resultSet->GetDouble(index, doubleVal)) {
            return 0;
        }
        return doubleVal;
    }

private:
    static std::variant<int32_t, std::string, int64_t, double> DefaultVariantVal(ResultSetDataType type)
    {
        switch (type) {
            case ResultSetDataType::TYPE_STRING:
                return std::string();
            case ResultSetDataType::TYPE_INT32:
                return 0;
            case ResultSetDataType::TYPE_INT64:
                return static_cast<int64_t>(0);
            case ResultSetDataType::TYPE_DOUBLE:
                return static_cast<double>(0.0);
            default:
                return 0;
        }

        return 0;
    }
};

NG::SafeAreaInsets ConvertAvoidArea(const OHOS::Rosen::AvoidArea& avoidArea);
Rect ConvertDMRect2Rect(const OHOS::Rosen::DMRect& displayAvailableRect);
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_ENTRANCE_UTILS_H
