/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/select_overlay/magnifier_controller.h"

#include "core/components/common/properties/color.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/select_overlay/magnifier.h"
#include "core/components_ng/pattern/select_overlay/magnifier_pattern.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void MagnifierController::UpdateShowMagnifier(bool isShowMagnifier)
{
    isShowMagnifier_ = isShowMagnifier;
    if (isShowMagnifier_) {
        OpenMagnifier();
    } else {
        CloseMagnifier();
    }
}

bool MagnifierController::UpdateMagnifierOffsetX(OffsetF& magnifierPaintOffset, VectorF& magnifierOffset,
    const OffsetF& basePaintOffset)
{
    float left = basePaintOffset.GetX() + localOffset_.GetX() - magnifierNodeWidth_.ConvertToPx() / 2;
    auto rootUINode = GetRootNode();
    CHECK_NULL_RETURN(rootUINode, false);
    auto rootGeometryNode = rootUINode->GetGeometryNode();
    CHECK_NULL_RETURN(rootGeometryNode, false);
    auto rootFrameSize = rootGeometryNode->GetFrameSize();
    auto magnifierX =
        std::clamp(left, 0.f, static_cast<float>(rootFrameSize.Width() - magnifierNodeWidth_.ConvertToPx()));
    magnifierPaintOffset.SetX(magnifierX);
    magnifierOffset.x = MAGNIFIER_OFFSETX.ConvertToPx();
    return true;
}

bool MagnifierController::UpdateMagnifierOffsetY(OffsetF& magnifierPaintOffset, VectorF& magnifierOffset,
    const OffsetF& basePaintOffset)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    float menuHeight = magnifierNodeHeight_.ConvertToPx();
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    auto keyboardInsert = safeAreaManager->GetKeyboardInset();
    auto hasKeyboard = GreatNotEqual(keyboardInsert.Length(), 0.0f);
    auto magnifierY = basePaintOffset.GetY() + localOffset_.GetY() - menuHeight / 2;
    float offsetY_ = 0.f;

    if (hasKeyboard && basePaintOffset.GetY() + localOffset_.GetY() >= keyboardInsert.start) {
        UpdateShowMagnifier();
        return false;
    }
    auto screenHeight = SystemProperties::GetDeviceHeight();
    magnifierY = std::clamp(magnifierY, 0.f, static_cast<float>(screenHeight - menuHeight));
    auto rootUINode = GetRootNode();
    CHECK_NULL_RETURN(rootUINode, false);
    auto rootGeometryNode = rootUINode->GetGeometryNode();
    CHECK_NULL_RETURN(rootGeometryNode, false);
    auto rootFrameSize = rootGeometryNode->GetFrameSize();
    offsetY_ = std::clamp(magnifierY, 0.f, static_cast<float>(MAGNIFIER_OFFSETY.ConvertToPx()));
    auto magnifierPaintOffsetY = magnifierY - offsetY_;
    magnifierPaintOffsetY =
        std::clamp(magnifierPaintOffsetY, 0.f, static_cast<float>(rootFrameSize.Height() - menuHeight));
    magnifierPaintOffset.SetY(magnifierPaintOffsetY);
    magnifierOffset.y = offsetY_;
    return true;
}

bool MagnifierController::UpdateMagnifierOffset()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textBasePattern = DynamicCast<TextBase>(pattern);
    CHECK_NULL_RETURN(textBasePattern, false);
    auto childContext = magnifierFrameNode_->GetRenderContext();
    CHECK_NULL_RETURN(childContext, false);
    auto paintOffset = textBasePattern->GetTextPaintOffset();
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    Color colorhost = ViewAbstract::GetBackgroundColor(AceType::RawPtr(host));
    Color colorMagnifier = colorhost.ChangeAlpha(0);
    ViewAbstract::SetBackgroundColor(AceType::RawPtr(magnifierFrameNode_), colorMagnifier);
    OffsetF magnifierPaintOffset;
    VectorF magnifierOffset(0.f, 0.f);
    if (!IsLocalOffsetInHostRange(host)) {
        UpdateShowMagnifier(false);
        return false;
    }
    CHECK_NULL_RETURN(UpdateMagnifierOffsetX(magnifierPaintOffset, magnifierOffset, paintOffset), false);
    CHECK_NULL_RETURN(UpdateMagnifierOffsetY(magnifierPaintOffset, magnifierOffset, paintOffset), false);
    auto geometryNode = magnifierFrameNode_->GetGeometryNode();
    if (localOffsetChanged_ && NearEqual(params_.offsetX_, magnifierOffset.x) &&
        NearEqual(params_.offsetY_, magnifierOffset.y)) {
        // change x one pixel so magnifier can refresh
        magnifierPaintOffset.SetX(magnifierPaintOffset.GetX() - 1.0f);
        magnifierOffset.x += 1.0f;
    }
    geometryNode->SetFrameOffset(magnifierPaintOffset);
    childContext->UpdatePosition(
        OffsetT<Dimension>(Dimension(magnifierPaintOffset.GetX()), Dimension(magnifierPaintOffset.GetY())));
    childContext->SetContentRectToFrame(RectF(magnifierPaintOffset.GetX(), magnifierPaintOffset.GetY(), 0.0f, 0.0f));
    params_.offsetX_ = magnifierOffset.x;
    params_.offsetY_ = magnifierOffset.y;
    params_.factor_ = MAGNIFIER_FACTOR;
    params_.changed_ = !params_.changed_;
    ViewAbstract::SetMagnifier(AceType::RawPtr(magnifierFrameNode_), params_);
    magnifierFrameNode_->ForceSyncGeometryNode();
    magnifierFrameNode_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool MagnifierController::IsLocalOffsetInHostRange(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_RETURN(host, false);
    auto localOffset = localOffsetWithoutTrans_.value_or(localOffset_);
    auto viewPort = GetViewPort(host);
    viewPort.SetOffset({ 0, 0 });
    return viewPort.IsInRegion(PointF{ localOffset.GetX(), localOffset.GetY() });
}

