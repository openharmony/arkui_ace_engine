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

@Component
export struct FullScreenLaunchComponent {
  @BuilderParam content: Callback<void> = this.doNothingBuilder;
  context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;
  appId: string = "";
  options?: AtomicServiceOptions
  @State private isShow: boolean = false;

  @Builder
  doNothingBuilder() {
  };

  resetOptions() {
    if (this.options?.parameters) {
      this.options.parameters['ohos.extra.param.key.showMode'] = 1;
      this.options.parameters['ability.want.params.IsNotifyOccupiedAreaChange'] = true;
      hilog.info(0x3900, 'FullScreenLaunchComponent', 'replaced options is %{public}s !', JSON.stringify(this.options))
    } else {
      this.options = {
        parameters: {
          'ohos.extra.param.key.showMode': 1,
          'ability.want.params.IsNotifyOccupiedAreaChange': true
        }
      }
    }
  }

  async checkAbility() {
    this.resetOptions()
    try {
      const res: boolean = await abilityManager.isEmbeddedOpenAllowed(this.context, this.appId)
      if (res) {
        this.isShow = true;
        hilog.info(0x3900, 'FullScreenLaunchComponent', ' EmbeddedOpen is Allowed!')
      } else {
        this.popUp()
      }
    } catch (e) {
      hilog.error(0x3900, 'FullScreenLaunchComponent', 'isEmbeddedOpenAllowed called error!%{public}s', e.message)
    }
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
    })
      .height('100%')
      .width('100%')
      .onRelease(
        () => {
          this.isShow = false;
        }
      ).onError(
      err => {
        this.isShow = false;
        hilog.error(0x3900, 'FullScreenLaunchComponent', 'call up UIExtension error!%{public}s', err.message)
        this.getUIContext().showAlertDialog({
          message: err.message
        })
      }
    )
  }
}