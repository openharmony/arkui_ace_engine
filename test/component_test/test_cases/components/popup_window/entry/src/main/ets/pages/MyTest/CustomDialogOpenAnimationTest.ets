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
import Curves from '@ohos.curves'

/*
* CustomDialog弹窗 CustomDialogControllerOptions对象说明
* 找到画面文本为CustomDialogOpenAnimationOpen的Button组件和画面文本为''的Text组件
* 点击button1，弹出并找到画面文本为CustomDialogOpenAnimation的customDialog1弹窗
* 获取customDialog1的参数openAnimation.duration与期待值500比对
* 获取customDialog1的参数openAnimation.tempo与期待值0.5比对
* 获取customDialog1的参数openAnimation.curve与期待值Curve.ExtremeDeceleration比对
* 获取customDialog1的参数openAnimation.delay与期待值1000比对
* 获取customDialog1的参数openAnimation.iterations与期待值2比对
* 获取customDialog1的参数openAnimation.playMode与期待值PlayMode.Normal比对
* 获取customDialog1的参数openAnimation.finishCallbackType与期待值FinishCallbackType.REMOVED比对
* 获取customDialog1的参数openAnimation.expectedFrameRateRange.min与期待值10比对
* 获取customDialog1的参数openAnimation.expectedFrameRateRange.max与期待值120比对
* 获取customDialog1的参数openAnimation.expectedFrameRateRange.expected与期待值60比对
* 点击坐标(100,100)退出弹窗
* 获取text的参数content与期待值'OnFish is ok'比对
* 点击button1，弹出并找到画面文本为CustomDialogOpenAnimation的customDialog2弹窗
* 获取customDialog2的参数openAnimation.tempo与期待值-1比对
* 获取customDialog2的参数openAnimation.curve与期待值Curves.cubicBezierCurve(0.25, 0.1, 0.25, 1.0).interpolate(0.5)比对
* 获取customDialog2的参数openAnimation.playMode与期待值PlayMode.Reverse比对
* 获取customDialog2的参数openAnimation.finishCallbackType与期待值FinishCallbackType.LOGICALLY比对
* 点击坐标(100,100)退出弹窗
* 获取text的参数content与期待值'OnFish is okk'比对
* 点击button1，弹出并找到画面文本为CustomDialogOpenAnimation的customDialog3弹窗
* 获取customDialog3参数openAnimation.curve与期待值"fast-out-slow-in"比对
* 获取customDialog3的参数openAnimation.playMode与期待值PlayMode.Alternate比对
* 点击坐标(100,100)退出弹窗
* 点击button1，弹出并找到画面文本为CustomDialogOpenAnimation的customDialog4弹窗
* 获取customDialog4的参数openAnimation.playMode与期待值PlayMode.AlternateReverse比对
* 点击坐标(100,100)退出弹窗
*/
export default async function customDialogOpenAnimationTest() {
  defineTest('customDialogOpenAnimationTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('customDialogOpenAnimationTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('CustomDialogOpenAnimationOpen').enabled(true))
    let text: Component = await driver.findComponent(Matcher.create().text('').enabled(true))

    await button1.tap()
    let customDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let openAnimation1: string = await customDialog1.getInspectorInfo()
    assertFalse(JSON.parse(openAnimation1).$attrs.openAnimation == undefined)
    assertEqual(JSON.parse(openAnimation1).$attrs.openAnimation.duration, 500)
    assertEqual(JSON.parse(openAnimation1).$attrs.openAnimation.tempo, 0.5)
    assertEqual(JSON.parse(openAnimation1).$attrs.openAnimation.curve, Curve.ExtremeDeceleration)
    assertEqual(JSON.parse(openAnimation1).$attrs.openAnimation.delay, 1000)
    assertEqual(JSON.parse(openAnimation1).$attrs.openAnimation.iterations, 2)
    assertEqual(JSON.parse(openAnimation1).$attrs.openAnimation.playMode, PlayMode.Normal)
    assertEqual(JSON.parse(openAnimation1).$attrs.openAnimation.finishCallbackType, FinishCallbackType.REMOVED)
    assertEqual(JSON.parse(openAnimation1)
      .$attrs
      .openAnimation
      .expectedFrameRateRange
      .min, 10)
    assertEqual(JSON.parse(openAnimation1)
      .$attrs
      .openAnimation
      .expectedFrameRateRange
      .max, 120)
    assertEqual(JSON.parse(openAnimation1)
      .$attrs
      .openAnimation
      .expectedFrameRateRange
      .expected, 60)
    await driver.tap(100, 100)
    let content1: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(content1).$attrs.content, 'OnFish is ok')

    await button1.tap()
    let customDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let openAnimation2: string = await customDialog2.getInspectorInfo()
    assertEqual(JSON.parse(openAnimation2).$attrs.openAnimation.tempo, -1)
    assertEqual(JSON.parse(openAnimation2).$attrs.openAnimation.curve,
      Curves.cubicBezierCurve(0.25, 0.1, 0.25, 1.0).interpolate(0.5))
    assertEqual(JSON.parse(openAnimation2).$attrs.openAnimation.playMode, PlayMode.Reverse)
    assertEqual(JSON.parse(openAnimation2).$attrs.openAnimation.finishCallbackType, FinishCallbackType.LOGICALLY)
    await driver.tap(100, 100)
    let content2: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(content2).$attrs.content, 'OnFish is okk')

    await button1.tap()
    let customDialog3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let openAnimation3: string = await customDialog3.getInspectorInfo()
    assertEqual(JSON.parse(openAnimation3).$attrs.openAnimation.curve, "fast-out-slow-in")
    assertEqual(JSON.parse(openAnimation3).$attrs.openAnimation.playMode, PlayMode.Alternate)
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let openAnimation4: string = await customDialog4.getInspectorInfo()
    assertEqual(JSON.parse(openAnimation4).$attrs.openAnimation.playMode, PlayMode.AlternateReverse)
    await driver.tap(100, 100)
  }, 0)
}