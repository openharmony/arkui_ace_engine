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
        withInstanceId(this.instanceId_, () => {
            this.ohos_font.registerFont(options);
        });
    }

    getSystemFontList() {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_font.getSystemFontList();
        });
    }

    getFontByName(fontName) {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_font.getFontByName(fontName);
        });
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
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_mediaQuery.matchMediaSync(condition);
        });
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
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_UIInspector.createComponentObserver(id);
        });
    }
}

class ComponentSnapshot {
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_componentSnapshot = globalThis.requireNapi('arkui.componentSnapshot');
    }
    get(id, callback, options) {
        return withInstanceId(this.instanceId_, () => {
            if (typeof callback !== 'function') {
                return this.ohos_componentSnapshot.get(id, callback);
            } else {
                this.ohos_componentSnapshot.get(id, callback, options);
            }
        });
    }
    createFromBuilder(builder, callback, delay, checkImageStatus, options) {
        return withInstanceId(this.instanceId_, () => {
            if (typeof callback !== 'function') {
                return this.ohos_componentSnapshot.createFromBuilder(builder, callback, delay, checkImageStatus);
            } else {
                this.ohos_componentSnapshot.createFromBuilder(builder, callback, delay, checkImageStatus, options);
            }
        });
    }
    getSync(id, options) {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_componentSnapshot.getSync(id, options);
        });
    }

    getWithUniqueId(uniqueId, options) {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_componentSnapshot.getWithUniqueId(uniqueId, options);
        });
    }

    getSyncWithUniqueId(uniqueId, options) {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_componentSnapshot.getSyncWithUniqueId(uniqueId, options);
        });
    }

    createFromComponent(content, delay, checkImageStatus, options) {
        if (content === undefined || content === null) {
            let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_componentSnapshot.createFromComponent(content.getFrameNode(), delay, checkImageStatus, options);
        });
    }

    getWithRange(start, end, isStartRect, options)
    {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_componentSnapshot.getWithRange(start, end, isStartRect, options);
        });
    }

    getSizeLimitation()
    {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let limitation = this.ohos_componentSnapshot.getSizeLimitation();
        __JSScopeUtil__.restoreInstanceId();
        return limitation;
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
        return withInstanceId(this.instanceId_, () => {
            if (typeof callback !== 'undefined') {
                this.ohos_dragController.executeDrag(custom, dragInfo, callback);
            } else {
                return this.ohos_dragController.executeDrag(custom, dragInfo);
            }
        });
    }

    createDragAction(customs, dragInfo) {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_dragController.createDragAction(customs, dragInfo);
        });
    }

    getDragPreview() {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_dragController.getDragPreview();
        });
    }

    setDragEventStrictReportingEnabled(enable) {
        withInstanceId(this.instanceId_, () => {
            JSViewAbstract.setDragEventStrictReportingEnabled(enable);
        });
    }

    notifyDragStartRequest(request) {
        withInstanceId(this.instanceId_, () => {
            JSViewAbstract.notifyDragStartRequest(request);
        });
    }

    cancelDataLoading(key) {
        withInstanceId(this.instanceId_, () => {
            JSViewAbstract.cancelDataLoading(key);
        });
    }

    enableDropDisallowedBadge(enable) {
        withInstanceId(this.instanceId_, () => {
            JSViewAbstract.enableDropDisallowedBadge(enable);
        });
    }
}

