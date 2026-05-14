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

#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {

class WaterFlowStaticTestCore : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::TearDown();
    }
};

} // namespace

/**
 * @tc.name: WaterFlowLpxAttribute001
 * @tc.desc: Verify rowsGap and itemMinWidth keep independent LPX attributes.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowStaticTestCore, WaterFlowLpxAttribute001, TestSize.Level1)
{
    auto frameNode = WaterFlowModelNG::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);

    WaterFlowModelNG::SetRowsGap(AceType::RawPtr(frameNode), std::make_optional(Dimension(12.0, DimensionUnit::LPX)));
    WaterFlowModelNG::SetItemMinWidth(
        AceType::RawPtr(frameNode), std::make_optional(Dimension(100.0, DimensionUnit::LPX)));
    EXPECT_TRUE(frameNode->lpxAttributes_.count(LpxAttribute::LPX_ROWS_GAP));
    EXPECT_TRUE(frameNode->lpxAttributes_.count(LpxAttribute::LPX_ITEM_MIN_WIDTH));

    WaterFlowModelNG::SetRowsGap(AceType::RawPtr(frameNode), std::make_optional(Dimension(12.0, DimensionUnit::VP)));
    EXPECT_FALSE(frameNode->lpxAttributes_.count(LpxAttribute::LPX_ROWS_GAP));
    EXPECT_TRUE(frameNode->lpxAttributes_.count(LpxAttribute::LPX_ITEM_MIN_WIDTH));
}
} // namespace OHOS::Ace::NG
