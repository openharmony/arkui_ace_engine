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

    const std::vector<Section>& GetSectionInfo() const
    {
        counter++;
        return vector;
    }
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
    auto controller = peer_->GetController();
    ASSERT_NE(controller, nullptr);
    auto refPtr = controller.GetRawPtr();
    ASSERT_NE(refPtr, nullptr);
    MockWaterFlowSections* mockSections = reinterpret_cast<MockWaterFlowSections*>(refPtr);

    accessor_->length(peer_);
    accessor_->length(peer_);
    accessor_->length(nullptr);
    accessor_->length(peer_);

    EXPECT_EQ(mockSections->counter, 3);
}
} // namespace OHOS::Ace::NG