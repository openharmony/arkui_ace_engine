/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVIGATION_UTILS_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVIGATION_UTILS_H

#include <vector>

#include "frameworks/base/memory/ace_type.h"
#include "frameworks/base/memory/referenced.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/core/components_ng/base/frame_node.h"
#include "frameworks/core/components_ng/pattern/navigation/navigation_declaration.h"
#include "frameworks/core/components_ng/pattern/navigation/navigation_options.h"

namespace OHOS::Ace::Framework {
class JSNavigationUtils {
public:
    static void ParseToolbarItemsConfiguration(const WeakPtr<NG::FrameNode>& targetNode,
        const JSCallbackInfo& info, const JSRef<JSArray>& jsArray, std::vector<NG::BarItem>& items);
    static void ParseTitleBarOptions(const JSCallbackInfo& info,
        bool needSetDefaultValue, NG::NavigationTitlebarOptions& options);
    static void ParseToolbarOptions(const JSCallbackInfo& info, NG::NavigationToolbarOptions& options);
    static void ParseBarItems(const WeakPtr<NG::FrameNode>& targetNode,
        const JSCallbackInfo& info, const JSRef<JSArray>& jsArray, std::vector<NG::BarItem>& items);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVIGATION_UTILS_H
