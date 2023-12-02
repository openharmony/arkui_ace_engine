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
const PUBLIC_TIPS = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAAXNSR0IArs4c6QAAA7ZJREFUSEu1VU1oXFUU/s6dSVK1xUlnbmKsKdZCJRFrmZmX5r20ZSIopf51U4pZ6EKlqIgLsViQIioiiuJC8G/ThWJXNSpR/Fm0tJM7mbmv01JMMVASm4AkM2ltK9XMzHtH32RmMOmbl2y82/ud853znXu/Q/ifDwXln0yl1qy79vd+JtoP4G4AdwBwAJom8FmAvoiubR2h48crzfL4EnAqFZ7/c+EAA68DWA9gkgDbJb4gWDgM3gTgHgBbAcwAOBjT6igBvJzoBoJCYmcXqDIMYBsDn7mMT26z1Tm/CucNo9tFyyEwPwtgRITcoejY2NX/YpcQzCaszYI4DUAw0YMdudEzqxnRnGHuJsZXAKZaFkJW5Nypy/W4BsGlROJWB605ELVDVAZkNjuxmuR1zKxhWoLxMwH56PUrgzQ+XvLuGgTFpPUmgw8RYMa0yi5PPm2aN60p0xmAW2Jr27b4DbaYtB5j8DCYX5J25v0GwR/37mgvtzkXGTjSodULfpXPGjvuEuxc8O4qYd7UlclM+eEKSfN7AANoExtkOn2t2kHBsJ4B86eCKhujudy0X2CtiEveXYhLkfW2fcV38MntD7gQPwIYklp9uUiwyNoutepvpjsDVEya3nt3pVYtTXH79oWKkzPzAL6TWg3VCX77t62fpFZPBw12LmkWieDInOoMwhUM81swNkqt7qsTlAj0TkyPvhoYmDAn4BFo1ROEKybMD5jwlNRqXZ3gLzA+lLZ6ObADo18RqCxzalcgLmG+RYQXpVa31AisXwG2Pc0CO0j2j8Aj0GpvMM46Cua4tNWW2iuqahaXWm0I7sDczQ6487T6YQWJJplwXmq1py7RAQAfQwhDZtO6WXAxaT4PZjdmZz5qijEsg5mzxPych6sSXO3riy64oRmAh6XOPO770eLbtwohzlZ/p8u9sdOZ8364uYR5jAh7Kk64uyt/stCwikLSeg3gwyAMypw6sTz48rZUpBJe8PypLEJuz3LXXPxP/Y8C9DUIb8icOrzEi6peU2IFojuZKLVaJ60XUrOSvOeoZS6Zt9v29SUE1QoWd4ECEHHBD3XqjGfdK55i3LqfBX9e3XYc7pP2yd/rQTcsnNo8jgHYBeL3XMHvdo6NzfrqHR/YSSH3IBgPe1sv7NBge37Uc4XG8V+ZgCgY1pMEfhuMDgB5MI0TYYqBCpgJVE0ar8rAdMQJO6/4FRK49Lm3t3Xu5sgjAngCzD0gdHvbDsBFgCeI6BRBfBPNpX9ppmMgwYrirwLwDyWbkigJz8KuAAAAAElFTkSuQmCC'
const RIGHT_ICON = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAAXNSR0IArs4c6QAAAR1JREFUSEvt1E9Kw1AQBvBvxgpexIUbN7pRiHgDKYFuBaWW0jaXiQmxWXgAE72BxVJPIf5ZiAgKQheC6MuUtxCCCzMPkl2zHr4ffJN5hIY/ajgfS6CyYVVF2Vl8WLCZdrqjx8rEPwMqIB9HdwDW2LDX7vefXBAVkCXJOrG5BfAFMjt+N3jWIirAhl2m0YaIzACag4ynRdSARbI03iSRKYAPLeIEWOQqjbcKkQmAd/ON3c5g8PpfXc6ADcuT0z0w3UDk3O8Nj2oHLtJwn4UngIT+yTCoFciScJuYryF4a7UK7+B49FIb0OiSS7/pp8stqJZcPjTXa1YB+Th6ALDqGm53owLsY7eCn1m7F9xrn4jfORXgGlqeXwKV7TVe0QK81HAZuzhflQAAAABJRU5ErkJggg=='

const DURATION = 230

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
  TipContent?: ResourceStr,
  ContentText?: ResourceStr,
}

export interface ErrorTipsInfoType {
  NETWORK_NOT_CONNECTED: string;
  NETWORK_CONNECTED_UNSTABLE: string;
  UNSTABLE_CONNECT_SERVER: string;
  CUSTOM_NETWORK_TIPS: string;
  CUSTOM_TIPS: string;
}

