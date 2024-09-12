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

export default async function selectOptionWidthTest() {
  /*
   * Select组件 OptionWidth属性
   * 找到画面id为selectOptionWidth1,selectOptionWidth2,selectOptionWidth3,selectOptionWidth4,selectOptionWidth5的Select组件
   * 找到画面文本为SelectOptionWidth的Button组件
   * 获取selectOptionWidth1的OptionWidth属性与期待值'100.000000'比对
   * 获取selectOptionWidth2的OptionWidth属性与期待值'300.000000'比对
   * 获取selectOptionWidth3的OptionWidth属性与期待值'300.000000'比对
   * 获取selectOptionWidth4的OptionWidth属性与期待值'150.000000'比对
   * 获取selectOptionWidth5的OptionWidth属性与期待值OptionWidthMode.FIT_CONTENT比对
   * 点击button，变更selectOptionWidth4的OptionWidth属性值为$r('app.string.option_num')，selectOptionWidth5的OptionWidth属性值为OptionWidthMode.FIT_TRIGGER
   * 获取selectOptionWidth4的OptionWidth属性与期待值$r('app.string.option_num')比对，selectOptionWidth5的OptionWidth属性与期待值OptionWidthMode.FIT_TRIGGER比对
   */
  defineTest('selectOptionWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectOptionWidthTestDemo running')
    let driver: Tester = Tester.create()
    let selectOptionWidth1: Component =
      await driver.findComponent(Matcher.create().id('selectOptionWidth1').enabled(true))
    let selectOptionWidth2: Component =
      await driver.findComponent(Matcher.create().id('selectOptionWidth2').enabled(true))
    let selectOptionWidth3: Component =
      await driver.findComponent(Matcher.create().id('selectOptionWidth3').enabled(true))
    let selectOptionWidth4: Component =
      await driver.findComponent(Matcher.create().id('selectOptionWidth4').enabled(true))
    let selectOptionWidth5: Component =
      await driver.findComponent(Matcher.create().id('selectOptionWidth5').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SelectOptionWidth').enabled(true))

    let optionWidth1: string = await selectOptionWidth1.getInspectorInfo()
    assertEqual(JSON.parse(optionWidth1).$attrs.optionWidth, '100.000000')

    let optionWidth2: string = await selectOptionWidth2.getInspectorInfo()
    assertEqual(JSON.parse(optionWidth2).$attrs.optionWidth, '300.000000')

    let optionWidth3: string = await selectOptionWidth3.getInspectorInfo()
    assertEqual(JSON.parse(optionWidth3).$attrs.optionWidth, '300.000000')

    let optionWidth4: string = await selectOptionWidth4.getInspectorInfo()
    assertEqual(JSON.parse(optionWidth4).$attrs.optionWidth, '150.000000')

    let optionWidth5: string = await selectOptionWidth5.getInspectorInfo()
    assertEqual(JSON.parse(optionWidth5).$attrs.optionWidth, OptionWidthMode.FIT_CONTENT)

    await button.tap()
    let optionWidth6: string = await selectOptionWidth4.getInspectorInfo()
    assertEqual(JSON.parse(optionWidth6).$attrs.optionWidth, $r('app.string.option_num'))
    let optionWidth7: string = await selectOptionWidth5.getInspectorInfo()
    assertEqual(JSON.parse(optionWidth7).$attrs.optionWidth, OptionWidthMode.FIT_TRIGGER)
  }, 0)
}