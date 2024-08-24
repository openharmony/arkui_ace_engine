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
import { Callback } from '@ohos.base';
import AtomicServiceOptions from '@ohos.app.ability.AtomicServiceOptions';
import commonEventManager from '@ohos.commonEventManager';
import Base from '@ohos.base';

export class LaunchController {
  public launchAtomicService = (appId: string, options?: AtomicServiceOptions) => {};
}

const EMBEDDED_FULL_MODE: number = 1;

@Component
export struct InnerFullScreenLaunchComponent {
  @BuilderParam content: Callback<void> = this.doNothingBuilder;
  private context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;
  controller: LaunchController = new LaunchController();
  private appId: string = '';
  private options?: AtomicServiceOptions;
  @State private isShow: boolean = false;
  private subscriber: commonEventManager.CommonEventSubscriber | null = null;
  private launchAtomicService = (appId: string, options?: AtomicServiceOptions) => {
    hilog.info(0x3900, 'InnerFullScreenLaunchComponent',
      'launchAtomicService, appId: %{public}s.', appId);
    this.appId = appId;
    this.options = options;
    this.checkAbility();
  }

  aboutToAppear() {
    let subscribeInfo: commonEventManager.CommonEventSubscribeInfo = {
      events: [commonEventManager.Support.COMMON_EVENT_DISTRIBUTED_ACCOUNT_LOGOUT],
    };

    commonEventManager.createSubscriber(subscribeInfo,
      (err:Base.BusinessError, data: commonEventManager.CommonEventSubscriber) => {
        if (err) {
          hilog.error(0x3900, 'InnerFullScreenLaunchComponent',
            'Failed to create subscriber, err: %{public}s.', err.message);
          return;
        }

        if (data == null || data == undefined) {
          hilog.error(0x3900, 'InnerFullScreenLaunchComponent', 'Failed to create subscriber, data is null.');
          return;
        }

        this.subscriber = data;
        commonEventManager.subscribe(this.subscriber,
          (err: Base.BusinessError, data: commonEventManager.CommonEventData) => {
            if (err) {
              hilog.error(0x3900, 'InnerFullScreenLaunchComponent',
                'Failed to subscribe common event, err: %{public}s.', err.message);
              return;
            }

            hilog.info(0x3900, 'InnerFullScreenLaunchComponent', 'Received account logout event.');
            this.isShow = false;
          })
      })
      this.controller.launchAtomicService = this.launchAtomicService;
  }

  aboutToDisappear() {
    if (this.subscriber !== null) {
      commonEventManager.unsubscribe(this.subscriber, (err) => {
        if (err) {
          hilog.error(0x3900, 'InnerFullScreenLaunchComponent',
            'UnsubscribeCallBack, err: %{public}s.', err.message);
        } else {
          hilog.info(0x3900, 'InnerFullScreenLaunchComponent', 'Unsubscribe.');
          this.subscriber = null;
        }
      })
    }
  }

  @Builder
  doNothingBuilder() {
  };

  resetOptions() {
    if (this.options?.parameters) {
      this.options.parameters['ohos.extra.param.key.showMode'] = EMBEDDED_FULL_MODE;
      this.options.parameters['ability.want.params.IsNotifyOccupiedAreaChange'] = true;
      hilog.info(0x3900, 'InnerFullScreenLaunchComponent', 'replaced options is %{public}s !', JSON.stringify(this.options));
    } else {
      this.options = {
        parameters: {
          'ohos.extra.param.key.showMode': EMBEDDED_FULL_MODE,
          'ability.want.params.IsNotifyOccupiedAreaChange': true,
        }
      };
    }
  }

  async checkAbility() {
    this.resetOptions();
    try {
      const res: boolean = await abilityManager.isEmbeddedOpenAllowed(this.context, this.appId);
      if (res) {
        this.isShow = true;
        hilog.info(0x3900, 'InnerFullScreenLaunchComponent', ' EmbeddedOpen is Allowed!');
      } else {
        hilog.info(0x3900, 'InnerFullScreenLaunchComponent', ' EmbeddedOpen is not Allowed!');
        this.popUp();
      }
    } catch (e) {
      hilog.error(0x3900, 'InnerFullScreenLaunchComponent', 'isEmbeddedOpenAllowed called error!%{public}s', e.message);
    }
  }

  async popUp() {
    this.isShow = false;
    try {
      const ability = await this.context.openAtomicService(this.appId, this.options);
      hilog.info(0x3900, 'InnerFullScreenLaunchComponent', '%{public}s open service success!', ability.want);
    } catch (e) {
      hilog.error(0x3900, 'InnerFullScreenLaunchComponent', '%{public}s open service error!', e.message);
    }
  }

  build() {
    Row() {
      this.content();
    }
    .justifyContent(FlexAlign.Center)
    .bindContentCover($$this.isShow, this.uiExtensionBuilder())
  }

  @Builder
  uiExtensionBuilder() {
    UIExtensionComponent({
      bundleName: `com.atomicservice.${this.appId}`,
      flags: this.options?.flags,
      parameters: this.options?.parameters
    })
      .height('100%')
      .width('100%')
      .onRelease(
        () => {
          hilog.error(0x3900, 'InnerFullScreenLaunchComponent', 'onRelease');
          this.isShow = false;
        }
      ).onError(
      err => {
        this.isShow = false;
        hilog.error(0x3900, 'InnerFullScreenLaunchComponent', 'call up UIExtension error! %{public}s', err.message);
        this.getUIContext().showAlertDialog({
          message: err.message
        });
      }
    )
  }
}