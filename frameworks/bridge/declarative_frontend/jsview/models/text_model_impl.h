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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TEXT_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TEXT_MODEL_IMPL_H

#include <functional>
#include <string>

#include "core/components/text/text_component_v2.h"
#include "core/components_ng/pattern/text/text_model.h"

namespace OHOS::Ace::Framework {
class ACE_EXPORT TextModelImpl : public TextModel {
public:
    void Create(const std::string& content) override;
    void SetFontSize(const Dimension& value) override;
    void SetTextColor(const Color& value) override;
    void SetItalicFontStyle(Ace::FontStyle value) override;
    void SetFontWeight(FontWeight value) override;
    void SetFontFamily(const std::vector<std::string>& value) override;
    void SetTextAlign(TextAlign value) override;
    void SetTextOverflow(TextOverflow value) override;
    void SetMaxLines(uint32_t value) override;
    void SetLineHeight(const Dimension& value) override;
    void SetTextDecoration(TextDecoration value) override;
    void SetTextDecorationColor(const Color& value) override;
    void SetBaselineOffset(const Dimension& value) override;
    void SetTextCase(TextCase value) override;
    void SetLetterSpacing(const Dimension& value) override;
    void SetAdaptMinFontSize(const Dimension& value) override;
    void SetAdaptMaxFontSize(const Dimension& value) override;
    void OnSetHeight() override;
    void OnSetWidth() override;
    void OnSetAlign() override;
    void SetOnClick(std::function<void(const BaseEventInfo*)>&& click) override;
    void SetRemoteMessage(std::function<void()>&& event) override;
    void SetCopyOption(CopyOptions copyOption) override;

    void SetOnDragStartId(const OnDragFunc& onDragStartId) override;
    void SetOnDragEnterId(const OnDropFunc& onDragEnterId) override;
    void SetOnDragMoveId(const OnDropFunc& onDragMoveId) override;
    void SetOnDragLeaveId(const OnDropFunc& onDragLeaveId) override;
    void SetOnDropId(const OnDropFunc& onDropId) override;

private:
    static RefPtr<TextComponentV2> GetComponent();
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TEXT_MODEL_IMPL_H
