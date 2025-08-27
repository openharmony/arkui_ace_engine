/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RENDER_NODE_RENDER_NODE_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RENDER_NODE_RENDER_NODE_PAINT_PROPERTY_H

#include <cstdint>
#include "core/components_ng/render/paint_property.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class RenderNodePaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(RenderNodePaintProperty, PaintProperty);
private:
    WeakPtr<FrameNode> host_;

public:
    RenderNodePaintProperty() = default;
    ~RenderNodePaintProperty() override = default;

    void SetHost(const WeakPtr<FrameNode>& host)
    {
        host_ = host;
    }

    RefPtr<FrameNode> GetHost() const
    {
        return host_.Upgrade();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RenderNodeFlag, int32_t, PROPERTY_UPDATE_RENDER);
};
}

#endif
