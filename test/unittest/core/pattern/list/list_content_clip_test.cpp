/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "list_test_ng.h"
#include "test/mock/frameworks/core/animation/mock_animation_manager.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"

#define private public
#define protected public

#include "core/common/multi_thread_build_manager.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/list/list_item_group_paint_method.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_model.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_pattern.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"

#undef private
#undef protected

namespace OHOS::Ace::NG {
class ListContentClipTestNg : public ListTestNg {
public:
    PaddingProperty CreatePadding(float left, float top, float right, float bottom);
    ListModelNG CreateHorizontalList();
};

PaddingProperty ListContentClipTestNg::CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

ListModelNG ListContentClipTestNg::CreateHorizontalList()
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ListModelNG model;
    model.Create();
    model.SetListDirection(Axis::HORIZONTAL);
    ViewAbstract::SetWidth(CalcLength(HEIGHT));
    ViewAbstract::SetHeight(CalcLength(WIDTH));
    RefPtr<ScrollControllerBase> scrollController = model.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    model.SetScroller(scrollController, proxy);
    GetList();
    return model;
}

/**
 * @tc.name: ContentClipBoundaryWithPadding001
 * @tc.desc: Test List with ContentClip BOUNDARY mode and bottom padding
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipBoundaryWithPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with content clip and bottom padding
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    model.SetSpace(Dimension(5));
    PaddingProperty padding = CreatePadding(0, 0, 0, 150);
    layoutProperty_->UpdatePadding(padding);
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: item3 is layout complete, item4.5 is not layout.
     */
    auto item3 = GetChildFrameNode(frameNode_, 3);
    EXPECT_TRUE(item3->IsActive());
    EXPECT_EQ(GetChildHeight(frameNode_, 3), ITEM_MAIN_SIZE);
    auto item4 = GetChildFrameNode(frameNode_, 4);
    EXPECT_FALSE(item4->IsActive());
    EXPECT_EQ(GetChildHeight(frameNode_, 4), 0);

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range is 0-2.
     */
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 2);
}

/**
 * @tc.name: ContentClipBoundaryWithPadding002
 * @tc.desc: Test List with ContentClip BOUNDARY mode and top padding
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipBoundaryWithPadding002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with content clip and top padding
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    model.SetSpace(Dimension(5));
    model.SetInitialIndex(1);
    PaddingProperty padding = CreatePadding(0, 100, 0, 0);
    layoutProperty_->UpdatePadding(padding);
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: items are layout complete.
     */
    for (int32_t i = 0; i < 3; i++) {
        auto item = GetChildFrameNode(frameNode_, i);
        EXPECT_TRUE(item->IsActive());
        EXPECT_EQ(GetChildHeight(frameNode_, i), ITEM_MAIN_SIZE);
    }

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range excludes padding area.
     */
    EXPECT_GE(startIndex, 1);
    EXPECT_GE(endIndex, 3);
}

/**
 * @tc.name: ContentClipSafeAreaWithPadding001
 * @tc.desc: Test List with ContentClip SAFE_AREA mode and bottom padding
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipSafeAreaWithSafeAreaPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with SAFE_AREA content clip and bottom padding
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    model.SetSpace(Dimension(5));
    PaddingProperty paddingProperty;
    paddingProperty.bottom = std::make_optional<CalcLength>(150);
    layoutProperty_->UpdateSafeAreaPadding(paddingProperty);
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: item3 is layout complete, item4 is not layout.
     */
    auto item3 = GetChildFrameNode(frameNode_, 3);
    EXPECT_TRUE(item3->IsActive());
    EXPECT_EQ(GetChildHeight(frameNode_, 3), ITEM_MAIN_SIZE);
    auto item4 = GetChildFrameNode(frameNode_, 4);
    EXPECT_FALSE(item4->IsActive());
    EXPECT_EQ(GetChildHeight(frameNode_, 4), 0);

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range is 0-2.
     */
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 2);
}

/**
 * @tc.name: ContentClipSafeAreaWithSafeAreaPadding002
 * @tc.desc: Test List with ContentClip BOUNDARY mode and top padding
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipSafeAreaWithSafeAreaPadding002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with content clip and top padding
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    model.SetSpace(Dimension(5));
    model.SetInitialIndex(1);
    PaddingProperty paddingProperty;
    paddingProperty.top = std::make_optional<CalcLength>(100);
    layoutProperty_->UpdateSafeAreaPadding(paddingProperty);
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: items are layout complete.
     */
    for (int32_t i = 0; i < 3; i++) {
        auto item = GetChildFrameNode(frameNode_, i);
        EXPECT_TRUE(item->IsActive());
        EXPECT_EQ(GetChildHeight(frameNode_, i), ITEM_MAIN_SIZE);
    }

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range excludes padding area.
     */
    EXPECT_GE(startIndex, 1);
    EXPECT_GE(endIndex, 3);
}

/**
 * @tc.name: ContentClipSafeAreaWithIgnoreLayoutSafeArea001
 * @tc.desc: Test List with ContentClip SAFE_AREA mode and ListItem with ignoreLayoutSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipSafeAreaWithIgnoreLayoutSafeArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with SAFE_AREA content clip and bottom safeAreaPadding
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    model.SetSpace(Dimension(5));
    PaddingProperty paddingProperty;
    paddingProperty.bottom = std::make_optional<CalcLength>(150);
    layoutProperty_->UpdateSafeAreaPadding(paddingProperty);
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step2. Set ignoreLayoutSafeArea for item3 and check layout
     */
    auto item3 = GetChildFrameNode(frameNode_, 3);
    ASSERT_NE(item3, nullptr);
    IgnoreLayoutSafeAreaOpts opts = { .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_BOTTOM };
    item3->GetLayoutProperty()->UpdateIgnoreLayoutSafeAreaOpts(opts);
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step3. check item layout with ignoreLayoutSafeArea
     * @tc.expected: item3 with ignoreLayoutSafeArea should extend into safeAreaPadding area
     */
    EXPECT_TRUE(item3->IsActive());
    auto item3GeometryNode = item3->GetGeometryNode();
    ASSERT_NE(item3GeometryNode, nullptr);
    EXPECT_EQ(item3GeometryNode->GetFrameSize().Height(), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step4. check item4 is not layout
     * @tc.expected: item4 is not active
     */
    auto item4 = GetChildFrameNode(frameNode_, 4);
    ASSERT_NE(item4, nullptr);
    EXPECT_FALSE(item4->IsActive());

    /**
     * @tc.steps: step5. check onScrollIndex
     * @tc.expected: index range is 0-3 (item3 visible due to ignoreLayoutSafeArea)
     */
    EXPECT_EQ(startIndex, 0);
    EXPECT_GE(endIndex, 2);
}

