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
    section1.columnsGap = Converter::ArkValue<Opt_Dimension>(1.f);
    section1.crossCount = Converter::ArkValue<Opt_Number>(2);
    section1.itemsCount = Converter::ArkValue<Ark_Number>(3);
    section1.rowsGap = Converter::ArkValue<Opt_Dimension>(4.f);
    Ark_SectionOptions section2;
    section2.columnsGap = Converter::ArkValue<Opt_Dimension>(5.f);
    section2.crossCount = Converter::ArkValue<Opt_Number>(6);
    section2.itemsCount = Converter::ArkValue<Ark_Number>(7);
    section2.rowsGap = Converter::ArkValue<Opt_Dimension>(8.f);
    accessor_->push(peer_, &section1);
    accessor_->push(peer_, &section2);
    auto length = accessor_->length(peer_);
    EXPECT_EQ(Converter::Convert<int>(length), 2);
}

template<typename T>
std::optional<decltype(T().ToString())> ToStr(const std::optional<T>& src)
{
    return src ? std::make_optional(src->ToString()) : std::nullopt;
}

/**
 * @tc.name: ValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSectionAccessorTest, ValuesTest, TestSize.Level1)
{
    Ark_SectionOptions section;
    section.columnsGap = Converter::ArkValue<Opt_Dimension>(1.f);
    section.crossCount = Converter::ArkValue<Opt_Number>(2);
    section.itemsCount = Converter::ArkValue<Ark_Number>(3);
    section.rowsGap = Converter::ArkValue<Opt_Dimension>(4.f);
    const auto length = "123.0vp";
    Ark_Padding arkPadding = {
        .left = Converter::ArkValue<Opt_Length>(length),
        .top = Converter::ArkValue<Opt_Length>(length),
        .right = Converter::ArkValue<Opt_Length>(length),
        .bottom = Converter::ArkValue<Opt_Length>(length),
    };
    auto margin = Converter::ArkUnion<Opt_Union_Margin_Dimension, Ark_Padding>(arkPadding);
    section.margin = margin;
    accessor_->push(peer_, &section);
    Array_SectionOptions sections = accessor_->values(peer_);
    EXPECT_EQ(sections.length, 1);
    EXPECT_EQ(Converter::Convert<int32_t>(sections.array[0].itemsCount), 3);
    auto crossCountOpt  = Converter::OptConvert<int32_t>(sections.array[0].crossCount);
    EXPECT_EQ(crossCountOpt, 2);
    EXPECT_EQ(ToStr(Converter::OptConvert<Dimension>(section.columnsGap)),
              ToStr(Converter::OptConvert<Dimension>(sections.array[0].columnsGap)));
    EXPECT_EQ(ToStr(Converter::OptConvert<Dimension>(section.rowsGap)),
              ToStr(Converter::OptConvert<Dimension>(sections.array[0].rowsGap)));
    EXPECT_EQ(ToStr(Converter::OptConvert<MarginProperty>(section.margin)),
              ToStr(Converter::OptConvert<MarginProperty>(sections.array[0].margin)));
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