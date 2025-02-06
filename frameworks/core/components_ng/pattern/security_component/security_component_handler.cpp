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

#include "core/components_ng/pattern/security_component/security_component_handler.h"
#include "ui/base/geometry/dimension.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "base/geometry/dimension.h"
#include "base/utils/system_properties.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/security_component/security_component_log.h"
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
using namespace OHOS::Security;
using namespace OHOS::Security::SecurityComponent;
namespace {
constexpr uint64_t SECOND_TO_MILLISECOND = 1000;
constexpr float HALF = 2.0f;
const std::string SEC_COMP_ID = "security component id = ";
const std::string SEC_COMP_TYPE = ", security component type = ";
}

static std::vector<uintptr_t> g_callList = {
    reinterpret_cast<uintptr_t>(SecurityComponentHandler::RegisterSecurityComponent),
    reinterpret_cast<uintptr_t>(SecurityComponentHandler::UpdateSecurityComponent),
    reinterpret_cast<uintptr_t>(SecurityComponentHandler::ReportSecurityComponentClickEventInner)
};

SecurityComponentProbe SecurityComponentHandler::probe;
SecurityComponent::SecCompUiRegister uiRegister(g_callList, &SecurityComponentHandler::probe);

bool SecurityComponentHandler::GetDisplayOffset(RefPtr<FrameNode>& node, double& offsetX, double& offsetY)
{
    double x = node->GetTransformRelativeOffset().GetX();
    double y = node->GetTransformRelativeOffset().GetY();
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto windowOffset = pipelineContext->GetDisplayWindowRectInfo().GetOffset();
    offsetX = x + windowOffset.GetX();
    offsetY = y + windowOffset.GetY();
    return true;
}

bool SecurityComponentHandler::GetWindowRect(RefPtr<FrameNode>& node,
    OHOS::Security::SecurityComponent::SecCompRect& winRect)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto rect = pipelineContext->GetDisplayWindowRectInfo();
    winRect.x_ = rect.Left();
    winRect.y_ = rect.Top();
    winRect.width_ = rect.Right() - rect.Left();
    winRect.height_ = rect.Bottom() - rect.Top();
    return true;
}

