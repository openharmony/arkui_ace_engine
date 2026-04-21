/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import web_webview from '@ohos.web.webview';
import { ComplainInfo } from '../../complainApi/ComplainInfo';
import { ComplainParams } from '../../complainApi/ComplainParams';
import { ConfigVo, generateUUID } from '../../complainApi/ComplainUtils';
import { DeviceInfoUtil } from '../../complainApi/DeviceTypeUtil';
import deviceInfo from "@ohos.deviceInfo";
import hilog from "@ohos.hilog";
import { LanguageUtil } from '../../complainApi/LanguageUtil';
import { JsonUtils } from '../../complainApi/JsonUtil';
import { ComplainFileSelectUtil } from '../../complainApi/ComplainFileSelectUtil';
import { KeyCode } from "@ohos.multimodalInput.keyCode";
import connection from "@ohos.net.connection";
import inputMethod from "@ohos.inputMethod";
const TAG = 'complainSheetComponents';
const DOMAIN = 0x0f5c;
export class complainSheetComponents extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.stack = new NavPathStack();
        this.webviewController = new web_webview.WebviewController();
        this.params = new ComplainParams();
        this.fromSheet = false;
        this.__mediaPreviewTitleVisible = new ObservedPropertySimplePU(false, this, "mediaPreviewTitleVisible");
        this.__complainInfo = new ObservedPropertyObjectPU(new ComplainInfo(), this, "complainInfo");
        this.__customTitle = new ObservedPropertyObjectPU('', this, "customTitle");
        this.__title = new ObservedPropertyObjectPU('', this, "title");
        this.isWeb = false;
        this.__isShowLoading = new ObservedPropertySimplePU(true, this, "isShowLoading");
        this.isFinished = false;
        this.complainUrl = '';
        this.configVo = new ConfigVo();
        this.deviceType = '2in1';
        this.productEnvStr = 'https://complain-productEnvStr';
        this.devEnvStr = 'https://complain-devEnvStr';
        this.mirrorEnvStr = 'https://complain-mirrorEnvStr';
        this.tmpEnvStr = this.productEnvStr;
        this.canUploadCount = 5;
        this.context = this.getUIContext().getHostContext();
        this.themeStorage = ThemeColorMode.SYSTEM;
        this.back = () => {
            hilog.info(DOMAIN, TAG, 'Enter Back');
            if (this.mediaPreviewTitleVisible) {
                this.webviewController.runJavaScript('closePreviewPanel', () => {
                });
                if (this.complainInfo.hideMediaPreView) {
                    this.complainInfo.hideMediaPreView();
                }
                return true;
            }
            if (this.configVo.keyBoardHeight > 0) {
                let inputMethodController = inputMethod.getController();
                inputMethodController.stopInputSession();
                hilog.info(DOMAIN, TAG, 'keyboardHeight: ' + this.configVo.keyBoardHeight);
                return true;
            }
            try {
                if (this.webviewController.accessBackward()) {
                    hilog.info(DOMAIN, TAG, 'backward');
                    this.webviewController.backward();
                    return true;
                }
            }
            catch (e) {
                hilog.error(DOMAIN, TAG, 'complain accessBackward error: ', e);
            }
            if (this.params.onBackPressed) {
                this.params.onBackPressed();
            }
            else {
                this.params.pathInfo.pop();
            }
            return true;
        };
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.stack !== undefined) {
            this.stack = params.stack;
        }
        if (params.webviewController !== undefined) {
            this.webviewController = params.webviewController;
        }
        if (params.params !== undefined) {
            this.params = params.params;
        }
        if (params.fromSheet !== undefined) {
            this.fromSheet = params.fromSheet;
        }
        if (params.mediaPreviewTitleVisible !== undefined) {
            this.mediaPreviewTitleVisible = params.mediaPreviewTitleVisible;
        }
        if (params.complainInfo !== undefined) {
            this.complainInfo = params.complainInfo;
        }
        if (params.customTitle !== undefined) {
            this.customTitle = params.customTitle;
        }
        if (params.title !== undefined) {
            this.title = params.title;
        }
        if (params.isWeb !== undefined) {
            this.isWeb = params.isWeb;
        }
        if (params.isShowLoading !== undefined) {
            this.isShowLoading = params.isShowLoading;
        }
        if (params.isFinished !== undefined) {
            this.isFinished = params.isFinished;
        }
        if (params.complainUrl !== undefined) {
            this.complainUrl = params.complainUrl;
        }
        if (params.configVo !== undefined) {
            this.configVo = params.configVo;
        }
        if (params.deviceType !== undefined) {
            this.deviceType = params.deviceType;
        }
        if (params.productEnvStr !== undefined) {
            this.productEnvStr = params.productEnvStr;
        }
        if (params.devEnvStr !== undefined) {
            this.devEnvStr = params.devEnvStr;
        }
        if (params.mirrorEnvStr !== undefined) {
            this.mirrorEnvStr = params.mirrorEnvStr;
        }
        if (params.tmpEnvStr !== undefined) {
            this.tmpEnvStr = params.tmpEnvStr;
        }
        if (params.canUploadCount !== undefined) {
            this.canUploadCount = params.canUploadCount;
        }
        if (params.context !== undefined) {
            this.context = params.context;
        }
        if (params.themeStorage !== undefined) {
            this.themeStorage = params.themeStorage;
        }
        if (params.back !== undefined) {
            this.back = params.back;
        }
    }
    updateStateVars(params) {
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__mediaPreviewTitleVisible.purgeDependencyOnElmtId(rmElmtId);
        this.__complainInfo.purgeDependencyOnElmtId(rmElmtId);
        this.__customTitle.purgeDependencyOnElmtId(rmElmtId);
        this.__title.purgeDependencyOnElmtId(rmElmtId);
        this.__isShowLoading.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.__mediaPreviewTitleVisible.aboutToBeDeleted();
        this.__complainInfo.aboutToBeDeleted();
        this.__customTitle.aboutToBeDeleted();
        this.__title.aboutToBeDeleted();
        this.__isShowLoading.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get mediaPreviewTitleVisible() {
        return this.__mediaPreviewTitleVisible.get();
    }
    set mediaPreviewTitleVisible(newValue) {
        this.__mediaPreviewTitleVisible.set(newValue);
    }
    get complainInfo() {
        return this.__complainInfo.get();
    }
    set complainInfo(newValue) {
        this.__complainInfo.set(newValue);
    }
    get customTitle() {
        return this.__customTitle.get();
    }
    set customTitle(newValue) {
        this.__customTitle.set(newValue);
    }
    get title() {
        return this.__title.get();
    }
    set title(newValue) {
        this.__title.set(newValue);
    }
    get isShowLoading() {
        return this.__isShowLoading.get();
    }
    set isShowLoading(newValue) {
        this.__isShowLoading.set(newValue);
    }
    async aboutToAppear() {
        let navigationInfo = this.queryNavigationInfo();
        if (navigationInfo != undefined) {
            this.stack = navigationInfo.pathStack;
        }
        DeviceInfoUtil.init();
        const navParams = this.stack.getParamByIndex(this.stack.getIndexByName('complainSheetComponent')[0]);
        this.params.additionalContext = navParams;
    }
    async initComplainParams() {
        this.params.appId = '1111';
        this.params.sceneId = '1';
        this.params.subSceneId = '1';
        this.params.pathInfo = this.stack;
        this.params.deviceId = '123456789';
        this.params.additionalContext = { 'commandId': '12345', 'commentContent': 'XXXX' };
    }
    async initComplainInfo() {
        this.complainInfo.bundleName = 'xxx';
        this.complainInfo.traceId = generateUUID();
        this.complainInfo.osVer = DeviceInfoUtil.osVersion;
        this.complainInfo.deviceType = DeviceInfoUtil.deviceType;
        this.complainInfo.deviceModel = DeviceInfoUtil.deviceModel;
        this.complainInfo.osApi = String(DeviceInfoUtil.deviceSdkApiVersion);
        this.complainInfo.appVer = 'xxx';
        this.complainInfo.anonId = 'xxx';
        this.complainInfo.appId = this.params.appId;
        this.complainInfo.sceneId = this.params.sceneId;
        this.complainInfo.subSceneId = this.params.subSceneId;
        if (this.params.deviceId) {
            this.complainInfo.deviceId = this.params.deviceId;
        }
        else {
            this.complainInfo.deviceId = deviceInfo.ODID;
        }
        this.complainInfo.showMediaPreView = () => {
            this.title = '';
            this.mediaPreviewTitleVisible = true;
        };
        this.complainInfo.hideMediaPreView = () => {
            this.title = this.customTitle;
            this.mediaPreviewTitleVisible = false;
        };
        this.complainInfo.theme = this.params.theme;
        this.complainInfo.fileList = this.params.fileList;
        this.complainInfo.jwtToken = this.params.jwtToken;
        this.complainInfo.businessKey = this.params.businessKey;
        this.complainInfo.channelId = this.params.channelId ? this.params.channelId : 'OHOS';
        this.complainInfo.disableContactInfo = this.params.disableContactInfo;
        this.complainInfo.disableUserUpload = this.params.disableUserUpload;
        this.complainInfo.showBackButton = true;
        this.complainInfo.additionalContext = this.params.additionalContext;
        this.complainInfo.afterSubmit = (jsonString) => {
            if (this.params.afterSubmit) {
                this.params.afterSubmit(jsonString);
                this.isFinished = true;
            }
        };
        this.complainInfo.operate = (options) => {
            hilog.error(DOMAIN, TAG, 'complain operate type: ' + options);
            switch (options) {
                case 'ready':
                    this.isShowLoading = false;
                    break;
                default:
                    break;
            }
        };
        this.complainInfo.historyBack = () => {
            if (this.params.onHistoryBack) {
                this.params.onHistoryBack();
            }
            else {
                this.params.pathInfo.pop();
            }
        };
    }
    async refreshComplainUrl() {
        const language = LanguageUtil.getLanguageCode();
        const accessMode = 'bindSheet';
        if (this.params.colorMode === ColorMode.DARK) {
            this.complainUrl =
                `${this.tmpEnvStr}?next=1&lang=${language}&theme=dark&appId=&{this.params.appId}&accessMode=${accessMode}&deviceType=${this.deviceType}`;
        }
        else {
            this.complainUrl =
                `${this.tmpEnvStr}?next=1&lang=${language}&appId=&{this.params.appId}&accessMode=${accessMode}&deviceType=${this.deviceType}`;
        }
        this.webviewController.registerJavaScriptProxy(this.complainInfo, 'complainJSInterface', ['complainAddInfo', 'refreshAccessToken', 'afterSubmit', 'historyBack', 'showMediaPreview', 'operate',
            'refreshComplainSessionId', 'onEvent']);
        hilog.info(DOMAIN, TAG, 'start to loadComplainUrl: ' + this.complainUrl);
        if (this.complainInfo.hideMediaPreView) {
            this.complainInfo.hideMediaPreView();
        }
        this.webviewController.loadUrl(this.complainUrl);
        setTimeout(() => {
            if (this.isShowLoading === true) {
                this.isShowLoading = false;
            }
        }, 7000);
    }
    async init() {
        await this.initComplainParams();
        await this.initComplainInfo();
        this.refreshComplainUrl();
    }
    async selectFile(result) {
        this.webviewController.runJavaScript('uploadMaterialData()', async (error, res) => {
            if (error) {
                let e = error;
                hilog.error(DOMAIN, TAG, `run JavaScript error, ErrorCode: ${e.code}, Message: ${e.message}`);
                return;
            }
            if (res) {
                hilog.info(DOMAIN, TAG, `The uploadMaterialData() return value is : ${res}}`);
                let uploadLimit = JsonUtils.parse(res);
                this.canUploadCount = uploadLimit.canUploadCount ? uploadLimit.canUploadCount : 5;
            }
            else {
                this.canUploadCount = 5;
            }
            const choseFile = await ComplainFileSelectUtil.selectFiles(this.canUploadCount, this.configVo);
            result.handleFileList(choseFile);
        });
        return;
    }
    web(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Web.create({ src: '', controller: this.webviewController });
            Web.id('Web');
            Web.accessibilityLevel('no');
            Web.backgroundColor({ "id": 125831061, "type": 10001, params: ['sys.color.background_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Web.onKeyEvent(event => {
                if (!event || !this.fromSheet) {
                    return;
                }
                if (event.type === KeyType.Down && event.keyCode === KeyCode.KEYCODE_ESCAPE) {
                    try {
                        if (this.mediaPreviewTitleVisible) {
                            this.webviewController.runJavaScript('closePreviewPanel()', () => {
                            });
                            if (this.complainInfo.hideMediaPreView) {
                                this.complainInfo.hideMediaPreView();
                            }
                        }
                        else if (this.webviewController.getUrl().indexOf('complainRecordList') >= 0 ||
                            this.webviewController.getUrl().indexOf('complainGuide') >= 0) {
                            this.title = this.customTitle;
                            this.webviewController.backward();
                        }
                        else if (this.params.onBackPressed) {
                            this.params.onBackPressed();
                        }
                        else {
                            this.params.pathInfo.pop();
                        }
                    }
                    catch (e) {
                        hilog.error(DOMAIN, TAG, `complain accesssBackWard error: ${e}}`);
                    }
                }
            });
            Web.onShowFileSelector((event) => {
                hilog.info(DOMAIN, TAG, `onShowFileSelector`);
                if (event) {
                    this.selectFile(event.result);
                }
                return true;
            });
            Web.onControllerAttached(async () => {
                try {
                    await this.init();
                }
                catch (error) {
                    let e = error;
                    hilog.error(DOMAIN, TAG, `complain onControllerAttached error: ${e?.message}`);
                }
            });
            Web.onPageBegin(() => {
                hilog.info(DOMAIN, TAG, `complain page onPageBegin`);
            });
            Web.onPageEnd(() => {
                hilog.info(DOMAIN, TAG, `complain page onPageEnd`);
                if (connection.hasDefaultNetSync()) {
                    this.isWeb = true;
                }
                else {
                    this.isWeb = false;
                }
            });
            Web.onErrorReceive((event) => {
                hilog.error(DOMAIN, TAG, `complain page onErrorReceive ` + event?.error.getErrorInfo());
                if (event?.error.getErrorInfo() === 'ERR_INTERNET_DISCONNECTED') {
                    if (!this.isWeb) {
                        this.isShowLoading = false;
                    }
                }
                else if (event?.error.getErrorInfo() === 'ERROR_TIMED_OUT' && !DeviceInfoUtil.isTv()) {
                    this.isShowLoading = false;
                }
            });
            Web.onHttpErrorReceive((event) => {
                hilog.error(DOMAIN, TAG, `complain page onHttpErrorReceive, code: ` + event?.response.getResponseCode() +
                    'message: ' + event?.response.getReasonMessage());
            });
            Web.onConsole((event) => {
                hilog.info(DOMAIN, TAG, `complain log: ` + event?.message.getMessage());
                return true;
            });
            Web.nestedScroll({
                scrollForward: NestedScrollMode.SELF_ONLY,
                scrollBackward: NestedScrollMode.SELF_ONLY
            });
            Web.minFontSize(1);
            Web.darkMode(WebDarkMode.Auto);
            Web.overScrollMode(OverScrollMode.ALWAYS);
            Web.javaScriptAccess(true);
            Web.fileAccess(false);
            Web.geolocationAccess(false);
            Web.width('100%');
            Web.height('100%');
            Web.backgroundColor(Color.Transparent);
            Web.allowDrop(null);
        }, Web);
    }
    buildNavDestinationContent(parent = null) {
        this.web.bind(this)();
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            NavDestination.create(() => {
                this.buildNavDestinationContent.bind(this)();
            }, { moduleName: "__harDefaultModuleName__", pagePath: "" });
            NavDestination.backgroundColor('#202224');
            NavDestination.height('100%');
            NavDestination.width('100%');
            NavDestination.title('XXX');
            NavDestination.onBackPressed(this.back);
        }, NavDestination);
        NavDestination.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}