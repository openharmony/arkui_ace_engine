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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_AVOID_INFO_AVOID_INFO_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_AVOID_INFO_AVOID_INFO_MANAGER_H

#include <cstdint>
#include <functional>
#include <set>

#include "base/memory/ace_type.h"
#include "base/geometry/ng/rect_t.h"
#include "base/want/want_wrap.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

struct ContainerModalAvoidInfo {
    bool needAvoid = false;
    int32_t titleHeight = 0;
    RectF controlBottonsRect;

    std::string ToString() const;
};

class IAvoidInfoListener : public virtual AceType {
    DECLARE_ACE_TYPE(IAvoidInfoListener, AceType);
public:
    IAvoidInfoListener() = default;
    virtual ~IAvoidInfoListener() = default;

    virtual void OnAvoidInfoChange(const ContainerModalAvoidInfo& info) = 0;
};

using ParseAvoidInfoCallback = std::function<bool(const AAFwk::Want& want, ContainerModalAvoidInfo& info)>;
using BuildAvoidInfoCallback = std::function<void(const ContainerModalAvoidInfo& info, AAFwk::Want& want)>;
using UECAvoidInfoConsumer = std::function<int32_t(const AAFwk::Want& data)>;
using RegisterUECAvoidInfoConsumerCallback = std::function<void(UECAvoidInfoConsumer&& consumer)>;
using RequestAvoidInfoCallback = std::function<void()>;

class AvoidInfoManager : public virtual AceType {
    DECLARE_ACE_TYPE(AvoidInfoManager, AceType);
public:
    AvoidInfoManager() = default;
    ~AvoidInfoManager() = default;

    void SetPipelineContext(const WeakPtr<PipelineContext>& pipeline)
    {
        pipeline_ = pipeline;
    }
    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }
    void SetAvoidInfo(const ContainerModalAvoidInfo& info)
    {
        avoidInfo_ = info;
    }
    void SetAvoidInfoForUEC(const ContainerModalAvoidInfo& info)
    {
        avoidInfoForUEC_ = info;
    }

    void SetParseAvoidInfoCallback(ParseAvoidInfoCallback&& callback)
    {
        parseCallback_ = std::move(callback);
    }
    bool ParseAvoidInfo(const AAFwk::Want& want, ContainerModalAvoidInfo& info)
    {
        CHECK_NULL_RETURN(parseCallback_, false);
        return parseCallback_(want, info);
    }
    void SetBuildAvoidInfoCallback(BuildAvoidInfoCallback&& callback)
    {
        buildCallback_ = std::move(callback);
    }
    void BuildAvoidInfo(const ContainerModalAvoidInfo& info, AAFwk::Want& want)
    {
        if (buildCallback_) {
            buildCallback_(info, want);
        }
    }
    void SetRegisterUECAvoidInfoConsumerCallback(RegisterUECAvoidInfoConsumerCallback&& callback)
    {
        registerUECConsumerCallback_ = std::move(callback);
    }
    void SetRequestAvoidInfoCallback(RequestAvoidInfoCallback&& callback)
    {
        requestAvoidInfoCallback_ = std::move(callback);
    }

    void OnAvoidInfoChange(const ContainerModalAvoidInfo& info);
    void AddAvoidInfoListener(WeakPtr<IAvoidInfoListener> listener);
    void RemoveAvoidInfoListener(WeakPtr<IAvoidInfoListener> listener);

    int32_t GetContainerModalTitleHeight();
    bool GetContainerModalButtonsRect(RectF& containerModal, RectF& buttonsRect);
    bool NeedAvoidContainerModal();

    static void GetContainerModalAvoidInfoForUEC(const RefPtr<FrameNode>& uecNode, ContainerModalAvoidInfo& info);
    static bool CheckIfNeedNotifyAvoidInfoChange(
        const ContainerModalAvoidInfo& prevInfo, const ContainerModalAvoidInfo& curInfo);

private:
    void RegisterListenerIfNeeded();
    void UnregisterListenerIfNeeded();
    void GetContainerModalAvoidInfo(ContainerModalAvoidInfo& info);
    void OnContainerModalInfoChange();
    int32_t OnUECAvoidInfoReceived(const AAFwk::Want& data);

    int32_t instanceId_ = -1;
    WeakPtr<PipelineContext> pipeline_;
    ParseAvoidInfoCallback parseCallback_;
    BuildAvoidInfoCallback buildCallback_;
    RegisterUECAvoidInfoConsumerCallback registerUECConsumerCallback_;
    RequestAvoidInfoCallback requestAvoidInfoCallback_;
    bool hasRegisterListener_ = false;
    int32_t containerModalListenerId_ = 0;
    std::set<WeakPtr<IAvoidInfoListener>> listeners_;
    ContainerModalAvoidInfo avoidInfo_;
    ContainerModalAvoidInfo avoidInfoForUEC_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_AVOID_INFO_AVOID_INFO_MANAGER_H
