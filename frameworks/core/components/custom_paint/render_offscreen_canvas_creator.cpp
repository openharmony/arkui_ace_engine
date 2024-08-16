/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/custom_paint/render_custom_paint.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "rosen_render_offscreen_canvas.h"
#endif

namespace OHOS::Ace {
RefPtr<OffscreenCanvas> RenderOffscreenCanvas::Create(
    const WeakPtr<PipelineBase>& context, int32_t width, int32_t height)
{
    if (SystemProperties::GetRosenBackendEnabled()) {
#ifdef ENABLE_ROSEN_BACKEND
        return AceType::MakeRefPtr<RosenRenderOffscreenCanvas>(context, width, height);
#else
        return nullptr;
#endif
    } else {
#ifndef NG_BUILD
        return nullptr;
#else
        return nullptr;
#endif
    }
}
} // namespace OHOS::Ace
