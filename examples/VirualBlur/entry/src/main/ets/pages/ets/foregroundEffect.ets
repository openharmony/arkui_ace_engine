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
struct ForegroundEffectEts {
  private imageSize: number = 100;

  @State disable: boolean | undefined = true;
  @State sys: SystemAdaptiveOptions | undefined = undefined;
  build() {
    Column({ space: 5 }) {
      // foregroundEffect
      Stack() {
        Image($r('app.media.startIcon'))
          .width(this.imageSize)
          .height(this.imageSize)
          .foregroundEffect({ radius: 20 }, {disableSystemAdaptation: this.disable})
        Column()
          .width(this.imageSize)
          .height(this.imageSize)
          .foregroundEffect({ radius: 20 }, this.sys)
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
        Text('foregroundEffect设置在Image上面')
        Text(`disableSystemAdaptation：${this.disable}`)
        Button('change disableSystemAdaptation sys true')
          .onClick(() => {
            this.sys = {disableSystemAdaptation: true}
          })
        Button('change disableSystemAdaptation sys false')
          .onClick(() => {
            this.sys = {disableSystemAdaptation: false}
          })
        Button('change disableSystemAdaptation sys undefined')
          .onClick(() => {
            this.sys = undefined
          })
      }
    }
    .width('100%')
    .padding({ top: 5 })
  }
}

