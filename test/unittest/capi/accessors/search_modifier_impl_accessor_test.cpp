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
#include "gmock/gmock.h"

#include "core/components/search/search_theme.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/search/search_layout_property.h"
#include "core/interfaces/native/implementation/search_modifier_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace GeneratedModifier;

namespace {
constexpr float TEST_MARGIN_VALUE = 10.0f;
constexpr float TEST_MARGIN_VALUE_2 = 20.0f;
}

class SearchModifierImplAccessorTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        themeManager_ = AceType::MakeRefPtr<NiceMock<MockThemeManager>>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager_);

        g_isResourceDecoupling = false;
        themeConstants_ = AceType::MakeRefPtr<ThemeConstants>(nullptr);
        EXPECT_CALL(*themeManager_, GetThemeConstants(testing::_, testing::_))
            .WillRepeatedly(testing::Return(themeConstants_));
        ON_CALL(*themeManager_, GetTheme(testing::_)).WillByDefault(testing::Return(nullptr));
        ON_CALL(*themeManager_, GetTheme(testing::_, testing::_)).WillByDefault(testing::Return(nullptr));

        themeConstants_->LoadTheme(0);
        MockThemeStyle::GetInstance()->SetAttributes({});

        MockContainer::SetUp(MockPipelineContext::GetCurrent());
        MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
        MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
        AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
        themeManager_ = nullptr;
        themeConstants_ = nullptr;
    }

    void SetUp() override
    {
        auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto pattern = AceType::MakeRefPtr<SearchPattern>();
        auto layoutProperty = AceType::MakeRefPtr<SearchLayoutProperty>();
        frameNode_ = FrameNode::CreateFrameNode(V2::SEARCH_ETS_TAG, nodeId, pattern, layoutProperty);
        ASSERT_NE(frameNode_, nullptr);
    }

    void TearDown() override
    {
        frameNode_ = nullptr;
        PeerUtils::ClearAllPeers();
    }

    static RefPtr<NiceMock<MockThemeManager>> themeManager_;
    static RefPtr<ThemeConstants> themeConstants_;
    RefPtr<FrameNode> frameNode_;
};

RefPtr<NiceMock<MockThemeManager>> SearchModifierImplAccessorTest::themeManager_;
RefPtr<ThemeConstants> SearchModifierImplAccessorTest::themeConstants_;

/**
 * @tc.name: SetMarginImplTest001
 * @tc.desc: Test SearchModifier::SetMarginImpl with valid Padding value
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierImplAccessorTest, SetMarginImplTest001, TestSize.Level1)
{
    Ark_Padding inputValue;
    inputValue.left = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE);
    inputValue.top = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE);
    inputValue.right = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE);
    inputValue.bottom = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE);
    auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);

    SearchModifier::SetMarginImpl(reinterpret_cast<Ark_NativePointer>(AceType::RawPtr(frameNode_)), &value);

    auto layoutProperty = frameNode_->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetMarginProperty(), nullptr);
}

/**
 * @tc.name: SetMarginImplTest002
 * @tc.desc: Test SearchModifier::SetMarginImpl with different values for each side
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierImplAccessorTest, SetMarginImplTest002, TestSize.Level1)
{
    Ark_Padding inputValue;
    inputValue.left = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE);
    inputValue.top = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE_2);
    inputValue.right = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE);
    inputValue.bottom = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE_2);
    auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);

    SearchModifier::SetMarginImpl(reinterpret_cast<Ark_NativePointer>(AceType::RawPtr(frameNode_)), &value);

    auto layoutProperty = frameNode_->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetMarginProperty(), nullptr);
}

/**
 * @tc.name: SetMarginImplTest003
 * @tc.desc: Test SearchModifier::SetMarginImpl with null value
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierImplAccessorTest, SetMarginImplTest003, TestSize.Level1)
{
    auto value = Converter::ArkValue<Opt_Union_Padding_Length_LocalizedPadding>();

    SearchModifier::SetMarginImpl(reinterpret_cast<Ark_NativePointer>(AceType::RawPtr(frameNode_)), &value);

    auto layoutProperty = frameNode_->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: SetMarginImplTest004
 * @tc.desc: Test SearchModifier::SetMarginImpl with empty padding
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierImplAccessorTest, SetMarginImplTest004, TestSize.Level1)
{
    Ark_Padding inputValue;
    inputValue.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
    inputValue.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
    inputValue.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
    inputValue.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
    auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);

    SearchModifier::SetMarginImpl(reinterpret_cast<Ark_NativePointer>(AceType::RawPtr(frameNode_)), &value);

    auto layoutProperty = frameNode_->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: SetMarginImplTest005
 * @tc.desc: Test SearchModifier::SetMarginImpl verifies UserMargin update
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierImplAccessorTest, SetMarginImplTest005, TestSize.Level1)
{
    Ark_Padding inputValue;
    inputValue.left = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE);
    inputValue.top = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE);
    inputValue.right = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE);
    inputValue.bottom = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE);
    auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);

    SearchModifier::SetMarginImpl(reinterpret_cast<Ark_NativePointer>(AceType::RawPtr(frameNode_)), &value);

    auto layoutProperty = frameNode_->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    (void)layoutProperty->GetUserMargin();
}

/**
 * @tc.name: SetMarginImplTest006
 * @tc.desc: Test SearchModifier::SetMarginImpl with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierImplAccessorTest, SetMarginImplTest006, TestSize.Level1)
{
    Ark_Padding inputValue;
    inputValue.left = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE);
    inputValue.top = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE);
    inputValue.right = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE);
    inputValue.bottom = Converter::ArkValue<Opt_Length>(TEST_MARGIN_VALUE);
    auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);

    SearchModifier::SetMarginImpl(nullptr, &value);
}

} // namespace OHOS::Ace::NG