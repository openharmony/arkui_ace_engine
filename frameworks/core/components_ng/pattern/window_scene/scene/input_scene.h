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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INPUT_SCENE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INPUT_SCENE_H

#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"

namespace OHOS::Ace::NG {
class InputScene : public SystemWindowScene {
    DECLARE_ACE_TYPE(InputScene, SystemWindowScene);

public:
    explicit InputScene(const sptr<Rosen::Session>& session);
    ~InputScene() override = default;
    uint32_t GetWindowPatternType() const override;

private:
    void OnAttachToFrameNode() override;

    ACE_DISALLOW_COPY_AND_MOVE(InputScene);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INPUT_SCENE_H
