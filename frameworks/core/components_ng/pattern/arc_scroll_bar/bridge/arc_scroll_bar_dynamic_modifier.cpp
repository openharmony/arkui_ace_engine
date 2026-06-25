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

#include "core/components_ng/pattern/arc_scroll_bar/bridge/arc_scroll_bar_dynamic_modifier.h"

#include "core/components_ng/pattern/arc_scroll_bar/arc_scroll_bar_pattern.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
namespace {

RefPtr<Pattern> CreateArcScrollBarPatternImpl()
{
    return AceType::MakeRefPtr<ArcScrollBarPattern>();
}

RefPtr<ScrollBar> CreateArcScrollBarImpl()
{
    return AceType::MakeRefPtr<ArcScrollBar>();
}

RefPtr<ScrollBarOverlayModifier> CreateArcScrollBarOverlayModifierImpl(ScrollBar* existingScrollBar)
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

void UpdateArcScrollBarOverlayImpl(ScrollBarOverlayModifier* overlayModifier, ScrollBar* scrollBar, bool& result)
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
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIArcScrollBarCustomModifier modifier = {
        .createArcScrollBarPattern = CreateArcScrollBarPatternImpl,
        .createArcScrollBar = CreateArcScrollBarImpl,
        .createArcScrollBarOverlayModifier = CreateArcScrollBarOverlayModifierImpl,
        .updateArcScrollBarOverlay = UpdateArcScrollBarOverlayImpl,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
