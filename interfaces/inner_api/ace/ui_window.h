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

#ifndef FOUNDATION_ACE_INTERFACE_INNER_API_UI_WINDOW_H
#define FOUNDATION_ACE_INTERFACE_INNER_API_UI_WINDOW_H

#include <refbase.h>

#include "ui_content.h"

namespace OHOS::Rosen {
class RSSurfaceNode;
class ISession;
class ISessionStageStateListener;
}

namespace OHOS::Ace::NG {

class ACE_EXPORT UIWindow {
public:
    static std::shared_ptr<UIWindow> CreateRootScene();

    static std::shared_ptr<UIWindow> CreateWindowScene(const std::shared_ptr<AbilityRuntime::Context>& context,
        const sptr<Rosen::ISession>& iSession, const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode);

    static std::shared_ptr<UIWindow> CreateWindowExtension(const std::shared_ptr<AbilityRuntime::Context>& context,
        const sptr<Rosen::ISession>& iSession, const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode);

    virtual ~UIWindow() = default;

    virtual void LoadContent(const std::string& contentUrl, NativeEngine* engine, NativeValue* storage,
        AbilityRuntime::Context* context = nullptr) = 0;

    // for lifecycle
    virtual void RegisterSessionStageStateListener(
        const std::shared_ptr<Rosen::ISessionStageStateListener>& listener) = 0;

    virtual void Connect() = 0;
    virtual void Foreground() = 0;
    virtual void Background() = 0;
    virtual void Disconnect() = 0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_INTERFACE_INNER_API_UI_WINDOW_H
