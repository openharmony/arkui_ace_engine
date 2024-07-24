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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function sizeTest() {
  /*
  * Row组件 Size通用属性
  * 找到画面id为rowSize的组件
  * 找到画面text为ButtonSize的button组件
  * 获取rowSize的Size属性与期待值 { width: ’100.00px‘, height: ’100.00px‘ } 比较
  * 点击button，变更rowSize的Size属性为{ width: 50.00vp, height: 50.00vp }
  * 获取rowSize的Size属性与期待值{ width: 50.00vp, height: 50.00vp }比较
  * 点击button，变更rowSize的Size属性为{ width: $r('app.string.common_breadth'), height: $r('app.string.common_breadth') }
  * 获取rowSize的Size属性与期待值{ width: $r('app.string.common_breadth'), height: $r('app.string.common_breadth') }比较
  */
  defineTest('sizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sizeTestDemo running')
    let driver: Tester = Tester.create()
    let rowSize: Component = await driver.findComponent(Matcher.create().id('rowSize').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonSize').enabled(true))

    let size1: string = await rowSize.getInspectorInfo()
    assertEqual(JSON.parse(size1).$attrs.size.width, '100.00px')
    assertEqual(JSON.parse(size1).$attrs.size.height, '100.00px')

    await button.tap()
    let size2: string = await rowSize.getInspectorInfo()
    assertEqual(JSON.parse(size2).$attrs.size.width, '50.00vp')
    assertEqual(JSON.parse(size2).$attrs.size.height, '50.00vp')

    await button.tap()
    let size3: string = await rowSize.getInspectorInfo()
    assertEqual(JSON.parse(size3).$attrs.size.width, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(size3).$attrs.size.height, $r('app.string.common_breadth'))
  }, 0)
}