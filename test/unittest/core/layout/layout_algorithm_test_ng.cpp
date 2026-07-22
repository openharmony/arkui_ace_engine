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

#define private public
#define protected public

#include <sstream>
#include <unordered_set>

#include "test/unittest/core/layout/layout_algorithm_test_ng.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/property/layout_constraint.h"

namespace OHOS::Ace {
    // Test seams provided by mock_feature_param.cpp (ace_components_mock).
    void SetMockFeatureParamPageOverflowFixEnabled(bool enabled);
    void SetMockFeatureParamPageOverflowFixWhitelist(std::unordered_set<std::string> whitelist);
    void ResetMockFeatureParam();
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

// Helper function to get layout constraint from optional
inline LayoutConstraintF GetLayoutConstraint(const std::optional<LayoutConstraintF>& constraint)
{
    if (constraint.has_value()) {
        return constraint.value();
    }
    return LayoutConstraintF();
}

/**
 * @tc.name: PostponeForIgnoreTagFuncs
 * @tc.desc: test Get/SetPostponeForIgnore
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, PostponeForIgnoreTagFuncs, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    EXPECT_EQ(layoutAlgorithm->GetNeedPostponeForIgnore(), false);
    layoutAlgorithm->SetNeedPostponeForIgnore(true);
    EXPECT_EQ(layoutAlgorithm->GetNeedPostponeForIgnore(), true);
}

/**
 * @tc.name: CollectOverflowFromFrameNodeTest002
 * @tc.desc: test CollectOverflowFromFrameNode with null hostNode
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, CollectOverflowFromFrameNodeTest002, TestSize.Level0)
{
    auto result = LayoutAlgorithm::CollectOverflowFromFrameNode(nullptr, false);
    EXPECT_FALSE(result.overflowDisabled);
    EXPECT_FALSE(result.totalChildFrameRect.has_value());
}

/**
 * @tc.name: IsContentOverflowShouldDoOverflowWorkFalseTest001
 * @tc.desc: test IsContentOverflow when ShouldDoOverflowWork returns false
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, IsContentOverflowShouldDoOverflowWorkFalseTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = false;

    auto frameNode = FrameNode::CreateFrameNode("test", 9, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    OverflowCollector collector(false);

    // Without FeatureParam enabled, ShouldDoOverflowWork returns false
    auto result = layoutAlgorithm->IsContentOverflow(AceType::RawPtr(layoutWrapper), collector);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsContentOverflowIsOverflowWarningEnabledFalseTest001
 * @tc.desc: test IsContentOverflow when isOverflowWarningEnabled is false
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, IsContentOverflowIsOverflowWarningEnabledFalseTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = false;

    auto frameNode = FrameNode::CreateFrameNode("test", 10, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    OverflowCollector collector(false);

    auto result = layoutAlgorithm->IsContentOverflow(AceType::RawPtr(layoutWrapper), collector);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleContentOverflowTest001
 * @tc.desc: test HandleContentOverflow with valid layoutWrapper (non-overflow component returns early)
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleContentOverflowTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    // Test with a non-overflow component (Pattern without specific pattern type)
    // FrameNode with default Pattern is not in OVERFLOW_ENABLED_COMPONENTS
    auto frameNode = FrameNode::CreateFrameNode("test", 11, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    // HandleContentOverflow should not crash and should return early for non-overflow components
    // The method should execute without crash and return without processing
    layoutAlgorithm->HandleContentOverflow(AceType::RawPtr(layoutWrapper));
    // For non-overflow components, the method returns early without processing vOverflowHandler
    SUCCEED();
}

/**
 * @tc.name: HandleContentOverflowNullLayoutWrapperTest001
 * @tc.desc: test HandleContentOverflow with null layoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleContentOverflowNullLayoutWrapperTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    // Should not crash with null layoutWrapper
    layoutAlgorithm->HandleContentOverflow(nullptr);
    SUCCEED();
}

/**
 * @tc.name: HandleContentOverflowNullHostNodeTest001
 * @tc.desc: test HandleContentOverflow with null hostNode
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleContentOverflowNullHostNodeTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, nullptr);

    // Should not crash with null hostNode
    layoutAlgorithm->HandleContentOverflow(AceType::RawPtr(layoutWrapper));
    SUCCEED();
}

/**
 * @tc.name: HandleContentOverflowNonOverflowComponentTest001
 * @tc.desc: test HandleContentOverflow with non-overflow component
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleContentOverflowNonOverflowComponentTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    // Button is not in OVERFLOW_ENABLED_COMPONENTS
    auto frameNode = FrameNode::CreateFrameNode("Button", 12, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    // Should not crash and return early
    layoutAlgorithm->HandleContentOverflow(AceType::RawPtr(layoutWrapper));
    SUCCEED();
}

/**
 * @tc.name: HandleStackContentOverflowNullLayoutWrapperTest001
 * @tc.desc: test HandleStackContentOverflow with null layoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleStackContentOverflowNullLayoutWrapperTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    // Should not crash with null layoutWrapper
    layoutAlgorithm->HandleStackContentOverflow(nullptr);
    SUCCEED();
}

/**
 * @tc.name: HandleStackContentOverflowNullHostNodeTest001
 * @tc.desc: test HandleStackContentOverflow with null hostNode
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleStackContentOverflowNullHostNodeTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, nullptr);

    // Should not crash with null hostNode
    layoutAlgorithm->HandleStackContentOverflow(AceType::RawPtr(layoutWrapper));
    SUCCEED();
}

/**
 * @tc.name: HandleStackContentOverflowNonStackComponentTest001
 * @tc.desc: test HandleStackContentOverflow with non-Stack component
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleStackContentOverflowNonStackComponentTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    // Column is in OVERFLOW_ENABLED_COMPONENTS but not Stack
    auto frameNode = FrameNode::CreateFrameNode("Column", 14, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    // Should not crash and return early (not Stack)
    layoutAlgorithm->HandleStackContentOverflow(AceType::RawPtr(layoutWrapper));
    SUCCEED();
}

/**
 * @tc.name: IsContentOverflowForSmartLayoutTest001
 * @tc.desc: test overflow detection and safe-area disable for smart layout
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, IsContentOverflowForSmartLayoutTest001, TestSize.Level0)
{
    auto algo = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto host = FrameNode::CreateFrameNode("Column", 200, AceType::MakeRefPtr<Pattern>());
    host->GetGeometryNode()->SetFrameSize(SizeF(50.0f, 50.0f));
    auto wrapper = AceType::MakeRefPtr<LayoutWrapperNode>(host, host->GetGeometryNode(), host->GetLayoutProperty());

    auto overflowChild = FrameNode::CreateFrameNode("Text", 201, AceType::MakeRefPtr<Pattern>());
    overflowChild->GetGeometryNode()->SetFrameSize(SizeF(80.0f, 80.0f));
    overflowChild->MountToParent(host);
    overflowChild->SetActive(true);
    EXPECT_TRUE(algo->IsContentOverflowForSmartLayout(AceType::RawPtr(wrapper)));

    auto safeHost = FrameNode::CreateFrameNode("Column", 202, AceType::MakeRefPtr<Pattern>());
    safeHost->GetGeometryNode()->SetFrameSize(SizeF(50.0f, 50.0f));
    auto safeWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(safeHost, safeHost->GetGeometryNode(),
        safeHost->GetLayoutProperty());
    auto safeChild = FrameNode::CreateFrameNode("Text", 203, AceType::MakeRefPtr<Pattern>());
    safeChild->GetLayoutProperty()->UpdateSafeAreaExpandOpts({.type = SAFE_AREA_TYPE_ALL, .edges = SAFE_AREA_EDGE_ALL});
    safeChild->GetGeometryNode()->SetFrameSize(SizeF(80.0f, 80.0f));
    safeChild->MountToParent(safeHost);
    safeChild->SetActive(true);
    EXPECT_FALSE(algo->IsContentOverflowForSmartLayout(AceType::RawPtr(safeWrapper)));

    host->GetGeometryNode()->SetFrameSize(SizeF(100.0f, 100.0f));
    EXPECT_FALSE(algo->IsContentOverflowForSmartLayout(AceType::RawPtr(wrapper)));
    EXPECT_FALSE(algo->HandleContentOverflowWithSmartLayout(AceType::RawPtr(wrapper)));
}

/**
 * @tc.name: NodePath2HashTest002
 * @tc.desc: FNV-1a 64-bit matches standard reference vectors.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, NodePath2HashTest002, TestSize.Level0)
{
    // Reference vectors computed independently from the FNV-1a 64 specification.
    LayoutAlgorithm algo;
    EXPECT_EQ(algo.NodePath2Hash(""), 0xcbf29ce484222325ULL);
    EXPECT_EQ(algo.NodePath2Hash("a"), 0xaf63dc4c8601ec8cULL);
    EXPECT_EQ(algo.NodePath2Hash("foobar"), 0x85944171f73967e8ULL);
    EXPECT_EQ(algo.NodePath2Hash("Column"), 0x9e40e59654c8ad67ULL);
}

/**
 * @tc.name: ComputeCurrentPathHashTest001
 * @tc.desc: ComputeCurrentPathHash returns empty string for null hostNode.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, ComputeCurrentPathHashTest001, TestSize.Level0)
{
    auto algo = AceType::MakeRefPtr<LayoutAlgorithm>();
    EXPECT_EQ(algo->ComputeCurrentPathHash(nullptr), "");
    EXPECT_FALSE(algo->HandleContentOverflowWithSmartLayout(nullptr));
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, nullptr);
    EXPECT_FALSE(algo->HandleContentOverflowWithSmartLayout(AceType::RawPtr(layoutWrapper)));
    auto hostA = FrameNode::CreateFrameNode("Column", 401, AceType::MakeRefPtr<Pattern>());
    auto hostB = FrameNode::CreateFrameNode("Row", 402, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(algo->ComputeCurrentPathHash(AceType::RawPtr(hostA)),
        algo->ComputeCurrentPathHash(AceType::RawPtr(hostB)));
}

/**
 * @tc.name: HandleContentOverflowWithSmartLayoutFeatureOffTest001
 * @tc.desc: Returns false when the smart layout page-overflow-fix feature is disabled.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleContentOverflowWithSmartLayoutFeatureOffTest001, TestSize.Level0)
{
    OHOS::Ace::ResetMockFeatureParam();
    auto algo = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto frameNode = FrameNode::CreateFrameNode("Column", 300, AceType::MakeRefPtr<Pattern>());
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, frameNode->GetGeometryNode(), frameNode->GetLayoutProperty());
    EXPECT_FALSE(algo->HandleContentOverflowWithSmartLayout(AceType::RawPtr(layoutWrapper)));
    OHOS::Ace::ResetMockFeatureParam();
}

/**
 * @tc.name: HandleContentOverflowWithSmartLayoutUnsupportedTagTest001
 * @tc.desc: Feature on but component tag is not in SMART_LAYOUT_ENABLED_COMPONENTS returns false.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleContentOverflowWithSmartLayoutUnsupportedTagTest001, TestSize.Level0)
{
    OHOS::Ace::ResetMockFeatureParam();
    OHOS::Ace::SetMockFeatureParamPageOverflowFixEnabled(true);
    auto algo = AceType::MakeRefPtr<LayoutAlgorithm>();
    // Button is not a smart-layout supported component.
    auto frameNode = FrameNode::CreateFrameNode("Button", 301, AceType::MakeRefPtr<Pattern>());
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, frameNode->GetGeometryNode(), frameNode->GetLayoutProperty());
    EXPECT_FALSE(algo->HandleContentOverflowWithSmartLayout(AceType::RawPtr(layoutWrapper)));
    OHOS::Ace::ResetMockFeatureParam();
}

/**
 * @tc.name: HandleContentOverflowWithSmartLayoutNotOnMainTreeTest001
 * @tc.desc: Feature on and supported tag, but node not on main tree returns false.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleContentOverflowWithSmartLayoutNotOnMainTreeTest001, TestSize.Level0)
{
    OHOS::Ace::ResetMockFeatureParam();
    OHOS::Ace::SetMockFeatureParamPageOverflowFixEnabled(true);
    auto algo = AceType::MakeRefPtr<LayoutAlgorithm>();
    // Column is in SMART_LAYOUT_ENABLED_COMPONENTS; a freshly created node is not on the main tree.
    auto frameNode = FrameNode::CreateFrameNode("Column", 302, AceType::MakeRefPtr<Pattern>());
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, frameNode->GetGeometryNode(), frameNode->GetLayoutProperty());
    EXPECT_FALSE(algo->HandleContentOverflowWithSmartLayout(AceType::RawPtr(layoutWrapper)));
    OHOS::Ace::ResetMockFeatureParam();
}

/**
 * @tc.name: ComputeCurrentPathHashValidTest001
 * @tc.desc: ComputeCurrentPathHash returns the FNV-1a hex of "bundleName:path".
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, ComputeCurrentPathHashValidTest001, TestSize.Level0)
{
    auto algo = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto hostNode = FrameNode::CreateFrameNode("Column", 400, AceType::MakeRefPtr<Pattern>());

    auto result = algo->ComputeCurrentPathHash(AceType::RawPtr(hostNode));
    EXPECT_FALSE(result.empty());

    // Rebuild the same path the implementation uses, then compare against the hash directly.
    auto* context = hostNode->GetContext();
    std::string bundleName = context ? context->GetBundleName() : "";
    std::string expectedPath = bundleName + ":" + hostNode->GetPath();
    std::stringstream ss;
    ss << std::hex << algo->NodePath2Hash(expectedPath);
    EXPECT_EQ(result, ss.str());
}

/**
 * @tc.name: IsSmartLayoutEffectiveFeatureOffTest001
 * @tc.desc: Returns false when the feature switch is off.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, IsSmartLayoutEffectiveFeatureOffTest001, TestSize.Level0)
{
    OHOS::Ace::ResetMockFeatureParam();
    auto algo = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto hostNode = FrameNode::CreateFrameNode("Column", 410, AceType::MakeRefPtr<Pattern>());
    EXPECT_FALSE(algo->IsSmartLayoutEffective(hostNode));
    OHOS::Ace::ResetMockFeatureParam();
}

/**
 * @tc.name: IsSmartLayoutEffectiveNullHostTest001
 * @tc.desc: Feature on but null hostNode returns false.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, IsSmartLayoutEffectiveNullHostTest001, TestSize.Level0)
{
    OHOS::Ace::ResetMockFeatureParam();
    OHOS::Ace::SetMockFeatureParamPageOverflowFixEnabled(true);
    auto algo = AceType::MakeRefPtr<LayoutAlgorithm>();
    RefPtr<FrameNode> nullHost = nullptr;
    EXPECT_FALSE(algo->IsSmartLayoutEffective(nullHost));
    OHOS::Ace::ResetMockFeatureParam();
}

/**
 * @tc.name: IsSmartLayoutEffectiveUnsupportedTagTest001
 * @tc.desc: Feature on but component tag not supported returns false.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, IsSmartLayoutEffectiveUnsupportedTagTest001, TestSize.Level0)
{
    OHOS::Ace::ResetMockFeatureParam();
    OHOS::Ace::SetMockFeatureParamPageOverflowFixEnabled(true);
    auto algo = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto hostNode = FrameNode::CreateFrameNode("Button", 411, AceType::MakeRefPtr<Pattern>());
    EXPECT_FALSE(algo->IsSmartLayoutEffective(hostNode));
    OHOS::Ace::ResetMockFeatureParam();
}

/**
 * @tc.name: IsSmartLayoutEffectiveNotOnMainTreeTest001
 * @tc.desc: Feature on and supported tag, but node not on main tree returns false.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, IsSmartLayoutEffectiveNotOnMainTreeTest001, TestSize.Level0)
{
    OHOS::Ace::ResetMockFeatureParam();
    OHOS::Ace::SetMockFeatureParamPageOverflowFixEnabled(true);
    auto algo = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto hostNode = FrameNode::CreateFrameNode("Column", 412, AceType::MakeRefPtr<Pattern>());
    hostNode->onMainTree_ = false; // freshly created node is off the main tree
    EXPECT_FALSE(algo->IsSmartLayoutEffective(hostNode));
    OHOS::Ace::ResetMockFeatureParam();
}

/**
 * @tc.name: IsSmartLayoutEffectiveHandlerNullTest001
 * @tc.desc: Feature on, on main tree, but base Pattern returns no handler returns false.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, IsSmartLayoutEffectiveHandlerNullTest001, TestSize.Level0)
{
    OHOS::Ace::ResetMockFeatureParam();
    OHOS::Ace::SetMockFeatureParamPageOverflowFixEnabled(true);
    auto algo = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto hostNode = FrameNode::CreateFrameNode("Column", 413, AceType::MakeRefPtr<Pattern>());
    hostNode->onMainTree_ = true;
    EXPECT_FALSE(algo->IsSmartLayoutEffective(hostNode));
    OHOS::Ace::ResetMockFeatureParam();
}

/**
 * @tc.name: IsSmartLayoutEffectiveWhitelistMissTest001
 * @tc.desc: Feature on with handler, but pathHash not in whitelist returns false and caches the hash.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, IsSmartLayoutEffectiveWhitelistMissTest001, TestSize.Level0)
{
    OHOS::Ace::ResetMockFeatureParam();
    OHOS::Ace::SetMockFeatureParamPageOverflowFixEnabled(true);
    auto algo = AceType::MakeRefPtr<LayoutAlgorithm>();
    // Supported tag + a pattern that provides a real VerticalOverflowHandler.
    auto hostNode = FrameNode::CreateFrameNode("Column", 414, AceType::MakeRefPtr<FlexLayoutPattern>());
    hostNode->onMainTree_ = true;

    EXPECT_FALSE(algo->IsSmartLayoutEffective(hostNode));

    // The handler should have cached a computed pathHash on the miss path.
    auto pattern = hostNode->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    auto handler = pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(hostNode)));
    ASSERT_NE(handler, nullptr);
    EXPECT_FALSE(handler->GetCachedPathHash().empty());
    OHOS::Ace::ResetMockFeatureParam();
}

/**
 * @tc.name: IsSmartLayoutEffectiveWhitelistHitTest001
 * @tc.desc: Feature on and pathHash in whitelist returns true.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, IsSmartLayoutEffectiveWhitelistHitTest001, TestSize.Level0)
{
    OHOS::Ace::ResetMockFeatureParam();
    OHOS::Ace::SetMockFeatureParamPageOverflowFixEnabled(true);
    auto algo = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto hostNode = FrameNode::CreateFrameNode("Column", 415, AceType::MakeRefPtr<FlexLayoutPattern>());
    hostNode->onMainTree_ = true;

    // Pre-compute the same hash the implementation will derive, and whitelist it.
    std::string hash = algo->ComputeCurrentPathHash(AceType::RawPtr(hostNode));
    OHOS::Ace::SetMockFeatureParamPageOverflowFixWhitelist({ hash });

    EXPECT_TRUE(algo->IsSmartLayoutEffective(hostNode));
    OHOS::Ace::ResetMockFeatureParam();
}
} // namespace OHOS::Ace::NG
