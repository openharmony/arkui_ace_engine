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
#include "frameworks/core/components_ng/manager/full_screen/full_screen_manager.h"
#include "frameworks/core/components_ng/pattern/pattern.h"

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
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

protected:
};

/**
 * @tc.name: FullScreenManagerTest001
 * @tc.desc: RequestFullScreen Successfully and then ExitFullScreen Successfully
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FullScreenManagerTestNg, FullScreenManagerTest001, TestSize.Level1)
{
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto fullScreenManager = AceType::MakeRefPtr<FullScreenManager>(root);

    auto frameNode = AceType::MakeRefPtr<FrameNode>(CURRENT_TAG, -1, AceType::MakeRefPtr<Pattern>(), false);
    auto parentNode = AceType::MakeRefPtr<FrameNode>(PARENT_TAG, -1, AceType::MakeRefPtr<Pattern>(), false);
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetMarginFrameOffset(FRAME_OFFSET);
    geometryNode->SetFrameSize(MAX_SIZE);
    CalcSize idealSize = { CalcLength(MAX_WIDTH), CalcLength(MAX_HEIGHT) };
    frameNode->SetGeometryNode(geometryNode);

    fullScreenManager->RequestFullScreen(frameNode);
    // RequestFullScreen Successfully
    // Check size and offset
    auto selfIdealSizeFullScreen = frameNode->GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize;
    auto maxSizeFullScreen = frameNode->GetLayoutProperty()->GetCalcLayoutConstraint()->maxSize;
    CalcSize idealSizeFS = { CalcLength(ROOT_WIDTH), CalcLength(ROOT_HEIGHT) };
    EXPECT_EQ(idealSizeFS, selfIdealSizeFullScreen);
    EXPECT_EQ(idealSizeFS, maxSizeFullScreen);
    auto geometryNodeRequestFS = frameNode->GetGeometryNode();
    auto marginFrameOffsetRequestFS = geometryNodeRequestFS->GetMarginFrameOffset();
    EXPECT_EQ(marginFrameOffsetRequestFS, OffsetF(0, 0));
    // Check frameNode's parent is root
    auto parentTag = frameNode->GetParent()->GetTag();
    EXPECT_EQ(parentTag, ROOT_TAG);

    fullScreenManager->ExitFullScreen(frameNode);
    // RequestFullScreen Successfully
    // Check size and offset
    auto selfIdealSizeExitFullScreen = frameNode->GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_EQ(idealSize, selfIdealSizeExitFullScreen);
    auto geometryNodeExitFS = frameNode->GetGeometryNode();
    auto marginFrameOffsetExitFS = geometryNodeExitFS->GetMarginFrameOffset();
    EXPECT_EQ(marginFrameOffsetExitFS, FRAME_OFFSET);
    // Check frameNode's parent has recovered
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
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto fullScreenManager = AceType::MakeRefPtr<FullScreenManager>(root);

    auto frameNode = AceType::MakeRefPtr<FrameNode>(CURRENT_TAG, -1, AceType::MakeRefPtr<Pattern>(), false);
    auto parentNode = AceType::MakeRefPtr<FrameNode>(PARENT_TAG, -1, AceType::MakeRefPtr<Pattern>(), false);
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetMarginFrameOffset(FRAME_OFFSET);
    geometryNode->SetFrameSize(MAX_SIZE);
    CalcSize idealSize = { CalcLength(MAX_WIDTH), CalcLength(MAX_HEIGHT) };
    frameNode->SetGeometryNode(geometryNode);

    fullScreenManager->ExitFullScreen(frameNode);

    // ExitFullScreen fail: all of the frameNode has no change
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
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto fullScreenManager = AceType::MakeRefPtr<FullScreenManager>(root);

    auto frameNode = AceType::MakeRefPtr<FrameNode>(CURRENT_TAG, -1, AceType::MakeRefPtr<Pattern>(), false);
    auto parentNode = AceType::MakeRefPtr<FrameNode>(PARENT_TAG, -1, AceType::MakeRefPtr<Pattern>(), false);
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetMarginFrameOffset(FRAME_OFFSET);
    geometryNode->SetFrameSize(MAX_SIZE);
    CalcSize idealSize = { CalcLength(MAX_WIDTH), CalcLength(MAX_HEIGHT) };
    frameNode->SetGeometryNode(geometryNode);

    fullScreenManager->RequestFullScreen(frameNode);
    // RequestFullScreen Successfully
    // Check size and offset
    auto selfIdealSizeFullScreen = frameNode->GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize;
    auto maxSizeFullScreen = frameNode->GetLayoutProperty()->GetCalcLayoutConstraint()->maxSize;
    CalcSize idealSizeFS = { CalcLength(ROOT_WIDTH), CalcLength(ROOT_HEIGHT) };
    EXPECT_EQ(idealSizeFS, selfIdealSizeFullScreen);
    EXPECT_EQ(idealSizeFS, maxSizeFullScreen);
    auto geometryNodeRequestFS = frameNode->GetGeometryNode();
    auto marginFrameOffsetRequestFS = geometryNodeRequestFS->GetMarginFrameOffset();
    EXPECT_EQ(marginFrameOffsetRequestFS, OffsetF(0, 0));
    // Check frameNode's parent is root
    auto parentTag = frameNode->GetParent()->GetTag();
    EXPECT_EQ(parentTag, ROOT_TAG);

    // RequestFullScreen again fail, the MarginFrameOffset wouldn't turn to (0, 0)
    frameNode->GetGeometryNode()->SetMarginFrameOffset(FRAME_OFFSET);
    fullScreenManager->RequestFullScreen(frameNode);
    marginFrameOffsetRequestFS = geometryNodeRequestFS->GetMarginFrameOffset();
    EXPECT_EQ(marginFrameOffsetRequestFS, FRAME_OFFSET);
}
} // namespace OHOS::Ace::NG
