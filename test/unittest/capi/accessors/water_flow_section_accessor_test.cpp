/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/implementation/water_flow_sections_accessor_peer_impl.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "accessor_test_base.h"
#include "node_api.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "gmock/gmock.h"
#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class MockWaterFlowSections : public WaterFlowSections {
public:
    MockWaterFlowSections() = default;
    ~MockWaterFlowSections() override = default;

public:
    mutable int counter = 0;
    std::vector<Section> vector;
};

class WaterFlowSectionAccessorTest : public AccessorTestBase<GENERATED_ArkUIWaterFlowSectionsAccessor,
    &GENERATED_ArkUIAccessors::getWaterFlowSectionsAccessor, WaterFlowSectionsPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockWaterFlowSections_ = new MockWaterFlowSections();
        mockWaterFlowSectionsKeeper_ = AceType::Claim(mockWaterFlowSections_);
        ASSERT_NE(mockWaterFlowSectionsKeeper_, nullptr);
        auto peerImpl = reinterpret_cast<WaterFlowSectionsPeer*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->SetController(mockWaterFlowSectionsKeeper_);
        ASSERT_NE(mockWaterFlowSections_, nullptr);
    }
    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockWaterFlowSectionsKeeper_ = nullptr;
        mockWaterFlowSections_ = nullptr;
    }

    MockWaterFlowSections *mockWaterFlowSections_ = nullptr;
    RefPtr<MockWaterFlowSections> mockWaterFlowSectionsKeeper_ = nullptr;
};

/**
 * @tc.name: LengthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSectionAccessorTest, LengthTest, TestSize.Level1)
{
    Ark_SectionOptions section1;
    section1.columnsGap = Converter::ArkValue<Opt_Length>(1);
    section1.crossCount = Converter::ArkValue<Opt_Number>(2);
    section1.itemsCount = Converter::ArkValue<Ark_Number>(3);
    section1.rowsGap = Converter::ArkValue<Opt_Length>(4);
    Ark_SectionOptions section2;
    section2.columnsGap = Converter::ArkValue<Opt_Length>(5);
    section2.crossCount = Converter::ArkValue<Opt_Number>(6);
    section2.itemsCount = Converter::ArkValue<Ark_Number>(7);
    section2.rowsGap = Converter::ArkValue<Opt_Length>(8);
    accessor_->push(peer_, &section1);
    accessor_->push(peer_, &section2);
    auto length = accessor_->length(peer_);
    EXPECT_EQ(Converter::Convert<int>(length), 2);
}

/**
 * @tc.name: ValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSectionAccessorTest, ValuesTest, TestSize.Level1)
{
    Ark_SectionOptions section;
    section.columnsGap = Converter::ArkValue<Opt_Length>(1);
    section.crossCount = Converter::ArkValue<Opt_Number>(2);
    section.itemsCount = Converter::ArkValue<Ark_Number>(3);
    section.rowsGap = Converter::ArkValue<Opt_Length>(4);
    const CalcLength length(123.0_vp);
    Ark_Padding arkPadding = {
        .left = Converter::ArkValue<Opt_Length>(length.GetDimension()),
        .top = Converter::ArkValue<Opt_Length>(length.GetDimension()),
        .right = Converter::ArkValue<Opt_Length>(length.GetDimension()),
        .bottom = Converter::ArkValue<Opt_Length>(length.GetDimension()),
    };
    Opt_Union_Margin_Dimension margin = Converter::ArkUnion<Opt_Union_Margin_Dimension, Ark_Padding>
                        (Converter::ArkValue<Ark_Padding>(arkPadding));
    section.margin = margin;
    accessor_->push(peer_, &section);
    Array_SectionOptions sections = accessor_->values(peer_);
    EXPECT_EQ(sections.length, 1);
    EXPECT_EQ(Converter::Convert<int32_t>(sections.array[0].itemsCount), 3);
    auto crossCountOpt  = Converter::OptConvert<Ark_Number>(sections.array[0].crossCount);
    auto crossCount = Converter::Convert<int32_t>(crossCountOpt.value());
    EXPECT_EQ(crossCount, 2);
    EXPECT_EQ(Converter::OptConvert<Dimension>(section.columnsGap),
              Converter::OptConvert<Dimension>(sections.array[0].columnsGap));
    EXPECT_EQ(Converter::OptConvert<Dimension>(section.rowsGap),
              Converter::OptConvert<Dimension>(sections.array[0].rowsGap));
    EXPECT_EQ(Converter::OptConvert<MarginProperty>(section.margin),
              Converter::OptConvert<MarginProperty>(sections.array[0].margin));
}

/**
 * @tc.name: OnGetItemMainSizeByIndexTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSectionAccessorTest, OnGetItemMainSizeByIndexTest, TestSize.Level1)
{
    const auto inputValue = 123;
    const auto expextedValue = 789;
    auto onGetItemMainSizeByIndex = [](int32_t index) -> float {
        return index == 123 ? 789 : 0;
    };

    std::vector<WaterFlowSections::Section> waterFlowSections;
    WaterFlowSections::Section waterFlowsection;

    waterFlowsection.onGetItemMainSizeByIndex = onGetItemMainSizeByIndex;
    waterFlowSections.push_back(waterFlowsection);
    auto start = peer_->GetController()->GetSectionInfo().size();
    peer_->GetController()->ChangeData(start, 0, waterFlowSections);

    Array_SectionOptions arkSections = accessor_->values(peer_);

    ASSERT_TRUE(arkSections.length == 1);
    auto onGetItemMainSizeByIndeX = Converter::OptConvert<::GetItemMainSizeByIndex>
                                        (arkSections.array[0].onGetItemMainSizeByIndex);
    ASSERT_TRUE(onGetItemMainSizeByIndeX);
    auto modelCallback = [callback = CallbackHelper(*onGetItemMainSizeByIndeX)]
            (int32_t value) -> float {
                Ark_Number param = Converter::ArkValue<Ark_Number>(value);
                auto resultOpt = callback.InvokeWithOptConvertResult<float, Ark_Number, Callback_Number_Void>(param);
                return resultOpt.value_or(0);
            };
    EXPECT_EQ(modelCallback(inputValue), expextedValue);
}
} // namespace OHOS::Ace::NG