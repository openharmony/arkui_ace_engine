/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
    assertFalse,
    assertTrue,
    Component,
    defineTest,
    Matcher,
    TestCaseLevel,
    Tester
  } from '@ohos.arkui.componentTest'
  
  
  export default async function alphabetIndexerAlignStyleTest() {
    /*
  * AlphabetIndexer组件  alignStyle属性
  * 找到画面id为alphabetIndexerAlignStyle1,alphabetIndexerAlignStyle2,alphabetIndexerAlignStyle3,alphabetIndexerAlignStyle4,alphabetIndexerAlignStyle5的AlphabetIndexer组件
  * 找到画面文本为AlphabetIndexerAlignStyle的button组件
  * 获取alphabetIndexer1的alignStyle属性与期待值IndexerAlign.Right,$r('app.string.length')比对
  * 获取alphabetIndexer2的alignStyle属性与期待值IndexerAlign.Left,60比对
  * 获取alphabetIndexer3的alignStyle属性与期待值IndexerAlign.Left,10比对
  * 获取alphabetIndexer4的alignStyle属性与期待值IndexerAlign.Left,100比对
  * 获取alphabetIndexer5的alignStyle属性与期待值IndexerAlign.Left,10比对
  * 点击button,变更alphabetIndexer1的alignStyle属性值为'100px'
  * 获取alphabetIndexer1的alignStyle属性与期待值'100px'比对
  */
    defineTest('alphabetIndexerAlignStyleTestDemo', {
      level: TestCaseLevel.LEVEL0
    }, async () => {
      console.log("alphabetIndexerAlignStyleTestDemo running")
      const  driver: Tester = Tester.create()
      const  alphabetIndexer1: Component =
        await driver.findComponent(Matcher.create().id('alphabetIndexerAlignStyle1').enabled(true))
      const  alphabetIndexer2: Component =
        await driver.findComponent(Matcher.create().id('alphabetIndexerAlignStyle2').enabled(true))
      const  alphabetIndexer3: Component =
        await driver.findComponent(Matcher.create().id('alphabetIndexerAlignStyle3').enabled(true))
      const  alphabetIndexer4: Component =
        await driver.findComponent(Matcher.create().id('alphabetIndexerAlignStyle4').enabled(true))
      const  alphabetIndexer5: Component =
        await driver.findComponent(Matcher.create().id('alphabetIndexerAlignStyle5').enabled(true))
      const  button: Component = await driver.findComponent(Matcher.create().text('AlphabetIndexerAlignStyle').enabled(true))
  
      const  alignStyle1: string = await alphabetIndexer2.getInspectorInfo()
      assertFalse(JSON.parse(alignStyle1).$attrs.alignStyle.value == undefined)
      assertEqual(JSON.parse(alignStyle1).$attrs.alignStyle.value, 'IndexerAlign.Right')
      assertEqual(JSON.parse(alignStyle1).$attrs.alignStyle.offset, $r('app.string.length'))
      const  alignStyle2: string = await alphabetIndexer3.getInspectorInfo()
      assertEqual(JSON.parse(alignStyle2).$attrs.alignStyle.value, 'IndexerAlign.Left')
      assertEqual(JSON.parse(alignStyle2).$attrs.alignStyle.offset, 60)
      const  alignStyle3: string = await alphabetIndexer4.getInspectorInfo()
      assertEqual(JSON.parse(alignStyle3).$attrs.alignStyle.value, 'IndexerAlign.Left')
      assertEqual(JSON.parse(alignStyle3).$attrs.alignStyle.offset, 10)
      const  alignStyle4: string = await alphabetIndexer5.getInspectorInfo()
      assertEqual(JSON.parse(alignStyle4).$attrs.alignStyle.value, 'IndexerAlign.Left')
      assertEqual(JSON.parse(alignStyle4).$attrs.alignStyle.offset, 100)
  
      const  alignStyle5: string = await alphabetIndexer1.getInspectorInfo()
      assertEqual(JSON.parse(alignStyle5).$attrs.alignStyle.value, 'IndexerAlign.Left')
      assertEqual(JSON.parse(alignStyle5).$attrs.alignStyle.offset, 10)
  
      await button.tap()
      const  alignStyle6: string = await alphabetIndexer1.getInspectorInfo()
      assertEqual(JSON.parse(alignStyle6).$attrs.alignStyle.value, 'IndexerAlign.Left')
      assertEqual(JSON.parse(alignStyle6).$attrs.alignStyle.offset, '100px')
    }, 0)
  }


