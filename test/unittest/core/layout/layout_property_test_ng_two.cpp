/*
 * Copyright (c) 2024 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
} // namespace

class LayoutPropertyTestNgTwo : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: CheckLocalizedBorderImageOutset001
 * @tc.desc: Test CheckLocalizedBorderImageOutset when borderImageStart_ has value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageOutset001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderImage = AceType::MakeRefPtr<BorderImage>();
    auto outsetDimension = Dimension(5.0);
    borderImage->SetEdgeOutset(BorderImageDirection::START, outsetDimension);
    renderContext->UpdateBorderImage(borderImage);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedBorderImageOutset(textDirection);
    EXPECT_EQ(borderImage->GetBorderImageEdge(BorderImageDirection::LEFT).GetBorderImageOutset(), outsetDimension);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedBorderImageOutset(textDirection);
    EXPECT_EQ(borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT).GetBorderImageOutset(), outsetDimension);
}

/**
 * @tc.name: CheckLocalizedBorderImageOutset002
 * @tc.desc: Test CheckLocalizedBorderImageOutset when borderImageEnd_ has value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageOutset002, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderImage = AceType::MakeRefPtr<BorderImage>();
    auto outsetDimension = Dimension(5.0);
    borderImage->SetEdgeOutset(BorderImageDirection::END, outsetDimension);
    renderContext->UpdateBorderImage(borderImage);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedBorderImageOutset(textDirection);
    EXPECT_EQ(borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT).GetBorderImageOutset(), outsetDimension);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedBorderImageOutset(textDirection);
    EXPECT_EQ(borderImage->GetBorderImageEdge(BorderImageDirection::LEFT).GetBorderImageOutset(), outsetDimension);
}

/**
 * @tc.name: CheckLocalizedBorderImageOutset003
 * @tc.desc: Test CheckLocalizedBorderImageOutset When neither borderImageStart_ nor borderImageEnd_ has a value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageOutset003, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderImage = AceType::MakeRefPtr<BorderImage>();
    renderContext->UpdateBorderImage(borderImage);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedBorderImageOutset(textDirection);
    EXPECT_FALSE(borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT).GetBorderImageOutset().IsValid());
    EXPECT_FALSE(borderImage->GetBorderImageEdge(BorderImageDirection::LEFT).GetBorderImageOutset().IsValid());
}

/**
 * @tc.name: CheckLocalizedBorderImageWidth001
 * @tc.desc: Test CheckLocalizedBorderImageWidth when borderImageStart_ has value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageWidth001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderImage = AceType::MakeRefPtr<BorderImage>();
    auto widthDimension = Dimension(5.0);
    borderImage->SetEdgeWidth(BorderImageDirection::START, widthDimension);
    renderContext->UpdateBorderImage(borderImage);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedBorderImageWidth(textDirection);
    EXPECT_EQ(borderImage->GetBorderImageEdge(BorderImageDirection::LEFT).GetBorderImageWidth(), widthDimension);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedBorderImageWidth(textDirection);
    EXPECT_EQ(borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT).GetBorderImageWidth(), widthDimension);
}

/**
 * @tc.name: CheckLocalizedBorderImageWidth002
 * @tc.desc: Test CheckLocalizedBorderImageWidth when borderImageEnd_ has value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageWidth002, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderImage = AceType::MakeRefPtr<BorderImage>();
    auto widthDimension = Dimension(5.0);
    borderImage->SetEdgeWidth(BorderImageDirection::END, widthDimension);
    renderContext->UpdateBorderImage(borderImage);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedBorderImageWidth(textDirection);
    EXPECT_EQ(borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT).GetBorderImageWidth(), widthDimension);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedBorderImageWidth(textDirection);
    EXPECT_EQ(borderImage->GetBorderImageEdge(BorderImageDirection::LEFT).GetBorderImageWidth(), widthDimension);
}

/**
 * @tc.name: CheckLocalizedBorderImageWidth003
 * @tc.desc: Test CheckLocalizedBorderImageWidth When neither borderImageStart_ nor borderImageEnd_ has a value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageWidth003, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderImage = AceType::MakeRefPtr<BorderImage>();
    renderContext->UpdateBorderImage(borderImage);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedBorderImageWidth(textDirection);
    EXPECT_FALSE(borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT).GetBorderImageWidth().IsValid());
    EXPECT_FALSE(borderImage->GetBorderImageEdge(BorderImageDirection::LEFT).GetBorderImageWidth().IsValid());
}

/**
 * @tc.name: CheckLocalizedBorderImageSlice001
 * @tc.desc: Test CheckLocalizedBorderImageSlice when borderImageStart_ has value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageSlice001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderImage = AceType::MakeRefPtr<BorderImage>();
    auto sliceDimension = Dimension(5.0);
    borderImage->SetEdgeSlice(BorderImageDirection::START, sliceDimension);
    renderContext->UpdateBorderImage(borderImage);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedBorderImageSlice(textDirection);
    EXPECT_EQ(borderImage->GetBorderImageEdge(BorderImageDirection::LEFT).GetBorderImageSlice(), sliceDimension);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedBorderImageSlice(textDirection);
    EXPECT_EQ(borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT).GetBorderImageSlice(), sliceDimension);
}

/**
 * @tc.name: CheckLocalizedBorderImageSlice002
 * @tc.desc: Test CheckLocalizedBorderImageSlice when borderImageEnd_ has value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageSlice002, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderImage = AceType::MakeRefPtr<BorderImage>();
    auto sliceDimension = Dimension(5.0);
    borderImage->SetEdgeSlice(BorderImageDirection::END, sliceDimension);
    renderContext->UpdateBorderImage(borderImage);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedBorderImageSlice(textDirection);
    EXPECT_EQ(borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT).GetBorderImageSlice(), sliceDimension);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedBorderImageSlice(textDirection);
    EXPECT_EQ(borderImage->GetBorderImageEdge(BorderImageDirection::LEFT).GetBorderImageSlice(), sliceDimension);
}

/**
 * @tc.name: CheckLocalizedBorderImageSlice003
 * @tc.desc: Test CheckLocalizedBorderImageSlice When neither borderImageStart_ nor borderImageEnd_ has a value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageSlice003, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderImage = AceType::MakeRefPtr<BorderImage>();
    renderContext->UpdateBorderImage(borderImage);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedBorderImageSlice(textDirection);
    EXPECT_FALSE(borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT).GetBorderImageSlice().IsValid());
    EXPECT_FALSE(borderImage->GetBorderImageEdge(BorderImageDirection::LEFT).GetBorderImageSlice().IsValid());
}

/**
 * @tc.name: CheckLocalizedEdgeColors001
 * @tc.desc: Test CheckLocalizedEdgeColors when startColor has value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedEdgeColors001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    BorderColorProperty borderColorProperty;
    borderColorProperty.startColor = std::make_optional<Color>(Color::BLUE);
    renderContext->UpdateBorderColor(borderColorProperty);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedEdgeColors(textDirection);
    ASSERT_NE(renderContext->GetBorder(), nullptr);
    EXPECT_EQ(renderContext->GetBorder()->GetBorderColorValue().leftColor.value(), Color::BLUE);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedEdgeColors(textDirection);
    ASSERT_NE(renderContext->GetBorder(), nullptr);
    EXPECT_EQ(renderContext->GetBorder()->GetBorderColorValue().rightColor.value(), Color::BLUE);
}

/**
 * @tc.name: CheckLocalizedEdgeColors002
 * @tc.desc: Test CheckLocalizedEdgeColors when endColor,topColor,bottomColor all have values
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedEdgeColors002, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    BorderColorProperty borderColorProperty;
    borderColorProperty.endColor = std::make_optional<Color>(Color::BLUE);
    borderColorProperty.topColor = std::make_optional<Color>(Color::RED);
    borderColorProperty.bottomColor = std::make_optional<Color>(Color::GREEN);
    renderContext->UpdateBorderColor(borderColorProperty);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedEdgeColors(textDirection);
    ASSERT_NE(renderContext->GetBorder(), nullptr);
    EXPECT_EQ(renderContext->GetBorder()->GetBorderColorValue().rightColor.value(), Color::BLUE);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedEdgeColors(textDirection);
    ASSERT_NE(renderContext->GetBorder(), nullptr);
    EXPECT_EQ(renderContext->GetBorder()->GetBorderColorValue().leftColor.value(), Color::BLUE);
    EXPECT_EQ(renderContext->GetBorder()->GetBorderColorValue().topColor.value(), Color::RED);
}

/**
 * @tc.name: CheckLocalizedEdgeColors003
 * @tc.desc: Test CheckLocalizedEdgeColors When neither startColor nor endColor has a value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedEdgeColors003, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    BorderColorProperty borderColorProperty;
    renderContext->UpdateBorderColor(borderColorProperty);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedEdgeColors(textDirection);
    ASSERT_NE(renderContext->GetBorder(), nullptr);
    EXPECT_EQ(renderContext->GetBorder()->GetBorderColorValue().multiValued, false);
}

/**
 * @tc.name: CheckLocalizedEdgeWidths001
 * @tc.desc: Test CheckLocalizedEdgeWidths when startDimen,topDimen,bottomDimen,leftDimen all have values
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedEdgeWidths001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    BorderWidthProperty borderWidth;
    auto startDimen = Dimension(5.0);
    borderWidth.startDimen = std::make_optional<Dimension>(5.0);
    borderWidth.topDimen = std::make_optional<Dimension>(6.0);
    borderWidth.bottomDimen = std::make_optional<Dimension>(7.0);
    borderWidth.leftDimen = std::make_optional<Dimension>(8.0);
    renderContext->UpdateBorderWidth(borderWidth);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedEdgeWidths(layoutProperty, textDirection);
    ASSERT_NE(layoutProperty->GetBorderWidthProperty(), nullptr);
    EXPECT_EQ(layoutProperty->GetBorderWidthProperty()->leftDimen, startDimen);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedEdgeWidths(layoutProperty, textDirection);
    ASSERT_NE(layoutProperty->GetBorderWidthProperty(), nullptr);
    EXPECT_EQ(layoutProperty->GetBorderWidthProperty()->rightDimen, startDimen);
}

/**
 * @tc.name: CheckLocalizedEdgeWidths002
 * @tc.desc: Test CheckLocalizedEdgeWidths when endDimen,rightDimen have values
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedEdgeWidths002, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    BorderWidthProperty borderWidth;
    auto endDimen = Dimension(5.0);
    borderWidth.endDimen = std::make_optional<Dimension>(5.0);
    borderWidth.rightDimen = std::make_optional<Dimension>(6.0);
    renderContext->UpdateBorderWidth(borderWidth);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedEdgeWidths(layoutProperty, textDirection);
    ASSERT_NE(layoutProperty->GetBorderWidthProperty(), nullptr);
    EXPECT_EQ(layoutProperty->GetBorderWidthProperty()->rightDimen, endDimen);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedEdgeWidths(layoutProperty, textDirection);
    ASSERT_NE(layoutProperty->GetBorderWidthProperty(), nullptr);
    EXPECT_EQ(layoutProperty->GetBorderWidthProperty()->leftDimen, endDimen);
}

/**
 * @tc.name: CheckLocalizedEdgeWidths003
 * @tc.desc: Test CheckLocalizedEdgeWidths When neither startDimen nor endDimen has a value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedEdgeWidths003, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    BorderWidthProperty borderWidth;
    renderContext->UpdateBorderWidth(borderWidth);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedEdgeWidths(layoutProperty, textDirection);
    ASSERT_NE(renderContext->GetBorder(), nullptr);
    EXPECT_EQ(renderContext->GetBorder()->GetBorderWidthValue().multiValued, false);
}

/**
 * @tc.name: CheckLocalizedMargin001
 * @tc.desc: Test CheckLocalizedMargin when start,top,bottom,left have values
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedMargin001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    PaddingPropertyT<CalcLength> paddingProperty;
    paddingProperty.start = std::make_optional<CalcLength>(5.0);
    paddingProperty.top = std::make_optional<CalcLength>(6.0);
    paddingProperty.bottom = std::make_optional<CalcLength>(7.0);
    paddingProperty.left = std::make_optional<CalcLength>(8.0);
    layoutProperty->UpdateMargin(paddingProperty);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedMargin(layoutProperty, textDirection);
    auto& marginProperty = layoutProperty->GetMarginProperty();
    ASSERT_NE(marginProperty, nullptr);
    EXPECT_EQ(marginProperty->left.value(), CalcLength(5.0));

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedMargin(layoutProperty, textDirection);
    ASSERT_NE(marginProperty, nullptr);
    EXPECT_EQ(marginProperty->right.value(), CalcLength(5.0));
}

/**
 * @tc.name: CheckLocalizedMargin002
 * @tc.desc: Test CheckLocalizedMargin when end,right have values
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedMargin002, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    PaddingPropertyT<CalcLength> paddingProperty;
    paddingProperty.end = std::make_optional<CalcLength>(5.0);
    paddingProperty.right = std::make_optional<CalcLength>(6.0);
    layoutProperty->UpdateMargin(paddingProperty);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedMargin(layoutProperty, textDirection);
    auto& marginProperty = layoutProperty->GetMarginProperty();
    ASSERT_NE(marginProperty, nullptr);
    EXPECT_EQ(marginProperty->right.value(), CalcLength(5.0));

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedMargin(layoutProperty, textDirection);
    ASSERT_NE(marginProperty, nullptr);
    EXPECT_EQ(marginProperty->left.value(), CalcLength(5.0));
}

/**
 * @tc.name: CheckLocalizedMargin003
 * @tc.desc: Test CheckLocalizedMargin When neither start nor end has a value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedMargin003, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    PaddingPropertyT<CalcLength> paddingProperty;
    layoutProperty->UpdateMargin(paddingProperty);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedMargin(layoutProperty, textDirection);
    auto& marginProperty = layoutProperty->GetMarginProperty();
    ASSERT_NE(marginProperty, nullptr);
    EXPECT_FALSE(marginProperty->right.has_value());
    EXPECT_FALSE(marginProperty->left.has_value());
}

/**
 * @tc.name: CheckLocalizedPadding001
 * @tc.desc: Test CheckLocalizedPadding when start,top,bottom,left have values
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedPadding001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    PaddingPropertyT<CalcLength> paddingProperty;
    paddingProperty.start = std::make_optional<CalcLength>(5.0);
    paddingProperty.top = std::make_optional<CalcLength>(6.0);
    paddingProperty.bottom = std::make_optional<CalcLength>(7.0);
    paddingProperty.left = std::make_optional<CalcLength>(8.0);
    layoutProperty->UpdatePadding(paddingProperty);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedPadding(layoutProperty, textDirection);
    auto& padding = layoutProperty->GetPaddingProperty();
    ASSERT_NE(padding, nullptr);
    EXPECT_EQ(padding->left.value(), CalcLength(5.0));

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedPadding(layoutProperty, textDirection);
    ASSERT_NE(padding, nullptr);
    EXPECT_EQ(padding->right.value(), CalcLength(5.0));
}

/**
 * @tc.name: CheckLocalizedPadding002
 * @tc.desc: Test CheckLocalizedPadding when end,right have values
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedPadding002, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    PaddingPropertyT<CalcLength> paddingProperty;
    paddingProperty.end = std::make_optional<CalcLength>(5.0);
    paddingProperty.right = std::make_optional<CalcLength>(6.0);
    layoutProperty->UpdatePadding(paddingProperty);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedPadding(layoutProperty, textDirection);
    auto& padding = layoutProperty->GetPaddingProperty();
    ASSERT_NE(padding, nullptr);
    EXPECT_EQ(padding->right.value(), CalcLength(5.0));

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedPadding(layoutProperty, textDirection);
    ASSERT_NE(padding, nullptr);
    EXPECT_EQ(padding->left.value(), CalcLength(5.0));
}

/**
 * @tc.name: CheckLocalizedPadding003
 * @tc.desc: Test CheckLocalizedPadding When neither start nor end has a value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedPadding003, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    PaddingPropertyT<CalcLength> paddingProperty;
    layoutProperty->UpdatePadding(paddingProperty);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedPadding(layoutProperty, textDirection);
    auto& padding = layoutProperty->GetPaddingProperty();
    ASSERT_NE(padding, nullptr);
    EXPECT_FALSE(padding->right.has_value());
    EXPECT_FALSE(padding->left.has_value());
}

/**
 * @tc.name: LocalizedPaddingOrMarginChange001
 * @tc.desc: Test LocalizedPaddingOrMarginChange
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, LocalizedPaddingOrMarginChange001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    PaddingPropertyT<CalcLength> paddingProperty1;
    std::unique_ptr<PaddingProperty> PaddingProperty2 = std::make_unique<PaddingProperty>();

    layoutProperty->LocalizedPaddingOrMarginChange(paddingProperty1, PaddingProperty2);

    paddingProperty1.end = std::make_optional<CalcLength>(5.0);
    layoutProperty->LocalizedPaddingOrMarginChange(paddingProperty1, PaddingProperty2);
    EXPECT_EQ(PaddingProperty2->end.value(), CalcLength(5.0));

    paddingProperty1.start = std::make_optional<CalcLength>(5.0);
    layoutProperty->LocalizedPaddingOrMarginChange(paddingProperty1, PaddingProperty2);
    EXPECT_EQ(PaddingProperty2->start.value(), CalcLength(5.0));
}

/**
 * @tc.name: CheckLocalizedOuterBorderColor001
 * @tc.desc: Test CheckLocalizedOuterBorderColor when startColor has value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedOuterBorderColor001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    BorderColorProperty borderColorProperty;
    borderColorProperty.startColor = std::make_optional<Color>(Color::BLUE);
    renderContext->UpdateOuterBorderColor(borderColorProperty);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedOuterBorderColor(textDirection);
    ASSERT_NE(renderContext->GetOuterBorder(), nullptr);
    EXPECT_EQ(renderContext->GetOuterBorder()->GetOuterBorderColorValue().leftColor.value(), Color::BLUE);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedOuterBorderColor(textDirection);
    ASSERT_NE(renderContext->GetOuterBorder(), nullptr);
    EXPECT_EQ(renderContext->GetOuterBorder()->GetOuterBorderColorValue().rightColor.value(), Color::BLUE);
}

/**
 * @tc.name: CheckLocalizedOuterBorderColor002
 * @tc.desc: Test CheckLocalizedOuterBorderColor when endColor,topColor,bottomColor have values
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedOuterBorderColor002, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    BorderColorProperty borderColorProperty;
    borderColorProperty.endColor = std::make_optional<Color>(Color::BLUE);
    borderColorProperty.topColor = std::make_optional<Color>(Color::RED);
    borderColorProperty.bottomColor = std::make_optional<Color>(Color::GREEN);
    renderContext->UpdateOuterBorderColor(borderColorProperty);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedOuterBorderColor(textDirection);
    layoutProperty->CheckLocalizedOuterBorderColor(textDirection);
    ASSERT_NE(renderContext->GetOuterBorder(), nullptr);
    EXPECT_EQ(renderContext->GetOuterBorder()->GetOuterBorderColorValue().rightColor.value(), Color::BLUE);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedOuterBorderColor(textDirection);
    ASSERT_NE(renderContext->GetOuterBorder(), nullptr);
    EXPECT_EQ(renderContext->GetOuterBorder()->GetOuterBorderColorValue().leftColor.value(), Color::BLUE);
}

/**
 * @tc.name: CheckLocalizedOuterBorderColor003
 * @tc.desc: Test CheckLocalizedOuterBorderColor When neither startColor nor endColor has a value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedOuterBorderColor003, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    BorderColorProperty borderColorProperty;
    renderContext->UpdateOuterBorderColor(borderColorProperty);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedOuterBorderColor(textDirection);
    ASSERT_NE(renderContext->GetOuterBorder(), nullptr);
    EXPECT_FALSE(renderContext->GetOuterBorder()->GetOuterBorderColorValue().rightColor.has_value());
    EXPECT_FALSE(renderContext->GetOuterBorder()->GetOuterBorderColorValue().leftColor.has_value());
}

/**
 * @tc.name: CheckLocalizedBorderRadiuses001
 * @tc.desc: Test CheckLocalizedBorderRadiuses when radiusTopStart,radiusTopEnd,
 * radiusBottomStart,radiusBottomEnd have values
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderRadiuses001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopStart = std::make_optional<Dimension>(5.0);
    borderRadius.radiusTopEnd = std::make_optional<Dimension>(6.0);
    borderRadius.radiusBottomStart = std::make_optional<Dimension>(7.0);
    borderRadius.radiusBottomEnd = std::make_optional<Dimension>(8.0);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBorderRadius(borderRadius);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedBorderRadiuses(textDirection);
    ASSERT_NE(renderContext->GetBorder(), nullptr);
    EXPECT_EQ(renderContext->GetBorder()->GetBorderRadiusValue().radiusTopLeft.value(), Dimension(5.0));

    textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedBorderRadiuses(textDirection);
    ASSERT_NE(renderContext->GetBorder(), nullptr);
    EXPECT_EQ(renderContext->GetBorder()->GetBorderRadiusValue().radiusTopRight.value(), Dimension(5.0));
}

/**
 * @tc.name: CheckLocalizedBorderRadiuses002
 * @tc.desc: Test CheckLocalizedBorderRadiuses when radiusTopStart,radiusTopEnd,
 * radiusBottomStart,radiusBottomEnd have no values
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderRadiuses002, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    BorderRadiusProperty borderRadius;
    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBorderRadius(borderRadius);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedBorderRadiuses(textDirection);
    ASSERT_NE(renderContext->GetBorder(), nullptr);
    EXPECT_FALSE(renderContext->GetBorder()->GetBorderRadiusValue().radiusTopLeft.has_value());
    EXPECT_FALSE(renderContext->GetBorder()->GetBorderRadiusValue().radiusTopRight.has_value());
}

/**
 * @tc.name: CheckLocalizedBorderRadiuses003
 * @tc.desc: Test CheckLocalizedBorderRadiuses When one of radiusTopStart,radiusTopEnd,
 * radiusBottomStart,radiusBottomEnd has a value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderRadiuses003, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto radiusTopStart = Dimension(5.0);
    auto radiusTopEnd = Dimension(6.0);
    auto radiusBottomStart = Dimension(7.0);
    auto radiusBottomEnd = Dimension(8.0);

    BorderRadiusProperty borderRadius;
    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    borderRadius.radiusTopStart = std::make_optional<Dimension>(radiusTopStart);
    renderContext->UpdateBorderRadius(borderRadius);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckLocalizedBorderRadiuses(textDirection);
    ASSERT_NE(renderContext->GetBorder(), nullptr);
    EXPECT_EQ(renderContext->GetBorder()->GetBorderRadiusValue().radiusTopLeft.value(), radiusTopStart);

    borderRadius.radiusTopStart = std::nullopt;
    borderRadius.radiusTopEnd = std::make_optional<Dimension>(radiusTopEnd);
    renderContext->GetBorder()->UpdateBorderRadius(borderRadius);
    layoutProperty->CheckLocalizedBorderRadiuses(textDirection);
    EXPECT_EQ(renderContext->GetBorder()->GetBorderRadiusValue().radiusTopRight.value(), radiusTopEnd);

    borderRadius.radiusTopEnd = std::nullopt;
    borderRadius.radiusBottomStart = std::make_optional<Dimension>(radiusBottomStart);
    renderContext->GetBorder()->UpdateBorderRadius(borderRadius);
    layoutProperty->CheckLocalizedBorderRadiuses(textDirection);
    EXPECT_EQ(renderContext->GetBorder()->GetBorderRadiusValue().radiusBottomLeft.value(), radiusBottomStart);

    borderRadius.radiusBottomStart = std::nullopt;
    borderRadius.radiusBottomEnd = std::make_optional<Dimension>(radiusBottomEnd);
    renderContext->GetBorder()->UpdateBorderRadius(borderRadius);
    layoutProperty->CheckLocalizedBorderRadiuses(textDirection);
    EXPECT_EQ(renderContext->GetBorder()->GetBorderRadiusValue().radiusBottomRight.value(), radiusBottomEnd);
}

/**
 * @tc.name: CheckOffsetLocalizedEdges001
 * @tc.desc: Test CheckOffsetLocalizedEdges
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckOffsetLocalizedEdges001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto top = CalcDimension(1.0);
    auto bottom = CalcDimension(2.0);
    auto left = CalcDimension(3.0);
    auto right = CalcDimension(4.0);

    EdgesParam edges;
    edges.SetTop(top);
    edges.SetBottom(bottom);
    edges.SetLeft(left);
    edges.SetRight(right);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateOffsetEdges(edges);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckOffsetLocalizedEdges(textDirection);
    ASSERT_NE(renderContext->GetPositionProperty(), nullptr);
    EXPECT_EQ(renderContext->GetPositionProperty()->GetOffsetEdgesValue().left.value(), left);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckOffsetLocalizedEdges(textDirection);
    ASSERT_NE(renderContext->GetPositionProperty(), nullptr);
    EXPECT_EQ(renderContext->GetPositionProperty()->GetOffsetEdgesValue().left.value(), right);
}

/**
 * @tc.name: CheckOffsetLocalizedEdges002
 * @tc.desc: Test CheckOffsetLocalizedEdges
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckOffsetLocalizedEdges002, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    EdgesParam edges;

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateOffsetEdges(edges);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckOffsetLocalizedEdges(textDirection);
    ASSERT_NE(renderContext->GetPositionProperty(), nullptr);
    EXPECT_FALSE(renderContext->GetPositionProperty()->GetOffsetEdgesValue().left.has_value());
    EXPECT_FALSE(renderContext->GetPositionProperty()->GetOffsetEdgesValue().right.has_value());
}

/**
 * @tc.name: CheckPositionLocalizedEdges001
 * @tc.desc: Test CheckPositionLocalizedEdges
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckPositionLocalizedEdges001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto top = CalcDimension(1.0);
    auto bottom = CalcDimension(2.0);
    auto left = CalcDimension(3.0);
    auto right = CalcDimension(4.0);

    EdgesParam edges;
    edges.SetTop(top);
    edges.SetBottom(bottom);
    edges.SetLeft(left);
    edges.SetRight(right);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdatePositionEdges(edges);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckPositionLocalizedEdges(textDirection);
    ASSERT_NE(renderContext->GetPositionProperty(), nullptr);
    EXPECT_EQ(renderContext->GetPositionProperty()->GetPositionEdgesValue().left.value(), left);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckPositionLocalizedEdges(textDirection);
    ASSERT_NE(renderContext->GetPositionProperty(), nullptr);
    EXPECT_EQ(renderContext->GetPositionProperty()->GetPositionEdgesValue().left.value(), right);
}

/**
 * @tc.name: CheckPositionLocalizedEdges002
 * @tc.desc: Test CheckPositionLocalizedEdges
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckPositionLocalizedEdges002, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    EdgesParam edges;

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdatePositionEdges(edges);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckPositionLocalizedEdges(textDirection);
    ASSERT_NE(renderContext->GetPositionProperty(), nullptr);
    EXPECT_FALSE(renderContext->GetPositionProperty()->GetPositionEdgesValue().left.has_value());
    EXPECT_FALSE(renderContext->GetPositionProperty()->GetPositionEdgesValue().right.has_value());
}

/**
 * @tc.name: ConstraintEqual001
 * @tc.desc: Test ConstraintEqual when preContentConstraint is nullopt
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, ConstraintEqual001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    auto preLayoutConstraint = std::make_optional<LayoutConstraintF>();
    auto preContentConstraint = std::make_optional<LayoutConstraintF>();
    preContentConstraint = std::nullopt;

    layoutProperty->layoutConstraint_ = preLayoutConstraint;
    bool bResult = layoutProperty->ConstraintEqual(preLayoutConstraint, preContentConstraint);
    EXPECT_FALSE(bResult);
}

/**
 * @tc.name: UpdateAllGeometryTransition001
 * @tc.desc: Test UpdateAllGeometryTransition
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, UpdateAllGeometryTransition001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = CustomNode::CreateCustomNode(parentId, "parent");
    layoutProperty->UpdateAllGeometryTransition(parent);

    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->UpdateAllGeometryTransition(frameNodeHost);
    EXPECT_FALSE(layoutProperty->GetGeometryTransition());
}

/**
 * @tc.name: FromJson001
 * @tc.desc: Test FromJson
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, FromJson001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    auto json = JsonUtil::Create(true);
    json->Put("padding", "0.0");
    json->Put("margin", "0.0");
    json->Put("direction", "Direction.Rtl");
    layoutProperty->FromJson(json);

    EXPECT_EQ(layoutProperty->GetNonAutoLayoutDirection(), TextDirection::RTL);
}

/**
 * @tc.name: UpdateSafeAreaPadding001
 * @tc.desc: Test UpdateSafeAreaPadding
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, UpdateSafeAreaPadding001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    PaddingProperty paddingProperty;
    layoutProperty->ResetSafeAreaPadding();
    layoutProperty->UpdateSafeAreaPadding(paddingProperty);
    EXPECT_TRUE(layoutProperty->GetSafeAreaPaddingProperty());

    paddingProperty.start = std::make_optional<CalcLength>(5.0);
    layoutProperty->UpdateSafeAreaPadding(paddingProperty);
    layoutProperty->ResetSafeAreaPadding();
    EXPECT_FALSE(layoutProperty->GetSafeAreaPaddingProperty());
}

/**
 * @tc.name: PixelRoundToJsonValue001
 * @tc.desc: Test PixelRoundToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, PixelRoundToJsonValue001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    const std::string VALUE = "PixelRoundCalcPolicy.FORCE_CEIL";

    layoutProperty->pixelRoundFlag_ = static_cast<uint8_t>(PixelRoundPolicy::FORCE_CEIL_START);
    auto res = layoutProperty->PixelRoundToJsonValue();
    auto jsonValue = JsonUtil::ParseJsonString(res);
    ASSERT_NE(jsonValue, nullptr);
    EXPECT_EQ(jsonValue->GetString("start"), VALUE);

    layoutProperty->pixelRoundFlag_ = static_cast<uint8_t>(PixelRoundPolicy::FORCE_CEIL_TOP);
    res = layoutProperty->PixelRoundToJsonValue();
    jsonValue = JsonUtil::ParseJsonString(res);
    ASSERT_NE(jsonValue, nullptr);
    EXPECT_EQ(jsonValue->GetString("top"), VALUE);

    layoutProperty->pixelRoundFlag_ = static_cast<uint8_t>(PixelRoundPolicy::FORCE_CEIL_END);
    res = layoutProperty->PixelRoundToJsonValue();
    jsonValue = JsonUtil::ParseJsonString(res);
    ASSERT_NE(jsonValue, nullptr);
    EXPECT_EQ(jsonValue->GetString("end"), VALUE);

    layoutProperty->pixelRoundFlag_ = static_cast<uint8_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM);
    res = layoutProperty->PixelRoundToJsonValue();
    jsonValue = JsonUtil::ParseJsonString(res);
    ASSERT_NE(jsonValue, nullptr);
    EXPECT_EQ(jsonValue->GetString("bottom"), VALUE);
}
}
