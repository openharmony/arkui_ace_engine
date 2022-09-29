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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_NODE_H

#include <vector>

#include "include/core/SkCanvas.h"
#include "include/core/SkPath.h"

#include "base/memory/ace_type.h"
#include "core/components/declaration/svg/svg_base_declaration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_context.h"

namespace OHOS::Ace::NG {
enum class SvgLengthType {
    HORIZONTAL,
    VERTICAL,
    OTHER,
};

class SvgContext;

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

    virtual SkPath AsPath(const Size& viewPort) const
    {
        return {};
    }

    virtual RSPath AsRSPath(const Size& viewPort) const
    {
        return {};
    }

    const Rect AsBounds(const Size& viewPort) const
    {
        auto bounds = AsPath(viewPort).getBounds();
        return { bounds.left(), bounds.top(), bounds.width(), bounds.height() };
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

protected:
    // override as need by derived class
    // called by function AppendChild
    virtual void OnAppendChild(const RefPtr<SvgNode>& child) {}
    // called by function InitStyle
    virtual void OnInitStyle() {}

    // function override by graphic tag
    virtual void OnDraw(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color) {}
    void OnDrawTraversed(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color);
    bool OnCanvas(RSCanvas& canvas);
    void OnClipPath(RSCanvas& canvas, const Size& viewPort);
    void OnFilter(RSCanvas& canvas, const Size& viewPort);
    void OnMask(RSCanvas& canvas, const Size& viewPort);
    void OnTransform(RSCanvas& canvas, const Size& viewPort);

    double ConvertDimensionToPx(const Dimension& value, const Size& viewPort, SvgLengthType type) const;
    double ConvertDimensionToPx(const Dimension& value, double baseValue) const;

    std::optional<Gradient> GetGradient(const std::string& href);
    const Rect& GetRootViewBox() const;

    // defs gradient animation
    void InitNoneFlag()
    {
        hrefFill_ = false;
        hrefRender_ = false;
        childStyleTraversed_ = false;
        styleTraversed_ = false;
        drawTraversed_ = false;
    }

    WeakPtr<SvgContext> svgContext_;
    RefPtr<SvgBaseDeclaration> declaration_;
    std::vector<RefPtr<SvgNode>> children_;
    std::string nodeId_;
    std::string text_;

    std::string hrefClipPath_;
    std::string hrefMaskId_;
    std::string hrefFilterId_;
    std::string transform_;
    uint8_t opacity_ = 0xFF;

    bool hrefFill_ = true;   // 需要根据svg_xx特殊处理
    bool hrefRender_ = true; // 需要根据svg_xx特殊处理
    bool childStyleTraversed_ = true; // 样式继承传递时，是否传递给子标签， 图形标签 circle/path/line/... = false
    bool styleTraversed_ = true; // 样式继承传递时，是否支持被遍历 mask/defs/pattern/filter = false
    bool drawTraversed_ = true;  // 绘制时，是否支持被遍历 mask/defs/pattern/filter = false

    SkCanvas* skCanvas_ = nullptr;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_NODE_H