export default async function alphabetIndexerAutoCollapseTest() {
  /*
* AlphabetIndexer组件  autoCollapse属性
* 找到画面id为alphabetIndexerAutoCollapse1,alphabetIndexerAutoCollapse2,alphabetIndexerAutoCollapse3,alphabetIndexerAutoCollapse4,alphabetIndexerAutoCollapse5,alphabetIndexerAutoCollapse6的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerAutoCollapse的button组件
* 获取alphabetIndexer1的autoCollapse属性与期待值true比对
* 获取alphabetIndexer2的autoCollapse属性与期待值true比对
* 获取alphabetIndexer3的autoCollapse属性与期待值true比对
* 获取alphabetIndexer4的autoCollapse属性与期待值true比对
* 获取alphabetIndexer5的autoCollapse属性与期待值true比对
* 获取alphabetIndexer6的autoCollapse属性与期待值true比对
* 点击button，变更alphabetIndexer1的autoCollapse属性值为false
* 获取alphabetIndexer1的autoCollapse属性与期待值false比对
*/
  defineTest('alphabetIndexerAutoCollapseTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerAutoCollapseTestDemo running")
    const  driver: Tester = Tester.create()
    const  alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAutoCollapse1').enabled(true))
    const  alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAutoCollapse2').enabled(true))
    const  alphabetIndexer3: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAutoCollapse3').enabled(true))
    const  alphabetIndexer4: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAutoCollapse4').enabled(true))
    const  alphabetIndexer5: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAutoCollapse5').enabled(true))
    const  alphabetIndexer6: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAutoCollapse6').enabled(true))
    const  button: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerAutoCollapse').enabled(true))

    const  autoCollapse1: string = await alphabetIndexer2.getInspectorInfo()
    assertTrue(JSON.parse(autoCollapse1).$attrs.autoCollapse)
    const  autoCollapse2: string = await alphabetIndexer3.getInspectorInfo()
    assertTrue(JSON.parse(autoCollapse2).$attrs.autoCollapse)
    const  autoCollapse3: string = await alphabetIndexer4.getInspectorInfo()
    assertTrue(JSON.parse(autoCollapse3).$attrs.autoCollapse)
    const  autoCollapse4: string = await alphabetIndexer5.getInspectorInfo()
    assertTrue(JSON.parse(autoCollapse4).$attrs.autoCollapse)
    const  autoCollapse5: string = await alphabetIndexer6.getInspectorInfo()
    assertTrue(JSON.parse(autoCollapse5).$attrs.autoCollapse)

    const  autoCollapse6: string = await alphabetIndexer1.getInspectorInfo()
    assertTrue(JSON.parse(autoCollapse6).$attrs.autoCollapse)

    await button.tap()
    const  autoCollapse7: string = await alphabetIndexer1.getInspectorInfo()
    assertFalse(JSON.parse(autoCollapse7).$attrs.autoCollapse)
  }, 0)
}


export default async function alphabetIndexerColorTest() {
  /*
* AlphabetIndexer组件  color属性
* 找到画面id为alphabetIndexerColor1,alphabetIndexerColor2的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerColor1,AlphabetIndexerColor2的button组件
* 获取alphabetIndexer1的color属性与期待值Color.Gray比对
* 获取alphabetIndexer2的color属性与期待值'#FF808080'比对
* 点击button1，变更alphabetIndexer2的color属性值为'#FFFFA500'
* 获取alphabetIndexer2的color属性与期待值'#FFFFA500'比对
* 点击button2，变更alphabetIndexer2的color属性值为$r('sys.color.ohos_id_color_text_hyperlink')
* 获取alphabetIndexer2的color属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
*/
  defineTest('alphabetIndexerColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerColorTestDemo running")
    const  driver: Tester = Tester.create()
    const  alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerColor1').enabled(true))
    const  alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerColor2').enabled(true))
    const  button1: Component = await driver.findComponent(Matcher.create().text('AlphabetIndexerColor1').enabled(true))
    const  button2: Component = await driver.findComponent(Matcher.create().text('AlphabetIndexerColor2').enabled(true))

    const  color1: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(color1).$attrs.color.toLowerCase(), Color.Gray)

    const  color2: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(color2).$attrs.color, '#FF808080')
    await button1.tap()
    const  color3: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(color3).$attrs.color, '#FFFFA500')
    await button2.tap()
    const  color4: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(color4).$attrs.color, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}

