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
function __ArkUI_PreloadDynamicModule__(componentName, abcName) {
  getUINativeModule().loadNativeModule(componentName);
  let module = globalThis.requireNapi(abcName);
  if (componentName === 'CalendarPickerDialog' || componentName === 'TimePickerDialog' || componentName === 'DatePickerDialog') {
    module.exportViewDialog();
  } else {
    module.exportView();
  }
  module.loadComponent();
}

// @ts-ignore
if (globalThis.Hyperlink === undefined) {
  globalThis.Hyperlink = {
    create: function(address, content) {
      getUINativeModule().loadNativeModule("Hyperlink");
      let module = globalThis.requireNapi('arkui.components.arkhyperlink');
      module.exportView();
      getUINativeModule().hyperlink.create(address, content);
    },
    name: 'JSHyperlink'
  }
}

// @ts-ignore
if (globalThis.CalendarPicker === undefined) {
  globalThis.CalendarPicker = {
    create: function(params) {
      getUINativeModule().loadNativeModule('CalendarPicker');
      let module = globalThis.requireNapi('arkui.components.arkcalendarpicker');
      module.exportView();
      getUINativeModule().calendarPicker.create(params);
    },
    name: 'JSCalendarPicker'
  }
}

// @ts-ignore
if (globalThis.CalendarPickerDialog === undefined) {
  globalThis.CalendarPickerDialog = class {
    static name = 'JSCalendarPickerDialog'
    constructor() {}
    static show(params) {
      getUINativeModule().loadNativeModule('CalendarPickerDialog');
      let module = globalThis.requireNapi('arkui.components.arkcalendarpicker');
      module.exportViewDialog();
      getUINativeModule().calendarPickerDialog.show(params);
    }
  }
}

// @ts-ignore
if (globalThis.Gauge === undefined) {
  globalThis.Gauge = {
    create: function(params) {
      getUINativeModule().loadNativeModule('Gauge');
      let module = globalThis.requireNapi('arkui.components.arkgauge');
      module.exportView();
      module.loadComponent();
      getUINativeModule().gauge.create(params);
    },
    name: 'JSGauge'
  }
}

// @ts-ignore
if (globalThis.AlphabetIndexer === undefined) {
  globalThis.AlphabetIndexer = {
    create: function (params) {
      getUINativeModule().loadNativeModule('Indexer');
      let module = globalThis.requireNapi('arkui.components.arkalphabetindexer');
      module.exportView();
      if (params !== undefined) {
        getUINativeModule().alphabetIndexer.create(params, false);
      } else {
        getUINativeModule().alphabetIndexer.create(undefined, false);
      }
      return this;
    },
    createArc: function (params) {
      getUINativeModule().loadNativeModule('Indexer');
      let module = globalThis.requireNapi('arkui.components.arkalphabetindexer');
      module.exportView();
      if (params !== undefined) {
        getUINativeModule().alphabetIndexer.create(params, true);
      } else {
        getUINativeModule().alphabetIndexer.create(undefined, true);
      }
      return this;
    },
    name: 'JSAlphabetIndexer'
  }
}

// @ts-ignore
if (globalThis.Checkbox === undefined) {
  globalThis.Checkbox = {
    create: function(params) {
      getUINativeModule().loadNativeModule('Checkbox');
      let module = globalThis.requireNapi('arkui.components.arkcheckbox');
      module.exportView();
      module.loadComponent();
      getUINativeModule().checkbox.create(params);
    }
  };
}

// @ts-ignore
if (globalThis.CheckboxGroup === undefined) {
  globalThis.CheckboxGroup = {
    create: function(params) {
      getUINativeModule().loadNativeModule('CheckboxGroup');
      let module = globalThis.requireNapi('arkui.components.arkcheckboxgroup');
      module.exportView();
      module.loadComponent();
      getUINativeModule().checkboxgroup.create(params);
    }
  };
}

