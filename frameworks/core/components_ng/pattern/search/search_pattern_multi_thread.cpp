/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/search/search_pattern.h"

#include <cstdint>
#include "base/geometry/dimension.h"
#include "base/utils/utf_helper.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "base/geometry/rect.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/search/search_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/search/search_model.h"
#include "core/components_ng/pattern/search/search_text_field.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/event/touch_event.h"
#include "core/components/theme/app_theme.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t TEXTFIELD_INDEX = 0;
constexpr float MAX_FONT_SCALE = 2.0f;

void InitSearchMaxFontScale(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto maxFontScale = MAX_FONT_SCALE;
    if (textFieldLayoutProperty->HasMaxFontScale()) {
        maxFontScale = std::min(textFieldLayoutProperty->GetMaxFontScale().value(), maxFontScale);
    } else if (pipeline->GetMaxAppFontScale()) {
        maxFontScale = std::min(pipeline->GetMaxAppFontScale(), maxFontScale);
    }
    textFieldLayoutProperty->UpdateMaxFontScale(maxFontScale);
}
} // namespace

void SearchPattern::OnAttachToMainTreeMultiThread()
{
    if (processTextFieldDefaultStyleAndBehaviorsMultiThread_) {
        processTextFieldDefaultStyleAndBehaviorsMultiThread_ = false;
        ProcessTextFieldDefaultStyleAndBehaviorsMultiThread();
    }
}

void SearchPattern::ProcessTextFieldDefaultStyleAndBehaviors()
{
    processTextFieldDefaultStyleAndBehaviorsMultiThread_ = true;
}

void SearchPattern::ProcessTextFieldDefaultStyleAndBehaviorsMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto frameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto textFieldPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textFieldPaintProperty);
    auto colorMode = pipeline->GetColorMode();
    pattern->SetOriginCursorColor(colorMode == ColorMode::DARK ? Color(0x4DFFFFFF) : Color(0x4D000000));
    if (pipeline->GetHasPreviewTextOption()) {
        pattern->SetSupportPreviewText(pipeline->GetSupportPreviewText());
    }
    textFieldPaintProperty->UpdateCursorColor(textFieldTheme->GetCursorColor());
    textFieldPaintProperty->UpdateCursorWidth(textFieldTheme->GetCursorWidth());
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    InitSearchMaxFontScale(frameNode);
}

} // namespace OHOS::Ace::NG
