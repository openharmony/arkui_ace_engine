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

#include "rosen_render_custom_paint.h"

namespace OHOS::Ace {
RefPtr<RenderNode> RenderCustomPaint::Create()
{
    if (SystemProperties::GetRosenBackendEnabled()) {
#ifdef ENABLE_ROSEN_BACKEND
        return AceType::MakeRefPtr<RosenRenderCustomPaint>();
#else
        return nullptr;
#endif
    } else {
        return nullptr;
    }
}

double RenderCustomPaint::PaintMeasureText(const MeasureContext& context)
{
    if (SystemProperties::GetRosenBackendEnabled()) {
#ifdef ENABLE_ROSEN_BACKEND
        return RosenRenderCustomPaint::MeasureTextInner(context);
#else
        return 0.0;
#endif
    } else {
        return 0.0;
    }
}

Size RenderCustomPaint::MeasureTextSize(const MeasureContext& context)
{
    if (SystemProperties::GetRosenBackendEnabled()) {
#ifdef ENABLE_ROSEN_BACKEND
        return RosenRenderCustomPaint::MeasureTextSizeInner(context);
#else
        return Size(0.0, 0.0);
#endif
    } else {
        return Size(0.0, 0.0);
    }
}
} // namespace OHOS::Ace
