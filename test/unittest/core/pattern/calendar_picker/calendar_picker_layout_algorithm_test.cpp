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
#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/theme/icon_theme.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/button/button_theme.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_layout_algorithm.h"
#include "core/components_ng/pattern/calendar/calendar_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const SizeF CONTAINER_SIZE(720.0f, 1136.f);
const SizeF PARENT_IDEAL_SIZE(720.0f, 1136.f);
const SizeF SELF_IDEAL_SIZE(600.0f, 1000.f);
const Dimension ENTRY_BUTTON_WIDTH = Dimension(100.0, DimensionUnit::PX);
const CalcSize CONSTRAINT_SIZE = { CalcLength(300.0), CalcLength(300.0) };
const SizeF CONSTRAINT_MAX_SIZE(300.0f, 300.f);
const CalcSize CONSTRAINT_SELF_SIZE = { CalcLength(400.0), CalcLength(400.0) };
} // namespace

class CalendarPickerLayoutAlgorithmTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    RefPtr<Theme> GetThemeByType(ThemeType type);
    void CreateCalendarPicker();
    void GetCalendarPickerLayoutAlgorithm();
    void CreateContentChildNode();
    void CreateButtonChildNode();

    RefPtr<IconTheme> iconThem_;
    RefPtr<DialogTheme> dialogTheme_;
    RefPtr<PickerTheme> pickerThem_;
    RefPtr<ButtonTheme> buttonTheme_;
    RefPtr<CalendarTheme> calendarTheme_;

    RefPtr<FrameNode> frameNode_;
    RefPtr<LayoutWrapperNode> layoutWrapper_;
    RefPtr<CalendarPickerLayoutAlgorithm> calendarPickerLayoutAlgorithm_;
};

void CalendarPickerLayoutAlgorithmTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void CalendarPickerLayoutAlgorithmTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void CalendarPickerLayoutAlgorithmTest::SetUp()
{
    iconThem_ = AceType::MakeRefPtr<IconTheme>();
    dialogTheme_ = AceType::MakeRefPtr<DialogTheme>();
    pickerThem_ = MockThemeDefault::GetPickerTheme();
    buttonTheme_ = AceType::MakeRefPtr<ButtonTheme>();
    calendarTheme_ = AceType::MakeRefPtr<CalendarTheme>();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([this](ThemeType type) -> RefPtr<Theme> {return GetThemeByType(type);});

    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([this](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> {return GetThemeByType(type);});
}

void CalendarPickerLayoutAlgorithmTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<Theme> CalendarPickerLayoutAlgorithmTest::GetThemeByType(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return iconThem_;
    } else if (type == DialogTheme::TypeId()) {
        return dialogTheme_;
    } else if (type == PickerTheme::TypeId()) {
        return pickerThem_;
    } else if (type == ButtonTheme::TypeId()) {
        return buttonTheme_;
    } else if (type == CalendarTheme::TypeId()) {
        return calendarTheme_;
    } else {
        return nullptr;
    }
}

void CalendarPickerLayoutAlgorithmTest::CreateCalendarPicker()
{
    CalendarSettingData settingData;
    CalendarPickerModelNG calendarPickerModel;
    calendarPickerModel.Create(settingData);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode_, nullptr);
}

