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
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

/*
* CustomDialog弹窗 CustomDialogControllerOptions对象说明
* 找到画面文本为CustomDialogGridCountOpen的Button组件
* 点击button1弹出并找到画面文本为CustomDialogGridCount的customDialog1弹窗
* 获取customDialog1的参数gridCount与期待值3比对
* 点击坐标(100,100)退出弹窗
*/
export default async function customDialogGridCountTest() {
  defineTest('customDialogGridCountTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('customDialogGridCountTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('CustomDialogGridCountOpen').enabled(true))

    await button1.tap()
    let customDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let gridCount: string = await customDialog1.getInspectorInfo()
    assertEqual(JSON.parse(gridCount).$attrs.gridCount, '3')
    await driver.tap(100, 100)
  }, 0)
}