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

class ComponentSnapshot {
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_componentSnapshot = globalThis.requireNapi('arkui.componentSnapshot');
    }
    get(id, callback, options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof callback !== 'function') {
            let promise = this.ohos_componentSnapshot.get(id, callback);
            __JSScopeUtil__.restoreInstanceId();
            return promise;
        } else {
            this.ohos_componentSnapshot.get(id, callback, options);
            __JSScopeUtil__.restoreInstanceId();
        }
    }
    createFromBuilder(builder, callback, delay, checkImageStatus, options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof callback !== 'function') {
            let promise = this.ohos_componentSnapshot.createFromBuilder(builder, callback, delay, checkImageStatus);
            __JSScopeUtil__.restoreInstanceId();
            return promise;
        } else {
            this.ohos_componentSnapshot.createFromBuilder(builder, callback, delay, checkImageStatus, options);
            __JSScopeUtil__.restoreInstanceId();
        }
    }
    getSync(id, options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let pixelmap = this.ohos_componentSnapshot.getSync(id, options);
        __JSScopeUtil__.restoreInstanceId();
        return pixelmap;
    }

    getWithUniqueId(uniqueId, options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let promise = this.ohos_componentSnapshot.getWithUniqueId(uniqueId, options);
        __JSScopeUtil__.restoreInstanceId();
        return promise;
    }

    getSyncWithUniqueId(uniqueId, options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let pixelmap = this.ohos_componentSnapshot.getSyncWithUniqueId(uniqueId, options);
        __JSScopeUtil__.restoreInstanceId();
        return pixelmap;
    }

    createFromComponent(content, delay, checkImageStatus, options) {
        if (content === undefined || content === null) {
            let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
            __JSScopeUtil__.restoreInstanceId();
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let promise = this.ohos_componentSnapshot.createFromComponent(content.getFrameNode(), delay, checkImageStatus, options);
        __JSScopeUtil__.restoreInstanceId();
        return promise;
    }

    getWithRange(start, end, isStartRect, options)
    {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let pixelmap = this.ohos_componentSnapshot.getWithRange(start, end, isStartRect, options);
        __JSScopeUtil__.restoreInstanceId();
        return pixelmap;
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

    setDragEventStrictReportingEnabled(enable) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        JSViewAbstract.setDragEventStrictReportingEnabled(enable);
        __JSScopeUtil__.restoreInstanceId();
    }

    notifyDragStartRequest(request) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        JSViewAbstract.notifyDragStartRequest(request);
        __JSScopeUtil__.restoreInstanceId();
    }

    cancelDataLoading(key) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        JSViewAbstract.cancelDataLoading(key);
        __JSScopeUtil__.restoreInstanceId();
    }

    enableDropDisallowedBadge(enable) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        JSViewAbstract.enableDropDisallowedBadge(enable);
        __JSScopeUtil__.restoreInstanceId();
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
    addGlobalGestureListener(...args) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_observer?.addGlobalGestureListener(...args);
        __JSScopeUtil__.restoreInstanceId();
    }
    removeGlobalGestureListener(...args) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_observer?.removeGlobalGestureListener(...args);
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

class FrameCallback {
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

    static createUIContextWithoutWindow(context) {
        let utils = globalThis.requireNapi('arkui.containerUtils');
        let uicontext = undefined;
        if (utils) {
            uicontext = utils.createContainerWithoutWindow(context);
        }

        return uicontext;
    }

