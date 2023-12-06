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
import i18n from '@ohos.i18n';
import curves from '@ohos.curves';

const PUBLIC_TIPS = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAAXNSR0IArs4c6QAAA7ZJREFUSEu1VU1oXFUU/s6dSVK1xUlnbmKsKdZCJRFrmZmX5r20ZSIopf51U4pZ6EKlqIgLsViQIioiiuJC8G/ThWJXNSpR/Fm0tJM7mbmv01JMMVASm4AkM2ltK9XMzHtH32RmMOmbl2y82/ud853znXu/Q/ifDwXln0yl1qy79vd+JtoP4G4AdwBwAJom8FmAvoiubR2h48crzfL4EnAqFZ7/c+EAA68DWA9gkgDbJb4gWDgM3gTgHgBbAcwAOBjT6igBvJzoBoJCYmcXqDIMYBsDn7mMT26z1Tm/CucNo9tFyyEwPwtgRITcoejY2NX/YpcQzCaszYI4DUAw0YMdudEzqxnRnGHuJsZXAKZaFkJW5Nypy/W4BsGlROJWB605ELVDVAZkNjuxmuR1zKxhWoLxMwH56PUrgzQ+XvLuGgTFpPUmgw8RYMa0yi5PPm2aN60p0xmAW2Jr27b4DbaYtB5j8DCYX5J25v0GwR/37mgvtzkXGTjSodULfpXPGjvuEuxc8O4qYd7UlclM+eEKSfN7AANoExtkOn2t2kHBsJ4B86eCKhujudy0X2CtiEveXYhLkfW2fcV38MntD7gQPwIYklp9uUiwyNoutepvpjsDVEya3nt3pVYtTXH79oWKkzPzAL6TWg3VCX77t62fpFZPBw12LmkWieDInOoMwhUM81swNkqt7qsTlAj0TkyPvhoYmDAn4BFo1ROEKybMD5jwlNRqXZ3gLzA+lLZ6ObADo18RqCxzalcgLmG+RYQXpVa31AisXwG2Pc0CO0j2j8Aj0GpvMM46Cua4tNWW2iuqahaXWm0I7sDczQ6487T6YQWJJplwXmq1py7RAQAfQwhDZtO6WXAxaT4PZjdmZz5qijEsg5mzxPych6sSXO3riy64oRmAh6XOPO770eLbtwohzlZ/p8u9sdOZ8364uYR5jAh7Kk64uyt/stCwikLSeg3gwyAMypw6sTz48rZUpBJe8PypLEJuz3LXXPxP/Y8C9DUIb8icOrzEi6peU2IFojuZKLVaJ60XUrOSvOeoZS6Zt9v29SUE1QoWd4ECEHHBD3XqjGfdK55i3LqfBX9e3XYc7pP2yd/rQTcsnNo8jgHYBeL3XMHvdo6NzfrqHR/YSSH3IBgPe1sv7NBge37Uc4XG8V+ZgCgY1pMEfhuMDgB5MI0TYYqBCpgJVE0ar8rAdMQJO6/4FRK49Lm3t3Xu5sgjAngCzD0gdHvbDsBFgCeI6BRBfBPNpX9ppmMgwYrirwLwDyWbkigJz8KuAAAAAElFTkSuQmCC'
const RIGHT_ICON = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAAXNSR0IArs4c6QAAAR1JREFUSEvt1E9Kw1AQBvBvxgpexIUbN7pRiHgDKYFuBaWW0jaXiQmxWXgAE72BxVJPIf5ZiAgKQheC6MuUtxCCCzMPkl2zHr4ffJN5hIY/ajgfS6CyYVVF2Vl8WLCZdrqjx8rEPwMqIB9HdwDW2LDX7vefXBAVkCXJOrG5BfAFMjt+N3jWIirAhl2m0YaIzACag4ynRdSARbI03iSRKYAPLeIEWOQqjbcKkQmAd/ON3c5g8PpfXc6ADcuT0z0w3UDk3O8Nj2oHLtJwn4UngIT+yTCoFciScJuYryF4a7UK7+B49FIb0OiSS7/pp8stqJZcPjTXa1YB+Th6ALDqGm53owLsY7eCn1m7F9xrn4jfORXgGlqeXwKV7TVe0QK81HAZuzhflQAAAABJRU5ErkJggg=='

export enum HardwareStatusType {
  on = 1,
  off = 0,
}

