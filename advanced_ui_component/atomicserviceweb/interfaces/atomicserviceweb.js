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

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {
    });
}
const web_webview = requireNapi('web.webview');
const router = requireNapi('router');
const deviceInfo = requireNapi('deviceInfo');
const geoLocationManager = requireNapi('geoLocationManager');
const bundleManager = requireNapi('bundle.bundleManager');
const abilityAccessCtrl = requireNapi('abilityAccessCtrl');
const connection = requireNapi('net.connection');
const request = requireNapi('request');
const fs = requireNapi('file.fs');
const util = requireNapi('util');
const photoAccessHelper = requireNapi('file.photoAccessHelper');
const filePreview = globalThis.requireNapi('filemanagement.filepreview', false, '', 'hms');
const fileUri = requireNapi('file.fileuri');
const picker = requireNapi('multimedia.cameraPicker');
const filePicker = requireNapi('file.picker');
const atomicServiceWebNapi = requireInternal('atomicservice.AtomicServiceWeb');

class Error {
    constructor(e11, f11) {
        this.code = e11;
        this.message = f11;
    }
}

class JsApiConfig {
    constructor(a11, b11, c11, d11) {
        this.apiName = a11;
        this.minVersion = b11;
        this.maxVersion = c11;
        this.requiredFieldNames = d11;
    }
}

const LOG_ENABLE = true;
const LOG_PREFIX = '[AtomicServiceWebLog]';
const UPLOAD_IMAGE_CACHE_DIR = '/cache/';
const JAVA_SCRIPT_PROXY_OBJECT_NAME = 'atomicServiceProxy';
const JAVA_SCRIPT_PROXY_API_NAME_LIST = ['invokeJsApi'];
const ATOMIC_SERVICE_JS_API_MAP = new Map();
const registerJsApi = (v10, w10, x10, y10, z10) => {
    ATOMIC_SERVICE_JS_API_MAP.set(v10, new JsApiConfig(w10, x10, y10, z10));
};
const MAX_VERSION = '99.99.99';
const ATOMIC_SERVICE_JS_SDK_CURRENT_VERSION = '1.0.0';
const PERMISSION_APPROXIMATELY_LOCATION = 'ohos.permission.APPROXIMATELY_LOCATION';
const SYSTEM_INTERNAL_ERROR = new Error(500, 'System internal error.');
const JS_API_INVALID_INVOKE_ERROR = new Error(200001, 'Invalid invoke.');
const PARAM_REQUIRED_ERROR_CODE = 200002;
const PARAM_NUMBER_POSITIVE_ERROR_CODE = 200003;
const ROUTER_PARAM_MODE_INVALID_ERROR = new Error(200004, 'Param mode is invalid.');
const BACK_URL_NOT_EXIST_OR_OPENED_ERROR = new Error(200005, 'Url is not exist or opened, can not be back.');
const NAV_PATH_STACK_NOT_EXIST_ERROR_CODE = 200006;
const POP_PATH_NAME_NOT_EXIST_ERROR = new Error(200007, 'Name is not exist or opened, can not be pop.');
const POP_PATH_PARAM_INDEX_INVALID_ERROR = new Error(200008, 'Param index is invalid.');
const POP_PATH_INDEX_OUT_OF_RANGE_ERROR = new Error(200009, 'The Index is out of range.');
const UPLOAD_IMAGE_FILES_REQUIRED_ERROR = new Error(200010, 'Param files is required.');
const UPLOAD_IMAGE_FILE_NOT_EXIST_ERROR_CODE = 200011;
const UPLOAD_IMAGE_FILES_URI_REQUIRED_ERROR = new Error(200012, 'Param uri of files is required.');
const UPLOAD_FILE_ERROR = new Error(200013, 'Upload file error.');
const IMAGE_CAN_NOT_PREVIEW_ERROR = new Error(200014, 'The filePath can not preview.');
const NETWORK_NO_ACTIVE_ERROR = new Error(200015, 'The network is not active.');
{
    registerJsApi('router.pushUrl', 'pushUrl', '1.0.0', MAX_VERSION, ['url']);
    registerJsApi('router.replaceUrl', 'replaceUrl', '1.0.0', MAX_VERSION, ['url']);
    registerJsApi('router.back', 'backUrl', '1.0.0', MAX_VERSION, []);
    registerJsApi('router.clear', 'clearUrl', '1.0.0', MAX_VERSION, []);
    registerJsApi('navPathStack.pushPath', 'pushPath', '1.0.0', MAX_VERSION, ['name']);
    registerJsApi('navPathStack.replacePath', 'replacePath', '1.0.0', MAX_VERSION, ['name']);
    registerJsApi('navPathStack.pop', 'popPath', '1.0.0', MAX_VERSION, []);
    registerJsApi('navPathStack.clear', 'clearPath', '1.0.0', MAX_VERSION, []);
    registerJsApi('asWeb.postMessage', 'postMessage', '1.0.0', MAX_VERSION, ['data']);
    registerJsApi('asWeb.getEnv', 'getEnv', '1.0.0', MAX_VERSION, []);
    registerJsApi('asWeb.checkJsApi', 'checkJsApi', '1.0.0', MAX_VERSION, ['jsApiList']);
    registerJsApi('cameraPicker.pick', 'pickCamera', '1.0.0', MAX_VERSION, ['mediaTypes', 'cameraPosition']);
    registerJsApi('photoViewPicker.select', 'selectPhoto', '1.0.0', MAX_VERSION, []);
    registerJsApi('filePreview.openPreview', 'openPreview', '1.0.0', MAX_VERSION, ['uri']);
    registerJsApi('request.uploadFile', 'uploadFile', '1.0.0', MAX_VERSION, ['url', 'files']);
    registerJsApi('request.downloadFile', 'downloadFile', '1.0.0', MAX_VERSION, ['url']);
    registerJsApi('connection.getNetworkType', 'getNetworkType', '1.0.0', MAX_VERSION, []);
    registerJsApi('location.getLocation', 'getLocation', '1.0.0', MAX_VERSION, []);
}

