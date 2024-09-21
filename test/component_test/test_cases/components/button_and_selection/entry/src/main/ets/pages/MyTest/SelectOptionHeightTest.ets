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

export default async function selectOptionHeightTest() {
  /*
  * Select组件 OptionHeight属性
  * 找到画面id为selectOptionHeight1,selectOptionHeight2,selectOptionHeight3,selectOptionHeight4的Select组件
  * 找到画面文本为SelectOptionHeight的Button组件
  * 获取selectOptionHeight1的OptionHeight属性与期待值'100.000000'比对
  * 获取selectOptionHeight2的OptionHeight属性与期待值'300.000000'比对
  * 获取selectOptionHeight3的OptionHeight属性与期待值'300.000000'比对
  * 获取selectOptionHeight4的OptionHeight属性与期待值'150.000000'比对
  * 点击button，变更selectOptionHeight4的OptionHeight属性值为$r('app.string.option_height')
  * 获取selectOptionHeight4的OptionHeight属性与期待值$r('app.string.option_height')比对
  */
  defineTest('selectOptionHeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectOptionHeightTestDemo running')
    let driver: Tester = Tester.create()
    let selectOptionHeight1: Component =
      await driver.findComponent(Matcher.create().id('selectOptionHeight1').enabled(true))
    let selectOptionHeight2: Component =
      await driver.findComponent(Matcher.create().id('selectOptionHeight2').enabled(true))
    let selectOptionHeight3: Component =
      await driver.findComponent(Matcher.create().id('selectOptionHeight3').enabled(true))
    let selectOptionHeight4: Component =
      await driver.findComponent(Matcher.create().id('selectOptionHeight4').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SelectOptionHeight').enabled(true))

    let optionHeight1: string = await selectOptionHeight1.getInspectorInfo()
    assertEqual(JSON.parse(optionHeight1).$attrs.optionHeight, '100.000000')

    let optionHeight2: string = await selectOptionHeight2.getInspectorInfo()
    assertEqual(JSON.parse(optionHeight2).$attrs.optionHeight, '300.000000')

    let optionHeight3: string = await selectOptionHeight3.getInspectorInfo()
    assertEqual(JSON.parse(optionHeight3).$attrs.optionHeight, '300.000000')

    let optionHeight4: string = await selectOptionHeight4.getInspectorInfo()
    assertEqual(JSON.parse(optionHeight4).$attrs.optionHeight, '150.000000')

    await button.tap()
    let optionHeight5: string = await selectOptionHeight4.getInspectorInfo()
    assertEqual(JSON.parse(optionHeight5).$attrs.optionHeight, $r('app.string.option_height'))
  }, 0)
}