    static destroyUIContextWithoutWindow() {
        let utils = globalThis.requireNapi('arkui.containerUtils');
        if (utils) {
            utils.destroyContainerWithoutWindow();
        }
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

    getFilteredInspectorTree(filter) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof filter === 'undefined') {
            let result_ = globalThis.getFilteredInspectorTree();
            __JSScopeUtil__.restoreInstanceId();
            return result_;
        } else {
            let result_ = globalThis.getFilteredInspectorTree(filter);
            __JSScopeUtil__.restoreInstanceId();
            return result_;
        }
    }

    getFilteredInspectorTreeById(id, depth, filter) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof filter === 'undefined') {
            let result_ = globalThis.getFilteredInspectorTreeById(id, depth);
            __JSScopeUtil__.restoreInstanceId();
            return result_;
        } else {
            let result_ = globalThis.getFilteredInspectorTreeById(id, depth, filter);
            __JSScopeUtil__.restoreInstanceId();
            return result_;
        }
    }

    getComponentSnapshot() {
        this.ComponentSnapshot_ = new ComponentSnapshot(this.instanceId_);
        return this.ComponentSnapshot_;
    }

    vp2px(value) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let vp2pxResult = globalThis.vp2px(value);
        __JSScopeUtil__.restoreInstanceId();
        return vp2pxResult;
    }

    px2vp(value) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let px2vpResult = globalThis.px2vp(value);
        __JSScopeUtil__.restoreInstanceId();
        return px2vpResult;
    }

    fp2px(value) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let fp2pxResult = globalThis.fp2px(value);
        __JSScopeUtil__.restoreInstanceId();
        return fp2pxResult;
    }

    px2fp(value) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let px2fpResult = globalThis.px2fp(value);
        __JSScopeUtil__.restoreInstanceId();
        return px2fpResult;
    }

    lpx2px(value) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let lpx2pxResult = globalThis.lpx2px(value);
        __JSScopeUtil__.restoreInstanceId();
        return lpx2pxResult;
    }

    px2lpx(value) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let px2lpxResult = globalThis.px2lpx(value);
        __JSScopeUtil__.restoreInstanceId();
        return px2lpxResult;
    }

    getComponentUtils() {
        if (this.componentUtils_ == null) {
            this.componentUtils_ = new ComponentUtils(this.instanceId_);
        }
        return this.componentUtils_;
    }

    getOverlayManager() {
        if(!this.overlayManager_) {
            this.overlayManager_ = new OverlayManager(this.instanceId_);
        }
        this.overlayManager_.setOverlayManagerOptions();
        return this.overlayManager_;
    }
    setOverlayManagerOptions(options) {
        if(!this.overlayManager_) {
            this.overlayManager_ = new OverlayManager(this.instanceId_);
        }
        return this.overlayManager_.setOverlayManagerOptions(options);
    }
    getOverlayManagerOptions() {
        if(!this.overlayManager_) {
            this.overlayManager_ = new OverlayManager(this.instanceId_);
        }
        return this.overlayManager_.getOverlayManagerOptions();
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

    openBindSheet(content, options, targetId) {
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let argLength = arguments.length;
        if (argLength < 1 || content === null || content === undefined) {
            __JSScopeUtil__.restoreInstanceId();
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        if ((argLength >= 3 && (targetId === null || targetId === undefined))) {
            __JSScopeUtil__.restoreInstanceId();
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        let result_;
        if (argLength === 1) {
            result_ = Context.openBindSheet(content.getNodePtr());
        } else if (argLength === 2) {
            result_ = Context.openBindSheet(content.getNodePtr(), options);
        } else {
            result_ = Context.openBindSheet(content.getNodePtr(), options, targetId);
        }
        __JSScopeUtil__.restoreInstanceId();
        return result_;
    }

    updateBindSheet(content, options, partialUpdate) {
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let argLength = arguments.length;
        if (argLength < 2 || content === null || content === undefined) {
            __JSScopeUtil__.restoreInstanceId();
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        let result_;
        if (argLength === 2) {
            result_ = Context.updateBindSheet(content.getNodePtr(), options);
        } else {
            result_ = Context.updateBindSheet(content.getNodePtr(), options, partialUpdate);
        }
        __JSScopeUtil__.restoreInstanceId();
        return result_;
    }

    closeBindSheet(content) {
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (arguments.length < 1 || content === null || content === undefined) {
            __JSScopeUtil__.restoreInstanceId();
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        let result_ = Context.closeBindSheet(content.getNodePtr());
        __JSScopeUtil__.restoreInstanceId();
        return result_;
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

    setPixelRoundMode(pixelRoundMode) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        JSViewAbstract.setPixelRoundMode(pixelRoundMode);
        __JSScopeUtil__.restoreInstanceId();
    }

    getPixelRoundMode() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let pixelRoundMode = JSViewAbstract.getPixelRoundMode();
        __JSScopeUtil__.restoreInstanceId();
        return pixelRoundMode;
    }

    dispatchKeyEvent(node, event) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let result = JSViewAbstract.dispatchKeyEvent(node, event);
        __JSScopeUtil__.restoreInstanceId();
        return result;
    }

    getAtomicServiceBar() {
        const bundleMgr = globalThis.requireNapi('bundle.bundleManager');
        if (!bundleMgr || !bundleMgr.BundleFlag) {
            return undefined;
        }
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
        if (!nodePtr) {
            __JSScopeUtil__.restoreInstanceId();
            return null;
        }
        let xNode = globalThis.__getArkUINode__();
        let node = xNode.FrameNodeUtils.searchNodeInRegisterProxy(nodePtr);
        if (!node) {
            node = xNode.FrameNodeUtils.createFrameNode(this, nodePtr);
        }
        __JSScopeUtil__.restoreInstanceId();
        return node;
    }

    getAttachedFrameNodeById(id) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let nodePtr = getUINativeModule().getAttachedFrameNodeById(id);
        if (!nodePtr) {
            __JSScopeUtil__.restoreInstanceId();
            return null;
        }
        let xNode = globalThis.__getArkUINode__();
        let node = xNode.FrameNodeUtils.searchNodeInRegisterProxy(nodePtr);
        if (!node) {
            node = xNode.FrameNodeUtils.createFrameNode(this, nodePtr);
        }
        __JSScopeUtil__.restoreInstanceId();
        return node;
    }

    getFrameNodeByNodeId(id) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let nodePtr = getUINativeModule().getFrameNodeById(id);
        let xNode = globalThis.__getArkUINode__();
        let node = xNode.FrameNodeUtils.searchNodeInRegisterProxy(nodePtr);
        if (!node) {
            node = xNode.FrameNodeUtils.createFrameNode(this, nodePtr);
        }
        __JSScopeUtil__.restoreInstanceId();
        return node;
    }

    getFrameNodeByUniqueId(uniqueId) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let nodePtr = getUINativeModule().getFrameNodeByUniqueId(uniqueId);
        if (nodePtr === undefined) {
            __JSScopeUtil__.restoreInstanceId();
            return null;
        }
        let xNode = globalThis.__getArkUINode__();
        let node = xNode.FrameNodeUtils.searchNodeInRegisterProxy(nodePtr);
        if (!node) {
            node = xNode.FrameNodeUtils.createFrameNode(this, nodePtr);
        }
        __JSScopeUtil__.restoreInstanceId();
        return node;
    }

    getPageInfoByUniqueId(uniqueId) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        const pageInfo = getUINativeModule().getPageInfoByUniqueId(uniqueId);
        __JSScopeUtil__.restoreInstanceId();
        return pageInfo;
    }

    getNavigationInfoByUniqueId(uniqueId) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        const navigationInfo = getUINativeModule().getNavigationInfoByUniqueId(uniqueId);
        __JSScopeUtil__.restoreInstanceId();
        return navigationInfo;
    }

    getFocusController() {
        if (this.focusController_ == null) {
            this.focusController_ = new FocusController(this.instanceId_);
        }
        return this.focusController_;
    }

    setDynamicDimming(id, number) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let nodePtr = getUINativeModule().getFrameNodeByKey(id);
        if (!nodePtr) {
            return;
        }
        Context.setDynamicDimming(nodePtr, number);
    }

    getCursorController() {
        if (this.cursorController_ == null) {
            this.cursorController_ = new CursorController(this.instanceId_);
        }
        return this.cursorController_;
    }
    
    getContextMenuController() {
        if (this.contextMenuController_ == null) {
            this.contextMenuController_ = new ContextMenuController(this.instanceId_);
        }
        return this.contextMenuController_;
    }

    getWindowName() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        const windowName = getUINativeModule().common.getWindowName();
        __JSScopeUtil__.restoreInstanceId();
        return windowName;
    }

    getWindowWidthBreakpoint() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        const breakpoint = getUINativeModule().common.getWindowWidthBreakpoint();
        __JSScopeUtil__.restoreInstanceId();
        return breakpoint;
    }

    getWindowHeightBreakpoint() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        const breakpoint = getUINativeModule().common.getWindowHeightBreakpoint();
        __JSScopeUtil__.restoreInstanceId();
        return breakpoint;
    }

    clearResourceCache() {
        getUINativeModule().resource.clearCache();
    }

    postFrameCallback(frameCallback) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        getUINativeModule().common.postFrameCallback(frameCallback, 0);
        __JSScopeUtil__.restoreInstanceId();
    }

    postDelayedFrameCallback(frameCallback, delayMillis) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        getUINativeModule().common.postFrameCallback(frameCallback, delayMillis);
        __JSScopeUtil__.restoreInstanceId();
    }

    requireDynamicSyncScene(id) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let dynamicSceneInfo = getUINativeModule().requireDynamicSyncScene(id);
        if (!dynamicSceneInfo) {
            __JSScopeUtil__.restoreInstanceId();
            return [];
        }
        if (dynamicSceneInfo.tag === 'Swiper') {
            __JSScopeUtil__.restoreInstanceId();
            let nodeRef = dynamicSceneInfo.nativeRef;
            return SwiperDynamicSyncScene.createInstances(nodeRef);
        }
        if (dynamicSceneInfo.tag === 'Marquee') {
            __JSScopeUtil__.restoreInstanceId();
            let nodeRef = dynamicSceneInfo.nativeRef;
            return MarqueeDynamicSyncScene.createInstances(nodeRef);
        }
        __JSScopeUtil__.restoreInstanceId();
        return [];
    }

    isFollowingSystemFontScale() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let isFollowing = Context.isFollowingSystemFontScale();
        __JSScopeUtil__.restoreInstanceId();
        return isFollowing;
    }

    getMaxFontScale() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let maxFontScale = Context.getMaxFontScale();
        __JSScopeUtil__.restoreInstanceId();
        return maxFontScale;
    }

    bindTabsToScrollable(tabsController, scroller) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        Context.bindTabsToScrollable(tabsController, scroller);
        __JSScopeUtil__.restoreInstanceId();
    }

    unbindTabsFromScrollable(tabsController, scroller) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        Context.unbindTabsFromScrollable(tabsController, scroller);
        __JSScopeUtil__.restoreInstanceId();
    }

    bindTabsToNestedScrollable(tabsController, parentScroller, childScroller) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        Context.bindTabsToNestedScrollable(tabsController, parentScroller, childScroller);
        __JSScopeUtil__.restoreInstanceId();
    }

    unbindTabsFromNestedScrollable(tabsController, parentScroller, childScroller) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        Context.unbindTabsFromNestedScrollable(tabsController, parentScroller, childScroller);
        __JSScopeUtil__.restoreInstanceId();
    }

    enableSwipeBack(enabled) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        Context.enableSwipeBack(enabled);
        __JSScopeUtil__.restoreInstanceId();
    }

    getTextMenuController() {
        if (this.textMenuController_ == null) {
            this.textMenuController_ = new TextMenuController(this.instanceId_);
        }
        return this.textMenuController_;
    }

    freezeUINode(idOrUniqueId, isFreeze) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof idOrUniqueId === "string") {
            getUINativeModule().common.freezeUINodeById(idOrUniqueId, isFreeze);
        } else if (typeof idOrUniqueId === "number") {
            getUINativeModule().common.freezeUINodeByUniqueId(idOrUniqueId, isFreeze);
        }
        __JSScopeUtil__.restoreInstanceId();
    }
        
    isAvailable() {
        return __availableInstanceIds__.has(this.instanceId_);
    }

    setKeyboardAppearanceConfig(uniqueId, config) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let nodePtr = getUINativeModule().getFrameNodeByUniqueId(uniqueId);
        Context.setKeyboardAppearanceConfig(nodePtr, config);
        __JSScopeUtil__.restoreInstanceId();
    }
}

