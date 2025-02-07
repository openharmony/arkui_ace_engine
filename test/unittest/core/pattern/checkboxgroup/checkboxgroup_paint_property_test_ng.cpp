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
#include <optional>
#include <string>
#include <utility>

#include "gtest/gtest.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components/checkable/checkable_component.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkbox/checkbox_model.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_method.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/pipeline/base/render_node.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::string NAME = "checkbox";
const std::string GROUP_NAME = "checkboxGroup";
const std::string GROUP_NAME_CHANGE = "checkboxGroupChange";
const std::string TAG = "CHECKBOX_TAG";
const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
constexpr float BORDER_RADIUS = 100.0;
constexpr float CHECK_STROKE = 200.0;

constexpr float CHECKMARK_PAINTSIZE = 400.0;
constexpr float HOVER_DURATION = 250.0;
constexpr float HOVER_TO_TOUCH_DURATION = 100.0;
constexpr double BORDER_WIDTH = 300.0;
const Color POINT_COLOR = Color::BLUE;
const Color ACTIVE_COLOR = Color::BLACK;
const Color INACTIVE_COLOR = Color::GREEN;
const Color SHADOW_COLOR = Color::RED;
const Color CLICK_EFFECT_COLOR = Color::WHITE;
const Color HOVER_COLOR = Color::GRAY;
const Color INACTIVE_POINT_COLOR = Color::TRANSPARENT;

constexpr Dimension HOVER_RADIUS = Dimension(3.0);
constexpr Dimension HORIZONTAL_PADDING = Dimension(5.0);
constexpr Dimension VERTICAL_PADDING = Dimension(4.0);
constexpr Dimension SHADOW_WIDTH_FORUPDATE = Dimension(6.0);
constexpr Dimension PADDING_SIZE = Dimension(2.0);
} // namespace

class CheckBoxGroupPaintPropertyTestNG : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CheckBoxGroupPaintPropertyTestNG::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
}

void CheckBoxGroupPaintPropertyTestNG::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void CheckBoxGroupPaintPropertyTestNG::SetUp() {}

void CheckBoxGroupPaintPropertyTestNG::TearDown() {}

CheckBoxGroupModifier::Parameters CreateDefModifierParam()
{
    CheckBoxGroupModifier::Parameters parameters = { BORDER_WIDTH, BORDER_RADIUS, CHECK_STROKE, CHECKMARK_PAINTSIZE,
        HOVER_DURATION, HOVER_TO_TOUCH_DURATION, POINT_COLOR, ACTIVE_COLOR, INACTIVE_COLOR, SHADOW_COLOR,
        CLICK_EFFECT_COLOR, HOVER_COLOR, INACTIVE_POINT_COLOR, HOVER_RADIUS, HORIZONTAL_PADDING, VERTICAL_PADDING,
        SHADOW_WIDTH_FORUPDATE, UIStatus::UNSELECTED, PADDING_SIZE, PADDING_SIZE, false,
        CheckBoxGroupPaintProperty::SelectStatus::NONE };

    return parameters;
}

