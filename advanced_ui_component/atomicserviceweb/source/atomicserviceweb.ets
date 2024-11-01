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

import web_webview from '@ohos.web.webview';
import router from '@ohos.router';
import deviceInfo from '@ohos.deviceInfo';
import common from '@ohos.app.ability.common';
import geoLocationManager from '@ohos.geoLocationManager';
import bundleManager from '@ohos.bundle.bundleManager';
import abilityAccessCtrl, { Permissions } from '@ohos.abilityAccessCtrl';
import connection from '@ohos.net.connection';
import request from '@ohos.request';
import fs from '@ohos.file.fs';
import util from '@ohos.util';
import photoAccessHelper from '@ohos.file.photoAccessHelper';
import { filePreview } from '@kit.PreviewKit';
import fileUri from '@ohos.file.fileuri';
import picker from '@ohos.multimedia.cameraPicker';
import filePicker from '@ohos.file.picker';
import { BusinessError } from '@ohos.base';

class AsError {
  public code: number;
  public message: string;

  constructor(code: number, message: string) {
    this.code = code;
    this.message = message;
  }
}

class JsApiConfig {
  public apiName: string;
  public minVersion: string;
  public maxVersion: string;
  public requiredFieldNames?: string[];

  constructor(apiName: string, minVersion: string, maxVersion: string, requiredFieldNames?: string[]) {
    this.apiName = apiName;
    this.minVersion = minVersion;
    this.maxVersion = maxVersion;
    this.requiredFieldNames = requiredFieldNames;
  }
}

const LOG_ENABLE: boolean = true;
const LOG_PREFIX: string = '[AtomicServiceWebLog]';
const UPLOAD_IMAGE_CACHE_DIR: string = '/cache/';
const JAVA_SCRIPT_PROXY_OBJECT_NAME: string = 'atomicServiceProxy';
const JAVA_SCRIPT_PROXY_API_NAME_LIST: string[] = ['invokeJsApi'];
const ATOMIC_SERVICE_JS_API_MAP = new Map<string, JsApiConfig>();
const registerJsApi = (apiNameAlias: string, apiName: string, minVersion: string, maxVersion: string,
  requiredFieldNames: string[]): void => {
  ATOMIC_SERVICE_JS_API_MAP.set(apiNameAlias, new JsApiConfig(apiName, minVersion, maxVersion, requiredFieldNames));
};
const MAX_VERSION = '99.99.99';
const ATOMIC_SERVICE_JS_SDK_CURRENT_VERSION = '1.0.0';
const PERMISSION_APPROXIMATELY_LOCATION: Permissions = 'ohos.permission.APPROXIMATELY_LOCATION';

const SYSTEM_INTERNAL_ERROR: AsError = new AsError(500, 'System internal error.');
const JS_API_INVALID_INVOKE_ERROR: AsError = new AsError(200001, 'Invalid invoke.');
const PARAM_REQUIRED_ERROR_CODE: number = 200002;
const PARAM_NUMBER_POSITIVE_ERROR_CODE: number = 200003;
const ROUTER_PARAM_MODE_INVALID_ERROR: AsError = new AsError(200004, 'Param mode is invalid.');
const BACK_URL_NOT_EXIST_OR_OPENED_ERROR: AsError = new AsError(200005, 'Url is not exist or opened, can not be back.');
const NAV_PATH_STACK_NOT_EXIST_ERROR_CODE: number = 200006;
const POP_PATH_NAME_NOT_EXIST_ERROR: AsError = new AsError(200007, 'Name is not exist or opened, can not be pop.');
const POP_PATH_PARAM_INDEX_INVALID_ERROR: AsError = new AsError(200008, 'Param index is invalid.');
const POP_PATH_INDEX_OUT_OF_RANGE_ERROR: AsError = new AsError(200009, 'The Index is out of range.');
const UPLOAD_IMAGE_FILES_REQUIRED_ERROR: AsError = new AsError(200010, 'Param files is required.');
const UPLOAD_IMAGE_FILE_NOT_EXIST_ERROR_CODE: number = 200011;
const UPLOAD_IMAGE_FILES_URI_REQUIRED_ERROR: AsError = new AsError(200012, 'Param uri of files is required.');
const UPLOAD_FILE_ERROR: AsError = new AsError(200013, 'Upload file error.');
const IMAGE_CAN_NOT_PREVIEW_ERROR: AsError = new AsError(200014, 'The filePath can not preview.');
const NETWORK_NO_ACTIVE_ERROR: AsError = new AsError(200015, 'The network is not active.');
const PERMISSION_LOCATION_USER_REFUSED_ERROR: number = 200016;

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

@Component
export struct AtomicServiceWeb {
  public src: ResourceStr | undefined = undefined;
  public navPathStack?: NavPathStack;
  @Prop mixedMode?: MixedMode;
  @Prop darkMode?: WebDarkMode;
  @Prop forceDarkAccess?: boolean;
  @ObjectLink controller: AtomicServiceWebController;
  public onMessage?: Callback<OnMessageEvent> = () => {
  };
  public onErrorReceive?: Callback<OnErrorReceiveEvent> = () => {
  };
  public onHttpErrorReceive?: Callback<OnHttpErrorReceiveEvent> = () => {
  };
  public onPageBegin?: Callback<OnPageBeginEvent> = () => {
  };
  public onPageEnd?: Callback<OnPageEndEvent> = () => {
  };
  public onProgressChange?: Callback<OnProgressChangeEvent> = () => {
  };
  public onControllerAttached?: VoidCallback;
  public onLoadIntercept?: Callback<OnLoadInterceptEvent, boolean>;
  private context: common.UIAbilityContext = this.getUIContext().getHostContext() as common.UIAbilityContext;
  private webViewController: web_webview.WebviewController = new web_webview.WebviewController();
  private schemeHandler: web_webview.WebSchemeHandler = new web_webview.WebSchemeHandler();
  private atomicService?: AtomicService;
  private atomicServiceProxy?: AtomicServiceProxy;

