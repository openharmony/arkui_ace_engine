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
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/ace_engine.h"

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

void SheetWrapperPattern::InitSubWindowId()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (!container->IsSubContainer()) {
        return;
    }
    subWindowId_ = Container::CurrentId();
    TAG_LOGI(AceLogTag::ACE_SHEET, "sheet wrapper open in subwindow id is %u", subWindowId_);
    auto currentId = SubwindowManager::GetInstance()->GetParentContainerId(subWindowId_);
    container = AceEngine::Get().GetContainer(currentId);
    CHECK_NULL_VOID(container);
    if (container->IsUIExtensionWindow()) {
        TAG_LOGI(AceLogTag::ACE_SHEET, "sheet host window is UEC");
        isShowInUEC_ = true;
    }
}

void SheetWrapperPattern::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto rootNode = AceType::DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(rootNode);
    if (rootNode->GetTag() != V2::NAVDESTINATION_VIEW_ETS_TAG) {
        return;
    }
    auto wrapperRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(wrapperRenderContext);
    auto navDestinationPattern = rootNode->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    auto zIndex = navDestinationPattern->GetTitlebarZIndex();

    // set the sheet to float on the NavDestination's titlebar when the sheet shows in NavDestination
    wrapperRenderContext->UpdateZIndex(zIndex + 1);
}

void SheetWrapperPattern::InitMainWindowRect(int32_t subwindowId)
{
    if (subWindowId_ == INVALID_SUBWINDOW_ID) {
        return;
    }
    auto instanceId = SubwindowManager::GetInstance()->GetParentContainerId(subwindowId);
    auto mainWindowContext = PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(mainWindowContext);
    auto windowGlobalRect = mainWindowContext->GetDisplayWindowRectInfo();
    mainWindowRect_ = RectF(windowGlobalRect.Left(), windowGlobalRect.Top(),
        windowGlobalRect.Width(), windowGlobalRect.Height());
    if (isShowInUEC_) {
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(subWindowId_,
            SubwindowType::TYPE_SHEET);
        CHECK_NULL_VOID(subwindow);
        auto rect = subwindow->GetUIExtensionHostWindowRect();
        mainWindowRect_ = RectF(rect.Left(), rect.Top(), rect.Width(), rect.Height());
    }
}

void SheetWrapperPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto maskLayoutProps = host->GetLayoutProperty();
    CHECK_NULL_VOID(maskLayoutProps);
    maskLayoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT);
    maskLayoutProps->UpdateAlignment(Alignment::TOP_LEFT);
    auto maskRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(maskRenderContext);
    maskRenderContext->UpdateClipEdge(true);
    InitSubWindowId();
    InitMainWindowRect(subWindowId_);
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
