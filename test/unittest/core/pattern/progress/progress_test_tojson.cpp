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
#include <cmath>
#include <cstddef>
#include <memory>
#include <optional>
#include <vector>

#include "gtest/gtest.h"

#include "base/memory/referenced.h"
#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/memory/ace_type.h"
#include "core/components/progress/progress_theme.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/progress/progress_layout_algorithm.h"
#include "core/components_ng/pattern/progress/progress_layout_property.h"
#include "core/components_ng/pattern/progress/progress_model_ng.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/components_ng/pattern/progress/progress_theme_wrapper.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/progress_mask_property.h"
#include "core/components_ng/render/render_context.h"
#include "core/components_ng/token_theme/token_theme_storage.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {
namespace {
using namespace testing;
using namespace testing::ext;
constexpr double VALUE_OF_PROGRESS = 100.0;
constexpr double MAX_VALUE_OF_PROGRESS = 100000.0;
constexpr ProgressType PROGRESS_TYPE_LINEAR = ProgressType::LINEAR;
constexpr ProgressType PROGRESS_TYPE_RING = ProgressType::RING;
constexpr ProgressType PROGRESS_TYPE_CAPSULE = ProgressType::CAPSULE;
constexpr int32_t SCALE_COUNT = 120;
constexpr Dimension STROKE_WIDTH = 10.0_vp;
constexpr Dimension SCALE_WIDTH = 10.0_vp;
constexpr Color FRONT_COLOR = Color(0xff0000ff);
constexpr Color BG_COLOR = Color(0xffc0c0c0);
constexpr float PROGRESS_COMPONENT_WIDTH = 200.0f;
constexpr float PROGRESS_COMPONENT_HEIGHT = 200.0f;
constexpr Dimension TEST_PROGRESS_THICKNESS = 4.0_vp;
constexpr Dimension TEST_PROGRESS_STROKE_WIDTH = 10.0_vp;
constexpr Dimension TEST_PROGRESS_DEFAULT_DIAMETER = 72.0_vp;
constexpr Dimension TEST_PROGRESS_SCALE_WIDTH = 2.0_vp;
const Color TEST_COLOR = Color::BLUE;
const LinearColor TEST_LINEARCOLOR = LinearColor(TEST_COLOR);
const std::vector<std::string> FONT_FAMILY = { "serif" };

ProgressModelNG progressModel;
RefPtr<ProgressTheme> progressTheme;
RefPtr<ProgressTheme> progressThemeWrapper;
RefPtr<MockThemeManager> themeManager;
} // namespace

class ProgressTestToJson : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetProgress();
    ProgressModelNG CreateProgress(double value, double max, NG::ProgressType type);

    RefPtr<FrameNode> frameNode_;
    RefPtr<ProgressPattern> pattern_;
    RefPtr<EventHub> eventHub_;
    RefPtr<ProgressLayoutProperty> layoutProperty_;
    RefPtr<ProgressPaintProperty> paintProperty_;
    RefPtr<ProgressAccessibilityProperty> accessibilityProperty_;
};

void ProgressTestToJson::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    testing::FLAGS_gmock_verbose = "error";
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_PROGRESS);
    progressTheme = ProgressTheme::Builder().Build(themeConstants);
    progressTheme = AceType::MakeRefPtr<ProgressTheme>();
    progressTheme->trackThickness_ = TEST_PROGRESS_THICKNESS;
    progressTheme->scaleLength_ = TEST_PROGRESS_STROKE_WIDTH;
    progressTheme->ringDiameter_ = TEST_PROGRESS_DEFAULT_DIAMETER;
    progressTheme->trackBgColor_ = BG_COLOR;
    progressTheme->trackSelectedColor_ = FRONT_COLOR;
    progressTheme->scaleNumber_ = SCALE_COUNT;
    progressTheme->scaleWidth_ = TEST_PROGRESS_SCALE_WIDTH;
    progressThemeWrapper = ProgressThemeWrapper::WrapperBuilder().Build(themeConstants);
    progressThemeWrapper->trackThickness_ = TEST_PROGRESS_THICKNESS;
    progressThemeWrapper->scaleLength_ = TEST_PROGRESS_STROKE_WIDTH;
    progressThemeWrapper->ringDiameter_ = TEST_PROGRESS_DEFAULT_DIAMETER;
    progressThemeWrapper->trackBgColor_ = BG_COLOR;
    progressThemeWrapper->trackSelectedColor_ = FRONT_COLOR;
    progressThemeWrapper->scaleNumber_ = SCALE_COUNT;
    progressThemeWrapper->scaleWidth_ = TEST_PROGRESS_SCALE_WIDTH;
}

