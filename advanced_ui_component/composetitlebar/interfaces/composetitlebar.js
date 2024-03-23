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
const PUBLIC_MORE = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAY' +
  'AAABS3GwHAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAA' +
  'AAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAABEZJREFUeNrt3D1rFFEUBuA' +
  'xhmAhFlYpUohYiYWFRcAmKAhWK2pjo1iKf8BCMIKFf8BarCyMhVj4VZhGSKEg2FqJyCKWIhYWnstMINgYsh+cmfs88BI' +
  'Cydxw7jmzu2HvNg0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADBN+3r6dx+LXIqsRpa7FF8j48hm5Fn3Peo9mAEYRdY' +
  'jJ3f582Vj7nZfUe/eDsCRyMPI2h5/fyNyI/JDT6v3Tvt7sBllE15ETkxwjeORi5G3ke/6W737MgBnI68jh6ZwrcORq5H' +
  'nhkC9+zAA5YXXy8jBKV5zKXIu8jjyS7+rd+YBeNVtyrSVO9PRyBM9r94LSTfjWuTUDK9/eYIXeENUbb0zDsBi5PYc1rm' +
  'j79U74wCszuih+F/ljrSi/+uud8YBGA10rayqrnfGAVgb6FpZVV3vjAOwPNC1sqq63hkHYGWga2VVdb0XKt/8Rf1fd70' +
  'zDsB4jmt5u3Tl9a59AMb6v+56ZxyArYGulVXV9c44ABtzXOup/q+73hkH4N2cHio/Rj7r/7rrnXEAfkfuz2Gddb2v3ln' +
  '/DfpgxneLzaY9xE3l9c46AH8iVyI/Z3Dt8nB/Xc+rd5H5QMy3yJemPVs6zY0edc9HUe/0Z4I/dQ/N5Vjd0oTXKp9QcKF' +
  'pD2qj3r0YgO1NeRM507TH6/bifeR85IMeV++d+vTBWOV9JDcjt5rdv6uw3M3uRR7pa/Xu+wBsOxA53bTnTP/3UX1b3fN' +
  'Q1BsAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAKqyr6d/97HIpchqZLlL8TUyjmxGnnX' +
  'fo96DGYBRZD1ycpc/XzbmbvcV9e7tAByJPIys7fH3NyI3Ij/0tHrvtL8Hm1E24UXkxATXOB65GHkb+a6/1bsvA3A28jp' +
  'yaArXOhy5GnluCNS7DwNQXni9jByc4jWXIucijyO/9Lt6Zx6AV92mTFu5Mx2NPNHz6r2QdDOuRU7N8PqXJ3iBN0TV1jv' +
  'jACxGbs9hnTv6Xr0zDsDqjB6K/1XuSCv6v+56ZxyA0UDXyqrqemccgLWBrpVV1fXOOADLA10rq6rrnXEAVga6VlZV13u' +
  'h8s1f1P911zvjAIznuJa3S1de79oHYKz/6653xgHYGuhaWVVd74wDsDHHtZ7q/7rrnXEA3s3pofJj5LP+r7veGQfgd+T' +
  '+HNZZ1/vqnfXfoA9mfLfYbNpD3FRe76wD8CdyJfJzBtcuD/fX9bx6F5kPxHyLfGnas6XT3OhR93wU9U5/JvhT99BcjtU' +
  'tTXit8gkFF5r2oDbq3YsB2N6UN5EzTXu8bi/eR85HPuhx9d6pTx+MVd5HcjNyq9n9uwrL3exe5JG+Vu++D8C2A5HTTXv' +
  'O9H8f1bfVPQ9FvQEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgCn7C9HjBtwWfXpKAAAAAElFTkSuQmCC';