// @ts-ignore
if (globalThis.Button === undefined) {
  globalThis.Button = {
    createWithLabel: function(...args) {
      getUINativeModule().loadNativeModule('Button');
      let module = globalThis.requireNapi('arkui.components.arkbutton');
      module.exportView();
      module.loadComponent();
      getUINativeModule().button.createWithLabel(...args);
    },
    createWithChild: function(...args) {
      getUINativeModule().loadNativeModule('Button');
      let module = globalThis.requireNapi('arkui.components.arkbutton');
      module.exportView();
      module.loadComponent();
      getUINativeModule().button.createWithChild(...args);
    },
    name: 'JSButton'
  };
}


// @ts-ignore
if (globalThis.Rating === undefined) {
  globalThis.Rating = {
    create: function(params) {
      getUINativeModule().loadNativeModule('Rating');
      const module = globalThis.requireNapi('arkui.components.arkrating');
      module.exportView();
      module.loadComponent();
      getUINativeModule().rating.create(params);
    },
    name: 'JSRating'
  };
}

// @ts-ignore
if (globalThis.SideBarContainer === undefined) {
  globalThis.SideBarContainer = {
    create: function(params) {
      getUINativeModule().loadNativeModule('Sidebar');
      let module = globalThis.requireNapi('arkui.components.arksidebarcontainer');
      module.exportView();
      getUINativeModule().sideBarContainer.create(params);
    }
  }
}

// @ts-ignore
if (globalThis.RowSplit === undefined) {
  globalThis.RowSplit = {
    create: function() {
      getUINativeModule().loadNativeModule('RowSplit');
      let module = globalThis.requireNapi('arkui.components.arkrowsplit');
      module.exportView();
      getUINativeModule().rowSplit.create();
    },
    name: 'JSRowSplit'
  };
}

// @ts-ignore
if (globalThis.ColumnSplit === undefined) {
  globalThis.ColumnSplit = {
    create: function() {
      getUINativeModule().loadNativeModule('ColumnSplit');
      let module = globalThis.requireNapi('arkui.components.arkcolumnsplit');
      module.exportView();
      getUINativeModule().columnSplit.create();
    },
    name: 'JSColumnSplit'
  };
}
// @ts-ignore
if (globalThis.Stepper === undefined) {
  globalThis.Stepper = {
    create: function(params) {
      getUINativeModule().loadNativeModule('Stepper');
      let module = globalThis.requireNapi('arkui.components.arkstepper');
      module.exportView();
      getUINativeModule().stepper.create(params);
    },
    name: 'JSStepper'
  };
}

// @ts-ignore
if (globalThis.StepperItem === undefined) {
  globalThis.StepperItem = {
    create: function(params) {
      getUINativeModule().loadNativeModule('StepperItem');
      let module = globalThis.requireNapi('arkui.components.arkstepperitem');
      module.exportView();
      getUINativeModule().stepperItem.create(params);
    },
    name: 'JSStepperItem'
  };
}

// @ts-ignore
if (globalThis.Marquee === undefined) {
  globalThis.Marquee = {
    create: function(params) {
      getUINativeModule().loadNativeModule('Marquee');
      let module = globalThis.requireNapi('arkui.components.arkmarquee');
      module.exportView();
      module.loadComponent();
      getUINativeModule().marquee.create(params);
    },
 	name: 'JSMarquee'
  };
}

// @ts-ignore
if (globalThis.Refresh === undefined) {
  globalThis.Refresh = {
    create: function(params) {
      getUINativeModule().loadNativeModule('Refresh');
      let module = globalThis.requireNapi('arkui.components.arkrefresh');
      module.exportView();
      module.loadComponent();
      getUINativeModule().refresh.create(params);
    },
    name: 'JSRefresh'
  }
}

// @ts-ignore
if (globalThis.Navigator === undefined) {
  globalThis.Navigator = {
    create: function(params) {
      getUINativeModule().loadNativeModule('Navigator');
      let module = globalThis.requireNapi('arkui.components.arknavigator');
      module.exportView();
      module.loadComponent();
      getUINativeModule().navigator.create(params);
    },
    name: 'JSNavigator'
  }
}

