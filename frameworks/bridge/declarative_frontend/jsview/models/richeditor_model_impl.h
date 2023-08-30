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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_RICH_EDITOR_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_RICH_EDITOR_MODEL_IMPL_H

#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
namespace OHOS::Ace::Framework {
class ACE_EXPORT RichEditorModelImpl : public RichEditorModel {
    void Create() override;
    RefPtr<RichEditorControllerBase> GetRichEditorController() override;
    void SetOnReady(std::function<void()>&& func) override;
    void SetOnSelect(std::function<void(const BaseEventInfo*)>&& func) override;
    void SetAboutToIMEInput(std::function<bool(const NG::RichEditorInsertValue&)>&& func) override;
    void SetOnIMEInputComplete(std::function<void(const NG::RichEditorAbstractSpanResult&)>&& func) override;
    void SetAboutToDelete(std::function<bool(const NG::RichEditorDeleteValue&)>&& func) override;
    void SetOnDeleteComplete(std::function<void()>&& func) override;
    void SetCustomKeyboard(std::function<void()>&& func) override;
    void SetCopyOption(CopyOptions& copyOptions) override;
    void BindSelectionMenu(RichEditorType& editorType, ResponseType& responseType,
        std::function<void()>& buildFunc, SelectMenuParam& menuParam) override;
    void SetOnPaste(std::function<bool()>&& func) override;
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_RICH_EDITOR_MODEL_IMPL_H
