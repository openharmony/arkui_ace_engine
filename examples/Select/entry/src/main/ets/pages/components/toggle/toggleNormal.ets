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
export function ToggleBuilder(name: string, param: Object) {
  ToggleExample()
}

@Entry
@Component
struct ToggleExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Text('点击开关效果正常，不截断不错乱')
          .margin({ top: 50, bottom: 50 })
        Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
          Toggle({ type: ToggleType.Switch, isOn: false })
            .selectedColor('#007DFF')
            .switchPointColor('#FFFFFF')
            .width('150px')
            .height('300px')
            .switchStyle({
              pointRadius: undefined,
              trackBorderRadius: 5,
              pointColor: Color.Black,
              unselectedColor: Color.Pink
            })
            .onChange((isOn: boolean) => {
              console.info('Component status:' + isOn)
            })
        }

        Text('type: Switch switchUnselectedColor: ')
          .fontSize(12)
          .fontColor(0xcccccc)
          .width('90%')
        Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
          Toggle({ type: ToggleType.Switch, isOn: false })
            .selectedColor('#007DFF')
            .switchPointColor('#FFFFFF')
            .onChange((isOn: boolean) => {
              console.info('Component status:' + isOn)
            })
        }
      }
      .width('100%')
      .padding(24)
    }
    .title('ToggleNormal')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { ToggleExample };