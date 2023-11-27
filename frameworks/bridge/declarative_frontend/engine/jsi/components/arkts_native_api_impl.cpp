/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "base/memory/ace_type.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_blank_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_button_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_checkbox_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_checkboxgroup_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_common_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_image_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_counter_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_divider_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_grid_col_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_grid_row_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_image_span_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_nav_destination_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_navigation_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_panel_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_text_area_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_text_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_toggle_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_radio_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_rating_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_select_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_slider_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_textpicker_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_timepicker_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_rich_editor_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_video_modifier.h"
#include "core/components/common/layout/constants.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_nav_destination_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_navigation_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_nav_router_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_navigator_modifier.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/pipeline/base/element_register.h"

using namespace OHOS::Ace::NG;

NodeHandle GetFrameNodeById(int nodeId)
{
    auto node = OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(nodeId);
    return OHOS::Ace::AceType::RawPtr(node);
}

static struct ArkUINodeAPI impl = {
    GetFrameNodeById,
    GetCommonModifier,
    GetCheckboxGroupModifier,
    GetCounterModifier,
    GetTextModifier,
    GetButtonModifier,
    GetToggleModifier,
    GetImageSpanModifier,
    GetBlankModifier,
    GetSelectModifier,
    GetRadioModifier,
    GetCheckboxModifier,
    GetTimepickerModifier,
    GetTextpickerModifier,
    GetRatingModifier,
    GetSliderModifier,
    GetDividerModifier,
    GetNavDestinationModifier,
    GetGridColModifier,
    GetGridRowModifier,
    GetPanelModifier,
    GetTextAreaModifier,
    GetNavigationModifier,
    GetRichEditorModifier,
    GetImageModifier,
    GetVideoModifier,
    GetNavigatorModifier,
    GetNavRouterModifier,
};

ArkUINodeAPI* GetArkUIInternalNodeAPI()
{
    return &impl;
}

extern "C" ACE_FORCE_EXPORT ArkUINodeAPI* GetArkUINodeAPI()
{
    return &impl;
}
