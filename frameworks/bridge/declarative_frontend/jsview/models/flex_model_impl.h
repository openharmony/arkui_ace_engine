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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_FLEX_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_FLEX_MODEL_IMPL_H

#include "core/components_ng/pattern/flex/flex_model.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
namespace OHOS::Ace::Framework {

class FlexModelImpl : public FlexModel {
public:
    void CreateFlexRow() override;

    void CreateWrap() override;

    void SetDirection(FlexDirection direction) override;
    void SetWrapDirection(WrapDirection direction) override;

    void SetMainAxisAlign(FlexAlign flexAlign) override;
    void SetWrapMainAlignment(WrapAlignment value) override;

    void SetCrossAxisAlign(FlexAlign flexAlign) override;
    void SetWrapCrossAlignment(WrapAlignment value) override;

    void SetAlignItems(int32_t value) override;

    void SetWrapAlignment(WrapAlignment value) override;

    void SetFlexWidth() override;
    void SetFlexHeight() override;
    void SetHasHeight() override;
    void SetHasWidth() override;

    void SetJustifyContent(int32_t value) override;
    void SetAlignContent(int32_t value) override;
    void SetMainSpace(const std::optional<Dimension>& space) override {};
    void SetCrossSpace(const std::optional<Dimension>& space) override {};
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_FLEX_MODEL_IMPL_H