const PUBLIC_BACK = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAY' +
  'AAABS3GwHAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAA' +
  'XNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAA8VJREFUeNrt3LFLlHEYwPFXz0G' +
  'iIZpEoikkwsFRIiK3gqCigxIC/4Kmhv6OoChouaGoqKCgCKducGh0cDAIamhwiCaHCIeelztpUszee/vl8/nAM3Vd8nufr' +
  '+fddVYVAAAAAAAAAAAAAAAAAAAAAABQijFH0KhrMd2Y2ZitmNWYRzHLjkYAB9lUzMOYizv8eS/mZsymoypLxxE0svzvY07' +
  'vcpu5mOmY145LAAdx+U/u4bZzwx+JPjq2cow7glaWf1vXsQkg6/JvPwoggJTLjwDSL/8nRyiAzN/5nzpGAWRd/n7MM0cpg' +
  'IzLvx6z6CjL453gdpZ/IWbDcQrA8iMAy48ALD8CsPwIwPIjAMuPACw/ArD8CMDyIwDLjwAsPwKw/AjA8iMAy48ALD8CsPw' +
  'IwPIjAMuPACw/ArD85A3A8pM2AMtP2gAsP2kDsPykDcDykzYAy0/aACw/aQOw/KQNwPKTNgDLT9oALD9pA7D8pA3A8pM2A' +
  'MtP2gAsP2kDsPykDcDykzYAy0/aACw/aQOw/KQNwPKTNgDLT9oALD9pA7D8pA3A8pM2AMtP2gAsP2kDsPykDcDykzYAy0/' +
  'aACw/aQOw/KQNwPLz3xlv6H4mYp5YfrI+AizF9BwnI/AlZi3mbsxy03feaeh+HsQcc60YgSMxMzE3YmZj3sX8LOlHoPoLn' +
  'HedaEE35n5pzwF856dN9SPBpZICmHRNaNnlkgL46nrQsvmSAqhftlx1TWjR4ZICqPVcE1q0XloA96rBa7XQhl5pAWzFXKm' +
  '8i8vo9WMeN3VnnQa/sO8xL2POxEy7Toxo+RdjNpu6w1F9HuBqNXi99lw1eKMM9utHzIeYV8MftbccCQAAAAAAsBdt/XLc+s' +
  'Py9W+MmPqL+1iJuVA1+C4gdFr6d77FvK0GH2nb739lPR5zNuZ51eBnQhFAJQIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIE' +
  'IAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAI' +
  'EIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIE8M8jmBlGgABSRnAqZiXms+MUQNYIDnkUKMu4I/gj6z' +
  'ELMRv7/PsnHKEAMkcw6fgEkDmCNUcngMwRvHFsngRnfWJcL/9tRyaAgxrB+ZijO9ymH7MUs+m4yjLmCBozEXMr5nr1+9We1' +
  'ZgXMXccDwAAAAAAAAAAAAAAAAAAAAAAwO5+AfVgtqHKRnawAAAAAElFTkSuQmCC';
