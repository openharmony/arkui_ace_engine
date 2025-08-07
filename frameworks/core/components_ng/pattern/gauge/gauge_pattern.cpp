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
#include "core/components_ng/pattern/gauge/gauge_pattern.h"

#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/gauge/gauge_layout_algorithm.h"
#include "core/components_ng/pattern/gauge/gauge_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
bool GaugePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool /*skipLayout*/)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    return true;
}

void GaugePattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    FireBuilder();
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetPositionProperty()) {
        layoutProperty->UpdateAlignment(
            layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER));
    } else {
        layoutProperty->UpdateAlignment(Alignment::CENTER);
    }

    if (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        InitTitleContent();
        auto gaugePaintProperty = GetPaintProperty<GaugePaintProperty>();
        CHECK_NULL_VOID(gaugePaintProperty);
        if (gaugePaintProperty->GetIsShowIndicatorValue(false) && gaugePaintProperty->HasIndicatorIconSourceInfo()) {
            InitIndicatorImage();
        }

        auto gaugeLayoutProperty = GetLayoutProperty<GaugeLayoutProperty>();
        CHECK_NULL_VOID(gaugeLayoutProperty);

        if (gaugeLayoutProperty->GetIsShowLimitValueValue(false) && gaugePaintProperty->HasGradientColors() &&
            gaugePaintProperty->GetGradientColorsValue().size() != 0) {
            InitLimitValueText(GetMinValueTextId(), true);
            InitLimitValueText(GetMaxValueTextId(), false);
        } else {
            if (minValueTextId_.has_value()) {
                HideLimitValueText(GetMinValueTextId(), true);
            }
            if (maxValueTextId_.has_value()) {
                HideLimitValueText(GetMaxValueTextId(), false);
            }
        }
        if (gaugeLayoutProperty->GetIsShowDescriptionValue(false)) {
            InitDescriptionNode();
        }
    }
}

void GaugePattern::FireBuilder()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!makeFunc_.has_value()) {
        host->RemoveChildAndReturnIndex(contentModifierNode_);
        contentModifierNode_ = nullptr;
        host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
        return;
    }
    auto node = BuildContentModifierNode();
    if (contentModifierNode_ == node) {
        return;
    }
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    host->RemoveChildAndReturnIndex(contentModifierNode_);
    contentModifierNode_ = node;
    CHECK_NULL_VOID(contentModifierNode_);
    host->AddChild(contentModifierNode_, 0);
    host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
}

RefPtr<FrameNode> GaugePattern::BuildContentModifierNode()
{
    if (!makeFunc_.has_value()) {
        return nullptr;
    }
    CHECK_NULL_RETURN(makeFunc_, nullptr);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto gaugePaintProperty = GetPaintProperty<GaugePaintProperty>();
    CHECK_NULL_RETURN(gaugePaintProperty, nullptr);
    auto min = gaugePaintProperty->GetMin().value_or(0.0f);
    auto max = gaugePaintProperty->GetMax().value_or(100.0f);
    auto value = gaugePaintProperty->GetValue().value_or(min);
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    auto enabled = eventHub->IsEnabled();
    GaugeConfiguration gaugeConfiguration(value, min, max, enabled);
    return (makeFunc_.value())(gaugeConfiguration);
}

void GaugePattern::InitTitleContent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if ((host->TotalChildCount() > 0) && (!titleChildId_.has_value())) {
        auto firstChild = host->GetFirstChild();
        CHECK_NULL_VOID(firstChild);
        if (firstChild->GetTag() == V2::GAUGE_DESCRIPTION_TAG) {
            return;
        }

        if (minValueTextId_.has_value() && (firstChild->GetId() == minValueTextId_.value())) {
            return;
        }

        titleChildId_ = firstChild->GetId();
    }
}

void GaugePattern::InitDescriptionNode()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto linearNode = FrameNode::GetOrCreateFrameNode(V2::GAUGE_DESCRIPTION_TAG, GetDescriptionNodeId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    CHECK_NULL_VOID(linearNode);
    linearNode->Clean();
    auto descriptionRenderContext = linearNode->GetRenderContext();
    CHECK_NULL_VOID(descriptionRenderContext);
    descriptionRenderContext->UpdateClipEdge(true);
    CHECK_NULL_VOID(descriptionNode_);
    descriptionNode_->MountToParent(linearNode);
    auto property = linearNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(property);

    linearNode->MountToParent(frameNode);
    linearNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    linearNode->MarkModifyDone();
}

