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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_MODEL_H

#include <functional>
#include <memory>
#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/components/box/drag_drop_event.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/text/text_styles.h"

namespace OHOS::Ace {
class ACE_EXPORT TextModel {
public:
    static TextModel* GetInstance();
    virtual ~TextModel() = default;

    virtual void Create(const std::string& content) = 0;
    virtual void SetFontSize(const Dimension& value) = 0;
    virtual void SetTextColor(const Color& value) = 0;
    virtual void SetItalicFontStyle(Ace::FontStyle value) = 0;
    virtual void SetFontWeight(FontWeight value) = 0;
    virtual void SetFontFamily(const std::vector<std::string>& value) = 0;
    virtual void SetTextAlign(TextAlign value) = 0;
    virtual void SetTextOverflow(TextOverflow value) = 0;
    virtual void SetMaxLines(uint32_t value) = 0;
    virtual void SetLineHeight(const Dimension& value) = 0;
    virtual void SetTextDecoration(TextDecoration value) = 0;
    virtual void SetTextDecorationColor(const Color& value) = 0;
    virtual void SetBaselineOffset(const Dimension& value) = 0;
    virtual void SetTextCase(TextCase value) = 0;
    virtual void SetLetterSpacing(const Dimension& value) = 0;
    virtual void SetAdaptMinFontSize(const Dimension& value) = 0;
    virtual void SetAdaptMaxFontSize(const Dimension& value) = 0;
    virtual void OnSetWidth() {};
    virtual void OnSetHeight() {};
    virtual void OnSetAlign() {};
    virtual void SetOnClick(std::function<void(const BaseEventInfo* info)>&& click) = 0;
    virtual void SetRemoteMessage(std::function<void()>&& click) = 0;
    virtual void SetCopyOption(CopyOptions copyOption) = 0;

    // TODO: OnDragFunc has component defines.
    virtual void SetOnDragStartId(const OnDragFunc& onDragStartId) = 0;
    virtual void SetOnDragEnterId(const OnDropFunc& onDragEnterId) = 0;
    virtual void SetOnDragMoveId(const OnDropFunc& onDragMoveId) = 0;
    virtual void SetOnDragLeaveId(const OnDropFunc& onDragLeaveId) = 0;
    virtual void SetOnDropId(const OnDropFunc& onDropId) = 0;

private:
    static std::unique_ptr<TextModel> instance_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_MODEL_H
