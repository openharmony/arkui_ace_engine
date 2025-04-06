/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifdef _GNU_SOURCE
#include <dlfcn.h>
#endif
#include <mutex>

#ifdef ACE_INSTANCE_LOG
#include "core/common/container_scope.h"
#endif

namespace OHOS::Ace {
namespace {
#ifdef ACE_INSTANCE_LOG
constexpr const char* INSTANCE_ID_GEN_REASONS[] = {
    "scope",
    "active",
    "default",
    "singleton",
    "foreground",
    "undefined",
};
#endif
} // namespace

const std::unordered_map<AceLogTag, const char*> g_DOMAIN_CONTENTS_MAP = {
    { AceLogTag::ACE_DEFAULT_DOMAIN, "Ace" },
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
    { AceLogTag::ACE_WINDOW_SCENE, "AceWindowScene" },
    { AceLogTag::ACE_NODE_CONTAINER, "AceNodeContainer" },
    { AceLogTag::ACE_NATIVE_NODE, "AceNativeNode" },
    { AceLogTag::ACE_ISOLATED_COMPONENT, "AceIsolatedComponent" },
    { AceLogTag::ACE_DYNAMIC_COMPONENT, "AceDynamicComponent" },
    { AceLogTag::ACE_SECURITYUIEXTENSION, "AceSecurityUiExtensionComponent" },
    { AceLogTag::ACE_MARQUEE, "AceMarquee" },
    { AceLogTag::ACE_OBSERVER, "AceObserver" },
    { AceLogTag::ACE_EMBEDDED_COMPONENT, "AceEmbeddedComponent" },
    { AceLogTag::ACE_TEXT_CLOCK, "AceTextClock" },
    { AceLogTag::ACE_FOLDER_STACK, "AceFolderStack" },
    { AceLogTag::ACE_SELECT_COMPONENT, "AceSelectComponent" },
    { AceLogTag::ACE_STATE_STYLE, "AceStateStyle" },
    { AceLogTag::ACE_SEARCH, "AceSearch" },
    { AceLogTag::ACE_STATE_MGMT, "AceStateMgmt" },
    { AceLogTag::ACE_REPEAT, "AceRepeat" },
    { AceLogTag::ACE_SHEET, "AceSheet" },
    { AceLogTag::ACE_CANVAS_COMPONENT, "AceCanvasComponent" },
    { AceLogTag::ACE_SCROLL_BAR, "AceScrollBar" },
    { AceLogTag::ACE_MOVING_PHOTO, "AceMovingPhoto" },
    { AceLogTag::ACE_ARK_COMPONENT, "AceArkComponent" },
    { AceLogTag::ACE_WINDOW, "AceWindow" },
    { AceLogTag::ACE_WINDOW_PIPELINE, "AceWindowPipeline" },
    { AceLogTag::ACE_INPUTKEYFLOW, "InputKeyFlow"},
    { AceLogTag::ACE_APPBAR, "AceAppBar"},
    { AceLogTag::ACE_SELECT_OVERLAY, "AceSelectOverlay"},
    { AceLogTag::ACE_CLIPBOARD, "AceClipBoard"},
    { AceLogTag::ACE_SECURITY_COMPONENT, "AceSecurityComponent"},
    { AceLogTag::ACE_LAYOUT_INSPECTOR, "AceLayoutInspector" },
    { AceLogTag::ACE_MEDIA_QUERY, "AceMediaQuery" },
    { AceLogTag::ACE_LAYOUT, "AceLayout" },
    { AceLogTag::ACE_STYLUS, "AceStylus"},
    { AceLogTag::ACE_BADGE, "AceBadge"},
    { AceLogTag::ACE_QRCODE, "AceQRCode"},
    { AceLogTag::ACE_PROGRESS, "ACE_PROGRESS"},
    { AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "AceDrawableDescriptor"},
    { AceLogTag::ACE_LAZY_GRID, "AceLazyGrid"},
};
// initial static member object
LogLevel LogWrapper::level_ = LogLevel::DEBUG;

char LogWrapper::GetSeparatorCharacter()
{
    return '/';
}

#ifdef ACE_INSTANCE_LOG
int32_t LogWrapper::GetId()
{
    return ContainerScope::CurrentId();
}

const std::string LogWrapper::GetIdWithReason()
{
    int32_t currentId = ContainerScope::CurrentId();
    std::pair<int32_t, InstanceIdGenReason> idWithReason = ContainerScope::CurrentIdWithReason();
    return std::to_string(currentId) + ":" + std::to_string(idWithReason.first) + ":" +
           INSTANCE_ID_GEN_REASONS[static_cast<uint32_t>(idWithReason.second)];
}
#endif

static std::atomic<bool> skipBacktrace = false;

void SetSkipBacktrace(bool inputFlag)
{
    skipBacktrace.store(inputFlag);
}

bool LogBacktrace(size_t maxFrameNums)
{
    if (skipBacktrace.load()) {
        return true;
    }
    static const char* (*pfnGetTrace)(size_t, size_t);
#ifdef _GNU_SOURCE
    if (!pfnGetTrace) {
        pfnGetTrace = (decltype(pfnGetTrace))dlsym(RTLD_DEFAULT, "GetTrace");
    }
#endif
    if (!pfnGetTrace) {
        return false;
    }

    static std::mutex mtx;
    std::lock_guard lock(mtx);
    size_t skipFrameNum = 2;
    LOGI("Backtrace: skipFrameNum=%{public}zu maxFrameNums=%{public}zu\n%{public}s",
        skipFrameNum, maxFrameNums, pfnGetTrace(skipFrameNum, maxFrameNums));
    return true;
}
} // namespace OHOS::Ace
