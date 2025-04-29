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

export default async function alertDialogButtonDirectionTest() {
  /*
   * AlertDialog弹窗 ButtonDirection对象说明
   * 找到画面id为alertDialogButtonDirection1，alertDialogButtonDirection2的AlertDialog弹窗
   * 找到画面文本为One Button Dialog,Two Button Dialog,AlertDialogButtonDirection的Button组件
   * 点击button1，弹出text为AlertDialogButtonDirection1的AlertDialog弹窗
   * 获取buttonDirection1属性与期待值DialogButtonDirection.AUTO比对
   * 点击空白退出
   * 点击button2，弹出text为AlertDialogButtonDirection2的AlertDialog弹窗
   * 获取buttonDirection2属性与期待值DialogButtonDirection.HORIZONTAL比对
   * 点击空白退出
   * 点击button3，变更AlertDialogButtonDirection2的属性值为DialogButtonDirection.VERTICAL
   * 点击空白退出
   */
  defineTest('alertDialogButtonDirectionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alertDialogButtonDirectionTestDemo running")
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('One Button Dialog').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('Two Button Dialog').enabled(true))
    let button3: Component =
      await driver.findComponent(Matcher.create().text('AlertDialogButtonDirection').enabled(true))
    await button1.tap()
    let alertDialogButtonDirection1: Component =
      await driver.findComponent(Matcher.create().type('AlertDialog').enabled(true))
    let buttonDirection1: string = await alertDialogButtonDirection1.getInspectorInfo()
    assertEqual(JSON.parse(buttonDirection1).$attrs.buttonDirection, 'DialogButtonDirection.AUTO')
    await driver.tap(100, 100)

    await button2.tap()
    let alertDialogButtonDirection2: Component =
      await driver.findComponent(Matcher.create().type('AlertDialog').enabled(true))
    let buttonDirection2: string = await alertDialogButtonDirection2.getInspectorInfo()
    assertEqual(JSON.parse(buttonDirection2).$attrs.buttonDirection, 'DialogButtonDirection.HORIZONTAL')
    await driver.tap(100, 100)

    await button3.tap()
    await button2.tap()
    let alertDialogButtonDirection3: Component =
      await driver.findComponent(Matcher.create().type('AlertDialog').enabled(true))
    let buttonDirection3: string = await alertDialogButtonDirection3.getInspectorInfo()
    assertEqual(JSON.parse(buttonDirection3).$attrs.buttonDirection, 'DialogButtonDirection.VERTICAL')
    await driver.tap(100, 100)
  }, 0)
}