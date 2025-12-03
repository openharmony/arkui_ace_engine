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
#include "ani/ani_parser.h"
 
#include "core/interfaces/native/implementation/scroller_peer_impl.h"
#include "interfaces/inner_api/ace_kit/src/view/scroller_impl.h"
 
namespace OHOS::Ace::Kit {
 
class ScrollerDataAni : public ScrollerImpl::ScrollerData {
    DECLARE_ACE_TYPE(ScrollerDataAni, ScrollerImpl::ScrollerData);
public:
    explicit ScrollerDataAni(const RefPtr<ScrollerPeer>& scrollerPeer) : scrollerPeer_(scrollerPeer) {}
    bool operator==(const Ace::RefPtr<ScrollerImpl::ScrollerData>& other) const override
    {
        auto impl = AceType::DynamicCast<ScrollerDataAni>(other);
        CHECK_NULL_RETURN(impl, false);
        return scrollerPeer_ == impl->scrollerPeer_;
    }
    const WeakPtr<ScrollControllerBase>& GetController() const override
    {
        static WeakPtr<ScrollControllerBase> retPtr = nullptr;
        return retPtr;
    }
    void AddObserver(const ScrollerObserver& observer, int32_t id) override {}
    void RemoveObserver(int32_t id) override {}

private:
    RefPtr<ScrollerPeer> scrollerPeer_;
};
 
RefPtr<Scroller> ACE_FORCE_EXPORT ParseScroller(ani_long value)
{
    ScrollerPeer* scroller = reinterpret_cast<ScrollerPeer*>(value);
    return AceType::MakeRefPtr<ScrollerImpl>(AceType::MakeRefPtr<ScrollerDataAni>(AceType::Claim(scroller)));
}
 
} // namespace OHOS::Ace::Kit
