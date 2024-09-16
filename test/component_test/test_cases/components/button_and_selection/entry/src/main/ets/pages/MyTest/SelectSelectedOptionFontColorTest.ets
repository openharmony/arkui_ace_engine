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

export default async function selectSelectedOptionFontColorTest() {
  /*
   * Select组件 SelectedOptionFontColor属性
   * 找到画面id为selectSelectedOptionFontColor1，selectSelectedOptionFontColor2，selectSelectedOptionFontColor3的Select组件
   * 找到画面文本为SelectSelectedOptionFontColor的Button组件
   * 获取selectSelectedOptionFontColor1的SelectedOptionFontColor属性与期待值Color.Green比对
   * 获取selectSelectedOptionFontColor2的SelectedOptionFontColor属性与期待值'#FFFFA500'比对
   * 获取selectSelectedOptionFontColor3的SelectedOptionFontColor属性与期待值'#FF8EFF65'比对
   * 点击button，变更selectSelectedOptionFontColor3的SelectedOptionFontColor属性值为$r('sys.color.ohos_fa_palette1')
   * 获取selectSelectedOptionFontColor3的SelectedOptionFontColor属性与期待值$r('sys.color.ohos_fa_palette1')比对
   */
  defineTest('selectSelectedOptionFontColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectSelectedOptionFontColorTestDemo running')
    let driver: Tester = Tester.create()
    let selectSelectedOptionFontColor1: Component =
      await driver.findComponent(Matcher.create().id('selectSelectedOptionFontColor1').enabled(true))
    let selectSelectedOptionFontColor2: Component =
      await driver.findComponent(Matcher.create().id('selectSelectedOptionFontColor2').enabled(true))
    let selectSelectedOptionFontColor3: Component =
      await driver.findComponent(Matcher.create().id('selectSelectedOptionFontColor3').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('SelectSelectedOptionFontColor').enabled(true))

    let selectedOptionFontColor1: string = await selectSelectedOptionFontColor1.getInspectorInfo()
    assertEqual(JSON.parse(selectedOptionFontColor1).$attrs.selectedOptionFontColor.toLowerCase(), Color.Green)

    let selectedOptionFontColor2: string = await selectSelectedOptionFontColor2.getInspectorInfo()
    assertEqual(JSON.parse(selectedOptionFontColor2).$attrs.selectedOptionFontColor, '#FFFFA500')

    let selectedOptionFontColor3: string = await selectSelectedOptionFontColor3.getInspectorInfo()
    assertEqual(JSON.parse(selectedOptionFontColor3).$attrs.selectedOptionFontColor, '#FF8EFF65')

    await button.tap()
    let selectedOptionFontColor4: string = await selectSelectedOptionFontColor3.getInspectorInfo()
    assertEqual(JSON.parse(selectedOptionFontColor4).$attrs.selectedOptionFontColor, $r('sys.color.ohos_fa_palette1'))
  }, 0)
}