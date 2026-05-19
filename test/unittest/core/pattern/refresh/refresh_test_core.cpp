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

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/refresh/refresh_layout_property.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {

class RefreshTestCore : public testing::Test {
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
 * @tc.name: RefreshLpxAttribute001
 * @tc.desc: Verify refreshOffset and indicatorOffset keep independent LPX attributes.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestCore, RefreshLpxAttribute001, TestSize.Level1)
{
    RefreshModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    model.SetRefreshOffset(Dimension(64.0, DimensionUnit::LPX));
    model.SetIndicatorOffset(Dimension(16.0, DimensionUnit::LPX));
    EXPECT_TRUE(frameNode->lpxAttributes_.count(LpxAttribute::LPX_REFRESH_OFFSET));
    EXPECT_TRUE(frameNode->lpxAttributes_.count(LpxAttribute::LPX_INDICATOR_OFFSET));

    model.SetRefreshOffset(Dimension(64.0, DimensionUnit::VP));
    EXPECT_FALSE(frameNode->lpxAttributes_.count(LpxAttribute::LPX_REFRESH_OFFSET));
    EXPECT_TRUE(frameNode->lpxAttributes_.count(LpxAttribute::LPX_INDICATOR_OFFSET));
}
} // namespace OHOS::Ace::NG
