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

#ifndef WEB_AREA_CHANGED_H
#define WEB_AREA_CHANGED_H
#include "core/components/web/resource/web_delegate.h"

namespace OHOS::Ace {
class WebAvoidAreaChangedListener : public Referenced, public OHOS::Rosen::IAvoidAreaChangedListener {
public:
    explicit WebAvoidAreaChangedListener(WeakPtr<WebDelegate> webDelegate) : webDelegate_(webDelegate) {}
    ~WebAvoidAreaChangedListener() = default;
    void OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea avoidArea, OHOS::Rosen::AvoidAreaType type) override;

private:
    WeakPtr<WebDelegate> webDelegate_;
};
}

#endif