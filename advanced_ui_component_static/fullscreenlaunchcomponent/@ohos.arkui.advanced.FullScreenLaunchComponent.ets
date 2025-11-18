/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import hilog from '@ohos.hilog';
import abilityManager from '@ohos.app.ability.abilityManager';
import common from '@ohos.app.ability.common';
import { ErrorCallback, Callback, BusinessError} from '@ohos.base';
import AtomicServiceOptions from '@ohos.app.ability.AtomicServiceOptions';
import commonEventManager from '@ohos.commonEventManager';
import { State, Memo } from '@ohos.arkui.stateManagement';
import { $$ } from '@kit.ArkUI';
import { ReceiveCallback, RecordData, Column, Text, Row, UIExtensionComponent, Component, BuilderParam, TerminationInfo, Builder, FlexAlign, ClickEvent, AlertDialogParamWithConfirm, CustomBuilder, ContentCoverOptions } from '@ohos.arkui.component';
import bundleManager from "@ohos.bundle.bundleManager"

const errCodeAbnormal: number = 100014;
const API20: number = 20;
const requestComponentTerminateKey: string = 'ohos.param.key.requestComponentTerminate';
const atomicServiceDataTag: string = "ohos.atomicService.window";
@Component
export struct FullScreenLaunchComponent {
  @BuilderParam content:() => void = this.doNothingBuilder;
  context: common.UIAbilityContext = this.getUIContext().getHostContext() as common.UIAbilityContext;
  appId: string = "";
  options?: AtomicServiceOptions
  @State private isShow: boolean = false;
  private subscriber: commonEventManager.CommonEventSubscriber | null = null;
  private apiVersion: int = 0;
  onError?: ErrorCallback<BusinessError>;
  onTerminated?: Callback<TerminationInfo>;
  onReceive?: ReceiveCallback;

  aboutToAppear() {
    hilog.error(0x3900, 'FullScreenLaunchComponent', 'start FullScreenLaunchComponent');
    let bundleFlags = bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION |
        bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_METADATA;
    bundleManager.getBundleInfoForSelf(bundleFlags).then((data): void => {
      let tmp = new Int(data.targetVersion);
      this.apiVersion = tmp % 1000;
      hilog.info(0x3900, 'FullScreenLaunchComponent',
        'getBundleInfoForSelf success, data: %{public}s.', JSON.stringify(this.apiVersion));
    }).catch((err): void => {
      if (err instanceof BusinessError) {
        hilog.error(0x3900, 'FullScreenLaunchComponent',
          'getBundleInfoForSelf fail_1, cause: %{public}s.', err.message);
      }
    });
    let subscribeInfo: commonEventManager.CommonEventSubscribeInfo = {
      events: [commonEventManager.Support.COMMON_EVENT_DISTRIBUTED_ACCOUNT_LOGOUT],
    }

    commonEventManager.createSubscriber(subscribeInfo,
      (err: BusinessError<void> | null, data: commonEventManager.CommonEventSubscriber | undefined) => {
        if (err) {
          hilog.error(0x3900, 'FullScreenLaunchComponent',
            'Failed to create subscriber, err: %{public}s.', JSON.stringify(err))
          return;
        }

        if (data == null || data == undefined) {
          hilog.error(0x3900, 'FullScreenLaunchComponent', 'Failed to create subscriber, data is null.')
          return;
        }

        this.subscriber = data;
        commonEventManager.subscribe(this.subscriber as commonEventManager.CommonEventSubscriber,
          (err: BusinessError | null, data: commonEventManager.CommonEventData | undefined) => {
            if (err) {
              hilog.error(0x3900, 'FullScreenLaunchComponent',
                'Failed to subscribe common event, err: %{public}s.', JSON.stringify(err))
              return;
            }

            hilog.info(0x3900, 'FullScreenLaunchComponent', 'Received account logout event.')
            this.isShow = false;
          })
      })
    hilog.error(0x3900, 'FullScreenLaunchComponent', 'end FullScreenLaunchComponent')
  }

  aboutToDisappear() {
    if (this.subscriber !== null) {
      commonEventManager.unsubscribe(this.subscriber as commonEventManager.CommonEventSubscriber, (err) => {
        if (err) {
          hilog.error(0x3900, 'FullScreenLaunchComponent',
            'UnsubscribeCallBack, err: %{public}s.', JSON.stringify(err))
        } else {
          hilog.info(0x3900, 'FullScreenLaunchComponent', 'Unsubscribe.')
          this.subscriber = null
        }
      })
    }
  }

  @Builder
  doNothingBuilder() {
  };

