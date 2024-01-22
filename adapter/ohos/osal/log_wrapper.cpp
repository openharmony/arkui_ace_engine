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

#include "base/log/log_wrapper.h"

#include <cstring>
#include <map>
#include <unordered_map>

#include "hilog/log.h"

#ifdef ACE_INSTANCE_LOG
#include "core/common/container_scope.h"
#endif

extern "C" {
int HiLogPrintArgs(LogType type, LogLevel level, unsigned int domain, const char* tag, const char* fmt, va_list ap);
}

namespace OHOS::Ace {

namespace {

const ::LogLevel LOG_LEVELS[] = {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
};

const std::map<AceLogTag, const char*> DOMAIN_CONTENTS_MAP = {
    { AceLogTag::DEFAULT, "Ace" },
    { AceLogTag::ACE_ALPHABET_INDEXER, "AceAlphabetIndexer" },
    { AceLogTag::ACE_COUNTER, "AceCounter" },
    { AceLogTag::ACE_SUB_WINDOW, "AceSubWindow" },
    { AceLogTag::ACE_FORM, "AceForm" },
    { AceLogTag::ACE_DRAG, "AceDrag" },
    { AceLogTag::ACE_VIDEO, "AceVideo" },
    { AceLogTag::ACE_COMPONENT_SNAPSHOT, "AceComponentSnapshot" },
    { AceLogTag::ACE_CANVAS, "AceCanvas" },
    { AceLogTag::ACE_REFRESH, "AceRefresh" },
    { AceLogTag::ACE_SCROLL, "AceScroll" },
    { AceLogTag::ACE_SCROLLABLE, "AceScrollable" },
    { AceLogTag::ACE_FONT, "AceFont" },
    { AceLogTag::ACE_OVERLAY, "AceOverlay" },
    { AceLogTag::ACE_DIALOG_TIMEPICKER, "AceDialogTimePicker" },
    { AceLogTag::ACE_DIALOG, "AceDialog" },
    { AceLogTag::ACE_PANEL, "AcePanel" },
    { AceLogTag::ACE_MENU, "AceMenu" },
    { AceLogTag::ACE_TEXTINPUT, "AceTextInput" },
    { AceLogTag::ACE_TEXT, "AceText" },
    { AceLogTag::ACE_TEXT_FIELD, "AceTextField" },
    { AceLogTag::ACE_SWIPER, "AceSwiper" },
    { AceLogTag::ACE_TABS, "AceTabs" },
    { AceLogTag::ACE_BLANK, "AceBlank" },
    { AceLogTag::ACE_GRIDROW, "AceGridRow" },
    { AceLogTag::ACE_INPUTTRACKING, "AceInputTracking" },
    { AceLogTag::ACE_RICH_TEXT, "AceRichText" },
    { AceLogTag::ACE_WEB, "AceWeb" },
    { AceLogTag::ACE_FOCUS, "AceFocus" },
    { AceLogTag::ACE_MOUSE, "AceMouse" },
    { AceLogTag::ACE_GESTURE, "AceGesture" },
    { AceLogTag::ACE_IMAGE, "AceImage" },
    { AceLogTag::ACE_RATING, "AceRating" },
    { AceLogTag::ACE_LIST, "AceList" },
    { AceLogTag::ACE_NAVIGATION, "AceNavigation" },
    { AceLogTag::ACE_WATERFLOW, "AceWaterFlow" },
    { AceLogTag::ACE_ACCESSIBILITY, "AceAccessibility" },
    { AceLogTag::ACE_ROUTER, "AceRouter" },
    { AceLogTag::ACE_THEME, "AceTheme" },
    { AceLogTag::ACE_BORDER_IMAGE, "AceBorderImage" },
    { AceLogTag::ACE_GRID, "AceGrid" },
    { AceLogTag::ACE_PLUGIN_COMPONENT, "AcePluginComponent" },
    { AceLogTag::ACE_UIEXTENSIONCOMPONENT, "AceUiExtensionComponent" },
    { AceLogTag::ACE_IF, "AceIf" },
    { AceLogTag::ACE_FOREACH, "AceForEach" },
    { AceLogTag::ACE_LAZY_FOREACH, "AceLazyForEach" },
    { AceLogTag::ACE_GAUGE, "AceGauge" },
    { AceLogTag::ACE_HYPERLINK, "AceHyperLink" },
    { AceLogTag::ACE_ANIMATION, "AceAnimation" },
    { AceLogTag::ACE_XCOMPONENT, "AceXcomponent" },
    { AceLogTag::ACE_AUTO_FILL, "AceAutoFill" },
    { AceLogTag::ACE_KEYBOARD, "AceKeyboard" },
    { AceLogTag::ACE_UIEVENT, "AceUIEvent" },
    { AceLogTag::ACE_UI_SERVICE, "AceUIService" },
    { AceLogTag::ACE_DISPLAY_SYNC, "AceDisplaySync" },
    { AceLogTag::ACE_RESOURCE, "AceResource" },
    { AceLogTag::ACE_SIDEBAR, "AceSideBarContainer" },
    { AceLogTag::ACE_GEOMETRY_TRANSITION, "AceGeometryTransition" },
    { AceLogTag::ACE_DOWNLOAD_MANAGER, "DownloadManager" },
    { AceLogTag::ACE_WINDOW_SCENE, "WMSCom" },
    { AceLogTag::ACE_NODE_CONTAINER, "AceNodeContainer" },
    { AceLogTag::ACE_NATIVE_NODE, "AceNativeNode" },
    { AceLogTag::ACE_DYNAMIC_COMPONENT, "AceDynamicComponent" },
    { AceLogTag::ACE_MARQUEE, "AceMarquee" },
};

const char* APP_DOMAIN_CONTENT = "JSApp";

constexpr uint32_t LOG_DOMAINS[] = {
    0xD003900,
    0xC0D0,
};

constexpr LogType LOG_TYPES[] = {
    LOG_CORE,
    LOG_APP,
};

} // namespace

// initial static member object
LogLevel LogWrapper::level_ = LogLevel::DEBUG;

char LogWrapper::GetSeparatorCharacter()
{
    return '/';
}

void LogWrapper::PrintLog(LogDomain domain, LogLevel level, AceLogTag tag, const char* fmt, va_list args)
{
    uint32_t hilogDomain = LOG_DOMAINS[static_cast<uint32_t>(domain)] + static_cast<uint32_t>(tag);
    const char* domainContent = domain == LogDomain::FRAMEWORK ? DOMAIN_CONTENTS_MAP.at(tag) : APP_DOMAIN_CONTENT;
#ifdef ACE_PRIVATE_LOG
    std::string newFmt(fmt);
    ReplaceFormatString("{private}", "{public}", newFmt);
    HiLogPrintArgs(LOG_TYPES[static_cast<uint32_t>(domain)], LOG_LEVELS[static_cast<uint32_t>(level)],
        hilogDomain, domainContent, newFmt.c_str(), args);
#else
    HiLogPrintArgs(LOG_TYPES[static_cast<uint32_t>(domain)], LOG_LEVELS[static_cast<uint32_t>(level)],
        hilogDomain, domainContent, fmt, args);
#endif
}

#ifdef ACE_INSTANCE_LOG
int32_t LogWrapper::GetId()
{
    return ContainerScope::CurrentId();
}

const char* LogWrapper::GetIdMethod()
{
    return ContainerScope::CurrentIdGenerateMethod();
}
#endif

} // namespace OHOS::Ace
