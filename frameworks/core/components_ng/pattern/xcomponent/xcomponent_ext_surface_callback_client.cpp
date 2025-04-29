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

#include "core/components_ng/pattern/xcomponent/xcomponent_ext_surface_callback_client.h"

namespace OHOS::Ace::NG {
void XComponentExtSurfaceCallbackClient::ProcessSurfaceCreate()
{
    auto xcPattern = weakXComponentPattern_.Upgrade();
    CHECK_NULL_VOID(xcPattern);
    xcPattern->XComponentSizeInit();
}

void XComponentExtSurfaceCallbackClient::ProcessSurfaceChange(int32_t width, int32_t height)
{
    auto xcPattern = weakXComponentPattern_.Upgrade();
    CHECK_NULL_VOID(xcPattern);
    xcPattern->XComponentSizeChange({ 0, 0, width, height }, true);
}

void XComponentExtSurfaceCallbackClient::ProcessSurfaceDestroy()
{
    auto xcPattern = weakXComponentPattern_.Upgrade();
    CHECK_NULL_VOID(xcPattern);
    xcPattern->OnSurfaceDestroyed();
}
} // namespace OHOS::Ace::NG
