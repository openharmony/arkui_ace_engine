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

import web_webview from '@ohos.web.webview';
import { ComplainInfo } from '../../complainApi/ComplainInfo';
import { ComplainParams } from '../../complainApi/ComplainParams';
import { ConfigVo, generateUUID, UploadCountVo } from '../../complainApi/ComplainUtils';
import { common } from '@kit.AbilityKit';
import { DeviceInfoUtil } from '../../complainApi/DeviceTypeUtil';
import { deviceInfo } from '@kit.BasicServicesKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { LanguageUtil } from '../../complainApi/LanguageUtil';
import business_error from '@ohos.base';
import { JsonUtils } from '../../complainApi/JsonUtil';
import { ComplainFileSelectUtil } from '../../complainApi/ComplainFileSelectUtil';
import { KeyCode } from '@kit.InputKit';
import { connection } from '@kit.NetworkKit';
import { inputMethod } from '@kit.IMEKit';

const TAG: string = 'complainSheetComponents';
const DOMAIN: number = 0x0f5c;

@Component
export struct complainSheetComponents {
  stack: NavPathStack = new NavPathStack();
  private webviewController: web_webview.WebviewController = new web_webview.WebviewController();
  params: ComplainParams = new ComplainParams();
  fromSheet: boolean = false;
  @State mediaPreviewTitleVisible: boolean = false; // 预览文件标题栏是否展示
  @State complainInfo: ComplainInfo = new ComplainInfo();
  @State customTitle: ResourceStr = '';
  @State title: ResourceStr = '';
  private isWeb: boolean = false;
  @State isShowLoading: boolean = true;
  private isFinished: boolean = false;
  private complainUrl: string = '';
  private configVo: ConfigVo = new ConfigVo();
  private deviceType: string = '2in1';
  private productEnvStr: string = 'https://complain-productEnvStr';
  private devEnvStr: string = 'https://complain-devEnvStr';
  private mirrorEnvStr: string = 'https://complain-mirrorEnvStr';
  private tmpEnvStr: string = this.productEnvStr;
  private canUploadCount: number = 5;
  private context = this.getUIContext().getHostContext() as common.UIAbilityContext;
  private themeStorage: ThemeColorMode = ThemeColorMode.SYSTEM;

