/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <utility>

#include "gtest/gtest.h"

#define private public
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/components_ng/pattern/data_panel/data_panel_modifer.h"
#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"
#include "core/components_ng/pattern/data_panel/data_panel_pattern.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float FACTOR = 1.0f;
constexpr float OVER_FULL = 150.0f;
constexpr float BELOW_EDGE = 10.0f;
constexpr float BELOW_ZERO = -10.0f;
const Color BACKGROUND_COLOR = Color::RED;
const Color START_COLOR = Color::BLUE;
const Color END_COLOR = Color::GREEN;
const OffsetF OFFSET = { 1.0f, 1.0f };
constexpr float HEIGHT = 10.0f;
constexpr float TOTAL_WIDTH = 100.0f;
constexpr float XSPACE = 10.0f;
constexpr float SEGMENTWIDTH = 20.0f;
constexpr float SPACEWIDTH = 5.0f;
constexpr bool USE_EFFECT = false;
constexpr bool USE_ANIMATOR = false;
constexpr float PERCENT = 1.0f;
} // namespace

class DataPanelPaintMethodTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void DataPanelPaintMethodTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void DataPanelPaintMethodTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

class DataPanelTheme : public Theme {
    DECLARE_ACE_TYPE(DataPanelTheme, Theme)
public:
    DataPanelTheme() = default;
    ~DataPanelTheme() override = default;

    Dimension GetThickness() const
    {
        return 20.0_vp;
    }

    std::vector<std::pair<Color, Color>> GetColorsArray() const
    {
        return color;
    }

private:
    std::vector<std::pair<Color, Color>> color;
};

/**
 * @tc.name: DataPanelPaintMethodTest001
 * @tc.desc: Test DataPanel PaintMethod PaintRainbowFilterMask
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintMethodTest001, TestSize.Level1)
{
    DataPanelModifier dataPanelModifier;
    dataPanelModifier.AttachProperty(AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0));
    Testing::MockCanvas rsCanvas;
    ArcData arcData;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    arcData.progress = 0.0f;
    dataPanelModifier.PaintRainbowFilterMask(rsCanvas, FACTOR, arcData);
    arcData.progress = OVER_FULL;
    dataPanelModifier.PaintRainbowFilterMask(rsCanvas, FACTOR, arcData);
    arcData.progress = BELOW_EDGE;
    dataPanelModifier.PaintRainbowFilterMask(rsCanvas, FACTOR, arcData);
    arcData.progress = BELOW_ZERO;
    dataPanelModifier.PaintRainbowFilterMask(rsCanvas, FACTOR, arcData);
}

/**
 * @tc.name: DataPanelPaintMethodTest002
 * @tc.desc: Test DataPanel PaintMethod PaintProgress
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintMethodTest002, TestSize.Level1)
{
    DataPanelModifier dataPanelModifier;
    dataPanelModifier.AttachProperty(AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0));
    Testing::MockCanvas rsCanvas;
    ArcData arcData;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    arcData.progress = 0.0f;
    dataPanelModifier.PaintProgress(rsCanvas, arcData, USE_EFFECT, USE_ANIMATOR, PERCENT);
    arcData.progress = OVER_FULL;
    dataPanelModifier.PaintProgress(rsCanvas, arcData, USE_EFFECT, USE_ANIMATOR, PERCENT);
    arcData.progress = BELOW_EDGE;
    dataPanelModifier.PaintProgress(rsCanvas, arcData, USE_EFFECT, USE_ANIMATOR, PERCENT);
    arcData.progress = BELOW_ZERO;
    dataPanelModifier.PaintProgress(rsCanvas, arcData, USE_EFFECT, USE_ANIMATOR, PERCENT);
}

/**
 * @tc.name: DataPanelPaintMethodTest003
 * @tc.desc: Test DataPanel PaintMethod PaintBackground
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintMethodTest003, TestSize.Level1)
{
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    dataPanelModifier.PaintBackground(rsCanvas, OFFSET, TOTAL_WIDTH, HEIGHT);
}

/**
 * @tc.name: DataPanelPaintMethodTest004
 * @tc.desc: Test DataPanel PaintMethod PaintSpace
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintMethodTest004, TestSize.Level1)
{
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    dataPanelModifier.PaintSpace(rsCanvas, OFFSET, SPACEWIDTH, XSPACE, HEIGHT);
}

/**
 * @tc.name: DataPanelPaintMethodTest005
 * @tc.desc: Test DataPanel PaintMethod PaintColorSegment
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintMethodTest005, TestSize.Level1)
{
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    dataPanelModifier.PaintColorSegment(rsCanvas, OFFSET, SEGMENTWIDTH, XSPACE, HEIGHT, START_COLOR, END_COLOR);
}

/**
 * @tc.name: DataPanelPaintMethodTest006
 * @tc.desc: Test DataPanel PaintMethod PaintTrackBackground
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintMethodTest006, TestSize.Level1)
{
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    ArcData arcData;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    dataPanelModifier.PaintTrackBackground(rsCanvas, arcData, BACKGROUND_COLOR);
}

/**
 * @tc.name: DataPanelPaintMethodTest007
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintMethodTest007, TestSize.Level1)
{
    /**
     * case 1:defaultThickness >= radius
     * radius = -10.0f
     */
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DataPanelTheme>()));
    DrawingContext context { rsCanvas, -10.0f, -10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.PaintCircle(context, OFFSET, 0.0f);
}

