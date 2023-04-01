/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#define protected public
#define private public
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/layout/layout_property.h"
#undef private
#undef protected
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
Dimension width {50.0, DimensionUnit::PX};
Dimension height {100.0, DimensionUnit::PX};
Dimension minWidth {10.0, DimensionUnit::PX};
Dimension minHeight {20.0, DimensionUnit::PX};
Dimension maxWidth {100.0, DimensionUnit::PX};
Dimension maxHeight {200.0, DimensionUnit::PX};
Dimension radius {10.0, DimensionUnit::PX};
float ratio = 1.0f;
int32_t ten = 10;
const Color BLUE = Color(0xff0000ff);
std::string srcimages = "common/images/mmm.jpg";
BackgroundImageSize backgroundSize {BackgroundImageSizeType::AUTO, 1.0};
BackgroundImagePosition backgroundPosition {BackgroundImagePositionType::PERCENT, -1.0,
    BackgroundImagePositionType::PERCENT, 0.0};
OffsetF offsetF {1.0, 1.0};
Offset offset {2.0, 2.0};
static constexpr int32_t FOUF = 4;
}; // namespace
class ViewAbstractTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: ViewAbstractTest001
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetOverlay.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    OverlayOptions overlay;
    viewAbstract.SetOverlay(std::move(overlay));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest002
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetWidth.push FrameNode is null.
     * @tc.steps: step2. callback SetHeight.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetWidth(NG::CalcLength(width));
    viewAbstract.SetHeight(NG::CalcLength(height));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    EXPECT_EQ(Node, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest003
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetWidth.push FrameNode is not null.
     * @tc.steps: step2. callback SetHeight.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewAbstract viewAbstract;
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetWidth(NG::CalcLength(width));
    viewAbstract.SetHeight(NG::CalcLength(height));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest004
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetMinWidth.push FrameNode is null.
     * @tc.steps: step2. callback SetMinHeight.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetMinWidth(NG::CalcLength(minWidth));
    viewAbstract.SetMinHeight(NG::CalcLength(minHeight));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest005
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetMinWidth.push FrameNode is not null.
     * @tc.steps: step2. callback SetMinHeight.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewAbstract viewAbstract;
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetMinWidth(NG::CalcLength(minWidth));
    viewAbstract.SetMinHeight(NG::CalcLength(minHeight));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest006
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetMaxWidth.push FrameNode is null.
     * @tc.steps: step2. callback SetMaxHeight.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetMaxWidth(NG::CalcLength(maxWidth));
    viewAbstract.SetMaxHeight(NG::CalcLength(maxHeight));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest007
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetMaxWidth.push FrameNode is not null.
     * @tc.steps: step2. callback SetMaxHeight.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewAbstract viewAbstract;
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetMaxWidth(NG::CalcLength(maxWidth));
    viewAbstract.SetMaxHeight(NG::CalcLength(maxHeight));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest008
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback ClearWidthOrHeight.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.ClearWidthOrHeight(true);

    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.ClearWidthOrHeight(true);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    viewStackProcessor.instance = nullptr;

    /**
     * @tc.steps: step3.ClearStack and callback ClearWidthOrHeight.
     * @tc.expected: step. Return expected results.
     */
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.ClearWidthOrHeight(true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest009
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetAspectRatio.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetAspectRatio(1.0f);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0010
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetAspectRatio.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetAspectRatio(ratio);
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetAspectRatio(ratio);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0011
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackgroundColor.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetBackgroundColor(BLUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0012
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackgroundColor.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetBackgroundColor(BLUE);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0013
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackgroundImage.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetBackgroundImage(srcimages);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0014
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackgroundImage.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetBackgroundImage(srcimages);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0015
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackgroundImageRepeat.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t repeatIndex = 1;
    auto repeat = static_cast<ImageRepeat>(repeatIndex);
    viewAbstract.SetBackgroundImageRepeat(repeat);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0016
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackgroundImageRepeat.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    int32_t repeatIndex = 1;
    auto repeat = static_cast<ImageRepeat>(repeatIndex);
    viewAbstract.SetBackgroundImageRepeat(repeat);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0017
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackgroundImageSize.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetBackgroundImageSize(backgroundSize);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0018
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackgroundImageSize.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetBackgroundImageSize(backgroundSize);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0019
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackgroundImagePosition.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetBackgroundImagePosition(backgroundPosition);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0020
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackgroundImagePosition.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetBackgroundImagePosition(backgroundPosition);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0021
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackgroundBlurStyle.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetBackgroundBlurStyle(blurStyleOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0022
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackgroundBlurStyle.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::THIN;
    blurStyleOption.colorMode = ThemeColorMode::LIGHT;
    blurStyleOption.adaptiveColor = AdaptiveColor::AVERAGE;
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetBackgroundBlurStyle(blurStyleOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0023
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetLayoutWeight.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetLayoutWeight(ten);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0024
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetLayoutWeight.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetLayoutWeight(ten);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0025
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetLayoutDirection.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto direction = static_cast<TextDirection>(index);
    viewAbstract.SetLayoutDirection(direction);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0026
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetLayoutDirection.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    int32_t index = 1;
    auto direction = static_cast<TextDirection>(index);
    viewAbstract.SetLayoutDirection(direction);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0027
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetAlignRules.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    std::map<AlignDirection, AlignRule> alignRules;
    viewAbstract.SetAlignRules(alignRules);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0028
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetAlignRules.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    std::map<AlignDirection, AlignRule> alignRules;
    viewAbstract.SetAlignRules(alignRules);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0029
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetAlignSelf.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto alignSelf = static_cast<FlexAlign>(index);
    viewAbstract.SetAlignSelf(alignSelf);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0030
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetAlignSelf.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    int32_t index = 1;
    auto alignSelf = static_cast<FlexAlign>(index);
    viewAbstract.SetAlignSelf(alignSelf);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0031
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetFlexShrink.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetFlexShrink(ratio);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0032
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetFlexShrink.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetFlexShrink(ratio);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0033
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetFlexGrow.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetFlexGrow(ratio);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0034
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetFlexGrow.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetFlexGrow(ratio);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0035
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetFlexBasis.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetFlexBasis(width);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0036
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetFlexBasis.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetFlexBasis(width);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0037
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetDisplayIndex.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetDisplayIndex(2);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0038
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetDisplayIndex.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetDisplayIndex(2);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0039
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetPadding.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetPadding(NG::CalcLength(width));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0040
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetPadding.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetPadding(NG::CalcLength(width));
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0041
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetPadding.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    NG::PaddingProperty paddings;
    viewAbstract.SetPadding(paddings);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0042
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetPadding.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    NG::PaddingProperty paddings;
    viewAbstract.SetPadding(paddings);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0043
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetMargin.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetMargin(NG::CalcLength(width));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0044
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetMargin.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetMargin(NG::CalcLength(width));
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0045
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetMargin.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    NG::MarginProperty margins;
    viewAbstract.SetMargin(margins);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0046
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0046, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetMargin.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    NG::MarginProperty margins;
    viewAbstract.SetMargin(margins);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0047
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderRadius.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetBorderRadius(width);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0048
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderRadius.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetBorderRadius(width);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0049
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0049, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderRadius.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    NG::BorderRadiusProperty borderRadius;
    viewAbstract.SetBorderRadius(borderRadius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0050
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderRadius.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    NG::BorderRadiusProperty borderRadius;
    viewAbstract.SetBorderRadius(borderRadius);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0051
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderColor.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetBorderColor(BLUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0052
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0052, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderColor.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetBorderColor(BLUE);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0053
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0053, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderColor.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    NG::BorderColorProperty borderColors;
    viewAbstract.SetBorderColor(borderColors);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0054
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0054, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderColor.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    NG::BorderColorProperty borderColors;
    viewAbstract.SetBorderColor(borderColors);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0055
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0055, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderWidth.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetBorderWidth(width);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0056
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0056, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderWidth.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetBorderWidth(width);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0057
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0057, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderWidth.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    NG::BorderWidthProperty borderWidth;
    viewAbstract.SetBorderWidth(borderWidth);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0058
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0058, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderWidth.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    NG::BorderWidthProperty borderWidth;
    viewAbstract.SetBorderWidth(borderWidth);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0059
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0059, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderStyle.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto borderStyle = static_cast<BorderStyle>(index);
    viewAbstract.SetBorderStyle(borderStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0060
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0060, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderStyle.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    int32_t index = 1;
    auto borderStyle = static_cast<BorderStyle>(index);
    viewAbstract.SetBorderStyle(borderStyle);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0061
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0061, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderStyle.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    NG::BorderStyleProperty borderStyles;
    viewAbstract.SetBorderStyle(borderStyles);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0062
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0062, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderStyle.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    NG::BorderStyleProperty borderStyles;
    viewAbstract.SetBorderStyle(borderStyles);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0063
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0063, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnClick.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    GestureEventFunc tapEventFunc;
    viewAbstract.SetOnClick(std::move(tapEventFunc));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0064
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0064, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnClick.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    GestureEventFunc tapEventFunc;
    viewAbstract.SetOnClick(std::move(tapEventFunc));
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0065
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0065, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnTouch.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    TouchEventFunc touchEventFunc;
    viewAbstract.SetOnTouch(std::move(touchEventFunc));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0066
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0066, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnTouch.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    TouchEventFunc touchEventFunc;
    viewAbstract.SetOnTouch(std::move(touchEventFunc));
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0067
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0067, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnMouse.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    OnMouseEventFunc onMouseEventFunc;
    viewAbstract.SetOnMouse(std::move(onMouseEventFunc));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0068
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0068, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnMouse.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OnMouseEventFunc onMouseEventFunc;
    viewAbstract.SetOnMouse(std::move(onMouseEventFunc));
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0069
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0069, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnHover.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    OnHoverEventFunc onHoverEventFunc;
    viewAbstract.SetOnHover(std::move(onHoverEventFunc));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0070
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0070, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnHover.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OnHoverEventFunc onHoverEventFunc;
    viewAbstract.SetOnHover(std::move(onHoverEventFunc));
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0071
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0071, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetHoverEffect.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
        int32_t index = 1;
    auto hoverEffect = static_cast<HoverEffectType>(index);
    viewAbstract.SetHoverEffect(hoverEffect);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0072
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0072, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetHoverEffect.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    int32_t index = 1;
    auto hoverEffect = static_cast<HoverEffectType>(index);
    viewAbstract.SetHoverEffect(hoverEffect);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0073
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0073, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetEnabled.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetEnabled(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0074
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0074, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetEnabled.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    focusHub->show_ = true;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    viewAbstract.SetEnabled(true);
    EXPECT_FALSE(focusHub->IsFocusableScope());
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0075
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0075, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetFocusable.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetFocusable(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0076
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0076, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetFocusable.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetFocusable(true);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0077
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0077, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnFocus.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    auto callback = []() {
        srcimages = "test";
    };
    viewAbstract.SetOnFocus(callback);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0078
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0078, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnFocus.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    auto callback = []() {
        srcimages = "test";
    };
    viewAbstract.SetOnFocus(callback);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0079
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0079, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnBlur.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    auto callback = []() {
        srcimages = "test";
    };
    viewAbstract.SetOnBlur(callback);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0080
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0080, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnBlur.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    auto callback = []() {
        srcimages = "test";
    };
    viewAbstract.SetOnBlur(callback);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0081
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0081, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnKeyEvent.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    OnKeyCallbackFunc onKeyCallback;
    viewAbstract.SetOnKeyEvent(std::move(onKeyCallback));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0082
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0082, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnKeyEvent.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OnKeyCallbackFunc onKeyCallback;
    viewAbstract.SetOnKeyEvent(std::move(onKeyCallback));
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0083
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0083, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetTabIndex.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetTabIndex(1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0084
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0084, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetTabIndex.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetTabIndex(1);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0085
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0085, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetFocusOnTouch.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetFocusOnTouch(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0086
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0086, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetFocusOnTouch.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetFocusOnTouch(true);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0087
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0087, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetDefaultFocus.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetDefaultFocus(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0088
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0088, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetDefaultFocus.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetDefaultFocus(true);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0089
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0089, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetGroupDefaultFocus.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetGroupDefaultFocus(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0090
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0090, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetGroupDefaultFocus.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetGroupDefaultFocus(true);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0091
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0091, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnAppear.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    auto callback = []() {
        srcimages = "test";
    };
    viewAbstract.SetOnAppear(callback);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0092
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0092, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnAppear.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    auto callback = []() {
        srcimages = "test";
    };
    viewAbstract.SetOnAppear(callback);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0093
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0093, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnDisappear.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    auto callback = []() {
        srcimages = "test";
    };
    viewAbstract.SetOnDisappear(callback);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0094
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0094, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnDisappear.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    auto callback = []() {
        srcimages = "test";
    };
    viewAbstract.SetOnDisappear(callback);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0095
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0095, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetResponseRegion.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    std::vector<DimensionRect> responseRegion;
    viewAbstract.SetResponseRegion(std::move(responseRegion));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0096
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0096, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetResponseRegion.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    std::vector<DimensionRect> responseRegion;
    viewAbstract.SetResponseRegion(std::move(responseRegion));
    EXPECT_EQ(responseRegion.size(), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0097
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0097, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetTouchable.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetTouchable(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0098
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0098, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetTouchable.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetTouchable(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0099
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0099, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetHitTestMode.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto hitTestMode = static_cast<HitTestMode>(index);
    viewAbstract.SetHitTestMode(hitTestMode);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0100
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00100, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetHitTestMode.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    int32_t index = 1;
    auto hitTestMode = static_cast<HitTestMode>(index);
    viewAbstract.SetHitTestMode(hitTestMode);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0101
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0101, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnDragStart.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragStart;
    viewAbstract.SetOnDragStart(std::move(onDragStart));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0102
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00102, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnDragStart.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragStart;
    viewAbstract.SetOnDragStart(std::move(onDragStart));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0103
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0103, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnDragEnter.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragEnter;
    viewAbstract.SetOnDragEnter(std::move(onDragEnter));
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0104
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00104, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnDragEnter.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    frameNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(width), CalcLength(height)));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragEnter;
    viewAbstract.SetOnDragEnter(std::move(onDragEnter));
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0105
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0105, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnDragLeave.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragLeave;
    viewAbstract.SetOnDragLeave(std::move(onDragLeave));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0106
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00106, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnDragLeave.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragLeave;
    viewAbstract.SetOnDragLeave(std::move(onDragLeave));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0107
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0107, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnDragMove.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragMove;
    viewAbstract.SetOnDragMove(std::move(onDragMove));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0108
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00108, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnDragMove.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDragMove;
    viewAbstract.SetOnDragMove(std::move(onDragMove));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0109
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0109, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnDrop.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDrop;
    viewAbstract.SetOnDrop(std::move(onDrop));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0110
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00110, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnDrop.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&,
        const std::string&)> onDrop;
    viewAbstract.SetOnDrop(std::move(onDrop));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0111
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0111, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetAlign.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    Alignment alignment;
    viewAbstract.SetAlign(std::move(alignment));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0112
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00112, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetAlign.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    Alignment alignment;
    viewAbstract.SetAlign(std::move(alignment));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0113
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0113, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetVisibility.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto visible = static_cast<VisibleType>(index);
    viewAbstract.SetVisibility(std::move(visible));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0114
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00114, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetVisibility.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    int32_t index = 1;
    auto visible = static_cast<VisibleType>(index);
    viewAbstract.SetVisibility(std::move(visible));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0115
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0115, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetGeometryTransition.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetGeometryTransition(srcimages);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0116
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00116, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetGeometryTransition.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetGeometryTransition(srcimages);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0117
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0117, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOpacity.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetOpacity(1.0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0118
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00118, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOpacity.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetOpacity(1.0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0119
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0119, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetPosition.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    OffsetT<Dimension> value = {width, height};
    viewAbstract.SetPosition(value);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0120
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00120, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetPosition.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OffsetT<Dimension> value = {width, height};
    viewAbstract.SetPosition(value);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0121
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0121, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOffset.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    OffsetT<Dimension> value = {width, height};
    viewAbstract.SetOffset(value);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0122
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00122, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOffset.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OffsetT<Dimension> value = {width, height};
    viewAbstract.SetOffset(value);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0123
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0123, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback MarkAnchor.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    OffsetT<Dimension> value = {width, height};
    viewAbstract.MarkAnchor(value);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0124
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00124, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback MarkAnchor.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OffsetT<Dimension> value = {width, height};
    viewAbstract.MarkAnchor(value);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0125
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0125, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetZIndex.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetZIndex(FOUF);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0126
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00126, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetZIndex.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetZIndex(FOUF);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0127
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0127, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetScale.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    VectorF scale(1.0f, 1.0f);
    viewAbstract.SetScale(scale);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0128
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00128, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetScale.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    VectorF scale(1.0f, 1.0f);
    viewAbstract.SetScale(scale);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0129
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0129, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetPivot.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    DimensionOffset value = {width, height};
    viewAbstract.SetPivot(value);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0130
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00130, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetPivot.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    DimensionOffset value = {width, height};
    viewAbstract.SetPivot(value);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0131
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0131, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetTranslate.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    NG::TranslateOptions value;
    viewAbstract.SetTranslate(std::move(value));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0132
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00132, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetTranslate.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    NG::TranslateOptions value;
    viewAbstract.SetTranslate(std::move(value));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0133
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0133, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetRotate.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    Vector4F scale(1.0f, 1.0f, 2.0f, 2.0f);
    viewAbstract.SetRotate(scale);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0134
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00134, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetRotate.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    Vector4F scale(1.0f, 1.0f, 2.0f, 2.0f);
    viewAbstract.SetRotate(scale);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0135
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0135, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetTransformMatrix.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    Matrix4 matrix;
    viewAbstract.SetTransformMatrix(std::move(matrix));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0136
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00136, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetTransformMatrix.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    Matrix4 matrix;
    viewAbstract.SetTransformMatrix(std::move(matrix));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0137
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0137, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackdropBlur.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetBackdropBlur(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0138
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00138, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackdropBlur.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetBackdropBlur(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0139
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0139, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetFrontBlur.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetFrontBlur(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0140
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00140, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetFrontBlur.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetFrontBlur(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0141
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0141, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackShadow.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    ShadowStyle style {1};
    Shadow shadow {ratio, offset, BLUE, style};
    viewAbstract.SetBackShadow(shadow);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0142
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00142, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBackShadow.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    ShadowStyle style {1};
    Shadow shadow {ratio, offset, BLUE, style};
    viewAbstract.SetBackShadow(shadow);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0143
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0143, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetLinearGradient.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    NG::Gradient gradient;
    viewAbstract.SetLinearGradient(std::move(gradient));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0144
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00144, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetLinearGradient.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    NG::Gradient gradient;
    viewAbstract.SetLinearGradient(std::move(gradient));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0145
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0145, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetSweepGradient.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    NG::Gradient gradient;
    viewAbstract.SetSweepGradient(std::move(gradient));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0146
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00146, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetSweepGradient.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    NG::Gradient gradient;
    viewAbstract.SetSweepGradient(std::move(gradient));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0147
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0147, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetRadialGradient.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    NG::Gradient gradient;
    viewAbstract.SetRadialGradient(std::move(gradient));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0148
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00148, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetRadialGradient.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    NG::Gradient gradient;
    viewAbstract.SetRadialGradient(std::move(gradient));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0149
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0149, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetInspectorId.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetInspectorId(srcimages);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0150
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00150, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetInspectorId.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetInspectorId(srcimages);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0151
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0151, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetDebugLine.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetDebugLine(srcimages);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0152
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0152, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetGrid.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto visible = static_cast<GridSizeType>(index);
    viewAbstract.SetGrid(FOUF, FOUF, std::move(visible));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0153
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00153, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetGrid.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    frameNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(width), CalcLength(height)));
    int32_t index = 1;
    auto visible = static_cast<GridSizeType>(index);
    viewAbstract.SetGrid(FOUF, FOUF, std::move(visible));
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0154
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0154, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetTransition.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    TransitionOptions options;
    viewAbstract.SetTransition(std::move(options));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0155
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00155, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetTransition.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    TransitionOptions options;
    viewAbstract.SetTransition(std::move(options));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0156
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0156, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetClipShape.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    RefPtr<BasicShape> basicShape;
    viewAbstract.SetClipShape(std::move(basicShape));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0157
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00157, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetClipShape.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    RefPtr<BasicShape> basicShape;
    viewAbstract.SetClipShape(std::move(basicShape));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0158
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0158, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetMask.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    RefPtr<BasicShape> basicShape;
    viewAbstract.SetMask(std::move(basicShape));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0159
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00159, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetMask.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    RefPtr<BasicShape> basicShape;
    viewAbstract.SetMask(std::move(basicShape));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0160
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0160, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetClipEdge.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetClipEdge(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0161
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00161, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetClipEdge.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetClipEdge(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0162
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0162, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetGrayScale.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetGrayScale(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0163
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00163, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetGrayScale.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetGrayScale(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0164
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0164, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetContrast.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetContrast(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0165
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00165, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetContrast.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetContrast(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0166
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0166, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetSaturate.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetSaturate(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0167
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00167, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetSaturate.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetSaturate(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0168
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0168, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetSepia.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetSepia(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0169
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00169, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetSepia.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetSepia(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0170
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0170, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetInvert.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetInvert(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0171
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00171, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetInvert.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetInvert(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0172
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0172, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetHueRotate.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetHueRotate(ratio);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0173
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00173, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetHueRotate.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetHueRotate(ratio);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0174
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0174, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBrightness.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetBrightness(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0175
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00175, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBrightness.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetBrightness(radius);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0176
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0176, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetColorBlend.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetColorBlend(BLUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0177
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00177, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetColorBlend.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetColorBlend(BLUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0178
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0178, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderImageSource.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetBorderImageSource(srcimages);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0179
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00179, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderImageSource.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetBorderImageSource(srcimages);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0180
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0180, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderImage.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    RefPtr<BorderImage> borderImage;
    viewAbstract.SetBorderImage(std::move(borderImage));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0181
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00181, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderImage.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    RefPtr<BorderImage> borderImage;
    viewAbstract.SetBorderImage(std::move(borderImage));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0182
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0182, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetHasBorderImageSlice.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetHasBorderImageSlice(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0183
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00183, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetHasBorderImageSlice.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetHasBorderImageSlice(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0184
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0184, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetHasBorderImageWidth.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetHasBorderImageWidth(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0185
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00185, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetHasBorderImageWidth.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetHasBorderImageWidth(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0186
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0186, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetHasBorderImageOutset.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetHasBorderImageOutset(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0187
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00187, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetHasBorderImageOutset.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetHasBorderImageOutset(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0188
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0188, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetHasBorderImageRepeat.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetHasBorderImageRepeat(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0189
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00189, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetHasBorderImageRepeat.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    viewAbstract.SetHasBorderImageRepeat(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0190
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0190, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderImageGradient.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    Gradient gradient;
    viewAbstract.SetBorderImageGradient(std::move(gradient));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0191
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00191, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetBorderImageGradient.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    Gradient gradient;
    viewAbstract.SetBorderImageGradient(std::move(gradient));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0192
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0192, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOverlay.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    OverlayOptions overlay;
    viewAbstract.SetOverlay(std::move(overlay));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0193
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00193, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOverlay.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OverlayOptions overlay;
    viewAbstract.SetOverlay(std::move(overlay));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0194
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0194, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetMotionPath.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    MotionPathOption motionPath;
    viewAbstract.SetMotionPath(std::move(motionPath));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0195
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00195, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetMotionPath.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    MotionPathOption motionPath;
    viewAbstract.SetMotionPath(std::move(motionPath));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0196
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0196, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetSharedTransition.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    viewAbstract.SetSharedTransition("", nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0197
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest00197, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetSharedTransition.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    std::shared_ptr<SharedTransitionOption> option;
    viewAbstract.SetSharedTransition(srcimages, std::move(option));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0198
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0198, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnAreaChanged.push FrameNode is null.
     * @tc.expected: step2. Return expected results..
     */
    ViewAbstract viewAbstract;
    std::function<void(const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)>
        onAreaChanged;
    viewAbstract.SetOnAreaChanged(std::move(onAreaChanged));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode, nullptr);
}

/**
 * @tc.name: ViewAbstractTest0199
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0199, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback SetOnVisibleChange.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    constexpr char TAG_ROOT[] = "root";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    ViewAbstract viewAbstract;
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    std::function<void(bool, double)> onVisibleChange;
    const std::vector<double> ratios;
    viewAbstract.SetOnVisibleChange(std::move(onVisibleChange), ratios);
    EXPECT_FALSE(FRAME_NODE_ROOT->isMeasureBoundary_);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest0201
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0201, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback ShowMenu.push isContextMenu is false.
     * @tc.expected: step2. Return expected results..
     */
    std::shared_ptr<SubwindowManager> subwindow = SubwindowManager::GetInstance();
    ContainerScope sontainerScope(1);
    sontainerScope.currentId_ = 1;
    ViewAbstract::ShowMenu(1, offsetF, false);
    auto container = Container::Current();
    EXPECT_EQ(container, nullptr);
}

/**
 * @tc.name: ViewAbstractTest0202
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0202, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2. callback Pop.push FrameNode is not null.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    constexpr char TAG_ROOT[] = "root";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    ViewAbstract viewAbstract;
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    viewAbstract.Pop();
    EXPECT_TRUE(viewStackProcessor.elementsStack_.empty());
}

/**
 * @tc.name: ViewAbstractTest0203
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0203, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetWidth.
     * @tc.steps: step2.ClearStack and callback SetHeight.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetWidth(NG::CalcLength(width));
    viewAbstract.SetHeight(NG::CalcLength(height));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0204
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0204, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetMinWidth.
     * @tc.steps: step2.ClearStack and callback SetMinHeight.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetMinWidth(NG::CalcLength(minWidth));
    viewAbstract.SetMinHeight(NG::CalcLength(minHeight));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0205
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0205, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetMaxWidth.
     * @tc.steps: step2.ClearStack and callback SetMaxHeight.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetMaxWidth(NG::CalcLength(maxWidth));
    viewAbstract.SetMaxHeight(NG::CalcLength(maxHeight));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0206
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0206, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetMotionPath.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    MotionPathOption motionPath;
    viewAbstract.SetMotionPath(std::move(motionPath));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0207
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0207, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetAspectRatio.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetAspectRatio(1.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0208
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0208, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBackgroundColor.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetBackgroundColor(BLUE);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0209
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0209, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBackgroundImage.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetBackgroundImage(srcimages);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0210
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0210, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBackgroundImageRepeat.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    auto repeat = static_cast<ImageRepeat>(index);
    viewAbstract.SetBackgroundImageRepeat(repeat);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0211
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0211, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBackgroundImageSize.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetBackgroundImageSize(backgroundSize);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0212
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0212, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBackgroundImagePosition.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetBackgroundImagePosition(backgroundPosition);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0213
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0213, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBackgroundBlurStyle.
     * @tc.expected: step2. Return expected results..
     */
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetBackgroundBlurStyle(blurStyleOption);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0214
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0214, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetLayoutWeight.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetLayoutWeight(ten);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0215
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0215, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetLayoutDirection.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    auto direction = static_cast<TextDirection>(index);
    viewAbstract.SetLayoutDirection(direction);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0216
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0216, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetAlignRules.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    std::map<AlignDirection, AlignRule> alignRules;
    viewAbstract.SetAlignRules(alignRules);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0217
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0217, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetAlignSelf.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    auto alignSelf = static_cast<FlexAlign>(index);
    viewAbstract.SetAlignSelf(alignSelf);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0218
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0218, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetFlexShrink.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetFlexShrink(ratio);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0219
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0219, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetFlexGrow.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetFlexGrow(ratio);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0220
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0220, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetFlexBasis.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetFlexBasis(width);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0221
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0221, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetDisplayIndex.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetDisplayIndex(ten);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0222
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0222, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetPadding.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetPadding(NG::CalcLength(width));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0223
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0223, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetPadding.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    NG::PaddingProperty paddings;
    viewAbstract.SetPadding(paddings);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0224
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0224, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetMargin.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetMargin(NG::CalcLength(width));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0225
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0225, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetMargin.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    NG::MarginProperty margins;
    viewAbstract.SetMargin(margins);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0226
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0226, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBorderRadius.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetBorderRadius(width);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0227
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0227, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBorderRadius.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    NG::BorderRadiusProperty borderRadius;
    viewAbstract.SetBorderRadius(borderRadius);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0228
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0228, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBorderColor.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetBorderColor(BLUE);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0229
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0229, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBorderColor.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    NG::BorderColorProperty borderColors;
    viewAbstract.SetBorderColor(borderColors);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0230
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0230, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBorderWidth.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetBorderWidth(width);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0231
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0231, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBorderWidth.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    NG::BorderWidthProperty borderWidth;
    viewAbstract.SetBorderWidth(borderWidth);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0232
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0232, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBorderStyle.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    auto borderStyle = static_cast<BorderStyle>(index);
    viewAbstract.SetBorderStyle(borderStyle);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0233
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0233, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBorderStyle.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    NG::BorderStyleProperty borderStyles;
    viewAbstract.SetBorderStyle(borderStyles);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0234
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0234, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetAlign.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    Alignment alignment;
    viewAbstract.SetAlign(std::move(alignment));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0235
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0235, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetVisibility.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    auto visible = static_cast<VisibleType>(index);
    viewAbstract.SetVisibility(std::move(visible));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0236
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0236, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetOpacity.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetOpacity(1.0);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0237
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0237, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetPosition.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    OffsetT<Dimension> value = {width, height};
    viewAbstract.SetPosition(value);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0238
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0238, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetOffset.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    OffsetT<Dimension> value = {width, height};
    viewAbstract.SetOffset(value);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0239
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0239, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback MarkAnchor.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    OffsetT<Dimension> value = {width, height};
    viewAbstract.MarkAnchor(value);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0240
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0240, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetZIndex.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetZIndex(FOUF);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0241
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0241, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetScale.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    VectorF scale(1.0f, 1.0f);
    viewAbstract.SetScale(scale);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0242
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0242, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetPivot.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    DimensionOffset value = {width, height};
    viewAbstract.SetPivot(value);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0243
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0243, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetTranslate.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    NG::TranslateOptions value;
    viewAbstract.SetTranslate(std::move(value));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0244
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0244, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetRotate.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    Vector4F scale(1.0f, 1.0f, 2.0f, 2.0f);
    viewAbstract.SetRotate(scale);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0245
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0245, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetTransformMatrix.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    Matrix4 matrix;
    viewAbstract.SetTransformMatrix(std::move(matrix));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0246
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0246, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBackdropBlur.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetBackdropBlur(radius);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0247
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0247, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetFrontBlur.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetFrontBlur(radius);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0248
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0248, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBackShadow.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    ShadowStyle style {1};
    Shadow shadow {ratio, offset, BLUE, style};
    viewAbstract.SetBackShadow(shadow);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0249
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0249, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetLinearGradient.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    NG::Gradient gradient;
    viewAbstract.SetLinearGradient(std::move(gradient));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0250
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0250, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetSweepGradient.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    NG::Gradient gradient;
    viewAbstract.SetSweepGradient(std::move(gradient));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0251
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0251, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetRadialGradient.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    NG::Gradient gradient;
    viewAbstract.SetRadialGradient(std::move(gradient));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0252
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0252, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetTransition.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    TransitionOptions options;
    viewAbstract.SetTransition(std::move(options));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0253
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0253, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetClipShape.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    RefPtr<BasicShape> basicShape;
    viewAbstract.SetClipShape(std::move(basicShape));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0254
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0254, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetClipEdge.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetClipEdge(false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0255
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0255, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetMask.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    RefPtr<BasicShape> basicShape;
    viewAbstract.SetMask(std::move(basicShape));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0256
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0256, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBrightness.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetBrightness(radius);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0257
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0257, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetGrayScale.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetGrayScale(radius);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0258
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0258, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetContrast.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetContrast(radius);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0259
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0259, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetSaturate.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetSaturate(radius);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0260
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0260, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetSepia.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetSepia(radius);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0261
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0261, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetInvert.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetInvert(radius);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0262
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0262, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetHueRotate.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetHueRotate(ratio);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0263
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0263, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetColorBlend.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetColorBlend(BLUE);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0264
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0264, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBorderImage.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    RefPtr<BorderImage> borderImage;
    viewAbstract.SetBorderImage(std::move(borderImage));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0265
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0265, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBorderImageSource.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetBorderImageSource(srcimages);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0266
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0266, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetHasBorderImageSlice.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetHasBorderImageSlice(false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0267
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0267, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetHasBorderImageWidth.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetHasBorderImageWidth(false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0268
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0268, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetHasBorderImageOutset.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetHasBorderImageOutset(false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0269
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0269, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetHasBorderImageRepeat.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetHasBorderImageRepeat(false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest0270
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTest, ViewAbstractTest0270, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     * @tc.steps: step2.ClearStack and callback SetBorderImageGradient.
     * @tc.expected: step2. Return expected results..
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    viewStackProcessor.GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    Gradient gradient;
    viewAbstract.SetBorderImageGradient(std::move(gradient));
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace::NG