/**
 * @tc.name: ContentClipSafeAreaWithIgnoreLayoutSafeArea002
 * @tc.desc: Test List with ContentClip SAFE_AREA mode and multiple ListItem with ignoreLayoutSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipSafeAreaWithIgnoreLayoutSafeArea002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with SAFE_AREA content clip and bottom safeAreaPadding
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    model.SetSpace(Dimension(5));
    PaddingProperty paddingProperty;
    paddingProperty.bottom = std::make_optional<CalcLength>(150);
    layoutProperty_->UpdateSafeAreaPadding(paddingProperty);
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step2. Set ignoreLayoutSafeArea for item2 and item3 with different edges
     */
    auto item2 = GetChildFrameNode(frameNode_, 2);
    ASSERT_NE(item2, nullptr);
    IgnoreLayoutSafeAreaOpts opts2 = { .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL };
    item2->GetLayoutProperty()->UpdateIgnoreLayoutSafeAreaOpts(opts2);

    auto item3 = GetChildFrameNode(frameNode_, 3);
    ASSERT_NE(item3, nullptr);
    IgnoreLayoutSafeAreaOpts opts3 = { .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_BOTTOM };
    item3->GetLayoutProperty()->UpdateIgnoreLayoutSafeAreaOpts(opts3);

    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step3. check item layout with ignoreLayoutSafeArea
     * @tc.expected: items with ignoreLayoutSafeArea should be active
     */
    EXPECT_TRUE(item2->IsActive());
    EXPECT_TRUE(item3->IsActive());
    EXPECT_EQ(GetChildHeight(frameNode_, 2), ITEM_MAIN_SIZE);
    EXPECT_EQ(GetChildHeight(frameNode_, 3), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step4. check item4 and item5 are not layout
     * @tc.expected: items beyond safeAreaPadding are not active
     */
    auto item4 = GetChildFrameNode(frameNode_, 4);
    ASSERT_NE(item4, nullptr);
    EXPECT_FALSE(item4->IsActive());

    /**
     * @tc.steps: step5. check onScrollIndex
     * @tc.expected: index range should include items with ignoreLayoutSafeArea
     */
    EXPECT_EQ(startIndex, 0);
    EXPECT_GE(endIndex, 2);
}

/**
 * @tc.name: ContentClipCustomWithPadding001
 * @tc.desc: Test List with ContentClip CUSTOM mode and bottom padding
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipCustomWithPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with CUSTOM content clip and bottom padding
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateList();
    auto shape = AceType::MakeRefPtr<ShapeRect>();
    shape->SetWidth(Dimension(1, DimensionUnit::PERCENT));
    shape->SetHeight(Dimension(1, DimensionUnit::PERCENT));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    model.SetSpace(Dimension(5));
    PaddingProperty padding = CreatePadding(0, 0, 0, 150);
    layoutProperty_->UpdatePadding(padding);
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: item3 is layout complete, item4 is not layout.
     */
    auto item3 = GetChildFrameNode(frameNode_, 3);
    EXPECT_TRUE(item3->IsActive());
    EXPECT_EQ(GetChildHeight(frameNode_, 3), ITEM_MAIN_SIZE);
    auto item4 = GetChildFrameNode(frameNode_, 4);
    EXPECT_FALSE(item4->IsActive());
    EXPECT_EQ(GetChildHeight(frameNode_, 4), 0);

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range is 0-2.
     */
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 2);
}

/**
 * @tc.name: ContentClipCustomWithPadding002
 * @tc.desc: Test List with ContentClip BOUNDARY mode and top padding
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipCustomWithPadding002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with content clip and top padding
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateList();
    auto shape = AceType::MakeRefPtr<ShapeRect>();
    shape->SetWidth(Dimension(1, DimensionUnit::PERCENT));
    shape->SetHeight(Dimension(1, DimensionUnit::PERCENT));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    model.SetSpace(Dimension(5));
    model.SetInitialIndex(1);
    PaddingProperty padding = CreatePadding(0, 100, 0, 0);
    layoutProperty_->UpdatePadding(padding);
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: items are layout complete.
     */
    for (int32_t i = 0; i < 3; i++) {
        auto item = GetChildFrameNode(frameNode_, i);
        EXPECT_TRUE(item->IsActive());
        EXPECT_EQ(GetChildHeight(frameNode_, i), ITEM_MAIN_SIZE);
    }

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range excludes padding area.
     */
    EXPECT_GE(startIndex, 1);
    EXPECT_GE(endIndex, 3);
}

