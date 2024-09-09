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

import {
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function textPickerDialogBackgroundBlurStyleTest() {
  /*
   * TextPickerDialog组件 BackgroundBlurStyle对象
   * 找到画面文本为TextPickerDialogBackgroundBlurStyle的Button组件
   * 找到画面文本为ClickToggleBackgroundBlueStyle的Button2组件
   * 点击Button2改变BackgroundBlurStyle对象属性为BlurStyle.Thin
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundBlurStyle1的BackgroundBlurStyle对象属性与期待值BlurStyle.Thin比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变BackgroundBlurStyle对象属性为BlurStyle.Regular
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundBlurStyle2的BackgroundBlurStyle对象属性与期待值BlurStyle.Regular比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变BackgroundBlurStyle对象属性为BlurStyle.Thick
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundBlurStyle3的BackgroundBlurStyle对象属性与期待值BlurStyle.Thick比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变BackgroundBlurStyle对象属性为BlurStyle.BACKGROUND_THIN
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundBlurStyle4的BackgroundBlurStyle对象属性与期待值BlurStyle.BACKGROUND_THIN比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变BackgroundBlurStyle对象属性为BlurStyle.BACKGROUND_REGULAR
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundBlurStyle5的BackgroundBlurStyle对象属性与期待值BlurStyle.BACKGROUND_REGULAR比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变BackgroundBlurStyle对象属性为BlurStyle.BACKGROUND_THICK
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundBlurStyle6的BackgroundBlurStyle对象属性与期待值BlurStyle.BACKGROUND_THICK比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变BackgroundBlurStyle对象属性为BlurStyle.BACKGROUND_ULTRA_THICK
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundBlurStyle7的BackgroundBlurStyle对象属性与期待值BlurStyle.BACKGROUND_ULTRA_THICK比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变BackgroundBlurStyle对象属性为BlurStyle.NONE
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundBlurStyle8的BackgroundBlurStyle对象属性与期待值BlurStyle.NONE比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变BackgroundBlurStyle对象属性为BlurStyle.COMPONENT_ULTRA_THIN
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundBlurStyle9的BackgroundBlurStyle对象属性与期待值BlurStyle.COMPONENT_ULTRA_THIN比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变BackgroundBlurStyle对象属性为BlurStyle.COMPONENT_THIN
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundBlurStyle10的BackgroundBlurStyle对象属性与期待值BlurStyle.COMPONENT_THIN比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变BackgroundBlurStyle对象属性为BlurStyle.COMPONENT_REGULAR
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundBlurStyle11的BackgroundBlurStyle对象属性与期待值BlurStyle.COMPONENT_REGULAR比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变BackgroundBlurStyle对象属性为BlurStyle.COMPONENT_THICK
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundBlurStyle12的BackgroundBlurStyle对象属性与期待值BlurStyle.COMPONENT_THICK比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变BackgroundBlurStyle对象属性为BlurStyle.COMPONENT_ULTRA_THICK
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundBlurStyle13的BackgroundBlurStyle对象属性与期待值BlurStyle.COMPONENT_ULTRA_THICK比对
   * 点击屏幕坐标(100，100)
   */
  defineTest('textPickerDialogBackgroundBlurStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textPickerDialogBackgroundBlurStyleTestDemo running")
    let driver: Tester = Tester.create()

    let button: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogBackgroundBlurStyle').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('ClickToggleBackgroundBlueStyle').enabled(true))

    await button2.tap()
    await button.tap()
    let textBackgroundBlurStyle1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle1: string = await textBackgroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle1).$attrs.backgroundBlurStyle.value, 'BlurStyle.Thin')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textBackgroundBlurStyle2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle2: string = await textBackgroundBlurStyle2.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle2).$attrs.backgroundBlurStyle, 'BlurStyle.Regular')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textBackgroundBlurStyle3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle3: string = await textBackgroundBlurStyle3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle3).$attrs.backgroundBlurStyle, 'BlurStyle.Thick')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textBackgroundBlurStyle4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle4: string = await textBackgroundBlurStyle4.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle4).$attrs.backgroundBlurStyle, 'BlurStyle.BACKGROUND_THIN')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textBackgroundBlurStyle5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle5: string = await textBackgroundBlurStyle5.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle5).$attrs.backgroundBlurStyle, 'BlurStyle.BACKGROUND_REGULAR')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textBackgroundBlurStyle6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle6: string = await textBackgroundBlurStyle6.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle6).$attrs.backgroundBlurStyle, 'BlurStyle.BACKGROUND_THICK')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textBackgroundBlurStyle7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle7: string = await textBackgroundBlurStyle7.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle7).$attrs.backgroundBlurStyle, 'BlurStyle.BACKGROUND_ULTRA_THICK')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textBackgroundBlurStyle8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle8: string = await textBackgroundBlurStyle8.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle8).$attrs.backgroundBlurStyle, 'BlurStyle.NONE')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textBackgroundBlurStyle9: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle9: string = await textBackgroundBlurStyle9.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle9).$attrs.backgroundBlurStyle, 'BlurStyle.COMPONENT_ULTRA_THIN')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textBackgroundBlurStyle10: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle10: string = await textBackgroundBlurStyle10.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle10).$attrs.backgroundBlurStyle, 'BlurStyle.COMPONENT_THIN')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textBackgroundBlurStyle11: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle11: string = await textBackgroundBlurStyle11.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle11).$attrs.backgroundBlurStyle, 'BlurStyle.COMPONENT_REGULAR')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textBackgroundBlurStyle12: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle12: string = await textBackgroundBlurStyle12.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle12).$attrs.backgroundBlurStyle, 'BlurStyle.COMPONENT_THICK')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textBackgroundBlurStyle13: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle13: string = await textBackgroundBlurStyle13.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle13).$attrs.backgroundBlurStyle, 'BlurStyle.COMPONENT_ULTRA_THICK')
    await driver.tap(100, 100)

  }, 0)
}