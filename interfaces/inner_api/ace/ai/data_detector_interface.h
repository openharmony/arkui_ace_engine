/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_DATA_DETECTOR_INTERFACE_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_DATA_DETECTOR_INTERFACE_H

#include <functional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "commonlibrary/c_utils/base/include/refbase.h"

namespace OHOS {
class IRemoteObject;
}

namespace OHOS::Ace {
constexpr int32_t UNSUPPORTED_CODE = 801;
using FuncVariant = std::variant<std::function<std::string()>, std::function<void(sptr<IRemoteObject>, std::string)>,
    std::function<void(int32_t, std::string)>,
    std::function<void(int32_t, std::string, std::string, int32_t, std::string)>>;

struct TextDataDetectInfo {
    std::string text;
    std::string module;
    bool isWordPosEnabled = false;
};

struct TextDataDetectResult {
    int32_t code = UNSUPPORTED_CODE;
    std::string entity;
    std::string wordPos;
    std::unordered_map<std::string, std::vector<std::pair<std::string, FuncVariant>>> menuOptionAndAction;
};

using TextDetectResultFunc = std::function<void(const TextDataDetectResult)>;

class DataDetectorInterface {
public:
    virtual bool IsDataDetectorSupported() = 0;
    virtual void GetAIEntityMenu(TextDataDetectResult& textDataDetectResult) = 0;
    virtual void DataDetect(const TextDataDetectInfo& info, const TextDetectResultFunc& resultFunc) = 0;

    virtual int8_t GetCursorPosition(const std::string& text, int8_t offset)
    {
        return -1;
    }

    virtual std::vector<int8_t> GetWordSelection(const std::string& text, int8_t offset)
    {
        return std::vector<int8_t> { -1, -1 };
    }

protected:
    virtual ~DataDetectorInterface() {}
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DATA_DETECTOR_INTERFACE_H
