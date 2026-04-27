/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <gtest/gtest.h>
#include <algorithm>
#include <limits>

// NOLINTBEGIN
#define private public
#define protected public
#include "core/components_ng/pattern/smart_layout/smart_layout_algorithm.h"
#include "core/components_ng/pattern/smart_layout/smart_layout_engine_loader.h"
#undef private
#undef protected
// NOLINTEND

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t TEST_HOST_NODE_ID = 1600;
constexpr int32_t TEST_CHILD_NODE_ID = 1601;
constexpr int32_t TEST_NULL_ROOT_HOST_NODE_ID = 2600;
constexpr int32_t TEST_NULL_ROOT_CHILD_NODE_ID = 2601;
constexpr int32_t TEST_NON_FLEX_LAYOUT_HOST_NODE_ID = 2800;
constexpr int32_t TEST_NON_FLEX_CHILD_NODE_ID = 2801;
constexpr int32_t TEST_FLEX_DEFAULT_HOST_NODE_ID = 2900;
constexpr int32_t TEST_FLEX_DEFAULT_CHILD_NODE_ID = 2901;
constexpr float TEST_PARENT_WIDTH = 120.0f;
constexpr float TEST_PARENT_HEIGHT = 90.0f;
constexpr float TEST_PERFORM_PARENT_HEIGHT = 80.0f;
constexpr int32_t INVALID_MAIN_ALIGN = 999;
constexpr int32_t INVALID_CROSS_ALIGN = 1000;

class TestRecursiveLock final : public RecursiveLock {
public:
    void Lock() override {}
    void Unlock() override {}
};

class SmartLayoutAlgorithmTestWrapper final : public LayoutWrapper {
public:
    SmartLayoutAlgorithmTestWrapper(const WeakPtr<FrameNode>& hostNode, const std::string& hostTag)
        : LayoutWrapper(hostNode), hostTag_(hostTag)
    {}

    ~SmartLayoutAlgorithmTestWrapper() override = default;

    const RefPtr<LayoutAlgorithmWrapper>& GetLayoutAlgorithm(bool needReset = false) override
    {
        return layoutAlgorithm_;
    }

    void Measure(const std::optional<LayoutConstraintF>& parentConstraint) override {}

    void Layout() override
    {
        layoutCalled_ = true;
    }

    int32_t GetTotalChildCount() const override
    {
        return static_cast<int32_t>(children_.size());
    }

    const RefPtr<GeometryNode>& GetGeometryNode() const override
    {
        return geometryNode_;
    }

    const RefPtr<LayoutProperty>& GetLayoutProperty() const override
    {
        return layoutProperty_;
    }

    RefPtr<LayoutWrapper> GetOrCreateChildByIndex(uint32_t index, bool addToRenderTree, bool isCache) override
    {
        return nullptr;
    }

    RefPtr<LayoutWrapper> GetChildByIndex(uint32_t index, bool isCache) override
    {
        return nullptr;
    }

    ChildrenListWithGuard GetAllChildrenWithBuild(bool addToRenderTree = true) override
    {
        return ChildrenListWithGuard(children_, lock_);
    }

    void RemoveChildInRenderTree(uint32_t index) override {}

    void RemoveAllChildInRenderTree() override {}

    void SetActiveChildRange(int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCached) override
    {}

    void RecycleItemsByIndex(int32_t start, int32_t end) override {}

    const std::string& GetHostTag() const override
    {
        return hostTag_;
    }

    bool IsActive() const override
    {
        return active_;
    }

    void SetActive(bool active = true, bool needRebuildRenderContext = false) override
    {
        active_ = active;
    }

    void SetCacheCount(int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint) override {}

    float GetBaselineDistance() const override
    {
        return 0.0f;
    }

    bool CheckNeedForceMeasureAndLayout() override
    {
        return false;
    }

    void AddChild(const RefPtr<LayoutWrapper>& child)
    {
        children_.push_back(child);
    }

    void SetGeometry(const RefPtr<GeometryNode>& geometry)
    {
        geometryNode_ = geometry;
    }

    void SetLayoutProp(const RefPtr<LayoutProperty>& prop)
    {
        layoutProperty_ = prop;
    }

    bool layoutCalled_ = false;

private:
    std::string hostTag_;
    bool active_ = true;
    TestRecursiveLock lock_;
    std::list<RefPtr<LayoutWrapper>> children_;
    RefPtr<GeometryNode> geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutProperty> layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithm_;
};

class SmartLayoutAlgorithmFakeNode final : public ISmartLayoutNode {
public:
    explicit SmartLayoutAlgorithmFakeNode(int64_t nodeId = 0, const std::string& nodeName = "node")
        : nodeId_(nodeId), nodeName_(nodeName)
    {
        scaleInfo_.sizeScale.value = 1.0;
    }

    void SetLayoutType(SmartLayoutType type) override
    {
        context_.layoutType = type;
    }

    SmartLayoutType GetLayoutType() const override
    {
        return context_.layoutType;
    }

    void SetFixedSizeConstraints(double width, double height) override
    {
        size_.width.value = width;
        size_.height.value = height;
    }

    bool SolveLayout() override
    {
        solveCalled_ = true;
        return solveResult_;
    }