void ProgressTestToJson::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    progressTheme = nullptr;
    themeManager = nullptr;
}

void ProgressTestToJson::SetUp()
{
    MockContainer::SetUp();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(progressThemeWrapper));
}

void ProgressTestToJson::TearDown()
{
    RemoveFromStageNode();
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    ClearOldNodes(); // Each testcase will create new node at begin
}

void ProgressTestToJson::GetProgress()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ProgressPattern>();
    eventHub_ = frameNode_->GetEventHub<EventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<ProgressLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ProgressAccessibilityProperty>();
}

ProgressModelNG ProgressTestToJson::CreateProgress(double value, double max, NG::ProgressType type)
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ProgressModelNG model;
    model.Create(0.0, value, 0.0, max, type);
    ViewAbstract::SetWidth(CalcLength(PROGRESS_COMPONENT_WIDTH));
    ViewAbstract::SetHeight(CalcLength(PROGRESS_COMPONENT_HEIGHT));
    GetProgress();
    return model;
}

/**
 * @tc.name: ProgressToJsonEnableSmoothEffect
 * @tc.desc: Test ProgressPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestToJson, ProgressToJsonEnableSmoothEffect, TestSize.Level1)
{
    /**
     * @tc.step: step1. creat instance and set enableSmoothEffect value.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    model.SetStrokeWidth(STROKE_WIDTH);
    model.SetColor(FRONT_COLOR);
    model.SetBackgroundColor(BG_COLOR);
    bool enableSmoothEffect = true;
    model.SetSmoothEffect(enableSmoothEffect);
    CreateDone();

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be true.
     */
    EXPECT_EQ(json->GetString("enableSmoothEffect"), "true");
}

/**
 * @tc.name: ProgressToJsonIsSensitive
 * @tc.desc: Test progresspaintproperty ToJsomValue
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestToJson, ProgressToJsonIsSensitive, TestSize.Level1)
{
    /**
     * @tc.step: step1. creat instance and set isSensitive value.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    model.SetStrokeWidth(STROKE_WIDTH);
    model.SetColor(FRONT_COLOR);
    model.SetBackgroundColor(BG_COLOR);
    CreateDone();

    bool privacySensitive = true;
    paintProperty_->UpdateIsSensitive(privacySensitive);
    EXPECT_EQ(paintProperty_->GetIsSensitive().value(), true);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    EXPECT_NE(json, nullptr);
    paintProperty_->ToJsonValue(json, filter);
    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be 1: true.
     */
    std::string res = std::to_string(paintProperty_->GetIsSensitive().value());
    EXPECT_EQ(json->GetString("isSensitive"), res.c_str());
}

/**
 * @tc.name: ProgressToJsonStyle
 * @tc.desc: Test ProgressPattern ToJsonValue..
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestToJson, ProgressToJsonStyle, TestSize.Level1)
{
    /**
     * @tc.step: step1. creat instance and set style value.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    model.SetStrokeWidth(STROKE_WIDTH);
    model.SetScaleCount(SCALE_COUNT);
    model.SetScaleWidth(SCALE_WIDTH);
    model.SetColor(FRONT_COLOR);
    model.SetBackgroundColor(BG_COLOR);
    CreateDone();
    int defaultVal = 0;
    Dimension defaultScalwith = 0.0_vp;
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("strokeWidth", layoutProperty_->GetStrokeWidthValue().ToString().c_str());
    jsonValue->Put("scaleCount", std::to_string(paintProperty_->GetScaleCountValue(defaultVal)).c_str());
    jsonValue->Put("scaleWidth", paintProperty_->GetScaleWidthValue(defaultScalwith).ToString().c_str());

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be as we set.
     */
    EXPECT_EQ(json->GetString("style"), jsonValue->ToString().c_str());
}

