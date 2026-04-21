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

#ifndef TEST_UNITTEST_CORE_PATTERN_BUTTON_BUTTON_TEST_MIN_H
#define TEST_UNITTEST_CORE_PATTERN_BUTTON_BUTTON_TEST_MIN_H

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <utility>
#include "gtest/gtest.h"

#define protected public
#define private public

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {

constexpr float ZERO = 0.0f;
constexpr float BUTTON_WIDTH = 200.0f;
constexpr float BUTTON_HEIGHT = 100.0f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float TOP_PADDING = 0.0f;
constexpr float BOTTOM_PADDING = 0.0f;
constexpr bool STATE_EFFECT = true;
const std::string CREATE_VALUE = "Hello World";
const std::string BUTTON_VALUE = "Test";
const std::string TEST_RESULT = "result_ok";
const std::string TEST_RESULT_CAPSULE = "capsule";
const std::string TEST_RESULT_DOWNLOAD = "download";
const ButtonType BUTTON_TYPE_CAPSULE_VALUE = ButtonType::CAPSULE;
const ButtonType BUTTON_TYPE_CUSTOM_VALUE = ButtonType::CUSTOM;
const ButtonType BUTTON_TYPE_DOWNLOAD_VALUE = ButtonType::DOWNLOAD;
const ButtonType BUTTON_TYPE_CIRCLE_VALUE = ButtonType::CIRCLE;
const ButtonType BUTTON_TYPE_ROUNDED_RECTANGLE_VALUE = ButtonType::ROUNDED_RECTANGLE;
const Dimension BORDER_RADIUS = 5.0_vp;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const Dimension DEFAULT_HEIGTH = 40.0_vp;
const char LABEL_TEXT[] = "button";
const Dimension BUTTON_FONT_SIZE_VALUE = 30.0_vp;
const Ace::FontWeight BUTTON_BOLD_FONT_WEIGHT_VALUE = Ace::FontWeight::BOLD;
const Ace::FontStyle BUTTON_ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Color BUTTON_TEXT_COLOR_VALUE = Color::RED;
const Color FONT_COLOR = Color(0XFFFF0000);
const int NODE_ID = 10;
const uint32_t MAX_LINE_VALUE = 10;
const float MIN_SCALE_VALUE = 0.5f;
const float MAX_SCALE_VALUE = 3.2f;
const float NEGATIVE_SCALE_VALUE = -1.0f;
const float MAX_SCALE_NORMAL = 1.0f;
const Dimension FONT_SIZE = 10.0_vp;

inline struct CreateWithPara createWithPara = { std::make_optional(true), std::make_optional(CREATE_VALUE),
    std::make_optional(true), std::make_optional(ButtonType::CAPSULE), std::make_optional(true), std::nullopt,
    std::nullopt, std::nullopt };
inline struct CreateWithPara createWithParaByRoundedRect = { std::make_optional(true), std::make_optional(CREATE_VALUE),
    std::make_optional(true), std::make_optional(ButtonType::ROUNDED_RECTANGLE), std::make_optional(true), std::nullopt,
    std::nullopt, std::nullopt };

struct TestProperty {
    std::optional<ButtonType> typeValue = std::nullopt;
    std::optional<bool> stateEffectValue = std::nullopt;
    std::optional<Dimension> fontSizeValue = std::nullopt;
    std::optional<Ace::FontWeight> fontWeightValue = std::nullopt;
    std::optional<Color> textColorValue = std::nullopt;
    std::optional<Ace::FontStyle> fontStyleValue = std::nullopt;
    std::optional<std::vector<std::string>> fontFamilyValue = std::nullopt;
    std::optional<Dimension> borderRadius = std::nullopt;
    std::optional<ButtonStyleMode> buttonStyle = std::nullopt;
    std::optional<ControlSize> controlSize = std::nullopt;
    std::optional<ButtonRole> buttonRole = std::nullopt;
};

struct LableStyleProperty {
    std::optional<Ace::TextOverflow> textOverflow = std::nullopt;
    std::optional<uint32_t> maxLines = std::nullopt;
    std::optional<Dimension> minFontSize = std::nullopt;
    std::optional<Dimension> maxFontSize = std::nullopt;
    std::optional<Dimension> fontSize = std::nullopt;
    std::optional<Ace::FontWeight> fontWeight = std::nullopt;
    std::optional<std::vector<std::string>> fontFamily = std::nullopt;
    std::optional<Ace::FontStyle> fontStyle = std::nullopt;
    std::optional<Ace::TextHeightAdaptivePolicy> adaptHeight;
};

// Base test class for button tests
class ButtonTestBase : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static void CreateLayoutTask(const RefPtr<FrameNode>& frameNode);
    static RefPtr<FrameNode> CreateButton(
        const std::u16string& content, const std::function<void(ButtonModelNG)>& callback);

protected:
    PaddingProperty CreatePadding(float left, float top, float right, float bottom);
    RefPtr<FrameNode> CreateLabelButtonParagraph(const std::string& createValue, const TestProperty& testProperty);
    RefPtr<FrameNode> CreateLabelButtonParagraphByRoundedRect(
        const std::string& createValue, const TestProperty& testProperty);

private:
    void CreateAndCheckTextOverflow(RefPtr<FrameNode> frameNode, bool isCheckTextOverflow);
    void CheckTextMarqueeOption(RefPtr<FrameNode> frameNode, bool isMarqueeStart);
};

} // namespace OHOS::Ace::NG

#endif // TEST_UNITTEST_CORE_PATTERN_BUTTON_BUTTON_TEST_MIN_H