  aboutToAppear(): void {
    if (!this.atomicService) {
      this.atomicService = new AtomicServiceApi(this.context, this.navPathStack, this.onMessage);
      this.atomicServiceProxy = new AtomicServiceProxy(this.atomicService);
    }

    try {
      let bundleInfo: bundleManager.BundleInfo = bundleManager.getBundleInfoForSelfSync(
        bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION);
      if (bundleInfo?.appInfo?.appProvisionType === 'debug') {
        console.log(`AtomicServiceWeb setWebDebuggingAccess`);
        web_webview.WebviewController.setWebDebuggingAccess(true);
      }
    } catch (err) {
      console.error(`AtomicServiceWeb set Web Debug Mode failed, code is ${err.code}, message is ${err.message}`);
    }
  }

  aboutToDisappear(): void {
    this.atomicService?.notifyMessage();
  }

  build() {
    Web({ src: this.src, controller: this.webViewController })
      .zoomAccess(false)
      .allowWindowOpenMethod(false)
      .domStorageAccess(true)
      .layoutMode(WebLayoutMode.NONE)
      .mixedMode(this.mixedMode)
      .darkMode(this.darkMode)
      .forceDarkAccess(this.forceDarkAccess)
      .onErrorReceive((event: OnErrorReceiveEvent) => this.onCommonCallBack('onErrorReceive', event,
        this.onErrorReceive))
      .onHttpErrorReceive((event: OnHttpErrorReceiveEvent) => this.onCommonCallBack('onHttpErrorReceive', event,
        this.onHttpErrorReceive))
      .onPageBegin((event: OnPageBeginEvent) => this.onCommonCallBack('onPageBegin', event, this.onPageBegin))
      .onPageEnd((event: OnPageEndEvent) => this.onCommonCallBack('onPageEnd', event, this.onPageEnd))
      .onProgressChange((event: OnProgressChangeEvent) => this.onCommonCallBack('onProgressChange', event,
        this.onProgressChange))
      .onControllerAttached(() => {
        this.registerJavaScriptProxy();
        this.schemeHandler.onRequestStart((request: web_webview.WebSchemeHandlerRequest) => {
          return !this.checkUrl(request.getRequestUrl());
        });
        this.webViewController.setWebSchemeHandler('https', this.schemeHandler);
        this.initAtomicServiceWebController();
        if (this.onControllerAttached) {
          try {
            this.onControllerAttached();
          } catch (error) {
            console.error(`AtomicServiceWeb onControllerAttached failed, code is ${error.code}, message is ${error.message}`);
          }
        }
      })
      .onOverrideUrlLoading((webResourceRequest: WebResourceRequest) => {
        return !this.checkUrl(webResourceRequest.getRequestUrl());
      })
      .onLoadIntercept(event => {
        let checkResult = !this.checkUrl(event.data.getRequestUrl());
        if (!checkResult && this.onLoadIntercept) {
          try {
            return this.onLoadIntercept(event);
          } catch (error) {
            console.error(`AtomicServiceWeb onLoadIntercept failed, code is ${error.code}, message is ${error.message}`);
            return true;
          }
        }
        return checkResult
      })
  }

  onCommonCallBack<T>(method: string, event: T, callback?: (event: T) => void): void {
    try {
      callback && callback(event);
    } catch (error) {
      console.error(`AtomicServiceWeb ${method} failed, code is ${error.code}, message is ${error.message}`);
    }
  }

  registerJavaScriptProxy(): void {
    try {
      this.webViewController.registerJavaScriptProxy(this.atomicServiceProxy, JAVA_SCRIPT_PROXY_OBJECT_NAME,
        JAVA_SCRIPT_PROXY_API_NAME_LIST);
    } catch (error) {
      let e: BusinessError = error as BusinessError;
      console.error(`AtomicServiceWeb registerJavaScriptProxy failed, code is ${e.code}, message is ${e.message}`);
    }
  }

  initAtomicServiceWebController(): void {
    if (!this.controller) {
      return;
    }
    this.controller.setWebviewController(this.webViewController);
  }

  cutUrl(url: string): string {
    if (url) {
      let index: number = url.indexOf('?');
      if (index > -1) {
        return url.substring(0, index);
      }
    }
    return url;
  }

  checkUrl(url: string): boolean {
    if (!url) {
      return false;
    }
    if (url.startsWith('resource://rawfile')) {
      return true;
    }
    url = this.cutUrl(url);
    console.log(`AtomicServiceWebLog checkUrl url=${url}`);
    return true;
  }
}

@Observed
export class AtomicServiceWebController {
  private webViewController?: web_webview.WebviewController;

  setWebviewController(webViewController: web_webview.WebviewController): void {
    this.webViewController = webViewController;
  }

  checkWebviewController(): void {
    if (!this.webViewController) {
      const error: BusinessError<string> = {
        name: '',
        message: 'Init error. The AtomicServiceWebController must be associated with a AtomicServiceWeb component.',
        code: 17100001,
      }
      throw error as Error;
    }
  }

  getUserAgent(): string | undefined {
    this.checkWebviewController();
    return this.webViewController?.getUserAgent();
  }

  getCustomUserAgent(): string | undefined {
    this.checkWebviewController();
    return this.webViewController?.getCustomUserAgent();
  }

  setCustomUserAgent(userAgent: string): void {
    this.checkWebviewController();
    this.webViewController?.setCustomUserAgent(userAgent);
  }

  accessForward(): boolean | undefined {
    this.checkWebviewController();
    return this.webViewController?.accessForward();
  }