/**
 * @tc.name: ContentClipBoundaryWithListItemGroup001
 * @tc.desc: Test List with ListItemGroup and ContentClip BOUNDARY mode
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipBoundaryWithListItemGroup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with ListItemGroup and content clip
     */
    ListItemIndex startIndex;
    ListItemIndex endIndex;
    ListModelNG model = CreateList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    PaddingProperty paddingProperty;
    paddingProperty.top = std::make_optional<CalcLength>(10);
    paddingProperty.bottom = std::make_optional<CalcLength>(150);
    layoutProperty_->UpdateSafeAreaPadding(paddingProperty);
    auto onScrollVisibleContentChange = [&startIndex, &endIndex](const ListItemIndex start, const ListItemIndex end) {
        startIndex = start;
        endIndex = end;
    };
    model.SetOnScrollVisibleContentChange(onScrollVisibleContentChange);
    CreateListItemGroups(1, V2::ListItemGroupStyle::NONE, TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: items in content area are layout complete.
     */
    auto group = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(group, nullptr);
    for (int32_t i = 0; i < 4; i++) {
        auto item = GetChildFrameNode(group, i);
        EXPECT_TRUE(item->IsActive());
        EXPECT_EQ(GetChildHeight(group, i), ITEM_MAIN_SIZE);
    }
    auto item4 = GetChildFrameNode(group, 4);
    ASSERT_NE(item4, nullptr);
    EXPECT_FALSE(item4->IsActive());

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range excludes padding area.
     */
    EXPECT_GE(startIndex.indexInGroup, 0);
    EXPECT_GE(endIndex.indexInGroup, 2);
}

/**
 * @tc.name: ContentClipBoundaryWithListItemGroup002
 * @tc.desc: Test List with ListItemGroup and ContentClip BOUNDARY mode and top padding
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipBoundaryWithListItemGroup002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with ListItemGroup and content clip
     * @tc.expected: items in content area are layout complete.
     */
    ListItemIndex startIndex;
    ListItemIndex endIndex;
    ListModelNG model = CreateList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    PaddingProperty paddingProperty;
    paddingProperty.top = std::make_optional<CalcLength>(150);
    layoutProperty_->UpdateSafeAreaPadding(paddingProperty);
    auto onScrollVisibleContentChange = [&startIndex, &endIndex](const ListItemIndex start, const ListItemIndex end) {
        startIndex = start;
        endIndex = end;
    };
    model.SetOnScrollVisibleContentChange(onScrollVisibleContentChange);
    CreateListItemGroups(1, V2::ListItemGroupStyle::NONE, TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_GE(startIndex.indexInGroup, 0);
    EXPECT_GE(endIndex.indexInGroup, 2);

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: items in content area are layout complete.
     */
    UpdateCurrentOffset(-140.f);
    auto group = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(group, nullptr);
    for (int32_t i = 0; i < 4; i++) {
        auto item = GetChildFrameNode(group, i);
        EXPECT_TRUE(item->IsActive());
        EXPECT_EQ(GetChildHeight(group, i), ITEM_MAIN_SIZE);
    }

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range excludes padding area.
     */
    EXPECT_GE(startIndex.indexInGroup, 1);
    EXPECT_GE(endIndex.indexInGroup, 3);
}

/**
 * @tc.name: ContentClipBoundaryMultipleItemsInPadding001
 * @tc.desc: Test List with multiple items in padding area
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipBoundaryMultipleItemsInPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with large bottom padding
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    model.SetSpace(Dimension(5));
    PaddingProperty padding = CreatePadding(0, 0, 0, 250);
    layoutProperty_->UpdatePadding(padding);
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: items 0-3 are layout complete, items 4-5 are not layout.
     */
    for (int32_t i = 0; i < 4; i++) {
        auto item = GetChildFrameNode(frameNode_, i);
        EXPECT_TRUE(item->IsActive());
        EXPECT_EQ(GetChildHeight(frameNode_, i), ITEM_MAIN_SIZE);
    }
    for (int32_t i = 4; i < 6; i++) {
        auto item = GetChildFrameNode(frameNode_, i);
        EXPECT_FALSE(item->IsActive());
        EXPECT_EQ(GetChildHeight(frameNode_, i), 0);
    }

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range is 0-1.
     */
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 1);
}

/**
 * @tc.name: ContentClipBoundaryHorizontalWithPadding001
 * @tc.desc: Test horizontal List with ContentClip BOUNDARY mode and right padding
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipBoundaryHorizontalWithPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create horizontal List with content clip and right padding
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateHorizontalList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    model.SetSpace(Dimension(5));
    PaddingProperty padding = CreatePadding(0, 0, 150, 0);
    layoutProperty_->UpdatePadding(padding);
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: item3 is layout complete, item4 is not layout.
     */
    auto item3 = GetChildFrameNode(frameNode_, 3);
    EXPECT_TRUE(item3->IsActive());
    EXPECT_EQ(GetChildWidth(frameNode_, 3), ITEM_MAIN_SIZE);
    auto item4 = GetChildFrameNode(frameNode_, 4);
    EXPECT_FALSE(item4->IsActive());
    EXPECT_EQ(GetChildWidth(frameNode_, 4), 0);

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range is 0-2.
     */
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 2);
}

/**
 * @tc.name: ContentClipBoundaryHorizontalWithPadding002
 * @tc.desc: Test horizontal List with ContentClip BOUNDARY mode and left padding
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipBoundaryHorizontalWithPadding002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create horizontal List with content clip and left padding
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateHorizontalList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    model.SetSpace(Dimension(5));
    model.SetInitialIndex(1);
    PaddingProperty padding = CreatePadding(100, 0, 0, 0);
    layoutProperty_->UpdatePadding(padding);
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: items are layout complete.
     */
    for (int32_t i = 0; i < 3; i++) {
        auto item = GetChildFrameNode(frameNode_, i);
        EXPECT_TRUE(item->IsActive());
        EXPECT_EQ(GetChildWidth(frameNode_, i), ITEM_MAIN_SIZE);
    }

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range excludes padding area.
     */
    EXPECT_GE(startIndex, 1);
    EXPECT_GE(endIndex, 3);
}

/**
 * @tc.name: ContentClipBoundaryHorizontalWithPadding003
 * @tc.desc: Test horizontal List with ContentClip BOUNDARY mode and right padding and rtl layout
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipBoundaryHorizontalWithPadding003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create horizontal List with content clip and right padding rtl layout
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateHorizontalList();
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    model.SetSpace(Dimension(5));
    model.SetInitialIndex(1);
    PaddingProperty padding = CreatePadding(0, 0, 100, 0);
    layoutProperty_->UpdatePadding(padding);
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: items are layout complete.
     */
    for (int32_t i = 0; i < 3; i++) {
        auto item = GetChildFrameNode(frameNode_, i);
        EXPECT_TRUE(item->IsActive());
        EXPECT_EQ(GetChildWidth(frameNode_, i), ITEM_MAIN_SIZE);
    }

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range excludes padding area.
     */
    EXPECT_GE(startIndex, 1);
    EXPECT_GE(endIndex, 3);
}

