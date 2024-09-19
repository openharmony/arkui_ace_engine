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

export default async function customDialogCancelTest() {
  /*
* CustomDialog弹窗 CustomDialogControllerOptions对象说明
* 找到画面文本为CustomDialogCancel的text组件
* 找到画面文本为CustomDialogCancelOpen的Button组件
* 点击button打开弹窗，点击坐标(100,100)退出弹窗
* 获取text的参数content与期待值'CustomDialogCancel is ok'比对
*/
  defineTest('customDialogCancelTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('customDialogCancelTestDemo running')
    let driver: Tester = Tester.create()
    let text: Component = await driver.findComponent(Matcher.create().id('CustomDialogCancel').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('CustomDialogCancelOpen').enabled(true))

    await button.tap()
    await driver.tap(100, 100)
    let content: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(content).$attrs.content, 'CustomDialogCancel is ok')
  }, 0)
}