  accessBackward(): boolean | undefined {
    this.checkWebviewController();
    return this.webViewController?.accessBackward();
  }

  accessStep(step: number): boolean | undefined {
    this.checkWebviewController();
    return this.webViewController?.accessStep(step);
  }

  forward(): void {
    this.checkWebviewController();
    this.webViewController?.forward();
  }

  backward(): void {
    this.checkWebviewController();
    this.webViewController?.backward();
  }

  refresh(): void {
    this.checkWebviewController();
    this.webViewController?.refresh();
  }

  loadUrl(url: string | Resource, headers?: Array<WebHeader>): void {
    this.checkWebviewController();
    if (headers) {
      this.webViewController?.loadUrl(url, headers);
    } else {
      this.webViewController?.loadUrl(url);
    }
  }
}

class AtomicServiceProxy {
  private atomicService: AtomicService;

  constructor(atomicService: AtomicService) {
    this.atomicService = atomicService;
  }

  invokeJsApi<T>(apiNameAlias: string, options: BaseOptions<T>): void {
    try {
      options = options || {};
      if (!apiNameAlias || !ATOMIC_SERVICE_JS_API_MAP.has(apiNameAlias)) {
        this.atomicService.errorWithCodeAndMsg(JS_API_INVALID_INVOKE_ERROR, options);
        return;
      }
      let jsApiConfig: JsApiConfig | undefined = ATOMIC_SERVICE_JS_API_MAP.get(apiNameAlias);
      if (!this.atomicService.checkRequiredFieldInOptions(jsApiConfig, options)) {
        return;
      }
      let atomicService: object = this.atomicService;
      atomicService[jsApiConfig?.apiName as string](options);
    } catch (err) {
      this.atomicService.error(err, options);
    }
  }
}

class AtomicService {
  protected context: common.UIAbilityContext;
  protected navPathStack?: NavPathStack;
  protected messageDataList: object[] = [];
  protected onMessage: (event: OnMessageEvent) => void = () => {
  };

  constructor(context: common.UIAbilityContext, navPathStack?: NavPathStack,
    onMessage?: (event: OnMessageEvent) => void) {
    this.context = context;
    this.navPathStack = navPathStack;
    this.onMessage = onMessage ? onMessage : this.onMessage;
  }

  success<T>(res: T, options: BaseOptions<T>): void {
    try {
      options?.callback && options?.callback(undefined, res);
    } catch (err) {
      this.consoleError(`callback error, code is ${err.code}, message is ${err.message}`);
    }
  }

  error<T>(err: BusinessError, options: BaseOptions<T>,): void {
    try {
      options?.callback && options?.callback(new AsError(err.code ? err.code : SYSTEM_INTERNAL_ERROR.code,
        err.message ? err.message : SYSTEM_INTERNAL_ERROR.message));
    } catch (err) {
      this.consoleError(`callback error, code is ${err.code}, message is ${err.message}`);
    }
  }

  errorWithCodeAndMsg<T>(error: AsError, options: BaseOptions<T>): void {
    try {
      options?.callback && options?.callback(error);
    } catch (err) {
      this.consoleError(`callback error, code is ${err.code}, message is ${err.message}`);
    }
  }

  consoleLog(msg: string): void {
    if (LOG_ENABLE) {
      console.log(`${LOG_PREFIX} ${msg}`);
    }
  }

  consoleError(msg: string): void {
    if (LOG_ENABLE) {
      console.error(`${LOG_PREFIX} ${msg}`);
    }
  }

  logOptions<T>(name: string, options: BaseOptions<T>): void {
    this.consoleLog(`${name} options=${JSON.stringify(options)}`);
  }

  checkParamRequired<V, T>(paramKey: string, paramValue: V, options: BaseOptions<T>): boolean {
    if (paramValue === undefined || paramValue === null || paramValue === '') {
      this.errorWithCodeAndMsg(new AsError(PARAM_REQUIRED_ERROR_CODE, `Param ${paramKey} is required.`), options);
      return false;
    }
    return true;
  }

  checkNumberParamPositive<T>(paramKey: string, paramValue: number, options: BaseOptions<T>): boolean {
    if (paramValue <= 0) {
      this.errorWithCodeAndMsg(new AsError(PARAM_NUMBER_POSITIVE_ERROR_CODE,
        `Param ${paramKey} must be a positive number.`), options);
      return false;
    }
    return true;
  }

  checkRequiredFieldInOptions<T>(jsApiConfig: JsApiConfig | undefined, options: BaseOptions<T>): boolean {
    if (!jsApiConfig) {
      return false;
    }
    if (!jsApiConfig.requiredFieldNames) {
      return true;
    }
    let obj: object = options;
    for (let i = 0; i < jsApiConfig.requiredFieldNames.length; i++) {
      let fieldName: string = jsApiConfig.requiredFieldNames[i];
      if (!this.checkParamRequired(fieldName, obj[fieldName], options)) {
        return false;
      }
    }
    return true;
  }

  checkRouterMode<T>(mode: string | undefined, options: BaseOptions<T>): boolean {
    if (!mode || mode === 'Single' || mode === 'Standard') {
      return true;
    }
    this.errorWithCodeAndMsg(ROUTER_PARAM_MODE_INVALID_ERROR, options);
    return false;
  }

  parseRouterMode(routerMode?: string): router.RouterMode {
    return routerMode === 'Single' ? router.RouterMode.Single : router.RouterMode.Standard;
  }

  getRouterIndexByDelta(delta: number): number {
    let length: number = Number.parseInt(router.getLength());
    for (let i = length; i > 0; i--) {
      let state = router.getStateByIndex(i);
      if (state?.name && delta-- == 0) {
        return i;
      }
    }
    return 1;
  }

