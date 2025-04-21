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

const TAG = 'TimePickerBootcamp'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function TimePickerBootcampTest() {

  describe('TimePickerBootcampTest', () => {

    beforeAll(async (done: Function) => {
      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(8000);
        console.info(TAG + 'TimePickerBootcamp' + ' begin');

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
        let width4: Point = await ListItems1[3].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 500)
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('时间选择器/TimePicker'))
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

    // format
    it('ArkUI_TimePicker_001', 0, async (done: Function) => {
      // 未找到该属性
      await Search('参数列表', 'format')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'format'
        }
      })

      done();
    })

    it('ArkUI_TimePicker_002', 0, async (done: Function) => {

      await Search('参数列表', 'format')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'format',
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    // 切换12小时制/24小时制
    it('ArkUI_TimePicker_003', 0, async (done: Function) => {

      await Search('参数列表', '切换12小时制/24小时制')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: '切换12小时制/24小时制'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('useMilitaryTime', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_TimePicker_004', 0, async (done: Function) => {

      await Search('参数列表', '切换12小时制/24小时制')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: '切换12小时制/24小时制',
          toggleClickType: ToggleClick.Close
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('useMilitaryTime', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })

    // disappearTextStyle.color
    it('ArkUI_TimePicker_005', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_TimePicker_006', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_TimePicker_007', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_TimePicker_008', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_TimePicker_009', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_TimePicker_010', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color',
          toggleClickType: ToggleClick.Close
        },
        id: 'TimePicker',
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
    it('ArkUI_TimePicker_011', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.font.size')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.font.size',
        },
        id: 'TimePicker',
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
        id: 'TimePicker',
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
    it('ArkUI_TimePicker_012', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.font.weight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.font.weight'
        },
        id: 'TimePicker',
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

    it('ArkUI_TimePicker_013', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.font.weight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.font.weight',
          toggleClickType: ToggleClick.Close
        },
        id: 'TimePicker',
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
    it('ArkUI_TimePicker_014', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_TimePicker_015', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_TimePicker_016', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_TimePicker_017', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_TimePicker_018', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_TimePicker_019', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'textStyle.color',
          toggleClickType: ToggleClick.Close
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // textStyle.font.size
    it('ArkUI_TimePicker_020', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.size')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'textStyle.font.size',
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('size', JsonType.value),
        ],
        assertEqual: '30.00fp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'textStyle.font.size',
          toggleClickType: ToggleClick.Close,
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('size', JsonType.value),
        ],
        assertEqual: '10.00fp'
      })

      done();
    })

    // textStyle.font.weight
    it('ArkUI_TimePicker_021', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.weight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'textStyle.font.weight'
        },
        id: 'TimePicker',
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

    it('ArkUI_TimePicker_022', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.weight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'textStyle.font.weight',
          toggleClickType: ToggleClick.Close
        },
        id: 'TimePicker',
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
    it('ArkUI_TimePicker_023', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_TimePicker_024', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_TimePicker_025', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_TimePicker_026', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_TimePicker_027', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_TimePicker_028', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color',
          toggleClickType: ToggleClick.Close
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // selectedTextStyle.font.size
    it('ArkUI_TimePicker_029', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.font.size')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.font.size',
        },
        id: 'TimePicker',
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
        id: 'TimePicker',
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
    it('ArkUI_TimePicker_030', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.font.weight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.font.weight'
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Regular'
      })

      done();
    })

    it('ArkUI_TimePicker_031', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.font.weight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.font.weight',
          toggleClickType: ToggleClick.Close
        },
        id: 'TimePicker',
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

    // loop
    it('ArkUI_TimePicker_032', 0, async (done: Function) => {

      await Search('参数列表', 'loop')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'loop',
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('loop', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })

    it('ArkUI_TimePicker_033', 0, async (done: Function) => {

      await Search('参数列表', 'loop')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'loop',
          toggleClickType: ToggleClick.Close
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('loop', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    // dateTimeOptions.hour
    it('ArkUI_TimePicker_034', 0, async (done: Function) => {

      await Search('参数列表', 'dateTimeOptions.hour')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'dateTimeOptions.hour',
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('dateTimeOptions', JsonType.obj),
          new KeyStruct('hour', JsonType.value),
        ],
        assertEqual: '2-digit'
      })

      done();
    })

    it('ArkUI_TimePicker_035', 0, async (done: Function) => {

      await Search('参数列表', 'dateTimeOptions.hour')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'dateTimeOptions.hour',
          toggleClickType: ToggleClick.Close
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('dateTimeOptions', JsonType.obj),
          new KeyStruct('hour', JsonType.value),
        ],
        assertEqual: 'numeric'
      })

      done();
    })

    // dateTimeOptions.minute
    it('ArkUI_TimePicker_036', 0, async (done: Function) => {

      await Search('参数列表', 'dateTimeOptions.minute')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'dateTimeOptions.minute',
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('dateTimeOptions', JsonType.obj),
          new KeyStruct('minute', JsonType.value),
        ],
        assertEqual: 'numeric'
      })

      done();
    })

    it('ArkUI_TimePicker_037', 0, async (done: Function) => {

      await Search('参数列表', 'dateTimeOptions.minute')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'dateTimeOptions.minute',
          toggleClickType: ToggleClick.Close
        },
        id: 'TimePicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('dateTimeOptions', JsonType.obj),
          new KeyStruct('minute', JsonType.value),
        ],
        assertEqual: '2-digit'
      })

      done();
    })
  })
}