// @ts-ignore
if (globalThis.Radio === undefined) {
  globalThis.Radio = {
    create: function(params) {
      getUINativeModule().loadNativeModule('Radio');
      let module = globalThis.requireNapi('arkui.components.arkradio');
      module.exportView();
      module.loadComponent();
      getUINativeModule().radio.create(params);
    },
    name: 'JSRadio'
  }
}

// @ts-ignore
if (globalThis.Slider === undefined) {
  globalThis.Slider = {
    create: function(params) {
      getUINativeModule().loadNativeModule('Slider');
      let module = globalThis.requireNapi('arkui.components.arkslider');
      module.exportView();
      module.loadComponent();
      getUINativeModule().slider.create(params);
    },
    name: 'JSSlider'
  }
}

if (globalThis.QRCode === undefined) {
  globalThis.QRCode = {
    create: function(value) {
      getUINativeModule().loadNativeModule('QRCode');
      let module = globalThis.requireNapi('arkui.components.arkqrcode');
      module.exportView();
      module.loadComponent();
      getUINativeModule().qrcode.create(value);
    },
    name: 'JSQRCode'
  }
}

//@ts-ignore
if (globalThis.CommonShape === undefined) {
  globalThis.CommonShape = {
    create: function() {
      getUINativeModule().loadNativeModule('CommonShape');
      let module = globalThis.requireNapi('arkui.components.arkcommonshape');
      module.exportView();
      module.loadComponent();
    },
    name: 'JSShapeAbstract'
  }
}

// @ts-ignore
if (globalThis.Circle === undefined) {
  globalThis.Circle = class {
    static name = 'JSCircle'
    constructor(value) {
      return new __Circle__(value);
    }
    static create(value) {
      getUINativeModule().loadNativeModule('Circle');
      let module = globalThis.requireNapi('arkui.components.arkcircle');
      module.exportView();
      module.loadComponent();
      getUINativeModule().circle.create(value);
    }
  }
}

// @ts-ignore
if (globalThis.Ellipse === undefined) {
  globalThis.Ellipse = class {
    static name = 'JSEllipse'
    constructor(value) {
      return new __Ellipse__(value);
    }
    static create(value) {
      getUINativeModule().loadNativeModule('Ellipse');
      let module = globalThis.requireNapi('arkui.components.arkellipse');
      module.exportView();
      module.loadComponent();
      getUINativeModule().ellipse.create(value);
    }
  }
}

// @ts-ignore
if (globalThis.Shape === undefined) {
  globalThis.Shape = {
    create: function(value) {
      getUINativeModule().loadNativeModule('Shape');
      let module = globalThis.requireNapi('arkui.components.arkshape');
      module.exportView();
      module.loadComponent();
      getUINativeModule().shape.create(value);
    },
    name: 'JSShape'
  }
}

// @ts-ignore
if (globalThis.Rect === undefined) {
  globalThis.Rect = class {
    static name = 'JSRect'
    constructor(value) {
      return new __Rect__(value);
    }
    static create(value) {
      getUINativeModule().loadNativeModule('Rect');
      let module = globalThis.requireNapi('arkui.components.arkrect');
      module.exportView();
      module.loadComponent();
      getUINativeModule().rect.create(value);
    }
  }
}

// @ts-ignore
if (globalThis.Line === undefined) {
  globalThis.Line = {
    create: function(value) {
      getUINativeModule().loadNativeModule('Line');
      let module = globalThis.requireNapi('arkui.components.arkline');
      module.exportView();
      module.loadComponent();
      getUINativeModule().line.create(value);
    },
    name: 'JSLine'
  }
}

// @ts-ignore
if (globalThis.Polyline === undefined) {
  globalThis.Polyline = {
    create: function(value) {
      getUINativeModule().loadNativeModule('Polyline');
      let module = globalThis.requireNapi('arkui.components.arkpolyline');
      module.exportView();
      module.loadComponent();
      getUINativeModule().polyline.create(value);
    },
    name: 'JSPolyline'
  }
}

