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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CONTAINER_MODAL_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CONTAINER_MODAL_CONSTANTS_H

#include "core/components/common/properties/color.h"
#include "frameworks/base/geometry/dimension.h"

namespace OHOS::Ace {

const Dimension CONTAINER_OUTER_RADIUS = 16.0_vp;
const Dimension CONTAINER_BORDER_WIDTH = 0.0_vp;
const Dimension CONTAINER_TITLE_HEIGHT = 37.0_vp;
const Dimension TITLE_PADDING_START = 20.0_vp;
const Dimension TITLE_PADDING_END = 24.0_vp;
const Dimension ZERO_PADDING = 0.0_vp;
const Dimension TITLE_ELEMENT_MARGIN_HORIZONTAL = 12.0_vp;
const Dimension TITLE_ELEMENT_MARGIN_HORIZONTAL_ACCESS_DEVICE = 8.0_vp;
const Dimension TITLE_ICON_SIZE = 28.0_vp;
const Dimension TITLE_BUTTON_SIZE = 28.0_vp;
const Dimension CONTROL_BUTTON_ROW_LEFT_PADDING = 12.0_vp;
const Dimension CONTROL_BUTTON_ROW_RIGHT_PADDING = 20.0_vp;
const Dimension TITLE_BUTTON_RESPONSE_REGIOIN_WIDTH = 40.0_vp;
const Dimension TITLE_BUTTON_RESPONSE_REGIOIN_HEIGHT = 40.0_vp;
const Dimension TITLE_BUTTON_RESPONSE_REGIOIN_OFFSET_X = -8.0_vp;
const Dimension TITLE_BUTTON_RESPONSE_REGIOIN_OFFSET_Y = -8.0_vp;
const Dimension TITLE_TEXT_FONT_SIZE = 16.0_vp;
const Dimension CONTENT_PADDING = 4.0_vp;
const Color CONTAINER_BACKGROUND_COLOR = Color(0xf2e6e7ed);
const Color CONTAINER_BACKGROUND_COLOR_LOST_FOCUS = Color(0xfff2f2f2);
const Color CONTAINER_BORDER_COLOR = Color(0x33000000);
const Color CONTAINER_BORDER_COLOR_LOST_FOCUS = Color(0x19000000);
const Color TITLE_TEXT_COLOR = Color(0xff000000);
const Color TITLE_TEXT_COLOR_LOST_FOCUS = Color(0x66000000);
const Color TITLE_BUTTON_BACKGROUND_COLOR = Color(0x19000000);
const Color TITLE_BUTTON_BACKGROUND_COLOR_LOST_FOCUS = Color(0x0a000000);
const Color TITLE_BUTTON_CLICKED_COLOR = Color(0x33000000);
const std::string CONTAINER_MODAL_STACK_ID = "ContainerModalStack";

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CONTAINER_MODAL_CONSTANTS_H