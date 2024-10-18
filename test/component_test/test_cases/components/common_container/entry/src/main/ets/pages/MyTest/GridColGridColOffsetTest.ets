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

export default async function GridColGridColOffsetTest() {
  /*
   * GridCol组件 GridColOffset属性
   * 找到画面id为gridColOffset的GridCol组件
   * 找到画面文本为GridColOffset的Button组件
   * 获取gridCol的GridColOffset属性与期待值1比对
   * 点击button，变更gridCol的GridColOffset属性值为{ xs: 1, sm: 2, md: 3, lg: 4, xl: 5, xxl: 6 }
   * 获取gridCol的GridColOffset属性与期待值{ xs: 1, sm: 2, md: 3, lg: 4, xl: 5, xxl: 6 }比对
   */
  defineTest('GridColOffsetTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridColGridColOffsetTestDemo running')
    let driver: Tester = Tester.create()
    let gridCol: Component = await driver.findComponent(Matcher.create().id('gridColOffset').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridColOffset').enabled(true))

    let gridColOffset1: string = await gridCol.getInspectorInfo()
    assertEqual(JSON.parse(gridColOffset1).$attrs.gridColOffset, 1)

    await button.tap()
    let gridColOffset2: string = await gridCol.getInspectorInfo()
    assertEqual(JSON.parse(gridColOffset2).$attrs.gridColOffset.xs, 1)
    assertEqual(JSON.parse(gridColOffset2).$attrs.gridColOffset.sm, 2)
    assertEqual(JSON.parse(gridColOffset2).$attrs.gridColOffset.md, 3)
    assertEqual(JSON.parse(gridColOffset2).$attrs.gridColOffset.lg, 4)
    assertEqual(JSON.parse(gridColOffset2).$attrs.gridColOffset.xl, 5)
    assertEqual(JSON.parse(gridColOffset2).$attrs.gridColOffset.xxl, 6)
  })
}