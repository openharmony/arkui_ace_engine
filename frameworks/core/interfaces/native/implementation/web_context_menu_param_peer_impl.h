/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_WEB_CONTEXT_MENU_PARAM_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_WEB_CONTEXT_MENU_PARAM_PEER_IMPL_H

#include "core/components/web/web_event.h"

struct WebContextMenuParamPeer {
    OHOS::Ace::RefPtr<OHOS::Ace::WebContextMenuParam> handler;

    int32_t GetPreviewWidth()
    {
        UpdatePreviewSize();
        return previewWidth_;
    }

    int32_t GetPreviewHeight()
    {
        UpdatePreviewSize();
        return previewHeight_;
    }

private:
    int32_t previewWidth_ = -1;
    int32_t previewHeight_ = -1;

    void UpdatePreviewSize()
    {
        if (previewWidth_ >= 0 && previewHeight_ >= 0) {
            return;
        }
        if (handler) {
            int32_t x = 0;
            int32_t y = 0;
            handler->GetImageRect(x, y, previewWidth_, previewHeight_);
        }
    }
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_WEB_CONTEXT_MENU_PARAM_PEER_IMPL_H