// @ts-ignore
if (globalThis.Path === undefined) {
  globalThis.Path = class {
    static name = 'JSPath'
    constructor(value) {
      return new __Path__(value);
    }
    static create(value) {
      getUINativeModule().loadNativeModule('Path');
      let module = globalThis.requireNapi('arkui.components.arkpath');
      module.exportView();
      module.loadComponent();
      getUINativeModule().path.create(value);
    }
  }
}

// @ts-ignore
if (globalThis.Polygon === undefined) {
  globalThis.Polygon = {
    create: function(params) {
      getUINativeModule().loadNativeModule('Polygon');
      let module = globalThis.requireNapi('arkui.components.arkpolygon');
      module.exportView();
      module.loadComponent();
      getUINativeModule().polygon.create(params);
    },
    name: 'JSPolygon'
  }
}

// @ts-ignore
if (globalThis.GridRow === undefined) {
  globalThis.GridRow = {
    create: function(params) {
      getUINativeModule().loadNativeModule('GridRow');
      let module = globalThis.requireNapi('arkui.components.arkgridrow');
      module.exportView();
      module.loadComponent();
      globalThis.GridRow.create(params);
    },
    name: 'JSGridRow'
  }
}

// @ts-ignore
if (globalThis.GridCol === undefined) {
  globalThis.GridCol = {
    create: function(params) {
      getUINativeModule().loadNativeModule('GridCol');
      let module = globalThis.requireNapi('arkui.components.arkgridcol');
      module.exportView();
      module.loadComponent();
      globalThis.GridCol.create(params);
    },
    name: 'JSGridCol'
  }
}

// @ts-ignore
if (globalThis.FolderStack === undefined) {
  globalThis.FolderStack = {
    create: function(params) {
      getUINativeModule().loadNativeModule('FolderStack');
      let module = globalThis.requireNapi('arkui.components.arkfolderstack');
      module.exportView();
      getUINativeModule().folderStack.create(params);
    },
    name: 'JSFolderStack'
  };
}

// @ts-ignore
if (globalThis.TimePicker === undefined) {
  globalThis.TimePicker = {
    create: function(params) {
      getUINativeModule().loadNativeModule('TimePicker');
      const module = globalThis.requireNapi('arkui.components.arktimepicker');
      module.exportView();
      getUINativeModule().timePicker.create(params);
    },
 	name: 'JSTimePicker'
  }
}

// @ts-ignore
if (globalThis.TimePickerDialog === undefined) {
  globalThis.TimePickerDialog = class {
    static name = 'JSTimePickerDialog'
    constructor() {}
    static show(params) {
      getUINativeModule().loadNativeModule('TimePickerDialog');
      let module = globalThis.requireNapi('arkui.components.arktimepicker');
      module.exportViewDialog();
      getUINativeModule().timePickerDialog.show(params);
    }
  }
}

// @ts-ignore
if (globalThis.TextPicker === undefined) {
  globalThis.TextPicker = {
    create: function(params) {
      getUINativeModule().loadNativeModule('TextPicker');
      const module = globalThis.requireNapi('arkui.components.arktextpicker');
      module.exportView();
      module.loadComponent();
      getUINativeModule().textpicker.create(params);
    },
 	name: 'JSTextPicker'
  }
}

// @ts-ignore
if (globalThis.TextPickerDialog === undefined) {
  globalThis.TextPickerDialog = class {
    static name = 'JSTextPickerDialog'
    constructor() {}
    static show(params) {
      getUINativeModule().loadNativeModule('TextPickerDialog');
      let module = globalThis.requireNapi('arkui.components.arktextpicker');
      module.exportViewDialog();
      getUINativeModule().textPickerDialog.show(params);
    }
  }
}

if (globalThis.TextInput === undefined) {
  globalThis.TextInput = {
    create: function(params) {
      getUINativeModule().loadNativeModule('TextInput');
      let module = globalThis.requireNapi('arkui.components.arktextinput');
      module.exportView();
      module.loadComponent();
      getUINativeModule().textInput.create(params);
    },
    name: 'JSTextInput'
  }
}

