/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

namespace {
const double MAX_WIDTH = 2.0;
const double MAX_INTRINSIC_WIDTH = 4.0;
const double SCALE = 0.5;
}

class CanvasCustomPaintMethodTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void CanvasCustomPaintMethodTestNg::SetUpTestCase() {}

void CanvasCustomPaintMethodTestNg::TearDownTestCase() {}

/**
 * @tc.name: CanvasCustomPaintMethodTest001
 * @tc.desc: Test the function 'CheckFilterProperty' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg, CanvasCustomPaintMethodTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    /**
     * @tc.steps2: When FilterType is GRAYSCALE, call the function CheckFilterProperty.
     * @tc.expected: return value are as expected.
     */
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::GRAYSCALE, "10"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::GRAYSCALE, "10.5"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::GRAYSCALE, "10%"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::GRAYSCALE, "10.5%"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::GRAYSCALE, " "));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::GRAYSCALE, "10px"));
    /**
     * @tc.steps3: When FilterType is SEPIA, call the function CheckFilterProperty.
     * @tc.expected: return value are as expected.
     */
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::SEPIA, "10"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::SEPIA, "10.5"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::SEPIA, "10%"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::SEPIA, "10.5%"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::SEPIA, " "));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::SEPIA, "10px"));
    /**
     * @tc.steps4: When FilterType is INVERT, call the function CheckFilterProperty.
     * @tc.expected: return value are as expected.
     */
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::INVERT, "10"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::INVERT, "10.5"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::INVERT, "10%"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::INVERT, "10.5%"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::INVERT, " "));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::INVERT, "10px"));
    /**
     * @tc.steps5: When FilterType is OPACITY, call the function CheckFilterProperty.
     * @tc.expected: return value are as expected.
     */
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::OPACITY, "10"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::OPACITY, "10.5"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::OPACITY, "10%"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::OPACITY, "10.5%"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::OPACITY, " "));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::OPACITY, "10px"));
    /**
     * @tc.steps5: When FilterType is BRIGHTNESS, call the function CheckFilterProperty.
     * @tc.expected: return value are as expected.
     */
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::BRIGHTNESS, "10"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::BRIGHTNESS, "10.5"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::BRIGHTNESS, "10%"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::BRIGHTNESS, "10.5%"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::BRIGHTNESS, " "));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::BRIGHTNESS, "10px"));
    /**
     * @tc.steps6: When FilterType is CONTRAST, call the function CheckFilterProperty.
     * @tc.expected: return value are as expected.
     */
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::CONTRAST, "10"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::CONTRAST, "10.5"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::CONTRAST, "10%"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::CONTRAST, "10.5%"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::CONTRAST, " "));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::CONTRAST, "10px"));
}

/**
 * @tc.name: CanvasCustomPaintMethodTest002
 * @tc.desc: Test the function 'CheckFilterProperty' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg, CanvasCustomPaintMethodTest002, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    /**
     * @tc.steps2: When FilterType is BLUR, call the function CheckFilterProperty.
     * @tc.expected: return value are as expected.
     */
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::BLUR, "10px"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::BLUR, "10.5px"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::BLUR, "10rem"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::BLUR, "10.5rem"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::BLUR, "10%px"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::BLUR, "10%rem"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::BLUR, "10.5%px"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::BLUR, "10.5%rem"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::BLUR, " "));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::BLUR, "10"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::BLUR, "10.5"));
    /**
     * @tc.steps3: When FilterType is HUE_ROTATE, call the function CheckFilterProperty.
     * @tc.expected: return value are as expected.
     */
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::HUE_ROTATE, "10deg"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::HUE_ROTATE, "10.5deg"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::HUE_ROTATE, "10rad"));
    EXPECT_TRUE(paintMethod->CheckFilterProperty(FilterType::HUE_ROTATE, "10.5rad"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::HUE_ROTATE, "10%deg"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::HUE_ROTATE, "10%rad"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::HUE_ROTATE, "10.5%deg"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::HUE_ROTATE, "10.5%rad"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::HUE_ROTATE, " "));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::HUE_ROTATE, "10"));
    EXPECT_FALSE(paintMethod->CheckFilterProperty(FilterType::HUE_ROTATE, "10.5"));
}

