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

#include "test/unittest/core/base/view_abstract_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
/**
 * @tc.name: SetTranslateTest001
 * @tc.desc: Test the SetTranslate function of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetTranslateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Check ViewStackProcessor and construct TranslateOptions value.
     */
    TranslateOptions options1 { Dimension(100), Dimension(-200), Dimension(1) };
    auto stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    stack->ClearVisualState();
    auto node = stack->GetMainFrameNode();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. Set a none zero TranslateOptions value and get.
     * @tc.expected: step2. Translate value is same with the value set.
     */
    ViewAbstract::SetTranslate(options1);
    auto translateValue = ViewAbstract::GetTranslate(node);
    EXPECT_EQ(options1, translateValue);
    /**
     * @tc.steps: step3. Set a zero TranslateOptions value and get.
     * @tc.expected: step3. Translate value is zero.
     */
    NG::TranslateOptions options2(0.0f, 0.0f, 0.0f);
    ViewAbstract::SetTranslate(options2);
    translateValue = ViewAbstract::GetTranslate(node);
    EXPECT_EQ(translateValue.x.Value(), 0.0f);
    EXPECT_EQ(translateValue.y.Value(), 0.0f);
    EXPECT_EQ(translateValue.z.Value(), 0.0f);
}

/**
 * @tc.name: SetRotateTest001
 * @tc.desc: Test the SetRotate function of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetRotateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Check ViewStackProcessor.
     */
    auto stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    stack->ClearVisualState();
    auto node = stack->GetMainFrameNode();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. Set a none zero angle value and get.
     * @tc.expected: step2. Angle value is same with the value set.
     */
    constexpr float angle = 90.0f;
    Vector5F options1 { 0.0f, 0.0f, 1.0f, angle, 0.0f };
    ViewAbstract::SetRotate(options1);
    auto rotateValue = ViewAbstract::GetRotate(node);
    EXPECT_EQ(options1, rotateValue);
    /**
     * @tc.steps: step3. Set a zero angle value and get. Restore the rotate value in node.
     * @tc.expected: step3. Angle value is same with the value set.
     */
    constexpr float angleZero = 0.0f;
    Vector5F options2 { 0.0f, 0.0f, 1.0f, angleZero, 0.0f };
    // the last step should be restore the rotation value on node to default value.
    ViewAbstract::SetRotate(options2);
    rotateValue = ViewAbstract::GetRotate(node);
    EXPECT_TRUE(NearEqual(rotateValue.w, angleZero));
}

/**
 * @tc.name: SetScaleTest001
 * @tc.desc: Test the SetScale function of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetScaleTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Check ViewStackProcessor.
     */
    auto stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    stack->ClearVisualState();
    auto node = stack->GetMainFrameNode();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. Set a positive scale value and get.
     * @tc.expected: step2. Scale value is same with the value set.
     */
    constexpr float scaleValue1 = 2.0f;
    VectorF scale1 { scaleValue1, scaleValue1 };
    ViewAbstract::SetScale(scale1);
    auto scaleValue = ViewAbstract::GetScale(node);
    EXPECT_EQ(scale1, scaleValue);
    /**
     * @tc.steps: step3. Set a negative angle value and get.
     * @tc.expected: step3. Scale value is same with the value set.
     */
    constexpr float scaleValue2 = -2.0f;
    VectorF scale2 { scaleValue2, scaleValue2 };
    ViewAbstract::SetScale(scale2);
    scaleValue = ViewAbstract::GetScale(node);
    EXPECT_EQ(scale2, scaleValue);
    /**
     * @tc.steps: step3. Set a zero angle value and get. Restore the rotate value in node.
     * @tc.expected: step3. Angle value is same with the value set.
     */
    VectorF scale3 { 1.0f, 1.0f };
    ViewAbstract::SetScale(scale3);
    scaleValue = ViewAbstract::GetScale(node);
    EXPECT_EQ(scale3, scaleValue);
}

/**
 * @tc.name: SetPivotTest001
 * @tc.desc: Test the SetPivot function of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetPivotTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Check ViewStackProcessor.
     */
    auto stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    stack->ClearVisualState();
    auto node = stack->GetMainFrameNode();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. Set a pivot value with x and y value and get.
     * @tc.expected: step2. Pivot value is same with the value set.
     */
    constexpr float centerX = 50.0f;
    constexpr float centerY = -50.0f;
    DimensionOffset offset1 { Dimension(centerX), Dimension(centerY) };
    ViewAbstract::SetPivot(offset1);
    auto pivotProperty = node->GetRenderContext()->GetTransformCenter();
    ASSERT_TRUE(pivotProperty.has_value());
    EXPECT_TRUE(NearEqual(offset1, pivotProperty.value()));
    /**
     * @tc.steps: step3. Set a pivot value with x, y and z value and get.
     * @tc.expected: step3. Pivot value is same with the value set.
     */
    DimensionOffset offset2 { Dimension(centerX), Dimension(0.0f) };
    constexpr float centerZ = 50.0f;
    offset2.SetZ(Dimension(centerZ));
    ViewAbstract::SetPivot(offset2);
    pivotProperty = node->GetRenderContext()->GetTransformCenter();
    ASSERT_TRUE(pivotProperty.has_value());
    EXPECT_TRUE(NearEqual(offset2, pivotProperty.value()));
    /**
     * @tc.steps: step4. Set a default pivot value and get. Restore the pivot value in node.
     * @tc.expected: step4. Pivot value is same with the value set.
     */
    constexpr Dimension defaultDim(0.5f, DimensionUnit::PERCENT);
    DimensionOffset offset3 { defaultDim, defaultDim };
    ViewAbstract::SetPivot(offset3);
    pivotProperty = node->GetRenderContext()->GetTransformCenter();
    ASSERT_TRUE(pivotProperty.has_value());
    EXPECT_TRUE(NearEqual(offset3, pivotProperty.value()));
}
} // namespace OHOS::Ace::NG