/**
 * @tc.name: CheckBoxGroupPaintPropertyTest001
 * @tc.desc: Verify ToJsonValue of shape.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroup model.
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    /**
     * @tc.steps: step2. Set style to CheckBoxGroup model
     */
    checkBoxGroupModelNG.SetCheckboxGroupStyle(CheckBoxStyle::SQUARE_STYLE);

    /**
     * @tc.steps: step3. Get paint property and get CheckBoxGroup property
     * @tc.expected: The checkboxShape value is empty.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto json = JsonUtil::Create(true);
    paintProperty->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);
    EXPECT_EQ(json->GetString("checkboxShape"), "");
}

/**
 * @tc.name: CheckBoxGroupPaintPropertyTest002
 * @tc.desc: Test ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintPropertyTest002, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Create CheckBoxGroup model.
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    /**
     * @tc.steps: step2. Call SetCheckboxGroupStyle
     */
    checkBoxGroupModelNG.SetCheckboxGroupStyle(CheckBoxStyle::SQUARE_STYLE);

    /**
     * @tc.steps: step3. Create the frame node.
     * @tc.expected: create successfully.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    ASSERT_NE(element, nullptr);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step4. Call Clone, ToJsonValue and Reset.
     * @tc.expected: Check the layoutProperty value.
     */
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto clone = paintProperty->Clone();

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    paintProperty->ToJsonValue(json, filter);
    paintProperty->Reset();
    clone.Reset();
    ASSERT_NE(json, nullptr);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupPaintPropertyTest003
 * @tc.desc: ToJsonValue Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintPropertyTest003, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Init CheckBoxGroup model
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    /**
     * @tc.steps: step2. Set parameters to CheckBoxGroup model
     */
    checkBoxGroupModelNG.SetCheckboxGroupStyle(CheckBoxStyle::CIRCULAR_STYLE);

    /**
     * @tc.steps: step3. Get paint property and get CheckBoxGroup property
     * @tc.expected: Check the CheckBoxGroup property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto json = JsonUtil::Create(true);
    paintProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("checkboxShape"), "0");

    /**
     * @tc.steps: step4. Call UpdateCheckBoxGroupSelectedStyle and ToJsonValue
     * @tc.expected: Check the CheckBoxGroup property value
     */
    paintProperty->UpdateCheckBoxGroupSelectedStyle(CheckBoxStyle::SQUARE_STYLE);
    json = JsonUtil::Create(true);
    paintProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("checkboxShape"), "1");
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupPaintPropertyTest004
 * @tc.desc: ToJsonValue Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintPropertyTest004, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Init CheckBoxGroup model
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    /**
     * @tc.steps: step2. Set parameters to CheckBoxGroup model
     */
    checkBoxGroupModelNG.SetCheckboxGroupStyle(CheckBoxStyle::CIRCULAR_STYLE);

    /**
     * @tc.steps: step3. Get paint property and get CheckBoxGroup property
     * @tc.expected: Check the CheckBoxGroup property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto json = JsonUtil::Create(true);
    paintProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("checkboxShape"), "0");

    /**
     * @tc.steps: step4. Call UpdateCheckBoxGroupSelectedStyle and ToJsonValue
     * @tc.expected: Check the CheckBoxGroup property value
     */
    paintProperty->UpdateCheckBoxGroupSelectedStyle(CheckBoxStyle::SQUARE_STYLE);
    json = JsonUtil::Create(true);
    paintProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("checkboxShape"), "1");
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest005
 * @tc.desc: Verify ToJsonValue of shape.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintMethodTest005, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Init CheckBoxGroup model.
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    /**
     * @tc.steps: step2. Set parameters to CheckBoxGroup model
     */
    checkBoxGroupModelNG.SetCheckboxGroupStyle(CheckBoxStyle::SQUARE_STYLE);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto paintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);
    CheckBoxGroupModifier::Parameters parameters = CreateDefModifierParam();
    auto modifier = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    modifier->uiStatus_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(UIStatus::ON_TO_OFF));
    modifier->enabled_ = AceType::MakeRefPtr<PropertyBool>(false);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(modifier);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);

    /**
     * @tc.steps: step3. Get paint property and get CheckBoxGroup property
     * @tc.expected: Check the CheckBoxGroup property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    paintProperty->UpdateCheckBoxGroupSelectedStyle(CheckBoxStyle::CIRCULAR_STYLE);
    auto json = JsonUtil::Create(true);
    paintProperty->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);
    EXPECT_EQ(json->GetString("checkboxShape"), "0");

    /**
     * @tc.steps: step4. Call UpdateCheckBoxGroupSelectedStyle and ToJsonValue
     * @tc.expected: Check the CheckBoxGroup property value
     */
    paintProperty->UpdateCheckBoxGroupSelectedStyle(CheckBoxStyle::SQUARE_STYLE);
    json = JsonUtil::Create(true);
    paintProperty->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);
    EXPECT_EQ(json->GetString("checkboxShape"), "1");
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest006s
 * @tc.desc: Verify ToJsonValue of shape.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintMethodTest006, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1.  Init CheckBoxGroup model.
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    /**
     * @tc.steps: step2. Set parameters to CheckBoxGroup model
     */
    checkBoxGroupModelNG.SetCheckboxGroupStyle(CheckBoxStyle::CIRCULAR_STYLE);

    /**
     * @tc.steps: step3. Create geometryNode
     * @tc.expected: Create successfully.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto paintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);

    /**
     * @tc.steps: step4. Create CheckBoxGroupModifier
     * @tc.expected: Create successfully.
     */
    CheckBoxGroupModifier::Parameters parameters = CreateDefModifierParam();
    auto modifier = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    ASSERT_NE(modifier, nullptr);
    modifier->uiStatus_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(UIStatus::ON_TO_OFF));
    modifier->enabled_ = AceType::MakeRefPtr<PropertyBool>(false);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(modifier);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);

    /**
     * @tc.steps: step5. Get paint property and get CheckBoxGroup property
     * @tc.expected: Check the CheckBoxGroup property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    paintProperty->UpdateCheckBoxGroupSelectedStyle(CheckBoxStyle::SQUARE_STYLE);
    auto json = JsonUtil::Create(true);
    paintProperty->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);
    EXPECT_EQ(json->GetString("checkboxShape"), "1");

    /**
     * @tc.steps: step6. Call UpdateCheckBoxGroupSelectedStyle and ToJsonValue
     * @tc.expected: Check the CheckBoxGroup property value
     */
    paintProperty->UpdateCheckBoxGroupSelectedStyle(CheckBoxStyle::CIRCULAR_STYLE);
    json = JsonUtil::Create(true);
    paintProperty->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);
    EXPECT_EQ(json->GetString("checkboxShape"), "0");
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest007
 * @tc.desc: Set CheckBox value into CheckBoxGroupPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintMethodTest007, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Init CheckBoxGroup model
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    /**
     * @tc.steps: step2. Get paint property and get CheckBox property
     * @tc.expected: Check the CheckBoxGroup property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->HasCheckBoxGroupSelectedStyle(), false);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest008
 * @tc.desc: Test CheckBoxGroupModifier's DrawTouchAndHoverBoard.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintMethodTest008, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Create geometryNode and some parameters
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto paintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);

    /**
     * @tc.steps: step2. Get paint property and set CheckBoxGroup style
     * @tc.expected: Check the CheckBoxGroup property value
     */
    CheckBoxGroupModifier::Parameters parameters = CreateDefModifierParam();
    auto modifier = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    ASSERT_NE(modifier, nullptr);
    modifier->DrawTouchAndHoverBoard(canvas, CONTENT_SIZE, CONTENT_OFFSET);
    modifier->SetCheckboxGroupStyle(CheckBoxStyle::CIRCULAR_STYLE);
    modifier->enabled_->Set(false);

    /**
     * @tc.steps: step3. Call func DrawTouchAndHoverBoard
     */
    modifier->DrawTouchAndHoverBoard(canvas, CONTENT_SIZE, CONTENT_OFFSET);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest009
 * @tc.desc: Test CheckBoxPaintProperty's Reset.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintMethodTest009, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Init CheckBoxGroup model
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(NAME);

    /**
     * @tc.steps: step2. Set parameters to CheckBoxGroup property
     */
    checkBoxGroupModelNG.SetCheckboxGroupStyle(CheckBoxStyle::CIRCULAR_STYLE);

    /**
     * @tc.steps: step3. Get paint property and get CheckBoxGroup property
     * @tc.expected: Check the CheckBoxGroup property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxGroupPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxGroupPaintProperty, nullptr);
    checkBoxGroupPaintProperty->Reset();
    ASSERT_FALSE(checkBoxGroupPaintProperty->HasCheckBoxGroupSelectedStyle());
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest010
 * @tc.desc: Test CheckBoxGroupModifier's DrawRectOrCircle.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintMethodTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create geometryNode and some parameters
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto paintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateCheckBoxGroupSelectedStyle(CheckBoxStyle::SQUARE_STYLE);
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);

    /**
     * @tc.steps: step2. Get paint property and modifier
     * @tc.expected: Check the CheckBoxGroup property value
     */
    CheckBoxGroupModifier::Parameters parameters = CreateDefModifierParam();
    auto checkBoxGroupModifier = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(checkBoxGroupModifier);
    auto modifier = checkBoxPaintMethod.GetContentModifier(&paintWrapper);
    ASSERT_NE(modifier, nullptr);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);

    /**
     * @tc.steps: step3. Call DrawRectOrCircle
     */
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    RSRoundRect rrect;
    checkBoxGroupModifier->DrawRectOrCircle(canvas, rrect);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest011
 * @tc.desc: Test CheckBoxGroupModifier's DrawRectOrCircle.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintMethodTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create geometryNode and some parameters
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto paintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateCheckBoxGroupSelectedStyle(CheckBoxStyle::CIRCULAR_STYLE);
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);

    /**
     * @tc.steps: step2. Update modifier
     */
    CheckBoxGroupModifier::Parameters parameters = CreateDefModifierParam();
    auto checkBoxGroupModifier = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(checkBoxGroupModifier);
    auto modifier = checkBoxPaintMethod.GetContentModifier(&paintWrapper);
    ASSERT_NE(modifier, nullptr);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);

    /**
     * @tc.steps: step3. Call DrawRectOrCircle
     */
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    RSRoundRect rrect;
    checkBoxGroupModifier->DrawRectOrCircle(canvas, rrect);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest012
 * @tc.desc: Test CheckBoxGroupModifier's DrawRectOrCircle.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintMethodTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create geometryNode and some parameters
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto paintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);

    CheckBoxGroupModifier::Parameters parameters = CreateDefModifierParam();
    auto checkBoxGroupModifier = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(checkBoxGroupModifier);
    auto modifier = checkBoxPaintMethod.GetContentModifier(&paintWrapper);
    ASSERT_NE(modifier, nullptr);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);

    /**
     * @tc.steps: step2. Call DrawRectOrCircle
     */
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    RSRoundRect rrect;
    checkBoxGroupModifier->DrawRectOrCircle(canvas, rrect);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest013
 * @tc.desc: Test CheckBoxGroupModifier's DrawRectOrCircle.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintMethodTest013, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Create geometryNode and some parameters
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto paintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateCheckBoxGroupSelectedStyle(CheckBoxStyle::SQUARE_STYLE);
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);

    /**
     * @tc.steps: step2. Call DrawRectOrCircle
     */
    CheckBoxGroupModifier::Parameters parameters = CreateDefModifierParam();
    auto checkBoxGroupModifier = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(checkBoxGroupModifier);
    auto modifier = checkBoxPaintMethod.GetContentModifier(&paintWrapper);
    ASSERT_NE(modifier, nullptr);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    RSRoundRect rrect;
    checkBoxGroupModifier->DrawRectOrCircle(canvas, rrect);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest014
 * @tc.desc: Test CheckBoxGroupModifier's DrawRectOrCircle.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintMethodTest014, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Create geometryNode and some parameters
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);

    /**
     * @tc.steps: step2. Call DrawRectOrCircle
     */
    CheckBoxGroupModifier::Parameters parameters = CreateDefModifierParam();
    auto checkBoxGroupModifier = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(checkBoxGroupModifier);
    auto modifier = checkBoxPaintMethod.GetContentModifier(&paintWrapper);
    ASSERT_NE(modifier, nullptr);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    RSRoundRect rrect;
    checkBoxGroupModifier->DrawRectOrCircle(canvas, rrect);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest015
 * @tc.desc: Test CheckBoxGroup PaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintMethodTest015, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    /**
     * @tc.steps: step1. Create geometryNode and some parameters
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto paintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateCheckBoxGroupSelectedStyle(CheckBoxStyle::CIRCULAR_STYLE);
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);

    /**
     * @tc.steps: step2. Get paint property
     * @tc.expected: Check the CheckBoxGroup property value
     */
    CheckBoxGroupModifier::Parameters parameters = CreateDefModifierParam();
    auto modifier = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    modifier->DrawTouchAndHoverBoard(canvas, CONTENT_SIZE, CONTENT_OFFSET);
    modifier->SetCheckboxGroupStyle(CheckBoxStyle::CIRCULAR_STYLE);
    modifier->enabled_->Set(false);

    /**
     * @tc.steps: step3s. Call func DrawTouchAndHoverBoard
     */
    modifier->DrawTouchAndHoverBoard(canvas, CONTENT_SIZE, CONTENT_OFFSET);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest016
 * @tc.desc: Test CheckBoxGroup PaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintPropertyTestNG, CheckBoxGroupPaintMethodTest016, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Create geometryNode and some parameters
     * @tc.expected: Check the CheckBoxGroup property value
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto paintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateCheckBoxGroupSelectedStyle(CheckBoxStyle::SQUARE_STYLE);
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);

    /**
     * @tc.steps: step2. Get paint property
     * @tc.expected: Check the CheckBoxGroup property value
     */
    CheckBoxGroupModifier::Parameters parameters = CreateDefModifierParam();
    auto modifier = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    modifier->DrawTouchAndHoverBoard(canvas, CONTENT_SIZE, CONTENT_OFFSET);
    modifier->SetCheckboxGroupStyle(CheckBoxStyle::SQUARE_STYLE);
    modifier->enabled_->Set(false);

    /**
     * @tc.steps: step3. Call func DrawTouchAndHoverBoard
     */
    modifier->DrawTouchAndHoverBoard(canvas, CONTENT_SIZE, CONTENT_OFFSET);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}
} // namespace OHOS::Ace::NG
