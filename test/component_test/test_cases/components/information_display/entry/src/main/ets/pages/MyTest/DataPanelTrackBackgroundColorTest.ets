/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function dataPanelTrackBackgroundColorTest() {
  /*
   * DataPanel组件 trackBackgroundColor属性
   * 找到画面id为dataPanelTrackBackgroundColor1，dataPanelTrackBackgroundColor2的DataPanel组件
   * 找到画面文本为DataPanelTrackBackgroundColor1,DataPanelTrackBackgroundColor2的Button组件
   * 获取dataPanel1的trackBackgroundColor属性与期待值Color.Yellow比对
   * 获取dataPanel2的trackBackgroundColor属性与期待值$r('sys.color.ohos_fa_palette1')比对
   * 点击button1，变更dataPanel1的trackBackgroundColor属性值为'#FFFF00FF'
   * 获取dataPanel1的trackBackgroundColor属性与期待值'#FFFF00FF'比对
   * 点击button2，变更dataPanel1的trackBackgroundColor属性值为'#FFFF00AA'
   * 获取dataPanel1的trackBackgroundColor属性与期待值'#FFFF00AA'比对
   */
  defineTest('dataPanelTrackBackgroundColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('dataPanelTrackBackgroundColorTestDemo running')
    let driver: Tester = Tester.create()
    let dataPanel1: Component = await driver.findComponent(Matcher.create()
      .id('dataPanelTrackBackgroundColor1')
      .enabled(true))
    let dataPanel2: Component = await driver.findComponent(Matcher.create()
      .id('dataPanelTrackBackgroundColor2')
      .enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create()
      .text('DataPanelTrackBackgroundColor1')
      .enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create()
      .text('DataPanelTrackBackgroundColor2')
      .enabled(true))

    let trackBackgroundColor1: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(trackBackgroundColor1).$attrs.trackBackgroundColor.toLowerCase(), Color.Yellow)
    let trackBackgroundColor2: string = await dataPanel2.getInspectorInfo()
    assertEqual(JSON.parse(trackBackgroundColor2)
      .$attrs
      .trackBackgroundColor, $r('sys.color.ohos_fa_palette1'))

    await button1.tap()
    let trackBackgroundColor3: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(trackBackgroundColor3).$attrs.trackBackgroundColor, '#FFFF00FF')
    await button2.tap()
    let trackBackgroundColor4: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(trackBackgroundColor4).$attrs.trackBackgroundColor, '#FFFF00AA')
  }, 0)
}