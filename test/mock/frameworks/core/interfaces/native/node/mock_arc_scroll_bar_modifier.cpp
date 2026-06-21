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

#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/arc_scroll_bar/arc_scroll_bar_pattern.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"
#include "core/interfaces/native/node/node_arc_scroll_bar_modifier.h"

namespace OHOS::Ace::NG {
namespace {

// ---- bridge stubs ----

RefPtr<Pattern> CreateArcScrollBarPattern()
{
    return AceType::MakeRefPtr<ArcScrollBarPattern>();
}

RefPtr<ScrollBar> CreateArcScrollBarStub()
{
    return AceType::MakeRefPtr<ArcScrollBar>();
}

RefPtr<ScrollBarOverlayModifier> CreateArcScrollBarOverlayModifierStub(
    ScrollBar* existingScrollBar)
{
    auto overlayModifier = AceType::MakeRefPtr<ArcScrollBarOverlayModifier>();
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(existingScrollBar);
    if (arcScrollBar) {
        overlayModifier->SetPositionMode(arcScrollBar->GetPositionMode());
        overlayModifier->SetArcRect(arcScrollBar->GetArcActiveRect());
        overlayModifier->SetBackgroundArcRect(arcScrollBar->GetArcBarRect());
    }
    return overlayModifier;
}

void UpdateArcScrollBarOverlayStub(ScrollBarOverlayModifier* overlayModifier,
    ScrollBar* scrollBar, bool& result)
{
    auto arcOverlayModifier = AceType::DynamicCast<ArcScrollBarOverlayModifier>(overlayModifier);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    if (!arcOverlayModifier || !arcScrollBar) {
        result = false;
        return;
    }
    overlayModifier->SetBarColor(arcScrollBar->GetArcForegroundColor());
    arcOverlayModifier->SetBackgroundBarColor(arcScrollBar->GetArcBackgroundColor());
    arcOverlayModifier->StartArcBarAnimation(
        arcScrollBar->GetHoverAnimationType(),
        arcScrollBar->GetOpacityAnimationType(),
        arcScrollBar->GetNeedAdaptAnimation(),
        arcScrollBar->GetArcActiveRect(),
        arcScrollBar->GetArcBarRect());
    result = true;
}

} // namespace

namespace NodeModifier {
const ArkUIArcScrollBarCustomModifier* GetArcScrollBarCustomModifier()
{
    static const ArkUIArcScrollBarCustomModifier modifier = {
        .createArcScrollBarPattern = CreateArcScrollBarPattern,
        .createArcScrollBar = CreateArcScrollBarStub,
        .createArcScrollBarOverlayModifier = CreateArcScrollBarOverlayModifierStub,
        .updateArcScrollBarOverlay = UpdateArcScrollBarOverlayStub,
    };
    return &modifier;
}

const ArkUIArcScrollBarModifier* GetArcScrollBarModifier()
{
    static const ArkUIArcScrollBarModifier modifier = {};
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
