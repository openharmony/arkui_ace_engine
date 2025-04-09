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
  titleSearch,
  ToggleClick
} from '../../utils';

const TAG = 'SymbolGlyphBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function SymbolGlyphBootcampTest() {
  describe('SymbolGlyphBootcampTest', () => {
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(6000);
        console.info(TAG + 'SymbolGlyphBootcamp001' + ' begin');

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[3].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(4000);

        let atomDisplays: Component = await driver.findComponent(ON.text('文本与输入'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let ListItems1: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width3: Point = await ListItems1[0].getBoundsCenter()
        let width4: Point = await ListItems1[5].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 500)
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('SymbolGlyph'))
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
     * 测试组件fontColor1
     */
    it('ArkUI_SymbolGlyph_0001', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'fontColor1')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fontColor1',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_SymbolGlyph_0002', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor1')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fontColor1',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_SymbolGlyph_0003', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor1')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'fontColor1',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0004', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor1')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'fontColor1',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_SymbolGlyph_0005', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor1')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'fontColor1',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_SymbolGlyph_0006', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor1')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'fontColor1',
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    /**
     * 测试组件fontColor2
     */
    it('ArkUI_SymbolGlyph_0007', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'fontColor2')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fontColor2',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_SymbolGlyph_0008', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor2')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fontColor2',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_SymbolGlyph_0009', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor2')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'fontColor2',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0010', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor2')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'fontColor2',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_SymbolGlyph_0011', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor2')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'fontColor2',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_SymbolGlyph_0012', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor2')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'fontColor2',
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    /**
     * 测试组件fontColor3
     */
    it('ArkUI_SymbolGlyph_0013', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'fontColor3')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fontColor3',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_SymbolGlyph_0014', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor3')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fontColor3',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_SymbolGlyph_0015', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor3')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'fontColor3',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0016', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor3')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'fontColor3',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_SymbolGlyph_0017', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor3')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'fontColor3',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_SymbolGlyph_0018', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor3')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'fontColor3',
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    /**
     * 测试组件fontSize且获取属性正确
     */
    it('ArkUI_SymbolGlyph_0019', 0, async (done: Function) => {
      await Search('参数列表', 'fontSize')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'fontSize',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: '100.00fp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'fontSize',
          toggleClickType: ToggleClick.Close
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: '0.00fp'
      })

      done();
    })
    /**
     * 测试组件fontWeight且获取属性正确
     */
    it('ArkUI_SymbolGlyph_0020', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '100'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0021', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '200'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0022', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '300'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0023', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '400'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0024', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '500'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0025', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '600'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0026', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 6,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '700'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0027', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 7,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '800'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0028', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '900'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0029', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Lighter'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0030', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 10,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Normal'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0031', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Regular'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0032', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Medium'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0033', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 13,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Bold'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0034', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 14,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Close
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Bolder'
      })

      done();
    })
    /**
     * 测试组件renderingStrategy且获取属性正确
     */
    it('ArkUI_SymbolGlyph_0035', 0, async (done: Function) => {
      await Search('参数列表', 'renderingStrategy')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'renderingStrategy',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderingStrategy', JsonType.value),
        ],
        assertEqual: 'SymbolRenderingStrategy.SINGLE'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0036', 0, async (done: Function) => {
      await Search('参数列表', 'renderingStrategy')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'renderingStrategy',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderingStrategy', JsonType.value),
        ],
        assertEqual: 'SymbolRenderingStrategy.MULTIPLE_COLOR'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0037', 0, async (done: Function) => {
      await Search('参数列表', 'renderingStrategy')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'renderingStrategy',
          toggleClickType: ToggleClick.Close
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderingStrategy', JsonType.value),
        ],
        assertEqual: 'SymbolRenderingStrategy.MULTIPLE_OPACITY'
      })

      done();
    })
    /**
     * 测试组件effectStrategy且获取属性正确
     */
    it('ArkUI_SymbolGlyph_0038', 0, async (done: Function) => {
      await Search('参数列表', 'effectStrategy')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'effectStrategy',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('effectStrategy', JsonType.value),
        ],
        assertEqual: 'SymbolEffectStrategy.NONE'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0039', 0, async (done: Function) => {
      await Search('参数列表', 'effectStrategy')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'effectStrategy',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('effectStrategy', JsonType.value),
        ],
        assertEqual: 'SymbolEffectStrategy.SCALE'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0040', 0, async (done: Function) => {
      await Search('参数列表', 'effectStrategy')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'effectStrategy',
          toggleClickType: ToggleClick.Close
        },
        id: 'SymbolGlyph',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('effectStrategy', JsonType.value),
        ],
        assertEqual: 'SymbolEffectStrategy.HIERARCHICAL'
      })

      done();
    })
    /**
     * 测试组件symbolEffect.isActive且获取属性正确
     */
    it('ArkUI_SymbolGlyph_0041', 0, async (done: Function) => {
      await Search('参数列表', 'symbolEffect.isActive')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'symbolEffect.isActive',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph1',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('symbolEffect', JsonType.obj),
        ],
        assertEqual: '{"effectType":2,"scopeType":0,"commonSubType":0,"fillStyle":1,"isTxtActive":true,"isActive":true}'
      })

      done();
    })

    it('ArkUI_SymbolGlyph_0042', 0, async (done: Function) => {
      await Search('参数列表', 'symbolEffect.isActive')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'symbolEffect.isActive',
          toggleClickType: ToggleClick.Close
        },
        id: 'SymbolGlyph1',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('symbolEffect', JsonType.obj),
        ],
        assertEqual: '{"effectType":2,"scopeType":0,"commonSubType":0,"fillStyle":1,"isTxtActive":false,"isActive":false}'
      })

      done();
    })
    /**
     * 测试组件symbolEffect.triggerValue且获取属性正确
     */
    it('ArkUI_SymbolGlyph_0043', 0, async (done: Function) => {
      await Search('参数列表', 'symbolEffect.triggerValue')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'symbolEffect.triggerValue',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolGlyph2',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('symbolEffect', JsonType.obj),
        ],
        assertEqual: '{"effectType":7,"scopeType":1,"commonSubType":0,"fillStyle":0,"isTxtActive":false,"triggerNum":10}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'symbolEffect.triggerValue',
          toggleClickType: ToggleClick.Close
        },
        id: 'SymbolGlyph2',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('symbolEffect', JsonType.obj),
        ],
        assertEqual: '{"effectType":7,"scopeType":1,"commonSubType":0,"fillStyle":0,"isTxtActive":false,"triggerNum":-1}'
      })

      done();
    })

  })
}