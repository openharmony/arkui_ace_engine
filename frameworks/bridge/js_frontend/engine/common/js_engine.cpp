/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"

#include "frameworks/bridge/js_frontend/engine/common/runtime_constants.h"

namespace OHOS::Ace::Framework {
void JsEngineInstance::RegisterSingleComponent(
    std::string& command, const std::string& componentName, const std::string& methods)
{
    LOGI("RegisterComponent: %{private}s", componentName.c_str());
    command.append("registerComponents(")
        .append(" [{\'methods\':")
        .append(methods)
        .append(",\'type\':\'")
        .append(componentName)
        .append("\'}]);");
}

void JsEngineInstance::RegisterModules(std::string& command)
{
    LOGI("RegisterModules");
    static const JsModule moduleList[] = {
        { "system.router", "['push', 'replace', 'back', 'clear', 'getLength', 'getState']" },
        { "system.app", "['getInfo', 'getPackageInfo', 'terminate', 'requestFullWindow', 'screenOnVisible']" },
        { "system.prompt", "['showToast', 'showDialog']" }, { "system.configuration", "['getLocale']" },
        { "timer", "['setTimeout', 'clearTimeout', 'setInterval', 'clearInterval']" },
        { "system.image", "['getImage']" }, { "system.device", "['getInfo']" },
        { "system.grid", "['getSystemLayoutInfo']" }, { "system.mediaquery", "['addListener', 'getDeviceType']" },
        { "animation", "['requestAnimationFrame', 'cancelAnimationFrame']" } };
    for (const auto& module : moduleList) {
        LOGD("RegisterModule: %{private}s", module.moduleName.c_str());
        command.append("registerModules(")
            .append(" {\"")
            .append(module.moduleName)
            .append("\": ")
            .append(module.methods)
            .append(" } );");
    }
}

void JsEngineInstance::RegisterCommonComponents(std::string& command)
{
    LOGI("RegisterCommonComponents");
    static const char* commonMethodNode[] = {
        NODE_TAG_CLOCK,
        NODE_TAG_IMAGE,
        NODE_TAG_LABEL,
        NODE_TAG_LIST_ITEM,
        NODE_TAG_LIST_ITEM_GROUP,
        NODE_TAG_PROGRESS,
        NODE_TAG_RATING,
        NODE_TAG_SELECT,
        NODE_TAG_SWITCH,
        NODE_TAG_TABS,
        NODE_TAG_TAB_BAR,
        NODE_TAG_TAB_CONTENT,
        NODE_TAG_TEXT,
    };

    for (const auto& nodeTag : commonMethodNode) {
        RegisterSingleComponent(
            command, nodeTag, "['focus', 'animate', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']");
    }
}

void JsEngineInstance::RegisterComponents(std::string& command)
{
    LOGI("RegisterComponents");
    RegisterCommonComponents(command);

    static const JsComponent componentList[] = {
        { "button", "['setProgress', 'focus', 'animate', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "chart", "['append', 'focus', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "calendar", "['goto', 'focus', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "canvas", "['getContext', 'animate', 'focus', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "dialog", "['show', 'close', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "div", "['focus', 'animate', 'getScrollOffset', 'scrollBy', 'getBoundingClientRect']" },
        { "divider", "['animate', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "grid-container", "['getColumns', 'getColumnWidth', 'getGutterWidth', 'getSizeType', "
                            "'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "image-animator", "['start', 'stop', 'pause', 'resume', 'getState', 'animate', 'focus', "
                            "'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "input",
            "['showError', 'focus', 'animate', 'delete', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "list", "['scrollTo', 'scrollBy', 'focus', 'scrollArrow', 'scrollTop', 'scrollBottom', 'scrollPage', "
                  "'collapseGroup', 'expandGroup', 'currentOffset', 'rotation', 'animate', 'chainanimation', "
                  "'getBoundingClientRect', 'getScrollOffset']" },
        { "marquee", "['start', 'stop', 'focus', 'animate', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "menu", "['show', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "option", "['focus', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "panel", "['show', 'close', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "picker", "['show', 'animate', 'focus', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "picker-view", "['rotation', 'animate', 'focus', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "piece", "['focus', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "popup", "['focus', 'show', 'hide', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "search", "['animate', 'focus', 'delete', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "slider", "['rotation', 'focus', 'animate', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "stack", "['focus', 'animate', 'getScrollOffset', 'scrollBy', 'getBoundingClientRect']" },
        { "swiper", "['swipeTo', 'focus', 'showPrevious', 'showNext', 'rotation', 'animate', 'getBoundingClientRect', "
                    "'scrollBy', 'getScrollOffset']" },
        { "video", "['start', 'pause', 'setCurrentTime', 'requestFullscreen', 'exitFullscreen', 'focus', 'animate', "
                   "'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "stepper", "['setNextButtonStatus', 'focus', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "textarea", "['focus', 'animate', 'delete', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" },
        { "web", "['reload', 'getBoundingClientRect', 'scrollBy', 'getScrollOffset']" }
    };
    for (const auto& component : componentList) {
        RegisterSingleComponent(command, component.componentName, component.methods);
    }
}

void JsEngineInstance::InitModulesAndComponents(void* context)
{
    LOGI("InitModulesAndComponents");
    std::string command;

    // register modules
    RegisterModules(command);

    // register components
    RegisterComponents(command);

    FlushCommandBuffer(context, command);
}
} // namespace OHOS::Ace::Framework
