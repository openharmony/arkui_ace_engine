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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_LAYERS_HOLE_LAYER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_LAYERS_HOLE_LAYER_H

#include "base/geometry/offset.h"
#include "base/geometry/size.h"
#include "core/pipeline/layers/container_layer.h"
#include "core/pipeline/layers/scene_builder.h"

namespace OHOS::Ace::Flutter {

class HoleLayer : public ContainerLayer {
    DECLARE_ACE_TYPE(HoleLayer, ContainerLayer)
public:
    HoleLayer(double width, double height);
    ~HoleLayer() override = default;

    void AddToScene(SceneBuilder& builder, double x, double y) override;

    void Dump() override;

    void SetSize(double width, double height)
    {
        size_.SetWidth(width);
        size_.SetHeight(height);
    }

    void SetOffset(double x, double y)
    {
        offset_.SetX(x);
        offset_.SetY(y);
    }

    const Offset& GetOffset() const
    {
        return offset_;
    }

private:
    Offset offset_;
    OHOS::Ace::Size size_;
    int32_t holeId_;
};

} // namespace OHOS::Ace::Flutter

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_LAYERS_HOLE_LAYER_H
