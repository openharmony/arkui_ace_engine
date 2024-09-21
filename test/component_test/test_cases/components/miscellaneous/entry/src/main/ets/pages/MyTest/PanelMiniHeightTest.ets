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

export default async function panelMiniHeightTest() {
  /*
   * Panel组件 MiniHeight属性
   * 找到画面id为panelMiniHeight的Panel组件
   * 找到画面文本为PanelMiniHeight的Button组件
   * 获取panel的MiniHeight属性与期待值'60.00vp'比对
   * 点击button，变更panel的MiniHeight属性值为'10'
   * 获取panel的MiniHeight属性与期待值'10.00vp'比对
   */
  defineTest('panelMiniHeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('panelMiniHeightTestDemo running')

    let driver: Tester = Tester.create()
    let panel: Component = await driver.findComponent(Matcher.create().id('panelMiniHeight').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PanelMiniHeight').enabled(true))

    let miniHeight1: string = await panel.getInspectorInfo()
    assertEqual(JSON.parse(miniHeight1).$attrs.miniHeight, '60.00vp')

    await button.tap()
    let miniHeight2: string = await panel.getInspectorInfo()
    assertEqual(JSON.parse(miniHeight2).$attrs.miniHeight, '10.00vp')
  }, 0)
}