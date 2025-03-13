/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_NODE_H

#include <vector>

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/animation/svg_animate.h"
#include "core/components_ng/image_provider/svg_dom_base.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/svg_context.h"
#include "core/components_ng/svg/base/svg_bounding_box_context.h"
#include "core/components_ng/svg/parse/svg_attributes_parser.h"

namespace OHOS::Ace::NG {

class SvgContext;
class SvgAnimation;

struct SvgInitStyleProcessInfo {
    SvgInitStyleProcessInfo() = default;
    SvgInitStyleProcessInfo(RefPtr<SvgNode> svgNode) : svgNode(svgNode) {}
    RefPtr<SvgNode> svgNode = nullptr; // The SVG node currently being processed
    int32_t childIndex = 0; // Index of the next child node to traverse for the current node
};

// three level inherit class, for example:
// 1. SvgMask::SvgQuote::SvgNode
// 2. SvgPath::SvgGraphic::SvgNode
class SvgNode : public AceType {
    DECLARE_ACE_TYPE(SvgNode, AceType);

public:
    SvgNode() = default;
    ~SvgNode() override = default;

    void InitStyle(const SvgBaseAttribute& attr);
    void ProcessSvgStyle(RefPtr<SvgNode> svgNode, const SvgBaseAttribute& attr);
    void ProcessChildAnimations(const RefPtr<SvgNode>& currentSvgNode);
    bool ProcessChildStyle(SvgInitStyleProcessInfo& currentSvgNodeInfo,
        std::stack<std::pair<SvgInitStyleProcessInfo, const SvgBaseAttribute*>>& initStyleTaskSt);
    void InitStyleDfs(const WeakPtr<SvgNode>& root, const SvgBaseAttribute& attr);

    // draw entrance function, approve override by second level class.
    virtual void Draw(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color);
    virtual void Draw(RSCanvas& canvas, const SvgLengthScaleRule& lengthRule);
    virtual void SetAttr(const std::string& name, const std::string& value);

    virtual bool ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
    {
        return false;
    }

    virtual void AppendChild(const RefPtr<SvgNode>& child)
    {
        children_.emplace_back(child);
        OnAppendChild(child);
    }

    void InheritAttr(const SvgBaseAttribute& parent)
    {
        attributes_.Inherit(parent);
    }

    void InheritUseAttr(const SvgBaseAttribute& parent)
    {
        attributes_.InheritFromUse(parent);
    }

    virtual RSRecordingPath AsPath(const Size& viewPort) const
    {
        return {};
    }

    virtual RSRecordingPath AsPath(const SvgLengthScaleRule& lengthRule)
    {
        return {};
    }

    virtual RSPath AsRSPath(const Size& viewPort) const;

    Rect AsBounds(const Size& viewPort) const
    {
        auto bounds = AsPath(viewPort).GetBounds();
        return { bounds.GetLeft(), bounds.GetTop(), bounds.GetWidth(), bounds.GetHeight() };
    }

    void SetContext(const WeakPtr<SvgContext>& svgContext)
    {
        svgContext_ = svgContext;
    }

    WeakPtr<SvgContext>& GetContext()
    {
        return svgContext_;
    }

    void SetNodeId(const std::string& value)
    {
        nodeId_ = value;
    }

    void SetSmoothEdge(float value)
    {
        smoothEdge_ = value;
    }

    float GetSmoothEdge() const
    {
        return smoothEdge_;
    }

    void SetColorFilter(const std::optional<ImageColorFilter>& colorFilter)
    {
        colorFilter_ = colorFilter;
    }

    void SetEffectFilterArea(const Rect& effectFilterArea)
    {
        effectFilterArea_ = effectFilterArea;
    }

    Rect GetEffectFilterArea() const
    {
        return effectFilterArea_;
    }

    std::optional<ImageColorFilter> GetColorFilter() const
    {
        return colorFilter_;
    }

    SvgBaseAttribute GetBaseAttributes() const
    {
        return attributes_;
    }

    void SetBaseAttributes(const SvgBaseAttribute& attr)
    {
        attributes_ = attr;
    }

    void SetImagePath(const std::string& path)
    {
        imagePath_ = path;
    }

