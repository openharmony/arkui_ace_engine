/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

var __decorate = this && this.__decorate || function(e, t, o, i) {
  var s, n = arguments.length,
    r = n < 3 ? t : null === i ? i = Object.getOwnPropertyDescriptor(t, o) : i;
  if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) r = Reflect.decorate(e, t, o, i);
  else
    for (var c = e.length - 1; c >= 0; c--)(s = e[c]) && (r = (n < 3 ? s(r) : n > 3 ? s(t, o, r) : s(t, o)) || r);
  return n > 3 && r && Object.defineProperty(t, o, r), r
};
const KeyCode = requireNapi("multimodalInput.keyCode").KeyCode;
const MeasureText = requireNapi("measure");
const PUBLIC_MORE = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAYAAABS3GwHAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAABEZJREFUeNrt3D1rFFEUBuAxhmAhFlYpUohYiYWFRcAmKAhWK2pjo1iKf8BCMIKFf8BarCyMhVj4VZhGSKEg2FqJyCKWIhYWnstMINgYsh+cmfs88BICydxw7jmzu2HvNg0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADBN+3r6dx+LXIqsRpa7FF8j48hm5Fn3Peo9mAEYRdYjJ3f582Vj7nZfUe/eDsCRyMPI2h5/fyNyI/JDT6v3Tvt7sBllE15ETkxwjeORi5G3ke/6W737MgBnI68jh6ZwrcORq5HnhkC9+zAA5YXXy8jBKV5zKXIu8jjyS7+rd+YBeNVtyrSVO9PRyBM9r94LSTfjWuTUDK9/eYIXeENUbb0zDsBi5PYc1rmj79U74wCszuih+F/ljrSi/+uud8YBGA10rayqrnfGAVgb6FpZVV3vjAOwPNC1sqq63hkHYGWga2VVdb0XKt/8Rf1fd70zDsB4jmt5u3Tl9a59AMb6v+56ZxyArYGulVXV9c44ABtzXOup/q+73hkH4N2cHio/Rj7r/7rrnXEAfkfuz2Gddb2v3ln/DfpgxneLzaY9xE3l9c46AH8iVyI/Z3Dt8nB/Xc+rd5H5QMy3yJemPVs6zY0edc9HUe/0Z4I/dQ/N5Vjd0oTXKp9QcKFpD2qj3r0YgO1NeRM507TH6/bifeR85IMeV++d+vTBWOV9JDcjt5rdv6uw3M3uRR7pa/Xu+wBsOxA53bTnTP/3UX1b3fNQ1BsAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAKqyr6d/97HIpchqZLlL8TUyjmxGnnXfo96DGYBRZD1ycpc/XzbmbvcV9e7tAByJPIys7fH3NyI3Ij/0tHrvtL8Hm1E24UXkxATXOB65GHkb+a6/1bsvA3A28jpyaArXOhy5GnluCNS7DwNQXni9jByc4jWXIucijyO/9Lt6Zx6AV92mTFu5Mx2NPNHz6r2QdDOuRU7N8PqXJ3iBN0TV1jvjACxGbs9hnTv6Xr0zDsDqjB6K/1XuSCv6v+56ZxyA0UDXyqrqemccgLWBrpVV1fXOOADLA10rq6rrnXEAVga6VlZV13uh8s1f1P911zvjAIznuJa3S1de79oHYKz/6653xgHYGuhaWVVd74wDsDHHtZ7q/7rrnXEA3s3pofJj5LP+r7veGQfgd+T+HNZZ1/vqnfXfoA9mfLfYbNpD3FRe76wD8CdyJfJzBtcuD/fX9bx6F5kPxHyLfGnas6XT3OhR93wU9U5/JvhT99BcjtUtTXit8gkFF5r2oDbq3YsB2N6UN5EzTXu8bi/eR85HPuhx9d6pTx+MVd5HcjNyq9n9uwrL3exe5JG+Vu++D8C2A5HTTXvO9H8f1bfVPQ9FvQEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgCn7C9HjBtwWfXpKAAAAAElFTkSuQmCC";
export class TabTitleBar extends ViewPU {
  constructor(e, t, o, i = -1) {
    super(e, o, i);
    this.tabItems = void 0;
    this.menuItems = void 0;
    this.swiperContent = void 0;
    this.__tabWidth = new ObservedPropertySimplePU(0, this, "tabWidth");
    this.__currentIndex = new ObservedPropertySimplePU(0, this, "currentIndex");
    this.menuSectionWidth = 0;
    this.tabOffsets = Array();
    this.imageWidths = Array();
    this.scroller = new Scroller;
    this.swiperController = new SwiperController;
    this.settings = new RenderingContextSettings(!0);
    this.leftContext2D = new CanvasRenderingContext2D(this.settings);
    this.rightContext2D = new CanvasRenderingContext2D(this.settings);
    this.setInitiallyProvidedValue(t)
  }
  setInitiallyProvidedValue(e) {
    void 0 !== e.tabItems && (this.tabItems = e.tabItems);
    void 0 !== e.menuItems && (this.menuItems = e.menuItems);
    void 0 !== e.swiperContent && (this.swiperContent = e.swiperContent);
    void 0 !== e.tabWidth && (this.tabWidth = e.tabWidth);
    void 0 !== e.currentIndex && (this.currentIndex = e.currentIndex);
    void 0 !== e.menuSectionWidth && (this.menuSectionWidth = e.menuSectionWidth);
    void 0 !== e.tabOffsets && (this.tabOffsets = e.tabOffsets);
    void 0 !== e.imageWidths && (this.imageWidths = e.imageWidths);
    void 0 !== e.scroller && (this.scroller = e.scroller);
    void 0 !== e.swiperController && (this.swiperController = e.swiperController);
    void 0 !== e.settings && (this.settings = e.settings);
    void 0 !== e.leftContext2D && (this.leftContext2D = e.leftContext2D);
    void 0 !== e.rightContext2D && (this.rightContext2D = e.rightContext2D)
  }
  updateStateVars(e) {}
  purgeVariableDependenciesOnElmtId(e) {
    this.__tabWidth.purgeDependencyOnElmtId(e);
    this.__currentIndex.purgeDependencyOnElmtId(e)
  }
  aboutToBeDeleted() {
    this.__tabWidth.aboutToBeDeleted();
    this.__currentIndex.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }
  get tabWidth() {
    return this.__tabWidth.get()
  }
  set tabWidth(e) {
    this.__tabWidth.set(e)
  }
  get currentIndex() {
    return this.__currentIndex.get()
  }
  set currentIndex(e) {
    this.__currentIndex.set(e)
  }
  GradientMask(e, t, o, i, s, n = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.width(TabTitleBar.gradientMaskWidth);
      Column.height(TabTitleBar.totalHeight);
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((n, r) => {
      ViewStackProcessor.StartGetAccessRecordingFor(n);
      Canvas.create(e);
      Canvas.width(TabTitleBar.gradientMaskWidth);
      Canvas.height(TabTitleBar.totalHeight);
      Canvas.onReady((() => {
        var n = e.createLinearGradient(t, o, i, s);
        n.addColorStop(0, "#ffffffff");
        n.addColorStop(1, "#00ffffff");
        e.fillStyle = n;
        e.fillRect(0, 0, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight)
      }));
      r || Canvas.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Canvas.pop();
    Column.pop()
  }
  aboutToAppear() {
    this.tabItems.forEach((e => {
      this.imageWidths.push(0)
    }));
    this.loadOffsets()
  }
  loadOffsets() {
    this.tabOffsets.length = 0;
    let e = 0;
    this.tabOffsets.push(e);
    e += TabContentItem.marginFirst;
    this.tabItems.forEach(((t, o) => {
      if (void 0 !== t.icon) Math.abs(this.imageWidths[o]) > TabContentItem.imageHotZoneWidth ? e += this.imageWidths[o] : e += TabContentItem.imageHotZoneWidth;
      else {
        e += TabContentItem.paddingLeft;
        e += px2vp(MeasureText.measureText({
          textContent: t.title,
          fontSize: 18,
          fontWeight: FontWeight.Medium
        }));
        e += TabContentItem.paddingRight
      }
      this.tabOffsets.push(e)
    }))
  }
  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Flex.create({
        justifyContent: FlexAlign.SpaceBetween,
        alignItems: ItemAlign.Stretch
      });
      Flex.backgroundColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_background"],
        bundleName: "",
        moduleName: ""
      });
      Flex.margin({
        right: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_max_padding_end"],
          bundleName: "",
          moduleName: ""
        }
      });
      Flex.onAreaChange(((e, t) => {
        this.tabWidth = Number(t.width) - this.menuSectionWidth
      }));
      t || Flex.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Stack.create({
        alignContent: Alignment.End
      });
      t || Stack.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Stack.create({
        alignContent: Alignment.Start
      });
      t || Stack.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      List.create({
        initialIndex: 0,
        scroller: this.scroller,
        space: 0
      });
      List.width("100%");
      List.height(TabTitleBar.totalHeight);
      List.constraintSize({
        maxWidth: this.tabWidth
      });
      List.edgeEffect(EdgeEffect.Spring);
      List.listDirection(Axis.Horizontal);
      List.scrollBar(BarState.Off);
      t || List.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      ForEach.create();
      this.forEachUpdateFunction(e, this.tabItems, ((e, t) => {
        const o = e;
        {
          const e = !0;
          const i = (t, o) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            ListItem.create(n, e);
            o || ListItem.pop();
            ViewStackProcessor.StopGetAccessRecording()
          };
          const s = () => {
            this.observeComponentCreation(i);
            this.observeComponentCreation(((e, i) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              i ? ViewPU.create(new TabContentItem(this, {
                item: o,
                index: t,
                maxIndex: this.tabItems.length - 1,
                currentIndex: this.currentIndex,
                onCustomClick: e => this.currentIndex = e,
                onImageComplete: e => {
                  this.imageWidths[t] = px2vp(e);
                  this.loadOffsets()
                }
              }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {
                currentIndex: this.currentIndex
              });
              ViewStackProcessor.StopGetAccessRecording()
            }));
            ListItem.pop()
          };
          const n = (e, s) => {
            i(e, s);
            this.updateFuncByElmtId.set(e, i);
            this.observeComponentCreation(((e, i) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              i ? ViewPU.create(new TabContentItem(this, {
                item: o,
                index: t,
                maxIndex: this.tabItems.length - 1,
                currentIndex: this.currentIndex,
                onCustomClick: e => this.currentIndex = e,
                onImageComplete: e => {
                  this.imageWidths[t] = px2vp(e);
                  this.loadOffsets()
                }
              }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {
                currentIndex: this.currentIndex
              });
              ViewStackProcessor.StopGetAccessRecording()
            }));
            ListItem.pop()
          };
          e ? (() => {
            this.observeComponentCreation(i);
            ListItem.pop()
          })() : s()
        }
      }), void 0, !0, !1);
      t || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    ForEach.pop();
    List.pop();
    Column.pop();
    this.GradientMask.bind(this)(this.leftContext2D, 0, TabTitleBar.totalHeight / 2, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight / 2);
    Stack.pop();
    this.GradientMask.bind(this)(this.rightContext2D, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight / 2, 0, TabTitleBar.totalHeight / 2);
    Stack.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      void 0 !== this.menuItems && this.menuItems.length > 0 ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          __Common__.create();
          __Common__.height(TabTitleBar.totalHeight);
          __Common__.onAreaChange(((e, t) => {
            this.menuSectionWidth = Number(t.width)
          }));
          t || __Common__.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          t ? ViewPU.create(new CollapsibleMenuSection(this, {
            menuItems: this.menuItems,
            index: 1 + TabTitleBar.instanceCount++
          }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
          ViewStackProcessor.StopGetAccessRecording()
        }));
        __Common__.pop()
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    Flex.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Swiper.create(this.swiperController);
      Swiper.index(this.currentIndex);
      Swiper.itemSpace(0);
      Swiper.indicator(!1);
      Swiper.width("100%");
      Swiper.height("100%");
      Swiper.curve(Curve.Friction);
      Swiper.onChange((e => {
        const t = this.tabOffsets[e] + TabTitleBar.correctionOffset;
        this.currentIndex = e;
        this.scroller.scrollTo({
          xOffset: t > 0 ? t : 0,
          yOffset: 0,
          animation: {
            duration: 300,
            curve: Curve.EaseInOut
          }
        })
      }));
      Swiper.onAppear((() => {
        this.scroller.scrollToIndex(this.currentIndex);
        this.scroller.scrollBy(TabTitleBar.correctionOffset, 0)
      }));
      t || Swiper.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.swiperContent.bind(this)();
    Swiper.pop();
    Column.pop();
    Column.pop()
  }
  rerender() {
    this.updateDirtyElements()
  }
}
TabTitleBar.totalHeight = 56;
TabTitleBar.correctionOffset = -40;
TabTitleBar.gradientMaskWidth = 24;
TabTitleBar.instanceCount = 0;
__decorate([], TabTitleBar.prototype, "GradientMask", null);
class CollapsibleMenuSection extends ViewPU {
  constructor(e, t, o, i = -1) {
    super(e, o, i);
    this.menuItems = void 0;
    this.index = void 0;
    this.firstFocusableIndex = -1;
    this.__isPopupShown = new ObservedPropertySimplePU(!1, this, "isPopupShown");
    this.__isMoreIconOnFocus = new ObservedPropertySimplePU(!1, this, "isMoreIconOnFocus");
    this.__isMoreIconOnHover = new ObservedPropertySimplePU(!1, this, "isMoreIconOnHover");
    this.__isMoreIconOnClick = new ObservedPropertySimplePU(!1, this, "isMoreIconOnClick");
    this.setInitiallyProvidedValue(t)
  }
  setInitiallyProvidedValue(e) {
    void 0 !== e.menuItems && (this.menuItems = e.menuItems);
    void 0 !== e.index && (this.index = e.index);
    void 0 !== e.firstFocusableIndex && (this.firstFocusableIndex = e.firstFocusableIndex);
    void 0 !== e.isPopupShown && (this.isPopupShown = e.isPopupShown);
    void 0 !== e.isMoreIconOnFocus && (this.isMoreIconOnFocus = e.isMoreIconOnFocus);
    void 0 !== e.isMoreIconOnHover && (this.isMoreIconOnHover = e.isMoreIconOnHover);
    void 0 !== e.isMoreIconOnClick && (this.isMoreIconOnClick = e.isMoreIconOnClick)
  }
  updateStateVars(e) {}
  purgeVariableDependenciesOnElmtId(e) {
    this.__isPopupShown.purgeDependencyOnElmtId(e);
    this.__isMoreIconOnFocus.purgeDependencyOnElmtId(e);
    this.__isMoreIconOnHover.purgeDependencyOnElmtId(e);
    this.__isMoreIconOnClick.purgeDependencyOnElmtId(e)
  }
  aboutToBeDeleted() {
    this.__isPopupShown.aboutToBeDeleted();
    this.__isMoreIconOnFocus.aboutToBeDeleted();
    this.__isMoreIconOnHover.aboutToBeDeleted();
    this.__isMoreIconOnClick.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }
  get isPopupShown() {
    return this.__isPopupShown.get()
  }
  set isPopupShown(e) {
    this.__isPopupShown.set(e)
  }
  get isMoreIconOnFocus() {
    return this.__isMoreIconOnFocus.get()
  }
  set isMoreIconOnFocus(e) {
    this.__isMoreIconOnFocus.set(e)
  }
  get isMoreIconOnHover() {
    return this.__isMoreIconOnHover.get()
  }
  set isMoreIconOnHover(e) {
    this.__isMoreIconOnHover.set(e)
  }
  get isMoreIconOnClick() {
    return this.__isMoreIconOnClick.get()
  }
  set isMoreIconOnClick(e) {
    this.__isMoreIconOnClick.set(e)
  }
  getMoreIconFgColor() {
    return this.isMoreIconOnClick ? {
      id: -1,
      type: 10001,
      params: ["sys.color.ohos_id_color_titlebar_icon_pressed"],
      bundleName: "",
      moduleName: ""
    } : {
      id: -1,
      type: 10001,
      params: ["sys.color.ohos_id_color_titlebar_icon"],
      bundleName: "",
      moduleName: ""
    }
  }
  getMoreIconBgColor() {
    return this.isMoreIconOnClick ? {
      id: -1,
      type: 10001,
      params: ["sys.color.ohos_id_color_click_effect"],
      bundleName: "",
      moduleName: ""
    } : this.isMoreIconOnHover ? {
      id: -1,
      type: 10001,
      params: ["sys.color.ohos_id_color_hover"],
      bundleName: "",
      moduleName: ""
    } : Color.Transparent
  }
  aboutToAppear() {
    this.menuItems.forEach(((e, t) => {
      e.isEnabled && -1 == this.firstFocusableIndex && t > CollapsibleMenuSection.maxCountOfVisibleItems - 2 && (this.firstFocusableIndex = 1e3 * this.index + t + 1)
    }))
  }
  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.height("100%");
      Column.justifyContent(FlexAlign.Center);
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          ForEach.create();
          this.forEachUpdateFunction(e, this.menuItems, ((e, t) => {
            const o = e;
            this.observeComponentCreation(((e, i) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              i ? ViewPU.create(new ImageMenuItem(this, {
                item: o,
                index: 1e3 * this.index + t + 1
              }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
              ViewStackProcessor.StopGetAccessRecording()
            }))
          }), void 0, !0, !1);
          t || ForEach.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        ForEach.pop()
      })) : this.ifElseBranchUpdateFunction(1, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          ForEach.create();
          this.forEachUpdateFunction(e, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), ((e, t) => {
            const o = e;
            this.observeComponentCreation(((e, i) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              i ? ViewPU.create(new ImageMenuItem(this, {
                item: o,
                index: 1e3 * this.index + t + 1
              }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
              ViewStackProcessor.StopGetAccessRecording()
            }))
          }), void 0, !0, !1);
          t || ForEach.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        ForEach.pop();
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Row.width(ImageMenuItem.imageHotZoneWidth);
          Row.height(ImageMenuItem.imageHotZoneWidth);
          Row.borderRadius(ImageMenuItem.buttonBorderRadius);
          Row.foregroundColor(this.getMoreIconFgColor());
          Row.backgroundColor(this.getMoreIconBgColor());
          Row.justifyContent(FlexAlign.Center);
          ViewStackProcessor.visualState("focused");
          Row.border({
            radius: {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_corner_radius_clicked"],
              bundleName: "",
              moduleName: ""
            },
            width: ImageMenuItem.focusBorderWidth,
            color: {
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_focused_outline"],
              bundleName: "",
              moduleName: ""
            },
            style: BorderStyle.Solid
          });
          ViewStackProcessor.visualState("normal");
          Row.border({
            radius: {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_corner_radius_clicked"],
              bundleName: "",
              moduleName: ""
            },
            width: 0
          });
          ViewStackProcessor.visualState();
          Row.onFocus((() => this.isMoreIconOnFocus = !0));
          Row.onBlur((() => this.isMoreIconOnFocus = !1));
          Row.onHover((e => this.isMoreIconOnHover = e));
          Row.onKeyEvent((e => {
            if (e.keyCode === KeyCode.KEYCODE_ENTER || e.keyCode === KeyCode.KEYCODE_SPACE) {
              e.type === KeyType.Down && (this.isMoreIconOnClick = !0);
              e.type === KeyType.Up && (this.isMoreIconOnClick = !1)
            }
          }));
          Row.onTouch((e => {
            e.type === TouchType.Down && (this.isMoreIconOnClick = !0);
            e.type === TouchType.Up && (this.isMoreIconOnClick = !1)
          }));
          Row.onClick((() => this.isPopupShown = !0));
          Row.bindPopup(this.isPopupShown, {
            builder: {
              builder: this.popupBuilder.bind(this)
            },
            placement: Placement.Bottom,
            popupColor: Color.White,
            enableArrow: !1,
            onStateChange: e => {
              this.isPopupShown = e.isVisible;
              e.isVisible || (this.isMoreIconOnClick = !1)
            }
          });
          t || Row.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Image.create(PUBLIC_MORE);
          Image.width(ImageMenuItem.imageSize);
          Image.height(ImageMenuItem.imageSize);
          Image.focusable(!0);
          t || Image.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Row.pop()
      }));
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    Row.pop();
    Column.pop()
  }
  popupBuilder(e = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
      Column.margin({
        top: CollapsibleMenuSection.focusPadding,
        bottom: CollapsibleMenuSection.focusPadding
      });
      Column.onAppear((() => {
        focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex)
      }));
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      ForEach.create();
      this.forEachUpdateFunction(e, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), ((e, t) => {
        const o = e;
        this.observeComponentCreation(((e, i) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          i ? ViewPU.create(new ImageMenuItem(this, {
            item: o,
            index: 1e3 * this.index + CollapsibleMenuSection.maxCountOfVisibleItems + t
          }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
          ViewStackProcessor.StopGetAccessRecording()
        }))
      }), void 0, !0, !1);
      t || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    ForEach.pop();
    Column.pop()
  }
  rerender() {
    this.updateDirtyElements()
  }
}
CollapsibleMenuSection.maxCountOfVisibleItems = 1;
CollapsibleMenuSection.focusPadding = 4;
CollapsibleMenuSection.marginsNum = 2;
__decorate([], CollapsibleMenuSection.prototype, "popupBuilder", null);
class TabContentItem extends ViewPU {
  constructor(e, t, o, i = -1) {
    super(e, o, i);
    this.item = void 0;
    this.index = void 0;
    this.maxIndex = void 0;
    this.onCustomClick = void 0;
    this.onImageComplete = void 0;
    this.__currentIndex = new SynchedPropertySimpleOneWayPU(t.currentIndex, this, "currentIndex");
    this.__isOnFocus = new ObservedPropertySimplePU(!1, this, "isOnFocus");
    this.__isOnHover = new ObservedPropertySimplePU(!1, this, "isOnHover");
    this.__isOnClick = new ObservedPropertySimplePU(!1, this, "isOnClick");
    this.__tabWidth = new ObservedPropertySimplePU(0, this, "tabWidth");
    this.setInitiallyProvidedValue(t)
  }
  setInitiallyProvidedValue(e) {
    void 0 !== e.item && (this.item = e.item);
    void 0 !== e.index && (this.index = e.index);
    void 0 !== e.maxIndex && (this.maxIndex = e.maxIndex);
    void 0 !== e.onCustomClick && (this.onCustomClick = e.onCustomClick);
    void 0 !== e.onImageComplete && (this.onImageComplete = e.onImageComplete);
    void 0 !== e.isOnFocus && (this.isOnFocus = e.isOnFocus);
    void 0 !== e.isOnHover && (this.isOnHover = e.isOnHover);
    void 0 !== e.isOnClick && (this.isOnClick = e.isOnClick);
    void 0 !== e.tabWidth && (this.tabWidth = e.tabWidth)
  }
  updateStateVars(e) {
    this.__currentIndex.reset(e.currentIndex)
  }
  purgeVariableDependenciesOnElmtId(e) {
    this.__currentIndex.purgeDependencyOnElmtId(e);
    this.__isOnFocus.purgeDependencyOnElmtId(e);
    this.__isOnHover.purgeDependencyOnElmtId(e);
    this.__isOnClick.purgeDependencyOnElmtId(e);
    this.__tabWidth.purgeDependencyOnElmtId(e)
  }
  aboutToBeDeleted() {
    this.__currentIndex.aboutToBeDeleted();
    this.__isOnFocus.aboutToBeDeleted();
    this.__isOnHover.aboutToBeDeleted();
    this.__isOnClick.aboutToBeDeleted();
    this.__tabWidth.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }
  get currentIndex() {
    return this.__currentIndex.get()
  }
  set currentIndex(e) {
    this.__currentIndex.set(e)
  }
  get isOnFocus() {
    return this.__isOnFocus.get()
  }
  set isOnFocus(e) {
    this.__isOnFocus.set(e)
  }
  get isOnHover() {
    return this.__isOnHover.get()
  }
  set isOnHover(e) {
    this.__isOnHover.set(e)
  }
  get isOnClick() {
    return this.__isOnClick.get()
  }
  set isOnClick(e) {
    this.__isOnClick.set(e)
  }
  get tabWidth() {
    return this.__tabWidth.get()
  }
  set tabWidth(e) {
    this.__tabWidth.set(e)
  }
  getBgColor() {
    return this.isOnClick ? {
      id: -1,
      type: 10001,
      params: ["sys.color.ohos_id_color_click_effect"],
      bundleName: "",
      moduleName: ""
    } : this.isOnHover ? {
      id: -1,
      type: 10001,
      params: ["sys.color.ohos_id_color_hover"],
      bundleName: "",
      moduleName: ""
    } : Color.Transparent
  }
  getBorderAttr() {
    return this.isOnFocus ? {
      radius: {
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_corner_radius_clicked"],
        bundleName: "",
        moduleName: ""
      },
      width: TabContentItem.focusBorderWidth,
      color: {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_focused_outline"],
        bundleName: "",
        moduleName: ""
      },
      style: BorderStyle.Solid
    } : {
      width: 0
    }
  }
  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Stack.create();
      Stack.margin({
        left: 0 === this.index ? TabContentItem.marginFirst : 0,
        right: this.index === this.maxIndex ? 12 : 0
      });
      t || Stack.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.height(TabTitleBar.totalHeight);
      Row.alignItems(VerticalAlign.Center);
      Row.justifyContent(FlexAlign.Center);
      Row.borderRadius(TabContentItem.buttonBorderRadius);
      Row.backgroundColor(this.getBgColor());
      Row.onAreaChange(((e, t) => {
        this.tabWidth = Number(t.width)
      }));
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.justifyContent(FlexAlign.Center);
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      void 0 === this.item.icon ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.item.title);
          Context.animation({
            duration: 300
          });
          Text.fontSize(this.index === this.currentIndex ? {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_headline7"],
            bundleName: "",
            moduleName: ""
          } : {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_headline9"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontColor(this.index === this.currentIndex ? {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_titlebar_text"],
            bundleName: "",
            moduleName: ""
          } : {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_titlebar_text_off"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontWeight(FontWeight.Medium);
          Text.focusable(!0);
          Context.animation(null);
          Text.padding({
            top: this.index === this.currentIndex ? 6 : 10,
            left: TabContentItem.paddingLeft,
            bottom: 2,
            right: TabContentItem.paddingRight
          });
          Text.onFocus((() => this.isOnFocus = !0));
          Text.onBlur((() => this.isOnFocus = !1));
          Text.onHover((e => this.isOnHover = e));
          Text.onKeyEvent((e => {
            if (e.keyCode === KeyCode.KEYCODE_ENTER || e.keyCode === KeyCode.KEYCODE_SPACE) {
              e.type === KeyType.Down && (this.isOnClick = !0);
              e.type === KeyType.Up && (this.isOnClick = !1)
            }
          }));
          Text.onTouch((e => {
            e.type === TouchType.Down && (this.isOnClick = !0);
            e.type === TouchType.Up && (this.isOnClick = !1)
          }));
          Text.onClick((() => this.onCustomClick && this.onCustomClick(this.index)));
          t || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop()
      })) : this.ifElseBranchUpdateFunction(1, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Context.animation({
            duration: 300
          });
          Row.constraintSize({
            minWidth: TabContentItem.imageHotZoneWidth,
            minHeight: TabContentItem.imageHotZoneWidth
          });
          Row.scale({
            x: this.index === this.currentIndex ? TabContentItem.imageMagnificationFactor : 1,
            y: this.index === this.currentIndex ? TabContentItem.imageMagnificationFactor : 1
          });
          Context.animation(null);
          Row.justifyContent(FlexAlign.Center);
          Row.onFocus((() => this.isOnFocus = !0));
          Row.onBlur((() => this.isOnFocus = !1));
          Row.onHover((e => this.isOnHover = e));
          Row.onKeyEvent((e => {
            if (e.keyCode === KeyCode.KEYCODE_ENTER || e.keyCode === KeyCode.KEYCODE_SPACE) {
              e.type === KeyType.Down && (this.isOnClick = !0);
              e.type === KeyType.Up && (this.isOnClick = !1)
            }
          }));
          Row.onTouch((e => {
            e.type === TouchType.Down && (this.isOnClick = !0);
            e.type === TouchType.Up && (this.isOnClick = !1)
          }));
          Row.onClick((() => this.onCustomClick && this.onCustomClick(this.index)));
          t || Row.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Image.create(this.item.icon);
          Image.alt(this.item.title);
          Image.height(TabContentItem.imageSize);
          Image.objectFit(ImageFit.ScaleDown);
          Image.focusable(!0);
          Image.onComplete((e => {
            this.onImageComplete && this.onImageComplete(e.componentWidth)
          }));
          Image.onError((e => {
            this.onImageComplete && this.onImageComplete(e.componentWidth)
          }));
          t || Image.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Row.pop()
      }));
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    Column.pop();
    Row.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.isOnFocus && this.tabWidth > 0 ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Row.width(this.tabWidth);
          Row.height(TabTitleBar.totalHeight);
          Row.hitTestBehavior(HitTestMode.None);
          Row.borderRadius(TabContentItem.buttonBorderRadius);
          Row.border(this.getBorderAttr());
          t || Row.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Row.pop()
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    Stack.pop()
  }
  rerender() {
    this.updateDirtyElements()
  }
}
TabContentItem.imageSize = 24;
TabContentItem.imageHotZoneWidth = 48;
TabContentItem.imageMagnificationFactor = 1.4;
TabContentItem.buttonBorderRadius = 8;
TabContentItem.focusBorderWidth = 2;
TabContentItem.paddingLeft = 8;
TabContentItem.paddingRight = 8;
TabContentItem.marginFirst = 16;
class ImageMenuItem extends ViewPU {
  constructor(e, t, o, i = -1) {
    super(e, o, i);
    this.item = void 0;
    this.index = void 0;
    this.__isOnFocus = new ObservedPropertySimplePU(!1, this, "isOnFocus");
    this.__isOnHover = new ObservedPropertySimplePU(!1, this, "isOnHover");
    this.__isOnClick = new ObservedPropertySimplePU(!1, this, "isOnClick");
    this.setInitiallyProvidedValue(t)
  }
  setInitiallyProvidedValue(e) {
    void 0 !== e.item && (this.item = e.item);
    void 0 !== e.index && (this.index = e.index);
    void 0 !== e.isOnFocus && (this.isOnFocus = e.isOnFocus);
    void 0 !== e.isOnHover && (this.isOnHover = e.isOnHover);
    void 0 !== e.isOnClick && (this.isOnClick = e.isOnClick)
  }
  updateStateVars(e) {}
  purgeVariableDependenciesOnElmtId(e) {
    this.__isOnFocus.purgeDependencyOnElmtId(e);
    this.__isOnHover.purgeDependencyOnElmtId(e);
    this.__isOnClick.purgeDependencyOnElmtId(e)
  }
  aboutToBeDeleted() {
    this.__isOnFocus.aboutToBeDeleted();
    this.__isOnHover.aboutToBeDeleted();
    this.__isOnClick.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }
  get isOnFocus() {
    return this.__isOnFocus.get()
  }
  set isOnFocus(e) {
    this.__isOnFocus.set(e)
  }
  get isOnHover() {
    return this.__isOnHover.get()
  }
  set isOnHover(e) {
    this.__isOnHover.set(e)
  }
  get isOnClick() {
    return this.__isOnClick.get()
  }
  set isOnClick(e) {
    this.__isOnClick.set(e)
  }
  getFgColor() {
    return this.isOnClick ? {
      id: -1,
      type: 10001,
      params: ["sys.color.ohos_id_color_titlebar_icon_pressed"],
      bundleName: "",
      moduleName: ""
    } : {
      id: -1,
      type: 10001,
      params: ["sys.color.ohos_id_color_titlebar_icon"],
      bundleName: "",
      moduleName: ""
    }
  }
  getBgColor() {
    return this.isOnClick ? {
      id: -1,
      type: 10001,
      params: ["sys.color.ohos_id_color_click_effect"],
      bundleName: "",
      moduleName: ""
    } : this.isOnHover ? {
      id: -1,
      type: 10001,
      params: ["sys.color.ohos_id_color_hover"],
      bundleName: "",
      moduleName: ""
    } : Color.Transparent
  }
  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.width(ImageMenuItem.imageHotZoneWidth);
      Row.height(ImageMenuItem.imageHotZoneWidth);
      Row.borderRadius(ImageMenuItem.buttonBorderRadius);
      Row.foregroundColor(this.getFgColor());
      Row.backgroundColor(this.getBgColor());
      Row.justifyContent(FlexAlign.Center);
      Row.opacity(this.item.isEnabled ? 1 : ImageMenuItem.disabledImageOpacity);
      ViewStackProcessor.visualState("focused");
      Row.border({
        radius: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_corner_radius_clicked"],
          bundleName: "",
          moduleName: ""
        },
        width: ImageMenuItem.focusBorderWidth,
        color: {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_focused_outline"],
          bundleName: "",
          moduleName: ""
        },
        style: BorderStyle.Solid
      });
      ViewStackProcessor.visualState("normal");
      Row.border({
        radius: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_corner_radius_clicked"],
          bundleName: "",
          moduleName: ""
        },
        width: 0
      });
      ViewStackProcessor.visualState();
      Row.onFocus((() => {
        this.item.isEnabled && (this.isOnFocus = !0)
      }));
      Row.onBlur((() => this.isOnFocus = !1));
      Row.onHover((e => {
        this.item.isEnabled && (this.isOnHover = e)
      }));
      Row.onKeyEvent((e => {
        if (this.item.isEnabled && (e.keyCode === KeyCode.KEYCODE_ENTER || e.keyCode === KeyCode.KEYCODE_SPACE)) {
          e.type === KeyType.Down && (this.isOnClick = !0);
          e.type === KeyType.Up && (this.isOnClick = !1)
        }
      }));
      Row.onTouch((e => {
        if (this.item.isEnabled) {
          e.type === TouchType.Down && (this.isOnClick = !0);
          e.type === TouchType.Up && (this.isOnClick = !1)
        }
      }));
      Row.onClick((() => this.item.isEnabled && this.item.action && this.item.action()));
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Image.create(this.item.value);
      Image.width(ImageMenuItem.imageSize);
      Image.height(ImageMenuItem.imageSize);
      Image.focusable(this.item.isEnabled);
      Image.key(ImageMenuItem.focusablePrefix + this.index);
      t || Image.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Row.pop()
  }
  rerender() {
    this.updateDirtyElements()
  }
}
ImageMenuItem.imageSize = 24;
ImageMenuItem.imageHotZoneWidth = 48;
ImageMenuItem.buttonBorderRadius = 8;
ImageMenuItem.focusBorderWidth = 2;
ImageMenuItem.disabledImageOpacity = .4;
ImageMenuItem.focusablePrefix = "Id-TabTitleBar-ImageMenuItem-";
export default {
  TabTitleBar: TabTitleBar
};