  async aboutToAppear(): Promise<void> {
    let navigationInfo: NavigationInfo = this.queryNavigationInfo() as NavigationInfo;
    if (navigationInfo != undefined) {
      this.stack = navigationInfo.pathStack;
    }

    DeviceInfoUtil.init();

    const navParams: Record<string, string> = this.stack.getParamByIndex(
      this.stack.getIndexByName('complainSheetComponent')[0]
    )! as Record<string, string>;
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
    } else {
      this.complainInfo.deviceId = deviceInfo.ODID;
    }
    this.complainInfo.showMediaPreView = () => {
      this.title = '';
      this.mediaPreviewTitleVisible = true;
    }
    this.complainInfo.hideMediaPreView = () => {
      this.title = this.customTitle;
      this.mediaPreviewTitleVisible = false;
    }
    this.complainInfo.theme = this.params.theme;
    this.complainInfo.fileList = this.params.fileList;
    this.complainInfo.jwtToken = this.params.jwtToken;
    this.complainInfo.businessKey = this.params.businessKey;
    this.complainInfo.channelId = this.params.channelId ? this.params.channelId : 'OHOS';
    this.complainInfo.disableContactInfo = this.params.disableContactInfo;
    this.complainInfo.disableUserUpload = this.params.disableUserUpload;
    this.complainInfo.showBackButton = true;
    this.complainInfo.additionalContext = this.params.additionalContext;
    this.complainInfo.afterSubmit = (jsonString?: string) => {
      if (this.params.afterSubmit) {
        this.params.afterSubmit(jsonString);
        this.isFinished = true;
      }
    }
    this.complainInfo.operate = (options: string) => {
      hilog.error(DOMAIN, TAG, 'complain operate type: ' + options);
      switch (options) {
        case 'ready':
          this.isShowLoading = false;
          break;
        default:
          break;
      }
    }
    this.complainInfo.historyBack = () => {
      if (this.params.onHistoryBack) {
        this.params.onHistoryBack();
      } else {
        this.params.pathInfo.pop();
      }
    }
  }

  async refreshComplainUrl() {
    const language = LanguageUtil.getLanguageCode();
    const accessMode = 'bindSheet';
    if (this.params.colorMode === ColorMode.DARK) {
      this.complainUrl =
        `${this.tmpEnvStr}?next=1&lang=${language}&theme=dark&appId=&{this.params.appId}&accessMode=${accessMode}&deviceType=${this.deviceType}`
    } else {
      this.complainUrl =
        `${this.tmpEnvStr}?next=1&lang=${language}&appId=${this.params.appId}&accessMode=${accessMode}&deviceType=${this.deviceType}`
    }
    this.webviewController.registerJavaScriptProxy(this.complainInfo,
      'complainJSInterface',
      ['complainAddInfo', 'refreshAccessToken', 'afterSubmit', 'historyBack', 'showMediaPreview', 'operate',
        'refreshComplainSessionId', 'onEvent'])

    hilog.info(DOMAIN, TAG, 'start to loadComplainUrl: ' + this.complainUrl);
    if (this.complainInfo.hideMediaPreView) {
      this.complainInfo.hideMediaPreView();
    }
    this.webviewController.loadUrl(this.complainUrl);
    setTimeout(() => {
      if (this.isShowLoading === true) {
        this.isShowLoading = false;
      }
    }, 7000)
  }

  async init() {
    await this.initComplainParams();
    await this.initComplainInfo();
    this.refreshComplainUrl();
  }

  async selectFile(result: FileSelectorResult) : Promise<void> {
    this.webviewController.runJavaScript('uploadMaterialData()', async  (error, res) => {
      if (error) {
        let e: business_error.BusinessError = error as business_error.BusinessError;
        hilog.error(DOMAIN, TAG, `run JavaScript error, ErrorCode: ${e.code}, Message: ${e.message}`);
        return;
      }
      if (res) {
        hilog.info(DOMAIN, TAG, `The uploadMaterialData() return value is : ${res}}`);
        let uploadLimit = JsonUtils.parse(res) as UploadCountVo;
        this.canUploadCount = uploadLimit.canUploadCount ? uploadLimit.canUploadCount : 5;
      } else {
        this.canUploadCount = 5;
      }
      const choseFile = await ComplainFileSelectUtil.selectFiles(this.canUploadCount, this.configVo);
      result.handleFileList(choseFile);
    })
    return;
  }

  @Builder
  web() {
    Web({ src: '', controller: this.webviewController })
      .id('Web')
      .accessibilityLevel('no')
      .backgroundColor($r('sys.color.background_primary'))
      .onKeyEvent(event => {
        if (!event || !this.fromSheet) {
          return;
        }
        if (event.type === KeyType.Down && event.keyCode === KeyCode.KEYCODE_ESCAPE) {
          try {
            if (this.mediaPreviewTitleVisible) {
              this.webviewController.runJavaScript('closePreviewPanel()', () => {
              })
              if (this.complainInfo.hideMediaPreView) {
                this.complainInfo.hideMediaPreView();
              }
            } else if (this.webviewController.getUrl().indexOf('complainRecordList') >= 0 ||
              this.webviewController.getUrl().indexOf('complainGuide') >= 0) {
              this.title = this.customTitle;
              this.webviewController.backward();
            } else if (this.params.onBackPressed) {
              this.params.onBackPressed();
            } else {
              this.params.pathInfo.pop();
            }
          } catch (e) {
            hilog.error(DOMAIN, TAG, `complain accesssBackWard error: ${e}}`);
          }
        }
      })
      .onShowFileSelector((event) => {
        hilog.info(DOMAIN, TAG, `onShowFileSelector`);
        if (event) {
          this.selectFile(event.result)
        }
        return true;
      })
      .onControllerAttached(async () => {
        try {
          await this.init();
        } catch (error) {
          let e: business_error.BusinessError = error as business_error.BusinessError;
          hilog.error(DOMAIN, TAG, `complain onControllerAttached error: ${e?.message}`);
        }
      })
      .onPageBegin(() => {
        hilog.info(DOMAIN, TAG, `complain page onPageBegin`);
      })
      .onPageEnd(() => {
        hilog.info(DOMAIN, TAG, `complain page onPageEnd`);
        if (connection.hasDefaultNetSync()) {
          this.isWeb = true;
        } else {
          this.isWeb = false;
        }
      })
      .onErrorReceive((event) => {
        // 网页加载遇到错误时触发该回调，无网不会触发该回调
        hilog.error(DOMAIN, TAG, `complain page onErrorReceive ` + event?.error.getErrorInfo());
        if (event?.error.getErrorInfo() === 'ERR_INTERNET_DISCONNECTED') {
          if (!this.isWeb) {
            this.isShowLoading = false;
          }
        } else if (event?.error.getErrorInfo() === 'ERROR_TIMED_OUT' && !DeviceInfoUtil.isTv()) {
          this.isShowLoading = false;
        }
      })
      .onHttpErrorReceive((event) => {
        // 网页加载资源遇到的HTTP错误（响应码 >= 400）时触发该回调
        hilog.error(DOMAIN, TAG, `complain page onHttpErrorReceive, code: ` + event?.response.getResponseCode() +
          'message: ' + event?.response.getReasonMessage());
      })
      .onConsole((event) => {
        hilog.info(DOMAIN, TAG, `complain log: ` + event?.message.getMessage());
        return true;
      })
      .nestedScroll({
        scrollForward: NestedScrollMode.SELF_ONLY,
        scrollBackward: NestedScrollMode.SELF_ONLY
      })
      .minFontSize(1)
      .darkMode(WebDarkMode.Auto)
      .overScrollMode(OverScrollMode.ALWAYS)
      .javaScriptAccess(true)
      .fileAccess(false)
      .geolocationAccess(false)
      .width('100%')
      .height('100%')
      .backgroundColor(Color.Transparent)
      .allowDrop(null)
  }

  @Builder
  private buildNavDestinationContent() {
    this.web();
  }

  back = (): boolean => {
    hilog.info(DOMAIN, TAG, 'Enter Back');
    if (this.mediaPreviewTitleVisible) {
      this.webviewController.runJavaScript('closePreviewPanel', () => {
      })
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
    } catch (e) {
      hilog.error(DOMAIN, TAG, 'complain accessBackward error: ', e);
    }
    if (this.params.onBackPressed) {
      this.params.onBackPressed();
    } else {
      this.params.pathInfo.pop();
    }
    return true;
  }

  build() {
    NavDestination() {
      this.buildNavDestinationContent();
    }
    .backgroundColor('#202224')
    .height('100%')
    .width('100%')
    .title('XXX')
    .onBackPressed(this.back)
  }
}