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
} // namespace OHOS::Ace::NG
