/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_RANGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_RANGE_H

#include <cstdint>

namespace OHOS::Ace {

struct TextRange {
    int32_t start = -1;
    int32_t end = -1;

    bool operator==(const TextRange& other) const
    {
        return this->start == other.start && this->end == other.end;
    }

    bool operator!=(const TextRange& other) const
    {
        return this->start != other.start || this->end != other.end;
    }

    bool IsValid() const
    {
        return start > -1 && end > -1;
    }

    int32_t GetLength() const
    {
        return std::abs(end - start);
    }

    std::string ToString() const
    {
        std::stringstream ss;
        ss << "[start:" << start << "," << "end:" << end << "]";
        return ss.str();
    }

    void Reset()
    {
        start = -1;
        end = -1;
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_RANGE_H
