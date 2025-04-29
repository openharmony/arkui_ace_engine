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
import { assertEqual, assertFalse } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function foregroundBlurStyleTest() {
  /*
   * Rating组件 ForegroundBlurStyle属性
   * 找到画面id为 imageForegroundBlurStyle1 的 image 组件
   * 找到画面文本为 ButtonForegroundBlurStyle 的Button组件
   * 获取 imageForegroundBlurStyle1 的 ForegroundBlurStyle 属性与期待值 BlurStyle.Thin 比对
   * 获取 imageForegroundBlurStyle1 的 colorMode 属性与期待值 ThemeColorMode.SYSTEM 比对
   * 获取 imageForegroundBlurStyle1 的 adaptiveColor 属性与期待值 AdaptiveColor.DEFAULT 比对
   * 获取 imageForegroundBlurStyle1 的 grayscale 属性与期待值 [12, 103] 比对
   * 点击 button1 改变 imageForegroundBlurStyle1 的 foregroundBlurStyle 属性与期待值 BlurStyle.Regular 比对
   * 点击 button1 改变 imageForegroundBlurStyle1 的 foregroundBlurStyle 属性与期待值 BlurStyle.Thick 比对
   * 点击 button1 改变 imageForegroundBlurStyle1 的 foregroundBlurStyle 属性与期待值 BlurStyle.BACKGROUND_THIN 比对
   * 点击 button1 改变 imageForegroundBlurStyle1 的 foregroundBlurStyle 属性与期待值 BlurStyle.BACKGROUND_REGULAR 比对
   * 点击 button1 改变 imageForegroundBlurStyle1 的 foregroundBlurStyle 属性与期待值 BlurStyle.BACKGROUND_THICK 比对
   * 点击 button1 改变 imageForegroundBlurStyle1 的 foregroundBlurStyle 属性与期待值 BlurStyle.BACKGROUND_ULTRA_THICK 比对
   * 点击 button1 改变 imageForegroundBlurStyle1 的 foregroundBlurStyle 属性与期待值 BlurStyle.NONE 比对
   * 点击 button1 改变 imageForegroundBlurStyle1 的 foregroundBlurStyle 属性与期待值 BlurStyle.COMPONENT_ULTRA_THIN 比对
   * 点击 button1 改变 imageForegroundBlurStyle1 的 foregroundBlurStyle 属性与期待值 BlurStyle.COMPONENT_THIN 比对
   * 点击 button1 改变 imageForegroundBlurStyle1 的 foregroundBlurStyle 属性与期待值 BlurStyle.COMPONENT_REGULAR 比对
   * 点击 button1 改变 imageForegroundBlurStyle1 的 foregroundBlurStyle 属性与期待值 BlurStyle.COMPONENT_THICK 比对
   * 点击 button1 改变 imageForegroundBlurStyle1 的 foregroundBlurStyle 属性与期待值 BlurStyle.COMPONENT_ULTRA_THICK 比对
   */
  defineTest('foregroundBlurStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('foregroundBlurStyleTestDemo running')
    let driver: Tester = Tester.create()
    let imageForegroundBlurStyle1: Component =
      await driver.findComponent(Matcher.create().id('imageForegroundBlurStyle1').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('ButtonForegroundBlurStyle').enabled(true))
    let foregroundBlurStyle1: string = await imageForegroundBlurStyle1.getInspectorInfo()
    assertFalse(JSON.parse(foregroundBlurStyle1).$attrs.foregroundBlurStyle == undefined)

    assertEqual(JSON.parse(foregroundBlurStyle1).$attrs.foregroundBlurStyle, BlurStyle.Thin)
    assertEqual(JSON.parse(foregroundBlurStyle1)
      .$attrs
      .foregroundBlurStyle
      .colorMode, ThemeColorMode.SYSTEM)
    assertEqual(JSON.parse(foregroundBlurStyle1)
      .$attrs
      .foregroundBlurStyle
      .adaptiveColor, AdaptiveColor.DEFAULT)
    assertEqual(JSON.parse(foregroundBlurStyle1)
      .$attrs
      .foregroundBlurStyle
      .blurOptions
      .grayscale, [12, 103]
    )
    await button1.tap()
    let foregroundBlurStyle2: string = await imageForegroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundBlurStyle2).$attrs.foregroundBlurStyle, BlurStyle.Regular)

    await button1.tap()
    let foregroundBlurStyle3: string = await imageForegroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundBlurStyle3).$attrs.foregroundBlurStyle, BlurStyle.Thick)

    await button1.tap()
    let foregroundBlurStyle4: string = await imageForegroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundBlurStyle4).$attrs.foregroundBlurStyle, BlurStyle.BACKGROUND_THIN)

    await button1.tap()
    let foregroundBlurStyle5: string = await imageForegroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundBlurStyle5).$attrs.foregroundBlurStyle, BlurStyle.BACKGROUND_REGULAR)

    await button1.tap()
    let foregroundBlurStyle6: string = await imageForegroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundBlurStyle6).$attrs.foregroundBlurStyle, BlurStyle.BACKGROUND_THICK)

    await button1.tap()
    let foregroundBlurStyle7: string = await imageForegroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundBlurStyle7).$attrs.foregroundBlurStyle, BlurStyle.BACKGROUND_ULTRA_THICK)

    await button1.tap()
    let foregroundBlurStyle8: string = await imageForegroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundBlurStyle8).$attrs.foregroundBlurStyle, BlurStyle.NONE)

    await button1.tap()
    let foregroundBlurStyle9: string = await imageForegroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundBlurStyle9).$attrs.foregroundBlurStyle, BlurStyle.COMPONENT_ULTRA_THIN)

    await button1.tap()
    let foregroundBlurStyle10: string = await imageForegroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundBlurStyle10).$attrs.foregroundBlurStyle, BlurStyle.COMPONENT_THIN)

    await button1.tap()
    let foregroundBlurStyle11: string = await imageForegroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundBlurStyle11).$attrs.foregroundBlurStyle, BlurStyle.COMPONENT_REGULAR)

    await button1.tap()
    let foregroundBlurStyle12: string = await imageForegroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundBlurStyle12).$attrs.foregroundBlurStyle, BlurStyle.COMPONENT_THICK)

    await button1.tap()
    let foregroundBlurStyle13: string = await imageForegroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundBlurStyle13).$attrs.foregroundBlurStyle, BlurStyle.COMPONENT_ULTRA_THICK)
  }, 0)
}