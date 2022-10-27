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

#include "gtest/gtest.h"

namespace OHOS::Ace::NG {

class BaseShapePatternTestNg : public testing::Test {
public:
    void CheckSize();
    void CheckNoSize();
    void CheckLayoutAlgorithom();
    void CheckFill();
    void CheckFillOpacity();
    void CheckStroke();
    void CheckStrokeWidth();
    void CheckStrokeOpacity();
    void CheckStrokeDashArray();
    void CheckStrokeDashOffset();
    void CheckStrokeLineCap();
    void CheckStrokeLineJoin();
    void CheckStrokeMiterLimit();
    void CheckAntiAlias();

    const float WIDTH = 200.0f;
    const float HEIGHT = 300.0f;
};

} // namespace OHOS::Ace::NG