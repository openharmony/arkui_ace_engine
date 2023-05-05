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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SLIDING_PANEL_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SLIDING_PANEL_MODEL_IMPL_H

#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "core/components_ng/pattern/panel/sliding_panel_model.h"

namespace OHOS::Ace::Framework {
class SlidingPanelModelImpl : public OHOS::Ace::SlidingPanelModel {
public:
    void Create(bool isShow) override;
    void SetPanelType(PanelType type) override;
    void SetPanelMode(PanelMode mode) override;
    void SetHasDragBar(bool hasDragBar) override;
    void SetMiniHeight(const Dimension& miniHeight) override;
    void SetHalfHeight(const Dimension& halfHeight) override;
    void SetFullHeight(const Dimension& fullHeight) override;
    void SetIsShow(bool isShow) override;
    void SetBackgroundMask(const Color& backgroundMask) override;
    void SetBackgroundColor(const Color& backgroundColor) override;
    void SetOnSizeChange(std::function<void(const BaseEventInfo*)>&& changeEvent) override;
    void SetOnHeightChange(std::function<void(const float)>&& onHeightChange) override;
    void Pop() override;
    void SetBorderColor(const Color& borderColor) override;
    void SetBorderWidth(const Dimension& borderWidth) override;
    void SetBorderStyle(const BorderStyle& borderStyle) override;
    void SetBorder(const BorderStyle& borderStyle, const Dimension& borderWidth) override;
    void SetModeChangeEvent(std::function<void(const BaseEventInfo*)>&& modeChangeEvent) override {};

protected:
    static RefPtr<BoxComponent> GetPanelBox();
    static RefPtr<Decoration> GetPanelDecoration();
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SLIDING_PANEL_MODEL_IMPL_H