void CalendarPickerLayoutAlgorithmTest::CreateContentChildNode()
{
    auto contentFrameNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(contentFrameNode, nullptr);
    auto contentLayoutProperty = contentFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    RefPtr<GeometryNode> contentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> contentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        contentFrameNode, contentFrameNodeGeometryNode, contentFrameNode->GetLayoutProperty());
    ASSERT_NE(contentNodeLayoutWrapper, nullptr);
    layoutWrapper_->AppendChild(contentNodeLayoutWrapper);

    auto yearNode = AceType::DynamicCast<FrameNode>(contentFrameNode->GetOrCreateChildByIndex(0));
    auto yearContentLayoutProperty = yearNode->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<GeometryNode> yearContentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> yearContentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        yearNode, yearContentFrameNodeGeometryNode, yearNode->GetLayoutProperty());
    ASSERT_NE(yearContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(yearContentNodeLayoutWrapper);

    auto textNode1 = AceType::DynamicCast<FrameNode>(contentFrameNode->GetOrCreateChildByIndex(1));
    auto text1ContentLayoutProperty = textNode1->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<GeometryNode> text1ContentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> text1ContentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        textNode1, text1ContentFrameNodeGeometryNode, textNode1->GetLayoutProperty());
    ASSERT_NE(text1ContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(text1ContentNodeLayoutWrapper);

    auto monthNode = AceType::DynamicCast<FrameNode>(contentFrameNode->GetOrCreateChildByIndex(2));
    auto monthContentLayoutProperty = monthNode->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<GeometryNode> monthContentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> monthContentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        monthNode, monthContentFrameNodeGeometryNode, monthNode->GetLayoutProperty());
    ASSERT_NE(monthContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(monthContentNodeLayoutWrapper);

    auto textNode2 = AceType::DynamicCast<FrameNode>(contentFrameNode->GetOrCreateChildByIndex(3));
    auto text2ContentLayoutProperty = textNode2->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<GeometryNode> text2ContentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> text2ContentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        textNode2, text2ContentFrameNodeGeometryNode, textNode2->GetLayoutProperty());
    ASSERT_NE(text2ContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(text2ContentNodeLayoutWrapper);

    auto dayNode = AceType::DynamicCast<FrameNode>(contentFrameNode->GetOrCreateChildByIndex(4));
    auto dayContentLayoutProperty = dayNode->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<GeometryNode> dayContentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> dayContentNodeLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dayNode, dayContentFrameNodeGeometryNode, dayNode->GetLayoutProperty());
    ASSERT_NE(dayContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(dayContentNodeLayoutWrapper);
}

void CalendarPickerLayoutAlgorithmTest::CreateButtonChildNode()
{
    auto flexFrameNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(1));
    ASSERT_NE(flexFrameNode, nullptr);
    auto flexLayoutProperty = flexFrameNode->GetLayoutProperty<FlexLayoutProperty>();
    RefPtr<GeometryNode> flexFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> flexNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        flexFrameNode, flexFrameNodeGeometryNode, flexFrameNode->GetLayoutProperty());
    ASSERT_NE(flexNodeLayoutWrapper, nullptr);
    layoutWrapper_->AppendChild(flexNodeLayoutWrapper);

    auto buttonNode1 = AceType::DynamicCast<FrameNode>(flexFrameNode->GetOrCreateChildByIndex(0));
    auto button1LayoutProperty = buttonNode1->GetLayoutProperty<ButtonLayoutProperty>();
    RefPtr<GeometryNode> button1NodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> button1NodeLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(buttonNode1, button1NodeGeometryNode, buttonNode1->GetLayoutProperty());
    ASSERT_NE(button1NodeLayoutWrapper, nullptr);
    flexNodeLayoutWrapper->AppendChild(button1NodeLayoutWrapper);

    auto buttonNode2 = AceType::DynamicCast<FrameNode>(flexFrameNode->GetOrCreateChildByIndex(1));
    auto button2LayoutProperty = buttonNode2->GetLayoutProperty<ButtonLayoutProperty>();
    RefPtr<GeometryNode> button2NodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> button2NodeLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(buttonNode2, button2NodeGeometryNode, buttonNode2->GetLayoutProperty());
    ASSERT_NE(button2NodeLayoutWrapper, nullptr);
    flexNodeLayoutWrapper->AppendChild(button2NodeLayoutWrapper);

    auto imageNode1 = AceType::DynamicCast<FrameNode>(buttonNode1->GetOrCreateChildByIndex(0));
    auto image1LayoutProperty = imageNode1->GetLayoutProperty<ImageLayoutProperty>();
    RefPtr<GeometryNode> image1NodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> image1NodeLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageNode1, image1NodeGeometryNode, imageNode1->GetLayoutProperty());
    ASSERT_NE(image1NodeLayoutWrapper, nullptr);
    layoutWrapper_->AppendChild(image1NodeLayoutWrapper);

    auto imageNode2 = AceType::DynamicCast<FrameNode>(buttonNode2->GetOrCreateChildByIndex(0));
    auto image2LayoutProperty = imageNode2->GetLayoutProperty<ImageLayoutProperty>();
    RefPtr<GeometryNode> image2NodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> image2NodeLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageNode2, image2NodeGeometryNode, imageNode2->GetLayoutProperty());
    ASSERT_NE(image2NodeLayoutWrapper, nullptr);
    layoutWrapper_->AppendChild(image2NodeLayoutWrapper);
}

