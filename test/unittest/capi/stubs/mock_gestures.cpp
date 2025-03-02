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

#include "mock_gestures.h"

namespace OHOS::Ace {

GestureModel* GestureModel::instance_ = nullptr;
GestureModel* GestureModel::GetInstance()
{
    return instance_;
}

TapGestureModel* TapGestureModel::instance_ = nullptr;
TapGestureModel* TapGestureModel::GetInstance()
{
    if (!instance_) {
        instance_ = new TapGestureModel();
    }
    return instance_;
}

LongPressGestureModel* LongPressGestureModel::instance_ = nullptr;
LongPressGestureModel* LongPressGestureModel::GetInstance()
{
    if (!instance_) {
        instance_ = new LongPressGestureModel();
    }
    return instance_;
}

PanGestureModel* PanGestureModel::instance_ = nullptr;
PanGestureModel* PanGestureModel::GetInstance()
{
    if (!instance_) {
        instance_ = new PanGestureModel();
    }
    return instance_;
}

PinchGestureModel* PinchGestureModel::instance_ = nullptr;
PinchGestureModel* PinchGestureModel::GetInstance()
{
    if (!instance_) {
        instance_ = new PinchGestureModel();
    }
    return instance_;
}

SwipeGestureModel* SwipeGestureModel::instance_ = nullptr;
SwipeGestureModel* SwipeGestureModel::GetInstance()
{
    if (!instance_) {
        instance_ = new SwipeGestureModel();
    }
    return instance_;
}

RotationGestureModel* RotationGestureModel::instance_ = nullptr;
RotationGestureModel* RotationGestureModel::GetInstance()
{
    if (!instance_) {
        instance_ = new RotationGestureModel();
    }
    return instance_;
}

GestureGroupModel* GestureGroupModel::instance_ = nullptr;
GestureGroupModel* GestureGroupModel::GetInstance()
{
    if (!instance_) {
        instance_ = new GestureGroupModel();
    }
    return instance_;
}

} // OHOS::Ace