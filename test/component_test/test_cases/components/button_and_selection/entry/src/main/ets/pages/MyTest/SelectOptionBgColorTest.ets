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

export default async function selectOptionBgColorTest() {
  /*
   * Select组件 OptionBgColor属性
   * 找到画面id为selectOptionBgColor1，selectOptionBgColor2，selectOptionBgColor3的Select组件
   * 找到画面文本为SelectOptionBgColor的Button组件
   * 获取selectOptionBgColor1的OptionBgColor属性与期待值Color.Green比对
   * 获取selectOptionBgColor2的OptionBgColor属性与期待值'#FFA52A2A'比对
   * 获取selectOptionBgColor3的OptionBgColor属性与期待值'#FF8EFF65'比对
   * 点击button，变更selectOptionBgColor3的OptionBgColor属性值为$r('sys.color.ohos_fa_palette1')
   * 获取selectOptionBgColor3的OptionBgColor属性与期待值$r('sys.color.ohos_fa_palette1')比对
   */
  defineTest('selectOptionBgColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectOptionBgColorTestDemo running')
    let driver: Tester = Tester.create()
    let selectOptionBgColor1: Component =
      await driver.findComponent(Matcher.create().id('selectOptionBgColor1').enabled(true))
    let selectOptionBgColor2: Component =
      await driver.findComponent(Matcher.create().id('selectOptionBgColor2').enabled(true))
    let selectOptionBgColor3: Component =
      await driver.findComponent(Matcher.create().id('selectOptionBgColor3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SelectOptionBgColor').enabled(true))

    let optionBgColor1: string = await selectOptionBgColor1.getInspectorInfo()
    assertEqual(JSON.parse(optionBgColor1).$attrs.optionBgColor.toLowerCase(), Color.Green)

    let optionBgColor2: string = await selectOptionBgColor2.getInspectorInfo()
    assertEqual(JSON.parse(optionBgColor2).$attrs.optionBgColor, '#FFA52A2A')

    let optionBgColor3: string = await selectOptionBgColor3.getInspectorInfo()
    assertEqual(JSON.parse(optionBgColor3).$attrs.optionBgColor, '#FF8EFF65')

    await button.tap()
    let optionBgColor4: string = await selectOptionBgColor3.getInspectorInfo()
    assertEqual(JSON.parse(optionBgColor4).$attrs.optionBgColor, $r('sys.color.ohos_fa_palette1'))
  }, 0)
}