/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "arkoala_api_generated.h"
#include <unordered_map>
#include "base/log/log_wrapper.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/common/container.h"
#include "core/common/ace_application_info.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/implementation/text_menu_item_id_peer.h"

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<TextMenuShowMode>& dst, const Ark_TextMenuShowMode& src)
{
    switch (src) {
        case ARK_TEXT_MENU_SHOW_MODE_DEFAULT: dst = TextMenuShowMode::DEFAULT; break;
        case ARK_TEXT_MENU_SHOW_MODE_PREFER_WINDOW: dst = TextMenuShowMode::PREFER_WINDOW; break;
        default: {
            dst = TextMenuShowMode::DEFAULT;
        }
    }
}
template<>
void AssignCast(std::optional<NG::TextMenuOptions>& dst, const Ark_TextMenuOptions& src)
{
    auto textMenuShowMode = Converter::OptConvert<NG::TextMenuShowMode>(src.showMode);
    if (textMenuShowMode) {
        NG::TextMenuOptions textMenuOptions;
        textMenuOptions.showMode = *textMenuShowMode;
        dst = textMenuOptions;
    }
}
} /* namespace OHOS::Ace::NG::Converter */

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GlobalScopeUicontextTextMenuAccessor {
void SetMenuOptionsImpl(const Ark_TextMenuOptions* options)
{
    TAG_LOGI(AceLogTag::ACE_SELECT_OVERLAY, "TextMenu SetMenuOptions enter");
    CHECK_NULL_VOID(options);
    NG::TextMenuOptions textMenuOptions = { .showMode = NG::TextMenuShowMode::DEFAULT };
    auto optTextMenuOptions = Converter::OptConvert<NG::TextMenuOptions>(*options);
    if (!optTextMenuOptions) {
        optTextMenuOptions = textMenuOptions;
    }
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    auto selectOverlayManager = pipelineContext->GetSelectOverlayManager();
    if (selectOverlayManager) {
        selectOverlayManager->SetTextMenuOptions(*optTextMenuOptions);
    }
}
void DisableSystemServiceMenuItemsImpl(Ark_Boolean disable)
{
    TAG_LOGI(AceLogTag::ACE_SELECT_OVERLAY, "TextMenu DisableSystemServiceMenuItemsImpl enter");
    auto disableAll = Converter::Convert<bool>(disable);
    auto textMenuInfo = AceApplicationInfo::GetInstance().GetTextMenuInfo();
    auto isPrevDisableAll = (textMenuInfo.disableFlags & NG::DISABLE_ALL_FLAG) == NG::DISABLE_ALL_FLAG;
    if (disableAll) {
        AceApplicationInfo::GetInstance().AddTextMenuDisableFlag(NG::DISABLE_ALL_FLAG);
    } else {
        AceApplicationInfo::GetInstance().SetTextMenuDisableFlags(~NG::DISABLE_ALL_FLAG);
    }
    if (isPrevDisableAll != disableAll && textMenuInfo.menuOnChangeCallback) {
        if (!textMenuInfo.menuOnChangeCallback()) {
            AceApplicationInfo::GetInstance().SetTextMenuOnChangeCallback(nullptr);
        }
    }
}
SystemServiceMenuDisableFlag GetDisableFlag(const std::string& id)
{
    static std::unordered_map<std::string, NG::SystemServiceMenuDisableFlag> disableFlagsMap = {
        { NG::OH_DEFAULT_TRANSLATE, NG::DISABLE_TRANSLATE_FLAG },
        { NG::OH_DEFAULT_SEARCH, NG::DISABLE_SEARCH_FLAG },
        { NG::OH_DEFAULT_SHARE, NG::DISABLE_SHARE_FLAG },
        { NG::OH_DEFAULT_CAMERA_INPUT, NG::DISABLE_CAMERA_INPUT_FLAG },
        { NG::OH_DEFAULT_AI_WRITE, NG::DISABLE_AI_WRITER_FLAG },
        { NG::OH_DEFAULT_COLLABORATION_SERVICE, NG::DISABLE_COLLABORATION_SERVICE_FLAG },
        { NG::OH_DEFAULT_AI_MENU_URL, NG::DISABLE_AI_MENU_URL_FLAG },
        { NG::OH_DEFAULT_AI_MENU_PHONE, NG::DISABLE_AI_MENU_PHONE_FLAG },
        { NG::OH_DEFAULT_AI_MENU_EMAIL, NG::DISABLE_AI_MENU_EMAIL_FLAG },
        { NG::OH_DEFAULT_AI_MENU_ADDRESS, NG::DISABLE_AI_MENU_ADDRESS_FLAG },
        { NG::OH_DEFAULT_AI_MENU_DATETIME, NG::DISABLE_AI_MENU_DATETIME_FLAG },
        { NG::OH_DEFAULT_ASK_CELIA, NG::DISABLE_ASK_CELIA_FLAG },
        { NG::OH_DEFAULT_AUTO_FILL, NG::DISABLE_AUTO_FILL_FLAG },
    };
    return disableFlagsMap.find(id) == disableFlagsMap.end() ? NG::DISABLE_NORMAL_FLAG : disableFlagsMap[id];
}
void DisableMenuItemsImpl(const Array_TextMenuItemId* items)
{
    TAG_LOGI(AceLogTag::ACE_SELECT_OVERLAY, "TextMenu DisableMenuItemsImpl enter");
    CHECK_NULL_VOID(items);
    auto textMenuInfo = AceApplicationInfo::GetInstance().GetTextMenuInfo();
    auto oldFlags = textMenuInfo.disableFlags;
    AceApplicationInfo::GetInstance().SetTextMenuDisableFlags(NG::DISABLE_ALL_FLAG);
    for (Ark_Int32 i = 0; i < items->length; i++) {
        auto peer = items->array[i];
        if (peer && peer->id) {
            AceApplicationInfo::GetInstance().AddTextMenuDisableFlag(GetDisableFlag(peer->id.value()));
        }
    }
    if (oldFlags != AceApplicationInfo::GetInstance().GetTextMenuInfo().disableFlags &&
        textMenuInfo.menuOnChangeCallback) {
        if (!textMenuInfo.menuOnChangeCallback()) {
            AceApplicationInfo::GetInstance().SetTextMenuOnChangeCallback(nullptr);
        }
    }
}
} // GlobalScopeUicontextTextMenuAccessor
const GENERATED_ArkUIGlobalScopeUicontextTextMenuAccessor* GetGlobalScopeUicontextTextMenuAccessor()
{
    static const GENERATED_ArkUIGlobalScopeUicontextTextMenuAccessor GlobalScopeUicontextTextMenuAccessorImpl {
        GlobalScopeUicontextTextMenuAccessor::SetMenuOptionsImpl,
        GlobalScopeUicontextTextMenuAccessor::DisableSystemServiceMenuItemsImpl,
        GlobalScopeUicontextTextMenuAccessor::DisableMenuItemsImpl,
    };
    return &GlobalScopeUicontextTextMenuAccessorImpl;
}

}
