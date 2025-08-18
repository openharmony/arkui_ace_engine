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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MENU_ITEM_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MENU_ITEM_PAINT_METHOD_H

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/placement.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_paint_property.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {
struct ItemDividerInfo {
    float strokeWidth = 0.0f;
    float startMargin = 0.0f;
    float endMargin = 0.0f;
    float width = 0.0f;
    float topMargin = 0.0f;
    Color color = Color::TRANSPARENT;
};
class ACE_EXPORT MenuItemPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(MenuItemPaintMethod, NodePaintMethod);
public:
    MenuItemPaintMethod(bool isOption = false) : isOption_(isOption) {}
    ~MenuItemPaintMethod() override = default;

    CanvasDrawFunction GetOverlayDrawFunction(PaintWrapper* paintWrapper) override;

private:
    void DrawPathWithBrush(RSCanvas& canvas, const RSPath& path, const Color& color);
    void HandleMenuItem(PaintWrapper* paintWrapper, const RefPtr<MenuItemPaintProperty>& props,
        const RefPtr<SelectTheme>& selectTheme, RSPath& path, RSCanvas& canvas);
    void HandleOption(PaintWrapper* paintWrapper, const RefPtr<MenuItemPaintProperty>& props,
        const RefPtr<SelectTheme>& selectTheme, RSPath& path, RSCanvas& canvas);
    void PaintCustomDivider(SizeF optionSize, float horInterval, float iconHorInterval,
        PaintWrapper* paintWrapper, RSPath& path);

    bool isOption_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(MenuItemPaintMethod);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MENU_ITEM_PAINT_METHOD_H