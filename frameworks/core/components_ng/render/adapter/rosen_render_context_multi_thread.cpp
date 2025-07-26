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
}