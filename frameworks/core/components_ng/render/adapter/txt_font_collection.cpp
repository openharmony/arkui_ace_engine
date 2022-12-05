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

#include "core/components_ng/render/adapter/txt_font_collection.h"

#ifdef NG_BUILD
#include "ace_shell/shell/common/window_manager.h"
#else
#include "flutter/lib/ui/text/font_collection.h"
#include "flutter/lib/ui/ui_dart_state.h"
#include "flutter/lib/ui/window/window.h"
#endif

#include "base/utils/utils.h"
#include "core/common/container.h"

namespace OHOS::Ace::NG {

RefPtr<FontCollection> FontCollection::Current()
{
#ifdef NG_BUILD
    int32_t id = Container::CurrentId();
    auto window = flutter::ace::WindowManager::GetWindow(id);
    CHECK_NULL_RETURN(window, nullptr);
    return AceType::MakeRefPtr<TxtFontCollection>(window->GetFontCollection());
#else
    CHECK_NULL_RETURN(flutter::UIDartState::Current(), nullptr);
    auto window = flutter::UIDartState::Current()->window();
    CHECK_NULL_RETURN(window, nullptr);
    CHECK_NULL_RETURN(window->client(), nullptr);
    auto& fontCollection = window->client()->GetFontCollection();
    return AceType::MakeRefPtr<TxtFontCollection>(fontCollection.GetFontCollection());
#endif
}

TxtFontCollection::TxtFontCollection(const std::shared_ptr<txt::FontCollection>& fontCollection)
    : collection_(fontCollection)
{}

} // namespace OHOS::Ace::NG
