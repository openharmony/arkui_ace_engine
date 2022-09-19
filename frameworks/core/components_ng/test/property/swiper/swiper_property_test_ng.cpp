/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "gtest/gtest.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/animation/cubic_curve.h"
#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/pattern/swiper/swiper_view.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t INDEX_DEFAULT = 1;
constexpr int32_t SWIPER_LAYOUT_PROPERTY_INDEX_1 = -1;
constexpr int32_t SWIPER_LAYOUT_PROPERTY_INDEX_2 = 0;
constexpr int32_t SWIPER_LAYOUT_PROPERTY_INDEX_3 = 1;
const std::vector<int32_t> SWIPER_LAYOUT_PROPERTY_INDEX = { SWIPER_LAYOUT_PROPERTY_INDEX_1,
                                                            SWIPER_LAYOUT_PROPERTY_INDEX_2,
                                                            SWIPER_LAYOUT_PROPERTY_INDEX_3 };

const bool SWIPER_PAINT_PROPERTY_AUTOPLAY = false;
constexpr int32_t SWIPER_PAINT_PROPERTY_INTERVAL_DEFAULT = 3000;
constexpr int32_t SWIPER_PAINT_PROPERTY_INTERVAL_1 = 5000;
constexpr int32_t SWIPER_PAINT_PROPERTY_INTERVAL_2 = -100;
const std::vector<int32_t> SWIPER_PAINT_PROPERTY_INTERVAL = { SWIPER_PAINT_PROPERTY_INTERVAL_1,
                                                              SWIPER_PAINT_PROPERTY_INTERVAL_2 };
const bool SWIPER_LAYOUT_PROPERTY_SHOW_INDICATOR = false;
const bool SWIPER_PAINT_PROPERTY_LOOP = false;
const SwiperDisplayMode SWIPER_LAYOUT_PROPERTY_DISPLAY_MODE = SwiperDisplayMode::AUTO_LINEAR;
const std::vector<EdgeEffect> SWIPER_PAINT_PROPERTY_EDGE_EFFECT = { EdgeEffect::FADE,
                                                                    EdgeEffect::NONE,
                                                                    EdgeEffect::SPRING };

const RefPtr<Curve> LINEAR = AceType::MakeRefPtr<LinearCurve>();
const RefPtr<Curve> SINE = AceType::MakeRefPtr<SineCurve>();
const RefPtr<Curve> EASE = AceType::MakeRefPtr<CubicCurve>(0.25f, 0.1f, 0.25f, 1.0f);
const RefPtr<Curve> SMOOTH = AceType::MakeRefPtr<CubicCurve>(0.4f, 0.0f, 0.4f, 1.0f);
const RefPtr<Curve> ELASTICS = AceType::MakeRefPtr<ElasticsCurve>(2.0f);
const std::vector<RefPtr<Curve>> SWIPER_PAINT_PROPERTY_CURVE = { LINEAR, SINE, EASE, SMOOTH, ELASTICS };

const std::vector<int32_t> SWIPER_PAINT_PROPERTY_DURATION = { 100, 2000, 400 };
constexpr Dimension SWIPER_PAINT_PROPERTY_ITEM_SPACE_1 = Dimension(0);
constexpr Dimension SWIPER_PAINT_PROPERTY_ITEM_SPACE_2 = Dimension(1);
constexpr Dimension SWIPER_PAINT_PROPERTY_ITEM_SPACE_3 = Dimension(10);
const std::vector<Dimension> SWIPER_PAINT_PROPERTY_ITEM_SPACE = { SWIPER_PAINT_PROPERTY_ITEM_SPACE_1,
                                                                  SWIPER_PAINT_PROPERTY_ITEM_SPACE_2,
                                                                  SWIPER_PAINT_PROPERTY_ITEM_SPACE_3 };
                                                                
const std::vector<int32_t> SWIPER_PAINT_PROPERTY_CACHED_COUNT = { -2, 1, 5, 10 };
const std::vector<int32_t> SWIPER_PAINT_PROPERTY_DISPLAY_COUNT = { -2, 0, 2, 10 };
const bool SWIPER_LAYOUT_PROPERTY_SHOW_DISABLE_SWIPE = true;

const std::vector<Axis> SWIPER_PAINT_PROPERTY_DIRECTION = { Axis::HORIZONTAL,
                                                            Axis::FREE,
                                                            Axis::NONE,
                                                            Axis::VERTICAL };
} // namespace

class SwiperPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: SwiperLayoutPropertyTest001
 * @tc.desc: Set one index value into SwiperLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperLayoutPropertyTest001, TestSize.Level1)
{
    SwiperView::Create();
    SwiperView::SetIndex(INDEX_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto swiperLayoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_FALSE(swiperLayoutProperty == nullptr);
    EXPECT_EQ(swiperLayoutProperty->GetIndex().value_or(0), INDEX_DEFAULT);
}

/**
 * @tc.name: SwiperLayoutPropertyTest002
 * @tc.desc: set a lot of index values into SwiperLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperLayoutPropertyTest002, TestSize.Level1)
{
    for (int32_t i = 0; i < SWIPER_LAYOUT_PROPERTY_INDEX.size(); ++i) {
        SwiperView::Create();
        SwiperView::SetIndex(SWIPER_LAYOUT_PROPERTY_INDEX[i]);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto swiperLayoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
        EXPECT_FALSE(swiperLayoutProperty == nullptr);
        EXPECT_EQ(swiperLayoutProperty->GetIndex().value_or(0), SWIPER_LAYOUT_PROPERTY_INDEX[i]);
    }
}

/**
 * @tc.name: SwiperPaintPropertyTest003
 * @tc.desc: set autoPlay value into SwiperLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperPaintPropertyTest003, TestSize.Level1)
{
    SwiperView::Create();
    SwiperView::SetAutoPlay(SWIPER_PAINT_PROPERTY_AUTOPLAY);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode == nullptr, false);
    auto swiperPaintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();
    EXPECT_FALSE(swiperPaintProperty == nullptr);
    EXPECT_EQ(swiperPaintProperty->GetAutoPlay().value_or(false), SWIPER_PAINT_PROPERTY_AUTOPLAY);
}

/**
 * @tc.name: SwiperPaintPropertyTest004
 * @tc.desc: set a lot of intertval values into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperPaintPropertyTest004, TestSize.Level1)
{
    for (const auto& interval : SWIPER_PAINT_PROPERTY_INTERVAL) {
        SwiperView::Create();
        SwiperView::SetAutoPlayInterval(interval);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto swiperPaintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();
        EXPECT_FALSE(swiperPaintProperty == nullptr);
        EXPECT_EQ(swiperPaintProperty->GetAutoPlayInterval().value_or(SWIPER_PAINT_PROPERTY_INTERVAL_DEFAULT),
            interval);
    }
}

/**
 * @tc.name: SwiperLayoutPropertyTest005
 * @tc.desc: set showIndicator value into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperLayoutPropertyTest005, TestSize.Level1)
{
    SwiperView::Create();
    SwiperView::SetShowIndicator(SWIPER_LAYOUT_PROPERTY_SHOW_INDICATOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode == nullptr, false);
    auto swiperLayoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_FALSE(swiperLayoutProperty == nullptr);
    EXPECT_EQ(swiperLayoutProperty->GetShowIndicator().value_or(false), SWIPER_LAYOUT_PROPERTY_SHOW_INDICATOR);
}

/**
 * @tc.name: SwiperPaintPropertyTest006
 * @tc.desc: set loop value into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperPaintPropertyTest006, TestSize.Level1)
{
    SwiperView::Create();
    SwiperView::SetLoop(SWIPER_PAINT_PROPERTY_LOOP);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode == nullptr, false);
    auto swiperPaintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();
    EXPECT_FALSE(swiperPaintProperty == nullptr);
    EXPECT_EQ(swiperPaintProperty->GetLoop().value_or(false), SWIPER_PAINT_PROPERTY_LOOP);
}

/**
 * @tc.name: SwiperLayoutPropertyTest007
 * @tc.desc: set one displayMode value into SwiperLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperLayoutPropertyTest007, TestSize.Level1)
{
    SwiperView::Create();
    SwiperView::SetDisplayMode(SWIPER_LAYOUT_PROPERTY_DISPLAY_MODE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto swiperLayoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_FALSE(swiperLayoutProperty == nullptr);
    EXPECT_EQ(swiperLayoutProperty->GetDisplayMode().value_or(SwiperDisplayMode::STRETCH),
        SWIPER_LAYOUT_PROPERTY_DISPLAY_MODE);
}

/**
 * @tc.name: SwiperPaintPropertyTest008
 * @tc.desc: set one effectMode value into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperPaintPropertyTest008, TestSize.Level1)
{
    for (const auto& effectMode : SWIPER_PAINT_PROPERTY_EDGE_EFFECT) {
        SwiperView::Create();
        SwiperView::SetEdgeEffect(effectMode);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_FALSE(frameNode == nullptr);
        auto swiperPaintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();
        EXPECT_FALSE(swiperPaintProperty == nullptr);
        EXPECT_EQ(swiperPaintProperty->GetEdgeEffect().value_or(EdgeEffect::FADE), effectMode);
    }
}

/**
 * @tc.name: SwiperPaintPropertyTest009
 * @tc.desc: set curve value into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperPaintPropertyTest009, TestSize.Level1)
{
    for (int32_t i = 0; i < static_cast<int32_t>(SWIPER_PAINT_PROPERTY_CURVE.size()); ++i) {
        SwiperView::Create();
        SwiperView::SetCurve(SWIPER_PAINT_PROPERTY_CURVE[i]);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto swiperPaintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();
        EXPECT_FALSE(swiperPaintProperty == nullptr);
        EXPECT_EQ(swiperPaintProperty->GetCurve().value_or(Curves::EASE), SWIPER_PAINT_PROPERTY_CURVE[i]);
    }
}

/**
 * @tc.name: SwiperPaintPropertyTest0010
 * @tc.desc: set duration value into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperPaintPropertyTest0010, TestSize.Level1)
{
    for (const auto& duration : SWIPER_PAINT_PROPERTY_DURATION) {
        SwiperView::Create();
        SwiperView::SetDuration(duration);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto swiperPaintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();
        EXPECT_FALSE(swiperPaintProperty == nullptr);
        EXPECT_EQ(swiperPaintProperty->GetDuration().value_or(Curves::EASE), duration);
    }
}

/**
 * @tc.name: SwiperLayoutPropertyTest0011
 * @tc.desc: set a lot of itemSpace values into SwiperLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperLayoutPropertyTest0011, TestSize.Level1)
{
    for (const auto& itemSpace : SWIPER_PAINT_PROPERTY_ITEM_SPACE) {
        SwiperView::Create();
        SwiperView::SetItemSpace(itemSpace);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto swiperLayoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
        EXPECT_FALSE(swiperLayoutProperty == nullptr);
        EXPECT_EQ(swiperLayoutProperty->GetItemSpace().value_or(Dimension(0)).Value(),
            static_cast<int32_t>(itemSpace.Value()));
    }
}

/**
 * @tc.name: SwiperLayoutPropertyTest0012
 * @tc.desc: set a lot of cachedCount values into SwiperLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperLayoutPropertyTest0012, TestSize.Level1)
{
    for (int32_t i = 0; i < SWIPER_PAINT_PROPERTY_CACHED_COUNT.size(); ++i) {
        SwiperView::Create();
        SwiperView::SetCachedCount(SWIPER_PAINT_PROPERTY_CACHED_COUNT[i]);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto swiperLayoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
        EXPECT_FALSE(swiperLayoutProperty == nullptr);
        EXPECT_EQ(swiperLayoutProperty->GetCachedCount().value_or(1), SWIPER_PAINT_PROPERTY_CACHED_COUNT[i]);
    }
}

/**
 * @tc.name: SwiperLayoutPropertyTest0013
 * @tc.desc: set a lot of displayCount values into SwiperLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperLayoutPropertyTest0013, TestSize.Level1)
{
    for (int32_t i = 0; i < SWIPER_PAINT_PROPERTY_DISPLAY_COUNT.size(); ++i) {
        SwiperView::Create();
        SwiperView::SetDisplayCount(SWIPER_PAINT_PROPERTY_DISPLAY_COUNT[i]);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto swiperLayoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
        EXPECT_FALSE(swiperLayoutProperty == nullptr);
        EXPECT_EQ(swiperLayoutProperty->GetDisplayCount().value_or(1), SWIPER_PAINT_PROPERTY_DISPLAY_COUNT[i]);
    }
}

/**
 * @tc.name: SwiperPaintPropertyTest0014
 * @tc.desc: set disableSwipe value into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperPaintPropertyTest0014, TestSize.Level1)
{
    SwiperView::Create();
    SwiperView::SetDisableSwipe(SWIPER_LAYOUT_PROPERTY_SHOW_DISABLE_SWIPE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode == nullptr, false);
    auto swiperPaintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();
    EXPECT_FALSE(swiperPaintProperty == nullptr);
    EXPECT_EQ(swiperPaintProperty->GetDisableSwipe().value_or(false), SWIPER_LAYOUT_PROPERTY_SHOW_DISABLE_SWIPE);
}

/**
 * @tc.name: SwiperLayoutPropertyTest0015
 * @tc.desc: set one direction value into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperPaintPropertyTest0015, TestSize.Level1)
{
    for (const auto& direction : SWIPER_PAINT_PROPERTY_DIRECTION) {
        SwiperView::Create();
        SwiperView::SetDirection(direction);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_FALSE(frameNode == nullptr);
        auto swiperLayoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
        EXPECT_FALSE(swiperLayoutProperty == nullptr);
        EXPECT_EQ(swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL), direction);
    }
}

/**
 * @tc.name: SwiperPropertyTest0016
 * @tc.desc: set id into Swiper and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPropertyTestNg, SwiperPropertyTest0016, TestSize.Level1)
{
    SwiperView::Create();
    ViewAbstract::SetInspectorId(V2::SWIPER_ETS_TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    EXPECT_EQ(frameNode->GetInspectorId().value_or(""), V2::SWIPER_ETS_TAG);
}
} // namespace OHOS::Ace::NG
