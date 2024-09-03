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

#include "core/components_ng/gestures/pan_gesture.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

RefPtr<NGGestureRecognizer> PanGesture::CreateRecognizer()
{
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, nullptr);

    RefPtr<PanRecognizer> panRecognizer;
    if (panGestureOption_) {
        panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption_);
    } else {
        panRecognizer = AceType::MakeRefPtr<PanRecognizer>(fingers_, direction_, distance_);
    }
    if (onActionStartId_) {
        panRecognizer->SetOnActionStart(*onActionStartId_);
    }

    if (onActionUpdateId_) {
        panRecognizer->SetOnActionUpdate(*onActionUpdateId_);
    }

    if (onActionEndId_) {
        panRecognizer->SetOnActionEnd(*onActionEndId_);
    }

    if (onActionCancelId_) {
        panRecognizer->SetOnActionCancel(*onActionCancelId_);
    }

    panRecognizer->SetPriority(priority_);
    panRecognizer->SetPriorityMask(gestureMask_);
    panRecognizer->SetGestureInfo(gestureInfo_);
    panRecognizer->SetUserData(userData_);
    return panRecognizer;
}

void PanGesture::SerializeTo(char* buff)
{
    *reinterpret_cast<int32_t*>(buff) = fingers_;
    buff += sizeof(int32_t);
    *reinterpret_cast<GesturePriority*>(buff) = priority_;
    buff += sizeof(GesturePriority);
    *reinterpret_cast<GestureMask*>(buff) = gestureMask_;
    buff += sizeof(GestureMask);
    *reinterpret_cast<PanDirection*>(buff) = direction_;
    buff += sizeof(PanDirection);
    *reinterpret_cast<double*>(buff) = distance_;
    buff += sizeof(double);
    double* matrix = reinterpret_cast<double*>(buff);
    for (int i = 0; i < Matrix4::DIMENSION; i++) {
        for (int j = 0; j < Matrix4::DIMENSION; j++) {
            matrix[i * Matrix4::DIMENSION + j] = matrix_.Get(i, j);
        }
    }
}

int32_t PanGesture::SizeofMe()
{
    return sizeof(int32_t) + sizeof(GestureType) + sizeof(PanDirection) + sizeof(double) + sizeof(Matrix4) +
           sizeof(fingers_) + sizeof(priority_) + sizeof(gestureMask_);
}

int32_t PanGesture::Serialize(char* panGesture)
{
    if (panGesture == nullptr) {
        return -1;
    }
    int sizePan = SizeofMe();
    panGesture = SetHeader(panGesture, GestureType::PAN, sizePan);
    SerializeTo(panGesture);
    return sizePan;
}

int32_t PanGesture::Deserialize(const char* buff)
{
    if (buff == nullptr) {
        return -1;
    }
    buff += sizeof(GestureType) + sizeof(int32_t);
    fingers_ = *reinterpret_cast<int32_t*>(const_cast<char*>(buff));
    buff += sizeof(int32_t);
    priority_ = *reinterpret_cast<GesturePriority*>(const_cast<char*>(buff));
    buff += sizeof(GesturePriority);
    gestureMask_ = *reinterpret_cast<GestureMask*>(const_cast<char*>(buff));
    buff += sizeof(GestureMask);
    direction_ = *reinterpret_cast<PanDirection*>(const_cast<char*>(buff));
    buff += sizeof(PanDirection);
    distance_ = *reinterpret_cast<double*>(const_cast<char*>(buff));
    buff += sizeof(double);
    double* matrix = reinterpret_cast<double*>(const_cast<char*>(buff));
    for (int i = 0; i < Matrix4::DIMENSION; i++) {
        for (int j = 0; j < Matrix4::DIMENSION; j++) {
            matrix_.Set(i, j, matrix[i * Matrix4::DIMENSION + j]);
        }
    }
    return SizeofMe();
}


} // namespace OHOS::Ace::NG
