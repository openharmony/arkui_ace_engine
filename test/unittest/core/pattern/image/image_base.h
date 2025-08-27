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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_TEXTFIELD_TEXTINPUT_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_TEXTFIELD_TEXTINPUT_TEST_NG_H

#include <optional>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_canvas_image.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/image/image_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/image/image_paint_method.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/mouse_event.h"
#include "core/image/image_source_info.h"
#include "interfaces/native/node/resource.h"

#undef private
#undef protected

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
constexpr double RADIUS_DEFAULT = 50.0;
constexpr double RADIUS_EXTREME = 300.0;
constexpr double IMAGE_WIDTH_DEFAULT = -1.0;
constexpr double IMAGE_HEIGHT_DEFAULT = -1.0;
constexpr double IMAGE_COMPONENTWIDTH_DEFAULT = -1.0;
constexpr double IMAGE_COMPONENTHEIGHT_DEFAULT = -1.0;
constexpr double WIDTH = 400.0;
constexpr double HEIGHT = 500.0;
constexpr double IMAGE_COMPONENT_MAXSIZE_WIDTH = 600.0;
constexpr double IMAGE_COMPONENT_MAXSIZE_HEIGHT = 700.0;
constexpr double IMAGE_SOURCESIZE_WIDTH = 300.0;
constexpr double IMAGE_SOURCESIZE_HEIGHT = 200.0;
constexpr double ALT_SOURCESIZE_WIDTH = 100.0;
constexpr double ALT_SOURCESIZE_HEIGHT = 200.0;
constexpr Dimension IMAGE_SOURCEINFO_WIDTH = Dimension(IMAGE_SOURCESIZE_WIDTH);
constexpr Dimension IMAGE_SOURCEINFO_HEIGHT = Dimension(IMAGE_SOURCESIZE_HEIGHT);
constexpr Dimension ALT_SOURCEINFO_WIDTH = Dimension(ALT_SOURCESIZE_WIDTH);
constexpr Dimension ALT_SOURCEINFO_HEIGHT = Dimension(ALT_SOURCESIZE_HEIGHT);
constexpr ImageFit IMAGE_FIT_DEFAULT = ImageFit::COVER;
constexpr ImageRepeat IMAGE_REPEAT_DEFAULT = ImageRepeat::REPEAT;
constexpr ImageInterpolation IMAGE_INTERPOLATION_DEFAULT = ImageInterpolation::HIGH;
constexpr ImageRenderMode IMAGE_RENDERMODE_DEFAULT = ImageRenderMode::ORIGINAL;
constexpr bool MATCHTEXTDIRECTION_DEFAULT = true;
const Color SVG_FILL_COLOR_DEFAULT = Color::BLUE;
const std::vector<float> COLOR_FILTER_DEFAULT = { 1.0, 2.0, 3.0 };
const SizeF CONTENT_SIZE = SizeF(400.0f, 500.0f);
const OffsetF CONTENT_OFFSET = OffsetF(50.0f, 60.0f);
constexpr bool SYNCMODE_DEFAULT = false;
constexpr CopyOptions COPYOPTIONS_DEFAULT = CopyOptions::None;
constexpr bool AUTORESIZE_DEFAULT = true;
constexpr bool FIT_ORIGINAL_SIZE_DEFAULT = true;
constexpr ImageRepeat IMAGE_NO_REPEAT = ImageRepeat::NO_REPEAT;
constexpr ImageInterpolation IMAGE_NO_INTERPOLATION = ImageInterpolation::NONE;
constexpr ImageRenderMode IMAGE_NO_RENDERMODE = ImageRenderMode::ORIGINAL;
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.svg";
const std::string ALT_SRC_URL = "file://data/data/com.example.test/res/exampleAlt.jpg";
const std::string RESOURCE_URL = "resource:///ohos_test_image.svg";
const std::string PNG_IMAGE = "/common/media/aaa.png";
const std::string BUNDLE_NAME;
const std::string MODULE_NAME;
const std::string WEB_IMAGE =
    "https://img2.baidu.com/it/u=3999091694,1705560228&fm=253&fmt=auto&app=120&f=JPEG?w=1280&h=800";
constexpr int32_t DURATION_DEFAULT = 1000;
constexpr int32_t ITERATION_DEFAULT = 1;
constexpr int32_t STATE_START = 1;
constexpr Dimension IMAGE_WIDTH = 170.0_vp;
constexpr Dimension IMAGE_HEIGHT = 120.0_vp;
constexpr Dimension IMAGE_TOP = 0.0_vp;
constexpr Dimension IMAGE_LEFT = 0.0_vp;
const std::vector<float> COLOR_FILTER_NULL;
const std::string tagName = "TestNode";
const std::string URL_LENGTH_EQUAL_35 = "https://example.com/api/v1/resource";
const std::string URL_LENGTH_LESS_THAN_30 = "https://example.com";
const std::string RESULT_FOR_URL_LENGTH_EQUAL_35 = "https://example*****ap*/v*/r*so*rc*";
const std::string RESULT_FOR_URL_LENGTH_LESS_THAN_30 = "ht*ps*//*xa*pl*.c*m";

class ImageBases : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static RefPtr<FrameNode> CreateImageNode(
        const std::string& src, const std::string& alt, RefPtr<PixelMap> pixMap = nullptr);
    static RefPtr<FrameNode> CreateImageNodeWithDefaultProp(
        const std::string& src, const std::string& alt, RefPtr<PixelMap> pixMap = nullptr);
    static RefPtr<FrameNode> CreateSyncImageNode();
    static RefPtr<FrameNode> CreateSyncWebImageNode();
    static RefPtr<PixelMap> CreatePixelMap(const std::string& src);
    static RefPtr<FrameNode> CreatePixelMapAnimator(int32_t number = 1);
};

template <class LayoutPropertyCls = ImageLayoutProperty,
          class PatternCls = ImagePattern,
          class RenderPropertyCls = ImageRenderProperty>
auto GetCompoment()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutPropertyCls>();
    EXPECT_NE(layoutProperty, nullptr);
    auto pattern = frameNode->GetPattern<PatternCls>();
    EXPECT_NE(pattern, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<RenderPropertyCls>();
    EXPECT_NE(renderProperty, nullptr);
    return std::make_tuple(frameNode, layoutProperty, pattern, renderProperty);
}

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto node = MakeRefPtr<TestNode>(nodeId);
        return node;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode(tagName, nodeId) {}
    ~TestNode() override = default;
};

std::vector<RefPtr<UINode>> PopUINodes();
void PushUINodes(std::vector<RefPtr<UINode>> &vec);
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_TEXTFIELD_TEXTINPUT_TEST_NG_H