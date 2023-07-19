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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_SHALLOW_BUILDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_SHALLOW_BUILDER_H

#include <functional>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace::NG {

// ShallowBuilder对象用于ListItem和GridItem内部内容懒加载能力。
// 在最小化更新场景下，ListItem、GridItem这些组件采用懒加载方式，内部内容在js执行时不会创建仅保存创建方法。
class ACE_EXPORT ShallowBuilder : public virtual AceType {
    DECLARE_ACE_TYPE(ShallowBuilder, AceType);

public:
    using DeepRenderFunc = std::function<RefPtr<UINode>()>;

    explicit ShallowBuilder(DeepRenderFunc&& deepRenderFunc) : deepRenderFunc_(std::move(deepRenderFunc)) {}
    ~ShallowBuilder() override = default;

    bool IsExecuteDeepRenderDone() const
    {
        return executeDeepRenderDone_;
    }

    void MarkIsExecuteDeepRenderDone(bool executeDeepRenderDone)
    {
        executeDeepRenderDone_ = executeDeepRenderDone;
    }

    RefPtr<UINode> ExecuteDeepRender()
    {
        CHECK_NULL_RETURN(deepRenderFunc_, nullptr);
        executeDeepRenderDone_ = true;
        return deepRenderFunc_();
    }

private:
    DeepRenderFunc deepRenderFunc_;
    bool executeDeepRenderDone_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(ShallowBuilder);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_SHALLOW_BUILDER_H
