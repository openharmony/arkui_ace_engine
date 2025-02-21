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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_USE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_USE_H

#include "core/components_ng/svg/parse/svg_attributes_parser.h"
#include "core/components_ng/svg/parse/svg_graphic.h"

namespace OHOS::Ace::NG {

class SvgUse : public SvgGraphic {
    DECLARE_ACE_TYPE(SvgUse, SvgGraphic);

public:
    SvgUse();
    ~SvgUse() override = default;

    static RefPtr<SvgNode> Create();

    void OnInitStyle() override;
    RSRecordingPath AsPath(const Size& viewPort) const override;
    void OnDraw(RSCanvas& canvas, const Size& layout, const std::optional<Color>& color) override;
    RSRecordingPath AsPath(const SvgLengthScaleRule& lengthRule) override;
    void OnDraw(RSCanvas& canvas, const SvgLengthScaleRule& lengthRule) override;
    bool ParseAndSetSpecializedAttr(const std::string& name, const std::string& value) override;
    void ApplyOpacity(RSCanvas& canvas);

private:
    // saves the current attributes of the svg node, and restores them when the scope exits.
    class AttributeScope {
    public:
        explicit AttributeScope(const RefPtr<SvgNode>& node);
        ~AttributeScope();

    private:
        SvgBaseAttribute attributes_;
        WeakPtr<SvgNode> node_;
    };
    SvgAttributes useAttr_;
    bool isDrawingPath_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_USE_H