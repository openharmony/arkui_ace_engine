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
#include "accessor_test_base.h"
#include "core/interfaces/native/implementation/layoutable_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

const int32_t CHILD_NODE_ID = 117;
const int32_t FRAME_WIDTH = 12;
const int32_t FRAME_HEIGHT = 13;

class MockLayoutWrapperChild;

class MockLayoutPropertyChild : public LayoutProperty {
public:
    MockLayoutPropertyChild() = default;
    ~MockLayoutPropertyChild() override = default;
    MOCK_METHOD(void, UpdateCalcMinSize, (const CalcSize& value), (override));
    MOCK_METHOD(void, UpdateCalcMaxSize, (const CalcSize& value), (override));
};

class MockLayoutWrapperParent : public LayoutWrapper {
public:
    explicit MockLayoutWrapperParent(WeakPtr<FrameNode> hostNode) : LayoutWrapper(std::move(hostNode))
    {
        childFrameNode_ = AceType::MakeRefPtr<FrameNode>("CHILD_TEST", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
        childLayoutWrapper_ = AceType::MakeRefPtr<MockLayoutWrapperChild>(childFrameNode_);
        layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    }
    ~MockLayoutWrapperParent() override = default;

    MOCK_METHOD(const RefPtr<LayoutAlgorithmWrapper>&, GetLayoutAlgorithm, (bool needReset), (override));
    MOCK_METHOD(void, Measure, (const std::optional<LayoutConstraintF>& parentConstraint), (override));
    MOCK_METHOD(void, Layout, (), (override));
    int32_t GetTotalChildCount() const override
    {
        return 1;
    }
    MOCK_METHOD(const RefPtr<GeometryNode>&, GetGeometryNode, (), (const, override));
    const RefPtr<LayoutProperty>& GetLayoutProperty() const override
    {
        return layoutProperty_;
    }
    RefPtr<LayoutWrapper> GetOrCreateChildByIndex(uint32_t index, bool addToRenderTree, bool isCache) override
    {
        return childLayoutWrapper_;
    }
    MOCK_METHOD(RefPtr<LayoutWrapper>, GetChildByIndex, (uint32_t index, bool isCache), (override));
    MOCK_METHOD(ChildrenListWithGuard, GetAllChildrenWithBuild, (bool addToRenderTree), (override));
    MOCK_METHOD(void, RemoveChildInRenderTree, (uint32_t index), (override));
    MOCK_METHOD(void, RemoveAllChildInRenderTree, (), (override));
    MOCK_METHOD(void, SetActiveChildRange,
        (int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCached), (override));
    MOCK_METHOD(void, RecycleItemsByIndex, (int32_t start, int32_t end), (override));
    MOCK_METHOD(const std::string&, GetHostTag, (), (const, override));
    MOCK_METHOD(bool, IsActive, (), (const, override));
    MOCK_METHOD(void, SetActive, (bool active, bool needRebuildRenderContext), (override));
    MOCK_METHOD(
        void, SetCacheCount, (int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint), (override));
    MOCK_METHOD(float, GetBaselineDistance, (), (const, override));
    MOCK_METHOD(bool, CheckNeedForceMeasureAndLayout, (), (override));
public:
    RefPtr<FrameNode> childFrameNode_;
    RefPtr<MockLayoutWrapperChild> childLayoutWrapper_;
    RefPtr<LayoutProperty> layoutProperty_;
};

class MockLayoutWrapperChild : public LayoutWrapper {
public:
    explicit MockLayoutWrapperChild(WeakPtr<FrameNode> hostNode) : LayoutWrapper(hostNode)
    {
        layoutProperty_ = AceType::MakeRefPtr<MockLayoutPropertyChild>();
        layoutProperty_->SetHost(hostNode);
        geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    }
    ~MockLayoutWrapperChild() override = default;

