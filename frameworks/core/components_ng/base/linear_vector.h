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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_LINEAR_VECTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_LINEAR_VECTOR_H

#include <vector>

#include "base/geometry/size.h"
#include "frameworks/base/utils/macros.h"

namespace OHOS::Ace::NG {
template<typename T>
class ACE_EXPORT LinearVector : public std::vector<T> {
public:
    LinearVector() = default;
    explicit LinearVector(const size_t n) : std::vector<T>(n) {};
    LinearVector(const size_t n, T value) : std::vector<T>(n, value) {};
    LinearVector(std::initializer_list<T> li) : std::vector<T>(li) {};
    ~LinearVector() = default;

    LinearVector operator+(const LinearVector& linearVector) const
    {
        LinearVector longLinearVector = linearVector.size() > this->size() ? linearVector : *this;
        const LinearVector* shortLinearVector = linearVector.size() <= this->size() ? &linearVector : this;
        for (size_t i = 0; i < shortLinearVector->size(); ++i) {
            longLinearVector[i] += shortLinearVector->at(i);
        }
        return longLinearVector;
    }

    LinearVector operator-(const LinearVector& linearVector) const
    {
        LinearVector longLinearVector = linearVector.size() > this->size() ? linearVector : *this;
        const LinearVector* shortLinearVector = linearVector.size() <= this->size() ? &linearVector : this;
        for (size_t i = 0; i < shortLinearVector->size(); ++i) {
            longLinearVector[i] -= shortLinearVector->at(i);
        }
        return longLinearVector;
    }

    LinearVector operator*(const float scale) const
    {
        LinearVector linearVector = *this;
        for (size_t i = 0; i < linearVector.size(); ++i) {
            linearVector[i] *= scale;
        }
        return linearVector;
    }

    bool operator==(const LinearVector& linearVector) const
    {
        if (this->size() != linearVector.size()) {
            return false;
        }
        for (size_t i = 0; i < linearVector.size(); ++i) {
            if (!NearEqual(this->at(i), linearVector[i])) {
                return false;
            }
        }
        return true;
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_LINEAR_VECTOR_H
