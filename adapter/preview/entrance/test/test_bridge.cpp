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

#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <map>

#include "adapter/preview/entrance/ace_ability.h"
#include "adapter/preview/entrance/ace_run_args.h"
#include "run_args_parser.h"
#include "frameworks/base/log/log.h"
#include "core/event/touch_event.h"
#include "core/event/key_event.h"
#include "adapter/preview/entrance/event_dispatcher.h"
#include "base/utils/macros.h"

namespace {
const std::map<int, OHOS::Ace::TouchType>TOUCH_TYPE_MAP = {
    {0, OHOS::Ace::TouchType::DOWN},
    {1, OHOS::Ace::TouchType::UP},
    {2, OHOS::Ace::TouchType::MOVE},
    {3, OHOS::Ace::TouchType::CANCEL},
    {4, OHOS::Ace::TouchType::UNKNOWN},
};
const std::map<int, OHOS::Ace::SourceType>SOURCE_TYPE_MAP = {
    {0, OHOS::Ace::SourceType::NONE},
    {1, OHOS::Ace::SourceType::MOUSE},
    {2, OHOS::Ace::SourceType::TOUCH},
    {3, OHOS::Ace::SourceType::TOUCH_PAD},
    {4, OHOS::Ace::SourceType::KEYBOARD},
};

using Callback = void (*)(const void* pp, const size_t bufferSize, const int32_t width, const int32_t height);
Callback cb {nullptr};

auto renderCallback = [](const void* p, const size_t bufferSize, const int32_t width, const int32_t height) -> bool {
    cb(p, bufferSize, width, height);
    LOGI("bufferSize = %{public}d, width = %{public}d, height = %{public}d.",
        static_cast<uint32_t>(bufferSize), width, height);
    return true;
};

auto pageCallback = [](const std::string currentPagePath) -> bool {
    LOGI("callback currentPage:%s", currentPagePath.c_str());
    return true;
};
} // namespace

extern "C" ACE_FORCE_EXPORT_WITH_PREVIEW bool RegisterCallback(Callback callback);
extern "C" ACE_FORCE_EXPORT_WITH_PREVIEW int StartPreviewer(const char* configContents);
extern "C" ACE_FORCE_EXPORT_WITH_PREVIEW void Stop();
extern "C" ACE_FORCE_EXPORT_WITH_PREVIEW void DispatchTouchEvent(int id, float x, float y,
    int touchtype, int sourcetype);
extern "C" ACE_FORCE_EXPORT_WITH_PREVIEW void DispatchBackPressedEvent();
extern "C" ACE_FORCE_EXPORT_WITH_PREVIEW void DispatchInputMethodEvent(unsigned int codePoint);

// registering callback function
bool RegisterCallback(Callback callback)
{
    cb = callback;
    if (!cb) {
        LOGE("registering callback function failed!");
        return false;
    }
    return true;
}

int StartPreviewer(const char* configContents)
{
    OHOS::Ace::Samples::RunArgsParser runArgsParser;
    bool flagParser = runArgsParser.Parse(configContents);
    if (!flagParser) {
        LOGE("Parse run args failed!");
        return -1;
    }
    OHOS::Ace::Platform::AceRunArgs args = runArgsParser.GetAceRunArgs();
    args.onRender = std::move(renderCallback);
    args.onRouterChange = std::move(pageCallback);
    auto ability = OHOS::Ace::Platform::AceAbility::CreateInstance(args);
    if (!ability) {
        LOGE("Could not create AceAbility!");
        return -1;
    }
    ability->InitEnv();
    LOGI("Ace initialize done. run loop now");
    ability->Start();
    return 0;
}

void Stop()
{
    OHOS::Ace::Platform::AceAbility::Stop();
}

void DispatchTouchEvent(int id, float x, float y, int touchtype, int sourcetype)
{
    OHOS::Ace::TouchEvent events;
    events.id=id;
    events.x=x;
    events.y=y;
    events.type=TOUCH_TYPE_MAP.at(touchtype);
    events.sourceType=SOURCE_TYPE_MAP.at(sourcetype);
    LOGI("id =%{public}d,x=%{public}f,y=%{public}f", events.id, events.x, events.y);
    OHOS::Ace::Platform::EventDispatcher::GetInstance().DispatchTouchEvent(events);
}

void DispatchBackPressedEvent()
{
    OHOS::Ace::Platform::EventDispatcher::GetInstance().DispatchBackPressedEvent();
}

void DispatchInputMethodEvent(unsigned int codePoint)
{
    OHOS::Ace::Platform::EventDispatcher::GetInstance().DispatchInputMethodEvent(codePoint);
}
