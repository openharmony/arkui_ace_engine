/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/callback_keeper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/dialog_common.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"

namespace OHOS::Ace::NG::GeneratedModifier {
void AddOnWillDismiss(DialogProperties& properties, Opt_Callback_DismissDialogAction_Void onWillDismiss)
{
    auto onWillDismissOpt = Converter::OptConvert<Callback_DismissDialogAction_Void>(onWillDismiss);
    CHECK_NULL_VOID(onWillDismissOpt);
    properties.onWillDismiss = [callback = CallbackHelper(onWillDismissOpt.value())](
        const int32_t& info, const int32_t& instanceId
    ) {
        const auto dismissReason = static_cast<BindSheetDismissReason>(info);
        const auto keeper = CallbackKeeper::Claim(std::move(ViewAbstract::DismissDialog));
        Ark_DismissDialogAction action {
            .dismiss = keeper.ArkValue(),
            .reason = Converter::ArkValue<Ark_DismissReason>(dismissReason)
        };
        callback.Invoke(action);
    };
}
} // namespace OHOS::Ace::NG::GeneratedModifier