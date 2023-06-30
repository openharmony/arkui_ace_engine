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

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkCanvas.h"
#include "include/core/SkPath.h"
#else
#include "core/components_ng/render/drawing.h"
#endif

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/animation/svg_animate.h"
#include "core/components/declaration/svg/svg_base_declaration.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/svg/svg_context.h"

namespace OHOS::Ace::NG {
enum class SvgLengthType {
    HORIZONTAL,
    VERTICAL,
    OTHER,
};

class SvgContext;
class SvgAnimation;

// three level inherit class, for example:
// 1. SvgMask::SvgQuote::SvgNode
// 2. SvgPath::SvgGraphic::SvgNode
class SvgNode : public AceType {
    DECLARE_ACE_TYPE(SvgNode, AceType);

public:
    SvgNode() = default;
    ~SvgNode() override = default;

    void InitStyle(const RefPtr<SvgBaseDeclaration>& parent);

    // draw entrance function, approve override by second level class.
    virtual void Draw(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color);

    virtual void SetAttr(const std::string& name, const std::string& value);

    virtual void AppendChild(const RefPtr<SvgNode>& child)
    {
        children_.emplace_back(child);
        OnAppendChild(child);
    }

    virtual void Inherit(const RefPtr<SvgBaseDeclaration>& parent)
    {
        if (declaration_) {
            declaration_->Inherit(parent);
        }
    }

#ifndef USE_ROSEN_DRAWING
    virtual SkPath AsPath(const Size& viewPort) const
#else
    virtual RSRecordingPath AsPath(const Size& viewPort) const
#endif
    {
        return {};
    }

    virtual RSPath AsRSPath(const Size& viewPort) const;

    Rect AsBounds(const Size& viewPort) const
    {
#ifndef USE_ROSEN_DRAWING
        auto bounds = AsPath(viewPort).getBounds();
        return { bounds.left(), bounds.top(), bounds.width(), bounds.height() };
#else
        auto bounds = AsPath(viewPort).GetBounds();
        return { bounds.GetLeft(), bounds.GetTop(), bounds.GetWidth(), bounds.GetHeight() };
#endif
    }

    void SetContext(const WeakPtr<SvgContext>& svgContext)
    {
        svgContext_ = svgContext;
    }

    void SetNodeId(const std::string& value)
    {
        nodeId_ = value;
    }

    void SetText(const std::string& text)
    {
        text_ = text;
    }

    RefPtr<SvgBaseDeclaration> GetDeclaration()
    {
        return declaration_;
    }

protected:
    // override as need by derived class
    // called by function AppendChild
    virtual void OnAppendChild(const RefPtr<SvgNode>& child) {}
    // called by function InitStyle
    virtual void OnInitStyle() {}
    // function override by graphic tag
    virtual void OnDraw(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color) {}

    virtual void OnDrawTraversed(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color);
    bool OnCanvas(RSCanvas& canvas);
    void OnClipPath(RSCanvas& canvas, const Size& viewPort);
    void OnFilter(RSCanvas& canvas, const Size& viewPort);
    void OnMask(RSCanvas& canvas, const Size& viewPort);
    void OnTransform(RSCanvas& canvas, const Size& viewPort);

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
    void AnimateValueTransform(const RefPtr<SvgAnimation>& animate, double originalValue);
    void AnimateFrameTransform(const RefPtr<SvgAnimation>& animate, double originalValue);

    // update svg attribute in animation
    template<typename T>
    void UpdateAttr(const std::string& name, const T& val);
    void UpdateAttrHelper(const std::string& name, const std::string& val);

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
    RefPtr<SvgBaseDeclaration> declaration_;
    std::vector<RefPtr<SvgNode>> children_;
    std::string nodeId_;
    std::string text_;
    std::string transform_;
    std::map<std::string, std::vector<float>> animateTransform_;

    std::string hrefClipPath_;
    std::string hrefMaskId_;
    std::string hrefFilterId_;
    uint8_t opacity_ = 0xFF;

    bool hrefFill_ = true;   // get fill attributes from reference
    bool hrefRender_ = true; // get render attr (mask, filter, transform, opacity, clip path) from reference
    bool passStyle_ = true; // pass style attributes to child node, TAGS circle/path/line/... = false
    bool inheritStyle_ = true;  // inherit style attributes from parent node, TAGS mask/defs/pattern/filter = false
    bool drawTraversed_ = true; // enable OnDraw, TAGS mask/defs/pattern/filter = false

#ifndef USE_ROSEN_DRAWING
    SkCanvas* skCanvas_ = nullptr;
#else
    RSCanvas* rsCanvas_ = nullptr;
#endif

    ACE_DISALLOW_COPY_AND_MOVE(SvgNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_NODE_H