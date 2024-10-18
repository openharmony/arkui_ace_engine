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

export default async function toggleSwitchPointColorTest() {
  /*
   * Toggle组件 SwitchPointColor属性
   * 找到画面id为toggleSwitchPointColor1，toggleSwitchPointColor2， toggleSwitchPointColor3的Button组件
   * 找到画面文本为ToggleSwitchPointColor的Button组件
   * 获取toggleSwitchPointColor1的SwitchPointColor属性与期待值Color.Black比对
   * 获取toggleSwitchPointColor2的SwitchPointColor属性与期待值'#FFA52A2A'比对
   * 获取toggleSwitchPointColor3的SwitchPointColor属性与期待值'#FF8EFF65'比对
   * 点击button，变更toggleSwitchPointColor3的SwitchPointColor属性值为$r('sys.color.ohos_fa_palette1')
   * 获取toggleSwitchPointColor3的SwitchPointColor属性与期待值$r('sys.color.ohos_fa_palette1')比对
   */
  defineTest('toggleSwitchPointColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('toggleSwitchPointColorTestDemo running')
    let driver: Tester = Tester.create()
    let toggleSwitchPointColor1: Component =
      await driver.findComponent(Matcher.create().id('toggleSwitchPointColor1').enabled(true))
    let toggleSwitchPointColor2: Component =
      await driver.findComponent(Matcher.create().id('toggleSwitchPointColor2').enabled(true))
    let toggleSwitchPointColor3: Component =
      await driver.findComponent(Matcher.create().id('toggleSwitchPointColor3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ToggleSwitchPointColor').enabled(true))

    let switchPointColor1: string = await toggleSwitchPointColor1.getInspectorInfo()
    assertEqual(JSON.parse(switchPointColor1).$attrs.switchPointColor.toLowerCase(), Color.Black)

    let switchPointColor2: string = await toggleSwitchPointColor2.getInspectorInfo()
    assertEqual(JSON.parse(switchPointColor2).$attrs.switchPointColor, '#FFA52A2A')

    let switchPointColor3: string = await toggleSwitchPointColor3.getInspectorInfo()
    assertEqual(JSON.parse(switchPointColor3).$attrs.switchPointColor, '#FF8EFF65')

    await button.tap()
    let switchPointColor4: string = await toggleSwitchPointColor3.getInspectorInfo()
    assertEqual(JSON.parse(switchPointColor4).$attrs.switchPointColor, $r('sys.color.ohos_fa_palette1'))
  }, 0)
}