/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
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

export default async function selectOptionFontColorTest() {
  /*
  * Select组件 OptionFontColor属性
  * 找到画面id为selectOptionFontColor1,selectOptionFontColor2,selectOptionFontColor3的Select组件
  * 找到画面文本为SelectOptionFontColor的Button组件
  * 获取selectOptionFontColor1的OptionFontColor属性与期待值Color.Blue比对
  * 获取selectOptionFontColor2的OptionFontColor属性与期待值'#FFFFF000'比对
  * 获取selectOptionFontColor3的OptionFontColor属性与期待值'#FF8EFF65'比对
  * 点击button，变更selectOptionFontColor3的OptionFontColor属性值为$r('sys.color.ohos_fa_palette1')
  * 获取selectOptionFontColor3的OptionFontColor属性与期待值$r('sys.color.ohos_fa_palette1')比对
  */
  defineTest('selectOptionFontColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectOptionFontColorTestDemo running')
    let driver: Tester = Tester.create()
    let selectOptionFontColor1: Component =
      await driver.findComponent(Matcher.create().id('selectOptionFontColor1').enabled(true))
    let selectOptionFontColor2: Component =
      await driver.findComponent(Matcher.create().id('selectOptionFontColor2').enabled(true))
    let selectOptionFontColor3: Component =
      await driver.findComponent(Matcher.create().id('selectOptionFontColor3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SelectOptionFontColor').enabled(true))

    let optionFontColor1: string = await selectOptionFontColor1.getInspectorInfo()
    assertEqual(JSON.parse(optionFontColor1).$attrs.optionFontColor.toLowerCase(), Color.Blue)

    let optionFontColor2: string = await selectOptionFontColor2.getInspectorInfo()
    assertEqual(JSON.parse(optionFontColor2).$attrs.optionFontColor, '#FFFFF000')

    let optionFontColor3: string = await selectOptionFontColor3.getInspectorInfo()
    assertEqual(JSON.parse(optionFontColor3).$attrs.optionFontColor, '#FF8EFF65')

    await button.tap()
    let optionFontColor4: string = await selectOptionFontColor3.getInspectorInfo()
    assertEqual(JSON.parse(optionFontColor4).$attrs.optionFontColor, $r('sys.color.ohos_fa_palette1'))
  }, 0)
}