void MagnifierController::OpenMagnifier()
{
    auto rootUINode = GetRootNode();
    CHECK_NULL_VOID(rootUINode);
    if ((!magnifierFrameNode_) || (rootUINode->GetChildIndexById(magnifierFrameNode_->GetId()) == -1) ||
        (colorModeChange_)) {
        colorModeChange_ = false;
        CreateMagnifierChildNode();
    }
    CHECK_NULL_VOID(magnifierFrameNode_);
    if (rootUINode->GetChildIndexById(magnifierFrameNode_->GetId()) == -1) {
        magnifierFrameNode_->MountToParent(rootUINode);
    }
    CHECK_NULL_VOID(UpdateMagnifierOffset());
    ChangeMagnifierVisibility(true);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textBase = DynamicCast<TextBase>(pattern);
    CHECK_NULL_VOID(textBase);
    textBase->SetIsTextDraggable(false);
}

RefPtr<FrameNode> MagnifierController::GetRootNode()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto rootNode = pipeline->GetRootElement();
    CHECK_NULL_RETURN(rootNode, nullptr);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, rootNode);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, rootNode);
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        auto root = FindWindowScene(host);
        rootNode = DynamicCast<FrameNode>(root);
    }
    return rootNode;
}

RefPtr<UINode> MagnifierController::FindWindowScene(const RefPtr<FrameNode>& targetNode)
{
    CHECK_NULL_RETURN(targetNode, nullptr);
    auto parent = targetNode->GetParent();
    while (parent && parent->GetTag() != V2::WINDOW_SCENE_ETS_TAG) {
        parent = parent->GetParent();
    }
    CHECK_NULL_RETURN(parent, nullptr);
    return parent;
}

void MagnifierController::ChangeMagnifierVisibility(const bool& visible)
{
    CHECK_NULL_VOID(visible_ != visible);
    visible_ = visible;
    double lastOpacity = visible ? 1.0 : 0.0;
    auto callBack = [weak = WeakClaim(this), lastOpacity]() {
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        auto hostNode = controller->GetMagnifierNode();
        CHECK_NULL_VOID(hostNode);
        ViewAbstract::SetOpacity(AceType::RawPtr(hostNode), lastOpacity);
        hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };
    auto parms = params_;
    parms.factor_ = 0.f;
    auto endCallBack = [weak = WeakClaim(this), parms]() {
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        auto hostNode = controller->GetMagnifierNode();
        CHECK_NULL_VOID(hostNode);
        ViewAbstract::SetMagnifier(AceType::RawPtr(hostNode), parms);
        auto parentNode = hostNode->GetParent();
        CHECK_NULL_VOID(parentNode);
        parentNode->RemoveChild(hostNode);
        parentNode->MarkNeedSyncRenderTree();
        parentNode->RebuildRenderContextTree();
    };
    AnimationOption option;
    option.SetCurve(Curves::FRICTION);
    option.SetDuration(ANIMATION_DURATION_150);
    if (removeFrameNode_) {
        AnimationUtils::Animate(option, callBack, endCallBack);
    } else {
        AnimationUtils::Animate(option, callBack);
    }
}

void MagnifierController::RemoveMagnifierFrameNode()
{
    magnifierNodeExist_ = false;
    if (isShowMagnifier_) {
        removeFrameNode_ = true;
        UpdateShowMagnifier();
    } else {
        CHECK_NULL_VOID(magnifierFrameNode_);
        auto parentNode = magnifierFrameNode_->GetParent();
        CHECK_NULL_VOID(parentNode);
        parentNode->RemoveChild(magnifierFrameNode_);
        parentNode->MarkNeedSyncRenderTree();
        parentNode->RebuildRenderContextTree();
    }
    removeFrameNode_ = false;
    hostViewPort_.reset();
}

