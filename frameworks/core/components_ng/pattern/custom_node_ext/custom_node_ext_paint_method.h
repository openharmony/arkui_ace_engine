/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_PAINT_METHOD_H

#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_modifier.h"

namespace OHOS::Ace::NG {

class CustomNodeExtPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(CustomNodeExtPaintMethod, NodePaintMethod);
public:
    explicit CustomNodeExtPaintMethod(const RefPtr<CustomNodeExtContentModifier>& contentModifier,
        const RefPtr<CustomNodeExtForegroundModifier>& foregroundModifier,
        const RefPtr<CustomNodeExtOverlayModifier>& overlayModifier)
        : contentModifier_(contentModifier), foregroundModifier_(foregroundModifier), overlayModifier_(overlayModifier)
    {}

    ~CustomNodeExtPaintMethod() override = default;
    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        return contentModifier_;
    }

    RefPtr<Modifier> GetForegroundModifier(PaintWrapper* paintWrapper) override
    {
        return foregroundModifier_;
    }

    RefPtr<Modifier> GetOverlayModifier(PaintWrapper* paintWrapper) override
    {
        return overlayModifier_;
    }
private:
    RefPtr<CustomNodeExtContentModifier> contentModifier_;
    RefPtr<CustomNodeExtForegroundModifier> foregroundModifier_;
    RefPtr<CustomNodeExtOverlayModifier> overlayModifier_;
};
}
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_PAINT_METHOD_H