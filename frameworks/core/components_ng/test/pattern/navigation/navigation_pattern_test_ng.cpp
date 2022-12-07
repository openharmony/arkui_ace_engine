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

#define protected public
#define private public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_view.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class NavigationPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
protected:
};

/**
 * @tc.name: NavigationPatternTest_001
 * @tc.desc: Test REPLACE navigator.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_001, TestSize.Level1)
{
    NavigationView navigationView;
    navigationView.Create();
    navigationView.SetTitle("navigationView", false);

    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    EXPECT_NE(navigationLayoutProperty, nullptr);
}

/**
 * @tc.name: NavigationPatternTest_002
 * @tc.desc: Test NavigationPattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_002, TestSize.Level1)
{
    NavigationView navigationView;
    navigationView.Create();
    navigationView.SetTitle("navigationView", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    EXPECT_NE(navigationLayoutProperty, nullptr);

    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(hostNode, nullptr);

    NavigationPattern navigationPattern;
    navigationPattern.OnModifyDone();
}

/**
 * @tc.name: NavigationPatternTest_003
 * @tc.desc: Various situations of Test NavigationPattern OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_003, TestSize.Level1)
{
    NavigationView navigationView;
    navigationView.Create();
    navigationView.SetTitle("navigationView", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    EXPECT_NE(navigationLayoutProperty, nullptr);

    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(hostNode, nullptr);
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    EXPECT_NE(layoutWrapper, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    std::vector<DirtySwapConfig> configValue;
    configValue.push_back(config);
    config.skipLayout = false;
    configValue.push_back(config);
    config.skipMeasure = false;
    configValue.push_back(config);
    config.skipLayout = true;
    configValue.push_back(config);

    for (auto &iter : configValue) {
        EXPECT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, iter), false);
    }
}

/**
 * @tc.name: NavigationPatternTest_004
 * @tc.desc: Test Two level nesting of layoutWrapper.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_004, TestSize.Level1)
{
    NavigationView navigationView;
    navigationView.Create();
    navigationView.SetTitle("navigationView", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    EXPECT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    EXPECT_NE(layoutWrapper, nullptr);
    
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    bool result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(result, false);

    auto setNavigation = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(setNavigation);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: NavigationPatternTest_005
 * @tc.desc: Test REPLACE navigator.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_005, TestSize.Level1)
{
    NavigationView navigationView;
    navigationView.Create();
    navigationView.SetTitle("navigationView", false);

    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    navigationView.SetCustomTitle(frameNode);
    RefPtr<UINode> uiNode = nullptr;
    navigationView.SetCustomTitle(uiNode);

    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    EXPECT_NE(navigationLayoutProperty, nullptr);
}
}