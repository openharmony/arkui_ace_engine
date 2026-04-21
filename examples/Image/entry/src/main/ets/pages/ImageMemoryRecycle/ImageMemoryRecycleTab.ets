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
 * @File: ImageMemoryRecycleTab.ets
 * @Description: Tab switching background recovery test.
 * This demonstrates image memory recycling in Tab component scenarios.
 * The test verifies that images in inactive tabs are properly recycled
 * and restored when switching tabs or returning from background.
 */

class TabImageItem {
  public id: string
  public index: number

  constructor(index: number) {
    this.id = `tab_image_${index}`
    this.index = index
  }
}

@Entry
@Component
struct ImageMemoryRecycleTab {
  @State recycleEnabled: boolean = false
  @State tabImages1: Array<TabImageItem> = []
  @State tabImages2: Array<TabImageItem> = []

  aboutToAppear() {
    this.recycleEnabled = true
    const uiContext = this.getUIContext()
    if (uiContext) {
      uiContext.recycleInvisibleImageMemory(true)
    }
    // 初始化Tab图片数据
    this.tabImages1 = Array.from({ length: 4 }, (_, i) => new TabImageItem(i))
    this.tabImages2 = Array.from({ length: 4 }, (_, i) => new TabImageItem(i))
  }

  build() {
    Column() {
      Text('Tab切换退后台恢复测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 10 })
      Text('验证Tab场景中，退后台后图片能否正常恢复显示')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 15 })

      Row() {
        Text('内存回收: ')
          .fontSize(16)
        Toggle({ type: ToggleType.Switch, isOn: this.recycleEnabled })
          .onChange((isOn: boolean) => {
            const uiContext = this.getUIContext()
            if (uiContext) {
              uiContext.recycleInvisibleImageMemory(isOn)
            }
          })
      }
      .width('100%')
      .padding(12)
      .backgroundColor('#f0f0f0')
      .borderRadius(8)

      Tabs() {
        TabContent() {
          Column() {
            ForEach(this.tabImages1, (item: TabImageItem) => {
              Image($r(`app.media.test${item.index % 3 + 1}`))
                .width(120)
                .height(120)
                .margin(8)
            }, (item: TabImageItem) => item.id)
          }
        }
        .tabBar('Tab1')

        TabContent() {
          Column() {
            ForEach(this.tabImages2, (item: TabImageItem) => {
              Image($r(`app.media.test${item.index % 3 + 1}`))
                .width(120)
                .height(120)
                .margin(8)
            }, (item: TabImageItem) => item.id)
          }
        }
        .tabBar('Tab2')
      }
      .layoutWeight(1)
      .margin({ top: 20 })

      Text('说明: 只有上划退后台才会触发回收')
        .fontSize(12)
        .fontColor('#999999')
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