class DynamicSyncScene {
    /**
     * Construct new instance of DynamicSyncScene.
     * initialize with instanceId.
     * @param {Object} nodeRef - obtained on the c++ side.
     * @param {Object} frameRateRange - frameRateRange
     * @since 12
     */
    constructor(nodeRef, frameRateRange) {
        this.frameRateRange = { ...frameRateRange };
        if (!nodeRef.invalid()) {
            this.nodeRef = nodeRef;
            this.nodePtr = this.nodeRef.getNativeHandle();
        }
    }

    /**
     * Get the frame rate range.
     * @returns {Object} The frame rate range.
     */
    getFrameRateRange() {
        return this.frameRateRange;
    }
}

class SwiperDynamicSyncScene extends DynamicSyncScene {
    /**
     * Create instances of SwiperDynamicSyncScene.
     * @param {Object} nodeRef - obtained on the c++ side.
     * @returns {SwiperDynamicSyncScene[]} Array of SwiperDynamicSyncScene instances.
     */
    static createInstances(nodeRef) {
        return [new SwiperDynamicSyncScene(nodeRef, 0), new SwiperDynamicSyncScene(nodeRef, 1)];
    }

    /**
     * Construct new instance of SwiperDynamicSyncScene.
     * @param {Object} nodeRef - obtained on the c++ side.
     * @param {number} type - type of the scenes.
     */
    constructor(nodeRef, type) {
        super(nodeRef, { min: 0, max: 120, expected: 120 });
        this.type = type;
    }

