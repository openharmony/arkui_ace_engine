/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class MockLayoutProperty : public LayoutProperty {
public:
    MockLayoutProperty() = default;
    ~MockLayoutProperty() override = default;
};

class MockLayoutWrapper : public LayoutWrapper {
public:
    explicit MockLayoutWrapper(WeakPtr<FrameNode> hostNode) : LayoutWrapper(hostNode)
    {
        layoutProperty_ = AceType::MakeRefPtr<MockLayoutProperty>();
        layoutProperty_->SetHost(hostNode);
        geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    }
    ~MockLayoutWrapper() override = default;

    MOCK_METHOD(const RefPtr<LayoutAlgorithmWrapper>&, GetLayoutAlgorithm, (bool needReset), (override));
    MOCK_METHOD(void, Measure, (const std::optional<LayoutConstraintF>& parentConstraint), (override));
    MOCK_METHOD(void, Layout, (), (override));
    int32_t GetTotalChildCount() const override
    {
        return 0;
    }
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

    MockLayoutProperty* GetMockLayoutProperty()
    {
        return reinterpret_cast<MockLayoutProperty*>(layoutProperty_.GetRawPtr());
    }
};

class CustomLayoutRootModifierTest : public ModifierTestBase<GENERATED_ArkUICustomLayoutRootModifier,
    &GENERATED_ArkUINodeModifiers::getCustomLayoutRootModifier, GENERATED_ARKUI_CUSTOM_LAYOUT_ROOT> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
    }
};

/*
 * @tc.name: SubscribeOnMeasureSizeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomLayoutRootModifierTest, SubscribeOnMeasureSizeTest, TestSize.Level1)
{
    static const int32_t resourceIdTest = 123;
    LayoutConstraintF layoutConstraintTest = {
        .minSize = { 10.0f, 15.25f },
        .maxSize = { 100.0f, 120.0f },
    };

    auto callback = [](Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GeometryInfo selfLayoutInfo,
        const Array_Measurable children, const Ark_ConstraintSizeOptions constraint,
        const Callback_SizeResult_Void continuation) {
        EXPECT_EQ(resourceId, resourceIdTest);

        EXPECT_EQ(Converter::OptConvert<float>(constraint.minWidth), 10.0f);
        EXPECT_EQ(Converter::OptConvert<float>(constraint.minHeight), 15.25f);
        EXPECT_EQ(Converter::OptConvert<float>(constraint.maxWidth), 100.0f);
        EXPECT_EQ(Converter::OptConvert<float>(constraint.maxHeight), 120.0f);

        auto convChildren = Converter::Convert<std::vector<Ark_Measurable>>(children);
        EXPECT_TRUE(convChildren.empty());

        Ark_SizeResult result = {
            .width = Converter::ArkValue<Ark_Number>(35.0f),
            .height = Converter::ArkValue<Ark_Number>(40.0f),
        };
        CallbackHelper(continuation).InvokeSync(result);
    };

    auto arkCallback = Converter::ArkValue<Callback_onMeasureSize_SizeResult>(
        nullptr, callback, resourceIdTest);
    modifier_->setSubscribeOnMeasureSize(node_, &arkCallback);
    auto customNode = reinterpret_cast<NG::CustomMeasureLayoutNode *>(node_);
    ASSERT_NE(customNode, nullptr);

    auto layoutWrapper =
        AceType::MakeRefPtr<MockLayoutWrapper>(AceType::Claim<NG::CustomMeasureLayoutNode>(customNode));
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->layoutProperty_->UpdateLayoutConstraint(layoutConstraintTest);

    customNode->FireOnMeasure(layoutWrapper.GetRawPtr());
    SizeF size =  layoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_FLOAT_EQ(size.Width(), 35.0f);
    EXPECT_FLOAT_EQ(size.Height(), 40.0f);
}

/*
 * @tc.name: SubscribeOnPlaceChildrenTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomLayoutRootModifierTest, SubscribeOnPlaceChildrenTest, TestSize.Level1)
{
    static const int32_t resourceIdTest = 123;
    LayoutConstraintF layoutConstraintTest = {
        .minSize = { 10.0f, 15.25f },
        .maxSize = { 100.0f, 120.0f },
    };

    static std::optional<int32_t> checkData;

    auto callback = [](Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GeometryInfo selfLayoutInfo,
        const Array_Layoutable children, const Ark_ConstraintSizeOptions constraint) {
        checkData = Converter::Convert<int32_t>(resourceId);

        EXPECT_EQ(Converter::OptConvert<float>(constraint.minWidth), 10.0f);
        EXPECT_EQ(Converter::OptConvert<float>(constraint.minHeight), 15.25f);
        EXPECT_EQ(Converter::OptConvert<float>(constraint.maxWidth), 100.0f);
        EXPECT_EQ(Converter::OptConvert<float>(constraint.maxHeight), 120.0f);

        auto convChildren = Converter::Convert<std::vector<Ark_Layoutable>>(children);
        EXPECT_TRUE(convChildren.empty());
    };

    auto arkCallback = Converter::ArkValue<Callback_onPlaceChildren_Void>(
        nullptr, callback, resourceIdTest);
    modifier_->setSubscribeOnPlaceChildren(node_, &arkCallback);
    auto customNode = reinterpret_cast<NG::CustomMeasureLayoutNode *>(node_);
    ASSERT_NE(customNode, nullptr);

    auto layoutWrapper =
        AceType::MakeRefPtr<MockLayoutWrapper>(AceType::Claim<NG::CustomMeasureLayoutNode>(customNode));
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->layoutProperty_->UpdateLayoutConstraint(layoutConstraintTest);

    ASSERT_FALSE(checkData.has_value());
    customNode->FireOnLayout(layoutWrapper.GetRawPtr());
    ASSERT_TRUE(checkData.has_value());
    EXPECT_EQ(checkData.value(), resourceIdTest);
}

} // namespace OHOS::Ace::NG