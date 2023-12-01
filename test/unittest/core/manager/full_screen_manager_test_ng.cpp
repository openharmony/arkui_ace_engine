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

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/manager/full_screen/full_screen_manager.h"
#include "core/components_ng/pattern/pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const float MAX_WIDTH = 400.0f;
const float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
const OffsetF FRAME_OFFSET(10.0f, 10.0f);
const std::string ROOT_TAG("root");
const std::string CURRENT_TAG("current");
const std::string PARENT_TAG("parent");
const float ROOT_WIDTH = 1.0f;
const float ROOT_HEIGHT = 1.0f;
} // namespace

class FullScreenManagerTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void FullScreenManagerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void FullScreenManagerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: FullScreenManagerTest001
 * @tc.desc: RequestFullScreen Successfully and then ExitFullScreen Successfully
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FullScreenManagerTestNg, FullScreenManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FullScreenManager
     */
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto fullScreenManager = AceType::MakeRefPtr<FullScreenManager>(root);

    /**
     * @tc.steps: step2. construct a FrameNode needed to be fullScreened
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(CURRENT_TAG, -1, AceType::MakeRefPtr<Pattern>(), false);

    /**
     * @tc.steps: step3. set the parentNode and layout property of the FrameNode constructed on step2
     */
    auto parentNode = AceType::MakeRefPtr<FrameNode>(PARENT_TAG, -1, AceType::MakeRefPtr<Pattern>(), false);
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetMarginFrameOffset(FRAME_OFFSET);
    geometryNode->SetFrameSize(MAX_SIZE);
    CalcSize idealSize = { CalcLength(MAX_WIDTH), CalcLength(MAX_HEIGHT) };
    frameNode->SetGeometryNode(geometryNode);

    /**
     * @tc.steps: step4. call RequestFullScreen function
     */
    CalcSize idealSizeFS = { CalcLength(ROOT_WIDTH), CalcLength(ROOT_HEIGHT) };
    MockPipelineContext::GetCurrent()->SetRootSize(ROOT_WIDTH, ROOT_HEIGHT);
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSizeFS;
    layoutConstraint.maxSize = idealSizeFS;
    frameNode->UpdateLayoutConstraint(layoutConstraint);
    fullScreenManager->RequestFullScreen(frameNode);

    /**
     * @tc.expected: step4. the layout property of the FrameNode match the demand of full screen
     */
    auto selfIdealSizeFullScreen = frameNode->GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize;
    auto maxSizeFullScreen = frameNode->GetLayoutProperty()->GetCalcLayoutConstraint()->maxSize;
    EXPECT_EQ(idealSizeFS, selfIdealSizeFullScreen);
    EXPECT_EQ(idealSizeFS, maxSizeFullScreen);
    auto geometryNodeRequestFS = frameNode->GetGeometryNode();
    auto marginFrameOffsetRequestFS = geometryNodeRequestFS->GetMarginFrameOffset();
    EXPECT_EQ(marginFrameOffsetRequestFS, OffsetF(0, 0));

    /**
     * @tc.expected: step4. the parent node of the FrameNode is the root
     */
    auto parentTag = frameNode->GetParent()->GetTag();
    EXPECT_EQ(parentTag, ROOT_TAG);

    /**
     * @tc.steps: step5. call ExitFullScreen function
     */
    fullScreenManager->ExitFullScreen(frameNode);

    /**
     * @tc.expected: step5. the layout property and the parent node of the FrameNode has recovered
     */
    auto selfIdealSizeExitFullScreen = frameNode->GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize;
    auto geometryNodeExitFS = frameNode->GetGeometryNode();
    auto marginFrameOffsetExitFS = geometryNodeExitFS->GetMarginFrameOffset();
    EXPECT_EQ(marginFrameOffsetExitFS, FRAME_OFFSET);
    parentTag = frameNode->GetParent()->GetTag();
    EXPECT_EQ(parentTag, PARENT_TAG);
}