void MagnifierController::CloseMagnifier()
{
    CHECK_NULL_VOID(magnifierFrameNode_);
    ViewAbstract::ReSetMagnifier(AceType::RawPtr(magnifierFrameNode_));
    ChangeMagnifierVisibility(false);
    magnifierFrameNode_->ForceSyncGeometryNode();
    magnifierFrameNode_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void MagnifierController::InitMagnifierParams()
{
    params_.factor_ = MAGNIFIER_FACTOR;
    params_.width_ = MAGNIFIER_WIDTH.ConvertToPx();
    params_.height_ = MAGNIFIER_HEIGHT.ConvertToPx();
    params_.borderWidth_ = MAGNIFIER_BORDERWIDTH.ConvertToPx();
    params_.cornerRadius_ = MAGNIFIER_CORNERRADIUS.ConvertToPx();
    params_.shadowOffsetX_ = MAGNIFIER_SHADOWOFFSETX.ConvertToPx();
    params_.shadowOffsetY_ = MAGNIFIER_SHADOWOFFSETY.ConvertToPx();
    params_.shadowSize_ = MAGNIFIER_SHADOWSIZE.ConvertToPx();
    params_.shadowStrength_ = MAGNIFIER_SHADOWSTRENGTH;

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    uint32_t gradientMaskColor1 = textFieldTheme->GetGlassMaskPrimaryColor().GetValue();
    uint32_t gradientMaskColor2 = textFieldTheme->GetGlassMaskSecondaryColor().GetValue();

    Color outlineColor1 = textFieldTheme->GetGlassOutlinePrimaryColor();
    Color outlineColor2 = textFieldTheme->GetGlassOutlineSecondaryColor();
    if (SystemProperties::GetColorMode() == ColorMode::DARK) {
        outlineColor1 = outlineColor1.ChangeAlpha(0xCC); // 0xCC: 80%
        outlineColor2 = outlineColor2.ChangeAlpha(0xCC); // 0xCC: 80%
    } else {
        outlineColor1 = outlineColor1.ChangeAlpha(0x7F); // 0x7F: 50%
        outlineColor2 = outlineColor2.ChangeAlpha(0x7F); // 0x7F: 50%
    }
    uint32_t outerContourColor1 = outlineColor1.GetValue();
    uint32_t outerContourColor2 = outlineColor2.GetValue();
    params_.gradientMaskColor1_ = ArgbToRgba(gradientMaskColor1);
    params_.gradientMaskColor2_ = ArgbToRgba(gradientMaskColor2);
    params_.outerContourColor1_ = ArgbToRgba(outerContourColor1);
    params_.outerContourColor2_ = ArgbToRgba(outerContourColor2);
    magnifierNodeWidth_ =
        MAGNIFIER_WIDTH + MAGNIFIER_SHADOWOFFSETX + MAGNIFIER_SHADOWSIZE * 1.5; // 1.5: Compute the node width
    magnifierNodeHeight_ =
        MAGNIFIER_HEIGHT + MAGNIFIER_SHADOWOFFSETY + MAGNIFIER_SHADOWSIZE * 1.5; // 1.5: Compute the node height
}

uint32_t MagnifierController::ArgbToRgba(const uint32_t& color)
{
    uint8_t a = (color >> 24) & 0xff; // 24: get alpha
    uint8_t r = (color >> 16) & 0xff; // 16: get red
    uint8_t g = (color >> 8) & 0xff; // 8: get green
    uint8_t b = color & 0xff; // get blue
    return (r << 24) | (g << 16) | (b << 8) | a; // 24: red, 16: green, 8: blue
}

void MagnifierController::CreateMagnifierChildNode()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textBasePattern = DynamicCast<TextBase>(pattern);
    CHECK_NULL_VOID(textBasePattern);

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ACE_SCOPED_TRACE("Create[%s][self:%d]", V2::TEXTINPUT_ETS_TAG, nodeId);
    auto childNode = FrameNode::GetOrCreateFrameNode(V2::MAGNIFIER_TAG, nodeId,
        [weak = WeakClaim(Referenced::RawPtr(textBasePattern))]() {
            auto textBase = weak.Upgrade();
            return AceType::MakeRefPtr<MagnifierPattern>(textBase);
        });
    CHECK_NULL_VOID(childNode);
    InitMagnifierParams();
    ViewAbstract::SetWidth(AceType::RawPtr(childNode), CalcLength(magnifierNodeWidth_));
    ViewAbstract::SetHeight(AceType::RawPtr(childNode), CalcLength(magnifierNodeHeight_));
    ViewAbstract::SetOpacity(AceType::RawPtr(childNode), 0.0);
    auto layoutProperty = AceType::DynamicCast<LayoutProperty>(childNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    childNode->ForceSyncGeometryNode();
    childNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    magnifierFrameNode_ = childNode;
    visible_ = false;
}

RectF MagnifierController::GetViewPort(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_RETURN(host, RectF());
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, RectF());
    auto frameRect = geometryNode->GetFrameRect();
    if (!hostViewPort_.has_value()) {
        return frameRect;
    }
    frameRect.SetWidth(std::max(frameRect.Width(), hostViewPort_->Width()));
    frameRect.SetHeight(std::max(frameRect.Height(), hostViewPort_->Height()));
    return frameRect;
}
} // namespace OHOS::Ace::NG