void CalendarPickerLayoutAlgorithmTest::GetCalendarPickerLayoutAlgorithm()
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    layoutWrapper_ = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper_, nullptr);
    auto calendarPickerPattern = AceType::DynamicCast<CalendarPickerPattern>(frameNode_->GetPattern());
    ASSERT_NE(calendarPickerPattern, nullptr);
    auto layoutAlgorithm = calendarPickerPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper_->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    CreateContentChildNode();
    CreateButtonChildNode();

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper_->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    calendarPickerLayoutAlgorithm_ =
        AceType::DynamicCast<CalendarPickerLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(calendarPickerLayoutAlgorithm_, nullptr);
}

/**
 * @tc.name: CalendarPickerContentMeasure001
 * @tc.desc: Test CalendarPickerContentMeasure when widthLayoutPolicy_ and heightLayoutPolicy_ are not match parent.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerLayoutAlgorithmTest, CalendarPickerContentMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CalendarPicker.
     */
    CreateCalendarPicker();
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step2. Get CalendarPicker layout algorithm.
     */
    GetCalendarPickerLayoutAlgorithm();
    ASSERT_NE(calendarPickerLayoutAlgorithm_, nullptr);

    /**
     * @tc.steps: step3. Set widthLayoutPolicy_ and heightLayoutPolicy_ to LayoutCalPolicy::NO_MATCH.
     */
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;

    /**
     * @tc.steps: step4. set layout constraint to a valid value.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SELF_IDEAL_SIZE);
    parentLayoutConstraint.parentIdealSize.SetSize(PARENT_IDEAL_SIZE);
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutProperty->UpdateContentConstraint();

    /**
     * @tc.steps: step4. Call CalendarPickerContentMeasure function.
     * @tc.expected: The value of frameSize will be changed to SELF_IDEAL_SIZE.
     */
    calendarPickerLayoutAlgorithm_->CalendarPickerContentMeasure(AceType::RawPtr(layoutWrapper_));
    auto contentWrapper = layoutWrapper_->GetOrCreateChildByIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto contentGeometryNode = contentWrapper->GetGeometryNode();
    ASSERT_NE(contentGeometryNode, nullptr);

    SizeF geometryFrameSize = contentGeometryNode->GetFrameSize();
    EXPECT_EQ(geometryFrameSize, SELF_IDEAL_SIZE);
}

/**
 * @tc.name: CalendarPickerContentMeasure002
 * @tc.desc: Test CalendarPickerContentMeasure when widthLayoutPolicy_ and heightLayoutPolicy_ are match parent.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerLayoutAlgorithmTest, CalendarPickerContentMeasure002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CalendarPicker.
     */
    CreateCalendarPicker();
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step2. Get CalendarPicker layout algorithm.
     */
    GetCalendarPickerLayoutAlgorithm();
    ASSERT_NE(calendarPickerLayoutAlgorithm_, nullptr);

    /**
     * @tc.steps: step3. Set widthLayoutPolicy_ and heightLayoutPolicy_ to LayoutCalPolicy::MATCH_PARENT.
     */
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;

    /**
     * @tc.steps: step4. set layout constraint to a valid value.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONSTRAINT_MAX_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SELF_IDEAL_SIZE);
    parentLayoutConstraint.parentIdealSize.SetSize(PARENT_IDEAL_SIZE);
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutProperty->UpdateContentConstraint();

    /**
     * @tc.steps: step4. Call CalendarPickerContentMeasure function.
     * @tc.expected: The value of frameSize will be changed to PARENT_IDEAL_SIZE.
     */
    calendarPickerLayoutAlgorithm_->CalendarPickerContentMeasure(AceType::RawPtr(layoutWrapper_));
    auto contentWrapper = layoutWrapper_->GetOrCreateChildByIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto contentGeometryNode = contentWrapper->GetGeometryNode();
    ASSERT_NE(contentGeometryNode, nullptr);

    SizeF geometryFrameSize = contentGeometryNode->GetFrameSize();
    EXPECT_EQ(geometryFrameSize, PARENT_IDEAL_SIZE);
}

