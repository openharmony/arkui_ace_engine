/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme.h"

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {
void JSThemeColors::SetColors(const JSRef<JSArray>& colors)
{
    for (int i = 0; i < COLORS_NUMBER; i++) {
        RefPtr<ResourceObject> resObj;
        Color value;
        JSViewAbstract::ParseJsColor(colors->GetValueAt(i), value, resObj);
        if (resObj) {
            JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(colors->GetValueAt(i));
            JSViewAbstract::CompleteResourceObject(jsObj);
            resObj = JSViewAbstract::GetResourceObject(jsObj);
        }
        ResourceValue resValue = { resObj, value };
        colors_.push_back(resValue);
    }
}

} // namespace OHOS::Ace::Framework
