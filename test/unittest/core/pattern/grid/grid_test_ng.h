/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_GRID_GRID_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_GRID_GRID_TEST_NG_H

#include "test/unittest/core/pattern/scrollable/scrollable_utils_test_ng.h"

#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#define protected public
#define private public
#include "core/components_ng/pattern/grid/grid_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension GRIDITEM_FOCUS_INTERVAL = 3.0_vp;
constexpr Dimension BORDER_RADIUS = 8.0_vp;
constexpr float COL_GAP = 10.f;
constexpr float ROW_GAP = 5.f;
constexpr float BIG_ROW_GAP = 700.f;
constexpr float MEDIUM_ROW_GAP = 35.f;
constexpr int32_t FILL_VALUE = -2;
} // namespace

class GridTestNg : public ScrollableUtilsTestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetGrid();
    GridModelNG CreateGrid();
    GridModelNG CreateRepeatGrid(int32_t itemNumber, std::function<float(uint32_t)>&& getSize);
    void CreateItemsInLazyForEach(int32_t itemNumber, std::function<float(uint32_t)>&& getSize);

    /**
     * @param height -2 corresponds to 100% height
     */
    GridItemModelNG CreateGridItem(
        float width = NULL_VALUE, float height = NULL_VALUE, GridItemStyle gridItemStyle = GridItemStyle::NONE);
    void CreateGridItems(int32_t itemNumber = 10, float width = NULL_VALUE, float height = NULL_VALUE,
        GridItemStyle gridItemStyle = GridItemStyle::NONE);
    void CreateFocusableGridItems(int32_t itemNumber = 10, float width = NULL_VALUE, float height = NULL_VALUE,
        GridItemStyle gridItemStyle = GridItemStyle::NONE);
    void CreateFixedItems(int32_t itemNumber, GridItemStyle gridItemStyle = GridItemStyle::NONE);
    void CreateFixedHeightItems(int32_t itemNumber, float height, GridItemStyle gridItemStyle = GridItemStyle::NONE);
    void CreateFixedWidthItems(int32_t itemNumber, float width, GridItemStyle gridItemStyle = GridItemStyle::NONE);
    void CreateBigItem(int32_t rowStart = NULL_VALUE, int32_t rowEnd = NULL_VALUE, int32_t colStart = NULL_VALUE,
        int32_t colEnd = NULL_VALUE, float width = NULL_VALUE, float height = NULL_VALUE);
    void CreateFocusableBigItem(int32_t rowStart = NULL_VALUE, int32_t rowEnd = NULL_VALUE,
        int32_t colStart = NULL_VALUE, int32_t colEnd = NULL_VALUE);
    void CreateBigColItem(int32_t colStart, int32_t colEnd);
    void CreateBigRowItem(int32_t rowStart, int32_t rowEnd);
    void AddFixedHeightItems(int32_t cnt, float height);
    void UpdateCurrentOffset(float offset, int32_t source = SCROLL_FROM_UPDATE);
    void CreateAdaptChildSizeGridItems(int32_t itemNumber, GridItemStyle gridItemStyle = GridItemStyle::NONE);
    ColumnModelNG CreateColumn(float width = NULL_VALUE, float height = NULL_VALUE);
    void CreateColumns(int32_t itemNumber = 10, float width = NULL_VALUE, float height = NULL_VALUE);

    void CheckPreloadListEqual(const std::list<int32_t>& expectedList) const;
    RefPtr<FrameNode> GetItem(int32_t idx, bool asCache);

    RefPtr<GridPattern> pattern_;
    RefPtr<GridEventHub> eventHub_;
    RefPtr<GridLayoutProperty> layoutProperty_;
    RefPtr<GridAccessibilityProperty> accessibilityProperty_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_GRID_GRID_TEST_NG_H
