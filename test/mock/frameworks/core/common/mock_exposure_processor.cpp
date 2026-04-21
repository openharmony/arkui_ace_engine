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
#include "core/common/recorder/exposure_processor.h"

namespace OHOS::Ace::Recorder {
ExposureProcessor::ExposureProcessor(const std::string& pageUrl, const std::string& inspectorId) : pageUrl_(pageUrl)
{
}

ExposureProcessor::ExposureProcessor(
    const std::string& pageUrl, const std::string& inspectorId, double ratio, int duration)
    : cfg_({ inspectorId, ratio, duration }), pageUrl_(pageUrl)
{}

ExposureProcessor::ExposureProcessor(const RefPtr<ExposureProcessor>& processor) {}

bool ExposureProcessor::IsNeedRecord() const
{
    return true;
}

double ExposureProcessor::GetRatio() const
{
    return 0.0;
}

void ExposureProcessor::OnVisibleChange(bool isVisible, const std::string& param)
{
}
} // namespace OHOS::Ace::Recorder
