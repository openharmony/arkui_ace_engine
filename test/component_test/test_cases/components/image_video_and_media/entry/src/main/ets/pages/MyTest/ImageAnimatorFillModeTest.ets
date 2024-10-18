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

export default async function imageAnimatorFillModeTest() {
  /*
 * ImageAnimator组件 FillMode属性
 * 找到画面id为imageAnimatorFillMode1,imageAnimatorFillMode2的ImageAnimator组件
 * 找到画面文本为ImageAnimatorFillMode1,ImageAnimatorFillMode2的Button组件
 * 获取imageAnimator1的FillMode属性与期待值FillMode.None比对
 * 获取imageAnimator2的FillMode属性与期待值FillMode.Both比对
 * 点击button1，变更imageAnimator1的FillMode属性值为FillMode.Forwards
 * 获取imageAnimator1的FillMode属性与期待值FillMode.Forwards比对
 * 点击button2，变更imageAnimator1的FillMode属性值为FillMode.Backwards
 * 获取imageAnimator1的FillMode属性与期待值FillMode.Backwards比对
 */
  defineTest('imageAnimatorFillModeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageAnimatorFillModeTestDemo running")
    let driver: Tester = Tester.create()
    let imageAnimator1: Component =
      await driver.findComponent(Matcher.create().id('imageAnimatorFillMode1').enabled(true))
    let imageAnimator2: Component =
      await driver.findComponent(Matcher.create().id('imageAnimatorFillMode2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ImageAnimatorFillMode1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ImageAnimatorFillMode2').enabled(true))
    let fillMode1: string = await imageAnimator1.getInspectorInfo()
    assertEqual(JSON.parse(fillMode1).$attrs.fillMode, 'FillMode.None')
    let fillMode2: string = await imageAnimator2.getInspectorInfo()
    assertEqual(JSON.parse(fillMode2).$attrs.fillMode, 'FillMode.Both')
    await button1.tap()
    let fillMode3: string = await imageAnimator1.getInspectorInfo()
    assertEqual(JSON.parse(fillMode3).$attrs.fillMode, 'FillMode.Forwards')
    await button2.tap()
    let fillMode4: string = await imageAnimator1.getInspectorInfo()
    assertEqual(JSON.parse(fillMode4).$attrs.fillMode, 'FillMode.Backwards')
  }, 0)
}