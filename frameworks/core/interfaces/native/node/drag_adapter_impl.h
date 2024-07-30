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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_DRAG_ADAPTER_IMPL_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_DRAG_ADAPTER_IMPL_H
#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "base/error/error_code.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/interfaces/arkoala/arkoala_api.h"


namespace OHOS::Ace::DragAdapter {
const ArkUIDragAdapterAPI* GetDragAdapterAPI();
} // namespace OHOS::Ace::DragAdapter
#endif // FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_DRAG_ADAPTER_IMPL_H