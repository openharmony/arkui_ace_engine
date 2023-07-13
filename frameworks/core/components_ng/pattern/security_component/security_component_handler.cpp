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

#include <securec.h>

#include "base/log/ace_scoring_log.h"
#include "base/utils/system_properties.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
#ifdef SECURITY_COMPONENT_ENABLE
using namespace OHOS::Security;
using namespace OHOS::Security::SecurityComponent;
namespace {
constexpr uint64_t SECOND_TO_MILLISECOND = 1000;
}

static std::vector<uintptr_t> g_callList = {
    reinterpret_cast<uintptr_t>(SecurityComponentHandler::RegisterSecurityComponent),
    reinterpret_cast<uintptr_t>(SecurityComponentHandler::UpdateSecurityComponent),
    reinterpret_cast<uintptr_t>(SecurityComponentHandler::ReportSecurityComponentClickEvent)
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

bool SecurityComponentHandler::CheckOpacity(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext)
{
    if (renderContext->GetOpacity().has_value() &&
        !NearEqual(renderContext->GetOpacity().value(), 1.0f)) {
        LOGW("Parent %{public}s opacity is set, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckBrightness(const RefPtr<FrameNode>& node,
    const RefPtr<RenderContext>& renderContext)
{
    if (renderContext->GetFrontBrightness().has_value() &&
        !NearEqual(renderContext->GetFrontBrightness().value().ConvertToVp(), 1.0f)) {
        LOGW("Parent %{public}s brightness is set, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckVisibility(const RefPtr<FrameNode>& node, RefPtr<LayoutProperty>& layoutProperty)
{
    if (layoutProperty->GetVisibility().has_value() &&
        (layoutProperty->GetVisibility().value() != VisibleType::VISIBLE)) {
        LOGW("Parent %{public}s is not visible, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckBlur(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext)
{
    if (renderContext->GetFrontBlurRadius().has_value() &&
        GreatNotEqual(renderContext->GetFrontBlurRadius().value().ConvertToPx(), 0.0f)) {
        LOGW("Parent %{public}s is blur, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckGrayScale(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext)
{
    if (renderContext->GetFrontGrayScale().has_value() &&
        GreatNotEqual(renderContext->GetFrontGrayScale().value().ConvertToVp(), 0.0f)) {
        LOGW("Parent %{public}s set gray scale, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckSaturate(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext)
{
    if (renderContext->GetFrontSaturate().has_value() &&
        !NearEqual(renderContext->GetFrontSaturate().value().ConvertToVp(), 1.0f)) {
        LOGW("Parent %{public}s set saturate, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckContrast(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext)
{
    if (renderContext->GetFrontContrast().has_value() &&
        !NearEqual(renderContext->GetFrontContrast().value().ConvertToVp(), 1.0f)) {
        LOGW("Parent %{public}s set contrast, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckInvert(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext)
{
    if (renderContext->GetFrontInvert().has_value() &&
        !NearEqual(renderContext->GetFrontInvert().value().ConvertToVp(), 0.0f)) {
        LOGW("Parent %{public}s set Invert, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckSepia(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext)
{
    if (renderContext->GetFrontSepia().has_value() &&
        !NearEqual(renderContext->GetFrontSepia().value().ConvertToVp(), 0.0f)) {
        LOGW("Parent %{public}s set sepia, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckHueRotate(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext)
{
    if (renderContext->GetFrontHueRotate().has_value() &&
        !NearEqual(renderContext->GetFrontHueRotate().value(), 0.0f) &&
        !NearEqual(renderContext->GetFrontHueRotate().value(), 360.0f)) {
        LOGW("Parent %{public}s set HueRotate, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckColorBlend(const RefPtr<FrameNode>& node,
    const RefPtr<RenderContext>& renderContext)
{
    if (renderContext->GetFrontColorBlend().has_value() &&
        (renderContext->GetFrontColorBlend().value() != Color::TRANSPARENT)) {
        LOGW("Parent %{public}s set color blend, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckClipMask(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext)
{
    if (renderContext->GetClipMask().has_value()) {
        LOGW("Parent %{public}s set clip mask, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckForegroundColor(const RefPtr<FrameNode>& node,
    const RefPtr<RenderContext>& renderContext)
{
    if (renderContext->GetForegroundColor().has_value() &&
        (renderContext->GetForegroundColor().value() != Color::TRANSPARENT)) {
        LOGW("Parent %{public}s set foreground color, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckSphericalEffect(const RefPtr<FrameNode>& node,
    const RefPtr<RenderContext>& renderContext)
{
    if (renderContext->GetSphericalEffect().has_value() &&
        !NearEqual(renderContext->GetSphericalEffect().value(), 0.0f)) {
        LOGW("Parent %{public}s set SphericalEffect, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckLightUpEffect(const RefPtr<FrameNode>& node,
    const RefPtr<RenderContext>& renderContext)
{
    if (renderContext->GetLightUpEffect().has_value()) {
        LOGW("Parent %{public}s set light up effect, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckPixelStretchEffect(const RefPtr<FrameNode>& node,
    const RefPtr<RenderContext>& renderContext)
{
    if (renderContext->GetPixelStretchEffect().has_value()) {
        LOGW("Parent %{public}s set PixelStretchEffect, security component is invalid", node->GetTag().c_str());
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckRenderEffect(RefPtr<FrameNode>& node)
{
    const auto& renderContext = node->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto layoutProperty = node->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);

    if (CheckOpacity(node, renderContext) || CheckBrightness(node, renderContext) ||
        CheckVisibility(node, layoutProperty) || CheckBlur(node, renderContext) ||
        CheckGrayScale(node, renderContext) || CheckSaturate(node, renderContext) ||
        CheckContrast(node, renderContext) || CheckInvert(node, renderContext) ||
        CheckSepia(node, renderContext) || CheckHueRotate(node, renderContext) ||
        CheckColorBlend(node, renderContext) || CheckClipMask(node, renderContext) ||
        CheckForegroundColor(node, renderContext) || CheckSphericalEffect(node, renderContext)||
        CheckLightUpEffect(node, renderContext) || CheckPixelStretchEffect(node, renderContext)) {
        return true;
    }
    return false;
}

bool SecurityComponentHandler::CheckParentNodesEffect(RefPtr<FrameNode>& node)
{
    RefPtr<RenderContext> renderContext = node->GetRenderContext();
    auto frameRect = renderContext->GetPaintRectWithTransform();
    frameRect.SetOffset(node->GetOffsetRelativeToWindow());
    auto visibleRect = frameRect;
    auto parent = node->GetParent();
    while (parent != nullptr) {
        auto parentNode = AceType::DynamicCast<FrameNode>(parent);
        if (parentNode == nullptr) {
            return false;
        }
        if (CheckRenderEffect(parentNode)) {
            return true;
        }
        RefPtr<RenderContext> parentRenderContext = parentNode->GetRenderContext();
        if (!parentRenderContext->GetClipEdge().value_or(false)) {
            parent = parent->GetParent();
            continue;
        }
        GetVisibleRect(parentNode, visibleRect);
        double currentVisibleRatio = CalculateCurrentVisibleRatio(visibleRect, frameRect);
        if (!NearEqual(currentVisibleRatio, 1)) {
            LOGW("security component is not completely displayed.");
            LOGW("visibleWidth: %{public}f, visibleHeight: %{public}f, frameWidth: %{public}f, frameHeight: %{public}f",
                visibleRect.Width(), visibleRect.Height(), frameRect.Width(), frameRect.Height());
            return true;
        }
        parent = parent->GetParent();
    }
    return false;
}

void SecurityComponentHandler::GetVisibleRect(RefPtr<FrameNode>& node, RectF& visibleRect)
{
    auto parentFrame = AceType::DynamicCast<FrameNode>(node);
    if (!parentFrame) {
        LOGW("Parent %{public}s get frame failed", node->GetTag().c_str());
        return;
    }
    RectF parentRect = parentFrame->GetRenderContext()->GetPaintRectWithTransform();
    parentRect.SetOffset(parentFrame->GetOffsetRelativeToWindow());
    visibleRect = visibleRect.Constrain(parentRect);
}

double SecurityComponentHandler::CalculateCurrentVisibleRatio(const RectF& visibleRect, const RectF& renderRect)
{
    if (!visibleRect.IsValid() || !renderRect.IsValid()) {
        return 0.0;
    }
    return visibleRect.Width() * visibleRect.Height() / (renderRect.Width() * renderRect.Height());
}

bool SecurityComponentHandler::InitBaseInfo(OHOS::Security::SecurityComponent::SecCompBase& buttonInfo,
    RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto layoutProperty = AceType::DynamicCast<SecurityComponentLayoutProperty>(node->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);
    buttonInfo.nodeId_ = node->GetId();
    buttonInfo.padding_.top = layoutProperty->GetBackgroundTopPadding().value().ConvertToVp();
    buttonInfo.padding_.right = layoutProperty->GetBackgroundRightPadding().value().ConvertToVp();
    buttonInfo.padding_.bottom = layoutProperty->GetBackgroundBottomPadding().value().ConvertToVp();
    buttonInfo.padding_.left = layoutProperty->GetBackgroundLeftPadding().value().ConvertToVp();
    buttonInfo.textIconSpace_ = layoutProperty->GetTextIconSpace().value().ConvertToVp();

    if (!GetDisplayOffset(node, buttonInfo.rect_.x_, buttonInfo.rect_.y_)) {
        LOGW("Get display offset failed");
        return false;
    }

    if (!GetWindowRect(node, buttonInfo.windowRect_)) {
        LOGW("Get window rect failed");
        return false;
    }
    auto render = node->GetRenderContext();
    CHECK_NULL_RETURN(render, false);
    auto rect = render->GetPaintRectWithTransform();
    buttonInfo.rect_.width_ = rect.Width();
    buttonInfo.rect_.height_ = rect.Height();

    return true;
}

bool SecurityComponentHandler::InitChildInfo(OHOS::Security::SecurityComponent::SecCompBase& buttonInfo,
    RefPtr<FrameNode>& node)
{
    RefPtr<FrameNode> iconNode = GetSecCompChildNode(node, V2::IMAGE_ETS_TAG);
    if (iconNode != nullptr) {
        CHECK_NULL_RETURN(iconNode->GetGeometryNode(), false);
        buttonInfo.iconSize_ = SystemProperties::Px2Vp(iconNode->GetGeometryNode()->GetFrameSize().Width());
        auto iconProp = iconNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_RETURN(iconProp, false);
        buttonInfo.iconColor_.value =
            iconProp->GetImageSourceInfo().value().GetFillColor().value().GetValue();
    }

    RefPtr<FrameNode> textNode = GetSecCompChildNode(node, V2::TEXT_ETS_TAG);
    if (textNode != nullptr) {
        auto textProp = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_RETURN(textProp, false);
        buttonInfo.fontSize_ = textProp->GetFontSize().value().ConvertToVp();
        buttonInfo.fontColor_.value = textProp->GetTextColor().value().GetValue();
    }

    RefPtr<FrameNode> buttonNode = GetSecCompChildNode(node, V2::BUTTON_ETS_TAG);
    if (buttonNode != nullptr) {
        const auto& renderContext = buttonNode->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, false);
        buttonInfo.bgColor_.value = renderContext->GetBackgroundColor().value().GetValue();

        auto bgProp = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_RETURN(bgProp, false);
        const auto& borderWidth = bgProp->GetBorderWidthProperty();
        if (borderWidth != nullptr) {
            buttonInfo.borderWidth_ = borderWidth->leftDimen.value().ConvertToVp();
        }
    }
    if (!InitBaseInfo(buttonInfo, node)) {
        return false;
    }
    return true;
}

bool SecurityComponentHandler::InitButtonInfo(std::string& componentInfo, RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto layoutProperty = AceType::DynamicCast<SecurityComponentLayoutProperty>(node->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);
    std::string type = node->GetTag();
    if (type == V2::LOCATION_BUTTON_ETS_TAG) {
        LocationButton buttonInfo;
        buttonInfo.parentEffect_ = CheckParentNodesEffect(node);
        buttonInfo.text_ = layoutProperty->GetSecurityComponentDescription().value();
        buttonInfo.icon_ = layoutProperty->GetIconStyle().value();
        buttonInfo.bg_ = static_cast<SecCompBackground>(
            layoutProperty->GetBackgroundType().value());
        buttonInfo.type_ = SecCompType::LOCATION_COMPONENT;
        if (!InitChildInfo(buttonInfo, node)) {
            return false;
        }
        componentInfo = buttonInfo.ToJsonStr();
    } else if (type == V2::PASTE_BUTTON_ETS_TAG) {
        PasteButton buttonInfo;
        buttonInfo.parentEffect_ = CheckParentNodesEffect(node);
        buttonInfo.text_ = layoutProperty->GetSecurityComponentDescription().value();
        buttonInfo.icon_ = layoutProperty->GetIconStyle().value();
        buttonInfo.bg_ = static_cast<SecCompBackground>(
            layoutProperty->GetBackgroundType().value());
        buttonInfo.type_ = SecCompType::PASTE_COMPONENT;
        if (!InitChildInfo(buttonInfo, node)) {
            return false;
        }
        componentInfo = buttonInfo.ToJsonStr();
    } else if (type == V2::SAVE_BUTTON_ETS_TAG) {
        SaveButton buttonInfo;
        buttonInfo.parentEffect_ = CheckParentNodesEffect(node);
        buttonInfo.text_ = layoutProperty->GetSecurityComponentDescription().value();
        buttonInfo.icon_ = layoutProperty->GetIconStyle().value();
        buttonInfo.bg_ = static_cast<SecCompBackground>(
            layoutProperty->GetBackgroundType().value());
        buttonInfo.type_ = SecCompType::SAVE_COMPONENT;
        if (!InitChildInfo(buttonInfo, node)) {
            return false;
        }
        componentInfo = buttonInfo.ToJsonStr();
    } else {
        return false;
    }
    return true;
}

int32_t SecurityComponentHandler::RegisterSecurityComponent(RefPtr<FrameNode>& node, int32_t& scId)
{
    SecurityComponentHandler::probe.InitProbeTask();
    std::string componentInfo;
    if (!InitButtonInfo(componentInfo, node)) {
        return -1;
    }
    int32_t ret = SecCompKit::RegisterSecurityComponent(
        SecCompType::LOCATION_COMPONENT, componentInfo, scId);
    return ret;
}

int32_t SecurityComponentHandler::UpdateSecurityComponent(RefPtr<FrameNode>& node, int32_t scId)
{
    std::string componentInfo;
    if (!InitButtonInfo(componentInfo, node)) {
        return -1;
    }
    int32_t ret = SecCompKit::UpdateSecurityComponent(scId, componentInfo);
    return ret;
}

int32_t SecurityComponentHandler::UnregisterSecurityComponent(int32_t scId)
{
    if (scId == -1) {
        return -1;
    }
    int32_t ret = SecCompKit::UnregisterSecurityComponent(scId);
    return ret;
}

int32_t SecurityComponentHandler::ReportSecurityComponentClickEvent(int32_t scId,
    RefPtr<FrameNode>& node, GestureEvent& event)
{
    if (scId == -1) {
        return -1;
    }
    std::string componentInfo;
    if (!InitButtonInfo(componentInfo, node)) {
        return -1;
    }
    SecCompClickEvent secEvent;
    secEvent.touchX = event.GetDisplayX();
    secEvent.touchY = event.GetDisplayY();
    secEvent.timestamp = static_cast<uint64_t>(event.GetTimeStamp().time_since_epoch().count()) / SECOND_TO_MILLISECOND;
    auto data = event.GetEnhanceData();
    if (data.size() > 0) {
        secEvent.extraInfo.data = data.data();
        secEvent.extraInfo.dataSize = data.size();
    }
    return SecCompKit::ReportSecurityComponentClickEvent(scId, componentInfo, secEvent);
}
#else
int32_t SecurityComponentHandler::RegisterSecurityComponent(RefPtr<FrameNode>& node, int32_t& scId)
{
    return 0;
}

int32_t SecurityComponentHandler::UpdateSecurityComponent(RefPtr<FrameNode>& node, int32_t scId)
{
    return 0;
}

int32_t SecurityComponentHandler::UnregisterSecurityComponent(int32_t scId)
{
    return 0;
}

int32_t SecurityComponentHandler::ReportSecurityComponentClickEvent(int32_t scId,
    RefPtr<FrameNode>& node, GestureEvent& event)
{
    return 0;
}
#endif
} // namespace OHOS::Ace::NG