/**
 * @tc.name: ContentClipSafeAreaHorizontalWithPadding001
 * @tc.desc: Test horizontal List with ContentClip SAFE_AREA mode and right padding
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipSafeAreaHorizontalWithPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create horizontal: List with SAFE_AREA content clip and right padding
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateHorizontalList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    model.SetSpace(Dimension(5));
    PaddingProperty paddingProperty;
    paddingProperty.right = std::make_optional<CalcLength>(120);
    layoutProperty_->UpdateSafeAreaPadding(paddingProperty);
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: item3 is layout complete, item4 is not layout.
     */
    auto item3 = GetChildFrameNode(frameNode_, 3);
    EXPECT_TRUE(item3->IsActive());
    EXPECT_EQ(GetChildWidth(frameNode_, 3), ITEM_MAIN_SIZE);
    auto item4 = GetChildFrameNode(frameNode_, 4);
    EXPECT_FALSE(item4->IsActive());
    EXPECT_EQ(GetChildWidth(frameNode_, 4), 0);

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range is 0-2.
     */
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 2);
}

/**
 * @tc.name: ContentClipCustomHorizontalWithPadding001
 * @tc.desc: Test horizontal List with ContentClip CUSTOM mode and right padding
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipCustomHorizontalWithPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create horizontal List with CUSTOM content clip and right padding
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateHorizontalList();
    auto shape = AceType::MakeRefPtr<ShapeRect>();
    shape->SetWidth(Dimension(1, DimensionUnit::PERCENT));
    shape->SetHeight(Dimension(1, DimensionUnit::PERCENT));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    model.SetSpace(Dimension(5));
    PaddingProperty padding = CreatePadding(0, 0, 100, 0);
    layoutProperty_->UpdatePadding(padding);
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: item3 is layout complete, item4 is not layout.
     */
    auto item3 = GetChildFrameNode(frameNode_, 3);
    EXPECT_TRUE(item3->IsActive());
    EXPECT_EQ(GetChildWidth(frameNode_, 3), ITEM_MAIN_SIZE);
    auto item4 = GetChildFrameNode(frameNode_, 4);
    EXPECT_FALSE(item4->IsActive());
    EXPECT_EQ(GetChildWidth(frameNode_, 4), 0);

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range is 0-2.
     */
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 2);
}

/**
 * @tc.name: ContentClipBoundaryHorizontalWithListItemGroup001
 * @tc.desc: Test horizontal List with ListItemGroup and ContentClip BOUNDARY mode
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipBoundaryHorizontalWithListItemGroup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create horizontal List with ListItemGroup and content clip
     */
    ListItemIndex startIndex;
    ListItemIndex endIndex;
    ListModelNG model = CreateHorizontalList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    PaddingProperty paddingProperty;
    paddingProperty.start = std::make_optional<CalcLength>(10);
    paddingProperty.end = std::make_optional<CalcLength>(150);
    layoutProperty_->UpdateSafeAreaPadding(paddingProperty);
    auto onScrollVisibleContentChange = [&startIndex, &endIndex](const ListItemIndex start, const ListItemIndex end) {
        startIndex = start;
        endIndex = end;
    };
    model.SetOnScrollVisibleContentChange(onScrollVisibleContentChange);
    CreateListItemGroups(1, V2::ListItemGroupStyle::NONE, TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: items in content area are layout complete.
     */
    auto group = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(group, nullptr);
    for (int32_t i = 0; i < 4; i++) {
        auto item = GetChildFrameNode(group, i);
        EXPECT_TRUE(item->IsActive());
        EXPECT_EQ(GetChildWidth(group, i), ITEM_MAIN_SIZE);
    }
    auto item4 = GetChildFrameNode(group, 4);
    ASSERT_NE(item4, nullptr);
    EXPECT_FALSE(item4->IsActive());

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range excludes padding area.
     */
    EXPECT_GE(startIndex.indexInGroup, 0);
    EXPECT_GE(endIndex.indexInGroup, 2);
}

/**
 * @tc.name: ContentClipCustomLargerThanComponent001
 * @tc.desc: Test List with CUSTOM content clip larger than component (vertical scroll)
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipCustomLargerThanComponent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with CUSTOM content clip larger than component
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateList();
    auto shape = AceType::MakeRefPtr<ShapeRect>();
    shape->SetHeight(Dimension(500));
    shape->SetOffset(DimensionOffset(Dimension(0), Dimension(-50)));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    model.SetInitialIndex(1);
    model.SetSpace(Dimension(5));
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: items should be layout within larger clip area.
     */
    for (int32_t i = 0; i < 6; i++) {
        auto item = GetChildFrameNode(frameNode_, i);
        EXPECT_TRUE(item->IsActive());
        EXPECT_EQ(GetChildHeight(frameNode_, i), ITEM_MAIN_SIZE);
    }

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range should cover more items due to larger clip area.
     */
    EXPECT_GE(startIndex, 1);
    EXPECT_GE(endIndex, 4);
}

/**
 * @tc.name: ContentClipCustomLargerThanComponent002
 * @tc.desc: Test List with CUSTOM content clip larger than component (horizontal scroll)
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipCustomLargerThanComponent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create horizontal List with CUSTOM content clip larger than component
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateHorizontalList();
    auto shape = AceType::MakeRefPtr<ShapeRect>();
    shape->SetWidth(Dimension(500));
    shape->SetOffset(DimensionOffset(Dimension(-50), Dimension(0)));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    model.SetInitialIndex(1);
    model.SetSpace(Dimension(5));
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: items should be layout within a larger clip area.
     */
    for (int32_t i = 0; i < 6; i++) {
        auto item = GetChildFrameNode(frameNode_, i);
        EXPECT_TRUE(item->IsActive());
        EXPECT_EQ(GetChildWidth(frameNode_, i), ITEM_MAIN_SIZE);
    }

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range should cover more items due to larger clip area.
     */
    EXPECT_GE(startIndex, 1);
    EXPECT_GE(endIndex, 4);
}

