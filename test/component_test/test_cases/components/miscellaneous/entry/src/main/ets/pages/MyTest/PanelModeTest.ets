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

export default async function panelModeTest() {
  /*
   * Panel组件 Mode属性
   * 找到画面id为panelMode的Panel组件
   * 找到画面文本为PanelMode1,PanelMode2的Button组件
   * 获取panel的Mode属性与期待值PanelMode.Full比对
   * 点击button1，变更panel的Mode属性值为PanelMode.Mini
   * 获取panel的Mode属性与期待值PanelMode.Mini比对
   * 点击button2，变更panel的Mode属性值为PanelMode.Half
   * 获取panel的Mode属性与期待值PanelMode.Half比对
   */
  defineTest('panelModeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('panelModeTestDemo running')
    let driver: Tester = Tester.create()
    let panel: Component = await driver.findComponent(Matcher.create().id('panelMode').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('PanelMode1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('PanelMode2').enabled(true))

    let mode1: string = await panel.getInspectorInfo()
    assertEqual(JSON.parse(mode1).$attrs.mode, 'PanelMode.Full')

    await button1.tap()
    let mode2: string = await panel.getInspectorInfo()
    assertEqual(JSON.parse(mode2).$attrs.mode, 'PanelMode.Mini')

    await button2.tap()
    let mode3: string = await panel.getInspectorInfo()
    assertEqual(JSON.parse(mode3).$attrs.mode, 'PanelMode.Half')
  }, 0)
}