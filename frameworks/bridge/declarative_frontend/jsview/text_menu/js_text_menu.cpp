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

#include "frameworks/bridge/declarative_frontend/jsview/text_menu/js_text_menu.h"

#include "base/log/log_wrapper.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/common/container.h"

namespace OHOS::Ace::Framework {

void JSTextMenu::SetMenuOptions(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_SELECT_OVERLAY, "TextMenu SetMenuOptions enter");
    auto scopedDelegate = EngineHelper::GetCurrentDelegateSafely();
    if (!scopedDelegate) {
        // this case usually means there is no foreground container, need to figure out the reason.
        TAG_LOGE(AceLogTag::ACE_SELECT_OVERLAY, "scopedDelegate is null, please check");
        return;
    }
    if (info.Length() < 1 || !info[0]->IsObject()) {
        info.SetReturnValue(info.This());
        return;
    }
    NG::TextMenuOptions textMenuOptions;
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto showModeJsVal = paramObject->GetProperty("showMode");
    if (showModeJsVal->IsNull() || showModeJsVal->IsUndefined() || !showModeJsVal->IsNumber()) {
        info.SetReturnValue(info.This());
        return;
    }
    textMenuOptions.showMode = NG::CastToTextMenuShowMode(showModeJsVal->ToNumber<int32_t>());
    auto container = Container::CurrentSafely();
    if (!container) {
        info.SetReturnValue(info.This());
        return;
    }
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    if (!pipelineContext) {
        info.SetReturnValue(info.This());
        return;
    }
    auto selectOverlayManager = pipelineContext->GetSelectOverlayManager();
    if (selectOverlayManager) {
        selectOverlayManager->SetTextMenuOptions(textMenuOptions);
    }
    info.SetReturnValue(info.This());
}

void JSTextMenu::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextMenu>::Declare("TextMenu");
    JSClass<JSTextMenu>::StaticMethod("setMenuOptions", &JSTextMenu::SetMenuOptions);
    JSClass<JSTextMenu>::InheritAndBind<JSViewAbstract>(globalObj);
}

} // namespace OHOS::Ace::Framework