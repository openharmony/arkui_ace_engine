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

#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/drawing_decoration_painter.h"
#include "core/components/theme/blur_style_theme.h"
namespace OHOS::Ace::NG {

namespace ROSEN_RENDER_MULTI_THREAD {
ColorMode GetResourceColorMode(PipelineContext* pipeline)
{
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, ColorMode::LIGHT);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, ColorMode::LIGHT);
    auto resourceAdapter = themeConstants->GetResourceAdapter();
    CHECK_NULL_RETURN(resourceAdapter, ColorMode::LIGHT);
    return resourceAdapter->GetResourceColorMode();
}


std::shared_ptr<Rosen::RSFilter> CreateRSMaterialFilter(
    const BlurStyleOption& blurStyleOption, PipelineContext* pipeline, const SysOptions& sysOptions)
{
    auto blurStyleTheme = pipeline->GetTheme<BlurStyleTheme>();
    if (!blurStyleTheme) {
        LOGW("cannot find theme of blurStyle, create blurStyle failed");
        return nullptr;
    }
    ThemeColorMode colorMode = blurStyleOption.colorMode;
    if (blurStyleOption.colorMode == ThemeColorMode::SYSTEM) {
        colorMode = GetResourceColorMode(pipeline) == ColorMode::DARK ?
            ThemeColorMode::DARK : ThemeColorMode::LIGHT;
    }
    auto blurParam = blurStyleTheme->GetBlurParameter(blurStyleOption.blurStyle, colorMode);
    CHECK_NULL_RETURN(blurParam, nullptr);
    auto ratio = blurStyleOption.scale;
    auto maskColor = blurParam->maskColor.BlendOpacity(ratio);
    auto radiusPx = blurParam->radius * pipeline->GetDipScale();
    auto radiusBlur = DrawingDecorationPainter::ConvertRadiusToSigma(radiusPx) * ratio;
    auto saturation = (blurParam->saturation - 1) * ratio + 1.0;
    auto brightness = (blurParam->brightness - 1) * ratio + 1.0;
    return Rosen::RSFilter::CreateMaterialFilter(radiusBlur, saturation, brightness, maskColor.GetValue(),
        static_cast<Rosen::BLUR_COLOR_MODE>(blurStyleOption.adaptiveColor), sysOptions.disableSystemAdaptation);
}
};

void RosenRenderContext::NotifyHostTransformUpdatedMultiThread(bool changed)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakPtr<FrameNode>(host), changed]() {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        node->NotifyTransformInfoChanged();
        node->OnNodeTransformInfoUpdate(changed);
        node->UpdateAccessibilityNodeRect();
    });
}

void RosenRenderContext::SetFrontBlurFilterMultiThread()
{
    auto node = GetHost();
    CHECK_NULL_VOID(node);
    auto task = [weakNode = WeakPtr<FrameNode>(node), rsNode = std::weak_ptr<Rosen::RSNode>(rsNode_),
        weak = WeakClaim(this) ]() {
        auto host = weak.Upgrade();
        CHECK_NULL_VOID(host);
        auto rsNodeUp = rsNode.lock();
        CHECK_NULL_VOID(rsNodeUp);
        auto node = weakNode.Upgrade();
        CHECK_NULL_VOID(node);
        auto context = node->GetContextWithCheck();
        CHECK_NULL_VOID(context);
        const auto& foreground = host->GetForeground();
        CHECK_NULL_VOID(foreground);
        const auto& blurStyleOption = foreground->propBlurStyleOption;
        auto sysOptions = foreground->propSysOptionsForBlur.value_or(SysOptions());
        std::shared_ptr<Rosen::RSFilter> frontFilter;
        if (!blurStyleOption.has_value()) {
            const auto& radius = foreground->propBlurRadius;
            if (radius.has_value() && radius->IsValid()) {
                float radiusPx = context->NormalizeToPx(radius.value());
                float backblurRadius = DrawingDecorationPainter::ConvertRadiusToSigma(radiusPx);
                frontFilter = Rosen::RSFilter::CreateBlurFilter(backblurRadius, backblurRadius,
                    sysOptions.disableSystemAdaptation);
            }
        } else {
            frontFilter = ROSEN_RENDER_MULTI_THREAD::CreateRSMaterialFilter(blurStyleOption.value(),
                context, sysOptions);
        }
        rsNodeUp->SetFilter(frontFilter);
    };
    node->PostAfterAttachMainTreeTask(task);
}

