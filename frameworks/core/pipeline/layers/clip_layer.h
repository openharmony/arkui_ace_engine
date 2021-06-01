/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_LAYERS_CLIP_LAYER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_LAYERS_CLIP_LAYER_H

#include "base/geometry/rrect.h"
#include "core/pipeline/layers/layer.h"
#include "core/pipeline/layers/offset_layer.h"
#include "core/pipeline/layers/scene_builder.h"

namespace OHOS::Ace::Flutter {

enum class Clip {
    NONE = 0,
    HARD_EDGE,
    ANTI_ALIAS,
    ANTI_ALIAS_WITH_SAVE_LAYER,
};

class ClipLayer : public OffsetLayer {
    DECLARE_ACE_TYPE(ClipLayer, OffsetLayer)
public:
    ClipLayer(double left, double right, double top, double bottom, Clip clipBehavior)
        : OffsetLayer(0, 0), clipBehavior_(clipBehavior)
    {
        rrect_.sk_rrect = SkRRect::MakeRect(SkRect::MakeLTRB(static_cast<SkScalar>(left), static_cast<SkScalar>(top),
            static_cast<SkScalar>(right), static_cast<SkScalar>(bottom)));
    }
    ~ClipLayer() override = default;

    void AddToScene(SceneBuilder& builder, double x, double y) override;

    void SetClip(double left, double right, double top, double bottom, Clip clipBehavior);
    void SetClipRRect(const RRect& rrect, Clip clipBehavior);
    void SetClipRRect(const Rect& rect, double x, double y, Clip clipBehavior);
    void SetClipRRect(const flutter::RRect& rrect);
    SkVector GetSkRadii(const Radius& radius);
    void Dump() override;

private:
    flutter::RRect rrect_;
    Clip clipBehavior_ { Clip::NONE };
};

} // namespace OHOS::Ace::Flutter

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_LAYERS_CLIP_LAYER_H
