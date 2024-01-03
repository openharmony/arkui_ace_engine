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

const KeyCode = requireNapi("multimodalInput.keyCode").KeyCode;
export var EditableLeftIconType;
! function(e) {
  e[e.Back = 0] = "Back";
  e[e.Cancel = 1] = "Cancel"
}(EditableLeftIconType || (EditableLeftIconType = {}));
const PUBLIC_CANCEL = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAYAAABS3GwHAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAABKpJREFUeNrt3bFrlHccx/Ff4o2dgkOQ4JzR4SYJgksnbYcGOrTQsUPtpE4d/RNcFBeFlg7NUlTSTrXQQgsKGV0KHTs4ODiJSL8PdxaUGJK7pPc893m94TvleZLnnt/7fcc9z5FrDQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAnDQrPTuej2u2a87VvKp5XLNT87OlGiSf1lx6Zz2/q3kkgLdZr7k5lX8/7tZ8XfOCU4OgW887U/n341bN9T6s56menLAfaj464OfdM8iF6XYv+dV7+X+pOX/ANuOatZqHAmjti5prh9jurAgGI//mIbbtIvi15u9FHvBqD07a50fYdqtmt+YDrg1a/jd8tuiD7kMA4yNuL4LlkH+WtV/KAEYz7COC4cs/69ovXQB7M+4ngmHLP8/aL1UAD+bYVwTDlX/etT8W+nAV6M82uQS6PuP+rg4NV/5vBNDa6za5HLY9xzO5CIYl/9OaT5obYf/xrE1uioggQ/6LNf/04QGd6tHJFQH5owMQAfnjAxAB+eMDEAH54wMQAfnjAxAB+eMDEAH54wMQAfnjAxAB+eMDEAH54wMQAfnjAxAB+eMDEAH54wMQAfnjAxAB+eMDEAH54wMQAfnjAxAB+eMDEAH54wMQAfnjAxAB+eMDSI6A/AKIjYD8AoiNgPwCiI2A/AKIjYD8AoiNgPwCiI2A/AKIjYD8AoiNgPwCiI2A/AKIjYD8AoiNgPwCiI2A/AKIjYD8AoiNgPwCiI2A/AKIjYD8AoiNgPwCiI2A/AKIjYD8AoiNgPwCiI1gjfyLY8UpmJnNqbjrc/yO32pOk98rQPIrwWnyCyA5AvILQATkF4AIyC8AEZBfACIgvwBEQH4BiID8J8qqU3BiPJ8O+XuMO8Eng8/2CID85BcA+ckvAPKT35tg8h+n/KP2/3/2SADojfzf1+yKYH7cBxim/N39hWX8RnsBkP9Q8r9BBAKIlV8EAoiXXwQCiJdfBAKIl18EAoiXXwQz4D5A/+Tv2KjZmuPvdfu6T+AVYJDyd3Qfo17Gb7QXAPkPzTMRCCBVfhEIIF5+EQggXn4RCCBefhEIIF5+EQggXn4RCCBefhEIIF5+EQggXn4RCCBefhEIIF5+EQggXn4RCCBefhEIIF5+EQggXn4RCCBefhEIwD+qFUFuAOQXQWwA5BdBbADkF0FsAOQXQWwA5BdBbADkF0FsAOQXQWwA5BdBbADkF0FsAOQXQWwA5BdBbADkF0FsAOQXQWwA5BdBbADkF0FsAOQXQWwA5BdBbADkF0FsAOQXQWwA5BdBdAD3a8bkj4rgTM2PAmjty5or5I+L4FzNHzV/LfKB9OGb4rfJP0iO49xvL/pB9CGAMfljIxgLoLUR+WMjGAmgtT3yx0awJ4DWdsgfG8HOog+6D1eBntR8WLNB/sFzlKtDnfw3BNDa65rfp2+I3hfBo5rL5B9UBFttcoNzP35qk8vfLxZ9sCs9OnHdG6Kvps8e3TXiVzWPp88Ut3k1OLr1vFpz6Z31/LbmntMDAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEAO/wLvsR65mx80NAAAAABJRU5ErkJggg==";
const PUBLIC_OK = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAYAAABS3GwHAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAA+lJREFUeNrt3bFrFgccx+GLlSDi4JDBITiJZHBwEBGRIoqKoIu6iVMd3OosCg6W0sm/wEFUDDgpCDoIDoqOKqIoHUrp4CDFoUMRB39HLotoeXMpMXff54EfFE0ivv1+kpQGrmkAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAIBJTHkJGIhddT/V7ajbUPey7l7dlbpPAmCs1tb9Wne2++cvPa07Vfd7nw/+g9eXVT7+m3Wn69Z8421m6w7WXa37KADGNv4TE7ztTN36uvtL/UPWeJ0Z+PgXnejzBwmAMYx/8VuhTQIgcfy9CYCxjP9D3TsBkPqZf95XAFLH3372vyAAEsf/T93Ruvd93tn/CWbo4z9c96jvBxAAseMXANHjFwDR4xcA0eMXANHjFwDR4xcA0eMXANHjFwDR4xcA0eMXANHjFwDR4xcA0eMXANHjFwDR4xcA0eMXANHjFwDR4xcA0eMXANHjFwDR4xcA0eMXANHjFwDR4xcA0eMXANHjFwDR4xcA0eP/HgG0z3f9uVl45uu2ZuGBBu3zXn9rej7mEuMfSgDtA46v1c195ff+rbtU94stGv9KWqnHpLaPsXxSt/k//iXsq9vY9HjUJca/2gNoH2e/c4K32yUC4x9bAOvqrjeTP41GBMY/qgC2151Z4vuIwPhXxEo8I2xdz/c7W3fZXo1/6F8B/q471/N9fSUw/sEH8LEb8hYRGH9iAK3HdafrpkVg/IkBtA8yflt3bBn/3SEC4x9sAK3Xda9EYPypAYjA+OMDEIHxxwcgAuOPD0AExh8fgAiMPz4AERh/fAAiMP74AERg/PEBiMD44wMQgfHHByAC448PQATGHx+ACIw/PgARGH98AMkRGL8AYiMwfgHERmD8AoiNwPgFEBuB8QsgNgLjF0BsBMYvgNgIjF8AsREYvwBiIzB+AcRGYPwCiI3A+AUQG4HxCyA2AuMXQGwExi+A2AiMXwCxERi/AGIjMH4BjDaCTXUP6j59423aJ2PeMH4BjDWCHd24n9f9+cXvHa+7U7fb+Fe/qeC/ezvU+e5bleX40A11pm6u+xapMX5fARK+Eix+u7O1brbp/1Bw4xfAoCP4Pxi/AGIjMH4BxEZg/AKIjcD4BRAbgfELIDYC4xdAbATGL4DYCIxfAIOL4EXdkbrpZX6sd3WH6p56WQUwJG/qbtX92Cz8EFwfD+sO1L31cq4uU16CibU/M3Sy7nzdlgnf51ndxbrbXj4BjCmEPXX76/Y2Cz8DNNP9+l91f3Sf8e92AQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAzKZwK1uX4kZ6mnAAAAAElFTkSuQmCC";
const PUBLIC_BACK = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAYAAABS3GwHAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAA8VJREFUeNrt3LFLlHEYwPFXz0GiIZpEoikkwsFRIiK3gqCigxIC/4Kmhv6OoChouaGoqKCgCKducGh0cDAIamhwiCaHCIeelztpUszee/vl8/nAM3Vd8nufr+fddVYVAAAAAAAAAAAAAAAAAAAAAABQijFH0KhrMd2Y2ZitmNWYRzHLjkYAB9lUzMOYizv8eS/mZsymoypLxxE0svzvY07vcpu5mOmY145LAAdx+U/u4bZzwx+JPjq2cow7glaWf1vXsQkg6/JvPwoggJTLjwDSL/8nRyiAzN/5nzpGAWRd/n7MM0cpgIzLvx6z6CjL453gdpZ/IWbDcQrA8iMAy48ALD8CsPwIwPIjAMuPACw/ArD8CMDyIwDLjwAsPwKw/AjA8iMAy48ALD8CsPwIwPIjAMuPACw/ArD85A3A8pM2AMtP2gAsP2kDsPykDcDykzYAy0/aACw/aQOw/KQNwPKTNgDLT9oALD9pA7D8pA3A8pM2AMtP2gAsP2kDsPykDcDykzYAy0/aACw/aQOw/KQNwPKTNgDLT9oALD9pA7D8pA3A8pM2AMtP2gAsP2kDsPykDcDykzYAy0/aACw/aQOw/KQNwPLz3xlv6H4mYp5YfrI+AizF9BwnI/AlZi3mbsxy03feaeh+HsQcc60YgSMxMzE3YmZj3sX8LOlHoPoLnHedaEE35n5pzwF856dN9SPBpZICmHRNaNnlkgL46nrQsvmSAqhftlx1TWjR4ZICqPVcE1q0XloA96rBa7XQhl5pAWzFXKm8i8vo9WMeN3VnnQa/sO8xL2POxEy7Toxo+RdjNpu6w1F9HuBqNXi99lw1eKMM9utHzIeYV8MftbccCQAAAAAAsBdt/XLc+sPy9W+MmPqL+1iJuVA1+C4gdFr6d77FvK0GH2nb739lPR5zNuZ51eBnQhFAJQIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIE8M8jmBlGgABSRnAqZiXms+MUQNYIDnkUKMu4I/gj6zELMRv7/PsnHKEAMkcw6fgEkDmCNUcngMwRvHFsngRnfWJcL/9tRyaAgxrB+ZijO9ymH7MUs+m4yjLmCBozEXMr5nr1+9We1ZgXMXccDwAAAAAAAAAAAAAAAAAAAAAAwO5+AfVgtqHKRnawAAAAAElFTkSuQmCC";
export class EditableTitleBar extends ViewPU {
  constructor(e, t, A, i = -1) {
    super(e, A, i);
    this.leftIconStyle = void 0;
    this.title = void 0;
    this.menuItems = void 0;
    this.onSave = void 0;
    this.onCancel = void 0;
    this.__titleMaxWidth = new ObservedPropertySimplePU(0, this, "titleMaxWidth");
    this.__backActive = new ObservedPropertySimplePU(!1, this, "backActive");
    this.setInitiallyProvidedValue(t)
  }
  setInitiallyProvidedValue(e) {
    void 0 !== e.leftIconStyle && (this.leftIconStyle = e.leftIconStyle);
    void 0 !== e.title && (this.title = e.title);
    void 0 !== e.menuItems && (this.menuItems = e.menuItems);
    void 0 !== e.onSave && (this.onSave = e.onSave);
    void 0 !== e.onCancel && (this.onCancel = e.onCancel);
    void 0 !== e.titleMaxWidth && (this.titleMaxWidth = e.titleMaxWidth);
    void 0 !== e.backActive && (this.backActive = e.backActive)
  }
  updateStateVars(e) {}
  purgeVariableDependenciesOnElmtId(e) {
    this.__titleMaxWidth.purgeDependencyOnElmtId(e);
    this.__backActive.purgeDependencyOnElmtId(e)
  }
  aboutToBeDeleted() {
    this.__titleMaxWidth.aboutToBeDeleted();
    this.__backActive.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }
  get titleMaxWidth() {
    return this.__titleMaxWidth.get()
  }
  set titleMaxWidth(e) {
    this.__titleMaxWidth.set(e)
  }
  get backActive() {
    return this.__backActive.get()
  }
  set backActive(e) {
    this.__backActive.set(e)
  }
  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Flex.create({
        justifyContent: FlexAlign.SpaceBetween,
        alignItems: ItemAlign.Stretch
      });
      Flex.width("100%");
      Flex.height(EditableTitleBar.totalHeight);
      Flex.backgroundColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_background"],
        bundleName: "",
        moduleName: ""
      });
      Flex.onAreaChange(((e, t) => {
        let A = Number(t.width);
        A = A - EditableTitleBar.leftPadding - EditableTitleBar.rightPadding - EditableTitleBar.titlePadding;
        A = A - ImageMenuItem.imageHotZoneWidth - ImageMenuItem.imageHotZoneWidth;
        void 0 !== this.menuItems ? this.menuItems.length > EditableTitleBar.maxCountOfExtraItems ? this.titleMaxWidth = A - ImageMenuItem.imageHotZoneWidth * EditableTitleBar.maxCountOfExtraItems : this.titleMaxWidth = A - ImageMenuItem.imageHotZoneWidth * this.menuItems.length : this.titleMaxWidth = A
      }));
      t || Flex.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.margin({
        left: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_default_padding_start"],
          bundleName: "",
          moduleName: ""
        }
      });
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.leftIconStyle == EditableLeftIconType.Back ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Navigator.create();
          Navigator.active(this.backActive);
          t || Navigator.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Navigator.pop();
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          t ? ViewPU.create(new ImageMenuItem(this, {
            item: {
              value: PUBLIC_BACK,
              isEnabled: !0,
              action: () => this.backActive = !0
            }
          }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
          ViewStackProcessor.StopGetAccessRecording()
        }))
      })) : this.ifElseBranchUpdateFunction(1, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          t ? ViewPU.create(new ImageMenuItem(this, {
            item: {
              value: PUBLIC_CANCEL,
              isEnabled: !0,
              action: () => this.onCancel && this.onCancel()
            }
          }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
          ViewStackProcessor.StopGetAccessRecording()
        }))
      }));
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.justifyContent(FlexAlign.Start);
      Column.alignItems(HorizontalAlign.Start);
      Column.constraintSize({
        maxWidth: this.titleMaxWidth
      });
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Text.create(this.title);
      Text.fontWeight(FontWeight.Medium);
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_headline8"],
        bundleName: "",
        moduleName: ""
      });
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_titlebar_text"],
        bundleName: "",
        moduleName: ""
      });
      Text.maxLines(1);
      Text.textOverflow({
        overflow: TextOverflow.Ellipsis
      });
      Text.constraintSize({
        maxWidth: this.titleMaxWidth
      });
      t || Text.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Text.pop();
    Column.pop();
    Row.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      t ? ViewPU.create(new EditableTitleBarMenuSection(this, {
        menuItems: this.menuItems,
        onSave: this.onSave
      }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Flex.pop()
  }
  rerender() {
    this.updateDirtyElements()
  }
}
EditableTitleBar.maxCountOfExtraItems = 2;
EditableTitleBar.totalHeight = 56;
EditableTitleBar.leftPadding = 12;
EditableTitleBar.rightPadding = 12;
EditableTitleBar.titlePadding = 16;
class EditableTitleBarMenuSection extends ViewPU {
  constructor(e, t, A, i = -1) {
    super(e, A, i);
    this.menuItems = void 0;
    this.onSave = void 0;
    this.setInitiallyProvidedValue(t)
  }
  setInitiallyProvidedValue(e) {
    void 0 !== e.menuItems && (this.menuItems = e.menuItems);
    void 0 !== e.onSave && (this.onSave = e.onSave)
  }
  updateStateVars(e) {}
  purgeVariableDependenciesOnElmtId(e) {}
  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }
  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.margin({
        left: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_elements_margin_vertical_l"],
          bundleName: "",
          moduleName: ""
        },
        right: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_default_padding_end"],
          bundleName: "",
          moduleName: ""
        }
      });
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
      void 0 !== this.menuItems && this.menuItems.length > 0 ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          ForEach.create();
          this.forEachUpdateFunction(e, this.menuItems.slice(0, EditableTitleBar.maxCountOfExtraItems), (e => {
            const t = e;
            this.observeComponentCreation(((e, A) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              A ? ViewPU.create(new ImageMenuItem(this, {
                item: t
              }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
              ViewStackProcessor.StopGetAccessRecording()
            }))
          }));
          t || ForEach.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        ForEach.pop()
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      t ? ViewPU.create(new ImageMenuItem(this, {
        item: {
          value: PUBLIC_OK,
          isEnabled: !0,
          action: () => this.onSave && this.onSave()
        }
      }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Row.pop();
    Column.pop()
  }
  rerender() {
    this.updateDirtyElements()
  }
}
class ImageMenuItem extends ViewPU {
  constructor(e, t, A, i = -1) {
    super(e, A, i);
    this.item = void 0;
    this.__isOnFocus = new ObservedPropertySimplePU(!1, this, "isOnFocus");
    this.__isOnHover = new ObservedPropertySimplePU(!1, this, "isOnHover");
    this.__isOnClick = new ObservedPropertySimplePU(!1, this, "isOnClick");
    this.setInitiallyProvidedValue(t)
  }
  setInitiallyProvidedValue(e) {
    void 0 !== e.item && (this.item = e.item);
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
export default {
  EditableLeftIconType: EditableLeftIconType,
  EditableTitleBar: EditableTitleBar
};