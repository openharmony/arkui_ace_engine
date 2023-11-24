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
const PUBLIC_TIPS = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAYAAABXAvmHAAAFFklEQVRoQ9VZTVLbMBSW3CFhGU4A7KDdhBMUdoUuiE8AnKDkBMAJgBOUniDpoqE7coOmizbsGk5QL4FOrb5nS46kSJYluzBoJpOFbel97+d7P6LkhS/6wuUnjQEYvNvYJpR2o4isspR0YecOKGcNfvg/g9+EEJowkt6RlIzjr7fjJpRXC0AmdES2KaH7IEzXU6CEUnKV/mWf64AJAoCCU0pPQMvbnkLbXp8wEh3Fox9gJb/lBWDQ63aiPw8njJFD7hryablGU3JHGJuQ6FVCWkuzeDhJAPAauhehLHMrsNgBdy9NWnrF0vQMLIIuV2lVBpBpPaIDTfAE/HrICL0UwlY6FV4a7G72IF7egjKOtW8SlrK4qltVAgCHHYN2TxThGRkzGvVDzC4LjFalj4/nhDC0arEAWD++nl64FOIEMNjbOAWTo/BiJbD5EWw+dG3u83yw96ZLSYoWXhPfMcLO4tHtadk+pQC45kE7xZpw81b2US8QmTUebuCbgtEABAT37ZVtHysArhHcDAMPFgRYq9XHoPQRKuTd4d4mWqJXWCJlO7aYMAJA1oCA/TYXnkxYq73zFMILoYe7mzcSTWNgb5nYyQhguPf6oxRUM/gYNeDlNtz9kC47PCC9YiYP7gdUooiJYW80jXWLLgDgdImuky0u/NjHFQwWxH3WvZWQBzaCyGUh0ZbOegsANNMZUbvA6ErIDmckDmEuzRsmYIUt+XwFACYX4HsMIFxQeEU7ITzPCaDQXB0A3JV+2zxCBSBxPgC52P8y7bu0bXrOXeiX/Mxk/qp7q1agV73RzyPxrQIA6AsPXaujMfxW1xqPJe8YEEJq+yXgRisLADSzKy9V1ZT8HiiDKRZotVfq0LBNuYUF5Kxbx32E0HAg+i1PgpCVRlNn2VKmqM/vN89F4SeXGMWmsp+50ncViwAADGJREswAwHqV72zvaARTsKMEYJ6+QylPcSE1ky7Qny8YzcWL/WQA8wAOSDq6QEo+gdK7dz3d8RVaft8WyGYANQMOD9YSUFBCLAFQxJQMoGANKNxqMQYeLAcdVrIyd4daQmY2QQpmCxhqDt9D5UaoCVbTkmNBCnMAUtCFFHA6QABwCJ0cVLVYhLk7K5eCnEGs8GzFfrTsUJn2mqBlWSGyS84TmdL71vdZzho3oP6EtdtxnSyclSeWOm0OIB+biD6gdinhcgnf53JilPOUvZhrIBf4CmnNwmpjkwBLrguLKgCapD7usx+wHgKNXVaZ8dgBKKMdJaeo/YDqRkFtYO6vaiuYMVHJZKGUDPLeGKuErDDUy5zFllIpwsKC2TBPCqZSxSsMJcliU1+hkXb5dlMW0OexJitaxirKYEkJGpfw4rk0T0Wzn/nGQEHD85K82lgl8+Hc74pGGuxfu5qsClw6H7O4mM5ZBwz20aIW0E8FwjStLutPyoe7Uj3DNfhfR4zc8rLm4V6kfDri7FPV3JDBCL4OKqVLw3jdJTzu5wSg1yFCCNw8XWqf1a5xLNdWjV1wFKyixwR/kAFh0SffCR5SbUTTA8N9GwQsg5sf+52AbMlKFihAZGZmUB6o10H8+QzADFPGvsM98EzM89Gvyf19By79OpCO4bKPwR6Wa9mAaysvACoQ9TrIhyYX3kXBGTQ9AZffQQCkZAXDYNSm0SIuTHjTM4bsekmWlyehsVQLgCwhdmC5e0SrkHrBVbIZK/5wobAz/IGbzfB2vo7QwTHgUulzPG/MAs8hPJ75D1DwJF6CXORhAAAAAElFTkSuQmCC'

