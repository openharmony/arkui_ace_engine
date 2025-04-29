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
import {
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function customDialogAutoCancelTest() {
  /*
   * CustomDialog弹窗 CustomDialogControllerOptions对象说明
   * 找到画面文本为CustomDialogAutoCancelOpen,CustomDialogAutoCancel的Button组件
   * 点击button1，弹出并找到text为CustomDialogAutoCancel的customDialog1弹窗
   * 获取customDialog1的参数autoCancel与期待值true比对
   * 点击坐标(100,100)退出弹窗
   * 点击button2，弹出并找到text为CustomDialogAutoCancel的customDialog2弹窗
   * 获取customDialog2的参数autoCancel与期待值False比对
   * 点击坐标(100,100)退出弹窗
  */
  defineTest('customDialogAutoCancelTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('customDialogAutoCancelTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('CustomDialogAutoCancelOpen').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('CustomDialogAutoCancel').enabled(true))

    await button1.tap()
    let customDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let autoCancel1: string = await customDialog1.getInspectorInfo()
    assertTrue(JSON.parse(autoCancel1).$attrs.autoCancel)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let customDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let button3: Component =
      await driver.findComponent(Matcher.create().text('CustomDialogAutoCancelClose').enabled(true))
    let autoCancel2: string = await customDialog2.getInspectorInfo()
    assertFalse(JSON.parse(autoCancel2).$attrs.autoCancel)
    await button3.tap()
  }, 0)
}