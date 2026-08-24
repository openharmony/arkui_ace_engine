/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
 
#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_SERVICE_COLLABORATION_HEADER_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_SERVICE_COLLABORATION_HEADER_H
 
// This header aggregates ace_engine internal headers needed by
// the closed-source service_collaboration (expanded_menu) module,
// and exposes them via innerApi so that the closed-source repo
// does not need to reference ace_engine source paths directly.
 
// base headers
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
 
// core components_ng headers
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/popup_param.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/select_overlay/service_collaboration_menu_ace_helper.h"
 
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_SERVICE_COLLABORATION_HEADER_H