/**
 * @tc.name: ProgressToJsonRingStyleOptions
 * @tc.desc: Test ProgressPattern ToJsonValue..
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestToJson, ProgressToJsonRingStyleOptions, TestSize.Level1)
{
    /**
     * @tc.step: step1. creat instance and set RingStyleOptions value.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);
    model.SetStrokeWidth(STROKE_WIDTH);
    model.SetScaleCount(SCALE_COUNT);
    model.SetScaleWidth(SCALE_WIDTH);
    model.SetColor(FRONT_COLOR);
    model.SetBackgroundColor(BG_COLOR);
    CreateDone();

    Dimension defaultScalwith = 0.0_vp;
    bool enableScanEffect = true;
    bool shadow = true;
    paintProperty_->UpdateEnableRingScanEffect(enableScanEffect);
    paintProperty_->UpdatePaintShadow(shadow);
    paintProperty_->UpdateProgressStatus(ProgressStatus::PROGRESSING);
    paintProperty_->UpdateScaleWidth(defaultScalwith);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be as we set.
     */
    auto ringStyle = json->GetObject("ringStyle");
    EXPECT_EQ(ringStyle->GetString("strokeWidth"), "10.00vp");
    EXPECT_EQ(ringStyle->GetString("enableScanEffect"), "true");
    EXPECT_EQ(ringStyle->GetString("shadow"), "true");
    EXPECT_EQ(ringStyle->GetString("status"), "ProgressStatus.PROGRESSING");
}

/**
 * @tc.name: ProgressToJsonLinearStyleOptions
 * @tc.desc: Test ProgressPattern ToJsonValue..
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestToJson, ProgressToJsonLinearStyleOptions, TestSize.Level1)
{
    /**
     * @tc.step: step1. creat instance and set LinearStyleOptions value.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    model.SetStrokeWidth(STROKE_WIDTH);
    model.SetScaleCount(SCALE_COUNT);
    model.SetScaleWidth(SCALE_WIDTH);
    model.SetColor(FRONT_COLOR);
    model.SetBackgroundColor(BG_COLOR);
    CreateDone();
    bool enableScanEffect = true;
    paintProperty_->UpdateEnableLinearScanEffect(enableScanEffect);
    paintProperty_->UpdateStrokeRadius(STROKE_WIDTH / 2);
    paintProperty_->UpdateProgressStatus(ProgressStatus::PROGRESSING);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    EXPECT_NE(json, nullptr);
    pattern_->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be as we set.
     */
    auto linearStyle = json->GetObject("linearStyle");
    EXPECT_EQ(linearStyle->GetString("strokeWidth"), "10.00vp");
    EXPECT_EQ(linearStyle->GetString("enableScanEffect"), "true");
    EXPECT_EQ(linearStyle->GetString("strokeRadius"), "5.00vp");
}

/**
 * @tc.name: ProgressToJsonCapsuleStyleOptions
 * @tc.desc: Test ProgressPattern ToJsonValue..
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestToJson, ProgressToJsonCapsuleStyleOptions, TestSize.Level1)
{
    /**
     * @tc.step: step1. creat instance and set CapsuleStyleOptions value.
     */
    Dimension defaultSize = 6.66_vp;
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    model.SetColor(FRONT_COLOR);
    model.SetBackgroundColor(BG_COLOR);
    model.SetBorderColor(BG_COLOR);
    model.SetBorderWidth(STROKE_WIDTH);
    std::string text = "hellow world";
    model.SetText(text);
    model.SetShowText(true);
    model.SetFontSize(defaultSize);
    model.SetFontColor(BG_COLOR);
    model.SetItalicFontStyle(Ace::FontStyle::ITALIC);
    model.SetFontWeight(FontWeight::BOLD);
    const std::vector<std::string> fontFamily = { "serif", "scans" };
    model.SetFontFamily(fontFamily);
    CreateDone();
    bool enableScanEffect = true;
    bool shadow = true;
    paintProperty_->UpdateEnableScanEffect(enableScanEffect);
    paintProperty_->UpdatePaintShadow(shadow);
    paintProperty_->UpdateProgressStatus(ProgressStatus::PROGRESSING);
    paintProperty_->UpdateItalicFontStyle(Ace::FontStyle::ITALIC);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be as we set.
     */
    auto capsuleStyle = json->GetObject("capsuleStyle");
    EXPECT_EQ(capsuleStyle->GetString("borderWidth"), "10.00vp");
    EXPECT_EQ(capsuleStyle->GetString("borderRadius"), "100.00px");
    EXPECT_EQ(capsuleStyle->GetString("borderColor"), "#FFC0C0C0");
    EXPECT_EQ(capsuleStyle->GetString("content"), "hellow world");
    EXPECT_EQ(capsuleStyle->GetString("enableScanEffect"), "true");
    EXPECT_EQ(capsuleStyle->GetString("showDefaultPercentage"), "true");
    auto font = capsuleStyle->GetObject("font");
    EXPECT_EQ(font->GetString("size"), "6.66vp");
    EXPECT_EQ(font->GetString("style"), "FontStyle.Italic");
    EXPECT_EQ(font->GetString("weight"), "FontWeight.Bold");
    EXPECT_EQ(font->GetString("family"), "serif,scans");
}
} // namespace OHOS::Ace::NG
