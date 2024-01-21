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

#include <cstdint>
#include <map>
#include <memory>

#include "gtest/gtest.h"

#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/utils/utils.h"
#define protected public
#define private public
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_with_options_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/base/mock_drag_window.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

namespace OHOS::Ace::NG {
namespace {
using namespace testing;
using namespace testing::ext;
constexpr float GRID_WIDTH = 480.f;
constexpr float GRID_HEIGHT = 800.f;
constexpr int32_t VIEW_LINE_NUMBER = 4;
constexpr float ITEM_WIDTH = GRID_WIDTH / VIEW_LINE_NUMBER;
constexpr float ITEM_HEIGHT = GRID_HEIGHT / VIEW_LINE_NUMBER;
constexpr Dimension GRIDITEM_FOCUS_INTERVAL = 3.0_vp;
constexpr Dimension BORDER_RADIUS = 8.0_vp;
constexpr float COL_GAP = 10.f;
constexpr float ROW_GAP = 5.f;
constexpr float BIG_ROW_GAP = 700.f;
constexpr float MEDIUM_ROW_GAP = 75.f;
} // namespace

class GridTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void Create(const std::function<void(GridModelNG)>& callback = nullptr);
    static void CreateItem(int32_t itemNumber = 10, float width = NULL_VALUE, float height = NULL_VALUE,
        GridItemStyle gridItemStyle = GridItemStyle::NONE);
    static void CreateColItem(int32_t itemNumber, GridItemStyle gridItemStyle = GridItemStyle::NONE);
    static void CreateRowItem(int32_t itemNumber, GridItemStyle gridItemStyle = GridItemStyle::NONE);
    static void CreateFixedItem(int32_t itemNumber, GridItemStyle gridItemStyle = GridItemStyle::NONE);
    static void CreateBigItem(int32_t rowStart = NULL_VALUE, int32_t rowEnd = NULL_VALUE,
        int32_t colStart = NULL_VALUE, int32_t colEnd = NULL_VALUE, float width = NULL_VALUE,
        float height = NULL_VALUE);
    static void CreateBigColItem(int32_t colStart, int32_t colEnd);
    static void CreateBigRowItem(int32_t rowStart, int32_t rowEnd);
    void ScrollTo(float position);
    void UpdateCurrentOffset(float offset, int32_t source = SCROLL_FROM_UPDATE);
    
    RefPtr<FrameNode> frameNode_;
    RefPtr<GridPattern> pattern_;
    RefPtr<GridEventHub> eventHub_;
    RefPtr<GridLayoutProperty> layoutProperty_;
    RefPtr<GridAccessibilityProperty> accessibilityProperty_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_GRID_GRID_TEST_NG_H