const DURATION = 800

@Component
export struct ExceptionPrompt {
  @Prop @Watch('TypeStatusChange') type: number //异常提示类型
  @Prop HardwareStatus: boolean //网络硬件打开状态
  @Prop Icon: string //异常提示图标
  @Prop TipContent: string //提示文字内容
  @Prop ContentText: string //无法获取的文字内容
  @State ShowStatus: boolean = false //异常提示显隐
  @Prop @Watch('OpacityStatusChange') ThemeColorStatus: boolean //默认浅色背景true  false：深色背景
  @State OpacityNum: number = 0.15 //背景第一层的不透明度
  @State HEIGHT: number = 80 //提示框到顶部的距离
  @State BORDER_RADIUS: number = 12 //提示框的圆角值
  @State DURATION: number = 1500 //animateTo的duration时间值
  @State BG_OPACITY: number = 1
  @State state: boolean = false
  @State ErrorDefaultObj: Object = {
    1: '网络未连接',
    2: '网络连接不稳定，请点击重试',
    3: '无法连接到服务器，请点击重试',
    4: '无法获取xxx，请点击重试'
  }
  @State text: string = ''
  ReconnectionFunction: () => void = () => {
  }
  ConfigureNetworkFunction: () => void = () => {
  }

  OpacityStatusChange(_propName: boolean): void {
    // 监听dark背景的变化触发相关业务
    if (this.ThemeColorStatus) {
      this.OpacityNum = 0.15
    } else {
      this.OpacityNum = 0.2
    }
  }

  TypeStatusChange(_propName: string): void {
    if (this.state && this.type !== 1 && this.type !== 2) {
      setTimeout(() => {
        this.state = false
      }, DURATION)
    }
    if (this.type === 1 || this.type === 2) {
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
        this.text = this.ErrorDefaultObj[this.type]
        if (this.type === 4) {
          this.text = `无法获取${this.ContentText}，请点击重试`
        }
        this.ShowStatus = true
      }, DURATION)
    } else {
      this.text = this.ErrorDefaultObj[this.type]
      if (this.type === 4) {
        this.text = `无法获取${this.ContentText}，请点击重试`
      }
      this.ShowStatus = true
    }
  }

  aboutToAppear() {
    console.log('123:', this.ContentText)
    if (this.ThemeColorStatus) {
      this.OpacityNum = 0.15
    } else {
      this.OpacityNum = 0.2
    }
  }

  build() {
    Column() {
      Row() {
        Column() {
        }
        .height('100%')
        .width('100%')
        .borderRadius(this.BORDER_RADIUS)
        .backgroundColor($r('sys.color.ohos_id_color_background'))

        Column() {
        }
        .height('100%')
        .width('100%')
        .borderRadius(this.BORDER_RADIUS)
        .backgroundColor($r('sys.color.ohos_id_color_warning'))
        .opacity(this.OpacityNum)
        .position({})
        .zIndex(999)

        Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
          Flex({ alignItems: ItemAlign.Center }) {
            Image(this.Icon || $r('app.media.ic_public_fail') || PUBLIC_TIPS)
              .width("24vp")
              .height('24vp')
              .margin({
                right: 16
              })
              .objectFit(ImageFit.Contain)
              .fillColor($r('sys.color.ohos_id_color_warning'))
            Text(this.TipContent || this.text)
              .fontSize($r('sys.float.ohos_id_text_size_body1'))
              .fontColor($r('sys.color.ohos_id_color_warning'))
          }
          .width('100%')
          .height('100%')
          // 设置网络
          if (!this.TipContent) {
            Flex({ alignItems: ItemAlign.Center, justifyContent: FlexAlign.End }) {
              Text('设置网络')
                .fontSize($r('sys.float.ohos_id_text_size_body2'))
                .fontColor($r('sys.color.ohos_id_color_text_secondary'))
              Image($r('app.media.ic_public_arrow_right'))
                .margin({ left: 4 })
                .width('15dp')
                .height('24dp')
                .fillColor($r('sys.color.ohos_id_color_tertiary'))
            }
            .margin({ left: 16 })
            .width(this.state ? '45%' : 0)
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
      .animation({ duration: DURATION })
    }
    .width('100%')
    .height(48)
    .position({ y: this.HEIGHT })
    .zIndex(999)

  }
}
