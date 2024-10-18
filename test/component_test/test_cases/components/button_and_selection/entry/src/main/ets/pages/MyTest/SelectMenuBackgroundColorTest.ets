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

export default async function selectMenuBackgroundColorTest() {
  /*
   * Select组件 MenuBackgroundColor属性
   * 找到画面id为selectMenuBackgroundColor1，selectMenuBackgroundColor2，selectMenuBackgroundColor3的Select组件
   * 找到画面文本为SelectMenuBackgroundColor的Button组件
   * 获取menuBackgroundColor1的MenuBackgroundColor属性与期待值Color.Red比对
   * 获取menuBackgroundColor2的MenuBackgroundColor属性与期待值'#FFA52A2A'比对
   * 获取menuBackgroundColor3的MenuBackgroundColor属性与期待值'#FF8EFF65'比对
   * 点击button，变更menuBackgroundColor3的MenuBackgroundColor属性值为$r('sys.color.ohos_fa_palette1')
   * 获取menuBackgroundColor3的MenuBackgroundColor属性与期待值$r('sys.color.ohos_fa_palette1')比对
   */
  defineTest('selectMenuBackgroundColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectMenuBackgroundColorTestDemo running')
    let driver: Tester = Tester.create()
    let selectMenuBackgroundColor1: Component =
      await driver.findComponent(Matcher.create().id('selectMenuBackgroundColor1').enabled(true))
    let selectMenuBackgroundColor2: Component =
      await driver.findComponent(Matcher.create().id('selectMenuBackgroundColor2').enabled(true))
    let selectMenuBackgroundColor3: Component =
      await driver.findComponent(Matcher.create().id('selectMenuBackgroundColor3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SelectMenuBackgroundColor').enabled(true))

    let menuBackgroundColor1: string = await selectMenuBackgroundColor1.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundColor1).$attrs.menuBackgroundColor.toLowerCase(), Color.Red)

    let menuBackgroundColor2: string = await selectMenuBackgroundColor2.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundColor2).$attrs.menuBackgroundColor, '#FFA52A2A')

    let menuBackgroundColor3: string = await selectMenuBackgroundColor3.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundColor3).$attrs.menuBackgroundColor, '#FF8EFF65')

    await button.tap()
    let menuBackgroundColor4: string = await selectMenuBackgroundColor3.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundColor4).$attrs.menuBackgroundColor, $r('sys.color.ohos_fa_palette1'))
  }, 0)
}