@Component
export struct ExceptionPrompt {
  @Link @Watch('TypeStatusChange') Type: TypeEnum //异常提示类型
  @Link Options: OptionType //异常提示类型
  @State ShowStatus: boolean = false //异常提示显隐
  @State @Watch('OpacityStatusChange') ThemeColorStatus: boolean = true //默认浅色背景true  false：深色背景
  @State OpacityNum: number = 0.15 //背景第一层的不透明度
  @State HEIGHT: number = 80 //提示框到顶部的距离
  @State BORDER_RADIUS: number = 12 //提示框的圆角值
  @State DURATION: number = 1500 //animateTo的duration时间值
  @State BG_OPACITY: number = 1
  @State state: boolean = false
  @State text: string = ''
  @State ErrorDefaultObj: ErrorTipsInfoType = {
    NETWORK_NOT_CONNECTED: '网络未连接',
    NETWORK_CONNECTED_UNSTABLE: '网络连接不稳定，请点击重试',
    UNSTABLE_CONNECT_SERVER: '无法连接到服务器，请点击重试',
    CUSTOM_NETWORK_TIPS: '无法获取xxx，请点击重试',
    CUSTOM_TIPS: '自定义提示内容'
  }
  ReconnectionFunction: () => void = () => {
    // 点击左侧文本，变为正在连接状态'
  }
  ConfigureNetworkFunction: () => void = () => {
    // 点击设置网络，打开设置网络弹出框
  }

  OpacityStatusChange(_propName: boolean): void {
    // 监听dark背景的变化触发相关业务
    if (this.ThemeColorStatus) {
      this.OpacityNum = 0.15
    } else {
      this.OpacityNum = 0.2
    }
  }

  SetText() {
    if (this.Type === TypeEnum.NETWORK_NOT_CONNECTED) {
      this.text = this.ErrorDefaultObj.NETWORK_NOT_CONNECTED
    }
    if (this.Type === TypeEnum.NETWORK_CONNECTED_UNSTABLE) {
      this.text = this.ErrorDefaultObj.NETWORK_CONNECTED_UNSTABLE
    }
    if (this.Type === TypeEnum.UNSTABLE_CONNECT_SERVER) {
      this.text = this.ErrorDefaultObj.UNSTABLE_CONNECT_SERVER

    }
    if (this.Type === TypeEnum.CUSTOM_NETWORK_TIPS) {
      this.text = `无法获取${this.Options.ContentText || ''}，请点击重试`

    }
    if (this.Type === TypeEnum.CUSTOM_TIPS) {
      this.text = `${this.Options.TipContent}` || this.ErrorDefaultObj.CUSTOM_TIPS

    }
  }
  // 监听Type数据变化
  TypeStatusChange(_propName: string): void {
    if (this.Type !== TypeEnum.DEFAULT_HIDE) {
      console.log("=========TypeStatusChange=========>", _propName)
      if (this.state && this.Type !== TypeEnum.NETWORK_NOT_CONNECTED && this.Type !== TypeEnum.NETWORK_CONNECTED_UNSTABLE) {
        setTimeout(() => {
          this.state = false
        }, DURATION)
      }
      if (this.Type === TypeEnum.NETWORK_NOT_CONNECTED || this.Type === TypeEnum.NETWORK_CONNECTED_UNSTABLE) {
        if (!this.ShowStatus) {
          this.state = true
        } else {
          setTimeout(() => {
            this.state = true
          }, DURATION)
        }
      }
      if (this.ShowStatus) {
        this.ShowStatus = false
        setTimeout(() => {
          this.SetText()
          this.ShowStatus = true
        }, DURATION)
      } else {
        this.SetText()
        this.ShowStatus = true
      }
    } else {
      this.ShowStatus = false
    }
  }

  aboutToAppear() {
    if (this.Type !== TypeEnum.DEFAULT_HIDE) {
      this.ShowStatus = true
      this.SetText()
    }
    if (this.Type === TypeEnum.NETWORK_NOT_CONNECTED || this.Type === TypeEnum.NETWORK_CONNECTED_UNSTABLE) {
      this.state = true

    }
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
      if (TypeEnum.NETWORK_NOT_CONNECTED || TypeEnum.NETWORK_CONNECTED_UNSTABLE) {
        Flex({ alignItems: ItemAlign.Center, justifyContent: FlexAlign.End }) {
          Text('设置网络')
            .fontSize($r('sys.float.ohos_id_text_size_body2'))
            .fontColor($r('sys.color.ohos_id_color_text_secondary'))
            .width(58)
            .maxLines(1)
            .padding(0)
            .margin({ right: 4 })
          Image($r('sys.media.ohos_ic_public_arrow_right')||RIGHT_ICON)
            .width('12vp')
            .height('24vp')
            .fillColor($r('sys.color.ohos_id_color_tertiary'))
        }
        .width(this.state ? 105 : 0)
        .height('100%')
        .onClick(() => {
          // 点击设置网络，打开设置网络弹出框
          this.ConfigureNetworkFunction()
        })
      }
    }
    .padding({ left: 12, right: 12 })
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
      Row() {
        this.FirstBuilder()
        this.SecondBuilder()
        this.TextBuilder()
      }
      .padding({
        left: $r('sys.float.ohos_id_max_padding_start'),
        right: $r('sys.float.ohos_id_max_padding_end'),
      })
      .position({})
      .zIndex(999)
      .opacity(this.ShowStatus ? 1 : 0)
      .animation({ duration: DURATION })
    }
    .width('100%')
    .height((this.Type === TypeEnum.UNSTABLE_CONNECT_SERVER || this.Type === TypeEnum.CUSTOM_NETWORK_TIPS) || this.text.length < 10 ? 48 : 58)
    .position({ y: this.HEIGHT })
    .zIndex(999)
    .opacity(0.9)
  }
}
