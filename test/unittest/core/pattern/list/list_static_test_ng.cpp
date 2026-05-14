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

#include <optional>

#include "list_test_ng.h"
#include "test/mock/frameworks/core/animation/mock_animation_manager.h"

#define private public
#define protected public
#include "core/components_ng/pattern/list/list_model_static.h"
#undef private
#undef protected

namespace OHOS::Ace::NG {
class ListScrollerTestNg : public ListTestNg {};

/**
 * @tc.name: SetCachedCount001
 * @tc.desc: Test SetCachedCount
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, SetCachedCount001, TestSize.Level1)
{
    CreateList();
    std::optional<int32_t> cachedCount = 10;
    ListModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), cachedCount);
    ASSERT_NE(layoutProperty_, nullptr);
    auto ret = layoutProperty_->GetCachedCountValue(0);
    EXPECT_EQ(ret, cachedCount.value());

    cachedCount.reset();
    ListModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), cachedCount);
    EXPECT_FALSE(layoutProperty_->GetCachedCount().has_value());
}


/**
 * @tc.name: SetCachedCount002
 * @tc.desc: Test SetCachedCount
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, SetCachedCount002, TestSize.Level1)
{
    CreateList();
    std::optional<int32_t> cachedCount = 10;
    ListModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), cachedCount, true);
    ASSERT_NE(layoutProperty_, nullptr);
    auto ret = layoutProperty_->GetCachedCountValue(0);
    EXPECT_EQ(ret, cachedCount.value());

    cachedCount.reset();
    ListModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), cachedCount, true);
    EXPECT_FALSE(layoutProperty_->GetCachedCount().has_value());
}

/**
 * @tc.name: SetInitialIndex
 * @tc.desc: Test SetInitialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, SetInitialIndex, TestSize.Level1)
{
    CreateList();
    std::optional<int32_t> initialIndex = -1;
    ListModelStatic::SetInitialIndex(AceType::RawPtr(frameNode_), initialIndex);
    ASSERT_NE(layoutProperty_, nullptr);
    EXPECT_FALSE(layoutProperty_->GetInitialIndex().has_value());
}

/**
 * @tc.name: ListLpxAttribute001
 * @tc.desc: Verify space and spaceWidth keep independent LPX attributes.
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ListLpxAttribute001, TestSize.Level1)
{
    CreateList();
    ListModelStatic::SetListSpace(
        AceType::RawPtr(frameNode_), std::make_optional(Dimension(10.0, DimensionUnit::LPX)));
    ListModelStatic::SetListSpaceWidth(
        AceType::RawPtr(frameNode_), std::make_optional(Dimension(20.0, DimensionUnit::LPX)));
    EXPECT_TRUE(frameNode_->lpxAttributes_.count(LpxAttribute::LPX_SPACE));
    EXPECT_TRUE(frameNode_->lpxAttributes_.count(LpxAttribute::LPX_SPACE_WIDTH));

    ListModelStatic::SetListSpace(
        AceType::RawPtr(frameNode_), std::make_optional(Dimension(10.0, DimensionUnit::VP)));
    EXPECT_FALSE(frameNode_->lpxAttributes_.count(LpxAttribute::LPX_SPACE));
    EXPECT_TRUE(frameNode_->lpxAttributes_.count(LpxAttribute::LPX_SPACE_WIDTH));
}
} // namespace OHOS::Ace::NG
