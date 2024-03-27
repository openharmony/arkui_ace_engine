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
     * initialize with instanceId.
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

    getSystemFontList() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let arrayResult_ = this.ohos_font.getSystemFontList();
        __JSScopeUtil__.restoreInstanceId();
        return arrayResult_;
    }

    getFontByName(fontName) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let result_ = this.ohos_font.getFontByName(fontName);
        __JSScopeUtil__.restoreInstanceId();
        return result_;
    }
}

class MediaQuery {
    /**
     * Construct new instance of MediaQuery.
     * initialize with instanceId.
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
     * initialize with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 10
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_UIInspector = globalThis.requireNapi('arkui.inspector');
    }
    createComponentObserver(id) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let componentObserver = this.ohos_UIInspector.createComponentObserver(id);
        __JSScopeUtil__.restoreInstanceId();
        return componentObserver;
    }
}

class DragController {
    /**
     * Construct new instance of DragController.
     * initialize with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 11
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_dragController = globalThis.requireNapi('arkui.dragController');
    }

    executeDrag(custom, dragInfo, callback) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof callback !== 'undefined') {
            this.ohos_dragController.executeDrag(custom, dragInfo, callback);
            __JSScopeUtil__.restoreInstanceId();
        } else {
            let eventPromise = this.ohos_dragController.executeDrag(custom, dragInfo);
            __JSScopeUtil__.restoreInstanceId();
            return eventPromise;
        }
    }

    createDragAction(customs, dragInfo) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let dragAction = this.ohos_dragController.createDragAction(customs, dragInfo);
        __JSScopeUtil__.restoreInstanceId();
        return dragAction;
    }

    getDragPreview() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let dragPreview = this.ohos_dragController.getDragPreview();
        __JSScopeUtil__.restoreInstanceId();
        return dragPreview;
    }
}

class UIObserver {
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_observer = globalThis.requireNapi('arkui.observer');
    }
    on(...args) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_observer.on(...args);
        __JSScopeUtil__.restoreInstanceId();
    }
    off(...args) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_observer.off(...args);
        __JSScopeUtil__.restoreInstanceId();
    }
}

class MeasureUtils {
    /**
     * Construct new instance of MeasureUtils.
     * initialize with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 12
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_measureUtils = globalThis.requireNapi('measure');
    }

    measureText(options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let number = this.ohos_measureUtils.measureText(options);
        __JSScopeUtil__.restoreInstanceId();
        return number;
    }

    measureTextSize(options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let sizeOption = this.ohos_measureUtils.measureTextSize(options);
        __JSScopeUtil__.restoreInstanceId();
        return sizeOption;
    }
}

class UIContext {
    /**
     * Construct new instance of UIContext.
     * initialize with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 10
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
    }

    getDragController() {
        this.dragController_ = new DragController(this.instanceId_);
        return this.dragController_;
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

    getUIInspector() {
        this.UIInspector_ = new UIInspector(this.instanceId_);
        return this.UIInspector_;
    }

    getComponentUtils() {
        if (this.componentUtils_ == null) {
            this.componentUtils_ = new ComponentUtils(this.instanceId_);
        }
        return this.componentUtils_;
    }

    getOverlayManager() {
        this.overlayManager_ = new OverlayManager(this.instanceId_);
        return this.overlayManager_;
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

    setKeyboardAvoidMode(value) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        __KeyboardAvoid__.setKeyboardAvoid(value);
        __JSScopeUtil__.restoreInstanceId();
    }

    getKeyboardAvoidMode() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let keyBoardAvoidMode = __KeyboardAvoid__.getKeyboardAvoid();
        __JSScopeUtil__.restoreInstanceId();
        return keyBoardAvoidMode;
    }

    getAtomicServiceBar() {
        const bundleMgr = globalThis.requireNapi('bundle.bundleManager');
        let data = bundleMgr.getBundleInfoForSelfSync(bundleMgr.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION);
        if (data.appInfo.bundleType == 1) {
            this.atomServiceBar = new AtomicServiceBar(this.instanceId_);
            return this.atomServiceBar;
        } else {
            return undefined;
        }
    }

    getUIObserver() {
        this.observer_ = new UIObserver(this.instanceId_);
        return this.observer_;
    }

    keyframeAnimateTo(param, keyframes) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        Context.keyframeAnimateTo(param, keyframes);
        __JSScopeUtil__.restoreInstanceId();
    }

    animateToImmediately(param, event) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        Context.animateToImmediately(param, event);
        __JSScopeUtil__.restoreInstanceId();
    }

    getMeasureUtils() {
        this.measureUtils_ = new MeasureUtils(this.instanceId_);
        return this.measureUtils_;
    }

    getHostContext() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let context = getContext();
        __JSScopeUtil__.restoreInstanceId();
        return context;
    }

    getSharedLocalStorage() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let localStorage = NativeLocalStorage.GetShared();
        __JSScopeUtil__.restoreInstanceId();
        return localStorage;
    }

    getFrameNodeById(id) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let nodePtr = getUINativeModule().getFrameNodeByKey(id);
        let xNode = globalThis.requireNapi('arkui.node');
        let node = xNode.FrameNodeUtils.searchNodeInRegisterProxy(nodePtr);
        if (!node) {
            node = xNode.FrameNodeUtils.createFrameNode(this, nodePtr);
        }
        __JSScopeUtil__.restoreInstanceId();
        return node;
    }
    getFocusController() {
        if (this.focusController_ == null) {
            this.focusController_ = new FocusController(this.instanceId_);
        }
        return this.focusController_;
    }
}

class FocusController {
    /**
     * Construct new instance of FocusController.
     * initialize with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 12
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_focusController = globalThis.requireNapi('arkui.focusController');
    }
    clearFocus() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_focusController.clearFocus();
        __JSScopeUtil__.restoreInstanceId();
    }

    requestFocus(value) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let result = this.ohos_focusController.requestFocus(value);
        __JSScopeUtil__.restoreInstanceId();
        return result;
    }
}

class ComponentUtils {
    /**
     * Construct new instance of ComponentUtils.
     * initialize with instanceId.
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
     * initialize with instanceId.
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
            if (promise) {
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
            if (promise) {
                return promise;
            }
        }
    }

    back(options, params) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof options === 'number' || arguments.length === 2) {
            this.ohos_router.back(options, params);
        } else {
            this.ohos_router.back(options);
        }
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

    getStateByIndex(index) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let state = this.ohos_router.getState(index);
        __JSScopeUtil__.restoreInstanceId();
        return state;
    }

    getStateByUrl(url) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let state = this.ohos_router.getState(url);
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
            if (promise) {
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
            if (promise) {
                return promise;
            }
        }
    }
}

class PromptAction {
    /**
     * Construct new instance of PromptAction.
     * initialize with instanceId.
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

class AtomicServiceBar {
    /**
     * Construct new instance of AtomicServiceBar.
     * initialize with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 11
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_atomicServiceBar = globalThis.requireNapi('atomicservicebar');
    }

    setVisible(visible) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_atomicServiceBar.setVisible(visible);
        __JSScopeUtil__.restoreInstanceId();
    }

    setBackgroundColor(color) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_atomicServiceBar.setBackgroundColor(color);
        __JSScopeUtil__.restoreInstanceId();
    }

    setTitleContent(content) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_atomicServiceBar.setTitleContent(content);
        __JSScopeUtil__.restoreInstanceId();
    }

    setTitleFontStyle(font) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_atomicServiceBar.setTitleFontStyle(font);
        __JSScopeUtil__.restoreInstanceId();
    }

    setIconColor(color) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_atomicServiceBar.setIconColor(color);
        __JSScopeUtil__.restoreInstanceId();
    }
}

class OverlayManager {
    /**
     * Construct new instance of Overlay.
     * initialize with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 12
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_overlayManager = globalThis.requireNapi('overlay');
    }

    addComponentContent(content, index) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof index !== 'undefined') {
            this.ohos_overlayManager.addFrameNode(content.getFrameNode(), index);
        } else {
            this.ohos_overlayManager.addFrameNode(content.getFrameNode());
        }
        __JSScopeUtil__.restoreInstanceId();
    }

    removeComponentContent(content) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_overlayManager.removeFrameNode(content.getFrameNode());
        __JSScopeUtil__.restoreInstanceId();
    }

    showComponentContent(content) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_overlayManager.showNode(content.getFrameNode());
        __JSScopeUtil__.restoreInstanceId();
    }

    hideComponentContent(content) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_overlayManager.hideNode(content.getFrameNode());
        __JSScopeUtil__.restoreInstanceId();
    }

    showAllComponentContent() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_overlayManager.showAllFrameNodes();
        __JSScopeUtil__.restoreInstanceId();
    }

    hideAllComponentContent() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_overlayManager.hideAllFrameNodes();
        __JSScopeUtil__.restoreInstanceId();
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

/**
 * check regex valid
 * @param pattern regex string
 * @returns valid result
 */
function __checkRegexValid__(pattern) {
    let result = true;
    try {
        new RegExp(pattern);
    } catch (error) {
        result = false;
    } finally {
        return result;
    }
}