    void SyncData() override {}

    void CreateChildrenFromInfos(const std::vector<ChildLayoutInfo>& infos) override
    {
        createdInfos_ = infos;
        children_.clear();
        for (const auto& info : infos) {
            auto child = std::make_shared<SmartLayoutAlgorithmFakeNode>(info.id, "child_" + std::to_string(info.id));
            child->position_.offsetX.value = info.offsetX;
            child->position_.offsetY.value = info.offsetY;
            child->size_.width.value = info.width;
            child->size_.height.value = info.height;
            children_.push_back(child);
        }
    }

    const std::vector<std::shared_ptr<ISmartLayoutNode>>& GetChildren() const override
    {
        return children_;
    }

    void ApplyColumnConstraints() override
    {
        applyColumnCount_++;
    }

    void ApplyRowConstraints() override
    {
        applyRowCount_++;
    }

    int64_t GetNodeId() const override
    {
        return nodeId_;
    }

    const std::string& GetName() const override
    {
        return nodeName_;
    }

    const NodePosition& GetPosition() const override
    {
        return position_;
    }

    const NodeSize& GetSize() const override
    {
        return size_;
    }

    const ScaleInfo& GetScaleInfo() const override
    {
        return scaleInfo_;
    }

    SmartLayoutRect GetChildrenBoundingBox() const override
    {
        if (children_.empty()) {
            return boundingBox_;
        }
        double minX = std::numeric_limits<double>::max();
        double minY = std::numeric_limits<double>::max();
        double maxRight = std::numeric_limits<double>::lowest();
        double maxBottom = std::numeric_limits<double>::lowest();
        for (const auto& child : children_) {
            auto x = child->GetPosition().offsetX.value;
            auto y = child->GetPosition().offsetY.value;
            auto w = child->GetSize().width.value;
            auto h = child->GetSize().height.value;
            minX = std::min(minX, x);
            minY = std::min(minY, y);
            maxRight = std::max(maxRight, x + w);
            maxBottom = std::max(maxBottom, y + h);
        }
        return SmartLayoutRect(minX, minY, maxRight - minX, maxBottom - minY);
    }

    void SetAvoidSafeArea(bool avoid) override {}

    LayoutContext& GetContext() override
    {
        return context_;
    }

    void SetPosition(double x, double y)
    {
        position_.offsetX.value = x;
        position_.offsetY.value = y;
    }

    void SetNodeSize(double width, double height)
    {
        size_.width.value = width;
        size_.height.value = height;
    }

    void SetBoundingBox(const SmartLayoutRect& rect)
    {
        boundingBox_ = rect;
    }

    void SetSolveResult(bool result)
    {
        solveResult_ = result;
    }

    void SetSizeScale(double value)
    {
        scaleInfo_.sizeScale.value = value;
    }

    bool solveCalled_ = false;
    int32_t applyColumnCount_ = 0;
    int32_t applyRowCount_ = 0;
    std::vector<ChildLayoutInfo> createdInfos_;

private:
    int64_t nodeId_ = 0;
    std::string nodeName_;
    bool solveResult_ = true;
    NodePosition position_ = {};
    NodeSize size_ = {};
    ScaleInfo scaleInfo_ = {};
    LayoutContext context_;
    SmartLayoutRect boundingBox_ {};
    std::vector<std::shared_ptr<ISmartLayoutNode>> children_;
};

class SmartLayoutAlgorithmFakeEngine final : public ISmartLayoutEngine {
public:
    std::shared_ptr<ISmartLayoutNode> CreateRootNode(const std::string& name = "root") override
    {
        if (returnNullRoot_) {
            return nullptr;
        }
        if (!rootNode_) {
            rootNode_ = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, name);
        }
        return rootNode_;
    }

    bool returnNullRoot_ = false;
    std::shared_ptr<SmartLayoutAlgorithmFakeNode> rootNode_ = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");
};

class SmartLayoutEngineLoaderGuard final {
public:
    explicit SmartLayoutEngineLoaderGuard(ISmartLayoutEngine* testEngine)
        : loader_(SmartLayoutEngineLoader::GetInstance()),
          oldEngine_(loader_.engine_),
          oldLoadAttempted_(loader_.loadAttempted_.load(std::memory_order_acquire))
    {
        loader_.engine_ = testEngine;
        loader_.loadAttempted_.store(true, std::memory_order_release);
    }

    ~SmartLayoutEngineLoaderGuard()
    {
        loader_.engine_ = oldEngine_;
        loader_.loadAttempted_.store(oldLoadAttempted_, std::memory_order_release);
    }

private:
    SmartLayoutEngineLoader& loader_;
    ISmartLayoutEngine* oldEngine_ = nullptr;
    bool oldLoadAttempted_ = false;
};

RefPtr<FrameNode> CreateTestFrameNode(const std::string& tag, int32_t id)
{
    return FrameNode::CreateFrameNode(tag, id, AceType::MakeRefPtr<Pattern>());
}

} // namespace

class SmartLayoutAlgorithmTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: SmartLayoutAlgorithmTest000
 * @tc.desc: Level0 sanity test for GetLayoutTypeFromWrapper nullptr input.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest000, TestSize.Level0)
{
    SmartLayoutAlgorithm algorithm;
    EXPECT_EQ(algorithm.GetLayoutTypeFromWrapper(nullptr), SmartLayoutType::UNKNOWN);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest001
 * @tc.desc: Test GetLayoutTypeFromWrapper with nullptr and unknown tag
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest001, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    EXPECT_EQ(algorithm.GetLayoutTypeFromWrapper(nullptr), SmartLayoutType::UNKNOWN);

    auto hostNode = CreateTestFrameNode("unknown", 1);
    auto wrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(WeakPtr<FrameNode>(hostNode), "unknown");
    EXPECT_EQ(algorithm.GetLayoutTypeFromWrapper(wrapper.GetRawPtr()), SmartLayoutType::UNKNOWN);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest002
 * @tc.desc: Test GetLayoutTypeFromWrapper with column and row tags
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest002, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto hostNode1 = CreateTestFrameNode(V2::COLUMN_ETS_TAG, 2);
    auto columnWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(hostNode1), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(algorithm.GetLayoutTypeFromWrapper(columnWrapper.GetRawPtr()), SmartLayoutType::COLUMN);

    auto hostNode2 = CreateTestFrameNode(V2::ROW_ETS_TAG, 3);
    auto rowWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(hostNode2), V2::ROW_ETS_TAG);
    EXPECT_EQ(algorithm.GetLayoutTypeFromWrapper(rowWrapper.GetRawPtr()), SmartLayoutType::ROW);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest003
 * @tc.desc: Test GetLayoutTypeFromWrapper with flex tag and flex direction
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest003, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto hostNode = CreateTestFrameNode(V2::FLEX_ETS_TAG, 4);
    auto wrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(WeakPtr<FrameNode>(hostNode), V2::FLEX_ETS_TAG);

    auto flexProp = AceType::MakeRefPtr<FlexLayoutProperty>();
    flexProp->UpdateFlexDirection(FlexDirection::COLUMN_REVERSE);
    wrapper->SetLayoutProp(flexProp);
    EXPECT_EQ(algorithm.GetLayoutTypeFromWrapper(wrapper.GetRawPtr()), SmartLayoutType::COLUMN);

    flexProp->UpdateFlexDirection(FlexDirection::ROW);
    EXPECT_EQ(algorithm.GetLayoutTypeFromWrapper(wrapper.GetRawPtr()), SmartLayoutType::ROW);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest004
 * @tc.desc: Test CollectChildInfo with valid and invalid children
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest004, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto parentHost = CreateTestFrameNode(V2::ROW_ETS_TAG, 5);
    auto parentWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(parentHost), V2::ROW_ETS_TAG);

    auto childHost1 = CreateTestFrameNode(V2::BLANK_ETS_TAG, 101);
    auto childWrapper1 = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost1), V2::BLANK_ETS_TAG);
    auto geo1 = AceType::MakeRefPtr<GeometryNode>();
    geo1->SetFrameSize(SizeF(50.0f, 20.0f));
    geo1->SetFrameOffset(OffsetF(3.0f, 4.0f));
    childWrapper1->SetGeometry(geo1);

    auto childHost2 = CreateTestFrameNode(V2::TEXT_ETS_TAG, 102);
    auto childWrapper2 = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost2), V2::TEXT_ETS_TAG);
    childWrapper2->SetGeometry(nullptr);

    auto childWithoutHost = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(), V2::TEXT_ETS_TAG);

    parentWrapper->AddChild(childWrapper1);
    parentWrapper->AddChild(nullptr);
    parentWrapper->AddChild(childWrapper2);
    parentWrapper->AddChild(childWithoutHost);

    auto infos = algorithm.CollectChildInfo(parentWrapper.GetRawPtr());
    ASSERT_EQ(infos.size(), 2);

    EXPECT_EQ(infos[0].id, 101);
    EXPECT_EQ(infos[0].width, 50.0);
    EXPECT_EQ(infos[0].height, 20.0);
    EXPECT_EQ(infos[0].offsetX, 3.0);
    EXPECT_EQ(infos[0].offsetY, 4.0);
    EXPECT_TRUE(infos[0].isBlank);

    EXPECT_EQ(infos[1].id, 102);
    EXPECT_EQ(infos[1].width, 0.0);
    EXPECT_EQ(infos[1].height, 0.0);
    EXPECT_FALSE(infos[1].isBlank);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest005
 * @tc.desc: Test InitializeLayoutContext with empty children
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest005, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    algorithm.rootNode_ = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");

    auto host = CreateTestFrameNode(V2::ROW_ETS_TAG, 6);
    auto wrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(WeakPtr<FrameNode>(host), V2::ROW_ETS_TAG);

    EXPECT_FALSE(algorithm.InitializeLayoutContext(wrapper.GetRawPtr()));
}