void RosenRenderContext::SetPositionToRSNodeMultiThread()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(rsNode_);
    auto rect = AdjustPaintRect();
    if (!rect.GetSize().IsPositive()) {
        return;
    }
    paintRect_ = rect;
    if (frameNode->ParentExpansive() && !frameNode->SelfExpansive()) {
        // Dynamically modify position, need consider parent expand
        frameNode->AdjustNotExpandNode();
        rect = paintRect_;
    }
    rsNode_->SetBounds(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
    if (useContentRectForRSFrame_) {
        SetContentRectToFrame(rect);
    } else {
        rsNode_->SetFrame(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
    }
    if (frameOffset_.has_value()) {
        rsNode_->SetFrame(
            rect.GetX() + frameOffset_->GetX(), rect.GetY() + frameOffset_->GetY(), rect.Width(), rect.Height());
    }
    frameNode->PostAfterAttachMainTreeTask([weak = WeakPtr<FrameNode>(frameNode), rect]() {
        auto host = weak.Upgrade();
        host->OnSyncGeometryFrameFinish(rect);
        ElementRegister::GetInstance()->ReSyncGeometryTransition(host);
    });
}

void RosenRenderContext::AnimateHoverEffectScaleMultiThread(bool isHovered)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakClaim(this), isHovered]() {
        auto renderContext = weak.Upgrade();
        CHECK_NULL_VOID(renderContext);
        renderContext->AnimateHoverEffectScale(isHovered);
    });
}

void RosenRenderContext::AnimateHoverEffectBoardMultiThread(bool isHovered)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakClaim(this), isHovered]() {
        auto renderContext = weak.Upgrade();
        CHECK_NULL_VOID(renderContext);
        renderContext->AnimateHoverEffectBoard(isHovered);
    });
}

void RosenRenderContext::OnZIndexUpdateMultiThread(const RefPtr<FrameNode>& parent)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto weak = WeakClaim(AceType::RawPtr(parent));
    auto task = [weak]() {
        auto parent = weak.Upgrade();
        CHECK_NULL_VOID(parent);
        parent->RebuildRenderContextTree();
    };
    host->PostAfterAttachMainTreeTask([weak, taskCallback = std::move(task)]() {
        auto parent = weak.Upgrade();
        CHECK_NULL_VOID(parent);
        auto pipeline = parent->GetContext();
        CHECK_NULL_VOID(pipeline);
        if (pipeline->IsLayouting()) {
            pipeline->AddAfterLayoutTask(std::move(taskCallback));
            return;
        }
        taskCallback();
    });
}

void RosenRenderContext::UpdateBackBlurStyleMultiThreadInner(
    const std::optional<BlurStyleOption>& bgBlurStyle, const SysOptions& sysOptions)
{
    CHECK_NULL_VOID(rsNode_);
    if (!UpdateBlurBackgroundColor(bgBlurStyle)) {
        rsNode_->SetBackgroundFilter(nullptr);
        return;
    }
    SetBackBlurFilter();
}

