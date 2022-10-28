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

#include "core/components_ng/pattern/shape/polygon_model_ng.h"
#include "core/components_ng/test/pattern/shape/base_polygon_pattern_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class PolygonPatternTestNg : public BasePolygonPatternTestNg {};

/**
 * @tc.name: Creator001
 * @tc.desc: create polygon with width and height
 * @tc.type: FUNC
 */

HWTEST_F(PolygonPatternTestNg, Creator001, TestSize.Level1)
{
    PolygonModelNG().Create(true);
    CheckSize();
}

/**
 * @tc.name: Creator002
 * @tc.desc: create polygon with no width or height
 * @tc.type: FUNC
 */

HWTEST_F(PolygonPatternTestNg, Creator002, TestSize.Level1)
{
    PolygonModelNG().Create(true);
    CheckNoSize();
}

/**
 * @tc.name: PolygonPaintProperty001
 * @tc.desc: create path with points
 * @tc.type: FUNC
 */

HWTEST_F(PolygonPatternTestNg, PolygonPaintProperty001, TestSize.Level1)
{
    PolygonModelNG().Create(true);
    CheckPoints();
}

} // namespace OHOS::Ace::NG