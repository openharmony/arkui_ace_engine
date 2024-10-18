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

export default async function customDialogAlignmentTest() {
  /*
 * CustomDialog弹窗 CustomDialogControllerOptions对象说明
 * 找到画面文本为CustomDialogAlignmentOpen的Button组件
 * 点击button，弹出并找到text为CustomDialogAlignment的customDialog1弹窗
 * 获取customDialog1的参数alignment与期待值DialogAlignment.TOP比对
 * 点击坐标(500,300)退出弹窗
 * 点击button，弹出并找到text为CustomDialogAlignment的customDialog2弹窗
 * 获取customDialog2的参数alignment与期待值DialogAlignment.CENTER比对
 * 点击坐标(100,100)退出弹窗
 * 点击button，弹出并找到text为CustomDialogAlignment的customDialog3弹窗
 * 获取customDialog3的参数alignment与期待值DialogAlignment.BOTTOM比对
 * 点击坐标(100,100)退出弹窗
 * 点击button，弹出并找到text为CustomDialogAlignment的customDialog4弹窗
 * 获取customDialog4的参数alignment与期待值DialogAlignment.DEFAULT比对
 * 点击坐标(100,100)退出弹窗
 * 点击button，弹出并找到text为CustomDialogAlignment的customDialog5弹窗
 * 获取customDialog5的参数alignment与期待值DialogAlignment.TOP_START比对
 * 点击坐标(500,300)退出弹窗
 * 点击button，弹出并找到text为CustomDialogAlignment的customDialog6弹窗
 * 获取customDialog6的参数alignment与期待值DialogAlignment.TOP_END比对
 * 点击坐标(500,300)退出
 * 点击button，弹出并找到text为CustomDialogAlignment的customDialog7弹窗
 * 获取customDialog7的参数alignment与期待值DialogAlignment.CENTER_START比对
 * 点击坐标(100,100)退出弹窗
 * 点击button，弹出并找到text为CustomDialogAlignment的customDialog8弹窗
 * 获取customDialog8的参数alignment与期待值DialogAlignment.CENTER_END比对
 * 点击坐标(100,100)退出弹窗
 * 点击button，弹出并找到text为CustomDialogAlignment的customDialog9弹窗
 * 获取customDialog9的参数alignment与期待值DialogAlignment.BOTTOM_START比对
 * 点击坐标(100,100)退出弹窗
 * 点击button，弹出并找到text为CustomDialogAlignment的customDialog10弹窗
 * 获取customDialog10的参数alignment与期待值DialogAlignment.BOTTOM_END比对
 * 点击坐标(100,100)退出弹窗
 */
  defineTest('customDialogAlignmentTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('customDialogAlignmentTestDemo running')
    let driver: Tester = Tester.create()
    let button: Component = await driver.findComponent(Matcher.create().text('CustomDialogAlignmentOpen').enabled(true))

    await button.tap()
    let customDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment1: string = await customDialog1.getInspectorInfo()
    assertEqual(JSON.parse(alignment1).$attrs.alignment, 'DialogAlignment.TOP')
    await driver.tap(500, 300)

    await button.tap()
    let customDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment2: string = await customDialog2.getInspectorInfo()
    assertEqual(JSON.parse(alignment2).$attrs.alignment, 'DialogAlignment.CENTER')
    await driver.tap(100, 100)

    await button.tap()
    let customDialog3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment3: string = await customDialog3.getInspectorInfo()
    assertEqual(JSON.parse(alignment3).$attrs.alignment, 'DialogAlignment.BOTTOM')
    await driver.tap(100, 100)

    await button.tap()
    let customDialog4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment4: string = await customDialog4.getInspectorInfo()
    assertEqual(JSON.parse(alignment4).$attrs.alignment, 'DialogAlignment.DEFAULT')
    await driver.tap(100, 100)

    await button.tap()
    let customDialog5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment5: string = await customDialog5.getInspectorInfo()
    assertEqual(JSON.parse(alignment5).$attrs.alignment, 'DialogAlignment.TOP_START')
    await driver.tap(500, 300)

    await button.tap()
    let customDialog6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment6: string = await customDialog6.getInspectorInfo()
    assertEqual(JSON.parse(alignment6).$attrs.alignment, 'DialogAlignment.TOP_END')
    await driver.tap(500, 300)

    await button.tap()
    let customDialog7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment7: string = await customDialog7.getInspectorInfo()
    assertEqual(JSON.parse(alignment7).$attrs.alignment, 'DialogAlignment.CENTER_START')
    await driver.tap(100, 100)

    await button.tap()
    let customDialog8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment8: string = await customDialog8.getInspectorInfo()
    assertEqual(JSON.parse(alignment8).$attrs.alignment, 'DialogAlignment.CENTER_END')
    await driver.tap(100, 100)

    await button.tap()
    let customDialog9: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment9: string = await customDialog9.getInspectorInfo()
    assertEqual(JSON.parse(alignment9).$attrs.alignment, 'DialogAlignment.BOTTOM_START')
    await driver.tap(100, 100)

    await button.tap()
    let customDialog10: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment10: string = await customDialog10.getInspectorInfo()
    assertEqual(JSON.parse(alignment10).$attrs.alignment, 'DialogAlignment.BOTTOM_END')
  }, 0)
}