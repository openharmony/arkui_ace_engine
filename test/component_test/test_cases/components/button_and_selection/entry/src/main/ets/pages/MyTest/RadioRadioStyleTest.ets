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

export default async function radioRadioStyleTest() {
  /*
   * Radio组件 RadioStyle属性
   * 找到画面id为radioRadioStyle1，radioRadioStyle2，radioRadioStyle3，...，radioRadioStyle10，radioRadioStyle11的Radio组件
   * 找到画面文本为RadioStyle的Button组件
   * 获取radioRadioStyle1的RadioStyle属性与期待值{ checkedBackgroundColor: Color.Gray }比对
   * 获取radioRadioStyle2的RadioStyle属性与期待值{ uncheckedBorderColor: Color.Green }比对
   * 获取radioRadioStyle3的RadioStyle属性与期待值{ indicatorColor: Color.Pink }比对
   * 获取radioRadioStyle4的RadioStyle属性与期待值{ checkedBackgroundColor: '#FFA52A2A' }比对
   * 获取radioRadioStyle5的RadioStyle属性与期待值{ uncheckedBorderColor: '#FFFFA500' }比对
   * 获取radioRadioStyle6的RadioStyle属性与期待值{ indicatorColor: '#FF8EFF65' }比对
   * 获取radioRadioStyle7的RadioStyle属性与期待值{ checkedBackgroundColor: $r('sys.color.ohos_fa_palette1') }比对
   * 获取radioRadioStyle8的RadioStyle属性与期待值{ uncheckedBorderColor: $r('sys.color.ohos_id_shadow_floating_md_dark') }比对
   * 获取radioRadioStyle9的RadioStyle属性与期待值{ indicatorColor: $r('sys.color.ohos_id_shadow_floating_md') }比对
   * 获取radioRadioStyle10的RadioStyle属性与期待值{ checkedBackgroundColor: '#FF0A6E46' }比对
   * 获取radioRadioStyle11的RadioStyle属性与期待值{ uncheckedBorderColor: '#FF0A0A19' }比对
   * 点击button，变更radioRadioStyle6的RadioStyle属性值为{ indicatorColor: $r('sys.color.ohos_fa_palette1') }，变更radioRadioStyle11的RadioStyle属性值为{ uncheckedBorderColor: $r('sys.color.ohos_id_color_badge_red_dark') }
   * 获取radioRadioStyle6的RadioStyle属性与期待值{ indicatorColor: $r('sys.color.ohos_fa_palette1') }比对，radioRadioStyle11的RadioStyle属性值为{ uncheckedBorderColor: $r('sys.color.ohos_id_color_badge_red_dark') }
   */
  defineTest('radioRadioStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('radioRadioStyleTestDemo running')
    let driver: Tester = Tester.create()
    let radioRadioStyle1: Component = await driver.findComponent(Matcher.create().id('radioRadioStyle1').enabled(true))
    let radioRadioStyle2: Component = await driver.findComponent(Matcher.create().id('radioRadioStyle2').enabled(true))
    let radioRadioStyle3: Component = await driver.findComponent(Matcher.create().id('radioRadioStyle3').enabled(true))
    let radioRadioStyle4: Component = await driver.findComponent(Matcher.create().id('radioRadioStyle4').enabled(true))
    let radioRadioStyle5: Component = await driver.findComponent(Matcher.create().id('radioRadioStyle5').enabled(true))
    let radioRadioStyle6: Component = await driver.findComponent(Matcher.create().id('radioRadioStyle6').enabled(true))
    let radioRadioStyle7: Component = await driver.findComponent(Matcher.create().id('radioRadioStyle7').enabled(true))
    let radioRadioStyle8: Component = await driver.findComponent(Matcher.create().id('radioRadioStyle8').enabled(true))
    let radioRadioStyle9: Component = await driver.findComponent(Matcher.create().id('radioRadioStyle9').enabled(true))
    let radioRadioStyle10: Component =
      await driver.findComponent(Matcher.create().id('radioRadioStyle10').enabled(true))
    let radioRadioStyle11: Component =
      await driver.findComponent(Matcher.create().id('radioRadioStyle11').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('RadioStyle').enabled(true))

    let radioStyle1: string = await radioRadioStyle1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(radioStyle1).$attrs.radioStyle).checkedBackgroundColor.toLowerCase(), Color.Gray)

    let radioStyle2: string = await radioRadioStyle2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(radioStyle2).$attrs.radioStyle).uncheckedBorderColor.toLowerCase(), Color.Green)

    let radioStyle3: string = await radioRadioStyle3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(radioStyle3).$attrs.radioStyle).indicatorColor.toLowerCase(), Color.Pink)

    let radioStyle4: string = await radioRadioStyle4.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(radioStyle4).$attrs.radioStyle).checkedBackgroundColor, '#FFA52A2A')

    let radioStyle5: string = await radioRadioStyle5.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(radioStyle5).$attrs.radioStyle).uncheckedBorderColor, '#FFFFA500')

    let radioStyle6: string = await radioRadioStyle6.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(radioStyle6).$attrs.radioStyle).indicatorColor, '#FF8EFF65')

    let radioStyle7: string = await radioRadioStyle7.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(radioStyle7).$attrs.radioStyle).checkedBackgroundColor,
      $r('sys.color.ohos_fa_palette1'))

    let radioStyle8: string = await radioRadioStyle8.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(radioStyle8).$attrs.radioStyle).uncheckedBorderColor,
      $r('sys.color.ohos_id_shadow_floating_md_dark'))

    let radioStyle9: string = await radioRadioStyle9.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(radioStyle9).$attrs.radioStyle).indicatorColor,
      $r('sys.color.ohos_id_shadow_floating_md'))

    let radioStyle10: string = await radioRadioStyle10.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(radioStyle10).$attrs.radioStyle).checkedBackgroundColor, '#FF0A6E46')

    let radioStyle11: string = await radioRadioStyle11.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(radioStyle11).$attrs.radioStyle).uncheckedBorderColor, '#FF0A0A19')

    await button.tap()
    let radioStyle12: string = await radioRadioStyle6.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(radioStyle12).$attrs.radioStyle).indicatorColor, $r('sys.color.ohos_fa_palette1'))

    let radioStyle13: string = await radioRadioStyle11.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(radioStyle13).$attrs.radioStyle).uncheckedBorderColor,
      $r('sys.color.ohos_id_color_badge_red_dark'))
  }, 0)
}