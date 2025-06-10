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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SAVE_BUTTON_SAVE_BUTTON_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SAVE_BUTTON_SAVE_BUTTON_MODEL_NG_H

#include "core/components_ng/pattern/security_component/save_button/save_button_common.h"
#include "core/components_ng/pattern/security_component/security_component_model_ng.h"

namespace OHOS::Ace::NG {
struct SaveButtonStyle {
    inline static const auto DEFAULT_ICON = SaveButtonIconStyle::ICON_FULL_FILLED;
    inline static const auto DEFAULT_TEXT = SaveButtonSaveDescription::DOWNLOAD;
    inline static const auto DEFAULT_BACKGROUND_TYPE = ButtonType::CAPSULE;

    SaveButtonStyle()
    {
        text = SaveButtonStyle::DEFAULT_TEXT;
        icon = SaveButtonStyle::DEFAULT_ICON;
        backgroundType = SaveButtonStyle::DEFAULT_BACKGROUND_TYPE;
    }

    std::optional<SaveButtonIconStyle> icon;
    std::optional<SaveButtonSaveDescription> text;
    std::optional<ButtonType> backgroundType;
};
class ACE_FORCE_EXPORT SaveButtonModelNG : public SecurityComponentModelNG {
public:
    static SaveButtonModelNG* GetInstance();
    void Create(int32_t text, int32_t icon,
        int32_t backgroundType, bool isArkuiComponent) override;
    virtual bool GetIconResource(int32_t iconStyle, InternalResource::ResourceId& id) override;
    virtual bool GetTextResource(int32_t textStyle, std::string& text) override;
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static bool InitSaveButton(FrameNode* frameNode,
        const SaveButtonStyle& style, bool isArkuiComponent);
private:
    static std::unique_ptr<SaveButtonModelNG> instance_;
    static std::mutex mutex_;

    static bool GetIconResourceStatic(int32_t iconStyle, InternalResource::ResourceId& id);
    static bool GetTextResourceStatic(int32_t textStyle, std::string& text);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SAVE_BUTTON_SAVE_BUTTON_MODEL_NG_H
