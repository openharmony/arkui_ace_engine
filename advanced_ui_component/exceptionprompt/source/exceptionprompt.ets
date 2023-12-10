/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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
const START_TIME = 250
const END_TIME = 200
const HEIGHT = 80
const BORDER_RADIUS = 12
const OPACITY_NUM = 0.18

export enum HardwareStatusType {
  ON = 0,
  OFF = 1,
}

export enum MarginStateType {
  DEFAULT_MARGIN = 0,
  FIT_MARGIN = 1,
}

export enum PromptType {
  DEFAULT_HIDE = 0,
  NETWORK_NOT_CONNECTED = 1,
  NETWORK_CONNECTED_UNSTABLE = 2,
  UNSTABLE_CONNECT_SERVER = 3,
  CUSTOM_NETWORK_TIPS = 4,
  CUSTOM_TIPS = 5,
}

export interface PromptOptions {
  hardwareStatus: HardwareStatusType,
  icon?: ResourceStr,
  tip?: ResourceStr,
  networkTip?: ResourceStr,
  marginState: MarginStateType
}

interface ErrorTipsInfoType {
  networkConnected: ResourceStr;
  networkConnectedUnstable: ResourceStr;
  unstableConnectServer: ResourceStr;
  customNetworkLeft?: ResourceStr;
  customNetworkRight?: ResourceStr;
  customTips?: ResourceStr;
}

@Component
export struct ExceptionPrompt {
  @Prop @Watch('typeStatusChange') type: PromptType
  @Prop options: PromptOptions
  @State isShowStatus: boolean = false
  @State isState: boolean = false
  @State tipText: string = ''
  touchBackgroundColor: Resource = $r('sys.color.ohos_id_color_sub_background_transparent')
  setNetwork: ResourceStr = $r('sys.string.ohos_set_network')
  @State errorDefaultObj: ErrorTipsInfoType = {
    networkConnected: '网络未连接',
    networkConnectedUnstable: '网络连接不稳定，请点击重试',
    unstableConnectServer: '无法连接到服务器，请点击重试',
    customNetworkLeft: '无法获取',
    customNetworkRight: '请点击重试',
    customTips: ''
  }
  onReconnectionFunction: () => void = () => {
    // Click the text on the left to change into the connecting state
  }
  onConfigureNetworkFunction: () => void = () => {
    // Click Set Network to open the Set network pop-up interface
  }

  SetText() {
    if (this.type === PromptType.NETWORK_NOT_CONNECTED) {
      this.tipText = `${this.errorDefaultObj.networkConnected}`

    }
    if (this.type === PromptType.NETWORK_CONNECTED_UNSTABLE) {
      this.tipText = `${this.errorDefaultObj.networkConnectedUnstable}`
    }
    if (this.type === PromptType.UNSTABLE_CONNECT_SERVER) {
      this.tipText = `${this.errorDefaultObj.unstableConnectServer}`
    }
    if (this.type === PromptType.CUSTOM_NETWORK_TIPS) {
      this.tipText = `${this.errorDefaultObj.customNetworkLeft}${this.options.networkTip || ''}，${this.errorDefaultObj.customNetworkRight}`
    }
    if (this.type === PromptType.CUSTOM_TIPS) {
      this.tipText = `${this.options.tip}` || `${this.errorDefaultObj.customTips}`
    }
  }
  // 监听Type数据变化
  typeStatusChange(_propName: string): void {
    if (this.type !== PromptType.DEFAULT_HIDE) {
      if (this.isState && this.type !== PromptType.NETWORK_NOT_CONNECTED && this.type !== PromptType.NETWORK_CONNECTED_UNSTABLE) {
        setTimeout(() => {
          this.isState = false
        }, END_TIME)
      }
      if (this.type === PromptType.NETWORK_NOT_CONNECTED || this.type === PromptType.NETWORK_CONNECTED_UNSTABLE) {
        if (!this.isShowStatus) {
          this.isState = true
        } else {
          setTimeout(() => {
            this.isState = true
          }, START_TIME)
        }
      }
      if (this.isShowStatus) {
        this.isShowStatus = false
        setTimeout(() => {
          this.SetText()
          this.isShowStatus = true
        }, START_TIME)
      } else {
        this.SetText()
        this.isShowStatus = true
      }
    } else {
      this.isShowStatus = false
      setTimeout(() => {
        this.isState = false
      }, START_TIME)
    }
  }

