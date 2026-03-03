/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <hilog/log.h>

#include "FakeCustomWidget.h"


namespace NativeXComponentSample {

/**
 * @brief Constructor for FakeCustomWidget
 * @param name The name of the custom widget
 */
FakeCustomWidget::FakeCustomWidget(const std::string& name)
    : AccessibleObject(name)
{
    SetComponentType("customwidget");
    SetAccessibilityGroup(true);
    SetAccessibilityLevel("page");

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FakeCustomWidget",
        "Created FakeCustomWidget: %{public}s", name.c_str());
}

/**
 * @brief Destructor for FakeCustomWidget
 */
FakeCustomWidget::~FakeCustomWidget()
{
    Cleanup();
}

} // namespace NativeXComponentSample
