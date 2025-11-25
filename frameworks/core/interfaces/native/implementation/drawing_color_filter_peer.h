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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_DRAWING_COLOR_FILTER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_DRAWING_COLOR_FILTER_PEER_IMPL_H

#include "base/image/drawing_color_filter.h"
#include "base/memory/referenced.h"

struct drawing_ColorFilterPeer final {
    OHOS::Ace::RefPtr<OHOS::Ace::DrawingColorFilter> drawingColorFilter;

    static drawing_ColorFilterPeer *Create(void* data)
    {
        auto colorFilter = OHOS::Ace::DrawingColorFilter::CreateDrawingColorFilterFromNative(data);
        return new drawing_ColorFilterPeer{ colorFilter };
    }

    static void Destroy(drawing_ColorFilterPeer *peer)
    {
        CHECK_NULL_VOID(peer);
        delete peer;
    }
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_DRAWING_COLOR_FILTER_PEER_IMPL_H