class UIObserver {
    constructor(instanceId) {
        this.instanceId_ = instanceId;
        this.ohos_observer = globalThis.requireNapi('arkui.observer');
    }
    on(...args) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_observer.on(...args);
        });
    }
    off(...args) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_observer.off(...args);
        });
    }
    addGlobalGestureListener(...args) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_observer?.addGlobalGestureListener(...args);
        });
    }
    removeGlobalGestureListener(...args) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_observer?.removeGlobalGestureListener(...args);
        });
    }
    onSwiperContentUpdate(...args) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_observer.onSwiperContentUpdate(...args);
        });
    }
    offSwiperContentUpdate(...args) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_observer.offSwiperContentUpdate(...args);
        });
    }
    onRouterPageSizeChange(...args) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_observer.onRouterPageSizeChange(...args);
        });
    }
    offRouterPageSizeChange(...args) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_observer.offRouterPageSizeChange(...args);
        });
    }
    onNavDestinationSizeChange(...args) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_observer.onNavDestinationSizeChange(...args);
        });
    }
    offNavDestinationSizeChange(...args) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_observer.offNavDestinationSizeChange(...args);
        });
    }
    onNavDestinationSizeChangeByUniqueId(...args) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_observer.onNavDestinationSizeChangeByUniqueId(...args);
        });
    }
    offNavDestinationSizeChangeByUniqueId(...args) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_observer.offNavDestinationSizeChangeByUniqueId(...args);
        });
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
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_measureUtils.measureText(options);
        });
    }

    measureTextSize(options) {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_measureUtils.measureTextSize(options);
        });
    }

    getParagraphs(styledString, options) {
        return withInstanceId(this.instanceId_, () => {
            return TextLayout.getParagraphs(styledString, options);
        });
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

    static getCallingScopeUIContext() {
        let containerId = __JSScopeUtil__.getCallingScopeUIContext();
        if (containerId < 0) {
            return undefined;
        }
        return new UIContext(containerId);
    }

    static getLastFocusedUIContext() {
        let containerId = __JSScopeUtil__.getLastFocusedUIContext();
        if (containerId < 0) {
            return undefined;
        }
        return new UIContext(containerId);
    }

    static getLastForegroundUIContext() {
        let containerId = __JSScopeUtil__.getLastForegroundUIContext();
        if (containerId < 0) {
            return undefined;
        }
        return new UIContext(containerId);
    }

    static getAllUIContexts() {
        let allContainerId = __JSScopeUtil__.getAllUIContexts();
        let contextArray = new Array();
        for (let item of allContainerId) {
            if (item >= 0) {
                contextArray.push(new UIContext(item));
            }
        }
        return contextArray;
    }

    static resolveUIContext() {
        let contextInfo = __JSScopeUtil__.resolveUIContext();
        return new ResolvedUIContext(contextInfo[0], contextInfo[1]);
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

    static setResourceManagerCacheMaxCountForHSP(count) {
        getUINativeModule().resource.setResourceManagerCacheMaxCountForHSP(count);
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
        return withInstanceId(this.instanceId_, () => {
            this.animator_ = globalThis.requireNapi('animator');
            return this.animator_.create(options);
        });
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
        return withInstanceId(this.instanceId_, () => {
            if (typeof filter === 'undefined') {
                return globalThis.getFilteredInspectorTree();
            } else {
                return globalThis.getFilteredInspectorTree(filter);
            }
        });
    }

    getFilteredInspectorTreeById(id, depth, filter) {
        return withInstanceId(this.instanceId_, () => {
            if (typeof filter === 'undefined') {
                return globalThis.getFilteredInspectorTreeById(id, depth);
            } else {
                return globalThis.getFilteredInspectorTreeById(id, depth, filter);
            }
        });
    }

    getComponentSnapshot() {
        this.ComponentSnapshot_ = new ComponentSnapshot(this.instanceId_);
        return this.ComponentSnapshot_;
    }

    vp2px(value) {
        return withInstanceId(this.instanceId_, () => {
            return globalThis.vp2px(value);
        });
    }

    px2vp(value) {
        return withInstanceId(this.instanceId_, () => {
            return globalThis.px2vp(value);
        });
    }

    fp2px(value) {
        return withInstanceId(this.instanceId_, () => {
            return globalThis.fp2px(value);
        });
    }

    px2fp(value) {
        return withInstanceId(this.instanceId_, () => {
            return globalThis.px2fp(value);
        });
    }

    lpx2px(value) {
        return withInstanceId(this.instanceId_, () => {
            return globalThis.lpx2px(value);
        });
    }

    px2lpx(value) {
        return withInstanceId(this.instanceId_, () => {
            return globalThis.px2lpx(value);
        });
    }

    getId() {
        return this.instanceId_ ?? -1;
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
        withInstanceId(this.instanceId_, () => {
            Context.animateTo(value, event);
        });
    }

    showAlertDialog(options) {
        withInstanceId(this.instanceId_, () => {
            AlertDialog.show(options);
        });
    }

    showActionSheet(value) {
        withInstanceId(this.instanceId_, () => {
            ActionSheet.show(value);
        });
    }

    openBindSheet(content, options, targetId) {
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        let argLength = arguments.length;
        if (argLength < 1 || content === null || content === undefined) {
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        if ((argLength >= 3 && (targetId === null || targetId === undefined))) {
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        return withInstanceId(this.instanceId_, () => {
            if (argLength === 1) {
                return Context.openBindSheet(content.getNodePtr());
            } else if (argLength === 2) {
                return Context.openBindSheet(content.getNodePtr(), options);
            } else {
                return Context.openBindSheet(content.getNodePtr(), options, targetId);
            }
        });
    }

    updateBindSheet(content, options, partialUpdate) {
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        let argLength = arguments.length;
        if (argLength < 2 || content === null || content === undefined) {
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        return withInstanceId(this.instanceId_, () => {
            if (argLength === 2) {
                return Context.updateBindSheet(content.getNodePtr(), options);
            } else {
                return Context.updateBindSheet(content.getNodePtr(), options, partialUpdate);
            }
        });
    }

    closeBindSheet(content) {
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        if (arguments.length < 1 || content === null || content === undefined) {
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        return withInstanceId(this.instanceId_, () => {
            return Context.closeBindSheet(content.getNodePtr());
        });
    }

    showDatePickerDialog(options) {
        withInstanceId(this.instanceId_, () => {
            DatePickerDialog.show(options);
        });
    }

    showTimePickerDialog(options) {
        withInstanceId(this.instanceId_, () => {
            TimePickerDialog.show(options);
        });
    }

    showTextPickerDialog(options) {
        withInstanceId(this.instanceId_, () => {
            TextPickerDialog.show(options);
        });
    }

    runScopedTask(callback) {
        withInstanceId(this.instanceId_, () => {
            if (callback !== undefined) {
                callback();
            }
        });
    }

    setKeyboardAvoidMode(value) {
        withInstanceId(this.instanceId_, () => {
            __KeyboardAvoid__.setKeyboardAvoid(value);
        });
    }

    getKeyboardAvoidMode() {
        return withInstanceId(this.instanceId_, () => {
            return __KeyboardAvoid__.getKeyboardAvoid();
        });
    }

    setPixelRoundMode(pixelRoundMode) {
        withInstanceId(this.instanceId_, () => {
            JSViewAbstract.setPixelRoundMode(pixelRoundMode);
        });
    }

    enableEventPassthrough(enabled, eventType) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        getUINativeModule().enableEventPassthrough(enabled, eventType);
        __JSScopeUtil__.restoreInstanceId();
    }

    getPixelRoundMode() {
        return withInstanceId(this.instanceId_, () => {
            return JSViewAbstract.getPixelRoundMode();
        });
    }

    dispatchKeyEvent(node, event) {
        return withInstanceId(this.instanceId_, () => {
            return JSViewAbstract.dispatchKeyEvent(node, event);
        });
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

    getLuminanceSampler(target) {
        return withInstanceId(this.instanceId_, () => {
            const luminanceSampler = globalThis.requireNapi("luminancesampler");
            return luminanceSampler?.getOrCreateLuminanceSampler(this.instanceId_, target);
        });
    }

    keyframeAnimateTo(param, keyframes) {
        withInstanceId(this.instanceId_, () => {
            Context.keyframeAnimateTo(param, keyframes);
        });
    }

    animateToImmediately(param, event) {
        withInstanceId(this.instanceId_, () => {
            Context.animateToImmediately(param, event);
        });
    }

    getMeasureUtils() {
        this.measureUtils_ = new MeasureUtils(this.instanceId_);
        return this.measureUtils_;
    }

    getHostContext() {
        return withInstanceId(this.instanceId_, () => {
            return getContext();
        });
    }

    getSharedLocalStorage() {
        return withInstanceId(this.instanceId_, () => {
            return NativeLocalStorage.GetShared();
        });
    }

    getFrameNodeById(id) {
        return withInstanceId(this.instanceId_, () => {
            let nodePtr = getUINativeModule().getFrameNodeByKey(id);
            if (!nodePtr) {
                return null;
            }
            let xNode = globalThis.__getArkUINode__();
            let node = xNode.FrameNodeUtils.searchNodeInRegisterProxy(nodePtr);
            if (!node) {
                node = xNode.FrameNodeUtils.createFrameNode(this, nodePtr);
            }
            return node;
        });
    }

    getAttachedFrameNodeById(id) {
        return withInstanceId(this.instanceId_, () => {
            let nodePtr = getUINativeModule().getAttachedFrameNodeById(id);
            if (!nodePtr) {
                return null;
            }
            let xNode = globalThis.__getArkUINode__();
            let node = xNode.FrameNodeUtils.searchNodeInRegisterProxy(nodePtr);
            if (!node) {
                node = xNode.FrameNodeUtils.createFrameNode(this, nodePtr);
            }
            return node;
        });
    }

    getFrameNodeByNodeId(id) {
        return withInstanceId(this.instanceId_, () => {
            let nodePtr = getUINativeModule().getFrameNodeById(id);
            let xNode = globalThis.__getArkUINode__();
            let node = xNode.FrameNodeUtils.searchNodeInRegisterProxy(nodePtr);
            if (!node) {
                node = xNode.FrameNodeUtils.createFrameNode(this, nodePtr);
            }
            return node;
        });
    }

    getFrameNodeByUniqueId(uniqueId) {
        return withInstanceId(this.instanceId_, () => {
            let nodePtr = getUINativeModule().getFrameNodeByUniqueId(uniqueId);
            if (nodePtr === undefined) {
                return null;
            }
            let xNode = globalThis.__getArkUINode__();
            let node = xNode.FrameNodeUtils.searchNodeInRegisterProxy(nodePtr);
            if (!node) {
                node = xNode.FrameNodeUtils.createFrameNode(this, nodePtr);
            }
            return node;
        });
    }

    getPageInfoByUniqueId(uniqueId) {
        return withInstanceId(this.instanceId_, () => {
            return getUINativeModule().getPageInfoByUniqueId(uniqueId);
        });
    }

    getNavigationInfoByUniqueId(uniqueId) {
        return withInstanceId(this.instanceId_, () => {
            return getUINativeModule().getNavigationInfoByUniqueId(uniqueId);
        });
    }

    getFocusController() {
        if (this.focusController_ == null) {
            this.focusController_ = new FocusController(this.instanceId_);
        }
        return this.focusController_;
    }

    setDynamicDimming(id, number) {
        return withInstanceId(this.instanceId_, () => {
            let nodePtr = getUINativeModule().getFrameNodeByKey(id);
            if (!nodePtr) {
                return;
            }
            Context.setDynamicDimming(nodePtr, number);
        });
    }

    setImageCacheCount(value) {
        withInstanceId(this.instanceId_, () => {
            Context.setImageCacheCount(value, this.instanceId_);
        });
    }

    setImageRawDataCacheSize(value) {
        withInstanceId(this.instanceId_, () => {
            Context.setImageRawDataCacheSize(value, this.instanceId_);
        });
    }

    recycleInvisibleImageMemory(value) {
        withInstanceId(this.instanceId_, () => {
            getUINativeModule().common.recycleInvisibleImageMemory(value, this.instanceId_);
        });
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
        return withInstanceId(this.instanceId_, () => {
            return getUINativeModule().common.getWindowName();
        });
    }

    getWindowId() {
        return withInstanceId(this.instanceId_, () => {
            return getUINativeModule().common.getWindowId();
        });
    }
    
    getWindowWidthBreakpoint() {
        return withInstanceId(this.instanceId_, () => {
            return getUINativeModule().common.getWindowWidthBreakpoint();
        });
    }

    getWindowHeightBreakpoint() {
        return withInstanceId(this.instanceId_, () => {
            return getUINativeModule().common.getWindowHeightBreakpoint();
        });
    }

    clearResourceCache() {
        getUINativeModule().resource.clearCache();
    }

    postFrameCallback(frameCallback) {
        return withInstanceId(this.instanceId_, () => {
            getUINativeModule().common.postFrameCallback(frameCallback, 0);
        });
    }

    postDelayedFrameCallback(frameCallback, delayMillis) {
        return withInstanceId(this.instanceId_, () => {
            getUINativeModule().common.postFrameCallback(frameCallback, delayMillis);
        });
    }

    requireDynamicSyncScene(id) {
        return withInstanceId(this.instanceId_, () => {
            let dynamicSceneInfo = getUINativeModule().requireDynamicSyncScene(id);
            if (!dynamicSceneInfo) {
                return [];
            }
            if (dynamicSceneInfo.tag === 'Swiper') {
                let nodeRef = dynamicSceneInfo.nativeRef;
                return SwiperDynamicSyncScene.createInstances(nodeRef);
            }
            if (dynamicSceneInfo.tag === 'Marquee') {
                let nodeRef = dynamicSceneInfo.nativeRef;
                return MarqueeDynamicSyncScene.createInstances(nodeRef);
            }
            return [];
        });
    }

    isFollowingSystemFontScale() {
        return withInstanceId(this.instanceId_, () => {
            return Context.isFollowingSystemFontScale();
        });
    }

    getMaxFontScale() {
        return withInstanceId(this.instanceId_, () => {
            return Context.getMaxFontScale();
        });
    }

    bindTabsToScrollable(tabsController, scroller) {
        withInstanceId(this.instanceId_, () => {
            Context.bindTabsToScrollable(tabsController, scroller);
        });
    }

    unbindTabsFromScrollable(tabsController, scroller) {
        withInstanceId(this.instanceId_, () => {
            Context.unbindTabsFromScrollable(tabsController, scroller);
        });
    }

    bindTabsToNestedScrollable(tabsController, parentScroller, childScroller) {
        withInstanceId(this.instanceId_, () => {
            Context.bindTabsToNestedScrollable(tabsController, parentScroller, childScroller);
        });
    }

    unbindTabsFromNestedScrollable(tabsController, parentScroller, childScroller) {
        withInstanceId(this.instanceId_, () => {
            Context.unbindTabsFromNestedScrollable(tabsController, parentScroller, childScroller);
        });
    }

    enableSwipeBack(enabled) {
        withInstanceId(this.instanceId_, () => {
            Context.enableSwipeBack(enabled);
        });
    }

    getTextMenuController() {
        if (this.textMenuController_ == null) {
            this.textMenuController_ = new TextMenuController(this.instanceId_);
        }
        return this.textMenuController_;
    }

    freezeUINode(idOrUniqueId, isFreeze) {
        withInstanceId(this.instanceId_, () => {
            if (typeof idOrUniqueId === "string") {
                getUINativeModule().common.freezeUINodeById(idOrUniqueId, isFreeze);
            } else if (typeof idOrUniqueId === "number") {
                getUINativeModule().common.freezeUINodeByUniqueId(idOrUniqueId, isFreeze);
            }
        });
    }
        
    isAvailable() {
        return __availableInstanceIds__.has(this.instanceId_);
    }

    setKeyboardAppearanceConfig(uniqueId, config) {
        withInstanceId(this.instanceId_, () => {
            let nodePtr = getUINativeModule().getFrameNodeByUniqueId(uniqueId);
            Context.setKeyboardAppearanceConfig(nodePtr, config);
        });
    }

    setCacheRange(frameNode, range) {
        withInstanceId(this.instanceId_, () => {
            let nodePtr = frameNode.getNodePtr();
            getUINativeModule().list.setCacheRange(nodePtr, range);
        });
    }

    getMagnifier() {
        if (this.magnifier_ == null) {
            this.magnifier_ = new Magnifier(this.instanceId_);
        }
        return this.magnifier_;
    }
    
    setCustomKeyboardContinueFeature(feature) {
        withInstanceId(this.instanceId_, () => {
            Context.setCustomKeyboardContinueFeature(feature);
        });
    }

    getPageRootNode() {
        if (!this.isAvailable()) {
            throw new BusinessError(120007, 'The UIContext is not available');
        }
        return withInstanceId(this.instanceId_, () => {
            let nodePtr = getUINativeModule().getPageRootNode(this.instanceId_);
            let xNode = globalThis.__getArkUINode__();
            let node = xNode.FrameNodeUtils.searchNodeInRegisterProxy(nodePtr);
            if (!node) {
                node = xNode.FrameNodeUtils.createFrameNode(this, nodePtr);
            }
            return node;
        });
    }

    isEasySplit() {
        return withInstanceId(this.instanceId_, () => {
            return Context.isEasySplit();
        });
    }
}

class ResolvedUIContext extends UIContext {
    constructor(instanceId, strategy) {
        super(instanceId);
        this.strategy = strategy;
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
        withInstanceId(this.instanceId_, () => {
            this.ohos_focusController.clearFocus();
        });
    }

    requestFocus(value) {
        if (this.ohos_focusController === null || this.ohos_focusController === undefined) {
            return false;
        }
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_focusController.requestFocus(value);
        });
    }

    activate(isActive, autoInactive) {
        if (this.ohos_focusController === null || this.ohos_focusController === undefined) {
            return false;
        }
        return withInstanceId(this.instanceId_, () => {
            if (arguments.length === 2) {
                return this.ohos_focusController.activate(isActive, autoInactive);
            } else {
                return this.ohos_focusController.activate(isActive);
            }
        });
    }

    isActive() {
        if (this.ohos_focusController === null || this.ohos_focusController === undefined) {
            return;
        }
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_focusController.isActive();
        });
    }

    setAutoFocusTransfer(value) {
        if (this.ohos_focusController === null || this.ohos_focusController === undefined) {
            return;
        }
        withInstanceId(this.instanceId_, () => {
            this.ohos_focusController.setAutoFocusTransfer(value);
        });
    }

    configWindowMask(enable) {
        if (this.ohos_focusController === null || this.ohos_focusController === undefined) {
            return;
        }
        withInstanceId(this.instanceId_, () => {
            this.ohos_focusController.configWindowMask(enable);
        });
    }

    setKeyProcessingMode(value) {
        if (this.ohos_focusController === null || this.ohos_focusController === undefined) {
            return;
        }
        withInstanceId(this.instanceId_, () => {
            this.ohos_focusController.setKeyProcessingMode(value);
        });
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
        withInstanceId(this.instanceId_, () => {
            cursorControl.restoreDefault();
        });
    }
    
    setCursor(value) {
        withInstanceId(this.instanceId_, () => {
            cursorControl.setCursor(value);
        });
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
        withInstanceId(this.instanceId_, () => {
            ContextMenu.close();
        });
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
        return withInstanceId(this.instanceId_, () => {
            if (typeof this.ohos_componentUtils.getRectangleById !== 'function'){
                throw Error('getRectangleById is not callable');
            }
            return this.ohos_componentUtils?.getRectangleById?.(id, this.instanceId_);
        });
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
        return withInstanceId(this.instanceId_, () => {
            if (typeof callback === 'undefined' && typeof modeOrCallback === 'undefined') {
                return this.ohos_router.pushUrl(options);
            }
            else if (typeof callback !== 'undefined' && typeof modeOrCallback !== 'undefined') {
                this.ohos_router.pushUrl(options, modeOrCallback, callback);
            }
            else if (typeof callback === 'undefined' && typeof modeOrCallback !== 'undefined') {
                let promise = this.ohos_router.pushUrl(options, modeOrCallback);
                if (promise) {
                    return promise;
                }
            }
        });
    }

    replaceUrl(options, modeOrCallback, callback) {
        return withInstanceId(this.instanceId_, () => {
            if (typeof callback === 'undefined' && typeof modeOrCallback === 'undefined') {
                return this.ohos_router.replaceUrl(options);
            }
            else if (typeof callback !== 'undefined' && typeof modeOrCallback !== 'undefined') {
                this.ohos_router.replaceUrl(options, modeOrCallback, callback);
            }
            else if (typeof callback === 'undefined' && typeof modeOrCallback !== 'undefined') {
                let promise = this.ohos_router.replaceUrl(options, modeOrCallback);
                if (promise) {
                    return promise;
                }
            }
        });
    }

    back(options, params) {
        withInstanceId(this.instanceId_, () => {
            if (typeof options === 'number' || arguments.length === 2) {
                this.ohos_router.back(options, params);
            } else {
                this.ohos_router.back(options);
            }
        });
    }

    clear() {
        withInstanceId(this.instanceId_, () => {
            this.ohos_router.clear();
        });
    }

    getLength() {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_router.getLength();
        });
    }

    getStackSize() {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_router.getStackSize();
        });
    }

    getState() {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_router.getState();
        });
    }

    getStateByIndex(index) {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_router.getStateByIndex(index);
        });
    }

    getStateByUrl(url) {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_router.getStateByUrl(url);
        });
    }

    showAlertBeforeBackPage(options) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_router.showAlertBeforeBackPage(options);
        });
    }

    hideAlertBeforeBackPage() {
        withInstanceId(this.instanceId_, () => {
            this.ohos_router.hideAlertBeforeBackPage();
        });
    }

    getParams() {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_router.getParams();
        });
    }

    pushNamedRoute(options, modeOrCallback, callback) {
        return withInstanceId(this.instanceId_, () => {
            if (typeof callback === 'undefined' && typeof modeOrCallback === 'undefined') {
                return this.ohos_router.pushNamedRoute(options);
            }
            else if (typeof callback !== 'undefined' && typeof modeOrCallback !== 'undefined') {
                this.ohos_router.pushNamedRoute(options, modeOrCallback, callback);
            }
            else if (typeof callback === 'undefined' && typeof modeOrCallback !== 'undefined') {
                let promise = this.ohos_router.pushNamedRoute(options, modeOrCallback);
                if (promise) {
                    return promise;
                }
            }
        });
    }

    replaceNamedRoute(options, modeOrCallback, callback) {
        return withInstanceId(this.instanceId_, () => {
            if (typeof callback === 'undefined' && typeof modeOrCallback === 'undefined') {
                return this.ohos_router.replaceNamedRoute(options);
            }
            else if (typeof callback !== 'undefined' && typeof modeOrCallback !== 'undefined') {
                this.ohos_router.replaceNamedRoute(options, modeOrCallback, callback);
            }
            else if (typeof callback === 'undefined' && typeof modeOrCallback !== 'undefined') {
                let promise = this.ohos_router.replaceNamedRoute(options, modeOrCallback);
                if (promise) {
                    return promise;
                }
            }
        });
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
        withInstanceId(this.instanceId_, () => {
            this.ohos_prompt.showToast(options);
        });
    }

    openToast(options) {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_prompt.openToast(options);
        });
    }

    closeToast(toastId) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_prompt.closeToast(toastId);
        });
    }

    showDialog(options, callback) {
        return withInstanceId(this.instanceId_, () => {
            if (typeof callback !== 'undefined') {
                this.ohos_prompt.showDialog(options, callback);
            }
            else {
                return this.ohos_prompt.showDialog(options);
            }
        });
    }

    openCustomDialog(content, options) {
        return withInstanceId(this.instanceId_, () => {
            if (arguments.length === 2) {
                return this.ohos_prompt.openCustomDialog(content.getFrameNode(), options);
            }
            else {
                if (content.builderNode_ === undefined) {
                    return this.ohos_prompt.openCustomDialog(content);
                }
                else {
                    return this.ohos_prompt.openCustomDialog(content.getFrameNode());
                }
            }
        });
    }

    openCustomDialogWithController(content, controller, options) {
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        let isDialogController = controller instanceof this.ohos_prompt.DialogController;
        if (!isDialogController) {
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        return withInstanceId(this.instanceId_, () => {
            if (typeof options === 'undefined') {
                return this.ohos_prompt.openCustomDialogWithController(content.getFrameNode(), controller);
            }
            return this.ohos_prompt.openCustomDialogWithController(content.getFrameNode(), controller, options);
        });
    }

    presentCustomDialog(builder, controller, options) {
        return withInstanceId(this.instanceId_, () => {
            if (typeof controller === 'undefined' && typeof options === 'undefined') {
                return this.ohos_prompt.presentCustomDialog(builder);
            }
            let paramErrMsg =
                'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
                ' 2. Incorrect parameter types; 3. Parameter verification failed.';
            let isDialogController = controller instanceof this.ohos_prompt.DialogController;
            if (!isDialogController) {
                return new Promise((resolve, reject) => {
                    reject({ message: paramErrMsg, code: 401 });
                });
            }
            if (typeof options === 'undefined') {
                return this.ohos_prompt.presentCustomDialog(builder, controller);
            }
            return this.ohos_prompt.presentCustomDialog(builder, controller, options);
        });
    }

    updateCustomDialog(content, options) {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_prompt.updateCustomDialog(content.getFrameNode(), options);
        });
    }

    closeCustomDialog(content) {
        return withInstanceId(this.instanceId_, () => {
            if (typeof content === 'number') {
                this.ohos_prompt.closeCustomDialog(content);
            }
            else {
                return this.ohos_prompt.closeCustomDialog(content.getFrameNode());
            }
        });
    }

    getTopOrder() {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_prompt.__getTopOrder__();
        });
    }

    getBottomOrder() {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_prompt.__getBottomOrder__();
        });
    }

    openPopup(content, target, options) {
        let argLength = arguments.length;
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        if (argLength < 2 || argLength > 3 || content === null || content === undefined || target === null || target === undefined) {
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        return withInstanceId(this.instanceId_, () => {
            if (argLength === 2) {
                return Context.openPopup(content.getNodePtr(), target);
            } else {
                return Context.openPopup(content.getNodePtr(), target, options);
            }
        });
    }

    updatePopup(content, options, partialUpdate) {
        let argLength = arguments.length;
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        if (argLength < 2 || argLength > 3 || content === null || content === undefined || options === null || options === undefined) {
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        return withInstanceId(this.instanceId_, () => {
            if (argLength === 2) {
                return Context.updatePopup(content.getNodePtr(), options);
            } else {
                return Context.updatePopup(content.getNodePtr(), options, partialUpdate);
            }
        });
    }

    closePopup(content) {
        let argLength = arguments.length;
        const paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        if (argLength !== 1 || content === null || content === undefined) {
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        return withInstanceId(this.instanceId_, () => {
            return Context.closePopup(content.getNodePtr());
        });
    }

    openMenu(content, target, options) {
        let argLength = arguments.length;
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        if (argLength < 2 || argLength > 3 || content === null || content === undefined || target === null || target === undefined) {
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        return withInstanceId(this.instanceId_, () => {
            if (argLength === 2) {
                return Context.openMenu(content.getNodePtr(), target);
            } else {
                return Context.openMenu(content.getNodePtr(), target, options);
            }
        });
    }

    updateMenu(content, options, partialUpdate) {
        let argLength = arguments.length;
        let paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        if (argLength < 2 || argLength > 3 || content === null || content === undefined || options === null || options === undefined) {
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        return withInstanceId(this.instanceId_, () => {
            if (argLength === 2) {
                return Context.updateMenu(content.getNodePtr(), options);
            } else {
                return Context.updateMenu(content.getNodePtr(), options, partialUpdate);
            }
        });
    }

    closeMenu(content) {
        let argLength = arguments.length;
        const paramErrMsg =
            'Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;' +
            ' 2. Incorrect parameter types; 3. Parameter verification failed.';
        if (argLength !== 1 || content === null || content === undefined) {
            return new Promise((resolve, reject) => {
                reject({ message: paramErrMsg, code: 401 });
            });
        }
        return withInstanceId(this.instanceId_, () => {
            return Context.closeMenu(content.getNodePtr());
        });
    }

    showActionMenu(options, callback) {
        return withInstanceId(this.instanceId_, () => {
            if (typeof callback !== 'undefined') {
                this.ohos_prompt.showActionMenu(options, callback);
            }
            else {
                return this.ohos_prompt.showActionMenu(options);
            }
        });
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
        withInstanceId(this.instanceId_, () => {
            this.ohos_atomicServiceBar.setVisible(visible);
        });
    }

    setBackgroundColor(color) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_atomicServiceBar.setBackgroundColor(color);
        });
    }

    setTitleContent(content) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_atomicServiceBar.setTitleContent(content);
        });
    }

    setTitleFontStyle(font) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_atomicServiceBar.setTitleFontStyle(font);
        });
    }

    setIconColor(color) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_atomicServiceBar.setIconColor(color);
        });
    }

    getBarRect() {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_atomicServiceBar.getBarRect();
        });
    }

    onBarRectChange(callback) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_atomicServiceBar.onBarRectChange(callback);
        });
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
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_overlayManager.setOverlayManagerOptions(options);
        });
    }

    getOverlayManagerOptions() {
        return withInstanceId(this.instanceId_, () => {
            return this.ohos_overlayManager.getOverlayManagerOptions();
        });
    }

    addComponentContent(content, index) {
        withInstanceId(this.instanceId_, () => {
            if (typeof index !== 'undefined') {
                this.ohos_overlayManager.addFrameNode(content.getFrameNode(), index);
            } else {
                this.ohos_overlayManager.addFrameNode(content.getFrameNode());
            }
        });
    }

    addComponentContentWithOrder(content, levelOrder) {
        withInstanceId(this.instanceId_, () => {
            if (typeof levelOrder !== 'undefined') {
                this.ohos_overlayManager.addFrameNodeWithOrder(content.getFrameNode(), levelOrder);
            } else {
                this.ohos_overlayManager.addFrameNodeWithOrder(content.getFrameNode());
            }
        });
    }

    removeComponentContent(content) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_overlayManager.removeFrameNode(content.getFrameNode());
        });
    }

    showComponentContent(content) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_overlayManager.showNode(content.getFrameNode());
        });
    }

    hideComponentContent(content) {
        withInstanceId(this.instanceId_, () => {
            this.ohos_overlayManager.hideNode(content.getFrameNode());
        });
    }

    showAllComponentContents() {
        withInstanceId(this.instanceId_, () => {
            this.ohos_overlayManager.showAllFrameNodes();
        });
    }

    hideAllComponentContents() {
        withInstanceId(this.instanceId_, () => {
            this.ohos_overlayManager.hideAllFrameNodes();
        });
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
        withInstanceId(this.instanceId_, () => {
            TextMenu.setMenuOptions(textMenuOptions);
        });
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

class Magnifier {
    /**
     * Construct new instance of Magnifier.
     * initialize with instanceId.
     * @param instanceId obtained on the c++ side.
     * @since 22
     */
    constructor(instanceId) {
        this.instanceId_ = instanceId;
    }

    bind(id) {
        withInstanceId(this.instanceId_, () => {
            MagnifierController.bind(id);
        });
    }

    show(x, y) {
        withInstanceId(this.instanceId_, () => {
            MagnifierController.show(x, y);
        });
    }

    unbind() {
        withInstanceId(this.instanceId_, () => {
            MagnifierController.unbind();
        });
    }
}

/**
 * Helper function to wrap operations with syncInstanceId/restoreInstanceId
 * Ensures restoreInstanceId is always called, even on exceptions
 * @param {number} instanceId - The instance ID to sync
 * @param {Function} callback - The operation to execute
 * @returns {*} The result of callback
 */
function withInstanceId(instanceId, callback) {
    __JSScopeUtil__.syncInstanceId(instanceId);
    try {
        return callback();
    } finally {
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

function __getResourceId__(params) {
    let resName = '';
    if (params.params.length > 0) {
        resName = params.params[0];
    }
    let bundleName = params.bundleName;
    let moduleName = params.moduleName;

    const re = new RegExp('^\\[\\S+]');
    resName = resName.replace(re, 'app'); // Process [hsp].type.name. GetResId only accept app or sys format.
    return getUINativeModule().resource.getResourceId(resName, bundleName, moduleName);
}