class ComposeTitleBar extends ViewPU {
  constructor(l, k, m, b = -1, n = undefined, o) {
    super(l, m, b, o);
    if (typeof n === "function") {
      this.paramsGenerator_ = n;
    }
    this.item = null;
    this.title = '';
    this.subtitle = '';
    this.menuItems = undefined;
    this.__titleMaxWidth = new ObservedPropertySimplePU(0, this, "titleMaxWidth");
    this.__backActive = new ObservedPropertySimplePU(false, this, "backActive");
    this.setInitiallyProvidedValue(k);
  }
  setInitiallyProvidedValue(k) {
    if (k.item !== undefined) {
      this.item = k.item;
    }
    if (k.title !== undefined) {
      this.title = k.title;
    }
    if (k.subtitle !== undefined) {
      this.subtitle = k.subtitle;
    }
    if (k.menuItems !== undefined) {
      this.menuItems = k.menuItems;
    }
    if (k.titleMaxWidth !== undefined) {
      this.titleMaxWidth = k.titleMaxWidth;
    }
    if (k.backActive !== undefined) {
      this.backActive = k.backActive;
    }
  }
  updateStateVars(k) {
  }
  purgeVariableDependenciesOnElmtId(j) {
    this.__titleMaxWidth.purgeDependencyOnElmtId(j);
    this.__backActive.purgeDependencyOnElmtId(j);
  }
  aboutToBeDeleted() {
    this.__titleMaxWidth.aboutToBeDeleted();
    this.__backActive.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get titleMaxWidth() {
    return this.__titleMaxWidth.get();
  }
  set titleMaxWidth(i) {
    this.__titleMaxWidth.set(i);
  }
  get backActive() {
    return this.__backActive.get();
  }
  set backActive(i) {
    this.__backActive.set(i);
  }
  initialRender() {
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Flex.create({
        justifyContent: FlexAlign.SpaceBetween,
        alignItems: ItemAlign.Stretch
      });
      Flex.width('100%');
      Flex.height(ComposeTitleBar.totalHeight);
      Flex.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background'], "bundleName": "", "moduleName": "" });
      Flex.onAreaChange((u, i) => {
        let v = Number(i.width);
        if (this.menuItems !== undefined) {
          let w = this.menuItems.length;
          if (w >= CollapsibleMenuSection.maxCountOfVisibleItems) {
            v = v - ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
          }
          else if (w > 0) {
            v = v - ImageMenuItem.imageHotZoneWidth * w;
          }
        }
        this.titleMaxWidth = v;
        this.titleMaxWidth -= ComposeTitleBar.leftPadding;
        this.titleMaxWidth -= ImageMenuItem.imageHotZoneWidth;
        if (this.item !== undefined) {
          this.titleMaxWidth -= ComposeTitleBar.portraitImageLeftPadding
            + ComposeTitleBar.portraitImageSize
            + ComposeTitleBar.portraitImageRightPadding;
        }
        this.titleMaxWidth -= ComposeTitleBar.rightPadding;
      });
      if (!c) {
        Flex.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Row.create();
      Row.margin({ left: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_default_padding_start'], "bundleName": "", "moduleName": "" } });
      if (!c) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Navigator.create();
      Navigator.active(this.backActive);
      if (!c) {
        Navigator.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Navigator.pop();
    {
      this.observeComponentCreation((b, c) => {
        ViewStackProcessor.StartGetAccessRecordingFor(b);
        if (c) {
          let n = () => {
            return {
              item: {
                value: { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_back'], "bundleName": "", "moduleName": "" },
                isEnabled: true,
                action: () => this.backActive = true
              },
              index: -1
            };
          };
          ViewPU.create(new ImageMenuItem(this, { item: {
            value: { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_back'], "bundleName": "", "moduleName": "" },
            isEnabled: true,
            action: () => this.backActive = true
          }, index: -1 }, undefined, b, n, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 89 }));
        }
        else {
          this.updateStateVarsOfChildByElmtId(b, {});
        }
        ViewStackProcessor.StopGetAccessRecording();
      });
    }
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      If.create();
      if (this.item !== undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((b, c) => {
            var d;
            ViewStackProcessor.StartGetAccessRecordingFor(b);
            Image.create((d = this.item) === null || d === void 0 ? void 0 : d.value);
            Image.width(ComposeTitleBar.portraitImageSize);
            Image.height(ComposeTitleBar.portraitImageSize);
            Image.margin({
              left: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], "bundleName": "", "moduleName": "" },
              right: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_paragraph_margin_m'], "bundleName": "", "moduleName": "" }
            });
            Image.focusable(false);
            Image.borderRadius(ImageMenuItem.buttonBorderRadius);
            if (!c) {
              Image.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!c) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Column.create();
      Column.justifyContent(FlexAlign.Start);
      Column.alignItems(HorizontalAlign.Start);
      Column.constraintSize({ maxWidth: this.titleMaxWidth });
      if (!c) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      If.create();
      if (this.title !== undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((b, c) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b);
            Row.create();
            Row.justifyContent(FlexAlign.Start);
            if (!c) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((b, c) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b);
            Text.create(this.title);
            Text.fontWeight(FontWeight.Medium);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_headline8'], "bundleName": "", "moduleName": "" });
            Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_text'], "bundleName": "", "moduleName": "" });
            Text.maxLines(this.subtitle !== undefined ? 1 : 2);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.constraintSize({ maxWidth: this.titleMaxWidth });
            if (!c) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!c) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      If.create();
      if (this.subtitle !== undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((b, c) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b);
            Row.create();
            Row.justifyContent(FlexAlign.Start);
            if (!c) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((b, c) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b);
            Text.create(this.subtitle);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_over_line'], "bundleName": "", "moduleName": "" });
            Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_subtitle_text'], "bundleName": "", "moduleName": "" });
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.constraintSize({ maxWidth: this.titleMaxWidth });
            if (!c) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!c) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Column.pop();
    Row.pop();
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      If.create();
      if (this.menuItems !== undefined && this.menuItems.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          {
            this.observeComponentCreation((b, c) => {
              ViewStackProcessor.StartGetAccessRecordingFor(b);
              if (c) {
                let n = () => {
                  return {
                    menuItems: this.menuItems,
                    index: 1 + ComposeTitleBar.instanceCount++
                  };
                };
                ViewPU.create(new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + ComposeTitleBar.instanceCount++ }, undefined, b, n, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 139 }));
              }
              else {
                this.updateStateVarsOfChildByElmtId(b, {});
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
          }
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!c) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Flex.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
ComposeTitleBar.totalHeight = 56;
ComposeTitleBar.leftPadding = 12;
ComposeTitleBar.rightPadding = 12;
ComposeTitleBar.portraitImageSize = 40;
ComposeTitleBar.portraitImageLeftPadding = 4;
ComposeTitleBar.portraitImageRightPadding = 16;
ComposeTitleBar.instanceCount = 0;
class CollapsibleMenuSection extends ViewPU {
  constructor(l, k, m, b = -1, n = undefined, o) {
    super(l, m, b, o);
    if (typeof n === "function") {
      this.paramsGenerator_ = n;
    }
    this.menuItems = undefined;
    this.index = 0;
    this.firstFocusableIndex = -1;
    this.__isPopupShown = new ObservedPropertySimplePU(false, this, "isPopupShown");
    this.__isMoreIconOnFocus = new ObservedPropertySimplePU(false, this, "isMoreIconOnFocus");
    this.__isMoreIconOnHover = new ObservedPropertySimplePU(false, this, "isMoreIconOnHover");
    this.__isMoreIconOnClick = new ObservedPropertySimplePU(false, this, "isMoreIconOnClick");
    this.setInitiallyProvidedValue(k);
  }
  setInitiallyProvidedValue(k) {
    if (k.menuItems !== undefined) {
      this.menuItems = k.menuItems;
    }
    if (k.index !== undefined) {
      this.index = k.index;
    }
    if (k.firstFocusableIndex !== undefined) {
      this.firstFocusableIndex = k.firstFocusableIndex;
    }
    if (k.isPopupShown !== undefined) {
      this.isPopupShown = k.isPopupShown;
    }
    if (k.isMoreIconOnFocus !== undefined) {
      this.isMoreIconOnFocus = k.isMoreIconOnFocus;
    }
    if (k.isMoreIconOnHover !== undefined) {
      this.isMoreIconOnHover = k.isMoreIconOnHover;
    }
    if (k.isMoreIconOnClick !== undefined) {
      this.isMoreIconOnClick = k.isMoreIconOnClick;
    }
  }
  updateStateVars(k) {
  }
  purgeVariableDependenciesOnElmtId(j) {
    this.__isPopupShown.purgeDependencyOnElmtId(j);
    this.__isMoreIconOnFocus.purgeDependencyOnElmtId(j);
    this.__isMoreIconOnHover.purgeDependencyOnElmtId(j);
    this.__isMoreIconOnClick.purgeDependencyOnElmtId(j);
  }
  aboutToBeDeleted() {
    this.__isPopupShown.aboutToBeDeleted();
    this.__isMoreIconOnFocus.aboutToBeDeleted();
    this.__isMoreIconOnHover.aboutToBeDeleted();
    this.__isMoreIconOnClick.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get isPopupShown() {
    return this.__isPopupShown.get();
  }
  set isPopupShown(i) {
    this.__isPopupShown.set(i);
  }
  get isMoreIconOnFocus() {
    return this.__isMoreIconOnFocus.get();
  }
  set isMoreIconOnFocus(i) {
    this.__isMoreIconOnFocus.set(i);
  }
  get isMoreIconOnHover() {
    return this.__isMoreIconOnHover.get();
  }
  set isMoreIconOnHover(i) {
    this.__isMoreIconOnHover.set(i);
  }
  get isMoreIconOnClick() {
    return this.__isMoreIconOnClick.get();
  }
  set isMoreIconOnClick(i) {
    this.__isMoreIconOnClick.set(i);
  }
  getMoreIconFgColor() {
    return this.isMoreIconOnClick
      ? { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'], "bundleName": "", "moduleName": "" } : { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_icon'], "bundleName": "", "moduleName": "" };
  }
  getMoreIconBgColor() {
    if (this.isMoreIconOnClick) {
      return { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "", "moduleName": "" };
    }
    else if (this.isMoreIconOnHover) {
      return { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "", "moduleName": "" };
    }
    else {
      return Color.Transparent;
    }
  }
  aboutToAppear() {
    var d;
    (d = this.menuItems) === null || d === void 0 ? void 0 : d.forEach((s, r) => {
      if (s.isEnabled && this.firstFocusableIndex == -1 && r > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
        this.firstFocusableIndex = this.index * 1000 + r + 1;
      }
    });
  }
  initialRender() {
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Column.create();
      Column.height('100%');
      Column.margin({ right: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_default_padding_end'], "bundleName": "", "moduleName": "" } });
      Column.justifyContent(FlexAlign.Center);
      if (!c) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Row.create();
      if (!c) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      If.create();
      if (this.menuItems) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((b, c) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b);
            If.create();
            if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((b, c) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(b);
                  ForEach.create();
                  const p = (q, r) => {
                    const s = q;
                    {
                      this.observeComponentCreation((b, c) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(b);
                        if (c) {
                          let n = () => {
                            return {
                              item: s,
                              index: this.index * 1000 + r + 1
                            };
                          };
                          ViewPU.create(new ImageMenuItem(this, { item: s, index: this.index * 1000 + r + 1 }, undefined, b, n, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 214 }));
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(b, {});
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                      });
                    }
                  };
                  this.forEachUpdateFunction(b, this.menuItems, p, undefined, true, false);
                  if (!c) {
                    ForEach.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                ForEach.pop();
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation((b, c) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(b);
                  ForEach.create();
                  const p = (q, r) => {
                    const s = q;
                    {
                      this.observeComponentCreation((b, c) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(b);
                        if (c) {
                          let n = () => {
                            return {
                              item: s,
                              index: this.index * 1000 + r + 1
                            };
                          };
                          ViewPU.create(new ImageMenuItem(this, { item: s, index: this.index * 1000 + r + 1 }, undefined, b, n, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 218 }));
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(b, {});
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                      });
                    }
                  };
                  this.forEachUpdateFunction(b, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), p, undefined, true, false);
                  if (!c) {
                    ForEach.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                ForEach.pop();
                this.observeComponentCreation((b, c) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(b);
                  Row.create();
                  Row.width(ImageMenuItem.imageHotZoneWidth);
                  Row.height(ImageMenuItem.imageHotZoneWidth);
                  Row.borderRadius(ImageMenuItem.buttonBorderRadius);
                  Row.foregroundColor(this.getMoreIconFgColor());
                  Row.backgroundColor(this.getMoreIconBgColor());
                  Row.justifyContent(FlexAlign.Center);
                  ViewStackProcessor.visualState("focused");
                  Row.border({
                    radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "", "moduleName": "" },
                    width: ImageMenuItem.focusBorderWidth,
                    color: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "", "moduleName": "" },
                    style: BorderStyle.Solid
                  });
                  ViewStackProcessor.visualState("normal");
                  Row.border({
                    radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "", "moduleName": "" },
                    width: 0
                  });
                  ViewStackProcessor.visualState();
                  Row.onFocus(() => this.isMoreIconOnFocus = true);
                  Row.onBlur(() => this.isMoreIconOnFocus = false);
                  Row.onHover((h) => this.isMoreIconOnHover = h);
                  Row.onKeyEvent((g) => {
                    if (g.keyCode !== KeyCode.KEYCODE_ENTER && g.keyCode !== KeyCode.KEYCODE_SPACE) {
                      return;
                    }
                    if (g.type === KeyType.Down) {
                      this.isMoreIconOnClick = true;
                    }
                    if (g.type === KeyType.Up) {
                      this.isMoreIconOnClick = false;
                    }
                  });
                  Row.onTouch((g) => {
                    if (g.type === TouchType.Down) {
                      this.isMoreIconOnClick = true;
                    }
                    if (g.type === TouchType.Up) {
                      this.isMoreIconOnClick = false;
                    }
                  });
                  Row.onClick(() => this.isPopupShown = true);
                  Row.bindPopup(this.isPopupShown, {
                    builder: { builder: this.popupBuilder.bind(this) },
                    placement: Placement.Bottom,
                    popupColor: Color.White,
                    enableArrow: false,
                    onStateChange: (t) => {
                      this.isPopupShown = t.isVisible;
                      if (!t.isVisible) {
                        this.isMoreIconOnClick = false;
                      }
                    }
                  });
                  if (!c) {
                    Row.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                this.observeComponentCreation((b, c) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(b);
                  Image.create(PUBLIC_MORE);
                  Image.width(ImageMenuItem.imageSize);
                  Image.height(ImageMenuItem.imageSize);
                  Image.focusable(true);
                  if (!c) {
                    Image.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                Row.pop();
              });
            }
            if (!c) {
              If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          If.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!c) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Row.pop();
    Column.pop();
  }
  popupBuilder(l = null) {
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Column.create();
      Column.width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
      Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
      Column.onAppear(() => {
        focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex);
      });
      if (!c) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      If.create();
      if (this.menuItems) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((b, c) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b);
            ForEach.create();
            const p = (q, r) => {
              const s = q;
              {
                this.observeComponentCreation((b, c) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(b);
                  if (c) {
                    let n = () => {
                      return {
                        item: s,
                        index: this.index * 1000 + CollapsibleMenuSection.maxCountOfVisibleItems + r
                      };
                    };
                    ViewPU.create(new ImageMenuItem(this, { item: s, index: this.index * 1000 + CollapsibleMenuSection.maxCountOfVisibleItems + r }, undefined, b, n, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 298 }));
                  }
                  else {
                    this.updateStateVarsOfChildByElmtId(b, {});
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
              }
            };
            this.forEachUpdateFunction(b, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), p, undefined, true, false);
            if (!c) {
              ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          ForEach.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!c) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Column.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
CollapsibleMenuSection.maxCountOfVisibleItems = 3;
CollapsibleMenuSection.focusPadding = 4;
CollapsibleMenuSection.marginsNum = 2;
class ImageMenuItem extends ViewPU {
  constructor(l, k, m, b = -1, n = undefined, o) {
    super(l, m, b, o);
    if (typeof n === "function") {
      this.paramsGenerator_ = n;
    }
    this.item = null;
    this.index = 0;
    this.__isOnFocus = new ObservedPropertySimplePU(false, this, "isOnFocus");
    this.__isOnHover = new ObservedPropertySimplePU(false, this, "isOnHover");
    this.__isOnClick = new ObservedPropertySimplePU(false, this, "isOnClick");
    this.setInitiallyProvidedValue(k);
  }
  setInitiallyProvidedValue(k) {
    if (k.item !== undefined) {
      this.item = k.item;
    }
    if (k.index !== undefined) {
      this.index = k.index;
    }
    if (k.isOnFocus !== undefined) {
      this.isOnFocus = k.isOnFocus;
    }
    if (k.isOnHover !== undefined) {
      this.isOnHover = k.isOnHover;
    }
    if (k.isOnClick !== undefined) {
      this.isOnClick = k.isOnClick;
    }
  }
  updateStateVars(k) {
  }
  purgeVariableDependenciesOnElmtId(j) {
    this.__isOnFocus.purgeDependencyOnElmtId(j);
    this.__isOnHover.purgeDependencyOnElmtId(j);
    this.__isOnClick.purgeDependencyOnElmtId(j);
  }
  aboutToBeDeleted() {
    this.__isOnFocus.aboutToBeDeleted();
    this.__isOnHover.aboutToBeDeleted();
    this.__isOnClick.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get isOnFocus() {
    return this.__isOnFocus.get();
  }
  set isOnFocus(i) {
    this.__isOnFocus.set(i);
  }
  get isOnHover() {
    return this.__isOnHover.get();
  }
  set isOnHover(i) {
    this.__isOnHover.set(i);
  }
  get isOnClick() {
    return this.__isOnClick.get();
  }
  set isOnClick(i) {
    this.__isOnClick.set(i);
  }
  getFgColor() {
    return this.isOnClick
      ? { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'], "bundleName": "", "moduleName": "" } : { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_icon'], "bundleName": "", "moduleName": "" };
  }
  getBgColor() {
    if (this.isOnClick) {
      return { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "", "moduleName": "" };
    }
    else if (this.isOnHover) {
      return { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "", "moduleName": "" };
    }
    else {
      return Color.Transparent;
    }
  }
  initialRender() {
    this.observeComponentCreation((b, c) => {
      var d;
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Row.create();
      Row.width(ImageMenuItem.imageHotZoneWidth);
      Row.height(ImageMenuItem.imageHotZoneWidth);
      Row.borderRadius(ImageMenuItem.buttonBorderRadius);
      Row.foregroundColor(this.getFgColor());
      Row.backgroundColor(this.getBgColor());
      Row.justifyContent(FlexAlign.Center);
      Row.opacity(((d = this.item) === null || d === void 0 ? void 0 : d.isEnabled) ? 1 : ImageMenuItem.disabledImageOpacity);
      ViewStackProcessor.visualState("focused");
      Row.border({
        radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "", "moduleName": "" },
        width: ImageMenuItem.focusBorderWidth,
        color: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "", "moduleName": "" },
        style: BorderStyle.Solid
      });
      ViewStackProcessor.visualState("normal");
      Row.border({
        radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "", "moduleName": "" },
        width: 0
      });
      ViewStackProcessor.visualState();
      Row.onFocus(() => {
        var d;
        if (!((d = this.item) === null || d === void 0 ? void 0 : d.isEnabled)) {
          return;
        }
        this.isOnFocus = true;
      });
      Row.onBlur(() => this.isOnFocus = false);
      Row.onHover((h) => {
        var d;
        if (!((d = this.item) === null || d === void 0 ? void 0 : d.isEnabled)) {
          return;
        }
        this.isOnHover = h;
      });
      Row.onKeyEvent((g) => {
        var d;
        if (!((d = this.item) === null || d === void 0 ? void 0 : d.isEnabled)) {
          return;
        }
        if (g.keyCode !== KeyCode.KEYCODE_ENTER && g.keyCode !== KeyCode.KEYCODE_SPACE) {
          return;
        }
        if (g.type === KeyType.Down) {
          this.isOnClick = true;
        }
        if (g.type === KeyType.Up) {
          this.isOnClick = false;
        }
      });
      Row.onTouch((g) => {
        var d;
        if (!((d = this.item) === null || d === void 0 ? void 0 : d.isEnabled)) {
          return;
        }
        if (g.type === TouchType.Down) {
          this.isOnClick = true;
        }
        if (g.type === TouchType.Up) {
          this.isOnClick = false;
        }
      });
      Row.onClick(() => { var d, e, f; return ((d = this.item) === null || d === void 0 ? void 0 : d.isEnabled) && ((e = this.item) === null || e === void 0 ? void 0 : e.action) && ((f = this.item) === null || f === void 0 ? void 0 : f.action()); });
      if (!c) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b, c) => {
      var d, e;
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Image.create((d = this.item) === null || d === void 0 ? void 0 : d.value);
      Image.width(ImageMenuItem.imageSize);
      Image.height(ImageMenuItem.imageSize);
      Image.focusable((e = this.item) === null || e === void 0 ? void 0 : e.isEnabled);
      Image.key(ImageMenuItem.focusablePrefix + this.index);
      Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "", "moduleName": "" });
      if (!c) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
ImageMenuItem.imageSize = 24;
ImageMenuItem.imageHotZoneWidth = 48;
ImageMenuItem.buttonBorderRadius = 8;
ImageMenuItem.focusBorderWidth = 2;
ImageMenuItem.disabledImageOpacity = 0.4;
ImageMenuItem.focusablePrefix = "Id-ComposeTitleBar-ImageMenuItem-";
export default {
  ComposeTitleBar: ComposeTitleBar
};
