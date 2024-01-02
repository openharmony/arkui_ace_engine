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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_PAN_GESTURE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_PAN_GESTURE_H

#include <functional>
#include <string>
#include <vector>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/gestures/gesture_info.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT PanGesture : public Gesture {
    DECLARE_ACE_TYPE(PanGesture, Gesture);

public:
    PanGesture(int32_t fingers, const PanDirection& direction, double distance)
    {
        fingers_ = fingers;
        direction_ = direction;
        distance_ = distance;
        if (gestureInfo_) {
            gestureInfo_->SetType(GestureTypeName::PAN_GESTURE);
        } else {
            gestureInfo_ = MakeRefPtr<GestureInfo>(GestureTypeName::PAN_GESTURE);
        }
    };

    explicit PanGesture(RefPtr<PanGestureOption> panGestureOption)
    {
        panGestureOption_ = panGestureOption;
        if (gestureInfo_) {
            gestureInfo_->SetType(GestureTypeName::PAN_GESTURE);
        } else {
            gestureInfo_ = MakeRefPtr<GestureInfo>(GestureTypeName::PAN_GESTURE);
        }
    };
    ~PanGesture() override = default;

    void MoveTo(const char* c)
    {
        *(int32_t*)(c) = fingers_;
        c += sizeof(int32_t);
        *(GesturePriority*)(c) = priority_;
        c += sizeof(GesturePriority);
        *(GestureMask*)(c) = gestureMask_;
        c += sizeof(GestureMask);
        *(PanDirection*)(c) = direction_;
        c += sizeof(PanDirection);
        *(double*)(c) = distance_;
        c += sizeof(double);
        double* d = (double*)c;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                d[i * 4 + j] = matrix.Get(i, j);
            }
        }
    };

    virtual int32_t SizeofMe() override
    {
        return sizeof(int32_t) + sizeof(GestureType) + sizeof(PanDirection) + sizeof(double) + sizeof(Matrix4) +
               Gesture::SizeofMe();
    };

    int Serialize(const char* panGesture) override
    {
        int sizePan = SizeofMe();
        panGesture = SetHeader(panGesture, GestureType::PAN, sizePan);
        MoveTo(panGesture);
        return sizePan;
    };

    virtual int32_t Deserialize(char* p) override
    {
        p += sizeof(GestureType) + sizeof(int32_t);
        fingers_ = *(int32_t*)(p);
        p += sizeof(int32_t);
        priority_ = *(GesturePriority*)(p);
        p += sizeof(GesturePriority);
        gestureMask_ = *(GestureMask*)(p);
        p += sizeof(GestureMask);
        direction_ = *(PanDirection*)(p);
        p += sizeof(PanDirection);
        distance_ = *(double*)(p);
        p += sizeof(double);
        double* d = (double*)p;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrix.Set(i, j, d[i * 4 + j]);
            }
        }
        return SizeofMe();
    };

protected:
    RefPtr<NGGestureRecognizer> CreateRecognizer() override;

private:
    PanDirection direction_;
    double distance_ = 0.0;
    RefPtr<PanGestureOption> panGestureOption_;
    Matrix4 matrix;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_PAN_GESTURE_H