/**
 * @tc.name: SelfMeasure001
 * @tc.desc: Test SelfMeasure Function.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerLayoutAlgorithmTest, SelfMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CalendarPicker.
     */
    CreateCalendarPicker();
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step2. Get CalendarPicker layout algorithm.
     */
    GetCalendarPickerLayoutAlgorithm();
    ASSERT_NE(calendarPickerLayoutAlgorithm_, nullptr);

    /**
     * @tc.steps: step3. Set entryButtonWidth_ and contentMeasure_.
     */
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);

    theme->entryButtonWidth_ = ENTRY_BUTTON_WIDTH;
    calendarPickerLayoutAlgorithm_->contentMeasure_ = CONTAINER_SIZE;

    /**
     * @tc.steps: step4. Call SelfMeasure function.
     */
    calendarPickerLayoutAlgorithm_->SelfMeasure(AceType::RawPtr(layoutWrapper_));
    EXPECT_EQ(calendarPickerLayoutAlgorithm_->flexMeasure_.Width(), ENTRY_BUTTON_WIDTH.Value());
    EXPECT_EQ(calendarPickerLayoutAlgorithm_->flexMeasure_.Height(), CONTAINER_SIZE.Height());
}

/**
 * @tc.name: CalendarPickerContentMeasure003
 * @tc.desc: Test CalendarPickerContentMeasure when widthLayoutPolicy_ and heightLayoutPolicy_ are wrapContent.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerLayoutAlgorithmTest, CalendarPickerContentMeasure003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CalendarPicker.
     */
    CreateCalendarPicker();
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step2. Get CalendarPicker layout algorithm.
     */
    GetCalendarPickerLayoutAlgorithm();
    ASSERT_NE(calendarPickerLayoutAlgorithm_, nullptr);

    /**
     * @tc.steps: step3. Set widthLayoutPolicy_ and heightLayoutPolicy_ to LayoutCalPolicy::WRAP_CONTENT.
     */
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;

    /**
     * @tc.steps: step4. set layout constraint to a valid value.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONSTRAINT_MAX_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SELF_IDEAL_SIZE);
    parentLayoutConstraint.parentIdealSize.SetSize(PARENT_IDEAL_SIZE);
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutProperty->UpdateContentConstraint();

    /**
     * @tc.steps: step4. Call CalendarPickerContentMeasure function.
     * @tc.expected: The value of frameSize will be changed to CONSTRAINT_MAX_SIZE.
     */
    calendarPickerLayoutAlgorithm_->CalendarPickerContentMeasure(AceType::RawPtr(layoutWrapper_));
    auto contentWrapper = layoutWrapper_->GetOrCreateChildByIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto contentGeometryNode = contentWrapper->GetGeometryNode();
    ASSERT_NE(contentGeometryNode, nullptr);

    SizeF geometryFrameSize = contentGeometryNode->GetFrameSize();
    EXPECT_EQ(geometryFrameSize, CONSTRAINT_MAX_SIZE);
}

/**
 * @tc.name: CalendarPickerContentMeasure004
 * @tc.desc: Test CalendarPickerContentMeasure when widthLayoutPolicy_ and heightLayoutPolicy_ are fixAtIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerLayoutAlgorithmTest, CalendarPickerContentMeasure004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CalendarPicker.
     */
    CreateCalendarPicker();
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step2. Get CalendarPicker layout algorithm.
     */
    GetCalendarPickerLayoutAlgorithm();
    ASSERT_NE(calendarPickerLayoutAlgorithm_, nullptr);

    /**
     * @tc.steps: step3. Set widthLayoutPolicy_ and heightLayoutPolicy_ to LayoutCalPolicy::FIX_AT_IDEAL_SIZE.
     */
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;

    /**
     * @tc.steps: step4. set layout constraint to a valid value.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONSTRAINT_MAX_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SELF_IDEAL_SIZE);
    parentLayoutConstraint.parentIdealSize.SetSize(PARENT_IDEAL_SIZE);
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutProperty->UpdateContentConstraint();

    MeasureProperty constraint;
    constraint.selfIdealSize = CONSTRAINT_SELF_SIZE;
    constraint.maxSize = CONSTRAINT_SIZE;
    layoutProperty->UpdateCalcLayoutProperty(constraint);

    /**
     * @tc.steps: step4. Call CalendarPickerContentMeasure function.
     * @tc.expected: The value of frameSize will be changed to CONSTRAINT_MAX_SIZE.
     */
    calendarPickerLayoutAlgorithm_->CalendarPickerContentMeasure(AceType::RawPtr(layoutWrapper_));
    auto contentWrapper = layoutWrapper_->GetOrCreateChildByIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto contentGeometryNode = contentWrapper->GetGeometryNode();
    ASSERT_NE(contentGeometryNode, nullptr);

    SizeF geometryFrameSize = contentGeometryNode->GetFrameSize();
    EXPECT_EQ(geometryFrameSize, CONSTRAINT_MAX_SIZE);
}