    std::string GetImagePath() const
    {
        return imagePath_;
    }
    void SetIsRootNode(bool isRoot)
    {
        isRootNode_ = isRoot;
    }
    Offset CalcGlobalPivot(const std::pair<Dimension, Dimension>& transformOrigin, const Rect& baseRect);
    float GetRegionLength(Dimension origin, const SvgLengthScaleRule& boxMeasureRule, SvgLengthType lengthType);
    float GetRegionPosition(Dimension origin, const SvgLengthScaleRule& boxMeasureRule, SvgLengthType lengthType);
    float GetMeasuredLength(Dimension origin, const SvgLengthScaleRule& boxMeasureRule, SvgLengthType lengthType);
    float GetMeasuredPosition(Dimension origin, const SvgLengthScaleRule& boxMeasureRule, SvgLengthType lengthType);
    Rect GetSvgContainerRect() const;
    bool drawTraversed_ = true; // enable OnDraw, TAGS mask/defs/pattern/filter = false
protected:
    // override as need by derived class
    // called by function AppendChild
    virtual void OnAppendChild(const RefPtr<SvgNode>& child) {}
    // called by function InitStyle
    virtual void OnInitStyle() {}
    // function override by graphic tag
    virtual void OnDraw(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color) {}
    virtual void OnDraw(RSCanvas& canvas, const SvgLengthScaleRule& lengthRule) {}
    virtual void OnDrawTraversed(RSCanvas& canvas, const SvgLengthScaleRule& lengthRule);
    virtual void OnDrawTraversed(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color);
    virtual void AdjustContentAreaByViewBox(RSCanvas& canvas, const Size& viewPort) {}
    bool OnCanvas(RSCanvas& canvas);
    void OnClipPath(RSCanvas& canvas, const Size& viewPort);
    void OnFilter(RSCanvas& canvas, const Size& viewPort);
    void OnMask(RSCanvas& canvas, const Size& viewPort);
    void OnTransform(RSCanvas& canvas, const Size& viewPort);
    virtual void OnClipEffect(RSCanvas& canvas, const SvgCoordinateSystemContext& svgCoordinateSystemContext) {}
    virtual void OnMaskEffect(RSCanvas& canvas, const SvgCoordinateSystemContext& svgCoordinateSystemContext) {}
    virtual void OnFilterEffect(RSCanvas& canvas, const SvgCoordinateSystemContext& svgCoordinateSystemContext,
        float useOffsetX, float useOffsetY) {}
    void OnClipPath(RSCanvas& canvas, const SvgCoordinateSystemContext& svgCoordinateSystemContext);
    void OnFilter(RSCanvas& canvas, const SvgCoordinateSystemContext& svgCoordinateSystemContext);
    void OnMask(RSCanvas& canvas, const SvgCoordinateSystemContext& svgCoordinateSystemContext);
    void OnTransform(RSCanvas& canvas, const SvgLengthScaleRule& lengthRule);
    double ConvertDimensionToPx(const Dimension& value, const Size& viewPort, SvgLengthType type) const;
    double ConvertDimensionToPx(const Dimension& value, double baseValue) const;

    std::optional<Gradient> GetGradient(const std::string& href);
    const Rect& GetRootViewBox() const;
    virtual void PrepareAnimation(const RefPtr<SvgAnimation>& animate);
    // create animation that changes an attribute
    template<typename T>
    void AnimateOnAttribute(const RefPtr<SvgAnimation>& animate, const T& originalValue);
    // animate a transformation attribute
    void AnimateTransform(const RefPtr<SvgAnimation>& animate, double originalValue);
    void AnimateFromToTransform(const RefPtr<SvgAnimation>& animate, double originalValue);
    void AnimateFrameTransform(const RefPtr<SvgAnimation>& animate, double originalValue);

    // update svg attribute in animation
    template<typename T>
    void UpdateAttr(const std::string& name, const T& val);
    void UpdateAttrHelper(const std::string& name, const std::string& val);
    SvgLengthScaleRule TransformForCurrentOBB(RSCanvas& canvas, const SvgCoordinateSystemContext& context,
        SvgLengthScaleUnit contentUnits, float offsetX, float offsetY);

    // defs gradient animation
    void InitNoneFlag()
    {
        hrefFill_ = false;
        hrefRender_ = false;
        passStyle_ = false;
        inheritStyle_ = false;
        drawTraversed_ = false;
    }

    WeakPtr<SvgContext> svgContext_;
    std::vector<RefPtr<SvgNode>> children_;
    std::string nodeId_;
    std::string transform_;
    std::map<std::string, std::vector<float>> animateTransform_;

    SvgBaseAttribute attributes_;

    std::string hrefClipPath_;
    std::string hrefMaskId_;
    std::string hrefFilterId_;
    std::string imagePath_;
    uint8_t opacity_ = 0xFF;
    float smoothEdge_ = 0.0f;
    std::optional<ImageColorFilter> colorFilter_;
    Rect effectFilterArea_;
    float useOffsetX_ = 0.0f;
    float useOffsetY_ = 0.0f;

    bool hrefFill_ = true;   // get fill attributes from reference
    bool hrefRender_ = true; // get render attr (mask, filter, transform, opacity, clip path) from reference
    bool passStyle_ = true; // pass style attributes to child node, TAGS circle/path/line/... = false
    bool inheritStyle_ = true;  // inherit style attributes from parent node, TAGS mask/defs/pattern/filter = false
    bool isRootNode_ = false;
    RSCanvas* rsCanvas_ = nullptr;
    bool isDrawing_ = false; // Indicates if the current node is being drawn in the SVG rendering process.
    SvgLengthScaleRule lengthRule_;
    ACE_DISALLOW_COPY_AND_MOVE(SvgNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_NODE_H