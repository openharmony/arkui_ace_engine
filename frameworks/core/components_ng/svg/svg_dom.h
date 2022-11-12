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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_SVG_DOM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_SVG_DOM_H

#include "src/xml/SkDOM.h"
#include "src/xml/SkXMLParser.h"
#include "src/xml/SkXMLWriter.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/image_provider/svg_dom_base.h"
#include "frameworks/core/components_ng/svg/parse/svg_context.h"
#include "frameworks/core/components_ng/svg/parse/svg_node.h"
#include "frameworks/core/components_ng/svg/parse/svg_style.h"

namespace OHOS::Ace::NG {
class SvgDom : public SvgDomBase {
    DECLARE_ACE_TYPE(SvgDom, SvgDomBase);

public:
    SvgDom();
    ~SvgDom();

    static RefPtr<SvgDom> CreateSvgDom(SkStream& svgStream, const std::optional<Color>& color);

    void SetFunction(const FuncNormalizeToPx& funcNormalizeToPx, const FuncAnimateFlush& funcAnimateFlush);

    bool ParseSvg(SkStream& svgStream);

    void DrawImage(
        RSCanvas& canvas, const ImageFit& imageFit, const Size& layout, const std::optional<Color>& color) override;

    SizeF GetContainerSize() const override
    {
        // TODO: return correct size
        return {};
    }
    void SetContainerSize(const SizeF& containerSize) override {}
    void SetSvgFillColor(const std::optional<Color>& color) override
    {
        fillColor_ = color;
    }

protected:
    void FitImage(RSCanvas& canvas, const ImageFit& imageFit, const Size& layout);
    void FitViewPort(const Size& layout);

private:
    RefPtr<SvgNode> TranslateSvgNode(const SkDOM& dom, const SkDOM::Node* xmlNode, const RefPtr<SvgNode>& parent);
    void ParseAttrs(const SkDOM& xmlDom, const SkDOM::Node* xmlNode, const RefPtr<SvgNode>& svgNode);
    void SetAttrValue(const std::string& name, const std::string& value, const RefPtr<SvgNode>& svgNode);
    void ParseIdAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value);
    void ParseFillAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value);
    void ParseClassAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value);
    void ParseStyleAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value);
    void ApplyImageFit(ImageFit imageFit, double& scaleX, double& scaleY);
    void ApplyFill(double& scaleX, double& scaleY);
    void ApplyContain(double& scaleX, double& scaleY);
    void ApplyCover(double& scaleX, double& scaleY);
    void SyncRSNode(const RefPtr<RenderNode>& renderNode);

    RefPtr<SvgContext> svgContext_;
    RefPtr<SvgNode> root_;
    Size layout_; // svg外视口, 即image组件赋予的布局宽高
    Size svgSize_; // svg内视口，即图源内置宽高
    Rect viewBox_;
    std::optional<Color> fillColor_;
    PushAttr attrCallback_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_SVG_DOM_H