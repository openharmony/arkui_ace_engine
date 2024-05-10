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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_MODEL_NG_H

#include "core/components_ng/pattern/progress/progress_model.h"

namespace OHOS::Ace::NG {
using ProgressMakeCallback = std::function<RefPtr<FrameNode>(const ProgressConfiguration& config)>;

class ACE_EXPORT ProgressModelNG : public OHOS::Ace::ProgressModel {
public:
    void Create(double min, double value, double cachedValue, double max, NG::ProgressType type) override;
    void SetValue(double value) override;
    void SetColor(const Color& value) override;
    void SetBackgroundColor(const Color& value) override;
    void SetStrokeWidth(const Dimension& value) override;
    void SetScaleCount(int32_t value) override;
    void SetScaleWidth(const Dimension& value) override;
    void SetBorderColor(const Color& value) override;
    void SetBorderWidth(const Dimension& value) override;
    void SetFontSize(const Dimension& value) override;
    void SetFontColor(const Color& value) override;
    void SetText(const std::optional<std::string>& value) override;
    void SetItalicFontStyle(const Ace::FontStyle& value) override;
    void SetFontWeight(const FontWeight& value) override;
    void SetFontFamily(const std::vector<std::string>& value) override;
    void SetSweepingEffect(bool value) override;
    void SetGradientColor(const Gradient& value) override;
    void SetPaintShadow(bool value) override;
    void SetProgressStatus(ProgressStatus status) override;
    void SetShowText(bool value) override;
    void SetRingSweepingEffect(bool value) override;
    void SetLinearSweepingEffect(bool value) override;
    void SetSmoothEffect(bool value) override;
    void SetStrokeRadius(const Dimension& value) override;
    void ResetStrokeRadius() override;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId, double value, double max, NG::ProgressType type);
    static void SetValue(FrameNode* frameNode, double value);
    static void SetColor(FrameNode* frameNode, const Color& value);
    static void SetGradientColor(FrameNode* frameNode, const Gradient& value);
    static void SetSmoothEffect(FrameNode* frameNode, bool value);
    static void SetStrokeWidth(FrameNode* frameNode, const Dimension& value);
    static void SetLinearSweepingEffect(FrameNode* frameNode, bool value);
    static void SetRingSweepingEffect(FrameNode* frameNode, bool value);
    static void SetPaintShadow(FrameNode* frameNode, bool value);
    static void SetProgressStatus(FrameNode* frameNode, ProgressStatus status);
    static void SetScaleCount(FrameNode* frameNode, int32_t value);
    static void SetScaleWidth(FrameNode* frameNode, const Dimension& value);
    static void SetBorderWidth(FrameNode* frameNode, const Dimension& value);
    static void SetBorderColor(FrameNode* frameNode, const Color& value);
    static void SetSweepingEffect(FrameNode* frameNode, bool value);
    static void SetShowText(FrameNode* frameNode, bool value);
    static void SetText(FrameNode* frameNode, const std::optional<std::string>& value);
    static void SetFontColor(FrameNode* frameNode, const Color& value);
    static void SetFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetFontWeight(FrameNode* frameNode, const FontWeight& value);
    static void SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& value);
    static void SetItalicFontStyle(FrameNode* frameNode, const Ace::FontStyle& value);
    static void SetStrokeRadius(FrameNode* frameNode, const Dimension& value);
    static void ResetStrokeRadius(FrameNode* frameNode);
    static void SetBackgroundColor(FrameNode* frameNode, const Color& value);
    static void SetTotal(FrameNode* frameNode, double max);
    static void SetType(FrameNode* frameNode, NG::ProgressType type);
    static double GetValue(FrameNode* frameNode);
    static Color GetColor(FrameNode* frameNode);
    static double GetTotal(FrameNode* frameNode);
    static NG::ProgressType GetType(FrameNode* frameNode);
    static void SetBuilderFunc(FrameNode* frameNode, ProgressMakeCallback&& jsMake);
    static void ProgressInitialize(
        FrameNode* frameNode, double min, double value, double cachedValue, double max, NG::ProgressType type);

private:
    static void SetTextDefaultStyle(const RefPtr<FrameNode>& textNode, double value, double maxValue);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_MODEL_NG_H
