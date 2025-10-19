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

#include "test/unittest/core/layout/layout_property_test_ng_two.h"

namespace OHOS::Ace::NG {

/**
 * @tc.name: CheckLocalizedBorderImageOutset001
 * @tc.desc: Test CheckLocalizedBorderImageOutset when borderImageStart_ has value
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageOutset001, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageOutset002, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageOutset003, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageWidth001, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageWidth002, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageWidth003, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageSlice001, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageSlice002, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageSlice003, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedEdgeColors001, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedEdgeColors002, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedEdgeColors003, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedEdgeWidths001, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedEdgeWidths002, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedEdgeWidths003, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedMargin001, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedMargin002, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedMargin003, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedPadding001, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedPadding002, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedPadding003, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, LocalizedPaddingOrMarginChange001, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedOuterBorderColor001, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedOuterBorderColor002, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedOuterBorderColor003, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderRadiuses001, TestSize.Level0)
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

}