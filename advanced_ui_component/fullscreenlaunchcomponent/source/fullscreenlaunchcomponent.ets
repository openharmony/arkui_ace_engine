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
import hilog from '@ohos.hilog';
import abilityManager from '@ohos.app.ability.abilityManager';
import common from '@ohos.app.ability.common';
import { ErrorCallback, Callback, BusinessError } from '@ohos.base';
import AtomicServiceOptions from '@ohos.app.ability.AtomicServiceOptions';
import commonEventManager from '@ohos.commonEventManager';
import { bundleManager } from '@kit.AbilityKit';
import Base from '@ohos.base';

const API20: number = 20;
const errCodeAbnormal: number = 100014;
const errCodeCapabilityNotSupported: number = 801;
const requestComponentTerminateKey: string = 'ohos.param.key.requestComponentTerminate';
const atomicServiceDataTag: string = "ohos.atomicService.window";
@Component
export struct FullScreenLaunchComponent {
  @BuilderParam content: Callback<void> = this.doNothingBuilder;
  context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;
  appId: string = "";
  options?: AtomicServiceOptions
  @State private isShow: boolean = false;
  private subscriber: commonEventManager.CommonEventSubscriber | null = null;
  private apiVersion: number = 0;
  onError?: ErrorCallback;
  onTerminated?: Callback<TerminationInfo>;
  onReceive?: Callback<Record<string, Object>>;

  aboutToAppear() {
    let bundleFlags = bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION |
        bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_METADATA;
    try {
        bundleManager.getBundleInfoForSelf(bundleFlags).then((data) => {
            hilog.info(0x3900, 'FullScreenLaunchComponent', 'getBundleInfoForSelf success, data: %{public}s.', JSON.stringify(data.targetVersion % 1000));
            this.apiVersion = data.targetVersion % 1000;
        }).catch((err) => {
            hilog.error(0x3900, 'FullScreenLaunchComponent', 'getBundleInfoForSelf fail_1, cause: %{public}s.', err.message);
        });
    }
    catch (err) {
        let message = err.message;
        hilog.error(0x3900, 'FullScreenLaunchComponent', 'getBundleInfoForSelf fail_2, cause: %{public}s.', message);
    }
    let subscribeInfo: commonEventManager.CommonEventSubscribeInfo = {
      events: [commonEventManager.Support.COMMON_EVENT_DISTRIBUTED_ACCOUNT_LOGOUT],
    }

    commonEventManager.createSubscriber(subscribeInfo,
      (err: Base.BusinessError, data: commonEventManager.CommonEventSubscriber) => {
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
        commonEventManager.subscribe(this.subscriber,
          (err: Base.BusinessError, data: commonEventManager.CommonEventData) => {
            if (err) {
              hilog.error(0x3900, 'FullScreenLaunchComponent',
                'Failed to subscribe common event, err: %{public}s.', JSON.stringify(err))
              return;
            }

            hilog.info(0x3900, 'FullScreenLaunchComponent', 'Received account logout event.')
            this.isShow = false;
          })
      })
  }

  aboutToDisappear() {
    if (this.subscriber !== null) {
      commonEventManager.unsubscribe(this.subscriber, (err) => {
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
    if (this.options?.parameters) {
      this.options.parameters['ohos.extra.param.key.showMode'] = 1;
      this.options.parameters['ability.want.params.IsNotifyOccupiedAreaChange'] = true;
      this.options.parameters['ability.want.params.IsModal'] = true;
      this.options.parameters['ohos.extra.atomicservice.param.key.isFollowHostWindowMode'] = (this.apiVersion >= API20);
      hilog.info(0x3900, 'FullScreenLaunchComponent', 'replaced options is %{public}s !', JSON.stringify(this.options))
    } else {
      this.options = {
        parameters: {
          'ohos.extra.param.key.showMode': 1,
          'ability.want.params.IsNotifyOccupiedAreaChange': true,
          'ability.want.params.IsModal': true,
          'ohos.extra.atomicservice.param.key.isFollowHostWindowMode': (this.apiVersion >= API20)
        }
      }
    }
  }

  async checkAbility() {
    this.resetOptions()
    abilityManager.queryAtomicServiceStartupRule(this.context, this.appId)
      .then((data: abilityManager.AtomicServiceStartupRule) => {
        if (data.isOpenAllowed) {
          if (data.isEmbeddedAllowed) {
            this.isShow = true;
            hilog.info(0x3900, 'FullScreenLaunchComponent', 'EmbeddedOpen is Allowed!')
          } else {
            this.popUp()
            hilog.info(0x3900, 'FullScreenLaunchComponent', 'popUp is Allowed!')
          }
        } else {
          hilog.info(0x3900, 'FullScreenLaunchComponent', 'is not allowed open!')
        }
      }).catch((err: BusinessError) => {
        hilog.error(0x3900, 'FullScreenLaunchComponent', 'queryAtomicServiceStartupRule called error!%{public}s', err.message)
        if (errCodeCapabilityNotSupported === err.code) {
          this.popUp()
        }
      });
  }

  async popUp() {
    this.isShow = false;
    try {
      const ability = await this.context.openAtomicService(this.appId, this.options)
      hilog.info(0x3900, 'FullScreenLaunchComponent', '%{public}s open service success!', ability.want)
    } catch (e) {
      hilog.error(0x3900, 'FullScreenLaunchComponent', '%{public}s open service error!', e.message)
    }
  }

  build() {
    Row() {
      this.content();
    }.justifyContent(FlexAlign.Center)
    .onClick(
      () => {
        this.checkAbility();
      }
    ).bindContentCover($$this.isShow, this.uiExtensionBuilder());

  }

  @Builder
  uiExtensionBuilder() {
    UIExtensionComponent({
        bundleName: `com.atomicservice.${this.appId}`,
        flags: this.options?.flags,
        parameters: this.options?.parameters
      },
      {
        windowModeFollowStrategy: this.apiVersion >= API20 ? WindowModeFollowStrategy.FOLLOW_HOST_WINDOW_MODE :
          WindowModeFollowStrategy.FOLLOW_UI_EXTENSION_ABILITY_WINDOW_MODE
      })
      .height('100%')
      .width('100%')
      .backgroundColor($r(`sys.color.background_primary`))
      .onError(
        err => {
          if (this.onError != undefined) {
            this.onError(err);
          }
          this.isShow = false;
          hilog.error(0x3900, 'FullScreenLaunchComponent', 'call up UIExtension error:%{public}d!%{public}s', err.code,
            err.message)
          if (err.code != errCodeAbnormal) {
            this.getUIContext().showAlertDialog({
              message: err.message
            })
          }
        }
      )
      .onTerminated(info => {
        this.isShow = false;
        if (this.onTerminated != undefined) {
          this.onTerminated(info)
        }
      })
      .onReceive(data => {
        if (this.onReceive !== undefined) {
            const sourceKeys = Object.keys(data);
            let atomicServiceData: Record<string, Object> = {};
            for (let i = 0; i < sourceKeys.length; i++) {
                if (sourceKeys[i].includes(atomicServiceDataTag)) {
                    atomicServiceData[sourceKeys[i]] = data[sourceKeys[i]];
                }
            }
            this.onReceive(atomicServiceData);
        }
        if (data[requestComponentTerminateKey]) {
          this.isShow = false;
        }
      })
  }
}