export enum TypeEnum {
  DEFAULT_HIDE = 0,
  NETWORK_NOT_CONNECTED = 1,
  NETWORK_CONNECTED_UNSTABLE = 2,
  UNSTABLE_CONNECT_SERVER = 3,
  CUSTOM_NETWORK_TIPS = 4,
  CUSTOM_TIPS = 5,
}

export interface OptionType {
  HardwareStatus: HardwareStatusType,
  Icon?: ResourceStr,
  // TipContent?: ResourceStr,
  TipContent?: ResourceStr,
  ContentText?: ResourceStr,
  PaddingStatus: boolean
}

interface ErrorTipsInfoType {
  NETWORK_NOT_CONNECTED: ResourceStr;
  NETWORK_CONNECTED_UNSTABLE: ResourceStr;
  UNSTABLE_CONNECT_SERVER: ResourceStr;
  CUSTOM_NETWORK_TIPS1?: ResourceStr;
  CUSTOM_NETWORK_TIPS2?: ResourceStr;
  CUSTOM_TIPS?: ResourceStr;
}

@Component
export struct ExceptionPrompt {
  @Link @Watch('TypeStatusChange') Type: TypeEnum //异常提示类型
  @Link Options: OptionType //异常提示类型
  @State ShowStatus: boolean = false //异常提示显隐
  @State OpacityNum: number = 0.18 //背景第一层的不透明度
  @State HEIGHT: number = 80 //提示框到顶部的距离
  @State BORDER_RADIUS: number = 12 //提示框的圆角值
  @State BG_OPACITY: number = 1
  @State state: boolean = false
  @State text: string = ''
  @State BGCKGROUND_COLOR: Resource = $r('sys.color.ohos_id_color_sub_background_transparent')
  @State SetNetwork: string = '设置网络'
  @State ErrorDefaultObj: ErrorTipsInfoType = {
    NETWORK_NOT_CONNECTED: '网络未连接',
    NETWORK_CONNECTED_UNSTABLE: '网络连接不稳定，请点击重试',
    UNSTABLE_CONNECT_SERVER: '无法连接到服务器，请点击重试',
    CUSTOM_NETWORK_TIPS1: '无法获取',
    CUSTOM_NETWORK_TIPS2: '请点击重试',
    CUSTOM_TIPS: ''
  }
  ReconnectionFunction?: () => void = () => {
    // 点击左侧文本，变为正在连接状态'
  }
  ConfigureNetworkFunction?: () => void = () => {
    // 点击设置网络，打开设置网络弹出框
  }

  SetText() {
    if (this.Type === TypeEnum.NETWORK_NOT_CONNECTED) {
      this.text = `${this.ErrorDefaultObj.NETWORK_NOT_CONNECTED}`
    }
    if (this.Type === TypeEnum.NETWORK_CONNECTED_UNSTABLE) {
      this.text = `${this.ErrorDefaultObj.NETWORK_CONNECTED_UNSTABLE}`
    }
    if (this.Type === TypeEnum.UNSTABLE_CONNECT_SERVER) {
      this.text = `${this.ErrorDefaultObj.UNSTABLE_CONNECT_SERVER}`
    }
    if (this.Type === TypeEnum.CUSTOM_NETWORK_TIPS) {
      this.text = `${this.ErrorDefaultObj.CUSTOM_NETWORK_TIPS1}${this.Options.ContentText || ''}，${this.ErrorDefaultObj.CUSTOM_NETWORK_TIPS2}`
    }
    if (this.Type === TypeEnum.CUSTOM_TIPS) {
      this.text = `${this.Options.TipContent}` || `${this.ErrorDefaultObj.CUSTOM_TIPS}`
    }
  }
  // 监听Type数据变化
  TypeStatusChange(_propName: string): void {
    if (this.Type !== TypeEnum.DEFAULT_HIDE) {
      if (this.state && this.Type !== TypeEnum.NETWORK_NOT_CONNECTED && this.Type !== TypeEnum.NETWORK_CONNECTED_UNSTABLE) {
        setTimeout(() => {
          this.state = false
        }, 200)
      }
      if (this.Type === TypeEnum.NETWORK_NOT_CONNECTED || this.Type === TypeEnum.NETWORK_CONNECTED_UNSTABLE) {
        if (!this.ShowStatus) {
          this.state = true
        } else {
          setTimeout(() => {
            this.state = true
          }, 250)
        }
      }
      if (this.ShowStatus) {
        this.ShowStatus = false
        setTimeout(() => {
          this.SetText()
          this.ShowStatus = true
        }, 250)
      } else {
        this.SetText()
        this.ShowStatus = true
      }
    } else {
      this.ShowStatus = false
      setTimeout(() => {
        this.state = false
      }, 200)
    }
  }

