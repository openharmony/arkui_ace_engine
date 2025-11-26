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

#include "layout_property_test_ng.h"

namespace OHOS::Ace::NG {

/**
 * @tc.name: ResetAlignSelf001
 * @tc.desc: Test cast to ResetAlignSelf
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetAlignSelf001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call UpdateFlexBasis without flexItemProperty_.
     */
    layoutProperty->ResetAlignSelf();
    EXPECT_FALSE(layoutProperty->flexItemProperty_);

    /**
     * @tc.steps3 Call UpdateFlexBasis with flexItemProperty_.
     */
    FlexAlign flexAlign = FlexAlign::CENTER;
    layoutProperty->UpdateAlignSelf(flexAlign);
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->ResetAlignSelf();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps4 reset propAlignSelf.
     */
    flexAlign = FlexAlign::CENTER;
    layoutProperty->flexItemProperty_->propAlignSelf.reset();
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->ResetAlignSelf();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: UpdateDisplayIndex001
 * @tc.desc: Test cast to UpdateDisplayIndex
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateDisplayIndex001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call UpdateFlexBasis without flexItemProperty_.
     */
    EXPECT_FALSE(layoutProperty->flexItemProperty_);
    layoutProperty->UpdateDisplayIndex(0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);

    /**
     * @tc.steps3 Call UpdateFlexBasis with flexItemProperty_ again.
     * @tc.expect Update fail
     */
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->UpdateDisplayIndex(0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: SetOverlayOffset001
 * @tc.desc: Test cast to SetOverlayOffset
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, SetOverlayOffset001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->overlayOffsetX_ = Dimension::FromString("1px");
    layoutProperty->overlayOffsetY_ = Dimension::FromString("1px");

    /**
     * @tc.steps2 Call UpdateFlexBasis with overlayOffsetX and overlayOffsetY.
            xChanged = false, yChanged = false.
     */
    auto overlayOffsetX = std::make_optional<Dimension>(Dimension::FromString("1px"));
    auto overlayOffsetY = std::make_optional<Dimension>(Dimension::FromString("1px"));
    layoutProperty->SetOverlayOffset(overlayOffsetX, overlayOffsetY);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps3 Call UpdateFlexBasis with only overlayOffsetY.
            xChanged = false, yChanged = false.
     */
    overlayOffsetX = std::make_optional<Dimension>(Dimension::FromString("1px"));
    overlayOffsetY = std::make_optional<Dimension>(Dimension::FromString("2px"));
    layoutProperty->SetOverlayOffset(overlayOffsetX, overlayOffsetY);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps4 Call UpdateFlexBasis with overlayOffsetX and overlayOffsetY.
        @tc.expect: overlayOffsetX_ == overlayOffsetX and overlayOffsetY_ == overlayOffsetY
     */
    overlayOffsetX = std::make_optional<Dimension>(Dimension::FromString("2px"));
    overlayOffsetY = std::make_optional<Dimension>(Dimension::FromString("3px"));
    layoutProperty->SetOverlayOffset(overlayOffsetX, overlayOffsetY);
    EXPECT_EQ(layoutProperty->overlayOffsetX_, overlayOffsetX.value());
    EXPECT_EQ(layoutProperty->overlayOffsetY_, overlayOffsetY.value());

    /**
     * @tc.steps5 Call UpdateFlexBasis with overlayOffsetX and overlayOffsetY.
        @tc.expect: overlayOffsetX_ == overlayOffsetX and overlayOffsetY_ == overlayOffsetY
     */
    overlayOffsetX = std::nullopt;
    overlayOffsetY = std::nullopt;
    layoutProperty->SetOverlayOffset(overlayOffsetX, overlayOffsetY);
    EXPECT_EQ(layoutProperty->overlayOffsetX_, Dimension::FromString("0.0px"));
    EXPECT_EQ(layoutProperty->overlayOffsetY_, Dimension::FromString("0.0px"));

    /**
     * @tc.steps6 Call UpdateFlexBasis with error scenarios.
        @tc.expect: overlayOffsetX_ == 0 and overlayOffsetY_ == 0
     */
    overlayOffsetX = std::nullopt;
    overlayOffsetY = std::make_optional<Dimension>(Dimension::FromString("3px"));
    layoutProperty->SetOverlayOffset(overlayOffsetX, overlayOffsetY);
    EXPECT_EQ(layoutProperty->overlayOffsetX_, Dimension::FromString("0.0px"));
    EXPECT_EQ(layoutProperty->overlayOffsetY_, Dimension::FromString("0.0px"));
}

/**
 * @tc.name: UpdateAllGeometryTransition001
 * @tc.desc: Test cast to UpdateAllGeometryTransition
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateAllGeometryTransition001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto parent = FrameNode::CreateFrameNode("parentNode", 0, AceType::MakeRefPtr<Pattern>());
    parent->GetLayoutProperty()->UpdateGeometryTransition("parent", true, true);

    auto child = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>());
    child->GetLayoutProperty()->UpdateGeometryTransition("child", false, true);
    child->MountToParent(parent);

    LayoutProperty::UpdateAllGeometryTransition(parent);
    EXPECT_TRUE(child->GetLayoutProperty()->GetGeometryTransition());
}

/**
 * @tc.name: CreateMargin001
 * @tc.desc: Test cast to CreateMargin
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, CreateMargin001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call CreateMargin, push layoutConstraint_ null.
     * @tc.expected: Return margin is nullopt.
     */
    PaddingPropertyF margin = layoutProperty->CreateMargin();
    EXPECT_EQ(margin.top, std::nullopt);
    EXPECT_EQ(margin.bottom, std::nullopt);

