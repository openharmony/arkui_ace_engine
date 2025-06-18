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
PanGesture::PanGesture(int32_t fingers, const PanDirection& direction, const PanDistanceMapDimension& distanceMap,
    bool isLimitFingerCount)
{
    fingers_ = fingers;
    direction_ = direction;
    distanceMap_ = distanceMap;
    isLimitFingerCount_ = isLimitFingerCount;
    if (gestureInfo_) {
        gestureInfo_->SetType(GestureTypeName::PAN_GESTURE);
        gestureInfo_->SetRecognizerType(GestureTypeName::PAN_GESTURE);
    } else {
        gestureInfo_ = MakeRefPtr<GestureInfo>(GestureTypeName::PAN_GESTURE, GestureTypeName::PAN_GESTURE, false);
    }
};

RefPtr<NGGestureRecognizer> PanGesture::CreateRecognizer()
{
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, nullptr);

    RefPtr<PanRecognizer> panRecognizer;
    if (panGestureOption_) {
        panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption_);
    } else {
        panRecognizer = AceType::MakeRefPtr<PanRecognizer>(fingers_, direction_, distanceMap_, isLimitFingerCount_);
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
    if (gestureInfo_) {
        gestureInfo_->SetDisposeTag(false);
    }
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
    auto distanceMapSize = static_cast<int32_t>(distanceMap_.size());
    *reinterpret_cast<int32_t*>(buff) = distanceMapSize;
    buff += sizeof(int32_t);
    for (auto iter : distanceMap_) {
        *reinterpret_cast<SourceTool*>(buff) = iter.first;
        buff += sizeof(SourceTool);
        *reinterpret_cast<double*>(buff) = iter.second.ConvertToPx();
        buff += sizeof(double);
    }
    double* matrix = reinterpret_cast<double*>(buff);
    for (int i = 0; i < Matrix4::DIMENSION; i++) {
        for (int j = 0; j < Matrix4::DIMENSION; j++) {
            matrix[i * Matrix4::DIMENSION + j] = matrix_.Get(i, j);
        }
    }
}

int32_t PanGesture::SizeofMe()
{
    size_t sizeOfDistanceMap = sizeof(int32_t) + (sizeof(SourceTool) + sizeof(double)) * distanceMap_.size();
    return sizeof(int32_t) + sizeof(GestureType) + sizeof(PanDirection) + sizeOfDistanceMap + sizeof(Matrix4) +
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
    int32_t distanceMapSize = *reinterpret_cast<int32_t*>(const_cast<char*>(buff));
    buff += sizeof(int32_t);
    for (int i = 0; i < distanceMapSize; i++) {
        SourceTool sourceTool = *reinterpret_cast<SourceTool*>(const_cast<char*>(buff));
        buff += sizeof(SourceTool);
        double distance = *reinterpret_cast<double*>(const_cast<char*>(buff));
        buff += sizeof(double);
        distanceMap_[sourceTool] = Dimension(distance, DimensionUnit::PX);
    }
    double* matrix = reinterpret_cast<double*>(const_cast<char*>(buff));
    for (int i = 0; i < Matrix4::DIMENSION; i++) {
        for (int j = 0; j < Matrix4::DIMENSION; j++) {
            matrix_.Set(i, j, matrix[i * Matrix4::DIMENSION + j]);
        }
    }
    return SizeofMe();
}

void PanGesture::SetDistanceMap(const PanDistanceMapDimension& distanceMap)
{
    distanceMap_ = distanceMap;
}
} // namespace OHOS::Ace::NG
