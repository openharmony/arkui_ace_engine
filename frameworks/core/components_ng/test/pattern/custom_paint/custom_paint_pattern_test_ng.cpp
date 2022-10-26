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

#include <optional>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_v2/inspector/inspector_constants.h"

#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_event_hub.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_layout_algorithm.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_paint_method.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_pattern.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_view.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_pattern.h"


using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {

const float IDEAL_WIDTH = 300.0f;
const float IDEAL_HEIGHT = 300.0f;

const float MAX_WIDTH = 400.0f;
const float MAX_HEIGHT = 400.0f;

const float MIN_WIDTH = 0.0f;
const float MIN_HEIGHT = 0.0f;

const SizeF IDEAL_SIZE(IDEAL_WIDTH, IDEAL_HEIGHT);
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
const SizeF MIN_SIZE(MIN_WIDTH, MIN_HEIGHT);

} // namespace

class CustomPaintPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: CustomPaintPatternTestNg001
 * @tc.desc: Create the object of CustomPaintPattern and make sure its tag is corrected.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg001, TestSize.Level1)
{
    auto pattern = CustomPaintView::Create();
    EXPECT_FALSE(pattern == nullptr);
    auto customPaintFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(customPaintFrameNode == nullptr);
    EXPECT_EQ(customPaintFrameNode->GetTag(), V2::CANVAS_ETS_TAG);
}

/**
 * @tc.name: CustomPaintPatternTestNg002
 * @tc.desc: Test onReady event.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg002, TestSize.Level1)
{
    auto pattern = CustomPaintView::Create();
    EXPECT_FALSE(pattern == nullptr);
    bool flagEventCbk = false;
    CustomPaintView::SetOnReady([&flagEventCbk] () { flagEventCbk = true; });
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_FALSE(frameNode == nullptr);
    auto eventHub = frameNode->GetEventHub<CustomPaintEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    eventHub->FireReadyEvent();
    EXPECT_TRUE(flagEventCbk);
}

/**
 * @tc.name: CustomPaintPatternTestNg003
 * @tc.desc: Create the object of CustomPaintPattern.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg003, TestSize.Level1)
{
    auto pattern = CustomPaintView::Create();
    EXPECT_FALSE(pattern == nullptr);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    EXPECT_FALSE(layoutProperty == nullptr);

    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    auto canvasSize = layoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(canvasSize.value_or(SizeF(0.0f, 0.0f)), MAX_SIZE);

    layoutConstraint.selfIdealSize.SetSize(IDEAL_SIZE);
    canvasSize = layoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(canvasSize.value_or(SizeF(0.0f, 0.0f)), IDEAL_SIZE);
}

} // namespace OHOS::Ace::NG