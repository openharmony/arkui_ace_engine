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

#pragma once

#include <cstdint>
namespace OHOS::Ace::NG {
class LargeDeltaConverter {
public:
    LargeDeltaConverter() = default;
    virtual ~LargeDeltaConverter() = default;

    /**
     * @brief Converts a large delta to a jump index
     *
     * @return item index to jump to. Return -1 if conversion fails.
     */
    virtual int32_t Convert(float delta)
    {
        return -1;
    }
};
} // namespace OHOS::Ace::NG
