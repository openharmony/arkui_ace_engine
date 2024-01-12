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

#include <cstddef>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/animation/animator.h"
#include "core/animation/spring_curve.h"
#include "core/components/common/layout/constants.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_layout_algorithm.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_method.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_layout_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_utils.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
constexpr float SWIPER_WIDTH = 480.f;
constexpr float SWIPER_HEIGHT = 800.f;
constexpr int32_t ITEM_NUMBER = 4;
constexpr int32_t DEFAULT_INTERVAL = 3000;
constexpr int32_t DEFAULT_DURATION = 400;
constexpr float DRAG_SPEED = 500.0f;
constexpr float DRAG_OFFSET_X = 50.0f;

class SwiperTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void CreateWithItem(const std::function<void(SwiperModelNG)>& callback = nullptr);
    void CreateItem(int32_t itemNumber = ITEM_NUMBER);

    void CreateChildWrapperAppendToHostWrapper(
        int32_t startIndex, int32_t endIndex, const RefPtr<LayoutWrapperNode>& hostWrapper);
    void InitLayoutWrapper(const RefPtr<FrameNode>& frameNode, RefPtr<LayoutAlgorithm>& algorithm,
        RefPtr<FrameNode>& indicatorNode, RefPtr<LayoutWrapperNode>& layoutWrapper);
    void InitChild(RefPtr<LayoutWrapperNode>& indicatorNodeWrapper, const RefPtr<FrameNode>& indicatorNode);
    void InitArrowLayoutWrapper(const RefPtr<FrameNode>& frameNode_, const std::string& arrowType,
        RefPtr<FrameNode>& arrowNode, RefPtr<LayoutWrapperNode>& arrowLayoutWrapper);
    void AddArrowChild(const RefPtr<FrameNode>& arrowNode, const RefPtr<LayoutWrapperNode>& arrowLayoutWrapper);
    void CreateSwiperLayoutWrapper(const RefPtr<FrameNode>& frameNode_, RefPtr<LayoutWrapperNode>& swiperLayoutWrapper);

    RefPtr<FrameNode> frameNode_;
    RefPtr<SwiperPattern> pattern_;
    RefPtr<SwiperEventHub> eventHub_;
    RefPtr<SwiperLayoutProperty> layoutProperty_;
    RefPtr<SwiperPaintProperty> paintProperty_;
    RefPtr<SwiperAccessibilityProperty> accessibilityProperty_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_SWIPER_SWIPER_TEST_NG_H