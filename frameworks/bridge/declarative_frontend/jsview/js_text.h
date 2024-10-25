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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXT_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXT_H

#include "core/components/text/text_component_v2.h"
#include "core/components_ng/pattern/text/text_model.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components_ng/pattern/text/text_menu_extension.h"

namespace OHOS::Ace::Framework {

class JSText : public JSContainerBase {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void SetWidth(const JSCallbackInfo& info);
    static void SetHeight(const JSCallbackInfo& info);
    static void SetFont(const JSCallbackInfo& info);
    static void GetFontInfo(const JSCallbackInfo& info, Font& font);
    static void SetFontSize(const JSCallbackInfo& info);
    static void SetFontWeight(const JSCallbackInfo& info);
    static void SetMinFontScale(const JSCallbackInfo& info);
    static void SetMaxFontScale(const JSCallbackInfo& info);
    static void SetTextColor(const JSCallbackInfo& info);
    static void SetTextShadow(const JSCallbackInfo& info);
    static void SetTextOverflow(const JSCallbackInfo& info);
    static void SetMaxLines(const JSCallbackInfo& info);
    static void SetTextIndent(const JSCallbackInfo& info);
    static void SetFontStyle(int32_t value);
    static void SetAlign(const JSCallbackInfo& info);
    static void SetTextAlign(int32_t value);
    static void SetLineHeight(const JSCallbackInfo& info);
    static void SetLineSpacing(const JSCallbackInfo& info);
    static void SetFontFamily(const JSCallbackInfo& info);
    static void SetMinFontSize(const JSCallbackInfo& info);
    static void SetMaxFontSize(const JSCallbackInfo& info);
    static void SetLetterSpacing(const JSCallbackInfo& info);
    static void SetWordBreak(const JSCallbackInfo& info);
    static void SetLineBreakStrategy(const JSCallbackInfo& info);
    static void SetEllipsisMode(const JSCallbackInfo& info);
    static void SetTextSelection(const JSCallbackInfo& info);
    static void SetTextCaretColor(const JSCallbackInfo& info);
    static void SetSelectedBackgroundColor(const JSCallbackInfo& info);
    static void SetTextSelectableMode(const JSCallbackInfo& info);
    static void SetTextCase(int32_t value);
    static void SetBaselineOffset(const JSCallbackInfo& info);
    static void SetDecoration(const JSCallbackInfo& info);
    static void SetCopyOption(const JSCallbackInfo& info);
    static void SetOnCopy(const JSCallbackInfo& info);
    static void SetHeightAdaptivePolicy(int32_t value);
    static void JsOnClick(const JSCallbackInfo& info);
    static void JsOnClickWithoutNGBUILD(const JSCallbackInfo& info);
    static void JsRemoteMessage(const JSCallbackInfo& info);
    static void JsOnDragStart(const JSCallbackInfo& info);
    static void JsOnDragEnter(const JSCallbackInfo& info);
    static void JsOnDragMove(const JSCallbackInfo& info);
    static void JsOnDragLeave(const JSCallbackInfo& info);
    static void JsOnDrop(const JSCallbackInfo& info);
    static void JsFocusable(const JSCallbackInfo& info);
    static void JsDraggable(const JSCallbackInfo& info);
    static void JsMenuOptionsExtension(const JSCallbackInfo& info);
    static void JsEnableDataDetector(const JSCallbackInfo& info);
    static void JsDataDetectorConfig(const JSCallbackInfo& info);
    static void BindSelectionMenu(const JSCallbackInfo& info);
    static void SetOnTextSelectionChange(const JSCallbackInfo& info);
    static void ParseMenuParam(
        const JSCallbackInfo& info, const JSRef<JSObject>& menuOptions, NG::SelectMenuParam& menuParam);
    static void JsClip(const JSCallbackInfo& info);
    static void SetFontFeature(const JSCallbackInfo &info);
    static void SetForegroundColor(const JSCallbackInfo& info);
    static void SetMarqueeOptions(const JSCallbackInfo& info);
    static void SetOnMarqueeStateChange(const JSCallbackInfo& info);
    static void ParseMarqueeParam(const JSRef<JSObject>& paramObject, NG::TextMarqueeOptions& options);
    static void EditMenuOptions(const JSCallbackInfo& info);
    static void JsResponseRegion(const JSCallbackInfo& info);
    static void SetHalfLeading(const JSCallbackInfo& info);
    static void SetEnableHapticFeedback(const JSCallbackInfo& info);

private:
    static RefPtr<TextComponentV2> GetComponent();
};

class JSTextController final : public Referenced {
public:
    JSTextController() = default;
    ~JSTextController() override = default;

    static void JSBind(BindingTarget globalObj);

    static void Constructor(const JSCallbackInfo& args)
    {
        auto controller = Referenced::MakeRefPtr<JSTextController>();
        controller->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(controller));
    }

    static void Destructor(JSTextController* controller)
    {
        if (controller != nullptr) {
            controller->DecRefCount();
        }
    }

    void SetController(const RefPtr<TextControllerBase>& controller)
    {
        controllerWeak_ = controller;
    }

    void CloseSelectionMenu();

    void SetStyledString(const JSCallbackInfo& info);
    void GetLayoutManager(const JSCallbackInfo& args);
private:
    WeakPtr<TextControllerBase> controllerWeak_;
    ACE_DISALLOW_COPY_AND_MOVE(JSTextController);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXT_H
