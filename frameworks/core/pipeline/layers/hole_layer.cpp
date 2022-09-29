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

#include "core/pipeline/layers/hole_layer.h"

#include <atomic>

#include "base/log/dump_log.h"

namespace OHOS::Ace::Flutter {

HoleLayer::HoleLayer(double width, double height) : size_(width, height)
{
    static std::atomic<int32_t> holeId = 0;
    holeId_ = holeId.fetch_add(1, std::memory_order_relaxed);
}

void HoleLayer::AddToScene(SceneBuilder& builder, double x, double y) {
    builder.PushHole(x + offset_.GetX(), y + offset_.GetY(), size_.Width(), size_.Height(), holeId_);
    AddChildToScene(builder, x + offset_.GetX(), y + offset_.GetY());
    builder.Pop();
}

void HoleLayer::Dump()
{
    if (DumpLog::GetInstance().GetDumpFile()) {
        DumpLog::GetInstance().AddDesc("holeId:", holeId_);
        DumpLog::GetInstance().AddDesc("size:", size_.ToString());
        DumpLog::GetInstance().AddDesc("offset:", offset_.ToString());
    }
}

} // namespace OHOS::Ace::Flutter
