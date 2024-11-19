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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_MATRIX_2D_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_MATRIX_2D_PEER_IMPL_H

#include "arkoala_api.h"
#include "arkoala_api_generated.h"
#include "core/components/common/properties/paint_state.h"

struct Matrix2DPeer {
public:
    const OHOS::Ace::RefPtr<OHOS::Ace::TransformParam>& GetTransformParam() const
    {
        return param_;
    }
    void SetTransformParam(const OHOS::Ace::RefPtr<OHOS::Ace::TransformParam>& param)
    {
        param_ = param;
    }
private:
    OHOS::Ace::RefPtr<OHOS::Ace::TransformParam> param_ = nullptr;
};

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_MATRIX_2D_PEER_IMPL_H
