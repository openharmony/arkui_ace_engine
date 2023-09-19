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
class Font {
    /**
     * Construct new instance of Font.
     * initialzie with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 10
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_font = globalThis.requireNapi('font');
    }
    registerFont(options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_font.registerFont(options);
        __JSScopeUtil__.restoreInstanceId();
    }
}

class MediaQuery {
    /**
     * Construct new instance of MediaQuery.
     * initialzie with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 10
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_mediaQuery = globalThis.requireNapi('mediaquery');
    }
    matchMediaSync(condition) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let mediaQueryListener = this.ohos_mediaQuery.matchMediaSync(condition);
        __JSScopeUtil__.restoreInstanceId();
        return mediaQueryListener;
    }
}

class UIInspector {
    /**
     * Construct new instance of ArkUIInspector.
     * initialzie with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 10
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_UIInspector  = globalThis.requireNapi('arkui.inspector');
    }
    createComponentObserver(id) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let componentObserver = this.ohos_UIInspector.createComponentObserver(id);
        __JSScopeUtil__.restoreInstanceId();
        return componentObserver;
    }
}

class UIContext {
    /**
     * Construct new instance of UIContext.
     * initialzie with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 10
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
    }

    getFont() {
        this.font_ = new Font(this.instanceId_);
        return this.font_;
    }
    
    getRouter() {
        this.router_ = new Router(this.instanceId_);
        return this.router_;
    }

    createAnimator(options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.animator_ = globalThis.requireNapi('animator');
        let animatorResult = this.animator_.create(options);
        __JSScopeUtil__.restoreInstanceId();
        return animatorResult;
    }
    
    getPromptAction() {
        this.promptAction_ = new PromptAction(this.instanceId_);
        return this.promptAction_;
    }

    getMediaQuery() {
        this.mediaQuery_ = new MediaQuery(this.instanceId_);
        return this.mediaQuery_;
    }

    getUIInspector(){
        this.UIInspector_ = new UIInspector(this.instanceId_);
        return this.UIInspector_;
    }

    getComponentUtils() {
        if(this.componentUtils_ == null) {
            this.componentUtils_ = new ComponentUtils(this.instanceId_);
        }
        return this.componentUtils_;
    }
    animateTo(value, event) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        Context.animateTo(value, event);
        __JSScopeUtil__.restoreInstanceId();
    }

    showAlertDialog(options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        AlertDialog.show(options);
        __JSScopeUtil__.restoreInstanceId();
    }

    showActionSheet(value) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        ActionSheet.show(value);
        __JSScopeUtil__.restoreInstanceId();
    }

    showDatePickerDialog(options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        DatePickerDialog.show(options);
        __JSScopeUtil__.restoreInstanceId();
    }

    showTimePickerDialog(options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        TimePickerDialog.show(options);
        __JSScopeUtil__.restoreInstanceId();
    }
    
    showTextPickerDialog(options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        TextPickerDialog.show(options);
        __JSScopeUtil__.restoreInstanceId();
    }

    runScopedTask(callback) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (callback !== undefined) {
            callback();
        }
        __JSScopeUtil__.restoreInstanceId();
    }
}
class ComponentUtils {
    /**
     * Construct new instance of ComponentUtils.
     * initialzie with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 10
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_componentUtils = globalThis.requireNapi('arkui.componentUtils');
    }
    getRectangleById(id) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let componentInformation = this.ohos_componentUtils.getRectangleById(id);
        __JSScopeUtil__.restoreInstanceId();
        return componentInformation;
    }
}

class Router {
    /**
     * Construct new instance of Font.
     * initialzie with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 10
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_router = globalThis.requireNapi('router');
    }

    pushUrl(options, modeOrCallback, callback) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof callback === 'undefined' && typeof modeOrCallback === 'undefined') {
            let promise = this.ohos_router.pushUrl(options);
            __JSScopeUtil__.restoreInstanceId();
            return promise;
        }
        else if (typeof callback !== 'undefined' && typeof modeOrCallback !== 'undefined') {
            this.ohos_router.pushUrl(options, modeOrCallback, callback);
            __JSScopeUtil__.restoreInstanceId();
        }
        else if (typeof callback === 'undefined' && typeof modeOrCallback !== 'undefined') {
            let promise = this.ohos_router.pushUrl(options, modeOrCallback);
            __JSScopeUtil__.restoreInstanceId();
            if(promise)
            {
                return promise;
            }
        }
    }

    replaceUrl(options, modeOrCallback, callback) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof callback === 'undefined' && typeof modeOrCallback === 'undefined') {
            let promise = this.ohos_router.replaceUrl(options);
            __JSScopeUtil__.restoreInstanceId();
            return promise;
        }
        else if (typeof callback !== 'undefined' && typeof modeOrCallback !== 'undefined') {
            this.ohos_router.replaceUrl(options, modeOrCallback, callback);
            __JSScopeUtil__.restoreInstanceId();
        }
        else if (typeof callback === 'undefined' && typeof modeOrCallback !== 'undefined') {
            let promise = this.ohos_router.replaceUrl(options, modeOrCallback);
            __JSScopeUtil__.restoreInstanceId();
            if(promise)
            {
                return promise;
            }
        }
    }

    back(options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_router.back(options);
        __JSScopeUtil__.restoreInstanceId();
    }

    clear() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_router.clear();
        __JSScopeUtil__.restoreInstanceId();
    }

    getLength() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let result = this.ohos_router.getLength();
        __JSScopeUtil__.restoreInstanceId();
        return result;
    }

    getState() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let state = this.ohos_router.getState();
        __JSScopeUtil__.restoreInstanceId();
        return state;
    }

    showAlertBeforeBackPage(options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_router.showAlertBeforeBackPage(options);
        __JSScopeUtil__.restoreInstanceId();
    }

    hideAlertBeforeBackPage() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_router.hideAlertBeforeBackPage();
        __JSScopeUtil__.restoreInstanceId();
    }

    getParams() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let object = this.ohos_router.getParams();
        __JSScopeUtil__.restoreInstanceId();
        return object;
    }

    pushNamedRoute(options, modeOrCallback, callback) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof callback === 'undefined' && typeof modeOrCallback === 'undefined') {
            let promise = this.ohos_router.pushNamedRoute(options);
            __JSScopeUtil__.restoreInstanceId();
            return promise;
        }
        else if (typeof callback !== 'undefined' && typeof modeOrCallback !== 'undefined') {
            this.ohos_router.pushNamedRoute(options, modeOrCallback, callback);
            __JSScopeUtil__.restoreInstanceId();
        }
        else if (typeof callback === 'undefined' && typeof modeOrCallback !== 'undefined') {
            let promise = this.ohos_router.pushNamedRoute(options, modeOrCallback);
            __JSScopeUtil__.restoreInstanceId();
            if(promise)
            {
                return promise;
            }
        }
    }

    replaceNamedRoute(options, modeOrCallback, callback) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof callback === 'undefined' && typeof modeOrCallback === 'undefined') {
            let promise = this.ohos_router.replaceNamedRoute(options);
            __JSScopeUtil__.restoreInstanceId();
            return promise;
        }
        else if (typeof callback !== 'undefined' && typeof modeOrCallback !== 'undefined') {
            this.ohos_router.replaceNamedRoute(options, modeOrCallback, callback);
            __JSScopeUtil__.restoreInstanceId();
        }
        else if (typeof callback === 'undefined' && typeof modeOrCallback !== 'undefined') {
            let promise = this.ohos_router.replaceNamedRoute(options, modeOrCallback);
            __JSScopeUtil__.restoreInstanceId();
            if(promise)
            {
                return promise;
            }
        }
    }
}

class PromptAction {
    /**
     * Construct new instance of PromptAction.
     * initialzie with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 10
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_prompt = globalThis.requireNapi('promptAction');
    }

    showToast(options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_prompt.showToast(options);
        __JSScopeUtil__.restoreInstanceId();
    }

    showDialog(options, callback) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof callback !== 'undefined') {
            this.ohos_prompt.showDialog(options, callback);
            __JSScopeUtil__.restoreInstanceId();
        }
        else {
            let showDialogSuccessResponse = this.ohos_prompt.showDialog(options);
            __JSScopeUtil__.restoreInstanceId();
            return showDialogSuccessResponse;
        }
    }

    showActionMenu(options, callback) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof callback !== 'undefined') {
            this.ohos_prompt.showActionMenu(options, callback);
            __JSScopeUtil__.restoreInstanceId();
        }
        else {
            let actionMenuSuccessResponse = this.ohos_prompt.showActionMenu(options);
            __JSScopeUtil__.restoreInstanceId();
            return actionMenuSuccessResponse;
        }
    }
}

/**
 * Get UIContext instance.
 * @param instanceId obtained on the c++ side.
 * @returns UIContext instance.
 */
function __getUIContext__(instanceId) {
    return new UIContext(instanceId);
}
