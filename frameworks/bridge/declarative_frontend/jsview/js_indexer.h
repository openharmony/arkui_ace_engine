/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_INDEXER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_INDEXER_H

#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {
struct IndexerTextStyle {
    std::optional<Dimension> fontSize;
    std::optional<FontWeight> fontWeight;
    std::optional<std::vector<std::string>> fontFamily;
    std::optional<FontStyle> fontStyle;
    RefPtr<ResourceObject> fontSizeResObj;
    RefPtr<ResourceObject> fontFamilyResObj;
};
class JSIndexer : public JSContainerBase {
public:
    static void ParseIndexerSelectedObject(
        const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal, bool isMethodProp);
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& args);
    static void CreateArc(const JSCallbackInfo& args);
    static void Create(const JSCallbackInfo& args, bool isArc);
    static void JsOnSelected(const JSCallbackInfo& args);
    static void SetColor(const JSCallbackInfo& args);
    static void SetSelectedColor(const JSCallbackInfo& args);
    static void SetPopupColor(const JSCallbackInfo& args);
    static void SetSelectedBackgroundColor(const JSCallbackInfo& args);
    static void SetPopupBackground(const JSCallbackInfo& args);
    static void SetUsingPopup(bool state);
    static void SetSelectedFont(const JSCallbackInfo& args);
    static void SetFont(const JSCallbackInfo& args);
    static void SetPopupFont(const JSCallbackInfo& args);
    static void GetFontContent(const JSCallbackInfo& args, IndexerTextStyle& textStyle);
    static void SetItemSize(const JSCallbackInfo& args);
    static void SetAlignStyle(const JSCallbackInfo& args);
    static void SetSelected(const JSCallbackInfo& args);
    static void SetPopupPosition(const JSCallbackInfo& args);
    static void JsOnRequestPopupData(const JSCallbackInfo& args);
    static void JsOnPopupSelected(const JSCallbackInfo& args);
    static void SetPopupSelectedColor(const JSCallbackInfo& args);
    static void SetPopupUnselectedColor(const JSCallbackInfo& args);
    static void SetPopupItemFont(const JSCallbackInfo& args);
    static void SetPopupItemBackgroundColor(const JSCallbackInfo& args);
    static void SetAutoCollapse(const JSCallbackInfo& args);
    static void SetPopupItemBorderRadius(const JSCallbackInfo& args);
    static void SetItemBorderRadius(const JSCallbackInfo& args);
    static void SetPopupBackgroundBlurStyle(const JSCallbackInfo& args);
    static void SetPopupTitleBackground(const JSCallbackInfo& args);
    static std::optional<Color> PaseColor(const JSCallbackInfo& args);
    static void SetWidth(const JSCallbackInfo& args);
    static void SetEnableHapticFeedback(const JSCallbackInfo& args);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_INDEXER_H
