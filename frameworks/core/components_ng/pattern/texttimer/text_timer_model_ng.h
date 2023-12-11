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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_MODEL_NG_H

#include "core/components_ng/pattern/texttimer/text_timer_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TextTimerModelNG : public OHOS::Ace::TextTimerModel {
public:
    RefPtr<TextTimerController> Create() override;
    void SetFormat(const std::string& format) override;
    void SetIsCountDown(bool isCountDown) override;
    void SetInputCount(double count) override;
    void SetOnTimer(std::function<void(const std::string, const std::string)>&& onChange) override;
    void SetFontSize(const Dimension& value) override;
    void SetTextColor(const Color& value) override;
    void SetTextShadow(const std::vector<Shadow>& value) override;
    void SetItalicFontStyle(Ace::FontStyle value) override;
    void SetFontWeight(FontWeight value) override;
    void SetFontFamily(const std::vector<std::string>& value) override;
    static void SetFontColor(FrameNode* frameNode, const Color& value);
    static void SetFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetFontStyle(FrameNode* frameNode, Ace::FontStyle value);
    static void SetFontWeight(FrameNode* frameNode, FontWeight value);
    static void SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& value);
    static void SetFormat(FrameNode* frameNode, const std::string& format);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_MODEL_NG_H
