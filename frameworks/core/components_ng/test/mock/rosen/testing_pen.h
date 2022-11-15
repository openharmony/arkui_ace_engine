/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_PEN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_PEN_H

#include "utils/scalar.h"

#include "testing_color.h"

namespace OHOS::Ace::Testing {
using scalar = Rosen::Drawing::scalar;
class RSPen {
public:
    enum class CapStyle {
        FLAT_CAP,
        SQUARE_CAP,
        ROUND_CAP,
    };

    RSPen() = default;
    ~RSPen() = default;

    virtual void SetAntiAlias(bool aa) = 0;
    virtual void SetWidth(scalar width) = 0;
    virtual void SetCapStyle(CapStyle cs) = 0;
    virtual void SetColor(const RSColor& c) = 0;
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_PEN_H