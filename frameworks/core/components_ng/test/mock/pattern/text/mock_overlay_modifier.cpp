/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/text_overlay_modifier.h"

namespace OHOS::Ace::NG {
TextOverlayModifier::TextOverlayModifier() {}

void TextOverlayModifier::onDraw(DrawingContext& drawingContext) {}

void TextOverlayModifier::SetPrintOffset(const OffsetF& paintOffset) {}

void TextOverlayModifier::SetSelectedColor(uint32_t selectedColor) {}

void TextOverlayModifier::SetSelectedRects(const std::vector<RectF>& selectedRects) {}

bool TextOverlayModifier::IsSelectedRectsChanged(const std::vector<RectF>& selectedRects)
{
    return true;
}
} // namespace OHOS::Ace::NG