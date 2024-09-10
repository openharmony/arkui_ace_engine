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

export default async function imageAnimatorFixedSizeTest() {
  /*
* ImageAnimator组件 FixedSize属性
* 找到画面id为imageAnimatorFixedSize的ImageAnimator组件
* 找到画面文本为ImageAnimatorFixedSize1的Button组件
* 获取imageAnimator的FixedSize属性与期待值true比对
* 点击button1，变更imageAnimator1的FixedSize属性值为false
* 获取imageAnimator的FixedSize属性与期待值false比对
*/
  defineTest('imageAnimatorFixedSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageAnimatorFixedSizeTestDemo running")
    let driver: Tester = Tester.create()
    let imageAnimator: Component =
      await driver.findComponent(Matcher.create().id('imageAnimatorFixedSize').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ImageAnimatorFixedSize1').enabled(true))
    let fixedSize1: string = await imageAnimator.getInspectorInfo()
    assertTrue(JSON.parse(fixedSize1).$attrs.fixedSize)
    await button.tap()
    let fixedSize2: string = await imageAnimator.getInspectorInfo()
    assertFalse(JSON.parse(fixedSize2).$attrs.fixedSize)
  }, 0)
}