void GaugePattern::InitLimitValueText(int32_t valueTextId, bool isMin)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto gaugePaintProperty = GetPaintProperty<GaugePaintProperty>();
    CHECK_NULL_VOID(gaugePaintProperty);
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, valueTextId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_VOID(textNode);

    auto limitValue =
        isMin ? gaugePaintProperty->GetMinValue(DEFAULT_MIN_VALUE) : gaugePaintProperty->GetMaxValue(DEFAULT_MAX_VALUE);
    auto limitValueColor = Color::BLACK;
    if (gaugePaintProperty->HasGradientColors()) {
        limitValueColor = isMin ? gaugePaintProperty->GetGradientColorsValue().at(0).at(0).first
                                : GetMaxValueColor(gaugePaintProperty);
    } else {
        limitValueColor = isMin ? (*GAUGE_DEFAULT_COLOR.begin()) : (*GAUGE_DEFAULT_COLOR.rbegin());
    }
    std::ostringstream out;
    out << std::setiosflags(std::ios::fixed) << std::setprecision(0) << limitValue;

    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<GaugeTheme>();

    auto limitValueTextProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(limitValueTextProperty);
    limitValueTextProperty->UpdateContent(out.str());
    limitValueTextProperty->UpdateTextColor(limitValueColor);
    limitValueTextProperty->UpdateMaxLines(1);
    limitValueTextProperty->UpdateAdaptMaxFontSize(LIMIT_VALUE_MAX_FONTSIZE);
    limitValueTextProperty->UpdateAdaptMinFontSize(theme->GetLimitValueMinFontSize());
    limitValueTextProperty->UpdateFontWeight(FontWeight::MEDIUM);
    limitValueTextProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    auto textAlign = isMin ? TextAlign::LEFT : TextAlign::RIGHT;
    limitValueTextProperty->UpdateTextAlign(textAlign);

    textNode->MountToParent(frameNode);
    textNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    textNode->MarkModifyDone();
}

void GaugePattern::HideLimitValueText(int32_t valueTextId, bool isMin)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, valueTextId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_VOID(textNode);
    auto geometryNode = textNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(SizeF(0, 0));
    auto limitValueTextProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(limitValueTextProperty);
    limitValueTextProperty->Reset();
    textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    textNode->MarkModifyDone();
}

Color GaugePattern::GetMaxValueColor(const RefPtr<GaugePaintProperty>& gaugePaintProperty) const
{
    Color color(Color::BLACK);
    CHECK_NULL_RETURN(gaugePaintProperty, color);
    switch (gaugePaintProperty->GetGaugeTypeValue(GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT)) {
        case GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT: {
            color = gaugePaintProperty->GetGradientColorsValue().rbegin()->rbegin()->first;
            break;
        }
        case GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT: {
            color = gaugePaintProperty->GetGradientColorsValue().at(0).rbegin()->first;
            break;
        }
        case GaugeType::TYPE_CIRCULAR_MONOCHROME: {
            color = gaugePaintProperty->GetGradientColorsValue().at(0).at(0).first;
            break;
        }
        default:
            // do nothing.
            break;
    }
    return color;
}

void GaugePattern::InitIndicatorImage()
{
    auto gaugePaintProperty = GetPaintProperty<GaugePaintProperty>();
    CHECK_NULL_VOID(gaugePaintProperty);

    ImageSourceInfo sourceInfo = gaugePaintProperty->GetIndicatorIconSourceInfo().value_or(ImageSourceInfo(""));
    LoadNotifier iconLoadNotifier(CreateDataReadyCallback(), CreateLoadSuccessCallback(), CreateLoadFailCallback());
    indicatorIconLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(iconLoadNotifier), true);
    indicatorIconLoadingCtx_->LoadImageData();
}

LoadSuccessNotifyTask GaugePattern::CreateLoadSuccessCallback()
{
    auto task = [weak = WeakClaim(this)](const ImageSourceInfo& /* sourceInfo */) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnImageLoadSuccess();
    };
    return task;
}

DataReadyNotifyTask GaugePattern::CreateDataReadyCallback()
{
    auto task = [weak = WeakClaim(this)](const ImageSourceInfo& /* sourceInfo */) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnImageDataReady();
    };
    return task;
}

LoadFailNotifyTask GaugePattern::CreateLoadFailCallback()
{
    auto task = [weak = WeakClaim(this)](const ImageSourceInfo& /* sourceInfo */, const std::string& msg,
                    const ImageErrorInfo& /* errorInfo */) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnImageLoadFail();
    };
    return task;
}

void GaugePattern::OnImageLoadFail()
{
    auto gaugePaintProperty = GetPaintProperty<GaugePaintProperty>();
    CHECK_NULL_VOID(gaugePaintProperty);
    gaugePaintProperty->ResetIndicatorIconSourceInfo();
}

void GaugePattern::OnImageDataReady()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void GaugePattern::OnImageLoadSuccess()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkNeedRenderOnly();

    ImagePaintConfig config;
    config.isSvg_ = indicatorIconLoadingCtx_->GetSourceInfo().IsSvg();
    if (!config.isSvg_) {
        auto gaugePaintProperty = GetPaintProperty<GaugePaintProperty>();
        CHECK_NULL_VOID(gaugePaintProperty);
        gaugePaintProperty->ResetIndicatorIconSourceInfo();
        return;
    }
    config.srcRect_ = indicatorIconLoadingCtx_->GetSrcRect();
    config.dstRect_ = indicatorIconLoadingCtx_->GetDstRect();
    indicatorIconCanvasImage_ = indicatorIconLoadingCtx_->MoveCanvasImage();
    indicatorIconCanvasImage_->SetPaintConfig(config);
}

