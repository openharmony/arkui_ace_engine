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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PASTE_BUTTON_PASTE_BUTTON_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PASTE_BUTTON_PASTE_BUTTON_MODEL_NG_H

#include "core/components_ng/pattern/security_component/paste_button/paste_button_common.h"
#include "core/components_ng/pattern/security_component/security_component_model_ng.h"

namespace OHOS::Ace::NG {
struct PasteButtonStyle {
    inline static const auto DEFAULT_ICON = PasteButtonIconStyle::ICON_LINE;
    inline static const auto DEFAULT_TEXT = PasteButtonPasteDescription::PASTE;
    inline static const auto DEFAULT_BACKGROUND_TYPE = ButtonType::CAPSULE;

    PasteButtonStyle()
    {
        icon = PasteButtonStyle::DEFAULT_ICON;
        text = PasteButtonStyle::DEFAULT_TEXT;
        backgroundType = PasteButtonStyle::DEFAULT_BACKGROUND_TYPE;
    }

    std::optional<PasteButtonPasteDescription> text;
    std::optional<PasteButtonIconStyle> icon;
    std::optional<ButtonType> backgroundType;
};
class ACE_FORCE_EXPORT PasteButtonModelNG : public SecurityComponentModelNG {
public:
    static PasteButtonModelNG* GetInstance();
    void Create(int32_t text, int32_t icon,
        int32_t backgroundType, bool isArkuiComponent) override;
    RefPtr<FrameNode> CreateNode(int32_t text, int32_t icon,
        int32_t backgroundType, bool isArkuiComponent, uint32_t symbolIcon = -1);
    virtual bool GetIconResource(int32_t iconStyle, InternalResource::ResourceId& id) override;
    virtual bool GetTextResource(int32_t textStyle, std::string& text) override;
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static bool InitPasteButton(FrameNode* frameNode, const PasteButtonStyle& style, bool isArkuiComponent);
private:
    static std::unique_ptr<PasteButtonModelNG> instance_;
    static std::mutex mutex_;

    static bool GetIconResourceStatic(int32_t iconStyle, InternalResource::ResourceId& id);
    static bool GetTextResourceStatic(int32_t textStyle, std::string& text);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PASTE_BUTTON_PASTE_BUTTON_MODEL_NG_H
