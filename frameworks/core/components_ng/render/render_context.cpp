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

#include "core/components_ng/render/render_context.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
std::string RenderFitToString(RenderFit renderFit)
{
    static const std::string RenderFitStyles[] = { "RenderFit.CENTER", "RenderFit.TOP", "RenderFit.BOTTOM",
        "RenderFit.LEFT", "RenderFit.RIGHT", "RenderFit.TOP_LEFT", "RenderFit.TOP_RIGHT", "RenderFit.BOTTOM_LEFT",
        "RenderFit.BOTTOM_RIGHT", "RenderFit.RESIZE_FILL", "RenderFit.RESIZE_CONTAIN",
        "RenderFit.RESIZE_CONTAIN_TOP_LEFT", "RenderFit.RESIZE_CONTAIN_BOTTOM_RIGHT", "RenderFit.RESIZE_COVER",
        "RenderFit.RESIZE_COVER_TOP_LEFT", "RenderFit.RESIZE_COVER_BOTTOM_RIGHT" };
    return RenderFitStyles[static_cast<int>(renderFit)];
}

std::string UseEffectTypeToString(EffectType effectType)
{
    static const std::string UseEffectTypeStyles[] = { "EffectType.DEFAULT", "EffectType.WINDOW_EFFECT" };
    return UseEffectTypeStyles[static_cast<int>(effectType)];
}

} // namespace

void RenderContext::SetRequestFrame(const std::function<void()>& requestFrame)
{
    requestFrame_ = requestFrame;
}

void RenderContext::RequestNextFrame() const
{
    if (requestFrame_) {
        requestFrame_();
        auto node = GetHost();
        CHECK_NULL_VOID(node);
        if (node->GetInspectorId().has_value()) {
            auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
            CHECK_NULL_VOID(pipeline);
            pipeline->SetNeedRenderNode(WeakPtr<FrameNode>(node));
        }
    }
}

void RenderContext::SetHostNode(const WeakPtr<FrameNode>& host)
{
    host_ = host;
}

RefPtr<FrameNode> RenderContext::GetHost() const
{
    return host_.Upgrade();
}

FrameNode* RenderContext::GetUnsafeHost() const
{
    return UnsafeRawPtr(host_);
}

void RenderContext::SetSharedTransitionOptions(const std::shared_ptr<SharedTransitionOption>& option)
{
    sharedTransitionOption_ = option;
}

const std::shared_ptr<SharedTransitionOption>& RenderContext::GetSharedTransitionOption() const
{
    return sharedTransitionOption_;
}

void RenderContext::SetShareId(const ShareId& shareId)
{
    shareId_ = shareId;
}

const ShareId& RenderContext::GetShareId() const
{
    return shareId_;
}

bool RenderContext::HasSharedTransition() const
{
    return !shareId_.empty();
}

bool RenderContext::HasSharedTransitionOption() const
{
    return sharedTransitionOption_ != nullptr;
}

