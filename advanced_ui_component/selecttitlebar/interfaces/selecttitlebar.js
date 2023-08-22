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
  var s, r = arguments.length,
    n = r < 3 ? t : null === i ? i = Object.getOwnPropertyDescriptor(t, o) : i;
  if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) n = Reflect.decorate(e, t, o, i);
  else
    for (var c = e.length - 1; c >= 0; c--)(s = e[c]) && (n = (r < 3 ? s(n) : r > 3 ? s(t, o, n) : s(t, o)) || n);
  return r > 3 && n && Object.defineProperty(t, o, n), n
};
const KeyCode = requireNapi("multimodalInput.keyCode").KeyCode;
const PUBLIC_MORE = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAYAAABS3GwHAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAABEZJREFUeNrt3D1rFFEUBuAxhmAhFlYpUohYiYWFRcAmKAhWK2pjo1iKf8BCMIKFf8BarCyMhVj4VZhGSKEg2FqJyCKWIhYWnstMINgYsh+cmfs88BICydxw7jmzu2HvNg0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADBN+3r6dx+LXIqsRpa7FF8j48hm5Fn3Peo9mAEYRdYjJ3f582Vj7nZfUe/eDsCRyMPI2h5/fyNyI/JDT6v3Tvt7sBllE15ETkxwjeORi5G3ke/6W737MgBnI68jh6ZwrcORq5HnhkC9+zAA5YXXy8jBKV5zKXIu8jjyS7+rd+YBeNVtyrSVO9PRyBM9r94LSTfjWuTUDK9/eYIXeENUbb0zDsBi5PYc1rmj79U74wCszuih+F/ljrSi/+uud8YBGA10rayqrnfGAVgb6FpZVV3vjAOwPNC1sqq63hkHYGWga2VVdb0XKt/8Rf1fd70zDsB4jmt5u3Tl9a59AMb6v+56ZxyArYGulVXV9c44ABtzXOup/q+73hkH4N2cHio/Rj7r/7rrnXEAfkfuz2Gddb2v3ln/DfpgxneLzaY9xE3l9c46AH8iVyI/Z3Dt8nB/Xc+rd5H5QMy3yJemPVs6zY0edc9HUe/0Z4I/dQ/N5Vjd0oTXKp9QcKFpD2qj3r0YgO1NeRM507TH6/bifeR85IMeV++d+vTBWOV9JDcjt5rdv6uw3M3uRR7pa/Xu+wBsOxA53bTnTP/3UX1b3fNQ1BsAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAKqyr6d/97HIpchqZLlL8TUyjmxGnnXfo96DGYBRZD1ycpc/XzbmbvcV9e7tAByJPIys7fH3NyI3Ij/0tHrvtL8Hm1E24UXkxATXOB65GHkb+a6/1bsvA3A28jpyaArXOhy5GnluCNS7DwNQXni9jByc4jWXIucijyO/9Lt6Zx6AV92mTFu5Mx2NPNHz6r2QdDOuRU7N8PqXJ3iBN0TV1jvjACxGbs9hnTv6Xr0zDsDqjB6K/1XuSCv6v+56ZxyA0UDXyqrqemccgLWBrpVV1fXOOADLA10rq6rrnXEAVga6VlZV13uh8s1f1P911zvjAIznuJa3S1de79oHYKz/6653xgHYGuhaWVVd74wDsDHHtZ7q/7rrnXEA3s3pofJj5LP+r7veGQfgd+T+HNZZ1/vqnfXfoA9mfLfYbNpD3FRe76wD8CdyJfJzBtcuD/fX9bx6F5kPxHyLfGnas6XT3OhR93wU9U5/JvhT99BcjtUtTXit8gkFF5r2oDbq3YsB2N6UN5EzTXu8bi/eR85HPuhx9d6pTx+MVd5HcjNyq9n9uwrL3exe5JG+Vu++D8C2A5HTTXvO9H8f1bfVPQ9FvQEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgCn7C9HjBtwWfXpKAAAAAElFTkSuQmCC";
const PUBLIC_BACK = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAYAAABS3GwHAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAA8VJREFUeNrt3LFLlHEYwPFXz0GiIZpEoikkwsFRIiK3gqCigxIC/4Kmhv6OoChouaGoqKCgCKducGh0cDAIamhwiCaHCIeelztpUszee/vl8/nAM3Vd8nufr+fddVYVAAAAAAAAAAAAAAAAAAAAAABQijFH0KhrMd2Y2ZitmNWYRzHLjkYAB9lUzMOYizv8eS/mZsymoypLxxE0svzvY07vcpu5mOmY145LAAdx+U/u4bZzwx+JPjq2cow7glaWf1vXsQkg6/JvPwoggJTLjwDSL/8nRyiAzN/5nzpGAWRd/n7MM0cpgIzLvx6z6CjL453gdpZ/IWbDcQrA8iMAy48ALD8CsPwIwPIjAMuPACw/ArD8CMDyIwDLjwAsPwKw/AjA8iMAy48ALD8CsPwIwPIjAMuPACw/ArD85A3A8pM2AMtP2gAsP2kDsPykDcDykzYAy0/aACw/aQOw/KQNwPKTNgDLT9oALD9pA7D8pA3A8pM2AMtP2gAsP2kDsPykDcDykzYAy0/aACw/aQOw/KQNwPKTNgDLT9oALD9pA7D8pA3A8pM2AMtP2gAsP2kDsPykDcDykzYAy0/aACw/aQOw/KQNwPLz3xlv6H4mYp5YfrI+AizF9BwnI/AlZi3mbsxy03feaeh+HsQcc60YgSMxMzE3YmZj3sX8LOlHoPoLnHedaEE35n5pzwF856dN9SPBpZICmHRNaNnlkgL46nrQsvmSAqhftlx1TWjR4ZICqPVcE1q0XloA96rBa7XQhl5pAWzFXKm8i8vo9WMeN3VnnQa/sO8xL2POxEy7Toxo+RdjNpu6w1F9HuBqNXi99lw1eKMM9utHzIeYV8MftbccCQAAAAAAsBdt/XLc+sPy9W+MmPqL+1iJuVA1+C4gdFr6d77FvK0GH2nb739lPR5zNuZ51eBnQhFAJQIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIE8M8jmBlGgABSRnAqZiXms+MUQNYIDnkUKMu4I/gj6zELMRv7/PsnHKEAMkcw6fgEkDmCNUcngMwRvHFsngRnfWJcL/9tRyaAgxrB+ZijO9ymH7MUs+m4yjLmCBozEXMr5nr1+9We1ZgXMXccDwAAAAAAAAAAAAAAAAAAAAAAwO5+AfVgtqHKRnawAAAAAElFTkSuQmCC";
export class SelectTitleBar extends ViewPU {
  constructor(e, t, o, i = -1) {
    super(e, o, i);
    this.__selected = new ObservedPropertySimplePU(0, this, "selected");
    this.options = void 0;
    this.menuItems = void 0;
    this.subtitle = void 0;
    this.badgeValue = void 0;
    this.hidesBackButton = void 0;
    this.onSelected = void 0;
    this.__selectMaxWidth = new ObservedPropertySimplePU(0, this, "selectMaxWidth");
    this.__backActive = new ObservedPropertySimplePU(!1, this, "backActive");
    this.setInitiallyProvidedValue(t)
  }
  setInitiallyProvidedValue(e) {
    void 0 !== e.selected && (this.selected = e.selected);
    void 0 !== e.options && (this.options = e.options);
    void 0 !== e.menuItems && (this.menuItems = e.menuItems);
    void 0 !== e.subtitle && (this.subtitle = e.subtitle);
    void 0 !== e.badgeValue && (this.badgeValue = e.badgeValue);
    void 0 !== e.hidesBackButton && (this.hidesBackButton = e.hidesBackButton);
    void 0 !== e.onSelected && (this.onSelected = e.onSelected);
    void 0 !== e.selectMaxWidth && (this.selectMaxWidth = e.selectMaxWidth);
    void 0 !== e.backActive && (this.backActive = e.backActive)
  }
  updateStateVars(e) {}
  purgeVariableDependenciesOnElmtId(e) {
    this.__selected.purgeDependencyOnElmtId(e);
    this.__selectMaxWidth.purgeDependencyOnElmtId(e);
    this.__backActive.purgeDependencyOnElmtId(e)
  }
  aboutToBeDeleted() {
    this.__selected.aboutToBeDeleted();
    this.__selectMaxWidth.aboutToBeDeleted();
    this.__backActive.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }
  get selected() {
    return this.__selected.get()
  }
  set selected(e) {
    this.__selected.set(e)
  }
  get selectMaxWidth() {
    return this.__selectMaxWidth.get()
  }
  set selectMaxWidth(e) {
    this.__selectMaxWidth.set(e)
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
      Flex.height(SelectTitleBar.totalHeight);
      Flex.backgroundColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_background"],
        bundleName: "",
        moduleName: ""
      });
      Flex.onAreaChange(((e, t) => {
        let o = Number(t.width);
        if (!this.hidesBackButton) {
          o -= ImageMenuItem.imageHotZoneWidth;
          o += SelectTitleBar.leftPadding;
          o -= SelectTitleBar.leftPaddingWithBack
        }
        if (void 0 !== this.menuItems) {
          let e = this.menuItems.length;
          e >= CollapsibleMenuSection.maxCountOfVisibleItems ? o -= ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems : e > 0 && (o -= ImageMenuItem.imageHotZoneWidth * e)
        }
        void 0 !== this.badgeValue ? this.selectMaxWidth = o - SelectTitleBar.badgeSize - SelectTitleBar.leftPadding - SelectTitleBar.rightPadding - SelectTitleBar.badgePadding : this.selectMaxWidth = o - SelectTitleBar.leftPadding - SelectTitleBar.rightPadding
      }));
      t || Flex.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.margin({
        left: this.hidesBackButton ? {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_max_padding_start"],
          bundleName: "",
          moduleName: ""
        } : {
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
      this.hidesBackButton ? If.branchId(1) : this.ifElseBranchUpdateFunction(0, (() => {
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
        maxWidth: this.selectMaxWidth
      });
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      void 0 !== this.badgeValue ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Badge.create({
            count: this.badgeValue,
            position: BadgePosition.Right,
            style: {
              badgeSize: SelectTitleBar.badgeSize,
              badgeColor: {
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_emphasize"],
                bundleName: "",
                moduleName: ""
              },
              borderColor: {
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_emphasize"],
                bundleName: "",
                moduleName: ""
              },
              borderWidth: 0
            }
          });
          t || Badge.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Row.justifyContent(FlexAlign.Start);
          Row.margin({
            right: {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_elements_margin_horizontal_l"],
              bundleName: "",
              moduleName: ""
            }
          });
          t || Row.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Select.create(this.options);
          Select.selected(this.selected);
          Select.value(this.selected < this.options.length ? this.options[this.selected].value.toString() : "");
          Select.font({
            size: this.hidesBackButton && void 0 === this.subtitle ? {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_text_size_headline7"],
              bundleName: "",
              moduleName: ""
            } : {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_text_size_headline8"],
              bundleName: "",
              moduleName: ""
            }
          });
          Select.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_titlebar_text"],
            bundleName: "",
            moduleName: ""
          });
          Select.backgroundColor(Color.Transparent);
          Select.onSelect(this.onSelected);
          Select.constraintSize({
            maxWidth: this.selectMaxWidth
          });
          Select.offset({
            x: -4
          });
          t || Select.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Select.pop();
        Row.pop();
        Badge.pop()
      })) : this.ifElseBranchUpdateFunction(1, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Row.justifyContent(FlexAlign.Start);
          t || Row.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Select.create(this.options);
          Select.selected(this.selected);
          Select.value(this.selected < this.options.length ? this.options[this.selected].value.toString() : "");
          Select.font({
            size: this.hidesBackButton && void 0 === this.subtitle ? {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_text_size_headline7"],
              bundleName: "",
              moduleName: ""
            } : {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_text_size_headline8"],
              bundleName: "",
              moduleName: ""
            }
          });
          Select.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_titlebar_text"],
            bundleName: "",
            moduleName: ""
          });
          Select.backgroundColor(Color.Transparent);
          Select.onSelect(this.onSelected);
          Select.constraintSize({
            maxWidth: this.selectMaxWidth
          });
          Select.offset({
            x: -4
          });
          t || Select.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Select.pop();
        Row.pop()
      }));
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      void 0 !== this.subtitle ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Row.justifyContent(FlexAlign.Start);
          Row.margin({
            left: SelectTitleBar.subtitleLeftPadding
          });
          t || Row.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.subtitle);
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_over_line"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_titlebar_subtitle_text"],
            bundleName: "",
            moduleName: ""
          });
          Text.maxLines(1);
          Text.textOverflow({
            overflow: TextOverflow.Ellipsis
          });
          Text.constraintSize({
            maxWidth: this.selectMaxWidth
          });
          Text.offset({
            y: -4
          });
          t || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        Row.pop()
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    Column.pop();
    Row.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      void 0 !== this.menuItems && this.menuItems.length > 0 ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          t ? ViewPU.create(new CollapsibleMenuSection(this, {
            menuItems: this.menuItems
          }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
          ViewStackProcessor.StopGetAccessRecording()
        }))
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    Flex.pop()
  }
  rerender() {
    this.updateDirtyElements()
  }
}
SelectTitleBar.badgeSize = 16;
SelectTitleBar.totalHeight = 56;
SelectTitleBar.leftPadding = 24;
SelectTitleBar.leftPaddingWithBack = 12;
SelectTitleBar.rightPadding = 24;
SelectTitleBar.badgePadding = 16;
SelectTitleBar.subtitleLeftPadding = 4;
class CollapsibleMenuSection extends ViewPU {
  constructor(e, t, o, i = -1) {
    super(e, o, i);
    this.menuItems = void 0;
    this.__isPopupShown = new ObservedPropertySimplePU(!1, this, "isPopupShown");
    this.__isMoreIconOnFocus = new ObservedPropertySimplePU(!1, this, "isMoreIconOnFocus");
    this.__isMoreIconOnHover = new ObservedPropertySimplePU(!1, this, "isMoreIconOnHover");
    this.__isMoreIconOnClick = new ObservedPropertySimplePU(!1, this, "isMoreIconOnClick");
    this.setInitiallyProvidedValue(t)
  }
  setInitiallyProvidedValue(e) {
    void 0 !== e.menuItems && (this.menuItems = e.menuItems);
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
  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.height("100%");
      Column.margin({
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
      this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          ForEach.create();
          this.forEachUpdateFunction(e, this.menuItems, (e => {
            const t = e;
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              o ? ViewPU.create(new ImageMenuItem(this, {
                item: t
              }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
              ViewStackProcessor.StopGetAccessRecording()
            }))
          }));
          t || ForEach.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        ForEach.pop()
      })) : this.ifElseBranchUpdateFunction(1, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          ForEach.create();
          this.forEachUpdateFunction(e, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), (e => {
            const t = e;
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              o ? ViewPU.create(new ImageMenuItem(this, {
                item: t
              }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, {});
              ViewStackProcessor.StopGetAccessRecording()
            }))
          }));
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
            onStateChange: e => this.isPopupShown = e.isVisible
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
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      ForEach.create();
      this.forEachUpdateFunction(e, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), ((e, t) => {
        const o = e;
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          t ? ViewPU.create(new ImageMenuItem(this, {
            item: o
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
CollapsibleMenuSection.maxCountOfVisibleItems = 3;
CollapsibleMenuSection.focusPadding = 4;
CollapsibleMenuSection.marginsNum = 2;
__decorate([], CollapsibleMenuSection.prototype, "popupBuilder", null);
class ImageMenuItem extends ViewPU {
  constructor(e, t, o, i = -1) {
    super(e, o, i);
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
  SelectTitleBar: SelectTitleBar
};