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

export default async function selectMenuBackgroundBlurStyleTest() {
  /*
   * Select组件 MenuBackgroundBlurStyle属性
   * 找到画面id为selectMenuBackgroundBlurStyle1，selectMenuBackgroundBlurStyle2，...，selectMenuBackgroundBlurStyle10的Select组件
   * 找到画面文本为SelectMenuBackgroundBlurStyle的Button组件
   * 获取selectMenuBackgroundBlurStyle1的MenuBackgroundBlurStyle属性与期待值BlurStyle.Thin比对
   * 获取selectMenuBackgroundBlurStyle2的MenuBackgroundBlurStyle属性与期待值BlurStyle.Regular比对
   * 获取selectMenuBackgroundBlurStyle3的MenuBackgroundBlurStyle属性与期待值BlurStyle.Thick比对
   * 获取selectMenuBackgroundBlurStyle4的MenuBackgroundBlurStyle属性与期待值BlurStyle.BACKGROUND_THIN比对
   * 获取selectMenuBackgroundBlurStyle5的MenuBackgroundBlurStyle属性与期待值BlurStyle.BACKGROUND_THICK比对
   * 获取selectMenuBackgroundBlurStyle6的MenuBackgroundBlurStyle属性与期待值BlurStyle.BACKGROUND_ULTRA_THICK比对
   * 获取selectMenuBackgroundBlurStyle7的MenuBackgroundBlurStyle属性与期待值BlurStyle.NONE比对
   * 获取selectMenuBackgroundBlurStyle8的MenuBackgroundBlurStyle属性与期待值BlurStyle.COMPONENT_ULTRA_THIN比对
   * 获取selectMenuBackgroundBlurStyle9的MenuBackgroundBlurStyle属性与期待值BlurStyle.COMPONENT_REGULAR比对
   * 获取selectMenuBackgroundBlurStyle10的MenuBackgroundBlurStyle属性与期待值BlurStyle.COMPONENT_THICK比对
   * 点击button，变更selectMenuBackgroundBlurStyle4的MenuBackgroundBlurStyle属性值为BlurStyle.BACKGROUND_REGULAR，
        selectMenuBackgroundBlurStyle8的MenuBackgroundBlurStyle属性值为BlurStyle.COMPONENT_THIN，
        selectMenuBackgroundBlurStyle10的MenuBackgroundBlurStyle属性值为BlurStyle.COMPONENT_ULTRA_THICK
   * 获取selectMenuBackgroundBlurStyle4的MenuBackgroundBlurStyle与期待值BlurStyle.BACKGROUND_REGULAR对比，
        selectMenuBackgroundBlurStyle8的MenuBackgroundBlurStyle与期待值BlurStyle.COMPONENT_THIN对比，
        selectMenuBackgroundBlurStyle10的MenuBackgroundBlurStyle与期待值BlurStyle.COMPONENT_ULTRA_THICK对比
   */
  defineTest('selectMenuBackgroundBlurStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectMenuBackgroundBlurStyleTestDemo running')
    let driver: Tester = Tester.create()
    let selectMenuBackgroundBlurStyle1: Component =
      await driver.findComponent(Matcher.create().id('selectMenuBackgroundBlurStyle1').enabled(true))
    let selectMenuBackgroundBlurStyle2: Component =
      await driver.findComponent(Matcher.create().id('selectMenuBackgroundBlurStyle2').enabled(true))
    let selectMenuBackgroundBlurStyle3: Component =
      await driver.findComponent(Matcher.create().id('selectMenuBackgroundBlurStyle3').enabled(true))
    let selectMenuBackgroundBlurStyle4: Component =
      await driver.findComponent(Matcher.create().id('selectMenuBackgroundBlurStyle4').enabled(true))
    let selectMenuBackgroundBlurStyle5: Component =
      await driver.findComponent(Matcher.create().id('selectMenuBackgroundBlurStyle5').enabled(true))
    let selectMenuBackgroundBlurStyle6: Component =
      await driver.findComponent(Matcher.create().id('selectMenuBackgroundBlurStyle6').enabled(true))
    let selectMenuBackgroundBlurStyle7: Component =
      await driver.findComponent(Matcher.create().id('selectMenuBackgroundBlurStyle7').enabled(true))
    let selectMenuBackgroundBlurStyle8: Component =
      await driver.findComponent(Matcher.create().id('selectMenuBackgroundBlurStyle8').enabled(true))
    let selectMenuBackgroundBlurStyle9: Component =
      await driver.findComponent(Matcher.create().id('selectMenuBackgroundBlurStyle9').enabled(true))
    let selectMenuBackgroundBlurStyle10: Component =
      await driver.findComponent(Matcher.create().id('selectMenuBackgroundBlurStyle10').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('SelectMenuBackgroundBlurStyle').enabled(true))

    let menuBackgroundBlurStyle1: string = await selectMenuBackgroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundBlurStyle1).$attrs.menuBackgroundBlurStyle, 'BlurStyle.Thin')

    let menuBackgroundBlurStyle2: string = await selectMenuBackgroundBlurStyle2.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundBlurStyle2).$attrs.menuBackgroundBlurStyle, 'BlurStyle.Regular')

    let menuBackgroundBlurStyle3: string = await selectMenuBackgroundBlurStyle3.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundBlurStyle3).$attrs.menuBackgroundBlurStyle, 'BlurStyle.Thick')

    let menuBackgroundBlurStyle4: string = await selectMenuBackgroundBlurStyle4.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundBlurStyle4).$attrs.menuBackgroundBlurStyle, 'BlurStyle.BACKGROUND_THIN')

    let menuBackgroundBlurStyle5: string = await selectMenuBackgroundBlurStyle5.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundBlurStyle5).$attrs.menuBackgroundBlurStyle, 'BlurStyle.BACKGROUND_THICK')

    let menuBackgroundBlurStyle6: string = await selectMenuBackgroundBlurStyle6.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundBlurStyle6).$attrs.menuBackgroundBlurStyle, 'BlurStyle.BACKGROUND_ULTRA_THICK')

    let menuBackgroundBlurStyle7: string = await selectMenuBackgroundBlurStyle7.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundBlurStyle7).$attrs.menuBackgroundBlurStyle, 'BlurStyle.NONE')

    let menuBackgroundBlurStyle8: string = await selectMenuBackgroundBlurStyle8.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundBlurStyle8).$attrs.menuBackgroundBlurStyle, 'BlurStyle.COMPONENT_ULTRA_THIN')

    let menuBackgroundBlurStyle9: string = await selectMenuBackgroundBlurStyle9.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundBlurStyle9).$attrs.menuBackgroundBlurStyle, 'BlurStyle.COMPONENT_REGULAR')

    let menuBackgroundBlurStyle10: string = await selectMenuBackgroundBlurStyle10.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundBlurStyle10).$attrs.menuBackgroundBlurStyle, 'BlurStyle.COMPONENT_THICK')

    await button.tap()
    let menuBackgroundBlurStyle11: string = await selectMenuBackgroundBlurStyle4.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundBlurStyle11).$attrs.menuBackgroundBlurStyle, 'BlurStyle.BACKGROUND_REGULAR')

    let menuBackgroundBlurStyle12: string = await selectMenuBackgroundBlurStyle8.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundBlurStyle12).$attrs.menuBackgroundBlurStyle, 'BlurStyle.COMPONENT_THIN')

    let menuBackgroundBlurStyle13: string = await selectMenuBackgroundBlurStyle10.getInspectorInfo()
    assertEqual(JSON.parse(menuBackgroundBlurStyle13).$attrs.menuBackgroundBlurStyle, 'BlurStyle.COMPONENT_ULTRA_THICK')
  }, 0)
}