/**
 * @tc.name: ContentClipCustomLargerThanComponent003
 * @tc.desc: Test List with CUSTOM content clip larger than component (horizontal RTL)
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipCustomLargerThanComponent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create horizontal RTL List with CUSTOM content clip larger than component
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateHorizontalList();
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    auto shape = AceType::MakeRefPtr<ShapeRect>();
    shape->SetWidth(Dimension(500));
    shape->SetOffset(DimensionOffset(Dimension(-50), Dimension(0)));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    model.SetInitialIndex(1);
    model.SetSpace(Dimension(5));
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. check item layout.
     * @tc.expected: items should be layout within a larger clip area.
     */
    for (int32_t i = 0; i < 6; i++) {
        auto item = GetChildFrameNode(frameNode_, i);
        EXPECT_TRUE(item->IsActive());
        EXPECT_EQ(GetChildWidth(frameNode_, i), ITEM_MAIN_SIZE);
    }

    /**
     * @tc.steps: step3. check onScrollIndex
     * @tc.expected: index range should cover more items due to larger clip area.
     */
    EXPECT_GE(startIndex, 1);
    EXPECT_GE(endIndex, 4);
}

/**
 * @tc.name: ContentClipCustomScrollToItemInGroupTop001
 * @tc.desc: Test List with extended clip (top+bottom) and ScrollToItemInGroup to top
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipCustomScrollToItemInGroupTop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with extended clip area (top and bottom) and ListItemGroup
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateList();
    auto shape = AceType::MakeRefPtr<ShapeRect>();
    shape->SetHeight(Dimension(500));
    shape->SetOffset(DimensionOffset(Dimension(0), Dimension(-50)));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    model.SetSpace(Dimension(5));
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(1);
    CreateListItemGroups(1, V2::ListItemGroupStyle::NONE, 7);
    CreateDone();

    /**
     * @tc.steps: step2. Scroll to item in group at indexInGroup=2 with START alignment (top of component)
     */
    auto listPattern = frameNode_->GetPattern<ListPattern>();
    ASSERT_NE(listPattern, nullptr);
    listPattern->ScrollToItemInGroup(1, 2, false, ScrollAlign::START);
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step3. Check group item2 is at top of component (not clip area)
     * @tc.expected: group item2 Y-offset from list is 0
     */
    auto group = GetChildFrameNode(frameNode_, 1);
    ASSERT_NE(group, nullptr);
    auto groupItem2 = GetChildFrameNode(group, 2);
    ASSERT_NE(groupItem2, nullptr);
    EXPECT_TRUE(groupItem2->IsActive());
    EXPECT_EQ(GetChildY(group, 2) + GetChildY(frameNode_, 1), 0);
}

/**
 * @tc.name: ContentClipCustomScrollToItemInGroupCenter001
 * @tc.desc: Test List with extended clip (top+bottom) and ScrollToItemInGroup to center
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipCustomScrollToItemInGroupCenter001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with extended clip area (top and bottom) and ListItemGroup
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateList();
    auto shape = AceType::MakeRefPtr<ShapeRect>();
    shape->SetHeight(Dimension(500));
    shape->SetOffset(DimensionOffset(Dimension(0), Dimension(-50)));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    model.SetSpace(Dimension(5));
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(1);
    CreateListItemGroups(1, V2::ListItemGroupStyle::NONE, 5);
    CreateDone();

    /**
     * @tc.steps: step2. Scroll to item in group at indexInGroup=2 with CENTER alignment (center of component)
     */
    auto listPattern = frameNode_->GetPattern<ListPattern>();
    ASSERT_NE(listPattern, nullptr);
    listPattern->ScrollToItemInGroup(1, 2, false, ScrollAlign::CENTER);
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step3. Check group item2 is at center of component (not clip area)
     * @tc.expected: group item2 should be visible at component center position
     */
    auto group = GetChildFrameNode(frameNode_, 1);
    ASSERT_NE(group, nullptr);
    auto groupItem2 = GetChildFrameNode(group, 2);
    ASSERT_NE(groupItem2, nullptr);
    EXPECT_TRUE(groupItem2->IsActive());
    EXPECT_EQ(GetChildY(group, 2) + GetChildY(frameNode_, 1), 150); // 150: center item Y-offset
}

/**
 * @tc.name: ContentClipCustomScrollToItemInGroupBottom001
 * @tc.desc: Test List with extended clip (top+bottom) and ScrollToItemInGroup to bottom
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipCustomScrollToItemInGroupBottom001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with extended clip area (top and bottom) and ListItemGroup
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    ListModelNG model = CreateList();
    auto shape = AceType::MakeRefPtr<ShapeRect>();
    shape->SetHeight(Dimension(500));
    shape->SetOffset(DimensionOffset(Dimension(0), Dimension(-50)));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    model.SetSpace(Dimension(5));
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
    });
    CreateListItems(1);
    CreateListItemGroups(1, V2::ListItemGroupStyle::NONE, 5);
    CreateDone();

    /**
     * @tc.steps: step2. Scroll to item in group at indexInGroup=2 with END alignment (bottom of component)
     */
    auto listPattern = frameNode_->GetPattern<ListPattern>();
    ASSERT_NE(listPattern, nullptr);
    listPattern->ScrollToItemInGroup(1, 2, false, ScrollAlign::END);
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step3. Check group item2 is at bottom of component (not clip area)
     * @tc.expected: group item2 should be visible at component bottom position
     */
    auto group = GetChildFrameNode(frameNode_, 1);
    ASSERT_NE(group, nullptr);
    auto groupItem2 = GetChildFrameNode(group, 2);
    ASSERT_NE(groupItem2, nullptr);
    EXPECT_TRUE(groupItem2->IsActive());
    float groupItem2BottomOffset = GetChildY(group, 2) + GetChildY(frameNode_, 1) + GetChildHeight(group, 2);
    EXPECT_EQ(groupItem2BottomOffset, HEIGHT);
}

