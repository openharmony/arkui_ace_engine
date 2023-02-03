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

#ifndef FOUNDATION_ACE_INTERFACE_INNER_API_UI_WINDOW_H
#define FOUNDATION_ACE_INTERFACE_INNER_API_UI_WINDOW_H

#include <memory>

#include <refbase.h>

class NativeValue;
class NativeEngine;

namespace OHOS::AbilityRuntime {
class Context;
}

namespace OHOS::Rosen {
class RSSurfaceNode;
class ISceneSession;
class IExtensionSession;
class ISessionStageStateListener;
}

namespace OHOS::Ace::NG {

#ifndef ACE_EXPORT
#define ACE_EXPORT __attribute__((visibility("default")))
#endif

class ACE_EXPORT UIWindow {
public:
    static std::shared_ptr<UIWindow> CreateWindowScene(const std::shared_ptr<AbilityRuntime::Context>& context,
        const sptr<Rosen::ISceneSession>& iSceneSession, const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode);

    static std::shared_ptr<UIWindow> CreateWindowExtension(
        const std::shared_ptr<AbilityRuntime::Context>& context,
        const sptr<Rosen::IExtensionSession>& iExtensionSession,
        const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode);

    virtual ~UIWindow() = default;

    virtual void InitUIContent(const std::string& contentInfo, NativeEngine* engine, NativeValue* storage) = 0;

    // for lifecycle
    virtual void RegisterSessionStageStateListener(const std::shared_ptr<Rosen::ISessionStageStateListener>& listener) = 0;

    virtual void Connect() = 0;
    virtual void Foreground() = 0;
    virtual void Background() = 0;
    virtual void Disconnect() = 0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_INTERFACE_INNER_API_UI_WINDOW_H
