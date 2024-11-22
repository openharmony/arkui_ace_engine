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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SHAPE_ABSTRACT_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SHAPE_ABSTRACT_MODEL_IMPL_H

#include "core/components_ng/pattern/shape/shape_abstract_model.h"

namespace OHOS::Ace::Framework {

class ShapeAbstractModelImpl : public OHOS::Ace::ShapeAbstractModel {
public:
    void SetStroke(const Color& color) override;
    void SetFill(const Color& color) override;
    void SetForegroundColor(const Color& color) override;
    void SetStrokeDashOffset(const Ace::Dimension& dashOffset) override;
    void SetStrokeLineCap(int lineCapStyle) override;
    void SetStrokeLineJoin(int lineJoinStyle) override;
    void SetStrokeMiterLimit(double miterLimit) override;
    void SetStrokeOpacity(double opacity) override;
    void SetFillOpacity(double opacity) override;
    void SetStrokeWidth(const Ace::Dimension& lineWidth) override;
    void SetStrokeDashArray(const std::vector<Ace::Dimension>& dashArray) override;
    void SetAntiAlias(bool antiAlias) override;
    void SetWidth(Dimension& width) override;
    void SetHeight(Dimension& height) override;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SHAPE_ABSTRACT_MODEL_IMPL_H