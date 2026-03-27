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

#include "base/log/frame_report.h"

namespace OHOS::Ace {

FrameReport::FrameReport()
{
}
FrameReport::~FrameReport()
{
}

FrameReport &FrameReport::GetInstance()
{
    static FrameReport instance;
    return instance;
}

int FrameReport::GetEnable()
{
    return true;
}

void FrameReport::EndListFling()
{
}

void FrameReport::BeginListFling()
{
}

void FrameReport::EnableSelfRender()
{
}

void FrameReport::DisableSelfRender()
{
}
} // namespace OHOS::Ace