    /**
     * Set the frame rate range.
     * @param {Object} frameRateRange - The new frame rate range.
     */
    setFrameRateRange(frameRateRange) {
        this.frameRateRange = { ...frameRateRange };
        getUINativeModule().setFrameRateRange(this.nodePtr, frameRateRange, this.type);
    }
}

class MarqueeDynamicSyncScene extends DynamicSyncScene {
    /**
     * Create instances of MarqueeDynamicSyncScene.
     * @param {Object} nodeRef - obtained on the c++ side.
     * @returns {MarqueeDynamicSyncScene[]} Array of MarqueeDynamicSyncScene instances.
     */
    static createInstances(nodeRef) {
        return [new MarqueeDynamicSyncScene(nodeRef, 1)];
    }

    /**
     * Construct new instance of MarqueeDynamicSyncScene.
     * @param {Object} nodeRef - obtained on the c++ side.
     */
    constructor(nodeRef, type) {
        super(nodeRef, { min: 0, max: 120, expected: 120 });
        this.type = type;
    }

    /**
     * Set the frame rate range.
     * @param {Object} frameRateRange - The new frame rate range.
     */
    setFrameRateRange(frameRateRange) {
        this.frameRateRange = { ...frameRateRange }; // 确保每个实例有独立的frameRateRange
        getUINativeModule().setMarqueeFrameRateRange(this.nodePtr, frameRateRange, this.type);
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
        if (this.ohos_focusController === null || this.ohos_focusController === undefined) {
            return;
        }
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_focusController.clearFocus();
        __JSScopeUtil__.restoreInstanceId();
    }