    /**
     * @tc.steps3: call CreatePaddingAndBorderWithDefault, push layoutConstraint_is null.
     * @tc.expected: Return paddingPropertyF left == 1.0 + 3.0
     */
    layoutProperty->margin_ = std::make_unique<MarginProperty>();

    /**
     * @tc.steps4: call CreateMargin, push layoutConstraint_ null.
     * @tc.expected: Return margin is 0.
     */
    margin = layoutProperty->CreateMargin();
    EXPECT_FALSE(layoutProperty->layoutConstraint_.has_value());
    EXPECT_EQ(margin.top, std::nullopt);
    EXPECT_EQ(margin.bottom, std::nullopt);
}

/**
 * @tc.name: GetAspectRatio001
 * @tc.desc: Test cast to GetAspectRatio
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, GetAspectRatio001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: set magicItemProperty_ is null.
     */

    /**
     * @tc.steps4: call GetAspectRatio.
     * @tc.expected: Return fTemp is 0.
     */
    float fTemp = layoutProperty->GetAspectRatio();
    EXPECT_EQ(fTemp, 0.0f);
}

/**
 * @tc.name: UpdateAspectRatio001
 * @tc.desc: Test cast to UpdateAspectRatio
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateAspectRatio001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: create magicItemProperty_.
     */
    layoutProperty->magicItemProperty_.propAspectRatio = 1.0f;

    /**
     * @tc.steps3: call UpdateAspectRatio.
     * @tc.expected: Update false and propertyChangeFlag_ is still PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->UpdateAspectRatio(1.0f);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: UpdateAspectRatio002
 * @tc.desc: Test cast to UpdateAspectRatio
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateAspectRatio002, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call UpdateAspectRatio.
     * @tc.expected: Update true and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->UpdateAspectRatio(1.0f);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: ResetAspectRatio001
 * @tc.desc: Test cast to ResetAspectRatio
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetAspectRatio001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->ResetAspectRatio();

    /**
     * @tc.steps2: create magicItemProperty_.
     */

    /**
     * @tc.steps3: call ResetAspectRatio.
     * @tc.expected: Reset success and propertyChangeFlag_ is still PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->ResetAspectRatio();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(layoutProperty->magicItemProperty_.propAspectRatio.has_value());

    /**
     * @tc.steps4: create propAspectRatio.
     */
    layoutProperty->magicItemProperty_.propAspectRatio = 1.0f;

    /**
     * @tc.steps5: call ResetAspectRatio.
     * @tc.expected: Reset success and propertyChangeFlag_ is still PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->ResetAspectRatio();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
    EXPECT_FALSE(layoutProperty->magicItemProperty_.propAspectRatio.has_value());
}

/**
 * @tc.name: UpdateAllGeometryTransition002
 * @tc.desc: Test cast to UpdateAllGeometryTransition
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateAllGeometryTransition002, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Create a weakparent.
     * @tc.expected: GetHost is not null
     */
    RefPtr<FrameNode> parent = FrameNode::CreateFrameNode("parentNode", 0, AceType::MakeRefPtr<Pattern>());
    WeakPtr<FrameNode> weakparent = AceType::WeakClaim(AceType::RawPtr(parent));
    layoutProperty->host_ = weakparent;
    EXPECT_NE(layoutProperty->GetHost(), nullptr);

    /**
     * @tc.steps3 Create a weakGeo.
     * @tc.expected: GetGeometryTransition is not null
     */
    RefPtr<GeometryTransition> geo = AceType::MakeRefPtr<GeometryTransition>("test", true, true);
    WeakPtr<GeometryTransition> weakGeo = AceType::WeakClaim(AceType::RawPtr(geo));
    layoutProperty->geometryTransition_ = weakGeo;
    EXPECT_NE(layoutProperty->GetGeometryTransition(), nullptr);

    /**
     * @tc.steps4 call UpdateGeometryTransition.
     * @tc.expected: geometryTransition_ is Changed to new
     */
    SystemProperties::debugEnabled_ = true;
    layoutProperty->UpdateGeometryTransition("test1", true, true);
    EXPECT_EQ(layoutProperty->geometryTransition_.Upgrade()->id_, "test1");
}