    MOCK_METHOD(const RefPtr<LayoutAlgorithmWrapper>&, GetLayoutAlgorithm, (bool needReset), (override));
    void Measure(const std::optional<LayoutConstraintF>& parentConstraint) override
    {
        geometryNode_->SetFrameWidth(FRAME_WIDTH);
        geometryNode_->SetFrameHeight(FRAME_HEIGHT);
    }
    MOCK_METHOD(void, Layout, (), (override));
    MOCK_METHOD(int32_t, GetTotalChildCount, (), (const, override));
    const RefPtr<GeometryNode>& GetGeometryNode() const override
    {
        return geometryNode_;
    }
    const RefPtr<LayoutProperty>& GetLayoutProperty() const override
    {
        return layoutProperty_;
    }
    MOCK_METHOD(RefPtr<LayoutWrapper>, GetOrCreateChildByIndex, (uint32_t index, bool addToRenderTree, bool isCache),
        (override));
    MOCK_METHOD(RefPtr<LayoutWrapper>, GetChildByIndex, (uint32_t index, bool isCache), (override));
    MOCK_METHOD(ChildrenListWithGuard, GetAllChildrenWithBuild, (bool addToRenderTree), (override));
    MOCK_METHOD(void, RemoveChildInRenderTree, (uint32_t index), (override));
    MOCK_METHOD(void, RemoveAllChildInRenderTree, (), (override));
    MOCK_METHOD(void, SetActiveChildRange,
        (int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCached), (override));
    MOCK_METHOD(void, RecycleItemsByIndex, (int32_t start, int32_t end), (override));
    MOCK_METHOD(const std::string&, GetHostTag, (), (const, override));
    MOCK_METHOD(bool, IsActive, (), (const, override));
    MOCK_METHOD(void, SetActive, (bool active, bool needRebuildRenderContext), (override));
    MOCK_METHOD(
        void, SetCacheCount, (int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint), (override));
    MOCK_METHOD(float, GetBaselineDistance, (), (const, override));
    MOCK_METHOD(bool, CheckNeedForceMeasureAndLayout, (), (override));
public:
    RefPtr<LayoutProperty> layoutProperty_;
    RefPtr<GeometryNode> geometryNode_;