  aboutToAppear() {
    const language = i18n.System.getSystemLanguage();
    if (language.indexOf('zh') != -1) {
      // 中文
    } else if (language.indexOf('en') != -1) {
      // 英文
    }
    if (this.Type !== TypeEnum.DEFAULT_HIDE) {
      this.ShowStatus = true
      this.SetText()
    }
    if (this.Type === TypeEnum.NETWORK_NOT_CONNECTED || this.Type === TypeEnum.NETWORK_CONNECTED_UNSTABLE) {
      this.state = true

    }
  }

  isOneColum() {
    return (this.Type === TypeEnum.UNSTABLE_CONNECT_SERVER || this.Type === TypeEnum.CUSTOM_NETWORK_TIPS) || this.text.length < 10
  }

  @Builder FirstBuilder() {
    Column() {
    }
    .height('100%')
    .width('100%')
    .borderRadius(this.BORDER_RADIUS)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
  }

  @Builder SecondBuilder() {
    Column() {
    }
    .height('100%')
    .width('100%')
    .borderRadius(this.BORDER_RADIUS)
    .backgroundColor($r('sys.color.ohos_id_color_warning'))
    .opacity(this.OpacityNum)
    .position({})
    .zIndex(999)
  }

  @Builder TextBuilder() {
    Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
      Flex({ alignItems: ItemAlign.Center }) {
        Image(this.Options.Icon || $r('app.media.ic_public_fail') || PUBLIC_TIPS)
          .width("24vp")
          .height('24vp')
          .objectFit(ImageFit.Contain)
          .fillColor($r('sys.color.ohos_id_color_warning'))
        Text(this.text)
          .fontSize($r('sys.float.ohos_id_text_size_body1'))
          .fontColor($r('sys.color.ohos_id_color_warning'))
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .maxLines(2)
          .margin({ left: 16, right: 16 })
      }
      .width('100%')
      .height('100%')
      // 设置网络
      if (this.state) {
        Button({ stateEffect: true, type: ButtonType.Normal }) {
          Row() {
            Text(`${this.SetNetwork}`)
              .fontSize($r('sys.float.ohos_id_text_size_body2'))
              .fontColor($r('sys.color.ohos_id_color_text_secondary'))
              .maxLines(1)
              .padding(0)
              .margin({ right: 4 })
              .textAlign(TextAlign.End)
            Image($r('sys.media.ohos_ic_public_arrow_right') || RIGHT_ICON)
              .width('12vp')
              .height('24vp')
              .fillColor($r('sys.color.ohos_id_color_tertiary'))
          }
        }
        .backgroundColor(this.BGCKGROUND_COLOR)
        .width(this.state ? 120 : 0)
        .height(32)
        .borderRadius($r('sys.float.ohos_id_corner_radius_subtab'))
        .padding({ right: 8, left: 8 })
        .onTouch((event) => {
          if (event.type === TouchType.Down) {
            this.BGCKGROUND_COLOR = $r('sys.color.ohos_id_color_click_effect')
          }
          if (event.type === TouchType.Up) {
            this.BGCKGROUND_COLOR = $r('sys.color.ohos_id_color_sub_background_transparent')
          }
        })
        .onClick(() => {
          // 点击设置网络，打开设置网络弹出框
          this.ConfigureNetworkFunction()
        })
      }

    }
    .padding({ left: 12, right: 4 })
    .position({})
    .zIndex(999)
    .width('100%')
    .height('100%')
    .onClick(() => {
      if (this.Options.HardwareStatus) {
        // 点击左侧文本，变为正在连接状态'
        this.ReconnectionFunction()
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
      .padding(this.Options.PaddingStatus ? {
                                              left: $r('sys.float.ohos_id_card_margin_start'),
                                              right: $r('sys.float.ohos_id_card_margin_end')
                                            } : {
                                                  left: $r('sys.float.ohos_id_max_padding_start'),
                                                  right: $r('sys.float.ohos_id_max_padding_end')
                                                })
      .transition(
        TransitionEffect.OPACITY.animation({
          curve: curves.cubicBezierCurve(0.33, 0, 0.67, 1),
          duration: this.ShowStatus ? 250 : 200
        })
      )
      .visibility(this.ShowStatus ? Visibility.Visible : Visibility.None)
    }
    .width('100%')
    .height(this.isOneColum() ? 48 : 58)
    .position({ y: this.HEIGHT })
    .zIndex(999)
  }
}