/**
 * @tc.name: CanvasCustomPaintMethodTest003
 * @tc.desc: Test the function 'ParseFilter' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg, CanvasCustomPaintMethodTest003, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    /**
     * @tc.steps2: Call the function ParseFilter.
     * @tc.expected: return value are as expected.
     */
    std::vector<FilterProperty> filters;
    std::string filter = "gray";
    EXPECT_FALSE(paintMethod->ParseFilter(filter, filters));
    filter = "gray(50)";
    EXPECT_FALSE(paintMethod->ParseFilter(filter, filters));
    filter = "blur(10px";
    EXPECT_TRUE(paintMethod->ParseFilter(filter, filters));
    EXPECT_EQ(filters.size(), 1);
    EXPECT_EQ(filters[0].filterType_, FilterType::BLUR);
    EXPECT_EQ(filters[0].filterParam_, "10px");
}

/**
 * @tc.name: CanvasCustomPaintMethodTest004
 * @tc.desc: Test the function 'UpdateLineDash' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg, CanvasCustomPaintMethodTest004, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    /**
     * @tc.steps2: Call the function UpdateLineDash.
     * @tc.expected: return value are as expected.
     */
    RSPen pen;
    paintMethod->state_.strokeState.SetLineDash({ { 1.0, 0.0 }, 1.0 });
    paintMethod->state_.strokeState.SetLineDashOffset(1.0);
    paintMethod->UpdateLineDash(pen);
    EXPECT_EQ(paintMethod->state_.strokeState.GetLineDash().lineDash.size(), 2);
}

/**
 * @tc.name: CanvasCustomPaintMethodTest005
 * @tc.desc: Test the function 'MakeConicGradient' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg, CanvasCustomPaintMethodTest005, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    /**
     * @tc.steps2: Call the function MakeConicGradient.
     * @tc.expected: return value are as expected.
     */
    Ace::Gradient gradient;
    gradient.SetType(Ace::GradientType::CONIC);
    EXPECT_EQ(paintMethod->MakeConicGradient(nullptr, gradient), nullptr);
    AnimatableDimension animatableDimension(1.0);
    gradient.GetConicGradient().centerX = animatableDimension;
    EXPECT_EQ(gradient.GetConicGradient().centerX.has_value(), true);
    auto result = paintMethod->MakeConicGradient(nullptr, gradient);
    EXPECT_EQ(result, nullptr);

    gradient.GetConicGradient().centerY = animatableDimension;
    EXPECT_EQ(gradient.GetConicGradient().centerY.has_value(), true);
    result = paintMethod->MakeConicGradient(nullptr, gradient);
    EXPECT_EQ(result, nullptr);

    gradient.GetConicGradient().startAngle = animatableDimension;
    EXPECT_EQ(gradient.GetConicGradient().startAngle.has_value(), true);
    OHOS::Ace::GradientColor gradientColor1(Color::BLACK);
    OHOS::Ace::GradientColor gradientColor2(Color::RED);
    OHOS::Ace::GradientColor gradientColor3(Color::BLUE);
    gradient.AddColor(gradientColor1);
    gradient.AddColor(gradientColor2);
    gradient.AddColor(gradientColor3);
    result = paintMethod->MakeConicGradient(nullptr, gradient);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: CanvasCustomPaintMethodTest006
 * @tc.desc: Test the function 'GetFilterType' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg, CanvasCustomPaintMethodTest006, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    std::vector<FilterProperty> filters;
    /**
     * @tc.steps2: Call the function GetFilterType.
     * @tc.expected: return value are as expected.
     */
    paintMethod->SetFilterParam("none");
    EXPECT_TRUE(paintMethod->GetFilterType(filters));
    filters.clear();
    paintMethod->SetFilterParam("gray(10px)");
    EXPECT_FALSE(paintMethod->GetFilterType(filters));
    EXPECT_EQ(filters.size(), 0);
    filters.clear();
    paintMethod->SetFilterParam("blur(10px)");
    paintMethod->GetFilterType(filters);
    EXPECT_EQ(filters[0].filterType_, FilterType::BLUR);
    EXPECT_EQ(filters[0].filterParam_, "10px");
    EXPECT_EQ(filters.size(), 1);
}

/**
 * @tc.name: CanvasCustomPaintMethodTest007
 * @tc.desc: Test the function 'IsPercentStr' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg, CanvasCustomPaintMethodTest007, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    /**
     * @tc.steps2: Call the function IsPercentStr.
     * @tc.expected: return value are as expected.
     */
    std::string percentStr1 = "50.5%";
    EXPECT_TRUE(paintMethod->IsPercentStr(percentStr1));
    EXPECT_EQ(percentStr1, "50.5");

    std::string percentStr2 = "50px";
    EXPECT_FALSE(paintMethod->IsPercentStr(percentStr2));
    EXPECT_NE(percentStr2, "50");

    std::string percentStr3;
    EXPECT_FALSE(paintMethod->IsPercentStr(percentStr3));
}

