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

#include "core/components_ng/pattern/model/model_paint_method.h"


namespace OHOS::Ace::NG {

ModelPaintMethod::ModelPaintMethod(const WeakPtr<ModelAdapterWrapper>& adapter) : modelAdapter_(adapter)
{}

CanvasDrawFunction ModelPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto adapter = modelAdapter_.Upgrade();
    CHECK_NULL_RETURN(adapter, nullptr);
    return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto model = weak.Upgrade();
        if (model) {
            model->PerformPaint(canvas, paintWrapper);
            model->OnPaintFinish();
        }
    };
}

void ModelPaintMethod::OnPaintFinish()
{
    auto adapter = modelAdapter_.Upgrade();
    CHECK_NULL_VOID(adapter);
    adapter->OnPaintFinish();
}

void ModelPaintMethod::PerformPaint(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    auto adapter = modelAdapter_.Upgrade();
    CHECK_NULL_VOID(adapter);
    auto paintProperty = DynamicCast<ModelPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    adapter->OnPaint3D(paintProperty);
}
} // namespace OHOS::Ace::NG