/**
 * @tc.name: ContentClipCustomStickyHeaderFooter001
 * @tc.desc: Test List with extended clip (top+bottom) and sticky header/footer at component boundaries
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipCustomStickyHeaderFooter001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with extended clip area (top and bottom) and ListItemGroup with header/footer
     */
    ListModelNG model = CreateList();
    auto shape = AceType::MakeRefPtr<ShapeRect>();
    shape->SetHeight(Dimension(500));
    shape->SetOffset(DimensionOffset(Dimension(0), Dimension(-50)));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    model.SetSpace(Dimension(5));
    model.SetSticky(V2::StickyStyle::BOTH);
    CreateListItems(1);
    CreateGroupWithSetting(1, V2::ListItemGroupStyle::NONE, 7);
    CreateDone();

    /**
     * @tc.steps: step2. Check header sticky position at component top boundary (not clip area top)
     * @tc.expected: header should be at Y=0 (component top), not at Y=-50 (clip area top)
     */
    UpdateCurrentOffset(-200.f);
    auto group = GetChildFrameNode(frameNode_, 1);
    ASSERT_NE(group, nullptr);
    auto header = GetChildFrameNode(group, 0);
    ASSERT_NE(header, nullptr);
    EXPECT_TRUE(header->IsActive());
    EXPECT_EQ(GetChildY(group, 0) + GetChildY(frameNode_, 1), 0); // Header at component top boundary (Y=0)

    /**
     * @tc.steps: step3. Check footer sticky position at component bottom boundary (not clip area bottom)
     * @tc.expected: footer should be at Y=HEIGHT (component bottom), not at Y=HEIGHT+50 (clip area bottom)
     */
    auto footerIndex = 1 + 7; // Group index (1) + item count (7)
    auto footer = GetChildFrameNode(group, footerIndex);
    ASSERT_NE(footer, nullptr);
    EXPECT_TRUE(footer->IsActive());
    float footerYOffset = GetChildY(group, footerIndex) + GetChildY(frameNode_, 1) + GetChildHeight(group, footerIndex);
    EXPECT_EQ(footerYOffset, HEIGHT); // Footer at component bottom boundary (Y=HEIGHT)
}

/**
 * @tc.name: ContentClipBoundaryWithLazyVGridLayout001
 * @tc.desc: Test List with LazyVGridLayout and ContentClip BOUNDARY mode
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipBoundaryWithLazyVGridLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with LazyVGridLayout and content clip
     */
    int32_t lazyGridVisibleStart = -1;
    int32_t lazyGridVisibleEnd = -1;

    ListModelNG listModel = CreateList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    PaddingProperty padding = CreatePadding(0, 0, 0, 150);
    layoutProperty_->UpdatePadding(padding);

    LazyVGridLayoutModel lazyGridModel;
    lazyGridModel.Create();
    ViewAbstract::SetWidth(CalcLength(WIDTH));
    lazyGridModel.SetColumnsTemplate("1fr 1fr");

    auto onVisibleIndexesChangeCallback = [&lazyGridVisibleStart, &lazyGridVisibleEnd](int32_t start, int32_t end) {
        lazyGridVisibleStart = start;
        lazyGridVisibleEnd = end;
    };
    lazyGridModel.SetOnVisibleIndexesChange(onVisibleIndexesChangeCallback);

    auto lazyGridFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto lazyGridPattern = lazyGridFrameNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(lazyGridPattern, nullptr);

    for (int32_t i = 0; i < 20; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewStackProcessor::GetInstance()->Pop();
    }

    CreateDone();

    /**
     * @tc.steps: step2. check LazyVGridLayout visible indexes
     * @tc.expected: visible indexes should exclude padding area
     */
    EXPECT_EQ(lazyGridVisibleStart, 0);
    EXPECT_EQ(lazyGridVisibleEnd, 5);
    EXPECT_LE(lazyGridVisibleEnd, lazyGridPattern->layoutInfo_->endIndex_);
}

/**
 * @tc.name: ContentClipBoundaryWithLazyVGridLayout002
 * @tc.desc: Test List with LazyVGridLayout and ContentClip BOUNDARY mode with scroll
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipBoundaryWithLazyVGridLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with LazyVGridLayout and content clip
     */
    int32_t lazyGridVisibleStart = -1;
    int32_t lazyGridVisibleEnd = -1;

    ListModelNG listModel = CreateList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    PaddingProperty padding = CreatePadding(0, 100, 0, 150);
    layoutProperty_->UpdatePadding(padding);

    LazyVGridLayoutModel lazyGridModel;
    lazyGridModel.Create();
    ViewAbstract::SetWidth(CalcLength(WIDTH));
    lazyGridModel.SetColumnsTemplate("1fr 1fr");

    auto onVisibleIndexesChangeCallback = [&lazyGridVisibleStart, &lazyGridVisibleEnd](int32_t start, int32_t end) {
        lazyGridVisibleStart = start;
        lazyGridVisibleEnd = end;
    };
    lazyGridModel.SetOnVisibleIndexesChange(onVisibleIndexesChangeCallback);

    auto lazyGridFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto lazyGridPattern = lazyGridFrameNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(lazyGridPattern, nullptr);

    for (int32_t i = 0; i < 30; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewStackProcessor::GetInstance()->Pop();
    }

    CreateDone();
    EXPECT_EQ(lazyGridVisibleStart, 0);
    EXPECT_EQ(lazyGridVisibleEnd, 3);

    /**
     * @tc.steps: step2. scroll and check visible indexes
     * @tc.expected: visible indexes should update correctly after scroll
     */
    UpdateCurrentOffset(-210.f);

    EXPECT_EQ(lazyGridVisibleStart, 4);
    EXPECT_EQ(lazyGridVisibleEnd, 7);
    EXPECT_GT(lazyGridVisibleStart, lazyGridPattern->layoutInfo_->startIndex_);
    EXPECT_LE(lazyGridVisibleEnd, lazyGridPattern->layoutInfo_->endIndex_);
}