/**
 * @tc.name: CalendarPickerContentMeasure005
 * @tc.desc: Test CalendarPickerContentMeasure when widthLayoutPolicy_ and heightLayoutPolicy_ are wrapContent.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerLayoutAlgorithmTest, CalendarPickerContentMeasure005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CalendarPicker.
     */
    CreateCalendarPicker();
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step2. Get CalendarPicker layout algorithm.
     */
    GetCalendarPickerLayoutAlgorithm();
    ASSERT_NE(calendarPickerLayoutAlgorithm_, nullptr);

    /**
     * @tc.steps: step3. Set widthLayoutPolicy_ and heightLayoutPolicy_ to LayoutCalPolicy::WRAP_CONTENT.
     */
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;

    /**
     * @tc.steps: step4. set layout constraint to a valid value.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONSTRAINT_MAX_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SELF_IDEAL_SIZE);
    parentLayoutConstraint.parentIdealSize.SetSize(PARENT_IDEAL_SIZE);
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    if (!layoutProperty->calcLayoutConstraint_) {
        layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    }
    layoutProperty->calcLayoutConstraint_->maxSize = CONSTRAINT_SIZE;
    layoutProperty->UpdateContentConstraint();

    /**
     * @tc.steps: step4. Call CalendarPickerContentMeasure function.
     * @tc.expected: The value of frameSize will be changed to CONSTRAINT_MAX_SIZE.
     */
    calendarPickerLayoutAlgorithm_->CalendarPickerContentMeasure(AceType::RawPtr(layoutWrapper_));
    auto contentWrapper = layoutWrapper_->GetOrCreateChildByIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto contentGeometryNode = contentWrapper->GetGeometryNode();
    ASSERT_NE(contentGeometryNode, nullptr);

    SizeF geometryFrameSize = contentGeometryNode->GetFrameSize();
    EXPECT_EQ(geometryFrameSize, CONSTRAINT_MAX_SIZE);
}

/**
 * @tc.name: CalendarPickerMeasure001
 * @tc.desc: Test BeforeCreateLayoutWrapper when widthLayoutPolicy_ and heightLayoutPolicy_ are matchParent.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerLayoutAlgorithmTest, CalendarPickerMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CalendarPicker.
     */
    CreateCalendarPicker();
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step2. Get CalendarPicker layout algorithm.
     */
    GetCalendarPickerLayoutAlgorithm();
    ASSERT_NE(calendarPickerLayoutAlgorithm_, nullptr);

    /**
     * @tc.steps: step3. Set widthLayoutPolicy_ and heightLayoutPolicy_ to LayoutCalPolicy::MATCH_PARENT.
     */
    auto layoutProperty = layoutWrapper_->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;

    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->selfIdealSize.has_value());
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->selfIdealSize->Height().has_value());

    /**
     * @tc.steps: step4. Call BeforeCreateLayoutWrapper.
     * @tc.expected: Clear Height success.
     */
    auto calendarPickerPattern = AceType::DynamicCast<CalendarPickerPattern>(frameNode_->GetPattern());
    ASSERT_NE(calendarPickerPattern, nullptr);
    calendarPickerPattern->BeforeCreateLayoutWrapper();
    EXPECT_FALSE(layoutProperty->calcLayoutConstraint_->selfIdealSize->Height().has_value());
}

} // namespace OHOS::Ace::NG
