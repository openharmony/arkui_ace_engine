/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/sheet/bridge/sheet_manager_inner_modifier.h"

#include "core/components_ng/pattern/sheet/sheet_manager.h"

namespace OHOS::Ace::NG::InnerModifier {
namespace {

RefPtr<OverlayManager> FindPageNodeOverlay(
    const RefPtr<FrameNode>& targetNode, bool isShow, bool isStartByUIContext)
{
    return SheetManager::FindPageNodeOverlay(targetNode, isShow, isStartByUIContext);
}

void RegisterDestroyCallback(const RefPtr<FrameNode>& targetNode, SheetStyle& sheetStyle, int32_t containerId)
{
    SheetManager::GetInstance().RegisterDestroyCallback(targetNode, sheetStyle, containerId);
}

void CloseSheetInSubWindow(int32_t targetId)
{
    SheetManager::GetInstance().CloseSheetInSubWindow(SheetKey(targetId));
}

bool RemoveSheetByESC()
{
    return SheetManager::GetInstance().RemoveSheetByESC();
}

int32_t OpenBindSheetByUIContext(const RefPtr<FrameNode>& sheetContentNode,
    std::function<void()>&& titleBuildFunc, SheetStyle& sheetStyle, std::function<void()>&& onAppear,
    std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
    std::function<void(const int32_t info)>&& onWillDismiss, std::function<void()>&& onWillAppear,
    std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
    std::function<void(const float)>&& onDetentsDidChange, std::function<void(const float)>&& onWidthDidChange,
    std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack,
    int32_t currentInstanceId, int32_t targetId)
{
    return SheetManager::GetInstance().OpenBindSheetByUIContext(sheetContentNode, std::move(titleBuildFunc), sheetStyle,
        std::move(onAppear), std::move(onDisappear), std::move(shouldDismiss), std::move(onWillDismiss),
        std::move(onWillAppear), std::move(onWillDisappear), std::move(onHeightDidChange),
        std::move(onDetentsDidChange), std::move(onWidthDidChange), std::move(onTypeDidChange),
        std::move(sheetSpringBack), currentInstanceId, targetId);
}

int32_t UpdateBindSheetByUIContext(
    const RefPtr<FrameNode>& sheetContentNode, const SheetStyle& sheetStyle, bool isPartialUpdate,
    int32_t currentInstanceId)
{
    return SheetManager::GetInstance().UpdateBindSheetByUIContext(
        sheetContentNode, sheetStyle, isPartialUpdate, currentInstanceId);
}

int32_t CloseBindSheetByUIContext(const RefPtr<FrameNode>& sheetContentNode, int32_t currentInstanceId)
{
    return SheetManager::GetInstance().CloseBindSheetByUIContext(sheetContentNode, currentInstanceId);
}

void SetMaskInteractive(const RefPtr<FrameNode>& maskNode, bool isInteractive)
{
    SheetManager::SetMaskInteractive(maskNode, isInteractive);
}

int32_t GetDismissSheetId()
{
    return SheetManager::GetInstance().GetDismissSheet();
}
} // namespace

const ArkUISheetManagerInnerModifier* GetSheetManagerInnerModifier()
{
    static const ArkUISheetManagerInnerModifier modifier = {
        .findPageNodeOverlay = FindPageNodeOverlay,
        .registerDestroyCallback = RegisterDestroyCallback,
        .closeSheetInSubWindow = CloseSheetInSubWindow,
        .removeSheetByESC = RemoveSheetByESC,
        .openBindSheetByUIContext = OpenBindSheetByUIContext,
        .updateBindSheetByUIContext = UpdateBindSheetByUIContext,
        .closeBindSheetByUIContext = CloseBindSheetByUIContext,
        .setMaskInteractive = SetMaskInteractive,
        .getDismissSheetId = GetDismissSheetId,
    };
    return &modifier;
}
} // namespace OHOS::Ace::NG::InnerModifier
