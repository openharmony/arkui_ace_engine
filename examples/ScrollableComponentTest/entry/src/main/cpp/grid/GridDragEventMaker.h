/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 */

#ifndef GRID_DRAG_EVENT_MAKER_H
#define GRID_DRAG_EVENT_MAKER_H

#include <arkui/native_node.h>
#include <memory>

#include "ArkUIGridItemNode.h"
#include "ArkUIGridNode.h"

class GridDragEventMaker {
public:
    static ArkUI_NodeHandle CreateNativeNode();

private:
    static void ConfigureGrid(std::shared_ptr<ArkUIGridNode>& grid);
    static std::shared_ptr<ArkUIGridNode> BuildGrid();
    static std::shared_ptr<ArkUIGridNode> BuildGrid2();
    static std::shared_ptr<ArkUIGridItemNode> CreateGridItem(const std::string& content);
};
#endif // GRID_DRAG_EVENT_MAKER_H