// @ts-ignore
if (globalThis.TextArea === undefined) {
  globalThis.TextArea = {
    create: function(params) {
      getUINativeModule().loadNativeModule('TextArea');
      let module = globalThis.requireNapi('arkui.components.arktextarea');
      module.exportView();
      module.loadComponent();
      getUINativeModule().textArea.create(params);
    },
    name: 'JSTextArea'
  }
}

// @ts-ignore
if (globalThis.DataPanel === undefined) {
  globalThis.DataPanel = {
    create: function(params) {
      getUINativeModule().loadNativeModule('DataPanel');
      let module = globalThis.requireNapi('arkui.components.arkdatapanel');
      module.exportView();
      module.loadComponent();
      getUINativeModule().dataPanel.create(params);
    },
    name: 'JSDataPanel'
  }
}

// @ts-ignore
if (globalThis.SymbolGlyph === undefined) {
  globalThis.SymbolGlyph = {
    create: function(params) {
      getUINativeModule().loadNativeModule('SymbolGlyph');
      let module = globalThis.requireNapi('arkui.components.arksymbolglyph');
      module.exportView();
      module.loadComponent();
      getUINativeModule().symbolGlyph.create(params);
    },
    name: 'JSSymbolGlyph'
  };
}

// @ts-ignore
if (globalThis.SymbolSpan === undefined) {
  globalThis.SymbolSpan = {
    create: function(params) {
      getUINativeModule().loadNativeModule('SymbolSpan');
      let module = globalThis.requireNapi('arkui.components.arksymbolspan');
      module.exportView();
      module.loadComponent();
      getUINativeModule().symbolSpan.jsCreate(params);
    },
    name: 'JSSymbolSpan'
  };
}

// @ts-ignore
if (globalThis.PatternLock === undefined) {
  globalThis.PatternLock = {
    create: function(value) {
      getUINativeModule().loadNativeModule('PatternLock');
      let module = globalThis.requireNapi('arkui.components.arkpatternlock');
      module.exportView();
      getUINativeModule().patternlock.create(value);
    },
    name: 'JSPatternLock'
  }
}

// @ts-ignore
if (globalThis.Blank === undefined) {
  globalThis.Blank = {
    create: function(value) {
      getUINativeModule().loadNativeModule('Blank');
      let module = globalThis.requireNapi('arkui.components.arkblank');
      module.exportView();
      module.loadComponent();
      getUINativeModule().blank.create(value);
    },
    name: 'JSBlank'
  }
}

// @ts-ignore
if (globalThis.Divider === undefined) {
  globalThis.Divider = {
    create: function(params) {
      getUINativeModule().loadNativeModule('Divider');
      let module = globalThis.requireNapi('arkui.components.arkdivider');
      module.exportView();
      module.loadComponent();
      getUINativeModule().divider.create(params);
    },
    name: 'JSDivider'
  }
}

// @ts-ignore
if (globalThis.RelativeContainer === undefined) {
  globalThis.RelativeContainer = {
    create: function() {
      getUINativeModule().loadNativeModule('RelativeContainer');
      let module = globalThis.requireNapi('arkui.components.arkrelativecontainer');
      module.exportView();
      module.loadComponent();
      getUINativeModule().relativeContainer.create();
    },
    name: 'JSRelativeContainer'
  }
}

if (globalThis.GridContainer === undefined) {
  globalThis.GridContainer = {
    create: function(value) {
      getUINativeModule().loadNativeModule('GridContainer');
      let module = globalThis.requireNapi('arkui.components.arkgridcontainer');
      module.exportView();
      module.loadComponent();
      getUINativeModule().gridContainer.create(value);
    },
    name: 'JSGridContainer'
  }
}

// @ts-ignore
if (globalThis.WaterFlow === undefined) {
  globalThis.WaterFlow = {
    create: function(params) {
      getUINativeModule().loadNativeModule('WaterFlow');
      let module = globalThis.requireNapi('arkui.components.arkwaterflow');
      module.exportView();
      getUINativeModule().waterFlow.create(params);
    }
  }
}

