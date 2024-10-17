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

#include "core/accessibility/native_interface_accessibility_impl.h"

#include <iterator>

#include "base/log/log.h"

ArkUI_AccessibilityElementInfo::ArkUI_AccessibilityElementInfo()
{
    screenRect.leftTopX = 0;
    screenRect.leftTopY = 0;
    screenRect.rightBottomX = 0;
    screenRect.rightBottomY = 0;

    rangeInfo.current = 0;
    rangeInfo.max = 0;
    rangeInfo.min = 0;

    grid.columnCount = 0;
    grid.rowCount = 0;
    grid.selectionMode = 0;

    gridItem.columnIndex = 0;
    gridItem.rowIndex = 0;
    gridItem.columnSpan = 0;
    gridItem.rowSpan = 0;
    gridItem.heading = false;
    gridItem.selected = false;
}

void ArkUI_AccessibilityElementInfo::SetRect(const ArkUI_AccessibleRect& rect)
{
    this->screenRect = rect;
}

void ArkUI_AccessibilityElementInfo::SetRangeInfo(const ArkUI_AccessibleRangeInfo& rangeInfo)
{
    this->rangeInfo = rangeInfo;
}

void ArkUI_AccessibilityElementInfo::SetGridInfo(const ArkUI_AccessibleGridInfo& gridInfo)
{
    this->grid = gridInfo;
}

void ArkUI_AccessibilityElementInfo::SetGridItemInfo(const ArkUI_AccessibleGridItemInfo& gridItemInfo)
{
    this->gridItem = gridItemInfo;
}

void ArkUI_AccessibilityElementInfo::ClearChildNodeIds()
{
    childNodeIds.clear();
}

void ArkUI_AccessibilityElementInfo::AddChildNodeId(int64_t childNodeId)
{
    childNodeIds.push_back(childNodeId);
}

void ArkUI_AccessibilityElementInfo::ClearOperationActions()
{
    operationActions.clear();
}

void ArkUI_AccessibilityElementInfo::AddOperationAction(const ArkUI_AccessibleAction& action)
{
    operationActions.push_back(action);
}

ArkUI_AccessibilityElementInfo* ArkUI_AccessibilityElementInfoList::AddAndGetElementInfo()
{
    std::lock_guard<std::mutex> lock(mutex_);
    elementInfos_.push_back(ArkUI_AccessibilityElementInfo());
    return &elementInfos_.back();
}

bool ArkUI_AccessibilityElementInfoList::CopyAccessibilityElementInfo(
    std::vector<ArkUI_AccessibilityElementInfo>& infos)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (elementInfos_.empty()) {
        return false;
    }

    std::copy(elementInfos_.begin(), elementInfos_.end(), std::back_inserter(infos));
    return true;
}

const char* ArkUI_AccessibilityActionArguments::FindValueByKey(const char* key)
{
    auto iter = actionArguments_.find(key);
    if (iter == actionArguments_.end()) {
        return nullptr;
    }
    return iter->second.c_str();
}
