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

#include "base/geometry/shape.h"
#include "core/interfaces/native/implementation/shape_mask_peer.h"

void BaseShapePeer::SetRectShape(const RefPtr<OHOS::Ace::ShapeRect>& value)
{
    ResetAll();
    rect = value;
}

void BaseShapePeer::SetRoundRectShape(const RefPtr<OHOS::Ace::ShapeRect>& value)
{
    ResetAll();
    roundRect = value;
}

void BaseShapePeer::SetCircleShape(const RefPtr<OHOS::Ace::Circle>& value)
{
    ResetAll();
    circle = value;
}

void BaseShapePeer::SetOvalShape(const RefPtr<OHOS::Ace::ShapeRect>& value)
{
    ResetAll();
    oval = value;
}

void BaseShapePeer::SetCommandPath(const std::string& value)
{
    ResetAll();
    path = value;
}

void BaseShapePeer::ResetAll()
{
    rect = nullptr;
    roundRect = nullptr;
    circle = nullptr;
    oval = nullptr;
    path = std::nullopt;
}

BaseShapePeer::~BaseShapePeer() = default;