export default async function alphabetIndexerFontTest() {
  /*
* AlphabetIndexer组件 font属性
* 找到画面id为alphabetIndexerFont1,alphabetIndexerFont2,alphabetIndexerFont3,alphabetIndexerFont4,
* alphabetIndexerFont5,alphabetIndexerFont6,alphabetIndexerFont7的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerFont1的button组件
* 获取alphabetIndexer1的font属性与期待值8.00fp,200,'Arial',FontStyle::Normal比对
* 获取alphabetIndexer2的font属性与期待值FontWeight.Normal比对
* 获取alphabetIndexer3的font属性与期待值$r('app.string.length'),FontWeight.Lighter比对
* 获取alphabetIndexer4的font属性与期待值FontWeight.Medium比对
* 获取alphabetIndexer5的font属性与期待值FontWeight.Bold比对
* 获取alphabetIndexer6的font属性与期待值FontWeight.Regular比对
* 获取alphabetIndexer7的font属性与期待值FontWeight.Bolder比对
* 点击button1，变更alphabetIndexer1的font属性值为'10px',"200",'TESTFONTRawFile',FontStyle.Italic
* 获取alphabetIndexer1的font属性与期待值'10.00px',"200",'TESTFONTRawFile',FontStyle::Italic比对
*/
  defineTest('alphabetIndexerFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerFontTestDemo running")
    const  driver: Tester = Tester.create()
    const  alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerFont1').enabled(true))
    const  alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerFont2').enabled(true))
    const  alphabetIndexer3: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerFont3').enabled(true))
    const  alphabetIndexer4: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerFont4').enabled(true))
    const  alphabetIndexer5: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerFont5').enabled(true))
    const  alphabetIndexer6: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerFont6').enabled(true))
    const  alphabetIndexer7: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerFont7').enabled(true))
    const  button1: Component = await driver.findComponent(Matcher.create().text('AlphabetIndexerFont1').enabled(true))

    const  font1: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(font1).$attrs.font.fontWeight, 'FontWeight.Normal')
    const  font2: string = await alphabetIndexer3.getInspectorInfo()
    assertEqual(JSON.parse(font2).$attrs.font.fontSize, $r('app.string.font'))
    assertEqual(JSON.parse(font2).$attrs.font.fontWeight, 'FontWeight.Lighter')
    const  font3: string = await alphabetIndexer4.getInspectorInfo()
    assertEqual(JSON.parse(font3).$attrs.font.fontWeight, 'FontWeight.Medium')
    const  font4: string = await alphabetIndexer5.getInspectorInfo()
    assertEqual(JSON.parse(font4).$attrs.font.fontWeight, 'FontWeight.Bold')
    const  font5: string = await alphabetIndexer6.getInspectorInfo()
    assertEqual(JSON.parse(font5).$attrs.font.fontWeight, 'FontWeight.Regular')
    const  font6: string = await alphabetIndexer7.getInspectorInfo()
    assertEqual(JSON.parse(font6).$attrs.font.fontWeight, 'FontWeight.Bolder')

    const  font7: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(font7).$attrs.font.fontSize, '8.00fp')
    assertEqual(JSON.parse(font7).$attrs.font.fontWeight, '200')
    assertEqual(JSON.parse(font7).$attrs.font.fontFamily, 'Arial')
    assertEqual(JSON.parse(font7).$attrs.font.fontStyle, 'FontStyle::NORMAL')

    await button1.tap()
    const  font8: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(font8).$attrs.font.fontSize, '10.00px')
    assertEqual(JSON.parse(font8).$attrs.font.fontWeight, '200')
    assertEqual(JSON.parse(font8).$attrs.font.fontFamily, 'TESTFONTRawFile')
    assertEqual(JSON.parse(font8).$attrs.font.fontStyle, 'FontStyle::ITALIC')
  }, 0)
}


export default async function alphabetIndexerItemSizeTest() {
  /*
* AlphabetIndexer组件 itemSize属性
* 找到画面id为alphabetIndexerItemSize的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerColor1,AlphabetIndexerColor2的button组件
* 获取alphabetIndexer的itemSize属性与期待值32.00vp比对
* 点击button，变更alphabetIndexer的itemSize属性值为'100px'
* 获取alphabetIndexer的itemSize属性与期待值'100.00px'比对
*/
  defineTest('alphabetIndexerItemSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerItemSizeTestDemo running")
    const  driver: Tester = Tester.create()
    const  alphabetIndexer: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerItemSize').enabled(true))
    const  button: Component = await driver.findComponent(Matcher.create().text('AlphabetIndexerItemSize').enabled(true))

    const  itemSize1: string = await alphabetIndexer.getInspectorInfo()
    assertEqual(JSON.parse(itemSize1).$attrs.itemSize, '32.00vp')

    await button.tap()
    const  itemSize2: string = await alphabetIndexer.getInspectorInfo()
    assertEqual(JSON.parse(itemSize2).$attrs.itemSize, '100.00px')
  }, 0)
}

export default async function alphabetIndexerPopupColorTest() {
  /*
* AlphabetIndexer组件  popupColor属性
* 找到画面id为alphabetIndexerPopupColor1,alphabetIndexerPopupColor2的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerPopupColor1,AlphabetIndexerPopupColor2的button组件
* 获取alphabetIndexer1的popupColor属性与期待值Color.Red比对
* 获取alphabetIndexer2的popupColor属性与期待值'#FF808080'比对
* 点击button1，变更alphabetIndexer2的popupColor属性值为'#ffa500'
* 获取alphabetIndexer2的popupColor属性与期待值'#FFFFA500'比对
* 点击button2，变更alphabetIndexer2的popupColor属性值为$r('sys.color.ohos_id_color_text_hyperlink')
* 获取alphabetIndexer2的popupColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
*/
  defineTest('alphabetIndexerPopupColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerPopupColorTestDemo running")
    const  driver: Tester = Tester.create()
    const  alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupColor1').enabled(true))
    const  alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupColor2').enabled(true))
    const  button1: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerPopupColor1').enabled(true))
    const  button2: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerPopupColor2').enabled(true))

    const  popupColor1: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(popupColor1).$attrs.popupColor.toLowerCase(), Color.Red)

    const  popupColor2: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupColor2).$attrs.popupColor, '#FF808080')

    await button1.tap()
    const  popupColor3: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupColor3).$attrs.popupColor, '#FFFFA500')

    await button2.tap()
    const  popupColor4: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupColor4).$attrs.popupColor, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}