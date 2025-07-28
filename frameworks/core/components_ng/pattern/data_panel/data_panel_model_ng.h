/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_MODEL_NG_H

#include "core/components_ng/pattern/data_panel/data_panel_model.h"
#include "core/components_ng/base/common_configuration.h"

namespace OHOS::Ace::NG {
enum class DataPanelType {
    CIRCLE = 0,
    LINE = 1
};

class DataPanelConfiguration : public CommonConfiguration {
    public:
        DataPanelConfiguration(std::vector<double>& values, double maxValue, bool enabled)
            : CommonConfiguration(enabled), values_(values), maxValue_(maxValue)
        {}
        std::vector<double>& values_;
        double maxValue_;
};
using DataPanelMakeCallback =
    std::function<RefPtr<FrameNode>(const DataPanelConfiguration& dataPanelConfiguration)>;
class ACE_EXPORT DataPanelModelNG : public OHOS::Ace::DataPanelModel {
public:
    void Create(const std::vector<double>& values, double max, int32_t dataPanelType) override;
    void SetEffect(bool isCloseEffect) override;
    void SetValueColors(const std::vector<Gradient>& valueColors) override;
    void SetTrackBackground(const Color& trackBackgroundColor) override;
    void SetStrokeWidth(const Dimension& strokeWidth) override;
    void SetShadowOption(const DataPanelShadow& shadowOption) override;
    void CreateWithResourceObj(DataPanelResourceType colorType, const RefPtr<ResourceObject>& resObj) override;
    void SetValueColorsSetByUser(bool value) override;

    static RefPtr<FrameNode>CreateFrameNode(int32_t nodeId);
    static void SetValues(FrameNode* frameNode, const std::optional<std::vector<double>>& values);
    static void SetMax(FrameNode* frameNode, const std::optional<double>& max);
    static void SetType(FrameNode* frameNode, const std::optional<int32_t>& type);
    static void SetCloseEffect(FrameNode* frameNode, bool isClose);
    static void SetTrackBackground(FrameNode* frameNode, const Color& trackBackgroundColor);
    static void SetStrokeWidth(FrameNode* frameNode, const Dimension& strokeWidth);
    static void SetShadowOption(FrameNode* frameNode, const DataPanelShadow& shadowOption);
    static void SetValueColors(FrameNode* frameNode, const std::vector<Gradient>& valueColors);
    static void SetBuilderFunc(FrameNode* frameNode, NG::DataPanelMakeCallback&& jsMake);
    static void CreateWithResourceObj(FrameNode* frameNode, DataPanelResourceType colorType,
        const RefPtr<ResourceObject>& resObj);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_MODEL_NG_H