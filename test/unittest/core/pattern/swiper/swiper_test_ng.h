/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_SWIPER_SWIPER_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_SWIPER_SWIPER_TEST_NG_H

#include "test/unittest/core/pattern/test_ng.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"

#include "core/components/swiper/swiper_component.h"
#include "core/components_ng/pattern/swiper/swiper_helper.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper/arc_swiper_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/circle_dot_indicator/circle_dot_indicator_layout_algorithm.h"
#include "core/components_ng/pattern/swiper_indicator/circle_dot_indicator/circle_dot_indicator_paint_method.h"
#include "core/components_ng/pattern/swiper_indicator/circle_dot_indicator/circle_dot_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/arc_swiper_indicator_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model_ng.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
constexpr float SWIPER_WIDTH = 480.f;
constexpr float SWIPER_HEIGHT = 800.f;
constexpr int32_t ITEM_NUMBER = 4;
constexpr int32_t DEFAULT_INTERVAL = 3000;
constexpr int32_t DEFAULT_DURATION = 400;
constexpr float CAPTURE_MARGIN_SIZE = 15.0f;
const SwiperArrowParameters ARROW_PARAMETERS = { true, true, Dimension(24.f), Color::BLACK, Dimension(18.f),
    Color::FromString("#182431") };
const Color HOVER_ARROW_COLOR = Color::GRAY;
const Color CLICK_ARROW_COLOR = Color::FromString("#19182431");
constexpr double ARROW_DISABLED_ALPHA = 0.5;
const Color INDICATOR_TEXT_FONT_COLOR = Color::FromString("#ff182431");
const Dimension INDICATOR_TEXT_FONT_SIZE = Dimension(14.f);
const FontWeight INDICATOR_TEXT_FONT_WEIGHT = FontWeight::W800;
constexpr float PRE_MARGIN = 10.f;
constexpr float NEXT_MARGIN = 20.f;

class SwiperTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetSwiper();
    void CreateSwiperDone();
    SwiperModelNG CreateSwiper();
    SwiperModelNG CreateArcSwiper();
    void CreateSwiperItems(int32_t itemNumber = ITEM_NUMBER);
    void CreateItemWithSize(float width, float height);
    void CreateDefaultSwiper();
    void CreateWithArrow();
    void ShowNext();
    void ShowPrevious();
    void ChangeIndex(int32_t index);
    void SwipeTo(int32_t index);
    void SwipeToWithoutAnimation(int32_t index);
    void RemoveSwiperItem(int32_t index);
    void AddSwiperItem(int32_t slot);
    AssertionResult DigitText(std::u16string expectDigit);

    void InitCaptureTest();

    RefPtr<FrameNode> frameNode_;
    RefPtr<SwiperPattern> pattern_;
    RefPtr<SwiperEventHub> eventHub_;
    RefPtr<SwiperLayoutProperty> layoutProperty_;
    RefPtr<SwiperPaintProperty> paintProperty_;
    RefPtr<SwiperAccessibilityProperty> accessibilityProperty_;
    RefPtr<SwiperController> controller_;

    RefPtr<FrameNode> indicatorNode_;
    RefPtr<FrameNode> leftArrowNode_;
    RefPtr<FrameNode> rightArrowNode_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_SWIPER_SWIPER_TEST_NG_H