export class AtomicServiceWeb extends ViewPU {
    constructor(o10, p10, q10, r10 = -1, s10 = undefined, t10) {
        super(o10, q10, r10, t10);
        if (typeof s10 === "function") {
            this.paramsGenerator_ = s10;
        }
        this.__src = new SynchedPropertyObjectOneWayPU(p10.src, this, "src");
        this.navPathStack = undefined;
        this.onMessage = () => {
        };
        this.context = getContext(this);
        this.controller = new web_webview.WebviewController();
        this.schemeHandler = new web_webview.WebSchemeHandler();
        this.atomicService = undefined;
        this.atomicServiceProxy = undefined;
        this.setInitiallyProvidedValue(p10);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(n10) {
        if (n10.navPathStack !== undefined) {
            this.navPathStack = n10.navPathStack;
        }
        if (n10.onMessage !== undefined) {
            this.onMessage = n10.onMessage;
        }
        if (n10.context !== undefined) {
            this.context = n10.context;
        }
        if (n10.controller !== undefined) {
            this.controller = n10.controller;
        }
        if (n10.schemeHandler !== undefined) {
            this.schemeHandler = n10.schemeHandler;
        }
        if (n10.atomicService !== undefined) {
            this.atomicService = n10.atomicService;
        }
        if (n10.atomicServiceProxy !== undefined) {
            this.atomicServiceProxy = n10.atomicServiceProxy;
        }
    }

    updateStateVars(m10) {
        this.__src.reset(m10.src);
    }

    purgeVariableDependenciesOnElmtId(l10) {
        this.__src.purgeDependencyOnElmtId(l10);
    }

    aboutToBeDeleted() {
        this.__src.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get src() {
        return this.__src.get();
    }

    set src(k10) {
        this.__src.set(k10);
    }

    aboutToAppear() {
        if (!this.atomicService) {
            this.atomicService = new AtomicServiceApi(this.context, this.navPathStack, this.onMessage);
            this.atomicServiceProxy = new AtomicServiceProxy(this.atomicService);
        }
    }

    aboutToDisappear() {
        this.atomicService?.notifyMessage();
    }

    initialRender() {
        this.observeComponentCreation2((b10, c10) => {
            Web.create({ src: this.src, controller: this.controller });
            Web.fileAccess(true);
            Web.imageAccess(true);
            Web.onlineImageAccess(true);
            Web.javaScriptAccess(true);
            Web.domStorageAccess(true);
            Web.geolocationAccess(true);
            Web.onControllerAttached(() => {
                this.registerJavaScriptProxy();
                this.schemeHandler.onRequestStart((j10) => {
                    return !this.checkUrl(j10.getRequestUrl());
                });
                this.controller.setWebSchemeHandler('https', this.schemeHandler);
            });
            Web.onOverrideUrlLoading((h10) => {
                return !this.checkUrl(h10.getRequestUrl());
            });
            Web.onLoadIntercept(g10 => {
                return !this.checkUrl(g10.data.getRequestUrl());
            });
        }, Web);
    }

    registerJavaScriptProxy() {
        try {
            this.controller.registerJavaScriptProxy(this.atomicServiceProxy, JAVA_SCRIPT_PROXY_OBJECT_NAME, JAVA_SCRIPT_PROXY_API_NAME_LIST);
        } catch (y9) {
            let z9 = y9;
            console.error(`AtomicServiceWeb registerJavaScriptProxy failed, code is ${z9.code}, message is ${z9.message}`);
        }
    }

    cutUrl(q1) {
        if (q1) {
            let a2 = q1.indexOf('?');
            if (a2 > -1) {
                return q1.substring(0, a2);
            }
        }
        return q1;
    }

    checkUrl(q1) {
        if (!q1) {
            return false;
        }
        if (q1.startsWith('resource://rawfile')) {
            return true;
        }
        try {
            let w1 = this.context.abilityInfo.bundleName;
            let t1 = 'webView';
            q1 = this.cutUrl(q1);
            let res = atomicServiceWebNapi.checkUrl(w1, t1, q1);
            console.log(`AtomicServiceWeb checkUrl res=${res} bundleName=${w1} domainType=${t1} url=${q1}`);
            return res === 0;
        } catch (j2) {
            let n2 = j2;
            console.error(`AtomicServiceWeb checkUrl failed, code is ${n2.code}, message is ${n2.message}`);
            return false;
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class AtomicServiceProxy {
    constructor(r9) {
        this.atomicService = r9;
    }

    invokeJsApi(m9, n9) {
        try {
            n9 = n9 || {};
            if (!m9 || !ATOMIC_SERVICE_JS_API_MAP.has(m9)) {
                this.atomicService.errorWithCodeAndMsg(JS_API_INVALID_INVOKE_ERROR, n9);
                return;
            }
            this.atomicService.logOptions(m9, n9);
            let p9 = ATOMIC_SERVICE_JS_API_MAP.get(m9);
            if (!this.atomicService.checkRequiredFieldInOptions(p9, n9)) {
                return;
            }
            let q9 = this.atomicService;
            q9[p9?.apiName](n9);
        } catch (o9) {
            this.atomicService.error(o9, n9);
        }
    }
}

class AtomicService {
    constructor(i9, j9, k9) {
        this.messageDataList = [];
        this.onMessage = () => {
        };
        this.context = i9;
        this.navPathStack = j9;
        this.onMessage = k9 ? k9 : this.onMessage;
    }

    success(g9, h9) {
        h9?.callback && h9?.callback(undefined, g9);
    }

    error(e9, f9) {
        f9?.callback && f9?.callback(new Error(e9.code ? e9.code : SYSTEM_INTERNAL_ERROR.code, e9.message ? e9.message : SYSTEM_INTERNAL_ERROR.message));
    }

    errorWithCodeAndMsg(c9, d9) {
        d9?.callback && d9?.callback(c9);
    }

    consoleLog(b9) {
        if (LOG_ENABLE) {
            console.log(`${LOG_PREFIX} ${b9}`);
        }
    }

    consoleError(a9) {
        if (LOG_ENABLE) {
            console.error(`${LOG_PREFIX} ${a9}`);
        }
    }

    logOptions(y8, z8) {
        this.consoleLog(`${y8} options=${JSON.stringify(z8)}`);
    }

    checkParamRequired(v8, w8, x8) {
        if (w8 === undefined || w8 === null || w8 === '') {
            this.errorWithCodeAndMsg(new Error(PARAM_REQUIRED_ERROR_CODE, `Param ${v8} is required.`), x8);
            return false;
        }
        return true;
    }

    checkNumberParamPositive(s8, t8, u8) {
        if (t8 <= 0) {
            this.errorWithCodeAndMsg(new Error(PARAM_NUMBER_POSITIVE_ERROR_CODE, `Param ${s8} must be a positive number.`), u8);
            return false;
        }
        return true;
    }

    checkRequiredFieldInOptions(n8, o8) {
        if (!n8) {
            return false;
        }
        if (!n8.requiredFieldNames) {
            return true;
        }
        let p8 = o8;
        for (let i3 = 0; i3 < n8.requiredFieldNames.length; i3++) {
            let m3 = n8.requiredFieldNames[i3];
            if (!this.checkParamRequired(m3, p8[m3], o8)) {
                return false;
            }
        }
        return true;
    }

    checkRouterMode(l8, m8) {
        if (!l8 || l8 === 'Single' || l8 === 'Standard') {
            return true;
        }
        this.errorWithCodeAndMsg(ROUTER_PARAM_MODE_INVALID_ERROR, m8);
        return false;
    }

    parseRouterMode(k8) {
        return k8 === 'Single' ? router.RouterMode.Single : router.RouterMode.Standard;
    }

    getRouterIndexByDelta(g8) {
        let h8 = parseInt(router.getLength());
        for (let i8 = h8; i8 > 0; i8--) {
            let j8 = router.getStateByIndex(i8);
            if (j8?.name && g8-- == 0) {
                return i8;
            }
        }
        return 1;
    }

    checkBackUrlExists(a8, b8) {
        let c8 = parseInt(router.getLength());
        for (let d8 = c8; d8 > 0; d8--) {
            let e8 = router.getStateByIndex(d8);
            if (e8?.name) {
                let f8 = e8?.path + e8?.name;
                if (f8 === a8) {
                    return true;
                }
            }
        }
        this.errorWithCodeAndMsg(BACK_URL_NOT_EXIST_OR_OPENED_ERROR, b8);
        return false;
    }

    checkNavPathStack(y7, z7) {
        if (!this.navPathStack) {
            this.errorWithCodeAndMsg(new Error(NAV_PATH_STACK_NOT_EXIST_ERROR_CODE, `Current page is not NavDestination, not support ${y7}().`), z7);
            return false;
        }
        return true;
    }

    getNavPathIndexByDelta(w7) {
        let x7 = this.navPathStack?.getAllPathName();
        if (!x7 || x7.length == 0) {
            return -1;
        }
        return x7.length > w7 ? (x7.length - w7 - 1) : -1;
    }

    onPopHandler(u7, v7) {
        if (!u7?.info || !v7) {
            return;
        }
        v7(new OnPopEvent(u7.info.name, u7.info.param, u7.result));
    }

    getCurrentNavPathInfo() {
        let s7 = this.navPathStack?.getAllPathName();
        let t7 = (s7 && s7.length > 0) ? new NavPathInfo(s7[s7.length - 1], s7.length - 1) :
            new NavPathInfo(undefined, -1);
        if (t7.index >= 0) {
            t7.param = this.navPathStack?.getParamByIndex(t7.index);
        }
        return t7;
    }

    notifyMessage() {
        if (this.messageDataList.length <= 0) {
            return;
        }
        this.onMessage({ data: this.messageDataList });
        this.messageDataList = [];
    }

    isJsApiEnable(q7) {
        if (!q7) {
            return false;
        }
        if (this.compareVersion(q7.minVersion, ATOMIC_SERVICE_JS_SDK_CURRENT_VERSION) &&
        this.compareVersion(ATOMIC_SERVICE_JS_SDK_CURRENT_VERSION, q7.maxVersion)) {
            return true;
        }
        return false;
    }

    compareVersion(h7, i7) {
        if (!h7 || !i7) {
            return false;
        }
        let j7 = h7.split('.').map(p7 => parseInt(p7));
        let k7 = i7.split('.').map(o7 => parseInt(o7));
        for (let n7 = 0; n7 < j7.length && n7 < k7.length; n7++) {
            if (j7[n7] < k7[n7]) {
                return true;
            } else if (j7[n7] > k7[n7]) {
                return false;
            }
        }
        if (j7.length < k7.length) {
            return true;
        }
        if (j7.length > k7.length) {
            return false;
        }
        return true;
    }

    getUri(g7) {
        if (!g7 || g7.startsWith('file://')) {
            return g7;
        }
        return fileUri.getUriFromPath(g7);
    }

    async checkUploadFile(w6) {
        if (!w6.files || w6.files.length <= 0) {
            this.errorWithCodeAndMsg(UPLOAD_IMAGE_FILES_REQUIRED_ERROR, w6);
            return new CheckUploadFileResult(false);
        }
        let x6 = new Map();
        for (let y6 = 0; y6 < w6.files?.length; y6++) {
            let z6 = w6.files[y6];
            if (!z6.uri) {
                this.errorWithCodeAndMsg(UPLOAD_IMAGE_FILES_URI_REQUIRED_ERROR, w6);
                return new CheckUploadFileResult(false);
            }
            if (!z6.uri.startsWith('file://') && !fs.accessSync(z6.uri, fs.AccessModeType.EXIST)) {
                this.errorWithCodeAndMsg(new Error(UPLOAD_IMAGE_FILE_NOT_EXIST_ERROR_CODE, `File uri ${z6.uri} is not exist.`), w6);
                return new CheckUploadFileResult(false);
            }
            let a7 = z6.uri;
            let b7 = z6.uri;
            if (b7.indexOf(UPLOAD_IMAGE_CACHE_DIR) < 0) {
                let c7 = true;
                let d7 = b7.startsWith('file://') ? b7 : fileUri.getUriFromPath(z6.uri);
                b7 = this.context.cacheDir + '/' + b7.substring(b7.lastIndexOf('/') + 1);
                await fs.copy(d7, fileUri.getUriFromPath(b7)).catch((f7) => {
                    this.error(f7, w6);
                    c7 = false;
                });
                if (!c7) {
                    this.errorWithCodeAndMsg(UPLOAD_FILE_ERROR, w6);
                    return new CheckUploadFileResult(false);
                }
            }
            z6.uri = 'internal://' + b7.substring(b7.indexOf(UPLOAD_IMAGE_CACHE_DIR) + 1);
            x6.set(b7, a7);
        }
        return new CheckUploadFileResult(true, x6);
    }

    convertToRequestData(s6) {
        let t6 = [];
        if (s6) {
            s6.forEach(v6 => {
                if (!v6.name || !v6.value) {
                    return;
                }
                t6.push({ name: v6.name, value: v6.value });
            });
        }
        return t6;
    }

    convertToFile(o6) {
        let p6 = [];
        if (o6) {
            o6.forEach(r6 => {
                p6.push({
                    filename: r6.filename,
                    name: r6.name,
                    uri: r6.uri,
                    type: r6.type
                });
            });
        }
        return p6;
    }

    handleUploadFileResult(h6, i6, j6) {
        let k6 = [];
        if (h6) {
            h6.forEach(m6 => {
                let n6 = m6.path ? i6.get(m6.path) : m6.path;
                k6.push(new UploadFileTaskState(n6 ? n6 : m6.path, m6.responseCode, m6.message));
            });
        }
        this.success(new UploadFileResult(k6), j6);
    }

    parseFileNameFromUrl(e6) {
        if (!e6) {
            return '';
        }
        let f6 = e6.split('?')[0];
        if (f6.indexOf('/') < 0) {
            return '';
        }
        let g6 = f6.lastIndexOf('/');
        if (g6 == (f6.length - 1)) {
            return '';
        }
        return f6.substring(g6 + 1);
    }

    saveDownloadFile(r5, s5, t5, u5) {
        let v5 = new filePicker.DocumentViewPicker();
        v5.save({
            newFileNames: [s5]
        }).then(z5 => {
            let a6 = z5[0];
            fs.copy(fileUri.getUriFromPath(r5), a6).then(() => {
                u5 && u5(a6);
            }).catch((d6) => {
                this.error(d6, t5);
            });
        }).catch((y5) => {
            this.error(y5, t5);
        });
    }

    checkAccessToken(n5) {
        let o5 = bundleManager.getBundleInfoForSelfSync(bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION);
        let p5 = o5.appInfo.accessTokenId;
        let q5 = abilityAccessCtrl.createAtManager();
        return q5.checkAccessToken(p5, n5);
    }

    checkPermissions(b5, c5) {
        this.checkAccessToken(b5).then(g5 => {
            if (g5 == abilityAccessCtrl.GrantStatus.PERMISSION_GRANTED) {
                c5(undefined);
            } else {
                let h5 = abilityAccessCtrl.createAtManager();
                h5.requestPermissionsFromUser(this.context, [b5]).then(l5 => {
                    for (let m5 = 0; m5 < l5.authResults.length; m5++) {
                        if (l5.authResults[m5] != 0) {
                            return;
                        }
                    }
                    c5(undefined);
                }).catch((k5) => {
                    c5(k5);
                });
            }
        }).catch((f5) => {
            c5(f5);
        });
    }
}

class AtomicServiceApi extends AtomicService {
    constructor(y4, z4, a5) {
        super(y4, z4, a5);
    }

    pushUrl(u4) {
        if (!this.checkRouterMode(u4.mode, u4)) {
            return;
        }
        router.pushUrl({ url: u4.url, params: u4.params }, this.parseRouterMode(u4.mode)).then(() => {
            this.success(new PushUrlResult(), u4);
        }).catch((x4) => {
            this.error(x4, u4);
        });
    }

    replaceUrl(q4) {
        if (!this.checkRouterMode(q4.mode, q4)) {
            return;
        }
        router.replaceUrl({ url: q4.url, params: q4.params }, this.parseRouterMode(q4.mode)).then(() => {
            this.success(new ReplaceUrlResult(), q4);
        }).catch((t4) => {
            this.error(t4, q4);
        });
    }

    backUrl(p4) {
        if (p4.url) {
            if (!this.checkBackUrlExists(p4.url, p4)) {
                return;
            }
            router.back({ url: p4.url, params: p4.params });
            this.success(new BackUrlResult(), p4);
        } else if (p4.index || p4.index === 0) {
            if (!this.checkNumberParamPositive('index', p4.index, p4)) {
                return;
            }
            router.back(p4.index, p4.params);
            this.success(new BackUrlResult(), p4);
        } else if (p4.delta || p4.delta === 0) {
            if (!this.checkNumberParamPositive('delta', p4.delta, p4)) {
                return;
            }
            router.back(this.getRouterIndexByDelta(p4.delta), p4.params);
            this.success(new BackUrlResult(), p4);
        } else {
            router.back();
            this.success(new BackUrlResult(), p4);
        }
    }

    clearUrl(o4) {
        router.clear();
        this.success(new ClearUrlResult(), o4);
    }

    pushPath(m4) {
        if (!this.checkNavPathStack('navPathStack.pushPath', m4)) {
            return;
        }
        this.navPathStack?.pushPath({
            name: m4.name,
            param: m4.param,
            onPop: n4 => this.onPopHandler(n4, m4.onPop)
        }, m4.animated);
        this.success(new PushPathResult(), m4);
    }

    replacePath(k4) {
        if (!this.checkNavPathStack('navPathStack.replacePath', k4)) {
            return;
        }
        this.navPathStack?.replacePath({
            name: k4.name,
            param: k4.param,
            onPop: l4 => this.onPopHandler(l4, k4.onPop)
        }, k4.animated);
        this.success(new ReplacePathResult(), k4);
    }

    popPath(h4) {
        if (!this.checkNavPathStack('navPathStack.pop', h4)) {
            return;
        }
        if (h4.name) {
            let j4 = this.navPathStack?.popToName(h4.name, h4.result, h4.animated);
            if (j4 === undefined || j4 === -1) {
                this.errorWithCodeAndMsg(POP_PATH_NAME_NOT_EXIST_ERROR, h4);
                return;
            }
        } else if (h4.index || h4.index === 0) {
            if (h4.index < -1) {
                this.errorWithCodeAndMsg(POP_PATH_PARAM_INDEX_INVALID_ERROR, h4);
                return;
            }
            if (h4.index > this.getCurrentNavPathInfo().index) {
                this.errorWithCodeAndMsg(POP_PATH_INDEX_OUT_OF_RANGE_ERROR, h4);
                return;
            }
            this.navPathStack?.popToIndex(h4.index, h4.result, h4.animated);
        } else if (h4.delta || h4.delta === 0) {
            if (!this.checkNumberParamPositive('delta', h4.delta, h4)) {
                return;
            }
            this.navPathStack?.popToIndex(this.getNavPathIndexByDelta(h4.delta), h4.result, h4.animated);
        } else {
            this.navPathStack?.pop(h4.result, h4.animated);
        }
        let i4 = this.getCurrentNavPathInfo();
        this.success(new PopPathResult(i4.name, i4.index, i4.param), h4);
    }

    clearPath(g4) {
        if (!this.checkNavPathStack('navPathStack.clear', g4)) {
            return;
        }
        this.navPathStack?.clear(g4.animated);
        this.success(new ClearPathResult(), g4);
    }

    postMessage(c3) {
        c3.data && this.messageDataList.push(c3.data);
        this.success(new PostMessageResult(), c3);
    }

    getEnv(e4) {
        let f4 = new GetEnvResult();
        f4.deviceType = deviceInfo.deviceType;
        f4.brand = deviceInfo.brand;
        f4.productModel = deviceInfo.productModel;
        f4.osFullName = deviceInfo.osFullName;
        this.success(f4, e4);
    }

    checkJsApi(a4) {
        let b4 = new Map();
        a4.jsApiList?.forEach(d4 => {
            b4[d4] = this.isJsApiEnable(ATOMIC_SERVICE_JS_API_MAP.get(d4));
        });
        this.success(new CheckJsApiResult(b4), a4);
    }

    pickCamera(v3) {
        picker.pick(this.context, v3.mediaTypes, {
            cameraPosition: v3.cameraPosition,
            saveUri: v3.saveUri,
            videoDuration: v3.videoDuration
        }).then((z3) => {
            this.success(new PickCameraResult(z3.resultCode, z3.resultUri, z3.mediaType), v3);
        }).catch((y3) => {
            this.error(y3, v3);
        });
    }

    selectPhoto(p3) {
        let q3 = new photoAccessHelper.PhotoViewPicker();
        q3.select({
            MIMEType: p3.mimeType,
            maxSelectNumber: p3.maxSelectNumber,
            isPhotoTakingSupported: p3.isPhotoTakingSupported,
            isEditSupported: p3.isEditSupported,
            isSearchSupported: p3.isSearchSupported,
            recommendationOptions: {
                recommendationType: p3.recommendationType
            },
            preselectedUris: p3.preselectedUris
        }).then((u3) => {
            this.success(new SelectPhotoResult(u3.photoUris, u3.isOriginalPhoto), p3);
        }).catch((t3) => {
            this.error(t3, p3);
        });
    }

    openPreview(g3) {
        let h3 = this.getUri(g3.uri);
        filePreview.canPreview(this.context, h3).then((l3) => {
            if (!l3) {
                this.errorWithCodeAndMsg(IMAGE_CAN_NOT_PREVIEW_ERROR, g3);
                return;
            }
            filePreview.openPreview(this.context, {
                uri: h3,
                mimeType: g3.mimeType,
                title: g3.title
            }).then(() => {
                this.success(new OpenPreviewResult(), g3);
            }).catch((o3) => {
                this.error(o3, g3);
            });
        }).catch((k3) => {
            this.error(k3, g3);
        });
    }

    uploadFile(s2) {
        this.checkUploadFile(s2).then(w2 => {
            if (!w2.checkResult) {
                return;
            }
            let x2 = {
                url: s2.url,
                header: s2.header,
                method: s2.method,
                files: this.convertToFile(s2.files),
                data: this.convertToRequestData(s2.data)
            };
            this.consoleLog('uploadFile uploadConfig=' + JSON.stringify(x2));
            request.uploadFile(this.context, x2).then((b3) => {
                b3.on('complete', (f3) => {
                    this.handleUploadFileResult(f3, w2.uriMap, s2);
                });
                b3.on('fail', (e3) => {
                    this.handleUploadFileResult(e3, w2.uriMap, s2);
                });
            }).catch((a3) => {
                this.error(a3, s2);
            });
        }).catch((v2) => {
            this.error(v2, s2);
        });
    }

    downloadFile(f2) {
        let g2 = f2.fileName ? f2.fileName : this.parseFileNameFromUrl(f2.url);
        let h2 = `${util.generateRandomUUID().replaceAll('-', '')}`;
        let i2 = `${this.context.cacheDir}/${h2}`;
        request.downloadFile(this.context, {
            url: f2.url,
            header: f2.header ? f2.header : new Object(),
            filePath: i2,
            enableMetered: f2.enableMetered,
            enableRoaming: f2.enableRoaming,
            networkType: f2.networkType,
            background: false
        }).then((m2) => {
            m2.on('complete', () => {
                this.saveDownloadFile(i2, g2, f2, r2 => {
                    this.success(new DownloadFileResult(r2), f2);
                });
            });
            m2.on('fail', y2 => {
                this.errorWithCodeAndMsg(new Error(y2, 'File download fail.'), f2);
            });
        }).catch((l2) => {
            this.error(l2, f2);
        });
    }

    getNetworkType(v1) {
        connection.getDefaultNet().then(z1 => {
            if (!z1 || z1.netId === 0) {
                this.errorWithCodeAndMsg(NETWORK_NO_ACTIVE_ERROR, v1);
                return;
            }
            connection.getNetCapabilities(z1).then(n2 => {
                let t2 = new GetNetworkTypeResult(n2.bearerTypes, n2.networkCap, n2.linkUpBandwidthKbps, n2.linkDownBandwidthKbps);
                this.success(t2, v1);
            }).catch((j2) => {
                this.error(j2, v1);
            });
        }).catch((y1) => {
            this.error(y1, v1);
        });
    }

    getLocation(n1) {
        this.checkPermissions(PERMISSION_APPROXIMATELY_LOCATION, p1 => {
            if (p1) {
                this.error(p1, n1);
                return;
            }
            geoLocationManager.getCurrentLocation({
                priority: n1.priority,
                scenario: n1.scenario,
                maxAccuracy: n1.maxAccuracy,
                timeoutMs: n1.timeoutMs
            }).then(t1 => {
                let u1 = new GetLocationResult(t1.latitude, t1.longitude, t1.altitude, t1.accuracy, t1.speed, t1.timeStamp, t1.direction, t1.timeSinceBoot,
                    t1.additions, t1.additionSize);
                this.success(u1, n1);
            }).catch((s1) => {
                this.error(s1, n1);
            });
        });
    }
}

class NavPathInfo {
    constructor(l1, m1) {
        this.name = l1;
        this.index = m1;
    }
}

class CheckUploadFileResult {
    constructor(j1, k1) {
        this.checkResult = j1;
        this.uriMap = k1;
    }
}

class BaseOptions {
}

class PushUrlOptions extends BaseOptions {
}

class PushUrlResult {
}

class ReplaceUrlOptions extends BaseOptions {
}

class ReplaceUrlResult {
}

class BackUrlOptions extends BaseOptions {
}

class BackUrlResult {
}

class ClearUrlOptions extends BaseOptions {
}

class ClearUrlResult {
}

class OnPopEvent {
    constructor(g1, h1, i1) {
        this.name = g1;
        this.param = h1;
        this.result = i1;
    }
}

class PushPathOptions extends BaseOptions {
}

class PushPathResult {
}

class ReplacePathOptions extends BaseOptions {
}

class ReplacePathResult {
}

class PopPathOptions extends BaseOptions {
}

class PopPathResult {
    constructor(d1, e1, f1) {
        this.name = d1;
        this.index = e1;
        this.param = f1;
    }
}

class ClearPathOptions extends BaseOptions {
}

class ClearPathResult {
}

class PostMessageOptions extends BaseOptions {
}

class PostMessageResult {
}

export class OnMessageEvent {
}

class GetEnvOptions extends BaseOptions {
}

class GetEnvResult {
}

class CheckJsApiOptions extends BaseOptions {
}

class CheckJsApiResult {
    constructor(c1) {
        this.checkResult = c1;
    }
}

class PickCameraOptions extends BaseOptions {
}

class PickCameraResult {
    constructor(z, a1, b1) {
        this.resultCode = z;
        this.resultUri = a1;
        this.mediaType = b1;
    }
}

class SelectPhotoOptions extends BaseOptions {
}

class SelectPhotoResult {
    constructor(x, y) {
        this.photoUris = x;
        this.isOriginalPhoto = y;
    }
}

class OpenPreviewOptions extends BaseOptions {
}

class OpenPreviewResult {
}

class UploadFileOptions extends BaseOptions {
}

class UploadFile {
    constructor(t, u, v, w) {
        this.filename = t;
        this.name = u;
        this.uri = v;
        this.type = w;
    }
}

class UploadRequestData {
}

class UploadFileResult {
    constructor(s) {
        this.taskStates = s;
    }
}

class UploadFileTaskState {
    constructor(p, q, r) {
        this.path = p;
        this.responseCode = q;
        this.message = r;
    }
}

class DownloadFileOptions extends BaseOptions {
}

class DownloadFileResult {
    constructor(o) {
        this.uri = o;
    }
}

class GetNetworkTypeOptions extends BaseOptions {
}

class GetNetworkTypeResult {
    constructor(k, l, m, n) {
        this.bearerTypes = k;
        this.networkCap = l;
        this.linkUpBandwidthKbps = m;
        this.linkDownBandwidthKbps = n;
    }
}

class GetLocationOptions extends BaseOptions {
}

class GetLocationResult {
    constructor(a, b, c, d, e, f, g, h, i, j) {
        this.latitude = a;
        this.longitude = b;
        this.altitude = c;
        this.accuracy = d;
        this.speed = e;
        this.timeStamp = f;
        this.direction = g;
        this.timeSinceBoot = h;
        this.additions = i;
        this.additionSize = j;
    }
}

export default {
    AtomicServiceWeb
}