void RosenRenderContext::UpdateBackBlurStyleMultiThread(
    const std::optional<BlurStyleOption>& bgBlurStyle, const SysOptions& sysOptions)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& groupProperty = GetOrCreateBackground();
    if (groupProperty->CheckBlurStyleOption(bgBlurStyle) && groupProperty->CheckSystemAdaptationSame(sysOptions)) {
        // Same with previous value.
        // If colorMode is following system and has valid blurStyle, still needs updating
        if (bgBlurStyle->colorMode != ThemeColorMode::SYSTEM) {
            return;
        }
        if (bgBlurStyle->blurOption.grayscale.size() > 1) {
            Rosen::Vector2f grayScale(bgBlurStyle->blurOption.grayscale[0], bgBlurStyle->blurOption.grayscale[1]);
            host->PostAfterAttachMainTreeTask([this, grayScale]() {
                CHECK_NULL_VOID(rsNode_);
                rsNode_->SetGreyCoef(grayScale);
            });
        }
    } else {
        groupProperty->propBlurStyleOption = bgBlurStyle;
        groupProperty->propSysOptions = sysOptions;
    }
    host->PostAfterAttachMainTreeTask([this, bgBlurStyle, sysOptions]() {
        UpdateBackBlurStyleMultiThreadInner(bgBlurStyle, sysOptions);
    });
}

void RosenRenderContext::UpdateBackgroundEffectMultiThreadInner(
    const std::optional<EffectOption>& effectOption, const SysOptions& sysOptions)
{
    CHECK_NULL_VOID(rsNode_);
    if (!UpdateBlurBackgroundColor(effectOption)) {
        rsNode_->SetBackgroundFilter(nullptr);
        return;
    }
    auto context = GetPipelineContext();
    CHECK_NULL_VOID(context);
    float radiusPx = context->NormalizeToPx(effectOption->radius);
    float backblurRadius = DrawingDecorationPainter::ConvertRadiusToSigma(radiusPx);
    auto fastAverage = Rosen::BLUR_COLOR_MODE::DEFAULT;
    if (effectOption->adaptiveColor == AdaptiveColor::AVERAGE) {
        fastAverage = Rosen::BLUR_COLOR_MODE::FASTAVERAGE;
    }
    std::shared_ptr<Rosen::RSFilter> backFilter =
        Rosen::RSFilter::CreateMaterialFilter(backblurRadius, static_cast<float>(effectOption->saturation),
            static_cast<float>(effectOption->brightness), effectOption->color.GetValue(),
            static_cast<Rosen::BLUR_COLOR_MODE>(fastAverage), sysOptions.disableSystemAdaptation);
    rsNode_->SetBackgroundFilter(backFilter);
    if (effectOption->blurOption.grayscale.size() > 1) {
        Rosen::Vector2f grayScale(effectOption->blurOption.grayscale[0], effectOption->blurOption.grayscale[1]);
        rsNode_->SetGreyCoef(grayScale);
    }
}

void RosenRenderContext::UpdateBackgroundEffectMultiThread(
    const std::optional<EffectOption>& effectOption, const SysOptions& sysOptions)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& groupProperty = GetOrCreateBackground();
    if (groupProperty->CheckEffectOption(effectOption) && groupProperty->CheckSystemAdaptationSame(sysOptions)) {
        return;
    }
    groupProperty->propEffectOption = effectOption;
    groupProperty->propSysOptions = sysOptions;
    if (!effectOption.has_value()) {
        return;
    }
    host->PostAfterAttachMainTreeTask([this, effectOption, sysOptions]() {
        UpdateBackgroundEffectMultiThreadInner(effectOption, sysOptions);
    });
}

