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

#include "core/components_ng/property/position_property.h"

namespace OHOS::Ace::NG {

/**
 * @tc.name: CheckLocalizedBorderRadiuses002
 * @tc.desc: Test CheckLocalizedBorderRadiuses when radiusTopStart,radiusTopEnd,
 * radiusBottomStart,radiusBottomEnd have no values
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderRadiuses002, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderRadiuses003, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckOffsetLocalizedEdges001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto top = CalcDimension(1.0);
    auto bottom = CalcDimension(2.0);
    auto start = CalcDimension(3.0);
    auto end = CalcDimension(4.0);

    EdgesParam edges;
    edges.SetTop(top);
    edges.SetBottom(bottom);
    edges.start = start;
    edges.end = end;

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateOffsetEdges(edges);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckOffsetLocalizedEdges(textDirection);
    ASSERT_NE(renderContext->GetPositionProperty(), nullptr);
    EXPECT_EQ(renderContext->GetPositionProperty()->GetOffsetEdgesValue().left.value(), start);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckOffsetLocalizedEdges(textDirection);
    ASSERT_NE(renderContext->GetPositionProperty(), nullptr);
    EXPECT_EQ(renderContext->GetPositionProperty()->GetOffsetEdgesValue().left.value(), end);
}

/**
 * @tc.name: CheckOffsetLocalizedEdges002
 * @tc.desc: Test CheckOffsetLocalizedEdges
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckOffsetLocalizedEdges002, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, CheckPositionLocalizedEdges001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto top = CalcDimension(1.0);
    auto bottom = CalcDimension(2.0);
    auto start = CalcDimension(3.0);
    auto end = CalcDimension(4.0);

    EdgesParam edges;
    edges.SetTop(top);
    edges.SetBottom(bottom);
    edges.start = start;
    edges.end = end;

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdatePositionEdges(edges);

    auto textDirection = TextDirection::LTR;
    layoutProperty->CheckPositionLocalizedEdges(textDirection);
    ASSERT_NE(renderContext->GetPositionProperty(), nullptr);
    EXPECT_EQ(renderContext->GetPositionProperty()->GetPositionEdgesValue().left.value(), start);

    textDirection = TextDirection::RTL;
    layoutProperty->CheckPositionLocalizedEdges(textDirection);
    ASSERT_NE(renderContext->GetPositionProperty(), nullptr);
    EXPECT_EQ(renderContext->GetPositionProperty()->GetPositionEdgesValue().left.value(), end);
}

/**
 * @tc.name: CheckPositionLocalizedEdges002
 * @tc.desc: Test CheckPositionLocalizedEdges
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckPositionLocalizedEdges002, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, ConstraintEqual001, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, UpdateAllGeometryTransition001, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, FromJson001, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, UpdateSafeAreaPadding001, TestSize.Level0)
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
HWTEST_F(LayoutPropertyTestNgTwo, PixelRoundToJsonValue001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    const std::string VALUE = "PixelRoundCalcPolicy.FORCE_CEIL";

    layoutProperty->pixelRoundFlag_ = static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_START);
    auto res = layoutProperty->PixelRoundToJsonValue();
    auto jsonValue = JsonUtil::ParseJsonString(res);
    ASSERT_NE(jsonValue, nullptr);
    EXPECT_EQ(jsonValue->GetString("start"), VALUE);

    layoutProperty->pixelRoundFlag_ = static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_TOP);
    res = layoutProperty->PixelRoundToJsonValue();
    jsonValue = JsonUtil::ParseJsonString(res);
    ASSERT_NE(jsonValue, nullptr);
    EXPECT_EQ(jsonValue->GetString("top"), VALUE);

    layoutProperty->pixelRoundFlag_ = static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_END);
    res = layoutProperty->PixelRoundToJsonValue();
    jsonValue = JsonUtil::ParseJsonString(res);
    ASSERT_NE(jsonValue, nullptr);
    EXPECT_EQ(jsonValue->GetString("end"), VALUE);

    layoutProperty->pixelRoundFlag_ = static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM);
    res = layoutProperty->PixelRoundToJsonValue();
    jsonValue = JsonUtil::ParseJsonString(res);
    ASSERT_NE(jsonValue, nullptr);
    EXPECT_EQ(jsonValue->GetString("bottom"), VALUE);
}

/**
 * @tc.name: CheckLocalizedBorderImageSlice004
 * @tc.desc: Test CheckLocalizedBorderImageSlice when Api is 12 and 14
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageSlice004, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderImage = AceType::MakeRefPtr<BorderImage>();
    auto sliceDimension = Dimension(5.0);
    auto widthDimension = Dimension(5.0);
    int32_t settingApiVersion = 12;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
    borderImage->SetEdgeSlice(BorderImageDirection::LEFT, sliceDimension);
    borderImage->SetEdgeWidth(BorderImageDirection::START, widthDimension);
    renderContext->UpdateBorderImage(borderImage);

    auto textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedBorderImageSlice(textDirection);
    EXPECT_EQ(borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT).GetBorderImageSlice(), Dimension(0.0));

    settingApiVersion = 14;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
    auto borderImage1 = AceType::MakeRefPtr<BorderImage>();
    borderImage1->SetEdgeSlice(BorderImageDirection::LEFT, sliceDimension);
    borderImage1->SetEdgeWidth(BorderImageDirection::START, widthDimension);
    renderContext->UpdateBorderImage(borderImage1);

    layoutProperty->CheckLocalizedBorderImageSlice(textDirection);
    EXPECT_EQ(borderImage1->GetBorderImageEdge(BorderImageDirection::LEFT).GetBorderImageSlice(), sliceDimension);
}

/**
 * @tc.name: CheckLocalizedBorderImageWidth004
 * @tc.desc: Test CheckLocalizedBorderImageWidth when Api is 12 and 14
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageWidth004, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderImage = AceType::MakeRefPtr<BorderImage>();
    auto sliceDimension = Dimension(5.0);
    auto widthDimension = Dimension(5.0);
    int32_t settingApiVersion = 12;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
    borderImage->SetEdgeSlice(BorderImageDirection::START, sliceDimension);
    borderImage->SetEdgeWidth(BorderImageDirection::LEFT, widthDimension);
    renderContext->UpdateBorderImage(borderImage);

    auto textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedBorderImageWidth(textDirection);
    EXPECT_EQ(borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT).GetBorderImageWidth(), Dimension(0.0));

    settingApiVersion = 14;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
    auto borderImage1 = AceType::MakeRefPtr<BorderImage>();
    borderImage1->SetEdgeSlice(BorderImageDirection::START, sliceDimension);
    borderImage1->SetEdgeWidth(BorderImageDirection::LEFT, widthDimension);
    renderContext->UpdateBorderImage(borderImage);
    layoutProperty->CheckLocalizedBorderImageWidth(textDirection);
    EXPECT_EQ(borderImage1->GetBorderImageEdge(BorderImageDirection::LEFT).GetBorderImageWidth(), widthDimension);
}

/**
 * @tc.name: CheckLocalizedBorderImageOutset004
 * @tc.desc: Test CheckLocalizedBorderImageOutset when Api is 12 and 14
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckLocalizedBorderImageOutset004, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    auto renderContext = frameNodeHost->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderImage = AceType::MakeRefPtr<BorderImage>();
    auto outsetDimension = Dimension(5.0);
    auto widthDimension = Dimension(5.0);
    int32_t settingApiVersion = 12;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
    borderImage->SetEdgeOutset(BorderImageDirection::LEFT, outsetDimension);
    borderImage->SetEdgeWidth(BorderImageDirection::START, widthDimension);
    renderContext->UpdateBorderImage(borderImage);

    auto textDirection = TextDirection::RTL;
    layoutProperty->CheckLocalizedBorderImageOutset(textDirection);
    EXPECT_EQ(borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT).GetBorderImageOutset(), Dimension(0.0));

    settingApiVersion = 14;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
    renderContext->UpdateBorderImage(borderImage);
    auto borderImage1 = AceType::MakeRefPtr<BorderImage>();
    borderImage1->SetEdgeOutset(BorderImageDirection::LEFT, outsetDimension);
    borderImage1->SetEdgeWidth(BorderImageDirection::START, widthDimension);
    layoutProperty->CheckLocalizedBorderImageOutset(textDirection);
    EXPECT_EQ(borderImage1->GetBorderImageEdge(BorderImageDirection::LEFT).GetBorderImageOutset(), outsetDimension);
}

/**
 * @tc.name: UpdateLocalizedAlignment001
 * @tc.desc: Test cast to UpdateLocalizedAlignment
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, UpdateLocalizedAlignment001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    EXPECT_FALSE(layoutProperty->positionProperty_);
    layoutProperty->UpdateLocalizedAlignment("top_start");
    auto align = layoutProperty->GetPositionProperty()->GetLocalizedAlignment().value_or("center");
    EXPECT_EQ(align, "top_start");

    layoutProperty->UpdateLocalizedAlignment("bottom_end");
    auto align1 = layoutProperty->GetPositionProperty()->GetLocalizedAlignment().value_or("center");
    EXPECT_EQ(align1, "bottom_end");
}

/**
 * @tc.name: UpdateIsMirrorable001
 * @tc.desc: Test cast to UpdateIsMirrorable
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, UpdateIsMirrorable001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->UpdateIsMirrorable(true);
    auto isMirrorable = layoutProperty->GetPositionProperty()->GetIsMirrorable().value_or(false);
    EXPECT_EQ(isMirrorable, true);

    layoutProperty->UpdateIsMirrorable(false);
    auto isMirrorable1 = layoutProperty->GetPositionProperty()->GetIsMirrorable().value_or(false);
    EXPECT_EQ(isMirrorable1, false);
}

HWTEST_F(LayoutPropertyTestNgTwo, UpdateLayoutConstraint001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty and constraint.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    MeasureProperty constraint;
    constraint.maxSize = CALC_SIZE;
    constraint.minSize = CALC_SIZE;
    constraint.selfIdealSize = CALC_SIZE;
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>(constraint);
    layoutProperty->magicItemProperty_.UpdateAspectRatio(1.0);
    layoutProperty->measureType_ = MeasureType::MATCH_PARENT;
    auto frameNode = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto customMeasureLayoutNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(2, V2::TEXT_ETS_TAG);
    ASSERT_NE(customMeasureLayoutNode, nullptr);
    frameNode->parent_ = customMeasureLayoutNode;
    layoutProperty->SetHost(frameNode);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    layoutProperty->UpdateLayoutConstraint(std::move(layoutConstraintF));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->maxSize.value(), CALC_SIZE);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->minSize.value(), CALC_SIZE);
}

HWTEST_F(LayoutPropertyTestNgTwo, UpdateLayoutConstraint002, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty and constraint.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    MeasureProperty constraint;
    constraint.maxSize = CALC_SIZE;
    constraint.minSize = CALC_SIZE;
    constraint.selfIdealSize = CALC_SIZE;
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>(constraint);
    layoutProperty->magicItemProperty_.UpdateAspectRatio(1.0);
    layoutProperty->measureType_ = MeasureType::MATCH_PARENT;
    auto frameNode = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto customMeasureLayoutNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(2, V2::TEXT_ETS_TAG);
    ASSERT_NE(customMeasureLayoutNode, nullptr);
    frameNode->parent_ = customMeasureLayoutNode;
    layoutProperty->SetHost(frameNode);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    layoutProperty->UpdateLayoutConstraint(std::move(layoutConstraintF));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->maxSize.value(), CALC_SIZE);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->minSize.value(), CALC_SIZE);
}

/**
 * @tc.name: CheckBackgroundLayoutSafeAreaEdges001
 * @tc.desc: Test CheckBackgroundLayoutSafeAreaEdges
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckBackgroundLayoutSafeAreaEdges001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), true);
    layoutProperty->SetHost(frameNodeHost);

    layoutProperty->backgroundIgnoresLayoutSafeAreaEdges_ = LAYOUT_SAFE_AREA_EDGE_START | LAYOUT_SAFE_AREA_EDGE_TOP;
    layoutProperty->CheckBackgroundLayoutSafeAreaEdges(TextDirection::LTR);
    EXPECT_EQ(
        layoutProperty->backgroundIgnoresLayoutSafeAreaEdges_, LAYOUT_SAFE_AREA_EDGE_START | LAYOUT_SAFE_AREA_EDGE_TOP);
    EXPECT_EQ(layoutProperty->localizedBackgroundIgnoresLayoutSafeAreaEdges_,
        LAYOUT_SAFE_AREA_EDGE_START | LAYOUT_SAFE_AREA_EDGE_TOP);
    layoutProperty->CheckBackgroundLayoutSafeAreaEdges(TextDirection::RTL);
    EXPECT_EQ(
        layoutProperty->backgroundIgnoresLayoutSafeAreaEdges_, LAYOUT_SAFE_AREA_EDGE_START | LAYOUT_SAFE_AREA_EDGE_TOP);
    EXPECT_EQ(layoutProperty->localizedBackgroundIgnoresLayoutSafeAreaEdges_,
        LAYOUT_SAFE_AREA_EDGE_END | LAYOUT_SAFE_AREA_EDGE_TOP);

    layoutProperty->backgroundIgnoresLayoutSafeAreaEdges_ = LAYOUT_SAFE_AREA_EDGE_END | LAYOUT_SAFE_AREA_EDGE_BOTTOM;
    layoutProperty->CheckBackgroundLayoutSafeAreaEdges(TextDirection::LTR);
    EXPECT_EQ(layoutProperty->backgroundIgnoresLayoutSafeAreaEdges_,
        LAYOUT_SAFE_AREA_EDGE_END | LAYOUT_SAFE_AREA_EDGE_BOTTOM);
    EXPECT_EQ(layoutProperty->localizedBackgroundIgnoresLayoutSafeAreaEdges_,
        LAYOUT_SAFE_AREA_EDGE_END | LAYOUT_SAFE_AREA_EDGE_BOTTOM);
    layoutProperty->CheckBackgroundLayoutSafeAreaEdges(TextDirection::RTL);
    EXPECT_EQ(layoutProperty->backgroundIgnoresLayoutSafeAreaEdges_,
        LAYOUT_SAFE_AREA_EDGE_END | LAYOUT_SAFE_AREA_EDGE_BOTTOM);
    EXPECT_EQ(layoutProperty->localizedBackgroundIgnoresLayoutSafeAreaEdges_,
        LAYOUT_SAFE_AREA_EDGE_START | LAYOUT_SAFE_AREA_EDGE_BOTTOM);
}

/**
 * @tc.name: CheckIgnoreLayoutSafeArea
 * @tc.desc: Test CheckIgnoreLayoutSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckIgnoreLayoutSafeArea, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->ignoreLayoutSafeAreaOpts_ = std::make_unique<IgnoreLayoutSafeAreaOpts>();

    layoutProperty->ignoreLayoutSafeAreaOpts_->rawEdges = LAYOUT_SAFE_AREA_EDGE_START | LAYOUT_SAFE_AREA_EDGE_TOP;
    layoutProperty->CheckIgnoreLayoutSafeArea(TextDirection::LTR);
    EXPECT_EQ(
        layoutProperty->ignoreLayoutSafeAreaOpts_->edges, LAYOUT_SAFE_AREA_EDGE_START | LAYOUT_SAFE_AREA_EDGE_TOP);
    layoutProperty->CheckIgnoreLayoutSafeArea(TextDirection::RTL);
    EXPECT_EQ(layoutProperty->ignoreLayoutSafeAreaOpts_->edges, LAYOUT_SAFE_AREA_EDGE_END | LAYOUT_SAFE_AREA_EDGE_TOP);

    layoutProperty->ignoreLayoutSafeAreaOpts_->rawEdges = LAYOUT_SAFE_AREA_EDGE_END | LAYOUT_SAFE_AREA_EDGE_BOTTOM;
    layoutProperty->CheckIgnoreLayoutSafeArea(TextDirection::LTR);
    EXPECT_EQ(
        layoutProperty->ignoreLayoutSafeAreaOpts_->edges, LAYOUT_SAFE_AREA_EDGE_END | LAYOUT_SAFE_AREA_EDGE_BOTTOM);
    layoutProperty->CheckIgnoreLayoutSafeArea(TextDirection::RTL);
    EXPECT_EQ(
        layoutProperty->ignoreLayoutSafeAreaOpts_->edges, LAYOUT_SAFE_AREA_EDGE_START | LAYOUT_SAFE_AREA_EDGE_BOTTOM);
}

/**
 * @tc.name: TestIsIgnoreOptsValid
 * @tc.desc: Test IsIgnoreOptsValid
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, TestIsIgnoreOptsValid, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->ignoreLayoutSafeAreaOpts_ = std::make_unique<IgnoreLayoutSafeAreaOpts>();
    EXPECT_EQ(layoutProperty->IsIgnoreOptsValid(), false);
    layoutProperty->ignoreLayoutSafeAreaOpts_->type = LAYOUT_SAFE_AREA_TYPE_KEYBOARD;
    layoutProperty->ignoreLayoutSafeAreaOpts_->edges = LAYOUT_SAFE_AREA_EDGE_VERTICAL;
    EXPECT_EQ(layoutProperty->IsIgnoreOptsValid(), true);
}

/**
 * @tc.name: TestIsExpandConstraintNeeded
 * @tc.desc: Test IsExpandConstraintNeeded
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, TestIsExpandConstraintNeeded, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    EXPECT_EQ(layoutProperty->IsExpandConstraintNeeded(), false);
    layoutProperty->layoutPolicy_ = NG::LayoutPolicyProperty();
    layoutProperty->ignoreLayoutSafeAreaOpts_ = std::make_unique<IgnoreLayoutSafeAreaOpts>();
    layoutProperty->ignoreLayoutSafeAreaOpts_->type = LAYOUT_SAFE_AREA_TYPE_SYSTEM;
    layoutProperty->ignoreLayoutSafeAreaOpts_->edges = LAYOUT_SAFE_AREA_EDGE_ALL;
    EXPECT_EQ(layoutProperty->IsExpandConstraintNeeded(), false);

    layoutProperty->layoutPolicy_->widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutProperty->ignoreLayoutSafeAreaOpts_->edges = LAYOUT_SAFE_AREA_EDGE_VERTICAL;
    EXPECT_EQ(layoutProperty->IsExpandConstraintNeeded(), false);
    layoutProperty->ignoreLayoutSafeAreaOpts_->edges = LAYOUT_SAFE_AREA_EDGE_HORIZONTAL;
    EXPECT_EQ(layoutProperty->IsExpandConstraintNeeded(), true);

    layoutProperty->layoutPolicy_->widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_->heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    EXPECT_EQ(layoutProperty->IsExpandConstraintNeeded(), false);
    layoutProperty->ignoreLayoutSafeAreaOpts_->edges = LAYOUT_SAFE_AREA_EDGE_VERTICAL;
    EXPECT_EQ(layoutProperty->IsExpandConstraintNeeded(), true);
}

/**
 * @tc.name: TestMirrorOffset
 * @tc.desc: Test PaddingPropertyT MirrorOffset.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, TestMirrorOffset, TestSize.Level0)
{
    PaddingPropertyF edges = {
        .left = 10.0f,
        .right = 20.0f,
        .top = 30.0f,
        .bottom = 40.0f
    };
    OffsetF expectedRes(-20.0f, 30.0f);
    EXPECT_EQ(edges.MirrorOffset(), expectedRes);
}

/**
 * @tc.name: TestGenIgnoreOpts
 * @tc.desc: Test GenIgnoreOpts.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, TestGenIgnoreOpts, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    IgnoreLayoutSafeAreaOpts expectedRes = {
        .type = NG::LAYOUT_SAFE_AREA_TYPE_NONE,
        .edges = NG::LAYOUT_SAFE_AREA_TYPE_NONE
    };
    EXPECT_EQ(layoutProperty->GenIgnoreOpts(), expectedRes);
    layoutProperty->ignoreLayoutSafeAreaOpts_=std::make_unique<IgnoreLayoutSafeAreaOpts>();
    layoutProperty->ignoreLayoutSafeAreaOpts_->type=LAYOUT_SAFE_AREA_TYPE_SYSTEM;
    layoutProperty->ignoreLayoutSafeAreaOpts_->edges=LAYOUT_SAFE_AREA_EDGE_ALL;
    expectedRes = {
        .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL
    };
    EXPECT_EQ(layoutProperty->GenIgnoreOpts(), expectedRes);
}

/**
 * @tc.name: ExpandConstraintWithSafeAreaTest001
 * @tc.desc: Test ExpandConstraintWithSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, ExpandConstraintWithSafeAreaTest001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto frameNodeHost = FrameNode::CreateFrameNode("host", 1, AceType::MakeRefPtr<Pattern>(), false);
    layoutProperty->SetHost(frameNodeHost);
    layoutProperty->ExpandConstraintWithSafeArea();

    layoutProperty->ignoreLayoutSafeAreaOpts_ = std::make_unique<IgnoreLayoutSafeAreaOpts>();
    layoutProperty->ignoreLayoutSafeAreaOpts_->type = LAYOUT_SAFE_AREA_TYPE_SYSTEM;
    layoutProperty->ignoreLayoutSafeAreaOpts_->edges = LAYOUT_SAFE_AREA_EDGE_ALL;
    layoutProperty->layoutPolicy_->widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutProperty->layoutPolicy_->heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutProperty->ExpandConstraintWithSafeArea();

    frameNodeHost->SetIgnoreLayoutProcess(true);
    frameNodeHost->SetRootMeasureNode(true);
    frameNodeHost->SetEscapeDelayForIgnore(true);
    layoutProperty->ExpandConstraintWithSafeArea();

    auto parent = FrameNode::CreateFrameNode("parent", 0, AceType::MakeRefPtr<Pattern>(), true);
    frameNodeHost->MountToParent(parent);
    layoutProperty->ExpandConstraintWithSafeArea();

    EXPECT_EQ(frameNodeHost->GetIgnoreLayoutProcess(), true);
}

/**
 * @tc.name: TestConvertSafeAreaPadding
 * @tc.desc: Test ConvertWithResidueToPaddingPropertyF
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, TestConvertSafeAreaPadding, TestSize.Level0)
{
    std::unique_ptr<PaddingProperty> safeAreaPadding = std::make_unique<PaddingProperty>();
    *safeAreaPadding = {
        .left = CalcLength(50, DimensionUnit::VP),
        .right = CalcLength(50, DimensionUnit::VP),
        .top = CalcLength(50, DimensionUnit::VP),
        .bottom = CalcLength(50, DimensionUnit::VP)
    };
    ScaleProperty scaleProperty = {
        .vpScale = 3.25,
        .fpScale = 1.0,
        .lpxScale = 1.0
    };
    PaddingPropertyF fract = {
        .left = 0.4f + 0.4f,
        .right = 0.4f + 0.4f,
        .top = 0.4f + 0.4f,
        .bottom = 0.4f + 0.4f
    };
    PaddingPropertyF expectedRes = {
        .left = 163.0f,
        .right = 163.0f,
        .top = 163.0f,
        .bottom = 163.0f
    };
    auto res = ConvertWithResidueToPaddingPropertyF(safeAreaPadding, scaleProperty, fract);
    EXPECT_EQ(res, expectedRes);
}

/**
 * @tc.name: CheckCalcLayoutConstraintTest01
 * @tc.desc: Test CheckCalcLayoutConstraint()
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckCalcLayoutConstraintTest01, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create layoutProperty and update calcConstraint
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->layoutConstraint_ = LayoutConstraintF();
    MeasureProperty userConstraint = {
        .minSize = CalcSize(CalcLength("calc(10%)"), CalcLength("calc(10%)")),
        .maxSize = CalcSize(CalcLength("calc(90%)"), CalcLength("calc(90%)")),
        .selfIdealSize = CalcSize(CalcLength("calc(50%)"), CalcLength("calc(50%)")),
    };
    layoutProperty->UpdateCalcLayoutProperty(userConstraint);
    ASSERT_NE(layoutProperty->calcLayoutConstraint_, nullptr);
    LayoutConstraintF parentConstraint = {
        .scaleProperty = {.vpScale = 1.0, .fpScale = 1.0, .lpxScale = 1.0},
        .percentReference = { 100, 100 }
    };
    layoutProperty->CheckCalcLayoutConstraint(parentConstraint);
    /**
     * @tc.expected: layoutConstraint_ has correct maxSize, minSize and selfIdealSize.
     *               calcLayoutConstraint_ has cache for minSize, maxSize and selfIdealSize
     */
    EXPECT_EQ(layoutProperty->layoutConstraint_->maxSize, SizeF(90, 90))
        << layoutProperty->layoutConstraint_->maxSize.ToString();
    EXPECT_EQ(layoutProperty->layoutConstraint_->minSize, SizeF(10, 10))
        << layoutProperty->layoutConstraint_->minSize.ToString();
    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize, OptionalSizeF(50, 50))
        << layoutProperty->layoutConstraint_->maxSize.ToString();
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->preMaxSize.has_value());
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->preMinSize.has_value());
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->preMinSize,
        CalcSize(CalcLength("calc(10%)"), CalcLength("calc(10%)")))
        << layoutProperty->calcLayoutConstraint_->preMinSize.value().ToString();
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->preMaxSize,
        CalcSize(CalcLength("calc(90%)"), CalcLength("calc(90%)")))
        << layoutProperty->calcLayoutConstraint_->preMaxSize.value().ToString();
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->preSelfIdealSize.has_value());
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->preSelfIdealSize,
        CalcSize(CalcLength("calc(50%)"), CalcLength("calc(50%)")))
        << layoutProperty->calcLayoutConstraint_->preSelfIdealSize.value().ToString();
}

