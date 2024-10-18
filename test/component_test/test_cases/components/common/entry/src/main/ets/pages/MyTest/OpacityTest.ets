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
import { assertEqual, assertFalse, assertTrue } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function opacityTest() {
  /*
  * 使用TextClock组件 Opacity属性
  * 找到画面id为 imageClockOpacity1 的TextClock组件
  * 找到画面文本为ButtonOpacity的Button组件
  * 获取 imageClockOpacity1 的Opacity属性与期待值0.7比对
  * 点击button，变更 imageClockOpacity1 的Opacity属性值为$r('app.string.common_opacity')
  * 获取 imageClockOpacity1 的Opacity属性与期待值$r('app.string.common_opacity')比对
  */
  defineTest('opacityTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('opacityTestDemo running')
    let driver: Tester = Tester.create()
    let image1: Component =
      await driver.findComponent(Matcher.create().id('imageClockOpacity1'))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonOpacity').enabled(true))
    let opacity1: string = await image1.getInspectorInfo()
    assertEqual(JSON.parse(opacity1).$attrs.opacity, 0.7)
    await button.tap()
    let opacity2: string = await image1.getInspectorInfo()
    assertEqual(String(JSON.parse(opacity2).$attrs.opacity), $r('app.string.common_opacity'))
  }, 0)
}