/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <algorithm>
#include <cstddef>
#include <optional>
#include <utility>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "core/components_ng/pattern/custom_paint/canvas_event_hub.h"
#include "core/components_ng/pattern/custom_paint/canvas_layout_algorithm.h"
#include "core/components_ng/pattern/custom_paint/canvas_model.h"
#include "core/components_ng/pattern/custom_paint/canvas_model_ng.h"
#include "core/components_ng/pattern/custom_paint/canvas_modifier.h"
#include "core/components_ng/pattern/custom_paint/canvas_paint_mem.h"
#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/canvas_paint_op.h"
#include "core/components_ng/pattern/custom_paint/canvas_pattern.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_paint_method.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class CanvasTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void CanvasTestNg::SetUpTestCase() {}

void CanvasTestNg::TearDownTestCase() {}

/**
 * @tc.name: CanvasPatternTest001
 * @tc.desc: Test the function 'IsPercentStr' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasTestNg, CanvasPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps2: Call the function IsPercentStr with percent string.
     * @tc.expected: The return value is true and the '%' of percent string is droped.
     */
    const std::string exceptedresult("50");

    std::string percentStr("50%");
    EXPECT_TRUE(paintMethod->IsPercentStr(percentStr));
    EXPECT_STREQ(percentStr.c_str(), exceptedresult.c_str());

    /**
     * @tc.steps3: Call the function IsPercentStr with non-percent string.
     * @tc.expected: The return value is false and the non-percent string is not changed.
     */
    std::string nonPercentStr("50");
    EXPECT_FALSE(paintMethod->IsPercentStr(nonPercentStr));
    EXPECT_STREQ(nonPercentStr.c_str(), exceptedresult.c_str());
}
} // namespace OHOS::Ace::NG
