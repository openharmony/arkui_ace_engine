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
#ifndef CAPI_STUBS_MOCK_GESTURES_H
#define CAPI_STUBS_MOCK_GESTURES_H

#include "base/memory/ace_type.h"
#include "core/gestures/gesture_info.h"
#include "core/gestures/gesture_processor.h"

namespace OHOS::Ace {
class GestureModel {
public:
    static GestureModel* GetInstance();
    virtual ~GestureModel() = default;
    void Pop() {}

private:
    static GestureModel* instance_;
};

class TapGestureModel {
public:
    static TapGestureModel* GetInstance();
    virtual ~TapGestureModel() = default;
    virtual void Create(int32_t countNum, int32_t fingersNum, double distanceThreshold) {}
    static void SetMock(TapGestureModel* mock)
    {
        instance_ = mock;
    }
private:
    static TapGestureModel* instance_;
};

class LongPressGestureModel {
public:
    static LongPressGestureModel* GetInstance();
    virtual ~LongPressGestureModel() = default;
    virtual void Create(int32_t fingersNum, bool repeatResult, int32_t durationNum) {}
    static void SetMock(LongPressGestureModel* mock)
    {
        instance_ = mock;
    }
private:
    static LongPressGestureModel* instance_;
};

class PanGestureModel {
public:
    static PanGestureModel* GetInstance();
    virtual ~PanGestureModel() = default;
    virtual void Create(int32_t fingersNum, const PanDirection& panDirection, double distanceNum) {};
    static void SetMock(PanGestureModel* mock)
    {
        instance_ = mock;
    }
private:
    static PanGestureModel* instance_;
};

class TapGestureModelNG : public TapGestureModel {
public:
    void Create(int32_t countNum, int32_t fingersNum,
        double distanceThreshold = std::numeric_limits<double>::infinity()) {}
};

class LongPressGestureModelNG : public LongPressGestureModel {
public:
    void Create(int32_t fingersNum, bool repeatResult, int32_t durationNum) {}
};

class ACE_EXPORT PanGestureModelNG : public OHOS::Ace::PanGestureModel {
public:
    void Create(int32_t fingersNum, const PanDirection& panDirection, double distanceNum) {};
};

}
#endif //CAPI_STUBS_MOCK_GESTURES_H