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

#include "bridge/cj_frontend/cppview/canvas_pattern.h"

namespace OHOS::Ace::Framework {
NativeCanvasPattern::NativeCanvasPattern() : FFIData() {}

NativeCanvasPattern::~NativeCanvasPattern()
{
    LOGI("Native Canvas Pattern Destroyed: %{public}" PRId64, GetID());
}

void NativeCanvasPattern::SetTransform(int64_t matrixId)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(matrixId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d invert error, Cannot get NativeCanvasMatrix by id: %{public}" PRId64, matrixId);
        return;
    }
    if (canvasRenderWeak_) {
        canvasRenderWeak_->SetTransform(GetId(), matrix2d->GetTransform());
    }
}

} // namespace OHOS::Ace::Framework