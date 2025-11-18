/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef OHOS_ANI_ACE_SHAPE_PEER_H
#define OHOS_ANI_ACE_SHAPE_PEER_H

#include "base/memory/referenced.h"
#include "base/geometry/shape.h"

namespace OHOS::Ace {
struct CirclePeer {
    OHOS::Ace::RefPtr<OHOS::Ace::Circle> circleShape;
};
struct EllipsePeer {
    OHOS::Ace::RefPtr<OHOS::Ace::Ellipse> ellipseShape;
};
struct PathPeer {
    OHOS::Ace::RefPtr<OHOS::Ace::Path> pathShape;
};
struct RectPeer {
    OHOS::Ace::RefPtr<OHOS::Ace::ShapeRect> rectShape;
};
struct BasicPeer {
    OHOS::Ace::RefPtr<OHOS::Ace::BasicShape> basicShape;
};
} // namespace OHOS::Ace
#endif // OHOS_ANI_ACE_SHAPE_PEER_H