// @ts-ignore
if (globalThis.LazyVWaterFlowLayout === undefined) {
  globalThis.LazyVWaterFlowLayout = {
    create: function() {
      getUINativeModule().loadNativeModule('LazyVWaterFlowLayout');
      let module = globalThis.requireNapi('arkui.components.arklazywaterflowlayout');
      module.exportView();
      module.loadComponent();
      getUINativeModule().lazyVWaterFlowLayout.create();
    }
  }
}

// @ts-ignore
if (globalThis.FlowItem === undefined) {
  globalThis.FlowItem = {
    create: function(params) {
      getUINativeModule().loadNativeModule('FlowItem');
      let module = globalThis.requireNapi('arkui.components.arkflowitem');
      module.exportView();
      getUINativeModule().flowItem.create();
    }
  }
}

// @ts-ignore
if (globalThis.Menu === undefined) {
  globalThis.Menu = {
    create: function (params) {
      getUINativeModule().loadNativeModule('Menu');
      let module = globalThis.requireNapi('arkui.components.arkmenu');
      module.exportView();
      getUINativeModule().menu.create();
    },
    name: 'JSMenu'
  }
}


// @ts-ignore
if (globalThis.MenuItem === undefined) {
  globalThis.MenuItem = {
    create: function (params) {
      getUINativeModule().loadNativeModule('MenuItem');
      let module = globalThis.requireNapi('arkui.components.arkmenuitem');
      module.exportView();
      getUINativeModule().menuitem.create(params);
    },
    name: 'JSMenuItem'
  }
}

// @ts-ignore
if (globalThis.MenuItemGroup === undefined) {
  globalThis.MenuItemGroup = {
    create: function (params) {
      getUINativeModule().loadNativeModule('MenuItemGroup');
      let module = globalThis.requireNapi('arkui.components.arkmenuitemgroup');
      module.exportView();
      getUINativeModule().menuitemgroup.create(params);
    },
    name: 'JSMenuItemGroup'
  }
}

// @ts-ignore
if (globalThis.Counter === undefined) {
  globalThis.Counter = {
    create: function() {
      getUINativeModule().loadNativeModule('Counter');
      let module = globalThis.requireNapi('arkui.components.arkcounter');
      module.exportView();
      module.loadComponent();
      getUINativeModule().counter.create();
    },
    name : 'JSCounter'
  };
}

if (globalThis.RichEditor === undefined) {
  globalThis.RichEditor = {
    create: function(params) {
      getUINativeModule().loadNativeModule('Richeditor');
      let module = globalThis.requireNapi('arkui.components.arkricheditor');
      module.exportView();
      getUINativeModule().richEditor.create(params);
    },
    name: 'JSRichEditor'
  };
}

// @ts-ignore
if (globalThis.Search === undefined) {
  globalThis.Search = {
    create: function (params) {
      getUINativeModule().loadNativeModule("Search");
      var module = globalThis.requireNapi('arkui.components.arksearch');
      module.exportView();
      module.loadComponent();
      getUINativeModule().search.jsCreate(params);
    },
    name: 'JSSearch'
  };
}

// @ts-ignore
if (globalThis.Badge === undefined) {
  globalThis.Badge = {
    create: function (params) {
      getUINativeModule().loadNativeModule("Badge");
      let module = globalThis.requireNapi('arkui.components.arkbadge');
      module.exportView();
      module.loadComponent();
      getUINativeModule().badge.create(params);
    },
    name: 'JSBadge'
  };
}

// @ts-ignore
if (globalThis.ImageSpan === undefined) {
  globalThis.ImageSpan = {
    create: function (params) {
      getUINativeModule().loadNativeModule("ImageSpan");
      var module = globalThis.requireNapi('arkui.components.arkimagespan');
      module.exportView();
      module.loadComponent();
      if (!ViewStackProcessor.UsesNewPipeline()) {
        return;
      }
      Image.createImageSpan(params);
      getUINativeModule().imageSpan.create();
    },
    name: 'JSImageSpan'
  };
}

// @ts-ignore
if (globalThis.TextTimer === undefined) {
  globalThis.TextTimer = {
    create: function(params) {
      getUINativeModule().loadNativeModule('TextTimer');
      let module = globalThis.requireNapi('arkui.components.arktexttimer');
      module.exportView();
      module.loadComponent();
      getUINativeModule().texttimer.create(params?.isCountDown, params?.count, params?.controller, params?.startTime);
    },
    name: 'JSTextTimer'
  }
}

