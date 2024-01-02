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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_GESTURE_GROUP_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_GESTURE_GROUP_H

#include <functional>
#include <string>
#include <vector>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/components_ng/gestures/pan_gesture.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT GestureGroup : public Gesture {
    DECLARE_ACE_TYPE(GestureGroup, Gesture);

public:
    GestureGroup(GestureMode mode, const std::vector<RefPtr<Gesture>>& gestures) : mode_(mode), gestures_(gestures) {}
    explicit GestureGroup(GestureMode mode) : mode_(mode) {}
    ~GestureGroup() override = default;

    void AddGesture(RefPtr<Gesture> gesture)
    {
        gestures_.emplace_back(gesture);
    }

    int32_t SizeofMe() override
    {
        int32_t total = 0;
        for (auto& i : gestures_) {
            total += i->SizeofMe();
        }
        total += sizeof(int32_t);
        total += sizeof(GestureType);
        total += sizeof(GestureMode);
        return total;
    }

    virtual int32_t Serialize(const char* p) override
    {
        auto total = SizeofMe();
        p = SetHeader(p, GestureType::GROUP, total);
        *(GestureMode*)p = mode_;
        p += sizeof(GestureMode);

        for (auto& i : gestures_) {
            int32_t len = i->Serialize(p);
            p += len;
        }
        return total;
    }

    RefPtr<Gesture> MakeGesture(GestureType type)
    {
        if (type == GestureType::PAN) {
            PanDirection panDirection;
            panDirection.type = PanDirection::VERTICAL;
            return AceType::MakeRefPtr<PanGesture>(1, panDirection, 0);
        } else if (type == GestureType::GROUP) {
            return AceType::MakeRefPtr<GestureGroup>(GestureMode::Parallel);
        }
        return nullptr;
    }

    virtual int32_t Deserialize(char* p) override
    {
        int32_t* plen = reinterpret_cast<int32_t*>(p + sizeof(GestureType));
        int32_t total = *plen;
        auto ret = total;
        total -= sizeof(int32_t);
        total -= sizeof(GestureType);
        p += sizeof(GestureType) + sizeof(int32_t);
        mode_ = *(GestureMode*)(p);
        total -= sizeof(GestureMode);
        p += sizeof(GestureMode);
        while (total != 0) {
            auto gesture = MakeGesture(*(GestureType*)p);
            auto len = gesture->Deserialize(p);
            gestures_.push_back(gesture);
            p += len;
            total -= len;
        }
        return ret;
    }
    RefPtr<NGGestureRecognizer> CreateRecognizer() override;

private:
    GestureMode mode_;
    std::vector<RefPtr<Gesture>> gestures_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_GESTURE_GROUP_H
