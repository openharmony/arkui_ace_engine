/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

#ifndef CAPI0805_2_SAFEAREAEXAMPLE_REFACTORED_H
#define CAPI0805_2_SAFEAREAEXAMPLE_REFACTORED_H

#include "LayoutConstants.h"
#include "nodes/ArkUIBaseNode.h"
#include "nodes/ArkUIColumnNode.h"
#include "nodes/ArkUITextNode.h"
#include "nodes/ArkUIListNode.h"
#include <vector>

namespace NativeModule {

using namespace LayoutConstants;

std::shared_ptr<ArkUIBaseNode> SafeAreaExample()
{
    auto column = std::make_shared<ArkUIColumnNode>();
    auto title = std::make_shared<ArkUITextNode>();
    title->SetTextContent("expand safe area top edge");
    title->SetFontSize(Sizes::FONT_SIZE_MEDIUM);
    column->AddChild(title);
    column->SetPercentHeight(Percentages::FULL_WIDTH);
    column->SetPercentWidth(Percentages::FULL_WIDTH);
    column->SetBackgroundColor(Colors::BEIGE);
    column->SetExpandSafeArea(ARKUI_SAFE_AREA_TYPE_SYSTEM, ARKUI_SAFE_AREA_EDGE_TOP);
    return column;
}

} // namespace NativeModule
#endif // CAPI0805_2_SAFEAREAEXAMPLE_REFACTORED_H
