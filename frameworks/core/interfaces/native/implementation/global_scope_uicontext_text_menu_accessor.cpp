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
#include "base/log/log_wrapper.h"
#include "core/common/container.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"

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
} // GlobalScopeUicontextTextMenuAccessor
const GENERATED_ArkUIGlobalScopeUicontextTextMenuAccessor* GetGlobalScopeUicontextTextMenuAccessor()
{
    static const GENERATED_ArkUIGlobalScopeUicontextTextMenuAccessor GlobalScopeUicontextTextMenuAccessorImpl {
        GlobalScopeUicontextTextMenuAccessor::SetMenuOptionsImpl,
    };
    return &GlobalScopeUicontextTextMenuAccessorImpl;
}

}
