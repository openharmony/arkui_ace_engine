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

export default async function imageAnimatorReverseTest() {
  /*
* ImageAnimator组件 Reverse属性
* 找到画面id为imageAnimatorReverse的ImageAnimator组件
* 找到画面文本为ImageAnimatorReverse1的Button组件
* 获取imageAnimator的Reverse属性与期待值true比对
* 点击button1，变更imageAnimator的Reverse属性值为false
* 获取imageAnimator的Reverse属性与期待值false比对
*/
  defineTest('imageAnimatorReverseTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageAnimatorReverseTestDemo running")
    let driver: Tester = Tester.create()
    let imageAnimator: Component = await driver.findComponent(Matcher.create().id('imageAnimatorReverse').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ImageAnimatorReverse1').enabled(true))
    let reverse1: string = await imageAnimator.getInspectorInfo()
    assertTrue(JSON.parse(reverse1).$attrs.reverse)
    await button.tap()
    let reverse2: string = await imageAnimator.getInspectorInfo()
    assertFalse(JSON.parse(reverse2).$attrs.reverse)
  }, 0)
}