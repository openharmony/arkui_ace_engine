/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "gtest/gtest.h"

#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CURRENT_ID = 1;
} // namespace

bool DragDropManager::CheckDragDropProxy(int64_t id) const
{
    return CURRENT_ID == id;
}

void DragDropManager::UpdateDragWindowPosition(int32_t globalX, int32_t globalY) {}

void DragDropManager::OnDragStart(float /* globalX */, float /* globalY */, const RefPtr<FrameNode>& /* frameNode */)
{
    GTEST_LOG_(INFO) << "OnDragStart has called";
}

void DragDropManager::OnDragMove(float /* globalX */, float /* globalY */, const std::string& /* extraInfo */)
{
    GTEST_LOG_(INFO) << "OnDragMove has called";
}

void DragDropManager::OnDragEnd(float /* globalX */, float /* globalY */, const std::string& /* extraInfo */)
{
    GTEST_LOG_(INFO) << "OnDragEnd has called";
}

void DragDropManager::onDragCancel()
{
    GTEST_LOG_(INFO) << "onDragCancel has called";
}

void DragDropManager::OnItemDragStart(
    float /* globalX */, float /* globalY */, const RefPtr<FrameNode>& /* frameNode */)
{
    GTEST_LOG_(INFO) << "OnItemDragStart has called";
}

void DragDropManager::OnItemDragMove(
    float /* globalX */, float /* globalY */, int32_t /* draggedIndex */, DragType /* dragType */)
{
    GTEST_LOG_(INFO) << "OnItemDragMove has called";
}
void DragDropManager::OnItemDragEnd(
    float /* globalX */, float /* globalY */, int32_t /* draggedIndex */, DragType /* dragType */)
{
    GTEST_LOG_(INFO) << "OnItemDragEnd has called";
}

void DragDropManager::onItemDragCancel() {}

void DragDropManager::AddDataToClipboard(const std::string& extraInfo)
{
    GTEST_LOG_(INFO) << "AddDataToClipboard has called, extraInfo is " << extraInfo;
}

void DragDropManager::GetExtraInfoFromClipboard(std::string& /* extraInfo */)
{
    GTEST_LOG_(INFO) << "GetExtraInfoFromClipboard has called";
}

void DragDropManager::RestoreClipboardData()
{
    GTEST_LOG_(INFO) << "GetExtraInfoFromClipboard has called";
}

void DragDropManager::DestroyDragWindow() {}
} // namespace OHOS::Ace::NG
