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
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_layout_algorithm.h"

namespace OHOS::Ace::NG {
class SwiperIgnoreHiddenItemTestNg : public SwiperTestNg {
public:
    // Create swiper with all items displayed (displayCount=itemCount) so itemPosition_ contains all items
    // Default loop=false since ignoreHiddenItem requires loop=false
    SwiperModelNG CreateFullDisplaySwiper(int32_t itemCount, bool ignoreHiddenItem = true,
        bool loop = false);
    // Set visibility on a child item, must call before CreateSwiperDone for layout to apply
    void SetChildVisibility(int32_t index, VisibleType visibility);
};

SwiperModelNG SwiperIgnoreHiddenItemTestNg::CreateFullDisplaySwiper(
    int32_t itemCount, bool ignoreHiddenItem, bool loop)
{
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetIgnoreHiddenItem(AceType::RawPtr(frameNode_), ignoreHiddenItem);
    model.SetLoop(loop);
    model.SetDisplayCount(itemCount);
    model.SetDisplayMode(SwiperDisplayMode::STRETCH);
    CreateSwiperItems(itemCount);
    return model;
}

void SwiperIgnoreHiddenItemTestNg::SetChildVisibility(int32_t index, VisibleType visibility)
{
    auto childLayoutProperty = GetChildLayoutProperty<LayoutProperty>(frameNode_, index);
    ASSERT_NE(childLayoutProperty, nullptr);
    childLayoutProperty->UpdateVisibility(visibility);
}

// ==================== Property Tests ====================

/**
 * @tc.name: IgnoreHiddenItemProperty001
 * @tc.desc: Test IsIgnoreHiddenItem returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, IgnoreHiddenItemProperty001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_FALSE(pattern_->IsIgnoreHiddenItem());
}

/**
 * @tc.name: IgnoreHiddenItemProperty002
 * @tc.desc: Test IsIgnoreHiddenItem returns true when set with loop=false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, IgnoreHiddenItemProperty002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetIgnoreHiddenItem(AceType::RawPtr(frameNode_), true);
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_TRUE(pattern_->IsIgnoreHiddenItem());
}

/**
 * @tc.name: IgnoreHiddenItemProperty003
 * @tc.desc: Test IgnoreHiddenItem property in SwiperLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, IgnoreHiddenItemProperty003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetIgnoreHiddenItem(AceType::RawPtr(frameNode_), true);
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    auto prop = layoutProperty_->GetIgnoreHiddenItem();
    ASSERT_TRUE(prop.has_value());
    EXPECT_TRUE(prop.value());
}

/**
 * @tc.name: IgnoreHiddenItemProperty004
 * @tc.desc: Test IsIgnoreHiddenItem returns false when loop is true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, IgnoreHiddenItemProperty004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetIgnoreHiddenItem(AceType::RawPtr(frameNode_), true);
    model.SetLoop(true);
    CreateSwiperItems();
    CreateSwiperDone();
    // ignoreHiddenItem requires loop=false, so IsIgnoreHiddenItem should return false
    EXPECT_FALSE(pattern_->IsIgnoreHiddenItem());
}

/**
 * @tc.name: IgnoreHiddenItemProperty005
 * @tc.desc: Test IsIgnoreHiddenItem returns false when swipeByGroup is true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, IgnoreHiddenItemProperty005, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetIgnoreHiddenItem(AceType::RawPtr(frameNode_), true);
    model.SetLoop(false);
    model.SetSwipeByGroup(true);
    model.SetDisplayCount(2);
    model.SetDisplayMode(SwiperDisplayMode::STRETCH);
    CreateSwiperItems(4);
    CreateSwiperDone();
    // swipeByGroup takes priority, IsIgnoreHiddenItem should return false
    EXPECT_FALSE(pattern_->IsIgnoreHiddenItem());
}

// ==================== Layout Algorithm Tests ====================

/**
 * @tc.name: LayoutGoneItem001
 * @tc.desc: Test GONE item has size 0 in itemPosition_ when ignoreHiddenItem is true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, LayoutGoneItem001, TestSize.Level1)
{
    auto model = CreateFullDisplaySwiper(4, true);
    SetChildVisibility(1, VisibleType::GONE);
    CreateSwiperDone();
    // GONE item should have startPos == endPos (size=0) in itemPosition_
    auto it = pattern_->itemPosition_.find(1);
    ASSERT_NE(it, pattern_->itemPosition_.end());
    EXPECT_EQ(it->second.startPos, it->second.endPos);
}

/**
 * @tc.name: LayoutGoneItem002
 * @tc.desc: Test GONE item still occupies space when ignoreHiddenItem is false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, LayoutGoneItem002, TestSize.Level1)
{
    auto model = CreateFullDisplaySwiper(4, false);
    SetChildVisibility(1, VisibleType::GONE);
    CreateSwiperDone();
    // GONE item should still have non-zero size when ignoreHiddenItem is false
    auto it = pattern_->itemPosition_.find(1);
    ASSERT_NE(it, pattern_->itemPosition_.end());
    EXPECT_GT(it->second.endPos - it->second.startPos, 0.0f);
}

/**
 * @tc.name: LayoutGoneItem003
 * @tc.desc: Test INVISIBLE item still occupies space when ignoreHiddenItem is true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, LayoutGoneItem003, TestSize.Level1)
{
    auto model = CreateFullDisplaySwiper(4, true);
    SetChildVisibility(1, VisibleType::INVISIBLE);
    CreateSwiperDone();
    // INVISIBLE item should still have non-zero size
    auto it = pattern_->itemPosition_.find(1);
    ASSERT_NE(it, pattern_->itemPosition_.end());
    EXPECT_GT(it->second.endPos - it->second.startPos, 0.0f);
}

/**
 * @tc.name: LayoutGoneItem004
 * @tc.desc: Test GONE item is in itemPosition_ (not skipped) when ignoreHiddenItem is true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, LayoutGoneItem004, TestSize.Level1)
{
    auto model = CreateFullDisplaySwiper(5, true);
    SetChildVisibility(2, VisibleType::GONE);
    CreateSwiperDone();
    // All items should be in itemPosition_, including GONE ones
    EXPECT_EQ(pattern_->itemPosition_.size(), 5);
    for (int32_t i = 0; i < 5; ++i) {
        EXPECT_NE(pattern_->itemPosition_.find(i), pattern_->itemPosition_.end())
            << "Item " << i << " should be in itemPosition_";
    }
}

/**
 * @tc.name: LayoutGoneItem005
 * @tc.desc: Test GONE items do not produce spaceWidth spacing
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, LayoutGoneItem005, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetIgnoreHiddenItem(AceType::RawPtr(frameNode_), true);
    model.SetLoop(false);
    model.SetDisplayCount(3);
    model.SetDisplayMode(SwiperDisplayMode::STRETCH);
    model.SetItemSpace(Dimension(10.0f));
    CreateSwiperItems(3);
    SetChildVisibility(1, VisibleType::GONE);
    CreateSwiperDone();
    auto it0 = pattern_->itemPosition_.find(0);
    auto it1 = pattern_->itemPosition_.find(1);
    auto it2 = pattern_->itemPosition_.find(2);
    ASSERT_NE(it0, pattern_->itemPosition_.end());
    ASSERT_NE(it1, pattern_->itemPosition_.end());
    ASSERT_NE(it2, pattern_->itemPosition_.end());
    // GONE item (index 1) has size 0
    EXPECT_EQ(it1->second.startPos, it1->second.endPos);
    // item 2 starts right after item 0 (with one spaceWidth), no extra space from GONE item
    float item0End = it0->second.endPos;
    float item2Start = it2->second.startPos;
    float spaceWidth = 10.0f;
    EXPECT_EQ(item2Start, item0End + spaceWidth);
}

/**
 * @tc.name: LayoutGoneItem006
 * @tc.desc: Test all items GONE results in empty swiper area (no crash)
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, LayoutGoneItem006, TestSize.Level1)
{
    auto model = CreateFullDisplaySwiper(3, true);
    SetChildVisibility(0, VisibleType::GONE);
    SetChildVisibility(1, VisibleType::GONE);
    SetChildVisibility(2, VisibleType::GONE);
    CreateSwiperDone();
    // Should not crash, all items have size 0
    for (const auto& [index, info] : pattern_->itemPosition_) {
        EXPECT_EQ(info.startPos, info.endPos);
    }
}

// ==================== CheckUserSetIndex Tests ====================

/**
 * @tc.name: CheckUserSetIndex001
 * @tc.desc: Test CheckUserSetIndex skips GONE items when ignoreHiddenItem is true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, CheckUserSetIndex001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetIgnoreHiddenItem(AceType::RawPtr(frameNode_), true);
    model.SetLoop(false);
    model.SetIndex(0);
    CreateSwiperItems(5);
    SetChildVisibility(0, VisibleType::GONE);
    SetChildVisibility(1, VisibleType::GONE);
    CreateSwiperDone();
    // Index 0 and 1 are GONE, should auto-skip to first visible item
    EXPECT_NE(pattern_->GetCurrentIndex(), 0);
    EXPECT_NE(pattern_->GetCurrentIndex(), 1);
}

/**
 * @tc.name: CheckUserSetIndex002
 * @tc.desc: Test CheckUserSetIndex does not skip GONE items when ignoreHiddenItem is false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, CheckUserSetIndex002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetIgnoreHiddenItem(AceType::RawPtr(frameNode_), false);
    model.SetLoop(false);
    model.SetIndex(1);
    CreateSwiperItems(4);
    SetChildVisibility(1, VisibleType::GONE);
    CreateSwiperDone();
    // Without ignoreHiddenItem, index 1 should be accepted (GONE still occupies slot)
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);
}

// ==================== CheckTargetIndex Tests ====================

/**
 * @tc.name: CheckTargetIndex001
 * @tc.desc: Test CheckTargetIndex skips GONE items when ignoreHiddenItem is true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, CheckTargetIndex001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetIgnoreHiddenItem(AceType::RawPtr(frameNode_), true);
    model.SetLoop(false);
    CreateSwiperItems(5);
    SetChildVisibility(1, VisibleType::GONE);
    CreateSwiperDone();
    // Target index 1 should skip to next visible item
    int32_t result = pattern_->CheckTargetIndex(1);
    EXPECT_NE(result, 1);
}

/**
 * @tc.name: CheckTargetIndex002
 * @tc.desc: Test CheckTargetIndex does not skip GONE items when ignoreHiddenItem is false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, CheckTargetIndex002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetIgnoreHiddenItem(AceType::RawPtr(frameNode_), false);
    model.SetLoop(false);
    CreateSwiperItems(4);
    SetChildVisibility(1, VisibleType::GONE);
    CreateSwiperDone();
    int32_t result = pattern_->CheckTargetIndex(1);
    EXPECT_EQ(result, 1);
}

// ==================== CheckIndexWithIgnoreHiddenItem Tests ====================

/**
 * @tc.name: CheckIndexWithIgnoreHiddenItem001
 * @tc.desc: Test currentIndex jumps to index 0 when current item is GONE after visibility change
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, CheckIndexWithIgnoreHiddenItem001, TestSize.Level1)
{
    auto model = CreateFullDisplaySwiper(4, true);
    CreateSwiperDone();
    // Initially at index 0, all items visible
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);

    // Make all items GONE
    SetChildVisibility(0, VisibleType::GONE);
    SetChildVisibility(1, VisibleType::GONE);
    SetChildVisibility(2, VisibleType::GONE);
    SetChildVisibility(3, VisibleType::GONE);
    FlushUITasks();

    // Make items 0 and 2 visible again
    SetChildVisibility(0, VisibleType::VISIBLE);
    SetChildVisibility(2, VisibleType::VISIBLE);
    FlushUITasks();
    // currentIndex should be recalculated via jumpIndex mechanism
    EXPECT_NE(pattern_->GetCurrentIndex(), 1);
    EXPECT_NE(pattern_->GetCurrentIndex(), 3);
}

/**
 * @tc.name: CheckIndexWithIgnoreHiddenItem002
 * @tc.desc: Test no jumpIndex when currentIndex points to a visible item
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, CheckIndexWithIgnoreHiddenItem002, TestSize.Level1)
{
    auto model = CreateFullDisplaySwiper(4, true);
    CreateSwiperDone();
    auto indexBefore = pattern_->GetCurrentIndex();

    // Make a non-current item GONE
    SetChildVisibility(2, VisibleType::GONE);
    FlushUITasks();
    // currentIndex should remain unchanged since it still points to a visible item
    EXPECT_EQ(pattern_->GetCurrentIndex(), indexBefore);
}

// ==================== SwipeByGroup Priority Tests ====================

/**
 * @tc.name: SwipeByGroupPriority001
 * @tc.desc: Test swipeByGroup takes priority over ignoreHiddenItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, SwipeByGroupPriority001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetIgnoreHiddenItem(AceType::RawPtr(frameNode_), true);
    model.SetSwipeByGroup(true);
    model.SetLoop(false);
    model.SetDisplayCount(2);
    model.SetDisplayMode(SwiperDisplayMode::STRETCH);
    CreateSwiperItems(4);
    SetChildVisibility(1, VisibleType::GONE);
    CreateSwiperDone();
    // swipeByGroup takes priority, GONE item should still occupy space
    auto it = pattern_->itemPosition_.find(1);
    ASSERT_NE(it, pattern_->itemPosition_.end());
    EXPECT_GT(it->second.endPos - it->second.startPos, 0.0f);
}

// ==================== Dynamic Visibility Change Tests ====================

/**
 * @tc.name: DynamicVisibility001
 * @tc.desc: Test dynamic visibility change triggers re-layout with all items displayed
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, DynamicVisibility001, TestSize.Level1)
{
    auto model = CreateFullDisplaySwiper(4, true, false);
    CreateSwiperDone();
    // Initially all items visible, item 1 has non-zero size
    auto it1 = pattern_->itemPosition_.find(1);
    ASSERT_NE(it1, pattern_->itemPosition_.end());
    EXPECT_GT(it1->second.endPos - it1->second.startPos, 0.0f);

    // Make item 1 GONE
    SetChildVisibility(1, VisibleType::GONE);
    FlushUITasks();
    it1 = pattern_->itemPosition_.find(1);
    ASSERT_NE(it1, pattern_->itemPosition_.end());
    EXPECT_EQ(it1->second.startPos, it1->second.endPos);

    // Make item 1 visible again
    SetChildVisibility(1, VisibleType::VISIBLE);
    FlushUITasks();
    it1 = pattern_->itemPosition_.find(1);
    ASSERT_NE(it1, pattern_->itemPosition_.end());
    EXPECT_GT(it1->second.endPos - it1->second.startPos, 0.0f);
}

/**
 * @tc.name: DynamicVisibility002
 * @tc.desc: Test dynamic visibility change on all items then restore some
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIgnoreHiddenItemTestNg, DynamicVisibility002, TestSize.Level1)
{
    auto model = CreateFullDisplaySwiper(3, true, false);
    CreateSwiperDone();

    // Make all items GONE
    SetChildVisibility(0, VisibleType::GONE);
    SetChildVisibility(1, VisibleType::GONE);
    SetChildVisibility(2, VisibleType::GONE);
    FlushUITasks();
    // All items should have size 0
    for (const auto& [index, info] : pattern_->itemPosition_) {
        EXPECT_EQ(info.startPos, info.endPos);
    }

    // Restore item 1 to visible
    SetChildVisibility(1, VisibleType::VISIBLE);
    FlushUITasks();
    auto it1 = pattern_->itemPosition_.find(1);
    ASSERT_NE(it1, pattern_->itemPosition_.end());
    EXPECT_GT(it1->second.endPos - it1->second.startPos, 0.0f);
    // GONE items may not be in itemPosition_ after re-layout if outside layout range,
    // but any GONE items that remain should have size 0
    for (const auto& [index, info] : pattern_->itemPosition_) {
        if (index != 1) {
            EXPECT_EQ(info.startPos, info.endPos) << "GONE item " << index << " should have size 0";
        }
    }
}
} // namespace OHOS::Ace::NG