  checkBackUrlExists<T>(url: string, options: BaseOptions<T>): boolean {
    let length: number = Number.parseInt(router.getLength());
    for (let i = length; i > 0; i--) {
      let state = router.getStateByIndex(i);
      if (state?.name) {
        let stateUrl: string = state?.path + state?.name;
        if (stateUrl === url) {
          return true;
        }
      }
    }
    this.errorWithCodeAndMsg(BACK_URL_NOT_EXIST_OR_OPENED_ERROR, options);
    return false;
  }

  checkNavPathStack<T>(apiName: string, options: BaseOptions<T>): boolean {
    if (!this.navPathStack) {
      this.errorWithCodeAndMsg(new AsError(NAV_PATH_STACK_NOT_EXIST_ERROR_CODE,
        `Current page is not NavDestination, not support ${apiName}().`), options);
      return false;
    }
    return true;
  }

  getNavPathIndexByDelta(delta: number): number {
    let pathStack: string[] | undefined = this.navPathStack?.getAllPathName();
    if (!pathStack || pathStack.length == 0) {
      return -1;
    }
    return pathStack.length > delta ? (pathStack.length - delta - 1) : -1;
  }

  onPopHandler(popInfo: PopInfo, onPop?: (event: OnPopEvent) => void): void {
    if (!popInfo?.info || !onPop) {
      return;
    }
    onPop(new OnPopEvent(popInfo.info.name, popInfo.info.param as object, popInfo.result));
  }

  getCurrentNavPathInfo(): NavPathInfo {
    let navPathStack: Array<string> | undefined = this.navPathStack?.getAllPathName();
    let navPathInfo: NavPathInfo = (navPathStack && navPathStack.length > 0) ?
      new NavPathInfo(navPathStack[navPathStack.length - 1], navPathStack.length - 1) : new NavPathInfo(undefined, -1);
    if (navPathInfo.index >= 0) {
      navPathInfo.param = this.navPathStack?.getParamByIndex(navPathInfo.index) as object;
    }
    return navPathInfo;
  }

  notifyMessage(): void {
    if (this.messageDataList.length <= 0) {
      return;
    }
    try {
      this.onMessage(new OnMessageEvent(this.messageDataList));
    } catch (err) {
      this.consoleError(`onMessage failed, code is ${err.code}, message is ${err.message}`);
    }
    this.messageDataList = [];
  }

  isJsApiEnable(jsApiConfig?: JsApiConfig): boolean {
    if (!jsApiConfig) {
      return false;
    }
    if (this.compareVersion(jsApiConfig.minVersion, ATOMIC_SERVICE_JS_SDK_CURRENT_VERSION) &&
    this.compareVersion(ATOMIC_SERVICE_JS_SDK_CURRENT_VERSION, jsApiConfig.maxVersion)) {
      return true;
    }
    return false;
  }

  compareVersion(lowVersion: string, highVersion: string): boolean {
    if (!lowVersion || !highVersion) {
      return false;
    }
    let v1 = lowVersion.split('.').map(m => Number.parseInt(m));
    let v2 = highVersion.split('.').map(m => Number.parseInt(m));
    const maxLength = Math.max(v1.length, v2.length);
    for (let i = 0; i < maxLength; i++) {
      if (v1[i] < v2[i]) {
        return true;
      } else if (v1[i] > v2[i]) {
        return false;
      }
    }
    if (v1.length < v2.length) {
      return true;
    }
    if (v1.length > v2.length) {
      return false;
    }
    return true;
  }

  getUri(uriOrFilePath: string): string {
    if (!uriOrFilePath || uriOrFilePath.startsWith('file://')) {
      return uriOrFilePath;
    }
    return fileUri.getUriFromPath(uriOrFilePath);
  }

  async checkUploadFile(options: UploadFileOptions): Promise<CheckUploadFileResult> {
    if (!options.files || options.files.length <= 0) {
      this.errorWithCodeAndMsg(UPLOAD_IMAGE_FILES_REQUIRED_ERROR, options);
      return new CheckUploadFileResult(false);
    }
    let uriMap: Map<string, string> = new Map();
    for (let i = 0; i < options.files?.length; i++) {
      let file: UploadFile = options.files[i];
      if (!file.uri) {
        this.errorWithCodeAndMsg(UPLOAD_IMAGE_FILES_URI_REQUIRED_ERROR, options);
        return new CheckUploadFileResult(false);
      }
      if (!file.uri.startsWith('file://') && !fs.accessSync(file.uri, fs.AccessModeType.EXIST)) {
        this.errorWithCodeAndMsg(new AsError(UPLOAD_IMAGE_FILE_NOT_EXIST_ERROR_CODE,
          `File uri ${file.uri} is not exist.`), options);
        return new CheckUploadFileResult(false);
      }
      let originUri: string = file.uri;
      let uploadUri: string = file.uri;
      if (uploadUri.indexOf(UPLOAD_IMAGE_CACHE_DIR) < 0) {
        let srcUri: string = uploadUri.startsWith('file://') ? uploadUri : fileUri.getUriFromPath(file.uri);
        uploadUri = this.context.cacheDir + '/' + uploadUri.substring(uploadUri.lastIndexOf('/') + 1);
        try {
          await fs.copy(srcUri, fileUri.getUriFromPath(uploadUri))
        } catch (err) {
          this.errorWithCodeAndMsg(UPLOAD_FILE_ERROR, options);
          return new CheckUploadFileResult(false);
        }
      }
      file.uri = 'internal://' + uploadUri.substring(uploadUri.indexOf(UPLOAD_IMAGE_CACHE_DIR) + 1);
      uriMap.set(uploadUri, originUri);
    }
    return new CheckUploadFileResult(true, uriMap);
  }

