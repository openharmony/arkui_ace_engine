/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_AUTO_FILL_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_AUTO_FILL_CONTROLLER_H

#include <string>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "base/utils/utf_helper.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {

enum class AutoFillAnimationStatus { INIT, SHOW_ICON, TRANSLATION, HIDE_ICON };

enum class AutoFillContentLengthMode { INVALID, SHORT, MEDIUM, LONG, EXTRA_LONG };

class AutoFillController : public virtual AceType {
    DECLARE_ACE_TYPE(AutoFillController, AceType);

public:
    explicit AutoFillController(const WeakPtr<Pattern>& pattern) : pattern_(pattern) {}
    ~AutoFillController() override = default;
    void StartAutoFillAnimation(const std::function<void()>& onFinishCallback, const std::u16string& content);
    void ResetAutoFillAnimationStatus();

    const RefPtr<Paragraph>& GetAutoFillParagraph() const
    {
        return autoFillParagraph_;
    }

    AutoFillAnimationStatus GetAutoFillAnimationStatus() const
    {
        return autoFillAnimationStatus_;
    }

    void SetAutoFillAnimationStatus(AutoFillAnimationStatus status)
    {
        autoFillAnimationStatus_ = status;
    }

    const WeakPtr<FrameNode>& GetAutoFillIconNode() const
    {
        return autoFillIconNode_;
    }

    void SetAutoFillOriginTextColor(const Color& value)
    {
        autoFillOriginTextColor_ = value;
    }

    void SetAutoFillTextUtf16Value(const std::u16string& value)
    {
        autofillTextUtf16Value_ = value;
    }

    const std::u16string& GetAutoFillTextUtf16Value() const
    {
        return autofillTextUtf16Value_;
    }

    const RectF& GetAnimationTextRect() const
    {
        return animationTextRect_;
    }

private:
    void PlayAutoFillIconShowAnimation(const AutoFillContentLengthMode& mode);
    void PlayAutoFillDefaultCharAnimation(const AutoFillContentLengthMode& mode);
    void PlayAutoFillTranslationAnimation(const AutoFillContentLengthMode& mode);
    void PlayAutoFillIconHideAnimation(
        const std::function<void()>& onFinishCallback, const AutoFillContentLengthMode& mode);
    void PlayAutoFillTextScrollAnimation();
    bool InitAutoFillParagraph(const std::u16string& textContent);
    bool CreateAutoFillIcon();
    void ResetAutoFillIcon();
    AutoFillContentLengthMode GetAutoFillContentLengthMode();
    float GetSpringAnimationResponse(const AutoFillContentLengthMode& mode);
    float GetSpringAnimationDamping(const AutoFillContentLengthMode& mode);
    void UpdateAnimationTextRect();

    WeakPtr<Pattern> pattern_;
    RefPtr<Paragraph> autoFillParagraph_;
    AutoFillAnimationStatus autoFillAnimationStatus_ = AutoFillAnimationStatus::INIT;
    WeakPtr<FrameNode> autoFillIconNode_;
    std::u16string autofillTextUtf16Value_;
    float autoFillFirstCharOffset_ = 0.0f;
    Color autoFillOriginTextColor_;
    RectF animationTextRect_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_AUTO_FILL_CONTROLLER_H