/**
 * @tc.name: UpdateOuterBorderWidth001
 * @tc.desc: Test cast to UpdateOuterBorderWidth
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateOuterBorderWidth001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call UpdateOuterBorderWidth.
     * @tc.expected: Update false and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    BorderWidthProperty borderWidth;
    layoutProperty->UpdateOuterBorderWidth(borderWidth);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps3: create borderWidth_ and call UpdateOuterBorderWidth.
     * @tc.expected: Update true and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->outerBorderWidth_ = std::make_unique<BorderWidthProperty>();
    layoutProperty->outerBorderWidth_->leftDimen = Dimension(1.0f, DimensionUnit::PX);
    borderWidth.leftDimen = Dimension(2.0f, DimensionUnit::FP);
    layoutProperty->UpdateOuterBorderWidth(borderWidth);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(layoutProperty->outerBorderWidth_->leftDimen, Dimension(2.0f, DimensionUnit::FP));
}

/**
 * @tc.name: ClearUserDefinedIdealSize001
 * @tc.desc: Test cast to ClearUserDefinedIdealSize
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ClearUserDefinedIdealSize001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call ClearUserDefinedIdealSize.
     * @tc.expected: Clear false and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->ClearUserDefinedIdealSize(true, true);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps2: create calcLayoutConstraint_ and call ClearUserDefinedIdealSize.
     * @tc.expected: Clear false and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->ClearUserDefinedIdealSize(true, true);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps3: set selfIdealSize.
     * @tc.expected: selfIdealSize has value is true.
     */
    auto width = CalcLength::FromString("10px");
    auto height = CalcLength::FromString("10px");
    CalcSize calcSize(width, height);
    layoutProperty->calcLayoutConstraint_->UpdateSelfIdealSizeWithCheck(calcSize);
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->selfIdealSize.has_value());

    /**
     * @tc.steps4: call ClearUserDefinedIdealSize.
     * @tc.expected: Clear success and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->ClearUserDefinedIdealSize(true, true);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: UpdateMarginSelfIdealSize001
 * @tc.desc: Test cast to UpdateMarginSelfIdealSize
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateMarginSelfIdealSize001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call UpdateMarginSelfIdealSize.
     * @tc.expected: update true and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    SizeF calcSize(1.0f, 2.0f);
    layoutProperty->UpdateMarginSelfIdealSize(calcSize);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps2: create calcLayoutConstraint_ and call ClearUserDefinedIdealSize.
     * @tc.expected: update false and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->layoutConstraint_ = LayoutConstraintF();
    layoutProperty->UpdateMarginSelfIdealSize(calcSize);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps3: set selfIdealSize.
     */
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    OptionalSize<float> opSizeTemp(1.0f, 2.0f);
    layoutProperty->layoutConstraint_->selfIdealSize = opSizeTemp;

    /**
     * @tc.steps4: call UpdateMarginSelfIdealSize.
     * @tc.expected: update success and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->UpdateMarginSelfIdealSize(calcSize);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: ResetCalcMinSize003
 * @tc.desc: Test cast to ResetCalcMinSize
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetCalcMinSize003, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call UpdateMarginSelfIdealSize.
     * @tc.expected: update false and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->ResetCalcMinSize();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps2: create calcLayoutConstraint_ and call ClearUserDefinedIdealSize.
     * @tc.expected: update false and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->ResetCalcMinSize();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps3: set selfIdealSize.
     */
    layoutProperty->calcLayoutConstraint_->minSize = CALC_SIZE;

    /**
     * @tc.steps4: call UpdateMarginSelfIdealSize.
     * @tc.expected: update success and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->ResetCalcMinSize();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: ResetCalcMaxSize003
 * @tc.desc: Test cast to ResetCalcMaxSize
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetCalcMaxSize003, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2: call UpdateMarginSelfIdealSize.
     * @tc.expected: update false and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->ResetCalcMaxSize();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps2: create calcLayoutConstraint_ and call ClearUserDefinedIdealSize.
     * @tc.expected: update false and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->ResetCalcMaxSize();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps3: set selfIdealSize.
     */
    layoutProperty->calcLayoutConstraint_->maxSize = CALC_SIZE;

    /**
     * @tc.steps4: call UpdateMarginSelfIdealSize.
     * @tc.expected: update success and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->ResetCalcMaxSize();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: UpdateFlexGrow002
 * @tc.desc: Test cast to UpdateFlexGrow
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateFlexGrow002, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call ResetFlexGrow without flexItemProperty_.
     */
    layoutProperty->UpdateFlexGrow(1.0);

    /**
     * @tc.steps3 Call ResetFlexGrow with flexItemProperty_.
     */
    layoutProperty->UpdateFlexGrow(1.0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps4 reset propertyChangeFlag_ and call UpdateFlexGrow.
     * @tc.expected: update fail and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->flexItemProperty_->propFlexGrow = 1.0f;
    layoutProperty->UpdateFlexGrow(1.0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps4 call UpdateFlexGrow.
     * @tc.expected: update success and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->UpdateFlexGrow(2.0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(layoutProperty->flexItemProperty_->propFlexGrow, 2.0f);
}

/**
 * @tc.name: ResetFlexGrow002
 * @tc.desc: Test cast to ResetFlexGrow
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetFlexGrow002, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call ResetFlexGrow without flexItemProperty_.
     */
    layoutProperty->ResetFlexGrow();
    EXPECT_FALSE(layoutProperty->flexItemProperty_);

    /**
     * @tc.steps3 Call ResetFlexGrow with flexItemProperty_.
     * @tc.expected: propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->flexItemProperty_ = std::make_unique<FlexItemProperty>();
    layoutProperty->ResetFlexGrow();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps4 set propFlexGrow and call ResetFlexGrow.
     * @tc.expected: propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->flexItemProperty_->propFlexGrow = 2.0f;
    layoutProperty->ResetFlexGrow();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: UpdateFlexShrink001
 * @tc.desc: Test cast to UpdateFlexShrink
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateFlexShrink001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call ResetFlexGrow without flexItemProperty_.
     */
    layoutProperty->UpdateFlexShrink(1.0);

    /**
     * @tc.steps3 Call ResetFlexGrow with flexItemProperty_.
     */
    layoutProperty->UpdateFlexShrink(1.0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps4 reset propertyChangeFlag_ and call UpdateFlexGrow.
     * @tc.expected: update fail and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->flexItemProperty_->propFlexShrink = 1.0f;
    layoutProperty->UpdateFlexShrink(1.0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps4 call UpdateFlexGrow.
     * @tc.expected: update success and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->UpdateFlexShrink(2.0);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(layoutProperty->flexItemProperty_->propFlexShrink, 2.0f);
}

/**
 * @tc.name: ResetFlexShrink002
 * @tc.desc: Test cast to ResetFlexShrink
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ResetFlexShrink002, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call ResetFlexShrink without flexItemProperty_.
     */
    layoutProperty->ResetFlexShrink();
    EXPECT_FALSE(layoutProperty->flexItemProperty_);

    /**
     * @tc.steps3 Call ResetFlexShrink with flexItemProperty_.
     * @tc.expected: propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->flexItemProperty_ = std::make_unique<FlexItemProperty>();
    layoutProperty->ResetFlexShrink();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps3 Set propFlexShrink and Call ResetFlexShrink with flexItemProperty_.
     * @tc.expected: propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->flexItemProperty_->propFlexShrink = 1.0f;
    layoutProperty->ResetFlexShrink();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: UpdateFlexBasis002
 * @tc.desc: Test cast to UpdateFlexBasis
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateFlexBasis002, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call ResetFlexGrow without flexItemProperty_.
     */
    Dimension dim(1.0, DimensionUnit::PX);
    layoutProperty->UpdateFlexBasis(dim);

    /**
     * @tc.steps3 Call ResetFlexGrow with flexItemProperty_.
     */
    layoutProperty->UpdateFlexBasis(dim);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL | PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps4 reset propertyChangeFlag_ and call UpdateFlexGrow.
     * @tc.expected: update fail and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->flexItemProperty_->propFlexBasis = dim;
    layoutProperty->UpdateFlexBasis(dim);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps4 call UpdateFlexGrow.
     * @tc.expected: update success and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    layoutProperty->UpdateFlexBasis(Dimension(2.0, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(layoutProperty->flexItemProperty_->propFlexBasis, Dimension(2.0, DimensionUnit::VP));
}

/**
 * @tc.name: UpdateAlignRules001
 * @tc.desc: Test cast to UpdateAlignRules
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateAlignRules001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call UpdateAlignRules without flexItemProperty_.
     * @tc.expected: update success and propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE.
     */
    std::map<AlignDirection, AlignRule> firstItemAlignRules;
    AlignRule alignRule;
    alignRule.anchor = "test";
    alignRule.horizontal = HorizontalAlign::START;
    firstItemAlignRules[AlignDirection::LEFT] = alignRule;

    layoutProperty->UpdateAlignRules(firstItemAlignRules);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);

    /**
     * @tc.steps2 Call ResetFlexGrow again with flexItemProperty_.
     * @tc.expected: update fail and propertyChangeFlag_ is PROPERTY_UPDATE_NORMAL.
     */
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    layoutProperty->UpdateAlignRules(firstItemAlignRules);
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: GetPercentSensitive001
 * @tc.desc: Test cast to GetPercentSensitive
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, GetPercentSensitive001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call GetPercentSensitive without contentConstraint_.
     */
    std::pair<bool, bool> res = layoutProperty->GetPercentSensitive();
    EXPECT_EQ(res.first, false);
    EXPECT_EQ(res.second, false);

    /**
     * @tc.steps2 ReCall GetPercentSensitive with contentConstraint_ without calcLayoutConstraint_.
     */
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.maxSize = { 1.0, 1.0 };
    layoutProperty->contentConstraint_ = layoutConstraintF;
    res = layoutProperty->GetPercentSensitive();
    EXPECT_EQ(res.first, false);
    EXPECT_EQ(res.second, false);

    /**
     * @tc.steps3 ReCall GetPercentSensitive with contentConstraint_ without calcLayoutConstraint_.
     */
    layoutConstraintF.maxSize = { Infinity<float>() / 2.0f, Infinity<float>() / 2.0f };
    layoutProperty->contentConstraint_ = layoutConstraintF;
    res = layoutProperty->GetPercentSensitive();
    EXPECT_EQ(res.first, false);
    EXPECT_EQ(res.second, false);

    /**
     * @tc.steps4 ReCall GetPercentSensitive with contentConstraint_ with calcLayoutConstraint_.
     */
    CalcLength calcTemp("test1");
    calcTemp.dimension_ = Dimension(2.0f, DimensionUnit::PERCENT);
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    CalcSize cTemp;
    cTemp.width_ = calcTemp;
    cTemp.height_ = calcTemp;
    layoutProperty->calcLayoutConstraint_->selfIdealSize = cTemp;
    res = layoutProperty->GetPercentSensitive();
    EXPECT_EQ(res.first, true);
    EXPECT_EQ(res.second, true);
}

/**
 * @tc.name: UpdatePercentSensitive001
 * @tc.desc: Test cast to UpdatePercentSensitive
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdatePercentSensitive001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps2 Call UpdatePercentSensitive without contentConstraint_.
     */
    std::pair<bool, bool> res = layoutProperty->UpdatePercentSensitive(false, false);
    EXPECT_EQ(res.first, false);
    EXPECT_EQ(res.second, false);

    /**
     * @tc.steps3 ReCall UpdatePercentSensitive with contentConstraint_.
     */
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.maxSize = { 1.0, 1.0 };
    layoutProperty->contentConstraint_ = layoutConstraintF;
    res = layoutProperty->UpdatePercentSensitive(false, false);
    EXPECT_EQ(res.first, false);
    EXPECT_EQ(res.second, false);

    /**
     * @tc.steps4 ReCall UpdatePercentSensitive with contentConstraint_ .
     */
    layoutConstraintF.maxSize = { Infinity<float>() / 2.0f, Infinity<float>() / 2.0f };
    layoutProperty->contentConstraint_ = layoutConstraintF;
    res = layoutProperty->UpdatePercentSensitive(false, false);
    EXPECT_EQ(res.first, false);
    EXPECT_EQ(res.second, false);

    /**
     * @tc.steps5 ReCall UpdatePercentSensitive with contentConstraint_.
     */
    layoutConstraintF.maxSize = { Infinity<float>() / 2.0f, Infinity<float>() / 2.0f };
    layoutProperty->contentConstraint_ = layoutConstraintF;
    res = layoutProperty->UpdatePercentSensitive(true, true);
    EXPECT_EQ(res.first, true);
    EXPECT_EQ(res.second, true);
}

/**
 * @tc.name: ConstraintEqual001
 * @tc.desc: Test cast to ConstraintEqual
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ConstraintEqual001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    LayoutConstraintF preLayoutTemp;
    LayoutConstraintF preContentTemp;

    /**
     * @tc.steps2 Call ConstraintEqual without preLayoutTemp,preLayoutTemp.
     */
    bool bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1065
    EXPECT_FALSE(bResult);

    /**
     * @tc.steps3 Call ConstraintEqual with layoutConstraint_.
     */
    layoutProperty->layoutConstraint_ = preLayoutTemp;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1068
    EXPECT_FALSE(bResult);

    /**
     * @tc.steps4 Call ConstraintEqual with contentConstraint_.
     */
    preLayoutTemp.maxSize.width_ = Infinity<float>() / 2.0f;
    preLayoutTemp.maxSize.height_ = Infinity<float>() / 2.0f;
    layoutProperty->contentConstraint_ = preContentTemp;
    layoutProperty->widthPercentSensitive_ = false;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1073
    EXPECT_TRUE(bResult);

    /**
     * @tc.steps5 Call ConstraintEqual with contentConstraint_ and Width true Height false.
     */
    layoutProperty->widthPercentSensitive_ = true;
    layoutProperty->heightPercentSensitive_ = false;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1078
    EXPECT_TRUE(bResult);

    /**
     * @tc.steps6 Call ConstraintEqual with contentConstraint_and Width true Height true.
     */
    layoutProperty->heightPercentSensitive_ = true;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1080
    EXPECT_FALSE(bResult);
}

