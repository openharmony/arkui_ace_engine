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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_PAINT_METHOD_H

#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/model/model_adapter_wrapper.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ModelPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(ModelPaintMethod, NodePaintMethod)
public:
    ModelPaintMethod(const WeakPtr<ModelAdapterWrapper>& adapter);
    ~ModelPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

private:
    void PerformPaint(RSCanvas& canvas, PaintWrapper* paintWrapper);
    void OnPaintFinish();

    WeakPtr<ModelAdapterWrapper> modelAdapter_;
    ACE_DISALLOW_COPY_AND_MOVE(ModelPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_PAINT_METHOD_H
