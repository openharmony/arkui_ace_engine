/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "compatible/components/svg/svg_loader.h"

#include "compatible/components/svg/dom_svg.h"
#include "compatible/components/svg/dom_svg_animate.h"
#include "compatible/components/svg/dom_svg_animate_motion.h"
#include "compatible/components/svg/dom_svg_animate_transform.h"
#include "compatible/components/svg/dom_svg_base.h"
#include "compatible/components/svg/dom_svg_circle.h"
#include "compatible/components/svg/dom_svg_defs.h"
#include "compatible/components/svg/dom_svg_ellipse.h"
#include "compatible/components/svg/dom_svg_fe_colormatrix.h"
#include "compatible/components/svg/dom_svg_fe_composite.h"
#include "compatible/components/svg/dom_svg_fe_gaussianblur.h"
#include "compatible/components/svg/dom_svg_fe_offset.h"
#include "compatible/components/svg/dom_svg_filter.h"
#include "compatible/components/svg/dom_svg_g.h"
#include "compatible/components/svg/dom_svg_line.h"
#include "compatible/components/svg/dom_svg_mask.h"
#include "compatible/components/svg/dom_svg_path.h"
#include "compatible/components/svg/dom_svg_polygon.h"
#include "compatible/components/svg/dom_svg_polyline.h"
#include "compatible/components/svg/dom_svg_rect.h"
#include "compatible/components/svg/dom_svg_text.h"
#include "compatible/components/svg/dom_svg_text_path.h"
#include "compatible/components/svg/dom_svg_tspan.h"
#include "compatible/components/svg/dom_svg_use.h"
#include "compatible/components/svg/svg_animate_declaration.h"
#include "compatible/components/svg/svg_base_declaration.h"
#include "compatible/components/svg/svg_circle_declaration.h"
#include "compatible/components/svg/svg_compatible_modifier.h"
#include "compatible/components/svg/svg_declaration.h"
#include "compatible/components/svg/svg_ellipse_declaration.h"
#include "compatible/components/svg/svg_fe_blend_declaration.h"
#include "compatible/components/svg/svg_fe_colormatrix_declaration.h"
#include "compatible/components/svg/svg_fe_component_transfer_declaration.h"
#include "compatible/components/svg/svg_fe_composite_declaration.h"
#include "compatible/components/svg/svg_fe_declaration.h"
#include "compatible/components/svg/svg_fe_flood_declaration.h"
#include "compatible/components/svg/svg_fe_func_declaration.h"
#include "compatible/components/svg/svg_fe_gaussianblur_declaration.h"
#include "compatible/components/svg/svg_fe_merge_declaration.h"
#include "compatible/components/svg/svg_fe_merge_node_declaration.h"
#include "compatible/components/svg/svg_fe_offset_declaration.h"
#include "compatible/components/svg/svg_filter_declaration.h"
#include "compatible/components/svg/svg_gradient_declaration.h"
#include "compatible/components/svg/svg_image_declaration.h"
#include "compatible/components/svg/svg_line_declaration.h"
#include "compatible/components/svg/svg_mask_declaration.h"
#include "compatible/components/svg/svg_path_declaration.h"
#include "compatible/components/svg/svg_pattern_declaration.h"
#include "compatible/components/svg/svg_polygon_declaration.h"
#include "compatible/components/svg/svg_rect_declaration.h"
#include "compatible/components/svg/svg_stop_declaration.h"
#include "compatible/components/svg/svg_text_declaration.h"
#include "compatible/components/svg/svg_text_path_declaration.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
namespace SvgCompatibleModifier {
const ArkUISvgCompatibleModifier* GetSvgCompatibleModifier();
} // namespace SvgCompatibleModifier
RefPtr<Framework::DOMNode> SvgLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvg>(nodeId, nodeName);
}

void* SvgLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgDeclaration>();
}

const void* SvgLoader::GetCustomModifier(const std::string& tag)
{
    return SvgCompatibleModifier::GetSvgCompatibleModifier();
}

RefPtr<Framework::DOMNode> SvgAnimateLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgAnimate>(nodeId, nodeName);
}

void* SvgAnimateLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgAnimateLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgAnimateLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgAnimateDeclaration>();
}

RefPtr<Framework::DOMNode> SvgAnimateMotionLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgAnimateMotion>(nodeId, nodeName);
}

void* SvgAnimateMotionLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgAnimateMotionLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgAnimateMotionLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgAnimateDeclaration>();
}

RefPtr<Framework::DOMNode> SvgAnimateTransformLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgAnimateTransform>(nodeId, nodeName);
}

void* SvgAnimateTransformLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgAnimateTransformLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgAnimateTransformLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgAnimateDeclaration>();
}

RefPtr<Framework::DOMNode> SvgCircleLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgCircle>(nodeId, nodeName);
}

void* SvgCircleLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgCircleLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgCircleLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgCircleDeclaration>();
}

RefPtr<Framework::DOMNode> SvgDefsLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgDefs>(nodeId, nodeName);
}

void* SvgDefsLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgDefsLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgDefsLoader::CreateDeclaration()
{
    return nullptr;
}

RefPtr<Framework::DOMNode> SvgEllipseLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgEllipse>(nodeId, nodeName);
}

void* SvgEllipseLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgEllipseLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgEllipseLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgEllipseDeclaration>();
}

RefPtr<Framework::DOMNode> SvgFeColorMatrixLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgFeColorMatrix>(nodeId, nodeName);
}

void* SvgFeColorMatrixLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgFeColorMatrixLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgFeColorMatrixLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgFeColorMatrixDeclaration>();
}

RefPtr<Framework::DOMNode> SvgFeCompositeLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgFeComposite>(nodeId, nodeName);
}

void* SvgFeCompositeLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgFeCompositeLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgFeCompositeLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgFeCompositeDeclaration>();
}

RefPtr<Framework::DOMNode> SvgFeGaussianBlurLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgFeGaussianBlur>(nodeId, nodeName);
}

void* SvgFeGaussianBlurLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgFeGaussianBlurLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgFeGaussianBlurLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgFeGaussianBlurDeclaration>();
}

RefPtr<Framework::DOMNode> SvgFeOffsetLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgFeOffset>(nodeId, nodeName);
}

void* SvgFeOffsetLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgFeOffsetLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgFeOffsetLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgFeOffsetDeclaration>();
}

RefPtr<Framework::DOMNode> SvgFilterLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgFilter>(nodeId, nodeName);
}

void* SvgFilterLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgFilterLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgFilterLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgFilterDeclaration>();
}

RefPtr<Framework::DOMNode> SvgGLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgG>(nodeId, nodeName);
}

void* SvgGLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgGLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgGLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgDeclaration>();
}

RefPtr<Framework::DOMNode> SvgLineLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgLine>(nodeId, nodeName);
}

void* SvgLineLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgLineLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgLineLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgLineDeclaration>();
}

RefPtr<Framework::DOMNode> SvgMaskLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgMask>(nodeId, nodeName);
}

void* SvgMaskLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgMaskLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgMaskLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgMaskDeclaration>();
}

RefPtr<Framework::DOMNode> SvgPathLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgPath>(nodeId, nodeName);
}

void* SvgPathLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgPathLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgPathLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgPathDeclaration>();
}

RefPtr<Framework::DOMNode> SvgPolygonLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgPolygon>(nodeId, nodeName);
}

void* SvgPolygonLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgPolygonLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgPolygonLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgPolygonDeclaration>();
}

RefPtr<Framework::DOMNode> SvgPolylineLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgPolyline>(nodeId, nodeName);
}

void* SvgPolylineLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgPolylineLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgPolylineLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgPolygonDeclaration>();
}

RefPtr<Framework::DOMNode> SvgRectLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgRect>(nodeId, nodeName);
}

void* SvgRectLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgRectLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgRectLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgRectDeclaration>();
}

RefPtr<Framework::DOMNode> SvgTextLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgText>(nodeId, nodeName);
}

void* SvgTextLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgTextLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgTextLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgTextDeclaration>();
}

RefPtr<Framework::DOMNode> SvgTextPathLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgTextPath>(nodeId, nodeName);
}

void* SvgTextPathLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgTextPathLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgTextPathLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgTextPathDeclaration>();
}

RefPtr<Framework::DOMNode> SvgTspanLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgTspan>(nodeId, nodeName);
}

void* SvgTspanLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgTspanLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgTspanLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgTextDeclaration>();
}

RefPtr<Framework::DOMNode> SvgUseLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSvgUse>(nodeId, nodeName);
}

void* SvgUseLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgUseLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgUseLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgDeclaration>();
}

RefPtr<Framework::DOMNode> SvgGradientLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return nullptr;
}

void* SvgGradientLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgGradientLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgGradientLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgGradientDeclaration>();
}

RefPtr<Framework::DOMNode> SvgStopLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return nullptr;
}

void* SvgStopLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> SvgStopLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> SvgStopLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SvgStopDeclaration>();
}
} // namespace OHOS::Ace