void GaugePattern::ObscureLimitValueText(bool isSensitive)
{
    if (minValueTextId_.has_value()) {
        ObscureText(GetMinValueTextId(), isSensitive);
    }
    if (maxValueTextId_.has_value()) {
        ObscureText(GetMaxValueTextId(), isSensitive);
    }
}

void GaugePattern::ObscureText(int32_t valueTextId, bool isSensitive)
{
    auto textNode = FrameNode::GetFrameNode(V2::TEXT_ETS_TAG, valueTextId);
    CHECK_NULL_VOID(textNode);
    auto textPattern = textNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->OnSensitiveStyleChange(isSensitive);
    textNode->SetPrivacySensitive(isSensitive);
    textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void GaugePattern::OnSensitiveStyleChange(bool isSensitive)
{
    ObscureLimitValueText(isSensitive);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto gaugePaintProperty = frameNode->GetPaintProperty<NG::GaugePaintProperty>();
    CHECK_NULL_VOID(gaugePaintProperty);
    gaugePaintProperty->UpdateIsSensitive(isSensitive);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void GaugePattern::UpdateStrokeWidth(const CalcDimension& strokeWidth, bool isFirstLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<GaugePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto layoutProperty = host->GetLayoutProperty<GaugeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    paintProperty->UpdateStrokeWidth(strokeWidth);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    layoutProperty->UpdateStrokeWidth(strokeWidth);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void GaugePattern::UpdateIndicatorIconPath(
    const std::string& iconPath, const std::string& bundleName, const std::string& moduleName, bool isFirstLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto paintProperty = host->GetPaintProperty<GaugePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (pipelineContext->IsSystmColorChange() || isFirstLoad) {
        paintProperty->UpdateIndicatorIconSourceInfo(ImageSourceInfo(iconPath, bundleName, moduleName));
    }
    if (host->GetRerenderable()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void GaugePattern::UpdateIndicatorSpace(const CalcDimension& space, bool isFirstLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto paintProperty = host->GetPaintProperty<GaugePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (pipelineContext->IsSystmColorChange() || isFirstLoad) {
        paintProperty->UpdateIndicatorSpace(space);
    }
    if (host->GetRerenderable()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void GaugePattern::OnColorModeChange(uint32_t colorMode)
{
    Pattern::OnColorModeChange(colorMode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (host->GetRerenderable()) {
        host->MarkModifyDone();
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

bool GaugePattern::CheckDarkResource(uint32_t resId)
{
    auto colorMode = Container::CurrentColorMode();
    if (colorMode != ColorMode::DARK) {
        return true;
    }
    auto resourceAdapter = ResourceManager::GetInstance().GetResourceAdapter(Container::CurrentIdSafely());
    CHECK_NULL_RETURN(resourceAdapter, false);
    bool hasDarkRes = false;
    hasDarkRes = resourceAdapter->ExistDarkResById(std::to_string(resId));
    return hasDarkRes;
}

bool GaugePattern::ProcessSingleColorStop(Color& color, std::function<uint32_t(uint32_t)>& invertFunc)
{
    uint32_t resId = color.GetResourceId();
    if (resId != 0) {
        if (CheckDarkResource(resId)) {
            color.UpdateColorByResourceId();
            return true;
        } else if (invertFunc) {
            color = Color(invertFunc(color.GetValue()));
            return true;
        }
    } else if (invertFunc) {
        color = Color(invertFunc(color.GetValue()));
        return true;
    }
    return false;
}

bool GaugePattern::ProcessGradientColors(std::vector<std::vector<std::pair<Color, Dimension>>>& gradientColors,
    std::function<uint32_t(uint32_t)>& invertFunc)
{
    bool isGradientColorsResEmpty = true;
    for (auto& colorStopArray : gradientColors) {
        for (auto& colorStop : colorStopArray) {
            Color& color = colorStop.first;
            if (ProcessSingleColorStop(color, invertFunc)) {
                isGradientColorsResEmpty = false;
            }
        }
    }
    return isGradientColorsResEmpty;
}

void GaugePattern::OnColorConfigurationUpdate()
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto paintProperty = host->GetPaintProperty<GaugePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->GetUseJsLinearGradientValue(false) || !paintProperty->HasGradientColors()) {
        return;
    }
    bool isGradientColorsResEmpty = true;
    auto instanceId = Container::CurrentIdSafely();
    auto nodeTag = host->GetTag();
    auto invertFunc = ColorInverter::GetInstance().GetInvertFunc(instanceId, nodeTag);
    auto colorMode = Container::CurrentColorMode();
    auto gradientColors = paintProperty->GetGradientColorsValue();
    bool needInitRevert = false;
    auto colorModeInit = paintProperty->GetColorModeInitValue();
    if (colorModeInit == static_cast<int>(colorMode)) {
        needInitRevert = true;
    } else {
        isGradientColorsResEmpty = ProcessGradientColors(gradientColors, invertFunc);
    }
    if (needInitRevert) {
        paintProperty->UpdateGradientColors(paintProperty->GetGradientColorsInitValue());
    } else if (!isGradientColorsResEmpty) {
        paintProperty->UpdateGradientColors(gradientColors);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}
} // namespace OHOS::Ace::NG
