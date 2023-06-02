/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RENDERING_CONTEXT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RENDERING_CONTEXT_MODEL_H

#include <mutex>

#include "base/memory/referenced.h"
#include "frameworks/core/components_ng/pattern/custom_paint/custom_paint_pattern.h"
#include "frameworks/core/components_ng/pattern/custom_paint/offscreen_canvas_pattern.h"

namespace OHOS::Ace {
class RenderingContextModel {
public:
    static RenderingContextModel* GetInstance();
    virtual ~RenderingContextModel() = default;

    virtual void GetWidth(RefPtr<AceType>& canvasPattern, double& width) = 0;
    virtual void GetHeight(RefPtr<AceType>& canvasPattern, double& height) = 0;
    virtual void SetTransferFromImageBitmap(RefPtr<AceType>& canvasPattern,
        RefPtr<AceType> offscreenCPattern) = 0;

private:
    static std::unique_ptr<RenderingContextModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RENDERING_CONTEXT_MODEL_H