  convertToRequestData(data?: UploadRequestData[]): request.RequestData[] {
    let requestData: request.RequestData[] = [];
    if (data) {
      data.forEach(item => {
        if (!item.name || !item.value) {
          return;
        }
        requestData.push({ name: item.name, value: item.value });
      });
    }
    return requestData;
  }

  convertToFile(files?: UploadFile[]): request.File[] {
    let requestFiles: request.File[] = [];
    if (files) {
      files.forEach(item => {
        requestFiles.push({
          filename: item.filename,
          name: item.name,
          uri: item.uri,
          type: item.type
        });
      });
    }
    return requestFiles;
  }

  handleUploadFileResult(taskStateArray: Array<request.TaskState>, uriMap: Map<string, string>,
    options: UploadFileOptions): void {
    let taskStates: UploadFileTaskState[] = [];
    if (taskStateArray) {
      taskStateArray.forEach(taskState => {
        let path: (string | undefined) = taskState.path ? uriMap.get(taskState.path) : taskState.path;
        taskStates.push(new UploadFileTaskState(path ? path : taskState.path, taskState.responseCode,
          taskState.message));
      });
    }
    this.success(new UploadFileResult(taskStates), options);
  }

  parseFileNameFromUrl(url?: string): string {
    if (!url) {
      return '';
    }
    let http: string = url.split('?')[0];
    if (http.indexOf('/') < 0) {
      return '';
    }
    let index: number = http.lastIndexOf('/');
    if (index == (http.length - 1)) {
      return '';
    }
    return http.substring(index + 1);
  }

  saveDownloadFile(filePath: string, fileName: string, options: DownloadFileOptions,
    callback: (uri: string) => void): void {
    let documentPicker = new filePicker.DocumentViewPicker();
    documentPicker.save({
      newFileNames: [fileName]
    }).then(res => {
      let uri: string = res[0];
      fs.copy(fileUri.getUriFromPath(filePath), uri).then(() => {
        callback && callback(uri);
      }).catch((err: BusinessError) => {
        this.error(err, options);
      });
    }).catch((err: BusinessError) => {
      this.error(err, options);
    });
  }

  checkAccessToken(permissionName: Permissions): Promise<abilityAccessCtrl.GrantStatus> {
    let bundleInfo: bundleManager.BundleInfo = bundleManager.getBundleInfoForSelfSync(
      bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION);
    let tokenId: number = bundleInfo.appInfo.accessTokenId;
    let atManager: abilityAccessCtrl.AtManager = abilityAccessCtrl.createAtManager();
    return atManager.checkAccessToken(tokenId, permissionName);
  }

  checkPermissions(permissionName: Permissions, grantCallback: (err?: BusinessError) => void): void {
    this.checkAccessToken(permissionName).then(grantStatus => {
      if (grantStatus == abilityAccessCtrl.GrantStatus.PERMISSION_GRANTED) {
        grantCallback(undefined);
      } else {
        let atManager: abilityAccessCtrl.AtManager = abilityAccessCtrl.createAtManager();
        atManager.requestPermissionsFromUser(this.context, [permissionName]).then(permissionRequestResult => {
          for (let i = 0; i < permissionRequestResult.authResults.length; i++) {
            if (permissionRequestResult.authResults[i] != 0) {
              const error: BusinessError<void> = {
                name: '',
                message: `RequestPermissionsFromUser error. authResult: ${permissionRequestResult.authResults[i]}.`,
                code: PERMISSION_LOCATION_USER_REFUSED_ERROR
              }
              grantCallback(error);
              return;
            }
          }
          grantCallback(undefined);
        }).catch((err: BusinessError) => {
          grantCallback(err);
        });
      }
    }).catch((err: BusinessError) => {
      grantCallback(err);
    });
  }
}

class AtomicServiceApi extends AtomicService {
  constructor(context: common.UIAbilityContext, navPathStack?: NavPathStack,
    onMessage?: (event: OnMessageEvent) => void) {
    super(context, navPathStack, onMessage);
  }

  pushUrl(options: PushUrlOptions): void {
    if (!this.checkRouterMode(options.mode, options)) {
      return;
    }
    router.pushUrl({ url: options.url, params: options.params }, this.parseRouterMode(options.mode)).then(() => {
      this.success(new PushUrlResult(), options);
    }).catch((err: BusinessError) => {
      this.error(err, options);
    });
  }

  replaceUrl(options: ReplaceUrlOptions): void {
    if (!this.checkRouterMode(options.mode, options)) {
      return;
    }
    router.replaceUrl({ url: options.url, params: options.params }, this.parseRouterMode(options.mode)).then(() => {
      this.success(new ReplaceUrlResult(), options);
    }).catch((err: BusinessError) => {
      this.error(err, options);
    });
  }

  backUrl(options: BackUrlOptions): void {
    if (options.url) {
      if (!this.checkBackUrlExists(options.url, options)) {
        return;
      }
      router.back({ url: options.url, params: options.params });
      this.success(new BackUrlResult(), options);
    } else if (options.index || options.index === 0) {
      if (!this.checkNumberParamPositive('index', options.index, options)) {
        return;
      }
      router.back(options.index, options.params);
      this.success(new BackUrlResult(), options);
    } else if (options.delta || options.delta === 0) {
      if (!this.checkNumberParamPositive('delta', options.delta, options)) {
        return;
      }
      router.back(this.getRouterIndexByDelta(options.delta), options.params);
      this.success(new BackUrlResult(), options);
    } else {
      router.back();
      this.success(new BackUrlResult(), options);
    }
  }

  clearUrl(options: ClearUrlOptions): void {
    router.clear();
    this.success(new ClearUrlResult(), options);
  }

