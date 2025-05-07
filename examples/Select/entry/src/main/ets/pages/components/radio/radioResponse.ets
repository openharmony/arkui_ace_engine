/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

@Builder
export function RadioResponseBuilder(name: string, param: Object) {
  RadioResponseExample()
}

@Component
struct RadioResponseExample {
  pathStack: NavPathStack = new NavPathStack()
  @State hitTestBehavior_: HitTestMode = HitTestMode.Default
  @State perhaps: string = ''
  @State result: string = ''
  @State result2: string = ''
  @State buttonText: string = 'HitTestMode.Default'

  build() {
    NavDestination() {
      Column() {
        Text('HitTestMode.None的时候点击展示底部被响应，HitTestMode.Default的时候点击展示自身被响应')
          .fontSize(14)
          .width('100%')
          .height(100)
          .textAlign(TextAlign.Center)
        Row({ space: 10 }) {
          Text(this.result2)
            .fontSize(30)
            .width(100)
            .height(100)
          Text(this.result)
            .fontSize(30)
            .width(100)
            .height(100)
        }

        Button(this.buttonText)
          .width(200)
          .height(100)
          .onClick(() => {
            if (this.hitTestBehavior_ == HitTestMode.Default) {
              this.hitTestBehavior_ = HitTestMode.None
              this.buttonText = 'HitTestMode.None'
            } else {
              this.hitTestBehavior_ = HitTestMode.Default
              this.buttonText = 'HitTestMode.Default'
            }
            this.result = ''
            this.result2 = ''
          })
        Stack() {
          Text('底部onTouch')
            .backgroundColor(Color.Red)
            .width(100)
            .height(100)
            .onTouch(() => {
              this.result = 'Radio底部被响应'
            })

          Text('底部onTouch2')
            .backgroundColor(Color.Yellow)
            .width(100)
            .height(100)
            .onTouch(() => {
              this.result2 = 'Row底部被响应'
            })
            .margin({ bottom: 200 })

          Row() {
            Text('覆盖用Text')
              .width(100)
              .height(100)
              .backgroundColor(Color.Orange)
          }
          .width(100)
          .height(100)
          .margin({ bottom: 200 })
          .hitTestBehavior(this.hitTestBehavior_)
          .onTouch(() => {
            this.result2 = 'Row自身被响应'
          })

          Radio({ group: 'AAA', value: 'bbb' })
            .width(100)
            .height(100)
            .hitTestBehavior(this.hitTestBehavior_)
            .onTouch(() => {
              this.result = 'Radio自身被响应'
            })
        }
        .width('80%')
        .height('80%')
        .backgroundColor(Color.Pink)

      }
      .width('100%')
      .height('100%')
      .backgroundColor(Color.White)
    }
    .title('RadioResponse')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { RadioResponseExample }