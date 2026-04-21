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

// page1.ets
import { router } from '@kit.ArkUI';

@Entry
@Component
struct PageTransitionExample2 {
  @State scale2: number = 1
  @State opacity2: number = 1

  build() {
    Column() {
      Column() {
        Button("返回")
          .onClick(() => {
            router.back()
          })
      }
      .width('100%')
      .height('10%')
      .backgroundColor(Color.Orange)
      .justifyContent(FlexAlign.Center)
      Column() {
        Image($r("app.media.bbb")).width('100%').height('100%') // 图片存放在media文件夹下
      }
      .width('100%')
      .height('100%')
      .scale({ x: this.scale2 })
      .opacity(this.opacity2)
      .onClick(() => {
        router.back()
      })
    }
  }

  pageTransition() {
    PageTransitionEnter({ duration: 1200, curve: Curve.Linear })
      .onEnter((type: RouteType, progress: number) => {
        if(type==RouteType.Push || type == RouteType.Pop)
          this.scale2 = progress
        this.opacity2 = progress

      })
    PageTransitionExit({ duration: 1200, curve: Curve.Ease })
      .onExit((type: RouteType, progress: number) => {
        if (type == RouteType.Pop) {
          this.scale2 = 1 - progress
          this.opacity2 = 1 - progress
        }
      })
  }
}