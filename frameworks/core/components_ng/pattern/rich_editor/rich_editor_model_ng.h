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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_NG_H

#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_selection.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RichEditorModelNG : public OHOS::Ace::RichEditorModel {
public:
    void Create() override;
    RefPtr<RichEditorControllerBase> GetRichEditorController() override;
    void SetOnReady(std::function<void()>&& func) override;
    void SetOnSelect(std::function<void(const BaseEventInfo*)>&& func) override;
    void SetAboutToIMEInput(std::function<bool(const RichEditorInsertValue&)>&& func) override;
    void SetOnIMEInputComplete(std::function<void(const RichEditorAbstractSpanResult&)>&& func) override;
    void SetAboutToDelete(std::function<bool(const RichEditorDeleteValue&)>&& func) override;
    void SetOnDeleteComplete(std::function<void()>&& func) override;
    void SetCustomKeyboard(std::function<void()>&& func) override;
    void SetCopyOption(CopyOptions& copyOptions) override;
    void BindSelectionMenu(RichEditorType& editorType, ResponseType& responseType,
        std::function<void()>& buildFunc, SelectMenuParam& menuParam) override;
    void SetOnPaste(std::function<void(NG::TextCommonEvent&)>&& func) override;

private:
    void SetDraggable(bool draggable);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_NG_H