void RenderContext::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    ACE_PROPERTY_TO_JSON_VALUE(propBorder_, BorderProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propOuterBorder_, OuterBorderProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propPointLight_, PointLightProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propBdImage_, BorderImageProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propOverlay_, OverlayProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propPositionProperty_, RenderPositionProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propBackground_, BackgroundProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propForeground_, ForegroundProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propGraphics_, GraphicsProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propGradient_, GradientProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propTransform_, TransformProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propClip_, ClipProperty);
    ACE_PROPERTY_TO_JSON_VALUE(GetBackBlurStyle(), BlurStyleOption);
    ACE_PROPERTY_TO_JSON_VALUE(GetBackgroundEffect(), EffectOption);
    if (filter.IsFastFilter()) {
        ObscuredToJsonValue(json, filter);
        return;
    }
    if (propTransformMatrix_.has_value()) {
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("type", "matrix");
        auto matrixString = propTransformMatrix_->ToString();
        while (matrixString.find("\n") != std::string::npos) {
            auto num = matrixString.find("\n");
            matrixString.replace(num, 1, "");
        }
        jsonValue->Put("matrix", matrixString.c_str());
        json->PutExtAttr("transform", jsonValue, filter);
    } else {
        json->PutExtAttr("transform", JsonUtil::Create(true), filter);
    }
    json->PutExtAttr("backgroundColor",
        propBackgroundColor_.value_or(Color::TRANSPARENT).ColorToString().c_str(), filter);
    json->PutExtAttr("zIndex", propZIndex_.value_or(0), filter);
    json->PutExtAttr("opacity", propOpacity_.value_or(1), filter);
    if (propProgressMask_.has_value() && propProgressMask_.value()) {
        json->PutExtAttr("total", propProgressMask_.value()->GetMaxValue(), filter);
        json->PutExtAttr("updateProgress", propProgressMask_.value()->GetValue(), filter);
        json->PutExtAttr("updateColor", propProgressMask_.value()->GetColor().ColorToString().c_str(), filter);
        json->PutExtAttr("enableBreathe", propProgressMask_.value()->GetEnableBreathe(), filter);
    }
    json->PutExtAttr("lightUpEffect", propLightUpEffect_.value_or(0.0), filter);
    json->PutExtAttr("sphericalEffect", propSphericalEffect_.value_or(0.0), filter);
    auto pixStretchEffectOption = propPixelStretchEffect_.value_or(PixStretchEffectOption());
    auto pixelJsonValue = JsonUtil::Create(true);
    pixelJsonValue->Put("left", pixStretchEffectOption.left.ToString().c_str());
    pixelJsonValue->Put("right", pixStretchEffectOption.right.ToString().c_str());
    pixelJsonValue->Put("top", pixStretchEffectOption.top.ToString().c_str());
    pixelJsonValue->Put("bottom", pixStretchEffectOption.bottom.ToString().c_str());
    json->PutExtAttr("pixelStretchEffect", pixelJsonValue, filter);
    json->PutExtAttr("foregroundColor",
        propForegroundColor_.value_or(Color::FOREGROUND).ColorToString().c_str(), filter);
    if (propClickEffectLevel_.has_value()) {
        auto clickEffectJsonValue = JsonUtil::Create(true);
        clickEffectJsonValue->Put("level", std::to_string((int)propClickEffectLevel_.value().level).c_str());
        clickEffectJsonValue->Put("scale",
            std::to_string((float)propClickEffectLevel_.value().scaleNumber).c_str());
        json->PutExtAttr("clickEffect", clickEffectJsonValue, filter);
    }
    ObscuredToJsonValue(json, filter);
    json->PutExtAttr("renderGroup", propRenderGroup_.value_or(false) ? "true" : "false", filter);
    json->PutExtAttr("renderFit", RenderFitToString(propRenderFit_.value_or(RenderFit::TOP_LEFT)).c_str(), filter);
    json->PutExtAttr("useShadowBatching", propUseShadowBatching_.value_or(false) ? "true" : "false", filter);
    json->PutExtAttr("useEffect", propUseEffect_.value_or(false) ? "true" : "false", filter);
    json->PutExtAttr("useEffectType",
        UseEffectTypeToString(propUseEffectType_.value_or(EffectType::DEFAULT)).c_str(), filter);
}

void RenderContext::ObscuredToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto jsonObscuredArray = JsonUtil::CreateArray(true);
    std::vector<ObscuredReasons> obscuredReasons = propObscured_.value_or(std::vector<ObscuredReasons>());
    for (size_t i = 0; i < obscuredReasons.size(); i++) {
        auto index = std::to_string(i);
        auto value = std::to_string(static_cast<int32_t>(obscuredReasons[i]));
        jsonObscuredArray->Put(index.c_str(), value.c_str());
    }
    json->PutExtAttr("obscured", jsonObscuredArray, filter);
}

void RenderContext::FromJson(const std::unique_ptr<JsonValue>& json)
{
    auto borderRadius = json->GetValue("borderRadius");
    BorderRadiusProperty brp;
    brp.radiusTopLeft = Dimension::FromString(borderRadius->GetString("topLeft"));
    brp.radiusTopRight = Dimension::FromString(borderRadius->GetString("topRight"));
    brp.radiusBottomLeft = Dimension::FromString(borderRadius->GetString("bottomLeft"));
    brp.radiusBottomRight = Dimension::FromString(borderRadius->GetString("bottomRight"));
    UpdateBorderRadius(brp);
    UpdateBackgroundColor(Color::ColorFromString(json->GetString("backgroundColor")));
    auto clip = json->GetString("clip");
    if (clip == "true" || clip == "false") {
        UpdateClipEdge(clip == "true" ? true : false);
    } else {
        LOGE("UITree |ERROR| invalid clip=%{public}s", clip.c_str());
    }
}
} // namespace OHOS::Ace::NG
