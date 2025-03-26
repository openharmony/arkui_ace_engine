import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import { Point } from '@ohos.UiTest';
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Search,
  searchParentBlock,
  Slide,
  sliderDrag,
  ToggleClick
} from '../../utils';
import { ListItemGroupBootcamp } from 'feature/src/main/ets/pages/ScrollAndSwipe/ListItemGroupBootcamp';

const TAG = 'AlphabetIndexerBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function AlphabetIndexerBootcampTest() {
  describe('AlphabetIndexerBootcampTest', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(5000);
        console.info(TAG + 'AlphabetIndexerBootcamp001' + ' begin');

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[6].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(4000);

        let atomDisplays: Component = await driver.findComponent(ON.text('信息展示'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('索引条/AlphabetIndexer'))
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
    /**
     * 测试组件color且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0001', 0, async (done: Function) => {
      await Search('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'color',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0002', 0, async (done: Function) => {
      await Search('参数列表', 'color')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'color',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0003', 0, async (done: Function) => {
      await Search('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'color',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0004', 0, async (done: Function) => {
      await Search('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'color',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0005', 0, async (done: Function) => {
      await Search('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'color',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0006', 0, async (done: Function) => {
      await Search('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'color',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件selectedColor且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0007', 0, async (done: Function) => {
      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'selectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0008', 0, async (done: Function) => {
      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'selectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0009', 0, async (done: Function) => {
      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'selectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0010', 0, async (done: Function) => {
      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'selectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0011', 0, async (done: Function) => {
      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'selectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0012', 0, async (done: Function) => {
      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'selectedColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件popupColor且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0013', 0, async (done: Function) => {
      await Search('参数列表', 'popupColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'popupColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0014', 0, async (done: Function) => {
      await Search('参数列表', 'popupColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'popupColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0015', 0, async (done: Function) => {
      await Search('参数列表', 'popupColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'popupColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0016', 0, async (done: Function) => {
      await Search('参数列表', 'popupColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'popupColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0017', 0, async (done: Function) => {
      await Search('参数列表', 'popupColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'popupColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0018', 0, async (done: Function) => {
      await Search('参数列表', 'popupColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'popupColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件selectedBackgroundColor且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0019', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'selectedBackgroundColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0020', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'selectedBackgroundColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0021', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'selectedBackgroundColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0022', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'selectedBackgroundColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0023', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'selectedBackgroundColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0024', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'selectedBackgroundColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件popupBackground且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0025', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackground')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'popupBackground',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackground', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0026', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackground')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'popupBackground',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackground', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0027', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackground')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'popupBackground',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackground', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0028', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackground')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'popupBackground',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackground', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0029', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackground')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'popupBackground',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackground', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0030', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackground')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'popupBackground',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackground', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件usingPopup且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0031', 0, async (done: Function) => {
      await Search('参数列表', 'usingPopup')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'usingPopup',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('usingPopup', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0032', 0, async (done: Function) => {
      await Search('参数列表', 'usingPopup')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'usingPopup',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('usingPopup', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })
    /**
     * 测试组件selectedFontSize且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0033', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontSize')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'selectedFontSize',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedFont', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: '16.00fp'

      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'selectedFontSize',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedFont', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: '4.00fp'

      })


      done();
    })
    /**
     * 测试组件selectedFontStyle且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0034', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontStyle')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'selectedFontStyle',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedFont', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value),
        ],
        assertEqual: 'FontStyle::NORMAL'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0035', 0, async (done: Function) => {

      await Search('参数列表', 'selectedFontStyle')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'selectedFontStyle',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedFont', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value),
        ],
        assertEqual: 'FontStyle::ITALIC'
      })

      done();
    })
    /**
     * 测试组件selectedFontWeight且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0036', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontWeight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'selectedFontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedFont', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Lighter"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0037', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontWeight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'selectedFontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedFont', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Normal"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0038', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontWeight')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'selectedFontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedFont', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Regular"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0039', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontWeight')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'selectedFontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedFont', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Medium"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0040', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontWeight')

      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'selectedFontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedFont', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Bold"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0041', 0, async (done: Function) => {

      await Search('参数列表', 'selectedFontWeight')

      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'selectedFontWeight',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedFont', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Bolder"
      })

      done();
    })

  })
}