void RosenRenderContext::UpdateForeBlurStyleForColorModeMultiThread(const std::optional<BlurStyleOption>& fgBlurStyle,
    const SysOptions& sysOptions)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern();
    CHECK_NULL_VOID(pattern);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto&& updateFunc = [weak = AceType::WeakClaim(this), fgBlurStyle, sysOptions](
                            const RefPtr<ResourceObject>& resObj) {
        auto render = weak.Upgrade();
        CHECK_NULL_VOID(render);
        const auto& groupProperty = render->GetOrCreateForeground();
        if (groupProperty->CheckBlurStyleOption(fgBlurStyle) && groupProperty->CheckSysOptionsForBlurSame(sysOptions)) {
            // Same with previous value.
            // If colorMode is following system and has valid blurStyle, still needs updating
            if (fgBlurStyle->colorMode != ThemeColorMode::SYSTEM) {
                return;
            }
            if (fgBlurStyle->blurOption.grayscale.size() > 1) {
                auto host = render->GetHost();
                CHECK_NULL_VOID(host);
                Rosen::Vector2f grayScale(fgBlurStyle->blurOption.grayscale[0], fgBlurStyle->blurOption.grayscale[1]);
                host->PostAfterAttachMainTreeTask([weak, grayScale]() {
                    auto render = weak.Upgrade();
                    CHECK_NULL_VOID(render);
                    CHECK_NULL_VOID(render->rsNode_);
                    render->rsNode_->SetGreyCoef(grayScale);
                });
            }
        } else {
            groupProperty->propBlurStyleOption = fgBlurStyle;
            groupProperty->propSysOptionsForBlur = sysOptions;
        }
        auto host = render->GetHost();
        CHECK_NULL_VOID(host);
        host->PostAfterAttachMainTreeTask([weak]() {
            auto render = weak.Upgrade();
            CHECK_NULL_VOID(render);
            render->SetFrontBlurFilter();
        });
    };
    updateFunc(resObj);
    pattern->AddResObj("foregroundBlurStyle.blurStyle", resObj, std::move(updateFunc));
}

void RosenRenderContext::UpdateFrontBlurStyleMultiThread(
    const std::optional<BlurStyleOption>& fgBlurStyle, const SysOptions& sysOptions)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& groupProperty = GetOrCreateForeground();
    if (groupProperty->CheckBlurStyleOption(fgBlurStyle) && groupProperty->CheckSysOptionsForBlurSame(sysOptions)) {
        // Same with previous value.
        // If colorMode is following system and has valid blurStyle, still needs updating
        if (fgBlurStyle->colorMode != ThemeColorMode::SYSTEM) {
            return;
        }
        if (fgBlurStyle->blurOption.grayscale.size() > 1) {
            Rosen::Vector2f grayScale(fgBlurStyle->blurOption.grayscale[0], fgBlurStyle->blurOption.grayscale[1]);
            host->PostAfterAttachMainTreeTask([this, grayScale]() {
                CHECK_NULL_VOID(rsNode_);
                rsNode_->SetGreyCoef(grayScale);
            });
        }
    } else {
        groupProperty->propBlurStyleOption = fgBlurStyle;
        groupProperty->propSysOptionsForBlur = sysOptions;
    }
    host->PostAfterAttachMainTreeTask([this, fgBlurStyle, sysOptions]() {
        CHECK_NULL_VOID(rsNode_);
        if (SystemProperties::ConfigChangePerform()) {
            UpdateForeBlurStyleForColorMode(fgBlurStyle, sysOptions);
        }
        SetFrontBlurFilter();
    });
}

void RosenRenderContext::ResetBackBlurStyleMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& groupProperty = GetOrCreateBackground();
    groupProperty->propBlurStyleOption.reset();
    host->PostAfterAttachMainTreeTask([this]() {
        SetBackBlurFilter();
    });
}

void RosenRenderContext::SetHostNodeMultiThread(const WeakPtr<FrameNode>& host)
{
    RenderContext::SetHostNode(host);
    auto hostNode = GetHost();
    CHECK_NULL_VOID(hostNode);
    hostNode->PostAfterAttachMainTreeTask([this, host]() {
        AddFrameNodeInfoToRsNode();
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        frameNode->AddExtraCustomProperty("RS_NODE", rsNode_.get());
    });
}

void RosenRenderContext::SetNeedCallbackAreaChangeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakPtr<FrameNode>(host)]() {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        auto pipeline = node->GetContextRefPtr();
        CHECK_NULL_VOID(pipeline);
        pipeline->SetNeedCallbackAreaChange(true);
    });
}

void RosenRenderContext::SetRSUIContextMultiThread(PipelineContext* context)
{
    CHECK_NULL_VOID(context);
    auto window = context->GetWindow();
    CHECK_NULL_VOID(window);
    auto rsUIDirector = window->GetRSUIDirector();
    CHECK_NULL_VOID(rsUIDirector);
    auto rsUIContext = rsUIDirector->GetRSUIContext();
    CHECK_NULL_VOID(rsUIContext);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([this, weak = std::weak_ptr<Rosen::RSUIContext>(rsUIContext)]() {
        auto rsUIContextPtr = weak.lock();
        CHECK_NULL_VOID(rsUIContextPtr);
        auto rsNode = GetRSNode();
        CHECK_NULL_VOID(rsNode);
        rsNode->SetRSUIContext(rsUIContextPtr);
    });
}

