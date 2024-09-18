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

export default async function borderImageTest_three() {
  /*
   * Text组件 BorderImage通用属性
   * 找到画面id为textBorderImage3的组件
   * 找到画面text为ButtonBorderImage3的button组件
   * 获取textBorderImage3的BorderImage属性与期待值
   * { width: '10px', source: '../../../resources/base/media/2.png' }比较
   * 点击button，变更textBorderImage3的BorderImage属性与期待值
   * { width: 10, source: $r('app.media.icon') }比较
   * 点击button，变更textBorderImage3的BorderImage属性与期待值
   * { width: $r('app.string.common_breadth'), source: '../../../resources/base/media/2.png' }比较
   * 点击button，变更textBorderImage3的BorderImage属性与期待值
   * { width: { left: '8px', right: '10px', top: '8px', bottom: '10px' }, source: $r('app.media.icon') }比较
   * 点击button，变更textBorderImage3的BorderImage属性与期待值
   * { width: { left: 5, right: 5, top: 5, bottom: 5 }, source: '../../../resources/base/media/2.png' }比较
   * 点击button，变更textBorderImage3的BorderImage属性与期待值
   * { width: { left: $r('app.string.common_breadth'), right: $r('app.string.common_breadth'),
   *    top: $r('app.string.common_breadth'), bottom: $r('app.string.common_breadth') }, source: $r('app.media.icon') }比较
   */
  defineTest('borderImageTest_threeDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('borderImageTest_threeDemo running')
    let driver: Tester = Tester.create()
    let textBorderImage3: Component = await driver.findComponent(Matcher.create().id('textBorderImage3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonBorderImage3').enabled(true))

    let borderImage1: string = await textBorderImage3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage1).$attrs.borderImage).width, '10.00px')
    assertEqual(JSON.parse(JSON.parse(borderImage1).$attrs.borderImage).source, '../../../resources/base/media/2.png')

    await button.tap()
    let borderImage2: string = await textBorderImage3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage2).$attrs.borderImage).width, '10.00vp')
    assertEqual(JSON.parse(JSON.parse(borderImage2).$attrs.borderImage).source,
      $r('app.media.app_icon'))

    await button.tap()
    let borderImage3: string = await textBorderImage3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage3).$attrs.borderImage).width,
      $r('app.string.common_breadth'))
    assertEqual(JSON.parse(JSON.parse(borderImage3).$attrs.borderImage).source, '../../../resources/base/media/2.png')

    await button.tap()
    let borderImage4: string = await textBorderImage3.getInspectorInfo()
    assertEqual(JSON.parse(borderImage4)
      .$attrs
      .borderImage
      .width
      .left, '8px')
    assertEqual(JSON.parse(borderImage4)
      .$attrs
      .borderImage
      .width
      .right, '10px')
    assertEqual(JSON.parse(borderImage4)
      .$attrs
      .borderImage
      .width
      .top, '8px')
    assertEqual(JSON.parse(borderImage4)
      .$attrs
      .borderImage
      .width
      .bottom, '10px')
    assertEqual(JSON.parse(borderImage4).$attrs.borderImage.source, $r('app.media.app_icon'))

    await button.tap()
    let borderImage5: string = await textBorderImage3.getInspectorInfo()
    assertEqual(JSON.parse(borderImage5)
      .$attrs
      .borderImage
      .width
      .left, 5)
    assertEqual(JSON.parse(borderImage5)
      .$attrs
      .borderImage
      .width
      .right, 5)
    assertEqual(JSON.parse(borderImage5)
      .$attrs
      .borderImage
      .width
      .top, 5)
    assertEqual(JSON.parse(borderImage5)
      .$attrs
      .borderImage
      .width
      .bottom, 5)
    assertEqual(JSON.parse(borderImage5).$attrs.borderImage.source, '../../../resources/base/media/2.png')

    await button.tap()
    let borderImage6: string = await textBorderImage3.getInspectorInfo()
    assertEqual(JSON.parse(borderImage6)
      .$attrs
      .borderImage
      .width
      .left, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(borderImage6)
      .$attrs
      .borderImage
      .width
      .right, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(borderImage6)
      .$attrs
      .borderImage
      .width
      .top, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(borderImage6)
      .$attrs
      .borderImage
      .width
      .bottom, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(borderImage6).$attrs.borderImage.source, $r('app.media.app_icon'))
  }, 0)
}