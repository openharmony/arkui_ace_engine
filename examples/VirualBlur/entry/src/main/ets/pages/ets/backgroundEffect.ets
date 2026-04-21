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

@Entry
@Component
struct BackgroundEffectEts {
  private imageSize: number = 100;

  @State disable: boolean | undefined = true;
  @State sys: SystemAdaptiveOptions | undefined = undefined;
  @State index: number = 3;
  build() {
    Column({ space: 5 }) {
      // backgroundEffect 可以自定义设置 模糊半径，亮度，饱和度等参数
      Stack() {
        Image($r('app.media.startIcon'))
          .width(this.imageSize)
          .height(this.imageSize)
        Column()
          .width(this.imageSize)
          .height(this.imageSize)
          .backgroundEffect({ radius: 20 }, {disableSystemAdaptation: this.disable})
        Column()
          .width(this.imageSize)
          .height(this.imageSize)
          .backgroundEffect({ radius: 20 }, this.sys)
      }
      Column() {
        Button('change disableSystemAdaptation')
          .onClick(() => {
            this.disable = !this.disable
          })
        Button('change disableSystemAdaptation undefined')
          .onClick(() => {
            this.disable = undefined
          })

        Text('backgroundEffect设置在Column上面')
        Text(`第一个column的disableSystemAdaptation：${this.disable}`)
        if (this.index === 1) {
          Text(`第二个column的disableSystemAdaptation：true`)
        } else if (this.index === 2) {
          Text(`第二个column的disableSystemAdaptation：false`)
        } else {
          Text(`第二个column的disableSystemAdaptation：sys undefined`)
        }
        Button('change disableSystemAdaptation sys true')
          .onClick(() => {
            this.sys = {disableSystemAdaptation: true}
            this.index = 1;
          })
        Button('change disableSystemAdaptation sys false')
          .onClick(() => {
            this.sys = {disableSystemAdaptation: false}
            this.index = 2;
          })
        Button('change disableSystemAdaptation sys undefined')
          .onClick(() => {
            this.sys = undefined
            this.index = 3;
          })
      }
    }
    .width('100%')
    .padding({ top: 5 })
  }
}

