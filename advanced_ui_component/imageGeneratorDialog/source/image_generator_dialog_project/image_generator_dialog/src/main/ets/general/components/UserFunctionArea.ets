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

@Builder export function UserInteractiveTabBarBuilder(name: string) {
  UserInteractiveAreaTabBar({
    name: name
  })
}

@ComponentV2
export struct FunctionAreaPlaceholder {
  build() {
    Column() {
      Column()
        .width('100%')
        .height('100%')
        .border({width: 0.5})
    }
    .width('100%')
    .height('100%')
    .padding({
      right: 14
    })
  }
}

// style select
@ComponentV2
struct UserInteractiveAreaTabBar {
  @Param name: string = '__NA__'

  build() {
    Column() {
      Column() {
        Image('')
          .width(24)
          .height(24)
      }
      .padding(12)
      .width(48)
      .height(48)
      .margin({bottom: 4})
      .borderRadius(24)
      .backgroundColor('rgba(0,0,0,0.05)')
      Column() {
        Text(this.name)
          .fontFamily("HarmonyHeiTi")
          .fontColor("#000000")
          .fontSize(10)
          .fontWeight(500)
      }
      .height(10)
    }
  }
}