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

export default async function textPickerDialogAlignmentTest() {
  /*
   * TextPickerDialog组件 Alignment对象
   * 找到画面文本为TextPickerDialogAlignment的Button组件
   * 找到画面文本为ClickToggleAlignment的Button2组件
   * 点击Button2改变Alignment对象属性为DialogAlignment.Top
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取alignment1的Alignment对象属性与期待值DialogAlignment.Top比对
   * 点击屏幕坐标(580, 900)
   * 点击Button2改变Alignment对象属性为DialogAlignment.Center
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取alignment2的Alignment对象属性与期待值DialogAlignment.Center比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变Alignment对象属性为DialogAlignment.Bottom
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取alignment3的Alignment对象属性与期待值DialogAlignment.Bottom比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变Alignment对象属性为DialogAlignment.Default
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取alignment4的Alignment对象属性与期待值DialogAlignment.Default比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变Alignment对象属性为DialogAlignment.TopStart
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取alignment5的Alignment对象属性与期待值DialogAlignment.TopStart比对
   * 点击屏幕坐标(580, 900)
   * 点击Button2改变Alignment对象属性为DialogAlignment.TopEnd
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取alignment6的Alignment对象属性与期待值DialogAlignment.TopEnd比对
   * 点击屏幕坐标(580, 900)
   * 点击Button2改变Alignment对象属性为DialogAlignment.CenterStart
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取alignment7的Alignment对象属性与期待值DialogAlignment.CenterStart比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变Alignment对象属性为DialogAlignment.CenterEnd
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取alignment8的Alignment对象属性与期待值DialogAlignment.CenterEnd比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变Alignment对象属性为DialogAlignment.BottomStart
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取alignment9的Alignment对象属性与期待值DialogAlignment.BottomStart比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变Alignment对象属性为DialogAlignment.BottomEnd
   * 点击Button弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 获取alignment10的Alignment对象属性与期待值DialogAlignment.BottomEnd比对
   * 点击屏幕坐标(100，100)
   */
  defineTest('textPickerDialogAlignmentTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textPickerDialogAlignmentTestDemo running")

    let driver: Tester = Tester.create()
    let button: Component = await driver.findComponent(Matcher.create().text('TextPickerDialogAlignment').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ClickToggleAlignment').enabled(true))

    await button2.tap()
    await button.tap()
    let textPickerDialogAlignment1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment1: string = await textPickerDialogAlignment1.getInspectorInfo()
    assertEqual(JSON.parse(alignment1).$attrs.alignment, 'DialogAlignment.TOP')
    await driver.tap(580, 900)

    await button2.tap()
    await button.tap()
    let textPickerDialogAlignment2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment2: string = await textPickerDialogAlignment2.getInspectorInfo()
    assertEqual(JSON.parse(alignment2).$attrs.alignment, 'DialogAlignment.CENTER')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textPickerDialogAlignment3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment3: string = await textPickerDialogAlignment3.getInspectorInfo()
    assertEqual(JSON.parse(alignment3).$attrs.alignment, 'DialogAlignment.BOTTOM')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textPickerDialogAlignment4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment4: string = await textPickerDialogAlignment4.getInspectorInfo()
    assertEqual(JSON.parse(alignment4).$attrs.alignment, 'DialogAlignment.DEFAULT')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textPickerDialogAlignment5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment5: string = await textPickerDialogAlignment5.getInspectorInfo()
    assertEqual(JSON.parse(alignment5).$attrs.alignment, 'DialogAlignment.TOP_START')
    await driver.tap(580, 900)

    await button2.tap()
    await button.tap()
    let textPickerDialogAlignment6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment6: string = await textPickerDialogAlignment6.getInspectorInfo()
    assertEqual(JSON.parse(alignment6).$attrs.alignment, 'DialogAlignment.TOP_END')
    await driver.tap(580, 900)

    await button2.tap()
    await button.tap()
    let textPickerDialogAlignment7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment7: string = await textPickerDialogAlignment7.getInspectorInfo()
    assertEqual(JSON.parse(alignment7).$attrs.alignment, 'DialogAlignment.CENTER_START')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textPickerDialogAlignment8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment8: string = await textPickerDialogAlignment8.getInspectorInfo()
    assertEqual(JSON.parse(alignment8).$attrs.alignment, 'DialogAlignment.CENTER_END')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textPickerDialogAlignment9: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment9: string = await textPickerDialogAlignment9.getInspectorInfo()
    assertEqual(JSON.parse(alignment9).$attrs.alignment, 'DialogAlignment.BOTTOM_START')
    await driver.tap(100, 100)

    await button2.tap()
    await button.tap()
    let textPickerDialogAlignment10: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment10: string = await textPickerDialogAlignment10.getInspectorInfo()
    assertEqual(JSON.parse(alignment10).$attrs.alignment, 'DialogAlignment.BOTTOM_END')
    await driver.tap(100, 100)

  }, 0)
}