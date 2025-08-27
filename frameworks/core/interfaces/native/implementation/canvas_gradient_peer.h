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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_GRADIENT_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_GRADIENT_PEER_IMPL_H

#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/color.h"

struct CanvasGradientPeer {
    CanvasGradientPeer() = default;
    virtual ~CanvasGradientPeer() = default;

    const std::shared_ptr<OHOS::Ace::Gradient>& GetGradient() const
    {
        return gradient_;
    }
    void SetGradient(const std::shared_ptr<OHOS::Ace::Gradient>& gradient)
    {
        gradient_ = gradient;
    }

    virtual void AddColorStop(const float& offset, const OHOS::Ace::Color& color)
    {
        CHECK_NULL_VOID(gradient_);
        if (!isColorStopValid && gradient_->GetColors().empty()) {
            isColorStopValid = true;
        }
        OHOS::Ace::GradientColor gradientColor;
        if (offset < 0 || offset > 1) {
            isColorStopValid = false;
            // if the offset is invalid, fill the shape with transparent
            gradient_->ClearColors();
            gradientColor.SetColor(OHOS::Ace::Color::TRANSPARENT);
            gradientColor.SetDimension(0.0);
            gradient_->AddColor(gradientColor);
            gradient_->AddColor(gradientColor);
            return;
        }
        gradientColor.SetColor(color);
        gradientColor.SetDimension(offset);
        gradient_->AddColor(gradientColor);
        auto colorSize = gradient_->GetColors().size();
        // prevent setting only one colorStop
        if (colorSize == 1) {
            gradient_->AddColor(gradientColor);
        }
    }

private:
    std::shared_ptr<OHOS::Ace::Gradient> gradient_ = nullptr;
    bool isColorStopValid = false;
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_GRADIENT_PEER_IMPL_H
