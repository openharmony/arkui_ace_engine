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

#include "base/geometry/matrix4.h"

namespace OHOS::Ace {
Matrix4 Matrix4::CreateIdentity()
{
    return Matrix4();
}

Matrix4::Matrix4()
{
    for (int32_t col = 0; col < DIMENSION; ++col) {
        for (int32_t row = 0; row < DIMENSION; ++row) {
            matrix4x4_[col][row] = (col == row) ? 1.0 : 0.0;
        }
    }
}
} // namespace OHOS::Ace