  aboutToAppear() {
    if (this.type !== PromptType.DEFAULT_HIDE) {
      this.isShowStatus = true
      this.SetText()
    }
    if (this.type === PromptType.NETWORK_NOT_CONNECTED || this.type === PromptType.NETWORK_CONNECTED_UNSTABLE) {
      this.isState = true

    }
  }

  isOneColum() {
    return (this.type === PromptType.UNSTABLE_CONNECT_SERVER || this.type === PromptType.CUSTOM_NETWORK_TIPS) || JSON.stringify(this.tipText)
      .length < 10
  }

  OptionalMargins() {
    return this.options.marginState === MarginStateType.DEFAULT_MARGIN ? { left: $r('sys.float.ohos_id_card_margin_start'), right: $r('sys.float.ohos_id_card_margin_end') } : { left: $r('sys.float.ohos_id_max_padding_start'), right: $r('sys.float.ohos_id_max_padding_end') }
  }

  @Builder FirstBuilder() {
    Column() {
    }
    .height('100%')
    .width('100%')
    .borderRadius(BORDER_RADIUS)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
  }

  @Builder SecondBuilder() {
    Column() {
    }
    .height('100%')
    .width('100%')
    .borderRadius(BORDER_RADIUS)
    .backgroundColor($r('sys.color.ohos_id_color_warning'))
    .opacity(OPACITY_NUM)
    .position({})
    .zIndex(999)
  }

  @Builder TextBuilder() {
    Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
      Flex({ alignItems: ItemAlign.Center }) {
        Image(this.options.icon || $r('app.media.ic_public_fail'))
          .width("24vp")
          .height('24vp')
          .objectFit(ImageFit.Contain)
          .fillColor($r('sys.color.ohos_id_color_warning'))
        Text(this.tipText)
          .fontSize($r('sys.float.ohos_id_text_size_body1'))
          .fontColor($r('sys.color.ohos_id_color_warning'))
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .maxLines(2)
          .margin({ left: 16, right: 16 })
      }
      .width('100%')
      .height('100%')
      // 设置网络
      if (this.isState) {
        Button({ stateEffect: true, type: ButtonType.Normal }) {
          Row() {
            Text(this.setNetwork)
              .fontSize($r('sys.float.ohos_id_text_size_body2'))
              .fontColor($r('sys.color.ohos_id_color_text_secondary'))
              .maxLines(1)
              .padding(0)
              .margin({ right: 4 })
              .textAlign(TextAlign.End)
            Image($r('sys.media.ohos_ic_public_arrow_right'))
              .width('12vp')
              .height('24vp')
              .fillColor($r('sys.color.ohos_id_color_tertiary'))
          }
        }
        .backgroundColor(this.touchBackgroundColor)
        .width(this.isState ? 120 : 0)
        .height(32)
        .borderRadius($r('sys.float.ohos_id_corner_radius_subtab'))
        .padding({ right: 8, left: 8 })
        .onTouch((event) => {
          if (event.type === TouchType.Down) {
            this.touchBackgroundColor = $r('sys.color.ohos_id_color_click_effect')
          } else if (event.type === TouchType.Up) {
            this.touchBackgroundColor = $r('sys.color.ohos_id_color_sub_background_transparent')
          }

        })
        .onClick(() => {
          // 点击设置网络，打开设置网络弹出框
          this.onConfigureNetworkFunction()
        })
      }

    }
    .padding({ left: 12, right: 4 })
    .position({})
    .zIndex(999)
    .width('100%')
    .height('100%')
    .onClick(() => {
      if (this.options.hardwareStatus === HardwareStatusType.ON) {
        // 点击左侧文本，变为正在连接状态'
        this.onReconnectionFunction()
      }
    })
  }

  build() {
    Column() {
      Stack() {
        this.FirstBuilder()
        this.SecondBuilder()
        this.TextBuilder()
      }
      .padding(this.options.marginState === MarginStateType.DEFAULT_MARGIN ? { left: $r('sys.float.ohos_id_card_margin_start'), right: $r('sys.float.ohos_id_card_margin_end') } : { left: $r('sys.float.ohos_id_max_padding_start'), right: $r('sys.float.ohos_id_max_padding_end') })
      .transition(
        // @ts-ignore
        TransitionEffect.OPACITY.animation({
          duration: this.isShowStatus ? 250 : 200
        })
      )
      .visibility(this.isShowStatus ? Visibility.Visible : Visibility.None)
    }
    .width('100%')
    .height(this.isOneColum() ? 48 : 58)
    .position({ y: HEIGHT })
    .zIndex(999)
  }
}
