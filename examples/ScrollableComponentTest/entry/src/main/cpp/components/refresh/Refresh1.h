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

#ifndef ARKUI_CAPI_DEMO_REFRESH_COMPONENT_H
#define ARKUI_CAPI_DEMO_REFRESH_COMPONENT_H

#include <cstdint>

#include "components/component.h"

namespace ArkUICApiDemo {
class RefreshComponent : public Component {
public:
    RefreshComponent() : Component(ARKUI_NODE_REFRESH) {}
    explicit RefreshComponent(ArkUI_NodeHandle handle) : Component(handle) {}
    void SetPullToRefresh(int32_t pullToRefresh);
    void SetPullDownRatio(float pullDownRatio);
    void SetRefreshOffset(float refreshOffset);
    void SetRefreshing(bool refreshing);
    void SetRefreshContent(ArkUI_NodeHandle& node);
};
} // namespace ArkUICApiDemo
#endif // ARKUI_CAPI_DEMO_REFRESH_COMPONENT_H