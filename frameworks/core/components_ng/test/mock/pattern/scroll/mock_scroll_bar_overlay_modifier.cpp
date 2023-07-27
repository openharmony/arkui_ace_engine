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

#include "core/components_ng/pattern/scroll/inner/scroll_bar_overlay_modifier.h"

namespace OHOS::Ace::NG {
ScrollBarOverlayModifier::ScrollBarOverlayModifier() {}

void ScrollBarOverlayModifier::onDraw(DrawingContext& context) {}

void ScrollBarOverlayModifier::StartOpacityAnimation(OpacityAnimationType opacityAnimationType) {}

void ScrollBarOverlayModifier::SetRect(const SizeF& fgSize, const SizeF& bgSize, const OffsetF& fgOffset,
    const OffsetF& bgOffset, HoverAnimationType hoverAnimationType)
{}

void ScrollBarOverlayModifier::SetOffset(OffsetF fgOffset, OffsetF bgOffset) {}

void ScrollBarOverlayModifier::SetFgColor(Color fgColor) {}

void ScrollBarOverlayModifier::SetBgColor(Color bgColor) {}
} // namespace OHOS::Ace::NG