/**
 * @tc.name: CanvasCustomPaintMethodTest008
 * @tc.desc: Test the function 'PxStrToDouble' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg, CanvasCustomPaintMethodTest008, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    /**
     * @tc.steps2: Call the function PxStrToDouble.
     * @tc.expected: return value are as expected.
     */
    std::string str1 = "10";
    EXPECT_EQ(paintMethod->PxStrToDouble(str1), 0);
    str1 = "10px";
    EXPECT_EQ(paintMethod->PxStrToDouble(str1), 10);
}

/**
 * @tc.name: CanvasCustomPaintMethodTest009
 * @tc.desc: Test the function 'BlurStrToDouble' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg, CanvasCustomPaintMethodTest009, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    /**
     * @tc.steps2: Call the function BlurStrToDouble.
     * @tc.expected: return value are as expected.
     */
    std::string str1 = "10.0";
    EXPECT_EQ(paintMethod->BlurStrToDouble(str1), 0.0);
    str1 = "aaa";
    EXPECT_EQ(paintMethod->BlurStrToDouble(str1), 0.0);
    str1 = "10.0px";
    EXPECT_EQ(paintMethod->BlurStrToDouble(str1), 10.0);
    str1 = "20.0rem";
    EXPECT_EQ(paintMethod->BlurStrToDouble(str1), 300.0);
}

/**
 * @tc.name: CanvasCustomPaintMethodTest010
 * @tc.desc: Test the function 'PercentStrToFloat' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg, CanvasCustomPaintMethodTest010, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    /**
     * @tc.steps2: Call the function PercentStrToFloat.
     * @tc.expected: return value are as expected.
     */
    std::string str1 = "10";
    EXPECT_EQ(paintMethod->PercentStrToFloat(str1), 10);
    str1 = "10%";
    EXPECT_EQ(paintMethod->PercentStrToFloat(str1), 0.1f);
    str1 = "abc";
    EXPECT_EQ(paintMethod->PercentStrToFloat(str1), 0.0f);
    str1 = "";
    EXPECT_EQ(paintMethod->PercentStrToFloat(str1), 0.0f);
}

/**
 * @tc.name: CanvasCustomPaintMethodTest011
 * @tc.desc: Test the function 'CheckNumberAndPercentage' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg, CanvasCustomPaintMethodTest011, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    /**
     * @tc.steps2: Call the function CheckNumberAndPercentage.
     * @tc.expected: return value are as expected.
     */
    float result = 0.0f;
    EXPECT_FALSE(paintMethod->CheckNumberAndPercentage("x", true, result));
    EXPECT_FALSE(paintMethod->CheckNumberAndPercentage("", true, result));
    EXPECT_FALSE(paintMethod->CheckNumberAndPercentage("x101", true, result));
    EXPECT_FALSE(paintMethod->CheckNumberAndPercentage("1/01", true, result));
    EXPECT_TRUE(paintMethod->CheckNumberAndPercentage("88", true, result));
    EXPECT_EQ(result, 1.0f);
}

/**
 * @tc.name: CanvasCustomPaintMethodTest012
 * @tc.desc: Test the function 'CalcTextScale' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg, CanvasCustomPaintMethodTest012, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    /**
     * @tc.steps2: Call the function CalcTextScale.
     * @tc.expected: return value are as expected.
     */
    auto result = paintMethod->CalcTextScale(0.0, 1.0);
    EXPECT_FALSE(result.has_value());

    result = paintMethod->CalcTextScale(1.0, std::nullopt);
    EXPECT_FALSE(result.has_value());

    result =paintMethod->CalcTextScale(0.0, std::nullopt);
    EXPECT_FALSE(result.has_value());

    result = paintMethod->CalcTextScale(1.0, -1.0);
    EXPECT_EQ(result.value(), 0.0);

    result = paintMethod->CalcTextScale(1.0, 0.0);
    EXPECT_EQ(result.value(), 0.0);

    result = paintMethod->CalcTextScale(1.0, 1.0);
    EXPECT_FALSE(result.has_value());

    result = paintMethod->CalcTextScale(-1.0, 1.0);
    EXPECT_FALSE(result.has_value());

    result = paintMethod->CalcTextScale(MAX_INTRINSIC_WIDTH, MAX_WIDTH);
    EXPECT_EQ(result.value(), SCALE);
}
} // namespace OHOS::Ace::NG
