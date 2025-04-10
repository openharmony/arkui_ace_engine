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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_SHAPE_CLIP_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_SHAPE_CLIP_PEER_IMPL_H

#include "base/geometry/shape.h"

using OHOS::Ace::AceType;
using OHOS::Ace::Dimension;
using OHOS::Ace::DimensionOffset;
using OHOS::Ace::RefPtr;

const int32_t DEFAULT_COLOR = 0xFF000000;
const float DEFAULT_WIDTH = 0.0f;

struct ShapeClipPeer {
    struct Rect {
        Dimension width;
        Dimension height;
        DimensionOffset position;
    };
    struct RoundRect {
        Rect rect;
        OHOS::Ace::Corner corners;
    };
    struct Circle {
        DimensionOffset position;
        Dimension radius;
    };

    ShapeClipPeer() = default;
    virtual ~ShapeClipPeer() = default;

    void SetRectShape(const Rect& src)
    {
        rect = MakeRefPtr(src);
        roundRect = nullptr;
        circle = nullptr;
        oval = nullptr;
        path = std::nullopt;
    }
    void SetRoundRectShape(const RoundRect& src)
    {
        roundRect = MakeRefPtr(src);
        rect = nullptr;
        circle = nullptr;
        oval = nullptr;
        path = std::nullopt;
    }
    void SetCircleShape(const Circle& src)
    {
        circle = MakeRefPtr(src);
        rect = nullptr;
        roundRect = nullptr;
        oval = nullptr;
        path = std::nullopt;
    }
    void SetOvalShape(const Rect& src)
    {
        oval = MakeRefPtr(src);
        rect = nullptr;
        roundRect = nullptr;
        circle = nullptr;
        path = std::nullopt;
    }
    void SetCommandPath(const std::string& value)
    {
        path = value;
        rect = nullptr;
        roundRect = nullptr;
        circle = nullptr;
        oval = nullptr;
    }

private:
    RefPtr<OHOS::Ace::ShapeRect> MakeRefPtr(const Rect& src)
    {
        auto dst = AceType::MakeRefPtr<OHOS::Ace::ShapeRect>();
        dst->SetWidth(src.width);
        dst->SetHeight(src.height);
        dst->SetPosition(src.position);
        return dst;
    }
    RefPtr<OHOS::Ace::ShapeRect> MakeRefPtr(const RoundRect& src)
    {
        auto dst = MakeRefPtr(src.rect);
        dst->SetTopLeftRadius(src.corners.topLeftRadius);
        dst->SetTopRightRadius(src.corners.topRightRadius);
        dst->SetBottomLeftRadius(src.corners.bottomLeftRadius);
        dst->SetBottomRightRadius(src.corners.bottomRightRadius);
        return dst;
    }
    RefPtr<OHOS::Ace::Circle> MakeRefPtr(const Circle& src)
    {
        auto dst = AceType::MakeRefPtr<OHOS::Ace::Circle>();
        dst->SetPosition(src.position);
        dst->SetRadius(Dimension(src.radius));
        return dst;
    }

public:
    RefPtr<OHOS::Ace::ShapeRect> rect = nullptr;
    RefPtr<OHOS::Ace::ShapeRect> roundRect = nullptr;
    RefPtr<OHOS::Ace::Circle> circle = nullptr;
    RefPtr<OHOS::Ace::ShapeRect> oval = nullptr;
    std::optional<std::string> path = std::nullopt;
    uint32_t fillColor = DEFAULT_COLOR;
    uint32_t strokeColor = DEFAULT_COLOR;
    float strokeWidth = DEFAULT_WIDTH;
};
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_SHAPE_CLIP_PEER_IMPL_H