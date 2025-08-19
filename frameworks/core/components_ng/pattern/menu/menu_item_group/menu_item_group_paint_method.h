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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_PAINT_METHOD_H

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_paint_property.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
struct GroupDividerInfo {
    float strokeWidth = 0.0f;
    float startMargin = 0.0f;
    float endMargin = 0.0f;
    Color color = Color::TRANSPARENT;
    float width = 0.0f;
    float topMargin = 0.0f;
};
class ACE_EXPORT MenuItemGroupPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(MenuItemGroupPaintMethod, NodePaintMethod);
public:
    MenuItemGroupPaintMethod() = default;
    ~MenuItemGroupPaintMethod() override = default;

    CanvasDrawFunction GetOverlayDrawFunction(PaintWrapper* paintWrapper) override;

private:
    void PaintDivider(RSCanvas& canvas, PaintWrapper* paintWrapper, GroupDividerInfo info);
    GroupDividerInfo PreparePaintData(RefPtr<PipelineBase>& pipeline,
        RefPtr<MenuItemGroupPaintProperty>& props, PaintWrapper* paintWrapper);

    ACE_DISALLOW_COPY_AND_MOVE(MenuItemGroupPaintMethod);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_PAINT_METHOD_H