  pushPath(options: PushPathOptions): void {
    if (!this.checkNavPathStack('navPathStack.pushPath', options)) {
      return;
    }
    this.navPathStack?.pushPath({
      name: options.name,
      param: options.param,
      onPop: popInfo => this.onPopHandler(popInfo, options.onPop)
    }, options.animated);
    this.success(new PushPathResult(), options);
  }

  replacePath(options: ReplacePathOptions): void {
    if (!this.checkNavPathStack('navPathStack.replacePath', options)) {
      return;
    }
    this.navPathStack?.replacePath({
      name: options.name,
      param: options.param,
      onPop: popInfo => this.onPopHandler(popInfo, options.onPop)
    }, options.animated);
    this.success(new ReplacePathResult(), options);
  }

  popPath(options: PopPathOptions): void {
    if (!this.checkNavPathStack('navPathStack.pop', options)) {
      return;
    }
    if (options.name) {
      let index: number | undefined = this.navPathStack?.popToName(options.name, options.result, options.animated);
      if (index === undefined || index === -1) {
        this.errorWithCodeAndMsg(POP_PATH_NAME_NOT_EXIST_ERROR, options);
        return;
      }
    } else if (options.index || options.index === 0) {
      if (options.index < -1) {
        this.errorWithCodeAndMsg(POP_PATH_PARAM_INDEX_INVALID_ERROR, options);
        return;
      }
      if (options.index > this.getCurrentNavPathInfo().index) {
        this.errorWithCodeAndMsg(POP_PATH_INDEX_OUT_OF_RANGE_ERROR, options);
        return;
      }
      this.navPathStack?.popToIndex(options.index, options.result, options.animated);
    } else if (options.delta || options.delta === 0) {
      if (!this.checkNumberParamPositive('delta', options.delta, options)) {
        return;
      }
      this.navPathStack?.popToIndex(this.getNavPathIndexByDelta(options.delta), options.result, options.animated);
    } else {
      this.navPathStack?.pop(options.result, options.animated);
    }
    let navPathInfo: NavPathInfo = this.getCurrentNavPathInfo();
    this.success(new PopPathResult(navPathInfo.name, navPathInfo.index, navPathInfo.param), options);
  }

  clearPath(options: ClearPathOptions): void {
    if (!this.checkNavPathStack('navPathStack.clear', options)) {
      return;
    }
    this.navPathStack?.clear(options.animated);
    this.success(new ClearPathResult(), options);
  }

  postMessage(options: PostMessageOptions): void {
    options.data && this.messageDataList.push(options.data);
    this.success(new PostMessageResult(), options);
  }

  getEnv(options: GetEnvOptions): void {
    let res: GetEnvResult = new GetEnvResult();
    res.deviceType = deviceInfo.deviceType;
    res.brand = deviceInfo.brand;
    res.productModel = deviceInfo.productModel;
    res.osFullName = deviceInfo.osFullName;
    this.success(res, options);
  }

  checkJsApi(options: CheckJsApiOptions): void {
    let res: Map<string, boolean> = new Map();
    options.jsApiList?.forEach(jsApi => {
      res[jsApi] = this.isJsApiEnable(ATOMIC_SERVICE_JS_API_MAP.get(jsApi));
    });
    this.success(new CheckJsApiResult(res), options);
  }

  pickCamera(options: PickCameraOptions): void {
    picker.pick(this.context, options.mediaTypes as Array<picker.PickerMediaType>, {
      cameraPosition: options.cameraPosition,
      saveUri: options.saveUri,
      videoDuration: options.videoDuration
    }).then((pickerResult: picker.PickerResult) => {
      this.success(new PickCameraResult(pickerResult.resultCode, pickerResult.resultUri, pickerResult.mediaType),
        options);
    }).catch((err: BusinessError) => {
      this.error(err, options);
    });
  }

  selectPhoto(options: SelectPhotoOptions): void {
    let photoViewPicker = new photoAccessHelper.PhotoViewPicker();
    photoViewPicker.select({
      MIMEType: options.mimeType as photoAccessHelper.PhotoViewMIMETypes,
      maxSelectNumber: options.maxSelectNumber,
      isPhotoTakingSupported: options.isPhotoTakingSupported,
      isEditSupported: options.isEditSupported,
      isSearchSupported: options.isSearchSupported,
      recommendationOptions: {
        recommendationType: options.recommendationType
      },
      preselectedUris: options.preselectedUris
    }).then((selectResult: photoAccessHelper.PhotoSelectResult) => {
      this.success(new SelectPhotoResult(selectResult.photoUris, selectResult.isOriginalPhoto), options);
    }).catch((err: BusinessError) => {
      this.error(err, options);
    });
  }

  openPreview(options: OpenPreviewOptions): void {
    let uri: string = this.getUri(options.uri as string);
    filePreview.canPreview(this.context, uri).then((res: boolean) => {
      if (!res) {
        this.errorWithCodeAndMsg(IMAGE_CAN_NOT_PREVIEW_ERROR, options);
        return;
      }
      filePreview.openPreview(this.context, {
        uri: uri,
        mimeType: options.mimeType as string,
        title: options.title
      }).then(() => {
        this.success(new OpenPreviewResult(), options);
      }).catch((err: BusinessError) => {
        this.error(err, options);
      });
    }).catch((err: BusinessError) => {
      this.error(err, options);
    });
  }

  uploadFile(options: UploadFileOptions): void {
    this.checkUploadFile(options).then(res => {
      if (!res.checkResult) {
        return;
      }
      let uploadConfig: request.UploadConfig = {
        url: options.url as string,
        header: options.header as object,
        method: options.method as string,
        files: this.convertToFile(options.files),
        data: this.convertToRequestData(options.data)
      };
      request.uploadFile(this.context, uploadConfig).then((uploadTask: request.UploadTask) => {
        uploadTask.on('complete', (taskStateArray: Array<request.TaskState>) => {
          this.handleUploadFileResult(taskStateArray, res.uriMap as Map<string, string>, options);
        });
        uploadTask.on('fail', (taskStateArray: Array<request.TaskState>) => {
          this.handleUploadFileResult(taskStateArray, res.uriMap as Map<string, string>, options);
        });
      }).catch((err: BusinessError) => {
        this.error(err, options);
      });
    }).catch((err: BusinessError) => {
      this.error(err, options);
    });
  }

