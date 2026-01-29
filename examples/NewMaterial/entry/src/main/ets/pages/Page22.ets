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

/**
 * 测试目的：
 * 通过和renderGroup目前互斥的属性，从视觉上直观验证节点剔除能生效
 * 注意：使用visualEffect需要为系统应用!!!
 */
import uiEffect from '@ohos.graphics.uiEffect';
@Entry
@Component
struct Page2 {
  @State message: string = 'Hello World';

  build() {
    Row() {
      Column() {
        Text(this.message)
          .fontSize($r('app.float.page_text_font_size'))
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            this.message = 'Welcome';
          })
        Text('Hello World').fontSize(20)
          .backgroundColor(Color.Red)
          .visualEffect(uiEffect.createEffect().backgroundColorBlender(
            {
              cubicRate: 0.5,
              quadraticRate: 0.5,
              linearRate: 0.5,
              degree: 0.5,
              saturation: 0.5,
              positiveCoefficient: [2.3, 4.5, 2.0],
              negativeCoefficient: [0.5, 2.0, 0.5],
              fraction: 0.5
            }
          ))
        // .excludeFromRenderGroup(this.value1)
        Column() {
          Text('Hello World').fontSize(20)
            .backgroundColor(Color.Red)
            .visualEffect(uiEffect.createEffect().backgroundColorBlender(
              {
                cubicRate: 0.5,
                quadraticRate: 0.5,
                linearRate: 0.5,
                degree: 0.5,
                saturation: 0.5,
                positiveCoefficient: [2.3, 4.5, 2.0],
                negativeCoefficient: [0.5, 2.0, 0.5],
                fraction: 0.5
              }
            ))
        }

        // .excludeFromRenderGroup(this.value1)
      }
      .width('100%')
    }
    .height('100%')
  }
}