/**
 * @tc.name: CheckCalcLayoutConstraintTest02
 * @tc.desc: Test CheckCalcLayoutConstraint()
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, CheckCalcLayoutConstraintTest02, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create layoutProperty and update calcConstraint
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->layoutConstraint_ = LayoutConstraintF();
    MeasureProperty userConstraint = {
        .minSize = CalcSize(CalcLength("calc(10%)"), CalcLength("calc(10%)")),
        .maxSize = CalcSize(CalcLength("calc(90%)"), CalcLength("calc(90%)")),
        .selfIdealSize = CalcSize(CalcLength("calc(50%)"), CalcLength("calc(50%)")),
    };
    layoutProperty->UpdateCalcLayoutProperty(userConstraint);
    ASSERT_NE(layoutProperty->calcLayoutConstraint_, nullptr);
    LayoutConstraintF parentConstraint = {
        .scaleProperty = {.vpScale = 1.0, .fpScale = 1.0, .lpxScale = 1.0},
        .percentReference = { 100, 100 }
    };
    layoutProperty->CheckCalcLayoutConstraint(parentConstraint);
    /**
     * @tc.steps: step2. layoutProperty update new calcConstraint
     */
    userConstraint = {
        .minSize = CalcSize(CalcLength("calc(20%)"), CalcLength("calc(20%)")),
        .maxSize = CalcSize(CalcLength("calc(80%)"), CalcLength("calc(80%)")),
        .selfIdealSize = CalcSize(CalcLength("calc(40%)"), CalcLength("calc(40%)")),
    };
    layoutProperty->UpdateCalcLayoutProperty(userConstraint);
    layoutProperty->CheckCalcLayoutConstraint(parentConstraint);
    /**
     * @tc.expected: layoutConstraint_ has correct maxSize, minSize and selfIdealSize.
     *               calcLayoutConstraint_ has cache for minSize, maxSize and selfIdealSize
     */
    EXPECT_EQ(layoutProperty->layoutConstraint_->maxSize, SizeF(80, 80))
        << layoutProperty->layoutConstraint_->maxSize.ToString();
    EXPECT_EQ(layoutProperty->layoutConstraint_->minSize, SizeF(20, 20))
        << layoutProperty->layoutConstraint_->minSize.ToString();
    EXPECT_EQ(layoutProperty->layoutConstraint_->selfIdealSize, OptionalSizeF(50, 50))
        << layoutProperty->layoutConstraint_->maxSize.ToString();
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->preMinSize.has_value());
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->preMinSize,
        CalcSize(CalcLength("calc(20%)"), CalcLength("calc(20%)")))
        << layoutProperty->calcLayoutConstraint_->preMinSize.value().ToString();
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->preMaxSize.has_value());
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->preMaxSize,
        CalcSize(CalcLength("calc(80%)"), CalcLength("calc(80%)")))
        << layoutProperty->calcLayoutConstraint_->preMaxSize.value().ToString();
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->preSelfIdealSize.has_value());
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->preSelfIdealSize,
        CalcSize(CalcLength("calc(40%)"), CalcLength("calc(40%)")))
        << layoutProperty->calcLayoutConstraint_->preSelfIdealSize.value().ToString();
}

/**
 * @tc.name: GetAlignPositionWithDirectionTest001
 * @tc.desc: GetAlignPositionWithDirection
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNgTwo, GetAlignPositionWithDirectionTest001, TestSize.Level1)
{
    const SizeF parentSize(100.0f, 100.0f);
    const SizeF childSize(50.0f, 50.0f);
    for (const auto& testCase : OVERLAY_OPTIONS_TEST_CASES) {
        /**
        * @tc.steps: step1. call GetAlignPositionWithDirection function.
        * @tc.expected: step1. offset equals expectedResult.
        */
        auto offset = Alignment::GetAlignPositionWithDirection(parentSize, childSize,
            testCase.align, testCase.direction);
        EXPECT_FLOAT_EQ(offset.GetX(), testCase.expectedResult.GetX());
        EXPECT_FLOAT_EQ(offset.GetY(), testCase.expectedResult.GetY());
    }
}
}