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

interface toggleItem {
  id: string
  label: string
  isOn: boolean
  disabled: boolean
  color?: string
}

@Builder
export function ToggleUnionBuilder(name: string, param: Object) {
  toggleUnion()
}

@Component
export struct toggleUnion {
  // 基本开关状态
  @State basicToggle: boolean = false
  // 动态开关列表
  @State toggleItems: Array<toggleItem> = [
    {
      id: 'wifi',
      label: 'Wi-Fi',
      isOn: true,
      disabled: false,
      color: '#3498db'
    },
    {
      id: 'bluetooth',
      label: '蓝牙',
      isOn: false,
      disabled: false,
      color: '#9b59b6'
    },
    {
      id: 'airplane',
      label: '飞行模式',
      isOn: false,
      disabled: true
    },
    {
      id: 'hotspot',
      label: '热点',
      isOn: false,
      disabled: false,
      color: '#e74c3c'
    },
  ]
  // 联动控制
  @State masterToggle: boolean = false
  @State slaveToggles: boolean[] = [false, false, false]
  // 自定义样式开关状态
  @State customToggle: boolean = false
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 20 }) {
          // 1. 基本开关
          Row() {
            Toggle({ type: ToggleType.Switch, isOn: this.basicToggle })
              .onChange((isOn: boolean) => {
                this.basicToggle = isOn
                console.log('基本开关状态:', isOn)
              })
            Text('基本开关').fontSize(16).margin({ left: 10 })
          }.width('100%').justifyContent(FlexAlign.Start)

          Divider().strokeWidth(1).margin(10)

          // 2. 主从联动开关
          Text('联动控制').fontSize(18).width('100%').textAlign(TextAlign.Start)
          Row() {
            Toggle({ type: ToggleType.Switch, isOn: this.masterToggle })
              .onChange((isOn: boolean) => {
                this.masterToggle = isOn
                this.slaveToggles = this.slaveToggles.map(() => isOn)
                console.log('主开关状态变化:', isOn)
              })
            Text('主控制开关').fontSize(16).margin({ left: 10 })
          }.width('100%').justifyContent(FlexAlign.Start)

          Column() {
            ForEach(this.slaveToggles, (isOn: false, index) => {
              Row() {
                Toggle({ type: ToggleType.Switch, isOn: isOn })
                  .onChange((newIsOn: boolean) => {
                    let newSlaveToggles = [...this.slaveToggles]
                    newSlaveToggles[index] = newIsOn
                    this.slaveToggles = newSlaveToggles

                    // 如果所有从开关状态一致，更新主开关状态
                    const allSame = newSlaveToggles.every(val => val === newSlaveToggles[0])
                    if (allSame) {
                      this.masterToggle = newSlaveToggles[0]
                    } else {
                      this.masterToggle = false
                    }
                    console.log(`从开关 ${index + 1} 状态变化:`, newIsOn)
                  })
                Text(`从属开关 ${index + 1}`).fontSize(16).margin({ left: 10 })
              }
              .width('100%')
              .justifyContent(FlexAlign.Start)
              .margin({ bottom: 10 })
            })
          }.width('100%')

          Divider().strokeWidth(1).margin(10)

          // 3. 自定义样式开关
          Text('自定义样式').fontSize(18).width('100%').textAlign(TextAlign.Start)
          Row() {
            Toggle({ type: ToggleType.Switch, isOn: this.customToggle })
              .width(60)
              .height(30)
              .selectedColor('#FF6347')
              .switchPointColor('#FFFFFF')
              .onChange((isOn: boolean) => {
                this.customToggle = isOn
                console.log('自定义开关状态变化:', isOn)
              })
            Text('番茄主题开关').fontSize(16).margin({ left: 10 })
          }.width('100%').justifyContent(FlexAlign.Start)

          // 4. 按钮式开关
          Text('按钮式开关').fontSize(18).width('100%').textAlign(TextAlign.Start)
          Row() {
            Toggle({ type: ToggleType.Button, isOn: false })
              .width(80)
              .height(30)
              .selectedColor('#2ECC71')
            Text('按钮式开关').fontSize(16).margin({ left: 10 })
          }.width('100%').justifyContent(FlexAlign.Start)
        }
        .padding(20)
      }
    }
    .title('toggle场景测试合集')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

