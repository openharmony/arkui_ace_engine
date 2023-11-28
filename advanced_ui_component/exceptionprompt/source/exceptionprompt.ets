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
const Start_DURATION = 250 //动画时长
const End_DURATION = 200 //动画时长
@Component
export struct ExceptionPrompt {
  @Prop @Watch('TypeStatusChange') Type: number //异常提示类型
  @Prop HardwareStatus?: boolean = true //网络硬件打开状态
  @Prop Icon?: string = '' //异常提示图标
  @Prop TipContent?: string = '' //提示文字内容
  @Prop ContentText?: string = 'xxx' //无法获取的文字内容
  @Prop @Watch('OpacityStatusChange') ThemeColorStatus?: boolean = true //默认浅色背景true  false：深色背景
  @State ShowStatus: boolean = false //异常提示显隐
  @State OpacityNum: number = 0.15 //背景第一层的不透明度
  @State HEIGHT: number = 80 //提示框到顶部的距离
  @State BORDER_RADIUS: number = 12 //提示框的圆角值
  // @State DURATION: number = 1500 //animateTo的duration时间值
  @State BG_OPACITY: number = 1
  @State state: boolean = false
  // @State icons?:string=$r('app.media.ic_public_arrow_right1')
  @State ErrorDefaultObj: Object = {
    1: '网络未连接',
    2: '网络连接不稳定，请点击重试',
    3: '无法连接到服务器，请点击重试',
    4: '无法获取xxx，请点击重试'
  }
  @State text: string = ''
  // 点击左侧文本触发相关回调
  ReconnectionFunction: () => void = () => {
  }
  // 点击右侧设置网络触发相关回调
  ConfigureNetworkFunction: () => void = () => {
  }
  // 监听dark背景的变化触发相关业务
  OpacityStatusChange(_propName: boolean): void {

    if (this.ThemeColorStatus) {
      this.OpacityNum = 0.15
    } else {
      this.OpacityNum = 0.2
    }
  }
  //监听type值的变化触发相关业务
  TypeStatusChange(_propName: string): void {

    if (this.Type) {
      if (this.state && this.Type !== 1 && this.Type !== 2) {
        setTimeout(() => {
          this.state = false
        }, End_DURATION)
      }
      if (this.Type === 1 || this.Type === 2) {
        if (!this.ShowStatus) {
          this.state = true
        } else {
          setTimeout(() => {
            this.state = true
          }, Start_DURATION)
        }
      }
      if (this.ShowStatus) {
        this.ShowStatus = false
        setTimeout(() => {
          this.text = this.ErrorDefaultObj[this.Type]
          if (this.Type === 4) {
            this.text = `无法获取${this.ContentText}，请点击重试`
          }
          this.ShowStatus = true
        }, End_DURATION)
      } else {
        this.text = this.ErrorDefaultObj[this.Type]
        if (this.Type === 4) {
          this.text = `无法获取${this.ContentText}，请点击重试`
        }
        this.ShowStatus = true
      }
    } else {
      this.ShowStatus = false
    }
  }

  build() {
    Column() {
      Row() {
        // 背景第一层盒子
        Column() {
        }
        .height('100%')
        .width('100%')
        .borderRadius(this.BORDER_RADIUS)
        .backgroundColor($r('sys.color.ohos_id_color_background'))
        // 背景第二层
        Column() {
        }
        .height('100%')
        .width('100%')
        .borderRadius(this.BORDER_RADIUS)
        .backgroundColor($r('sys.color.ohos_id_color_warning'))
        .opacity(this.OpacityNum)
        .position({})
        .zIndex(999)
        // 异常提示框内容
        Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
          Flex({ alignItems: ItemAlign.Center }) {
            Image(this.Icon || PUBLIC_TIPS)
              .width('24vp')
              .height('24vp')
              .fillColor($r('sys.color.ohos_id_color_warning'))
            Text(this.TipContent || this.text)
              .fontSize($r('sys.float.ohos_id_text_size_body1'))
              .fontColor($r('sys.color.ohos_id_color_warning'))
              .margin({ left: 16 })

          }
          .width('100%')
          .height('100%')
          // 设置网络
          if (!this.TipContent) {
            Flex({ alignItems: ItemAlign.Center, justifyContent: FlexAlign.End }) {
              Text('设置网络')
                .fontSize($r('sys.float.ohos_id_text_size_body2'))
                .fontColor($r('sys.color.ohos_id_color_text_secondary'))
              Image(RIGHT_ICON)
                .margin({ left: 4 })
                .width(15)
                .height(24)
                .fillColor($r('sys.color.ohos_id_color_tertiary'))
            }
            .margin({ left: 16 })
            .width(this.state ? 130 : 0)
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
          if (this.HardwareStatus) {
            // 点击左侧文本，变为正在连接状态'
            this.ReconnectionFunction()
          }
        })
      }
      .padding({
        left: $r('sys.float.ohos_id_max_padding_start'),
        right: $r('sys.float.ohos_id_max_padding_end'),
      })
      .position({})
      .zIndex(999)
      .opacity(this.ShowStatus ? 1 : 0)
      .animation({ duration: 250 })
    }
    .width('100%')
    .height(48)
    .position({ y: this.HEIGHT })
    .zIndex(999)

  }
}
