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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_STYLUS_STYLUS_DETECTOR_INTERFACE_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_STYLUS_STYLUS_DETECTOR_INTERFACE_H

#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace OHOS::Ace {
struct NotifyInfo {
    int componentId;
    int x;
    int y;
};

struct ResultData {
    int errorCode;
    std::string errorMessage;
    std::string resultData;
};

enum CommandType { COMMAND_REQUEST_FOCUS, COMMAND_CLEAR_HIT, COMMAND_SET_TEXT, COMMAND_GET_TEXT, COMMAND_INVALID };

struct Command {
    CommandType commandType;
};

class IAceStylusCallback {
public:
    virtual ~IAceStylusCallback() = default;
    virtual void Callback(ResultData resultData) = 0;
};

class IStylusDetectorCallback {
public:
    virtual ~IStylusDetectorCallback() = default;
    virtual void OnDetector(
        const CommandType& command, std::string args, std::shared_ptr<IAceStylusCallback> callback);
};

class StylusDetectorInterface {
public:
    virtual bool IsEnable() = 0;
    virtual bool RegisterStylusInteractionListener(const std::shared_ptr<IStylusDetectorCallback>& callback) = 0;
    virtual void UnRegisterStylusInteractionListener() = 0;
    virtual bool Notify(const NotifyInfo& notifyInfo) = 0;

protected:
    virtual ~StylusDetectorInterface() {}
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_STYLUS_STYLUS_DETECTOR_INTERFACE_H