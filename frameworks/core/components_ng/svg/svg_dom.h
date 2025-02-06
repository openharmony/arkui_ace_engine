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

#include <memory>

#include "src/xml/SkDOM.h"
#include "src/xml/SkXMLParser.h"
#include "src/xml/SkXMLWriter.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/image_provider/svg_dom_base.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/svg/parse/svg_node.h"
#include "core/components_ng/svg/parse/svg_style.h"
#include "core/components_ng/svg/svg_context.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {

struct SvgTranslateProcessInfo {
    SvgTranslateProcessInfo() = default;
    SvgTranslateProcessInfo(RefPtr<SvgNode> currentNode, const SkDOM::Node* xmlNode)
        : currentNode(currentNode), xmlNode(xmlNode)
    {}
    RefPtr<SvgNode> currentNode = nullptr; // The SVG node currently being processed
    const SkDOM::Node* xmlNode = nullptr;
};

class SvgDom : public SvgDomBase {
    DECLARE_ACE_TYPE(SvgDom, SvgDomBase);

public:
    SvgDom();
    ~SvgDom() override;

    static RefPtr<SvgDom> CreateSvgDom(SkStream& svgStream, const ImageSourceInfo& src);

    void SetFuncNormalizeToPx(FuncNormalizeToPx&& funcNormalizeToPx);
    void SetAnimationCallback(std::function<void()>&& funcAnimateFlush, const WeakPtr<CanvasImage>& imagePtr) override;
    void SetAnimationOnFinishCallback(const std::function<void()>& onFinishCallback) override;
    void ControlAnimation(bool play) override;
    bool IsStatic() override;

    bool ParseSvg(SkStream& svgStream);

    void SetFillColor(const std::optional<Color>& color) override;
    void SetSmoothEdge(float value) override;
    void SetColorFilter(const std::optional<ImageColorFilter>& colorFilter) override;

    void DrawImage(
        RSCanvas& canvas, const ImageFit& imageFit, const Size& layout) override;

    SizeF GetContainerSize() const override;
    void SetContainerSize(const SizeF& containerSize) override {}
    void PushAnimatorOnFinishCallback(const RefPtr<SvgNode>& root, std::function<void()> onFinishCallback);
    std::string GetDumpInfo() override;

protected:
    void FitImage(RSCanvas& canvas, const ImageFit& imageFit, const Size& layout);
    void FitViewPort(const Size& layout);

private:
    RefPtr<SvgNode> TranslateSvgNode(const SkDOM& dom, const SkDOM::Node* xmlNode, const RefPtr<SvgNode>& parent);
    RefPtr<SvgNode> CreateSvgNodeFromDom(const SkDOM& dom, const SkDOM::Node* xmlNode, const RefPtr<SvgNode>& parent);
    void ParseAttrs(const SkDOM& xmlDom, const SkDOM::Node* xmlNode, const RefPtr<SvgNode>& svgNode);
    void SetAttrValue(const std::string& name, const std::string& value, const RefPtr<SvgNode>& svgNode);
    void ParseIdAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value);
    void ParseFillAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value);
    void ParseClassAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value);
    void ParseStyleAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value);
    void SyncRSNode(const RefPtr<RenderNode>& renderNode);
    void InitStyles();
    std::string IntToHexString(const int number);
    RefPtr<SvgContext> svgContext_;
    RefPtr<SvgNode> root_;
    Rect viewBox_;
    PushAttr attrCallback_;
    std::optional<Color> fillColor_;
    std::string path_;
    float smoothEdge_ = 0.0f;
    std::optional<ImageColorFilter> colorFilter_;
    std::atomic<bool> isStatic_{ true };
    bool isStyleInited_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_SVG_DOM_H
