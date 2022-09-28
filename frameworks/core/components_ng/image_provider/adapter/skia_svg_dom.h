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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_SKIA_SVG_DOM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_SKIA_SVG_DOM_H

#include "experimental/svg/model/SkSVGDOM.h"
#include "include/core/SkStream.h"

#include "core/components/common/properties/color.h"
#include "core/components_ng/image_provider/svg_dom.h"

namespace OHOS::Ace::NG {

union SkColorEx {
    struct {
        SkColor color : 32;
        bool valid : 1;
        uint32_t reserved : 31; // reserved
    };
    uint64_t value = 0;
};

class SkiaSvgDom : public SvgDom {
    DECLARE_ACE_TYPE(SvgDom, SvgDom);

public:
    SkiaSvgDom() = default;
    explicit SkiaSvgDom(const sk_sp<SkSVGDOM>& skiaDom) : skiaDom_(skiaDom) {}

    static RefPtr<SkiaSvgDom> CreateSkiaSvgDom(const sk_sp<SkData>& skData, const std::optional<Color>& svgFillColor)
    {
        const auto svgStream = std::make_unique<SkMemoryStream>(skData);
        SkColorEx skColor;
        if (svgFillColor.has_value()) {
            skColor.color = svgFillColor.value().GetValue();
            skColor.valid = 1;
        }
        auto skiaDom = SkSVGDOM::MakeFromStream(*svgStream, skColor.value);
        return AceType::MakeRefPtr<SkiaSvgDom>(skiaDom);
    }

    const sk_sp<SkSVGDOM>& GetSkiaSvgDom() const
    {
        return skiaDom_;
    }

    void Render(SkCanvas* skCanvas)
    {
        skiaDom_->render(skCanvas);
    }

    SizeF GetContainerSize() const override
    {
        return SizeF(skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
    }

    void SetContainerSize(const SizeF& containerSize) override
    {
        skiaDom_->setContainerSize({containerSize.Width(), containerSize.Height()});
    }
private:
    sk_sp<SkSVGDOM> skiaDom_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_SKIA_SVG_DOM_H
