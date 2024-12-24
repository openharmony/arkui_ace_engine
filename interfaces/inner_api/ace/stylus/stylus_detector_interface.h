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
    std::string bundleName;
};

struct ResultData {
    int errorCode;
    std::string errorMessage;
    std::string resultData;
};

enum CommandType {
    COMMAND_REQUEST_FOCUS,
    COMMAND_CLEAR_HIT,
    COMMAND_SET_TEXT,
    COMMAND_GET_TEXT,
    COMMAND_UNDO,
    COMMAND_REDO,
    COMMAND_CANUNDO,
    COMMAND_CANREDO,
    COMMAND_DELETE_TEXT,
    COMMAND_CHOICE_TEXT,
    COMMAND_INSERT_SPACE,
    COMMAND_MOVE_CURSOR,
    COMMAND_INVALID
};

struct Command {
    CommandType commandType;
};

struct StylusGestureRect {
    float Left;
    float Top;
    float Width;
    float Height;
};

struct MoveCursorOption {
    int32_t x;
    int32_t y;
    bool showHandle;
};

struct ChoiceTextOption {
    StylusGestureRect rect;
    bool showMenu;
};

class IAceStylusCallback {
public:
    virtual ~IAceStylusCallback() = default;
    virtual void Callback(ResultData resultData) = 0;
};

class IStylusDetectorCallback {
public:
    virtual ~IStylusDetectorCallback() = default;
    virtual int32_t OnDetector(const CommandType& command, void* data, std::shared_ptr<IAceStylusCallback> callback);
    virtual bool OnDetectorSync(const CommandType& command);
};

class StylusDetectorInterface {
public:
    virtual bool IsEnable() = 0;
    virtual bool RegisterStylusInteractionListener(const std::string& bundleName,
        const std::shared_ptr<IStylusDetectorCallback>& callback) = 0;
    virtual void UnRegisterStylusInteractionListener(const std::string& bundleName) = 0;
    virtual bool Notify(const NotifyInfo& notifyInfo) = 0;

protected:
    virtual ~StylusDetectorInterface() {}
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_STYLUS_STYLUS_DETECTOR_INTERFACE_H