// @ts-ignore
if (globalThis.Progress === undefined) {
  globalThis.Progress = {
    create: function(value) {
      getUINativeModule().loadNativeModule('Progress');
      let module = globalThis.requireNapi('arkui.components.arkprogress');
      module.exportView();
      module.loadComponent();
      getUINativeModule().progress.create(value?.value, value?.total, value?.style, value?.type);
    },
    name: 'JSProgress'
  }
}

// @ts-ignore
if (globalThis.TextClock === undefined) {
  globalThis.TextClock = {
    create: function (params) {
      getUINativeModule().loadNativeModule("TextClock");
      let module = globalThis.requireNapi('arkui.components.arktextclock');
      module.exportView();
      module.loadComponent();
      getUINativeModule().textclock.create(params);
    },
    name: 'JSTextClock'
  };
}

// @ts-ignore
if (globalThis.Toggle === undefined) {
  globalThis.Toggle = {
    create: function (params) {
      getUINativeModule().loadNativeModule('Toggle');
      let module = globalThis.requireNapi('arkui.components.arktoggle');
      module.exportView();
      module.loadComponent();
      getUINativeModule().toggle.create(params);
    },
    name: 'JSToggle'
  };
}

// @ts-ignore
if (globalThis.Swiper === undefined) {
  globalThis.Swiper = {
    create: function(controller) {
      getUINativeModule().loadNativeModule('Swiper');
      let module = globalThis.requireNapi('arkui.components.arkswiper');
      module.exportView();
      module.loadComponent();
      getUINativeModule().swiper.setSwiperInitialize(true, controller);
    },
    name: 'JSSwiper'
  };
}

// @ts-ignore
if (globalThis.IndicatorComponent === undefined) {
  globalThis.IndicatorComponent = {
    create: function(controller) {
      getUINativeModule().loadNativeModule('SwiperIndicator');
      let module = globalThis.requireNapi('arkui.components.arkswiperindicator');
      module.exportView();
      module.loadComponent();
      getUINativeModule().indicatorComponent.create(controller);
    },
    name: 'JSIndicator'
  };
}

// @ts-ignore
if (globalThis.Tabs === undefined) {
  globalThis.Tabs = {
    create: function(params) {
      getUINativeModule().loadNativeModule('Tabs');
      let module = globalThis.requireNapi('arkui.components.arktabs');
      module.exportView();
      module.loadComponent();
      getUINativeModule().tabs.create(params);
    },
    name: 'JSTabs'
  };
}

// @ts-ignore
if (globalThis.TabContent === undefined) {
  globalThis.TabContent = {
    create: function(params) {
      getUINativeModule().loadNativeModule('TabContent');
      let module = globalThis.requireNapi('arkui.components.arktabcontent');
      module.exportView();
      module.loadComponent();
      getUINativeModule().tabContent.create(params);
    },
    name: 'JSTabContent'
  };
}

// @ts-ignore
if (globalThis.XComponent === undefined) {
  globalThis.XComponent = {
    create: function(params) {
      getUINativeModule().loadNativeModule('XComponent');
      let module = globalThis.requireNapi('arkui.components.arkxcomponent');
      module.exportView();
      module.loadComponent();
      getUINativeModule().xComponent.create(params);
    },
    name: 'JSXComponent'
  }
}

// @ts-ignore
if (globalThis.LazyColumnLayout === undefined) {
  globalThis.LazyColumnLayout = {
    create: function () {
      getUINativeModule().loadNativeModule('LazyColumnLayout');
      let module = globalThis.requireNapi('arkui.components.arklazycolumnlayout');
      module.exportView();
      module.loadComponent();
      getUINativeModule().lazyColumnLayout.create();
    }
  }
}