  resetOptions() {
    let isFollowHostWindowMode: boolean = false;
    if (this.apiVersion >= API20) {
      isFollowHostWindowMode = true;
    }
    if (this.options?.parameters) {
      const options: AtomicServiceOptions = this.options as AtomicServiceOptions;
      const parameters: Record<string, Object> = options.parameters as Record<string, Object>;
      parameters['ohos.extra.param.key.showMode'] = 1;
      parameters['ability.want.params.IsNotifyOccupiedAreaChange'] = true;
      parameters['ability.want.params.IsModal'] = true;
      parameters['ohos.extra.atomicservice.param.key.isFollowHostWindowMode'] = isFollowHostWindowMode;
      hilog.info(0x3900, 'FullScreenLaunchComponent', 'replaced options is %{public}s !', JSON.stringify(this.options))
    } else {
      this.options = {
        parameters: {
          'ohos.extra.param.key.showMode': 1,
          'ability.want.params.IsNotifyOccupiedAreaChange': true,
          'ability.want.params.IsModal': true,
          'ohos.extra.atomicservice.param.key.isFollowHostWindowMode': isFollowHostWindowMode
        } as Record<string, Object>
      } as AtomicServiceOptions
    }
  }

  async checkAbility() {
    this.resetOptions()
    let embeddedOpenAllowed: boolean = false;
    abilityManager.isEmbeddedOpenAllowed(this.context, this.appId).then((data: boolean | undefined): void => {
      if(data) {
        hilog.info(0x0000, 'FullScreenLaunchComponent', 'isEmbeddedOpenAllowed true.');
        embeddedOpenAllowed = true;
      } else {
        hilog.info(0x0000, 'FullScreenLaunchComponent', 'isEmbeddedOpenAllowed false.');
      }
      if (embeddedOpenAllowed) {
        this.isShow = true;
        hilog.info(0x3900, 'FullScreenLaunchComponent', 'EmbeddedOpen is Allowed!');
      } else {
        this.popUp();
        hilog.info(0x3900, 'FullScreenLaunchComponent', 'popUp is Allowed!');
      }
    }).catch((err: BusinessError<void>|null): void => {
      hilog.info(0x0000, 'FullScreenLaunchComponent',
        'isEmbeddedOpenAllowed failed, code is ${err?.code}, message is ${err?.message}');
    });
  }

  async popUp() {
    this.isShow = false;
    try {
      const ability = await this.context.openAtomicService(this.appId, this.options);
      hilog.info(0x3900, 'FullScreenLaunchComponent', '%{public}s open service success!', ability.want);
    }
    catch (err) {
      if (err instanceof BusinessError) {
        hilog.error(0x3900, 'FullScreenLaunchComponent', '%{public}s open service error!', err.message);
      }
    }
  }

  build() {
    hilog.error(0x3900, 'FullScreenLaunchComponent',
      'FullScreenLaunchComponent build start')
    Row() {
      this.content();
    }.justifyContent(FlexAlign.Center)
    .onClick(
      (ev: ClickEvent) => {
        this.checkAbility();
      }
    ).bindContentCover($$(this.isShow), (@Memo () => {
      this.uiExtensionBuilder()
    }) as CustomBuilder, {} as ContentCoverOptions);

    hilog.error(0x3900, 'FullScreenLaunchComponent',
      'FullScreenLaunchComponent build end')
  }

  @Builder
  uiExtensionBuilder() {
    UIExtensionComponent({
      bundleName: `com.atomicservice.${this.appId}`,
      parameters: this.options?.parameters
    })
      .height('100%')
      .width('100%')
      .onError(
        (err: BusinessError) => {
          if (this.onError != undefined) {
            const errCallback = this.onError as ErrorCallback<BusinessError>;
            errCallback(err);
          }
          this.isShow = false;
          hilog.error(0x3900, 'FullScreenLaunchComponent', 'call up UIExtension error:%{public}d!%{public}s', err.code,
            err.message)
          if (err.code != errCodeAbnormal) {
            this.getUIContext().showAlertDialog({
              message: err.message as string
            } as AlertDialogParamWithConfirm)
          }
        } as ErrorCallback<BusinessError>
      )
      .onTerminated((info: TerminationInfo) => {
        this.isShow = false;
        if (this.onTerminated != undefined) {
          const onTerminatedCallback = this.onTerminated as Callback<TerminationInfo>;
          onTerminatedCallback(info)
        }
      } as Callback<TerminationInfo>)
      .onReceive((data: Record<string, RecordData>) => {
        if (this.onReceive !== undefined) {
          let atomicServiceData: Record<string, RecordData> = {};
          for (let kv of data) {
            if (kv[0].includes(atomicServiceDataTag)) {
              atomicServiceData[kv[0]] = kv[1];
            }
          }
          const onReceiveCallback = this.onReceive as ReceiveCallback;
          onReceiveCallback(atomicServiceData);
        }
        if (data[requestComponentTerminateKey]) {
          this.isShow = false;
        }
      })
  }
}