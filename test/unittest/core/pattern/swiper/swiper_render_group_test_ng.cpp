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

#include "swiper_test_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_SWIPER_ITEM_COUNT = 4;
} // namespace

class SwiperUpdateItemRenderGroupTestNg : public SwiperTestNg {
public:
    void CreateSwiperWithItems()
    {
        SwiperModelNG model = CreateSwiper();
        CreateSwiperItems(TEST_SWIPER_ITEM_COUNT);
        CreateSwiperDone();
    }
};

/**
 * @tc.name: UpdateItemRenderGroup_RenderGroupFalseOverridesItemRenderGroupTrue
 * @tc.desc: When common renderGroup is set to false, itemRenderGroup=true should be overridden to false
 *   and lastSetRenderGroup_ should become false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUpdateItemRenderGroupTestNg,
    UpdateItemRenderGroup_RenderGroupFalseOverridesItemRenderGroupTrue, TestSize.Level1)
{
    CreateSwiperWithItems();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    renderContext->UpdateRenderGroup(false);
    pattern_->lastSetRenderGroup_ = false;
    pattern_->UpdateItemRenderGroup(true);

    EXPECT_FALSE(pattern_->lastSetRenderGroup_);
}

/**
 * @tc.name: UpdateItemRenderGroup_RenderGroupFalseOverridesItemRenderGroupFalse
 * @tc.desc: When common renderGroup is false and itemRenderGroup=false, should return early
 *   without updating lastSetRenderGroup_
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUpdateItemRenderGroupTestNg,
    UpdateItemRenderGroup_RenderGroupFalseOverridesItemRenderGroupFalse, TestSize.Level1)
{
    CreateSwiperWithItems();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    renderContext->UpdateRenderGroup(false);
    pattern_->lastSetRenderGroup_ = false;
    pattern_->groupedItems_.clear();

    pattern_->UpdateItemRenderGroup(false);

    EXPECT_FALSE(pattern_->lastSetRenderGroup_);
    EXPECT_TRUE(pattern_->groupedItems_.empty());
}

/**
 * @tc.name: UpdateItemRenderGroup_SameFalseTwiceShouldSkip
 * @tc.desc: When lastSetRenderGroup_ is false and new itemRenderGroup is false (no renderGroup override),
 *   should return early without collecting items into groupedItems_
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUpdateItemRenderGroupTestNg,
    UpdateItemRenderGroup_SameFalseTwiceShouldSkip, TestSize.Level1)
{
    CreateSwiperWithItems();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    renderContext->ResetRenderGroup();
    pattern_->lastSetRenderGroup_ = false;
    pattern_->groupedItems_.clear();

    pattern_->UpdateItemRenderGroup(false);

    EXPECT_FALSE(pattern_->lastSetRenderGroup_);
    EXPECT_TRUE(pattern_->groupedItems_.empty());
}

/**
 * @tc.name: UpdateItemRenderGroup_TrueThenFalseShouldUpdate
 * @tc.desc: When lastSetRenderGroup_ transitions from true to false, should update all grouped items
 *   with SuggestedRenderGroup=false and set lastSetRenderGroup_ to false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUpdateItemRenderGroupTestNg,
    UpdateItemRenderGroup_TrueThenFalseShouldUpdate, TestSize.Level1)
{
    CreateSwiperWithItems();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    renderContext->ResetRenderGroup();
    pattern_->lastSetRenderGroup_ = true;
    pattern_->groupedItems_.clear();

    pattern_->UpdateItemRenderGroup(true);
    EXPECT_TRUE(pattern_->lastSetRenderGroup_);
    EXPECT_FALSE(pattern_->groupedItems_.empty());

    pattern_->UpdateItemRenderGroup(false);
    EXPECT_FALSE(pattern_->lastSetRenderGroup_);
}

/**
 * @tc.name: UpdateItemRenderGroup_TrueToTrueShouldUpdate
 * @tc.desc: When lastSetRenderGroup_ is true and new itemRenderGroup is true, should still update
 *   grouped items (no early return since lastSetRenderGroup_ is true)
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUpdateItemRenderGroupTestNg,
    UpdateItemRenderGroup_TrueToTrueShouldUpdate, TestSize.Level1)
{
    CreateSwiperWithItems();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    renderContext->ResetRenderGroup();
    pattern_->lastSetRenderGroup_ = false;
    pattern_->groupedItems_.clear();

    pattern_->UpdateItemRenderGroup(true);
    EXPECT_TRUE(pattern_->lastSetRenderGroup_);
    EXPECT_FALSE(pattern_->groupedItems_.empty());

    int32_t groupedCountBefore = static_cast<int32_t>(pattern_->groupedItems_.size());
    pattern_->UpdateItemRenderGroup(true);
    EXPECT_TRUE(pattern_->lastSetRenderGroup_);
    EXPECT_EQ(static_cast<int32_t>(pattern_->groupedItems_.size()), groupedCountBefore);
}

/**
 * @tc.name: UpdateItemRenderGroup_FalseToTrueShouldCollectItems
 * @tc.desc: When lastSetRenderGroup_ transitions from false to true, should collect children
 *   into groupedItems_ and set SuggestedRenderGroup=true on them
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUpdateItemRenderGroupTestNg,
    UpdateItemRenderGroup_FalseToTrueShouldCollectItems, TestSize.Level1)
{
    CreateSwiperWithItems();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    renderContext->ResetRenderGroup();
    pattern_->lastSetRenderGroup_ = false;
    pattern_->groupedItems_.clear();

    pattern_->UpdateItemRenderGroup(true);
    EXPECT_TRUE(pattern_->lastSetRenderGroup_);
    EXPECT_FALSE(pattern_->groupedItems_.empty());

    int32_t childCount = 0;
    for (const auto& child : frameNode_->GetChildren()) {
        if (child->GetTag() != V2::SWIPER_INDICATOR_ETS_TAG) {
            childCount++;
        }
    }
    EXPECT_GE(static_cast<int32_t>(pattern_->groupedItems_.size()), childCount);
}

/**
 * @tc.name: UpdateItemRenderGroup_RenderGroupTrueDoesNotOverride
 * @tc.desc: When common renderGroup is true, itemRenderGroup=true should not be overridden
 *   and should proceed normally to set items as render group
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUpdateItemRenderGroupTestNg,
    UpdateItemRenderGroup_RenderGroupTrueDoesNotOverride, TestSize.Level1)
{
    CreateSwiperWithItems();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    renderContext->UpdateRenderGroup(true);
    pattern_->lastSetRenderGroup_ = false;
    pattern_->groupedItems_.clear();

    pattern_->UpdateItemRenderGroup(true);

    EXPECT_TRUE(pattern_->lastSetRenderGroup_);
    EXPECT_FALSE(pattern_->groupedItems_.empty());
}

/**
 * @tc.name: UpdateItemRenderGroup_IndicatorNotInGroupedItems
 * @tc.desc: Swiper indicator nodes should be excluded from groupedItems_
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUpdateItemRenderGroupTestNg,
    UpdateItemRenderGroup_IndicatorNotInGroupedItems, TestSize.Level1)
{
    CreateSwiperWithItems();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    renderContext->ResetRenderGroup();
    pattern_->lastSetRenderGroup_ = false;
    pattern_->groupedItems_.clear();

    pattern_->UpdateItemRenderGroup(true);
    EXPECT_TRUE(pattern_->lastSetRenderGroup_);

    for (const auto& weakItem : pattern_->groupedItems_) {
        auto item = weakItem.Upgrade();
        if (item) {
            EXPECT_NE(item->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
        }
    }
}

/**
 * @tc.name: UpdateItemRenderGroup_NullHostReturnsEarly
 * @tc.desc: When host is null, UpdateItemRenderGroup should return early
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUpdateItemRenderGroupTestNg,
    UpdateItemRenderGroup_NullHostReturnsEarly, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    swiperPattern->lastSetRenderGroup_ = false;
    swiperPattern->groupedItems_.clear();

    swiperPattern->UpdateItemRenderGroup(true);

    EXPECT_FALSE(swiperPattern->lastSetRenderGroup_);
    EXPECT_TRUE(swiperPattern->groupedItems_.empty());
}
} // namespace OHOS::Ace::NG
