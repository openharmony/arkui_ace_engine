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

export default async function imageAnimatorIterationTest() {
  /*
* ImageAnimator组件 Iteration属性
* 找到画面id为imageAnimatorIterations的ImageAnimator组件
* 找到画面文本为ImageAnimatorIterations的Button组件
* 获取imageAnimator的Iteration属性与期待值2比对
* 点击button1，变更imageAnimator的Iteration属性值为-1
* 获取imageAnimator的Iteration属性与期待值-1比对
*/
  defineTest('imageAnimatorIterationTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageAnimatorIterationTestDemo running")
    let driver: Tester = Tester.create()
    let imageAnimator: Component =
      await driver.findComponent(Matcher.create().id('imageAnimatorIterations').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ImageAnimatorIterations').enabled(true))
    let iteration1: string = await imageAnimator.getInspectorInfo()
    assertEqual(JSON.parse(iteration1).$attrs.iteration, '2')
    await button1.tap()
    let iteration2: string = await imageAnimator.getInspectorInfo()
    assertEqual(JSON.parse(iteration2).$attrs.iteration, '-1')
  }, 0)
}