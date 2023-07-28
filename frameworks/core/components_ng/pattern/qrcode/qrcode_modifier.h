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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_QRCODE_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_QRCODE_MODIFIER_H

#include "qrcodegen.hpp"

#include "base/geometry/arc.h"
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {
class QRCodeModifier : public ContentModifier {
    DECLARE_ACE_TYPE(QRCodeModifier, ContentModifier);

    union BGRA {
        struct {
            uint8_t red;
            uint8_t green;
            uint8_t blue;
            uint8_t alpha;
        } argb;

        uint32_t value;
    };

public:
    QRCodeModifier();
    ~QRCodeModifier() override = default;
    void onDraw(DrawingContext& context) override;

    void SetQRCodeOpacity(float opacity);
    void SetQRCodeSize(float qrCodeSize);
    void SetQRCodeValue(const std::string& value);
    void SetPaintOffset(const OffsetF& paintOffset);
    void SetQRCodeColor(const Color& color);
    void SetQRCodeBackgroundColor(const Color& bgColor);

private:
    RSBitmap CreateBitMap(
        int32_t width, const qrcodegen::QrCode& qrCode, const Color& color, const Color& backgroundColor) const;
    uint32_t ConvertColorFromHighToLow(const Color& color) const;

    RefPtr<AnimatablePropertyFloat> opacity_;
    RefPtr<PropertyFloat> qrCodeSize_;
    RefPtr<PropertyString> value_;
    RefPtr<PropertyOffsetF> paintOffset_;
    RefPtr<PropertyColor> color_;
    RefPtr<PropertyColor> backgroundColor_;

    ACE_DISALLOW_COPY_AND_MOVE(QRCodeModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_QRCODE_MODIFIER_H