bool SecurityComponentHandler::CheckOpacity(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
    std::string& message)
{
    if (node->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
        return false;
    }
    if (renderContext->GetOpacity().has_value() &&
        !NearEqual(renderContext->GetOpacity().value(), 1.0f)) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s opacity = %{public}f, " \
            "security component is invalid", node->GetTag().c_str(), renderContext->GetOpacity().value());
        message = ", attribute opacity of parent component " + node->GetTag() +
            "(id = " + std::to_string(node->GetId()) + ") is set, opacity = " +
            std::to_string(renderContext->GetOpacity().value());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckBrightness(const RefPtr<FrameNode>& node,
    const RefPtr<RenderContext>& renderContext, std::string& message)
{
    if (renderContext->GetFrontBrightness().has_value() &&
        !NearEqual(renderContext->GetFrontBrightness().value().Value(), 1.0f)) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s brightness = %{public}f, " \
            "security component is invalid", node->GetTag().c_str(),
            renderContext->GetFrontBrightness().value().Value());
        message = ", attribute brightness of parent component " + node->GetTag() +
            "(id = " + std::to_string(node->GetId()) + ") is set, brightness = " +
            std::to_string(renderContext->GetFrontBrightness().value().Value());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckVisibility(const RefPtr<FrameNode>& node, RefPtr<LayoutProperty>& layoutProperty,
    std::string& message)
{
    if (layoutProperty->GetVisibility().has_value() &&
        (layoutProperty->GetVisibility().value() != VisibleType::VISIBLE)) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s is not visible, security component is invalid",
            node->GetTag().c_str());
        message = ", attribute visibility of parent component " + node->GetTag() +
             "(id = " + std::to_string(node->GetId()) + ") is set, parent component is not visible";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckBlur(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
    std::string& message)
{
    if (renderContext->GetFrontBlurRadius().has_value() &&
        GreatNotEqual(renderContext->GetFrontBlurRadius().value().ConvertToPx(), 0.0f)) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s blur is set, security component is invalid",
            node->GetTag().c_str());
        message = ", attribute blur of parent component " + node->GetTag() +
            "(id = " + std::to_string(node->GetId()) + ") is set";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckForegroundBlurStyle(const RefPtr<FrameNode>& node,
    const RefPtr<RenderContext>& renderContext, std::string& message)
{
    auto blurStyleOption = renderContext->GetFrontBlurStyle();
    if (blurStyleOption.has_value() && (blurStyleOption->blurStyle != BlurStyle::NO_MATERIAL) &&
        (!NearEqual(blurStyleOption->scale, 0.0))) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s foregroundBlurStyle is set, " \
            "security component is invalid", node->GetTag().c_str());
        message = ", attribute foregroundBlurStyle of parent component " +
            node->GetTag() + "(id = " + std::to_string(node->GetId()) + ") is set";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckBlendMode(const RefPtr<FrameNode>& node,
    const RefPtr<RenderContext>& renderContext, std::string& message)
{
    auto blendMode = renderContext->GetBackBlendMode();
    if (blendMode.has_value() && blendMode != BlendMode::NONE && blendMode != BlendMode::SRC_OVER) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s blendMode is set, " \
            "security component is invalid", node->GetTag().c_str());
        message = ", attribute blendMode of parent component " +
            node->GetTag() + "(id = " + std::to_string(node->GetId()) + ") is set";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::GetBorderRect(const RefPtr<FrameNode>& parentNode, std::vector<RectF>& borderRects)
{
    auto renderContext = parentNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto borderWidth = renderContext->GetBorderWidth();
    CHECK_NULL_RETURN(borderWidth, false);
    auto parentRect = renderContext->GetPaintRectWithTransform();
    parentRect.SetOffset(parentNode->GetPositionToScreenWithTransform());
    auto borderColor = renderContext->GetBorderColor();
    auto leftIsTransparent = borderColor && borderColor->leftColor.has_value() &&
        (borderColor->leftColor.value() == Color::TRANSPARENT);
    auto rightIsTransparent = borderColor && borderColor->rightColor.has_value() &&
        (borderColor->rightColor.value() == Color::TRANSPARENT);
    auto topIsTransparent = borderColor && borderColor->topColor.has_value() &&
        (borderColor->topColor.value() == Color::TRANSPARENT);
    auto bottomIsTransparent = borderColor && borderColor->bottomColor.has_value() &&
        (borderColor->bottomColor.value() == Color::TRANSPARENT);

    if (borderWidth->leftDimen.has_value() && GreatNotEqual(borderWidth->leftDimen.value().ConvertToPx(), 1.0) &&
        !leftIsTransparent) {
        auto leftWidth = borderWidth->leftDimen.value().ConvertToPx();
        borderRects.emplace_back(RectF(parentRect.GetX(), parentRect.GetY(), leftWidth, parentRect.Height()));
    }
    if (borderWidth->rightDimen.has_value() && GreatNotEqual(borderWidth->rightDimen.value().ConvertToPx(), 1.0) &&
        !rightIsTransparent) {
        auto rightWidth = borderWidth->rightDimen.value().ConvertToPx();
        borderRects.emplace_back(RectF(parentRect.GetX() + parentRect.Width() - rightWidth, parentRect.GetY(),
            rightWidth, parentRect.Height()));
    }
    if (borderWidth->topDimen.has_value() && GreatNotEqual(borderWidth->topDimen.value().ConvertToPx(), 1.0) &&
        !topIsTransparent) {
        auto topWidth = borderWidth->topDimen.value().ConvertToPx();
        borderRects.emplace_back(RectF(parentRect.GetX(), parentRect.GetY(), parentRect.Width(), topWidth));
    }
    if (borderWidth->bottomDimen.has_value() && GreatNotEqual(borderWidth->bottomDimen.value().ConvertToPx(), 1.0) &&
        !bottomIsTransparent) {
        auto bottomWidth = borderWidth->bottomDimen.value().ConvertToPx();
        borderRects.emplace_back(RectF(parentRect.GetX(), parentRect.GetY() + parentRect.Height() - bottomWidth,
            parentRect.Width(), bottomWidth));
    }
    return true;
}

bool SecurityComponentHandler::CheckParentBorder(const RefPtr<FrameNode>& parentNode, const RectF& scRect,
    std::string& message)
{
    std::vector<RectF> borderRects;
    if (!GetBorderRect(parentNode, borderRects)) {
        return false;
    }
    for (const auto& rect : borderRects) {
        if (!rect.IsInnerIntersectWithRound(scRect)) {
            continue;
        }
        SC_LOG_ERROR("SecurityComponentCheckFail: security component is covered by the border of parent" \
            " %{public}s", parentNode->GetTag().c_str());
        message = ", security component is covered by the border of parent component " +
            parentNode->GetTag() + "(id = " + std::to_string(parentNode->GetId()) + ")";
        return true;
    }

    return false;
}

float SecurityComponentHandler::GetLinearGradientBlurRatio(std::vector<std::pair<float, float>>& fractionStops)
{
    float ratio = 1.0;
    int32_t size = static_cast<int32_t>(fractionStops.size());
    for (auto i = 0; i < size; i++) {
        auto fraction = fractionStops[i];
        if (NearEqual(fraction.first, 0.0)) {
            ratio = fraction.second;
        } else {
            break;
        }
    }
    return ratio;
}

bool SecurityComponentHandler::CheckDistance(const float& deltaY, const float& radius, const float& distance,
    const int32_t& multiplier)
{
    if (NearEqual(radius, 0.0)) {
        if (GreatNotEqual(deltaY * multiplier, 0.0)) {
            if (GreatNotEqual(distance, 1.0)) {
                return true;
            }
        }
        return false;
    }

    if (GreatOrEqual(deltaY * multiplier, 0.0)) {
        return true;
    }
    if (LessNotEqual(distance, (radius - 1) * (radius - 1))) {
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckDiagonalLinearGradientBlur(const RectF& parentRect, const RectF& rect,
    const NG::GradientDirection direction, const float& ratio, const float& radius)
{
    Point dest;
    Point src;
    float gradient;
    int32_t multiplier = 0;
    switch (direction) {
        case GradientDirection::LEFT_TOP:
            dest.SetX(rect.GetX() + radius);
            dest.SetY(rect.GetY() + radius);
            src.SetX(parentRect.GetX() + (1 - ratio) * parentRect.Width());
            src.SetY(parentRect.GetY() + (1 - ratio) * parentRect.Height());
            gradient = (0 - parentRect.Width()) / parentRect.Height();
            multiplier = 1;
            break;
        case GradientDirection::LEFT_BOTTOM:
            dest.SetX(rect.GetX() + radius);
            dest.SetY(rect.GetY() + rect.Height() - radius);
            src.SetX(parentRect.GetX() + (1 - ratio) * parentRect.Width());
            src.SetY(parentRect.GetY() + ratio * parentRect.Height());
            gradient = parentRect.Width() / parentRect.Height();
            multiplier = -1;
            break;
        case GradientDirection::RIGHT_TOP:
            dest.SetX(rect.GetX() + rect.Width() - radius);
            dest.SetY(rect.GetY() + radius);
            src.SetX(parentRect.GetX() + ratio * parentRect.Width());
            src.SetY(parentRect.GetY() + (1 - ratio) * parentRect.Height());
            gradient = parentRect.Width() / parentRect.Height();
            multiplier = 1;
            break;
        case GradientDirection::RIGHT_BOTTOM:
            dest.SetX(rect.GetX() + rect.Width() - radius);
            dest.SetY(rect.GetY() + rect.Height() - radius);
            src.SetX(parentRect.GetX() + ratio * parentRect.Width());
            src.SetY(parentRect.GetY() + ratio * parentRect.Height());
            gradient = (0 - parentRect.Width()) / parentRect.Height();
            multiplier = -1;
            break;
        default:
            return false;
    }

    float deltaY = gradient * dest.GetX() + src.GetY() - gradient * src.GetX() - dest.GetY();
    auto distance = (deltaY * deltaY) / (1 + gradient * gradient);
    return CheckDistance(deltaY, radius, distance, multiplier);
}

float SecurityComponentHandler::GetBorderRadius(RefPtr<FrameNode>& node, const NG::GradientDirection direction)
{
    RectF rect = node->GetTransformRectRelativeToWindow();
    auto maxRadius = std::min(rect.Width(), rect.Height()) / HALF;
    auto layoutProperty = AceType::DynamicCast<SecurityComponentLayoutProperty>(node->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, 0.0);
    if (layoutProperty->GetBackgroundType() == static_cast<int32_t>(ButtonType::CIRCLE) ||
        layoutProperty->GetBackgroundType() == static_cast<int32_t>(ButtonType::CAPSULE)) {
        return maxRadius;
    }

    RefPtr<FrameNode> buttonNode = GetSecCompChildNode(node, V2::BUTTON_ETS_TAG);
    CHECK_NULL_RETURN(buttonNode, 0.0);
    auto bgProp = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(bgProp, 0.0);
    auto borderRadius = bgProp->GetBorderRadius();
    float radius = 0.0;

    switch (direction) {
        case GradientDirection::LEFT_TOP:
            if (borderRadius.has_value() && borderRadius->radiusTopLeft.has_value()) {
                auto obtainedRadius = borderRadius->radiusTopLeft.value().ConvertToPx();
                radius = GreatNotEqual(obtainedRadius, maxRadius) ? maxRadius : obtainedRadius;
            }
            return radius;
        case GradientDirection::LEFT_BOTTOM:
            if (borderRadius.has_value() && borderRadius->radiusBottomLeft.has_value()) {
                auto obtainedRadius = borderRadius->radiusBottomLeft.value().ConvertToPx();
                radius = GreatNotEqual(obtainedRadius, maxRadius) ? maxRadius : obtainedRadius;
            }
            return radius;
        case GradientDirection::RIGHT_TOP:
            if (borderRadius.has_value() && borderRadius->radiusTopRight.has_value()) {
                auto obtainedRadius = borderRadius->radiusTopRight.value().ConvertToPx();
                radius = GreatNotEqual(obtainedRadius, maxRadius) ? maxRadius : obtainedRadius;
            }
            return radius;
        case GradientDirection::RIGHT_BOTTOM:
            if (borderRadius.has_value() && borderRadius->radiusBottomRight.has_value()) {
                auto obtainedRadius = borderRadius->radiusBottomRight.value().ConvertToPx();
                radius = GreatNotEqual(obtainedRadius, maxRadius) ? maxRadius : obtainedRadius;
            }
            return radius;
        default:
            return radius;
    }
    return radius;
}

bool SecurityComponentHandler::CheckLinearGradientBlur(const RefPtr<FrameNode>& parentNode,
    RefPtr<FrameNode>& node)
{
    RectF parentRect = parentNode->GetTransformRectRelativeToWindow();
    if (NearEqual(parentRect.Width(), 0.0) || NearEqual(parentRect.Height(), 0.0)) {
        return false;
    }

    RectF rect = node->GetTransformRectRelativeToWindow();
    const auto& parentRender = parentNode->GetRenderContext();
    CHECK_NULL_RETURN(parentRender, false);
    auto linearGradientBlurPara = parentRender->GetLinearGradientBlur();
    CHECK_NULL_RETURN(linearGradientBlurPara, false);
    float ratio = GetLinearGradientBlurRatio(linearGradientBlurPara->fractionStops_);
    if (NearEqual(ratio, 1.0)) {
        return false;
    }

    float radius = 0.0;
    switch (linearGradientBlurPara->direction_) {
        case GradientDirection::LEFT:
            return GreatNotEqual((parentRect.GetX() + parentRect.Width() - rect.GetX()) / parentRect.Width(), ratio);
        case GradientDirection::TOP:
            return GreatNotEqual((parentRect.GetY() + parentRect.Height() - rect.GetY()) / parentRect.Height(), ratio);
        case GradientDirection::RIGHT:
            return GreatNotEqual((rect.GetX() + rect.Width() - parentRect.GetX()) / parentRect.Width(), ratio);
        case GradientDirection::BOTTOM:
            return GreatNotEqual((rect.GetY() + rect.Height() - parentRect.GetY()) / parentRect.Height(), ratio);
        case GradientDirection::LEFT_TOP:
        case GradientDirection::LEFT_BOTTOM:
        case GradientDirection::RIGHT_TOP:
        case GradientDirection::RIGHT_BOTTOM:
            radius = GetBorderRadius(node, linearGradientBlurPara->direction_);
            return CheckDiagonalLinearGradientBlur(parentRect, rect,
                linearGradientBlurPara->direction_, ratio, radius);
        default:
            return false;
    }
}

bool SecurityComponentHandler::CheckGrayScale(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
    std::string& message)
{
    if (renderContext->GetFrontGrayScale().has_value() &&
        GreatNotEqual(renderContext->GetFrontGrayScale().value().ConvertToVp(), 0.0f)) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s grayscale is set, security component is invalid",
            node->GetTag().c_str());
        message = ", attribute grayscale of parent component " + node->GetTag() + "(id = " +
            std::to_string(node->GetId()) + ") is set";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckSaturate(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
    std::string& message)
{
    if (renderContext->GetFrontSaturate().has_value() &&
        !NearEqual(renderContext->GetFrontSaturate().value().ConvertToVp(), 1.0f)) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s saturate is set, security component is invalid",
            node->GetTag().c_str());
        message = ", attribute saturate of parent component " + node->GetTag() +
            "(id = " + std::to_string(node->GetId()) + ") is set";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckContrast(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
    std::string& message)
{
    if (renderContext->GetFrontContrast().has_value() &&
        !NearEqual(renderContext->GetFrontContrast().value().ConvertToVp(), 1.0f)) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s contrast is set, security component is invalid",
            node->GetTag().c_str());
        message = ", attribute contrast of parent component " + node->GetTag() +
            "(id = " + std::to_string(node->GetId()) + ") is set";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckInvert(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
    std::string& message)
{
    if (renderContext->GetFrontInvert().has_value() && renderContext->GetFrontInvert()->index() == 0 &&
        !NearEqual(std::get<float>(renderContext->GetFrontInvert().value()), 0.0f)) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s invert is set, security component is invalid",
            node->GetTag().c_str());
        message = ", attribute invert of parent component " + node->GetTag() +
            "(id = " + std::to_string(node->GetId()) + ") is set";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckSepia(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
    std::string& message)
{
    if (renderContext->GetFrontSepia().has_value() &&
        !NearEqual(renderContext->GetFrontSepia().value().ConvertToVp(), 0.0f)) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s sepia is set, security component is invalid",
            node->GetTag().c_str());
        message = ", attribute sepia of parent component " + node->GetTag() +
            "(id = " + std::to_string(node->GetId()) + ") is set";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckHueRotate(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
    std::string& message)
{
    if (renderContext->GetFrontHueRotate().has_value() &&
        !NearEqual(renderContext->GetFrontHueRotate().value(), 0.0f) &&
        !NearEqual(renderContext->GetFrontHueRotate().value(), 360.0f)) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s hueRotate is set, security component is invalid",
            node->GetTag().c_str());
        message = ", attribute hueRotate of parent component " + node->GetTag() +
            "(id = " + std::to_string(node->GetId()) + ") is set";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckColorBlend(const RefPtr<FrameNode>& node,
    const RefPtr<RenderContext>& renderContext, std::string& message)
{
    if (renderContext->GetFrontColorBlend().has_value() &&
        (renderContext->GetFrontColorBlend().value() != Color::TRANSPARENT)) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s colorBlend is set, security component is invalid",
            node->GetTag().c_str());
        message = ", attribute colorBlend of parent component " + node->GetTag() +
            "(id = " + std::to_string(node->GetId()) + ") is set";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckClipMask(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
    std::string& message)
{
    if (renderContext->GetClipMask().has_value()) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s clip mask is set, security component is invalid",
            node->GetTag().c_str());
        message = ", attribute maskShape of parent component " + node->GetTag() +
            "(id = " + std::to_string(node->GetId()) + ") is set";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckForegroundColor(const RefPtr<FrameNode>& node,
    const RefPtr<RenderContext>& renderContext, std::string& message)
{
    if (renderContext->GetForegroundColor().has_value()) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s foregroundColor is set, " \
            "security component is invalid", node->GetTag().c_str());
        message = ", attribute foregroundColor of parent component " + node->GetTag() +
            "(id = " + std::to_string(node->GetId()) + ") is set";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckSphericalEffect(const RefPtr<FrameNode>& node,
    const RefPtr<RenderContext>& renderContext, std::string& message)
{
    if (renderContext->GetSphericalEffect().has_value() &&
        !NearEqual(renderContext->GetSphericalEffect().value(), 0.0f)) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s sphericalEffect is set, " \
            "security component is invalid", node->GetTag().c_str());
        message = ", attribute sphericalEffect of parent component " + node->GetTag() +
            "(id = " + std::to_string(node->GetId()) + ") is set";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckLightUpEffect(const RefPtr<FrameNode>& node,
    const RefPtr<RenderContext>& renderContext, std::string& message)
{
    if (renderContext->GetLightUpEffect().has_value()) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s lightUpEffect is set, " \
            "security component is invalid", node->GetTag().c_str());
        message = ", attribute lightUpEffect of parent component " + node->GetTag() +
            "(id = " + std::to_string(node->GetId()) + ") is set";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckPixelStretchEffect(const RefPtr<FrameNode>& node,
    const RefPtr<RenderContext>& renderContext, std::string& message)
{
    if (renderContext->GetPixelStretchEffect().has_value()) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s pixelStretchEffect is set, " \
            "security component is invalid", node->GetTag().c_str());
        message = ", attribute pixelStretchEffect of parent component " + node->GetTag() +
            "(id = " + std::to_string(node->GetId()) + ") is set";
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckRenderEffect(RefPtr<FrameNode>& node, std::string& message)
{
    const auto& renderContext = node->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto layoutProperty = node->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);

    if (CheckOpacity(node, renderContext, message) || CheckBrightness(node, renderContext, message) ||
        CheckVisibility(node, layoutProperty, message) || CheckBlur(node, renderContext, message) ||
        CheckGrayScale(node, renderContext, message) || CheckSaturate(node, renderContext, message) ||
        CheckContrast(node, renderContext, message) || CheckInvert(node, renderContext, message) ||
        CheckSepia(node, renderContext, message) || CheckHueRotate(node, renderContext, message) ||
        CheckColorBlend(node, renderContext, message) || CheckClipMask(node, renderContext, message) ||
        CheckForegroundColor(node, renderContext, message) || CheckSphericalEffect(node, renderContext, message) ||
        CheckLightUpEffect(node, renderContext, message) || CheckPixelStretchEffect(node, renderContext, message) ||
        CheckForegroundBlurStyle(node, renderContext, message) || CheckBlendMode(node, renderContext, message)) {
        return true;
    }
    return false;
}

std::string GetClipErrorMsg(const std::string& scId, const std::string& scType,
    const RectF& visibleRect, const RectF& frameRect, const RefPtr<FrameNode>& parentNode)
{
    std::string message = "The id of " + scType + " is " + scId +
        ", attribute clip of parent component " + parentNode->GetTag() +
        "(id = " + std::to_string(parentNode->GetId()) + ") is set, " + scType +
        " is not completely displayed. The rect of visible part is {width = " +
        std::to_string(visibleRect.Width()) +
        ", height = " + std::to_string(visibleRect.Height()) +
        "}, the real size of " + scType + " is {width = " +
        std::to_string(frameRect.Width()) +
        ", height = " + std::to_string(frameRect.Height()) + "}";
    return message;
}

bool SecurityComponentHandler::IsSecComponentClipped(RefPtr<FrameNode>& parentNode,
    RectF& visibleRect, const RectF& frameRect, OHOS::Security::SecurityComponent::SecCompBase& buttonInfo)
{
    GetVisibleRect(parentNode, visibleRect);
    bool isClipped = IsOutOfParentWithRound(visibleRect, frameRect, buttonInfo);
    buttonInfo.isClipped_ = isClipped;
    buttonInfo.parentTag_ = parentNode->GetTag();

    if (isClipped && (visibleRect.IsValid() || frameRect.IsValid())) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Parents clip is set, " \
            "security component is not completely displayed.");
        SC_LOG_ERROR("visibleWidth: %{public}f, visibleHeight: %{public}f, " \
            "frameWidth: %{public}f, frameHeight: %{public}f",
            visibleRect.Width(), visibleRect.Height(), frameRect.Width(), frameRect.Height());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckParentNodesEffect(RefPtr<FrameNode>& node,
    OHOS::Security::SecurityComponent::SecCompBase& buttonInfo, std::string& message)
{
    RefPtr<RenderContext> renderContext = node->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto frameRect = renderContext->GetPaintRectWithTransform();
    frameRect.SetOffset(node->GetPositionToScreenWithTransform());
    auto visibleRect = frameRect;
    auto parent = node->GetParent();
    std::string scId = std::to_string(node->GetId());
    std::string scType = node->GetTag();
    while (parent != nullptr) {
        auto parentNode = AceType::DynamicCast<FrameNode>(parent);
        if (parentNode == nullptr) {
            parent = parent->GetParent();
            continue;
        }
        if (parentNode->CheckTopWindowBoundary()) {
            break;
        }
        if (CheckRenderEffect(parentNode, message)) {
            message = SEC_COMP_ID + scId + SEC_COMP_TYPE + scType + message;
            return true;
        }
        if (CheckParentBorder(parentNode, frameRect, message)) {
            message = SEC_COMP_ID + scId + SEC_COMP_TYPE + scType + message;
            return true;
        }
        if (CheckLinearGradientBlur(parentNode, node)) {
            SC_LOG_ERROR("SecurityComponentCheckFail: Parent %{public}s LinearGradientBlur is set, " \
                "security component is invalid", parentNode->GetTag().c_str());
            message = SEC_COMP_ID + scId + SEC_COMP_TYPE + scType +
                ", attribute linearGradientBlur of parent component " +
                node->GetTag() + " is set";
            return true;
        }
        RefPtr<RenderContext> parentRenderContext = parentNode->GetRenderContext();
        if ((parentRenderContext == nullptr) ||
            !parentRenderContext->GetClipEdge().value_or(false)) {
            parent = parent->GetParent();
            continue;
        }
        if (IsSecComponentClipped(parentNode, visibleRect, frameRect, buttonInfo)) {
            message = GetClipErrorMsg(scId, scType, visibleRect, frameRect, parentNode);
            return true;
        }
        parent = parent->GetParent();
    }
    return false;
}

void SecurityComponentHandler::GetVisibleRect(RefPtr<FrameNode>& node, RectF& visibleRect)
{
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    RectF parentRect = renderContext->GetPaintRectWithTransform();
    parentRect.SetOffset(node->GetPositionToScreenWithTransform());
    visibleRect = visibleRect.Constrain(parentRect);
}

bool SecurityComponentHandler::IsOutOfParentWithRound(const RectF& visibleRect, const RectF& renderRect,
    OHOS::Security::SecurityComponent::SecCompBase& buttonInfo)
{
    if (!visibleRect.IsValid() || !renderRect.IsValid()) {
        return true;
    }

    if (NearEqual(visibleRect.Width(), 0.0) || NearEqual(visibleRect.Height(), 0.0) ||
        NearEqual(renderRect.Width(), 0.0) || NearEqual(renderRect.Height(), 0.0)) {
        return true;
    }

    buttonInfo.leftClip_ = visibleRect.Left() - renderRect.Left();
    buttonInfo.rightClip_ = renderRect.Right() - visibleRect.Right();
    buttonInfo.topClip_ = visibleRect.Top() - renderRect.Top();
    buttonInfo.bottomClip_ = renderRect.Bottom() - visibleRect.Bottom();

    return LessNotEqual(renderRect.Left() + 1.0, visibleRect.Left()) ||
        GreatNotEqual(renderRect.Right(), visibleRect.Right() + 1.0) ||
        LessNotEqual(renderRect.Top() + 1.0, visibleRect.Top()) ||
        GreatNotEqual(renderRect.Bottom(), visibleRect.Bottom() + 1.0);
}

bool SecurityComponentHandler::GetWindowSceneWindowId(RefPtr<FrameNode>& node, uint32_t& windId)
{
    CHECK_NULL_RETURN(node, false);
    auto parent = node->GetParent();
    while (parent != nullptr && parent->GetTag() != V2::WINDOW_SCENE_ETS_TAG) {
        parent = parent->GetParent();
    }
    CHECK_NULL_RETURN(parent, false);
    auto windowSceneFrameNode = AceType::DynamicCast<FrameNode>(parent);
    CHECK_NULL_RETURN(windowSceneFrameNode, false);
    auto windowScene = windowSceneFrameNode->GetPattern<SystemWindowScene>();
    CHECK_NULL_RETURN(windowScene, false);
    auto session = windowScene->GetSession();
    CHECK_NULL_RETURN(session, false);

    windId = static_cast<uint32_t>(session->GetPersistentId());
    return true;
}

bool SecurityComponentHandler::GetPaddingInfo(OHOS::Security::SecurityComponent::SecCompBase& buttonInfo,
    RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto layoutProperty = AceType::DynamicCast<SecurityComponentLayoutProperty>(node->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);
    auto pipeline = node->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<SecurityComponentTheme>();
    CHECK_NULL_RETURN(theme, false);
    buttonInfo.padding_.top =
        layoutProperty->GetBackgroundTopPadding().value_or(theme->GetBackgroundTopPadding()).ConvertToVp();
    buttonInfo.padding_.right =
        layoutProperty->GetBackgroundRightPadding().value_or(theme->GetBackgroundRightPadding()).ConvertToVp();
    buttonInfo.padding_.bottom =
        layoutProperty->GetBackgroundBottomPadding().value_or(theme->GetBackgroundBottomPadding()).ConvertToVp();
    buttonInfo.padding_.left =
        layoutProperty->GetBackgroundLeftPadding().value_or(theme->GetBackgroundLeftPadding()).ConvertToVp();
    buttonInfo.textIconSpace_ =
        layoutProperty->GetTextIconSpace().value_or(theme->GetTextIconSpace()).ConvertToVp();
    return true;
}

bool SecurityComponentHandler::InitBaseInfo(OHOS::Security::SecurityComponent::SecCompBase& buttonInfo,
    RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    buttonInfo.nodeId_ = node->GetId();
    if (!GetPaddingInfo(buttonInfo, node)) {
        SC_LOG_WARN("InitBaseInfoWarning: Get padding info failed");
        return false;
    }

    if (!GetDisplayOffset(node, buttonInfo.rect_.x_, buttonInfo.rect_.y_)) {
        SC_LOG_WARN("InitBaseInfoWarning: Get display offset failed");
        return false;
    }

    if (!GetWindowRect(node, buttonInfo.windowRect_)) {
        SC_LOG_WARN("InitBaseInfoWarning: Get window rect failed");
        return false;
    }
    auto render = node->GetRenderContext();
    CHECK_NULL_RETURN(render, false);
    auto rect = render->GetPaintRectWithTransform();
    buttonInfo.rect_.width_ = rect.Width();
    buttonInfo.rect_.height_ = rect.Height();
    auto container = AceType::DynamicCast<Platform::AceContainer>(Container::Current());
    CHECK_NULL_RETURN(container, false);
    uint32_t windId = container->GetWindowId();
    auto pipeline = node->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, false);
    if (pipeline->IsFocusWindowIdSetted()) {
        windId = pipeline->GetFocusWindowId();
    }
    if (container->IsScenceBoardWindow()) {
        GetWindowSceneWindowId(node, windId);
    }
    buttonInfo.windowId_ = static_cast<int32_t>(windId);
    buttonInfo.crossAxisState_ = CrossAxisState::STATE_INVALID;
    auto instanceId = pipeline->GetInstanceId();
    auto window = Platform::AceContainer::GetUIWindow(instanceId);
    if (window) {
        buttonInfo.crossAxisState_ = static_cast<CrossAxisState>(window->GetCrossAxisState());
    }
    uint64_t displayId = container->GetDisplayId();
    if (displayId == Rosen::DISPLAY_ID_INVALID) {
        SC_LOG_WARN("InitBaseInfoWarning: Get displayId failed, using default displayId");
        displayId = 0;
    }
    buttonInfo.displayId_ = displayId;
    return true;
}

bool InitSCIconInfo(OHOS::Security::SecurityComponent::SecCompBase& buttonInfo,
    RefPtr<FrameNode>& iconNode)
{
    if (iconNode != nullptr) {
        CHECK_NULL_RETURN(iconNode->GetGeometryNode(), false);
        auto iconProp = iconNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_RETURN(iconProp, false);
        CHECK_NULL_RETURN(iconProp->GetCalcLayoutConstraint(), false);
        auto width = iconProp->GetCalcLayoutConstraint()->selfIdealSize->Width();
        CHECK_EQUAL_RETURN(width.has_value(), false, false);
        buttonInfo.iconSize_ = width->GetDimension().ConvertToVp();
        auto fillColor = iconProp->GetImageSourceInfo()->GetFillColor();
        CHECK_EQUAL_RETURN(fillColor.has_value(), false, false);
        buttonInfo.iconColor_.value = fillColor->GetValue();
    }
    return true;
}

bool InitSCTextInfo(OHOS::Security::SecurityComponent::SecCompBase& buttonInfo,
    RefPtr<FrameNode>& textNode)
{
    if (textNode != nullptr) {
        auto textProp = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_RETURN(textProp, false);
        auto pipeline = textNode->GetContextRefPtr();
        CHECK_NULL_RETURN(pipeline, false);
        auto theme = pipeline->GetTheme<SecurityComponentTheme>();
        CHECK_NULL_RETURN(theme, false);
        if (textProp->GetFontSize().has_value()) {
            buttonInfo.fontSize_ = textProp->GetFontSize()->Value();
        } else {
            buttonInfo.fontSize_ = theme->GetFontSize().Value();
        }
        if (textProp->GetTextColor().has_value()) {
            buttonInfo.fontColor_.value = textProp->GetTextColor().value().GetValue();
        }
    }
    return true;
}

bool InitSCButtonInfo(OHOS::Security::SecurityComponent::SecCompBase& buttonInfo,
    RefPtr<FrameNode>& buttonNode)
{
    if (buttonNode != nullptr) {
        const auto& renderContext = buttonNode->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, false);
        if (renderContext->GetBackgroundColor().has_value()) {
            buttonInfo.bgColor_.value = renderContext->GetBackgroundColor().value().GetValue();
        }

        auto bgProp = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_RETURN(bgProp, false);
        const auto& borderWidth = bgProp->GetBorderWidthProperty();
        if (borderWidth != nullptr) {
            if (borderWidth->leftDimen.has_value()) {
                buttonInfo.borderWidth_ = borderWidth->leftDimen.value().ConvertToVp();
            }
        }
    }
    return true;
}

bool SecurityComponentHandler::InitChildInfo(OHOS::Security::SecurityComponent::SecCompBase& buttonInfo,
    RefPtr<FrameNode>& node)
{
    RefPtr<FrameNode> iconNode = GetSecCompChildNode(node, V2::IMAGE_ETS_TAG);
    if (!InitSCIconInfo(buttonInfo, iconNode)) {
        return false;
    }

    RefPtr<FrameNode> symbolIconNode = GetSecCompChildNode(node, V2::SYMBOL_ETS_TAG);
    if (symbolIconNode != nullptr) {
        CHECK_NULL_RETURN(symbolIconNode->GetGeometryNode(), false);
        auto iconProp = symbolIconNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_RETURN(iconProp, false);
    }

    RefPtr<FrameNode> textNode = GetSecCompChildNode(node, V2::TEXT_ETS_TAG);
    if (!InitSCTextInfo(buttonInfo, textNode)) {
        return false;
    }

    RefPtr<FrameNode> buttonNode = GetSecCompChildNode(node, V2::BUTTON_ETS_TAG);
    if (!InitSCButtonInfo(buttonInfo, buttonNode)) {
        return false;
    }

    if (!InitBaseInfo(buttonInfo, node)) {
        return false;
    }
    return true;
}

void SecurityComponentHandler::WriteButtonInfo(
    const RefPtr<OHOS::Ace::NG::SecurityComponentLayoutProperty>& layoutProperty,
    RefPtr<FrameNode>& node, OHOS::Security::SecurityComponent::SecCompBase& buttonInfo,
    std::string& message)
{
    buttonInfo.parentEffect_ = CheckParentNodesEffect(node, buttonInfo, message);
    buttonInfo.text_ = layoutProperty->GetSecurityComponentDescription().value();
    buttonInfo.icon_ = layoutProperty->GetIconStyle().value();
    buttonInfo.bg_ = static_cast<SecCompBackground>(
        layoutProperty->GetBackgroundType().value());

    RectF rect = node->GetTransformRectRelativeToWindow();
    auto maxRadius = std::min(rect.Width(), rect.Height()) / HALF;
    if (layoutProperty->GetBackgroundType() == static_cast<int32_t>(ButtonType::CIRCLE) ||
        layoutProperty->GetBackgroundType() == static_cast<int32_t>(ButtonType::CAPSULE)) {
        buttonInfo.borderRadius_.leftBottom = maxRadius;
        buttonInfo.borderRadius_.leftTop = maxRadius;
        buttonInfo.borderRadius_.rightBottom = maxRadius;
        buttonInfo.borderRadius_.rightTop = maxRadius;
    } else {
        RefPtr<FrameNode> buttonNode = GetSecCompChildNode(node, V2::BUTTON_ETS_TAG);
        CHECK_NULL_VOID(buttonNode);
        auto bgProp = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(bgProp);
        const auto& borderRadius = bgProp->GetBorderRadius();
        if (borderRadius.has_value()) {
            buttonInfo.borderRadius_.leftBottom = borderRadius->radiusBottomLeft.value_or(Dimension(0.0)).ConvertToPx();
            buttonInfo.borderRadius_.leftTop = borderRadius->radiusTopLeft.value_or(Dimension(0.0)).ConvertToPx();
            buttonInfo.borderRadius_.rightBottom =
                borderRadius->radiusBottomRight.value_or(Dimension(0.0)).ConvertToPx();
            buttonInfo.borderRadius_.rightTop = borderRadius->radiusTopRight.value_or(Dimension(0.0)).ConvertToPx();
        }
    }

    if (SystemProperties::GetDeviceType() == DeviceType::WEARABLE) {
        buttonInfo.isWearableDevice_ = true;
    }
}

bool SecurityComponentHandler::InitButtonInfo(std::string& componentInfo, RefPtr<FrameNode>& node, SecCompType& scType,
    std::string& message)
{
    CHECK_NULL_RETURN(node, false);
    auto layoutProperty = AceType::DynamicCast<SecurityComponentLayoutProperty>(node->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);
    std::string type = node->GetTag();
    if (type == V2::LOCATION_BUTTON_ETS_TAG) {
        LocationButton buttonInfo;
        WriteButtonInfo(layoutProperty, node, buttonInfo, message);
        buttonInfo.type_ = SecCompType::LOCATION_COMPONENT;
        scType = SecCompType::LOCATION_COMPONENT;
        if (!InitChildInfo(buttonInfo, node)) {
            return false;
        }
        componentInfo = buttonInfo.ToJsonStr();
    } else if (type == V2::PASTE_BUTTON_ETS_TAG) {
        PasteButton buttonInfo;
        WriteButtonInfo(layoutProperty, node, buttonInfo, message);
        buttonInfo.type_ = SecCompType::PASTE_COMPONENT;
        scType = SecCompType::PASTE_COMPONENT;
        if (!InitChildInfo(buttonInfo, node)) {
            return false;
        }
        componentInfo = buttonInfo.ToJsonStr();
    } else if (type == V2::SAVE_BUTTON_ETS_TAG) {
        SaveButton buttonInfo;
        WriteButtonInfo(layoutProperty, node, buttonInfo, message);
        buttonInfo.type_ = SecCompType::SAVE_COMPONENT;
        scType = SecCompType::SAVE_COMPONENT;
        if (!InitChildInfo(buttonInfo, node)) {
            return false;
        }
        componentInfo = buttonInfo.ToJsonStr();
    } else {
        return false;
    }
    return true;
}

NG::RectF SecurityComponentHandler::UpdateClipRect(NG::RectF& clipRect, NG::RectF& paintRect)
{
    if (clipRect.IsIntersectWith(paintRect)) {
        return clipRect.IntersectRectT(paintRect);
    }

    return NG::RectF(0.0, 0.0, 0.0, 0.0);
}

NG::RectF SecurityComponentHandler::UpdatePaintRect(NG::RectF& paintRect, NG::RectF& clipRect)
{
    if (NearEqual(clipRect.Width(), -1.0) && NearEqual(clipRect.Height(), -1.0)) {
        return paintRect;
    }

    if (paintRect.IsIntersectWith(clipRect)) {
        return paintRect.IntersectRectT(clipRect);
    }

    return NG::RectF(0.0, 0.0, 0.0, 0.0);
}

int32_t SecurityComponentHandler::RegisterSecurityComponent(RefPtr<FrameNode>& node, int32_t& scId)
{
    SecurityComponentHandler::probe.InitProbeTask();
    std::string componentInfo;
    SecCompType type;
    std::string message;
    if (!InitButtonInfo(componentInfo, node, type, message)) {
        return -1;
    }
    int32_t ret = SecCompKit::RegisterSecurityComponent(
        type, componentInfo, scId);
    return ret;
}

int32_t SecurityComponentHandler::UpdateSecurityComponent(RefPtr<FrameNode>& node, int32_t& scId)
{
    std::string componentInfo;
    SecCompType type;
    std::string message;
    if (!InitButtonInfo(componentInfo, node, type, message)) {
        return -1;
    }
    int32_t ret = SecCompKit::UpdateSecurityComponent(scId, componentInfo);
    return ret;
}

int32_t SecurityComponentHandler::UnregisterSecurityComponent(int32_t& scId)
{
    if (scId == -1) {
        return -1;
    }
    int32_t ret = SecCompKit::UnregisterSecurityComponent(scId);
    return ret;
}

bool SecurityComponentHandler::IsContextTransparent(const RefPtr<FrameNode>& frameNode)
{
    const RefPtr<RenderContext> renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    if (renderContext->GetOpacity().has_value() && renderContext->GetOpacity().value() == 0.0) {
        return true;
    }
    if (static_cast<int32_t>(layoutProperty->GetVisibility().value_or(VisibleType::VISIBLE)) != 0) {
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckContainerTags(const RefPtr<FrameNode>& frameNode)
{
    static std::set<std::string> containerComponentTags = { "Flex", "Stack", "Row", "Column", "WindowScene", "root",
        "Swiper", "Grid", "GridItem", "page", "stage", "FormComponent", "Tabs", "TabContent", "ColumnSplit",
        "FolderStack", "GridCol", "GridRow", "RelativeContainer", "RowSplit", "List", "Scroll", "WaterFlow",
        "SideBarContainer", "Refresh", "Navigator", "ListItemGroup", "ListItem", "Hyperlink", "FormLink", "FlowItem",
        "Counter", "Custom", "overlay" };

    const RefPtr<RenderContext> renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    if (containerComponentTags.find(frameNode->GetTag()) != containerComponentTags.end() &&
        renderContext->GetBackgroundColor()->ColorToString().compare("#00000000") == 0) {
        return true;
    }
    return false;
}

bool SecurityComponentHandler::IsInModalPage(const RefPtr<UINode>& node)
{
    RefPtr<UINode> tmpNode = node;
    while (tmpNode) {
        if (tmpNode->GetTag() == V2::MODAL_PAGE_TAG) {
            return true;
        }
        tmpNode = tmpNode->GetParent();
    }
    return false;
}

bool SecurityComponentHandler::CheckSecurityComponentStatus(const RefPtr<UINode>& root, NodeMaps& maps,
    int32_t secNodeId, std::string& message, NG::RectF& clipRect)
{
    bool res = false;
    RectF paintRect;

    auto frameNode = AceType::DynamicCast<NG::FrameNode>(root);
    if (frameNode) {
        paintRect = frameNode->GetTransformRectRelativeToWindow();
        if (IsSecurityComponent(frameNode) && (frameNode->GetId() == secNodeId)) {
            if (IsInModalPage(root)) {
                return false;
            }
            return CheckRectIntersect(paintRect, secNodeId, maps.nodeId2Rect, maps.nodeId2Zindex, message);
        }
    }
    auto& children = root->GetChildren();
    for (auto child = children.rbegin(); child != children.rend(); ++child) {
        auto node = AceType::DynamicCast<NG::FrameNode>(*child);
        if (node && (IsContextTransparent(node) || !node->IsActive())) {
            continue;
        }
        NG::RectF bakClipRect = clipRect;
        if (frameNode && frameNode->GetRenderContext() &&
            frameNode->GetRenderContext()->GetClipEdge().has_value() && frameNode->GetRenderContext()->GetClipEdge()) {
            if (NearEqual(clipRect.Width(), -1.0) && NearEqual(clipRect.Height(), -1.0)) {
                clipRect = paintRect;
            } else {
                clipRect = UpdateClipRect(clipRect, paintRect);
            }
        }
        res |= CheckSecurityComponentStatus(*child, maps, secNodeId, message, clipRect);
        clipRect = bakClipRect;
    }

    if (frameNode && frameNode->GetTag() != V2::SHEET_WRAPPER_TAG && !CheckContainerTags(frameNode)) {
        paintRect = UpdatePaintRect(paintRect, clipRect);
        maps.nodeId2Rect[frameNode->GetId()] = std::make_pair(frameNode->GetTag(), paintRect);
    }
    return res;
}

bool SecurityComponentHandler::CheckRectIntersect(const RectF& dest, int32_t secNodeId,
    const std::unordered_map<int32_t, std::pair<std::string, NG::RectF>>& nodeId2Rect,
    std::unordered_map<int32_t, int32_t>& nodeId2Zindex, std::string& message)
{
    for (const auto& originRect : nodeId2Rect) {
        if (originRect.second.second.IsInnerIntersectWithRound(dest) &&
            (nodeId2Zindex[secNodeId] <= nodeId2Zindex[originRect.first]) &&
            (!NearEqual(originRect.second.second.Width(), 0.0) && !NearEqual(originRect.second.second.Height(), 0.0))) {
            SC_LOG_ERROR("SecurityComponentCheckFail: Security component id = %{public}d " \
                "is covered by id = %{public}d.", secNodeId, originRect.first);
            message = ", security component is covered by component " + originRect.second.first +
                "(id = " + std::to_string(originRect.first) +
                "), the size of security component is (x = " +
                std::to_string(dest.GetX()) +
                ", y = " + std::to_string(dest.GetY()) +
                ", width = " + std::to_string(dest.Width()) +
                ", height = " + std::to_string(dest.Height()) +
                "), the size of the component of covering security component "
                "is (x = " + std::to_string(originRect.second.second.GetX()) +
                ", y = " + std::to_string(originRect.second.second.GetY()) +
                ", width = " + std::to_string(originRect.second.second.Width()) +
                ", height = " + std::to_string(originRect.second.second.Height()) + ")";
            return true;
        }
    }
    return false;
}

bool SecurityComponentHandler::IsSecurityComponent(RefPtr<FrameNode>& node)
{
    return node->GetTag() == V2::LOCATION_BUTTON_ETS_TAG || node->GetTag() == V2::PASTE_BUTTON_ETS_TAG ||
           node->GetTag() == V2::SAVE_BUTTON_ETS_TAG;
}

int32_t SecurityComponentHandler::GetNodeZIndex(const RefPtr<UINode>& root)
{
    int32_t zIndex;
    auto node = AceType::DynamicCast<NG::FrameNode>(root);
    if (node) {
        const RefPtr<RenderContext> renderContext = node->GetRenderContext();
        if (!renderContext) {
            zIndex = 0;
        } else {
            zIndex = renderContext->GetZIndexValue(ZINDEX_DEFAULT_VALUE);
        }
    } else {
        zIndex = 0;
    }

    return zIndex;
}

void SecurityComponentHandler::UpdateAllZindex(const RefPtr<UINode>& root,
    std::unordered_map<int32_t, int32_t>& nodeId2Zindex)
{
    if (nodeId2Zindex.count(root->GetId()) == 0) {
        nodeId2Zindex[root->GetId()] = GetNodeZIndex(root);
    }
    auto& children = root->GetChildren();
    for (auto child = children.begin(); child != children.end(); ++child) {
        int32_t nodeZIndex = GetNodeZIndex(*child);
        nodeId2Zindex[(*child)->GetId()] = std::max(nodeZIndex, nodeId2Zindex[root->GetId()]);
        UpdateAllZindex(*child, nodeId2Zindex);
    }
}

bool SecurityComponentHandler::CheckComponentCoveredStatus(int32_t secNodeId, std::string& message)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, false);
    RefPtr<UINode> root = pipeline->GetRootElement();
    CHECK_NULL_RETURN(root, false);
    NodeMaps maps;
    UpdateAllZindex(root, maps.nodeId2Zindex);
    NG::RectF clipRect = NG::RectF(-1.0, -1.0, -1.0, -1.0);
    if (CheckSecurityComponentStatus(root, maps, secNodeId, message, clipRect)) {
        return true;
    }
    return false;
}

int32_t SecurityComponentHandler::ReportSecurityComponentClickEventInner(int32_t& scId,
    RefPtr<FrameNode>& node, SecCompClickEvent& event,
    Security::SecurityComponent::OnFirstUseDialogCloseFunc&& callback, std::string& message)
{
    std::string componentInfo;
    SecCompType type;
    std::string invalidEffectMsg;
    auto ret = InitButtonInfo(componentInfo, node, type, message);
    if (!message.empty()) {
        invalidEffectMsg = message;
    }
    if (!ret) {
        return -1;
    }
    auto container = AceType::DynamicCast<Platform::AceContainer>(Container::Current());
    CHECK_NULL_RETURN(container, -1);
    sptr<IRemoteObject> token = container->GetToken();
    if (container->GetParentToken() != nullptr) {
        token = container->GetParentToken();
    }
    SecCompInfo secCompInfo{ scId, componentInfo, event };
    int32_t res = SecCompKit::ReportSecurityComponentClickEvent(
        secCompInfo, token, std::move(callback), message);
    if (!message.empty() && message != "PARENT_HAVE_INVALID_EFFECT") {
        message = SEC_COMP_ID + std::to_string(node->GetId()) + SEC_COMP_TYPE + node->GetTag() + message;
    }

    if (res == SC_SERVICE_ERROR_COMPONENT_INFO_INVALID && !message.empty() &&
        message == "PARENT_HAVE_INVALID_EFFECT") {
        message = invalidEffectMsg;
    }
    return res;
}

bool SecurityComponentHandler::CheckSecurityComponentTextLimits(const RefPtr<FrameNode>& node, std::string& message)
{
    auto layoutProperty = AceType::DynamicCast<SecurityComponentLayoutProperty>(node->GetLayoutProperty());
    if (layoutProperty && layoutProperty->GetIsMaxLineLimitExceeded().has_value() &&
        layoutProperty->GetIsMaxLineLimitExceeded().value()) {
        SC_LOG_ERROR("SecurityComponentCheckFail: The text of the security component is cliped by lines.");
        message = SEC_COMP_ID + std::to_string(node->GetId()) + SEC_COMP_TYPE +
            node->GetTag() + ", the text of the security component is cliped by lines";
        return true;
    }
    if (layoutProperty && layoutProperty->GetIsTextLimitExceeded().has_value() &&
        layoutProperty->GetIsTextLimitExceeded().value()) {
        SC_LOG_ERROR("SecurityComponentCheckFail: The text of the security component is out of range.");
        message = SEC_COMP_ID + std::to_string(node->GetId()) + SEC_COMP_TYPE +
            node->GetTag() + ", the text of the security component is out of range";
        return true;
    }
    return false;
}

int32_t SecurityComponentHandler::ReportSecurityComponentClickEvent(int32_t& scId,
    RefPtr<FrameNode>& node, GestureEvent& event,
    Security::SecurityComponent::OnFirstUseDialogCloseFunc&& callback,
    std::string& message)
{
    SecCompClickEvent secEvent;
    secEvent.type = ClickEventType::POINT_EVENT_TYPE;
#ifdef SECURITY_COMPONENT_ENABLE
    secEvent.point.touchX = event.GetDisplayX();
    secEvent.point.touchY = event.GetDisplayY();
    auto pointerEvent = event.GetPointerEvent();
    uint8_t defaultData = 0;
    std::vector<uint8_t> dataBuffer;
    if (pointerEvent == nullptr) {
        SC_LOG_WARN("SecurityComponentClickEventWarning: Receive a NULL pointerEvent, set default data.");
        secEvent.extraInfo.data = &defaultData;
        secEvent.extraInfo.dataSize = 1;
        secEvent.point.timestamp = 0;
    } else {
        dataBuffer = pointerEvent->GetEnhanceData();
        if (dataBuffer.size() > 0) {
            secEvent.extraInfo.data = dataBuffer.data();
            secEvent.extraInfo.dataSize = dataBuffer.size();
        }
        std::chrono::microseconds microseconds(pointerEvent->GetActionTime());
        TimeStamp time(microseconds);
        secEvent.point.timestamp =
            static_cast<uint64_t>(time.time_since_epoch().count()) / SECOND_TO_MILLISECOND;
    }
#endif
    if (CheckSecurityComponentTextLimits(node, message)) {
        return -1;
    }
    if (CheckComponentCoveredStatus(node->GetId(), message)) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Security component is covered by another component.");
        message = SEC_COMP_ID + std::to_string(node->GetId()) + SEC_COMP_TYPE + node->GetTag() + message;
        return -1;
    }

    return ReportSecurityComponentClickEventInner(scId, node, secEvent, std::move(callback), message);
}

int32_t SecurityComponentHandler::ReportSecurityComponentClickEvent(int32_t& scId,
    RefPtr<FrameNode>& node, const KeyEvent& event,
    Security::SecurityComponent::OnFirstUseDialogCloseFunc&& callback)
{
    SecCompClickEvent secEvent;
    secEvent.type = ClickEventType::KEY_EVENT_TYPE;

    secEvent.key.timestamp =
        static_cast<uint64_t>(event.timeStamp.time_since_epoch().count()) / SECOND_TO_MILLISECOND;
    secEvent.key.keyCode = static_cast<int32_t>(event.code);
    auto data = event.enhanceData;
    if (data.size() > 0) {
        secEvent.extraInfo.data = data.data();
        secEvent.extraInfo.dataSize = data.size();
    }
    auto layoutProperty = AceType::DynamicCast<SecurityComponentLayoutProperty>(node->GetLayoutProperty());
    if (layoutProperty && layoutProperty->GetIsMaxLineLimitExceeded().has_value() &&
        layoutProperty->GetIsMaxLineLimitExceeded().value()) {
        SC_LOG_ERROR("SecurityComponentCheckFail: The text of the security component is cliped by lines.");
        return -1;
    }
    if (layoutProperty && layoutProperty->GetIsTextLimitExceeded().has_value() &&
        layoutProperty->GetIsTextLimitExceeded().value()) {
        SC_LOG_ERROR("SecurityComponentCheckFail: The text of the security component is out of range.");
        return -1;
    }
    std::string message;
    if (CheckComponentCoveredStatus(node->GetId(), message)) {
        SC_LOG_ERROR("SecurityComponentCheckFail: Security component is covered by another component.");
        return -1;
    }
    return ReportSecurityComponentClickEventInner(scId, node, secEvent, std::move(callback), message);
}

bool SecurityComponentHandler::IsSecurityComponentServiceExist()
{
    return SecCompKit::IsServiceExist();
}

bool SecurityComponentHandler::LoadSecurityComponentService()
{
    return SecCompKit::LoadService();
}

bool SecurityComponentHandler::IsSystemAppCalling()
{
    return SecCompKit::IsSystemAppCalling();
}
} // namespace OHOS::Ace::NG
