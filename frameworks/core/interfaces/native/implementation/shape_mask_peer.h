/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_SHAPE_MASK_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_SHAPE_MASK_PEER_IMPL_H

#include "base/geometry/shape.h"

using OHOS::Ace::AceType;
using OHOS::Ace::Dimension;
using OHOS::Ace::DimensionOffset;
using OHOS::Ace::RefPtr;

const int32_t DEFAULT_COLOR = 0xFF000000;
const float DEFAULT_WIDTH = 0.0f;

struct BaseShapePeer {
    BaseShapePeer() = default;
    explicit BaseShapePeer(const RefPtr<OHOS::Ace::BasicShape>& src) : shape(src) {}
    virtual ~BaseShapePeer() = default;

    RefPtr<OHOS::Ace::BasicShape> shape = nullptr;
};

struct ShapeMaskPeer final : public BaseShapePeer {
protected:
    ShapeMaskPeer() = default;
    explicit ShapeMaskPeer(const RefPtr<OHOS::Ace::BasicShape>& src) : BaseShapePeer(src) {}
    ~ShapeMaskPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;

public:
    void SetBasicProperties()
    {
        shape->SetColor(OHOS::Ace::Color(fillColor));
        shape->SetStrokeColor(strokeColor);
        shape->SetStrokeWidth(strokeWidth);
    }

    uint32_t fillColor = DEFAULT_COLOR;
    uint32_t strokeColor = DEFAULT_COLOR;
    float strokeWidth = DEFAULT_WIDTH;
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_SHAPE_MASK_PEER_IMPL_H
