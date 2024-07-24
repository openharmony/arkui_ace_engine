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

export default async function textPickerDialogOffsetTest() {
  /*
   * TextPickerDialog组件 Offset对象
   * 找到画面文本为TextPickerDialogOffset1,TextPickerDialogOffset2,TextPickerDialogOffset3的Button组件
   * 点击Button1改变Offset对象dx属性为50,
   * 改变Offset对象dy属性为0
   * 找到可以滚动的TextPickerDialog组件
   * 获取offset1的Offset对象dx属性与期待值50比对
   * 获取offset1的Offset对象dy属性与期待值0比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变Offset对象dx属性为'0',
   * 改变Offset对象dy属性为'50'
   * 找到可以滚动的TextPickerDialog组件
   * 获取offset2的Offset对象dx属性与期待值'0'比对
   * 获取offset2的Offset对象dy属性与期待值'50'比对
   * 点击屏幕坐标(100，100)
   * 点击Button3改变Offset对象dx属性为$r('app.integer.offset_size'),
   * 改变Offset对象dy属性为$r('app.integer.offset_size')
   * 找到可以滚动的TextPickerDialog组件
   * 获取offset3的Offset对象dx属性与期待值$r('app.integer.offset_size')比对
   * 获取offset3的Offset对象dy属性与期待值$r('app.integer.offset_size')比对
   * 点击屏幕坐标(100，100)
   */
  defineTest('textPickerDialogOffsetTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textPickerDialogOffsetTestDemo running")
    let driver: Tester = Tester.create()

    let button1: Component = await driver.findComponent(Matcher.create().text('TextPickerDialogOffset1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextPickerDialogOffset2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('TextPickerDialogOffset3').enabled(true))

    await button1.tap()
    let textOffset1: Component = await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let offset1: string = await textOffset1.getInspectorInfo()
    assertEqual(JSON.parse(offset1).$attrs.offset.dX, 50)
    assertEqual(JSON.parse(offset1).$attrs.offset.dY, 0)
    await driver.tap(100, 100)

    await button2.tap()
    let textOffset2: Component = await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let offset2: string = await textOffset2.getInspectorInfo()
    assertEqual(String(JSON.parse(offset2).$attrs.offset.dX), '0')
    assertEqual(String(JSON.parse(offset2).$attrs.offset.dY), '50')
    await driver.tap(100, 100)

    await button3.tap()
    let textOffset3: Component = await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let offset3: string = await textOffset3.getInspectorInfo()
    assertEqual(String(JSON.parse(offset3).$attrs.offset.dX), $r('app.integer.offset_size'))
    assertEqual(String(JSON.parse(offset3).$attrs.offset.dY), $r('app.integer.offset_size'))
    await driver.tap(100, 100)
  }, 0)
}