/**
 * @tc.name: ContentClipSafeAreaWithLazyVGridLayout001
 * @tc.desc: Test List with LazyVGridLayout and ContentClip SAFE_AREA mode
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipSafeAreaWithLazyVGridLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with LazyVGridLayout and SAFE_AREA content clip
     */
    int32_t lazyGridVisibleStart = -1;
    int32_t lazyGridVisibleEnd = -1;

    ListModelNG listModel = CreateList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    PaddingProperty paddingProperty;
    paddingProperty.bottom = std::make_optional<CalcLength>(150);
    layoutProperty_->UpdateSafeAreaPadding(paddingProperty);

    LazyVGridLayoutModel lazyGridModel;
    lazyGridModel.Create();
    ViewAbstract::SetWidth(CalcLength(WIDTH));
    lazyGridModel.SetColumnsTemplate("1fr 1fr");

    auto onVisibleIndexesChangeCallback = [&lazyGridVisibleStart, &lazyGridVisibleEnd](int32_t start, int32_t end) {
        lazyGridVisibleStart = start;
        lazyGridVisibleEnd = end;
    };
    lazyGridModel.SetOnVisibleIndexesChange(onVisibleIndexesChangeCallback);

    auto lazyGridFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto lazyGridPattern = lazyGridFrameNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(lazyGridPattern, nullptr);

    for (int32_t i = 0; i < 20; i++) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewStackProcessor::GetInstance()->Pop();
    }

    CreateDone();
    FlushUITasks(frameNode_);

    /**
     * @tc.steps: step2. check visible indexes
     * @tc.expected: visible indexes should exclude safe area padding
     */
    EXPECT_EQ(lazyGridVisibleStart, 0);
    EXPECT_EQ(lazyGridVisibleEnd, 5);
    EXPECT_LE(lazyGridVisibleEnd, lazyGridPattern->layoutInfo_->endIndex_);
}

/**
 * @tc.name: ContentClipSafeAreaWithMultipleLazyVGridLayout001
 * @tc.desc: Test List with three LazyVGridLayout and ContentClip SAFE_AREA mode, verify preload range
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipSafeAreaWithMultipleLazyVGridLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with SAFE_AREA content clip and safeAreaPadding
     * List frame height is 400.f (HEIGHT), with 100.f bottom safeAreaPadding
     * First LazyVGridLayout: height 350.f (larger than content area but smaller than clip extension)
     * Second LazyVGridLayout: upper boundary at 350.f (just within clip extension range)
     * Third LazyVGridLayout: upper boundary at 700.f (outside first LazyVGridLayout)
     */
    ListModelNG listModel = CreateList();
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    PaddingProperty safeAreaPadding;
    safeAreaPadding.bottom = std::make_optional<CalcLength>(100.f);
    layoutProperty_->UpdateSafeAreaPadding(safeAreaPadding);

    // create 3 lazyVGridLayout
    for (int32_t i = 0; i < 3; i++) {
        LazyVGridLayoutModel lazyGridModel1;
        lazyGridModel1.Create();
        ViewAbstract::SetWidth(CalcLength(WIDTH));
        lazyGridModel1.SetColumnsTemplate("1fr 1fr");
        for (int32_t i = 0; i < 14; i++) {
            StackModelNG stackModel;
            stackModel.Create();
            ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
            ViewAbstract::SetHeight(CalcLength(50.f));
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }

    CreateDone();
    FlushUITasks(frameNode_);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0);
    EXPECT_EQ(pattern_->itemPosition_[0].endPos, 350);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 350);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 700);

    /**
     * @tc.steps: step2. Get LazyVGridLayout patterns
     */
    auto lazyGrid1 = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(lazyGrid1, nullptr);
    auto lazyGridPattern1 = lazyGrid1->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(lazyGridPattern1, nullptr);

    auto lazyGrid2 = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(1));
    ASSERT_NE(lazyGrid2, nullptr);
    auto lazyGridPattern2 = lazyGrid2->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(lazyGridPattern2, nullptr);

    auto lazyGrid3 = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(2));
    ASSERT_NE(lazyGrid3, nullptr);
    auto lazyGridPattern3 = lazyGrid3->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(lazyGridPattern3, nullptr);

    /**
     * @tc.steps: step3. Verify first LazyVGridLayout preload range
     * First grid at Y=0, height 350.f (14 items / 2 columns * 50.f = 7 rows)
     * First grid fully visible and within clip extension, callback triggered
     * @tc.expected: first grid visible and preload range should cover all 14 items
     */
    auto layoutInfo1 = lazyGridPattern1->layoutInfo_;
    ASSERT_NE(layoutInfo1, nullptr);
    EXPECT_EQ(lazyGridPattern1->GetVisibleIndexesRangeForCallback(), (std::make_pair<int32_t, int32_t>(0, 13)));
    EXPECT_EQ(layoutInfo1->startIndex_, 0);
    EXPECT_EQ(layoutInfo1->endIndex_, layoutInfo1->totalItemCount_ - 1);

    /**
     * @tc.steps: step4. Verify second LazyVGridLayout preload range
     * Second grid starts at Y=350.f, within clip extension (350.f < 400.f frame + 100.f safeAreaPadding extension)
     * Callback not triggered (no fully visible items), but preload triggered for items within grid
     * @tc.expected: second grid visible range -1 (callback not triggered), preload range items 0-3
     */
    auto layoutInfo2 = lazyGridPattern2->layoutInfo_;
    ASSERT_NE(layoutInfo2, nullptr);
    EXPECT_EQ(lazyGridPattern2->GetVisibleIndexesRangeForCallback(), (std::make_pair<int32_t, int32_t>(-1, -1)));
    EXPECT_EQ(layoutInfo2->startIndex_, 0);
    EXPECT_EQ(layoutInfo2->endIndex_, 3);

    /**
     * @tc.steps: step5. Verify third LazyVGridLayout preload range
     * Third grid starts at Y=700.f, outside clip extension (700.f > 400.f frame + 100.f
     * safeAreaPadding + 200.f clipExtension)
     * Callback not triggered, preload not triggered
     * @tc.expected: third grid visible range -1, preload range -1
     */
    auto layoutInfo3 = lazyGridPattern3->layoutInfo_;
    ASSERT_NE(layoutInfo3, nullptr);
    EXPECT_EQ(lazyGridPattern3->GetVisibleIndexesRangeForCallback(), (std::make_pair<int32_t, int32_t>(-1, -1)));
    EXPECT_EQ(layoutInfo3->startIndex_, -1);
    EXPECT_EQ(layoutInfo3->endIndex_, -1);
}

