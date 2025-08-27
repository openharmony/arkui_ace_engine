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
export function ToggleTypeBuilder(name: string, param: Object) {
  ToggleTypeExample()
}

@Entry
@Component
struct ToggleTypeExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Text('type: Switch')
          .fontSize(12)
          .fontColor(0xcccccc)
          .width('90%')
        Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
          Toggle({ type: ToggleType.Switch, isOn: false })
            .selectedColor('#007DFF')
            .switchPointColor('#FFFFFF')
            .onChange((isOn: boolean) => {
              console.info('Component status:' + isOn);
            })

          Toggle({ type: ToggleType.Switch, isOn: true })
            .selectedColor('#007DFF')
            .switchPointColor('#FFFFFF')
            .onChange((isOn: boolean) => {
              console.info('Component status:' + isOn);
            })
        }

        Text('type: Checkbox')
          .fontSize(12)
          .fontColor(0xcccccc)
          .width('90%')
        Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
          Toggle({ type: ToggleType.Checkbox, isOn: false })
            .size({ width: 20, height: 20 })
            .selectedColor('#007DFF')
            .onChange((isOn: boolean) => {
              console.info('Component status:' + isOn);
            })

          Toggle({ type: ToggleType.Checkbox, isOn: true })
            .size({ width: 20, height: 20 })
            .selectedColor('#007DFF')
            .onChange((isOn: boolean) => {
              console.info('Component status:' + isOn);
            })
        }

        Text('type: Button')
          .fontSize(12)
          .fontColor(0xcccccc)
          .width('90%')
        Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
          Toggle({ type: ToggleType.Button, isOn: false }) {
            Text('status button').fontColor('#182431').fontSize(12)
          }.width(106)
          .selectedColor('rgba(0,125,255,0.20)')
          .onChange((isOn: boolean) => {
            console.info('Component status:' + isOn);
          })

          Toggle({ type: ToggleType.Button, isOn: true }) {
            Text('status button').fontColor('#182431').fontSize(12)
          }.width(106)
          .selectedColor('rgba(0,125,255,0.20)')
          .onChange((isOn: boolean) => {
            console.info('Component status:' + isOn);
          })
        }
      }
      .width('100%')
      .padding(24)
    }
    .title('ToggleType')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}