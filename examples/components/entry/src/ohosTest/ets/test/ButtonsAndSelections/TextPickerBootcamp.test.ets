import { describe, beforeAll, afterEach, it } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import { buttonClick,
  getToggle,
  JsonType, KeyStruct, radioClick,
  Search,
  searchParentBlock,
  searchToggle,
  Slide, sliderDrag,
  titleSearch,
  ToggleClick } from '../../utils';
import { Point } from '@ohos.UiTest';

const TAG = 'TextPickerBootcamp'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function TextPickerBootcampTest() {

  describe('TextPickerBootcampTest', () => {

    beforeAll(async (done: Function) => {
      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(8000);
        console.info(TAG + 'TextPickerBootcamp' + ' begin');

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

        let scrollSearch: Component = await driver.findComponent(ON.text('文本选择器/TextPicker'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })

    // selected
    it('ArkUI_TextPicker_001', 0, async (done: Function) => {

      await Search('参数列表', 'selected')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'selected',
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selected', JsonType.value),
        ],
        assertEqual: '0'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'selected',
          toggleClickType: ToggleClick.Close,
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selected', JsonType.value),
        ],
        assertEqual: '0'
      })

      done();
    })

    // defaultPickerItemHeight
    it('ArkUI_TextPicker_002', 0, async (done: Function) => {

      await Search('参数列表', 'defaultPickerItemHeight')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'defaultPickerItemHeight',
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('defaultPickerItemHeight', JsonType.value),
        ],
        assertEqual: '80.00fp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'defaultPickerItemHeight',
          toggleClickType: ToggleClick.Close,
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('defaultPickerItemHeight', JsonType.value),
        ],
        assertEqual: '20.00fp'
      })

      done();
    })

    // disappearTextStyle.color
    it('ArkUI_TextPicker_003', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_TextPicker_004', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_TextPicker_005', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_TextPicker_006', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_TextPicker_007', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_TextPicker_008', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.color')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.color',
          toggleClickType: ToggleClick.Close
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // disappearTextStyle.font.size
    it('ArkUI_TextPicker_009', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.font.size')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.font.size',
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('size', JsonType.value),
        ],
        assertEqual: '30.00fp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.font.size',
          toggleClickType: ToggleClick.Close,
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('size', JsonType.value),
        ],
        assertEqual: '10.00fp'
      })

      done();
    })

    // disappearTextStyle.font.weight
    it('ArkUI_TextPicker_010', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.font.weight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.font.weight'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Medium'
      })

      done();
    })

    it('ArkUI_TextPicker_011', 0, async (done: Function) => {

      await Search('参数列表', 'disappearTextStyle.font.weight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'disappearTextStyle.font.weight',
          toggleClickType: ToggleClick.Close
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disappearTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Regular'
      })

      done();
    })

    // textStyle.color
    it('ArkUI_TextPicker_012', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_TextPicker_013', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_TextPicker_014', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_TextPicker_015', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_TextPicker_016', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'textStyle.color'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_TextPicker_017', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.color')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'textStyle.color',
          toggleClickType: ToggleClick.Close
        },
        id: 'TextPicker',
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
    it('ArkUI_TextPicker_018', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.size')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'textStyle.font.size',
        },
        id: 'TextPicker',
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
        id: 'TextPicker',
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
    it('ArkUI_TextPicker_019', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.weight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'textStyle.font.weight'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Medium'
      })

      done();
    })

    it('ArkUI_TextPicker_020', 0, async (done: Function) => {

      await Search('参数列表', 'textStyle.font.weight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'textStyle.font.weight',
          toggleClickType: ToggleClick.Close
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value),

        ],
        assertEqual: 'FontWeight.Regular'
      })

      done();
    })

    // selectedTextStyle.color
    it('ArkUI_TextPicker_021', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_TextPicker_022', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_TextPicker_023', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_TextPicker_024', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_TextPicker_025', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_TextPicker_026', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.color')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.color',
          toggleClickType: ToggleClick.Close
        },
        id: 'TextPicker',
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
    it('ArkUI_TextPicker_027', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.font.size')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.font.size',
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('size', JsonType.value),
        ],
        assertEqual: '30.00fp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.font.size',
          toggleClickType: ToggleClick.Close,
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('size', JsonType.value),
        ],
        assertEqual: '10.00fp'
      })

      done();
    })

    // selectedTextStyle.font.weight
    it('ArkUI_TextPicker_028', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.font.weight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.font.weight'
        },
        id: 'TextPicker',
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

    it('ArkUI_TextPicker_029', 0, async (done: Function) => {

      await Search('参数列表', 'selectedTextStyle.font.weight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'selectedTextStyle.font.weight',
          toggleClickType: ToggleClick.Close
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedTextStyle', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('weight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Medium'
      })

      done();
    })

    // selectedIndex
    it('ArkUI_TextPicker_030', 0, async (done: Function) => {
      // 获取不到属性值
      await Search('参数列表', 'selectedIndex')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'selectedIndex',
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'selectedIndex',
          toggleClickType: ToggleClick.Close,
        }
      })

      done();
    })

    // canLoop
    it('ArkUI_TextPicker_031', 0, async (done: Function) => {

      await Search('参数列表', 'canLoop')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'canLoop'
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('canLoop', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })

    it('ArkUI_TextPicker_032', 0, async (done: Function) => {

      await Search('参数列表', 'canLoop')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'canLoop',
          toggleClickType: ToggleClick.Close
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('canLoop', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    // divider.strokeWidth
    it('ArkUI_TextPicker_033', 0, async (done: Function) => {

      await Search('参数列表', 'divider.strokeWidth')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'divider.strokeWidth',
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('strokeWidth', JsonType.value),
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'divider.strokeWidth',
          toggleClickType: ToggleClick.Close,
        },
        id: 'TextPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('strokeWidth', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
  })
}