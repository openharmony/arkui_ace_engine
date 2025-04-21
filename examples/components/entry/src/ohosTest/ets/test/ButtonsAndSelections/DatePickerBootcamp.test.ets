import { describe, beforeAll, it } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import {
  buttonClick,
  getToggle,
  JsonType,
  KeyStruct,
  radioClick,
  Search,
  searchParentBlock,
  searchToggle,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../utils';
import { Point } from '@ohos.UiTest';

const TAG = 'DatePickerBootcamp'

const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

const driver = Driver.create();

export default function DatePickerBootcampTest() {

  describe('DatePickerBootcampTest', () => {

    beforeAll(async (done: Function) => {
      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(8000);
        console.info(TAG + 'DatePickerBootcamp' + ' begin');

        let atomDisplays: Component = await driver.findComponent(ON.text('按钮与选择'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[1].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(1000);

        let ListItems1: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width3: Point = await ListItems1[0].getBoundsCenter()
        let width4: Point = await ListItems1[2].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 500)
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('日期选择器/DatePicker'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].doubleClick()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })

    // lunar
    it('ArkUI_DatePicker_001', 0, async (done: Function) => {

      await Search('参数列表', 'lunar')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'lunar'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lunar', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_DatePicker_002', 0, async (done: Function) => {

      await Search('参数列表', 'lunar')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lunar', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })

    // disappearTextStyle.color
    it('ArkUI_DatePicker_003', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_DatePicker_004', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_DatePicker_005', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_DatePicker_006', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_DatePicker_007', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_DatePicker_008', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color',
          toggleClickType: ToggleClick.Close
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // disappearTextStyle.font.size
    it('ArkUI_DatePicker_009', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.font.size')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.font.size'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('size', JsonType.value)
        ],
        assertEqual: '30.00fp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.font.size',
          toggleClickType: ToggleClick.Close,
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('size', JsonType.value)
        ],
        assertEqual: '10.00fp'
      })

      done();
    })

    // disappearTextStyle.font.weight
    it('ArkUI_DatePicker_010', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.font.weight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.font.weight'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Medium'
      })

      done();
    })

    it('ArkUI_DatePicker_011', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.font.weight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Regular'
      })

      done();
    })

    // textStyle.color
    it('ArkUI_DatePicker_012', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_DatePicker_013', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_DatePicker_014', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_DatePicker_015', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_DatePicker_016', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_DatePicker_017', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'textStyle.color',
          toggleClickType: ToggleClick.Close
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // textStyle.font.size
    it('ArkUI_DatePicker_018', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.size')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'textStyle.font.size'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('size', JsonType.value)
        ],
        assertEqual: '30.00fp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'textStyle.font.size',
          toggleClickType: ToggleClick.Close,
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('size', JsonType.value)
        ],
        assertEqual: '10.00fp'
      })

      done();
    })

    // textStyle.font.weight
    it('ArkUI_DatePicker_019', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.weight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'textStyle.font.weight'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Medium'
      })

      done();
    })

    it('ArkUI_DatePicker_020', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.weight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'textStyle.font.weight',
          toggleClickType: ToggleClick.Close
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Regular'
      })

      done();
    })

    // selectedTextStyle.color
    it('ArkUI_DatePicker_021', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_DatePicker_022', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_DatePicker_023', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_DatePicker_024', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_DatePicker_025', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_DatePicker_026', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color',
          toggleClickType: ToggleClick.Close
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // selectedTextStyle.font.size
    it('ArkUI_DatePicker_027', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.font.size')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.font.size'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('size', JsonType.value)
        ],
        assertEqual: '30.00fp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.font.size',
          toggleClickType: ToggleClick.Close,
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('size', JsonType.value)
        ],
        assertEqual: '10.00fp'
      })

      done();
    })

    // selectedTextStyle.font.weight
    it('ArkUI_DatePicker_028', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.font.weight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.font.weight'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Regular'
      })

      done();
    })

    it('ArkUI_DatePicker_029', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.font.weight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.font.weight',
          toggleClickType: ToggleClick.Close
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Medium'
      })

      done();
    })

    // flexBasis
    it('ArkUI_DatePicker_030', 0, async (done: Function) => {

      await Search('参数列表', 'flexBasis')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'flexBasis',
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('flexBasis', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'flexBasis',
          toggleClickType: ToggleClick.Close,
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('flexBasis', JsonType.value),
        ],
        assertEqual: '120.00vp'
      })

      done();
    })

    // direction
    it('ArkUI_DatePicker_031', 0, async (done: Function) => {

      await Search('参数列表', 'direction')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'direction'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'Direction.Ltr'
      })

      done();
    })

    it('ArkUI_DatePicker_032', 0, async (done: Function) => {

      await Search('参数列表', 'direction')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'direction'
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'Direction.Rtl'
      })

      done();
    })

    it('ArkUI_DatePicker_033', 0, async (done: Function) => {

      await Search('参数列表', 'direction')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'direction',
          toggleClickType: ToggleClick.Close
        },
        id: 'DatePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'Direction.Auto'
      })

      done();
    })

    // disabled
    it('ArkUI_DatePicker_034', 0, async (done: Function) => {

      // 无该属性
      await Search('参数列表', 'disabled')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'disabled'
        },
      })

      done();
    })

    it('ArkUI_DatePicker_035', 0, async (done: Function) => {

      await Search('参数列表', 'disabled')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'disabled',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
  })
}