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

#include "gtest/gtest.h"

#define private public
#include "base/geometry/ng/offset_t.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/components_ng/pattern/data_panel/data_panel_modifer.h"
#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"
#include "core/components_ng/pattern/data_panel/data_panel_pattern.h"
#include "core/components_ng/render/drawing.h"
#include "core/pipeline/base/constants.h"

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
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: DataPanelPaintMethodTest001
 * @tc.desc: Test DataPanel PaintMethod PaintRainbowFilterMask
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintPropertyTest001, TestSize.Level1)
{
    DataPanelModifier dataPanelModifier;
    dataPanelModifier.AttachProperty(AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0));
    RSCanvas rscanvas;
    ArcData arcData;
    arcData.progress = 0.0f;
    dataPanelModifier.PaintRainbowFilterMask(rscanvas, FACTOR, arcData);
    arcData.progress = OVER_FULL;
    dataPanelModifier.PaintRainbowFilterMask(rscanvas, FACTOR, arcData);
    arcData.progress = BELOW_EDGE;
    dataPanelModifier.PaintRainbowFilterMask(rscanvas, FACTOR, arcData);
    arcData.progress = BELOW_ZERO;
    dataPanelModifier.PaintRainbowFilterMask(rscanvas, FACTOR, arcData);
    dataPanelModifier.PaintBackground(rscanvas, OFFSET, TOTAL_WIDTH, HEIGHT);
    dataPanelModifier.PaintTrackBackground(rscanvas, arcData, BACKGROUND_COLOR);
    dataPanelModifier.PaintColorSegment(rscanvas, OFFSET, SEGMENTWIDTH, XSPACE, HEIGHT, START_COLOR, END_COLOR);
    dataPanelModifier.PaintSpace(rscanvas, OFFSET, SPACEWIDTH, XSPACE, HEIGHT);
}

/**
 * @tc.name: DataPanelPaintMethodTest002
 * @tc.desc: Test DataPanel PaintMethod PaintProgress
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPaintMethodTestNg, DataPanelPaintPropertyTest002, TestSize.Level1)
{
    DataPanelModifier dataPanelModifier;
    dataPanelModifier.AttachProperty(AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0));
    RSCanvas rscanvas;
    ArcData arcData;
    arcData.progress = 0.0f;
    dataPanelModifier.PaintProgress(rscanvas, arcData, USE_EFFECT, USE_ANIMATOR, PERCENT);
    arcData.progress = OVER_FULL;
    dataPanelModifier.PaintProgress(rscanvas, arcData, USE_EFFECT, USE_ANIMATOR, PERCENT);
    arcData.progress = BELOW_EDGE;
    dataPanelModifier.PaintProgress(rscanvas, arcData, USE_EFFECT, USE_ANIMATOR, PERCENT);
    arcData.progress = BELOW_ZERO;
    dataPanelModifier.PaintProgress(rscanvas, arcData, USE_EFFECT, USE_ANIMATOR, PERCENT);
    dataPanelModifier.PaintBackground(rscanvas, OFFSET, TOTAL_WIDTH, HEIGHT);
    dataPanelModifier.PaintTrackBackground(rscanvas, arcData, BACKGROUND_COLOR);
    dataPanelModifier.PaintColorSegment(rscanvas, OFFSET, SEGMENTWIDTH, XSPACE, HEIGHT, START_COLOR, END_COLOR);
    dataPanelModifier.PaintSpace(rscanvas, OFFSET, SPACEWIDTH, XSPACE, HEIGHT);
}

} // namespace OHOS::Ace::NG
