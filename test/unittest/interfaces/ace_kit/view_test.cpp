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

#include "gtest/gtest.h"
#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_pattern.h"
#include "ui/view/view.h"
#include "ui/view_factory/abstract_view_factory.h"
#include "test/unittest/core/base/view_abstract_test_ng.h"
#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Kit;

namespace OHOS::Ace::Kit {

class ViewTest :  public testing::Test {};

/**
 * @tc.name: ViewTest001
 * @tc.desc: Test SetWidth of view
 * @tc.type: FUNC
 */
HWTEST_F(ViewTest, ViewTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize View.
     * @tc.expected: All pointer is non-null.
     */
    View view;
    auto node =
        AbstractViewFactory::CreateFrameNode("test", 0, AceType::MakeRefPtr<MockAceKitPattern>());
    EXPECT_NE(node, nullptr);
    view.node_ = node;

    /**
     * @tc.steps: make width.Unit() is DimensionUnit::CALC.
     */
    const CalcDimension width = CalcDimension("20", DimensionUnit::CALC);
    view.SetWidth(width);

    /**
     * @tc.steps: getwidth to verify width is setted.
     */
    auto frameNode = reinterpret_cast<AceNode*>(node->GetHandle());
    auto res = NG::ViewAbstract::GetWidth(frameNode);

    auto unitNum = static_cast<int>(res.Unit());
    EXPECT_EQ(unitNum, 6);
}

/**
 * @tc.name: ViewTest002
 * @tc.desc: Test SetWidth of view
 * @tc.type: FUNC
 */
HWTEST_F(ViewTest, ViewTest002, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize View.
     * @tc.expected: All pointer is non-null.
     */
    View view;
    auto node =
        AbstractViewFactory::CreateFrameNode("test", 0, AceType::MakeRefPtr<MockAceKitPattern>());
    EXPECT_NE(node, nullptr);
    view.node_ = node;

    /**
     * @tc.steps: make width.Unit() is not DimensionUnit::CALC.
     */
    const CalcDimension width = CalcDimension(30.0f, DimensionUnit::PX);
    view.SetWidth(width);

    /**
     * @tc.steps: getwidth to verify width is setted.
     */
    auto frameNode = reinterpret_cast<AceNode*>(node->GetHandle());
    auto res = NG::ViewAbstract::GetWidth(frameNode);

    auto resWidth = res.Value();
    EXPECT_EQ(resWidth, 30);
}

/**
 * @tc.name: ViewTest003
 * @tc.desc: Test SetHeight of view
 * @tc.type: FUNC
 */
HWTEST_F(ViewTest, ViewTest003, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize View.
     * @tc.expected: All pointer is non-null.
     */
    View view;
    auto node =
        AbstractViewFactory::CreateFrameNode("test", 0, AceType::MakeRefPtr<MockAceKitPattern>());
    EXPECT_NE(node, nullptr);
    view.node_ = node;

    /**
     * @tc.steps: make width.Unit() is DimensionUnit::CALC.
     */
    const CalcDimension height = CalcDimension("20", DimensionUnit::CALC);
    view.SetHeight(height);

    /**
     * @tc.steps: getwidth to verify width is setted.
     */
    auto frameNode = reinterpret_cast<AceNode*>(node->GetHandle());
    auto res = NG::ViewAbstract::GetHeight(frameNode);

    auto unitNum = static_cast<int>(res.Unit());
    EXPECT_EQ(unitNum, 6);
}

/**
 * @tc.name: ViewTest004
 * @tc.desc: Test SetWidth of view
 * @tc.type: FUNC
 */
HWTEST_F(ViewTest, ViewTest004, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize View.
     * @tc.expected: All pointer is non-null.
     */
    View view;
    auto node =
        AbstractViewFactory::CreateFrameNode("test", 0, AceType::MakeRefPtr<MockAceKitPattern>());
    EXPECT_NE(node, nullptr);
    view.node_ = node;

    /**
     * @tc.steps: make width.Unit() is not DimensionUnit::CALC.
     */
    const CalcDimension height = CalcDimension(30.0f, DimensionUnit::PX);
    view.SetHeight(height);

    /**
     * @tc.steps: getwidth to verify width is setted.
     */
    auto frameNode = reinterpret_cast<AceNode*>(node->GetHandle());
    auto res = NG::ViewAbstract::GetHeight(frameNode);

    auto resHeight = res.Value();
    EXPECT_EQ(resHeight, 30);
}

/**
 * @tc.name: LinearGradientBlurViewTest001
 * @tc.desc: Test SetWidth of view
 * @tc.type: FUNC
 */
HWTEST_F(ViewTest, LinearGradientBlurViewTest001, TestSize.Level1)
{
    /**
     * @tc.steps: initialize View.
     * @tc.expected: All pointer is non-null.
     */
    View view;
    auto node =
        AbstractViewFactory::CreateFrameNode("testNode", 0, AceType::MakeRefPtr<MockAceKitPattern>());
    EXPECT_NE(node, nullptr);
    view.node_ = node;

    /**
     * @tc.steps: Initialize linearGradientBlurPara parameters.
     */
    std::vector<std::pair<float, float>> fractionStops;
    fractionStops.push_back(std::pair<float, float>(0.0f, 1.0f));
    CalcDimension dimensionRadius(0.0);
    NG::LinearGradientBlurPara blurPara(dimensionRadius, fractionStops, NG::GradientDirection::LEFT);

    /**
     * @tc.steps: Test SetLinearGradientBlur.
     */
    view.SetLinearGradientBlur(blurPara);
    auto frameNode = reinterpret_cast<AceNode*>(node->GetHandle());
    ASSERT_NE(frameNode, nullptr);
    const auto& target = frameNode->GetRenderContext();
    ASSERT_NE(target, nullptr);
    auto graphicsProperty = target->CloneGraphics();
    ASSERT_NE(graphicsProperty, nullptr);
    EXPECT_EQ(graphicsProperty->CheckLinearGradientBlur(blurPara), true);
    EXPECT_EQ(graphicsProperty->GetLinearGradientBlurValue(), blurPara);
}

/**
 * @tc.name: LinearGradientBlurViewTest002
 * @tc.desc: Test SetWidth of view
 * @tc.type: FUNC
 */
HWTEST_F(ViewTest, LinearGradientBlurViewTest002, TestSize.Level1)
{
    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     */
    NG::ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    bool result = NG::ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: initialize View.
     */
    View view;
    auto node =
        AbstractViewFactory::CreateFrameNode("testNode", 0, AceType::MakeRefPtr<MockAceKitPattern>());
    EXPECT_NE(node, nullptr);
    view.node_ = node;

    /**
     * @tc.steps: Initialize linearGradientBlurPara parameters.
     */
    std::vector<std::pair<float, float>> fractionStops;
    fractionStops.push_back(std::pair<float, float>(0.0f, 1.0f));
    CalcDimension dimensionRadius(60.0);
    NG::LinearGradientBlurPara blurPara(dimensionRadius, fractionStops, NG::GradientDirection::BOTTOM);

    /**
     * @tc.steps: Test "SetLinearGradientBlur", when "IsCurrentVisualStateProcess" return false.
     */
    view.SetLinearGradientBlur(blurPara);
    auto frameNode = reinterpret_cast<AceNode*>(node->GetHandle());
    ASSERT_NE(frameNode, nullptr);
    const auto& renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto graphicsProperty = renderContext->CloneGraphics();
    ASSERT_NE(graphicsProperty, nullptr);
    EXPECT_EQ(graphicsProperty->CheckLinearGradientBlur(blurPara), true);
    EXPECT_EQ(graphicsProperty->GetLinearGradientBlurValue(), blurPara);
}
}