/**
 * @tc.name: DataPanelPaintMethodTest08
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintMethodTest008, TestSize.Level1)
{
    /**
     * case 2:defaultThickness < radius
     * radius = 50.0f
     */
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DataPanelTheme>()));
    DrawingContext context { rsCanvas, 50.0f, 50.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.PaintCircle(context, OFFSET, 0.0f);
}

/**
 * @tc.name: DataPanelPaintMethodTest09
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintMethodTest009, TestSize.Level1)
{
    /**
     * case 3:maxValue > 0 and totalvalue < maxvalue
     * max = 100.0f Values = { 1.0f, 2.0f, 3.0f };
     * effect = false  totalvalue > 0
     */
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.SetMax(100.0f);
    dataPanelModifier.SetEffect(false);
    std::vector<double> VALUES = { 1.0f, 2.0f, 3.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintCircle(context, OFFSET, 0.0);
}

/**
 * @tc.name: DataPanelPaintMethodTest10
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintMethodTest010, TestSize.Level1)
{
    /**
     * case 4:maxValue < 0 and totalvalue > maxvalue
     * max = -100.0f Values = { 100.0f, 200.0f, 300.0f };
     * effect = true  totalvalue > 0
     */
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.SetMax(-100.0f);
    dataPanelModifier.SetEffect(true);
    std::vector<double> VALUES = { 100.0f, 200.0f, 300.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintCircle(context, OFFSET, 0.0);
}

/**
 * @tc.name: DataPanelPaintMethodTest11
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintMethodTest011, TestSize.Level1)
{
    /**
     * case 5:effect = true  totalvalue = 0
     * effect = true   values = { -10.0f, 10.0f } totalvalue = 0
     */
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.SetMax(100.0f);
    dataPanelModifier.SetEffect(true);
    std::vector<double> VALUES = { -10.0f, 10.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintCircle(context, OFFSET, 0.0);
}

/**
 * @tc.name: DataPanelPaintMethodTest12
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintMethodTest012, TestSize.Level1)
{
    /**
     * case 6:effect = false  totalvalue = 0
     * effect = false   values = { -10.0f, 10.0f } totalvalue = 0
     */
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.SetMax(100.0f);
    dataPanelModifier.SetEffect(false);
    std::vector<double> VALUES = { -10.0f, 10.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintCircle(context, OFFSET, 0.0);
}

/**
 * @tc.name: DataPanelPaintMethodTest13
 * @tc.desc: Test DataPanel PaintMethod PaintLineProgress
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintMethodTest013, TestSize.Level1)
{
    /**
     * case 1:sum of value = max ,max > 0
     * values ={10.0f,10.0f} max = 20.0f
     */
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.SetMax(20.0f);
    std::vector<double> VALUES = { 10.0f, 10.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintLinearProgress(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintMethodTest14
 * @tc.desc: Test DataPanel PaintMethod PaintLineProgress
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintMethodTest014, TestSize.Level1)
{
    /**
     * case 2:sum of value != max, max < 0
     * values ={-5.0f, 0.0f} max = -20.0f
     */
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.SetMax(-20.0f);
    std::vector<double> VALUES = { -5.0f, 0.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintLinearProgress(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintMethodTest15
 * @tc.desc: Test DataPanel PaintMethod PaintLineProgress
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintMethodTest015, TestSize.Level1)
{
    /**
     * case 3:one of value nearequael 0 and > 0
     * values ={ 0.0001f, 5.0f} max = 20.0f
     */
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.SetMax(20.0f);
    std::vector<double> VALUES = { 0.0001f, 5.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintLinearProgress(context, OFFSET);
}

} // namespace OHOS::Ace::NG
