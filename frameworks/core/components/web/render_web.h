/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RENDER_WEB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RENDER_WEB_H

#include "core/components/common/layout/constants.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components/web/web_component.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class RenderWeb : public RenderNode {
    DECLARE_ACE_TYPE(RenderWeb, RenderNode);

public:
    static RefPtr<RenderNode> Create();

    RenderWeb() : RenderNode(true) {}
    ~RenderWeb() override = default;

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void OnAttachContext() override;

    void SetDelegate(const RefPtr<WebDelegate>& delegate)
    {
        delegate_ = delegate;
    }

    void OnPageStartedV2(const std::string& param);
    void OnPageFinishedV2(const std::string& param);
    void OnPageErrorV2(const std::string& param);
    void OnMessageV2(const std::string& param);

    void SetOnPageStart(const std::function<void(std::string)>& param)
    {
        onPageStartedV2_ = param;
    }

    void SetOnPageFinish(const std::function<void(std::string)>& param)
    {
        onPageStartedV2_ = param;
    }

    void SetOnError(const std::function<void(std::string)>& param)
    {
        onPageStartedV2_ = param;
    }

    void SetOnMessage(const std::function<void(std::string)>& param)
    {
        onPageMessageV2_ = param;
    }

protected:
    RefPtr<WebDelegate> delegate_;

private:
    int32_t GetIntParam(const std::string& param, const std::string& name) const;
    std::string GetStringParam(const std::string& param, const std::string& name) const;
    std::string GetUrlStringParam(const std::string& param, const std::string& name) const;

    Offset position_;
    Size drawSize_;
    std::function<void(std::string)> onPageStartedV2_;
    std::function<void(std::string)> onPageFinishedV2_;
    std::function<void(std::string)> onPageErrorV2_;
    std::function<void(std::string)> onPageMessageV2_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RENDER_WEB_H