  downloadFile(options: DownloadFileOptions): void {
    let fileName: string = options.fileName ? options.fileName : this.parseFileNameFromUrl(options.url);
    let cacheFileName: string = `${util.generateRandomUUID().replaceAll('-', '')}`;
    let filePath: string = `${this.context.cacheDir}/${cacheFileName}`;
    request.downloadFile(this.context, {
      url: options.url,
      header: options.header ? options.header : new Object(),
      filePath: filePath,
      enableMetered: options.enableMetered,
      enableRoaming: options.enableRoaming,
      networkType: options.networkType,
      background: false
    }).then((downloadTask: request.DownloadTask) => {
      downloadTask.on('complete', () => {
        this.saveDownloadFile(filePath, fileName, options, uri => {
          this.success(new DownloadFileResult(uri), options);
        });
      });
      downloadTask.on('fail', errCode => {
        this.errorWithCodeAndMsg(new AsError(errCode, 'File download fail.'), options);
      });
    }).catch((err: BusinessError) => {
      this.error(err, options);
    });
  }

  getNetworkType(options: GetNetworkTypeOptions): void {
    connection.getDefaultNet().then(netHandle => {
      if (!netHandle || netHandle.netId === 0) {
        this.errorWithCodeAndMsg(NETWORK_NO_ACTIVE_ERROR, options);
        return;
      }
      connection.getNetCapabilities(netHandle).then(netCapabilities => {
        let res: GetNetworkTypeResult = new GetNetworkTypeResult(netCapabilities.bearerTypes,
          netCapabilities.networkCap, netCapabilities.linkUpBandwidthKbps, netCapabilities.linkDownBandwidthKbps);
        this.success(res, options);
      }).catch((err: BusinessError) => {
        this.error(err, options);
      });
    }).catch((err: BusinessError) => {
      this.error(err, options);
    });
  }

  getLocation(options: GetLocationOptions): void {
    this.checkPermissions(PERMISSION_APPROXIMATELY_LOCATION, err => {
      if (err) {
        this.error(err, options);
        return;
      }
      geoLocationManager.getCurrentLocation({
        priority: options.priority,
        scenario: options.scenario,
        maxAccuracy: options.maxAccuracy,
        timeoutMs: options.timeoutMs
      }).then(location => {
        let res: GetLocationResult = new GetLocationResult(location.latitude, location.longitude, location.altitude,
          location.accuracy, location.speed, location.timeStamp, location.direction, location.timeSinceBoot,
          location.additions, location.additionSize);
        this.success(res, options);
      }).catch((err: BusinessError) => {
        this.error(err, options);
      });
    });
  }
}

class NavPathInfo {
  public name: string | undefined;
  public index: number;
  public param?: object;

  constructor(name: string | undefined, index: number) {
    this.name = name;
    this.index = index;
  }
}

class CheckUploadFileResult {
  public checkResult: boolean;
  public uriMap?: Map<string, string>;

  constructor(checkResult: boolean, uriMap?: Map<string, string>) {
    this.checkResult = checkResult;
    this.uriMap = uriMap;
  }
}

class BaseOptions<T> {
  public callback?: (err: AsError | undefined, res?: T) => void;
}

class PushUrlOptions extends BaseOptions<PushUrlResult> {
  public url?: string;
  public params?: object;
  public mode?: string;
}

class PushUrlResult {
}

class ReplaceUrlOptions extends BaseOptions<ReplaceUrlResult> {
  public url?: string;
  public params?: object;
  public mode?: string;
}

class ReplaceUrlResult {
}

class BackUrlOptions extends BaseOptions<BackUrlResult> {
  public url?: string;
  public index?: number;
  public delta?: number;
  public params?: object;
}

class BackUrlResult {
}

class ClearUrlOptions extends BaseOptions<ClearUrlResult> {
}

class ClearUrlResult {
}

class OnPopEvent {
  public name?: string;
  public param?: object;
  public result?: object;

  constructor(name?: string, param?: object, result?: object) {
    this.name = name;
    this.param = param;
    this.result = result;
  }
}

class PushPathOptions extends BaseOptions<PushPathResult> {
  public name?: string;
  public param?: object;
  public animated?: boolean;
  public onPop?: (event: OnPopEvent) => void;
}

class PushPathResult {
}

class ReplacePathOptions extends BaseOptions<ReplacePathResult> {
  public name?: string;
  public param?: object;
  public animated?: boolean;
  public onPop?: (event: OnPopEvent) => void;
}

class ReplacePathResult {
}

class PopPathOptions extends BaseOptions<PopPathResult> {
  public name?: string;
  public index?: number;
  public delta?: number;
  public result?: object;
  public animated?: boolean;
}

class PopPathResult {
  public name: string | undefined;
  public index: number;
  public param?: object;

  constructor(name: string | undefined, index: number, param?: object) {
    this.name = name;
    this.index = index;
    this.param = param;
  }
}

class ClearPathOptions extends BaseOptions<ClearPathResult> {
  public animated?: boolean;
}

class ClearPathResult {
}

class PostMessageOptions extends BaseOptions<PostMessageResult> {
  public data?: object;
}

class PostMessageResult {
}

export class OnMessageEvent {
  public data: object[];

  constructor(data: object[]) {
    this.data = data;
  }
}

