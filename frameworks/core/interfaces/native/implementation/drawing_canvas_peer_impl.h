/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_DRAWING_CANVAS_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_DRAWING_CANVAS_PEER_IMPL_H

#include "core/interfaces/native/utility/peer_utils.h"

struct drawing_CanvasPeer {
#ifndef ACE_UNITTEST
public:
    explicit drawing_CanvasPeer(OHOS::Rosen::Drawing::Canvas* rsCanvas)
    {
        rsCanvas_ = rsCanvas;
    }
    ~drawing_CanvasPeer() = default;
    OHOS::Rosen::Drawing::Canvas* GetCanvas() const
    {
        return rsCanvas_;
    }
    friend OHOS::Ace::NG::PeerUtils;
private:
    OHOS::Rosen::Drawing::Canvas* rsCanvas_;
#endif
};

#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_DRAWING_CANVAS_PEER_IMPL_H