    requestFocus(value) {
        if (this.ohos_focusController === null || this.ohos_focusController === undefined) {
            return false;
        }
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let result = this.ohos_focusController.requestFocus(value);
        __JSScopeUtil__.restoreInstanceId();
        return result;
    }

    activate(isActive, autoInactive) {
        if (this.ohos_focusController === null || this.ohos_focusController === undefined) {
            return false;
        }
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (arguments.length === 2) {
            let result = this.ohos_focusController.activate(isActive, autoInactive);
            __JSScopeUtil__.restoreInstanceId();
            return result;
        } else {
            let result = this.ohos_focusController.activate(isActive);
            __JSScopeUtil__.restoreInstanceId();
            return result;
        }
    }

    isActive() {
        if (this.ohos_focusController === null || this.ohos_focusController === undefined) {
            return;
        }
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let result = this.ohos_focusController.isActive();
        __JSScopeUtil__.restoreInstanceId();
        return result;
    }

    setAutoFocusTransfer(value) {
        if (this.ohos_focusController === null || this.ohos_focusController === undefined) {
            return;
        }
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_focusController.setAutoFocusTransfer(value);
        __JSScopeUtil__.restoreInstanceId();
    }

    configWindowMask(enable) {
        if (this.ohos_focusController === null || this.ohos_focusController === undefined) {
            return;
        }
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_focusController.configWindowMask(enable);
        __JSScopeUtil__.restoreInstanceId();
    }

    setKeyProcessingMode(value) {
        if (this.ohos_focusController === null || this.ohos_focusController === undefined) {
            return;
        }
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_focusController.setKeyProcessingMode(value);
        __JSScopeUtil__.restoreInstanceId();
    }
}