/**
 * @tc.name: FullScreenManagerTest002
 * @tc.desc: ExitFullScreen without RequestFullScreen
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FullScreenManagerTestNg, FullScreenManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FullScreenManager
     */
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto fullScreenManager = AceType::MakeRefPtr<FullScreenManager>(root);

    /**
     * @tc.steps: step2. construct a FrameNode needed to be fullScreened
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(CURRENT_TAG, -1, AceType::MakeRefPtr<Pattern>(), false);

    /**
     * @tc.steps: step3. set the parentNode and layout property of the FrameNode constructed on step2
     */
    auto parentNode = AceType::MakeRefPtr<FrameNode>(PARENT_TAG, -1, AceType::MakeRefPtr<Pattern>(), false);
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetMarginFrameOffset(FRAME_OFFSET);
    geometryNode->SetFrameSize(MAX_SIZE);
    CalcSize idealSize = { CalcLength(MAX_WIDTH), CalcLength(MAX_HEIGHT) };
    frameNode->SetGeometryNode(geometryNode);

    /**
     * @tc.steps: step4. call the ExitFullScreen function without calling RequestFullScreen function before
     */
    fullScreenManager->ExitFullScreen(frameNode);

    /**
     * @tc.expected: step4. all property of the FrameNode has no changes
     */
    EXPECT_FALSE(frameNode->GetLayoutProperty()->GetCalcLayoutConstraint());
    auto geometryNodeExitFS = frameNode->GetGeometryNode();
    auto marginFrameOffsetExitFS = geometryNodeExitFS->GetMarginFrameOffset();
    EXPECT_EQ(marginFrameOffsetExitFS, FRAME_OFFSET);
    auto parentTag = frameNode->GetParent()->GetTag();
    EXPECT_EQ(parentTag, PARENT_TAG);
}

/**
 * @tc.name: FullScreenManagerTest003
 * @tc.desc: RequestFullScreen twice in a row
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FullScreenManagerTestNg, FullScreenManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FullScreenManager
     */
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto fullScreenManager = AceType::MakeRefPtr<FullScreenManager>(root);

    /**
     * @tc.steps: step2. construct a FrameNode needed to be fullScreened
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(CURRENT_TAG, -1, AceType::MakeRefPtr<Pattern>(), false);

    /**
     * @tc.steps: step3. set the parentNode and layout property of the FrameNode constructed on step2
     */
    auto parentNode = AceType::MakeRefPtr<FrameNode>(PARENT_TAG, -1, AceType::MakeRefPtr<Pattern>(), false);
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetMarginFrameOffset(FRAME_OFFSET);
    geometryNode->SetFrameSize(MAX_SIZE);
    CalcSize idealSize = { CalcLength(MAX_WIDTH), CalcLength(MAX_HEIGHT) };
    frameNode->SetGeometryNode(geometryNode);

    /**
     * @tc.steps: step4. call RequestFullScreen function firstly
     * @tc.expected: step4. the layout property of the FrameNode match the demand of full screen and
     *                      the parent node of the FrameNode is the root
     */
    MockPipelineContext::GetCurrent()->SetRootSize(ROOT_WIDTH, ROOT_HEIGHT);
    CalcSize idealSizeFS = { CalcLength(ROOT_WIDTH), CalcLength(ROOT_HEIGHT) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSizeFS;
    layoutConstraint.maxSize = idealSizeFS;
    frameNode->UpdateLayoutConstraint(layoutConstraint);
    fullScreenManager->RequestFullScreen(frameNode);
    auto selfIdealSizeFullScreen = frameNode->GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize;
    auto maxSizeFullScreen = frameNode->GetLayoutProperty()->GetCalcLayoutConstraint()->maxSize;
    EXPECT_EQ(idealSizeFS, selfIdealSizeFullScreen);
    EXPECT_EQ(idealSizeFS, maxSizeFullScreen);
    auto geometryNodeRequestFS = frameNode->GetGeometryNode();
    auto marginFrameOffsetRequestFS = geometryNodeRequestFS->GetMarginFrameOffset();
    EXPECT_EQ(marginFrameOffsetRequestFS, OffsetF(0, 0));
    auto parentTag = frameNode->GetParent()->GetTag();
    EXPECT_EQ(parentTag, ROOT_TAG);

    /**
     * @tc.steps: step5. set the MarginFrameOffset of the FrameNode not (0, 0) value
     */
    frameNode->GetGeometryNode()->SetMarginFrameOffset(FRAME_OFFSET);

    /**
     * @tc.steps: step6. call RequestFullScreen function again
     * @tc.expected: step6. RequestFullScreen failed, the MarginFrameOffset wouldn't turn to (0, 0)
     */
    fullScreenManager->RequestFullScreen(frameNode);
    marginFrameOffsetRequestFS = geometryNodeRequestFS->GetMarginFrameOffset();
    EXPECT_EQ(marginFrameOffsetRequestFS, FRAME_OFFSET);
}
} // namespace OHOS::Ace::NG
