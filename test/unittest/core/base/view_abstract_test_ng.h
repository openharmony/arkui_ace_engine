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

#ifndef TEST_UNITTEST_CORE_BASE_VIEW_ABSTRACT_TEST_NG_H
#define TEST_UNITTEST_CORE_BASE_VIEW_ABSTRACT_TEST_NG_H
#include "gtest/gtest.h"
#define protected public
#define private public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/error/error_code.h"
#include "core/components/common/layout/position_param.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/popup/popup_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_model_ng.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigator/navigator_model_ng.h"
#include "core/components_ng/pattern/navrouter/navrouter_model_ng.h"
#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stepper/stepper_item_model_ng.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/property/property.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/pipeline/base/element.h"
#include "core/pipeline/base/element_register.h"

#undef private
#undef protected

namespace OHOS::Ace::NG {
namespace {
const Dimension WIDTH { 50.0, DimensionUnit::PX };
const Dimension HEIGHT { 100.0, DimensionUnit::PX };
const Dimension MIN_WIDTH { 10.0, DimensionUnit::PX };
const Dimension MIN_HEIGHT { 20.0, DimensionUnit::PX };
const Dimension RADIUS { 10.0, DimensionUnit::PX };
const Dimension LEFT { 10.0, DimensionUnit::PX };
const Dimension TOP { 20.0, DimensionUnit::PX };
const Dimension RIGHT { 10.0, DimensionUnit::PX };
const Dimension BOTTOM { 20.0, DimensionUnit::PX };
const Dimension VALUE { -50.0, DimensionUnit::PX };
const Dimension ZERO { 0.0, DimensionUnit::PX };
const BiasPair biasPair(0.5f, 0.5f);
const InvertVariant invert = 0.0f;
const OffsetF OFFSETF { 1.0, 1.0 };
const Offset OFFSET { 2.0, 2.0 };
const float RATIO = 1.0f;
const double OPACITYS = 10;
const int32_t TEN = 10;
const int32_t FOUF = 4;
const int32_t INDEX = 1;
const Color BLUE = Color(0xff0000ff);
const SafeAreaExpandOpts safeAreaExpandOpts = SafeAreaExpandOpts();
const std::vector<ObscuredReasons> reasonsVector = { ObscuredReasons::PLACEHOLDER };

BackgroundImageSize BACKGROUNDSIZE { BackgroundImageSizeType::AUTO, 1.0 };
BackgroundImagePosition BACKGROUNDPOSITION { BackgroundImagePositionType::PERCENT, -1.0,
    BackgroundImagePositionType::PERCENT, 0.0 };

constexpr char TAG_ROOT[] = "root";
constexpr char TAG_CHILD[] = "child";
const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
const uint32_t REGISTER_ID = 1 << 20;
const auto FRAME_NODE_REGISTER = FrameNode::CreateFrameNode(TAG_ROOT, REGISTER_ID, MOCK_PATTERN_ROOT, false);

std::string srcimages = "common/images/mmm.jpg";
const std::string VALUE_EMPTY = "";
const std::string VALUE_X = "X";
const std::string VALUE_CX = "CX";
const std::string VALUE_TAB = "TAB";
const std::string VALUE_DPAD_UP = "DPAD_UP";
ViewAbstractModelNG viewAbstractModelNG;
auto callback = []() { srcimages = "test"; };
int32_t flag = 0;
const ImageSourceInfo imageSourceInfo = ImageSourceInfo("common/images/mmm.jpg", "abstract", "abstract");
}; // namespace
class ViewAbstractTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();
        auto frameNode =
            FrameNode::GetOrCreateFrameNode("components", nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
        stack->Push(frameNode);
    }
    void TearDown() override {}
};
} // namespace OHOS::Ace::NG

#endif //TEST_UNITTEST_CORE_BASE_VIEW_ABSTRACT_TEST_NG_H