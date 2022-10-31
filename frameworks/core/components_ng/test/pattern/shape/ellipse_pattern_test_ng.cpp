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

#include "core/components_ng/pattern/shape/ellipse_model_ng.h"
#include "core/components_ng/test/pattern/shape/base_shape_pattern_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class EllipsePatternTestNg : public BaseShapePatternTestNg {};

/**
 * @tc.name: Creator001
 * @tc.desc: create ellipse with width and height
 * @tc.type: FUNC
 */

HWTEST_F(EllipsePatternTestNg, Creator001, TestSize.Level1)
{
    EllipseModelNG().Create();
    CheckSize();
}

/**
 * @tc.name: Creator002
 * @tc.desc: create ellipse with no width or height
 * @tc.type: FUNC
 */

HWTEST_F(EllipsePatternTestNg, Creator002, TestSize.Level1)
{
    EllipseModelNG().Create();
    CheckNoSize();
}

} // namespace OHOS::Ace::NG
