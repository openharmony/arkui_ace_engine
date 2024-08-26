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
#include "core/components_ng/pattern/text_drag/text_drag_paint_method.h"

namespace OHOS::Ace::NG {
TextDragPaintMethod::TextDragPaintMethod(const WeakPtr<Pattern>& pattern,
    const RefPtr<TextDragOverlayModifier>& textDragOverlayModifier) : pattern_(pattern),
    overlayModifier_(textDragOverlayModifier) {}

RefPtr<Modifier> TextDragPaintMethod::GetOverlayModifier(PaintWrapper* paintWrapper)
{
    return overlayModifier_;
}
} // namespace OHOS::Ace::NG
