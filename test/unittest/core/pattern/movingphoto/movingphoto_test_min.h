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

#ifndef TEST_UNITTEST_CORE_PATTERN_MOVINGPHOTO_MOVINGPHOTO_TEST_MIN_H
#define TEST_UNITTEST_CORE_PATTERN_MOVINGPHOTO_MOVINGPHOTO_TEST_MIN_H

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_media_player.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_surface.h"
#include "test/mock/frameworks/core/common/mock_image_analyzer_manager.h"
#include "test/mock/frameworks/base/image/mock_pixel_map.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "base/geometry/ng/size_t.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/resource/internal_resource.h"
#include "core/common/ai/image_analyzer_mgr.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/video/video_theme.h"
#include "core/components_ng/pattern/video/video_utils.h"
#include "core/components/image/image_event.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/drag_event.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/image/image_source_info.h"
#include "component_ext/movingphoto/movingphoto_styles.h"
#include "component_ext/movingphoto/movingphoto_pattern.h"
#include "component_ext/movingphoto/movingphoto_node.h"
#include "component_ext/movingphoto/movingphoto_model_ng.h"
#include "component_ext/movingphoto/movingphoto_layout_property.h"
#include "component_ext/movingphoto/movingphoto_layout_algorithm.h"
#include "component_ext/movingphoto/movingphoto_utils.h"

namespace OHOS::Ace::NG {

struct TestProperty {
    std::optional<std::string> imageSrc;
    std::optional<bool> muted;
    std::optional<ImageFit> objectFit;
    std::optional<RefPtr<MovingPhotoController>> movingPhotoController;
};

constexpr bool MUTED_VALUE = false;
    constexpr ImageFit MOVINGPHOTO_IMAGE_FIT = ImageFit::COVER;
    constexpr uint32_t MOVINGPHOTO_CHILDREN_NUM = 2;
    const std::string MOVINGPHOTO_IMAGE_SRC = "common/video.mp4";
    constexpr float MAX_WIDTH = 400.0f;
    constexpr float MAX_HEIGHT = 400.0f;
    constexpr float MP_WIDTH = 300.0f;
    constexpr float MOVINGPHOTO_HEIGHT = 300.0f;
    constexpr float SCREEN_WIDTH_SMALL = 500.0f;
    constexpr float SCREEN_HEIGHT_SMALL = 1000.0f;
    const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
    const SizeF MOVINGPHOTO_SIZE(MP_WIDTH, MOVINGPHOTO_HEIGHT);
    constexpr int32_t SLIDER_INDEX = 2;
    constexpr int32_t MOVINGPHOTO_NODE_ID_1 = 1;
    constexpr int32_t MOVINGPHOTO_NODE_ID_2 = 2;

// Base test class for movingphoto tests
class MovingPhotoTestBase : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override {}

protected:
    static RefPtr<FrameNode> CreateMovingPhotoNode(TestProperty& testProperty);
    static TestProperty testProperty_;
};

} // namespace OHOS::Ace::NG

#endif // TEST_UNITTEST_CORE_PATTERN_MOVINGPHOTO_MOVINGPHOTO_TEST_MIN_H