class CursorController {
    /**
     * Construct new instance of CursorController.
     * initialzie with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 12
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
    }

    restoreDefault() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        cursorControl.restoreDefault();
        __JSScopeUtil__.restoreInstanceId();
    }
    
    setCursor(value) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        cursorControl.setCursor(value);
        __JSScopeUtil__.restoreInstanceId();
    }
}

class ContextMenuController {
    /**
     * Construct new instance of ContextMenuController.
     * initialzie with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 12
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
    }

    close() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        ContextMenu.close();
        __JSScopeUtil__.restoreInstanceId();
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
        if (typeof this.ohos_componentUtils.getRectangleById !== 'function'){
            throw Error('getRectangleById is not callable');
        }
        let componentInformation = this.ohos_componentUtils?.getRectangleById?.(id);
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
        let state = this.ohos_router.getStateByIndex(index);
        __JSScopeUtil__.restoreInstanceId();
        return state;
    }

    getStateByUrl(url) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let state = this.ohos_router.getStateByUrl(url);
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

    openToast(options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let promise = this.ohos_prompt.openToast(options);
        __JSScopeUtil__.restoreInstanceId();
        return promise;
    }

    closeToast(toastId) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_prompt.closeToast(toastId);
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

    openCustomDialog(content, options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (arguments.length === 2) {
            let result_ = this.ohos_prompt.openCustomDialog(content.getFrameNode(), options);
            __JSScopeUtil__.restoreInstanceId();
            return result_;
        }
        else {
            if (content.builderNode_ === undefined) {
                let result_ = this.ohos_prompt.openCustomDialog(content);
                __JSScopeUtil__.restoreInstanceId();
                return result_;
            }
            else {
                let result_ = this.ohos_prompt.openCustomDialog(content.getFrameNode());
                __JSScopeUtil__.restoreInstanceId();
                return result_;
            }
        }
    }

    openCustomDialogWithController(content, controller, options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        let isDialogController = controller instanceof this.ohos_prompt.DialogController;
        if (!isDialogController) {
            __JSScopeUtil__.restoreInstanceId();
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        if (typeof options === 'undefined') {
            let result_ = this.ohos_prompt.openCustomDialogWithController(content.getFrameNode(), controller);
            __JSScopeUtil__.restoreInstanceId();
            return result_;
        }
        let result_ = this.ohos_prompt.openCustomDialogWithController(content.getFrameNode(), controller, options);
        __JSScopeUtil__.restoreInstanceId();
        return result_;
    }

    presentCustomDialog(builder, controller, options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof controller === 'undefined' && typeof options === 'undefined') {
            let result_ = this.ohos_prompt.presentCustomDialog(builder);
            __JSScopeUtil__.restoreInstanceId();
            return result_;
        }
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        let isDialogController = controller instanceof this.ohos_prompt.DialogController;
        if (!isDialogController) {
            __JSScopeUtil__.restoreInstanceId();
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        if (typeof options === 'undefined') {
            let result_ = this.ohos_prompt.presentCustomDialog(builder, controller);
            __JSScopeUtil__.restoreInstanceId();
            return result_;
        }
        let result_ = this.ohos_prompt.presentCustomDialog(builder, controller, options);
        __JSScopeUtil__.restoreInstanceId();
        return result_;
    }

    updateCustomDialog(content, options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let result_ = this.ohos_prompt.updateCustomDialog(content.getFrameNode(), options);
        __JSScopeUtil__.restoreInstanceId();
        return result_;
    }

    closeCustomDialog(content) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof content === 'number') {
            this.ohos_prompt.closeCustomDialog(content);
            __JSScopeUtil__.restoreInstanceId();
        }
        else {
            let result_ = this.ohos_prompt.closeCustomDialog(content.getFrameNode());
            __JSScopeUtil__.restoreInstanceId();
            return result_;
        }
    }

    getTopOrder() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let result_ = this.ohos_prompt.__getTopOrder__();
        __JSScopeUtil__.restoreInstanceId();
        return result_;
    }

    getBottomOrder() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let result_ = this.ohos_prompt.__getBottomOrder__();
        __JSScopeUtil__.restoreInstanceId();
        return result_;
    }

    openPopup(content, target, options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let argLength = arguments.length;
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        if (argLength < 2 || argLength > 3 || content === null || content === undefined || target === null || target === undefined) {
            __JSScopeUtil__.restoreInstanceId();
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        let result_;
        if (argLength === 2) {
            result_ = Context.openPopup(content.getNodePtr(), target);
        } else {
            result_ = Context.openPopup(content.getNodePtr(), target, options);
        }
        __JSScopeUtil__.restoreInstanceId();
        return result_;
    }

    updatePopup(content, options, partialUpdate) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let argLength = arguments.length;
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        if (argLength < 2 || argLength > 3 || content === null || content === undefined || options === null || options === undefined) {
            __JSScopeUtil__.restoreInstanceId();
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        let result_;
        if (argLength === 2) {
            result_ = Context.updatePopup(content.getNodePtr(), options);
        } else {
            result_ = Context.updatePopup(content.getNodePtr(), options, partialUpdate);
        }
        __JSScopeUtil__.restoreInstanceId();
        return result_;
    }

    closePopup(content) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let argLength = arguments.length;
        const paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        if (argLength !== 1 || content === null || content === undefined) {
            __JSScopeUtil__.restoreInstanceId();
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        let result_ = Context.closePopup(content.getNodePtr());
        __JSScopeUtil__.restoreInstanceId();
        return result_;
    }

    openMenu(content, target, options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let argLength = arguments.length;
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        if (argLength < 2 || argLength > 3 || content === null || content === undefined || target === null || target === undefined) {
            __JSScopeUtil__.restoreInstanceId();
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        let result_;
        if (argLength === 2) {
            result_ = Context.openMenu(content.getNodePtr(), target);
        } else {
            result_ = Context.openMenu(content.getNodePtr(), target, options);
        }
        __JSScopeUtil__.restoreInstanceId();
        return result_;
    }

    updateMenu(content, options, partialUpdate) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let argLength = arguments.length;
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        if (argLength < 2 || argLength > 3 || content === null || content === undefined || options === null || options === undefined) {
            __JSScopeUtil__.restoreInstanceId();
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        let result_;
        if (argLength === 2) {
            result_ = Context.updateMenu(content.getNodePtr(), options);
        } else {
            result_ = Context.updateMenu(content.getNodePtr(), options, partialUpdate);
        }
        __JSScopeUtil__.restoreInstanceId();
        return result_;
    }

    closeMenu(content) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let argLength = arguments.length;
        const paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        if (argLength !== 1 || content === null || content === undefined) {
            __JSScopeUtil__.restoreInstanceId();
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        let result_ = Context.closeMenu(content.getNodePtr());
        __JSScopeUtil__.restoreInstanceId();
        return result_;
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

    getBarRect() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let rect = this.ohos_atomicServiceBar.getBarRect();
        __JSScopeUtil__.restoreInstanceId();
        return rect;
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

    setOverlayManagerOptions(options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let res = this.ohos_overlayManager.setOverlayManagerOptions(options);
        __JSScopeUtil__.restoreInstanceId();
        return res;
    }

    getOverlayManagerOptions() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let res = this.ohos_overlayManager.getOverlayManagerOptions();
        __JSScopeUtil__.restoreInstanceId();
        return res;
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

    addComponentContentWithOrder(content, levelOrder) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (typeof levelOrder !== 'undefined') {
            this.ohos_overlayManager.addFrameNodeWithOrder(content.getFrameNode(), levelOrder);
        } else {
            this.ohos_overlayManager.addFrameNodeWithOrder(content.getFrameNode());
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

    showAllComponentContents() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_overlayManager.showAllFrameNodes();
        __JSScopeUtil__.restoreInstanceId();
    }

    hideAllComponentContents() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.ohos_overlayManager.hideAllFrameNodes();
        __JSScopeUtil__.restoreInstanceId();
    }
}

class TextMenuController {
    /**
     * Construct new instance of TextMenuController.
     * initialzie with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 16
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
    }

    setMenuOptions(textMenuOptions) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        TextMenu.setMenuOptions(textMenuOptions);
        __JSScopeUtil__.restoreInstanceId();
    }

    static disableSystemServiceMenuItems(disable) {
        let controller = globalThis.requireNapi('arkui.textMenuController');
        controller.disableSystemServiceMenuItems(disable);
    }

    static disableMenuItems(items) {
        let controller = globalThis.requireNapi('arkui.textMenuController');
        controller.disableMenuItems(items);
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
 * Get FrameNode by id of UIContext instance.
 * @param instanceId obtained on the C++ side.
 * @param nodeId the id of frameNode.
 * @returns FrameNode instance.
 */
function __getFrameNodeByNodeId__(instanceId, nodeId) {
    const uiContext = __getUIContext__(instanceId);
    return uiContext.getFrameNodeByNodeId(nodeId);
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

const __availableInstanceIds__ = new Set();

/**
 * add available instanceId
 * @param instanceId instanceId to add
 */
function __addAvailableInstanceId__(instanceId) {
    __availableInstanceIds__.add(instanceId);
}

/**
 * remove available instanceId
 * @param instanceId instanceId to remove
 */
function __removeAvailableInstanceId__(instanceId) {
    __availableInstanceIds__.delete(instanceId);
}