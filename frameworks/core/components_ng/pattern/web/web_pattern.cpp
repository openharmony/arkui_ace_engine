/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/web/web_pattern.h"

#include <securec.h>
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <string_ex.h>
#include <unordered_map>
#include <vector>

#include "display_manager.h"
#include "file_uri.h"
#include "image_source.h"
#include "input_method_controller.h"
#include "parameters.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "auto_fill_type.h"
#include "page_node_info.h"

#include "adapter/ohos/capability/html/span_to_html.h"
#include "base/web/webview/arkweb_utils/arkweb_utils.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/rect.h"
#include "base/image/file_uri_helper.h"
#include "base/log/dump_log.h"
#include "base/utils/utils.h"
#include "base/mousestyle/mouse_style.h"
#include "base/utils/date_util.h"
#include "base/utils/linear_map.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "base/web/webview/arkweb_utils/arkweb_utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/common/ace_engine_ext.h"
#include "core/common/ai/image_analyzer_manager.h"
#include "core/common/container.h"
#include "core/common/ime/input_method_manager.h"
#include "core/common/recorder/event_definition.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/inspector_tree_collector.h"
#include "core/common/stylus/stylus_detector_mgr.h"
#include "core/common/udmf/udmf_client.h"
#include "core/common/udmf/unified_data.h"
#include "core/common/vibrator/vibrator_utils.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/picker/picker_data.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components/web/web_property.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/web/web_accessibility_child_tree_callback.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#include "core/components_ng/pattern/web/view_data_common.h"
#include "core/components_ng/pattern/web/transitional_node_info.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/event/event_info_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/utils/system_properties.h"
#include "frameworks/core/components_ng/base/ui_node.h"
#include "oh_window_pip.h"
#include "oh_window_comm.h"
#include "web_accessibility_session_adapter.h"
#include "web_pattern.h"
#include "nweb_handler.h"

namespace OHOS::Ace::NG {
namespace {
const std::string IMAGE_POINTER_CONTEXT_MENU_PATH = "etc/webview/ohos_nweb/context-menu.svg";
const std::string IMAGE_POINTER_ALIAS_PATH = "etc/webview/ohos_nweb/alias.svg";
const std::string AUTO_FILL_VIEW_DATA_PAGE_URL = "autofill_viewdata_origin_pageurl";
const std::string AUTO_FILL_VIEW_DATA_OTHER_ACCOUNT = "autofill_viewdata_other_account";
const std::string AUTO_FILL_START_POPUP_WINDOW = "persist.sys.abilityms.autofill.is_passwd_popup_window";
const std::string WEB_INFO_PC = "8";
const std::string WEB_INFO_TABLET = "4";
const std::string WEB_INFO_PHONE = "2";
const std::string WEB_INFO_DEFAULT = "1";
const std::string WEB_SNAPSHOT_PATH_PREFIX = "/data/storage/el2/base/cache/web/snapshot/web_frame_";
const std::string WEB_SNAPSHOT_PATH_PNG_SUFFIX = ".png";
const std::string WEB_SNAPSHOT_PATH_HEIC_SUFFIX = ".heic";
constexpr int32_t UPDATE_WEB_LAYOUT_DELAY_TIME = 20;
constexpr int32_t AUTOFILL_DELAY_TIME = 200;
constexpr int32_t IMAGE_POINTER_CUSTOM_CHANNEL = 4;
constexpr int32_t TOUCH_EVENT_MAX_SIZE = 5;
constexpr int32_t MOUSE_EVENT_MAX_SIZE = 10;
constexpr int32_t KEYEVENT_MAX_NUM = 1000;
constexpr int32_t MAXIMUM_ROTATION_DELAY_TIME = 800;
constexpr int32_t RESERVED_DEVICEID1 = 0xAAAAAAFF;
constexpr int32_t RESERVED_DEVICEID2 = 0xAAAAAAFE;
const LinearEnumMapNode<OHOS::NWeb::CursorType, MouseFormat> g_cursorTypeMap[] = {
    { OHOS::NWeb::CursorType::CT_CROSS, MouseFormat::CROSS },
    { OHOS::NWeb::CursorType::CT_HAND, MouseFormat::HAND_POINTING },
    { OHOS::NWeb::CursorType::CT_IBEAM, MouseFormat::TEXT_CURSOR },
    { OHOS::NWeb::CursorType::CT_WAIT, MouseFormat::LOADING },
    { OHOS::NWeb::CursorType::CT_HELP, MouseFormat::HELP },
    { OHOS::NWeb::CursorType::CT_EASTRESIZE, MouseFormat::WEST_EAST },
    { OHOS::NWeb::CursorType::CT_NORTHRESIZE, MouseFormat::NORTH_SOUTH },
    { OHOS::NWeb::CursorType::CT_NORTHEASTRESIZE, MouseFormat::NORTH_EAST_SOUTH_WEST },
    { OHOS::NWeb::CursorType::CT_NORTHWESTRESIZE, MouseFormat::NORTH_WEST_SOUTH_EAST },
    { OHOS::NWeb::CursorType::CT_SOUTHRESIZE, MouseFormat::NORTH_SOUTH },
    { OHOS::NWeb::CursorType::CT_SOUTHEASTRESIZE, MouseFormat::NORTH_WEST_SOUTH_EAST },
    { OHOS::NWeb::CursorType::CT_SOUTHWESTRESIZE, MouseFormat::NORTH_EAST_SOUTH_WEST },
    { OHOS::NWeb::CursorType::CT_WESTRESIZE, MouseFormat::WEST_EAST },
    { OHOS::NWeb::CursorType::CT_NORTHSOUTHRESIZE, MouseFormat::NORTH_SOUTH },
    { OHOS::NWeb::CursorType::CT_EASTWESTRESIZE, MouseFormat::WEST_EAST },
    { OHOS::NWeb::CursorType::CT_NORTHEASTSOUTHWESTRESIZE, MouseFormat::NORTH_EAST_SOUTH_WEST },
    { OHOS::NWeb::CursorType::CT_NORTHWESTSOUTHEASTRESIZE, MouseFormat::NORTH_WEST_SOUTH_EAST },
    { OHOS::NWeb::CursorType::CT_COLUMNRESIZE, MouseFormat::RESIZE_LEFT_RIGHT },
    { OHOS::NWeb::CursorType::CT_ROWRESIZE, MouseFormat::RESIZE_UP_DOWN },
    { OHOS::NWeb::CursorType::CT_MIDDLEPANNING, MouseFormat::MIDDLE_BTN_NORTH_SOUTH_WEST_EAST },
    { OHOS::NWeb::CursorType::CT_EASTPANNING, MouseFormat::MIDDLE_BTN_EAST },
    { OHOS::NWeb::CursorType::CT_NORTHPANNING, MouseFormat::MIDDLE_BTN_NORTH },
    { OHOS::NWeb::CursorType::CT_NORTHEASTPANNING, MouseFormat::MIDDLE_BTN_NORTH_EAST },
    { OHOS::NWeb::CursorType::CT_NORTHWESTPANNING, MouseFormat::MIDDLE_BTN_NORTH_WEST },
    { OHOS::NWeb::CursorType::CT_SOUTHPANNING, MouseFormat::MIDDLE_BTN_SOUTH },
    { OHOS::NWeb::CursorType::CT_SOUTHEASTPANNING, MouseFormat::MIDDLE_BTN_SOUTH_EAST },
    { OHOS::NWeb::CursorType::CT_SOUTHWESTPANNING, MouseFormat::MIDDLE_BTN_SOUTH_WEST },
    { OHOS::NWeb::CursorType::CT_WESTPANNING, MouseFormat::MIDDLE_BTN_WEST },
    { OHOS::NWeb::CursorType::CT_MOVE, MouseFormat::CURSOR_MOVE },
    { OHOS::NWeb::CursorType::CT_VERTICALTEXT, MouseFormat::HORIZONTAL_TEXT_CURSOR },
    { OHOS::NWeb::CursorType::CT_CELL, MouseFormat::CURSOR_CROSS },
    { OHOS::NWeb::CursorType::CT_PROGRESS, MouseFormat::RUNNING },
    { OHOS::NWeb::CursorType::CT_NODROP, MouseFormat::CURSOR_FORBID },
    { OHOS::NWeb::CursorType::CT_COPY, MouseFormat::CURSOR_COPY },
    { OHOS::NWeb::CursorType::CT_NONE, MouseFormat::CURSOR_NONE },
    { OHOS::NWeb::CursorType::CT_NOTALLOWED, MouseFormat::CURSOR_FORBID },
    { OHOS::NWeb::CursorType::CT_ZOOMIN, MouseFormat::ZOOM_IN },
    { OHOS::NWeb::CursorType::CT_ZOOMOUT, MouseFormat::ZOOM_OUT },
    { OHOS::NWeb::CursorType::CT_GRAB, MouseFormat::HAND_OPEN },
    { OHOS::NWeb::CursorType::CT_GRABBING, MouseFormat::HAND_GRABBING },
    { OHOS::NWeb::CursorType::CT_MIDDLE_PANNING_VERTICAL, MouseFormat::MIDDLE_BTN_NORTH_SOUTH },
    { OHOS::NWeb::CursorType::CT_MIDDLE_PANNING_HORIZONTAL, MouseFormat::MIDDLE_BTN_NORTH_SOUTH_WEST_EAST },
};

std::unordered_map<KeyCode, KeyCode> g_numPadFunctionMap = {
    { KeyCode::KEY_NUMPAD_0, KeyCode::KEY_INSERT },
    { KeyCode::KEY_NUMPAD_1, KeyCode::KEY_MOVE_END },
    { KeyCode::KEY_NUMPAD_2, KeyCode::KEY_DPAD_DOWN },
    { KeyCode::KEY_NUMPAD_3, KeyCode::KEY_PAGE_DOWN },
    { KeyCode::KEY_NUMPAD_4, KeyCode::KEY_DPAD_LEFT },
    { KeyCode::KEY_NUMPAD_5, KeyCode::KEY_CLEAR },
    { KeyCode::KEY_NUMPAD_6, KeyCode::KEY_DPAD_RIGHT },
    { KeyCode::KEY_NUMPAD_7, KeyCode::KEY_MOVE_HOME },
    { KeyCode::KEY_NUMPAD_8, KeyCode::KEY_DPAD_UP },
    { KeyCode::KEY_NUMPAD_9, KeyCode::KEY_PAGE_UP },
    { KeyCode::KEY_NUMPAD_DIVIDE, KeyCode::KEY_NUMPAD_DIVIDE },
    { KeyCode::KEY_NUMPAD_MULTIPLY, KeyCode::KEY_NUMPAD_MULTIPLY },
    { KeyCode::KEY_NUMPAD_SUBTRACT, KeyCode::KEY_NUMPAD_SUBTRACT },
    { KeyCode::KEY_NUMPAD_ADD, KeyCode::KEY_NUMPAD_ADD },
    { KeyCode::KEY_NUMPAD_DOT, KeyCode::KEY_FORWARD_DEL },
    { KeyCode::KEY_NUMPAD_ENTER, KeyCode::KEY_NUMPAD_ENTER }
};

constexpr Dimension OPTION_MARGIN = 8.0_vp;
constexpr Dimension CALIBERATE_X = 4.0_vp;
constexpr Color SELECTED_OPTION_FONT_COLOR = Color(0xff0a59f7);
constexpr Color SELECTED_OPTION_BACKGROUND_COLOR = Color(0x19254FF7);

constexpr int32_t HALF = 2;
constexpr int32_t AI_TIMEOUT_LIMIT = 200;
constexpr int32_t CHECK_PRE_SIZE = 5;
constexpr int32_t ADJUST_RATIO = 10;
constexpr int32_t DRAG_RESIZE_DELAY_TIME = 100;
constexpr int32_t DRAG_RESIZE_NO_MOVE_CHECK_TIME = 200;

struct TranslateTextExtraData {
    bool needTranslate = false;
    std::string registerObjectName = "";
    std::string registerFunctionName = "";
    std::string translateScript = "";
    std::string initScript = "";
};
TranslateTextExtraData g_translateTextData;
uint32_t g_currentControllerId = 0;
bool g_currentControllerIdStop = false;
enum PictureInPictureState {
    PIP_STATE_ENTER = 0,
    PIP_STATE_EXIT,
    PIP_STATE_PLAY,
    PIP_STATE_PAUSE,
    PIP_STATE_FAST_FORWARD,
    PIP_STATE_FAST_BACKWARD,
    PIP_STATE_RESTORE,
    PIP_STATE_HLS_ENTER,
    PIP_STATE_HLS_EXIT,
    PIP_STATE_RESIZE,
    PIP_STATE_NONE,
    PIP_STATE_UPDATE_SURFACE,
    PIP_STATE_PAGE_CLOSE,
};

struct PipData {
    uint32_t mainWindowId;
    int delegateId = -1;
    int childId = -1;
    int frameRoutingId = -1;
    int preStatus = -1;
    WeakPtr<WebPattern> pipWebPattern = nullptr;
};

std::unordered_map<uint32_t, PipData> pipCallbackMap_;
std::mutex pipCallbackMapMutex_;

bool ParseDateTimeJson(const std::string& timeJson, NWeb::DateTime& result)
{
    auto sourceJson = JsonUtil::ParseJsonString(timeJson);
    if (!sourceJson || sourceJson->IsNull()) {
        return false;
    }

    auto year = sourceJson->GetValue("year");
    if (year && year->IsNumber()) {
        result.year = year->GetInt();
    }
    auto month = sourceJson->GetValue("month");
    if (month && month->IsNumber()) {
        result.month = month->GetInt();
    }
    auto day = sourceJson->GetValue("day");
    if (day && day->IsNumber()) {
        result.day = day->GetInt();
    }
    auto hour = sourceJson->GetValue("hour");
    if (hour && hour->IsNumber()) {
        result.hour = hour->GetInt();
    }
    auto minute = sourceJson->GetValue("minute");
    if (minute && minute->IsNumber()) {
        result.minute = minute->GetInt();
    }
    return true;
}

std::string ParseTextJsonValue(const std::string& textJson)
{
    auto sourceJson = JsonUtil::ParseJsonString(textJson);
    if (!sourceJson || sourceJson->IsNull()) {
        return "";
    }
    auto value = sourceJson->GetValue("value");
    if (value && value->IsString()) {
        return value->GetString();
    }
    return "";
}

const std::string NWEB_AUTOFILL_TYPE_OFF = "off";
const std::map<std::string, AceAutoFillType> NWEB_AUTOFILL_TYPE_TO_ACE = {
    {OHOS::NWeb::NWEB_AUTOFILL_STREET_ADDRESS, AceAutoFillType::ACE_FULL_STREET_ADDRESS},
    {OHOS::NWeb::NWEB_AUTOFILL_ADDRESS_LEVEL_3, AceAutoFillType::ACE_DISTRICT_ADDRESS},
    {OHOS::NWeb::NWEB_AUTOFILL_ADDRESS_LEVEL_2, AceAutoFillType::ACE_CITY_ADDRESS},
    {OHOS::NWeb::NWEB_AUTOFILL_ADDRESS_LEVEL_1, AceAutoFillType::ACE_PROVINCE_ADDRESS},
    {OHOS::NWeb::NWEB_AUTOFILL_COUNTRY, AceAutoFillType::ACE_COUNTRY_ADDRESS},
    {OHOS::NWeb::NWEB_AUTOFILL_NAME, AceAutoFillType::ACE_PERSON_FULL_NAME},
    {OHOS::NWeb::NWEB_AUTOFILL_FAMILY_NAME, AceAutoFillType::ACE_PERSON_LAST_NAME},
    {OHOS::NWeb::NWEB_AUTOFILL_GIVEN_NAME, AceAutoFillType::ACE_PERSON_FIRST_NAME},
    {OHOS::NWeb::NWEB_AUTOFILL_TEL_NATIONAL, AceAutoFillType::ACE_PHONE_NUMBER},
    {OHOS::NWeb::NWEB_AUTOFILL_TEL, AceAutoFillType::ACE_FULL_PHONE_NUMBER},
    {OHOS::NWeb::NWEB_AUTOFILL_TEL_COUNTRY_CODE, AceAutoFillType::ACE_PHONE_COUNTRY_CODE},
    {OHOS::NWeb::NWEB_AUTOFILL_EMAIL, AceAutoFillType::ACE_EMAIL_ADDRESS},
    {OHOS::NWeb::NWEB_AUTOFILL_CC_NUMBER, AceAutoFillType::ACE_BANK_CARD_NUMBER},
    {OHOS::NWeb::NWEB_AUTOFILL_ID_CARD_NUMBER, AceAutoFillType::ACE_ID_CARD_NUMBER},
    {OHOS::NWeb::NWEB_AUTOFILL_DETAIL_INFO_WITHOUT_STREET, AceAutoFillType::ACE_DETAIL_INFO_WITHOUT_STREET},
    {OHOS::NWeb::NWEB_AUTOFILL_FORMAT_ADDRESS, AceAutoFillType::ACE_FORMAT_ADDRESS},
    {OHOS::NWeb::NWEB_AUTOFILL_NICKNAME, AceAutoFillType::ACE_NICKNAME},
    {OHOS::NWeb::NWEB_AUTOFILL_USERNAME, AceAutoFillType::ACE_USER_NAME},
    {OHOS::NWeb::NWEB_AUTOFILL_PASSWORD, AceAutoFillType::ACE_PASSWORD},
    {OHOS::NWeb::NWEB_AUTOFILL_NEW_PASSWORD, AceAutoFillType::ACE_NEW_PASSWORD},
    {OHOS::NWeb::NWEB_AUTOFILL_PASSPORT_NUMBER, AceAutoFillType::ACE_PASSPORT_NUMBER},
    {OHOS::NWeb::NWEB_AUTOFILL_VALIDITY, AceAutoFillType::ACE_VALIDITY},
    {OHOS::NWeb::NWEB_AUTOFILL_ISSUE_AT, AceAutoFillType::ACE_ISSUE_AT},
    {OHOS::NWeb::NWEB_AUTOFILL_ORGANIZATION, AceAutoFillType::ACE_ORGANIZATION},
    {OHOS::NWeb::NWEB_AUTOFILL_TAX_ID, AceAutoFillType::ACE_TAX_ID},
    {OHOS::NWeb::NWEB_AUTOFILL_ADDRESS_CITY_AND_STATE, AceAutoFillType::ACE_ADDRESS_CITY_AND_STATE},
    {OHOS::NWeb::NWEB_AUTOFILL_FLIGHT_NUMBER, AceAutoFillType::ACE_FLIGHT_NUMBER},
    {OHOS::NWeb::NWEB_AUTOFILL_LICENSE_NUMBER, AceAutoFillType::ACE_LICENSE_NUMBER},
    {OHOS::NWeb::NWEB_AUTOFILL_LICENSE_FILE_NUMBER, AceAutoFillType::ACE_LICENSE_FILE_NUMBER},
    {OHOS::NWeb::NWEB_AUTOFILL_LICENSE_PLATE, AceAutoFillType::ACE_LICENSE_PLATE},
    {OHOS::NWeb::NWEB_AUTOFILL_ENGINE_NUMBER, AceAutoFillType::ACE_ENGINE_NUMBER},
    {OHOS::NWeb::NWEB_AUTOFILL_LICENSE_CHASSIS_NUMBER, AceAutoFillType::ACE_LICENSE_CHASSIS_NUMBER},
};

const std::map<AceAutoFillType, std::string> ACE_AUTOFILL_TYPE_TO_NWEB = {
    {AceAutoFillType::ACE_FULL_STREET_ADDRESS, OHOS::NWeb::NWEB_AUTOFILL_STREET_ADDRESS},
    {AceAutoFillType::ACE_DISTRICT_ADDRESS, OHOS::NWeb::NWEB_AUTOFILL_ADDRESS_LEVEL_3},
    {AceAutoFillType::ACE_CITY_ADDRESS, OHOS::NWeb::NWEB_AUTOFILL_ADDRESS_LEVEL_2},
    {AceAutoFillType::ACE_PROVINCE_ADDRESS, OHOS::NWeb::NWEB_AUTOFILL_ADDRESS_LEVEL_1},
    {AceAutoFillType::ACE_COUNTRY_ADDRESS, OHOS::NWeb::NWEB_AUTOFILL_COUNTRY},
    {AceAutoFillType::ACE_PERSON_FULL_NAME, OHOS::NWeb::NWEB_AUTOFILL_NAME},
    {AceAutoFillType::ACE_PERSON_LAST_NAME, OHOS::NWeb::NWEB_AUTOFILL_FAMILY_NAME},
    {AceAutoFillType::ACE_PERSON_FIRST_NAME, OHOS::NWeb::NWEB_AUTOFILL_GIVEN_NAME},
    {AceAutoFillType::ACE_PHONE_NUMBER, OHOS::NWeb::NWEB_AUTOFILL_TEL_NATIONAL},
    {AceAutoFillType::ACE_FULL_PHONE_NUMBER, OHOS::NWeb::NWEB_AUTOFILL_TEL},
    {AceAutoFillType::ACE_PHONE_COUNTRY_CODE, OHOS::NWeb::NWEB_AUTOFILL_TEL_COUNTRY_CODE},
    {AceAutoFillType::ACE_EMAIL_ADDRESS, OHOS::NWeb::NWEB_AUTOFILL_EMAIL},
    {AceAutoFillType::ACE_BANK_CARD_NUMBER, OHOS::NWeb::NWEB_AUTOFILL_CC_NUMBER},
    {AceAutoFillType::ACE_ID_CARD_NUMBER, OHOS::NWeb::NWEB_AUTOFILL_ID_CARD_NUMBER},
    {AceAutoFillType::ACE_DETAIL_INFO_WITHOUT_STREET, OHOS::NWeb::NWEB_AUTOFILL_DETAIL_INFO_WITHOUT_STREET},
    {AceAutoFillType::ACE_FORMAT_ADDRESS, OHOS::NWeb::NWEB_AUTOFILL_FORMAT_ADDRESS},
    {AceAutoFillType::ACE_NICKNAME, OHOS::NWeb::NWEB_AUTOFILL_NICKNAME},
    {AceAutoFillType::ACE_USER_NAME, OHOS::NWeb::NWEB_AUTOFILL_USERNAME},
    {AceAutoFillType::ACE_PASSWORD, OHOS::NWeb::NWEB_AUTOFILL_PASSWORD},
    {AceAutoFillType::ACE_NEW_PASSWORD, OHOS::NWeb::NWEB_AUTOFILL_NEW_PASSWORD},
    {AceAutoFillType::ACE_PASSPORT_NUMBER, OHOS::NWeb::NWEB_AUTOFILL_PASSPORT_NUMBER},
    {AceAutoFillType::ACE_VALIDITY, OHOS::NWeb::NWEB_AUTOFILL_VALIDITY},
    {AceAutoFillType::ACE_ISSUE_AT, OHOS::NWeb::NWEB_AUTOFILL_ISSUE_AT},
    {AceAutoFillType::ACE_ORGANIZATION, OHOS::NWeb::NWEB_AUTOFILL_ORGANIZATION},
    {AceAutoFillType::ACE_TAX_ID, OHOS::NWeb::NWEB_AUTOFILL_TAX_ID},
    {AceAutoFillType::ACE_ADDRESS_CITY_AND_STATE, OHOS::NWeb::NWEB_AUTOFILL_ADDRESS_CITY_AND_STATE},
    {AceAutoFillType::ACE_FLIGHT_NUMBER, OHOS::NWeb::NWEB_AUTOFILL_FLIGHT_NUMBER},
    {AceAutoFillType::ACE_LICENSE_NUMBER, OHOS::NWeb::NWEB_AUTOFILL_LICENSE_NUMBER},
    {AceAutoFillType::ACE_LICENSE_FILE_NUMBER, OHOS::NWeb::NWEB_AUTOFILL_LICENSE_FILE_NUMBER},
    {AceAutoFillType::ACE_LICENSE_PLATE, OHOS::NWeb::NWEB_AUTOFILL_LICENSE_PLATE},
    {AceAutoFillType::ACE_ENGINE_NUMBER, OHOS::NWeb::NWEB_AUTOFILL_ENGINE_NUMBER},
    {AceAutoFillType::ACE_LICENSE_CHASSIS_NUMBER, OHOS::NWeb::NWEB_AUTOFILL_LICENSE_CHASSIS_NUMBER},
};

const std::map<std::string, OHOS::NWeb::NWebAutofillEvent> NWEB_AUTOFILL_EVENTS = {
    {OHOS::NWeb::NWEB_AUTOFILL_EVENT_SAVE, OHOS::NWeb::NWebAutofillEvent::SAVE},
    {OHOS::NWeb::NWEB_AUTOFILL_EVENT_FILL, OHOS::NWeb::NWebAutofillEvent::FILL},
    {OHOS::NWeb::NWEB_AUTOFILL_EVENT_UPDATE, OHOS::NWeb::NWebAutofillEvent::UPDATE},
    {OHOS::NWeb::NWEB_AUTOFILL_EVENT_CLOSE, OHOS::NWeb::NWebAutofillEvent::CLOSE},
};

std::string GetWebDebugBackGroundColor()
{
    return OHOS::system::GetParameter("web.debug.surfaceNodeBackgroundColor", "");
}

bool IsSnapshotPathValid(const std::string& snapshotPath)
{
    std::error_code ec;
    std::filesystem::path canonicalPath = std::filesystem::canonical(snapshotPath, ec);
    if (ec) {
        TAG_LOGE(AceLogTag::ACE_WEB, "blankless canonical failed:%{public}s", ec.message().c_str());
        return false;
    }
    
    if (snapshotPath.rfind(WEB_SNAPSHOT_PATH_PREFIX, 0) != 0 ||
        // 4为后缀".png"的长度
        snapshotPath.length() <= 4 ||
        // 4为后缀".png"的长度
        (snapshotPath.rfind(WEB_SNAPSHOT_PATH_PNG_SUFFIX) != snapshotPath.length() - 4 &&
        // 5为后缀".heic"的长度
         snapshotPath.rfind(WEB_SNAPSHOT_PATH_HEIC_SUFFIX) != snapshotPath.length() - 5)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "blankless the path or the format is wrong:%{public}s", snapshotPath.c_str());
        return false;
    }
    if (!std::filesystem::exists(canonicalPath, ec)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "blankless canonical path:%{public}s does not exist:%{public}s",
                 snapshotPath.c_str(), ec.message().c_str());
        return false;
    }
    return true;
}
} // namespace

void PipStartPipCallback(uint32_t controllerId, uint8_t requestId, uint64_t surfaceId)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "PipStartPipCallback %{public}u", controllerId);
    if (g_currentControllerId != controllerId) {
        TAG_LOGE(AceLogTag::ACE_WEB, "The controllerId is not equal %{public}u", g_currentControllerId);
        return;
    }
    std::lock_guard<std::mutex> lock(pipCallbackMapMutex_);
    auto it = pipCallbackMap_.find(controllerId);
    if (it != pipCallbackMap_.end()) {
        auto pip = it->second;

        OHNativeWindow *window = nullptr;
        int32_t ret = OH_NativeWindow_CreateNativeWindowFromSurfaceId(surfaceId, &window);
        if (ret != GSERROR_OK) {
            TAG_LOGI(AceLogTag::ACE_WEB, "CreateNativeWindowFromSurfaceId err:%{public}d ", ret);
            return;
        }
        if (window == nullptr) {
            TAG_LOGI(AceLogTag::ACE_WEB, "CreateNativeWindowFromSurfaceId window is null");
            return;
        }
        if (pip.pipWebPattern.Upgrade()) {
            pip.pipWebPattern.Upgrade()->SetPipNativeWindow(pip.delegateId, pip.childId, pip.frameRoutingId, window);
        }
    }
}

void PipLifecycleCallback(uint32_t controllerId, PictureInPicture_PipState state, int32_t errorCode)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "PipLifeCycleCallback, controllerId:%{public}u, "
        "PipState:%{public}d, errorCode:%{public}d", controllerId, state, errorCode);
    if (g_currentControllerId != controllerId || g_currentControllerIdStop) {
        g_currentControllerIdStop = false;
        TAG_LOGE(AceLogTag::ACE_WEB, "The controllerId is not equal %{public}u", g_currentControllerId);
        return;
    }
    uint32_t event;
    {
        std::lock_guard<std::mutex> lock(pipCallbackMapMutex_);
        auto it = pipCallbackMap_.find(controllerId);
        if (it != pipCallbackMap_.end()) {
            switch (state) {
                case PictureInPicture_PipState::STOPPED:
                    if (it->second.preStatus != PictureInPicture_PipState::ABOUT_TO_RESTORE) {
                        event = PIP_STATE_EXIT;
                    } else {
                        event = PIP_STATE_NONE;
                    }
                    break;
                case PictureInPicture_PipState::ABOUT_TO_RESTORE:
                    event = PIP_STATE_RESTORE;
                    break;
                default:
                    event = PIP_STATE_NONE;
            }
            if (event != PIP_STATE_NONE) {
                auto pip = it->second;
                if (pip.pipWebPattern.Upgrade()) {
                    pip.pipWebPattern.Upgrade()->SendPipEvent(pip.delegateId, pip.childId, pip.frameRoutingId, event);
                }
            }
            if (state != PictureInPicture_PipState::ABOUT_TO_STOP) {
                it->second.preStatus = state;
            }
        }
    }
}

void PipControlEventCallback(
    uint32_t controllerId, PictureInPicture_PipControlType actionType, PictureInPicture_PipControlStatus status)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "PipControlEventCallback, controllerId:%{public}u,"
        "actionType:%{public}d, status:%{public}d", controllerId, actionType, status);
    if (g_currentControllerId != controllerId) {
        TAG_LOGE(AceLogTag::ACE_WEB, "The controllerId is not equal %{public}u", g_currentControllerId);
        return;
    }
    uint32_t event;
    switch (actionType) {
        case PictureInPicture_PipControlType::VIDEO_PLAY_PAUSE:
            event = status == 0 ? PIP_STATE_PAUSE : PIP_STATE_PLAY;
            break;
        case PictureInPicture_PipControlType::FAST_FORWARD:
            event = PIP_STATE_FAST_FORWARD;
            break;
        case PictureInPicture_PipControlType::FAST_BACKWARD:
            event = PIP_STATE_FAST_BACKWARD;
            break;
        default:
            event = PIP_STATE_NONE;
    }
    if (event != PIP_STATE_NONE) {
        std::lock_guard<std::mutex> lock(pipCallbackMapMutex_);
        auto it = pipCallbackMap_.find(controllerId);
        if (it != pipCallbackMap_.end()) {
            auto pip = it->second;
            if (pip.pipWebPattern.Upgrade()) {
                pip.pipWebPattern.Upgrade()->SendPipEvent(pip.delegateId, pip.childId, pip.frameRoutingId, event);
            }
        }
    }
}

void PipResizeCallback(uint32_t controllerId, uint32_t width, uint32_t height, double scale)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "PipResizeCallback, controllerId:%{public}u, "
        "width:%{public}d, height:%{public}d", controllerId, width, height);
    if (g_currentControllerId != controllerId) {
        TAG_LOGE(AceLogTag::ACE_WEB, "The controllerId is not equal %{public}u", g_currentControllerId);
        return;
    }

    std::lock_guard<std::mutex> lock(pipCallbackMapMutex_);
    auto it = pipCallbackMap_.find(controllerId);
    if (it != pipCallbackMap_.end()) {
        auto pip = it->second;
        if (pip.pipWebPattern.Upgrade()) {
            pip.pipWebPattern.Upgrade()->SendPipEvent(
                pip.delegateId, pip.childId, pip.frameRoutingId, PIP_STATE_RESIZE);
        }
    }
}

constexpr int32_t SINGLE_CLICK_NUM = 1;
constexpr int32_t DOUBLE_CLICK_NUM = 2;
constexpr int32_t TRIPLE_CLICK_NUM = 3;
constexpr double DEFAULT_DBCLICK_INTERVAL = 0.5;
constexpr double DEFAULT_DBCLICK_OFFSET = 2.0;
constexpr double DEFAULT_AXIS_RATIO = -12.5;
constexpr double DEFAULT_WEB_WIDTH = 100.0;
constexpr double DEFAULT_WEB_HEIGHT = 80.0;
constexpr Dimension TOOLTIP_BORDER_WIDTH = 1.0_vp;
constexpr Dimension TOOLTIP_BORDER_RADIUS = 8.0_vp;
constexpr Dimension TOOLTIP_FONT_SIZE = 14.0_vp;
constexpr Dimension TOOLTIP_PADDING = 8.0_vp;
constexpr float TOOLTIP_MAX_PORTION = 0.35f;
constexpr float TOOLTIP_MARGIN = 10.0f;
constexpr float TOOLTIP_DELAY_MS = 700;
constexpr uint32_t ADJUST_WEB_DRAW_LENGTH = 3000;
constexpr int32_t FIT_CONTENT_LIMIT_LENGTH = 8000;
const std::string PATTERN_TYPE_WEB = "WEBPATTERN";
const std::string BUFFER_USAGE_WEB = "web";
const std::string BUFFER_USAGE_SURFACE = "web-surface-";
const std::string BUFFER_USAGE_TEXTURE = "web-texture-";
const std::string DEFAULT_WEB_TEXT_ENCODING_FORMAT = "UTF-8";
constexpr int32_t SYNC_SURFACE_QUEUE_SIZE = 8;
constexpr int32_t ASYNC_SURFACE_QUEUE_SIZE_FOR_PHONE_AND_PC = 5;
constexpr int32_t ASYNC_SURFACE_QUEUE_SIZE_FOR_OTHERS = 4;
constexpr uint32_t DEBUG_DRAGMOVEID_TIMER = 30;
// web feature params
constexpr char VISIBLE_ACTIVE_ENABLE[] = "persist.web.visible_active_enable";
constexpr char MEMORY_LEVEL_ENABEL[] = "persist.web.memory_level_enable";
const std::vector<std::string> SYNC_RENDER_SLIDE {V2::LIST_ETS_TAG, V2::SCROLL_ETS_TAG};

constexpr int32_t DEFAULT_PINCH_FINGER = 2;
constexpr double DEFAULT_PINCH_DISTANCE = 6.0;
constexpr double DEFAULT_PINCH_SCALE = 1.0;
constexpr double DEFAULT_PINCH_SCALE_MAX = 5.0;
constexpr double DEFAULT_PINCH_SCALE_MIN = 0.1;
constexpr int32_t STATUS_ZOOMIN = 1;
constexpr int32_t STATUS_ZOOMOUT = 2;
constexpr int32_t ZOOM_ERROR_COUNT_MAX = 5;
constexpr double ZOOMIN_PUBLIC_ERRAND = 0.4444;
constexpr int32_t ZOOM_CONVERT_NUM = 10;
constexpr int32_t POPUP_CALCULATE_RATIO = 2;
constexpr int32_t MIN_ACCESSIBILITY_FOCUS_SIZE = 2;

constexpr int32_t PINCH_START_TYPE = 1;
constexpr int32_t PINCH_UPDATE_TYPE = 3;
constexpr int32_t PINCH_END_TYPE = 2;
constexpr int32_t PINCH_CANCEL_TYPE = 4;

constexpr char ACCESSIBILITY_GENERIC_CONTAINER[] = "genericContainer";
constexpr char ACCESSIBILITY_IMAGE[] = "image";
constexpr char ACCESSIBILITY_PARAGRAPH[] = "paragraph";
constexpr char WEB_NODE_URL[] = "url";

const std::string IS_HINT_TYPE = "{\"isHint2Type\": true}";
const std::string STRING_LF = "\n";
const std::string DRAG_DATA_TYPE_TEXT = "general.plain-text";
const std::string DRAG_DATA_TYPE_HTML = "general.html";
const std::string DRAG_DATA_TYPE_APP_DEF = "ApplicationDefinedType";
const std::set<std::string> FILE_TYPE_SET = {"general.file", "general.audio", "general.video", "general.image"};
const std::string DRAG_DATA_TYPE_LINK = "general.hyperlink";
const std::string FAKE_DRAG_DATA_VAL = " ";
const std::string FAKE_LINK_VAL = "https://xxx.xxx.xxx";

#define WEB_ACCESSIBILITY_DELAY_TIME 100
#define GPU_ABNORMAL_VALUE (32 * 1024)
#define GPU_SERIOUS_ABNORMAL_VALUE (32 * 1024 * 1024)
#define SIZE_UNIT 1024
#define FLOAT_UNIT 100.0F
#define DECIMAL_POINTS 2
#define WEB_CHECK_FALSE_RETURN CHECK_NULL_RETURN

using Recorder::EventRecorder;

WebPattern::WebPattern()
{
    InitMagnifier();
    renderMode_ = RenderMode::ASYNC_RENDER;
    cursorType_ = OHOS::NWeb::CursorType::CT_NONE;
    viewDataCommon_ = std::make_shared<ViewDataCommon>();
    InitRotationEventCallback();
}

WebPattern::WebPattern(const std::string& webSrc, const RefPtr<WebController>& webController, RenderMode renderMode,
    bool incognitoMode, const std::string& sharedRenderProcessToken)
    : webSrc_(std::move(webSrc)), webController_(webController), renderMode_(renderMode), incognitoMode_(incognitoMode),
      sharedRenderProcessToken_(sharedRenderProcessToken)
{
    InitMagnifier();
    cursorType_ = OHOS::NWeb::CursorType::CT_NONE;
    viewDataCommon_ = std::make_shared<ViewDataCommon>();
    InitRotationEventCallback();
}

WebPattern::WebPattern(const std::string& webSrc, const SetWebIdCallback& setWebIdCallback, RenderMode renderMode,
    bool incognitoMode, const std::string& sharedRenderProcessToken)
    : webSrc_(std::move(webSrc)), setWebIdCallback_(setWebIdCallback), renderMode_(renderMode),
      incognitoMode_(incognitoMode), sharedRenderProcessToken_(sharedRenderProcessToken)
{
    InitMagnifier();
    cursorType_ = OHOS::NWeb::CursorType::CT_NONE;
    viewDataCommon_ = std::make_shared<ViewDataCommon>();
    InitRotationEventCallback();
}

WebPattern::~WebPattern()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "NWEB ~WebPattern start");
    ACE_SCOPED_TRACE("WebPattern::~WebPattern, web id = %d", GetWebId());
    UninitTouchEventListener();
    if (setWebDetachCallback_) {
        auto setWebDetachTask = [callback = setWebDetachCallback_, webId = GetWebId()]() {
            CHECK_NULL_VOID(callback);
            callback(webId);
        };
        PostTaskToUI(std::move(setWebDetachTask), "ArkUIWebviewControllerSetWebDetachTask");
    }
    if (delegate_) {
        TAG_LOGD(AceLogTag::ACE_WEB, "NWEB ~WebPattern delegate_ start SetAudioMuted");
        delegate_->SetAudioMuted(true);
        delegate_->UnRegisterNativeArkJSFunction(Recorder::WEB_OBJ_NAME);
    }

    if (observer_) {
        TAG_LOGD(AceLogTag::ACE_WEB, "NWEB ~WebPattern observer_ start NotifyDestory");
        observer_->NotifyDestory();
    }
    if (isActive_) {
        TAG_LOGD(AceLogTag::ACE_WEB, "NWEB ~WebPattern isActive_ start OnInActive");
        SetActiveStatusInner(false, true);
    }
    if (imageAnalyzerManager_) {
        imageAnalyzerManager_->ReleaseImageAnalyzer();
    }
    UninitializeAccessibility();
    HideMagnifier();
    OnTooltip("");

    {
        std::lock_guard<std::mutex> lock(pipCallbackMapMutex_);
        for (auto& it: pipController_) {
            OH_PictureInPicture_StopPip(it);
            OH_PictureInPicture_UnregisterAllResizeListeners(it);
            OH_PictureInPicture_DeletePip(it);
            pipCallbackMap_.erase(it);
        }
        pipController_.clear();
    }
    UninitRotationEventCallback();
}

void WebPattern::ShowContextSelectOverlay(const RectF& firstHandle, const RectF& secondHandle,
    TextResponseType responseType, bool handleReverse)
{
    if (contextSelectOverlay_) {
        contextSelectOverlay_->ProcessOverlay({ .animation = true });
    }
}

void WebPattern::CloseContextSelectionMenu()
{
    if (contextSelectOverlay_ && contextSelectOverlay_->IsCurrentMenuVisibile()) {
        contextSelectOverlay_->CloseOverlay(true, CloseReason::CLOSE_REASON_NORMAL);
    }
}

void WebPattern::RemovePreviewMenuNode()
{
    if (!previewImageNodeId_.has_value()) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_WEB, "RemovePreviewMenuNode");
    curContextMenuResult_ = false;
    auto previewNode =
        FrameNode::GetFrameNode(V2::IMAGE_ETS_TAG, previewImageNodeId_.value());
    CHECK_NULL_VOID(previewNode);
    auto parent = previewNode->GetParent();
    CHECK_NULL_VOID(parent);
    parent->RemoveChild(previewNode);
    previewImageNodeId_.reset();
    parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

bool WebPattern::IsPreviewMenuNotNeedShowPreview()
{
    bool isNotNeedShowPreview =
        ((isNewDragStyle_ || isAILinkMenuShow_) && IsPreviewImageNodeExist()) || imageOverlayIsSelected_;
    TAG_LOGI(AceLogTag::ACE_WEB,
        "IsPreviewMenuNotNeedShowPreview:%{public}d, for AI link preview menu %{public}d, for AI entity popup: "
        "%{public}d",
        isNotNeedShowPreview, isAILinkMenuShow_, imageOverlayIsSelected_);
    return isNotNeedShowPreview;
}

bool IsLongPreviewMenu(const std::shared_ptr<WebPreviewSelectionMenuParam>& param)
{
    return param->previewBuilder && param->responseType == ResponseType::LONG_PRESS &&
        param->type != WebElementType::TEXT;
}

void WebPattern::ConfigLongPreviewMenuParam(const std::shared_ptr<WebPreviewSelectionMenuParam>& param)
{
    auto onPreviewMenuAppear = [onAppear = std::move(param->menuParam.onDisappear),
                                onMenuShow = param->onMenuShow]() {
        TAG_LOGD(AceLogTag::ACE_WEB, "onLongPreviewMenuAppear");
        if (onAppear) {
            onAppear();
        }
        if (onMenuShow) {
            onMenuShow();
        }
    };
    param->menuParam.onAppear = std::move(onPreviewMenuAppear);

    auto onPreviewMenuDisappear = [weak = AceType::WeakClaim(this),
                                   onDisappear = std::move(param->menuParam.onDisappear),
                                   onMenuHide = param->onMenuHide]() {
        TAG_LOGD(AceLogTag::ACE_WEB, "onLongPreviewMenuDisappear");
        if (onMenuHide) {
            onMenuHide();
        }
        if (onDisappear) {
            onDisappear();
        }
        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->RemovePreviewMenuNode();
        CHECK_NULL_VOID(webPattern->contextMenuResult_);
        webPattern->contextMenuResult_->Cancel();
        webPattern->SetAILinkMenuShow(false);
    };
    param->menuParam.onDisappear = std::move(onPreviewMenuDisappear);
}

void WebPattern::SetPreviewSelectionMenu(const std::shared_ptr<WebPreviewSelectionMenuParam>& param)
{
    CHECK_NULL_VOID(param);
    if (IsLongPreviewMenu(param)) {
        ConfigLongPreviewMenuParam(param);
    } else {
        auto onPreviewMenuDisappear = [weak = AceType::WeakClaim(this),
                                       onDisappear = std::move(param->menuParam.onDisappear)]() {
            TAG_LOGD(AceLogTag::ACE_WEB, "onPreviewMenuDisappear");
            if (onDisappear) {
                onDisappear();
            }
            auto webPattern = weak.Upgrade();
            CHECK_NULL_VOID(webPattern);
            webPattern->RemovePreviewMenuNode();
            CHECK_NULL_VOID(webPattern->contextMenuResult_);
            webPattern->contextMenuResult_->Cancel();
            webPattern->SetAILinkMenuShow(false);
        };
        param->menuParam.onDisappear = std::move(onPreviewMenuDisappear);
    }
    auto key = std::make_pair(param->type, param->responseType);
    auto it = previewSelectionMenuMap_.find(key);
    if (it != previewSelectionMenuMap_.end()) {
        if (param->menuBuilder == nullptr) {
            previewSelectionMenuMap_.erase(it);
            return;
        }
        it->second = param;
        return;
    }
    previewSelectionMenuMap_[key] = param;
    TAG_LOGD(AceLogTag::ACE_WEB, "muneParam hapticFeedbackMode:%{public}d", param->menuParam.hapticFeedbackMode);
}

std::shared_ptr<WebPreviewSelectionMenuParam> WebPattern::GetPreviewSelectionMenuParams(
    const WebElementType& type, const ResponseType& responseType)
{
    auto key = std::make_pair(type, responseType);
    auto it = previewSelectionMenuMap_.find(key);
    if (it != previewSelectionMenuMap_.end()) {
        return it->second;
    }

    TAG_LOGD(AceLogTag::ACE_WEB, "The key not in previewSelectionMenuMap_");
    return nullptr;
}

void WebPattern::GetPreviewImageOffsetAndSize(bool isImage, Offset& previewOffset, SizeF& previewSize)
{
    CHECK_NULL_VOID(contextMenuParam_);
    int32_t x = 0;
    int32_t y = 0;
    int32_t width = 0;
    int32_t height = 0;
    contextMenuParam_->GetImageRect(x, y, width, height);
    if (isImage) {
        previewOffset.SetX((float)x);
        previewOffset.SetY((float)y);
        previewSize.SetWidth((float)width);
        previewSize.SetHeight((float)height);
    } else {
        previewOffset.SetX((float)x);
        previewOffset.SetY((float)y);
        if (width == 0 && height == 0) {
            previewSize.SetWidth(drawSize_.Width());
            previewSize.SetHeight(drawSize_.Height());
        } else {
            previewSize.SetWidth((float)width);
            previewSize.SetHeight((float)height);
        }
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    previewSize.SetWidth(previewSize.Width() / pipeline->GetDipScale());
    previewSize.SetHeight(previewSize.Height() / pipeline->GetDipScale());
}

RefPtr<FrameNode> WebPattern::CreatePreviewImageFrameNode(bool isImage)
{
    RemovePreviewMenuNode();
    previewImageNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto previewNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, previewImageNodeId_.value(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_RETURN(previewNode, nullptr);
    auto previewRenderContext = previewNode->GetRenderContext();
    CHECK_NULL_RETURN(previewRenderContext, nullptr);
    auto previewGesture = previewNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(previewGesture, nullptr);

    previewNode->SetDraggable(false);
    previewGesture->SetDragEvent(nullptr, { PanDirection::DOWN }, 0, Dimension(0));

    Offset previewOffset(0, 0);
    SizeF previewSize;
    GetPreviewImageOffsetAndSize(isImage, previewOffset, previewSize);
    if (previewSize.Width() <= 0 || previewSize.Height() <= 0) {
        TAG_LOGI(AceLogTag::ACE_WEB, "CreatePreviewImageFrameNode get preview size(%{public}f, %{public}f) error",
            previewSize.Width(), previewSize.Height());
        return nullptr;
    }
    previewRenderContext->UpdatePosition(
        OffsetT<Dimension>(Dimension(previewOffset.GetX()), Dimension(previewOffset.GetY())));

    auto previewProperty = previewNode->GetLayoutProperty<ImageLayoutProperty>();
    previewProperty->UpdateAutoResize(false);
    previewProperty->UpdateMarginSelfIdealSize(previewSize);
    MeasureProperty layoutConstraint;
    CalcSize idealSize = { CalcLength(Dimension(previewSize.Width(), DimensionUnit::VP).ConvertToPx()),
        CalcLength(Dimension(previewSize.Height(), DimensionUnit::VP).ConvertToPx()) };
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    previewNode->UpdateLayoutConstraint(layoutConstraint);
    TAG_LOGI(AceLogTag::ACE_WEB,
        "CreatePreviewImageFrameNode offset:%{public}f, %{public}f; size:%{public}f, %{public}f",
        previewOffset.GetX(), previewOffset.GetY(), previewSize.Width(), previewSize.Height());
    needUpdateImagePreviewParam_ = true;
    curContextMenuResult_ = true;
    return previewNode;
}

void WebPattern::CreateSnapshotImageFrameNode(const std::string& snapshotPath, uint32_t width, uint32_t height)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "blankless WebPattern::CreateSnapshotImageFrameNode");
    if (snapshotImageNodeId_.has_value()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "blankless already create snapshot image node!");
        return;
    }
    if (!IsSnapshotPathValid(snapshotPath)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "blankless snapshot path is invalid!");
        return;
    }

    if (delegate_ && (width != 0) && (height != 0)) {
        uint32_t resizeWidth = static_cast<uint32_t>(std::ceil(delegate_->ResizeWidth()));
        uint32_t resizeHeight = static_cast<uint32_t>(std::ceil(delegate_->ResizeHeight()));
        if ((width != resizeWidth) || (height != resizeHeight)) {
            TAG_LOGE(AceLogTag::ACE_WEB, "blankless snapshot size:[%{public}u, %{public}u] is invalid", width, height);
            return;
        }
        delegate_->RecordBlanklessFrameSize(width, height);
    }
    snapshotImageNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto snapshotNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, snapshotImageNodeId_.value(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_VOID(snapshotNode);
    auto pattern = snapshotNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSyncLoad(true);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto index = host->GetChildren().size();
    snapshotNode->MountToParent(host, index);

    snapshotNode->SetDraggable(false);
    auto gesture = snapshotNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    gesture->SetDragEvent(nullptr, { PanDirection::DOWN }, 0, Dimension(0));

    auto imageLayoutProperty = snapshotNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    ImageSourceInfo sourceInfo = ImageSourceInfo("file://" + snapshotPath);
    imageLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    snapshotNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    snapshotNode->MarkModifyDone();
}

void WebPattern::RemoveSnapshotFrameNode()
{
    if (!snapshotImageNodeId_.has_value()) {
        return;
    }
    if (delegate_) {
        delegate_->RecordBlanklessFrameSize(0, 0);
    }
    TAG_LOGI(AceLogTag::ACE_WEB, "blankless RemoveSnapshotFrameNode");
    auto snapshotNode = FrameNode::GetFrameNode(V2::IMAGE_ETS_TAG, snapshotImageNodeId_.value());
    snapshotImageNodeId_.reset();
    CHECK_NULL_VOID(snapshotNode);
    auto parent = snapshotNode->GetParent();
    CHECK_NULL_VOID(parent);
    parent->RemoveChild(snapshotNode);
    parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void WebPattern::SetActiveStatusInner(bool isActive, bool isForce)
{
    TAG_LOGI(AceLogTag::ACE_WEB,
        "WebPattern::SetActiveStatusInner webId:%{public}d, isActive_:%{public}d, isActive:%{public}d, "
        "isForce:%{public}d",
        GetWebId(), isActive_, isActive, isForce);
    if (!isForce) {
        if (isActive == isActive_) {
            return;
        }

        if (delegate_ && delegate_->IsActivePolicyDisable()) {
            TAG_LOGW(AceLogTag::ACE_WEB, "ArkWeb is IsActivePolicyDisable");
            return;
        }
    }
    isActive_ = isActive;
    if (delegate_) {
        isActive ? delegate_->OnActive() : delegate_->OnInactive();
    }
}

void WebPattern::UpdateImagePreviewParam()
{
    CHECK_NULL_VOID(needUpdateImagePreviewParam_);
    needUpdateImagePreviewParam_ = false;
    if (!previewImageNodeId_.has_value()) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_WEB, "UpdateImagePreviewParam");
    auto params = GetPreviewSelectionMenuParams(curElementType_, curResponseType_);
    if (!params) {
        RemovePreviewMenuNode();
        return;
    }
#ifndef ACE_UNITTEST
    auto previewNode =
        FrameNode::GetFrameNode(V2::IMAGE_ETS_TAG, previewImageNodeId_.value());
    CHECK_NULL_VOID(previewNode);
    if (curElementType_ == WebElementType::AILINK && GetDataDetectorEnable()) {
        if (!webDataDetectorAdapter_->GetPreviewMenuBuilder(params->menuBuilder, params->previewBuilder)) {
            return;
        }
    }
    ViewStackProcessor::GetInstance()->Push(previewNode);
    ViewAbstractModel::GetInstance()->BindContextMenu(
        curResponseType_, params->menuBuilder, params->menuParam, params->previewBuilder);
    ViewAbstractModel::GetInstance()->BindDragWithContextMenuParams(params->menuParam);
    ViewStackProcessor::GetInstance()->Finish();
#endif
}

void WebPattern::ShowPreviewMenu(WebElementType type)
{
    auto sourceType = contextMenuParam_->GetSourceTypeV2();
    if (sourceType == OHOS::NWeb::NWebContextMenuParams::ContextMenuSourceType::CM_ST_MOUSE) {
        curResponseType_ = ResponseType::RIGHT_CLICK;
    } else if (sourceType == OHOS::NWeb::NWebContextMenuParams::ContextMenuSourceType::CM_ST_LONG_PRESS ||
        sourceType == OHOS::NWeb::NWebContextMenuParams::ContextMenuSourceType::CM_ST_LONG_TAP) {
        curResponseType_ = ResponseType::LONG_PRESS;
    } else {
        TAG_LOGI(AceLogTag::ACE_WEB, "GetSourceType unknown, type: %{public}d", sourceType);
        return;
    }
    curElementType_ = type;
    auto params = GetPreviewSelectionMenuParams(curElementType_, curResponseType_);
    CHECK_NULL_VOID(params);
    auto host = GetHost();
    if (!host) {
        TAG_LOGE(AceLogTag::ACE_WEB, "GetHost failed");
        CHECK_NULL_VOID(delegate_);
        delegate_->OnContextMenuHide("");
        return;
    }

    if (!IsLongPreviewMenu(params)) {
        TAG_LOGI(AceLogTag::ACE_WEB, "Show web context menu");
        if (!contextSelectOverlay_) {
            contextSelectOverlay_ = AceType::MakeRefPtr<WebContextSelectOverlay>(WeakClaim(this));
        }
        CHECK_NULL_VOID(contextSelectOverlay_);
        contextSelectOverlay_->SetElementType(curElementType_);
        contextSelectOverlay_->SetResponseType(curResponseType_);
        ShowContextSelectOverlay(RectF(), RectF());
        return;
    }

    CHECK_NULL_VOID(isNewDragStyle_ || (type == WebElementType::AILINK));
    auto previewNode = CreatePreviewImageFrameNode(type == WebElementType::IMAGE);
    if (!previewNode) {
        TAG_LOGI(AceLogTag::ACE_WEB, "CreatePreviewImageFrameNode failed");
        previewImageNodeId_.reset();
        CHECK_NULL_VOID(delegate_);
        delegate_->OnContextMenuHide("");
        return;
    }
    isAILinkMenuShow_ = (type == WebElementType::AILINK);
    TAG_LOGI(AceLogTag::ACE_WEB, "ShowPreviewMenu for AI link: %{public}d", isAILinkMenuShow_);
    host->AddChild(previewNode);
    previewNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    previewNode->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

bool WebPattern::CopySelectionMenuParams(SelectOverlayInfo& selectInfo,
    const WebElementType& elementType, const ResponseType& responseType)
{
    auto selectMenuParams = GetPreviewSelectionMenuParams(elementType, responseType);
    CHECK_NULL_RETURN(selectMenuParams, false);
    CHECK_NULL_RETURN(selectMenuParams->menuBuilder, false);

    selectInfo.menuInfo.menuBuilder = selectMenuParams->menuBuilder;
    selectInfo.menuCallback.onAppear = selectMenuParams->menuParam.onAppear;
    selectInfo.menuCallback.onDisappear = selectMenuParams->menuParam.onDisappear;
    selectInfo.menuCallback.onMenuShow = selectMenuParams->onMenuShow;
    selectInfo.menuCallback.onMenuHide = selectMenuParams->onMenuHide;
    return true;
}

void WebPattern::OnContextMenuShow(const std::shared_ptr<BaseEventInfo>& info, bool isRichtext, bool result)
{
    TAG_LOGI(AceLogTag::ACE_WEB,
        "OnContextMenuShow result:%{public}d, isNewDragStyle_:%{public}d", result, isNewDragStyle_);
    curContextMenuResult_ = result;
    auto *eventInfo = TypeInfoHelper::DynamicCast<ContextMenuEvent>(info.get());
    CHECK_NULL_VOID(eventInfo);
    contextMenuParam_ = eventInfo->GetParam();
    CHECK_NULL_VOID(contextMenuParam_);
    contextMenuResult_ = eventInfo->GetContextMenuResult();
    CHECK_NULL_VOID(contextMenuResult_);
    bool isImage = false;
    bool isHyperLink = false;
    bool isText = false;
    bool isAILink = !contextMenuParam_->GetLinkUrl().empty() && contextMenuParam_->IsAILink() &&
                GetDataDetectorEnable() && webDataDetectorAdapter_->GetDataDetectorEnablePrewiew();
    auto copyOption =
        delegate_ ? delegate_->GetCopyOptionMode() : OHOS::NWeb::NWebPreference::CopyOptionMode::LOCAL_DEVICE;
    isAILink = isAILink && copyOption != OHOS::NWeb::NWebPreference::CopyOptionMode::NONE;
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWENTY)) {
        CHECK_NULL_VOID(delegate_);
        int hitTestResult = delegate_->GetLastHitTestResult();
        TAG_LOGI(AceLogTag::ACE_WEB, "OnContextMenuShow hitTestResult:%{public}d, isAILink:%{public}d", hitTestResult,
            contextMenuParam_->IsAILink());
        bool isEdit = false;
        switch (static_cast<WebHitTestType>(hitTestResult)) {
            case WebHitTestType::IMG:
                isImage = true;
                break;
            case WebHitTestType::HTTP_IMG:
                isImage = true;
                isHyperLink = true;
                break;
            case WebHitTestType::HTTP:
                isHyperLink = true;
                break;
            case WebHitTestType::EDIT:
                isEdit = true;
                break;
            default:
                break;
        }

        // since async hittest, reconfirm
        isImage = isImage && contextMenuParam_->GetMediaTypeV2() ==
                                 OHOS::NWeb::NWebContextMenuParams::ContextMenuMediaType::CM_MT_IMAGE;
        isHyperLink =
            isHyperLink && !isImage && !contextMenuParam_->GetLinkUrl().empty() && !contextMenuParam_->IsAILink();
        isText = (isEdit || contextMenuParam_->GetMediaTypeV2() ==
            OHOS::NWeb::NWebContextMenuParams::ContextMenuMediaType::CM_MT_TEXT) && !contextMenuParam_->IsAILink();
    } else {
        isImage = (contextMenuParam_->GetLinkUrl().empty() &&
                   (contextMenuParam_->GetMediaType() ==
                       OHOS::NWeb::NWebContextMenuParams::ContextMenuMediaType::CM_MT_IMAGE));
    }
    if (isRichtext) {
        if (!contextSelectOverlay_) {
            contextSelectOverlay_ = AceType::MakeRefPtr<WebContextSelectOverlay>(WeakClaim(this));
        }
        CHECK_NULL_VOID(contextSelectOverlay_);
        contextSelectOverlay_->SetElementType(WebElementType::NONE);
        contextSelectOverlay_->SetResponseType(ResponseType::RIGHT_CLICK);
        ShowContextSelectOverlay(RectF(), RectF());
        return;
    }
    CHECK_NULL_VOID(result);
    TAG_LOGD(AceLogTag::ACE_WEB, "OnContextMenuShow isImage:%{public}d, isHyperLink:%{public}d, isText:%{public}d",
        isImage, isHyperLink, isText);
    if (isImage) {
        ShowPreviewMenu(WebElementType::IMAGE);
    } else if (isHyperLink) {
        ShowPreviewMenu(WebElementType::LINK);
    } else if (isText) {
        ShowPreviewMenu(WebElementType::TEXT);
    } else if (isAILink) {
        CHECK_NULL_VOID(webDataDetectorAdapter_);
        if (!webDataDetectorAdapter_->SetPreviewMenuLink(contextMenuParam_->GetLinkUrl())) {
            return;
        }
        ShowPreviewMenu(WebElementType::AILINK);
    }
}

void WebPattern::OnCloseContextMenu()
{
    isAILinkMenuShow_ = false;
    CloseContextSelectionMenu();
    RemovePreviewMenuNode();
    curContextMenuResult_ = false;
}

void WebPattern::OnContextMenuHide()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern OnContextMenuHide");
    OnCloseContextMenu();
    CHECK_NULL_VOID(contextMenuResult_);
    contextMenuResult_->Cancel();
}

bool WebPattern::NeedSoftKeyboard() const
{
    if (delegate_) {
        return delegate_->NeedSoftKeyboard();
    }
    return false;
}

void WebPattern::EnableSecurityLayer(bool isNeedSecurityLayer)
{
    if (!renderContextForSurface_) {
        TAG_LOGE(AceLogTag::ACE_WEB, "WebPattern::EnableSecurityLayer, renderContextForSurface_ is null");
        return;
    }
    renderContextForSurface_->SetSecurityLayer(isNeedSecurityLayer);
}

void WebPattern::OnAttachToMainTree()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "OnAttachToMainTree WebId %{public}d", GetWebId());
    isAttachedToMainTree_ = true;
    InitSlideUpdateListener();
    // report component is in foreground.
    delegate_->OnRenderToForeground();

    if (delegate_->GetPageFinishedState()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnAttachToMainTree delegate_ pageFinishedState is true");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frontend = pipeline->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->AddToPageEventController(host);
}

void WebPattern::OnDetachFromMainTree()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "OnDetachFromMainTree WebId %{public}d", GetWebId());
    isAttachedToMainTree_ = false;
    // report component is in background.
    delegate_->OnRenderToBackground();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto frontend = pipelineContext->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->ReleasePageEvent(host, true, false);
}

void WebPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    SetRotation(pipeline->GetTransformHint());

    host->GetRenderContext()->UpdateClipEdge(true);
    if (!renderContextForSurface_) {
        renderContextForSurface_ = RenderContext::Create();
        static RenderContext::ContextParam param = { RenderContext::ContextType::HARDWARE_SURFACE,
            "RosenWeb" };
        CHECK_NULL_VOID(renderContextForSurface_);
        renderContextForSurface_->InitContext(false, param);
        // Disable hardware composition when initializing to fix visual artifacts when switching to a new webview.
        auto surfaceNode = OHOS::Rosen::RSBaseNode::ReinterpretCast<OHOS::Rosen::RSSurfaceNode>(GetSurfaceRSNode());
        CHECK_NULL_VOID(surfaceNode);
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnAttachToFrameNode, web id = %{public}d", GetWebId());
        ACE_SCOPED_TRACE("WebPattern::OnAttachToFrameNode, web id = %d", GetWebId());
        surfaceNode->SetHardwareEnabled(true, Rosen::SelfDrawingNodeType::DEFAULT, false);
    }

    if (!renderContextForPopupSurface_) {
        renderContextForPopupSurface_ = RenderContext::Create();
        CHECK_NULL_VOID(renderContextForPopupSurface_);
        static RenderContext::ContextParam popupParam  = { RenderContext::ContextType::HARDWARE_SURFACE,
            "RosenWebPopup" };
        renderContextForPopupSurface_->InitContext(false, popupParam);
    }
    host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    pipeline->AddNodesToNotifyMemoryLevel(host->GetId());

    auto callbackId = pipeline->RegisterTransformHintChangeCallback([weak = WeakClaim(this)](uint32_t transform) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            TAG_LOGD(AceLogTag::ACE_WEB, "OnAttach to frame node, set transform:%{public}u", transform);
            pattern->SetRotation(transform);
        }
    });
    UpdateTransformHintChangedCallbackId(callbackId);
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
    pipeline->RegisterListenerForTranslate(WeakClaim(RawPtr(host)));
    EventRecorder::Get().OnAttachWeb(host);
#endif
}

void WebPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(delegate_);
    isFocus_ = false;
    delegate_->OnBlur();
    OnQuickMenuDismissed();

    auto id = frameNode->GetId();
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
    pipeline->RemoveWindowSizeChangeCallback(id);
    pipeline->RemoveNodesToNotifyMemoryLevel(id);

    if (HasTransformHintChangedCallbackId()) {
        pipeline->UnregisterTransformHintChangedCallback(transformHintChangedCallbackId_.value_or(-1));
    }
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
    if (UiSessionManager::GetInstance()->GetWebFocusRegistered()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnDetachFromFrameNode, unregister event report callback");
        auto report = GetAccessibilityEventReport();
        CHECK_NULL_VOID(report);
        report->UnregisterCallback();
    }
    pipeline->UnRegisterListenerForTranslate(id);
    EventRecorder::Get().OnDetachWeb(id);
#endif
}

void WebPattern::SetRotation(uint32_t rotation)
{
    if (renderMode_ == RenderMode::SYNC_RENDER || rotation_ == rotation) {
        return;
    }
    rotation_ = rotation;
    CHECK_NULL_VOID(renderSurface_);
    renderSurface_->SetTransformHint(rotation);
    CHECK_NULL_VOID(delegate_);
    delegate_->SetTransformHint(rotation);
}

void WebPattern::InitEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    InitTouchEvent(gestureHub);
    InitDragEvent(gestureHub);
    InitPanEvent(gestureHub);
    InitPinchEvent(gestureHub);

    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    InitMouseEvent(inputHub);
    InitHoverEvent(inputHub);

    auto focusHub = eventHub->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitFocusEvent(focusHub);
}

void WebPattern::InitConfigChangeCallback(const RefPtr<PipelineContext> &context)
{
    auto langTask = [weak = AceType::WeakClaim(this)]() {
        auto WebPattern = weak.Upgrade();
        CHECK_NULL_VOID(WebPattern);
        WebPattern->UpdateLocale();
    };
    context->SetConfigChangedCallback(GetHost()->GetId(), std::move(langTask));
}

void WebPattern::InitFeatureParam()
{
    isVisibleActiveEnable_ = system::GetBoolParameter(VISIBLE_ACTIVE_ENABLE, true);
    isMemoryLevelEnable_ = system::GetBoolParameter(MEMORY_LEVEL_ENABEL, true);
}

void WebPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (panEvent_) {
        return;
    }
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        // Determine if there is already a fixed nested scroll mode.
        if (!pattern->GetIsFixedNestedScrollMode() || !pattern->GetNestedScrollParent()) {
            pattern->SetParentScrollable();
        }
        pattern->UpdateTouchpadSlidingStatus(event);
        pattern->GetParentAxis();
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragMove(event);
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleFlingMove(info);
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() { return; };
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
        { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
    gestureHub->AddPanEvent(panEvent_, panDirection, DEFAULT_PAN_FINGER, distanceMap);
    gestureHub->SetPanEventType(GestureTypeName::WEBSCROLL);
    gestureHub->SetOnGestureJudgeNativeBegin([](const RefPtr<NG::GestureInfo>& gestureInfo,
                                                const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
            if (!gestureInfo) {
                // info is null, default case to continue
                return GestureJudgeResult::CONTINUE;
            }
            if (gestureInfo->GetType() != GestureTypeName::WEBSCROLL) {
                // not web pan event type, continue
                return GestureJudgeResult::CONTINUE;
            }
            auto inputEventType = gestureInfo->GetInputEventType();
            if (inputEventType == InputEventType::AXIS) {
                // axis event type of web pan, dispatch to panEvent to process
                return GestureJudgeResult::CONTINUE;
            } else if (inputEventType == InputEventType::MOUSE_BUTTON) {
                // mouse button event type of web pan, dispatch to DragEvent to process
                return GestureJudgeResult::REJECT;
            }
            // In other cases, the panEvent is used by default
            return GestureJudgeResult::CONTINUE;
        });
}

void WebPattern::HandleFlingMove(const GestureEvent& event)
{
    if (snapshotImageNodeId_.has_value()) {
        TAG_LOGD(AceLogTag::ACE_WEB, "blankless during snapshot image, no need to handle fling move!");
        return;
    }
    if ((event.GetInputEventType() == InputEventType::AXIS) &&
        (event.GetSourceTool() == SourceTool::TOUCHPAD)) {
        CHECK_NULL_VOID(delegate_);
        std::vector<int32_t> pressedCodes;
        auto gesturePressedCodes = event.GetPressedKeyCodes();
        for (auto pCode : gesturePressedCodes) {
            pressedCodes.push_back(static_cast<int32_t>(pCode));
        }
        auto localLocation = event.GetLocalLocation();
        delegate_->WebHandleTouchpadFlingEvent(localLocation.GetX(), localLocation.GetY(),
                                               event.GetVelocity().GetVelocityX(),
                                               event.GetVelocity().GetVelocityY(),
                                               pressedCodes);
    }
}

void WebPattern::HandleDragMove(const GestureEvent& event)
{
    if (snapshotImageNodeId_.has_value()) {
        TAG_LOGD(AceLogTag::ACE_WEB, "blankless during snapshot image, no need to handle drag move!");
        return;
    }
    if (event.GetInputEventType() == InputEventType::AXIS) {
        CHECK_NULL_VOID(delegate_);
        auto localLocation = event.GetLocalLocation();
        std::vector<int32_t> pressedCodes;
        auto gesturePressedCodes = event.GetPressedKeyCodes();
        for (auto pCode : gesturePressedCodes) {
            pressedCodes.push_back(static_cast<int32_t>(pCode));
        }
        TAG_LOGD(AceLogTag::ACE_WEB, "HandleDragMove Axis deltaX: %{public}f deltaY: %{public}f",
            event.GetDelta().GetX(), event.GetDelta().GetY());
        delegate_->WebHandleAxisEvent(localLocation.GetX(), localLocation.GetY(),
            event.GetDelta().GetX() / DEFAULT_AXIS_RATIO, event.GetDelta().GetY() / DEFAULT_AXIS_RATIO,
            pressedCodes, static_cast<int32_t>(event.GetSourceTool()));
    }
}

void WebPattern::InitPinchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (pinchGesture_) {
        if (gestureHub->WillRecreateGesture()) {
            gestureHub->AddGesture(pinchGesture_);
        }
        return;
    }
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        if (event.GetSourceTool() == SourceTool::TOUCHPAD) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->startPageScale_ = pattern->pageScale_;
            TAG_LOGD(AceLogTag::ACE_WEB, "InitPinchEvent actionStartTask startPageScale: %{public}f",
                pattern->startPageScale_);

            pattern->startPinchScale_ = event.GetScale();
            pattern->preScale_ = pattern->startPinchScale_;
            pattern->zoomOutSwitch_ = false;
            pattern->zoomStatus_ = 0;
            pattern->zoomErrorCount_ = 0;
            TAG_LOGD(AceLogTag::ACE_WEB, "InitPinchEvent actionStartTask startPinchScale: %{public}f",
                pattern->startPinchScale_);

            pattern->HandleScaleGestureStart(event);
        }
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        ACE_SCOPED_TRACE("WebPattern::InitPinchEvent actionUpdateTask");
        if (event.GetSourceTool() == SourceTool::TOUCHPAD) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            TAG_LOGD(AceLogTag::ACE_WEB, "InitPinchEvent actionUpdateTask event scale:%{public}f: ", event.GetScale());
            pattern->HandleScaleGestureChange(event);
        }
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        if (event.GetSourceTool() == SourceTool::TOUCHPAD) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleScaleGestureEnd(event);
        }
    };
    auto actionCancelTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        if (event.GetSourceTool() == SourceTool::TOUCHPAD) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleScaleGestureCancel(event);
        }
    };

    pinchGesture_ = MakeRefPtr<PinchGesture>(DEFAULT_PINCH_FINGER, DEFAULT_PINCH_DISTANCE);
    pinchGesture_->SetPriority(GesturePriority::Parallel);
    pinchGesture_->SetOnActionStartId(actionStartTask);
    pinchGesture_->SetOnActionUpdateId(actionUpdateTask);
    pinchGesture_->SetOnActionEndId(actionEndTask);
    pinchGesture_->SetOnActionCancelId(actionCancelTask);
    gestureHub->AddGesture(pinchGesture_);
}

bool WebPattern::CheckZoomStatus(const double& curScale)
{
    int32_t curScaleNew = (int32_t)(curScale * 100);
    int32_t preScaleNew = (int32_t)(preScale_ * 100);

    // check zoom status
    if ((zoomStatus_ == STATUS_ZOOMOUT && curScaleNew - preScaleNew < 0) && zoomErrorCount_ < ZOOM_ERROR_COUNT_MAX) {
        zoomErrorCount_++;
        TAG_LOGI(AceLogTag::ACE_WEB, "CheckZoomStatus zoomStatus = zoomout && curScale < preScale,"
                                     "ignore date.");
        return false;
    } else if ((zoomStatus_ == STATUS_ZOOMIN && curScaleNew - preScaleNew > 0) &&
               zoomErrorCount_ < ZOOM_ERROR_COUNT_MAX) {
        zoomErrorCount_++;
        TAG_LOGI(AceLogTag::ACE_WEB, "CheckZoomStatus zoomStatus = zoomin && curScale >= preScale,"
                                     "ignore date.");
        return false;
    } else {
        // nothing
    }
    return true;
}

bool WebPattern::ZoomOutAndIn(const double& curScale, double& scale)
{
    int32_t curScaleNew = (int32_t)(curScale * 100);
    int32_t preScaleNew = (int32_t)(preScale_ * 100);

    // zoom out
    if (GreatOrEqual(curScale, preScale_)) {
        if (GreatOrEqual(preScale_, DEFAULT_PINCH_SCALE)) {
            // start page scale > 1
            if (GreatOrEqual(curScale, DEFAULT_PINCH_SCALE) && !zoomOutSwitch_) {
                scale = curScale * startPageScale_;

                TAG_LOGD(AceLogTag::ACE_WEB, "ZoomOutAndIn curScale * pageScale_= %{public}f", scale);
            } else {
                TAG_LOGD(AceLogTag::ACE_WEB, "ZoomOutAndIn curScale < DEFAULT_PINCH_SCALE");
                scale = DEFAULT_PINCH_SCALE + (curScale - startPinchScale_);
            }
        } else {
            // The scale is from 0.4 to 0.5, the scale conversion should be from 1.0 to 1.1
            // once
            if (zoomStatus_ == STATUS_ZOOMIN) {
                TAG_LOGI(AceLogTag::ACE_WEB, "ZoomOutAndIn Switch from zoomin to zoomout.");
                // must be page scale form 0.4 to 1
                scale = pageScale_;
                // reset
                startPinchScale_ = preScale_;
                zoomOutSwitch_ = true;
            } else {
                TAG_LOGD(AceLogTag::ACE_WEB, "ZoomOutAndIn zoomStatus_ = STATUS_ZOOMOUT curScale < 1.0");
                scale = DEFAULT_PINCH_SCALE + (curScale - startPinchScale_);
            }
        }
        zoomStatus_ = STATUS_ZOOMOUT;
        // zoom in
    } else {
        // from zoonout to zoomin
        if (zoomStatus_ == STATUS_ZOOMOUT) {
            TAG_LOGI(AceLogTag::ACE_WEB, "ZoomOutAndIn Switch from zoomout to zoomin.");
            // reset
            startPinchScale_ = preScale_;
            zoomOutSwitch_ = false;
        }

        if (curScaleNew == preScaleNew) {
            TAG_LOGI(AceLogTag::ACE_WEB, "ZoomOutAndIn curScaleNew == preScaleNew");
            return false;
        }

        scale = curScale;

        zoomStatus_ = STATUS_ZOOMIN;
    }
    return true;
}

void WebPattern::HandleScaleGestureChange(const GestureEvent& event)
{
    if (snapshotImageNodeId_.has_value()) {
        TAG_LOGD(AceLogTag::ACE_WEB, "blankless during snapshot image, no need to handle scale gesture change!");
        return;
    }
    CHECK_NULL_VOID(delegate_);

    double curScale = event.GetScale();
    if (NearEqual(curScale, preScale_)) {
        TAG_LOGI(AceLogTag::ACE_WEB, "HandleScaleGestureChange curScale == preScale");
        return;
    }

    if (LessOrEqual(curScale, 0.0) || LessOrEqual(preScale_, 0.0)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "HandleScaleGestureChange invalid scale");
        return;
    }

    TAG_LOGD(AceLogTag::ACE_WEB,
        "HandleScaleGestureChange curScale:%{public}f, preScale: %{public}f, "
        "zoomStatus: %{public}d, pageScale: %{public}f, startPinchScale: %{public}f, startPageScale: %{public}f",
        curScale, preScale_, zoomStatus_, pageScale_, startPinchScale_, startPageScale_);

    if (!CheckZoomStatus(curScale)) {
        return;
    }

    zoomErrorCount_ = 0;

    double newScale = curScale / preScale_;
    double newOriginScale = GetNewOriginScale(event.GetScale());

    double centerX = event.GetPinchCenter().GetX();
    double centerY = event.GetPinchCenter().GetY();
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto offset = frameNode->GetOffsetRelativeToWindow();
    TAG_LOGD(AceLogTag::ACE_WEB,
        "HandleScaleGestureChangeV2 curScale:%{public}f newScale: %{public}f"
        " centerX: %{public}f centerY: %{public}f",
        curScale, newScale, centerX, centerY);

    // Plan two
    delegate_->ScaleGestureChangeV2(
        PINCH_UPDATE_TYPE, newScale, newOriginScale, centerX - offset.GetX(), centerY - offset.GetY());

    preScale_ = curScale;
}

double WebPattern::getZoomOffset(double& scale) const
{
    double offset = DEFAULT_PINCH_SCALE - scale;
    if (LessOrEqual(offset, 0.0)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "getZoomOffset curScale < preScale");
        return 0.0;
    }
    return offset * ZOOM_CONVERT_NUM * ZOOMIN_PUBLIC_ERRAND;
}

double WebPattern::GetNewScale(double& scale) const
{
    if (GreatOrEqual(scale, DEFAULT_PINCH_SCALE_MAX)) {
        scale = DEFAULT_PINCH_SCALE_MAX;

        TAG_LOGE(AceLogTag::ACE_WEB, "GetNewScale scale > DEFAULT_PINCH_SCALE_MAX");
        return DEFAULT_PINCH_SCALE;
    }

    double newScale = 0.0;
    if (GreatOrEqual(scale, DEFAULT_PINCH_SCALE)) {
        // In order to achieve a sequence similar to scale, eg. 1.1, 1.2, 1.3
        if (zoomStatus_ == STATUS_ZOOMOUT) {
            newScale = scale / pageScale_;
            // scale > 1.0 when scale form zoomout to zoomin
        } else if (zoomStatus_ == STATUS_ZOOMIN) {
            scale = startPageScale_ * scale;
            if (GreatNotEqual(scale, 0.0)) {
                newScale = scale / pageScale_;
            } else {
                newScale = DEFAULT_PINCH_SCALE_MIN;
                scale = DEFAULT_PINCH_SCALE;

                TAG_LOGE(AceLogTag::ACE_WEB, "GetNewScale scale < 0.0");
            }
        }

        // scale max
        if (GreatOrEqual(newScale, DEFAULT_PINCH_SCALE_MAX)) {
            newScale = DEFAULT_PINCH_SCALE_MAX;
            scale = DEFAULT_PINCH_SCALE_MAX;

            TAG_LOGI(AceLogTag::ACE_WEB, "GetNewScale newScale > DEFAULT_PINCH_SCALE_MAX");
        }
    } else {
        TAG_LOGD(AceLogTag::ACE_WEB, "GetNewScale getZoomOffset:%{public}f", getZoomOffset(scale));

        scale = startPageScale_ - getZoomOffset(scale);
        if (GreatNotEqual(scale, 0.0)) {
            newScale = scale / pageScale_;
        } else {
            newScale = DEFAULT_PINCH_SCALE_MIN;
            scale = DEFAULT_PINCH_SCALE;

            TAG_LOGE(AceLogTag::ACE_WEB, "GetNewScale scale < 0.0");
        }

        TAG_LOGD(AceLogTag::ACE_WEB,
            "GetNewScale scale: %{public}f, newScale: %{public}f, pageScale: %{public}f, startPageScale: %{public}f",
            scale, newScale, pageScale_, startPageScale_);
    }

    // scale min
    if (LessNotEqual(newScale, DEFAULT_PINCH_SCALE_MIN)) {
        newScale = DEFAULT_PINCH_SCALE_MIN;
        scale = DEFAULT_PINCH_SCALE;

        TAG_LOGE(AceLogTag::ACE_WEB, "GetNewScale newScale < DEFAULT_PINCH_SCALE_MIN");
    }

    return newScale;
}

double WebPattern::GetNewOriginScale(double originScale) const
{
    double newScale = 0.0;
    if (zoomStatus_ == STATUS_ZOOMOUT) {
        newScale = DEFAULT_PINCH_SCALE_MAX;
    } else if (zoomStatus_ == STATUS_ZOOMIN) {
        newScale = DEFAULT_PINCH_SCALE_MIN;
    }

    return newScale;
}

void WebPattern::HandleScaleGestureStart(const GestureEvent& event)
{
    if (snapshotImageNodeId_.has_value()) {
        TAG_LOGD(AceLogTag::ACE_WEB, "blankless during snapshot image, no need to handle scale gesture start!");
        return;
    }
    CHECK_NULL_VOID(delegate_);

    double scale = event.GetScale();

    double centerX = event.GetPinchCenter().GetX();
    double centerY = event.GetPinchCenter().GetY();
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto offset = frameNode->GetOffsetRelativeToWindow();

    delegate_->ScaleGestureChangeV2(
        PINCH_START_TYPE, scale, event.GetScale(), centerX - offset.GetX(), centerY - offset.GetY());
}

void WebPattern::HandleScaleGestureEnd(const GestureEvent& event)
{
    if (snapshotImageNodeId_.has_value()) {
        TAG_LOGD(AceLogTag::ACE_WEB, "blankless during snapshot image, no need to handle scale gesture end!");
        return;
    }
    CHECK_NULL_VOID(delegate_);

    double scale = event.GetScale();

    double centerX = event.GetPinchCenter().GetX();
    double centerY = event.GetPinchCenter().GetY();
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto offset = frameNode->GetOffsetRelativeToWindow();

    delegate_->ScaleGestureChangeV2(
        PINCH_END_TYPE, scale, event.GetScale(), centerX - offset.GetX(), centerY - offset.GetY());
}

void WebPattern::HandleScaleGestureCancel(const GestureEvent& event)
{
    if (snapshotImageNodeId_.has_value()) {
        TAG_LOGD(AceLogTag::ACE_WEB, "blankless during snapshot image, no need to handle scale gesture cancel!");
        return;
    }
    CHECK_NULL_VOID(delegate_);

    double scale = event.GetScale();

    double centerX = event.GetPinchCenter().GetX();
    double centerY = event.GetPinchCenter().GetY();
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto offset = frameNode->GetOffsetRelativeToWindow();

    delegate_->ScaleGestureChangeV2(
        PINCH_CANCEL_TYPE, scale, event.GetScale(), centerX - offset.GetX(), centerY - offset.GetY());
}

void WebPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (touchEvent_) {
        return;
    }

    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnTooltip("");
        if (info.GetChangedTouches().empty()) {
            return;
        }

        // only handle touch event
        if (info.GetSourceDevice() != SourceType::TOUCH) {
            return;
        }
        pattern->isMouseEvent_ = false;
        pattern->HandleTouchEvent(info);
    };
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void WebPattern::InitMouseEvent(const RefPtr<InputEventHub>& inputHub)
{
    if (mouseEvent_) {
        return;
    }

    auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TouchEventInfo touchEventInfo("touchEvent");
        if (EventInfoConvertor::ConvertMouseToTouchIfNeeded(info, touchEventInfo)) {
            TAG_LOGI(AceLogTag::ACE_WEB, "Convert mouse event to touch event: button %{public}d, action %{public}d.",
                (int)info.GetButton(), (int)info.GetAction());
            touchEventInfo.SetTouchEventsEnd(true);
            pattern->HandleTouchEvent(touchEventInfo);
            return;
        }
        pattern->HandleMouseEvent(info);
    };

    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent_);
}

void WebPattern::InitHoverEvent(const RefPtr<InputEventHub>& inputHub)
{
    if (hoverEvent_) {
        return;
    }

    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        MouseInfo info;
        info.SetAction(isHover ? MouseAction::HOVER : MouseAction::HOVER_EXIT);
        pattern->WebOnMouseEvent(info);
    };

    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent_);
}

void WebPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    if (snapshotImageNodeId_.has_value()) {
        TAG_LOGD(AceLogTag::ACE_WEB, "blankless during snapshot image, no need to handle touch event!");
        return;
    }
    touchEventInfo_ = info;
    const auto& changedPoint = info.GetChangedTouches().front();
    if (changedPoint.GetTouchType() == TouchType::DOWN ||
        changedPoint.GetTouchType() == TouchType::UP) {
        if (touchEventQueue_.size() < TOUCH_EVENT_MAX_SIZE) {
            touchEventQueue_.push(info);
        }
    }

    if (changedPoint.GetTouchType() == TouchType::DOWN) {
        HandleTouchDown(info, false);
        return;
    }
    if (changedPoint.GetTouchType() == TouchType::MOVE) {
        HandleTouchMove(info, false);
        return;
    }
    if (changedPoint.GetTouchType() == TouchType::UP) {
        HandleTouchUp(info, false);
        return;
    }
    if (changedPoint.GetTouchType() == TouchType::CANCEL) {
        HandleTouchCancel(info);
        return;
    }
}

void WebPattern::HandleMouseEvent(MouseInfo& info)
{
    if (snapshotImageNodeId_.has_value()) {
        TAG_LOGD(AceLogTag::ACE_WEB, "blankless during snapshot image, no need to handle mouse event!");
        return;
    }
    if (info.GetAction() != MouseAction::MOVE) {
        TAG_LOGI(AceLogTag::ACE_WEB,
            "WebPattern::HandleMouseEvent, web id %{public}d, Action %{public}d, Button %{public}d",
            GetWebId(), static_cast<int32_t>(info.GetAction()), static_cast<int32_t>(info.GetButton()));
    }

    ACE_SCOPED_TRACE(
        "WebPattern::HandleMouseEvent, web id %d, Action %d, Button %d",
        GetWebId(), static_cast<int32_t>(info.GetAction()), static_cast<int32_t>(info.GetButton()));

    isMouseEvent_ = true;
    mouseInfo_ = info;
    if (info.GetButton() == MouseButton::LEFT_BUTTON
    && (info.GetAction() == MouseAction::PRESS || info.GetAction() == MouseAction::RELEASE)) {
        if (mouseInfoQueue_.size() < MOUSE_EVENT_MAX_SIZE) {
            mouseInfoQueue_.push(info);
        }
    }
    WebOnMouseEvent(info);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto button = static_cast<MouseButton>(info.GetButton());
    bool isSupportMouse = button == MouseButton::LEFT_BUTTON
        || button == MouseButton::RIGHT_BUTTON || button == MouseButton::MIDDLE_BUTTON;
    if (delegate_ && delegate_->HasOnNativeEmbedGestureEventV2() && isSupportMouse) {
        auto gestureHub = eventHub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        if (info.GetAction() == MouseAction::PRESS) {
            // start RecognizerDelay
            gestureHub->SetRecognizerDelayStatus(RecognizerDelayStatus::START);
        } else if (info.GetAction() == MouseAction::RELEASE) {
            gestureHub->SetRecognizerDelayStatus(RecognizerDelayStatus::NONE);
        }
    }

    auto mouseEventCallback = eventHub->GetOnMouseEvent();
    CHECK_NULL_VOID(mouseEventCallback);
    mouseEventCallback(info);
}

void WebPattern::WebOnMouseEvent(const MouseInfo& info)
{
    if (snapshotImageNodeId_.has_value()) {
        return;
    }
    if (mouseEventDeviceId_ != info.GetDeviceId()) {
        mouseEventDeviceId_ = info.GetDeviceId();
    }
    CHECK_NULL_VOID(delegate_);
    auto localLocation = info.GetLocalLocation();
    if ((info.GetAction() == MouseAction::PRESS) ||
        (info.GetButton() == MouseButton::LEFT_BUTTON) ||
        (info.GetButton() == MouseButton::RIGHT_BUTTON) ||
        (info.GetButton() == MouseButton::BACK_BUTTON) ||
        (info.GetButton() == MouseButton::FORWARD_BUTTON)) {
        OnTooltip("");
    }
    if (info.GetAction() == MouseAction::PRESS && !GetNativeEmbedModeEnabledValue(false)) {
        delegate_->OnContextMenuHide("");
        WebRequestFocus();
    }

    // set touchup false when using mouse
    isTouchUpEvent_ = false;
    if (info.GetButton() == MouseButton::LEFT_BUTTON && info.GetAction() == MouseAction::RELEASE) {
        if (isReceivedArkDrag_) {
            TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop Do not reset drag action when dragging,"
                "drop/cancel/end event will do this");
            return;
        }
        ResetDragAction();
    }
    isHoverExit_ = false;
    if (info.GetAction() == MouseAction::HOVER_EXIT) {
        TAG_LOGI(AceLogTag::ACE_WEB,
            "Set cursor to pointer when mouse pointer is hover exit.");
        OnCursorChange(OHOS::NWeb::CursorType::CT_POINTER, nullptr);
        isHoverExit_ = true;
        MouseInfo changedInfo;
        changedInfo.SetAction(MouseAction::HOVER_EXIT);
        changedInfo.SetLocalLocation(Offset(mouseHoveredX_, mouseHoveredY_));
        WebSendMouseEvent(changedInfo, SINGLE_CLICK_NUM);
        return;
    } else if (info.GetAction() == MouseAction::HOVER && isMouseLocked_) {
        OnCursorChange(OHOS::NWeb::CursorType::CT_LOCK, nullptr);
    }
    int32_t clickNum = HandleMouseClickEvent(info);

    WebSendMouseEvent(info, clickNum);

    if (info.GetAction() == MouseAction::MOVE) {
        mouseHoveredX_ = localLocation.GetX();
        mouseHoveredY_ = localLocation.GetY();
    }
}

void WebPattern::WebSendMouseEvent(const MouseInfo& info, int32_t clickNum)
{
    if (delegate_->IsFileSelectorShow() && info.GetAction() == MouseAction::HOVER_EXIT) {
        TAG_LOGW(AceLogTag::ACE_WEB, "WebPattern::WebSendMouseEvent blocked when FileSelector show.");
        return;
    }
    std::vector<int32_t> pressedCodes {};
    std::vector<KeyCode> keyCode = info.GetPressedKeyCodes();
    for (auto pCode : keyCode) {
        pressedCodes.push_back(static_cast<int32_t>(pCode));
    }

    std::shared_ptr<NWebMouseEventImpl> mouseEvent =
        std::make_shared<NWebMouseEventImpl>(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY(),
        info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY(),
        static_cast<int32_t>(info.GetButton()), static_cast<int32_t>(info.GetAction()),
        clickNum, pressedCodes);
    delegate_->WebOnMouseEvent(mouseEvent);
}

void WebPattern::ResetDragAction()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDraggable(false);
    auto eventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->ResetDragActionForWeb();

    if (!isDragging_) {
        return;
    }

    isDragging_ = false;
    isReceivedArkDrag_ = false;
    isDragStartFromWeb_ = false;
    // cancel drag action to avoid web kernel can't process other input event
    CHECK_NULL_VOID(delegate_);
    delegate_->HandleDragEvent(0, 0, DragAction::DRAG_CANCEL);
    gestureHub->CancelDragForWeb();
}

Offset WebPattern::GetDragOffset() const
{
    Offset webDragOffset;
    int x = 0;
    int y = 0;
    if (delegate_ && delegate_->dragData_) {
        delegate_->dragData_->GetDragStartPosition(x, y);
    }

    webDragOffset.SetX(x);
    webDragOffset.SetY(y);

    return webDragOffset;
}

SizeF WebPattern::GetDragPixelMapSize() const
{
    SizeF pixelMapSize;
    int32_t width = 0;
    int32_t height = 0;
    RefPtr<PixelMap> pixelMap = nullptr;
    if (delegate_) {
        pixelMap = delegate_->GetDragPixelMap();
    }
    if (pixelMap) {
        width = pixelMap->GetWidth();
        height = pixelMap->GetHeight();
    }
    pixelMapSize = SizeF(width, height);
    return pixelMapSize;
}

int32_t WebPattern::HandleMouseClickEvent(const MouseInfo& info)
{
    if (info.GetButton() != MouseButton::LEFT_BUTTON || info.GetAction() != MouseAction::PRESS) {
        return SINGLE_CLICK_NUM;
    }
    auto localLocation = info.GetLocalLocation();
    MouseClickInfo clickInfo;
    clickInfo.x = localLocation.GetX();
    clickInfo.y = localLocation.GetY();
    clickInfo.start = info.GetTimeStamp();
    if (mouseClickQueue_.empty()) {
        mouseClickQueue_.push(clickInfo);
        return SINGLE_CLICK_NUM;
    }
    std::chrono::duration<float> timeout_ = clickInfo.start - mouseClickQueue_.back().start;
    double offsetX = clickInfo.x - mouseClickQueue_.back().x;
    double offsetY = clickInfo.y - mouseClickQueue_.back().y;
    double offset = sqrt(offsetX * offsetX + offsetY * offsetY);
    if (timeout_.count() < DEFAULT_DBCLICK_INTERVAL && offset < DEFAULT_DBCLICK_OFFSET) {
        if (mouseClickQueue_.size() == SINGLE_CLICK_NUM) {
            mouseClickQueue_.push(clickInfo);
            return DOUBLE_CLICK_NUM;
        } else if (mouseClickQueue_.size() == DOUBLE_CLICK_NUM) {
            mouseClickQueue_.push(clickInfo);
            return TRIPLE_CLICK_NUM;
        } else if (mouseClickQueue_.size() == TRIPLE_CLICK_NUM) {
            mouseClickQueue_.pop();
            mouseClickQueue_.push(clickInfo);
            return TRIPLE_CLICK_NUM;
        }
    }
    if (mouseClickQueue_.size()) {
        std::queue<MouseClickInfo> empty;
        swap(empty, mouseClickQueue_);
        mouseClickQueue_.push(clickInfo);
    }
    return SINGLE_CLICK_NUM;
}

bool WebPattern::HandleDoubleClickEvent(const MouseInfo& info)
{
    if (info.GetButton() != MouseButton::LEFT_BUTTON || info.GetAction() != MouseAction::PRESS) {
        return false;
    }
    auto localLocation = info.GetLocalLocation();
    MouseClickInfo clickInfo;
    clickInfo.x = localLocation.GetX();
    clickInfo.y = localLocation.GetY();
    clickInfo.start = info.GetTimeStamp();
    if (mouseClickQueue_.empty()) {
        mouseClickQueue_.push(clickInfo);
        return false;
    }
    std::chrono::duration<float> timeout_ = clickInfo.start - mouseClickQueue_.back().start;
    double offsetX = clickInfo.x - mouseClickQueue_.back().x;
    double offsetY = clickInfo.y - mouseClickQueue_.back().y;
    double offset = sqrt(offsetX * offsetX + offsetY * offsetY);
    if (timeout_.count() < DEFAULT_DBCLICK_INTERVAL && offset < DEFAULT_DBCLICK_OFFSET) {
        SendDoubleClickEvent(clickInfo);
        std::queue<MouseClickInfo> empty;
        swap(empty, mouseClickQueue_);
        return true;
    }
    if (mouseClickQueue_.size() == 1) {
        mouseClickQueue_.push(clickInfo);
        return false;
    }
    mouseClickQueue_.pop();
    mouseClickQueue_.push(clickInfo);
    return false;
}

void WebPattern::SendDoubleClickEvent(const MouseClickInfo& info)
{
    CHECK_NULL_VOID(delegate_);
    delegate_->OnMouseEvent(info.x, info.y, MouseButton::LEFT_BUTTON, MouseAction::PRESS, DOUBLE_CLICK_NUM);
}

bool WebPattern::GenerateDragDropInfo(NG::DragDropInfo& dragDropInfo)
{
    if (delegate_) {
        dragDropInfo.pixelMap = delegate_->GetDragPixelMap();
    }

    if (dragDropInfo.pixelMap) {
        isW3cDragEvent_ = true;
        return true;
    }

    return false;
}

NG::DragDropInfo WebPattern::HandleOnDragStart(const RefPtr<OHOS::Ace::DragEvent>& info)
{
    if (snapshotImageNodeId_.has_value()) {
        TAG_LOGD(AceLogTag::ACE_WEB, "blankless during snapshot image, no need to handle on drag start!");
        return NG::DragDropInfo();
    }
    isDragging_ = true;
    isReceivedArkDrag_ = true;
    isDragStartFromWeb_ = true;
    NG::DragDropInfo dragDropInfo;
    if (GenerateDragDropInfo(dragDropInfo)) {
        auto frameNode = GetHost();
        CHECK_NULL_RETURN(frameNode, dragDropInfo);
        CHECK_NULL_RETURN(delegate_, dragDropInfo);
        CHECK_NULL_RETURN(delegate_->dragData_, dragDropInfo);
        // get drag pixel map successfully, disable next drag util received web kernel drag callback
        frameNode->SetDraggable(false);
        RefPtr<UnifiedData> aceUnifiedData = UdmfClient::GetInstance()->CreateUnifiedData();
        std::string fileName = delegate_->dragData_->GetImageFileName();
        std::string plainContent = delegate_->dragData_->GetFragmentText();
        std::string htmlContent = delegate_->dragData_->GetFragmentHtml();
        std::string linkUrl = delegate_->dragData_->GetLinkURL();
        std::string linkTitle = delegate_->dragData_->GetLinkTitle();
        if (!fileName.empty()) {
            OnDragFileNameStart(aceUnifiedData, fileName);
        } else {
            TAG_LOGW(AceLogTag::ACE_WEB, "DragDrop event start, dragdata has no image file uri, just pass");
        }
        if (!plainContent.empty()) {
            isDragEndMenuShow_ = true;
            UdmfClient::GetInstance()->AddPlainTextRecord(aceUnifiedData, plainContent);
        }
        if (!htmlContent.empty()) {
            isDragEndMenuShow_ = true;
            UdmfClient::GetInstance()->AddHtmlRecord(aceUnifiedData, htmlContent, "");
        }
        if (!linkUrl.empty()) {
            isDragEndMenuShow_ = false;
            UdmfClient::GetInstance()->AddLinkRecord(aceUnifiedData, linkUrl, linkTitle);
            TAG_LOGI(AceLogTag::ACE_WEB, "web DragDrop event Start, linkUrl size:%{public}zu", linkUrl.size());
        }
        UdmfClient::GetInstance()->SetTagProperty(aceUnifiedData, "records_to_entries_data_format");
        info->SetData(aceUnifiedData);
        HandleOnDragEnter(info);
        return dragDropInfo;
    }
    return dragDropInfo;
}

void WebPattern::OnDragFileNameStart(const RefPtr<UnifiedData>& aceUnifiedData, const std::string& fileName)
{
    isDragEndMenuShow_ = false;
    std::string fullName;
    if (delegate_->tempDir_.empty()) {
        fullName = "/data/storage/el2/base/haps/entry/temp/dragdrop/" + fileName;
    } else {
        fullName = delegate_->tempDir_ + "/dragdrop/" + fileName;
    }
    AppFileService::ModuleFileUri::FileUri fileUri(fullName);
    TAG_LOGI(AceLogTag::ACE_WEB, "web DragDrop event Start, FileUri:%{public}s, image path:%{public}s",
        fileUri.ToString().c_str(), fullName.c_str());
    std::vector<std::string> urlVec;
    std::string udmfUri = fileUri.ToString();
    urlVec.emplace_back(udmfUri);
    UdmfClient::GetInstance()->AddFileUriRecord(aceUnifiedData, urlVec);
}

void WebPattern::HandleOnDropMove(const RefPtr<OHOS::Ace::DragEvent>& info)
{
    if (snapshotImageNodeId_.has_value()) {
        TAG_LOGD(AceLogTag::ACE_WEB, "blankless during snapshot image, no need to handle on drag move!");
        return;
    }
    if (!isDragging_) {
        return;
    }

    if (!isW3cDragEvent_) {
        return;
    }

    CHECK_NULL_VOID(delegate_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto viewScale = pipelineContext->GetViewScale();
    int32_t globalX = static_cast<int32_t>(info->GetX()) * viewScale;
    int32_t globalY = static_cast<int32_t>(info->GetY()) * viewScale;
    auto offset = GetCoordinatePoint();
    globalX = static_cast<int32_t>(globalX - offset.value_or(OffsetF()).GetX());
    globalY = static_cast<int32_t>(globalY - offset.value_or(OffsetF()).GetY());
    delegate_->HandleDragEvent(globalX, globalY, DragAction::DRAG_OVER);
}

void WebPattern::InitCommonDragDropEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);

    isDisableDrag_ = false;
    // disable drag
    frameNode->SetDraggable(false);
    // init common drag drop event
    gestureHub->InitDragDropEvent();
    InitWebEventHubDragDropStart(eventHub);
    InitWebEventHubDragDropEnd(eventHub);
    InitWebEventHubDragMove(eventHub);
    TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop WebEventHub init drag event ok");
}

void WebPattern::InitWebEventHubDragDropStart(const RefPtr<WebEventHub>& eventHub)
{
    auto onDragStartId = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& info,
                             const std::string& extraParams) -> NG::DragDropInfo {
        NG::DragDropInfo dragDropInfo;
        CHECK_NULL_RETURN(info, dragDropInfo);
        TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop WebEventHub drag start,"
            " x:%{public}lf, y:%{public}lf", info->GetX(), info->GetY());
        auto pattern = weak.Upgrade();
        if (pattern) {
            TAG_LOGI(AceLogTag::ACE_WEB,
                "DragDrop event WebEventHub onDragStartId, x:%{public}lf, y:%{public}lf, webId:%{public}d",
                info->GetX(), info->GetY(), pattern->GetWebId());
            pattern->dropX_ = 0;
            pattern->dropY_ = 0;
            return pattern->HandleOnDragStart(info);
        }
        return dragDropInfo;
    };

    auto onDragEnterId = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& info,
                             const std::string& extraParams) {
        CHECK_NULL_VOID(info);
        TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop WebEventHub drag enter,"
            " x:%{public}lf, y:%{public}lf", info->GetX(), info->GetY());
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TAG_LOGI(AceLogTag::ACE_WEB,
            "DragDrop event WebEventHub onDragEnterId, x:%{public}lf, y:%{public}lf, webId:%{public}d",
            info->GetX(), info->GetY(), pattern->GetWebId());
        pattern->isW3cDragEvent_ = true;
        pattern->isDragging_ = true;
        pattern->isReceivedArkDrag_ = true;
        pattern->dropX_ = 0;
        pattern->dropY_ = 0;
        return pattern->HandleOnDragEnter(info);
    };

    // set custom OnDragStart function
    eventHub->SetOnDragStart(std::move(onDragStartId));
    eventHub->SetOnDragEnter(std::move(onDragEnterId));
}

void WebPattern::InitWebEventHubDragMove(const RefPtr<WebEventHub>& eventHub)
{
    auto onDragMoveId = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& info,
                             const std::string& extraParams) {
        CHECK_NULL_VOID(info);
        static uint32_t dragMoveCnt = 0;
        if ((dragMoveCnt % DEBUG_DRAGMOVEID_TIMER) == 0) {
            TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop  WebEventHub drag move,"
                " x:%{public}lf, y:%{public}lf", info->GetX(), info->GetY());
        }
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if ((dragMoveCnt++ % DEBUG_DRAGMOVEID_TIMER) == 0) {
            TAG_LOGI(AceLogTag::ACE_WEB,
                "DragDrop event WebEventHub onDragMoveId, x:%{public}lf, y:%{public}lf, webId:%{public}d",
                info->GetX(), info->GetY(), pattern->GetWebId());
        }
        if (!pattern->isDragging_) {
            return;
        }

        // update drag status
        info->SetResult(pattern->GetDragAcceptableStatus());

        pattern->HandleOnDropMove(info);
    };
    // set custom OnDragStart function
    eventHub->SetOnDragMove(std::move(onDragMoveId));
}

void WebPattern::InitWebEventHubDragDropEnd(const RefPtr<WebEventHub>& eventHub)
{
    auto onDragDropId = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& info,
                             const std::string& extraParams) {
        CHECK_NULL_VOID(info);
        TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop WebEventHub drag drop,"
            " x:%{public}lf, y:%{public}lf", info->GetX(), info->GetY());
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TAG_LOGI(AceLogTag::ACE_WEB,
            "DragDrop event WebEventHub onDragDropId, x:%{public}lf, y:%{public}lf, webId:%{public}d",
            info->GetX(), info->GetY(), pattern->GetWebId());
        if (!pattern->isDragging_) {
            return;
        }
        pattern->dropX_ = info->GetX();
        pattern->dropY_ = info->GetY();
        pattern->HandleOnDragDrop(info);
    };

    auto onDragLeaveId = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& info,
                             const std::string& extraParams) {
        CHECK_NULL_VOID(info);
        TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop WebEventHub drag leave,"
            " x:%{public}lf, y:%{public}lf", info->GetX(), info->GetY());
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TAG_LOGI(AceLogTag::ACE_WEB,
            "DragDrop event WebEventHub onDragLeaveId, x:%{public}lf, y:%{public}lf, webId:%{public}d",
            info->GetX(), info->GetY(), pattern->GetWebId());
        pattern->HandleOnDragLeave(info->GetX(), info->GetY());
    };

    auto onDragEndId = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& info) {
        CHECK_NULL_VOID(info);
        TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop WebEventHub drag end,"
            " x:%{public}lf, y:%{public}lf", info->GetX(), info->GetY());
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TAG_LOGI(AceLogTag::ACE_WEB,
            "DragDrop event WebEventHub onDragEndId, x:%{public}lf, y:%{public}lf, webId:%{public}d",
            info->GetX(), info->GetY(), pattern->GetWebId());
        pattern->HandleDragEnd(pattern->dropX_, pattern->dropY_);
    };
    // set custom OnDragStart function
    eventHub->SetOnDragEnd(std::move(onDragEndId));
    eventHub->SetOnDragLeave(std::move(onDragLeaveId));
    eventHub->SetOnDrop(std::move(onDragDropId));
}

bool WebPattern::IsImageDrag()
{
    if (delegate_) {
        return delegate_->IsImageDrag();
    }
    return false;
}

DragRet WebPattern::GetDragAcceptableStatus()
{
    OHOS::NWeb::NWebDragData::DragOperation status = delegate_->GetDragAcceptableStatus();
    int newDragOperation = static_cast<int>(status);
    // Fixed the issue that the corner icon blinks when you enter the move text box.
    if (lastDragOperation_ != newDragOperation) {
        lastDragOperation_ = newDragOperation;
        return DragRet::DRAG_DEFAULT;
    }
    if (status == OHOS::NWeb::NWebDragData::DragOperation::DRAG_OPERATION_COPY ||
        status == OHOS::NWeb::NWebDragData::DragOperation::DRAG_OPERATION_LINK) {
        return DragRet::ENABLE_DROP;
    } else if (status == OHOS::NWeb::NWebDragData::DragOperation::DRAG_OPERATION_MOVE) {
        return DragRet::DRAG_DEFAULT;
    }
    return DragRet::DISABLE_DROP;
}

bool WebPattern::NotifyStartDragTask(bool isDelayed)
{
    if (isDisableDrag_ || isTouchUpEvent_) {
        TAG_LOGW(AceLogTag::ACE_WEB, "DragDrop disable drag in web. isDisableDrag_:%{public}d,"
            "isTouchUpEvent_:%{public}d, isDelayed:%{public}d", isDisableDrag_, isTouchUpEvent_, isDelayed);
        if (isDelayed) {
            CHECK_NULL_RETURN(delegate_, false);
            delegate_->HandleDragEvent(0, 0, DragAction::DRAG_CANCEL);
        }
        return false;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(delegate_, false);
    auto manager = pipeline->GetDragDropManager();
    if (!manager || manager->IsDragging() || manager->IsMSDPDragging()) {
        TAG_LOGW(AceLogTag::ACE_WEB, "DragDrop, It's already dragging now, can't start drag task.");
        delegate_->HandleDragEvent(0, 0, DragAction::DRAG_CANCEL);
        return false;
    }
    isDragging_ = true;
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    auto eventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, false);
    if (curContextMenuResult_ && (!(isNewDragStyle_ || isAILinkMenuShow_) || !previewImageNodeId_.has_value())) {
        TAG_LOGI(AceLogTag::ACE_WEB,
            "preview menu is not displayed, and the app is notified to close the long-press menu");
        delegate_->OnContextMenuHide("");
    }
    // received web kernel drag callback, enable drag
    frameNode->SetDraggable(true);
    gestureHub->SetPixelMap(delegate_->GetDragPixelMap());
    if (!IsPreviewImageNodeExist()) {
        StartVibraFeedback("longPress.light");
    }
    if (!isMouseEvent_) {
        // mouse drag does not need long press action
        gestureHub->StartLongPressActionForWeb();
    }
    TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop enable drag and start drag task for web,"
        "is mouse event: %{public}d", isMouseEvent_);
    bool result = gestureHub->StartDragTaskForWeb();
    if (!result && isMouseEvent_) {
        TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop start drag task for web fail, reset drag action");
        ResetDragAction();
    }
    return true;
}

void WebPattern::InitDragEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (dragEvent_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto userOnDragStartFunc = eventHub->GetOnDragStart();
    if (userOnDragStartFunc) {
        isDisableDrag_ = true;
        return;
    }

    InitCommonDragDropEvent(gestureHub);

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        int32_t x = info.GetGlobalPoint().GetX();
        int32_t y = info.GetGlobalPoint().GetY();
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TAG_LOGI(AceLogTag::ACE_WEB,
            "DragDrop event gestureHub actionStartTask x:%{public}d, y:%{public}d, webId:%{public}d",
            x, y, pattern->GetWebId());
        pattern->HandleDragStart(x, y);
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        return;
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        int32_t x = info.GetGlobalPoint().GetX();
        int32_t y = info.GetGlobalPoint().GetY();
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TAG_LOGI(AceLogTag::ACE_WEB,
            "DragDrop event gestureHub actionEndTask x:%{public}d, y:%{public}d, webId:%{public}d",
            x, y, pattern->GetWebId());
        pattern->HandleDragEnd(x, y);
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TAG_LOGI(AceLogTag::ACE_WEB,
            "DragDrop event gestureHub actionCancelTask  webId:%{public}d", pattern->GetWebId());
        pattern->HandleDragCancel();
    };

    dragEvent_ = MakeRefPtr<DragEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->SetCustomDragEvent(dragEvent_, { PanDirection::ALL }, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
    gestureHub->SetRecognizerDelayStatus(RecognizerDelayStatus::NONE);
    TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop, init drag event done, isReceivedArkDrag_ is %{public}d",
        (int)isReceivedArkDrag_);
}

void WebPattern::HandleDragStart(int32_t x, int32_t y)
{
    if (snapshotImageNodeId_.has_value()) {
        TAG_LOGD(AceLogTag::ACE_WEB, "blankless during snapshot image, no need to handle drag start!");
        return;
    }
    TAG_LOGI(AceLogTag::ACE_WEB,
        "HandleDragStart DragDrop event actionStart, isDragStartFromWeb_:%{public}d, isMouseEvent_:%{public}d",
        (int)isDragStartFromWeb_, (int)isMouseEvent_);
    if (!isDragStartFromWeb_ && !isMouseEvent_) {
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        frameNode->SetDraggable(false);
        auto eventHub = frameNode->GetEventHub<WebEventHub>();
        CHECK_NULL_VOID(eventHub);
        auto gestureHub = eventHub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->ResetDragActionForWeb();
        isDragging_ = false;
        isReceivedArkDrag_ = false;
        // cancel drag action to avoid web kernel can't process other input event
        CHECK_NULL_VOID(delegate_);
        delegate_->HandleDragEvent(0, 0, DragAction::DRAG_CANCEL);
        gestureHub->CancelDragForWeb();
    }
    if (!isDragStartFromWeb_ && isMouseEvent_) {
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        auto eventHub = frameNode->GetEventHub<WebEventHub>();
        CHECK_NULL_VOID(eventHub);
        auto gestureHub = eventHub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->SetMouseDragMonitorState(true);
        isSetMouseDragMonitorState = true;
    }
}

void WebPattern::HandleOnDragEnter(const RefPtr<OHOS::Ace::DragEvent>& info)
{
    if (snapshotImageNodeId_.has_value()) {
        TAG_LOGD(AceLogTag::ACE_WEB, "blankless during snapshot image, no need to handle on drag enter!");
        return;
    }
    if (!delegate_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    int32_t globalX = static_cast<int32_t>(info->GetX());
    int32_t globalY = static_cast<int32_t>(info->GetY());
    auto viewScale = pipelineContext->GetViewScale();
    auto offset = GetCoordinatePoint();
    int32_t localX = static_cast<int32_t>(globalX - offset.value_or(OffsetF()).GetX()) * viewScale;
    int32_t localY = static_cast<int32_t>(globalY - offset.value_or(OffsetF()).GetY()) * viewScale;

    // fake drag data when enter
    delegate_->GetOrCreateDragData();
    // use summary to set fake data
    if (!isDragStartFromWeb_) {
        ClearDragData();
        SetFakeDragData(info);
    }
    delegate_->HandleDragEvent(localX, localY, DragAction::DRAG_ENTER);
    // RequestFocus to show the carret frame_caret
    WebRequestFocus();
}

void WebPattern::HandleOnDragDropLink(RefPtr<UnifiedData> aceData)
{
    CHECK_NULL_VOID(aceData);
    CHECK_NULL_VOID(delegate_);
    CHECK_NULL_VOID(delegate_->dragData_);
    // hyperlink
    std::string linkUrl;
    std::string linkTitle;
    UdmfClient::GetInstance()->GetLinkEntry(aceData, linkUrl, linkTitle);
    if (!linkUrl.empty()) {
        delegate_->dragData_->SetLinkURL(linkUrl);
        delegate_->dragData_->SetLinkTitle(linkTitle);
        TAG_LOGI(AceLogTag::ACE_WEB,
            "DragDrop event WebEventHub onDragDropId, linkUrl size:%{public}zu", linkUrl.size());
    } else {
        TAG_LOGW(AceLogTag::ACE_WEB,
            "DragDrop event WebEventHub onDragDropId, linkUrl is empty");
    }
}

void WebPattern::HandleOnDragDropFile(RefPtr<UnifiedData> aceData)
{
    CHECK_NULL_VOID(aceData);
    CHECK_NULL_VOID(delegate_);
    CHECK_NULL_VOID(delegate_->dragData_);
    // file
    std::vector<std::string> urlVec;
    UdmfClient::GetInstance()->GetFileUriEntry(aceData, urlVec);
    TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop event WebEventHub onDragDropId,"
        "url array size is:%{public}zu", urlVec.size());
    delegate_->dragData_->ClearImageFileNames();
    for (std::string url : urlVec) {
        TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop event WebEventHub onDragDropId,"
            "url get from udmf:%{public}zu", url.length());
        AppFileService::ModuleFileUri::FileUri fileUri(url);
        TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop event WebEventHub onDragDropId,"
            "fileUri ToString:%{public}zu", fileUri.ToString().length());
        std::string uriRealPath = FileUriHelper::GetRealPath(url);
        if (uriRealPath.empty()) {
            TAG_LOGW(AceLogTag::ACE_WEB, "DragDrop event WebEventHub onDragDropId, url is empty ");
            continue;
        }
        int access_result = access(uriRealPath.c_str(), F_OK);
        if (access_result == 0) {
            TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop event WebEventHub onDragDropId,url real path:%{public}zu",
                uriRealPath.length());
            delegate_->dragData_->SetFileUri(uriRealPath);
        } else {
            TAG_LOGW(AceLogTag::ACE_WEB,
                "DragDrop event WebEventHub onDragDropId, url can't access, "
                "uriRealPath:%{public}zu, access_result:%{public}d",
                uriRealPath.length(), access_result);
        }
    }
}

void WebPattern::ResetDragStateValue()
{
    isDragging_ = false;
    isReceivedArkDrag_ = false;
    isW3cDragEvent_ = false;
    isDragStartFromWeb_ = false;
}

void WebPattern::HandleOnDragDrop(const RefPtr<OHOS::Ace::DragEvent>& info)
{
    if (snapshotImageNodeId_.has_value()) {
        return;
    }
    ResetDragStateValue();
    CHECK_NULL_VOID(delegate_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto viewScale = pipelineContext->GetViewScale();
    auto offset = GetCoordinatePoint();
    int32_t localX = static_cast<int32_t>(info->GetX() - offset.value_or(OffsetF()).GetX()) * viewScale;
    int32_t localY = static_cast<int32_t>(info->GetY() - offset.value_or(OffsetF()).GetY()) * viewScale;
    ClearDragData();
    RefPtr<UnifiedData> aceData = info->GetData();
    // get data from ace(from udmf), and send it to chromium
    if (aceData && aceData->GetSize() >= 1) {
        TAG_LOGI(AceLogTag::ACE_WEB,
            "DragDrop event WebEventHub onDragDropId, size:%{public}" PRId64 "", aceData->GetSize());
        CHECK_NULL_VOID(delegate_->dragData_);
        // plain text
        std::string plain = UdmfClient::GetInstance()->GetPlainTextEntry(aceData);
        if (!plain.empty()) {
            delegate_->dragData_->SetFragmentText(plain);
            TAG_LOGI(AceLogTag::ACE_WEB,
                "DragDrop event WebEventHub onDragDropId, plain size:%{public}zu", plain.size());
        }
        // html
        std::string htmlContent;
        std::string plainContent;
        UdmfClient::GetInstance()->GetHtmlEntry(aceData, htmlContent, plainContent);
        if (!htmlContent.empty()) {
            delegate_->dragData_->SetFragmentHtml(htmlContent);
            TAG_LOGI(AceLogTag::ACE_WEB,
                "DragDrop event WebEventHub onDragDropId, htmlContent size:%{public}zu", htmlContent.size());
        }
        // spanstring
        std::vector<uint8_t> spanString = UdmfClient::GetInstance()->GetSpanStringEntry(aceData);
        if (!spanString.empty()) {
            std::string htmlStr = OHOS::Ace::SpanToHtml::ToHtml(spanString);
            delegate_->dragData_->SetFragmentHtml(htmlStr);
            TAG_LOGI(AceLogTag::ACE_WEB,
                "DragDrop event WebEventHub onDragDropId, spanstring to html success, html size:%{public}zu",
                htmlStr.size());
        }
        // link
        HandleOnDragDropLink(aceData);
        // file
        HandleOnDragDropFile(aceData);
    } else {
        TAG_LOGW(AceLogTag::ACE_WEB, "DragDrop event WebEventHub onDragDropId get data failed");
    }

    delegate_->HandleDragEvent(localX, localY, DragAction::DRAG_DROP);
    delegate_->RegisterWebWindowFocusChangedListener();
}

void WebPattern::HandleOnDragLeave(int32_t x, int32_t y)
{
    if (snapshotImageNodeId_.has_value()) {
        TAG_LOGD(AceLogTag::ACE_WEB, "blankless during snapshot image, no need to handle on drag leave!");
        return;
    }
    CHECK_NULL_VOID(delegate_);
    TAG_LOGI(AceLogTag::ACE_WEB,
        "DragDrop, HandleOnDragLeave, isDragStartFromWeb_ %{public}d, isReceivedArkDrag_ %{public}d",
        (int)isDragStartFromWeb_, (int)isReceivedArkDrag_);
    isDragging_ = false;
    isW3cDragEvent_ = false;
    isReceivedArkDrag_ = isDragStartFromWeb_ ? isReceivedArkDrag_ : false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto viewScale = pipelineContext->GetViewScale();
    auto offset = GetCoordinatePoint();
    int32_t localX = static_cast<int32_t>(x - offset.value_or(OffsetF()).GetX());
    int32_t localY = static_cast<int32_t>(y - offset.value_or(OffsetF()).GetY());
    delegate_->HandleDragEvent(localX * viewScale, localY * viewScale, DragAction::DRAG_LEAVE);
}

void WebPattern::HandleDragEnd(int32_t x, int32_t y)
{
    if (snapshotImageNodeId_.has_value()) {
        TAG_LOGD(AceLogTag::ACE_WEB, "blankless during snapshot image, no need to handle drag end!");
        return;
    }
    CHECK_NULL_VOID(delegate_);

    isDragging_ = false;
    isReceivedArkDrag_ = false;
    isW3cDragEvent_ = false;
    isDragStartFromWeb_ = false;
    ClearDragData();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto viewScale = pipelineContext->GetViewScale();
    auto offset = GetCoordinatePoint();
    int32_t localX = static_cast<int32_t>(x - offset.value_or(OffsetF()).GetX()) * viewScale;
    int32_t localY = static_cast<int32_t>(y - offset.value_or(OffsetF()).GetY()) * viewScale;
    if (x == 0 && y == 0) {
        delegate_->HandleDragEvent(0, 0, DragAction::DRAG_END);
    } else {
        delegate_->HandleDragEvent(localX, localY, DragAction::DRAG_END);
    }
    if (isSetMouseDragMonitorState) {
        auto eventHub = host->GetEventHub<WebEventHub>();
        CHECK_NULL_VOID(eventHub);
        auto gestureHub = eventHub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->SetMouseDragMonitorState(false);
        isSetMouseDragMonitorState = false;
    }
}

void WebPattern::HandleDragCancel()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    // disable drag
    frameNode->SetDraggable(false);
    CHECK_NULL_VOID(delegate_);
    isDragging_ = false;
    isReceivedArkDrag_ = false;
    isW3cDragEvent_ = false;
    isDragStartFromWeb_ = false;
    ClearDragData();
    delegate_->HandleDragEvent(0, 0, DragAction::DRAG_CANCEL);
}

void WebPattern::ClearDragData()
{
    CHECK_NULL_VOID(delegate_);
    std::string plain = "";
    std::string htmlContent = "";
    std::string linkUrl = "";
    std::string linkTitle = "";
    if (delegate_->dragData_) {
        delegate_->dragData_->SetFragmentText(plain);
        delegate_->dragData_->SetFragmentHtml(htmlContent);
        delegate_->dragData_->SetLinkURL(linkUrl);
        delegate_->dragData_->SetLinkTitle(linkTitle);
        delegate_->dragData_->ClearImageFileNames();
    }
}

void WebPattern::SetFakeDragData(const RefPtr<OHOS::Ace::DragEvent>& info)
{
    CHECK_NULL_VOID(delegate_);
    CHECK_NULL_VOID(delegate_->dragData_);
    if (info && !info->GetSummary().empty()) {
        std::map<std::string, int64_t> dragDataSummary = info->GetSummary();
        TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop, set fake drag data by summary, summary size is %{public}zu",
            dragDataSummary.size());
        std::map<std::string, int64_t>::iterator iter;
        for (iter = dragDataSummary.begin(); iter != dragDataSummary.end(); iter++) {
            if (FILE_TYPE_SET.find(iter->first) != FILE_TYPE_SET.end()) {
                delegate_->dragData_->SetFileUri(FAKE_DRAG_DATA_VAL);
            } else if (DRAG_DATA_TYPE_TEXT == iter->first) {
                delegate_->dragData_->SetFragmentText(FAKE_DRAG_DATA_VAL);
            } else if (DRAG_DATA_TYPE_HTML == iter->first || DRAG_DATA_TYPE_APP_DEF == iter->first) {
                delegate_->dragData_->SetFragmentHtml(FAKE_DRAG_DATA_VAL);
            } else if (DRAG_DATA_TYPE_LINK == iter->first) {
                delegate_->dragData_->SetLinkURL(FAKE_LINK_VAL);
                delegate_->dragData_->SetLinkTitle(FAKE_LINK_VAL);
            }
        }
        return;
    }
    delegate_->dragData_->SetFragmentText(FAKE_DRAG_DATA_VAL);
    delegate_->dragData_->SetFragmentHtml(FAKE_DRAG_DATA_VAL);
}

void WebPattern::InitFocusEvent(const RefPtr<FocusHub>& focusHub)
{
    auto focusTask = [weak = WeakClaim(this)](FocusReason reason) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleFocusEvent();
    };
    focusHub->SetOnFocusInternal(focusTask);

    auto blurTask = [weak = WeakClaim(this)](const BlurReason& blurReason) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent(blurReason);
    };
    focusHub->SetOnBlurReasonInternal(blurTask);

    auto keyTask = [weak = WeakClaim(this)](const KeyEvent& keyEvent) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->HandleKeyEvent(keyEvent);
    };
    focusHub->SetOnKeyEventInternal(keyTask);
}

void WebPattern::HandleFocusEvent()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::HandleFocusEvent webId:%{public}d, needOnFocus: %{public}d.", GetWebId(),
        needOnFocus_);
    CHECK_NULL_VOID(delegate_);
    isFocus_ = true;
    if (needOnFocus_) {
        delegate_->OnFocus();
    } else {
        delegate_->OnFocus(OHOS::NWeb::FocusReason::FOCUS_DEFAULT);
        needOnFocus_ = true;
    }
}

void WebPattern::HandleBlurEvent(const BlurReason& blurReason)
{
    TAG_LOGI(AceLogTag::ACE_WEB,
        "HandleBlurEvent webId:%{public}d, selectPopupMenuShowing: %{public}d, isDragStartFromWeb: %{public}d",
        GetWebId(), selectPopupMenuShowing_, isDragStartFromWeb_);
    CHECK_NULL_VOID(delegate_);
    isFocus_ = false;

    if (isDragStartFromWeb_) {
        return;
    }
    if (!selectPopupMenuShowing_) {
        delegate_->SetBlurReason(static_cast<OHOS::NWeb::BlurReason>(blurReason));
        delegate_->OnBlur();
    }
    OnQuickMenuDismissed();
    CloseContextSelectionMenu();
    if (!isVisible_ && isActive_ && IsDialogNested()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "HandleBlurEvent, dialog nested blur but invisible while active, set inactive.");
        SetActiveStatusInner(false);
    }
    HideMagnifier();
    EnableSecurityLayer(false);
}

bool WebPattern::HandleKeyEvent(const KeyEvent& keyEvent)
{
    if (contextSelectOverlay_ && contextSelectOverlay_->IsCurrentMenuVisibile() &&
        keyEvent.code == KeyCode::KEY_ESCAPE && keyEvent.action == KeyAction::DOWN) {
        bool isKeyNull = !(keyEvent.HasKey(KeyCode::KEY_ALT_LEFT) || keyEvent.HasKey(KeyCode::KEY_ALT_RIGHT) ||
            keyEvent.HasKey(KeyCode::KEY_SHIFT_LEFT) || keyEvent.HasKey(KeyCode::KEY_SHIFT_RIGHT) ||
            keyEvent.HasKey(KeyCode::KEY_CTRL_LEFT) || keyEvent.HasKey(KeyCode::KEY_CTRL_RIGHT) ||
            keyEvent.HasKey(KeyCode::KEY_META_LEFT) || keyEvent.HasKey(KeyCode::KEY_META_RIGHT));
        if (isKeyNull) {
            TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern Handle Escape");
            CloseContextSelectionMenu();
        }
    }
    bool ret = false;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, ret);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_RETURN(eventHub, ret);

    KeyEventInfo info(keyEvent);
    auto keyEventCallback = eventHub->GetOnKeyEvent();
    if (keyEventCallback) {
        keyEventCallback(info);
    }

    auto preKeyEventCallback = eventHub->GetOnPreKeyEvent();
    if (preKeyEventCallback) {
        ret = preKeyEventCallback(info);
        if (ret) {
            return ret;
        }
    }

    ret = WebOnKeyEvent(keyEvent);
    return ret;
}

void WebPattern::ClearKeyEventByKeyCode(int32_t keyCode)
{
    auto keyEvent = webKeyEvent_.begin();
    for (; keyEvent != webKeyEvent_.end();) {
        if (static_cast<int32_t>(keyEvent->code) == keyCode) {
            keyEvent = webKeyEvent_.erase(keyEvent);
        } else {
            ++keyEvent;
        }
    }

    if (webKeyEvent_.size() >= KEYEVENT_MAX_NUM) {
        webKeyEvent_.clear();
        TAG_LOGW(AceLogTag::ACE_WEB,
            "WebPattern::ClearKeyEventByKeyCode clear all keyevent.");
    } else {
        TAG_LOGW(AceLogTag::ACE_WEB,
            "WebPattern::ClearKeyEventByKeyCode clear all tab keyevent.");
    }
}

bool WebPattern::WebOnKeyEvent(const KeyEvent& keyEvent)
{
    CHECK_NULL_RETURN(delegate_, false);
    if (webKeyEvent_.size() >= KEYEVENT_MAX_NUM) {
        ClearKeyEventByKeyCode(static_cast<int32_t>(KeyCode::KEY_TAB));
    }
    TAG_LOGD(AceLogTag::ACE_WEB,
        "WebPattern::WebOnKeyEvent keyEvent:%{public}s", keyEvent.ToString().c_str());
    webKeyEvent_.push_back(keyEvent);
    if (keyEvent.code == KeyCode::KEY_TAB && keyEvent.action == KeyAction::DOWN) {
        tabKeyEvent_ = keyEvent;
    }
    std::vector<int32_t> pressedCodes;
    for (auto pCode : keyEvent.pressedCodes) {
        pressedCodes.push_back(static_cast<int32_t>(pCode));
    }
    KeyCode code = keyEvent.code;
    auto item = g_numPadFunctionMap.find(code);
    if (!keyEvent.numLock && item != g_numPadFunctionMap.end()) {
        code = item->second;
    }
    std::shared_ptr<NWebKeyboardEventImpl> keyboardEvent =
        std::make_shared<NWebKeyboardEventImpl>(static_cast<int32_t>(code),
                                                static_cast<int32_t>(keyEvent.action),
                                                keyEvent.unicode,
                                                keyEvent.enableCapsLock,
                                                pressedCodes);
    return delegate_->SendKeyboardEvent(keyboardEvent);
}

void WebPattern::KeyboardReDispatch(
    const std::shared_ptr<OHOS::NWeb::NWebKeyEvent>& event, bool isUsed)
{
    CHECK_NULL_VOID(event);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto taskExecutor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto keyEvent = webKeyEvent_.rbegin();
    for (; keyEvent != webKeyEvent_.rend(); ++keyEvent) {
        if (static_cast<int32_t>(keyEvent->code) == event->GetKeyCode() &&
            static_cast<int32_t>(keyEvent->action) == event->GetAction()) {
            break;
        }
    }
    if (keyEvent == webKeyEvent_.rend()) {
        TAG_LOGW(AceLogTag::ACE_WEB, "KeyEvent is not find keycode");
        return;
    }
    if (!isUsed) {
        taskExecutor->PostTask([context = AceType::WeakClaim(pipelineContext),
            event = *keyEvent] () {
            auto pipelineContext = context.Upgrade();
            CHECK_NULL_VOID(pipelineContext);
            TAG_LOGD(AceLogTag::ACE_WEB, "WebPattern::KeyboardReDispatch");
            pipelineContext->ReDispatch(const_cast<KeyEvent&>(event));
            },
            TaskExecutor::TaskType::UI, "ArkUIWebKeyboardReDispatch");
    }
    TAG_LOGD(AceLogTag::ACE_WEB, "WebPattern::KeyboardReDispatch erase key");
    webKeyEvent_.erase((++keyEvent).base());
}

void WebPattern::OnTakeFocus(const std::shared_ptr<OHOS::NWeb::NWebKeyEvent>& event)
{
    CHECK_NULL_VOID(event);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto taskExecutor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    if (static_cast<int32_t>(tabKeyEvent_.code) != event->GetKeyCode() ||
        static_cast<int32_t>(tabKeyEvent_.action) != event->GetAction()) {
        return;
    }
    taskExecutor->PostTask([context = AceType::WeakClaim(pipelineContext),
        event = tabKeyEvent_] () {
        auto pipelineContext = context.Upgrade();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->ReDispatch(const_cast<KeyEvent&>(event));
        },
        TaskExecutor::TaskType::UI, "ArkUIWebKeyboardReDispatch");
}

void WebPattern::WebRequestFocus()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);

    focusHub->RequestFocusImmediately();
}

void WebPattern::UpdateContentOffset(const RefPtr<LayoutWrapper>& dirty)
{
    CHECK_NULL_VOID(dirty);
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto paddingOffset = geometryNode->GetPaddingOffset();
    auto webContentSize = geometryNode->GetContentSize();

    auto positionProperty = renderContext->GetPropertyOfPosition();
    renderContext->SetBounds(
        paddingOffset.GetX() +  positionProperty.GetX(), paddingOffset.GetY() + positionProperty.GetY(),
        webContentSize.Width(), webContentSize.Height());
}

bool WebPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    UpdateImagePreviewParam();
    if (selectOverlayProxy_) {
        selectOverlayProxy_->UpdateAncestorViewPort(GetViewPort());
    }
    if (!config.contentSizeChange || isInWindowDrag_) {
        if (isLayoutModeChanged_) {
            isLayoutModeChanged_ = false;
        } else {
            return false;
        }
    }
    CHECK_NULL_RETURN(delegate_, false);
    CHECK_NULL_RETURN(dirty, false);

    Size drawSize = Size(1, 1);
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto rect = renderContext->GetPaintRectWithoutTransform();
    drawSize = Size(rect.Width(), rect.Height());
    if (drawSize.IsInfinite() || drawSize.IsEmpty()) {
        return false;
    }

    if (GreatOrEqual(drawSize.Width(), Infinity<double>())) {
        drawSize.SetWidth(DEFAULT_WEB_WIDTH);
    }
    if (GreatOrEqual(drawSize.Height(), Infinity<double>())) {
        drawSize.SetHeight(DEFAULT_WEB_HEIGHT);
    }

    drawSize_ = drawSize;
    drawSizeCache_ = drawSize_;
    if(!GetCoordinatePoint().has_value()) {
        return false;
    }
    auto offset = Offset(GetCoordinatePoint()->GetX(), GetCoordinatePoint()->GetY());
    if (!CheckSafeAreaIsExpand()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "Not safe area, drawsize_ : %{public}s, web id : %{public}d",
            drawSize_.ToString().c_str(), GetWebId());
        ACE_SCOPED_TRACE("WebPattern::OnDirtyLayoutWrapperSwap, drawsize_ : %s,  web id : %d",
            drawSize_.ToString().c_str(), GetWebId());
        if (isVirtualKeyBoardShow_ == VkState::VK_SHOW) {
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_RETURN(pipeline, false);
            ProcessVirtualKeyBoard(pipeline->GetRootWidth(), pipeline->GetRootHeight(), lastKeyboardHeight_);
        }
        delegate_->SetBoundsOrResize(drawSize_, offset, isKeyboardInSafeArea_ || keyboardGetready_);
        IsNeedResizeVisibleViewport();
        isKeyboardInSafeArea_ = false;
    } else {
        TAG_LOGD(AceLogTag::ACE_WEB, "OnDirtyLayoutWrapperSwap safeArea is set, no need setbounds");
    }
    if (offlineWebInited_ && !offlineWebRendered_) {
        TAG_LOGI(AceLogTag::ACE_WEB,
            "OnDirtyLayoutWrapperSwap; WebPattern is Offline Mode, WebId:%{public}d", GetWebId());
        offlineWebRendered_ = true;
        SetActiveStatusInner(true);
    }

    // first update size to load url.
    if (!isUrlLoaded_) {
        isUrlLoaded_ = true;
        if (webSrc_) {
            delegate_->LoadUrl();
        } else if (webData_) {
            delegate_->LoadDataWithRichText();
        }
    }

    if (renderMode_ == RenderMode::SYNC_RENDER) {
        return true;
    }
    return false;
}

void WebPattern::BeforeSyncGeometryProperties(const DirtySwapConfig& config)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto rect = renderContext->GetPaintRectWithoutTransform();
    auto heightBeforeUpdate = rect.Height();
    if (isResizeContentAvoid_ && frameNode->SelfExpansive()) {
        rect.SetHeight(heightAfterAvoid_);
        renderContext->UpdatePaintRect(rect);
        rect.SetHeight(heightBeforeUpdate);
    }

    if (!config.contentSizeChange || isInWindowDrag_) {
        return;
    }
    auto drawSize = Size(rect.Width(), rect.Height());
    if (drawSize.IsInfinite() || drawSize.IsEmpty()) {
        return;
    }

    if (GreatOrEqual(drawSize.Width(), Infinity<double>())) {
        drawSize.SetWidth(DEFAULT_WEB_WIDTH);
    }
    if (GreatOrEqual(drawSize.Height(), Infinity<double>())) {
        drawSize.SetHeight(DEFAULT_WEB_HEIGHT);
    }

    TAG_LOGD(AceLogTag::ACE_WEB, "BeforeSync, drawsize_ : %{public}s", drawSize.ToString().c_str());
    if (layoutMode_ != WebLayoutMode::FIT_CONTENT) {
        drawSize_ = drawSize;
        drawSizeCache_ = drawSize_;
    }
}

int32_t WebPattern::GetVisibleViewportAvoidHeight()
{
    int32_t avoidHeight = 0;
    if (delegate_ != nullptr && delegate_->GetNweb() != nullptr) {
        avoidHeight = delegate_->GetNweb()->GetVisibleViewportAvoidHeight();
    }
    return avoidHeight;
}

void WebPattern::UpdateLayoutAfterKeyboardShow(int32_t width, int32_t height, double keyboard, double oldWebHeight)
{
    lastKeyboardHeight_ = keyboard;
    if (isVirtualKeyBoardShow_ != VkState::VK_SHOW) {
        return;
    }

    TAG_LOGI(AceLogTag::ACE_WEB,
        "KeyboardShow height:%{public}d, keyboard:%{public}f, offset:%{public}f, oldWebHeight:%{public}f",
        height, keyboard, GetCoordinatePoint()->GetY(), oldWebHeight);
    if (CheckSafeAreaKeyBoard()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "CheckSafeAreaKeyBoard, no need resize");
        return;
    }
    if (GreatOrEqual(height, keyboard + GetCoordinatePoint()->GetY())) {
        double newHeight = height - keyboard - GetCoordinatePoint()->GetY();
        if (NearEqual(newHeight, oldWebHeight)) {
            return;
        }
        bool isUpdate = true;
        if (GetVisibleViewportAvoidHeight() != 0) {
            TAG_LOGI(AceLogTag::ACE_WEB, "visible viewport avoid, behavior consistent with OVERLAYS_CONTENT");
            return;
        }
        if (keyBoardAvoidMode_ == WebKeyboardAvoidMode::RESIZE_VISUAL) {
            visibleViewportSize_.SetWidth(drawSize_.Width());
            visibleViewportSize_.SetHeight(newHeight);
            isUpdate = false;
        } else if (keyBoardAvoidMode_ == WebKeyboardAvoidMode::OVERLAYS_CONTENT) {
            return;
        } else {
            TAG_LOGI(AceLogTag::ACE_WEB, "KeyboardShow newHeight: %{public}f", newHeight);
            drawSize_.SetHeight(newHeight);
            visibleViewportSize_.SetWidth(-1.0);
            visibleViewportSize_.SetHeight(-1.0);
            isResizeContentAvoid_ = true;
            heightAfterAvoid_ = newHeight;
        }
        UpdateWebLayoutSize(width, height, true, isUpdate);
    }
}

void WebPattern::OnAreaChangedInner()
{
    auto offset = GetCoordinatePoint().value_or(OffsetF());
    auto resizeOffset = Offset(offset.GetX(), offset.GetY());

    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto rect = renderContext->GetPaintRectWithoutTransform();
    auto size = Size(rect.Width(), rect.Height());
    delegate_->OnAreaChange({ resizeOffset.GetX(), resizeOffset.GetY(), size.Width(), size.Height() });
    if (CheckSafeAreaIsExpand() &&
        ((size.Width() != areaChangeSize_.Width()) || (size.Height() != areaChangeSize_.Height()))) {
        TAG_LOGD(AceLogTag::ACE_WEB, "OnAreaChangedInner setbounds: height:%{public}f, offsetY:%{public}f",
            size.Height(), resizeOffset.GetY());
        areaChangeSize_ = size;
        drawSize_ = size;
        if (renderMode_ != RenderMode::SYNC_RENDER) {
            drawSizeCache_ = drawSize_;
        }
        TAG_LOGD(AceLogTag::ACE_WEB, "Safe area, drawsize_ : %{public}s", drawSize_.ToString().c_str());
        delegate_->SetBoundsOrResize(drawSize_, resizeOffset, isKeyboardInSafeArea_);
        IsNeedResizeVisibleViewport();
        isKeyboardInSafeArea_ = false;
    }
    if (layoutMode_ == WebLayoutMode::NONE && renderMode_ == RenderMode::ASYNC_RENDER) {
        if (isVirtualKeyBoardShow_ != VkState::VK_SHOW) {
            drawSize_ = size;
            TAG_LOGD(AceLogTag::ACE_WEB, "ASYNC_RENDER, drawsize_ : %{public}s", drawSize_.ToString().c_str());
        }
        if (webOffset_ == offset) {
            return;
        }
    }
    if (offset != webOffset_) {
        webOffset_ = offset;
        if (webSelectOverlay_ && webSelectOverlay_->IsShowHandle())
            webSelectOverlay_->UpdateTouchHandleForOverlay();
    }
    if (isInWindowDrag_)
        return;
    TAG_LOGD(AceLogTag::ACE_WEB, "Normal state, drawsize_ : %{public}s", drawSize_.ToString().c_str());
    delegate_->SetBoundsOrResize(drawSize_, resizeOffset, isKeyboardInSafeArea_);
    IsNeedResizeVisibleViewport();
    isKeyboardInSafeArea_ = false;
    if (renderMode_ == RenderMode::SYNC_RENDER) {
        UpdateSlideOffset();
    }
}

void WebPattern::OnWebSrcUpdate()
{
    if (delegate_ && isUrlLoaded_) {
        delegate_->LoadUrl();
    }
}

void WebPattern::OnWebDataUpdate()
{
    if (delegate_ && isUrlLoaded_) {
        delegate_->LoadDataWithRichText();
    }
}

void WebPattern::OnJsEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateJavaScriptEnabled(value);
    }
}

void WebPattern::OnMediaPlayGestureAccessUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateMediaPlayGestureAccess(value);
    }
}

void WebPattern::OnFileAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateAllowFileAccess(value);
    }
}

void WebPattern::OnOnLineImageAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateBlockNetworkImage(!value);
    }
}

void WebPattern::OnDomStorageAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateDomStorageEnabled(value);
    }
}

void WebPattern::OnImageAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateLoadsImagesAutomatically(value);
    }
}

void WebPattern::OnMixedModeUpdate(MixedModeContent value)
{
    if (delegate_) {
        delegate_->UpdateMixedContentMode(value);
    }
}

void WebPattern::OnZoomAccessEnabledUpdate(bool value)
{
    if ((layoutMode_ == WebLayoutMode::FIT_CONTENT) || isEmbedModeEnabled_) {
        TAG_LOGI(AceLogTag::ACE_WEB, "When layoutMode is fit-content or EmbedMode is on, turn off zoom access.");
        value = false;
    }
    if (delegate_) {
        delegate_->UpdateSupportZoom(value);
    }
}

void WebPattern::OnGeolocationAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateGeolocationEnabled(value);
    }
}

void WebPattern::OnUserAgentUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateUserAgent(value);
    }
}

void WebPattern::OnCacheModeUpdate(WebCacheMode value)
{
    if (delegate_) {
        delegate_->UpdateCacheMode(value);
    }
}

void WebPattern::OnDarkModeUpdate(WebDarkMode mode)
{
    if (delegate_) {
        delegate_->UpdateDarkMode(mode);
    }
}

void WebPattern::OnOverScrollModeUpdate(int mode)
{
    if (delegate_) {
        delegate_->UpdateOverScrollMode(mode);
    }
}

void WebPattern::OnBlurOnKeyboardHideModeUpdate(int mode)
{
    if (delegate_) {
        delegate_->UpdateBlurOnKeyboardHideMode(mode);
    }
}

void WebPattern::OnCopyOptionModeUpdate(int32_t mode)
{
    if (delegate_) {
        delegate_->UpdateCopyOptionMode(mode);
    }
}

void WebPattern::OnMetaViewportUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateMetaViewport(value);
    }
}

void WebPattern::OnForceDarkAccessUpdate(bool access)
{
    if (delegate_) {
        delegate_->UpdateForceDarkAccess(access);
    }
}

void WebPattern::OnAudioResumeIntervalUpdate(int32_t resumeInterval)
{
    if (delegate_) {
        delegate_->UpdateAudioResumeInterval(resumeInterval);
    }
}

void WebPattern::OnAudioExclusiveUpdate(bool audioExclusive)
{
    if (delegate_) {
        delegate_->UpdateAudioExclusive(audioExclusive);
    }
}

void WebPattern::OnAudioSessionTypeUpdate(WebAudioSessionType value)
{
    if (delegate_) {
        delegate_->UpdateAudioSessionType(value);
    }
}

void WebPattern::OnOverviewModeAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateOverviewModeEnabled(value);
    }
}

void WebPattern::OnFileFromUrlAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateFileFromUrlEnabled(value);
    }
}

void WebPattern::OnDatabaseAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateDatabaseEnabled(value);
    }
}

void WebPattern::OnTextZoomRatioUpdate(int32_t value)
{
    if (delegate_) {
        delegate_->UpdateTextZoomRatio(value);
    }
}

void WebPattern::OnWebDebuggingAccessEnabledAndPortUpdate(
    const WebPatternProperty::WebDebuggingConfigType& enabled_and_port)
{
    if (delegate_) {
        bool enabled = std::get<0>(enabled_and_port);
        int32_t port = std::get<1>(enabled_and_port);
        if (port > 0) {
            delegate_->UpdateWebDebuggingAccessAndPort(enabled, port);
        } else {
            delegate_->UpdateWebDebuggingAccess(enabled);
        }
    }
}

void WebPattern::OnPinchSmoothModeEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdatePinchSmoothModeEnabled(value);
    }
}

void WebPattern::OnBackgroundColorUpdate(int32_t value)
{
    needSetDefaultBackgroundColor_ = false;
    UpdateBackgroundColorRightNow(value);
    if (delegate_) {
        delegate_->UpdateBackgroundColor(value);
    }
}

void WebPattern::OnInitialScaleUpdate(float value)
{
    if ((layoutMode_ == WebLayoutMode::FIT_CONTENT) || isEmbedModeEnabled_) {
        TAG_LOGI(AceLogTag::ACE_WEB, "When layoutMode is fit-content or EmbedMode is on, Not allow to update scale.");
        return;
    }
    if (delegate_) {
        delegate_->UpdateInitialScale(value);
    }
}

void WebPattern::OnMultiWindowAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateMultiWindowAccess(value);
    }
}

void WebPattern::OnAllowWindowOpenMethodUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateAllowWindowOpenMethod(value);
    }
}

void WebPattern::OnWebCursiveFontUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateWebCursiveFont(value);
    }
}

void WebPattern::OnWebFantasyFontUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateWebFantasyFont(value);
    }
}

void WebPattern::OnWebFixedFontUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateWebFixedFont(value);
    }
}

void WebPattern::OnWebSansSerifFontUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateWebSansSerifFont(value);
    }
}

void WebPattern::OnWebSerifFontUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateWebSerifFont(value);
    }
}

void WebPattern::OnWebStandardFontUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateWebStandardFont(value);
    }
}

void WebPattern::OnDefaultFixedFontSizeUpdate(int32_t value)
{
    if (delegate_) {
        delegate_->UpdateDefaultFixedFontSize(value);
    }
}

void WebPattern::OnDefaultFontSizeUpdate(int32_t value)
{
    if (delegate_) {
        delegate_->UpdateDefaultFontSize(value);
    }
}

void WebPattern::OnMinFontSizeUpdate(int32_t value)
{
    if (delegate_) {
        delegate_->UpdateMinFontSize(value);
    }
}

void WebPattern::OnMinLogicalFontSizeUpdate(int32_t value)
{
    if (delegate_) {
        delegate_->UpdateMinLogicalFontSize(value);
    }
}

void WebPattern::OnBlockNetworkUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateBlockNetwork(value);
    }
}

void WebPattern::OnHorizontalScrollBarAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateHorizontalScrollBarAccess(value);
    }
}

void WebPattern::OnVerticalScrollBarAccessEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateVerticalScrollBarAccess(value);
    }
}

void WebPattern::OnOverlayScrollbarEnabledUpdate(bool enable)
{
    if (delegate_) {
        delegate_->UpdateOverlayScrollbarEnabled(enable);
    }
}

void WebPattern::OnNativeEmbedModeEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateNativeEmbedModeEnabled(value);
    }
}

void WebPattern::OnIntrinsicSizeEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateIntrinsicSizeEnabled(value);
    }
}

void WebPattern::OnCssDisplayChangeEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateCssDisplayChangeEnabled(value);
    }
}

void WebPattern::OnNativeEmbedRuleTagUpdate(const std::string& tag)
{
    if (delegate_) {
        delegate_->UpdateNativeEmbedRuleTag(tag);
    }
}

void WebPattern::OnNativeEmbedRuleTypeUpdate(const std::string& type)
{
    if (delegate_) {
        delegate_->UpdateNativeEmbedRuleType(type);
    }
}

void WebPattern::OnTextAutosizingUpdate(bool isTextAutosizing)
{
    if (delegate_) {
        delegate_->UpdateTextAutosizing(isTextAutosizing);
    }
}

void WebPattern::OnKeyboardAvoidModeUpdate(const WebKeyboardAvoidMode& mode)
{
    keyBoardAvoidMode_ = mode;
}

void WebPattern::OnEnabledHapticFeedbackUpdate(bool enable)
{
    isEnabledHapticFeedback_ = enable;
}

bool WebPattern::IsRootNeedExportTexture()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    bool isNeedExportTexture = false;
    for (auto parent = host->GetParent(); parent != nullptr; parent = parent->GetParent()) {
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            continue;
        }
        isNeedExportTexture = frameNode->IsNeedExportTexture();
        if (isNeedExportTexture) {
            return isNeedExportTexture;
        }
    }
    return isNeedExportTexture;
}

void WebPattern::OnAttachContext(PipelineContext *context)
{
    nodeAttach_ = true;
    auto pipelineContext = Claim(context);
    int32_t newId = pipelineContext->GetInstanceId();
    instanceId_ = newId;
    windowId_ = pipelineContext->GetWindowId();
    if (delegate_) {
        delegate_->OnAttachContext(pipelineContext);
    }

    if (observer_) {
        observer_->OnAttachContext(pipelineContext);
    }

    if (updateInstanceIdCallback_) {
        updateInstanceIdCallback_(newId);
    }

    if (renderContextForSurface_) {
        renderContextForSurface_->SetRSUIContext(context);
    }

    if (renderSurface_) {
        renderSurface_->SetInstanceId(newId);
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int32_t nodeId = host->GetId();

    pipelineContext->AddWindowStateChangedCallback(nodeId);
    pipelineContext->AddWindowSizeChangeCallback(nodeId);
    pipelineContext->AddOnAreaChangeNode(nodeId);
    RegisterVisibleAreaChangeCallback(pipelineContext);
    needUpdateWeb_ = true;
    RegistVirtualKeyBoardListener(pipelineContext);
    InitConfigChangeCallback(pipelineContext);
    InitializeAccessibility();
    InitSurfaceDensityCallback(pipelineContext);
}

void WebPattern::OnDetachContext(PipelineContext *contextPtr)
{
    nodeAttach_ = false;
    auto context = AceType::Claim(contextPtr);
    CHECK_NULL_VOID(context);

    auto host = GetHost();
    int32_t nodeId = host->GetId();
    UninitializeAccessibility();
    UnInitSurfaceDensityCallback(context);
    context->RemoveWindowStateChangedCallback(nodeId);
    context->RemoveWindowSizeChangeCallback(nodeId);
    context->RemoveOnAreaChangeNode(nodeId);
    context->RemoveVisibleAreaChangeNode(nodeId);
    context->RemoveVirtualKeyBoardCallback(nodeId);
    context->RemoveConfigChangedCallback(nodeId);

    if (delegate_) {
        delegate_->OnDetachContext();
    }

    if (observer_) {
        observer_->OnDetachContext();
    }

    if (tooltipId_ != -1) {
        auto overlayManager = context->GetOverlayManager();
        if (overlayManager) {
            overlayManager->RemoveIndexerPopupById(tooltipId_);
        }
        tooltipId_ = -1;
    }
}

void WebPattern::SetUpdateInstanceIdCallback(std::function<void(int32_t)>&& callback)
{
    updateInstanceIdCallback_ = callback;
}

void WebPattern::OnScrollBarColorUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateScrollBarColor(value);
    }
}

void WebPattern::OnDefaultTextEncodingFormatUpdate(const std::string& value)
{
    if (delegate_) {
        delegate_->UpdateDefaultTextEncodingFormat(value);
    }
}

void WebPattern::OnNativeVideoPlayerConfigUpdate(const std::tuple<bool, bool>& config)
{
    if (delegate_) {
        delegate_->UpdateNativeVideoPlayerConfig(
            std::get<0>(config), std::get<1>(config));
    }
}

void WebPattern::OnForceEnableZoomUpdate(bool isEnabled)
{
    RETURN_IF_CALLING_FROM_M114();
    if (delegate_) {
        TAG_LOGI(AceLogTag::ACE_WEB, "SetForceEnableZoom :%{public}d", isEnabled);
        delegate_->SetForceEnableZoom(isEnabled);
    }
}

void WebPattern::RegistVirtualKeyBoardListener(const RefPtr<PipelineContext> &pipelineContext)
{
    if (!needUpdateWeb_) {
        return;
    }
    pipelineContext->SetVirtualKeyBoardCallback(GetHost()->GetId(),
        [weak = AceType::WeakClaim(this)](int32_t width, int32_t height, double keyboard, bool isCustomKeyboard) {
            auto webPattern = weak.Upgrade();
            CHECK_NULL_RETURN(webPattern, false);
            return webPattern->ProcessVirtualKeyBoard(width, height, keyboard, isCustomKeyboard);
        });
    needUpdateWeb_ = false;
}

void WebPattern::InitEnhanceSurfaceFlag()
{
    if (SystemProperties::GetExtSurfaceEnabled()) {
        isEnhanceSurface_ = true;
    } else {
        isEnhanceSurface_ = false;
    }
}

void WebPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (magnifierController_) {
        magnifierController_->SetColorModeChange(true);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void WebPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    // called in each update function.
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetHandleChildBounds(true);
    if (!delegate_) {
        // first create case,
        delegate_ = AceType::MakeRefPtr<WebDelegate>(PipelineContext::GetCurrentContext(), nullptr, "",
            Container::CurrentId());
        instanceId_ = Container::CurrentId();
        CHECK_NULL_VOID(delegate_);
        observer_ = AceType::MakeRefPtr<WebDelegateObserver>(delegate_, PipelineContext::GetCurrentContext());
        CHECK_NULL_VOID(observer_);
        delegate_->SetObserver(observer_);
        delegate_->SetRenderMode(renderMode_);
        delegate_->SetFitContentMode(layoutMode_);
        InitEnhanceSurfaceFlag();
        delegate_->SetNGWebPattern(Claim(this));
        delegate_->SetEnhanceSurfaceFlag(isEnhanceSurface_);
        delegate_->SetPopup(isPopup_);
        delegate_->SetParentNWebId(parentNWebId_);
        delegate_->SetBackgroundColor(GetBackgroundColorValue(static_cast<int32_t>(
            renderContext->GetBackgroundColor().value_or(GetDefaultBackgroundColor()).GetValue())));
        if (isEnhanceSurface_) {
            auto drawSize = Size(1, 1);
            delegate_->SetDrawSize(drawSize);
            delegate_->InitOHOSWeb(PipelineContext::GetCurrentContext());
        } else {
            auto drawSize = Size(1, 1);
            delegate_->SetDrawSize(drawSize);
            int32_t instanceId = Container::CurrentId();
            CHECK_NULL_VOID(renderSurface_);
            CHECK_NULL_VOID(popupRenderSurface_);
            CHECK_NULL_VOID(renderContextForSurface_);
            CHECK_NULL_VOID(renderContextForPopupSurface_);
            renderSurface_->SetInstanceId(instanceId);
            popupRenderSurface_->SetInstanceId(instanceId);
            renderSurface_->SetRenderContext(host->GetRenderContext());
            if (renderMode_ == RenderMode::SYNC_RENDER) {
                renderSurface_->SetIsTexture(true);
                renderSurface_->SetBufferTypeLeak(BUFFER_USAGE_TEXTURE + GetInspectorId());
                renderSurface_->SetPatternType(PATTERN_TYPE_WEB);
                renderSurface_->SetSurfaceQueueSize(SYNC_SURFACE_QUEUE_SIZE);
                renderContextForSurface_->SetOpacity(0.0f);
            } else {
                renderSurface_->SetIsTexture(false);
                renderSurface_->SetBufferUsage(BUFFER_USAGE_WEB);
                renderSurface_->SetBufferTypeLeak(BUFFER_USAGE_SURFACE + GetInspectorId());
                renderSurface_->SetSurfaceQueueSize(GetBufferSizeByDeviceType());
                renderSurface_->SetRenderContext(renderContextForSurface_);
            }
            popupRenderSurface_->SetIsTexture(false);
            popupRenderSurface_->SetSurfaceQueueSize(GetBufferSizeByDeviceType());
            popupRenderSurface_->SetRenderContext(renderContextForPopupSurface_);
            renderContext->AddChild(renderContextForSurface_, 0);
            if (SystemProperties::GetDeviceType() == DeviceType::TWO_IN_ONE) {
                renderContext->AddChild(renderContextForPopupSurface_, 1);
            }
            popupRenderSurface_->InitSurface();
            popupRenderSurface_->SetTransformHint(rotation_);
            popupRenderSurface_->UpdateSurfaceConfig();
            renderSurface_->InitSurface();
            renderSurface_->SetTransformHint(rotation_);
            TAG_LOGD(AceLogTag::ACE_WEB, "OnModify done, set rotation %{public}u", rotation_);
            renderSurface_->UpdateSurfaceConfig();
            delegate_->InitOHOSWeb(PipelineContext::GetCurrentContext(), renderSurface_);
#if defined(ENABLE_ROSEN_BACKEND)
            delegate_->SetPopupSurface(popupRenderSurface_);
#endif
            if (renderMode_ == RenderMode::ASYNC_RENDER) {
                std::string surfaceId = renderSurface_->GetUniqueId();
                delegate_->SetSurfaceId(surfaceId);
                TAG_LOGD(AceLogTag::ACE_WEB, "[getSurfaceId] set surfaceId is %{public}s", surfaceId.c_str());
            }
        }
        RecordWebEvent(true);

        UpdateJavaScriptOnDocumentStartByOrder();
        UpdateJavaScriptOnDocumentEndByOrder();
        UpdateJavaScriptOnDocumentStart();
        UpdateJavaScriptOnDocumentEnd();
        UpdateJavaScriptOnHeadReadyByOrder();

        bool isApiGteTwelve =
            AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE);
        delegate_->UpdateBackgroundColor(GetBackgroundColorValue(static_cast<int32_t>(
            renderContext->GetBackgroundColor().value_or(GetDefaultBackgroundColor()).GetValue())));
        delegate_->UpdateJavaScriptEnabled(GetJsEnabledValue(true));
        delegate_->UpdateBlockNetworkImage(!GetOnLineImageAccessEnabledValue(true));
        delegate_->UpdateLoadsImagesAutomatically(GetImageAccessEnabledValue(true));
        delegate_->UpdateMixedContentMode(GetMixedModeValue(MixedModeContent::MIXED_CONTENT_NEVER_ALLOW));
        delegate_->UpdateBypassVsyncCondition(GetBypassVsyncConditionValue(WebBypassVsyncCondition::NONE));
        isEmbedModeEnabled_ = GetNativeEmbedModeEnabledValue(false);
        if ((layoutMode_ == WebLayoutMode::FIT_CONTENT) || isEmbedModeEnabled_) {
            delegate_->UpdateSupportZoom(false);
        } else {
            delegate_->UpdateSupportZoom(GetZoomAccessEnabledValue(true));
        }
        delegate_->UpdateDomStorageEnabled(GetDomStorageAccessEnabledValue(false));
        delegate_->UpdateGeolocationEnabled(GetGeolocationAccessEnabledValue(true));
        delegate_->UpdateCacheMode(GetCacheModeValue(WebCacheMode::DEFAULT));
        if (webData_) {
            // Created a richtext component
            delegate_->SetRichtextIdentifier(webData_);
            delegate_->UpdateDarkMode(GetDarkModeValue(WebDarkMode::Auto));
            delegate_->UpdateForceDarkAccess(GetForceDarkAccessValue(true));
            delegate_->UpdateOverviewModeEnabled(GetOverviewModeAccessEnabledValue(false));
        } else {
            delegate_->UpdateDarkMode(GetDarkModeValue(WebDarkMode::Off));
            delegate_->UpdateForceDarkAccess(GetForceDarkAccessValue(false));
            delegate_->UpdateOverviewModeEnabled(GetOverviewModeAccessEnabledValue(true));
        }
        delegate_->UpdateAudioResumeInterval(GetAudioResumeIntervalValue(-1));
        delegate_->UpdateAudioExclusive(GetAudioExclusiveValue(true));
        delegate_->UpdateAudioSessionType(GetAudioSessionTypeValue(WebAudioSessionType::AUTO));
        delegate_->UpdateFileFromUrlEnabled(GetFileFromUrlAccessEnabledValue(false));
        delegate_->UpdateDatabaseEnabled(GetDatabaseAccessEnabledValue(false));
        delegate_->UpdateTextZoomRatio(GetTextZoomRatioValue(DEFAULT_TEXT_ZOOM_RATIO));
        auto webDebugingConfig = GetWebDebuggingAccessEnabledAndPort();
        if (webDebugingConfig) {
            bool enabled = std::get<0>(webDebugingConfig.value());
            int32_t port = std::get<1>(webDebugingConfig.value());
            if (port > 0) {
                delegate_->UpdateWebDebuggingAccessAndPort(enabled, port);
            } else {
                delegate_->UpdateWebDebuggingAccess(enabled);
            }
        }
        delegate_->UpdateMediaPlayGestureAccess(GetMediaPlayGestureAccessValue(true));
        delegate_->UpdatePinchSmoothModeEnabled(GetPinchSmoothModeEnabledValue(false));
        delegate_->UpdateMultiWindowAccess(GetMultiWindowAccessEnabledValue(false));
        delegate_->UpdateWebCursiveFont(GetWebCursiveFontValue(DEFAULT_CURSIVE_FONT_FAMILY));
        delegate_->UpdateWebFantasyFont(GetWebFantasyFontValue(DEFAULT_FANTASY_FONT_FAMILY));
        delegate_->UpdateWebFixedFont(GetWebFixedFontValue(DEFAULT_FIXED_fONT_FAMILY));
        delegate_->UpdateWebSansSerifFont(GetWebSansSerifFontValue(DEFAULT_SANS_SERIF_FONT_FAMILY));
        delegate_->UpdateWebSerifFont(GetWebSerifFontValue(DEFAULT_SERIF_FONT_FAMILY));
        delegate_->UpdateWebStandardFont(GetWebStandardFontValue(DEFAULT_STANDARD_FONT_FAMILY));
        delegate_->UpdateDefaultFixedFontSize(GetDefaultFixedFontSizeValue(DEFAULT_FIXED_FONT_SIZE));
        delegate_->UpdateDefaultFontSize(GetDefaultFontSizeValue(DEFAULT_FONT_SIZE));
        delegate_->UpdateDefaultTextEncodingFormat(GetDefaultTextEncodingFormatValue(DEFAULT_WEB_TEXT_ENCODING_FORMAT));
        delegate_->UpdateMinFontSize(GetMinFontSizeValue(DEFAULT_MINIMUM_FONT_SIZE));
        delegate_->UpdateMinLogicalFontSize(GetMinLogicalFontSizeValue(DEFAULT_MINIMUM_LOGICAL_FONT_SIZE));
        delegate_->UpdateHorizontalScrollBarAccess(GetHorizontalScrollBarAccessEnabledValue(true));
        delegate_->UpdateVerticalScrollBarAccess(GetVerticalScrollBarAccessEnabledValue(true));
        delegate_->UpdateScrollBarColor(GetScrollBarColorValue(DEFAULT_SCROLLBAR_COLOR));
        delegate_->UpdateOverlayScrollbarEnabled(GetOverlayScrollbarEnabledValue(false));
        delegate_->UpdateOverScrollMode(GetOverScrollModeValue(OverScrollMode::NEVER));
        delegate_->UpdateBlurOnKeyboardHideMode(GetBlurOnKeyboardHideModeValue(BlurOnKeyboardHideMode::SILENT));
        delegate_->UpdateCopyOptionMode(GetCopyOptionModeValue(static_cast<int32_t>(CopyOptions::Distributed)));
        delegate_->UpdateTextAutosizing(GetTextAutosizingValue(true));
        delegate_->UpdateAllowFileAccess(GetFileAccessEnabledValue(isApiGteTwelve ? false : true));
        delegate_->UpdateOptimizeParserBudgetEnabled(GetOptimizeParserBudgetEnabledValue(false));
        delegate_->UpdateWebMediaAVSessionEnabled(GetWebMediaAVSessionEnabledValue(true));
        delegate_->UpdateGestureFocusMode(GetGestureFocusModeValue(GestureFocusMode::DEFAULT));
        if (GetMetaViewport()) {
            delegate_->UpdateMetaViewport(GetMetaViewport().value());
        }
        if (GetBlockNetwork()) {
            delegate_->UpdateBlockNetwork(GetBlockNetwork().value());
        }
        if (GetUserAgent()) {
            delegate_->UpdateUserAgent(GetUserAgent().value());
        }
        if (GetInitialScale()) {
            delegate_->UpdateInitialScale(GetInitialScale().value());
        }
        isAllowWindowOpenMethod_ = SystemProperties::GetAllowWindowOpenMethodEnabled();
        delegate_->UpdateAllowWindowOpenMethod(GetAllowWindowOpenMethodValue(isAllowWindowOpenMethod_));
        delegate_->UpdateNativeEmbedModeEnabled(GetNativeEmbedModeEnabledValue(false));
        delegate_->UpdateIntrinsicSizeEnabled(GetIntrinsicSizeEnabledValue(false));
        delegate_->UpdateCssDisplayChangeEnabled(GetCssDisplayChangeEnabledValue(false));
        delegate_->UpdateNativeEmbedRuleTag(GetNativeEmbedRuleTagValue(""));
        delegate_->UpdateNativeEmbedRuleType(GetNativeEmbedRuleTypeValue(""));

        std::tuple<bool, bool> config = GetNativeVideoPlayerConfigValue({false, false});
        delegate_->UpdateNativeVideoPlayerConfig(std::get<0>(config), std::get<1>(config));

        if (GetEnableFollowSystemFontWeight()) {
            delegate_->UpdateEnableFollowSystemFontWeight(GetEnableFollowSystemFontWeight().value());
        }
        UpdateScrollBarWithBorderRadius();
    }

    // Set the default background color when the component did not set backgroundColor()
    // or needSetDefaultBackgroundColor_ is true.
    if (!renderContext->GetBackgroundColor() || needSetDefaultBackgroundColor_) {
        UpdateBackgroundColor(GetDefaultBackgroundColor().GetValue());
        needSetDefaultBackgroundColor_ = true;
    }

    // Initialize events such as keyboard, focus, etc.
    InitEvent();
    // Initialize web params.
    InitFeatureParam();
    InitializeAccessibility();
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
    InitInputEventReportCallback();
#endif
    // Initialize scrollupdate listener
    if (renderMode_ == RenderMode::SYNC_RENDER) {
        auto task = [weak = AceType::WeakClaim(this)]() {
            auto webPattern = weak.Upgrade();
            CHECK_NULL_VOID(webPattern);
            webPattern->InitSlideUpdateListener();
        };
        PostTaskToUI(std::move(task), "ArkUIWebInitSlideUpdateListener");
    }

    auto embedEnabledTask = [weak = AceType::WeakClaim(this)]() {
        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        if (webPattern->IsRootNeedExportTexture() && webPattern->delegate_) {
            webPattern->delegate_->UpdateNativeEmbedModeEnabled(false);
            webPattern->delegate_->SetNativeInnerWeb(true);
        }
    };
    PostTaskToUI(std::move(embedEnabledTask), "ArkUIWebUpdateNativeEmbedModeEnabled");

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    if (nodeAttach_) {
        pipelineContext->AddOnAreaChangeNode(host->GetId());
    }
    // offline mode
    if (host->GetNodeStatus() != NodeStatus::NORMAL_NODE) {
        InitInOfflineMode();
    }
    if (delegate_) {
        delegate_->SetSurfaceDensity(density_);
    }
    CheckAndSetWebNestedScrollExisted();
    UpdateScrollBarWithBorderRadius();
}

void WebPattern::SetSurfaceDensity(double density)
{
    density_ = density;
}

void WebPattern::UpdateScrollBarWithBorderRadius()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    if (!renderContext->GetBorderRadius().has_value()) {
        return;
    }
    auto borderRadius = renderContext->GetBorderRadius().value();
    auto clipState = renderContext->GetClipEdge().value_or(false);

    bool hasBorderRadiusValue = !borderRadius.radiusTopLeft.has_value() || !borderRadius.radiusTopRight.has_value() ||
                                !borderRadius.radiusBottomLeft.has_value() ||
                                !borderRadius.radiusBottomRight.has_value();
    if (hasBorderRadiusValue) {
        return;
    }

    CHECK_NULL_VOID(delegate_);
    if (clipState) {
        delegate_->SetBorderRadiusFromWeb(borderRadius.radiusTopLeft.value().Value(),
            borderRadius.radiusTopRight.value().Value(), borderRadius.radiusBottomLeft.value().Value(),
            borderRadius.radiusBottomRight.value().Value());
    } else {
        delegate_->SetBorderRadiusFromWeb(0.0f, 0.0f, 0.0f, 0.0f);
    }
}

extern "C" {
char* HandleWebMessage(const char** params, int32_t size)
{
#if defined(PREVIEW) || defined(ACE_UNITTEST)
    return nullptr;
#else
    if (!EventRecorder::Get().IsRecordEnable(Recorder::EventCategory::CATEGORY_WEB)) {
        return nullptr;
    }
    if (size < Recorder::WEB_PARAM_SIZE) {
        return nullptr;
    }
    for (int32_t i = 0; i < Recorder::WEB_PARAM_SIZE; i++) {
        if (params[i] == nullptr) {
            return nullptr;
        }
    }
    if (!EventRecorder::Get().IsMessageValid(
        params[Recorder::WEB_PARAM_INDEX_CATEGORY], params[Recorder::WEB_PARAM_INDEX_IDENTIFIER])) {
        return nullptr;
    }
    Recorder::EventParamsBuilder builder;
    builder.SetEventType(Recorder::EventType::WEB_ACTION)
        .SetEventCategory(Recorder::EventCategory::CATEGORY_WEB)
        .SetType(V2::WEB_ETS_TAG)
        .SetExtra(Recorder::KEY_WEB_CATEGORY, params[Recorder::WEB_PARAM_INDEX_CATEGORY])
        .SetText(params[Recorder::WEB_PARAM_INDEX_CONTENT]);
    EventRecorder::Get().OnEvent(std::move(builder));
    return nullptr;
#endif
}
}

void WebPattern::RecordWebEvent(bool isInit)
{
#if !defined(PREVIEW) && !defined(ACE_UNITTEST)
    TAG_LOGI(AceLogTag::ACE_WEB, "Web isInit %{public}d", isInit);
    CHECK_NULL_VOID(delegate_);
    if (isInit) {
        std::vector<std::pair<std::string, NativeMethodCallback>> methodList = {
            std::make_pair<std::string, NativeMethodCallback>(Recorder::WEB_METHOD_NAME, HandleWebMessage)
        };
        delegate_->RegisterNativeArkJSFunction(Recorder::WEB_OBJ_NAME, methodList, false);
        EventRecorder::Get().FillWebJsCode(onDocumentEndScriptItems_);
    }
#endif
}

bool WebPattern::RunJavascriptAsync(const std::string& jsCode, std::function<void(const std::string&)>&& callback)
{
#if !defined(PREVIEW) && !defined(ACE_UNITTEST)
    CHECK_NULL_RETURN(delegate_, false);
    delegate_->ExecuteTypeScript(jsCode, [cb = std::move(callback)](std::string result) { cb(result); });
    return true;
#else
    return false;
#endif
}

void WebPattern::LoadUrlInOfflineMode()
{
    if (!isUrlLoaded_) {
        isUrlLoaded_ = true;
        if (webSrc_) {
            delegate_->LoadUrl();
        } else if (webData_) {
            delegate_->LoadDataWithRichText();
        }
    }
}

void WebPattern::InitInOfflineMode()
{
    if (offlineWebInited_) {
        return;
    }
    ACE_SCOPED_TRACE("WebPattern::InitInOfflineMode");
    TAG_LOGI(AceLogTag::ACE_WEB, "Web offline mode type, webId:%{public}d", GetWebId());
    delegate_->OnRenderToBackground();
    offlineWebInited_ = true;
    isActive_ = false;
    isVisible_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int width = 0;
    int height = 0;
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto& calcLayout = layoutProperty->GetCalcLayoutConstraint();
    if (calcLayout) {
        width = calcLayout->selfIdealSize ?
            calcLayout->selfIdealSize->Width()->GetDimension().ConvertToPx() : 0;
        height = calcLayout->selfIdealSize ?
            calcLayout->selfIdealSize->Height()->GetDimension().ConvertToPx() : 0;
    }
    bool isUnSetSize = (width == 0) && (height == 0);
    auto container = Container::Current();
    uint64_t displayId = 0;
    if (container && container->GetCurrentDisplayId() != Rosen::DISPLAY_ID_INVALID) {
        displayId = container->GetCurrentDisplayId();
    }
    auto defaultDisplay = OHOS::Rosen::DisplayManager::GetInstance().GetDisplayById(displayId);
    if (isUnSetSize && defaultDisplay) {
        width = defaultDisplay->GetWidth();
        height = defaultDisplay->GetHeight();
    }
    Size drawSize = Size(width, height);
    Offset offset = Offset(0, 0);
    TAG_LOGD(AceLogTag::ACE_WEB, "InitInOfflineMode displayId : %{public}u, drawsize_ : %{public}s",
        (uint32_t)displayId, drawSize_.ToString().c_str());
    delegate_->SetBoundsOrResize(drawSize, offset);

    LoadUrlInOfflineMode();
    SetActiveStatusInner(false, true);
    delegate_->HideWebView();
    CloseContextSelectionMenu();
}

bool WebPattern::IsNeedResizeVisibleViewport()
{
    if (visibleViewportSize_.Width() < 0 || visibleViewportSize_.Height() < 0 ||
        isVirtualKeyBoardShow_ != VkState::VK_SHOW || NearZero(lastKeyboardHeight_)) {
        return false;
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    int32_t height = context->GetRootRect().Height();
    auto y = GetCoordinatePoint()->GetY();
    if (GreatOrEqual(height, lastKeyboardHeight_ + y)) {
        double newHeight = height - lastKeyboardHeight_ - y;
        if (GreatOrEqual(newHeight, drawSize_.Height()) ||
            NearEqual(newHeight, drawSize_.Height())) {
            visibleViewportSize_.SetWidth(-1.0);
            visibleViewportSize_.SetHeight(-1.0);
        } else {
            return false;
        }
    } else {
        visibleViewportSize_.SetWidth(-1.0);
        visibleViewportSize_.SetHeight(-1.0);
    }
    delegate_->ResizeVisibleViewport(visibleViewportSize_, false);
    return true;
}

bool WebPattern::ProcessVirtualKeyBoardHide(int32_t width, int32_t height, bool safeAreaEnabled)
{
    isResizeContentAvoid_ = false;
    isKeyboardInSafeArea_ = false;
    if (safeAreaEnabled) {
        isVirtualKeyBoardShow_ = VkState::VK_HIDE;
        return false;
    }
    if (isVirtualKeyBoardShow_ != VkState::VK_SHOW) {
        return false;
    }
    if (layoutMode_ == WebLayoutMode::FIT_CONTENT) {
        TAG_LOGI(AceLogTag::ACE_WEB, "ProcessVirtualKeyBoardHide layoutMode is FIT_CONTENT");
        isVirtualKeyBoardShow_ = VkState::VK_HIDE;
        return true;
    }
    drawSize_.SetSize(drawSizeCache_);
    visibleViewportSize_.SetWidth(-1.0);
    visibleViewportSize_.SetHeight(-1.0);
    UpdateWebLayoutSize(width, height, false);
    isVirtualKeyBoardShow_ = VkState::VK_HIDE;
    return true;
}

bool WebPattern::UpdateLayoutAfterKeyboard(int32_t width, int32_t height, double keyboard)
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    lastKeyboardHeight_ = keyboard;
    keyboardGetready_ = true;
    taskExecutor->PostDelayedTask(
        [weak = WeakClaim(this), width, height]() {
            auto webPattern = weak.Upgrade();
            CHECK_NULL_VOID(webPattern);
            // In split-screen mode, the keyboard height is reported multiple times and is not the same.
            // Use the last height.
            webPattern->UpdateLayoutAfterKeyboardShow(width,
                                                      height,
                                                      webPattern->lastKeyboardHeight_,
                                                      webPattern->GetDrawSize().Height());
            webPattern->keyboardGetready_ = false;
        }, TaskExecutor::TaskType::UI, UPDATE_WEB_LAYOUT_DELAY_TIME, "ArkUIWebUpdateLayoutAfterKeyboardShow");
    return true;
}

bool WebPattern::ProcessVirtualKeyBoardShow(int32_t width, int32_t height, double keyboard, bool safeAreaEnabled)
{
    if (IsDialogNested()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "ProcessVirtualKeyBoardShow, dialog nested, web don't consume keyboard event.");
        isKeyboardInSafeArea_ = true;
        return false;
    }
    if (isVirtualKeyBoardShow_ != VkState::VK_SHOW) {
        drawSizeCache_.SetSize(drawSize_);
    }
    if (drawSizeCache_.Height() <= (height - keyboard - GetCoordinatePoint()->GetY())) {
        TAG_LOGI(AceLogTag::ACE_WEB, "ProcessVirtualKeyBoardShow not obstruct");
        isVirtualKeyBoardShow_ = VkState::VK_SHOW;
        lastKeyboardHeight_ = keyboard;
        return !safeAreaEnabled;
    }
    if (height - GetCoordinatePoint()->GetY() < keyboard) {
        TAG_LOGI(AceLogTag::ACE_WEB, "ProcessVirtualKeyBoardShow Complete occlusion");
        isVirtualKeyBoardShow_ = VkState::VK_SHOW;
        return true;
    }
    if (!delegate_->NeedSoftKeyboard()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "ProcessVirtualKeyBoardShow not NeedSoftKeyboard");
        return false;
    }
    isVirtualKeyBoardShow_ = VkState::VK_SHOW;
    if (layoutMode_ == WebLayoutMode::FIT_CONTENT) {
        TAG_LOGI(AceLogTag::ACE_WEB, "ProcessVirtualKeyBoardShow layoutMode is FIT_CONTENT");
        lastKeyboardHeight_ = keyboard;
        return true;
    }
    if (safeAreaEnabled) {
        isKeyboardInSafeArea_ = true;
        lastKeyboardHeight_ = keyboard;
        return false;
    }

    if (!UpdateLayoutAfterKeyboard(width, height, keyboard)) {
        return false;
    }
    return true;
}

bool WebPattern::ProcessVirtualKeyBoard(int32_t width, int32_t height, double keyboard, bool isCustomKeyboard)
{
    if (isUsingCustomKeyboardAvoid_) {
        if (!isCustomKeyboard) {
            // if use custom keyboard, no need to handle the system keyboard event.
            TAG_LOGI(AceLogTag::ACE_WEB, "ProcessVirtualKeyBoard no need to handle the system keyboard event.");
            return false;
        }
    }
    CHECK_NULL_RETURN(delegate_, false);
    if (delegate_->ShouldVirtualKeyboardOverlay()) {
        if (!IsDialogNested()) {
            double webKeyboard = keyboard - (height - GetCoordinatePoint()->GetY() - drawSize_.Height());
            webKeyboard = (webKeyboard < 0) ? 0 : webKeyboard;
            TAG_LOGI(AceLogTag::ACE_WEB, "VirtualKeyboard Overlaycontent is true webKeyboard:%{public}f", webKeyboard);
            delegate_->SetVirtualKeyBoardArg(width, height, webKeyboard);
        } else {
            delegate_->SetVirtualKeyBoardArg(width, height, 0);
        }
    } else {
        delegate_->SetVirtualKeyBoardArg(width, height, keyboard);
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, false);
    bool keyboardSafeAreaEnabled = safeAreaManager->KeyboardSafeAreaEnabled();
    TAG_LOGI(AceLogTag::ACE_WEB,
        "ProcessVirtualKeyBoard width:%{public}d, height:%{public}d, keyboard:%{public}f, safeArea:%{public}d", width,
        height, keyboard, keyboardSafeAreaEnabled);
    if (!isFocus_ || !isVisible_) {
        UpdateOnFocusTextField(false);
        ProcessVirtualKeyBoardHideAvoidMenu(width, height, keyboardSafeAreaEnabled);
        return false;
    }
    UpdateOnFocusTextField(!NearZero(keyboard));
    if (NearZero(keyboard)) {
        return ProcessVirtualKeyBoardHideAvoidMenu(width, height, keyboardSafeAreaEnabled);
    }
    return ProcessVirtualKeyBoardShowAvoidMenu(width, height, keyboard, keyboardSafeAreaEnabled);
}

bool WebPattern::ProcessVirtualKeyBoardShowAvoidMenu(
    int32_t width, int32_t height, double keyboard, bool safeAreaEnabled)
{
    if (ProcessVirtualKeyBoardShow(width, height, keyboard, safeAreaEnabled)) {
        MenuAvoidKeyboard(false, keyboard);
        return true;
    }
    return false;
}

bool WebPattern::ProcessVirtualKeyBoardHideAvoidMenu(int32_t width, int32_t height, bool safeAreaEnabled)
{
    if (ProcessVirtualKeyBoardHide(width, height, safeAreaEnabled)) {
        MenuAvoidKeyboard(true);
        return true;
    }
    return false;
}

void WebPattern::UpdateWebLayoutSize(int32_t width, int32_t height, bool isKeyboard, bool isUpdate)
{
    CHECK_NULL_VOID(delegate_);
    if (delegate_->ShouldVirtualKeyboardOverlay()) {
        TAG_LOGW(AceLogTag::ACE_WEB, "VirtualKeyboard Overlaycontent is true and does not require resizing");
        return;
    }
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto rect = frameNode->GetRenderContext()->GetPaintRectWithoutTransform();
    auto offset = Offset(GetCoordinatePoint()->GetX(), GetCoordinatePoint()->GetY());

    // Scroll focused node into view when keyboard show.
    TAG_LOGI(AceLogTag::ACE_WEB, "UpdateWebLayoutSize drawsize_ : %{public}s, web id : %{public}d",
        drawSize_.ToString().c_str(), GetWebId());
    delegate_->SetBoundsOrResize(drawSize_, offset, isKeyboard);
    delegate_->ResizeVisibleViewport(visibleViewportSize_, isKeyboard);

    if (isUpdate) {
        ACE_SCOPED_TRACE("WebPattern::UpdateWebLayoutSize rect: %s", rect.ToString().c_str());
        if (renderMode_ == RenderMode::SYNC_RENDER) {
            renderSurface_->SetIsNeedSyncGeometryProperties(true);
            renderSurface_->SetKeyBoardAvoidRect(rect);
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF | PROPERTY_UPDATE_RENDER);
        } else {
            rect.SetSize(SizeF(drawSize_.Width(), drawSize_.Height()));
            frameNode->GetRenderContext()->SyncGeometryProperties(rect);
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    }
}

void WebPattern::HandleTouchDown(const TouchEventInfo& info, bool fromOverlay)
{
    if (!fromOverlay) {
        CloseContextSelectionMenu();
    }
    isTouchUpEvent_ = false;
    InitTouchEventListener();
    CHECK_NULL_VOID(delegate_);
    Offset touchOffset = Offset(0, 0);
    std::list<TouchInfo> touchInfos;
    if (!ParseTouchInfo(info, touchInfos)) {
        return;
    }
    for (auto& touchPoint : touchInfos) {
        if (fromOverlay) {
            touchPoint.x -= webOffset_.GetX();
            touchPoint.y -= webOffset_.GetY();
            TAG_LOGI(AceLogTag::ACE_WEB,
                "SelectOverlay touch down add id:%{public}d.", touchPoint.id);
            touchOverlayInfo_.push_back(touchPoint);
        }
        touchPointX = touchPoint.x;
        touchPointY = touchPoint.y;
        if (info.GetSourceTool() == SourceTool::PEN &&
            delegate_->SetFocusByPosition(touchPointX, touchPointY) &&
            StylusDetectorMgr::GetInstance()->IsNeedInterceptedTouchEventForWeb(touchPointX, touchPointY)) {
            TAG_LOGI(AceLogTag::ACE_WEB, "stylus touch down is editable.");
            isNeedInterceptedTouchEvent_ = true;
            WebRequestFocus();
            return;
        }
        if (info.GetSourceTool() == SourceTool::PEN && !IS_CALLING_FROM_M114()) {
            std::shared_ptr<OHOS::NWeb::NWebStylusTouchPointInfo> stylus_touch_point_info =
                std::make_shared<NWebStylusTouchPointInfoImpl>(touchPoint.id, touchPoint.x, touchPoint.y,
                    touchPoint.force, touchPoint.tiltX, touchPoint.tiltY, touchPoint.rollAngle, touchPoint.width,
                    touchPoint.height, static_cast<OHOS::NWeb::SourceTool>(touchPoint.sourceTool));
            delegate_->HandleStylusTouchDown(stylus_touch_point_info, fromOverlay);
        } else {
            delegate_->HandleTouchDown(touchPoint.id, touchPoint.x, touchPoint.y, fromOverlay);
        }
        if (overlayCreating_) {
            imageAnalyzerManager_->UpdateOverlayTouchInfo(touchPoint.x, touchPoint.y, TouchType::DOWN);
        }
    }
    if (IsDefaultGestureFocusMode() && !touchInfos.empty() && !GetNativeEmbedModeEnabledValue(false)) {
        WebRequestFocus();
    }
}

void WebPattern::HandleTouchUp(const TouchEventInfo& info, bool fromOverlay)
{
    isTouchUpEvent_ = true;
    UninitTouchEventListener();
    if (isNeedInterceptedTouchEvent_ && info.GetSourceTool() == SourceTool::PEN) {
        isNeedInterceptedTouchEvent_ = false;
        return;
    }
    CHECK_NULL_VOID(delegate_);
    if (!isReceivedArkDrag_) {
        ResetDragAction();
    }
    if (isDragging_) {
        ResetDragStateValue();
    }
    HideMagnifier();
    std::list<TouchInfo> touchInfos;
    if (!ParseTouchInfo(info, touchInfos)) {
        return;
    }
    touchEventInfoList_.clear();
    for (auto& touchPoint : touchInfos) {
        if (fromOverlay) {
            touchPoint.x -= webOffset_.GetX();
            touchPoint.y -= webOffset_.GetY();
            DelTouchOverlayInfoByTouchId(touchPoint.id);
        }

        if (info.GetSourceTool() == SourceTool::PEN && !IS_CALLING_FROM_M114()) {
            std::shared_ptr<OHOS::NWeb::NWebStylusTouchPointInfo> stylus_touch_point_info =
                std::make_shared<NWebStylusTouchPointInfoImpl>(touchPoint.id, touchPoint.x, touchPoint.y,
                    touchPoint.force, touchPoint.tiltX, touchPoint.tiltY, touchPoint.rollAngle, touchPoint.width,
                    touchPoint.height, static_cast<OHOS::NWeb::SourceTool>(touchPoint.sourceTool));
            delegate_->HandleStylusTouchUp(stylus_touch_point_info, fromOverlay);
        } else {
            delegate_->HandleTouchUp(touchPoint.id, touchPoint.x, touchPoint.y, fromOverlay);
        }

        if (overlayCreating_) {
            if (imageAnalyzerManager_) {
                imageAnalyzerManager_->UpdateOverlayTouchInfo(touchPoint.x, touchPoint.y, TouchType::UP);
            }
            overlayCreating_ = false;
        }
    }
}

void WebPattern::OnMagnifierHandleMove(const RectF& handleRect, bool isFirst)
{
    auto localX = handleRect.GetX() - webOffset_.GetX() + handleRect.Width() / HALF;
    auto localY = handleRect.GetY() - webOffset_.GetY() + handleRect.Height() / HALF;
    ShowMagnifier(localX, localY);
}

void WebPattern::HandleTouchMove(const TouchEventInfo& info, bool fromOverlay)
{
    CHECK_EQUAL_VOID(isNeedInterceptedTouchEvent_ && info.GetSourceTool() == SourceTool::PEN, true);
    if (isDragging_) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    if (manager->IsDragged()) {
        return;
    }
    CHECK_NULL_VOID(delegate_);
    std::list<TouchInfo> touchInfos;

    touchEventInfoList_.emplace_back(info);
    for (const auto& touchEventInfo : touchEventInfoList_) {
        ParseTouchInfo(touchEventInfo, touchInfos);
    }

    if (touchInfos.empty()) {
        return;
    }
    if (!info.GetTouchEventsEnd()) {
        return;
    }
    touchEventInfoList_.clear();

    touchInfos.sort([](const TouchInfo &point1, const TouchInfo &point2) {
        return point1.id < point2.id;
    });

    std::vector<std::shared_ptr<OHOS::NWeb::NWebTouchPointInfo>> touch_point_infos;
    std::vector<std::shared_ptr<OHOS::NWeb::NWebStylusTouchPointInfo>> stylus_touch_point_infos;
    for (auto& touchPoint : touchInfos) {
        if (fromOverlay) {
            touchPoint.x -= webOffset_.GetX();
            touchPoint.y -= webOffset_.GetY();
        }
        touchPointX = touchPoint.x;
        touchPointY = touchPoint.y;
        if (magnifierController_ && magnifierController_->GetMagnifierNodeExist()) {
            ShowMagnifier(touchPoint.x, touchPoint.y);
        }

        if (info.GetSourceTool() == SourceTool::PEN && !IS_CALLING_FROM_M114()) {
            std::shared_ptr<OHOS::NWeb::NWebStylusTouchPointInfo> stylus_touch_point_info =
                std::make_shared<NWebStylusTouchPointInfoImpl>(touchPoint.id, touchPoint.x, touchPoint.y,
                    touchPoint.force, touchPoint.tiltX, touchPoint.tiltY, touchPoint.rollAngle, touchPoint.width,
                    touchPoint.height, static_cast<OHOS::NWeb::SourceTool>(touchPoint.sourceTool));
            stylus_touch_point_infos.emplace_back(stylus_touch_point_info);
        } else {
            std::shared_ptr<OHOS::NWeb::NWebTouchPointInfo> touch_point_info =
                std::make_shared<NWebTouchPointInfoImpl>(touchPoint.id, touchPoint.x, touchPoint.y);
            touch_point_infos.emplace_back(touch_point_info);
        }

        if (overlayCreating_) {
            imageAnalyzerManager_->UpdateOverlayTouchInfo(touchPoint.x, touchPoint.y, TouchType::MOVE);
        }
    }

    if (!overlayCreating_) {
        if (info.GetSourceTool() == SourceTool::PEN && !IS_CALLING_FROM_M114()) {
            delegate_->HandleStylusTouchMove(stylus_touch_point_infos, fromOverlay);
        } else {
            delegate_->HandleTouchMove(touch_point_infos, fromOverlay);
        }
    }
}

void WebPattern::HandleTouchCancel(const TouchEventInfo& info)
{
    UninitTouchEventListener();
    if (isNeedInterceptedTouchEvent_ && info.GetSourceTool() == SourceTool::PEN) {
        isNeedInterceptedTouchEvent_ = false;
        return;
    }
    if (IsRootNeedExportTexture()) {
        HandleTouchUp(info, false);
    }
    CHECK_NULL_VOID(delegate_);
    delegate_->HandleTouchCancel();
    touchEventInfoList_.clear();
    if (overlayCreating_) {
        imageAnalyzerManager_->UpdateOverlayTouchInfo(0, 0, TouchType::CANCEL);
        overlayCreating_ = false;
    }
    HideMagnifier();
}

bool WebPattern::ParseTouchInfo(const TouchEventInfo& info, std::list<TouchInfo>& touchInfos)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    auto viewScale = context->GetViewScale();
    if (info.GetChangedTouches().empty()) {
        return false;
    }
    for (const auto& point : info.GetChangedTouches()) {
        TouchInfo touchInfo;
        touchInfo.id = point.GetFingerId();
        const Offset& location = point.GetLocalLocation();
        touchInfo.x = static_cast<float>(location.GetX() * viewScale);
        touchInfo.y = static_cast<float>(location.GetY() * viewScale);
        touchInfo.sourceTool = point.GetSourceTool();
        touchInfo.force = point.GetForce();
        touchInfo.tiltX = point.GetTiltX().value_or(0);
        touchInfo.tiltY = point.GetTiltY().value_or(0);
        touchInfo.rollAngle = point.GetRollAngle().value_or(0);
        touchInfo.width = point.GetWidth();
        touchInfo.height = point.GetHeight();
        touchInfos.emplace_back(touchInfo);
    }
    return true;
}

void WebPattern::RequestFullScreen()
{
    isFullScreen_ = true;
}

void WebPattern::ExitFullScreen()
{
    isFullScreen_ = false;
}

std::optional<OffsetF> WebPattern::GetCoordinatePoint()
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    return frameNode->GetTransformRelativeOffset();
}

void WebPattern::DelTouchOverlayInfoByTouchId(int32_t touchId)
{
    std::list<TouchInfo>::iterator iter;
    for (iter = touchOverlayInfo_.begin(); iter != touchOverlayInfo_.end();) {
        if (iter->id == touchId) {
            TAG_LOGI(AceLogTag::ACE_WEB,
                "SelectOverlay del touch overlay info by id:%{public}d", iter->id);
            iter = touchOverlayInfo_.erase(iter);
        } else {
            ++iter;
        }
    }
}

void WebPattern::CloseSelectOverlay()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (webSelectOverlay_ && webSelectOverlay_->IsShowHandle()) {
        webSelectOverlay_->CloseOverlay(false, CloseReason::CLOSE_REASON_CLICK_OUTSIDE);
        webSelectOverlay_->SetIsShowHandle(false);
        for (auto& touchOverlayInfo : touchOverlayInfo_) {
            TAG_LOGI(AceLogTag::ACE_WEB, "SelectOverlay send touch up id:%{public}d", touchOverlayInfo.id);
            delegate_->HandleTouchUp(touchOverlayInfo.id, touchOverlayInfo.x, touchOverlayInfo.y, true);
            HideMagnifier();
        }
        touchOverlayInfo_.clear();
    }
}

RectF WebPattern::ComputeMouseClippedSelectionBounds(int32_t x, int32_t y, int32_t w, int32_t h)
{
    auto offset = GetCoordinatePoint().value_or(OffsetF());
    float selectX = offset.GetX() + x;
    float selectY = offset.GetY();
    float selectWidth = w;
    float selectHeight = h;
    if (LessOrEqual(GetHostFrameSize().value_or(SizeF()).Height(), y)) {
        selectY += GetHostFrameSize().value_or(SizeF()).Height();
    } else if (y + h <= 0) {
        selectY -= h;
    } else {
        selectY += y;
    }
    return RectF(selectX, selectY, selectWidth, selectHeight);
}

void WebPattern::UpdateClippedSelectionBounds(int32_t x, int32_t y, int32_t w, int32_t h)
{
    selectArea_ = ComputeMouseClippedSelectionBounds(x, y, w, h);
    if (webSelectOverlay_) {
        webSelectOverlay_->UpdateClippedSelectionBounds(x, y, w, h);
    }
}

void WebPattern::SelectCancel() const
{
    if (isReceivedArkDrag_) {
        return;
    }
    if (webSelectOverlay_) {
        webSelectOverlay_->SelectCancel();
    }
}

bool WebPattern::IsSelectInfoValid()
{
    auto info = GetSelectInfo();
    return !info.empty() && info != STRING_LF;
}

std::optional<RectF> WebPattern::GetViewPort() const
{
    CHECK_NULL_RETURN(GetHost(), std::nullopt);
    auto parentNode = GetHost()->GetAncestorNodeOfFrame(true);
    while (parentNode) {
        auto scrollablePattern = AceType::DynamicCast<NestableScrollContainer>(parentNode->GetPattern());
        auto geometryNode = parentNode->GetGeometryNode();
        if (scrollablePattern && geometryNode) {
            auto offsetRelativeToWindow = parentNode->GetOffsetRelativeToWindow();
            return RectF(offsetRelativeToWindow, geometryNode->GetFrameRect().GetSize());
        }
        parentNode = parentNode->GetAncestorNodeOfFrame(true);
    }
    return std::nullopt;
}

std::string WebPattern::GetSelectInfo() const
{
    CHECK_NULL_RETURN(delegate_, std::string());
    return delegate_->GetSelectInfo();
}

void  WebPattern::OnSelectionMenuOptionsUpdate(const WebMenuOptionsParam& webMenuOption)
{
    menuOptionParam_ = std::move(webMenuOption.menuOption);
    for (auto& menuOption : menuOptionParam_) {
        std::function<void(const std::string&)> action = std::move(menuOption.action);
        menuOption.action = [weak = AceType::WeakClaim(this), action] (
                                const std::string selectInfo) {
            auto webPattern = weak.Upgrade();
            CHECK_NULL_VOID(webPattern);
            webPattern->SelectCancel();
            std::string selectStr = webPattern->GetSelectInfo();
            if (action) {
                action(selectStr);
            }
        };
    }
}

void WebPattern::UpdateEditMenuOptions(const NG::OnCreateMenuCallback&& onCreateMenuCallback,
    const NG::OnMenuItemClickCallback&& onMenuItemClick, const NG::OnPrepareMenuCallback&& onPrepareMenuCallback)
{
    onCreateMenuCallback_ = std::move(onCreateMenuCallback);
    onMenuItemClick_ = [weak = AceType::WeakClaim(this), action = std::move(onMenuItemClick)] (
                            const OHOS::Ace::NG::MenuItemParam& menuItem) -> bool {
        auto webPattern = weak.Upgrade();
        bool result = false;
        if (action) {
            result = action(menuItem);
        }
        CHECK_NULL_RETURN(webPattern, result);
        if (!result && webPattern->IsQuickMenuShow()) {
            webPattern->webSelectOverlay_->HideMenu(true);
        }
        return result;
    };
    if (onPrepareMenuCallback) {
        onPrepareMenuCallback_ = std::move(onPrepareMenuCallback);
    }
}

void WebPattern::UpdateDataDetectorConfig(const TextDetectConfig& config)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::UpdateDataDetectorConfig");
    auto adapter = GetDataDetectorAdapter();
    CHECK_NULL_VOID(adapter);
    adapter->SetDataDetectorConfig(config);
}

void WebPattern::HideHandleAndQuickMenuIfNecessary(bool hide, bool isScroll)
{
    if (webSelectOverlay_) {
        webSelectOverlay_->HideHandleAndQuickMenuIfNecessary(hide, isScroll);
    }
}

void WebPattern::ChangeVisibilityOfQuickMenu()
{
    CHECK_NULL_VOID(webSelectOverlay_);
    webSelectOverlay_->ChangeVisibilityOfQuickMenu();
}

bool WebPattern::ChangeVisibilityOfQuickMenuV2()
{
    if (webSelectOverlay_ && webSelectOverlay_->IsShowHandle()) {
        webSelectOverlay_->ChangeVisibilityOfQuickMenu();
        return true;
    }
    return false;
}

bool WebPattern::IsQuickMenuShow()
{
    CHECK_NULL_RETURN(webSelectOverlay_, false);
    return webSelectOverlay_->IsShowMenu();
}

bool WebPattern::RunQuickMenu(std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback)
{
    if (!webSelectOverlay_) {
        webSelectOverlay_ = AceType::MakeRefPtr<WebSelectOverlay>(WeakClaim(this));
    }
    if (webSelectOverlay_->RunQuickMenu(params, callback)) {
        DestroyAnalyzerOverlay();
        CloseDataDetectorMenu();
        return true;
    }
    return false;
}

void WebPattern::ShowMagnifier(int centerOffsetX, int centerOffsetY)
{
    if (magnifierController_) {
        OffsetF localOffset = OffsetF(centerOffsetX, centerOffsetY);
        magnifierController_->SetLocalOffset(localOffset);
    }
}

void WebPattern::HideMagnifier()
{
    TAG_LOGD(AceLogTag::ACE_WEB, "HideMagnifier");
    if (magnifierController_) {
        magnifierController_->RemoveMagnifierFrameNode();
    }
}

OffsetF WebPattern::GetTextPaintOffset() const
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, OffsetF());
    return frameNode->GetTransformRelativeOffset();
}

void WebPattern::OnQuickMenuDismissed()
{
    CloseSelectOverlay();
}

void WebPattern::DumpViewDataPageNode(RefPtr<ViewDataWrap> viewDataWrap, bool needsRecordData)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "called");
    CHECK_NULL_VOID(viewDataWrap);
    for (const auto& nodeInfo : pageNodeInfo_) {
        if (nodeInfo) {
            viewDataWrap->AddPageNodeInfoWrap(nodeInfo);
        }
    }
    viewDataWrap->SetPageUrl(viewDataCommon_->GetPageUrl());
    viewDataWrap->SetUserSelected(viewDataCommon_->IsUserSelected());
    viewDataWrap->SetOtherAccount(viewDataCommon_->IsOtherAccount());
}

void WebPattern::NotifyFillRequestSuccess(RefPtr<ViewDataWrap> viewDataWrap,
    RefPtr<PageNodeInfoWrap> nodeWrap, AceAutoFillType autoFillType)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "called");
    CHECK_NULL_VOID(viewDataWrap);
    auto nodeInfoWraps = viewDataWrap->GetPageNodeInfoWraps();
    auto jsonNode = JsonUtil::Create(true);
    AceAutoFillType focusType = AceAutoFillType::ACE_UNSPECIFIED;
    for (const auto& nodeInfoWrap : nodeInfoWraps) {
        if (nodeInfoWrap == nullptr) {
            continue;
        }
        auto type = nodeInfoWrap->GetAutoFillType();
        // white list check
        if (ACE_AUTOFILL_TYPE_TO_NWEB.count(type) != 0) {
            std::string key = ACE_AUTOFILL_TYPE_TO_NWEB.at(type);
            if (nodeInfoWrap->GetMetadata() != IS_HINT_TYPE) {
                jsonNode->Put(key.c_str(), nodeInfoWrap->GetValue().c_str());
            } else {
                auto json = JsonUtil::Create(true);
                json->Put(OHOS::NWeb::NWEB_VIEW_DATA_KEY_PLACEHOLDER.c_str(), nodeInfoWrap->GetId());
                json->Put(OHOS::NWeb::NWEB_VIEW_DATA_KEY_VALUE.c_str(), nodeInfoWrap->GetValue().c_str());
                jsonNode->Put(key.c_str(), std::move(json));
            }
        }
        if (nodeInfoWrap->GetIsFocus()) {
            focusType = type;
        }
    }
    auto pageUrl = viewDataWrap->GetPageUrl();
    jsonNode->Put(AUTO_FILL_VIEW_DATA_PAGE_URL.c_str(), pageUrl.c_str());
    auto otherAccount = viewDataWrap->GetOtherAccount();
    jsonNode->Put(AUTO_FILL_VIEW_DATA_OTHER_ACCOUNT.c_str(), otherAccount);
    delegate_->NotifyAutoFillViewData(jsonNode->ToString());

    // shift focus after autofill
    if (focusType != AceAutoFillType::ACE_UNSPECIFIED && !isPasswordFill_) {
        for (const auto& nodeInfo : pageNodeInfo_) {
            if (nodeInfo && nodeInfo->GetAutoFillType() == focusType) {
                TouchEventInfo info("autofill");
                TouchLocationInfo location("autofill", 0);
                auto rectF = nodeInfo->GetPageNodeRect();
                location.SetLocalLocation(
                    Offset(rectF.GetX() - requestedWebOffset_.GetX() + (rectF.Width() / POPUP_CALCULATE_RATIO),
                        rectF.GetY() - requestedWebOffset_.GetY() + (rectF.Height() / POPUP_CALCULATE_RATIO)));
                info.AddChangedTouchLocationInfo(std::move(location));
                HandleTouchDown(info, false);
                HandleTouchUp(info, false);
                break;
            }
        }
    }
}

void WebPattern::NotifyFillRequestFailed(int32_t errCode, const std::string& fillContent, bool isPopup)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "called, errCode:%{public}d", errCode);
    if (isPasswordFill_) {
        delegate_->AutofillCancel(fillContent);
    }
}

void WebPattern::ParseViewDataNumber(const std::string& key, int32_t value,
    RefPtr<PageNodeInfoWrap> node, RectT<float>& rect, float viewScale)
{
    CHECK_NULL_VOID(viewScale > FLT_EPSILON);
    CHECK_NULL_VOID(node);
    if (key == OHOS::NWeb::NWEB_VIEW_DATA_KEY_FOCUS) {
        node->SetIsFocus(static_cast<bool>(value));
    } else if (key == OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_X) {
        rect.SetLeft(value / viewScale);
    } else if (key == OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_Y) {
        rect.SetTop(value / viewScale);
    } else if (key == OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_W) {
        rect.SetWidth(value / viewScale);
    } else if (key == OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_H) {
        rect.SetHeight(value / viewScale);
    }
}

void ParseViewDataString(const std::string& key,
    const std::string& value, RefPtr<PageNodeInfoWrap> node)
{
    CHECK_NULL_VOID(node);
    if (key == OHOS::NWeb::NWEB_VIEW_DATA_KEY_VALUE) {
        node->SetValue(value);
    } else if (key == OHOS::NWeb::NWEB_VIEW_DATA_KEY_PLACEHOLDER) {
        node->SetPlaceholder(value);
    }
}

HintToTypeWrap WebPattern::GetHintTypeAndMetadata(const std::string& attribute, RefPtr<PageNodeInfoWrap> node)
{
    HintToTypeWrap hintToTypeWrap;
    if (NWEB_AUTOFILL_TYPE_OFF == attribute) {
        return hintToTypeWrap;
    }
    auto placeholder = node->GetPlaceholder();
    if (NWEB_AUTOFILL_TYPE_TO_ACE.count(attribute) != 0) {
        AceAutoFillType type = NWEB_AUTOFILL_TYPE_TO_ACE.at(attribute);
        if (node->GetIsFocus()) {
            if (type == AceAutoFillType::ACE_USER_NAME || type == AceAutoFillType::ACE_PASSWORD ||
                type == AceAutoFillType::ACE_NEW_PASSWORD) {
                TAG_LOGI(AceLogTag::ACE_WEB, "The form is login fill form");
                isPasswordFill_ = true;
            }
        }
        hintToTypeWrap.autoFillType = type;
    } else if (!placeholder.empty()) {
        // try hint2Type
        auto host = GetHost();
        CHECK_NULL_RETURN(host, hintToTypeWrap);
        auto container = Container::Current();
        if (container == nullptr) {
            container = Container::GetActive();
        }
        CHECK_NULL_RETURN(container, hintToTypeWrap);
        hintToTypeWrap = container->PlaceHolderToType(placeholder);
    }
    return hintToTypeWrap;
}

void WebPattern::ParseNWebViewDataNode(std::unique_ptr<JsonValue> child,
    std::vector<RefPtr<PageNodeInfoWrap>>& nodeInfos, int32_t nodeId)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    float viewScale = pipelineContext->GetViewScale();
    CHECK_NULL_VOID(viewScale > FLT_EPSILON);

    RefPtr<PageNodeInfoWrap> node = PageNodeInfoWrap::CreatePageNodeInfoWrap();
    std::string attribute = child->GetKey();

    RectT<float> rect;
    int32_t len = child->GetArraySize();
    for (int32_t index = 0; index < len; index++) {
        auto object = child->GetArrayItem(index);
        if (object == nullptr || !object->IsObject()) {
            continue;
        }
        for (auto child = object->GetChild(); child && !child->IsNull(); child = child->GetNext()) {
            if (child->IsString()) {
                ParseViewDataString(child->GetKey(), child->GetString(), node);
            } else if (child->IsNumber()) {
                ParseViewDataNumber(child->GetKey(), child->GetInt(), node, rect, viewScale);
            }
        }
    }

    HintToTypeWrap hintToTypeWrap = GetHintTypeAndMetadata(attribute, node);
    auto type = hintToTypeWrap.autoFillType;
    if (type != AceAutoFillType::ACE_UNSPECIFIED) {
        node->SetAutoFillType(type);
        node->SetMetadata(hintToTypeWrap.metadata);
    } else {
        return;
    }

    NG::RectF rectF;
    rectF.SetRect(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
    node->SetPageNodeRect(rectF);
    node->SetId(nodeId);
    node->SetDepth(-1);
    nodeInfos.emplace_back(node);
}

void WebPattern::ParseNWebViewDataCommonField(std::unique_ptr<JsonValue> child,
    const std::shared_ptr<ViewDataCommon>& viewDataCommon)
{
    std::string key = child->GetKey();
    if (child->IsString() && key == OHOS::NWeb::NWEB_AUTOFILL_EVENT_TYPE) {
        std::string eventType = child->GetString();
        if (NWEB_AUTOFILL_EVENTS.count(eventType) != 0) {
            OHOS::NWeb::NWebAutofillEvent event = NWEB_AUTOFILL_EVENTS.at(eventType);
            viewDataCommon->SetEventType(event);
        }
    }
    if (child->IsString() && key == OHOS::NWeb::NWEB_AUTOFILL_PAGE_URL) {
        viewDataCommon->SetPageUrl(child->GetString());
    }
    if (child->IsBool() && key == OHOS::NWeb::NWEB_AUTOFILL_IS_USER_SELECTED) {
        viewDataCommon->SetUserSelectedFlag(child->GetBool());
    }
    if (child->IsBool() && key == OHOS::NWeb::NWEB_AUTOFILL_IS_OTHER_ACCOUNT) {
        viewDataCommon->SetOtherAccountFlag(child->GetBool());
    }
    if (child->IsString() && key == OHOS::NWeb::NWEB_AUTOFILL_EVENT_SOURCE) {
        viewDataCommon->SetSource(child->GetString());
    }
}

void WebPattern::ParseNWebViewDataJson(const std::string& viewDataJson,
    std::vector<RefPtr<PageNodeInfoWrap>>& nodeInfos, const std::shared_ptr<ViewDataCommon>& viewDataCommon)
{
    nodeInfos.clear();
    auto sourceJson = JsonUtil::ParseJsonString(viewDataJson);
    if (sourceJson == nullptr || sourceJson->IsNull()) {
        return;
    }

    int32_t nodeId = 1;
    int32_t len = sourceJson->GetArraySize();
    for (int32_t index = 0; index < len; index++) {
        auto object = sourceJson->GetArrayItem(index);
        if (object == nullptr || !object->IsObject()) {
            continue;
        }
        auto child = object->GetChild();
        if (child == nullptr || child->IsNull()) {
            continue;
        }
        if (child->IsArray()) {
            ParseNWebViewDataNode(std::move(child), nodeInfos, nodeId);
            nodeId++;
        } else {
            ParseNWebViewDataCommonField(std::move(child), viewDataCommon);
        }
    }
}

AceAutoFillType WebPattern::GetFocusedType()
{
    AceAutoFillType type = AceAutoFillType::ACE_UNSPECIFIED;
    for (const auto& nodeInfo : pageNodeInfo_) {
        if (nodeInfo && nodeInfo->GetIsFocus()) {
            type = static_cast<AceAutoFillType>(nodeInfo->GetAutoFillType());
            break;
        }
    }
    if (ACE_AUTOFILL_TYPE_TO_NWEB.count(type) != 0) {
        std::string key = ACE_AUTOFILL_TYPE_TO_NWEB.at(type);
        TAG_LOGI(AceLogTag::ACE_WEB, "type:%{public}s", key.c_str());
    }
    return type;
}

bool WebPattern::HandleAutoFillEvent()
{
    if (isPasswordFill_ && viewDataCommon_->GetSource() != OHOS::NWeb::NWEB_AUTOFILL_FOR_LOGIN) {
        TAG_LOGI(AceLogTag::ACE_WEB,
            "Handle autofill event failed! The form contains a login node, but the soruce is incorrect.");
        return false;
    }

    auto eventType = viewDataCommon_->GetEventType();
    if (eventType == OHOS::NWeb::NWebAutofillEvent::FILL) {
        if (isPasswordFill_ && !system::GetBoolParameter(AUTO_FILL_START_POPUP_WINDOW, false)) {
            return RequestAutoFill(GetFocusedType());
        }
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto context = host->GetContext();
        CHECK_NULL_RETURN(context, false);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_RETURN(taskExecutor, false);
        bool fillRet = taskExecutor->PostDelayedTask(
            [weak = WeakClaim(this), nodeInfos = pageNodeInfo_] () {
                auto pattern = weak.Upgrade();
                CHECK_NULL_RETURN(pattern, false);
                return pattern->RequestAutoFill(pattern->GetFocusedType(), nodeInfos);
            },
            TaskExecutor::TaskType::UI, AUTOFILL_DELAY_TIME, "ArkUIWebHandleAutoFillEvent");
        return fillRet;
    }

    if (eventType == OHOS::NWeb::NWebAutofillEvent::SAVE) {
        return RequestAutoSave();
    } else if (eventType == OHOS::NWeb::NWebAutofillEvent::UPDATE) {
        return UpdateAutoFillPopup();
    } else if (eventType == OHOS::NWeb::NWebAutofillEvent::CLOSE) {
        return CloseAutoFillPopup();
    }

    return false;
}

bool WebPattern::HandleAutoFillEvent(const std::shared_ptr<OHOS::NWeb::NWebMessage>& viewDataJson)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "AutoFillEvent");
    viewDataCommon_ = std::make_shared<ViewDataCommon>();
    isPasswordFill_ = false;
    ParseNWebViewDataJson(viewDataJson->GetString(), pageNodeInfo_, viewDataCommon_);
    return HandleAutoFillEvent();
}

bool WebPattern::HandleAutoFillEvent(const std::shared_ptr<OHOS::NWeb::NWebHapValue>& viewDataJson)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "AutoFillEvent");
    viewDataCommon_ = std::make_shared<ViewDataCommon>();
    isPasswordFill_ = false;
    ParseNWebViewDataJson(viewDataJson->GetString(), pageNodeInfo_, viewDataCommon_);
    return HandleAutoFillEvent();
}

bool WebPattern::RequestAutoFill(AceAutoFillType autoFillType)
{
    return RequestAutoFill(autoFillType, pageNodeInfo_);
}

bool WebPattern::RequestAutoFill(AceAutoFillType autoFillType, const std::vector<RefPtr<PageNodeInfoWrap>>& nodeInfos)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "RequestAutoFill");
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto instanceId = context->GetInstanceId();
    CHECK_NULL_RETURN(instanceId, false);
    ContainerScope scope(instanceId);

    auto offset = GetCoordinatePoint().value_or(OffsetF());
    for (auto& nodeInfo : nodeInfos) {
        auto rect = nodeInfo->GetPageNodeRect();
        NG::RectF rectF;
        rectF.SetRect(rect.GetX() + offset.GetX(), rect.GetY()+ offset.GetY(), rect.Width(), rect.Height());
        nodeInfo->SetPageNodeRect(rectF);
    }
    pageNodeInfo_ = nodeInfos;
    requestedWebOffset_ = offset;

    auto container = Container::Current();
    if (container == nullptr) {
        container = Container::GetActive();
    }
    CHECK_NULL_RETURN(container, false);
    isAutoFillClosing_ = false;
    bool isPopup = false;
    return container->RequestAutoFill(host, autoFillType, false, isPopup, autoFillSessionId_, false) ==
           AceAutoFillError::ACE_AUTO_FILL_SUCCESS;
}

std::string WebPattern::GetAllTextInfo() const
{
    CHECK_NULL_RETURN(delegate_, std::string());
    return delegate_->GetAllTextInfo();
}

int WebPattern::GetSelectStartIndex() const
{
    CHECK_NULL_RETURN(delegate_, 0);
    return delegate_->GetSelectStartIndex();
}

int WebPattern::GetSelectEndIndex() const
{
    CHECK_NULL_RETURN(delegate_, 0);
    return delegate_->GetSelectEndIndex();
}

void WebPattern::GetHandleInfo(SelectOverlayInfo& infoHandle)
{
    firstInfoHandle_ = infoHandle.firstHandle.paintRect;
    secondInfoHandle_ = infoHandle.secondHandle.paintRect;
}

RefPtr<TextFieldTheme> WebPattern::GetTheme() const
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, nullptr);
    auto context = tmpHost->GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    return context->GetTheme<TextFieldTheme>(tmpHost->GetThemeScopeId());
}

bool WebPattern::IsShowAIWrite()
{
    auto container = Container::Current();
    if (container && container->IsSceneBoardWindow()) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto textFieldTheme = GetTheme();
    CHECK_NULL_RETURN(textFieldTheme, false);
    auto bundleName = textFieldTheme->GetAIWriteBundleName();
    auto abilityName = textFieldTheme->GetAIWriteAbilityName();
    if (bundleName.empty() || abilityName.empty()) {
        TAG_LOGW(AceLogTag::ACE_WEB, "Failed to obtain AI write package name!");
        return false;
    }
    aiWriteAdapter_->SetBundleName(bundleName);
    aiWriteAdapter_->SetAbilityName(abilityName);
    auto isAISupport = textFieldTheme->GetAIWriteIsSupport() == "true";
    TAG_LOGI(AceLogTag::ACE_WEB, "Whether the device supports AI write: %{public}d, nodeId: %{public}d", isAISupport,
        host->GetId());
    return isAISupport;
}

void WebPattern::HandleOnAIWrite()
{
    AIWriteInfo info;
    GetAIWriteInfo(info);
    CloseSelectOverlay();
    CloseKeyboard();
    auto callback = [weak = WeakClaim(this), info](std::vector<uint8_t>& buffer) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleAIWriteResult(info.selectStart, info.selectEnd, buffer);
        auto aiWriteAdapter = pattern->aiWriteAdapter_;
        CHECK_NULL_VOID(aiWriteAdapter);
        aiWriteAdapter->CloseModalUIExtension();
    };

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    aiWriteAdapter_->SetPipelineContext(pipeline);
    aiWriteAdapter_->ShowModalUIExtension(info, callback);
}

void WebPattern::FormatIndex(int32_t& startIndex, int32_t& endIndex)
{
    startIndex = std::min(startIndex, endIndex);
    endIndex = std::max(startIndex, endIndex);
    startIndex = std::clamp(startIndex, 0, static_cast<int32_t>(content_.length()));
    endIndex = std::clamp(endIndex, 0, static_cast<int32_t>(content_.length()));
}

std::u16string WebPattern::GetSelectedValue(int32_t startIndex, int32_t endIndex)
{
    auto allText = GetAllTextInfo();
    content_ = UtfUtils::Str8ToStr16(allText);
    FormatIndex(startIndex, endIndex);
    startIndex = std::clamp(startIndex, 0, static_cast<int32_t>(content_.length()));
    auto selectedValue = content_.substr(startIndex, endIndex - startIndex);
    if (selectedValue.empty()) {
        selectedValue = TextEmojiProcessor::SubU16string(startIndex, endIndex - startIndex, content_);
    }
    return selectedValue;
}

void WebPattern::GetAIWriteInfo(AIWriteInfo& info)
{
    info.firstHandle = firstInfoHandle_.ToString();
    info.secondHandle = secondInfoHandle_.ToString();
    info.selectStart = GetSelectStartIndex();
    info.selectEnd = GetSelectEndIndex();

    // serialize the selected text
    auto selectContent = GetSelectInfo();
    std::u16string selectContentAllValue = UtfUtils::Str8ToStr16(selectContent);
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(selectContentAllValue);
    spanString->EncodeTlv(info.selectBuffer);
    info.selectLength = static_cast<int32_t>(aiWriteAdapter_->GetSelectLengthOnlyText(spanString->GetU16string()));

    // serialize the sentenced-level text
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto contentAll = UtfUtils::Str8ToStr16(GetAllTextInfo());
    auto sentenceStart = 0;
    auto sentenceEnd = static_cast<int32_t>(contentAll.length());
    TAG_LOGD(AceLogTag::ACE_WEB, "Selected range=[%{public}d--%{public}d], content size=%{public}zu", info.selectStart,
        info.selectEnd, spanString->GetString().size());
    for (int32_t i = info.selectStart; i >= 0; --i) {
        if (aiWriteAdapter_->IsSentenceBoundary(contentAll[i])) {
            sentenceStart = i + 1;
            break;
        }
    }
    for (int32_t i = info.selectEnd; i < info.selectLength; i++) {
        if (aiWriteAdapter_->IsSentenceBoundary(contentAll[i])) {
            sentenceEnd = i;
            break;
        }
    }
    info.start = info.selectStart - sentenceStart;
    info.end = info.selectEnd - sentenceStart;
    auto sentenceContent = GetSelectedValue(sentenceStart, sentenceEnd);
    spanString = AceType::MakeRefPtr<SpanString>(sentenceContent);
    spanString->EncodeTlv(info.sentenceBuffer);
    TAG_LOGD(AceLogTag::ACE_WEB, "Sentence range=[%{public}d--%{public}d], content size=%{public}zu", sentenceStart,
        sentenceEnd, spanString->GetString().size());
    info.componentType = host->GetTag();
}

void WebPattern::HandleAIWriteResult(int32_t start, int32_t end, std::vector<uint8_t>& buffer)
{
    return;
}

bool WebPattern::RequestAutoSave()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "RequestAutoSave");
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto instanceId = context->GetInstanceId();
    CHECK_NULL_RETURN(instanceId, false);
    ContainerScope scope(instanceId);
    auto container = Container::Current();
    if (container == nullptr) {
        container = Container::GetActive();
    }
    CHECK_NULL_RETURN(container, false);
    return container->RequestAutoSave(host, nullptr, nullptr, false);
}

bool WebPattern::UpdateAutoFillPopup()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "UpdateAutoFillPopup");
    if (isAutoFillClosing_) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto instanceId = context->GetInstanceId();
    CHECK_NULL_RETURN(instanceId, false);
    ContainerScope scope(instanceId);
    auto container = Container::Current();
    if (container == nullptr) {
        container = Container::GetActive();
    }
    CHECK_NULL_RETURN(container, false);
    return container->UpdatePopupUIExtension(host, autoFillSessionId_, false);
}

bool WebPattern::CloseAutoFillPopup()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "CloseAutoFillPopup");
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto instanceId = context->GetInstanceId();
    CHECK_NULL_RETURN(instanceId, false);
    ContainerScope scope(instanceId);
    auto container = Container::Current();
    if (container == nullptr) {
        container = Container::GetActive();
    }
    CHECK_NULL_RETURN(container, false);
    isAutoFillClosing_ = true;
    return container->ClosePopupUIExtension(autoFillSessionId_);
}


void WebPattern::OnTouchSelectionChanged(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle)
{
    if (!webSelectOverlay_) {
        return;
    }
    webSelectOverlay_->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
}

bool WebPattern::OnCursorChange(
    const OHOS::NWeb::CursorType& cursorType, std::shared_ptr<OHOS::NWeb::NWebCursorInfo> cursorInfo)
{
    auto [type, info] = GetAndUpdateCursorStyleInfo(cursorType, cursorInfo);
    if (mouseEventDeviceId_ == RESERVED_DEVICEID1 || mouseEventDeviceId_ == RESERVED_DEVICEID2) {
        TAG_LOGD(AceLogTag::ACE_WEB, "OnCursorChange this device id is reserved.");
        return false;
    }
    if (isHoverExit_) {
        TAG_LOGD(AceLogTag::ACE_WEB, "OnCursorChange reciving unexpected hide command");
        return false;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto windowId = pipeline->GetWindowId();
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    int32_t curPointerStyle = 0;
    if (mouseStyle->GetPointerStyle(windowId, curPointerStyle) == -1) {
        return false;
    }

    if ((type == OHOS::NWeb::CursorType::CT_CONTEXTMENU) || (type == OHOS::NWeb::CursorType::CT_ALIAS)) {
        UpdateLocalCursorStyle(windowId, type);
    } else if (type == OHOS::NWeb::CursorType::CT_CUSTOM) {
        UpdateCustomCursor(windowId, info);
    } else {
        MouseFormat pointStyle = MouseFormat::DEFAULT;
        int64_t idx = BinarySearchFindIndex(g_cursorTypeMap, ArraySize(g_cursorTypeMap), type);
        if (idx >= 0) {
            pointStyle = g_cursorTypeMap[idx].value;
        }
        mouseStyle->SetPointerVisible(pointStyle);
        if (static_cast<int32_t>(pointStyle) != curPointerStyle) {
            mouseStyle->SetPointerStyle(windowId, pointStyle);
        }
    }
    return true;
}

CursorStyleInfo WebPattern::GetAndUpdateCursorStyleInfo(
    const OHOS::NWeb::CursorType& cursorType, std::shared_ptr<OHOS::NWeb::NWebCursorInfo> cursorInfo)
{
    auto type = cursorType;
    auto info = cursorInfo;
    if (type == OHOS::NWeb::CursorType::CT_LOCK) {
        type = OHOS::NWeb::CursorType::CT_NONE;
        isMouseLocked_ = true;
    } else if (type == OHOS::NWeb::CursorType::CT_UNLOCK) {
        type = cursorType_;
        info = nweb_cursorInfo_;
        isMouseLocked_ = false;
    } else {
        if (cursorType_ != type) {
            TAG_LOGI(AceLogTag::ACE_WEB, "OnCursorChange type: %{public}d isHoverExit: %{public}d", type, isHoverExit_);
            cursorType_ = type;
        }
        nweb_cursorInfo_.reset();
        if (type == OHOS::NWeb::CursorType::CT_CUSTOM) {
            nweb_cursorInfo_ = info;
        }
    }
    return std::make_tuple(type, info);
}

void WebPattern::UpdateLocalCursorStyle(int32_t windowId, const OHOS::NWeb::CursorType& type)
{
    std::shared_ptr<Media::PixelMap> pixelMap;
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    if (type == NWeb::CursorType::CT_CONTEXTMENU) {
        MouseFormat pointStyle = MouseFormat::CONTEXT_MENU;
        pixelMap = CreatePixelMapFromString(IMAGE_POINTER_CONTEXT_MENU_PATH);
        mouseStyle->SetMouseIcon(windowId, pointStyle, pixelMap);
    } else if (type == NWeb::CursorType::CT_ALIAS) {
        MouseFormat pointStyle = MouseFormat::ALIAS;
        pixelMap = CreatePixelMapFromString(IMAGE_POINTER_ALIAS_PATH);
        mouseStyle->SetMouseIcon(windowId, pointStyle, pixelMap);
    }
}

std::string WebPattern::GetPixelMapName(std::shared_ptr<Media::PixelMap> pixelMap, std::string featureName)
{
    if (!pixelMap) {
        TAG_LOGE(AceLogTag::ACE_WEB, "GetPixelMapName error, PixelMap is null");
        return "undefined_";
    }

    std::string memNameStr = "web-" + std::to_string(pixelMap->GetWidth()) + "x" +
                             std::to_string(pixelMap->GetHeight()) + "-" + featureName + "-" +
                             GetInspectorId();
    return memNameStr;
}

void WebPattern::UpdateCustomCursor(int32_t windowId, std::shared_ptr<OHOS::NWeb::NWebCursorInfo> info)
{
    int32_t x = 0;
    int32_t y = 0;
    int32_t width = 0;
    int32_t height = 0;
    uint8_t *buff = nullptr;
    if (info) {
        x = info->GetX();
        y = info->GetY();
        buff = info->GetBuff();
        width = info->GetWidth();
        height = info->GetHeight();
    }
    Media::InitializationOptions opt;
    opt.size.width = width;
    opt.size.height = height;
    opt.editable = true;
    auto pixelMap = Media::PixelMap::Create(opt);
    CHECK_NULL_VOID(pixelMap);
    uint64_t bufferSize = static_cast<uint64_t>(width * height * IMAGE_POINTER_CUSTOM_CHANNEL);
    uint32_t status = pixelMap->WritePixels(static_cast<const uint8_t*>(buff), bufferSize);
    if (status != 0) {
        TAG_LOGE(AceLogTag::ACE_WEB, "write pixel map failed %{public}u", status);
        return;
    }
    std::shared_ptr<Media::PixelMap> cursorPixelMap(pixelMap.release());
    CHECK_NULL_VOID(cursorPixelMap);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    float dipScale = pipeline->GetDipScale();
    cursorPixelMap->scale(dipScale, dipScale);

    auto mouseStyle = MouseStyle::CreateMouseStyle();
    CHECK_NULL_VOID(mouseStyle);
    uint32_t res = cursorPixelMap->SetMemoryName(GetPixelMapName(cursorPixelMap, "cursor"));
    TAG_LOGI(AceLogTag::ACE_WEB, "SetMemoryName result is %{public}d", res);
    mouseStyle->SetCustomCursor(windowId, x * dipScale, y * dipScale, cursorPixelMap);
}

std::shared_ptr<OHOS::Media::PixelMap> WebPattern::CreatePixelMapFromString(const std::string& filePath)
{
    OHOS::Media::SourceOptions opts;
    opts.formatHint = "image/svg+xml";
    uint32_t errCode = 0;
    auto imageSource = OHOS::Media::ImageSource::CreateImageSource(filePath, opts, errCode);
    CHECK_NULL_RETURN(imageSource, nullptr);
    std::set<std::string> formats;
    errCode = imageSource->GetSupportedFormats(formats);
    Media::DecodeOptions decodeOpts;
    std::shared_ptr<OHOS::Media::PixelMap> pixelMap = imageSource->CreatePixelMap(decodeOpts, errCode);
    CHECK_NULL_RETURN(pixelMap, nullptr);

    return pixelMap;
}

void WebPattern::OnTooltip(const std::string& tooltip)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    tooltipTimestamp_ = GetSysTimestamp();
    auto tooltipTimestamp = tooltipTimestamp_;

    if (tooltipId_ != -1) {
        overlayManager->RemoveIndexerPopupById(tooltipId_);
        tooltipId_ = -1;
    }
    auto tooltipText = tooltip;
    OHOS::Ace::StringUtils::TrimStrLeadingAndTrailing(tooltipText);
    if (tooltipText == "" || mouseHoveredX_ < 0 || mouseHoveredY_ < 0) {
        return;
    }
    ShowTooltip(tooltipText, tooltipTimestamp);
}

void WebPattern::OnPopupSize(int32_t x, int32_t y, int32_t width, int32_t height)
{
    CHECK_NULL_VOID(renderContextForPopupSurface_);
    TAG_LOGI(AceLogTag::ACE_WEB,
        "Web %{public}d popup window resize to (x:%{public}d, y:%{public}d, width:%{public}d, height:%{public}d)",
        GetWebId(), x, y, width, height);
    renderContextForPopupSurface_->SetBounds(x, y, width, height);
}

void WebPattern::OnPopupShow(bool show)
{
    if (!show) {
        CHECK_NULL_VOID(renderContextForPopupSurface_);
        renderContextForPopupSurface_->SetBounds(0, 0, 0, 0);
    }

    TAG_LOGI(AceLogTag::ACE_WEB, "Web %{public}d show popup window %{public}d", GetWebId(), show);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RequestFrame();
}

void WebPattern::GetVisibleRectToWeb(int& visibleX, int& visibleY, int& visibleWidth, int& visibleHeight)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RectF visibleRect;
    RectF visibleInnerRect;
    RectF frameRect;
    host->GetVisibleRectWithClip(visibleRect, visibleInnerRect, frameRect);
    auto offset = GetCoordinatePoint().value_or(OffsetF());
    visibleX = visibleInnerRect.GetX() - offset.GetX();
    visibleY = visibleInnerRect.GetY() - offset.GetY();
    visibleWidth = visibleInnerRect.Width();
    visibleHeight = visibleInnerRect.Height();
}

void WebPattern::RestoreRenderFit()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::RestoreRenderFit, webId: %{public}d, isRotation: %{public}d",
        GetWebId(), isRotating_);
    if (isRotating_) {
        return;
    }
    if (renderContextForSurface_) {
        renderContextForSurface_->SetRenderFit(RenderFit::TOP_LEFT);
    }
}

void WebPattern::AttachCustomKeyboard()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebCustomKeyboard AttachCustomKeyboard enter");
    CHECK_NULL_VOID(customKeyboardBuilder_);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->SetCustomKeyboardOption(true);
    overlayManager->BindKeyboard(customKeyboardBuilder_, frameNode->GetId());
    keyboardOverlay_ = overlayManager;
    keyboardOverlay_->AvoidCustomKeyboard(frameNode->GetId(), 0);
    isUsingCustomKeyboardAvoid_ = true;
    TAG_LOGI(AceLogTag::ACE_WEB, "WebCustomKeyboard AttachCustomKeyboard end");
}

void WebPattern::CloseCustomKeyboard()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebCustomKeyboard CloseCustomKeyboard enter");
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(keyboardOverlay_);
    keyboardOverlay_->CloseKeyboard(frameNode->GetId());
    isUsingCustomKeyboardAvoid_ = false;
    TAG_LOGI(AceLogTag::ACE_WEB, "WebCustomKeyboard CloseCustomKeyboard end");
    MenuAvoidKeyboard(true);
}

void WebPattern::HandleShowTooltip(const std::string& tooltip, int64_t tooltipTimestamp)
{
    if ((tooltipTimestamp_ != tooltipTimestamp) || (tooltip == "")) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    if (tooltipId_ == -1) {
        tooltipId_ = ElementRegister::GetInstance()->MakeUniqueId();
    }
    auto tooltipNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, tooltipId_,
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_VOID(tooltipNode);

    auto textRenderContext = tooltipNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    auto textLayoutProperty = tooltipNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(tooltip);

    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(TOOLTIP_BORDER_WIDTH);
    textLayoutProperty->UpdateBorderWidth(borderWidth);
    textLayoutProperty->UpdateFontSize(TOOLTIP_FONT_SIZE);
    textLayoutProperty->UpdatePadding({ CalcLength(TOOLTIP_PADDING),
        CalcLength(TOOLTIP_PADDING), CalcLength(TOOLTIP_PADDING), CalcLength(TOOLTIP_PADDING) });
    textLayoutProperty->UpdateCalcMaxSize(CalcSize(CalcLength(Dimension(
        pipeline->GetCurrentRootWidth() * TOOLTIP_MAX_PORTION)), std::nullopt));
    UpdateTooltipContentColor(tooltipNode);

    OffsetF tooltipOffset;
    CalculateTooltipOffset(tooltipNode, tooltipOffset);
    textRenderContext->UpdatePosition(OffsetT<Dimension>(Dimension(tooltipOffset.GetX()),
        Dimension(tooltipOffset.GetY())));
 
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(TOOLTIP_BORDER_RADIUS);
    textRenderContext->SetBorderRadius(borderRadius);

    Shadow shadow;
    if (GetShadowFromTheme(ShadowStyle::OuterDefaultSM, shadow)) {
        textRenderContext->UpdateBackShadow(shadow);
    }

    BorderColorProperty borderColor;
    borderColor.SetColor(Color::BLACK);
    textRenderContext->UpdateBorderColor(borderColor);
    overlayManager->ShowIndexerPopup(tooltipId_, tooltipNode);
}
 
bool WebPattern::GetShadowFromTheme(ShadowStyle shadowStyle, Shadow& shadow)
{
    if (shadowStyle == ShadowStyle::None) {
        return true;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto colorMode = pipelineContext->GetColorMode();
    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    CHECK_NULL_RETURN(shadowTheme, false);
    shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    return true;
}


void WebPattern::UpdateTooltipContentColor(const RefPtr<FrameNode>& textNode)
{
    CHECK_NULL_VOID(textNode);
    auto textRenderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    if (Color::BLACK == GetSystemColor()) {
        textLayoutProperty->UpdateTextColor(Color::WHITE);
        textRenderContext->UpdateBackgroundColor(Color::BLACK);
    } else {
        textLayoutProperty->UpdateTextColor(Color::BLACK);
        textRenderContext->UpdateBackgroundColor(Color::WHITE);
    }
}

void WebPattern::ShowTooltip(const std::string& tooltip, int64_t tooltipTimestamp)
{
    auto tooltipTask = [weak = WeakClaim(this), tooltip, tooltipTimestamp]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleShowTooltip(tooltip, tooltipTimestamp);
    };

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    taskExecutor->PostDelayedTask(tooltipTask, TaskExecutor::TaskType::UI, TOOLTIP_DELAY_MS, "ArkUIWebShowTooltip");
}

void WebPattern::CalculateTooltipOffset(RefPtr<FrameNode>& tooltipNode, OffsetF& tooltipOffset)
{
    auto textLayoutWrapper = tooltipNode->CreateLayoutWrapper(true);
    CHECK_NULL_VOID(textLayoutWrapper);
    textLayoutWrapper->Measure(std::nullopt);
    auto textGeometryNode = textLayoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(textGeometryNode);
    auto textWidth = textGeometryNode->GetMarginFrameSize().Width();
    auto textHeight = textGeometryNode->GetMarginFrameSize().Height();

    auto offset = GetCoordinatePoint().value_or(OffsetF());
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto rootNode = AceType::DynamicCast<FrameNode>(overlayManager->GetRootNode().Upgrade());
    CHECK_NULL_VOID(rootNode);
    auto root = rootNode->GetTransformRectRelativeToWindow();

    auto offsetX = offset.GetX() - root.GetX() + mouseHoveredX_ + TOOLTIP_MARGIN;
    auto offsetY = offset.GetY() - root.GetY() + mouseHoveredY_ + TOOLTIP_MARGIN;

    ScopedLayout scope(Referenced::RawPtr(pipeline));
    if (GreatNotEqual(offsetX + textWidth, root.Width())) {
        offsetX = root.Width() - textWidth;
    }
    if (GreatNotEqual(offsetY + textHeight, root.Height())) {
        offsetY = root.Height() - textHeight;
    }
    tooltipOffset.SetX(offsetX);
    tooltipOffset.SetY(offsetY);
    TAG_LOGI(AceLogTag::ACE_WEB,
        "CalculateTooltipOffset [Tooltip] width: %{public}f height: %{public}f offset:(%{public}f, %{public}f)"
        " [Web] width: %{public}f height: %{public}f offset:(%{public}f, %{public}f)",
        textWidth, textHeight, offsetX, offsetY, drawSize_.Width(), drawSize_.Height(), offset.GetX(), offset.GetY());
}

void WebPattern::OnSelectPopupMenu(std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam> params,
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback> callback)
{
    CHECK_NULL_VOID(params);
    CHECK_NULL_VOID(callback);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    auto id = host->GetId();
    std::vector<SelectParam> selectParam;
    for (auto& item : params->GetMenuItems()) {
        selectParam.push_back({
            item->GetLabel(), ""
        });
    }
    bool autoWrapFlag = true;
    auto menu = MenuView::Create(selectParam, id, host->GetTag(), autoWrapFlag);
    CHECK_NULL_VOID(menu);
    auto menuWrapperPattern = menu->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto destructor = [weak = WeakClaim(this), id]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto pipeline = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto manager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(manager);
        pattern->SetSelectPopupMenuShowing(false);
        manager->DeleteMenu(id);
    };
    eventHub->SetOnDisappear(destructor);

    WebPattern::InitSelectPopupMenuView(menu, callback, params, context->GetDipScale());
    menuWrapperPattern->RegisterMenuDisappearCallback([weak = WeakClaim(this), callback]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        callback->Cancel();
        pattern->SetSelectPopupMenuShowing(false);
    });
    auto offset = GetSelectPopupPostion(params->GetSelectMenuBound());
    TAG_LOGI(AceLogTag::ACE_WEB, "OnSelectPopupMenu offset:(%{public}f, %{public}f)", offset.GetX(), offset.GetY());
    selectPopupMenuShowing_ = true;
    overlayManager->ShowMenu(id, offset, menu);
}

void WebPattern::NotifyForNextTouchEvent()
{
    CHECK_NULL_VOID(delegate_);
    delegate_->NotifyForNextTouchEvent();
}

void WebPattern::InitTouchEventListener()
{
    TAG_LOGD(AceLogTag::ACE_WEB, "WebPattern::InitTouchEventListener");
    if (touchEventListener_) {
        return;
    }
    touchEventListener_ = std::make_shared<TouchEventListener>();
    touchEventListener_->SetPatternToListener(AceType::WeakClaim(this));

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    context->RegisterTouchEventListener(touchEventListener_);
}

void WebPattern::UninitTouchEventListener()
{
    TAG_LOGD(AceLogTag::ACE_WEB, "WebPattern::UninitTouchEventListener");
    touchEventListener_ = nullptr;

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    context->UnregisterTouchEventListener(AceType::WeakClaim(this));
}

void WebPattern::OnDateTimeChooserPopup(std::shared_ptr<OHOS::NWeb::NWebDateTimeChooser> chooser,
    const std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>>& suggestions,
    std::shared_ptr<NWeb::NWebDateTimeChooserCallback> callback)
{
    if (!chooser) {
        return;
    }

    bool result = false;
    if (suggestions.size() != 0) {
        result = ShowDateTimeSuggestionDialog(chooser, suggestions, callback);
    } else if (chooser->GetType() == NWeb::DTC_TIME) {
        result = ShowTimeDialog(chooser, suggestions, callback);
    } else {
        result = ShowDateTimeDialog(chooser, suggestions, callback);
    }
    if (!result) {
        callback->Continue(false, OHOS::NWeb::DateTime());
    }
}

DialogProperties WebPattern::GetDialogProperties(const RefPtr<DialogTheme>& theme)
{
    DialogProperties properties;
    if (GetWebInfoType() == WebInfoType::TYPE_MOBILE) {
        properties.alignment = DialogAlignment::BOTTOM;
    } else {
        properties.alignment = DialogAlignment::CENTER;
    }
    properties.customStyle = false;
    properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
    return properties;
}

bool WebPattern::ShowDateTimeDialog(std::shared_ptr<OHOS::NWeb::NWebDateTimeChooser> chooser,
    const std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>>& suggestions,
    std::shared_ptr<NWeb::NWebDateTimeChooserCallback> callback)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipelineContext, false);
    auto executor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_RETURN(executor, false);
    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    CHECK_NULL_RETURN(overlayManager, false);
    auto theme = pipelineContext->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(theme, false);
    NG::DatePickerSettingData settingData;
    settingData.isLunar = false;
    settingData.showTime = chooser->GetType() == NWeb::DTC_DATETIME_LOCAL;
    settingData.useMilitary = true;
    DialogProperties properties = GetDialogProperties(theme);
    std::map<std::string, PickerDate> datePickerProperty;
    std::map<std::string, PickerTime> timePickerProperty;
    OHOS::NWeb::DateTime minimum = chooser->GetMinimum();
    OHOS::NWeb::DateTime maximum = chooser->GetMaximum();
    OHOS::NWeb::DateTime dialogValue = chooser->GetDialogValue();
    settingData.datePickerProperty["start"] = PickerDate(minimum.year, minimum.month + 1, minimum.day);
    settingData.datePickerProperty["end"] = PickerDate(maximum.year, maximum.month + 1, maximum.day);
    if (chooser->GetHasSelected()) {
        int32_t day = (dialogValue.day == 0) ? 1 : dialogValue.day;
        settingData.datePickerProperty["selected"] = PickerDate(dialogValue.year, dialogValue.month + 1, day);
    }
    std::map<std::string, NG::DialogEvent> dialogEvent;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogEvent["acceptId"] = [callback](const std::string& info) {
        OHOS::NWeb::DateTime result;
        bool success = ParseDateTimeJson(info, result);
        callback->Continue(success, result);
    };
    dialogCancelEvent["cancelId"] =
        [callback](const GestureEvent&) { callback->Continue(false, OHOS::NWeb::DateTime()); };
    overlayManager->RegisterOnHideDialog([callback] { callback->Continue(false, OHOS::NWeb::DateTime()); });
    executor->PostTask(
        [properties, settingData, dialogEvent, dialogCancelEvent, weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowDateDialog(properties, settingData, dialogEvent, dialogCancelEvent);
        },
        TaskExecutor::TaskType::UI, "ArkUIWebShowDateDialog");
    return true;
}

bool WebPattern::ShowTimeDialog(std::shared_ptr<OHOS::NWeb::NWebDateTimeChooser> chooser,
    const std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>>& suggestions,
    std::shared_ptr<NWeb::NWebDateTimeChooserCallback> callback)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipelineContext, false);
    auto executor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_RETURN(executor, false);
    auto theme = pipelineContext->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    CHECK_NULL_RETURN(overlayManager, false);
    NG::TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = true;
    DialogProperties properties = GetDialogProperties(theme);
    std::map<std::string, PickerTime> timePickerProperty;
    OHOS::NWeb::DateTime minimum = chooser->GetMinimum();
    OHOS::NWeb::DateTime maximum = chooser->GetMaximum();
    OHOS::NWeb::DateTime dialogValue = chooser->GetDialogValue();
    timePickerProperty["start"] = PickerTime(minimum.hour, minimum.minute, minimum.second);
    timePickerProperty["selected"] = PickerTime(maximum.hour, maximum.minute, maximum.second);
    if (chooser->GetHasSelected()) {
        timePickerProperty["selected"] = PickerTime(dialogValue.hour, dialogValue.minute, dialogValue.second);
    } else {
        auto timeOfNow = GetTimeOfNow();
        timePickerProperty["selected"] =
            PickerTime(timeOfNow.hour24_, timeOfNow.minute_, timeOfNow.second_);
    }
    std::map<std::string, NG::DialogEvent> dialogEvent;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogEvent["acceptId"] = [callback](const std::string& info) {
        OHOS::NWeb::DateTime result;
        bool success = ParseDateTimeJson(info, result);
        callback->Continue(success, result);
    };
    dialogCancelEvent["cancelId"] =
        [callback](const GestureEvent&) { callback->Continue(false, OHOS::NWeb::DateTime()); };
    overlayManager->RegisterOnHideDialog([callback] { callback->Continue(false, OHOS::NWeb::DateTime()); });
    executor->PostTask(
        [properties, settingData, timePickerProperty, dialogEvent, dialogCancelEvent,
            weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowTimeDialog(properties, settingData, timePickerProperty, dialogEvent, dialogCancelEvent);
        },
        TaskExecutor::TaskType::UI, "ArkUIWebShowTimeDialog");
    return true;
}

bool WebPattern::ShowDateTimeSuggestionDialog(std::shared_ptr<OHOS::NWeb::NWebDateTimeChooser> chooser,
    const std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>>& suggestions,
    std::shared_ptr<NWeb::NWebDateTimeChooserCallback> callback)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipelineContext, false);
    auto executor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_RETURN(executor, false);
    auto theme = pipelineContext->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    CHECK_NULL_RETURN(overlayManager, false);
    NG::TextPickerSettingData settingData;
    if (memset_s(&settingData, sizeof(NG::TextPickerSettingData), 0, sizeof(NG::TextPickerSettingData)) != EOK) {
        return false;
    }
    std::map<std::string, OHOS::NWeb::DateTime> suggestionMap;
    for (size_t i = 0; i < suggestions.size(); i++) {
        settingData.rangeVector.push_back({ "", suggestions[i]->GetLocalizedValue() });
        settingData.values.push_back(suggestions[i]->GetLocalizedValue());
        suggestionMap.emplace(std::make_pair(suggestions[i]->GetLocalizedValue(), suggestions[i]->GetValue()));
    }
    settingData.columnKind = NG::TEXT;
    settingData.selected = chooser->GetSuggestionIndex();
    DialogProperties properties = GetDialogProperties(theme);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogEvent["acceptId"] = [suggestionMap, callback](const std::string& info) {
        std::string value = ParseTextJsonValue(info);
        if (suggestionMap.find(value) != suggestionMap.end()) {
            callback->Continue(true, suggestionMap.at(value));
        } else {
            callback->Continue(false, OHOS::NWeb::DateTime());
        }
    };
    dialogCancelEvent["cancelId"] =
        [callback](const GestureEvent&) { callback->Continue(false, OHOS::NWeb::DateTime()); };
    overlayManager->RegisterOnHideDialog([callback] { callback->Continue(false, OHOS::NWeb::DateTime()); });
    executor->PostTask(
        [properties, settingData, dialogEvent, dialogCancelEvent,
            weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowTextDialog(properties, settingData, dialogEvent, dialogCancelEvent);
        },
        TaskExecutor::TaskType::UI, "ArkUIWebShowTextDialog");
    return true;
}

void WebPattern::OnDateTimeChooserClose() {}

void WebPattern::InitSelectPopupMenuViewOption(const std::vector<RefPtr<FrameNode>>& options,
    const std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback>& callback,
    const std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam>& params,
    const double& dipScale)
{
    int32_t optionIndex = -1;
    int32_t width = params->GetSelectMenuBound() ? params->GetSelectMenuBound()->GetWidth() : 0;
    auto items = params->GetMenuItems();
    int32_t selectedIndex = params->GetSelectedItem();
    TAG_LOGD(AceLogTag::ACE_WEB, "InitSelectPopupMenuViewOption selectedIndex:%{public}d", selectedIndex);

    for (auto &&option : options) {
        optionIndex++;
        CHECK_NULL_VOID(option);
        auto optionPattern = option->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(optionPattern);
        auto optionPaintProperty = option->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(optionPaintProperty);
        optionPaintProperty->SetIdealWidthForWeb(width - OPTION_MARGIN.ConvertToPx());
        optionPattern->SetFontSize(Dimension(params->GetItemFontSize() * dipScale));
        if (selectedIndex == optionIndex) {
            optionPattern->SetFontColor(SELECTED_OPTION_FONT_COLOR);
            optionPattern->SetBgColor(SELECTED_OPTION_BACKGROUND_COLOR);
            optionPattern->UpdateNextNodeDivider(false);
            optionPaintProperty->UpdateNeedDivider(false);
        }
        auto hub = option->GetEventHub<MenuItemEventHub>();
        CHECK_NULL_VOID(hub);
        if (optionIndex >= 0 && static_cast<uint32_t>(optionIndex) < items.size()) {
            hub->SetEnabled(items[optionIndex]->GetIsEnabled());
            auto focusHub = option->GetFocusHub();
            if (focusHub) {
                focusHub->SetEnabled(items[optionIndex]->GetIsEnabled());
            }
        }
        auto selectCallback = [callback](int32_t index) {
            std::vector<int32_t> indices { static_cast<int32_t>(index) };
            callback->Continue(indices);
        };
        hub->SetOnSelect(std::move(selectCallback));
        option->MarkModifyDone();
    }
}

void WebPattern::InitSelectPopupMenuView(RefPtr<FrameNode>& menuWrapper,
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback> callback,
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam> params,
    const double& dipScale)
{
    auto menu = AceType::DynamicCast<FrameNode>(menuWrapper->GetChildAtIndex(0));
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);

    InitSelectPopupMenuViewOption(menuPattern->GetOptions(), callback, params, dipScale);
}

OffsetF WebPattern::GetSelectPopupPostion(std::shared_ptr<OHOS::NWeb::NWebSelectMenuBound> bound)
{
    auto offset = GetCoordinatePoint().value_or(OffsetF());
    if (bound) {
        offset.AddX(bound->GetX());
        offset.AddY(bound->GetY() + bound->GetHeight());
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        offset.AddX(-CALIBERATE_X.ConvertToPx());
    }
    return offset;
}

void WebPattern::UpdateLocale()
{
    CHECK_NULL_VOID(delegate_);
    delegate_->UpdateLocale();
}

void WebPattern::OnWindowShow()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnWindowShow WebId : %{public}d", GetWebId());
    CHECK_NULL_VOID(delegate_);
    delegate_->OnRenderToForeground();
    delegate_->OnOnlineRenderToForeground();

    if (isWindowShow_ || !isVisible_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    componentVisibility_ = layoutProperty->GetVisibility().value_or(VisibleType::GONE);
    // When the visibility of web component is invisible, the window notification is not processed
    if (componentVisibility_ == VisibleType::INVISIBLE) {
        ACE_SCOPED_TRACE("WebPattern::OnWindowShow visibility of web component is invisible, WebId %d", GetWebId());
        return;
    }
    delegate_->ShowWebView();
    SetActiveStatusInner(true);
    isWindowShow_ = true;
}

void WebPattern::OnWindowHide()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnWindowHide WebId : %{public}d", GetWebId());
    CHECK_NULL_VOID(delegate_);
    delegate_->OnRenderToBackground();

    if (!isWindowShow_) {
        return;
    }

    CHECK_NULL_VOID(delegate_);
    SetActiveStatusInner(false);
    delegate_->HideWebView();
    CloseContextSelectionMenu();
    needOnFocus_ = false;
    isWindowShow_ = false;
}

void WebPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    if (contextSelectOverlay_ && contextSelectOverlay_->SelectOverlayIsOn()) {
        contextSelectOverlay_->UpdateMenuOnWindowSizeChanged(type);
    }
    CHECK_NULL_VOID(delegate_);
    TAG_LOGD(AceLogTag::ACE_WEB, "WindowSizeChangeReason type: %{public}d ", type);
    if (type == WindowSizeChangeReason::MAXIMIZE) {
        WindowMaximize();
        return;
    }
    AdjustRotationRenderFit(type);
    bool isSmoothDragResizeEnabled = delegate_->GetIsSmoothDragResizeEnabled();
    if (!isSmoothDragResizeEnabled) {
        return;
    }
    dragResizeTimerFlag_ = false;
    auto dragTime = std::chrono::high_resolution_clock::now().time_since_epoch();
    lastDragTime_ = std::chrono::duration_cast<std::chrono::milliseconds>(dragTime).count();
    if (type == WindowSizeChangeReason::DRAG_START || type == WindowSizeChangeReason::DRAG ||
        type == WindowSizeChangeReason::SPLIT_DRAG_START || type == WindowSizeChangeReason::SPLIT_DRAG) {
        if (dragResizeTimerCount_ == 0) {
            DragResizeNoMoveTimer();
        }
        dragWindowFlag_ = true;
        delegate_->SetDragResizeStartFlag(true);
        WindowDrag(width, height);
    }
    if (type == WindowSizeChangeReason::DRAG_END || type == WindowSizeChangeReason::SPLIT_DRAG_END) {
        dragResizeTimerFlag_ = true;
        dragResizeTimerCount_ = 0;
        delegate_->SetDragResizeStartFlag(false);
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        auto offset = Offset(GetCoordinatePoint()->GetX(), GetCoordinatePoint()->GetY());
        delegate_->SetBoundsOrResize(drawSize_, offset, false);
        delegate_->ResizeVisibleViewport(visibleViewportSize_, false);
        dragWindowFlag_ = false;
        lastHeight_ = 0;
        lastWidth_ = 0;
    }
}

void WebPattern::DragResizeNoMoveTimer()
{
    if (dragResizeTimerFlag_) {
        dragResizeTimerCount_ = 0;
        return;
    }
    dragResizeTimerCount_++;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto time = std::chrono::high_resolution_clock::now().time_since_epoch();
    int nowTime = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
    int diff = nowTime - lastDragTime_;
    if (diff > DRAG_RESIZE_NO_MOVE_CHECK_TIME) {
        auto offset = Offset(GetCoordinatePoint()->GetX(), GetCoordinatePoint()->GetY());
        delegate_->SetDragResizeStartFlag(false);
        delegate_->SetBoundsOrResize(drawSize_, offset, false);
        delegate_->ResizeVisibleViewport(visibleViewportSize_, false);
    }
    taskExecutor->PostDelayedTask([weak = WeakClaim(this)] () {
        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->DragResizeNoMoveTimer();
        },
        TaskExecutor::TaskType::UI, DRAG_RESIZE_DELAY_TIME, "ArkUIWebDraggingResizeDelay");
}

void WebPattern::WindowDrag(int32_t width, int32_t height)
{
    if (delegate_) {
        if (lastHeight_ == 0 && lastWidth_ == 0) {
            lastHeight_ = height;
            lastWidth_ = width;
        }
        if (!GetPendingSizeStatus() && dragWindowFlag_) {
            int64_t pre_height = height - lastHeight_;
            int64_t pre_width = width - lastWidth_;
            if (pre_width == 0 && pre_height == 0) {
                delegate_->SetDragResizePreSize(pre_height, pre_width);
                return;
            }
            if (pre_height <= CHECK_PRE_SIZE && pre_height > 0) {
                pre_height = 0;
            }
            if (pre_width <= CHECK_PRE_SIZE && pre_width > 0) {
                pre_width = 0;
            }
            lastHeight_ = height;
            lastWidth_ = width;
            if (pre_width == 0 && pre_height == 0) {
                return;
            }
            delegate_->SetDragResizePreSize(pre_height * ADJUST_RATIO, pre_width * ADJUST_RATIO);
        }
    }
}

void WebPattern::WindowMaximize()
{
    if (!SystemProperties::GetWebDebugMaximizeResizeOptimize()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::WindowMaximize not enabled");
        return;
    }
    WebInfoType webInfoType = GetWebInfoType();
    if (webInfoType != WebInfoType::TYPE_2IN1) {
        return;
    }
    if (layoutMode_ != WebLayoutMode::NONE || renderMode_ != RenderMode::ASYNC_RENDER) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::WindowMaximize not support");
        return;
    }
    if (!isAttachedToMainTree_ || !isVisible_) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::WindowMaximize, webId: %{public}d", GetWebId());
    if (renderContextForSurface_) {
        renderContextForSurface_->SetRenderFit(RenderFit::RESIZE_FILL);
    }
    if (delegate_) {
        delegate_->MaximizeResize();
    }
}

void WebPattern::OnCompleteSwapWithNewSize()
{
    if (!isInWindowDrag_ || !isWaiting_)
        return;

    ACE_SCOPED_TRACE("WebPattern::OnCompleteSwapWithNewSize");
    isWaiting_ = false;
}

void WebPattern::OnResizeNotWork()
{
    if (!isInWindowDrag_ || !isWaiting_)
        return;

    ACE_SCOPED_TRACE("WebPattern::OnResizeNotWork");
    isWaiting_ = false;
}

void WebPattern::UpdateOnFocusTextField(bool isFocus)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    isFocus ? textFieldManager->SetOnFocusTextField(WeakClaim(this))
            : textFieldManager->ClearOnFocusTextField(host->GetId());
}

bool WebPattern::OnBackPressed()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    TAG_LOGI(AceLogTag::ACE_WEB, "Web %{public}d receives back press event", host->GetId());
    if (IsVirtualKeyBoardShow()) {
        CloseSelectOverlay();
        SelectCancel();
        TAG_LOGI(AceLogTag::ACE_WEB, "Request close soft keyboard.");
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        CHECK_NULL_RETURN(inputMethod, false);
        inputMethod->HideTextInput();
        inputMethod->Close();
        CHECK_NULL_RETURN(delegate_, true);
        delegate_->CloseCustomKeyboard();
        delegate_->GestureBackBlur();
        return true;
    }
    return false;
}

bool WebPattern::OnBackPressedForFullScreen() const
{
    if (!isFullScreen_) {
        return false;
    }

    TAG_LOGI(AceLogTag::ACE_WEB, "FullScreenBackPressEvent Received");
    CHECK_NULL_RETURN(fullScreenExitHandler_, false);
    auto webFullScreenExitHandler = fullScreenExitHandler_->GetHandler();
    CHECK_NULL_RETURN(webFullScreenExitHandler, false);
    webFullScreenExitHandler->ExitFullScreen();
    return true;
}

void WebPattern::SetFullScreenExitHandler(const std::shared_ptr<FullScreenEnterEvent>& fullScreenExitHandler)
{
    fullScreenExitHandler_ = fullScreenExitHandler;
}

void WebPattern::OnInActive()
{
    TAG_LOGI(AceLogTag::ACE_WEB,
        "WebPattern::OnInActive webId:%{public}d, isActive:%{public}d",
        GetWebId(), isActive_);
    SetActiveStatusInner(false);
}

void WebPattern::OnActive()
{
    TAG_LOGI(AceLogTag::ACE_WEB,
        "WebPattern::OnActive webId:%{public}d, isActive:%{public}d",
        GetWebId(), isActive_);
    UpdateScrollBarWithBorderRadius();
    SetActiveStatusInner(true);
}

void WebPattern::OnVisibleAreaChange(bool isVisible)
{
    bool isDialogNested = IsDialogNested();
    ACE_SCOPED_TRACE("WebPattern::OnVisibleAreaChange, webId: %d, isVisible: %d", GetWebId(), isVisible);
    TAG_LOGI(AceLogTag::ACE_WEB,
        "WebPattern::OnVisibleAreaChange webId:%{public}d, isVisible:%{public}d, old_isVisible:%{public}d, "
        "isVisibleActiveEnable:%{public}d, isDialogNested:%{public}d, isFocus:%{public}d",
        GetWebId(), isVisible, isVisible_, isVisibleActiveEnable_, isDialogNested, isFocus_);
    // pass isVisible value to arkweb directly without any judgment
    if (delegate_) {
        delegate_->SetVisibility(isVisible);
    }

    if (isVisible_ == isVisible) {
        return;
    }

    isVisible_ = isVisible;
    if (!isVisible_) {
        if (webSelectOverlay_) {
            webSelectOverlay_->UpdateSingleHandleVisible(false);
        }
        OnCursorChange(OHOS::NWeb::CursorType::CT_POINTER, nullptr);
        CloseSelectOverlay();
        if (IS_CALLING_FROM_M114() || (webSelectOverlay_ && !webSelectOverlay_->IsSingleHandle())) {
            SelectCancel();
        }
        DestroyAnalyzerOverlay();
        CloseDataDetectorMenu();
        OnTooltip("");
        isDragEndMenuShow_ = false;
        if (isVisibleActiveEnable_ && (!isDialogNested || !isFocus_)) {
            SetActiveStatusInner(false);
        }
    } else {
        if (isVisibleActiveEnable_) {
            SetActiveStatusInner(true);
        }
    }
}

Color WebPattern::GetDefaultBackgroundColor()
{
    auto darkMode = GetDarkModeValue(webData_ ? (WebDarkMode::Auto) : (WebDarkMode::Off));
    if (GetForceDarkAccessValue(false) &&
        (darkMode == WebDarkMode::On || ((darkMode == WebDarkMode::Auto) && (GetSystemColor() == Color::BLACK)))) {
        return Color::BLACK;
    } else {
        return Color::WHITE;
    }
}

void WebPattern::UpdateBackgroundColorRightNow(int32_t color)
{
    Color bkColor = Color(static_cast<uint32_t>(color));
    std::string debugBkgroundColor = GetWebDebugBackGroundColor();
    if (debugBkgroundColor != "none") {
        // debugBkgroundColor : #FFFFFFFF ARGB format
        bkColor = Color::ColorFromString(debugBkgroundColor);
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::UpdateBackgroundColorRightNow, use debug background color," \
            " color=%{public}s, web id = %{public}d", bkColor.ToString().c_str(), GetWebId());
    }

    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::UpdateBackgroundColorRightNow, color=%{public}s, web id = %{public}d",
        bkColor.ToString().c_str(), GetWebId());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(bkColor);
    CHECK_NULL_VOID(renderContextForSurface_);
    renderContextForSurface_->UpdateBackgroundColor(bkColor);
}

Color WebPattern::GetSystemColor() const
{
    Color color = Color::WHITE;
    auto appMgrClient = std::make_shared<AppExecFwk::AppMgrClient>();
    CHECK_NULL_RETURN(appMgrClient, color);
    if (appMgrClient->ConnectAppMgrService()) {
        return color;
    }
    auto systemConfig = OHOS::AppExecFwk::Configuration();
    appMgrClient->GetConfiguration(systemConfig);
    auto colorMode = systemConfig.GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
    if (colorMode == OHOS::AppExecFwk::ConfigurationInner::COLOR_MODE_DARK) {
        return Color::BLACK;
    }
    if (colorMode == OHOS::AppExecFwk::ConfigurationInner::COLOR_MODE_LIGHT) {
        return Color::WHITE;
    }
    TAG_LOGW(AceLogTag::ACE_WEB, "no system color mode is found.");
    return color;
}

void WebPattern::OnNotifyMemoryLevel(int32_t level)
{
    if (!isMemoryLevelEnable_) {
        return;
    }
    CHECK_NULL_VOID(delegate_);
    delegate_->NotifyMemoryLevel(level);
}

int WebPattern::GetWebId()
{
    if (delegate_) {
        return delegate_->GetWebId();
    }
    return -1;
}

ScrollResult WebPattern::HandleScroll(float offset, int32_t source, NestedState state, float velocity)
{
    // If no parent object is specified, the nearest nested scrollable parent is used by default.
    return HandleScroll(GetNestedScrollParent(), offset, source, state);
}

ScrollResult WebPattern::HandleScroll(RefPtr<NestableScrollContainer> parent, float offset,
    int32_t source, NestedState state)
{
    TAG_LOGD(AceLogTag::ACE_WEB,
        "WebPattern::HandleScroll scroll direction: %{public}d, find parent component: %{public}d",
        expectedScrollAxis_,
        (parent != nullptr));
    if (parent) {
        if (isTouchpadSliding_) {
            source = SCROLL_FROM_UPDATE;
        } else {
            source = isMouseEvent_ ? SCROLL_FROM_AXIS : source;
        }
        return parent->HandleScroll(offset, source, state);
    }
    return { 0.0f, false };
}

bool WebPattern::HandleScrollVelocity(float velocity, const RefPtr<NestableScrollContainer>& child)
{
    // If no parent object is specified, the nearest nested scrollable parent is used by default.
    return HandleScrollVelocity(GetNestedScrollParent(), velocity);
}

bool WebPattern::HandleScrollVelocity(const RefPtr<NestableScrollContainer>& parent, float velocity)
{
    CHECK_NULL_RETURN(parent, false);
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::HandleScrollVelocity, to parent scroll velocity=%{public}f", velocity);
    if (parent->HandleScrollVelocity(velocity)) {
        OnParentScrollDragEndRecursive(parent);
        return true;
    }
    return false;
}

void WebPattern::OnScrollStartRecursive(WeakPtr<NestableScrollContainer> child, float position, float velocity)
{
    // If only one position value is passed, it will be notified to the nearest nested scrollable parent.
    OnScrollStartRecursive(position);
}

void WebPattern::OnScrollStartRecursive(float position)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnScrollStartRecursive");
    SetIsNestedInterrupt(false);
    isFirstFlingScrollVelocity_ = true;
    isScrollStarted_ = true;
    isDragEnd_ = false;
    auto it = parentsMap_.find(expectedScrollAxis_);
    CHECK_EQUAL_VOID(it, parentsMap_.end());
    auto parent = it->second.Upgrade();
    if (parent) {
        parent->OnScrollStartRecursive(WeakClaim(this), position);
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnScrollStartRecursive parent OnScrollStartRecursive");
    }
}

void WebPattern::OnAttachToBuilderNode(NodeStatus nodeStatus)
{
    TAG_LOGD(AceLogTag::ACE_WEB, "WebPattern::OnAttachToBuilderNode");
    if (nodeStatus != NodeStatus::NORMAL_NODE) {
        InitInOfflineMode();
    }
}

void WebPattern::OnScrollEndRecursive(const std::optional<float>& velocity)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnScrollEndRecursive");
    CHECK_EQUAL_VOID(isScrollStarted_, false);
    auto it = parentsMap_.find(expectedScrollAxis_);
    if (parentsMap_.find(expectedScrollAxis_) != parentsMap_.end()) {
        auto parent = it->second.Upgrade();
        if (parent) {
            OnParentScrollDragEndRecursive(parent);
            parent->OnScrollEndRecursive(std::nullopt);
            TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnScrollEndRecursive parent OnScrollEndRecursive");
        }
    }
    isScrollStarted_ = false;
    SetIsNestedInterrupt(false);
    expectedScrollAxis_ = Axis::FREE;
}

void WebPattern::OnOverScrollFlingVelocity(float xVelocity, float yVelocity, bool isFling)
{
    float velocity = (expectedScrollAxis_ == Axis::HORIZONTAL) ? xVelocity : yVelocity;
    OnOverScrollFlingVelocityHandler(velocity, isFling);
}

void WebPattern::OnOverScrollFlingVelocityHandler(float velocity, bool isFling)
{
    float directVelocity = velocity;
    if (IsRtl() && expectedScrollAxis_ == Axis::HORIZONTAL) {
        directVelocity = -velocity;
    }
    auto it = parentsMap_.find(expectedScrollAxis_);
    CHECK_EQUAL_VOID(it, parentsMap_.end());
    auto parent = it->second;
    ScrollResult result = { 0.f, true };
    auto remain = 0.f;
    if (!isFling) {
        if (scrollState_) {
            if (CheckOverParentScroll(velocity, NestedScrollMode::SELF_FIRST)) {
                result = HandleScroll(parent.Upgrade(), -directVelocity, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
                remain = result.remain;
            } else if (CheckOverParentScroll(velocity, NestedScrollMode::PARENT_FIRST)) {
                remain = -directVelocity;
            }
            if (!NearZero(remain)) {
                HandleScroll(parent.Upgrade(), remain, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL);
            }
        }
    } else {
        if (CheckParentScroll(velocity, NestedScrollMode::SELF_FIRST)) {
            if (isFirstFlingScrollVelocity_) {
                HandleScrollVelocity(parent.Upgrade(), directVelocity);
                isFirstFlingScrollVelocity_ = false;
            }
        }
    }
}

void WebPattern::OnScrollState(bool scrollState)
{
    scrollState_ = scrollState;
    if (!scrollState) {
        OnScrollEndRecursive(std::nullopt);
    }
}

void WebPattern::OnScrollStart(const float x, const float y)
{
    TAG_LOGI(
        AceLogTag::ACE_WEB, "WebPattern::OnScrollStart  x=%{public}f, y=%{public}f, isRtl:%{public}d", x, y, IsRtl());
    scrollState_ = true;
    GetParentAxis();
    expectedScrollAxis_ =(abs(x) > abs(y) ? Axis::HORIZONTAL : Axis::VERTICAL);
    OnScrollStartRecursive(0.0);
    if (imageAnalyzerManager_) {
        imageAnalyzerManager_->UpdateOverlayStatus(
            false,
            0,
            0,
            0,
            0);
    }
}

void WebPattern::SetLayoutMode(WebLayoutMode mode)
{
    if (layoutMode_ == mode) {
        return;
    }
    layoutMode_ = mode;
    TAG_LOGI(AceLogTag::ACE_WEB, "layoutMode is: %{public}d.", layoutMode_);
    OnZoomAccessEnabledUpdate(GetZoomAccessEnabledValue(true));
    if (delegate_) {
        delegate_->UpdateLayoutMode(mode);
    }
    isLayoutModeChanged_ = true;
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE | PROPERTY_UPDATE_RENDER);
}

void WebPattern::SetRenderMode(RenderMode renderMode)
{
    if (isRenderModeInit_) {
        TAG_LOGI(AceLogTag::ACE_WEB, "renderMode not allow to change.");
        return;
    }
    renderMode_ = renderMode;
    TAG_LOGI(AceLogTag::ACE_WEB, "renderMode is %{public}d", renderMode_);
    isRenderModeInit_ = true;
}

void WebPattern::GetParentAxis()
{
    auto parent = GetNestedScrollParent();
    if (parent) {
        axis_ = parent->GetAxis();
        parentsMap_ = { { axis_, parent } };
        auto oppositeParent = SearchParent(axis_ == Axis::HORIZONTAL ? Axis::VERTICAL : Axis::HORIZONTAL);
        if (oppositeParent) {
            parentsMap_.emplace(oppositeParent->GetAxis(), oppositeParent);
        }
    } else {
        auto verticalParent = SearchParent(Axis::VERTICAL);
        auto horizontalParent = SearchParent(Axis::HORIZONTAL);
        if (verticalParent) {
            parentsMap_.emplace(verticalParent->GetAxis(), verticalParent);
        }
        if (horizontalParent) {
            parentsMap_.emplace(horizontalParent->GetAxis(), horizontalParent);
        }
    }
}

RefPtr<NestableScrollContainer> WebPattern::SearchParent()
{
    return SearchParent(Axis::NONE);
}

RefPtr<NestableScrollContainer> WebPattern::SearchParent(Axis scrollAxis)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    for (auto parent = host->GetParent(); parent != nullptr; parent = parent->GetParent()) {
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            continue;
        }
        auto pattern = frameNode->GetPattern<NestableScrollContainer>();
        if (!pattern ||
            (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) &&
                InstanceOf<RefreshPattern>(pattern))) {
            continue;
        }
        if (scrollAxis == Axis::NONE || scrollAxis == pattern->GetAxis()) {
            return pattern;
        }
    }
    return nullptr;
}

void WebPattern::SetNestedScrollExt(const NestedScrollOptionsExt &nestedScroll)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    if (nestedScroll.scrollUp == nestedScroll.scrollLeft) {
        nestedOpt.backward = nestedScroll.scrollUp;
    }
    if (nestedScroll.scrollDown == nestedScroll.scrollRight) {
        nestedOpt.forward = nestedScroll.scrollDown;
    }
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<NestableScrollContainer>();
    if (pattern) {
        pattern->SetNestedScroll(nestedOpt);
    }
    TAG_LOGI(
        AceLogTag::ACE_WEB, "SetNestedScrollExt nestedScroll: %{public}s", nestedScroll.ToString().c_str());
    nestedScroll_ = nestedScroll;
}

bool WebPattern::IsDialogNested()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    for (auto parent = host->GetParent(); parent != nullptr; parent = parent->GetParent()) {
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            continue;
        }
        if (frameNode->GetPattern<DialogPattern>()) {
            return true;
        }
    }
    return false;
}

void WebPattern::OnRootLayerChanged(int width, int height)
{
    if ((rootLayerWidth_ == width) && (rootLayerHeight_ == height)) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_WEB, "OnRootLayerChanged width : %{public}d, height : %{public}d", width, height);
    rootLayerWidth_ = width;
    rootLayerHeight_ = height;
    if (layoutMode_ != WebLayoutMode::FIT_CONTENT) {
        return;
    }
    rootLayerChangeSize_ = Size(width, height);
    ReleaseResizeHold();
}

void WebPattern::ReleaseResizeHold()
{
    if (layoutMode_ != WebLayoutMode::FIT_CONTENT) {
        return;
    }
    drawSize_.SetSize(rootLayerChangeSize_);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE | PROPERTY_UPDATE_RENDER);
}

bool WebPattern::OnNestedScroll(float& x, float& y, float& xVelocity, float& yVelocity, bool& isAvailable)
{
    isAvailable = true;
    // not a nested scrolling scene
    bool hasHorizontalParent = parentsMap_.find(Axis::HORIZONTAL) != parentsMap_.end();
    bool hasVerticalParent = parentsMap_.find(Axis::VERTICAL) != parentsMap_.end();
    if (!hasHorizontalParent && !hasVerticalParent) {
        return false;
    }
    float offset = y;
    float velocity = yVelocity;
    if (expectedScrollAxis_ == Axis::HORIZONTAL) {
        offset = x;
        velocity = xVelocity;
        if (isScrollStarted_) {
            y = 0.0f;
            yVelocity = 0.0f;
        }
    } else {
        if (isScrollStarted_) {
            x = 0.0f;
            xVelocity = 0.0f;
        }
    }
    bool isConsumed = offset != 0 ? FilterScrollEventHandleOffset(offset) : FilterScrollEventHandleVelocity(velocity);
    TAG_LOGI(AceLogTag::ACE_WEB,
        "WebPattern::OnNestedScroll  x=%{public}f, y=%{public}f, xVelocity:%{public}f, yVelocity:%{public}f, "
        "isConsumed:%{public}d",
        x, y, xVelocity, yVelocity, isConsumed);
    return isConsumed;
}

bool WebPattern::IsRtl()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto dir = layoutProperty->GetLayoutDirection();
    if (TextDirection::RTL == dir) {
        return true;
    } else if (TextDirection::LTR == dir) {
        return false;
    } else {
        return AceApplicationInfo::GetInstance().IsRightToLeft();
    }
}

bool WebPattern::FilterScrollEvent(const float x, const float y, const float xVelocity, const float yVelocity)
{
    float offset = expectedScrollAxis_ == Axis::HORIZONTAL ? x : y;
    float velocity = expectedScrollAxis_ == Axis::HORIZONTAL ? xVelocity : yVelocity;
    bool isConsumed = offset != 0 ? FilterScrollEventHandleOffset(offset) : FilterScrollEventHandleVelocity(velocity);
    TAG_LOGI(AceLogTag::ACE_WEB,
        "WebPattern::FilterScrollEvent  x=%{public}f, y=%{public}f, xVelocity:%{public}f, yVelocity:%{public}f, "
        "isConsumed:%{public}d",
        x, y, xVelocity, yVelocity, isConsumed);
    return isConsumed;
}

bool WebPattern::FilterScrollEventHandleOffset(float offset)
{
    float directOffset = offset;
    if (IsRtl() && expectedScrollAxis_ == Axis::HORIZONTAL) {
        directOffset = -offset;
    }
    auto it = parentsMap_.find(expectedScrollAxis_);
    CHECK_EQUAL_RETURN(it, parentsMap_.end(), false);
    auto parent = it->second;
    if (parent.Upgrade() && !NearZero(directOffset)) {
        auto res =
            HandleScroll(parent.Upgrade(), directOffset, SCROLL_FROM_UPDATE, NestedState::CHILD_CHECK_OVER_SCROLL);
        if (NearZero(res.remain)) {
            return true;
        }
        directOffset = res.remain;
    }
    if (CheckParentScroll(offset, NestedScrollMode::PARENT_FIRST)) {
        auto result = HandleScroll(parent.Upgrade(), directOffset, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
        CHECK_EQUAL_RETURN(isParentReachEdge_ && result.reachEdge, true, false);
        isParentReachEdge_ = result.reachEdge;
        CHECK_NULL_RETURN(delegate_, false);
        expectedScrollAxis_ == Axis::HORIZONTAL ? delegate_->ScrollByRefScreen(-result.remain, 0)
                                                : delegate_->ScrollByRefScreen(0, -result.remain);
        return true;
    } else if (CheckParentScroll(offset, NestedScrollMode::PARALLEL)) {
        HandleScroll(parent.Upgrade(), directOffset, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    }
    return false;
}

bool WebPattern::CheckParentScroll(const float &directValue, const NestedScrollMode &scrollMode)
{
    auto nestedScroll = GetNestedScrollExt();
    return (directValue > 0 && nestedScroll.scrollUp == scrollMode &&
            expectedScrollAxis_ != Axis::HORIZONTAL) ||
        (directValue > 0 && nestedScroll.scrollLeft == scrollMode &&
            expectedScrollAxis_ == Axis::HORIZONTAL) ||
        (directValue < 0 && nestedScroll.scrollDown == scrollMode &&
            expectedScrollAxis_ != Axis::HORIZONTAL) ||
        (directValue < 0 && nestedScroll.scrollRight == scrollMode &&
            expectedScrollAxis_ == Axis::HORIZONTAL);
}

bool WebPattern::CheckOverParentScroll(const float &directValue, const NestedScrollMode &scrollMode)
{
    auto nestedScroll = GetNestedScrollExt();
    return (directValue < 0 && nestedScroll.scrollUp == scrollMode &&
            expectedScrollAxis_ != Axis::HORIZONTAL) ||
        (directValue < 0 && nestedScroll.scrollLeft == scrollMode &&
            expectedScrollAxis_ == Axis::HORIZONTAL) ||
        (directValue > 0 && nestedScroll.scrollDown == scrollMode &&
            expectedScrollAxis_ != Axis::HORIZONTAL) ||
        (directValue > 0 && nestedScroll.scrollRight == scrollMode &&
            expectedScrollAxis_ == Axis::HORIZONTAL);
}

bool WebPattern::FilterScrollEventHandleVelocity(const float velocity)
{
    float directVelocity = velocity;
    if (IsRtl() && expectedScrollAxis_ == Axis::HORIZONTAL) {
        directVelocity = -velocity;
    }
    auto it = parentsMap_.find(expectedScrollAxis_);
    CHECK_EQUAL_RETURN(it, parentsMap_.end(), false);
    auto parent = it->second;
    if (parent.Upgrade() && parent.Upgrade()->NestedScrollOutOfBoundary()) {
        return HandleScrollVelocity(parent.Upgrade(), directVelocity);
    }
    if (CheckParentScroll(velocity, NestedScrollMode::PARENT_FIRST)) {
        if (isParentReachEdge_) {
            return false;
        }
        return HandleScrollVelocity(parent.Upgrade(), directVelocity);
    } else if (CheckParentScroll(velocity, NestedScrollMode::PARALLEL)) {
        HandleScrollVelocity(parent.Upgrade(), directVelocity);
    }
    return false;
}

void WebPattern::CheckAndSetWebNestedScrollExisted()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::CheckAndSetWebNestedScrollExisted");
    auto webBypassVsyncCondition = GetWebBypassVsyncCondition();
    bool isVsyncCondition = WebBypassVsyncCondition::SCROLLBY_FROM_ZERO_OFFSET == webBypassVsyncCondition;
    auto it = parentsMap_.find(Axis::VERTICAL);
    if (parentsMap_.find(Axis::VERTICAL) != parentsMap_.end()) {
        auto parent = it->second.Upgrade();
        if (parent) {
            TAG_LOGI(AceLogTag::ACE_WEB,
                "WebPattern::CheckAndSetWebNestedScrollExisted isVsyncCondition:%{public}d",
                isVsyncCondition);
            parent->SetWebNestedScrollExisted(isVsyncCondition);
        }
    }

    it = parentsMap_.find(Axis::HORIZONTAL);
    if (parentsMap_.find(Axis::HORIZONTAL) != parentsMap_.end()) {
        auto parent = it->second.Upgrade();
        if (parent) {
            TAG_LOGI(AceLogTag::ACE_WEB,
                "WebPattern::CheckAndSetWebNestedScrollExisted isVsyncCondition:%{public}d",
                isVsyncCondition);
            parent->SetWebNestedScrollExisted(isVsyncCondition);
        }
    }
}

bool WebPattern::IsDefaultFocusNodeExist()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto focusManager = pipeline->GetFocusManager();
    CHECK_NULL_RETURN(focusManager, false);
    auto focusView =  focusManager->GetLastFocusView().Upgrade();
    CHECK_NULL_RETURN(focusView, false);
    auto focusHub = focusView->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    bool result = focusHub->GetChildFocusNodeByType();
    return result;
}

void WebPattern::InitSlideUpdateListener()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    for (auto parent = host->GetParent(); parent != nullptr; parent = parent->GetParent()) {
        bool hasTargetParent =
            std::find(SYNC_RENDER_SLIDE.begin(), SYNC_RENDER_SLIDE.end(), parent->GetTag()) == SYNC_RENDER_SLIDE.end();
        if (hasTargetParent) {
            continue;
        }
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
        CHECK_NULL_VOID(frameNode);
        if (parent->GetTag() == V2::LIST_ETS_TAG) {
            auto pattern = frameNode->GetPattern<ListPattern>();
            CHECK_NULL_VOID(pattern);
            syncAxis_ = pattern->GetAxis();
        } else {
            auto pattern = frameNode->GetPattern<ScrollPattern>();
            CHECK_NULL_VOID(pattern);
            syncAxis_ = pattern->GetAxis();
        }
        CHECK_NULL_VOID(renderSurface_);
        renderSurface_->SetWebSlideAxis(syncAxis_);
    }
}

void WebPattern::UpdateSlideOffset()
{
    switch (syncAxis_) {
        case Axis::HORIZONTAL:
            CalculateHorizontalDrawRect();
            break;
        case Axis::VERTICAL:
            CalculateVerticalDrawRect();
            break;
        default :
            break;
    }
}

void WebPattern::CalculateHorizontalDrawRect()
{
    if (!GetCoordinatePoint().has_value()) {
        return;
    }
    fitContentOffset_ = OffsetF(GetCoordinatePoint()->GetX(), GetCoordinatePoint()->GetY());
    CHECK_NULL_VOID(renderSurface_);
    renderSurface_->SetWebOffset(fitContentOffset_.GetX());
    if (fitContentOffset_.GetX() >= 0) {
        if (isNeedReDrawRect_) {
            SetDrawRect(0, 0, ADJUST_WEB_DRAW_LENGTH + ADJUST_WEB_DRAW_LENGTH, drawRectHeight_);
        }
        isNeedReDrawRect_ = false;
        return;
    }

    int32_t stepGear = (-fitContentOffset_.GetX()) / ADJUST_WEB_DRAW_LENGTH;
    int32_t width = ADJUST_WEB_DRAW_LENGTH * 2 + stepGear;
    int32_t height = std::min(static_cast<int32_t>(drawSize_.Height()), FIT_CONTENT_LIMIT_LENGTH);
    int32_t x = ADJUST_WEB_DRAW_LENGTH * stepGear;
    int32_t y = 0;
    renderSurface_->SetWebMessage({ x, 0 });
    TAG_LOGD(AceLogTag::ACE_WEB, "SetDrawRect x : %{public}d, y : %{public}d, width : %{public}d, height : %{public}d",
        x, y, width, height);
    SetDrawRect(x, y, width, height);
    isNeedReDrawRect_ = true;
}

void WebPattern::CalculateVerticalDrawRect()
{
    if (!GetCoordinatePoint().has_value()) {
        return;
    }
    fitContentOffset_ = OffsetF(GetCoordinatePoint()->GetX(), GetCoordinatePoint()->GetY());
    CHECK_NULL_VOID(renderSurface_);
    renderSurface_->SetWebOffset(fitContentOffset_.GetY());
    if (fitContentOffset_.GetY() >= 0) {
        if (isNeedReDrawRect_) {
            SetDrawRect(0, 0, drawRectWidth_, ADJUST_WEB_DRAW_LENGTH + ADJUST_WEB_DRAW_LENGTH);
        }
        isNeedReDrawRect_ = false;
        return;
    }

    int32_t stepGear = (-fitContentOffset_.GetY()) / ADJUST_WEB_DRAW_LENGTH;
    int32_t width = std::min(static_cast<int32_t>(drawSize_.Width()), FIT_CONTENT_LIMIT_LENGTH);
    int32_t height = ADJUST_WEB_DRAW_LENGTH * 2 + stepGear;
    int32_t x = 0;
    int32_t y = ADJUST_WEB_DRAW_LENGTH * stepGear;
    renderSurface_->SetWebMessage({ 0, y });
    TAG_LOGD(AceLogTag::ACE_WEB, "SetDrawRect x : %{public}d, y : %{public}d, width : %{public}d, height : %{public}d",
        x, y, width, height);
    SetDrawRect(x, y, width, height);
    isNeedReDrawRect_ = true;
}

void WebPattern::PostTaskToUI(const std::function<void()>&& task, const std::string& name) const
{
    CHECK_NULL_VOID(task);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    auto taskExecutor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(task, TaskExecutor::TaskType::UI, name);
}

void WebPattern::SetDrawRect(int32_t x, int32_t y, int32_t width, int32_t height)
{
    if ((drawRectWidth_ == width) && (drawRectHeight_ == height)) {
        return;
    }
    drawRectWidth_ = width;
    drawRectHeight_ = height;
    CHECK_NULL_VOID(delegate_);
    delegate_->SetDrawRect(x, y, width, height);
}

bool WebPattern::GetPendingSizeStatus()
{
    if (delegate_) {
        return delegate_->GetPendingSizeStatus();
    }
    return false;
}

RefPtr<NodePaintMethod> WebPattern::CreateNodePaintMethod()
{
    auto paint = MakeRefPtr<WebPaintMethod>(renderSurface_);
    return paint;
}

void WebPattern::JavaScriptOnDocumentStart(const ScriptItems& scriptItems)
{
    onDocumentStartScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    onDocumentStartScriptItemsByOrder_ = std::nullopt;
    if (delegate_) {
        UpdateJavaScriptOnDocumentStart();
        delegate_->JavaScriptOnDocumentStart();
    }
}

void WebPattern::JavaScriptOnDocumentStartByOrder(const ScriptItems& scriptItems,
    const ScriptItemsByOrder& scriptItemsByOrder)
{
    onDocumentStartScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    onDocumentStartScriptItemsByOrder_ = std::make_optional<ScriptItemsByOrder>(scriptItemsByOrder);
    if (delegate_) {
        UpdateJavaScriptOnDocumentStartByOrder();
        delegate_->JavaScriptOnDocumentStartByOrder();
    }
}

void WebPattern::JavaScriptOnDocumentEndByOrder(const ScriptItems& scriptItems,
    const ScriptItemsByOrder& scriptItemsByOrder)
{
    onDocumentEndScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    onDocumentEndScriptItemsByOrder_ = std::make_optional<ScriptItemsByOrder>(scriptItemsByOrder);
    EventRecorder::Get().FillWebJsCode(onDocumentEndScriptItems_);
    if (delegate_) {
        UpdateJavaScriptOnDocumentEndByOrder();
        delegate_->JavaScriptOnDocumentEndByOrder();
    }
}

void WebPattern::JavaScriptOnHeadReadyByOrder(const ScriptItems& scriptItems,
    const ScriptItemsByOrder& scriptItemsByOrder)
{
    onHeadReadyScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    onHeadReadyScriptItemsByOrder_ = std::make_optional<ScriptItemsByOrder>(scriptItemsByOrder);
    if (delegate_) {
        UpdateJavaScriptOnHeadReadyByOrder();
        delegate_->JavaScriptOnHeadReadyByOrder();
    }
}

void WebPattern::JavaScriptOnDocumentEnd(const ScriptItems& scriptItems)
{
    onDocumentEndScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    onDocumentEndScriptItemsByOrder_ = std::nullopt;
    EventRecorder::Get().FillWebJsCode(onDocumentEndScriptItems_);
    if (delegate_) {
        UpdateJavaScriptOnDocumentEnd();
        delegate_->JavaScriptOnDocumentEnd();
    }
}

void WebPattern::UpdateJavaScriptOnDocumentStart()
{
    if (delegate_ && onDocumentStartScriptItems_.has_value() && !onDocumentStartScriptItemsByOrder_.has_value()) {
        delegate_->SetJavaScriptItems(onDocumentStartScriptItems_.value(), ScriptItemType::DOCUMENT_START);
        onDocumentStartScriptItems_ = std::nullopt;
    }
}

void WebPattern::UpdateJavaScriptOnDocumentStartByOrder()
{
    if (delegate_ && onDocumentStartScriptItems_.has_value() && onDocumentStartScriptItemsByOrder_.has_value()) {
        delegate_->SetJavaScriptItemsByOrder(onDocumentStartScriptItems_.value(), ScriptItemType::DOCUMENT_START,
            onDocumentStartScriptItemsByOrder_.value());
        onDocumentStartScriptItems_ = std::nullopt;
        onDocumentStartScriptItemsByOrder_ = std::nullopt;
    }
}

void WebPattern::UpdateJavaScriptOnDocumentEndByOrder()
{
    if (delegate_ && onDocumentEndScriptItems_.has_value() && onDocumentEndScriptItemsByOrder_.has_value()) {
        delegate_->SetJavaScriptItemsByOrder(onDocumentEndScriptItems_.value(), ScriptItemType::DOCUMENT_END,
            onDocumentEndScriptItemsByOrder_.value());
        onDocumentEndScriptItems_ = std::nullopt;
        onDocumentEndScriptItemsByOrder_ = std::nullopt;
    }
}

void WebPattern::UpdateJavaScriptOnHeadReadyByOrder()
{
    if (delegate_ && onHeadReadyScriptItems_.has_value() && onHeadReadyScriptItemsByOrder_.has_value()) {
        delegate_->SetJavaScriptItemsByOrder(onHeadReadyScriptItems_.value(), ScriptItemType::DOCUMENT_HEAD_READY,
            onHeadReadyScriptItemsByOrder_.value());
        onHeadReadyScriptItems_ = std::nullopt;
        onHeadReadyScriptItemsByOrder_ = std::nullopt;
    }
}

void WebPattern::UpdateJavaScriptOnDocumentEnd()
{
    if (delegate_ && onDocumentEndScriptItems_.has_value() && !onDocumentEndScriptItemsByOrder_.has_value()) {
        delegate_->SetJavaScriptItems(onDocumentEndScriptItems_.value(), ScriptItemType::DOCUMENT_END);
        onDocumentEndScriptItems_ = std::nullopt;
    }
}

std::shared_ptr<NWeb::NWebAccessibilityNodeInfo> WebPattern::GetAccessibilityNodeById(int64_t accessibilityId)
{
    if (!accessibilityState_) {
        return nullptr;
    }
    CHECK_NULL_RETURN(delegate_, nullptr);
    return delegate_->GetAccessibilityNodeInfoById(accessibilityId);
}

std::shared_ptr<NG::TransitionalNodeInfo> WebPattern::GetTransitionalNodeById(int64_t accessibilityId)
{
    if (!accessibilityState_) {
        return nullptr;
    }
    CHECK_NULL_RETURN(delegate_, nullptr);
    auto accessNode = delegate_->GetAccessibilityNodeInfoById(accessibilityId);
    CHECK_NULL_RETURN(accessNode, nullptr);
    return std::make_shared<NG::TransitionalNodeInfo>(accessNode);
}

std::shared_ptr<NG::TransitionalNodeInfo> WebPattern::GetFocusedAccessibilityNode(
    int64_t accessibilityId, bool isAccessibilityFocus)
{
    if (!accessibilityState_) {
        return nullptr;
    }
    CHECK_NULL_RETURN(delegate_, nullptr);
    auto accessNode = delegate_->GetFocusedAccessibilityNodeInfo(accessibilityId, isAccessibilityFocus);
    CHECK_NULL_RETURN(accessNode, nullptr);
    return std::make_shared<NG::TransitionalNodeInfo>(accessNode);
}


std::shared_ptr<NG::TransitionalNodeInfo> WebPattern::GetAccessibilityNodeByFocusMove(int64_t accessibilityId,
    int32_t direction)
{
    if (!accessibilityState_) {
        return nullptr;
    }
    CHECK_NULL_RETURN(delegate_, nullptr);
    auto accessNode = delegate_->GetAccessibilityNodeInfoByFocusMove(accessibilityId, direction);
    CHECK_NULL_RETURN(accessNode, nullptr);
    return std::make_shared<NG::TransitionalNodeInfo>(accessNode);
}

bool WebPattern::ExecuteAction(int64_t accessibilityId, AceAction action,
    const std::map<std::string, std::string>& actionArguments) const
{
    CHECK_NULL_RETURN(delegate_, false);
    if (!accessibilityState_) {
        return false;
    }
    return delegate_->ExecuteAction(accessibilityId, action, actionArguments);
}

void WebPattern::SetAccessibilityState(bool state, bool isDelayed)
{
    CHECK_NULL_VOID(delegate_);
    focusedAccessibilityId_ = -1;
    if (!state) {
        if (!accessibilityState_ || inspectorAccessibilityEnable_ || textBlurAccessibilityEnable_) {
            return;
        }
        accessibilityState_ = state;
        // accessibilityState_ acts as a service switch rather than a master switch
        if (IsAccessibilityUsedByEventReport()) {
            TAG_LOGE(AceLogTag::ACE_WEB, "WebPattern::SetAccessibilityState, still used by event report");
            return;
        }
        delegate_->SetAccessibilityState(state, isDelayed);
        return;
    }

    if (accessibilityState_ != state) {
        accessibilityState_ = state;
        delegate_->SetAccessibilityState(state, isDelayed);
    }
}

void WebPattern::UpdateFocusedAccessibilityId(int64_t accessibilityId)
{
    if (!accessibilityState_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    if (accessibilityId > 0) {
        focusedAccessibilityId_ = accessibilityId;
    } else if (focusedAccessibilityId_ == -1) {
        return;
    }
    RectT<int32_t> rect;
    if (focusedAccessibilityId_ <= 0) {
        focusedAccessibilityId_ = -1;
        renderContext->ResetAccessibilityFocusRect();
        renderContext->UpdateAccessibilityFocus(false);
        return;
    }
    if (GetAccessibilityFocusRect(rect, focusedAccessibilityId_)) {
        if (rect.Width() <= MIN_ACCESSIBILITY_FOCUS_SIZE || rect.Height() <= MIN_ACCESSIBILITY_FOCUS_SIZE) {
            renderContext->ResetAccessibilityFocusRect();
            renderContext->UpdateAccessibilityFocus(false);
        } else {
            renderContext->UpdateAccessibilityFocusRect(rect);
            renderContext->UpdateAccessibilityFocus(true);
        }
    } else {
        renderContext->ResetAccessibilityFocusRect();
        renderContext->UpdateAccessibilityFocus(false);
    }
}

void WebPattern::ClearFocusedAccessibilityId()
{
    if (!accessibilityState_) {
        return;
    }

    focusedAccessibilityId_ = -1;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->ResetAccessibilityFocusRect();
    renderContext->UpdateAccessibilityFocus(false);
}

std::shared_ptr<Rosen::RSNode> WebPattern::GetSurfaceRSNode() const
{
    CHECK_NULL_RETURN(renderContextForSurface_, nullptr);
    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(renderContextForSurface_);
    CHECK_NULL_RETURN(rosenRenderContext, nullptr);
    return rosenRenderContext->GetRSNode();
}

bool WebPattern::GetAccessibilityFocusRect(RectT<int32_t>& paintRect, int64_t accessibilityId) const
{
    if (!accessibilityState_) {
        return false;
    }
    CHECK_NULL_RETURN(delegate_, false);
    int32_t rectWidth = 0;
    int32_t rectHeight = 0;
    int32_t rectX = 0;
    int32_t rectY = 0;
    bool result = delegate_->GetAccessibilityNodeRectById(accessibilityId, &rectWidth, &rectHeight, &rectX, &rectY);
    if (!result) {
        return false;
    }

    paintRect.SetRect(rectX, rectY, rectWidth, rectHeight);
    return true;
}

void WebPattern::SetTouchEventInfo(const TouchEvent& touchEvent,
    TouchEventInfo& touchEventInfo, const std::string& embedId)
{
    CHECK_NULL_VOID(delegate_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto offset = host->GetTransformRelativeOffset();

    TouchEventInfo tempTouchInfo = touchEventInfo_;
    if (touchEvent.type == TouchType::DOWN || touchEvent.type == TouchType::UP) {
        while (!touchEventQueue_.empty()) {
            if (touchEventQueue_.front().GetChangedTouches().front().GetFingerId() == touchEvent.id) {
                tempTouchInfo = touchEventQueue_.front();
                touchEventQueue_.pop();
                break;
            } else {
                touchEventQueue_.pop();
            }
        }
    }
    auto pos = delegate_->GetPosition(embedId);
    touchEventInfo.SetSourceDevice(tempTouchInfo.GetSourceDevice());
    touchEventInfo.SetTarget(tempTouchInfo.GetTarget());
    touchEventInfo.SetForce(tempTouchInfo.GetForce());
    touchEventInfo.SetSourceTool(tempTouchInfo.GetSourceTool());
    touchEventInfo.SetTargetDisplayId(tempTouchInfo.GetTargetDisplayId());
    touchEventInfo.SetDeviceId(tempTouchInfo.GetDeviceId());

    TouchLocationInfo changedInfo("onTouch", touchEvent.id);
    changedInfo.SetLocalLocation(Offset(touchEvent.x, touchEvent.y));
    changedInfo.SetGlobalLocation(Offset(touchEvent.x + offset.GetX() + pos.GetX(),
        touchEvent.y + offset.GetY() + pos.GetY()));
    changedInfo.SetScreenLocation(Offset(touchEvent.x + offset.GetX() + pos.GetX(),
        touchEvent.y + offset.GetY() + pos.GetY()));
    changedInfo.SetGlobalDisplayLocation(Offset(touchEvent.x + offset.GetX() + pos.GetX(),
        touchEvent.y + offset.GetY() + pos.GetY()));
    changedInfo.SetTouchType(touchEvent.type);

    SetTouchLocationInfo(touchEvent, changedInfo, tempTouchInfo, touchEventInfo);

    touchEventInfo.AddChangedTouchLocationInfo(std::move(changedInfo));
}

void WebPattern::SetTouchLocationInfo(const TouchEvent& touchEvent, const TouchLocationInfo& changedInfo,
    const TouchEventInfo& tempTouchInfo, TouchEventInfo& touchEventInfo)
{
    float scaleX = 0.0f;
    float scaleY = 0.0f;
    const std::list<TouchLocationInfo>& touchList = tempTouchInfo.GetTouches();
    for (const TouchLocationInfo& location : touchList) {
        if (touchEvent.id == location.GetFingerId()) {
            const OHOS::Ace::Offset& localLocation = location.GetLocalLocation();
            scaleX = localLocation.GetX() - touchEvent.x;
            scaleY = localLocation.GetY() - touchEvent.y;
        }
    }
    for (const TouchLocationInfo& location : touchList) {
        TouchLocationInfo info("onTouch", location.GetFingerId());
        if (touchEvent.id == location.GetFingerId()) {
            info.SetGlobalLocation(changedInfo.GetGlobalLocation());
            info.SetLocalLocation(changedInfo.GetLocalLocation());
            info.SetScreenLocation(changedInfo.GetScreenLocation());
            info.SetGlobalDisplayLocation(changedInfo.GetGlobalDisplayLocation());
            info.SetTouchType(changedInfo.GetTouchType());
        } else {
            const OHOS::Ace::Offset& localLocation = location.GetLocalLocation();
            const OHOS::Ace::Offset& globalLocation = location.GetGlobalLocation();
            const OHOS::Ace::Offset& screenLocation = location.GetScreenLocation();
            const OHOS::Ace::Offset& globalDisplayLocation = location.GetGlobalDisplayLocation();
            info.SetGlobalLocation(Offset(globalLocation.GetX() - scaleX, globalLocation.GetY() - scaleY));
            info.SetLocalLocation(Offset(localLocation.GetX() - scaleX, localLocation.GetY() - scaleY));
            info.SetScreenLocation(Offset(screenLocation.GetX() - scaleX, screenLocation.GetY() - scaleY));
            info.SetGlobalDisplayLocation(
                Offset(globalDisplayLocation.GetX() - scaleX, globalDisplayLocation.GetY() - scaleY));
            info.SetTouchType(location.GetTouchType());
        }
        touchEventInfo.AddTouchLocationInfo(std::move(info));
    }
}

void WebPattern::RegisterVisibleAreaChangeCallback(const RefPtr<PipelineContext> &pipeline)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        if (!visible && !NearZero(ratio)) {
            TAG_LOGI(AceLogTag::ACE_WEB, "Fiterate not visible when ratio=%{public}f", ratio);
            return;
        }
        webPattern->OnVisibleAreaChange(visible);
    };
    std::vector<double> ratioList = {0.0, 1.0};
    pipeline->AddVisibleAreaChangeNode(host, ratioList, callback, false, true);
}

std::vector<int8_t> WebPattern::GetWordSelection(const std::string& text, int8_t offset)
{
    // start sync task
    std::future<std::vector<int8_t>> future = std::async(std::launch::async, [text, offset]() {
        return DataDetectorMgr::GetInstance().GetWordSelection(text, offset);
    });
    // set timeout
    auto status = future.wait_for(std::chrono::milliseconds(AI_TIMEOUT_LIMIT));
    if (status == std::future_status::ready) {
        return future.get();
    } else {
        TAG_LOGE(AceLogTag::ACE_WEB, "WebPattern::GetWordSelection timeout! return default");
        return std::vector<int8_t> { -1, -1 };
    }
}

bool WebPattern::CheckSafeAreaIsExpand()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto &&opts = layoutProperty->GetSafeAreaExpandOpts();
    CHECK_NULL_RETURN(opts, false);
    if ((opts->type & SAFE_AREA_TYPE_SYSTEM) || (opts->type & SAFE_AREA_TYPE_KEYBOARD)) {
        return true;
    }
    return false;
}

bool WebPattern::CheckSafeAreaKeyBoard()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto &&opts = layoutProperty->GetSafeAreaExpandOpts();
    CHECK_NULL_RETURN(opts, false);
    if ((opts->type & SAFE_AREA_TYPE_KEYBOARD) && (opts->edges & SAFE_AREA_EDGE_BOTTOM)) {
        TAG_LOGI(AceLogTag::ACE_WEB, "SafeArea type is KEYBOARD.");
        return true;
    }
    return false;
}

bool WebPattern::Backward()
{
    if (!delegate_) {
        TAG_LOGE(AceLogTag::ACE_WEB, "delegate is null");
        return false;
    }
    if (delegate_->AccessBackward()) {
        delegate_->Backward();
        return true;
    }
    return false;
}

void WebPattern::SuggestionSelected(int32_t index)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::SuggestionSelected index:%{public}d", index);
    CHECK_NULL_VOID(delegate_);
    delegate_->SuggestionSelected(index);
}

void WebPattern::OnShowAutofillPopup(
    const float offsetX, const float offsetY, const std::vector<std::string>& menu_items)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnShowAutofillPopup");
    isShowAutofillPopup_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto id = host->GetId();
    std::vector<SelectParam> selectParam;
    for (auto& item : menu_items) {
        selectParam.push_back({ item, "" });
    }
    auto menu = MenuView::Create(selectParam, id, host->GetTag());
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto menuContainer = AceType::DynamicCast<FrameNode>(menu->GetChildAtIndex(0));
    CHECK_NULL_VOID(menuContainer);
    auto menuPattern = menuContainer->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto options = menuPattern->GetOptions();
    for (auto &&option : options) {
        auto selectCallback = [weak = WeakClaim(this)](int32_t index) {
            auto webPattern = weak.Upgrade();
            CHECK_NULL_VOID(webPattern);
            webPattern->SuggestionSelected(index);
        };
        auto optionNode = AceType::DynamicCast<FrameNode>(option);
        if (optionNode) {
            auto hub = optionNode->GetEventHub<MenuItemEventHub>();
            auto optionPattern = optionNode->GetPattern<MenuItemPattern>();
            if (!hub || !optionPattern) {
                continue;
            }
            hub->SetOnSelect(std::move(selectCallback));
            optionNode->MarkModifyDone();
        }
    }
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto offset = GetCoordinatePoint().value_or(OffsetF());
    offset.AddX(offsetX);
    offset.AddY(offsetY);
    menu->GetOrCreateFocusHub()->SetFocusable(false);
    overlayManager->DeleteMenu(id);
    overlayManager->ShowMenu(id, offset, menu);
}

void WebPattern::OnShowAutofillPopupV2(
    const float offsetX, const float offsetY, const float height, const float width,
    const std::vector<std::string>& menu_items)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnShowAutofillPopupV2");
    isShowAutofillPopup_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::vector<OptionParam> optionParam;
    for (auto& item : menu_items) {
        optionParam.push_back({ item, "", nullptr });
    }
    NG::MenuParam menuParam;
    menuParam.isShow = true;
    menuParam.setShow = true;
    menuParam.placement = Placement::BOTTOM_LEFT;
    menuParam.isShowInSubWindow = false;
    auto dataListNode = CreateDataListFrameNode(OffsetF(offsetX, offsetY), height, width);
    CHECK_NULL_VOID(dataListNode);
    auto menu = MenuView::Create(std::move(optionParam), dataListNode->GetId(), dataListNode->GetTag(),
        MenuType::MENU, menuParam);
    auto menuContainer = AceType::DynamicCast<FrameNode>(menu->GetChildAtIndex(0));
    CHECK_NULL_VOID(menuContainer);
    auto menuPattern = menuContainer->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto options = menuPattern->GetOptions();
    for (auto &&option : options) {
        auto selectCallback = [weak = WeakClaim(this)](int32_t index) {
            auto webPattern = weak.Upgrade();
            CHECK_NULL_VOID(webPattern);
            webPattern->SuggestionSelected(index);
        };
        auto optionNode = AceType::DynamicCast<FrameNode>(option);
        if (optionNode) {
            auto hub = optionNode->GetEventHub<MenuItemEventHub>();
            auto optionPattern = optionNode->GetPattern<MenuItemPattern>();
            if (!hub || !optionPattern) {
                continue;
            }
            hub->SetOnSelect(std::move(selectCallback));
            optionNode->MarkModifyDone();
        }
    }
    auto context = dataListNode->GetContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    menu->GetOrCreateFocusHub()->SetFocusable(false);
    overlayManager->ShowMenu(dataListNode->GetId(), OffsetF(), menu);
}

void WebPattern::OnHideAutofillPopup()
{
    if (!isShowAutofillPopup_) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnHideAutofillPopup isShowAutofillPopup_ is null");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto id = host->GetId();
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->DeleteMenu(id);
    RemoveDataListNode();
    isShowAutofillPopup_ = false;
}

RefPtr<FrameNode> WebPattern::CreateDataListFrameNode(const OffsetF& offfset, const float height, const float width)
{
    RemoveDataListNode();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_RETURN(host, nullptr);
    dataListNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto dataListNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, dataListNodeId_.value(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_RETURN(dataListNode, nullptr);
    auto dataListRenderContext = dataListNode->GetRenderContext();
    CHECK_NULL_RETURN(dataListRenderContext, nullptr);
    auto dataListGesture = dataListNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(dataListGesture, nullptr);

    dataListNode->SetDraggable(false);
    dataListGesture->SetDragEvent(nullptr, { PanDirection::DOWN }, 0, Dimension(0));

    if (width <= 0 || height <= 0) {
        TAG_LOGI(AceLogTag::ACE_WEB, "CreateDataListFrameNode get size(%{public}f, %{public}f) error",
            width, height);
        return nullptr;
    }
    dataListRenderContext->UpdatePosition(
        OffsetT<Dimension>(Dimension(offfset.GetX()), Dimension(offfset.GetY() - height)));

    SizeF dataListSize;
    dataListSize.SetWidth(width);
    dataListSize.SetHeight(height / pipeline->GetDipScale());
    auto dataListProperty = dataListNode->GetLayoutProperty<ImageLayoutProperty>();
    dataListProperty->UpdateMarginSelfIdealSize(dataListSize);
    MeasureProperty layoutConstraint;
    CalcSize idealSize = { CalcLength(Dimension(dataListSize.Width(), DimensionUnit::VP).ConvertToPx()),
        CalcLength(Dimension(dataListSize.Height(), DimensionUnit::VP).ConvertToPx()) };
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    dataListNode->UpdateLayoutConstraint(layoutConstraint);
    host->AddChild(dataListNode);
    dataListNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    dataListNode->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
    return dataListNode;
}

void WebPattern::RemoveDataListNode()
{
    if (!dataListNodeId_.has_value()) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_WEB, "RemoveDataListNode");
    auto dataListNode = FrameNode::GetFrameNode(V2::IMAGE_ETS_TAG, dataListNodeId_.value());
    CHECK_NULL_VOID(dataListNode);
    auto context = dataListNode->GetContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->DeleteMenu(dataListNode->GetId());

    auto parent = dataListNode->GetParent();
    CHECK_NULL_VOID(parent);
    parent->RemoveChild(dataListNode);
    dataListNodeId_.reset();
    parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void WebPattern::CloseKeyboard()
{
    MenuAvoidKeyboard(true);
    InputMethodManager::GetInstance()->CloseKeyboard();
}

WebInfoType WebPattern::GetWebInfoType()
{
    std::string factoryLevel;
    if (delegate_) {
        factoryLevel = delegate_->GetWebInfoType();
    }
    if (factoryLevel == WEB_INFO_PHONE || factoryLevel == WEB_INFO_DEFAULT) {
        return WebInfoType::TYPE_MOBILE;
    } else if (factoryLevel == WEB_INFO_TABLET) {
        return WebInfoType::TYPE_TABLET;
    } else if (factoryLevel == WEB_INFO_PC) {
        return WebInfoType::TYPE_2IN1;
    }
    return WebInfoType::TYPE_UNKNOWN;
}

void WebPattern::JsonNodePutDefaultValue(std::unique_ptr<OHOS::Ace::JsonValue>& jsonNode,
    WebAccessibilityType key, bool value)
{
    if (!value) {
        return;
    }
    jsonNode->Put(EnumTypeToString(key).c_str(), 1);
}

void WebPattern::JsonNodePutDefaultValue(std::unique_ptr<OHOS::Ace::JsonValue>& jsonNode,
    WebAccessibilityType key, std::string value)
{
    if (value.empty()) {
        return;
    }
    jsonNode->Put(EnumTypeToString(key).c_str(), value.c_str());
}

void WebPattern::JsonNodePutDefaultValue(std::unique_ptr<OHOS::Ace::JsonValue>& jsonNode,
    WebAccessibilityType key, int32_t value, int32_t defaultValue)
{
    if (value == defaultValue) {
        return;
    }
    jsonNode->Put(EnumTypeToString(key).c_str(), value);
}

std::string WebPattern::EnumTypeToString(WebAccessibilityType type)
{
    return std::to_string(static_cast<int>(type));
}

std::string WebPattern::VectorIntToString(std::vector<int64_t>&& vec)
{
    std::string vecStr;
    uint32_t vecLen = vec.size();
    if (vecLen < 1) {
        return vecStr;
    }

    for (uint32_t i = 0; i < vecLen - 1; ++i) {
        vecStr += std::to_string(vec[i]) + " ";
    }
    return vecStr + std::to_string(vec[vecLen - 1]);
}

void WebPattern::WebNodeInfoToJsonValue(std::shared_ptr<OHOS::Ace::JsonValue>& jsonNodeArray,
    std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> webNodeInfo, std::string& nodeTag, bool isArray)
{
    auto jsonNode = JsonUtil::Create(true);
    jsonNode->Put(WEB_NODE_URL, delegate_ ? delegate_->GetUrl().c_str() : "");
    jsonNode->Put(EnumTypeToString(WebAccessibilityType::ID).c_str(), webNodeInfo->GetAccessibilityId());
    if (webNodeInfo->GetSelectionEnd() != 0) {
        jsonNode->Put(EnumTypeToString(WebAccessibilityType::SEL_START).c_str(), webNodeInfo->GetSelectionStart());
        jsonNode->Put(EnumTypeToString(WebAccessibilityType::SEL_END).c_str(), webNodeInfo->GetSelectionEnd());
    }
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::INPUT_TYPE, webNodeInfo->GetInputType(), -1);
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::LIVE_REGION, webNodeInfo->GetLiveRegion(), -1);
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::HINT, webNodeInfo->GetHint());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::CONTENT, webNodeInfo->GetContent());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::ERROR, webNodeInfo->GetError());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::CHILD_IDS, VectorIntToString(webNodeInfo->GetChildIds()));
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::PARENT_ID, webNodeInfo->GetParentId(), -1);
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::GRID_ROWS, webNodeInfo->GetGridRows(), -1);
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::GRID_COLS, webNodeInfo->GetGridColumns(), -1);
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::GRID_SEL_MODE, webNodeInfo->GetGridSelectedMode(), -1);
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::GRID_ITEM_ROW, webNodeInfo->GetGridItemRow(), -1);
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::GRID_ITEM_ROW_SPAN, webNodeInfo->GetGridItemRowSpan(), -1);
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::GRID_ITEM_COL, webNodeInfo->GetGridItemColumn(), -1);
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::GRID_ITEM_COL_SPAN,
        webNodeInfo->GetGridItemColumnSpan(), -1);
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::PAGE_ID, webNodeInfo->GetPageId(), -1);

    if (webNodeInfo->GetRectWidth() != 0 || webNodeInfo->GetRectHeight() != 0) {
        jsonNode->Put(EnumTypeToString(WebAccessibilityType::RECTX).c_str(), webNodeInfo->GetRectX());
        jsonNode->Put(EnumTypeToString(WebAccessibilityType::RECTY).c_str(), webNodeInfo->GetRectY());
        jsonNode->Put(EnumTypeToString(WebAccessibilityType::RECT_WIDTH).c_str(), webNodeInfo->GetRectWidth());
        jsonNode->Put(EnumTypeToString(WebAccessibilityType::RECT_HEIGHT).c_str(), webNodeInfo->GetRectHeight());
    }

    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::HEADING, webNodeInfo->GetIsHeading());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::CHECKED, webNodeInfo->GetIsChecked());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::EDITABLE, webNodeInfo->GetIsEditable());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::ENABLED, webNodeInfo->GetIsEnabled());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::FOCUSED, webNodeInfo->GetIsFocused());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::SELECTED, webNodeInfo->GetIsSelected());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::CHECKABLE, webNodeInfo->GetIsCheckable());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::CLICKABLE, webNodeInfo->GetIsClickable());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::FOCUSABLE, webNodeInfo->GetIsFocusable());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::SCROLLABLE, webNodeInfo->GetIsScrollable());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::PASSWORD, webNodeInfo->GetIsPassword());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::VISIBLE, webNodeInfo->GetIsVisible());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::PLURAL_LINE, webNodeInfo->GetIsPluralLineSupported());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::POPUP, webNodeInfo->GetIsPopupSupported());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::DELETABLE, webNodeInfo->GetIsDeletable());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::FOCUS, webNodeInfo->GetIsAccessibilityFocus());
    JsonNodePutDefaultValue(jsonNode, WebAccessibilityType::NODE_TAG, nodeTag);
    isArray ? jsonNodeArray->PutRef(std::move(jsonNode)) : jsonNodeArray->PutRef(nodeTag.c_str(), std::move(jsonNode));
}

void WebPattern::GetWebAllInfosImpl(WebNodeInfoCallback cb, int32_t webId, bool needFilter)
{
    CHECK_NULL_VOID(delegate_);
    std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> rootWebNode = delegate_->GetAccessibilityNodeInfoById(-1);
    CHECK_NULL_VOID(rootWebNode);

    auto jsonNodeArray =
        static_cast<std::shared_ptr<JsonValue>>(needFilter ? JsonUtil::Create(true) : JsonUtil::CreateArray(true));
    std::queue<uint64_t> que;
    for (auto id: rootWebNode->GetChildIds()) {
        que.push(id);
    }

    int nodeCount = 0;
    while (!que.empty()) {
        uint64_t tmp = que.front();
        que.pop();
        auto webNodeInfo = delegate_->GetAccessibilityNodeInfoById(tmp);
        CHECK_NULL_VOID(webNodeInfo);
        auto componentType = webNodeInfo->GetComponentType();
        if (needFilter) {
            if (componentType.compare(ACCESSIBILITY_GENERIC_CONTAINER) != 0
                && componentType.compare(ACCESSIBILITY_PARAGRAPH) != 0
                && componentType.compare(ACCESSIBILITY_IMAGE) != 0) {
                WebNodeInfoToJsonValue(jsonNodeArray, webNodeInfo, componentType);
            }
        } else {
            WebNodeInfoToJsonValue(jsonNodeArray, webNodeInfo, componentType, true);
        }
        for (auto id: webNodeInfo->GetChildIds()) {
            que.push(id);
        }
        nodeCount++;
    }
    TAG_LOGD(AceLogTag::ACE_WEB, "Current web info node count: %{public}d", nodeCount);
    cb(jsonNodeArray, webId);
    inspectorAccessibilityEnable_ = false;
    SetAccessibilityState(false);
}

void WebPattern::GetAllWebAccessibilityNodeInfos(WebNodeInfoCallback cb, int32_t webId, bool needFilter)
{
    CHECK_NULL_VOID(cb);
    inspectorAccessibilityEnable_ = true;
    SetAccessibilityState(true);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto taskExecutor = pipelineContext->GetTaskExecutor();
    taskExecutor->PostDelayedTask([weak = WeakClaim(this), cb, webId, needFilter] () {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto startTime = std::chrono::high_resolution_clock::now();
        pattern->GetWebAllInfosImpl(cb, webId, needFilter);
        auto nowTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> diff =
            std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - startTime);
        TAG_LOGD(AceLogTag::ACE_WEB, "GetAllAccessibilityInfo time cost: %{public}f", diff.count());
        },
        TaskExecutor::TaskType::UI, WEB_ACCESSIBILITY_DELAY_TIME, "GetAllWebAccessibilityNodeInfos");
}

void WebPattern::RegisterWebComponentClickCallback(WebComponentClickCallback&& callback)
{
    CHECK_NULL_VOID(callback);
    webComponentClickCallback_ = std::move(callback);
    textBlurAccessibilityEnable_ = true;
    SetAccessibilityState(true);
}

void WebPattern::UnregisterWebComponentClickCallback()
{
    webComponentClickCallback_ = nullptr;
    textBlurAccessibilityEnable_ = false;
    SetAccessibilityState(false);
}

void WebPattern::RequestFocus()
{
    WebRequestFocus();
}

bool WebPattern::IsCurrentFocus()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto eventHub = host->GetEventHub<WebEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, false);

    return focusHub->IsCurrentFocus();
}

void WebPattern::OnRebuildFrame()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    CHECK_NULL_VOID(renderContextForSurface_);
    renderContext->AddChild(renderContextForSurface_, 0);
    CHECK_NULL_VOID(renderContextForPopupSurface_);
    if (SystemProperties::GetDeviceType() == DeviceType::TWO_IN_ONE) {
        renderContext->AddChild(renderContextForPopupSurface_, 1);
    }
}

void WebPattern::CreateOverlay(const RefPtr<OHOS::Ace::PixelMap>& pixelMap, int offsetX, int offsetY, int rectWidth,
    int rectHeight, int pointX, int pointY)
{
    if (!imageAnalyzerManager_) {
        imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(GetHost(), ImageAnalyzerHolder::WEB);
    }
    TAG_LOGI(AceLogTag::ACE_WEB,
        "CreateOverlay, offsetX=%{public}d, offsetY=%{public}d, width=%{public}d, height=%{public}d", offsetX, offsetY,
        rectWidth, rectHeight);
    auto callback = [weak = AceType::WeakClaim(this)]() {
        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->OnTextSelected();
    };
    imageAnalyzerManager_->DestroyAnalyzerOverlay();
    awaitingOnTextSelected_ = true;
    auto selectedTask = [weak = AceType::WeakClaim(this)](bool isSelected) {
        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::CreateOverlay selectedTask=%{public}d", isSelected);
        webPattern->SetImageOverlaySelectedStatus(isSelected);
        if (isSelected) {
            webPattern->CloseSelectOverlay();
            webPattern->SelectCancel();
            webPattern->OnTextSelected();
            CHECK_NULL_VOID(webPattern->delegate_);
            webPattern->delegate_->OnContextMenuHide("");
        }
    };
    imageAnalyzerManager_->SetNotifySelectedCallback(std::move(selectedTask));
    imageAnalyzerManager_->UpdatePressOverlay(
        pixelMap, offsetX, offsetY, rectWidth, rectHeight, pointX, pointY, std::move(callback));
    imageAnalyzerManager_->CreateAnalyzerOverlay(nullptr);
}

void WebPattern::OnOverlayStateChanged(int offsetX, int offsetY, int rectWidth, int rectHeight)
{
    if (imageAnalyzerManager_) {
        TAG_LOGI(AceLogTag::ACE_WEB,
            "OnOverlayStateChanged, offsetX=%{public}d, offsetY=%{public}d, width=%{public}d, height=%{public}d",
            offsetX, offsetY, rectWidth, rectHeight);
        if (!rectWidth || !rectHeight) {
            TAG_LOGE(AceLogTag::ACE_WEB, "OnOverlayStateChanged failed: rect is empty, begin to destroy overlay");
            DestroyAnalyzerOverlay();
            return;
        }
        imageAnalyzerManager_->UpdateOverlayStatus(true, offsetX, offsetY, rectWidth, rectHeight);
    }
}

void WebPattern::OnTextSelected()
{
    if (!awaitingOnTextSelected_) {
        TAG_LOGD(AceLogTag::ACE_WEB, "OnTextSelected already called, ignored.");
        return;
    }
    awaitingOnTextSelected_ = false;
    CHECK_NULL_VOID(delegate_);
    delegate_->OnTextSelected();
    overlayCreating_ = true;
}

void WebPattern::DestroyAnalyzerOverlay()
{
    if (imageAnalyzerManager_ && imageAnalyzerManager_->IsOverlayCreated()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::DestroyAnalyzerOverlay");
        imageAnalyzerManager_->DestroyAnalyzerOverlay();
        delegate_->OnDestroyImageAnalyzerOverlay();
    }
    overlayCreating_ = false;
    imageOverlayIsSelected_ = false;
    awaitingOnTextSelected_ = false;
}

void WebPattern::OnAccessibilityHoverEvent(
    const NG::PointF& point, SourceType source, NG::AccessibilityHoverEventType eventType, TimeStamp time)
{
    CHECK_NULL_VOID(delegate_);
    delegate_->HandleAccessibilityHoverEvent(point, source, eventType, time);
}

std::string WebPattern::GetSurfaceIdByHtmlElementId(const std::string& htmlElementId)
{
    CHECK_NULL_RETURN(delegate_, "");
    return delegate_->GetSurfaceIdByHtmlElementId(htmlElementId);
}

int64_t WebPattern::GetWebAccessibilityIdBySurfaceId(const std::string& surfaceId)
{
    CHECK_NULL_RETURN(delegate_, -1);
    return delegate_->GetWebAccessibilityIdBySurfaceId(surfaceId);
}

void WebPattern::InitMagnifier()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "InitMagnifier");
    if (!magnifierController_) {
        magnifierController_ = MakeRefPtr<MagnifierController>(WeakClaim(this));
    }
}

void WebPattern::InitializeAccessibility()
{
    ContainerScope scope(instanceId_);
    if (accessibilityChildTreeCallback_.find(instanceId_) != accessibilityChildTreeCallback_.end()) {
        return;
    }
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    int64_t accessibilityId = frameNode->GetAccessibilityId();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityChildTreeCallback_[instanceId_] = std::make_shared<WebAccessibilityChildTreeCallback>(
        WeakClaim(this), frameNode->GetAccessibilityId());
    accessibilityManager->RegisterAccessibilityChildTreeCallback(accessibilityId,
        accessibilityChildTreeCallback_[instanceId_]);
    if (accessibilityManager->IsRegister()) {
        accessibilityChildTreeCallback_[instanceId_]->SetIsDelayed(true);
        accessibilityChildTreeCallback_[instanceId_]->OnRegister(pipeline->GetWindowId(),
            accessibilityManager->GetTreeId());
    }
}

void WebPattern::UninitializeAccessibility()
{
    ContainerScope scope(instanceId_);
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    int64_t accessibilityId = frameNode->GetAccessibilityId();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    if (accessibilityManager->IsRegister()) {
        if (accessibilityChildTreeCallback_.find(instanceId_) == accessibilityChildTreeCallback_.end() ||
            accessibilityChildTreeCallback_[instanceId_] == nullptr) {
            return;
        }
        accessibilityChildTreeCallback_[instanceId_]->OnDeregister();
    }
    accessibilityManager->DeregisterAccessibilityChildTreeCallback(accessibilityId);
    accessibilityChildTreeCallback_.erase(instanceId_);
}

void WebPattern::OnSetAccessibilityChildTree(int32_t childWindowId, int32_t childTreeId)
{
    treeId_ = childTreeId;
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    if (accessibilityProperty != nullptr) {
        accessibilityProperty->SetChildWindowId(childWindowId);
        accessibilityProperty->SetChildTreeId(childTreeId);
    }
}

bool WebPattern::OnAccessibilityChildTreeRegister()
{
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_RETURN(accessibilityManager, false);
    if (accessibilitySessionAdapter_ == nullptr) {
        accessibilitySessionAdapter_ = AceType::MakeRefPtr<WebAccessibilitySessionAdapter>(WeakClaim(this));
    }
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    int64_t accessibilityId = frameNode->GetAccessibilityId();
    return accessibilityManager->RegisterWebInteractionOperationAsChildTree(accessibilityId, WeakClaim(this));
}

bool WebPattern::OnAccessibilityChildTreeDeregister()
{
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_RETURN(accessibilityManager, false);
    if (treeId_ == 0) {
        TAG_LOGD(AceLogTag::ACE_WEB, "OnAccessibilityChildTreeDeregister: treeId is 0.");
        return false;
    }
    return accessibilityManager->DeregisterWebInteractionOperationAsChildTree(treeId_, WeakClaim(this));
}

bool WebPattern::GetActiveStatus() const
{
    return isActive_;
}

int32_t WebPattern::GetBufferSizeByDeviceType()
{
    return (SystemProperties::GetDeviceType() == DeviceType::PHONE ||
        SystemProperties::GetDeviceType() == DeviceType::TWO_IN_ONE) ?
        ASYNC_SURFACE_QUEUE_SIZE_FOR_PHONE_AND_PC : ASYNC_SURFACE_QUEUE_SIZE_FOR_OTHERS;
}

void WebPattern::StartVibraFeedback(const std::string& vibratorType)
{
    if (isEnabledHapticFeedback_) {
        NG::VibratorUtils::StartVibraFeedback(vibratorType);
    }
}

void WebPattern::UpdateTouchpadSlidingStatus(const GestureEvent& event)
{
    isTouchpadSliding_ = false;
    if ((event.GetInputEventType() == InputEventType::AXIS) &&
        (event.GetSourceTool() == SourceTool::TOUCHPAD)) {
        isTouchpadSliding_ = true;
    }
}

bool WebPattern::CloseImageOverlaySelection()
{
    if (imageOverlayIsSelected_) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::CloseImageOverlaySelection");
        DestroyAnalyzerOverlay();
        return true;
    }
    return false;
}

void WebPattern::SetDrawSize(double width, double height)
{
    drawSize_.SetWidth(width);
    drawSize_.SetHeight(height);
}

void WebPattern::OnParentScrollDragEndRecursive(RefPtr<NestableScrollContainer> parent)
{
    if (isDragEnd_) {
        return;
    }
    if (parent) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnParentScrollDragEndRecursive");
        parent->OnScrollDragEndRecursive();
    }
    isDragEnd_ = true;
}

bool WebPattern::GetAccessibilityVisible(int64_t accessibilityId)
{
    if (delegate_) {
        return delegate_->GetAccessibilityVisible(accessibilityId);
    }
    return true;
}

void WebPattern::DumpInfo()
{
    DumpSurfaceInfo();
    DumpGpuInfo();
}

void WebPattern::DumpGpuInfo()
{
    float totalSize = 0.0f;
    if (delegate_ != nullptr && delegate_->GetNweb() != nullptr) {
        totalSize = delegate_->GetNweb()->DumpGpuInfo();
    }
    if (totalSize > GPU_SERIOUS_ABNORMAL_VALUE) {
        totalSize /= SIZE_UNIT * SIZE_UNIT; // 转换成MB
    } else if (totalSize > GPU_ABNORMAL_VALUE) {
        totalSize /= SIZE_UNIT;
    }
    totalSize = std::round(totalSize * FLOAT_UNIT) / FLOAT_UNIT; // 变为浮点数
    // 使用ostringstream来格式化数字为字符串
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(DECIMAL_POINTS) << totalSize; // 转换成保留两位小数的字符串
    std::string formattedSize = oss.str();                               // 获取格式化后的字符串
    DumpLog::GetInstance().AddDesc("------------GpuMemoryInfo-----------");
    DumpLog::GetInstance().AddDesc("Total Gpu Memory size: " + formattedSize + "(MB)");
}

void WebPattern::DumpSurfaceInfo()
{
    if (renderSurface_ != nullptr) {
        DumpLog::GetInstance().AddDesc(std::string("surfaceId: ").append(renderSurface_->GetUniqueId()));
    }
}

RefPtr<WebEventHub> WebPattern::GetWebEventHub()
{
    return GetEventHub<WebEventHub>();
}

RefPtr<AccessibilitySessionAdapter> WebPattern::GetAccessibilitySessionAdapter()
{
    return accessibilitySessionAdapter_;
}

void WebPattern::OnOptimizeParserBudgetEnabledUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateOptimizeParserBudgetEnabled(value);
    }
}

void WebPattern::OnWebMediaAVSessionEnabledUpdate(bool enable)
{
    if (delegate_) {
        delegate_->UpdateWebMediaAVSessionEnabled(enable);
    }
}

void WebPattern::OnEnableDataDetectorUpdate(bool enable)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnEnableDataDetectorUpdate enable:%{public}d", enable);
    auto adapter = GetDataDetectorAdapter();
    CHECK_NULL_VOID(adapter);
    adapter->SetDataDetectorEnable(enable);
}

void WebPattern::PushOverlayInfo(float x, float y, int32_t id)
{
    TouchInfo touchPoint;
    touchPoint.id = id;
    touchPoint.x = x;
    touchPoint.y = y;
    touchOverlayInfo_.push_back(touchPoint);
}

void WebPattern::UpdateImageOverlayTouchInfo(int touchPointX, int touchPointY, TouchType touchType)
{
    if (overlayCreating_) {
        imageAnalyzerManager_->UpdateOverlayTouchInfo(touchPointX, touchPointY, TouchType::DOWN);
    }
}

void WebPattern::WebOverlayRequestFocus()
{
    if (!GetNativeEmbedModeEnabledValue(false)) {
        WebRequestFocus();
    }
}

std::string WebPattern::GetCurrentLanguage()
{
    std::string result = "";
    if (delegate_) {
        result = delegate_->GetCurrentLanguage();
    }
    return result;
}

void WebPattern::OnEnableFollowSystemFontWeightUpdate(bool value)
{
    if (delegate_) {
        delegate_->UpdateEnableFollowSystemFontWeight(value);
    }
}

void WebPattern::GetTranslateTextCallback(const std::string& result)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "GetTranslateTextCallback WebId:%{public}d | Text.length:%{public}d",
        GetWebId(), static_cast<int32_t>(result.size()));
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto id = frameNode->GetId();
    UiSessionManager::GetInstance()->SendWebTextToAI(id, result);
#endif
}

void WebPattern::RegisterTranslateTextJavaScript()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "RegisterTranslateTextJavaScript WebId:%{public}d", GetWebId());
    std::vector<std::string> methods;
    methods.push_back(g_translateTextData.registerFunctionName);
    auto lambda = [weak = AceType::WeakClaim(this)](const std::vector<std::string>& param) {
        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        if (webPattern && param.size() > 0) {
            webPattern->GetTranslateTextCallback(param[0]);
        }
    };
    std::vector<std::function<void(const std::vector<std::string>&)>> funcs;
    funcs.push_back(std::move(lambda));
    std::string permission = "";
    CHECK_NULL_VOID(delegate_);
    delegate_->RegisterNativeJavaScriptProxy(g_translateTextData.registerObjectName,
        methods, funcs, false, permission, true);
}

void WebPattern::RunJsInit()
{
    if (!g_translateTextData.needTranslate) {
        return;
    }
    if (!isRegisterJsObject_) {
        isRegisterJsObject_ = true;
        RegisterTranslateTextJavaScript();
        return;
    }
    TAG_LOGI(AceLogTag::ACE_WEB, "run java TranslateScript and InitScript. WebId:%{public}d", GetWebId());
    CHECK_NULL_VOID(delegate_);
    delegate_->ExecuteTypeScript(g_translateTextData.translateScript, [](std::string result) {});
    delegate_->ExecuteTypeScript(g_translateTextData.initScript, [](std::string result) {});
}

void WebPattern::GetTranslateText(std::string extraData, std::function<void(std::string)> callback, bool isContinued)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask([weak = AceType::WeakClaim(this), jsonData = extraData]() {
        std::unique_ptr<JsonValue> json = JsonUtil::ParseJsonString(jsonData);
        CHECK_NULL_VOID(json);
        g_translateTextData.registerObjectName = json->GetString("registerObjectName");
        g_translateTextData.registerFunctionName = json->GetString("registerFunctionName");
        g_translateTextData.translateScript = json->GetString("translateScript");
        g_translateTextData.initScript = json->GetString("initScript");

        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        TAG_LOGI(AceLogTag::ACE_WEB, "GetTranslateText WebId:%{public}d", webPattern->GetWebId());
        TAG_LOGI(AceLogTag::ACE_WEB,
            "GetTranslateText 'registerObjectName':%{public}s; 'registerFunctionName':%{public}s",
            g_translateTextData.registerObjectName.c_str(), g_translateTextData.registerFunctionName.c_str());
        g_translateTextData.needTranslate = true;
        webPattern->RunJsInit();
        }, TaskExecutor::TaskType::UI, "ArkUIWebGetTranslateText");
}

void WebPattern::SendTranslateResult(std::vector<std::string> results, std::vector<int32_t> ids)
{
    return;
}

void WebPattern::SendTranslateResult(std::string jscode)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "SendTranslateResult WebId:%{public}d; Text.length:%{public}d",
        GetWebId(), static_cast<int32_t>(jscode.size()));
    CHECK_NULL_VOID(delegate_);
    delegate_->ExecuteTypeScript(jscode, [](std::string result) {});
}

void WebPattern::EndTranslate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask([weak = AceType::WeakClaim(this)]() {
        g_translateTextData.needTranslate = false;
        g_translateTextData.translateScript = "";
        g_translateTextData.initScript = "";
        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        if (webPattern->isRegisterJsObject_) {
            CHECK_NULL_VOID(webPattern->delegate_);
            std::string p = g_translateTextData.registerObjectName;
            TAG_LOGI(AceLogTag::ACE_WEB, "UnRegister TranslateText JsObject %{public}s", p.c_str());
            webPattern->delegate_->UnRegisterNativeArkJSFunction(std::move(p));
            webPattern->isRegisterJsObject_ = false;
            webPattern->delegate_->Reload();
        }
        TAG_LOGI(AceLogTag::ACE_WEB, "EndTranslateText WebId:%{public}d", webPattern->GetWebId());
        }, TaskExecutor::TaskType::UI, "ArkUIWebEndTranslate");
}

void WebPattern::InitRotationEventCallback()
{
    if (rotationEndCallbackId_ != 0) {
        return;
    }

    TAG_LOGD(AceLogTag::ACE_WEB, "WebPattern::InitRotationEventCallback");

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    rotationEndCallbackId_ = context->RegisterRotationEndCallback(
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->RecoverToTopLeft();
        }
    );
}

void WebPattern::UninitRotationEventCallback()
{
    TAG_LOGD(AceLogTag::ACE_WEB, "WebPattern::UninitRotationEventCallback");

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->UnregisterRotationEndCallback(rotationEndCallbackId_);
    rotationEndCallbackId_ = 0;
}

void WebPattern::AdjustRotationRenderFit(WindowSizeChangeReason type)
{
    if (type != WindowSizeChangeReason::ROTATION) {
        return;
    }
    if (!isAttachedToMainTree_ || !isVisible_) {
        TAG_LOGD(AceLogTag::ACE_WEB, "WebPattern::AdjustRotationRenderFit not support");
        return;
    }

    if (delegate_) {
        delegate_->MaximizeResize();
    }

    bool isNwebEx = delegate_->IsNWebEx();
    TAG_LOGD(AceLogTag::ACE_WEB, "WebPattern::AdjustRotationRenderFit, isNwebEx: %{public}d", isNwebEx);
    if (isNwebEx && SystemProperties::GetDeviceType() == DeviceType::TWO_IN_ONE &&
        renderMode_ == RenderMode::ASYNC_RENDER) {
        isRotating_ = true;
        TAG_LOGD(AceLogTag::ACE_WEB, "WebPattern::AdjustRotationRenderFit, webId: %{public}d", GetWebId());
        if (renderContextForSurface_) {
            renderContextForSurface_->SetRenderFit(RenderFit::RESIZE_FILL);
        }

        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pipelineContext = host->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        auto taskExecutor = pipelineContext->GetTaskExecutor();

        std::string taskName = "ArkUIWebRotationDelayTask_" + std::to_string(GetWebId());
        taskExecutor->RemoveTask(TaskExecutor::TaskType::UI, taskName);
        taskExecutor->PostDelayedTask(
            [weak = WeakClaim(this), taskName]() {
            auto webPattern = weak.Upgrade();
            CHECK_NULL_VOID(webPattern);
            TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::RestoreRenderFit DelayedTask, task: %{public}s",
                taskName.c_str());
            webPattern->isRotating_ = false;
            if (webPattern->renderContextForSurface_) {
                webPattern->renderContextForSurface_->SetRenderFit(RenderFit::TOP_LEFT);
            }
            }, TaskExecutor::TaskType::UI, MAXIMUM_ROTATION_DELAY_TIME, taskName);
    }
}

void WebPattern::RecoverToTopLeft()
{
    if (!isRotating_) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::RecoverToTopLeft, webId: %{public}d", GetWebId());
    isRotating_ = false;
    if (renderContextForSurface_) {
        renderContextForSurface_->SetRenderFit(RenderFit::TOP_LEFT);
    }
}

RefPtr<WebAccessibilityEventReport> WebPattern::GetAccessibilityEventReport()
{
    if (!webAccessibilityEventReport_) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::GetAccessibilityEventReport, create new report instance");
        webAccessibilityEventReport_ = AceType::MakeRefPtr<WebAccessibilityEventReport>(WeakClaim(this));
    }
    return webAccessibilityEventReport_;
}

void WebPattern::InitInputEventReportCallback()
{
    if (UiSessionManager::GetInstance()->GetWebFocusRegistered()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::InitInputEventReportCallback, register event report callback");
        auto report = GetAccessibilityEventReport();
        CHECK_NULL_VOID(report);
        report->SetIsFirstRegister(true);
        report->RegisterAllReportEventCallback();
    } else if (webAccessibilityEventReport_) {
        TAG_LOGE(AceLogTag::ACE_WEB, "WebPattern::InitInputEventReportCallback, unregister event report callback");
        webAccessibilityEventReport_->UnregisterCallback();
    }
}

void WebPattern::SetTextEventAccessibilityEnable(bool enable)
{
    textBlurAccessibilityEnable_ = enable;
}

bool WebPattern::IsAccessibilityUsedByEventReport()
{
    if (webAccessibilityEventReport_) {
        return webAccessibilityEventReport_->GetEventReportEnable();
    }
    return false;
}

RefPtr<WebDataDetectorAdapter> WebPattern::GetDataDetectorAdapter()
{
    if (!webDataDetectorAdapter_) {
        webDataDetectorAdapter_ = AceType::MakeRefPtr<WebDataDetectorAdapter>(WeakClaim(this));
    }
    return webDataDetectorAdapter_;
}

bool WebPattern::GetDataDetectorEnable()
{
    if (!webDataDetectorAdapter_) {
        return false;
    }
    return webDataDetectorAdapter_->GetDataDetectorEnable();
}

void WebPattern::InitDataDetector()
{
    CHECK_NULL_VOID(webDataDetectorAdapter_);
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::InitDataDetector");
    webDataDetectorAdapter_->Init();
}

void WebPattern::InitAIDetectResult()
{
    if (!textDetectResult_.menuOptionAndAction.empty()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    TAG_LOGI(AceLogTag::ACE_WEB, "Web InitAIDetectResult");
    uiTaskExecutor.PostTask(
        [weak = AceType::WeakClaim(this), instanceId = context->GetInstanceId()] {
            ContainerScope scope(instanceId);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            TAG_LOGI(AceLogTag::ACE_WEB, "Get AI entity menu from ai_engine");
            DataDetectorMgr::GetInstance().GetAIEntityMenu(pattern->textDetectResult_);
        },
        "ArkUITextInitDataDetect");
}

void WebPattern::CloseDataDetectorMenu()
{
    CHECK_NULL_VOID(webDataDetectorAdapter_);
    webDataDetectorAdapter_->CloseAIMenu();
}

bool WebPattern::MenuAvoidKeyboard(bool hideOrClose, double height)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, false);
    auto keyboardInset = safeAreaManager->GetKeyboardWebInset();
    if (hideOrClose) {
        auto newBottom = std::optional<uint32_t>(keyboardInset.end);
        safeAreaManager->UpdateKeyboardWebSafeArea(0, newBottom);
        safeAreaManager->SetKeyboardInsetImpl(std::function<SafeAreaInsets::Inset(SafeAreaManager *)>());
    } else {
        safeAreaManager->UpdateKeyboardWebSafeArea(height);
        safeAreaManager->SetKeyboardInsetImpl([](SafeAreaManager* manager) {
            CHECK_NULL_RETURN(manager, SafeAreaInsets::Inset());
            return manager->GetKeyboardWebInset();
        });
    }
    return true;
}

void WebPattern::OnPip(int status,
    int delegateId, int childId, int frameRoutingId, int width, int height)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnPip status:%{public}d", status);
    Pip(status,  delegateId, childId, frameRoutingId, width, height);
}

void WebPattern::SetPipNativeWindow(int delegateId, int childId, int frameRoutingId, void* window)
{
    if (delegate_) {
        delegate_->SetPipNativeWindow(delegateId, childId, frameRoutingId, window);
    }
}

void WebPattern::SendPipEvent(int delegateId, int childId, int frameRoutingId, int event)
{
    if (delegate_) {
        delegate_->SendPipEvent(delegateId, childId, frameRoutingId, event);
    }
}

bool WebPattern::CheckVisible()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);

    if (!host->IsActive() || !host->IsVisible()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::CheckVisible host is inactive or invisible");
        return false;
    }

    auto parent = host->GetAncestorNodeOfFrame(true);
    while (parent) {
        if (parent->IsWindowBoundary()) {
            TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::CheckVisible IsWindowBoundary is true");
            return true;
        }
        if (!parent->IsActive() || !parent->IsVisible()) {
            TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::CheckVisible parent is inactive or invisible");
            return false;
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return true;
}

bool WebPattern::Pip(int status,
    int delegateId, int childId, int frameRoutingId, int width, int height)
{
    bool result = false;
    uint32_t pipController = 0;
    bool init = false;
    switch (status) {
        case PIP_STATE_ENTER:
        case PIP_STATE_HLS_ENTER: {
            napi_env env = CreateEnv();
            CHECK_NULL_RETURN(env, false);
            PipInfo pipInfo{windowId_, delegateId, childId,
                            frameRoutingId, width, height};
            result = CreatePip(status, env, init, pipController, pipInfo);
            WEB_CHECK_FALSE_RETURN(result, false);
            if (!init) {
                result = RegisterPip(pipController);
                WEB_CHECK_FALSE_RETURN(result, false);
            }
            result = StartPip(pipController);
            if (result) {
                if (!init) {
                    EnablePip(pipController);
                }
            }
            break;
        }
        case PIP_STATE_EXIT:
        case PIP_STATE_HLS_EXIT: {
            result = StopPip(delegateId, childId, frameRoutingId);
            break;
        }
        case PIP_STATE_PAGE_CLOSE: {
            result = PageClosePip(delegateId, childId, frameRoutingId);
            break;
        }
        case PIP_STATE_PLAY: {
            result = PlayPip(delegateId, childId, frameRoutingId);
            break;
        }
        case PIP_STATE_PAUSE: {
            result = PausePip(delegateId, childId, frameRoutingId);
            break;
        }
        default:
            TAG_LOGE(AceLogTag::ACE_WEB, "Pip status:%{public}d", status);
    }
    return result;
}

bool WebPattern::CreatePip(int status, napi_env env, bool& init, uint32_t &pipController,
    const PipInfo &pipInfo)
{
    {
        std::lock_guard<std::mutex> lock(pipCallbackMapMutex_);
        for (auto &it : pipCallbackMap_) {
            auto pip = it.second;
            if (pip.delegateId == pipInfo.delegateId && pip.childId == pipInfo.childId &&
                pip.frameRoutingId == pipInfo.frameRoutingId && pip.mainWindowId == windowId_) {
                pipController = it.first;
                init = true;
                return true;
            }
        }
    }
    PictureInPicture_PipTemplateType pipTemplateType = PictureInPicture_PipTemplateType::VIDEO_PLAY;
    PictureInPicture_PipControlGroup controlGroup[1] = {
        PictureInPicture_PipControlGroup::VIDEO_PLAY_FAST_FORWARD_BACKWARD
    };
    uint8_t controlGroupLength = 0;
    if (status == PIP_STATE_ENTER) {
        controlGroupLength = 1;
    }
    PictureInPicture_PipConfig pipConfig;
    OH_PictureInPicture_CreatePipConfig(&pipConfig);
    OH_PictureInPicture_SetPipMainWindowId(pipConfig, pipInfo.mainWindowId);
    OH_PictureInPicture_SetPipTemplateType(pipConfig, pipTemplateType);
    OH_PictureInPicture_SetPipRect(pipConfig, pipInfo.width, pipInfo.height);
    OH_PictureInPicture_SetPipControlGroup(pipConfig, controlGroup, controlGroupLength);
    OH_PictureInPicture_SetPipNapiEnv(pipConfig, env);
    auto errCode = OH_PictureInPicture_CreatePip(pipConfig, &pipController);
    if (errCode != 0) {
        OH_PictureInPicture_DestroyPipConfig(&pipConfig);
        return false;
    }
    OH_PictureInPicture_DestroyPipConfig(&pipConfig);
    struct PipData pipData;
    pipData.pipWebPattern = AceType::WeakClaim(this);
    pipData.delegateId = pipInfo.delegateId;
    pipData.childId = pipInfo.childId;
    pipData.mainWindowId = pipInfo.mainWindowId;
    pipData.frameRoutingId = pipInfo.frameRoutingId;
    {
        std::lock_guard<std::mutex> lock(pipCallbackMapMutex_);
        g_currentControllerId = pipController;
        pipCallbackMap_.erase(pipController);
        pipCallbackMap_.insert(std::make_pair(pipController, pipData));
        pipController_.push_back(pipController);
    }
    return true;
}

napi_env WebPattern::CreateEnv()
{
    auto engine = EngineHelper::GetCurrentEngine();
    if (!engine) {
        TAG_LOGE(AceLogTag::ACE_WEB, "Engine is null");
        return nullptr;
    }

    NativeEngine* nativeEngine = engine->GetNativeEngine();
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    if (env == nullptr) {
        TAG_LOGE(AceLogTag::ACE_WEB, "NativeEngine is null");
        return nullptr;
    }
    return env;
}

bool WebPattern::RegisterPip(uint32_t pipController)
{
    auto errCode = OH_PictureInPicture_RegisterStartPipCallback(pipController, PipStartPipCallback);
    if (errCode != 0) {
        TAG_LOGE(AceLogTag::ACE_WEB, "RegisterStartPipCallback err:%{public}d", errCode);
        return false;
    }
    errCode = OH_PictureInPicture_RegisterLifecycleListener(pipController, PipLifecycleCallback);
    if (errCode != 0) {
        TAG_LOGE(AceLogTag::ACE_WEB, "RegisterLifecycleListener err:%{public}d", errCode);
        return false;
    }
    errCode = OH_PictureInPicture_RegisterControlEventListener(pipController, PipControlEventCallback);
    if (errCode != 0) {
        TAG_LOGE(AceLogTag::ACE_WEB, "RegisterControlEventListener err:%{public}d", errCode);
        return false;
    }
    errCode = OH_PictureInPicture_RegisterResizeListener(pipController, PipResizeCallback);
    if (errCode != 0) {
        TAG_LOGE(AceLogTag::ACE_WEB, "RegisterResizeListener err:%{public}d", errCode);
        return false;
    }
    return true;
}

bool WebPattern::StartPip(uint32_t pipController)
{
    auto errCode = OH_PictureInPicture_StartPip(pipController);
    if (errCode != 0) {
        TAG_LOGE(AceLogTag::ACE_WEB, "OH_PictureInPicture_StartPip err: %{public}d", errCode);
        if (errCode == WINDOW_MANAGER_ERRORCODE_PIP_CREATE_FAILED) {
            std::lock_guard<std::mutex> lock(pipCallbackMapMutex_);
            for (auto &it : pipCallbackMap_) {
                auto pip = it.second;
                SendPipEvent(pip.delegateId, pip.childId, pip.frameRoutingId, PIP_STATE_EXIT);
            }
        }
        return false;
    }
    {
        std::lock_guard<std::mutex> lock(pipCallbackMapMutex_);
        g_currentControllerId = pipController;
    }
    return true;
}

void WebPattern::EnablePip(uint32_t pipController)
{
    OH_PictureInPicture_UpdatePipControlStatus(
        pipController, PictureInPicture_PipControlType::VIDEO_PLAY_PAUSE,
        PictureInPicture_PipControlStatus::PLAY);
    OH_PictureInPicture_SetPipControlEnabled(
        pipController, PictureInPicture_PipControlType::VIDEO_PLAY_PAUSE, true);
    OH_PictureInPicture_SetPipControlEnabled(
        pipController, PictureInPicture_PipControlType::FAST_FORWARD, true);
    OH_PictureInPicture_SetPipControlEnabled(
        pipController, PictureInPicture_PipControlType::FAST_BACKWARD, true);
}

bool WebPattern::StopPip(int delegateId, int childId, int frameRoutingId)
{
    std::lock_guard<std::mutex> lock(pipCallbackMapMutex_);
    for (auto &it : pipCallbackMap_) {
        auto pip = it.second;
        if (pip.delegateId == delegateId && pip.childId == childId &&
            pip.frameRoutingId == frameRoutingId) {
            bool result = true;
            auto errCode = OH_PictureInPicture_StopPip(it.first);
            if (errCode != 0) {
                TAG_LOGE(AceLogTag::ACE_WEB, "OH_PictureInPicture_StopPip err: %{public}d", errCode);
                result = false;
            }
            if (g_currentControllerId != it.first) {
                g_currentControllerIdStop = true;
                auto errCode = OH_PictureInPicture_StopPip(g_currentControllerId);
                CHECK_NE_RETURN(errCode, 0, false);
            }
            return result;
        }
    }
    return false;
}

bool WebPattern::PageClosePip(int delegateId, int childId, int frameRoutingId)
{
    std::lock_guard<std::mutex> lock(pipCallbackMapMutex_);
    for (auto &it : pipCallbackMap_) {
        auto pip = it.second;
        if (pip.delegateId == delegateId && pip.childId == childId &&
            pip.frameRoutingId == frameRoutingId) {
            auto errCode = OH_PictureInPicture_StopPip(it.first);
            if (errCode != 0) {
                TAG_LOGE(AceLogTag::ACE_WEB, "OH_PictureInPicture_StopPip err: %{public}d", errCode);
            }
            return errCode == 0;
        }
    }
    return false;
}

bool WebPattern::PlayPip(int delegateId, int childId, int frameRoutingId)
{
    bool flag = false;
    std::lock_guard<std::mutex> lock(pipCallbackMapMutex_);
    for (auto &it : pipCallbackMap_) {
        auto pip = it.second;
        if (pip.delegateId == delegateId && pip.childId == childId &&
            pip.frameRoutingId == frameRoutingId) {
            flag = true;
            OH_PictureInPicture_UpdatePipControlStatus(it.first,
                PictureInPicture_PipControlType::VIDEO_PLAY_PAUSE,
                PictureInPicture_PipControlStatus::PLAY);
        }
    }
    if (!flag) {
        TAG_LOGE(AceLogTag::ACE_WEB, "PlayPip id no match "
            "delegateId:%{public}d, childId:%{public}d frameRoutingId:%{public}d",
            delegateId, childId, frameRoutingId);
        return false;
    }
    return true;
}

bool WebPattern::PausePip(int delegateId, int childId, int frameRoutingId)
{
    bool flag = false;
    std::lock_guard<std::mutex> lock(pipCallbackMapMutex_);
    for (auto &it : pipCallbackMap_) {
        auto pip = it.second;
        if (pip.delegateId == delegateId && pip.childId == childId &&
            pip.frameRoutingId == frameRoutingId) {
            flag = true;
            OH_PictureInPicture_UpdatePipControlStatus(it.first,
                PictureInPicture_PipControlType::VIDEO_PLAY_PAUSE,
                PictureInPicture_PipControlStatus::PAUSE);
        }
    }
    if (!flag) {
        TAG_LOGE(AceLogTag::ACE_WEB, "PausePip id no match "
            "delegateId:%{public}d, childId:%{public}d frameRoutingId:%{public}d",
            delegateId, childId, frameRoutingId);
        return false;
    }
    return true;
}

void WebPattern::OnBypassVsyncConditionUpdate(WebBypassVsyncCondition condition)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebPattern::OnBypassVsyncConditionUpdate condition:%{public}d", condition);
    webBypassVsyncCondition_ = condition;
    if (delegate_) {
        delegate_->UpdateBypassVsyncCondition(condition);
    }
}

void WebPattern::SetDefaultBackgroundColor()
{
    needSetDefaultBackgroundColor_ = true;
}

void WebPattern::OnGestureFocusModeUpdate(GestureFocusMode mode)
{
    gestureFocusMode_ = mode;
    if (delegate_) {
        delegate_->UpdateGestureFocusMode(mode);
    }
}

void WebPattern::UpdateSingleHandleVisible(bool isVisible)
{
    if (delegate_) {
        delegate_->UpdateSingleHandleVisible(isVisible);
    }
}

void WebPattern::OnShowMagnifier()
{
    ShowMagnifier(static_cast<int>(touchPointX), static_cast<int>(touchPointY));
}

void WebPattern::OnHideMagnifier()
{
    HideMagnifier();
}


void WebPattern::SetTouchHandleExistState(bool touchHandleExist)
{
    if (delegate_) {
        delegate_->SetTouchHandleExistState(touchHandleExist);
    }
}

bool WebPattern::IsShowHandle()
{
    return webSelectOverlay_ && webSelectOverlay_->IsShowHandle();
}

void WebPattern::InitSurfaceDensityCallback(const RefPtr<PipelineContext> &context)
{
    TAG_LOGD(AceLogTag::ACE_WEB, "WebPattern::InitSurfaceDensityCallback");
    CHECK_NULL_VOID(context);
    density_ = context->GetDensity();
    if (delegate_) {
        delegate_->SetSurfaceDensity(density_);
    }
    densityCallbackId_ = context->RegisterDensityChangedCallback([weak = WeakClaim(this)](double density) {
        auto webPattern = weak.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->SetSurfaceDensity(density);
    });
}

void WebPattern::UnInitSurfaceDensityCallback(const RefPtr<PipelineContext> &context)
{
    TAG_LOGD(AceLogTag::ACE_WEB, "WebPattern::UnInitSurfaceDensityCallback");
    CHECK_NULL_VOID(context);
    context->UnregisterDensityChangedCallback(densityCallbackId_);
    densityCallbackId_ = 0;
}

void WebPattern::SetImeShow(bool visible)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipelineContext->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    textFieldManager->SetImeShow(visible);
}
} // namespace OHOS::Ace::NG
