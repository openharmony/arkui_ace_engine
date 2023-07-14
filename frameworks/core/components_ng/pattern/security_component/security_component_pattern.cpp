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

#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "base/log/ace_scoring_log.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/security_component/security_component_handler.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components/common/layout/constants.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
bool SecurityComponentPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty,
    const DirtySwapConfig& config)
{
    return !(config.skipMeasure || dirty->SkipMeasureContent());
}

void SecurityComponentPattern::SetNodeHitTestMode(RefPtr<FrameNode>& node, HitTestMode mode)
{
    if (node == nullptr) {
        return;
    }
    auto gestureHub = node->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetHitTestMode(mode);
}

void SecurityComponentPattern::InitSecurityComponentOnClick(RefPtr<FrameNode>& secCompNode, RefPtr<FrameNode>& icon,
    RefPtr<FrameNode>& text, RefPtr<FrameNode>& button)
{
    if (clickListener_ != nullptr) {
        return;
    }
    auto secCompGesture = secCompNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(secCompGesture);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto buttonPattern = weak.Upgrade();
        CHECK_NULL_VOID(buttonPattern);
        auto frameNode = buttonPattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        int32_t res = SecurityComponentHandler::ReportSecurityComponentClickEvent(buttonPattern->scId_,
            frameNode, info);
        if (res != 0) {
            LOGE("ReportSecurityComponentClickEvent failed, errno %{public}d", res);
        }
#ifdef SECURITY_COMPONENT_ENABLE
        auto jsonNode = JsonUtil::Create(true);
        jsonNode->Put("handleRes", res);
        std::shared_ptr<JsonValue> jsonShrd(jsonNode.release());
        info.SetSecCompHandleEvent(jsonShrd);
#endif
    };

    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    secCompGesture->AddClickEvent(clickListener_);
    SetNodeHitTestMode(icon, HitTestMode::HTMTRANSPARENT);
    SetNodeHitTestMode(text, HitTestMode::HTMTRANSPARENT);
}

#ifdef SECURITY_COMPONENT_ENABLE
void SecurityComponentPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    auto node = GetHost();
    CHECK_NULL_VOID(node);

    auto layoutProperty = AceType::DynamicCast<SecurityComponentLayoutProperty>(node->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    json->Put("text", layoutProperty->GetSecurityComponentDescription().value());
    json->Put("icon", layoutProperty->GetIconStyle().value());
    json->Put("background", layoutProperty->GetBackgroundType().value());
    json->Put("type", node->GetTag().c_str());

    RefPtr<FrameNode> iconNode = GetSecCompChildNode(node, V2::IMAGE_ETS_TAG);
    if (iconNode != nullptr) {
        json->Put("iconSize", static_cast<double>(
            SystemProperties::Px2Vp(iconNode->GetGeometryNode()->GetFrameSize().Width())));
        auto iconProp = iconNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(iconProp);
        json->Put("iconColor", static_cast<int64_t>(
            iconProp->GetImageSourceInfo().value().GetFillColor().value().GetValue()));
    }
    RefPtr<FrameNode> textNode = GetSecCompChildNode(node, V2::TEXT_ETS_TAG);
    if (textNode != nullptr) {
        auto textProp = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textProp);
        json->Put("fontSize", textProp->GetFontSize().value().ConvertToVp());
        json->Put("fontColor", static_cast<int64_t>(textProp->GetTextColor().value().GetValue()));
    }

    RefPtr<FrameNode> buttonNode = GetSecCompChildNode(node, V2::BUTTON_ETS_TAG);
    if (buttonNode != nullptr) {
        const auto& renderContext = buttonNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        json->Put("bgColor", static_cast<int64_t>(renderContext->GetBackgroundColor().value().GetValue()));
        auto bgProp = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(bgProp);
        const auto& borderWidth = bgProp->GetBorderWidthProperty();
        if (borderWidth != nullptr) {
            json->Put("borderWidth", borderWidth->leftDimen.value().ConvertToVp());
        }
    }
    json->Put("nodeId", node->GetId());
    json->Put("paddingTop", layoutProperty->GetBackgroundTopPadding().value().ConvertToVp());
    json->Put("paddingRight", layoutProperty->GetBackgroundRightPadding().value().ConvertToVp());
    json->Put("paddingBottom", layoutProperty->GetBackgroundBottomPadding().value().ConvertToVp());
    json->Put("paddingLeft", layoutProperty->GetBackgroundLeftPadding().value().ConvertToVp());
    json->Put("textIconSpace", layoutProperty->GetTextIconSpace().value().ConvertToVp());
    ToJsonValueRect(json);
}

