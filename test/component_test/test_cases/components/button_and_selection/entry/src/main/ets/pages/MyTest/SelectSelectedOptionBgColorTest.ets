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

export default async function selectSelectedOptionBgColorTest() {
  /*
   * Select组件 SelectedOptionBgColor属性
   * 找到画面id为selectSelectedOptionBgColor1，selectSelectedOptionBgColor2，selectSelectedOptionBgColor3的Select组件
   * 找到画面文本为SelectSelectedOptionBgColor的Button组件
   * 获取selectSelectedOptionBgColor1的SelectedOptionBgColor属性与期待值Color.Green比对
   * 获取selectSelectedOptionBgColor2的SelectedOptionBgColor属性与期待值'#FFFFA500'比对
   * 获取selectSelectedOptionBgColor3的SelectedOptionBgColor属性与期待值'#FF8EFF65'比对
   * 点击button，变更selectSelectedOptionBgColor3的SelectedOptionBgColor属性值为$r('sys.color.ohos_fa_palette1')
   * 获取selectSelectedOptionBgColor3的SelectedOptionBgColor属性与期待值$r('sys.color.ohos_fa_palette1')比对
   */
  defineTest('selectSelectedOptionBgColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectSelectedOptionBgColorTestDemo running')
    let driver: Tester = Tester.create()
    let selectSelectedOptionBgColor1: Component =
      await driver.findComponent(Matcher.create().id('selectSelectedOptionBgColor1').enabled(true))
    let selectSelectedOptionBgColor2: Component =
      await driver.findComponent(Matcher.create().id('selectSelectedOptionBgColor2').enabled(true))
    let selectSelectedOptionBgColor3: Component =
      await driver.findComponent(Matcher.create().id('selectSelectedOptionBgColor3').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('SelectSelectedOptionBgColor').enabled(true))

    let selectedOptionBgColor1: string = await selectSelectedOptionBgColor1.getInspectorInfo()
    assertEqual(JSON.parse(selectedOptionBgColor1).$attrs.selectedOptionBgColor.toLowerCase(), Color.Green)

    let selectedOptionBgColor2: string = await selectSelectedOptionBgColor2.getInspectorInfo()
    assertEqual(JSON.parse(selectedOptionBgColor2).$attrs.selectedOptionBgColor, '#FFFFA500')

    let selectedOptionBgColor3: string = await selectSelectedOptionBgColor3.getInspectorInfo()
    assertEqual(JSON.parse(selectedOptionBgColor3).$attrs.selectedOptionBgColor, '#FF8EFF65')

    await button.tap()
    let selectedOptionBgColor4: string = await selectSelectedOptionBgColor3.getInspectorInfo()
    assertEqual(JSON.parse(selectedOptionBgColor4).$attrs.selectedOptionBgColor, $r('sys.color.ohos_fa_palette1'))
  }, 0)
}