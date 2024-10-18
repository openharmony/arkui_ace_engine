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
import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function visibilityTest() {
  /*
  * 使用Circle组件 Visibility属性
  * 找到画面id为circleVisibility1，circleVisibility2的Circle组件
  * 找到画面文本为ButtonVisibility的Button组件
  * 获取circleVisibility1的Visibility属性与期待值Visibility.Visible比对
  * 获取circleVisibility2的Visibility属性与期待值Visibility.Hidden比对
  * 点击button，变更circleVisibility2的Visibility属性值为Visibility.None
  * 获取circleVisibility2的Visibility属性与期待值Visibility.None比对
  */
  defineTest('visibilityTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('visibilityTestDemo running')
    let driver: Tester = Tester.create()
    let circleVisibility1: Component =
      await driver.findComponent(Matcher.create().id('circleVisibility1').enabled(true))
    let circleVisibility2: Component =
      await driver.findComponent(Matcher.create().id('circleVisibility2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonVisibility').enabled(true))

    let visibility1: string = await circleVisibility1.getInspectorInfo()
    assertEqual(JSON.parse(visibility1).$attrs.visibility, 'Visibility.Visible')

    let visibility2: string = await circleVisibility2.getInspectorInfo()
    assertEqual(JSON.parse(visibility2).$attrs.visibility, 'Visibility.Hidden')

    await button.tap()
    let visibility3: string = await circleVisibility2.getInspectorInfo()
    assertEqual(JSON.parse(visibility3).$attrs.visibility, 'Visibility.None')
  }, 0)
}