/**
 * @tc.name: ContentClipSafeAreaWithMultipleLazyVGridLayout002
 * @tc.desc: Test List with three LazyVGridLayout and ContentClip SAFE_AREA mode and stackFromEnd, verify preload range
 * @tc.type: FUNC
 */
HWTEST_F(ListContentClipTestNg, ContentClipSafeAreaWithMultipleLazyVGridLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List with SAFE_AREA content clip and safeAreaPadding and stackFromEnd
     * List frame height is 400.f (HEIGHT), with 100.f top safeAreaPadding
     * Third LazyVGridLayout: upper boundary at 50.f (just within clip extension range)
     * Second LazyVGridLayout: bottom boundary at 50.f (just within clip extension range)
     * First LazyVGridLayout: bottom boundary at -400 (outside first LazyVGridLayout)
     */
    ListModelNG listModel = CreateList();
    listModel.SetStackFromEnd(true);
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    PaddingProperty safeAreaPadding;
    safeAreaPadding.top = std::make_optional<CalcLength>(100.f);
    layoutProperty_->UpdateSafeAreaPadding(safeAreaPadding);
    
    // create 3 lazyVGridLayout
    for (int32_t i = 0; i < 3; i++) {
        LazyVGridLayoutModel lazyGridModel1;
        lazyGridModel1.Create();
        ViewAbstract::SetWidth(CalcLength(WIDTH));
        lazyGridModel1.SetColumnsTemplate("1fr 1fr");
        for (int32_t i = 0; i < 14; i++) {
            StackModelNG stackModel;
            stackModel.Create();
            ViewAbstract::SetWidth(CalcLength(1, DimensionUnit::PERCENT));
            ViewAbstract::SetHeight(CalcLength(50.f));
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }

    CreateDone();
    FlushUITasks(frameNode_);
    FlushIdleTask(pattern_);
    EXPECT_EQ(pattern_->itemPosition_[2].endPos, 300);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -50);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, -50);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -400);

    /**
     * @tc.steps: step2. Get LazyVGridLayout patterns
     */
    auto lazyGrid1 = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(lazyGrid1, nullptr);
    auto lazyGridPattern1 = lazyGrid1->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(lazyGridPattern1, nullptr);

    auto lazyGrid2 = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(1));
    ASSERT_NE(lazyGrid2, nullptr);
    auto lazyGridPattern2 = lazyGrid2->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(lazyGridPattern2, nullptr);

    auto lazyGrid3 = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(2));
    ASSERT_NE(lazyGrid3, nullptr);
    auto lazyGridPattern3 = lazyGrid3->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(lazyGridPattern3, nullptr);

    /**
     * @tc.steps: step3. Verify third LazyVGridLayout preload range (stackFromEnd order: first child is at bottom)
     * Third grid: startPos=-50.f, endPos=300.f, height 350.f
     * Covers visible area [0, 400] and clip extension [-200, 600]
     * @tc.expected: third grid visible and preload range should cover all 14 items
     */
    auto layoutInfo3 = lazyGridPattern3->layoutInfo_;
    ASSERT_NE(layoutInfo3, nullptr);
    EXPECT_EQ(lazyGridPattern3->GetVisibleIndexesRangeForCallback(), (std::make_pair<int32_t, int32_t>(0, 13)));
    EXPECT_EQ(layoutInfo3->startIndex_, 0);
    EXPECT_EQ(layoutInfo3->endIndex_, 13);

    /**
     * @tc.steps: step4. Verify second LazyVGridLayout preload range (stackFromEnd order)
     * Second grid: startPos=-400.f, endPos=-50.f, height 350.f
     * Completely outside clip extension [-200, 600]
     * @tc.expected: second grid visible range -1, preload range items 10-13 (bottom 2 rows)
     */
    auto layoutInfo2 = lazyGridPattern2->layoutInfo_;
    ASSERT_NE(layoutInfo2, nullptr);
    EXPECT_EQ(lazyGridPattern2->GetVisibleIndexesRangeForCallback(), (std::make_pair<int32_t, int32_t>(-1, -1)));
    EXPECT_EQ(layoutInfo2->startIndex_, 10);
    EXPECT_EQ(layoutInfo2->endIndex_, 13);

    /**
     * @tc.steps: step5. Verify first LazyVGridLayout preload range (stackFromEnd order)
     * First grid: startPos=-750.f, endPos=-400.f, height 350.f
     * Completely outside clip extension [-200, 600]
     * @tc.expected: first grid visible range -1, preload range -1
     */
    auto layoutInfo1 = lazyGridPattern1->layoutInfo_;
    ASSERT_NE(layoutInfo1, nullptr);
    EXPECT_EQ(lazyGridPattern1->GetVisibleIndexesRangeForCallback(), (std::make_pair<int32_t, int32_t>(-1, -1)));
    EXPECT_EQ(layoutInfo1->startIndex_, -1);
    EXPECT_EQ(layoutInfo1->endIndex_, -1);
}
} // namespace OHOS::Ace::NG
