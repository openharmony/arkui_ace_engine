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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SCROLLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SCROLLER_PEER_IMPL_H

#include "base/memory/referenced.h"
#include "core/common/container_consts.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components/scroll_bar/scroll_proxy.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {

class ScrollerPeerImpl : public Referenced {
public:
    ScrollerPeerImpl() = default;
    ~ScrollerPeerImpl() override = default;

    void TriggerScrollTo(const Ark_ScrollOptions* options);
    void TriggerScrollEdge(Ark_Edge value, const Opt_ScrollEdgeOptions* options);
    void TriggerFling(const Ark_Number* velocity);
    void TriggerScrollPage0(const Ark_ScrollPageOptions* value);
    void TriggerScrollPage1(bool next);
    Ark_OffsetResult TriggerCurrentOffset();
    void TriggerScrollToIndex(const Ark_Number* value, const Opt_Boolean* smooth,
        const Opt_ScrollAlign* align, const Opt_ScrollToIndexOptions* options);
    void TriggerScrollBy(const Opt_Length* dx, const Opt_Length* dy);
    Ark_Boolean TriggerIsAtEnd();
    Ark_RectResult TriggerGetItemRect(const Ark_Number* index);
    Ark_Int32 TriggerGetItemIndex(const Ark_Number* x, const Ark_Number* y);

    const WeakPtr<ScrollControllerBase>& GetController() const
    {
        return controllerWeak_;
    }

    void SetController(const RefPtr<ScrollControllerBase>& controller)
    {
        controllerWeak_ = WeakPtr(controller);
    }

    void SetScrollBarProxy(const RefPtr<ScrollProxy>& proxy)
    {
        scrollBarProxyWeak_ = WeakPtr(proxy);
    }

    RefPtr<ScrollProxy> GetScrollBarProxy()
    {
        return scrollBarProxyWeak_.Upgrade();
    }

    void SetInstanceId(int32_t instanceId)
    {
        instanceId_ = instanceId;
    }

    int32_t GetInstanceId()
    {
        return instanceId_;
    }

private:
    WeakPtr<ScrollControllerBase> controllerWeak_;
    WeakPtr<ScrollProxy> scrollBarProxyWeak_;

    ACE_DISALLOW_COPY_AND_MOVE(ScrollerPeerImpl);

    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
};

} // namespace OHOS::Ace::NG::GeneratedModifier

struct ScrollerPeer : public OHOS::Ace::NG::GeneratedModifier::ScrollerPeerImpl {
    ScrollerPeer() = default;
    ~ScrollerPeer() override = default;

private:
    ACE_DISALLOW_COPY_AND_MOVE(ScrollerPeer);
};

#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SCROLLER_PEER_IMPL_H
