/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"

#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"

namespace OHOS::Ace::NG {
extern "C" ACE_FORCE_EXPORT XComponentControllerErrorCode OHOS_ACE_ChangeXComponentSurfaceCallbackMode(
    void* frameNode, char mode)
{
    auto* xcFrameNode = reinterpret_cast<NG::FrameNode*>(frameNode);
    if (!xcFrameNode) {
        return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    auto* xcPattern = xcFrameNode->GetPatternPtr<NG::XComponentPattern>();
    if (!xcPattern) {
        return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    xcPattern->ChangeSurfaceCallbackMode(static_cast<SurfaceCallbackMode>(mode));
    return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_NO_ERROR;
}

XComponentControllerErrorCode XComponentControllerNG::GetGlobalPosition(float& offsetX, float& offsetY)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    if (pattern->GetType() != XComponentType::SURFACE) {
        return XCOMPONENT_CONTROLLER_TYPE_ERROR;
    }
    auto globalPostion = pattern->GetOffsetRelativeToWindow();
    offsetX = globalPostion.GetX();
    offsetY = globalPostion.GetY();
    return XCOMPONENT_CONTROLLER_NO_ERROR;
}

XComponentControllerErrorCode XComponentControllerNG::GetSize(float& width, float& height)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    if (pattern->GetType() != XComponentType::SURFACE) {
        return XCOMPONENT_CONTROLLER_TYPE_ERROR;
    }
    auto drawSize = pattern->GetDrawSize();
    width = drawSize.Width();
    height = drawSize.Height();
    return XCOMPONENT_CONTROLLER_NO_ERROR;
}

XComponentControllerErrorCode XComponentControllerNG::SetExtController(
    std::shared_ptr<XComponentController> xcomponentController)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    if (pattern->GetType() != XComponentType::SURFACE) {
        return XCOMPONENT_CONTROLLER_TYPE_ERROR;
    }
    auto extController = std::static_pointer_cast<NG::XComponentControllerNG>(xcomponentController);
    if (!extController) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    auto extPattern = extController->GetPattern();
    if (!extPattern) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    if (extPattern->GetType() != XComponentType::SURFACE) {
        return XCOMPONENT_CONTROLLER_TYPE_ERROR;
    }
    return pattern->SetExtController(extPattern);
}

XComponentControllerErrorCode XComponentControllerNG::ResetExtController(
    std::shared_ptr<XComponentController> xcomponentController)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    if (pattern->GetType() != XComponentType::SURFACE) {
        return XCOMPONENT_CONTROLLER_TYPE_ERROR;
    }
    auto extController = std::static_pointer_cast<NG::XComponentControllerNG>(xcomponentController);
    auto extPattern = extController->GetPattern();
    if (!extPattern) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    if (extPattern->GetType() != XComponentType::SURFACE) {
        return XCOMPONENT_CONTROLLER_TYPE_ERROR;
    }
    return pattern->ResetExtController(extPattern);
}

void XComponentControllerNG::SetPattern(const RefPtr<XComponentPattern>& pattern)
{
    pattern_ = pattern;
}

RefPtr<XComponentPattern> XComponentControllerNG::GetPattern()
{
    return pattern_.Upgrade();
}

void XComponentControllerNG::GetSurfaceOffset(float& offsetX, float& offsetY)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto surfaceOffset = pattern->GetSurfaceOffset();
    offsetX = surfaceOffset.GetX();
    offsetY = surfaceOffset.GetY();
}

void XComponentControllerNG::GetSurfaceSize(float& surfaceWidth, float& surfaceHeight)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto surfaceSize = pattern->GetSurfaceSize();
    surfaceWidth = surfaceSize.Width();
    surfaceHeight = surfaceSize.Height();
}

void XComponentControllerNG::SetIdealSurfaceWidth(float surfaceWidth)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SetIdealSurfaceWidth(surfaceWidth);
}

void XComponentControllerNG::SetIdealSurfaceHeight(float surfaceHeight)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SetIdealSurfaceHeight(surfaceHeight);
}

void XComponentControllerNG::SetIdealSurfaceOffsetX(float offsetX)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SetIdealSurfaceOffsetX(offsetX);
}

void XComponentControllerNG::SetIdealSurfaceOffsetY(float offsetY)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SetIdealSurfaceOffsetY(offsetY);
}

void XComponentControllerNG::ClearIdealSurfaceOffset(bool isXAxis)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->ClearIdealSurfaceOffset(isXAxis);
}

void XComponentControllerNG::UpdateSurfaceBounds()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    const auto& [offsetChanged, sizeChanged, needFireNativeEvent] = pattern->UpdateSurfaceRect();
    pattern->HandleSurfaceChangeEvent(true, offsetChanged, sizeChanged, needFireNativeEvent);
}

void XComponentControllerNG::StartImageAnalyzer(void* config, OnAnalyzedCallback& onAnalyzed)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->StartImageAnalyzer(config, onAnalyzed);
}

void XComponentControllerNG::StopImageAnalyzer()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->StopImageAnalyzer();
}

void XComponentControllerNG::SetSurfaceRotation(bool isLock)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SetSurfaceRotation(isLock);
}

bool XComponentControllerNG::GetSurfaceRotation()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->GetSurfaceRotation();
}
} // namespace OHOS::Ace::NG
