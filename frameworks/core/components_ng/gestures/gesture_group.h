/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/components_ng/gestures/pan_gesture.h"
namespace OHOS::Ace::NG {

#define MAX_BYTES_SIZE  (1024*1024*10)
class ACE_FORCE_EXPORT GestureGroup : public Gesture {
    DECLARE_ACE_TYPE(GestureGroup, Gesture);

public:
    GestureGroup(GestureMode mode, const std::vector<RefPtr<Gesture>>& gestures) : mode_(mode), gestures_(gestures) {}
    explicit GestureGroup(GestureMode mode) : mode_(mode) {}
    ~GestureGroup() override = default;
    void AddGesture(RefPtr<Gesture> gesture)
    {
        gestures_.emplace_back(gesture);
    }
    int32_t SizeofMe() override;
    virtual int32_t Serialize(char* buff) override;
    
    RefPtr<Gesture> MakeGesture(GestureType type);

    virtual int32_t Deserialize(const char* buff) override;
    
    RefPtr<NGGestureRecognizer> CreateRecognizer() override;

    void RemoveChildrenByTag(const std::string& gestureTag, bool& needRecollect);

    void RemoveGesture(RefPtr<Gesture> gesture);

    const std::vector<RefPtr<Gesture>> &GetGestures() const
    {
        return gestures_;
    }
private:
    GestureMode mode_;
    std::vector<RefPtr<Gesture>> gestures_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_GESTURE_GROUP_H
