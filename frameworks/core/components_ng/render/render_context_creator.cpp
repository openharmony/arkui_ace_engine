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

#ifdef ENABLE_ROSEN_BACKEND
#include "core/components_ng/render/adapter/rosen_render_context.h"
#endif
#ifdef FLUTTER_2_5
#include "core/components_ng/render/adapter/flutter_render_context.h"
#endif
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
RefPtr<RenderContext> RenderContext::Create()
{
    if (SystemProperties::GetRosenBackendEnabled()) {
#ifdef ENABLE_ROSEN_BACKEND
        return MakeRefPtr<RosenRenderContext>();
#endif
    }
#ifdef FLUTTER_2_5
    return MakeRefPtr<FlutterRenderContext>();
#else
    return nullptr;
#endif
}
} // namespace OHOS::Ace::NG
