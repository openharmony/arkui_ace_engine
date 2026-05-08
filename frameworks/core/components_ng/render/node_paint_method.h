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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_NODE_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_NODE_PAINT_METHOD_H

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/render/paint_wrapper.h"
namespace OHOS::Ace::NG {
class Modifier;
class NodePaintMethod : public virtual AceType {
    DECLARE_ACE_TYPE(NodePaintMethod, AceType);

public:
    NodePaintMethod() = default;
    ~NodePaintMethod() override = default;

    virtual CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper)
    {
        return nullptr;
    }

    virtual CanvasDrawFunction GetForegroundDrawFunction(PaintWrapper* paintWrapper)
    {
        return nullptr;
    }

    virtual CanvasDrawFunction GetOverlayDrawFunction(PaintWrapper* paintWrapper)
    {
        return nullptr;
    }

    virtual RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper)
    {
        return nullptr;
    }

    virtual RefPtr<Modifier> GetOverlayModifier(PaintWrapper* paintWrapper)
    {
        return nullptr;
    }

    virtual RefPtr<Modifier> GetForegroundModifier(PaintWrapper* paintWrapper)
    {
        return nullptr;
    }

    virtual void UpdateContentModifier(PaintWrapper* paintWrapper) {}

    virtual void UpdateForegroundModifier(PaintWrapper* paintWrapper) {}

    virtual void UpdateOverlayModifier(PaintWrapper* paintWrapper) {}
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_NODE_PAINT_METHOD_H
