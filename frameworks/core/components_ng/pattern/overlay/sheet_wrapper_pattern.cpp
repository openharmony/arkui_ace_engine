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

#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"

namespace OHOS::Ace::NG {

void SheetWrapperPattern::RegisterSheetMaskColorRes(const RefPtr<FrameNode>& maskNode,
    const RefPtr<FrameNode>& sheetNode, RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(maskNode);
    auto pattern = maskNode->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_VOID(pattern);
    if (resObj) {
        auto maskNodeWK = AceType::WeakClaim(AceType::RawPtr(maskNode));
        auto sheetNodeWK = AceType::WeakClaim(AceType::RawPtr(sheetNode));
        auto&& updateFunc =
            [maskNodeWK, sheetNodeWK](const RefPtr<ResourceObject>& resObj) {
            // Parse the maskColor using the resource object.
            // If parse failed, use the default value in sheetTheme.
            Color maskColor;
            bool result = ResourceParseUtils::ParseResColor(resObj, maskColor);
            if (!result) {
                auto pipeline = PipelineBase::GetCurrentContext();
                CHECK_NULL_VOID(pipeline);
                auto sheetTheme = pipeline->GetTheme<SheetTheme>();
                CHECK_NULL_VOID(sheetTheme);
                maskColor = sheetTheme->GetMaskColor();
            }

            // Update sheetStyle.
            auto sheetNode = sheetNodeWK.Upgrade();
            CHECK_NULL_VOID(sheetNode);
            auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
            auto sheetStyle = layoutProperty->GetSheetStyleValue();
            NG::SheetStyle sheetStyleVal = sheetStyle;
            sheetStyleVal.maskColor = maskColor;
            layoutProperty->UpdateSheetStyle(sheetStyleVal);

            // Update sheet mask background color.
            auto maskNode = maskNodeWK.Upgrade();
            CHECK_NULL_VOID(maskNode);
            auto maskRenderContext = maskNode->GetRenderContext();
            CHECK_NULL_VOID(maskRenderContext);
            maskRenderContext->UpdateBackgroundColor(maskColor);
        };
        pattern->AddResObj("sheetWrapper.maskColor", resObj, std::move(updateFunc));
    } else {
        pattern->RemoveResObj("sheetWrapper.maskColor");
    }
}

void SheetWrapperPattern::UpdateSheetMaskResource(const RefPtr<FrameNode>& maskNode,
    const RefPtr<FrameNode>& sheetNode, NG::SheetStyle& sheetStyle)
{
    if (sheetStyle.maskColor.has_value()) {
        auto resObj = sheetStyle.GetMaskColorResObj();
        RegisterSheetMaskColorRes(maskNode, sheetNode, resObj);
    }
}
} // namespace OHOS::Ace::NG
