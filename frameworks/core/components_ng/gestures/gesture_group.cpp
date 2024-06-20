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

#include "core/components_ng/gestures/gesture_group.h"

#include "core/components_ng/gestures/recognizers/exclusive_recognizer.h"
#include "core/components_ng/gestures/recognizers/parallel_recognizer.h"
#include "core/components_ng/gestures/recognizers/sequenced_recognizer.h"

namespace OHOS::Ace::NG {

RefPtr<NGGestureRecognizer> GestureGroup::CreateRecognizer()
{
    std::vector<RefPtr<NGGestureRecognizer>> recognizers;
    for (auto& subGesture : gestures_) {
        auto recognizer = subGesture->CreateRecognizer();
        if (recognizer) {
            recognizers.emplace_back(recognizer);
        }
    }

    RefPtr<NGGestureRecognizer> groupRecognizer;
    switch (mode_) {
        case GestureMode::Sequence:
            groupRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
            if (onActionCancelId_) {
                groupRecognizer->SetOnActionCancel(*onActionCancelId_);
            }
            break;
        case GestureMode::Parallel:
            groupRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
            break;
        case GestureMode::Exclusive:
            groupRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
            break;
        default:
            return nullptr;
    }
    DynamicCast<RecognizerGroup>(groupRecognizer)->RemainChildOnResetStatus();
    groupRecognizer->SetPriority(priority_);
    groupRecognizer->SetPriorityMask(gestureMask_);
    groupRecognizer->SetGestureInfo(gestureInfo_);
    return groupRecognizer;
}

int32_t GestureGroup::Deserialize(const char* buff)
{
    if (buff == nullptr) {
        return -1;
    }
    int32_t* plen = reinterpret_cast<int32_t*>(const_cast<char*>(buff) + sizeof(GestureType));
    int32_t total = *plen;
    if (total <= 0 || total >= MAX_BYTES_SIZE) {
        return -1;
    }
    auto ret = total;
    total -= sizeof(int32_t);
    if (total < 0) {
        return -1;
    }
    total -= sizeof(GestureType);
    if (total < 0) {
        return -1;
    }
    buff += sizeof(GestureType) + sizeof(int32_t);
    mode_ = *reinterpret_cast<GestureMode*>(const_cast<char*>(buff));
    total -= sizeof(GestureMode);
    if (total < 0) {
        return -1;
    }
    buff += sizeof(GestureMode);
    while (total != 0) {
        auto gesture = MakeGesture(*(GestureType*)buff);
        auto len = gesture->Deserialize(buff);
        buff += len;
        total -= len;
        if (total < 0) {
            return -1;
        }
        gestures_.push_back(gesture);
    }
    return ret;
}

int32_t GestureGroup::SizeofMe()
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

RefPtr<Gesture> GestureGroup::MakeGesture(GestureType type)
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

int32_t GestureGroup::Serialize(char* buff)
{
    if (buff == nullptr) {
        return -1;
    }
    auto total = SizeofMe();
    buff = SetHeader(buff, GestureType::GROUP, total);
    *reinterpret_cast<GestureMode*>(buff) = mode_;
    buff += sizeof(GestureMode);
    for (auto& i : gestures_) {
        int32_t len = i->Serialize(buff);
        buff += len;
    }
    return total;
}

void GestureGroup::RemoveChildrenByTag(const std::string& gestureTag, bool& needRecollect)
{
    for (auto iter = gestures_.begin(); iter != gestures_.end();) {
        auto tag = (*iter)->GetTag();
        if (tag.has_value() && tag.value() == gestureTag) {
            iter = gestures_.erase(iter);
            needRecollect = true;
        } else {
            auto group = AceType::DynamicCast<GestureGroup>(*iter);
            if (group) {
                group->RemoveChildrenByTag(gestureTag, needRecollect);
            }
            iter++;
        }
    }
}

void GestureGroup::RemoveGesture(RefPtr<Gesture> gesture)
{
    for (auto iter = gestures_.begin(); iter != gestures_.end();) {
        if (*iter == gesture) {
            iter = gestures_.erase(iter);
        } else {
            auto group = AceType::DynamicCast<GestureGroup>(*iter);
            if (group) {
                group->RemoveGesture(gesture);
            }
            iter++;
        }
    }
}
} // namespace OHOS::Ace::NG