/**
 * @tc.name: ConstraintEqual002
 * @tc.desc: Test cast to ConstraintEqual002
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ConstraintEqual002, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    LayoutConstraintF preLayoutTemp;
    LayoutConstraintF preContentTemp;

    /**
     * @tc.steps2 Call ConstraintEqual without preLayoutTemp,preLayoutTemp.
     */
    bool bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1065
    EXPECT_FALSE(bResult);

    /**
     * @tc.steps3 Call ConstraintEqual with layoutConstraint_.
     */
    layoutProperty->layoutConstraint_ = preLayoutTemp;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1068
    EXPECT_FALSE(bResult);

    /**
     * @tc.steps4 Call ConstraintEqual with contentConstraint_.
     */
    preContentTemp.maxSize.width_ = Infinity<float>() / 2.0f;
    preContentTemp.maxSize.height_ = Infinity<float>() / 2.0f;
    layoutProperty->contentConstraint_ = preContentTemp;
    layoutProperty->layoutConstraint_ = preLayoutTemp;
    layoutProperty->widthPercentSensitive_ = false;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1073
    EXPECT_TRUE(bResult);

    /**
     * @tc.steps5 Call ConstraintEqual with contentConstraint_ and Width true Height false.
     */
    layoutProperty->widthPercentSensitive_ = true;
    layoutProperty->heightPercentSensitive_ = false;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1078
    EXPECT_TRUE(bResult);

    /**
     * @tc.steps6 Call ConstraintEqual with contentConstraint_and Width true Height true.
     */
    layoutProperty->heightPercentSensitive_ = true;
    bResult = layoutProperty->ConstraintEqual(preLayoutTemp, preContentTemp); // 1080
    EXPECT_TRUE(bResult);
}

/**
 * @tc.name: UpdateChainWeight001
 * @tc.desc: Test cast to UpdateChainWeight001
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateChainWeight001, TestSize.Level0)
{
    /**
     * @tc.steps1 Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    ChainWeightPair chainWeightPair(0.0f, 0.0f);
    
    /**
     * @tc.steps2 Call UpdateChainWeight with chainWeightPair.
     */
    layoutProperty->UpdateChainWeight(chainWeightPair);
    EXPECT_NE(layoutProperty->flexItemProperty_, nullptr);
}
} // namespace OHOS::Ace::NG