export class OnErrorReceiveEvent {
  public request: WebResourceRequest;
  public error: WebResourceError;

  constructor(request: WebResourceRequest, error: WebResourceError) {
    this.request = request;
    this.error = error;
  }
}

export class OnHttpErrorReceiveEvent {
  public request: WebResourceRequest;
  public response: WebResourceResponse;

  constructor(request: WebResourceRequest, response: WebResourceResponse) {
    this.request = request;
    this.response = response;
  }
}

export class OnPageBeginEvent {
  public url: string;

  constructor(url: string) {
    this.url = url;
  }
}

export class OnPageEndEvent {
  public url: string;

  constructor(url: string) {
    this.url = url;
  }
}

export class WebHeader {
  public headerKey: string;
  public headerValue: string;

  constructor(headerKey: string, headerValue: string) {
    this.headerKey = headerKey;
    this.headerValue = headerValue;
  }
}

class GetEnvOptions extends BaseOptions<GetEnvResult> {
}

class GetEnvResult {
  public deviceType?: string;
  public brand?: string;
  public productModel?: string;
  public osFullName?: string;
}

class CheckJsApiOptions extends BaseOptions<CheckJsApiResult> {
  public jsApiList?: string[];
}

class CheckJsApiResult {
  public checkResult?: Map<string, boolean>;

  constructor(checkResult?: Map<string, boolean>) {
    this.checkResult = checkResult;
  }
}

class PickCameraOptions extends BaseOptions<PickCameraResult> {
  public mediaTypes?: string[];
  public cameraPosition?: number;
  public saveUri?: string;
  public videoDuration?: number;
}

class PickCameraResult {
  public resultCode?: number;
  public resultUri?: string;
  public mediaType?: string;

  constructor(resultCode?: number, resultUri?: string, mediaType?: string) {
    this.resultCode = resultCode;
    this.resultUri = resultUri;
    this.mediaType = mediaType;
  }
}

class SelectPhotoOptions extends BaseOptions<SelectPhotoResult> {
  public mimeType?: string;
  public maxSelectNumber?: number;
  public isPhotoTakingSupported?: boolean;
  public isEditSupported?: boolean;
  public isSearchSupported?: boolean;
  public recommendationType?: number;
  public preselectedUris?: string[];
}

class SelectPhotoResult {
  public photoUris?: string[];
  public isOriginalPhoto?: boolean;

  constructor(photoUris?: string[], isOriginalPhoto?: boolean) {
    this.photoUris = photoUris;
    this.isOriginalPhoto = isOriginalPhoto;
  }
}

class OpenPreviewOptions extends BaseOptions<OpenPreviewResult> {
  public title?: string;
  public uri?: string;
  public mimeType?: string;
}

class OpenPreviewResult {
}

class UploadFileOptions extends BaseOptions<UploadFileResult> {
  public url?: string;
  public header?: object;
  public method?: string;
  public files?: UploadFile[];
  public data?: UploadRequestData[];
}

class UploadFile {
  public filename: string;
  public name: string;
  public uri: string;
  public type: string;

  constructor(filename: string, name: string, uri: string, type: string) {
    this.filename = filename;
    this.name = name;
    this.uri = uri;
    this.type = type;
  }
}

class UploadRequestData {
  public name?: string;
  public value?: string;
}

class UploadFileResult {
  public taskStates?: UploadFileTaskState[];

  constructor(taskStates?: UploadFileTaskState[]) {
    this.taskStates = taskStates;
  }
}

class UploadFileTaskState {
  public path?: string;
  public responseCode?: number;
  public message?: string;

  constructor(path?: string, responseCode?: number, message?: string) {
    this.path = path;
    this.responseCode = responseCode;
    this.message = message;
  }
}

class DownloadFileOptions extends BaseOptions<DownloadFileResult> {
  public url?: string;
  public header?: object;
  public fileName?: string;
  public enableMetered?: boolean;
  public enableRoaming?: boolean;
  public networkType?: number;
}

class DownloadFileResult {
  public uri?: string;

  constructor(uri?: string) {
    this.uri = uri;
  }
}

class GetNetworkTypeOptions extends BaseOptions<GetNetworkTypeResult> {
}

class GetNetworkTypeResult {
  public bearerTypes: number[];
  public networkCap?: number[];
  public linkUpBandwidthKbps?: number;
  public linkDownBandwidthKbps?: number;

  constructor(bearerTypes: number[], networkCap?: number[], linkUpBandwidthKbps?: number,
    linkDownBandwidthKbps?: number) {
    this.bearerTypes = bearerTypes;
    this.networkCap = networkCap;
    this.linkUpBandwidthKbps = linkUpBandwidthKbps;
    this.linkDownBandwidthKbps = linkDownBandwidthKbps;
  }
}

class GetLocationOptions extends BaseOptions<GetLocationResult> {
  public priority?: number;
  public scenario?: number;
  public maxAccuracy?: number;
  public timeoutMs?: number;
}

class GetLocationResult {
  public latitude: number;
  public longitude: number;
  public altitude: number;
  public accuracy: number;
  public speed: number;
  public timeStamp: number;
  public direction: number;
  public timeSinceBoot: number;
  public additions?: string[] | undefined;
  public additionSize?: number;

  constructor(latitude: number, longitude: number, altitude: number, accuracy: number, speed: number,
    timeStamp: number, direction: number, timeSinceBoot: number, additions?: string[], additionSize?: number) {
    this.latitude = latitude;
    this.longitude = longitude;
    this.altitude = altitude;
    this.accuracy = accuracy;
    this.speed = speed;
    this.timeStamp = timeStamp;
    this.direction = direction;
    this.timeSinceBoot = timeSinceBoot;
    this.additions = additions;
    this.additionSize = additionSize;
  }
}
