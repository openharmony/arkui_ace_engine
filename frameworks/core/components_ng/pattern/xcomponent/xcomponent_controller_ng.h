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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_CONTROLLER_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_CONTROLLER_NG_H

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/xcomponent/inner_xcomponent_controller.h"

namespace OHOS::Ace::NG {
class XComponentPattern;

class XComponentControllerNG : public OHOS::Ace::InnerXComponentController {
public:
    XComponentControllerNG() = default;
    ~XComponentControllerNG() override = default;

    XComponentControllerErrorCode GetGlobalPosition(float& offsetX, float& offsetY) override;

    XComponentControllerErrorCode GetSize(float& width, float& height) override;

    XComponentControllerErrorCode SetExtController(std::shared_ptr<XComponentController> xcomponentController) override;

    XComponentControllerErrorCode ResetExtController(
        std::shared_ptr<XComponentController> xcomponentController) override;

    void SetIdealSurfaceWidth(float surfaceWidth) override;

    void SetIdealSurfaceHeight(float surfaceHeight) override;

    void SetIdealSurfaceOffsetX(float offsetX) override;

    void SetIdealSurfaceOffsetY(float offsetY) override;

    void ClearIdealSurfaceOffset(bool isXAxis) override;

    void UpdateSurfaceBounds() override;

    void GetSurfaceSize(float& surfaceWidth, float& surfaceHeight) override;

    void GetLocalLocation(float& offsetX, float& offsetY) override;

    void SetPattern(const RefPtr<XComponentPattern>& pattern);

    RefPtr<XComponentPattern> GetPattern();

    void StartImageAnalyzer(void* config, OnAnalyzedCallback& onAnalyzed) override;

    void StopImageAnalyzer() override;

    void SetSurfaceRotation(bool isLock) override;

    bool GetSurfaceRotation() override;

private:
    WeakPtr<XComponentPattern> pattern_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_CONTROLLER_NG_H
