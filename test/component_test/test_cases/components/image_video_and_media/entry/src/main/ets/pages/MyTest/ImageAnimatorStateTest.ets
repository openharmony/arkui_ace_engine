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
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function imageAnimatorStateTest() {
  /*
* ImageAnimator组件 State属性
* 找到画面id为imageAnimatorState1,imageAnimatorState2的ImageAnimator组件
* 找到画面文本为ImageAnimatorState1,ImageAnimatorState2的Button组件
* 获取imageAnimator1的State属性与期待值AnimationStatus.Stopped比对
* 获取imageAnimator2的State属性与期待值AnimationStatus.Initial比对
* 点击button1，变更imageAnimator1的State属性值为AnimationStatus.Running
* 获取imageAnimator1的State属性与期待值AnimationStatus.Running比对
* 点击button2，变更imageAnimator1的State属性值为AnimationStatus.Paused
* 获取imageAnimator1的State属性与期待值AnimationStatus.Paused比对
*/
  defineTest('imageAnimatorStateTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageAnimatorStateTestDemo running")
    let driver: Tester = Tester.create()
    let imageAnimator1: Component = await driver.findComponent(Matcher.create().id('imageAnimatorState1').enabled(true))
    let imageAnimator2: Component = await driver.findComponent(Matcher.create().id('imageAnimatorState2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ImageAnimatorState1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ImageAnimatorState2').enabled(true))
    let state1: string = await imageAnimator1.getInspectorInfo()
    assertEqual(JSON.parse(state1).$attrs.state, 'AnimationStatus.Stopped')
    let state2: string = await imageAnimator2.getInspectorInfo()
    assertEqual(JSON.parse(state2).$attrs.state, 'AnimationStatus.Initial')
    await button1.tap()
    let state3: string = await imageAnimator1.getInspectorInfo()
    assertEqual(JSON.parse(state3).$attrs.state, 'AnimationStatus.Running')
    await button2.tap()
    let state4: string = await imageAnimator1.getInspectorInfo()
    assertEqual(JSON.parse(state4).$attrs.state, 'AnimationStatus.Paused')
  }, 0)
}