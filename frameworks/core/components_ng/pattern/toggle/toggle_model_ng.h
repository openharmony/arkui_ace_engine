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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TOGGLE_TOGGLE_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TOGGLE_TOGGLE_MODEL_NG_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/toggle/toggle_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ToggleModelNG : public OHOS::Ace::ToggleModel {
public:
    void Create(ToggleType toggleType, bool isOn) override;
    void SetSelectedColor(const std::optional<Color>& selectedColor) override;
    void SetSwitchPointColor(const Color& switchPointColor) override;
    void OnChange(ChangeEvent&& onChange) override;
    void SetWidth(const Dimension& width) override;
    void SetHeight(const Dimension& height) override;
    void SetBackgroundColor(const Color& color) override;
    bool IsToggle() override;
    void SetPadding(const NG::PaddingPropertyF& args, const NG::PaddingProperty& newArgs) override;
    void OnChangeEvent(ChangeEvent&& onChangeEvent) override;
    void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) override;

private:
    static void CreateCheckbox(int32_t nodeId);
    static void CreateSwitch(int32_t nodeId);
    static void CreateButton(int32_t nodeId);
    static void AddNewChild(const RefPtr<UINode>& parentFrame, int32_t nodeId, int32_t index);
    static int32_t RemoveNode(const RefPtr<FrameNode>& childFrameNode, int32_t nodeId);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TOGGLE_TOGGLE_MODEL_NG_H