    MockLayoutPropertyChild* GetMockLayoutProperty()
    {
        return reinterpret_cast<MockLayoutPropertyChild*>(layoutProperty_.GetRawPtr());
    }
};

class LayoutableAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUILayoutableAccessor,
        &GENERATED_ArkUIAccessors::getLayoutableAccessor, LayoutablePeer> {
public:
    void* CreatePeerInstance() override
    {
        auto peer = PeerUtils::CreatePeer<LayoutablePeer>();
        frameNode_ = AceType::MakeRefPtr<FrameNode>("TEST", 0, AceType::MakeRefPtr<Pattern>());
        layoutWrapper_ = AceType::MakeRefPtr<MockLayoutWrapperParent>(frameNode_);
        peer->measureLayoutParam = AceType::MakeRefPtr<MeasureLayoutParam>(layoutWrapper_.GetRawPtr());
        return peer;
    }

    RefPtr<FrameNode> frameNode_;
    RefPtr<MockLayoutWrapperParent> layoutWrapper_;
};

/**
 * @tc.name: LayoutTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutableAccessorTest, LayoutTest, TestSize.Level1)
{
    Ark_Position position {
        .x = Converter::ArkValue<Opt_Length>("70vp"),
        .y = Converter::ArkValue<Opt_Length>("80.25vp"),
    };
    layoutWrapper_->childLayoutWrapper_->geometryNode_->UpdateMargin({});

    EXPECT_CALL(*layoutWrapper_->childLayoutWrapper_, Layout()).Times(1);
    accessor_->layout(peer_, &position);

    OffsetF offset = layoutWrapper_->childLayoutWrapper_->geometryNode_->GetFrameOffset(false);
    EXPECT_FLOAT_EQ(offset.GetX(), 70.0f);
    EXPECT_FLOAT_EQ(offset.GetY(), 80.25f);
}

/**
 * @tc.name: GetMarginTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutableAccessorTest, GetMarginTest, TestSize.Level1)
{
    MarginProperty margin = {
        .top = CalcLength(70.0f, DimensionUnit::VP),
        .bottom = CalcLength(100.0f, DimensionUnit::VP),
        .left = CalcLength(40.0f, DimensionUnit::VP),
        .right = CalcLength(60.25f, DimensionUnit::VP),
    };
    layoutWrapper_->childLayoutWrapper_->GetMockLayoutProperty()->UpdateMargin(margin);
    Ark_DirectionalEdgesT result = accessor_->getMargin(peer_);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.top), 70.0f);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.bottom), 100.0f);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.start), 40.0f);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.end), 60.25f);
}

/**
 * @tc.name: GetMarginTestRTL
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutableAccessorTest, GetMarginTestRTL, TestSize.Level1)
{
    MarginProperty margin = {
        .left = CalcLength(40.0f, DimensionUnit::VP),
        .right = CalcLength(60.25f, DimensionUnit::VP),
    };
    layoutWrapper_->childLayoutWrapper_->GetMockLayoutProperty()->UpdateLayoutDirection(TextDirection::RTL);
    layoutWrapper_->childLayoutWrapper_->GetMockLayoutProperty()->UpdateMargin(margin);
    Ark_DirectionalEdgesT result = accessor_->getMargin(peer_);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.end), 40.0f);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.start), 60.25f);
}

/**
 * @tc.name: GetPaddingTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutableAccessorTest, GetPaddingTest, TestSize.Level1)
{
    PaddingProperty padding = {
        .top = CalcLength(70.0f, DimensionUnit::VP),
        .bottom = CalcLength(100.0f, DimensionUnit::VP),
        .left = CalcLength(40.0f, DimensionUnit::VP),
        .right = CalcLength(60.25f, DimensionUnit::VP),
    };
    layoutWrapper_->childLayoutWrapper_->GetMockLayoutProperty()->UpdatePadding(padding);
    Ark_DirectionalEdgesT result = accessor_->getPadding(peer_);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.top), 70.0f);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.bottom), 100.0f);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.start), 40.0f);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.end), 60.25f);
}

/**
 * @tc.name: GetBorderWidthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutableAccessorTest, GetBorderWidthTest, TestSize.Level1)
{
    BorderWidthProperty borderWidth = {
        .topDimen = Dimension(6.0, DimensionUnit::VP),
        .bottomDimen = Dimension(4.0, DimensionUnit::VP),
        .leftDimen = Dimension(10.0, DimensionUnit::VP),
        .rightDimen = Dimension(3.5, DimensionUnit::VP),
    };
    layoutWrapper_->childLayoutWrapper_->GetMockLayoutProperty()->UpdateBorderWidth(borderWidth);
    Ark_DirectionalEdgesT result = accessor_->getBorderWidth(peer_);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.top), 6.0f);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.bottom), 4.0f);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.start), 10.0f);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.end), 3.5f);
}

/**
 * @tc.name: GetBorderWidthTestRTL
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutableAccessorTest, GetBorderWidthTestRTL, TestSize.Level1)
{
    BorderWidthProperty borderWidth = {
        .leftDimen = Dimension(10.0, DimensionUnit::VP),
        .rightDimen = Dimension(3.5, DimensionUnit::VP),
    };
    layoutWrapper_->childLayoutWrapper_->GetMockLayoutProperty()->UpdateLayoutDirection(TextDirection::RTL);
    layoutWrapper_->childLayoutWrapper_->GetMockLayoutProperty()->UpdateBorderWidth(borderWidth);
    Ark_DirectionalEdgesT result = accessor_->getBorderWidth(peer_);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.end), 10.0f);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(result.start), 3.5f);
}

/**
 * @tc.name: GetMeasureResultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutableAccessorTest, GetMeasureResultTest, TestSize.Level1)
{
    layoutWrapper_->childLayoutWrapper_->Measure({});
    Ark_MeasureResult measureResult = accessor_->getMeasureResult(peer_);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(measureResult.width), 12.0f);
    EXPECT_FLOAT_EQ(Converter::Convert<float>(measureResult.height), 13.0f);
}

/**
 * @tc.name: GetUniqueIdTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutableAccessorTest, GetUniqueIdTest, TestSize.Level1)
{
    Opt_Number id = accessor_->getUniqueId(peer_);
    auto res = Converter::OptConvert<int32_t>(id);
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(res.value(), CHILD_NODE_ID);
}

} // namespace OHOS::Ace::NG