void RosenRenderContext::UpdateBackBlurRadiusMultiThread(const Dimension& radius)
{
    const auto& groupProperty = GetOrCreateBackground();
    if (groupProperty->CheckBlurRadiusChanged(radius)) {
        // Same with previous value
        return;
    }
    groupProperty->propBlurRadius = radius;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([this]() {
        SetBackBlurFilter();
    });
}

void RosenRenderContext::UpdateMotionBlurMultiThread(const MotionBlurOption& motionBlurOption)
{
    const auto& groupProperty = GetOrCreateForeground();
    groupProperty->propMotionBlur = motionBlurOption;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([this, motionBlurOption]() {
        CHECK_NULL_VOID(rsNode_);
        Rosen::Vector2f anchor(motionBlurOption.anchor.x, motionBlurOption.anchor.y);
        rsNode_->SetMotionBlurPara(motionBlurOption.radius, anchor);
    });
}

void RosenRenderContext::UpdateBackBlurMultiThread(
    const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions)
{
    const auto& groupProperty = GetOrCreateBackground();
    if (groupProperty->CheckBlurRadiusChanged(radius) && groupProperty->CheckSystemAdaptationSame(sysOptions)) {
        // Same with previous value
        return;
    }
    groupProperty->propBlurRadius = radius;
    groupProperty->propSysOptions = sysOptions;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([this, blurOption]() {
        CHECK_NULL_VOID(rsNode_);
        SetBackBlurFilter();
        if (blurOption.grayscale.size() > 1) {
            Rosen::Vector2f grayScale(blurOption.grayscale[0], blurOption.grayscale[0]);
            rsNode_->SetGreyCoef(grayScale);
        }
    });
}

void RosenRenderContext::UpdateNodeBackBlurMultiThread(const Dimension& radius, const BlurOption& blurOption)
{
    const auto& groupProperty = GetOrCreateBackground();
    groupProperty->propBackdropBlurOption = blurOption;
    if (groupProperty->CheckBlurRadiusChanged(radius) && groupProperty->CheckBlurOptionChanged(blurOption)) {
        // Same with previous value
        return;
    }
    groupProperty->propBlurRadius = radius;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([this, blurOption]() {
        CHECK_NULL_VOID(rsNode_);
        SetBackBlurFilter();
        if (blurOption.grayscale.size() > 1) {
            Rosen::Vector2f grayScale(blurOption.grayscale[0], blurOption.grayscale[1]);
            rsNode_->SetGreyCoef(grayScale);
        }
    });
}

void RosenRenderContext::UpdateFrontBlurRadiusMultiThread(const Dimension& radius)
{
    const auto& groupProperty = GetOrCreateForeground();
    if (groupProperty->CheckBlurRadiusChanged(radius)) {
        // Same with previous value
        return;
    }
    groupProperty->propBlurRadius = radius;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([this]() {
        SetFrontBlurFilter();
    });
}

void RosenRenderContext::UpdateFrontBlurMultiThread(
    const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions)
{
    const auto& groupProperty = GetOrCreateForeground();
    if (groupProperty->CheckBlurRadiusChanged(radius) && groupProperty->CheckSysOptionsForBlurSame(sysOptions)) {
        // Same with previous value
        return;
    }
    groupProperty->propBlurRadius = radius;
    groupProperty->propSysOptionsForBlur = sysOptions;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([this, blurOption]() {
        CHECK_NULL_VOID(rsNode_);
        SetFrontBlurFilter();
        if (blurOption.grayscale.size() > 1) {
            Rosen::Vector2f grayScale(blurOption.grayscale[0], blurOption.grayscale[1]);
            rsNode_->SetGreyCoef(grayScale);
        }
    });
}
}