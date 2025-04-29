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

#include "core/components_ng/pattern/qrcode/qrcode_pattern.h"

#include "base/log/dump_log.h"

namespace OHOS::Ace::NG {

void QRCodePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

bool QRCodePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure && skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<QRCodeLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    qrCodeSize_ = layoutAlgorithm->GetQRCodeSize();
    return true;
}

void QRCodePattern::OnModifyDone()
{
    Pattern::OnModifyDone();
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
}

void QRCodePattern::DumpInfo()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<QRCodePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    DumpLog::GetInstance().AddDesc(
        std::string("Color: ").append(paintProperty->GetColorValue(Color::TRANSPARENT).ColorToString()));
    DumpLog::GetInstance().AddDesc(
        std::string("ContentOpacity: ").append(std::to_string(paintProperty->GetOpacityValue(1.0f))));
    DumpLog::GetInstance().AddDesc(
        std::string("ContentString: ").append(paintProperty->GetValueValue(" ")));
}

FocusPattern QRCodePattern::GetFocusPattern() const
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, FocusPattern());
    auto qrCodeTheme = pipeline->GetTheme<QrcodeTheme>();
    CHECK_NULL_RETURN(qrCodeTheme, FocusPattern());
    auto focusStyleType = static_cast<FocusStyleType>(static_cast<int32_t>(qrCodeTheme->GetFocusStyleType()));
    FocusPattern focusPattern = { FocusType::NODE, true, FocusStyleType::INNER_BORDER };
    auto focusedColor = qrCodeTheme->GetFocusedColor();
    FocusPaintParam focusPaintParam;
    focusPaintParam.SetPaintColor(focusedColor);
    focusPattern.SetFocusPaintParams(focusPaintParam);
    focusPattern.SetStyleType(focusStyleType);
    return focusPattern;
}

void QRCodePattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<QRCodePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    json->Put("Color", paintProperty->GetColorValue(Color::TRANSPARENT).ColorToString().c_str());
    json->Put("ContentOpacity", std::to_string(paintProperty->GetOpacityValue(1.0f)).c_str());
    json->Put("ContentString", paintProperty->GetValueValue(" ").c_str());
}
} // namespace OHOS::Ace::NG
