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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_QRCODE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_QRCODE_PATTERN_H

#include <optional>

#include "base/geometry/axis.h"
#include "core/components/qrcode/qrcode_theme.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/qrcode/qrcode_layout_algorithm.h"
#include "core/components_ng/pattern/qrcode/qrcode_paint_method.h"
#include "core/components_ng/pattern/qrcode/qrcode_paint_property.h"

namespace OHOS::Ace::NG {

class QRCodePattern : public Pattern {
    DECLARE_ACE_TYPE(QRCodePattern, Pattern);

public:
    QRCodePattern() = default;
    ~QRCodePattern() override = default;

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<QRCodePaintProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<QRCodeLayoutAlgorithm>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<QRCodePaintMethod>(qrCodeSize_);
    }
    void OnModifyDone() override;
    FocusPattern GetFocusPattern() const override;

private:
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;

    float qrCodeSize_ = 0.0f;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_QRCODE_PATTERN_H
