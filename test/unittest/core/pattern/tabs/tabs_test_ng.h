/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_TABS_TABS_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_TABS_TABS_TEST_NG_H

#include "test/unittest/core/pattern/test_ng.h"
#define private public
#define protected public
#include "test/mock/core/animation/mock_animation_manager.h"

#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_item_pattern.h"
#include "core/common/container.h"

namespace OHOS::Ace::NG {
constexpr float TABS_WIDTH = 720.f;
constexpr float TABS_HEIGHT = 400.f;
constexpr int32_t TABCONTENT_NUMBER = 4;
constexpr float FIRST_ITEM_WIDTH = 800.0f;
constexpr float FIRST_ITEM_HEIGHT = 800.0f;
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
constexpr float TABBAR_WIDTH = 50.0f;
constexpr float TABBAR_HEIGHT = 40.0f;
constexpr float SWIPER_WIDTH = 750.0f;
constexpr float SWIPER_HEIGHT = 500.0f;
constexpr float DIVIDER_STROKE_WIDTH = 10.0f;
constexpr float TABS_PADDING = 20.0f;
const int BEGIN_INDEX = 0;
const int CURRENT_INDEX = 1;
const OffsetF CURRENT_OFFSET(1.0f, 1.0f);
constexpr float TEST_MASK_A_RADIUS_RATIO = 0.0f;
constexpr float TEST_MASK_B_RADIUS_RATIO = 1.414f;
constexpr float TEST_MASK_MIDDLE_RADIUS_RATIO = (TEST_MASK_A_RADIUS_RATIO + TEST_MASK_B_RADIUS_RATIO) / 2.0f;
constexpr int32_t TEST_DIVIDER_INDEX = 1;
constexpr int32_t TEST_TAB_BAR_INDEX = 2;
constexpr int32_t TEST_SELECTED_MASK_COUNT = 2;
constexpr int32_t TEST_UNSELECTED_MASK_COUNT = 1;
constexpr int32_t LG_COLUMN_NUM = 12;
constexpr int32_t XS_COLUMN_NUM = 2;
constexpr int32_t TAB_BAR_SIZE = 56.0f;
constexpr float BAR_ITEM_SIZE = 10.0f;
constexpr float BIG_FONT_SIZE_SCALE = 1.75f;
constexpr float LARGE_FONT_SIZE_SCALE = 2.0f;
constexpr float MAX_FONT_SIZE_SCALE = 3.2f;
constexpr double BIG_DIALOG_WIDTH = 216.0;
constexpr double MAX_DIALOG_WIDTH = 256.0;
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.svg";
constexpr int8_t MASK_COUNT = 2;
constexpr float DRAG_DELTA = TABS_WIDTH;

class TabsTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetTabs();
    TabsModelNG CreateTabs(BarPosition barPosition = BarPosition::START, int32_t index = 0);
    TabContentModelNG CreateTabContent();
    TabContentModelNG CreateTabContentWithDeepRender(std::function<void()>&& deepRenderFunc);
    void CreateTabContents(int32_t itemNumber = TABCONTENT_NUMBER);
    void CreateTabContentsWithBuilder(int32_t itemNumber = TABCONTENT_NUMBER);
    void CreateTabsDone(TabsModelNG model);
    TabBarBuilderFunc TabBarItemBuilder();
    void CreateTabContentTabBarStyle(TabBarStyle tabBarStyle);
    void CreateTabContentTabBarStyleWithBuilder(TabBarStyle tabBarStyle);
    void ChangeIndex(int32_t index);
    void HandleClick(int32_t index);
    void HandleMouseEvent(MouseAction action, Offset location);
    void HandleHoverEvent(bool isHover);
    GestureEvent CreateDragInfo(bool moveDirection);
    void MockPaintRect(const RefPtr<FrameNode>& frameNode);
    void MockPaintRectSmallSize(const RefPtr<FrameNode>& frameNode);
    RefPtr<TabBarModifier> OnDraw();
    AssertionResult CurrentIndex(int32_t expectIndex);
    AssertionResult VerifyBackgroundColor(int32_t itemIndex, Color expectColor);

    RefPtr<TabsNode> frameNode_;
    RefPtr<TabsPattern> pattern_;
    RefPtr<TabsLayoutProperty> layoutProperty_;

    RefPtr<FrameNode> swiperNode_;
    RefPtr<SwiperPattern> swiperPattern_;
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty_;
    RefPtr<SwiperPaintProperty> swiperPaintProperty_;
    RefPtr<SwiperController> swiperController_;

    RefPtr<FrameNode> tabBarNode_;
    RefPtr<TabBarPattern> tabBarPattern_;
    RefPtr<TabBarLayoutProperty> tabBarLayoutProperty_;
    RefPtr<TabBarPaintProperty> tabBarPaintProperty_;
    RefPtr<TabBarAccessibilityProperty> tabBarAccessibilityProperty_;

    RefPtr<FrameNode> dividerNode_;
    RefPtr<DividerRenderProperty> dividerRenderProperty_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_TABS_TABS_TEST_NG_H
