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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_WITH_THEME_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_WITH_THEME_NODE_H

#include <cstdint>

#include "base/utils/macros.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/token_theme/token_theme.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

using ThemeScopeDestroyCallback = std::function<void()>;

class ACE_EXPORT WithThemeNode : public UINode {
    DECLARE_ACE_TYPE(WithThemeNode, UINode);

public:
    static RefPtr<WithThemeNode> GetWithThemeNode(int32_t nodeId);
    static RefPtr<WithThemeNode> CreateWithThemeNode(int32_t nodeId);
    static RefPtr<WithThemeNode> GetOrCreateWithThemeNode(int32_t nodeId);

    explicit WithThemeNode(int32_t nodeId) : UINode(V2::JS_WITH_THEME_ETS_TAG, nodeId) {
        SetThemeScopeId(nodeId);
    }
    ~WithThemeNode() override;

    bool IsAtomicNode() const override
    {
        return false;
    }

    bool IsSyntaxNode() const override
    {
        return true;
    }

    void UpdateThemeScopeId(int32_t themeScopeId) override;
    void UpdateThemeScopeUpdate(int32_t themeScopeId) override;
    void NotifyThemeScopeUpdate();
    void SetOnThemeScopeDestroy(ThemeScopeDestroyCallback&& callback);

private:
    ThemeScopeDestroyCallback themeScopeDestroyCallback_;

    ACE_DISALLOW_COPY_AND_MOVE(WithThemeNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_WITH_THEME_NODE_H
