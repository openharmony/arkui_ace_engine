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

#include "core/components_ng/pattern/canvas/canvas_modifier.h"

#include "core/components_ng/pattern/canvas/custom_paint_util.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
constexpr size_t MAX_SIZE = 10;
CanvasModifier::CanvasModifier()
{
    needRender_ = AceType::MakeRefPtr<PropertyBool>(true);
    AttachProperty(needRender_);
}

void CanvasModifier::onDraw(DrawingContext& drawingContext)
{
    CHECK_NULL_VOID(rsRecordingCanvas_);
    auto& recordingCanvas = drawingContext.canvas;
    auto drawCmdList = rsRecordingCanvas_->GetDrawCmdList();
    CHECK_NULL_VOID(drawCmdList);
    auto rsDrawCmdList = static_cast<RSRecordingCanvas&>(recordingCanvas).GetDrawCmdList();
    CHECK_NULL_VOID(rsDrawCmdList);
    ACE_SCOPED_TRACE("CanvasModifier::onDraw Op count: %zu.", drawCmdList->GetOpItemSize());
    if (SystemProperties::GetCanvasDebugMode() > 0) {
        TAG_LOGI(AceLogTag::ACE_CANVAS,
            "Canvas Size: [%{public}d, %{public}d]->[%{public}d, %{public}d]; Command Size: %{public}zu.",
            rsDrawCmdList->GetWidth(), rsDrawCmdList->GetHeight(), drawCmdList->GetWidth(), drawCmdList->GetHeight(),
            drawCmdList->GetOpItemSize());
    }
    drawCmdSize_.SetWidth(drawCmdList->GetWidth());
    drawCmdSize_.SetHeight(drawCmdList->GetHeight());
    rsDrawCmdList->SetWidth(drawCmdList->GetWidth());
    rsDrawCmdList->SetHeight(drawCmdList->GetHeight());
    // Dump recent ten records
    CanvasModifierDump dumpInfo;
    dumpInfo.timestamp = GetCurrentTimestamp();
    dumpInfo.width = drawCmdList->GetWidth();
    dumpInfo.height = drawCmdList->GetHeight();
    dumpInfo.opItemSize = drawCmdList->GetOpItemSize();
    if (dumpInfos_.size() < MAX_SIZE) {
        dumpInfos_.push_back(dumpInfo);
    } else {
        dumpInfos_.erase(dumpInfos_.begin());
        dumpInfos_.push_back(dumpInfo);
    }
    ResetSurface();
    CHECK_EQUAL_VOID(drawCmdList->IsEmpty(), true);
    drawCmdList->Playback(recordingCanvas);
    rsRecordingCanvas_->Clear();
}

void CanvasModifier::ResetSurface()
{
    CHECK_EQUAL_VOID(needResetSurface_, false);
    auto renderContext = renderContext_.Upgrade();
    CHECK_NULL_VOID(renderContext);
    renderContext->ResetSurface(static_cast<int>(drawCmdSize_.Width()), static_cast<int>(drawCmdSize_.Height()));
    needResetSurface_ = false;
}

std::string CanvasModifier::GetDumpInfo()
{
    std::string ret;
    for (CanvasModifierDump& dumpInfo : dumpInfos_) {
        ret.append(ConvertTimestampToStr(dumpInfo.timestamp));
        ret.append(" Canvas Size: [" + std::to_string(dumpInfo.width) + ", " + std::to_string(dumpInfo.height) +
                   "], Command Size: " + std::to_string(dumpInfo.opItemSize) + "; ");
    }
    dumpInfos_.clear();
    return ret;
}

void CanvasModifier::GetSimplifyDumpInfo(std::unique_ptr<JsonValue>& array)
{
    for (CanvasModifierDump& dumpInfo : dumpInfos_) {
        auto info = JsonUtil::Create();
        info->Put("Timestamp", ConvertTimestampToStr(dumpInfo.timestamp).c_str());
        info->Put(
            "CanvasSize", ("[" + std::to_string(dumpInfo.width) + "," + std::to_string(dumpInfo.height) + "]").c_str());
        info->Put("CommandSize", std::to_string(dumpInfo.opItemSize).c_str());
        array->PutRef(std::move(info));
    }
}
} // namespace OHOS::Ace::NG
