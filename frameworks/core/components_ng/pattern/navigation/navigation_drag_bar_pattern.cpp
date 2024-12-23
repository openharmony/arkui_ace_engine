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

#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"

namespace OHOS::Ace::NG {
constexpr float BLUR_OPACITY = 0.1f;

void NavigationDragBarPattern::UpdateDefaultColor()
{
    auto dragBarNode = GetHost();
    CHECK_NULL_VOID(dragBarNode);
    auto renderContext = dragBarNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    renderContext->UpdateBackgroundColor(theme->GetDragBarDefaultColor().ChangeOpacity(BLUR_OPACITY));
    auto barNode = AceType::DynamicCast<FrameNode>(dragBarNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(barNode);
    auto barRenderContext = (barNode)->GetRenderContext();
    CHECK_NULL_VOID(barRenderContext);
    barRenderContext->UpdateBackgroundColor(theme->GetDragBarItemDefaultColor());
}

void NavigationDragBarPattern::UpdateActiveColor()
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto dragBarNode = GetHost();
    CHECK_NULL_VOID(dragBarNode);
    auto dragBarRenderContext = dragBarNode->GetRenderContext();
    CHECK_NULL_VOID(dragBarRenderContext);
    dragBarRenderContext->UpdateBackgroundColor(theme->GetDragBarActiveColor());
    auto barNode = AceType::DynamicCast<FrameNode>(dragBarNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(barNode);
    auto barRenderContext = barNode->GetRenderContext();
    CHECK_NULL_VOID(barRenderContext);
    barRenderContext->UpdateBackgroundColor(theme->GetDragBarItemActiveColor());
}
} // namespace OHOS::Ace::NG
