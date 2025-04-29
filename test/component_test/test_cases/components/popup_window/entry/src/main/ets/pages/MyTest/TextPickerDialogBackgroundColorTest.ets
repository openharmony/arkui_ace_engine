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

export default async function textPickerDialogBackgroundColorTest() {
  /*
   * TextPickerDialog组件 BackgroundColor对象
   * 找到画面文本为TextPickerDialogBackgroundColor1,TextPickerDialogBackgroundColor2,
   * TextPickerDialogBackgroundColor3,TextPickerDialogBackgroundColor4的Button组件
   * 点击Button1改变BackgroundBlurStyle对象属性为Color.Green
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundColor1的BackgroundColor对象属性与期待值Color.Green比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变BackgroundBlurStyle对象属性为0x0000ff
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundColor2的BackgroundColor对象属性与期待值0x0000ff比对
   * 点击屏幕坐标(100，100)
   * 点击Button3改变BackgroundBlurStyle对象属性为$r('app.color.color_red')
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundColor3的BackgroundColor对象属性与期待值$r('app.color.color_red')比对
   * 点击屏幕坐标(100，100)
   * 点击Button4改变BackgroundBlurStyle对象属性为'#ffff00'
   * 找到可以滚动的TextPickerDialog组件
   * 获取backgroundColor4的BackgroundColor对象属性与期待值'#ffff00'比对
   * 点击屏幕坐标(100，100)
   */
  defineTest('textPickerDialogBackgroundColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textPickerDialogBackgroundColorTestDemo running")
    let driver: Tester = Tester.create()

    let button1: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogBackgroundColor1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogBackgroundColor2').enabled(true))
    let button3: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogBackgroundColor3').enabled(true))
    let button4: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogBackgroundColor4').enabled(true))

    await button1.tap()
    let textDialogBackgroundColor1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor1: string = await textDialogBackgroundColor1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor1).$attrs.backgroundColor, Color.Green)
    await driver.tap(100, 100)

    await button2.tap()
    let textDialogBackgroundColor2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor2: string = await textDialogBackgroundColor2.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor2).$attrs.backgroundColor, 0x0000ff)
    await driver.tap(100, 100)

    await button3.tap()
    let textDialogBackgroundColor3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor3: string = await textDialogBackgroundColor3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor3).$attrs.backgroundColor, $r('app.color.color_red'))
    await driver.tap(100, 100)

    await button4.tap()
    let textDialogBackgroundColor4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor4: string = await textDialogBackgroundColor4.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor4).$attrs.backgroundColor, '#ffff00')
    await driver.tap(100, 100)

  }, 0)
}