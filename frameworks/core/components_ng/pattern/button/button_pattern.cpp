/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/button/button_pattern.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/pattern/button/button_paint_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
void ButtonPattern::OnAttachToFrameNode()
{
    auto host = frameNode_.Upgrade();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

bool ButtonPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    auto buttonLayoutProperty = GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, false);

    CHECK_NULL_RETURN(dirty, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (buttonLayoutProperty->GetType().value_or(ButtonType::CAPSULE) == ButtonType::CAPSULE) {
        Dimension radius(dirty->GetGeometryNode()->GetFrameSize().Height() / 2.0f);
        BorderRadiusProperty borderRadius { radius, radius, radius, radius };
        host->GetRenderContext()->UpdateBorderRadius(borderRadius);
        return false;
    }
    return false;
}

void ButtonPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonLayoutProperty = GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);

    if (!buttonPositionProperty_) {
        buttonPositionProperty_ = std::make_unique<ButtonPositionProperty>();
    }
    host->GetLayoutProperty()->UpdateAlignment(buttonPositionProperty_->GetAlignment().value_or(Alignment::CENTER));
    // check circle border radius.
    if (buttonLayoutProperty->GetType().value_or(ButtonType::CAPSULE) == ButtonType::CIRCLE) {
        do {
            auto& borderRadius = host->GetRenderContext()->GetBorderRadius();
            if (!borderRadius) {
                break;
            }
            if (borderRadius->radiusTopLeft.has_value()) {
                buttonLayoutProperty->UpdateRadius(borderRadius->radiusTopLeft.value());
                break;
            }
            if (borderRadius->radiusTopRight.has_value()) {
                buttonLayoutProperty->UpdateRadius(borderRadius->radiusTopRight.value());
                break;
            }
            if (borderRadius->radiusBottomLeft.has_value()) {
                buttonLayoutProperty->UpdateRadius(borderRadius->radiusBottomLeft.value());
                break;
            }
            if (borderRadius->radiusBottomRight.has_value()) {
                buttonLayoutProperty->UpdateRadius(borderRadius->radiusBottomRight.value());
                break;
            }
        } while (false);
    }

    auto gesture = host->GetOrCreateGestureEventHub();
    ACE_DCHECK(gesture);
    if (touchListener_) {
        return;
    }
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto buttonPattern = weak.Upgrade();
        CHECK_NULL_VOID(buttonPattern);
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            buttonPattern->OnTouchDown();
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
            buttonPattern->OnTouchUp();
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void ButtonPattern::OnTouchDown()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<ButtonPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->GetStateEffect().value_or(true)) {
        const auto& renderContext = host->GetRenderContext();
        renderContext->BlendBgColor(Color(0x19000000).BlendColor(Color(0xff3b3b3b)));
    }
}

void ButtonPattern::OnTouchUp()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<ButtonPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->GetStateEffect().value_or(true)) {
        const auto& renderContext = host->GetRenderContext();
        renderContext->ResetBlendBgColor();
    }
}

ButtonType ButtonPattern::GetButtonType() const
{
    auto buttonLayoutProperty = GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, ButtonType::CAPSULE);
    return buttonLayoutProperty->GetType().value_or(ButtonType::CAPSULE);
}
} // namespace OHOS::Ace::NG