// @ts-ignore
if (globalThis.LoadingProgress === undefined) {
  globalThis.LoadingProgress = {
    create: function(params) {
      getUINativeModule().loadNativeModule('LoadingProgress');
      let module = globalThis.requireNapi('arkui.components.arkloadingprogress');
      module.exportView();
      module.loadComponent();
      getUINativeModule().loadingProgress.create(params);
    },
 	name: 'JSLoadingProgress'
  };
}

// @ts-ignore
if (globalThis.ImageAnimator === undefined) {
  globalThis.ImageAnimator = {
    create: function () {
      getUINativeModule().loadNativeModule('ImageAnimator');
      let module = globalThis.requireNapi('arkui.components.arkimageanimator');
      module.exportView();
      module.loadComponent();
      getUINativeModule().imageAnimator.create();
    },
    name: 'JSImageAnimator'
  }
}

// @ts-ignore
if (globalThis.Grid === undefined) {
  globalThis.Grid = {
    create: function(scroller, options) {
      getUINativeModule().loadNativeModule('Grid');
      let module = globalThis.requireNapi('arkui.components.arkgrid');
      module.exportView();
      module.loadComponent();
      getUINativeModule().grid.create(scroller, options);
    },
    name: 'Grid'
  }
}

// @ts-ignore
if (globalThis.GridItem === undefined) {
  globalThis.GridItem = {
    create: function(func, isLazy, style) {
      getUINativeModule().loadNativeModule('GridItem');
      let module = globalThis.requireNapi('arkui.components.arkgriditem');
      module.exportView();
      module.loadComponent();
      getUINativeModule().gridItem.create(func, isLazy, style);
    },
    name: 'GridItem'
  }
}

// @ts-ignore
if (globalThis.DatePicker === undefined) {
  globalThis.DatePicker = {
    create: function(params) {
      getUINativeModule().loadNativeModule('DatePicker');
      const module = globalThis.requireNapi('arkui.components.arkdatepicker');
      module.exportView();
      module.loadComponent();
      getUINativeModule().datePicker.create(params);
    },
    name: 'JSDatePicker'
  }
}

// @ts-ignore
if (globalThis.DatePickerDialog === undefined) {
  globalThis.DatePickerDialog = class {
    static name = 'JSDatePickerDialog'
    constructor() {}
    static show(params) {
      getUINativeModule().loadNativeModule('DatePickerDialog');
      let module = globalThis.requireNapi('arkui.components.arkdatepicker');
      module.exportViewDialog();
      getUINativeModule().datePickerDialog.show(params);
    }
  }
}

// @ts-ignore
if (globalThis.LazyVGridLayout === undefined) {
  globalThis.LazyVGridLayout = {
    create: function () {
      getUINativeModule().loadNativeModule('LazyVGridLayout');
      let module = globalThis.requireNapi('arkui.components.arklazygridlayout');
      module.exportView();
      module.loadComponent();
      getUINativeModule().lazyVGridLayout.create();
    },
    name: 'JSLazyVGridLayout'
  };
}

// @ts-ignore
if (globalThis.Select === undefined) {
  globalThis.Select = {
    create: function (params) {
      getUINativeModule().loadNativeModule('Select');
      let module = globalThis.requireNapi('arkui.components.arkselect');
      module.exportView();
      module.loadComponent();
      getUINativeModule().select.create(params);
    },
    name: 'JSSelect'
  }
}

// @ts-ignore
if (globalThis.Panel === undefined) {
  globalThis.Panel = {
    create: function(params) {
      getUINativeModule().loadNativeModule('Panel');
      let module = globalThis.requireNapi('arkui.components.arkpanel');
      module.exportView();
      module.loadComponent();
      getUINativeModule().panel.create(params);
    },
    name: 'JSPanel'
  }
}

// @ts-ignore
if (globalThis.ToolBarItem === undefined) {
  globalThis.ToolBarItem = {
    create: function(params) {
      getUINativeModule().loadNativeModule('ToolBarItem');
      let module = globalThis.requireNapi('arkui.components.arktoolbaritem');
      module.exportView();
      module.loadComponent();
      getUINativeModule().toolBarItem.create(params);
    },
    name: 'JSToolBarItem'
  };
}