/**
 * @tc.name: SmartLayoutAlgorithmTest006
 * @tc.desc: Test InitializeLayoutContext with geometry and flex property
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest006, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto root = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");
    algorithm.rootNode_ = root;

    auto host = CreateTestFrameNode(V2::FLEX_ETS_TAG, 7);
    auto wrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(WeakPtr<FrameNode>(host), V2::FLEX_ETS_TAG);

    auto parentGeo = AceType::MakeRefPtr<GeometryNode>();
    parentGeo->SetFrameSize(SizeF(300.0f, 200.0f));
    wrapper->SetGeometry(parentGeo);

    auto flexProp = AceType::MakeRefPtr<FlexLayoutProperty>();
    flexProp->UpdateMainAxisAlign(FlexAlign::FLEX_END);
    flexProp->UpdateCrossAxisAlign(FlexAlign::CENTER);
    wrapper->SetLayoutProp(flexProp);

    auto childHost = CreateTestFrameNode(V2::TEXT_ETS_TAG, 701);
    auto childWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost), V2::TEXT_ETS_TAG);
    wrapper->AddChild(childWrapper);

    EXPECT_TRUE(algorithm.InitializeLayoutContext(wrapper.GetRawPtr()));
    EXPECT_EQ(root->GetContext().size.Width(), 300.0);
    EXPECT_EQ(root->GetContext().size.Height(), 200.0);
    EXPECT_EQ(root->GetContext().mainAxisAlign, SmartLayoutAlign::FLEX_END);
    EXPECT_EQ(root->GetContext().crossAxisAlign, SmartLayoutAlign::CENTER);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest007
 * @tc.desc: Test InitializeLayoutContext with nullptr geometry
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest007, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto root = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");
    algorithm.rootNode_ = root;

    auto host = CreateTestFrameNode(V2::ROW_ETS_TAG, 8);
    auto wrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(WeakPtr<FrameNode>(host), V2::ROW_ETS_TAG);
    wrapper->SetGeometry(nullptr);
    wrapper->SetLayoutProp(nullptr);

    auto childHost = CreateTestFrameNode(V2::TEXT_ETS_TAG, 801);
    auto childWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost), V2::TEXT_ETS_TAG);
    wrapper->AddChild(childWrapper);

    EXPECT_TRUE(algorithm.InitializeLayoutContext(wrapper.GetRawPtr()));
    EXPECT_EQ(root->GetContext().size.Width(), 0.0);
    EXPECT_EQ(root->GetContext().size.Height(), 0.0);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest008
 * @tc.desc: Test CalculateOffsetWithMargin in row, column and unknown modes
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest008, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto root = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");
    root->SetNodeSize(200.0, 100.0);
    root->SetBoundingBox(SmartLayoutRect(10.0, 20.0, 80.0, 40.0));
    algorithm.rootNode_ = root;

    SmartLayoutAlgorithmFakeNode child(1, "child");
    child.SetPosition(5.0, 7.0);

    root->SetLayoutType(SmartLayoutType::ROW);
    auto offsetRow = algorithm.CalculateOffsetWithMargin(child, nullptr, 50.0, 10.0);
    EXPECT_FLOAT_EQ(offsetRow.GetX(), 5.0f);
    EXPECT_FLOAT_EQ(offsetRow.GetY(), 17.0f);

    root->SetLayoutType(SmartLayoutType::COLUMN);
    auto offsetColumn = algorithm.CalculateOffsetWithMargin(child, nullptr, 50.0, 10.0);
    EXPECT_FLOAT_EQ(offsetColumn.GetX(), 55.0f);
    EXPECT_FLOAT_EQ(offsetColumn.GetY(), 7.0f);

    root->SetLayoutType(SmartLayoutType::UNKNOWN);
    auto offsetUnknown = algorithm.CalculateOffsetWithMargin(child, nullptr, 50.0, 10.0);
    EXPECT_FLOAT_EQ(offsetUnknown.GetX(), 5.0f);
    EXPECT_FLOAT_EQ(offsetUnknown.GetY(), 7.0f);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest009
 * @tc.desc: Test ExecuteLayout returns when layoutWrapper is nullptr or type unknown
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest009, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    algorithm.ExecuteLayout(nullptr, SmartLayoutType::ROW);
    algorithm.ExecuteLayout(nullptr, SmartLayoutType::UNKNOWN);
    EXPECT_EQ(algorithm.rootNode_, nullptr);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest010
 * @tc.desc: Test ExecuteLayout returns when engine is unavailable
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest010, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto host = CreateTestFrameNode(V2::ROW_ETS_TAG, 10);
    auto wrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(WeakPtr<FrameNode>(host), V2::ROW_ETS_TAG);

    SmartLayoutEngineLoaderGuard guard(nullptr);
    algorithm.ExecuteLayout(wrapper.GetRawPtr(), SmartLayoutType::ROW);
    EXPECT_EQ(algorithm.rootNode_, nullptr);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest011
 * @tc.desc: Test ExecuteLayout returns when CreateRootNode returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest011, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto host = CreateTestFrameNode(V2::ROW_ETS_TAG, 11);
    auto wrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(WeakPtr<FrameNode>(host), V2::ROW_ETS_TAG);

    auto* engine = new SmartLayoutAlgorithmFakeEngine();
    engine->returnNullRoot_ = true;
    {
        SmartLayoutEngineLoaderGuard guard(engine);
        algorithm.ExecuteLayout(wrapper.GetRawPtr(), SmartLayoutType::ROW);
    }
    delete engine;
    EXPECT_EQ(algorithm.rootNode_, nullptr);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest012
 * @tc.desc: Test ExecuteLayout in ROW path with successful solve and result apply
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest012, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto parentHost = CreateTestFrameNode(V2::ROW_ETS_TAG, 12);
    auto parentWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(parentHost), V2::ROW_ETS_TAG);

    auto parentGeo = AceType::MakeRefPtr<GeometryNode>();
    parentGeo->SetFrameSize(SizeF(200.0f, 100.0f));
    parentWrapper->SetGeometry(parentGeo);
    parentWrapper->SetLayoutProp(AceType::MakeRefPtr<LayoutProperty>());

    auto childHost1 = CreateTestFrameNode(V2::TEXT_ETS_TAG, 1201);
    auto childWrapper1 = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost1), V2::TEXT_ETS_TAG);
    auto childGeo1 = AceType::MakeRefPtr<GeometryNode>();
    childGeo1->SetFrameSize(SizeF(20.0f, 10.0f));
    childGeo1->SetFrameOffset(OffsetF(0.0f, 0.0f));
    childWrapper1->SetGeometry(childGeo1);

    auto childHost2 = CreateTestFrameNode(V2::BLANK_ETS_TAG, 1202);
    auto childWrapper2 = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost2), V2::BLANK_ETS_TAG);
    auto childGeo2 = AceType::MakeRefPtr<GeometryNode>();
    childGeo2->SetFrameSize(SizeF(30.0f, 10.0f));
    childGeo2->SetFrameOffset(OffsetF(40.0f, 20.0f));
    childWrapper2->SetGeometry(childGeo2);

    parentWrapper->AddChild(childWrapper1);
    parentWrapper->AddChild(childWrapper2);

    auto* engine = new SmartLayoutAlgorithmFakeEngine();
    engine->rootNode_->SetSolveResult(true);
    engine->rootNode_->SetSizeScale(1.5);

    {
        SmartLayoutEngineLoaderGuard guard(engine);
        algorithm.ExecuteLayout(parentWrapper.GetRawPtr(), SmartLayoutType::ROW);
    }

    ASSERT_NE(algorithm.rootNode_, nullptr);
    auto root = std::static_pointer_cast<SmartLayoutAlgorithmFakeNode>(algorithm.rootNode_);
    EXPECT_EQ(root->applyColumnCount_, 0);
    EXPECT_EQ(root->applyRowCount_, 1);
    EXPECT_TRUE(root->solveCalled_);
    ASSERT_EQ(root->createdInfos_.size(), 2);
    EXPECT_FALSE(root->createdInfos_[0].isBlank);
    EXPECT_TRUE(root->createdInfos_[1].isBlank);
    EXPECT_TRUE(childWrapper1->layoutCalled_);
    EXPECT_TRUE(childWrapper2->layoutCalled_);
    EXPECT_GT(childGeo1->GetFrameOffset().GetY(), 0.0f);

    delete engine;
}

/**
 * @tc.name: SmartLayoutAlgorithmTest013
 * @tc.desc: Test ExecuteLayout in COLUMN path with solve failure
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest013, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto parentHost = CreateTestFrameNode(V2::COLUMN_ETS_TAG, 13);
    auto parentWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(parentHost), V2::COLUMN_ETS_TAG);
    auto parentGeo = AceType::MakeRefPtr<GeometryNode>();
    parentGeo->SetFrameSize(SizeF(180.0f, 160.0f));
    parentWrapper->SetGeometry(parentGeo);

    auto childHost = CreateTestFrameNode(V2::TEXT_ETS_TAG, 1301);
    auto childWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost), V2::TEXT_ETS_TAG);
    auto childGeo = AceType::MakeRefPtr<GeometryNode>();
    childGeo->SetFrameSize(SizeF(20.0f, 15.0f));
    childGeo->SetFrameOffset(OffsetF(5.0f, 8.0f));
    childWrapper->SetGeometry(childGeo);
    parentWrapper->AddChild(childWrapper);

    auto* engine = new SmartLayoutAlgorithmFakeEngine();
    engine->rootNode_->SetSolveResult(false);
    {
        SmartLayoutEngineLoaderGuard guard(engine);
        algorithm.ExecuteLayout(parentWrapper.GetRawPtr(), SmartLayoutType::COLUMN);
    }

    ASSERT_NE(algorithm.rootNode_, nullptr);
    auto root = std::static_pointer_cast<SmartLayoutAlgorithmFakeNode>(algorithm.rootNode_);
    EXPECT_EQ(root->applyColumnCount_, 1);
    EXPECT_EQ(root->applyRowCount_, 0);
    EXPECT_TRUE(root->solveCalled_);
    EXPECT_FALSE(childWrapper->layoutCalled_);

    delete engine;
}

/**
 * @tc.name: SmartLayoutAlgorithmTest014
 * @tc.desc: Test ApplyChildLayout branch with missing node map entry
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest014, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto root = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");
    root->SetLayoutType(SmartLayoutType::ROW);
    root->SetNodeSize(100.0, 60.0);
    root->SetBoundingBox(SmartLayoutRect(0.0, 0.0, 20.0, 20.0));
    algorithm.rootNode_ = root;

    auto childHost = CreateTestFrameNode(V2::TEXT_ETS_TAG, 1401);
    auto childWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost), V2::TEXT_ETS_TAG);
    auto geo = AceType::MakeRefPtr<GeometryNode>();
    geo->SetFrameOffset(OffsetF(1.0f, 2.0f));
    childWrapper->SetGeometry(geo);

    std::unordered_map<int64_t, std::shared_ptr<ISmartLayoutNode>> emptyNodeMap;
    algorithm.ApplyChildLayout(childWrapper, emptyNodeMap, 1.0, 0.0, 0.0);
    EXPECT_FALSE(childWrapper->layoutCalled_);
    EXPECT_FLOAT_EQ(geo->GetFrameOffset().GetX(), 1.0f);
    EXPECT_FLOAT_EQ(geo->GetFrameOffset().GetY(), 2.0f);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest015
 * @tc.desc: Test ApplyChildLayout branch with nullptr geometry
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest015, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto root = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");
    root->SetLayoutType(SmartLayoutType::ROW);
    root->SetNodeSize(100.0, 60.0);
    root->SetBoundingBox(SmartLayoutRect(0.0, 0.0, 20.0, 20.0));
    algorithm.rootNode_ = root;

    auto mappedNode = std::make_shared<SmartLayoutAlgorithmFakeNode>(1501, "mapped");
    mappedNode->SetPosition(3.0, 6.0);
    mappedNode->SetNodeSize(10.0, 10.0);
    std::unordered_map<int64_t, std::shared_ptr<ISmartLayoutNode>> nodeMap;
    nodeMap[1501] = mappedNode;

    auto childHost = CreateTestFrameNode(V2::TEXT_ETS_TAG, 1501);
    auto childWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost), V2::TEXT_ETS_TAG);
    childWrapper->SetGeometry(nullptr);

    algorithm.ApplyChildLayout(childWrapper, nodeMap, 1.0, 0.0, 0.0);
    EXPECT_FALSE(childWrapper->layoutCalled_);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest016
 * @tc.desc: Test ApplyLayoutResults with nullptr and empty root children
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest016, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    algorithm.ApplyLayoutResults(nullptr);

    auto root = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");
    algorithm.rootNode_ = root;
    auto parentHost = CreateTestFrameNode(V2::ROW_ETS_TAG, TEST_HOST_NODE_ID);
    auto parentWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(parentHost), V2::ROW_ETS_TAG);
    auto childHost = CreateTestFrameNode(V2::TEXT_ETS_TAG, TEST_CHILD_NODE_ID);
    auto childWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost), V2::TEXT_ETS_TAG);
    parentWrapper->AddChild(childWrapper);
    algorithm.ApplyLayoutResults(parentWrapper.GetRawPtr());
    EXPECT_FALSE(childWrapper->layoutCalled_);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest017
 * @tc.desc: Test PerformSmartLayout triggers auto type detection and execute
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest017, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto host = CreateTestFrameNode(V2::ROW_ETS_TAG, 17);
    auto wrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(WeakPtr<FrameNode>(host), V2::ROW_ETS_TAG);
    auto geo = AceType::MakeRefPtr<GeometryNode>();
    geo->SetFrameSize(SizeF(TEST_PARENT_WIDTH, TEST_PERFORM_PARENT_HEIGHT));
    wrapper->SetGeometry(geo);

    auto childHost = CreateTestFrameNode(V2::TEXT_ETS_TAG, 1701);
    auto childWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost), V2::TEXT_ETS_TAG);
    auto childGeo = AceType::MakeRefPtr<GeometryNode>();
    childGeo->SetFrameSize(SizeF(10.0f, 10.0f));
    childGeo->SetFrameOffset(OffsetF(2.0f, 3.0f));
    childWrapper->SetGeometry(childGeo);
    wrapper->AddChild(childWrapper);

    auto* engine = new SmartLayoutAlgorithmFakeEngine();
    engine->rootNode_->SetSolveResult(true);
    {
        SmartLayoutEngineLoaderGuard guard(engine);
        algorithm.PerformSmartLayout(wrapper.GetRawPtr());
    }

    ASSERT_NE(algorithm.rootNode_, nullptr);
    auto root = std::static_pointer_cast<SmartLayoutAlgorithmFakeNode>(algorithm.rootNode_);
    EXPECT_EQ(root->GetLayoutType(), SmartLayoutType::ROW);
    EXPECT_EQ(root->applyRowCount_, 1);
    EXPECT_TRUE(root->solveCalled_);
    EXPECT_TRUE(childWrapper->layoutCalled_);

    delete engine;
}

/**
 * @tc.name: SmartLayoutAlgorithmTest018
 * @tc.desc: Test ApplyChildLayout with nullptr child wrapper
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest018, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto root = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");
    root->SetLayoutType(SmartLayoutType::ROW);
    root->SetNodeSize(100.0, 60.0);
    root->SetBoundingBox(SmartLayoutRect(0.0, 0.0, 20.0, 20.0));
    algorithm.rootNode_ = root;

    std::unordered_map<int64_t, std::shared_ptr<ISmartLayoutNode>> nodeMap;
    algorithm.ApplyChildLayout(nullptr, nodeMap, 1.0, 0.0, 0.0);
    EXPECT_TRUE(nodeMap.empty());
    EXPECT_TRUE(root->GetChildren().empty());
    EXPECT_TRUE(root->createdInfos_.empty());
}

/**
 * @tc.name: SmartLayoutAlgorithmTest019
 * @tc.desc: Test ApplyChildLayout with wrapper that has no host node
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest019, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto root = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");
    root->SetLayoutType(SmartLayoutType::ROW);
    root->SetNodeSize(100.0, 60.0);
    root->SetBoundingBox(SmartLayoutRect(0.0, 0.0, 20.0, 20.0));
    algorithm.rootNode_ = root;

    auto wrapperWithoutHost = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(), V2::TEXT_ETS_TAG);
    std::unordered_map<int64_t, std::shared_ptr<ISmartLayoutNode>> nodeMap;
    algorithm.ApplyChildLayout(wrapperWithoutHost, nodeMap, 1.0, 0.0, 0.0);
    EXPECT_FALSE(wrapperWithoutHost->layoutCalled_);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest020
 * @tc.desc: Test GetLayoutTypeFromWrapper flex branch without layout property
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest020, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto hostNode = CreateTestFrameNode(V2::FLEX_ETS_TAG, 20);
    auto wrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(WeakPtr<FrameNode>(hostNode), V2::FLEX_ETS_TAG);
    wrapper->SetLayoutProp(nullptr);
    EXPECT_EQ(algorithm.GetLayoutTypeFromWrapper(wrapper.GetRawPtr()), SmartLayoutType::ROW);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest021
 * @tc.desc: Test InitializeLayoutContext maps FLEX_START to SmartLayoutAlign::FLEX_START
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest021, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto root = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");
    algorithm.rootNode_ = root;

    auto host = CreateTestFrameNode(V2::FLEX_ETS_TAG, 21);
    auto wrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(WeakPtr<FrameNode>(host), V2::FLEX_ETS_TAG);

    auto parentGeo = AceType::MakeRefPtr<GeometryNode>();
    parentGeo->SetFrameSize(SizeF(TEST_PARENT_WIDTH, TEST_PARENT_HEIGHT));
    wrapper->SetGeometry(parentGeo);

    auto flexProp = AceType::MakeRefPtr<FlexLayoutProperty>();
    flexProp->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    flexProp->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    wrapper->SetLayoutProp(flexProp);

    auto childHost = CreateTestFrameNode(V2::TEXT_ETS_TAG, 2101);
    auto childWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost), V2::TEXT_ETS_TAG);
    wrapper->AddChild(childWrapper);

    EXPECT_TRUE(algorithm.InitializeLayoutContext(wrapper.GetRawPtr()));
    EXPECT_EQ(root->GetContext().mainAxisAlign, SmartLayoutAlign::FLEX_START);
    EXPECT_EQ(root->GetContext().crossAxisAlign, SmartLayoutAlign::FLEX_START);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest022
 * @tc.desc: Test InitializeLayoutContext convert default branch with invalid FlexAlign value
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest022, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto root = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");
    algorithm.rootNode_ = root;

    auto host = CreateTestFrameNode(V2::FLEX_ETS_TAG, 22);
    auto wrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(WeakPtr<FrameNode>(host), V2::FLEX_ETS_TAG);

    auto parentGeo = AceType::MakeRefPtr<GeometryNode>();
    parentGeo->SetFrameSize(SizeF(100.0f, 80.0f));
    wrapper->SetGeometry(parentGeo);

    auto flexProp = AceType::MakeRefPtr<FlexLayoutProperty>();
    flexProp->UpdateMainAxisAlign(static_cast<FlexAlign>(INVALID_MAIN_ALIGN));
    flexProp->UpdateCrossAxisAlign(static_cast<FlexAlign>(INVALID_CROSS_ALIGN));
    wrapper->SetLayoutProp(flexProp);

    auto childHost = CreateTestFrameNode(V2::TEXT_ETS_TAG, 2201);
    auto childWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost), V2::TEXT_ETS_TAG);
    wrapper->AddChild(childWrapper);

    EXPECT_TRUE(algorithm.InitializeLayoutContext(wrapper.GetRawPtr()));
    EXPECT_EQ(root->GetContext().mainAxisAlign, SmartLayoutAlign::FLEX_START);
    EXPECT_EQ(root->GetContext().crossAxisAlign, SmartLayoutAlign::FLEX_START);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest023
 * @tc.desc: Test CollectChildInfo with nullptr layoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest023, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto infos = algorithm.CollectChildInfo(nullptr);
    EXPECT_TRUE(infos.empty());
}

/**
 * @tc.name: SmartLayoutAlgorithmTest024
 * @tc.desc: Test ProcessLayoutChildren returns when childInfos is empty
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest024, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto root = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");
    algorithm.rootNode_ = root;
    ChildLayoutInfo seedInfo;
    seedInfo.id = 1;
    root->createdInfos_.push_back(seedInfo);

    auto host = CreateTestFrameNode(V2::ROW_ETS_TAG, 24);
    auto wrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(WeakPtr<FrameNode>(host), V2::ROW_ETS_TAG);
    algorithm.ProcessLayoutChildren(wrapper.GetRawPtr());

    EXPECT_EQ(root->createdInfos_.size(), 1);
    EXPECT_EQ(root->createdInfos_[0].id, 1);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest025
 * @tc.desc: Test BuildNodeIdMap skips nullptr child
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest025, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    std::vector<std::shared_ptr<ISmartLayoutNode>> children;
    children.emplace_back(nullptr);
    children.emplace_back(std::make_shared<SmartLayoutAlgorithmFakeNode>(2501, "child_2501"));

    auto nodeMap = algorithm.BuildNodeIdMap(children);
    EXPECT_EQ(nodeMap.size(), 1);
    EXPECT_EQ(nodeMap.count(2501), 1);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest026
 * @tc.desc: Test ApplyLayoutResults returns when rootNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest026, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto host = CreateTestFrameNode(V2::ROW_ETS_TAG, TEST_NULL_ROOT_HOST_NODE_ID);
    auto wrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(WeakPtr<FrameNode>(host), V2::ROW_ETS_TAG);
    auto childHost = CreateTestFrameNode(V2::TEXT_ETS_TAG, TEST_NULL_ROOT_CHILD_NODE_ID);
    auto childWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost), V2::TEXT_ETS_TAG);
    wrapper->AddChild(childWrapper);
    algorithm.rootNode_ = nullptr;
    algorithm.ApplyLayoutResults(wrapper.GetRawPtr());
    EXPECT_FALSE(childWrapper->layoutCalled_);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest027
 * @tc.desc: Test InitializeLayoutContext with nullptr layoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest027, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    algorithm.rootNode_ = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");
    EXPECT_FALSE(algorithm.InitializeLayoutContext(nullptr));
}

/**
 * @tc.name: SmartLayoutAlgorithmTest028
 * @tc.desc: Test InitializeLayoutContext keeps default align when layout property is not FlexLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest028, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto root = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");
    algorithm.rootNode_ = root;

    auto host = CreateTestFrameNode(V2::ROW_ETS_TAG, TEST_NON_FLEX_LAYOUT_HOST_NODE_ID);
    auto wrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(WeakPtr<FrameNode>(host), V2::ROW_ETS_TAG);
    auto parentGeo = AceType::MakeRefPtr<GeometryNode>();
    parentGeo->SetFrameSize(SizeF(TEST_PARENT_WIDTH, TEST_PARENT_HEIGHT));
    wrapper->SetGeometry(parentGeo);
    wrapper->SetLayoutProp(AceType::MakeRefPtr<LayoutProperty>());

    auto childHost = CreateTestFrameNode(V2::TEXT_ETS_TAG, TEST_NON_FLEX_CHILD_NODE_ID);
    auto childWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost), V2::TEXT_ETS_TAG);
    wrapper->AddChild(childWrapper);

    ASSERT_TRUE(algorithm.InitializeLayoutContext(wrapper.GetRawPtr()));
    EXPECT_EQ(root->GetContext().mainAxisAlign, SmartLayoutAlign::FLEX_START);
    EXPECT_EQ(root->GetContext().crossAxisAlign, SmartLayoutAlign::CENTER);
    EXPECT_EQ(root->GetContext().size.Width(), TEST_PARENT_WIDTH);
    EXPECT_EQ(root->GetContext().size.Height(), TEST_PARENT_HEIGHT);
}

/**
 * @tc.name: SmartLayoutAlgorithmTest029
 * @tc.desc: Test InitializeLayoutContext uses default FlexAlign values when flex property has no explicit align.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutAlgorithmTest, SmartLayoutAlgorithmTest029, TestSize.Level1)
{
    SmartLayoutAlgorithm algorithm;
    auto root = std::make_shared<SmartLayoutAlgorithmFakeNode>(0, "root");
    algorithm.rootNode_ = root;

    auto host = CreateTestFrameNode(V2::FLEX_ETS_TAG, TEST_FLEX_DEFAULT_HOST_NODE_ID);
    auto wrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(WeakPtr<FrameNode>(host), V2::FLEX_ETS_TAG);
    auto parentGeo = AceType::MakeRefPtr<GeometryNode>();
    parentGeo->SetFrameSize(SizeF(TEST_PARENT_WIDTH, TEST_PARENT_HEIGHT));
    wrapper->SetGeometry(parentGeo);

    auto flexProp = AceType::MakeRefPtr<FlexLayoutProperty>();
    wrapper->SetLayoutProp(flexProp);

    auto childHost = CreateTestFrameNode(V2::TEXT_ETS_TAG, TEST_FLEX_DEFAULT_CHILD_NODE_ID);
    auto childWrapper = AceType::MakeRefPtr<SmartLayoutAlgorithmTestWrapper>(
        WeakPtr<FrameNode>(childHost), V2::TEXT_ETS_TAG);
    wrapper->AddChild(childWrapper);

    ASSERT_TRUE(algorithm.InitializeLayoutContext(wrapper.GetRawPtr()));
    EXPECT_EQ(root->GetContext().mainAxisAlign, SmartLayoutAlign::FLEX_START);
    EXPECT_EQ(root->GetContext().crossAxisAlign, SmartLayoutAlign::CENTER);
}

} // namespace OHOS::Ace::NG
