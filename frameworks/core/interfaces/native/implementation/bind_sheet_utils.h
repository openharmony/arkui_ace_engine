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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_BIND_SHEET_UTILS_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_BIND_SHEET_UTILS_H
#include <algorithm>
#include <variant>

#include "base/utils/system_properties.h"
#include "base/utils/time_util.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/pattern/counter/counter_node.h"
#include "core/components_ng/pattern/view_context/view_context_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/implementation/transition_effect_peer_impl.h"
#include "base/log/log_wrapper.h"

namespace OHOS::Ace::NG {
class BindSheetUtil {
public:
    struct SheetCallbacks {
        std::function<void()> onAppear;
        std::function<void()> onDisappear;
        std::function<void()> onWillAppear;
        std::function<void()> onWillDisappear;
        std::function<void()> shouldDismiss;
        std::function<void(const int32_t)> onWillDismiss;
        std::function<void(const float)> onHeightDidChange;
        std::function<void(const float)> onDetentsDidChange;
        std::function<void(const float)> onWidthDidChange;
        std::function<void(const float)> onTypeDidChange;
        std::function<void()> titleBuilder;
        std::function<void()> sheetSpringBack;
    };

    static void ParseLifecycleCallbacks(SheetCallbacks& callbacks, const Ark_SheetOptions& sheetOptions);
    static void ParseFuntionalCallbacks(SheetCallbacks& callbacks, const Ark_SheetOptions& sheetOptions);
    static void ParseSheetParams(SheetStyle& sheetStyle, const Ark_SheetOptions& sheetOptions);
    static void ParseContentCoverCallbacks(WeakPtr<FrameNode> weakNode, const Ark_ContentCoverOptions& options,
        std::function<void()>& onShowCallback, std::function<void()>& onDismissCallback,
        std::function<void()>& onWillShowCallback, std::function<void()>& onWillDismissCallback,
        std::function<void(const int32_t& info)>& onWillDismissFunc);
};

} // namespace OHOS::Ace::NG
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_BIND_SHEET_UTILS_H