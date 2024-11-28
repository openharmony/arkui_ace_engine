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

#include "base/utils/utils.h"
#include "core/components/common/properties/paint_state.h"
#include "core/pipeline/pipeline_base.h"

struct Matrix2DPeer {
public:
    Matrix2DPeer(){
        pointer = std::make_shared<OHOS::Ace::TransformParam>(transform); 
    }
    ~Matrix2DPeer() {
        pointer = nullptr;
    }; 
    
    double GetDensity()
    {
        double density = PipelineBase::GetCurrentDensity();
        return ((GetUnit() == OHOS::Ace::CanvasUnit::DEFAULT) && !NearZero(density)) ? density : 1.0;
    }
public:
    std::shared_ptr<OHOS::Ace::TransformParam> pointer = nullptr;
    OHOS::Ace::TransformParam transform;
    OHOS::Ace::CanvasUnit unit = OHOS::Ace::CanvasUnit::DEFAULT;
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_MATRIX_2D_PEER_IMPL_H
