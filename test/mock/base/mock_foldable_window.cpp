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

#include "mock_foldable_window.h"

#include "base/memory/ace_type.h"

namespace OHOS::Ace {
RefPtr<FoldableWindow> FoldableWindow::CreateFoldableWindow(int32_t /* id */)
{
    static RefPtr<FoldableWindow> foldablewindow = AceType::MakeRefPtr<MockFoldableWindow>();
    return foldablewindow;
}
} // namespace OHOS::Ace