void SecurityComponentPattern::ToJsonValueRect(std::unique_ptr<JsonValue>& json) const
{
    auto node = GetHost();
    CHECK_NULL_VOID(node);
    double offsetX;
    double offsetY;
    SecurityComponentHandler::GetDisplayOffset(node, offsetX, offsetY);
    json->Put("rectX", offsetX);
    json->Put("rectY", offsetY);
    OHOS::Security::SecurityComponent::SecCompRect winRect;
    SecurityComponentHandler::GetWindowRect(node, winRect);
    json->Put("winRectX", winRect.x_);
    json->Put("winRectY", winRect.y_);
    json->Put("winRectWidth", winRect.width_);
    json->Put("winRectHeight", winRect.height_);
    auto render = node->GetRenderContext();
    CHECK_NULL_VOID(render);
    auto rect = render->GetPaintRectWithTransform();
    json->Put("rectWidth", rect.Width());
    json->Put("rectHeight", rect.Height());
}
#endif

void SecurityComponentPattern::OnModifyDone()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);

    RefPtr<FrameNode> iconNode = GetSecCompChildNode(frameNode, V2::IMAGE_ETS_TAG);
    if (iconNode != nullptr) {
        iconNode->MarkModifyDone();
    }

    RefPtr<FrameNode> textNode = GetSecCompChildNode(frameNode, V2::TEXT_ETS_TAG);
    if (textNode != nullptr) {
        textNode->MarkModifyDone();
    }

    RefPtr<FrameNode> buttonNode = GetSecCompChildNode(frameNode, V2::BUTTON_ETS_TAG);
    if (buttonNode != nullptr) {
        buttonNode->MarkModifyDone();
    }

    InitSecurityComponentOnClick(frameNode, iconNode, textNode, buttonNode);
    InitSecurityComponentAppearCallback(frameNode);
    RegisterOrUpdateSecurityComponent(frameNode, scId_);
}

void SecurityComponentPattern::RegisterOrUpdateSecurityComponent(RefPtr<FrameNode>& frameNode, int32_t& scId)
{
    if (scId == -1) {
        SecurityComponentHandler::RegisterSecurityComponent(frameNode, scId);
    } else {
        SecurityComponentHandler::UpdateSecurityComponent(frameNode, scId);
    }
}

void SecurityComponentPattern::InitSecurityComponentAppearCallback(RefPtr<FrameNode>& frameNode)
{
    if (isAppearCallback_) {
        return;
    }
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);

    auto onAppear = [weak = WeakClaim(this)]() {
        auto securityComponentPattern = weak.Upgrade();
        CHECK_NULL_VOID(securityComponentPattern);
        auto frameNode = securityComponentPattern->GetHost();
        securityComponentPattern->RegisterOrUpdateSecurityComponent(frameNode,
            securityComponentPattern->scId_);
    };

    auto onDisAppear = [weak = WeakClaim(this)]() {
        auto securityComponentPattern = weak.Upgrade();
        CHECK_NULL_VOID(securityComponentPattern);
        SecurityComponentHandler::UnregisterSecurityComponent(securityComponentPattern->scId_);
    };
    eventHub->SetOnAppear(std::move(onAppear));
    eventHub->SetOnDisappear(std::move(onDisAppear));
    isAppearCallback_ = true;
}
} // namespace OHOS::Ace::NG
