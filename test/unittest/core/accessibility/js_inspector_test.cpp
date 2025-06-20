/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "core/accessibility/js_inspector/inspect_badge.h"
#include "core/accessibility/js_inspector/inspect_button.h"
#include "core/accessibility/js_inspector/inspect_camera.h"
#include "core/accessibility/js_inspector/inspect_canvas.h"
#include "core/accessibility/js_inspector/inspect_chart.h"
#include "core/accessibility/js_inspector/inspect_dialog.h"
#include "core/accessibility/js_inspector/inspect_div.h"
#include "core/accessibility/js_inspector/inspect_divider.h"
#include "core/accessibility/js_inspector/inspect_form.h"
#include "core/accessibility/js_inspector/inspect_grid_column.h"
#include "core/accessibility/js_inspector/inspect_grid_container.h"
#include "core/accessibility/js_inspector/inspect_grid_row.h"
#include "core/accessibility/js_inspector/inspect_image_animator.h"
#include "core/accessibility/js_inspector/inspect_image.h"
#include "core/accessibility/js_inspector/inspect_input.h"
#include "core/accessibility/js_inspector/inspect_label.h"
#include "core/accessibility/js_inspector/inspect_list_item_group.h"
#include "core/accessibility/js_inspector/inspect_list_item.h"
#include "core/accessibility/js_inspector/inspect_list.h"
#include "core/accessibility/js_inspector/inspect_marquee.h"
#include "core/accessibility/js_inspector/inspect_menu.h"
#include "core/accessibility/js_inspector/inspect_navigation_bar.h"
#include "core/accessibility/js_inspector/inspect_node.h"
#include "core/accessibility/js_inspector/inspect_option.h"
#include "core/accessibility/js_inspector/inspect_panel.h"
#include "core/accessibility/js_inspector/inspect_picker.h"
#include "core/accessibility/js_inspector/inspect_picker_view.h"
#include "core/accessibility/js_inspector/inspect_piece.h"
#include "core/accessibility/js_inspector/inspect_popup.h"
#include "core/accessibility/js_inspector/inspect_progress.h"
#include "core/accessibility/js_inspector/inspect_qrcode.h"
#include "core/accessibility/js_inspector/inspect_rating.h"
#include "core/accessibility/js_inspector/inspect_refresh.h"
#include "core/accessibility/js_inspector/inspect_search.h"
#include "core/accessibility/js_inspector/inspect_select.h"
#include "core/accessibility/js_inspector/inspect_slider.h"
#include "core/accessibility/js_inspector/inspect_span.h"
#include "core/accessibility/js_inspector/inspect_stack.h"
#include "core/accessibility/js_inspector/inspect_stepper_item.h"
#include "core/accessibility/js_inspector/inspect_stepper.h"
#include "core/accessibility/js_inspector/inspect_swiper.h"
#include "core/accessibility/js_inspector/inspect_switch.h"
#include "core/accessibility/js_inspector/inspect_tab_bar.h"
#include "core/accessibility/js_inspector/inspect_tab_content.h"
#include "core/accessibility/js_inspector/inspect_tabs.h"
#include "core/accessibility/js_inspector/inspect_text.h"
#include "core/accessibility/js_inspector/inspect_textarea.h"
#include "core/accessibility/js_inspector/inspect_toggle.h"
#include "core/accessibility/js_inspector/inspect_toolbar_item.h"
#include "core/accessibility/js_inspector/inspect_toolbar.h"
#include "core/accessibility/js_inspector/inspect_video.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
namespace {
constexpr char INSPECTOR_ATTRS[] = "$attrs";
constexpr char INSPECTOR_STYLES[] = "$styles";
}
class JSInspectorTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

    void CheckToggleAttrAndStyle(InspectToggle& inspectToggle, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 3;
        uint16_t stylesSizeInsert = 4;
        uint16_t insertTwo = 2;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectToggle.attrs_["checked"], "false");
        EXPECT_EQ(inspectToggle.attrs_["disabled"], "false");
        EXPECT_EQ(inspectToggle.attrs_["focusable"], "false");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectToggle.styles_["color"], "#ff007dff");
            EXPECT_EQ(inspectToggle.styles_["font-size"], "16px");
            stylesSizeInsert += insertTwo;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectToggle.styles_["color"], "#e5ffffff");
            EXPECT_EQ(inspectToggle.styles_["font-size"], "18px");
            stylesSizeInsert += insertTwo;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectToggle.styles_["color"], "#ff45a5ff");
            EXPECT_EQ(inspectToggle.styles_["font-size"], "16px");
            stylesSizeInsert += insertTwo;
        }
        EXPECT_EQ(inspectToggle.styles_["allow-scale"], "true");
        EXPECT_EQ(inspectToggle.styles_["font-style"], "normal");
        EXPECT_EQ(inspectToggle.styles_["font-weight"], "normal");
        EXPECT_EQ(inspectToggle.styles_["font-family"], "sans-serif");
        EXPECT_EQ(inspectToggle.styles_.find("border"), inspectToggle.styles_.end());
        EXPECT_EQ(inspectToggle.styles_.find("border-left-style"), inspectToggle.styles_.end());
        EXPECT_EQ(inspectToggle.styles_.find("border-top-style"), inspectToggle.styles_.end());
        EXPECT_EQ(inspectToggle.styles_.find("border-right-style"), inspectToggle.styles_.end());
        EXPECT_EQ(inspectToggle.styles_.find("border-bottom-style"), inspectToggle.styles_.end());
        EXPECT_EQ(inspectToggle.styles_.find("border-left-width"), inspectToggle.styles_.end());
        EXPECT_EQ(inspectToggle.styles_.find("border-top-width"), inspectToggle.styles_.end());
        EXPECT_EQ(inspectToggle.styles_.find("border-right-width"), inspectToggle.styles_.end());
        EXPECT_EQ(inspectToggle.styles_.find("border-bottom-width"), inspectToggle.styles_.end());
        EXPECT_EQ(inspectToggle.styles_.find("border-left-color"), inspectToggle.styles_.end());
        EXPECT_EQ(inspectToggle.styles_.find("border-top-color"), inspectToggle.styles_.end());
        EXPECT_EQ(inspectToggle.styles_.find("border-right-color"), inspectToggle.styles_.end());
        EXPECT_EQ(inspectToggle.styles_.find("border-bottom-color"), inspectToggle.styles_.end());
        EXPECT_EQ(inspectToggle.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectToggle.styles_.size(), stylesSize + stylesSizeInsert);
    }

    void CheckTextAreaAttrAndStyle(InspectTextArea& inspectTextArea, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 4;
        uint16_t stylesSizeInsert = 3;
        uint16_t insertThree = 3;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectTextArea.attrs_["extend"], "false");
        EXPECT_EQ(inspectTextArea.attrs_["showcounter"], "false");
        EXPECT_EQ(inspectTextArea.attrs_["disabled"], "false");
        EXPECT_EQ(inspectTextArea.attrs_["focusable"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectTextArea.styles_["color"], "#e6000000");
            EXPECT_EQ(inspectTextArea.styles_["font-size"], "16px");
            EXPECT_EQ(inspectTextArea.styles_["placeholder-color"], "#99000000");
            stylesSizeInsert += insertThree;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectTextArea.styles_["color"], "#e6ffffff");
            EXPECT_EQ(inspectTextArea.styles_["font-size"], "18px");
            EXPECT_EQ(inspectTextArea.styles_["placeholder-color"], "#99ffffff");
            stylesSizeInsert += insertThree;
        }
        EXPECT_EQ(inspectTextArea.styles_["allow-scale"], "true");
        EXPECT_EQ(inspectTextArea.styles_["font-weight"], "normal");
        EXPECT_EQ(inspectTextArea.styles_["font-family"], "sans-serif");
        EXPECT_EQ(inspectTextArea.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectTextArea.styles_.size(), stylesSize + stylesSizeInsert);
    }

    void CheckTextAttrAndStyle(InspectText& inspectText, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 2;
        uint16_t stylesSizeInsert = 11;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectText.attrs_["disabled"], "false");
        EXPECT_EQ(inspectText.attrs_["focusable"], "false");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectText.styles_["color"], "#e5000000");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectText.styles_["color"], "#e5ffffff");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectText.styles_["color"], "#ffffffff");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectText.styles_["font-size"], "30px");
        EXPECT_EQ(inspectText.styles_["allow-scale"], "true");
        EXPECT_EQ(inspectText.styles_["letter-spacing"], "0px");
        EXPECT_EQ(inspectText.styles_["font-style"], "normal");
        EXPECT_EQ(inspectText.styles_["font-weight"], "normal");
        EXPECT_EQ(inspectText.styles_["text-decoration"], "none");
        EXPECT_EQ(inspectText.styles_["text-align"], "start");
        EXPECT_EQ(inspectText.styles_["line-height"], "0px");
        EXPECT_EQ(inspectText.styles_["text-overflow"], "clip");
        EXPECT_EQ(inspectText.styles_["font-family"], "sans-serif");
        EXPECT_EQ(inspectText.styles_["font-size-step"], "1px");
        EXPECT_EQ(inspectText.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectText.styles_.size(), stylesSize + stylesSizeInsert);
    }

    void CheckTabBarAttrAndStyle(InspectTabBar& inspectTabBar, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 3;
        uint16_t stylesSizeInsert = 0;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectTabBar.attrs_["mode"], "scrollable");
        EXPECT_EQ(inspectTabBar.attrs_["disabled"], "false");
        EXPECT_EQ(inspectTabBar.attrs_["focusable"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectTabBar.styles_["height"], "100px");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectTabBar.styles_["height"], "60px");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectTabBar.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectTabBar.styles_.size(), stylesSize + stylesSizeInsert);
    }

    void CheckSwiperAttrAndStyle(InspectSwiper& inspectSwiper, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 14;
        uint16_t stylesSizeInsert = 1;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectSwiper.attrs_["index"], "0");
        EXPECT_EQ(inspectSwiper.attrs_["autoplay"], "false");
        EXPECT_EQ(inspectSwiper.attrs_["interval"], "3000");
        EXPECT_EQ(inspectSwiper.attrs_["indicator"], "true");
        EXPECT_EQ(inspectSwiper.attrs_["digital"], "false");
        EXPECT_EQ(inspectSwiper.attrs_["indicatormask"], "false");
        EXPECT_EQ(inspectSwiper.attrs_["indicatordisabled"], "false");
        EXPECT_EQ(inspectSwiper.attrs_["loop"], "true");
        EXPECT_EQ(inspectSwiper.attrs_["vertical"], "false");
        EXPECT_EQ(inspectSwiper.attrs_["disabled"], "false");
        EXPECT_EQ(inspectSwiper.attrs_["focusable"], "true");
        EXPECT_EQ(inspectSwiper.attrs_["cachedsize"], "-1");
        EXPECT_EQ(inspectSwiper.attrs_["scrolleffect"], "spring");
        EXPECT_EQ(inspectSwiper.attrs_["displaymode"], "stretch");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectSwiper.styles_["indicator-selected-color"], "#ff007dff");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::TV || deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectSwiper.styles_["indicator-selected-color"], "#ffffffff");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectSwiper.styles_["indicator-size"], "4px");
        EXPECT_EQ(inspectSwiper.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectSwiper.styles_.size(), stylesSize + stylesSizeInsert);
    }

    void CheckSliderAttrAndStyle(InspectSlider& inspectSlider, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 10;
        uint16_t stylesSizeInsert = 1;
        uint16_t insertTwo = 2;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectSlider.attrs_["min"], "0");
        EXPECT_EQ(inspectSlider.attrs_["max"], "100");
        EXPECT_EQ(inspectSlider.attrs_["step"], "1");
        EXPECT_EQ(inspectSlider.attrs_["value"], "0");
        EXPECT_EQ(inspectSlider.attrs_["type"], "continuous");
        EXPECT_EQ(inspectSlider.attrs_["mode"], "outset");
        EXPECT_EQ(inspectSlider.attrs_["showsteps"], "false");
        EXPECT_EQ(inspectSlider.attrs_["showtips"], "false");
        EXPECT_EQ(inspectSlider.attrs_["disabled"], "false");
        EXPECT_EQ(inspectSlider.attrs_["focusable"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectSlider.styles_["color"], "#19000000");
            EXPECT_EQ(inspectSlider.styles_["selected-color"], "#ff007dff");
            stylesSizeInsert += insertTwo;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectSlider.styles_["color"], "#33ffffff");
            EXPECT_EQ(inspectSlider.styles_["selected-color"], "#ff0d9ffb");
            stylesSizeInsert += insertTwo;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectSlider.styles_["color"], "#26ffffff");
            EXPECT_EQ(inspectSlider.styles_["selected-color"], "#ff007dff");
            stylesSizeInsert += insertTwo;
        }
        EXPECT_EQ(inspectSlider.styles_["block-color"], "#ffffff");
        EXPECT_EQ(inspectSlider.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectSlider.styles_.size(), stylesSize + stylesSizeInsert);
    }

    void CheckRefreshAttrAndStyle(InspectRefresh& inspectRefresh, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 5;
        uint16_t stylesSizeInsert = 3;
        uint16_t insertTwo = 2;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectRefresh.attrs_["refreshing"], "false");
        EXPECT_EQ(inspectRefresh.attrs_["type"], "auto");
        EXPECT_EQ(inspectRefresh.attrs_["lasttime"], "false");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectRefresh.attrs_["friction"], "42");
            attrsSizeInsert++;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectRefresh.styles_["friction"], "62");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectRefresh.attrs_["disabled"], "false");
        EXPECT_EQ(inspectRefresh.attrs_["focusable"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectRefresh.styles_["background-color"], "white");
            EXPECT_EQ(inspectRefresh.styles_["progress-color"], "black");
            stylesSizeInsert += insertTwo;
        } else {
            EXPECT_EQ(inspectRefresh.styles_["background-color"], "black");
            EXPECT_EQ(inspectRefresh.styles_["progress-color"], "white");
            stylesSizeInsert += insertTwo;
        }
        EXPECT_EQ(inspectRefresh.styles_["min-width"], "0");
        EXPECT_EQ(inspectRefresh.styles_["min-height"], "0");
        EXPECT_EQ(inspectRefresh.styles_["box-shadow"], "0");
        EXPECT_EQ(inspectRefresh.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectRefresh.styles_.size(), stylesSize + stylesSizeInsert);
    }

    void CheckRatingAttrAndStyle(InspectRating& inspectRating, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 6;
        uint16_t stylesSizeInsert = 1;
        uint16_t insertTwo = 2;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectRating.attrs_["numstars"], "5");
        EXPECT_EQ(inspectRating.attrs_["rating"], "0");
        EXPECT_EQ(inspectRating.attrs_["stepsize"], "0.5");
        EXPECT_EQ(inspectRating.attrs_["indicator"], "false");
        EXPECT_EQ(inspectRating.attrs_["disabled"], "false");
        EXPECT_EQ(inspectRating.attrs_["focusable"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectRating.styles_["width"], "120px");
            EXPECT_EQ(inspectRating.styles_["height"], "24px");
            stylesSizeInsert += insertTwo;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectRating.styles_["width"], "360px");
            EXPECT_EQ(inspectRating.styles_["height"], "72px");
            stylesSizeInsert += insertTwo;
        }
        EXPECT_EQ(inspectRating.styles_["rtl-flip"], "true");
        EXPECT_EQ(inspectRating.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectRating.styles_.size(), stylesSize + stylesSizeInsert);
    }

    void CheckProgressAttrAndStyle(InspectProgress& inspectProgress, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 5;
        uint16_t stylesSizeInsert = 1;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectProgress.attrs_["type"], "horizontal");
        EXPECT_EQ(inspectProgress.attrs_["focusable"], "true");
        EXPECT_EQ(inspectProgress.attrs_["percent"], "0");
        EXPECT_EQ(inspectProgress.attrs_["secondarypercent"], "0");
        EXPECT_EQ(inspectProgress.attrs_["clockwise"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectProgress.styles_["color"], "#ff007dff");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectProgress.styles_["color"], "#e5ffffff");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectProgress.styles_["color"], "#ff45a5ff");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectProgress.styles_["stroke-width"], "4px");
        EXPECT_EQ(inspectProgress.styles_.find("background-size"), inspectProgress.styles_.end());
        EXPECT_EQ(inspectProgress.styles_.find("background-repeat"), inspectProgress.styles_.end());
        EXPECT_EQ(inspectProgress.styles_.find("background-position"), inspectProgress.styles_.end());
        EXPECT_EQ(inspectProgress.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectProgress.styles_.size(), stylesSize + stylesSizeInsert);
    }

    void CheckButtonAttrAndStyle(InspectButton& inspectButton, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 4;
        uint16_t stylesSizeInsert = 4;
        uint16_t insertTwo = 2;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectButton.attrs_["placement"], "end");
        EXPECT_EQ(inspectButton.attrs_["waiting"], "false");
        EXPECT_EQ(inspectButton.attrs_["disabled"], "false");
        EXPECT_EQ(inspectButton.attrs_["focusable"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectButton.styles_["text-color"], "#ff007dff");
            EXPECT_EQ(inspectButton.styles_["font-size"], "16px");
            stylesSizeInsert += insertTwo;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectButton.styles_["text-color"], "#e5ffffff");
            EXPECT_EQ(inspectButton.styles_["font-size"], "18px");
            stylesSizeInsert += insertTwo;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectButton.styles_["text-color"], "#ff45a5ff");
            EXPECT_EQ(inspectButton.styles_["font-size"], "16px");
            stylesSizeInsert += insertTwo;
        }
        EXPECT_EQ(inspectButton.styles_["allow-scale"], "true");
        EXPECT_EQ(inspectButton.styles_["font-style"], "normal");
        EXPECT_EQ(inspectButton.styles_["font-weight"], "normal");
        EXPECT_EQ(inspectButton.styles_["font-family"], "sans-serif");
        EXPECT_EQ(inspectButton.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectButton.styles_.size(), stylesSize + stylesSizeInsert);
    }

    void CheckDividerAttrAndStyle(InspectDivider& inspectDivider, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 1;
        uint16_t stylesSizeInsert = 10;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectDivider.attrs_["vertical"], "false");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectDivider.styles_["color"], "#08000000");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectDivider.styles_["color"], "#33ffffff");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectDivider.styles_["color"], "#33ffffff");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectDivider.styles_["stroke-width"], "1");
        EXPECT_EQ(inspectDivider.styles_["line-cap"], "butt");
        EXPECT_EQ(inspectDivider.styles_["margin-left"], "0");
        EXPECT_EQ(inspectDivider.styles_["margin-top"], "0");
        EXPECT_EQ(inspectDivider.styles_["margin-right"], "0");
        EXPECT_EQ(inspectDivider.styles_["margin-bottom"], "0");
        EXPECT_EQ(inspectDivider.styles_["display"], "flex");
        EXPECT_EQ(inspectDivider.styles_["visibility"], "visible");
        EXPECT_EQ(inspectDivider.styles_["flex-grow"], "0");
        EXPECT_EQ(inspectDivider.styles_["flex-shrink"], "1");
        EXPECT_EQ(inspectDivider.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectDivider.styles_.size(), stylesSize + stylesSizeInsert);
    }

    void CheckInputAttrAndStyle(InspectInput& inspectInput, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 6;
        uint16_t stylesSizeInsert = 3;
        uint16_t insertThree = 3;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectInput.attrs_["type"], "text");
        EXPECT_EQ(inspectInput.attrs_["checked"], "false");
        EXPECT_EQ(inspectInput.attrs_["enterkeytype"], "default");
        EXPECT_EQ(inspectInput.attrs_["showcounter"], "false");
        EXPECT_EQ(inspectInput.attrs_["disabled"], "false");
        EXPECT_EQ(inspectInput.attrs_["focusable"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectInput.styles_["color"], "#e6000000");
            EXPECT_EQ(inspectInput.styles_["font-size"], "16px");
            EXPECT_EQ(inspectInput.styles_["placeholder-color"], "#99000000");
            stylesSizeInsert += insertThree;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectInput.styles_["color"], "#e6ffffff");
            EXPECT_EQ(inspectInput.styles_["font-size"], "18px");
            EXPECT_EQ(inspectInput.styles_["placeholder-color"], "#99ffffff");
            stylesSizeInsert += insertThree;
        }
        EXPECT_EQ(inspectInput.styles_["allow-scale"], "true");
        EXPECT_EQ(inspectInput.styles_["font-weight"], "normal");
        EXPECT_EQ(inspectInput.styles_["font-family"], "sans-serif");
        EXPECT_EQ(inspectInput.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectInput.styles_.size(), stylesSize + stylesSizeInsert);
    }

    void CheckLabelAttrAndStyle(InspectLabel& inspectLabel, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 2;
        uint16_t stylesSizeInsert = 11;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectLabel.attrs_["disabled"], "false");
        EXPECT_EQ(inspectLabel.attrs_["focusable"], "false");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectLabel.styles_["color"], "#e5000000");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectLabel.styles_["color"], "#e5ffffff");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectLabel.styles_["color"], "#ffffffff");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectLabel.styles_["font-size"], "30px");
        EXPECT_EQ(inspectLabel.styles_["allow-scale"], "true");
        EXPECT_EQ(inspectLabel.styles_["letter-spacing"], "0px");
        EXPECT_EQ(inspectLabel.styles_["font-style"], "normal");
        EXPECT_EQ(inspectLabel.styles_["font-weight"], "normal");
        EXPECT_EQ(inspectLabel.styles_["text-decoration"], "none");
        EXPECT_EQ(inspectLabel.styles_["text-align"], "start");
        EXPECT_EQ(inspectLabel.styles_["line-height"], "0px");
        EXPECT_EQ(inspectLabel.styles_["text-overflow"], "clip");
        EXPECT_EQ(inspectLabel.styles_["font-family"], "sans-serif");
        EXPECT_EQ(inspectLabel.styles_["font-size-step"], "1px");
        EXPECT_EQ(inspectLabel.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectLabel.styles_.size(), stylesSize + stylesSizeInsert);
    }

    void CheckMarqueeAttrAndStyle(InspectMarquee& inspectMarquee, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 5;
        uint16_t stylesSizeInsert = 4;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectMarquee.attrs_["scrollamount"], "6");
        EXPECT_EQ(inspectMarquee.attrs_["loop"], "-1");
        EXPECT_EQ(inspectMarquee.attrs_["direction"], "left");
        EXPECT_EQ(inspectMarquee.attrs_["disabled"], "false");
        EXPECT_EQ(inspectMarquee.attrs_["focusable"], "false");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectMarquee.styles_["color"], "#e5000000");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectMarquee.styles_["color"], "#e5ffffff");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectMarquee.styles_["color"], "#ffffffff");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectMarquee.styles_["font-size"], "37.5");
        EXPECT_EQ(inspectMarquee.styles_["allow-scale"], "true");
        EXPECT_EQ(inspectMarquee.styles_["font-weight"], "normal");
        EXPECT_EQ(inspectMarquee.styles_["font-family"], "sans-serif");
        EXPECT_EQ(inspectMarquee.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectMarquee.styles_.size(), stylesSize + stylesSizeInsert);
    }
};

/**
 * @tc.name: InspectBadgeTest001
 * @tc.desc: InspectBadge::InspectBadge
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectBadgeTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectBadge inspectBadge(nodeId, tag);
    EXPECT_EQ(inspectBadge.nodeId_, nodeId);
    EXPECT_EQ(inspectBadge.tag_, tag);
}

/**
 * @tc.name: InspectBadgeTest002
 * @tc.desc: InspectBadge::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectBadgeTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectBadge inspectBadge(nodeId, tag);
    auto size = inspectBadge.attrs_.size();
    uint16_t sizeInsert = 7;
    inspectBadge.PackAttrAndStyle();
    EXPECT_EQ(inspectBadge.attrs_.size(), size + sizeInsert);
    EXPECT_EQ(inspectBadge.attrs_["placement"], "rightTop");
    EXPECT_EQ(inspectBadge.attrs_["count"], "0");
    EXPECT_EQ(inspectBadge.attrs_["visible"], "false");
    EXPECT_EQ(inspectBadge.attrs_["maxcount"], "99");
    EXPECT_EQ(inspectBadge.attrs_["config"], "BadgeConfig");
    EXPECT_EQ(inspectBadge.attrs_["disabled"], "false");
    EXPECT_EQ(inspectBadge.attrs_["focusable"], "false");
}

/**
 * @tc.name: InspectButtonTest001
 * @tc.desc: InspectButton::InspectButton
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectButtonTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectButton inspectButton(nodeId, tag);
    EXPECT_EQ(inspectButton.nodeId_, nodeId);
    EXPECT_EQ(inspectButton.tag_, tag);
}

/**
 * @tc.name: InspectButtonTest002
 * @tc.desc: InspectButton::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectButtonTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectButton inspectButton(nodeId, tag);
    auto attrsSize = inspectButton.attrs_.size();
    auto stylesSize = inspectButton.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectButton.PackAttrAndStyle();
    CheckButtonAttrAndStyle(inspectButton, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectButtonTest003
 * @tc.desc: InspectButton::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectButtonTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectButton inspectButton(nodeId, tag);
    auto attrsSize = inspectButton.attrs_.size();
    auto stylesSize = inspectButton.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectButton.PackAttrAndStyle();
    CheckButtonAttrAndStyle(inspectButton, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectButtonTest004
 * @tc.desc: InspectButton::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectButtonTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectButton inspectButton(nodeId, tag);
    auto attrsSize = inspectButton.attrs_.size();
    auto stylesSize = inspectButton.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectButton.PackAttrAndStyle();
    CheckButtonAttrAndStyle(inspectButton, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectButtonTest005
 * @tc.desc: InspectButton::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectButtonTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectButton inspectButton(nodeId, tag);
    auto attrsSize = inspectButton.attrs_.size();
    auto stylesSize = inspectButton.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectButton.PackAttrAndStyle();
    CheckButtonAttrAndStyle(inspectButton, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectButtonTest006
 * @tc.desc: InspectButton::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectButtonTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectButton inspectButton(nodeId, tag);
    auto attrsSize = inspectButton.attrs_.size();
    auto stylesSize = inspectButton.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectButton.PackAttrAndStyle();
    CheckButtonAttrAndStyle(inspectButton, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectButtonTest007
 * @tc.desc: InspectButton::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectButtonTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectButton inspectButton(nodeId, tag);
    auto attrsSize = inspectButton.attrs_.size();
    auto stylesSize = inspectButton.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectButton.PackAttrAndStyle();
    CheckButtonAttrAndStyle(inspectButton, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectCameraTest001
 * @tc.desc: InspectCamera::InspectCamera
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectCameraTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectCamera inspectCamera(nodeId, tag);
    EXPECT_EQ(inspectCamera.nodeId_, nodeId);
    EXPECT_EQ(inspectCamera.tag_, tag);
}

/**
 * @tc.name: InspectCameraTest002
 * @tc.desc: InspectCamera::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectCameraTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectCamera inspectCamera(nodeId, tag);
    auto size = inspectCamera.attrs_.size();
    uint16_t sizeInsert = 2;
    inspectCamera.PackAttrAndStyle();
    EXPECT_EQ(inspectCamera.attrs_.size(), size + sizeInsert);
    EXPECT_EQ(inspectCamera.attrs_["flash"], "off");
    EXPECT_EQ(inspectCamera.attrs_["deviceposition"], "back");
}

/**
 * @tc.name: InspectCanvasTest001
 * @tc.desc: InspectCanvas::InspectCanvas
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectCanvasTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectCanvas inspectCanvas(nodeId, tag);
    EXPECT_EQ(inspectCanvas.nodeId_, nodeId);
    EXPECT_EQ(inspectCanvas.tag_, tag);
}

/**
 * @tc.name: InspectCanvasTest002
 * @tc.desc: InspectCanvas::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectCanvasTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectCanvas inspectCanvas(nodeId, tag);
    auto size = inspectCanvas.attrs_.size();
    uint16_t sizeInsert = 2;
    inspectCanvas.PackAttrAndStyle();
    EXPECT_EQ(inspectCanvas.attrs_.size(), size + sizeInsert);
    EXPECT_EQ(inspectCanvas.attrs_["disabled"], "false");
    EXPECT_EQ(inspectCanvas.attrs_["focusable"], "false");
}

/**
 * @tc.name: InspectChartTest001
 * @tc.desc: InspectChart::InspectChart
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectChartTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectChart inspectChart(nodeId, tag);
    EXPECT_EQ(inspectChart.nodeId_, nodeId);
    EXPECT_EQ(inspectChart.tag_, tag);
}

/**
 * @tc.name: InspectChartTest002
 * @tc.desc: InspectChart::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectChartTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectChart inspectChart(nodeId, tag);
    auto attrsSize = inspectChart.attrs_.size();
    auto stylesSize = inspectChart.styles_.size();
    uint16_t attrsSizeInsert = 19;
    uint16_t stylesSizeInsert = 3;
    inspectChart.PackAttrAndStyle();
    EXPECT_EQ(inspectChart.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectChart.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectChart.attrs_["type"], "line");
    EXPECT_EQ(inspectChart.attrs_["effects"], "true");
    EXPECT_EQ(inspectChart.attrs_["disabled"], "false");
    EXPECT_EQ(inspectChart.attrs_["focusable"], "false");
    // insert makes sure that the second insert is invalid
    EXPECT_EQ(inspectChart.attrs_["strokeColor"], "#ff6384");
    EXPECT_EQ(inspectChart.attrs_["fillColor"], "#ff6384");
    EXPECT_EQ(inspectChart.attrs_["gradient"], "false");
    EXPECT_EQ(inspectChart.attrs_["min"], "0");
    EXPECT_EQ(inspectChart.attrs_["max"], "100");
    EXPECT_EQ(inspectChart.attrs_["axisTick"], "10");
    EXPECT_EQ(inspectChart.attrs_["display"], "false");
    EXPECT_EQ(inspectChart.attrs_["color"], "#c0c0c0");
    EXPECT_EQ(inspectChart.attrs_["width"], "1px");
    EXPECT_EQ(inspectChart.attrs_["smooth"], "false");
    EXPECT_EQ(inspectChart.attrs_["shape"], "circle");
    EXPECT_EQ(inspectChart.attrs_["size"], "5px");
    EXPECT_EQ(inspectChart.attrs_["strokeWidth"], "1px");
    EXPECT_EQ(inspectChart.attrs_["margin"], "1");
    EXPECT_EQ(inspectChart.attrs_["percent"], "0");
    EXPECT_EQ(inspectChart.styles_["stroke-width"], "32px");
    EXPECT_EQ(inspectChart.styles_["start-angle"], "240");
    EXPECT_EQ(inspectChart.styles_["total-angle"], "240");
}

/**
 * @tc.name: InspectDialogTest001
 * @tc.desc: InspectDialog::InspectDialog
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectDialogTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDialog inspectDialog(nodeId, tag);
    EXPECT_EQ(inspectDialog.nodeId_, nodeId);
    EXPECT_EQ(inspectDialog.tag_, tag);
}

/**
 * @tc.name: InspectDialogTest002
 * @tc.desc: InspectDialog::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectDialogTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDialog inspectDialog(nodeId, tag);
    auto attrsSize = inspectDialog.attrs_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 4;

    // SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectDialog.PackAttrAndStyle();
    EXPECT_EQ(inspectDialog.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectDialog.styles_.size(), stylesSizeInsert);
    EXPECT_EQ(inspectDialog.attrs_["disabled"], "false");
    EXPECT_EQ(inspectDialog.attrs_["dragable"], "false");
    EXPECT_EQ(inspectDialog.styles_["margin-left"], "0");
    EXPECT_EQ(inspectDialog.styles_["margin-top"], "0");
    EXPECT_EQ(inspectDialog.styles_["margin-right"], "0");
    EXPECT_EQ(inspectDialog.styles_["margin-bottom"], "0");
}

/**
 * @tc.name: InspectDivTest001
 * @tc.desc: InspectDiv::InspectDiv
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectDivTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDiv inspectDiv(nodeId, tag);
    EXPECT_EQ(inspectDiv.nodeId_, nodeId);
    EXPECT_EQ(inspectDiv.tag_, tag);
}

/**
 * @tc.name: InspectDivTest002
 * @tc.desc: InspectDiv::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectDivTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDiv inspectDiv(nodeId, tag);
    auto attrsSize = inspectDiv.attrs_.size();
    auto stylesSize = inspectDiv.styles_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 10;

    inspectDiv.PackAttrAndStyle();
    EXPECT_EQ(inspectDiv.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectDiv.attrs_["disabled"], "false");
    EXPECT_EQ(inspectDiv.attrs_["focusable"], "true");
    EXPECT_EQ(inspectDiv.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectDiv.styles_["flex-direction"], "row");
    EXPECT_EQ(inspectDiv.styles_["flex-wrap"], "nowrap");
    EXPECT_EQ(inspectDiv.styles_["justify-content"], "flex-start");
    EXPECT_EQ(inspectDiv.styles_["align-items"], "stretch");
    EXPECT_EQ(inspectDiv.styles_["align-content"], "flex-start");
    EXPECT_EQ(inspectDiv.styles_["display"], "flex");
    EXPECT_EQ(inspectDiv.styles_["grid-template-columns"], "1");
    EXPECT_EQ(inspectDiv.styles_["grid-template-rows"], "1");
    EXPECT_EQ(inspectDiv.styles_["grid-columns-gap"], "0");
    EXPECT_EQ(inspectDiv.styles_["grid-rows-gap"], "0");
}

/**
 * @tc.name: InspectDividerTest001
 * @tc.desc: InspectDivider::InspectDivider
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectDividerTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    EXPECT_EQ(inspectDivider.nodeId_, nodeId);
    EXPECT_EQ(inspectDivider.tag_, tag);
}

/**
 * @tc.name: InspectDividerTest002
 * @tc.desc: InspectDivider::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectDividerTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    auto attrsSize = inspectDivider.attrs_.size();
    auto stylesSize = inspectDivider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectDivider.PackAttrAndStyle();
    CheckDividerAttrAndStyle(inspectDivider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectDividerTest003
 * @tc.desc: InspectDivider::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectDividerTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    auto attrsSize = inspectDivider.attrs_.size();
    auto stylesSize = inspectDivider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectDivider.PackAttrAndStyle();
    CheckDividerAttrAndStyle(inspectDivider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectDividerTest004
 * @tc.desc: InspectDivider::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectDividerTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    auto attrsSize = inspectDivider.attrs_.size();
    auto stylesSize = inspectDivider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectDivider.PackAttrAndStyle();
    CheckDividerAttrAndStyle(inspectDivider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectDividerTest005
 * @tc.desc: InspectDivider::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectDividerTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    auto attrsSize = inspectDivider.attrs_.size();
    auto stylesSize = inspectDivider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectDivider.PackAttrAndStyle();
    CheckDividerAttrAndStyle(inspectDivider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectDividerTest006
 * @tc.desc: InspectDivider::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectDividerTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    auto attrsSize = inspectDivider.attrs_.size();
    auto stylesSize = inspectDivider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectDivider.PackAttrAndStyle();
    CheckDividerAttrAndStyle(inspectDivider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectDividerTest007
 * @tc.desc: InspectDivider::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectDividerTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    auto attrsSize = inspectDivider.attrs_.size();
    auto stylesSize = inspectDivider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectDivider.PackAttrAndStyle();
    CheckDividerAttrAndStyle(inspectDivider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectFormTest001
 * @tc.desc: InspectForm::InspectForm
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectFormTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectForm inspectForm(nodeId, tag);
    EXPECT_EQ(inspectForm.nodeId_, nodeId);
    EXPECT_EQ(inspectForm.tag_, tag);
}

/**
 * @tc.name: InspectGridColumnTest001
 * @tc.desc: InspectGridColumn::InspectGridColumn
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectGridColumnTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectGridColumn inspectGridColumn(nodeId, tag);
    EXPECT_EQ(inspectGridColumn.nodeId_, nodeId);
    EXPECT_EQ(inspectGridColumn.tag_, tag);
}

/**
 * @tc.name: InspectGridColumnTest002
 * @tc.desc: InspectGridColumn::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectGridColumnTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectGridColumn inspectGridColumn(nodeId, tag);
    auto attrsSize = inspectGridColumn.attrs_.size();
    auto stylesSize = inspectGridColumn.styles_.size();
    uint16_t attrsSizeInsert = 4;
    uint16_t stylesSizeInsert = 9;

    inspectGridColumn.PackAttrAndStyle();
    EXPECT_EQ(inspectGridColumn.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectGridColumn.attrs_["span"], "1");
    EXPECT_EQ(inspectGridColumn.attrs_["offset"], "0");
    EXPECT_EQ(inspectGridColumn.attrs_["disabled"], "false");
    EXPECT_EQ(inspectGridColumn.attrs_["focusable"], "false");
    EXPECT_EQ(inspectGridColumn.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectGridColumn.styles_["flex-direction"], "row");
    EXPECT_EQ(inspectGridColumn.styles_["flex-wrap"], "nowrap");
    EXPECT_EQ(inspectGridColumn.styles_["justify-content"], "flex-start");
    EXPECT_EQ(inspectGridColumn.styles_["align-items"], "stretch");
    EXPECT_EQ(inspectGridColumn.styles_["align-content"], "flex-start");
    EXPECT_EQ(inspectGridColumn.styles_["grid-template-columns"], "1");
    EXPECT_EQ(inspectGridColumn.styles_["grid-template-rows"], "1");
    EXPECT_EQ(inspectGridColumn.styles_["grid-columns-gap"], "0");
    EXPECT_EQ(inspectGridColumn.styles_["grid-rows-gap"], "0");
    EXPECT_EQ(inspectGridColumn.styles_.find("margin-left"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("margin-top"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("margin-right"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("margin-bottom"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("margin-start"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("margin-end"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("flex-grow"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("flex-shrink"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("position"), inspectGridColumn.styles_.end());
}

/**
 * @tc.name: InspectGridContainerTest001
 * @tc.desc: InspectGridContainer::InspectGridContainer
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectGridContainerTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectGridContainer inspectGridContainer(nodeId, tag);
    EXPECT_EQ(inspectGridContainer.nodeId_, nodeId);
    EXPECT_EQ(inspectGridContainer.tag_, tag);
}

/**
 * @tc.name: InspectGridContainerTest002
 * @tc.desc: InspectGridContainer::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectGridContainerTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectGridContainer inspectGridContainer(nodeId, tag);
    auto attrsSize = inspectGridContainer.attrs_.size();
    auto stylesSize = inspectGridContainer.styles_.size();
    uint16_t attrsSizeInsert = 5;
    uint16_t stylesSizeInsert = 3;

    inspectGridContainer.PackAttrAndStyle();
    EXPECT_EQ(inspectGridContainer.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectGridContainer.attrs_["columns"], "auto");
    EXPECT_EQ(inspectGridContainer.attrs_["sizetype"], "auto");
    EXPECT_EQ(inspectGridContainer.attrs_["gutter"], "24px");
    EXPECT_EQ(inspectGridContainer.attrs_["disabled"], "false");
    EXPECT_EQ(inspectGridContainer.attrs_["focusable"], "true");
    EXPECT_EQ(inspectGridContainer.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectGridContainer.styles_["justify-content"], "flex-start");
    EXPECT_EQ(inspectGridContainer.styles_["align-items"], "stretch");
    EXPECT_EQ(inspectGridContainer.styles_["align-content"], "flex-start");
}

/**
 * @tc.name: InspectGridRowTest001
 * @tc.desc: InspectGridRow::InspectGridRow
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectGridRowTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectGridRow inspectGridRow(nodeId, tag);
    EXPECT_EQ(inspectGridRow.nodeId_, nodeId);
    EXPECT_EQ(inspectGridRow.tag_, tag);
}

/**
 * @tc.name: InspectGridRowTest002
 * @tc.desc: InspectGridRow::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectGridRowTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectGridRow inspectGridRow(nodeId, tag);
    auto attrsSize = inspectGridRow.attrs_.size();
    auto stylesSize = inspectGridRow.styles_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 4;

    inspectGridRow.PackAttrAndStyle();
    EXPECT_EQ(inspectGridRow.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectGridRow.attrs_["disabled"], "false");
    EXPECT_EQ(inspectGridRow.attrs_["focusable"], "false");
    EXPECT_EQ(inspectGridRow.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectGridRow.styles_["flex-wrap"], "nowrap");
    EXPECT_EQ(inspectGridRow.styles_["justify-content"], "flex-start");
    EXPECT_EQ(inspectGridRow.styles_["align-items"], "flex-start");
    EXPECT_EQ(inspectGridRow.styles_["align-content"], "flex-start");
    EXPECT_EQ(inspectGridRow.styles_.find("padding-left"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("padding-top"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("padding-right"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("padding-bottom"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("padding-start"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("padding-end"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("margin-left"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("margin-top"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("margin-right"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("margin-bottom"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("margin-start"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("margin-end"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("flex-grow"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("flex-shrink"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("position"), inspectGridRow.styles_.end());
}

/**
 * @tc.name: InspectImageAnimatorTest001
 * @tc.desc: InspectImageAnimator::InspectImageAnimator
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectImageAnimatorTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectImageAnimator inspectImageAnimator(nodeId, tag);
    EXPECT_EQ(inspectImageAnimator.nodeId_, nodeId);
    EXPECT_EQ(inspectImageAnimator.tag_, tag);
}

/**
 * @tc.name: InspectImageAnimatorTest002
 * @tc.desc: InspectImageAnimator::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectImageAnimatorTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectImageAnimator inspectImageAnimator(nodeId, tag);
    auto attrsSize = inspectImageAnimator.attrs_.size();
    uint16_t attrsSizeInsert = 7;

    inspectImageAnimator.PackAttrAndStyle();
    EXPECT_EQ(inspectImageAnimator.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectImageAnimator.attrs_["predecode"], "0");
    EXPECT_EQ(inspectImageAnimator.attrs_["iteration"], "infinite");
    EXPECT_EQ(inspectImageAnimator.attrs_["reverse"], "false");
    EXPECT_EQ(inspectImageAnimator.attrs_["fixedsize"], "true");
    EXPECT_EQ(inspectImageAnimator.attrs_["fillmode"], "forwards");
    EXPECT_EQ(inspectImageAnimator.attrs_["disabled"], "false");
    EXPECT_EQ(inspectImageAnimator.attrs_["focusable"], "false");
}

/**
 * @tc.name: InspectImageTest001
 * @tc.desc: InspectImage::InspectImage
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectImageTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectImage inspectImage(nodeId, tag);
    EXPECT_EQ(inspectImage.nodeId_, nodeId);
    EXPECT_EQ(inspectImage.tag_, tag);
}

/**
 * @tc.name: InspectImageTest002
 * @tc.desc: InspectImage::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectImageTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectImage inspectImage(nodeId, tag);
    auto attrsSize = inspectImage.attrs_.size();
    auto stylesSize = inspectImage.styles_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 3;

    inspectImage.PackAttrAndStyle();
    EXPECT_EQ(inspectImage.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectImage.attrs_["disabled"], "false");
    EXPECT_EQ(inspectImage.attrs_["focusable"], "false");
    EXPECT_EQ(inspectImage.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectImage.styles_["object-fit"], "cover");
    EXPECT_EQ(inspectImage.styles_["match-text-direction"], "false");
    EXPECT_EQ(inspectImage.styles_["fit-original-size"], "false");
}

/**
 * @tc.name: InspectInputTest001
 * @tc.desc: InspectInput::InspectInput
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectInputTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    EXPECT_EQ(inspectInput.nodeId_, nodeId);
    EXPECT_EQ(inspectInput.tag_, tag);
}

/**
 * @tc.name: InspectInputTest002
 * @tc.desc: InspectInput::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectInputTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    auto attrsSize = inspectInput.attrs_.size();
    auto stylesSize = inspectInput.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectInput.PackAttrAndStyle();
    CheckInputAttrAndStyle(inspectInput, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectInputTest003
 * @tc.desc: InspectInput::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectInputTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    auto attrsSize = inspectInput.attrs_.size();
    auto stylesSize = inspectInput.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectInput.PackAttrAndStyle();
    CheckInputAttrAndStyle(inspectInput, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectInputTest004
 * @tc.desc: InspectInput::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectInputTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    auto attrsSize = inspectInput.attrs_.size();
    auto stylesSize = inspectInput.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectInput.PackAttrAndStyle();
    CheckInputAttrAndStyle(inspectInput, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectInputTest005
 * @tc.desc: InspectInput::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectInputTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    auto attrsSize = inspectInput.attrs_.size();
    auto stylesSize = inspectInput.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectInput.PackAttrAndStyle();
    CheckInputAttrAndStyle(inspectInput, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectInputTest006
 * @tc.desc: InspectInput::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectInputTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    auto attrsSize = inspectInput.attrs_.size();
    auto stylesSize = inspectInput.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectInput.PackAttrAndStyle();
    CheckInputAttrAndStyle(inspectInput, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectInputTest007
 * @tc.desc: InspectInput::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectInputTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    auto attrsSize = inspectInput.attrs_.size();
    auto stylesSize = inspectInput.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectInput.PackAttrAndStyle();
    CheckInputAttrAndStyle(inspectInput, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectLabelTest001
 * @tc.desc: InspectLabel::InspectLabel
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectLabelTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    EXPECT_EQ(inspectLabel.nodeId_, nodeId);
    EXPECT_EQ(inspectLabel.tag_, tag);
}

/**
 * @tc.name: InspectLabelTest002
 * @tc.desc: InspectLabel::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectLabelTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    auto attrsSize = inspectLabel.attrs_.size();
    auto stylesSize = inspectLabel.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectLabel.PackAttrAndStyle();
    CheckLabelAttrAndStyle(inspectLabel, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectLabelTest003
 * @tc.desc: InspectLabel::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectLabelTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    auto attrsSize = inspectLabel.attrs_.size();
    auto stylesSize = inspectLabel.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectLabel.PackAttrAndStyle();
    CheckLabelAttrAndStyle(inspectLabel, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectLabelTest004
 * @tc.desc: InspectLabel::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectLabelTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    auto attrsSize = inspectLabel.attrs_.size();
    auto stylesSize = inspectLabel.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectLabel.PackAttrAndStyle();
    CheckLabelAttrAndStyle(inspectLabel, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectLabelTest005
 * @tc.desc: InspectLabel::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectLabelTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    auto attrsSize = inspectLabel.attrs_.size();
    auto stylesSize = inspectLabel.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectLabel.PackAttrAndStyle();
    CheckLabelAttrAndStyle(inspectLabel, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectLabelTest006
 * @tc.desc: InspectLabel::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectLabelTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    auto attrsSize = inspectLabel.attrs_.size();
    auto stylesSize = inspectLabel.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectLabel.PackAttrAndStyle();
    CheckLabelAttrAndStyle(inspectLabel, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectLabelTest007
 * @tc.desc: InspectLabel::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectLabelTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    auto attrsSize = inspectLabel.attrs_.size();
    auto stylesSize = inspectLabel.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectLabel.PackAttrAndStyle();
    CheckLabelAttrAndStyle(inspectLabel, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectListItemGroupTest001
 * @tc.desc: InspectListItemGroup::InspectListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectListItemGroupTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectListItemGroup inspectListItemGroup(nodeId, tag);
    EXPECT_EQ(inspectListItemGroup.nodeId_, nodeId);
    EXPECT_EQ(inspectListItemGroup.tag_, tag);
}

/**
 * @tc.name: InspectListItemGroupTest002
 * @tc.desc: InspectListItemGroup::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectListItemGroupTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectListItemGroup inspectListItemGroup(nodeId, tag);
    auto attrsSize = inspectListItemGroup.attrs_.size();
    auto stylesSize = inspectListItemGroup.styles_.size();
    uint16_t attrsSizeInsert = 3;
    uint16_t stylesSizeInsert = 2;

    inspectListItemGroup.PackAttrAndStyle();
    EXPECT_EQ(inspectListItemGroup.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectListItemGroup.attrs_["type"], "default");
    EXPECT_EQ(inspectListItemGroup.attrs_["disabled"], "false");
    EXPECT_EQ(inspectListItemGroup.attrs_["focusable"], "true");
    EXPECT_EQ(inspectListItemGroup.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectListItemGroup.styles_["flex-direction"], "row");
    EXPECT_EQ(inspectListItemGroup.styles_["justify-content"], "flex-start");
    EXPECT_EQ(inspectListItemGroup.styles_.find("position"), inspectListItemGroup.styles_.end());
}

/**
 * @tc.name: InspectListItemTest001
 * @tc.desc: InspectListItem::InspectListItem
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectListItemTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectListItem inspectListItem(nodeId, tag);
    EXPECT_EQ(inspectListItem.nodeId_, nodeId);
    EXPECT_EQ(inspectListItem.tag_, tag);
}

/**
 * @tc.name: InspectListItemTest002
 * @tc.desc: InspectListItem::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectListItemTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectListItem inspectListItem(nodeId, tag);
    auto attrsSize = inspectListItem.attrs_.size();
    auto stylesSize = inspectListItem.styles_.size();
    uint16_t attrsSizeInsert = 7;
    uint16_t stylesSizeInsert = 1;

    inspectListItem.PackAttrAndStyle();
    EXPECT_EQ(inspectListItem.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectListItem.attrs_["type"], "default");
    EXPECT_EQ(inspectListItem.attrs_["primary"], "false");
    EXPECT_EQ(inspectListItem.attrs_["sticky"], "none");
    EXPECT_EQ(inspectListItem.attrs_["stickyradius"], "1000px");
    EXPECT_EQ(inspectListItem.attrs_["clickeffect"], "true");
    EXPECT_EQ(inspectListItem.attrs_["disabled"], "false");
    EXPECT_EQ(inspectListItem.attrs_["focusable"], "true");
    EXPECT_EQ(inspectListItem.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectListItem.styles_["column-span"], "1");
}

/**
 * @tc.name: InspectListTest001
 * @tc.desc: InspectList::InspectList
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectListTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectList inspectList(nodeId, tag);
    EXPECT_EQ(inspectList.nodeId_, nodeId);
    EXPECT_EQ(inspectList.tag_, tag);
}

/**
 * @tc.name: InspectListTest002
 * @tc.desc: InspectList::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectListTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectList inspectList(nodeId, tag);
    auto attrsSize = inspectList.attrs_.size();
    auto stylesSize = inspectList.styles_.size();
    uint16_t attrsSizeInsert = 18;
    uint16_t stylesSizeInsert = 7;

    inspectList.PackAttrAndStyle();
    EXPECT_EQ(inspectList.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectList.attrs_["scrollpage"], "true");
    EXPECT_EQ(inspectList.attrs_["cachedcount"], "0");
    EXPECT_EQ(inspectList.attrs_["scrollbar"], "off");
    EXPECT_EQ(inspectList.attrs_["scrolleffect"], "spring");
    EXPECT_EQ(inspectList.attrs_["indexer"], "false");
    EXPECT_EQ(inspectList.attrs_["indexermulti"], "false");
    EXPECT_EQ(inspectList.attrs_["indexerbubble"], "true");
    EXPECT_EQ(inspectList.attrs_["divider"], "false");
    EXPECT_EQ(inspectList.attrs_["shapemode"], "default");
    EXPECT_EQ(inspectList.attrs_["itemscale"], "true");
    EXPECT_EQ(inspectList.attrs_["itemcenter"], "false");
    EXPECT_EQ(inspectList.attrs_["updateeffect"], "false");
    EXPECT_EQ(inspectList.attrs_["chainanimation"], "false");
    EXPECT_EQ(inspectList.attrs_["scrollvibrate"], "true");
    EXPECT_EQ(inspectList.attrs_["initialindex"], "0");
    EXPECT_EQ(inspectList.attrs_["initialoffset"], "0");
    EXPECT_EQ(inspectList.attrs_["disabled"], "false");
    EXPECT_EQ(inspectList.attrs_["focusable"], "true");
    EXPECT_EQ(inspectList.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectList.styles_["divider-color"], "transparent");
    EXPECT_EQ(inspectList.styles_["divider-height"], "1");
    EXPECT_EQ(inspectList.styles_["divider-origin"], "0");
    EXPECT_EQ(inspectList.styles_["flex-direction"], "column");
    EXPECT_EQ(inspectList.styles_["columns"], "1");
    EXPECT_EQ(inspectList.styles_["align-items"], "stretch");
    EXPECT_EQ(inspectList.styles_["fade-color"], "grey");
}

/**
 * @tc.name: InspectMarqueeTest001
 * @tc.desc: InspectMarquee::InspectMarquee
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectMarqueeTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMarquee inspectMarquee(nodeId, tag);
    EXPECT_EQ(inspectMarquee.nodeId_, nodeId);
    EXPECT_EQ(inspectMarquee.tag_, tag);
}

/**
 * @tc.name: InspectMarqueeTest002
 * @tc.desc: InspectMarquee::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectMarqueeTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMarquee inspectMarquee(nodeId, tag);
    auto attrsSize = inspectMarquee.attrs_.size();
    auto stylesSize = inspectMarquee.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectMarquee.PackAttrAndStyle();
    CheckMarqueeAttrAndStyle(inspectMarquee, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectMarqueeTest003
 * @tc.desc: InspectMarquee::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectMarqueeTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMarquee inspectMarquee(nodeId, tag);
    auto attrsSize = inspectMarquee.attrs_.size();
    auto stylesSize = inspectMarquee.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectMarquee.PackAttrAndStyle();
    CheckMarqueeAttrAndStyle(inspectMarquee, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectMarqueeTest004
 * @tc.desc: InspectMarquee::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectMarqueeTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMarquee inspectMarquee(nodeId, tag);
    auto attrsSize = inspectMarquee.attrs_.size();
    auto stylesSize = inspectMarquee.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectMarquee.PackAttrAndStyle();
    CheckMarqueeAttrAndStyle(inspectMarquee, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectMarqueeTest005
 * @tc.desc: InspectMarquee::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectMarqueeTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMarquee inspectMarquee(nodeId, tag);
    auto attrsSize = inspectMarquee.attrs_.size();
    auto stylesSize = inspectMarquee.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectMarquee.PackAttrAndStyle();
    CheckMarqueeAttrAndStyle(inspectMarquee, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectMarqueeTest006
 * @tc.desc: InspectMarquee::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectMarqueeTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMarquee inspectMarquee(nodeId, tag);
    auto attrsSize = inspectMarquee.attrs_.size();
    auto stylesSize = inspectMarquee.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectMarquee.PackAttrAndStyle();
    CheckMarqueeAttrAndStyle(inspectMarquee, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectMarqueeTest007
 * @tc.desc: InspectMarquee::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectMarqueeTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMarquee inspectMarquee(nodeId, tag);
    auto attrsSize = inspectMarquee.attrs_.size();
    auto stylesSize = inspectMarquee.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectMarquee.PackAttrAndStyle();
    CheckMarqueeAttrAndStyle(inspectMarquee, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectMenuTest001
 * @tc.desc: InspectMenu::InspectMenu
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectMenuTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMenu inspectMenu(nodeId, tag);
    EXPECT_EQ(inspectMenu.nodeId_, nodeId);
    EXPECT_EQ(inspectMenu.tag_, tag);
}

/**
 * @tc.name: InspectMenuTest002
 * @tc.desc: InspectMenu::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectMenuTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMenu inspectMenu(nodeId, tag);
    auto attrsSize = inspectMenu.attrs_.size();
    auto stylesSize = inspectMenu.styles_.size();
    uint16_t attrsSizeInsert = 1;
    uint16_t stylesSizeInsert = 6;

    inspectMenu.PackAttrAndStyle();
    EXPECT_EQ(inspectMenu.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectMenu.attrs_["type"], "click");
    EXPECT_EQ(inspectMenu.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectMenu.styles_["font-size"], "30px");
    EXPECT_EQ(inspectMenu.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectMenu.styles_["letter-spacing"], "0");
    EXPECT_EQ(inspectMenu.styles_["font-style"], "normal");
    EXPECT_EQ(inspectMenu.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectMenu.styles_["font-family"], "sans-serif");
}

/**
 * @tc.name: InspectNavigationBarTest001
 * @tc.desc: InspectNavigationBar::InspectNavigationBar
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectNavigationBarTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectNavigationBar inspectNavigationBar(nodeId, tag);
    EXPECT_EQ(inspectNavigationBar.nodeId_, nodeId);
    EXPECT_EQ(inspectNavigationBar.tag_, tag);
}

/**
 * @tc.name: InspectNavigationBarTest002
 * @tc.desc: InspectNavigationBar::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectNavigationBarTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectNavigationBar inspectNavigationBar(nodeId, tag);
    auto attrsSize = inspectNavigationBar.attrs_.size();
    auto stylesSize = inspectNavigationBar.styles_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 3;

    inspectNavigationBar.PackAttrAndStyle();
    EXPECT_EQ(inspectNavigationBar.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectNavigationBar.attrs_["type"], "normal");
    EXPECT_EQ(inspectNavigationBar.attrs_["backenabled"], "false");
    EXPECT_EQ(inspectNavigationBar.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectNavigationBar.styles_["background-repeat"], "repeat");
    EXPECT_EQ(inspectNavigationBar.styles_["opacity"], "1");
    EXPECT_EQ(inspectNavigationBar.styles_["visibility"], "visible");
}

/**
 * @tc.name: InspectNodeTest001
 * @tc.desc: InspectNode::InspectNode
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectNodeTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectNode inspectNode(nodeId, tag);
    EXPECT_EQ(inspectNode.nodeId_, nodeId);
    EXPECT_EQ(inspectNode.tag_, tag);
}

/**
 * @tc.name: InspectNodeTest003
 * @tc.desc: InspectNode::InitCommonStyles
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectNodeTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectNode inspectNode(nodeId, tag);
    auto stylesSize = inspectNode.styles_.size();
    uint16_t stylesSizeInsert = 34;

    inspectNode.InitCommonStyles();
    EXPECT_EQ(inspectNode.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectNode.styles_["padding-left"], "0");
    EXPECT_EQ(inspectNode.styles_["padding-top"], "0");
    EXPECT_EQ(inspectNode.styles_["padding-right"], "0");
    EXPECT_EQ(inspectNode.styles_["padding-bottom"], "0");
    EXPECT_EQ(inspectNode.styles_["padding-start"], "0");
    EXPECT_EQ(inspectNode.styles_["padding-end"], "0");
    EXPECT_EQ(inspectNode.styles_["margin-left"], "0");
    EXPECT_EQ(inspectNode.styles_["margin-top"], "0");
    EXPECT_EQ(inspectNode.styles_["margin-right"], "0");
    EXPECT_EQ(inspectNode.styles_["margin-bottom"], "0");
    EXPECT_EQ(inspectNode.styles_["margin-start"], "0");
    EXPECT_EQ(inspectNode.styles_["margin-end"], "0");
    EXPECT_EQ(inspectNode.styles_["border"], "0");
    EXPECT_EQ(inspectNode.styles_["border-left-style"], "solid");
    EXPECT_EQ(inspectNode.styles_["border-top-style"], "solid");
    EXPECT_EQ(inspectNode.styles_["border-right-style"], "solid");
    EXPECT_EQ(inspectNode.styles_["border-bottom-style"], "solid");
    EXPECT_EQ(inspectNode.styles_["border-left-width"], "0");
    EXPECT_EQ(inspectNode.styles_["border-top-width"], "0");
    EXPECT_EQ(inspectNode.styles_["border-right-width"], "0");
    EXPECT_EQ(inspectNode.styles_["border-bottom-width"], "0");
    EXPECT_EQ(inspectNode.styles_["border-left-color"], "black");
    EXPECT_EQ(inspectNode.styles_["border-top-color"], "black");
    EXPECT_EQ(inspectNode.styles_["border-right-color"], "black");
    EXPECT_EQ(inspectNode.styles_["border-bottom-color"], "black");
    EXPECT_EQ(inspectNode.styles_["background-size"], "auto");
    EXPECT_EQ(inspectNode.styles_["background-repeat"], "repeat");
    EXPECT_EQ(inspectNode.styles_["background-position"], "0px 0px");
    EXPECT_EQ(inspectNode.styles_["opacity"], "1");
    EXPECT_EQ(inspectNode.styles_["display"], "flex");
    EXPECT_EQ(inspectNode.styles_["visibility"], "visible");
    EXPECT_EQ(inspectNode.styles_["flex-grow"], "0");
    EXPECT_EQ(inspectNode.styles_["flex-shrink"], "1");
    EXPECT_EQ(inspectNode.styles_["position"], "relative");
}

/**
 * @tc.name: InspectNodeTest004
 * @tc.desc: InspectNode::SetAllAttr
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectNodeTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectNode inspectNode(nodeId, tag);
    inspectNode.attrs_.insert(std::make_pair("disabled", "false"));
    auto rootJsonValue = JsonUtil::Create(true);
    auto attrsJsonValue = JsonUtil::Create(true);
    attrsJsonValue->Put("disabled", "false");
    inspectNode.SetAllAttr(rootJsonValue, INSPECTOR_ATTRS);
    EXPECT_EQ(rootJsonValue->GetObject(INSPECTOR_ATTRS)->ToString(), attrsJsonValue->ToString());
}

/**
 * @tc.name: InspectNodeTest005
 * @tc.desc: InspectNode::SetAllStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectNodeTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectNode inspectNode(nodeId, tag);
    inspectNode.styles_.insert(std::make_pair("position", "relative"));
    auto rootJsonValue = JsonUtil::Create(true);
    auto stylesJsonValue = JsonUtil::Create(true);
    stylesJsonValue->Put("position", "relative");
    inspectNode.SetAllStyle(rootJsonValue, INSPECTOR_STYLES);
    EXPECT_EQ(rootJsonValue->GetObject(INSPECTOR_STYLES)->ToString(), stylesJsonValue->ToString());
}

/**
 * @tc.name: InspectOptionTest001
 * @tc.desc: InspectOption::InspectOption
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectOptionTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectOption inspectOption(nodeId, tag);
    EXPECT_EQ(inspectOption.nodeId_, nodeId);
    EXPECT_EQ(inspectOption.tag_, tag);
}

/**
 * @tc.name: InspectOptionTest002
 * @tc.desc: InspectOption::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectOptionTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectOption inspectOption(nodeId, tag);
    auto attrsSize = inspectOption.attrs_.size();
    auto stylesSize = inspectOption.styles_.size();
    uint16_t attrsSizeInsert = 3;
    uint16_t stylesSizeInsert = 6;

    inspectOption.PackAttrAndStyle();
    EXPECT_EQ(inspectOption.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectOption.attrs_["action"], "show");
    EXPECT_EQ(inspectOption.attrs_["focusable"], "true");
    EXPECT_EQ(inspectOption.attrs_["disabled"], "false");
    EXPECT_EQ(inspectOption.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectOption.styles_["color"], "#e6000000");
    EXPECT_EQ(inspectOption.styles_["font-size"], "16px");
    EXPECT_EQ(inspectOption.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectOption.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectOption.styles_["text-decoration"], "none");
    EXPECT_EQ(inspectOption.styles_["font-family"], "sans-serif");
}

/**
 * @tc.name: InspectPanelTest001
 * @tc.desc: InspectPanel::InspectPanel
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectPanelTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPanel inspectPanel(nodeId, tag);
    EXPECT_EQ(inspectPanel.nodeId_, nodeId);
    EXPECT_EQ(inspectPanel.tag_, tag);
}

/**
 * @tc.name: InspectPanelTest002
 * @tc.desc: InspectPanel::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectPanelTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPanel inspectPanel(nodeId, tag);
    auto attrsSize = inspectPanel.attrs_.size();
    uint16_t attrsSizeInsert = 2;

    inspectPanel.PackAttrAndStyle();
    EXPECT_EQ(inspectPanel.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectPanel.attrs_["mode"], "full");
    EXPECT_EQ(inspectPanel.attrs_["dragbar"], "true");
    EXPECT_EQ(inspectPanel.styles_.find("display"), inspectPanel.styles_.end());
    EXPECT_EQ(inspectPanel.styles_.find("visibility"), inspectPanel.styles_.end());
    EXPECT_EQ(inspectPanel.styles_.find("flex-grow"), inspectPanel.styles_.end());
    EXPECT_EQ(inspectPanel.styles_.find("flex-shrink"), inspectPanel.styles_.end());
    EXPECT_EQ(inspectPanel.styles_.find("position"), inspectPanel.styles_.end());
}

/**
 * @tc.name: InspectPickerTest001
 * @tc.desc: InspectPicker::InspectPicker
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectPickerTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPicker inspectPicker(nodeId, tag);
    EXPECT_EQ(inspectPicker.nodeId_, nodeId);
    EXPECT_EQ(inspectPicker.tag_, tag);
}

/**
 * @tc.name: InspectPickerTest002
 * @tc.desc: InspectPicker::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectPickerTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPicker inspectPicker(nodeId, tag);
    auto attrsSize = inspectPicker.attrs_.size();
    auto stylesSize = inspectPicker.styles_.size();
    uint16_t attrsSizeInsert = 10;
    uint16_t stylesSizeInsert = 8;

    inspectPicker.PackAttrAndStyle();
    EXPECT_EQ(inspectPicker.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectPicker.attrs_["disabled"], "false");
    EXPECT_EQ(inspectPicker.attrs_["focusable"], "true");
    EXPECT_EQ(inspectPicker.attrs_["vibrate"], "true");
    EXPECT_EQ(inspectPicker.attrs_["selected"], "0");
    EXPECT_EQ(inspectPicker.attrs_["start"], "1970-1-1");
    EXPECT_EQ(inspectPicker.attrs_["end"], "2100-12-31");
    EXPECT_EQ(inspectPicker.attrs_["lunar"], "false");
    EXPECT_EQ(inspectPicker.attrs_["lunarswitch"], "false");
    EXPECT_EQ(inspectPicker.attrs_["containsecond"], "false");
    EXPECT_EQ(inspectPicker.attrs_["hours"], "24");
    EXPECT_EQ(inspectPicker.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectPicker.styles_["text-color"], "#e6000000");
    EXPECT_EQ(inspectPicker.styles_["font-size"], "30px");
    EXPECT_EQ(inspectPicker.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectPicker.styles_["letter-spacing"], "0");
    EXPECT_EQ(inspectPicker.styles_["font-style"], "normal");
    EXPECT_EQ(inspectPicker.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectPicker.styles_["font-family"], "sans-serif");
    EXPECT_EQ(inspectPicker.styles_["line-height"], "0px");
}

/**
 * @tc.name: InspectPickerViewTest001
 * @tc.desc: InspectPickerView::InspectPickerView
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectPickerViewTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPickerView inspectPickerView(nodeId, tag);
    EXPECT_EQ(inspectPickerView.nodeId_, nodeId);
    EXPECT_EQ(inspectPickerView.tag_, tag);
}

/**
 * @tc.name: InspectPickerViewTest002
 * @tc.desc: InspectPickerView::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectPickerViewTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPickerView inspectPickerView(nodeId, tag);
    auto attrsSize = inspectPickerView.attrs_.size();
    auto stylesSize = inspectPickerView.styles_.size();
    uint16_t attrsSizeInsert = 10;
    uint16_t stylesSizeInsert = 9;

    inspectPickerView.PackAttrAndStyle();
    EXPECT_EQ(inspectPickerView.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectPickerView.attrs_["type"], "text");
    EXPECT_EQ(inspectPickerView.attrs_["disabled"], "false");
    EXPECT_EQ(inspectPickerView.attrs_["focusable"], "true");
    EXPECT_EQ(inspectPickerView.attrs_["selected"], "0");
    EXPECT_EQ(inspectPickerView.attrs_["start"], "1970-1-1");
    EXPECT_EQ(inspectPickerView.attrs_["end"], "2100-12-31");
    EXPECT_EQ(inspectPickerView.attrs_["lunar"], "false");
    EXPECT_EQ(inspectPickerView.attrs_["lunarswitch"], "false");
    EXPECT_EQ(inspectPickerView.attrs_["containsecond"], "false");
    EXPECT_EQ(inspectPickerView.attrs_["hours"], "24");
    EXPECT_EQ(inspectPickerView.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectPickerView.styles_["color"], "#808080");
    EXPECT_EQ(inspectPickerView.styles_["font-size"], "30px");
    EXPECT_EQ(inspectPickerView.styles_["selected-color"], "#ffffff");
    EXPECT_EQ(inspectPickerView.styles_["selected-font-size"], "38px");
    EXPECT_EQ(inspectPickerView.styles_["focus-color"], "#ffffff");
    EXPECT_EQ(inspectPickerView.styles_["focus-font-size"], "38px");
    EXPECT_EQ(inspectPickerView.styles_["disappear-color"], "#ffffff");
    EXPECT_EQ(inspectPickerView.styles_["disappear-font-size"], "14px");
    EXPECT_EQ(inspectPickerView.styles_["font-family"], "sans-serif");
}

/**
 * @tc.name: InspectPieceTest001
 * @tc.desc: InspectPiece::InspectPiece
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectPieceTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPiece inspectPiece(nodeId, tag);
    EXPECT_EQ(inspectPiece.nodeId_, nodeId);
    EXPECT_EQ(inspectPiece.tag_, tag);
}

/**
 * @tc.name: InspectPieceTest002
 * @tc.desc: InspectPiece::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectPieceTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPiece inspectPiece(nodeId, tag);
    auto attrsSize = inspectPiece.attrs_.size();
    uint16_t attrsSizeInsert = 3;

    inspectPiece.PackAttrAndStyle();
    EXPECT_EQ(inspectPiece.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectPiece.attrs_["closable"], "false");
    EXPECT_EQ(inspectPiece.attrs_["disabled"], "false");
    EXPECT_EQ(inspectPiece.attrs_["focusable"], "false");
}

/**
 * @tc.name: InspectPopupTest001
 * @tc.desc: InspectPopup::InspectPopup
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectPopupTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPopup inspectPopup(nodeId, tag);
    EXPECT_EQ(inspectPopup.nodeId_, nodeId);
    EXPECT_EQ(inspectPopup.tag_, tag);
}

/**
 * @tc.name: InspectPopupTest002
 * @tc.desc: InspectPopup::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectPopupTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPopup inspectPopup(nodeId, tag);
    auto attrsSize = inspectPopup.attrs_.size();
    auto stylesSize = inspectPopup.styles_.size();
    uint16_t attrsSizeInsert = 5;
    uint16_t stylesSizeInsert = 1;

    inspectPopup.PackAttrAndStyle();
    EXPECT_EQ(inspectPopup.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectPopup.attrs_["placement"], "bottom");
    EXPECT_EQ(inspectPopup.attrs_["keepalive"], "false");
    EXPECT_EQ(inspectPopup.attrs_["clickable"], "true");
    EXPECT_EQ(inspectPopup.attrs_["arrowoffset"], "0");
    EXPECT_EQ(inspectPopup.attrs_["disabled"], "false");
    EXPECT_EQ(inspectPopup.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectPopup.styles_["mask-color"], "#00000000");
    EXPECT_EQ(inspectPopup.styles_.find("flex-grow"), inspectPopup.styles_.end());
    EXPECT_EQ(inspectPopup.styles_.find("flex-shrink"), inspectPopup.styles_.end());
    EXPECT_EQ(inspectPopup.styles_.find("position"), inspectPopup.styles_.end());
}

/**
 * @tc.name: InspectProgressTest001
 * @tc.desc: InspectProgress::InspectProgress
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectProgressTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    EXPECT_EQ(inspectProgress.nodeId_, nodeId);
    EXPECT_EQ(inspectProgress.tag_, tag);
}

/**
 * @tc.name: InspectProgressTest002
 * @tc.desc: InspectProgress::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectProgressTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    auto attrsSize = inspectProgress.attrs_.size();
    auto stylesSize = inspectProgress.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectProgress.PackAttrAndStyle();
    CheckProgressAttrAndStyle(inspectProgress, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectProgressTest003
 * @tc.desc: InspectProgress::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectProgressTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    auto attrsSize = inspectProgress.attrs_.size();
    auto stylesSize = inspectProgress.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectProgress.PackAttrAndStyle();
    CheckProgressAttrAndStyle(inspectProgress, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectProgressTest004
 * @tc.desc: InspectProgress::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectProgressTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    auto attrsSize = inspectProgress.attrs_.size();
    auto stylesSize = inspectProgress.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectProgress.PackAttrAndStyle();
    CheckProgressAttrAndStyle(inspectProgress, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectProgressTest005
 * @tc.desc: InspectProgress::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectProgressTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    auto attrsSize = inspectProgress.attrs_.size();
    auto stylesSize = inspectProgress.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectProgress.PackAttrAndStyle();
    CheckProgressAttrAndStyle(inspectProgress, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectProgressTest006
 * @tc.desc: InspectProgress::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectProgressTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    auto attrsSize = inspectProgress.attrs_.size();
    auto stylesSize = inspectProgress.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectProgress.PackAttrAndStyle();
    CheckProgressAttrAndStyle(inspectProgress, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectProgressTest007
 * @tc.desc: InspectProgress::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectProgressTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    auto attrsSize = inspectProgress.attrs_.size();
    auto stylesSize = inspectProgress.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectProgress.PackAttrAndStyle();
    CheckProgressAttrAndStyle(inspectProgress, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectQRcodeTest001
 * @tc.desc: InspectQRcode::InspectQRcode
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectQRcodeTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectQRcode inspectQRcode(nodeId, tag);
    EXPECT_EQ(inspectQRcode.nodeId_, nodeId);
    EXPECT_EQ(inspectQRcode.tag_, tag);
}

/**
 * @tc.name: InspectQRcodeTest002
 * @tc.desc: InspectQRcode::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectQRcodeTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectQRcode inspectQRcode(nodeId, tag);
    auto attrsSize = inspectQRcode.attrs_.size();
    auto stylesSize = inspectQRcode.styles_.size();
    uint16_t attrsSizeInsert = 3;
    uint16_t stylesSizeInsert = 2;

    inspectQRcode.PackAttrAndStyle();
    EXPECT_EQ(inspectQRcode.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectQRcode.attrs_["type"], "rect");
    EXPECT_EQ(inspectQRcode.attrs_["disabled"], "false");
    EXPECT_EQ(inspectQRcode.attrs_["focusable"], "false");
    EXPECT_EQ(inspectQRcode.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectQRcode.styles_["color"], "#000000");
    EXPECT_EQ(inspectQRcode.styles_["background-color"], "#ffffff");
}

/**
 * @tc.name: InspectRatingTest001
 * @tc.desc: InspectRating::InspectRating
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectRatingTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    EXPECT_EQ(inspectRating.nodeId_, nodeId);
    EXPECT_EQ(inspectRating.tag_, tag);
}

/**
 * @tc.name: InspectRatingTest002
 * @tc.desc: InspectRating::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectRatingTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    auto attrsSize = inspectRating.attrs_.size();
    auto stylesSize = inspectRating.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectRating.PackAttrAndStyle();
    CheckRatingAttrAndStyle(inspectRating, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRatingTest003
 * @tc.desc: InspectRating::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectRatingTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    auto attrsSize = inspectRating.attrs_.size();
    auto stylesSize = inspectRating.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectRating.PackAttrAndStyle();
    CheckRatingAttrAndStyle(inspectRating, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRatingTest004
 * @tc.desc: InspectRating::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectRatingTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    auto attrsSize = inspectRating.attrs_.size();
    auto stylesSize = inspectRating.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectRating.PackAttrAndStyle();
    CheckRatingAttrAndStyle(inspectRating, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRatingTest005
 * @tc.desc: InspectRating::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectRatingTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    auto attrsSize = inspectRating.attrs_.size();
    auto stylesSize = inspectRating.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectRating.PackAttrAndStyle();
    CheckRatingAttrAndStyle(inspectRating, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRatingTest006
 * @tc.desc: InspectRating::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectRatingTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    auto attrsSize = inspectRating.attrs_.size();
    auto stylesSize = inspectRating.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectRating.PackAttrAndStyle();
    CheckRatingAttrAndStyle(inspectRating, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRatingTest007
 * @tc.desc: InspectRating::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectRatingTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    auto attrsSize = inspectRating.attrs_.size();
    auto stylesSize = inspectRating.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectRating.PackAttrAndStyle();
    CheckRatingAttrAndStyle(inspectRating, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRefreshTest001
 * @tc.desc: InspectRefresh::InspectRefresh
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectRefreshTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    EXPECT_EQ(inspectRefresh.nodeId_, nodeId);
    EXPECT_EQ(inspectRefresh.tag_, tag);
}

/**
 * @tc.name: InspectRefreshTest002
 * @tc.desc: InspectRefresh::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectRefreshTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    auto attrsSize = inspectRefresh.attrs_.size();
    auto stylesSize = inspectRefresh.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectRefresh.PackAttrAndStyle();
    CheckRefreshAttrAndStyle(inspectRefresh, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRefreshTest003
 * @tc.desc: InspectRefresh::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectRefreshTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    auto attrsSize = inspectRefresh.attrs_.size();
    auto stylesSize = inspectRefresh.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectRefresh.PackAttrAndStyle();
    CheckRefreshAttrAndStyle(inspectRefresh, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRefreshTest004
 * @tc.desc: InspectRefresh::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectRefreshTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    auto attrsSize = inspectRefresh.attrs_.size();
    auto stylesSize = inspectRefresh.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectRefresh.PackAttrAndStyle();
    CheckRefreshAttrAndStyle(inspectRefresh, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRefreshTest005
 * @tc.desc: InspectRefresh::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectRefreshTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    auto attrsSize = inspectRefresh.attrs_.size();
    auto stylesSize = inspectRefresh.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectRefresh.PackAttrAndStyle();
    CheckRefreshAttrAndStyle(inspectRefresh, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRefreshTest006
 * @tc.desc: InspectRefresh::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectRefreshTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    auto attrsSize = inspectRefresh.attrs_.size();
    auto stylesSize = inspectRefresh.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectRefresh.PackAttrAndStyle();
    CheckRefreshAttrAndStyle(inspectRefresh, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRefreshTest007
 * @tc.desc: InspectRefresh::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectRefreshTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    auto attrsSize = inspectRefresh.attrs_.size();
    auto stylesSize = inspectRefresh.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectRefresh.PackAttrAndStyle();
    CheckRefreshAttrAndStyle(inspectRefresh, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSearchTest001
 * @tc.desc: InspectSearch::InspectSearch
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSearchTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSearch inspectSearch(nodeId, tag);
    EXPECT_EQ(inspectSearch.nodeId_, nodeId);
    EXPECT_EQ(inspectSearch.tag_, tag);
}

/**
 * @tc.name: InspectSearchTest002
 * @tc.desc: InspectSearch::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSearchTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSearch inspectSearch(nodeId, tag);
    auto attrsSize = inspectSearch.attrs_.size();
    auto stylesSize = inspectSearch.styles_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 3;

    inspectSearch.PackAttrAndStyle();
    EXPECT_EQ(inspectSearch.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectSearch.attrs_["disabled"], "false");
    EXPECT_EQ(inspectSearch.attrs_["focusable"], "true");
    EXPECT_EQ(inspectSearch.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectSearch.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectSearch.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectSearch.styles_["font-family"], "sans-serif");
}

/**
 * @tc.name: InspectSelectTest001
 * @tc.desc: InspectSelect::InspectSelect
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSelectTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSelect inspectSelect(nodeId, tag);
    EXPECT_EQ(inspectSelect.nodeId_, nodeId);
    EXPECT_EQ(inspectSelect.tag_, tag);
}

/**
 * @tc.name: InspectSelectTest002
 * @tc.desc: InspectSelect::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSelectTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSelect inspectSelect(nodeId, tag);
    auto attrsSize = inspectSelect.attrs_.size();
    auto stylesSize = inspectSelect.styles_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 1;

    inspectSelect.PackAttrAndStyle();
    EXPECT_EQ(inspectSelect.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectSelect.attrs_["disabled"], "false");
    EXPECT_EQ(inspectSelect.attrs_["focusable"], "true");
    EXPECT_EQ(inspectSelect.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectSelect.styles_["font-family"], "sans-serif");
}

/**
 * @tc.name: InspectSliderTest001
 * @tc.desc: InspectSlider::InspectSlider
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSliderTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSlider inspectSlider(nodeId, tag);
    EXPECT_EQ(inspectSlider.nodeId_, nodeId);
    EXPECT_EQ(inspectSlider.tag_, tag);
}

/**
 * @tc.name: InspectSliderTest002
 * @tc.desc: InspectSlider::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSliderTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSlider inspectSlider(nodeId, tag);
    auto attrsSize = inspectSlider.attrs_.size();
    auto stylesSize = inspectSlider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectSlider.PackAttrAndStyle();
    CheckSliderAttrAndStyle(inspectSlider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSliderTest003
 * @tc.desc: InspectSlider::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSliderTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSlider inspectSlider(nodeId, tag);
    auto attrsSize = inspectSlider.attrs_.size();
    auto stylesSize = inspectSlider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectSlider.PackAttrAndStyle();
    CheckSliderAttrAndStyle(inspectSlider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSliderTest004
 * @tc.desc: InspectSlider::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSliderTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSlider inspectSlider(nodeId, tag);
    auto attrsSize = inspectSlider.attrs_.size();
    auto stylesSize = inspectSlider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectSlider.PackAttrAndStyle();
    CheckSliderAttrAndStyle(inspectSlider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSliderTest005
 * @tc.desc: InspectSlider::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSliderTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSlider inspectSlider(nodeId, tag);
    auto attrsSize = inspectSlider.attrs_.size();
    auto stylesSize = inspectSlider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectSlider.PackAttrAndStyle();
    CheckSliderAttrAndStyle(inspectSlider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSliderTest006
 * @tc.desc: InspectSlider::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSliderTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSlider inspectSlider(nodeId, tag);
    auto attrsSize = inspectSlider.attrs_.size();
    auto stylesSize = inspectSlider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectSlider.PackAttrAndStyle();
    CheckSliderAttrAndStyle(inspectSlider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSliderTest007
 * @tc.desc: InspectSlider::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSliderTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSlider inspectSlider(nodeId, tag);
    auto attrsSize = inspectSlider.attrs_.size();
    auto stylesSize = inspectSlider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectSlider.PackAttrAndStyle();
    CheckSliderAttrAndStyle(inspectSlider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSpanTest001
 * @tc.desc: InspectSpan::InspectSpan
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSpanTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSpan inspectSpan(nodeId, tag);
    EXPECT_EQ(inspectSpan.nodeId_, nodeId);
    EXPECT_EQ(inspectSpan.tag_, tag);
}

/**
 * @tc.name: InspectSpanTest002
 * @tc.desc: InspectSpan::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSpanTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSpan inspectSpan(nodeId, tag);
    auto stylesSize = inspectSpan.styles_.size();
    uint16_t stylesSizeInsert = 6;

    inspectSpan.PackAttrAndStyle();
    EXPECT_EQ(inspectSpan.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectSpan.styles_["font-size"], "30px");
    EXPECT_EQ(inspectSpan.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectSpan.styles_["font-style"], "normal");
    EXPECT_EQ(inspectSpan.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectSpan.styles_["text-decoration"], "none");
    EXPECT_EQ(inspectSpan.styles_["font-family"], "sans-serif");
}

/**
 * @tc.name: InspectStackTest001
 * @tc.desc: InspectStack::InspectStack
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectStackTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectStack inspectStack(nodeId, tag);
    EXPECT_EQ(inspectStack.nodeId_, nodeId);
    EXPECT_EQ(inspectStack.tag_, tag);
}

/**
 * @tc.name: InspectStackTest002
 * @tc.desc: InspectStack::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectStackTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectStack inspectStack(nodeId, tag);
    auto attrsSize = inspectStack.attrs_.size();
    uint16_t attrsSizeInsert = 2;

    inspectStack.PackAttrAndStyle();
    EXPECT_EQ(inspectStack.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectStack.attrs_["disabled"], "false");
    EXPECT_EQ(inspectStack.attrs_["focusable"], "true");
}

/**
 * @tc.name: InspectStepperItemTest001
 * @tc.desc: InspectStepperItem::InspectStepperItem
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectStepperItemTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectStepperItem inspectStepperItem(nodeId, tag);
    EXPECT_EQ(inspectStepperItem.nodeId_, nodeId);
    EXPECT_EQ(inspectStepperItem.tag_, tag);
}

/**
 * @tc.name: InspectStepperItemTest002
 * @tc.desc: InspectStepperItem::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectStepperItemTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectStepperItem inspectStepperItem(nodeId, tag);
    auto attrsSize = inspectStepperItem.attrs_.size();
    auto stylesSize = inspectStepperItem.styles_.size();
    uint16_t attrsSizeInsert = 1;
    uint16_t stylesSizeInsert = 7;

    inspectStepperItem.PackAttrAndStyle();
    EXPECT_EQ(inspectStepperItem.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectStepperItem.attrs_["disabled"], "false");
    EXPECT_EQ(inspectStepperItem.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectStepperItem.styles_["color"], "#e600000");
    EXPECT_EQ(inspectStepperItem.styles_["font-size"], "16px");
    EXPECT_EQ(inspectStepperItem.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectStepperItem.styles_["font-style"], "normal");
    EXPECT_EQ(inspectStepperItem.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectStepperItem.styles_["text-decoration"], "none");
    EXPECT_EQ(inspectStepperItem.styles_["font-family"], "sans-serif");
    EXPECT_EQ(inspectStepperItem.styles_.find("flex-grow"), inspectStepperItem.styles_.end());
    EXPECT_EQ(inspectStepperItem.styles_.find("flex-shrink"), inspectStepperItem.styles_.end());
    EXPECT_EQ(inspectStepperItem.styles_.find("position"), inspectStepperItem.styles_.end());
}

/**
 * @tc.name: InspectStepperTest001
 * @tc.desc: InspectStepper::InspectStepper
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectStepperTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectStepper inspectStepper(nodeId, tag);
    EXPECT_EQ(inspectStepper.nodeId_, nodeId);
    EXPECT_EQ(inspectStepper.tag_, tag);
}

/**
 * @tc.name: InspectStepperTest002
 * @tc.desc: InspectStepper::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectStepperTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectStepper inspectStepper(nodeId, tag);
    auto attrsSize = inspectStepper.attrs_.size();
    uint16_t attrsSizeInsert = 2;

    inspectStepper.PackAttrAndStyle();
    EXPECT_EQ(inspectStepper.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectStepper.attrs_["disabled"], "false");
    EXPECT_EQ(inspectStepper.attrs_["focusable"], "false");
}

/**
 * @tc.name: InspectSwiperTest001
 * @tc.desc: InspectSwiper::InspectSwiper
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSwiperTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwiper inspectSwiper(nodeId, tag);
    EXPECT_EQ(inspectSwiper.nodeId_, nodeId);
    EXPECT_EQ(inspectSwiper.tag_, tag);
}

/**
 * @tc.name: InspectSwiperTest002
 * @tc.desc: InspectSwiper::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSwiperTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwiper inspectSwiper(nodeId, tag);
    auto attrsSize = inspectSwiper.attrs_.size();
    auto stylesSize = inspectSwiper.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectSwiper.PackAttrAndStyle();
    CheckSwiperAttrAndStyle(inspectSwiper, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSwiperTest003
 * @tc.desc: InspectSwiper::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSwiperTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwiper inspectSwiper(nodeId, tag);
    auto attrsSize = inspectSwiper.attrs_.size();
    auto stylesSize = inspectSwiper.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectSwiper.PackAttrAndStyle();
    CheckSwiperAttrAndStyle(inspectSwiper, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSwiperTest004
 * @tc.desc: InspectSwiper::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSwiperTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwiper inspectSwiper(nodeId, tag);
    auto attrsSize = inspectSwiper.attrs_.size();
    auto stylesSize = inspectSwiper.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectSwiper.PackAttrAndStyle();
    CheckSwiperAttrAndStyle(inspectSwiper, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSwiperTest005
 * @tc.desc: InspectSwiper::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSwiperTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwiper inspectSwiper(nodeId, tag);
    auto attrsSize = inspectSwiper.attrs_.size();
    auto stylesSize = inspectSwiper.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectSwiper.PackAttrAndStyle();
    CheckSwiperAttrAndStyle(inspectSwiper, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSwiperTest006
 * @tc.desc: InspectSwiper::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSwiperTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwiper inspectSwiper(nodeId, tag);
    auto attrsSize = inspectSwiper.attrs_.size();
    auto stylesSize = inspectSwiper.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectSwiper.PackAttrAndStyle();
    CheckSwiperAttrAndStyle(inspectSwiper, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSwiperTest007
 * @tc.desc: InspectSwiper::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSwiperTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwiper inspectSwiper(nodeId, tag);
    auto attrsSize = inspectSwiper.attrs_.size();
    auto stylesSize = inspectSwiper.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectSwiper.PackAttrAndStyle();
    CheckSwiperAttrAndStyle(inspectSwiper, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSwitchTest001
 * @tc.desc: InspectSwitch::InspectSwitch
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSwitchTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwitch inspectSwitch(nodeId, tag);
    EXPECT_EQ(inspectSwitch.nodeId_, nodeId);
    EXPECT_EQ(inspectSwitch.tag_, tag);
}

/**
 * @tc.name: InspectSwitchTest002
 * @tc.desc: InspectSwitch::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectSwitchTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwitch inspectSwitch(nodeId, tag);
    auto attrsSize = inspectSwitch.attrs_.size();
    auto stylesSize = inspectSwitch.styles_.size();
    uint16_t attrsSizeInsert = 6;
    uint16_t stylesSizeInsert = 7;

    inspectSwitch.PackAttrAndStyle();
    EXPECT_EQ(inspectSwitch.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectSwitch.attrs_["checked"], "false");
    EXPECT_EQ(inspectSwitch.attrs_["showtext"], "false");
    EXPECT_EQ(inspectSwitch.attrs_["texton"], "On");
    EXPECT_EQ(inspectSwitch.attrs_["textoff"], "Off");
    EXPECT_EQ(inspectSwitch.attrs_["disabled"], "false");
    EXPECT_EQ(inspectSwitch.attrs_["focusable"], "true");
    EXPECT_EQ(inspectSwitch.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectSwitch.styles_["texton-color"], "#000000");
    EXPECT_EQ(inspectSwitch.styles_["textoff-color"], "#000000");
    EXPECT_EQ(inspectSwitch.styles_["text-padding"], "0px");
    EXPECT_EQ(inspectSwitch.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectSwitch.styles_["font-style"], "normal");
    EXPECT_EQ(inspectSwitch.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectSwitch.styles_["font-family"], "sans-serif");
}

/**
 * @tc.name: InspectTabBarTest001
 * @tc.desc: InspectTabBar::InspectTabBar
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectTabBarTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectTabBar inspectTabBar(nodeId, tag);
    EXPECT_EQ(inspectTabBar.nodeId_, nodeId);
    EXPECT_EQ(inspectTabBar.tag_, tag);
}

/**
 * @tc.name: InspectTabBarTest002
 * @tc.desc: InspectTabBar::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectTabBarTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    uint16_t typeNum = 6;
    DeviceType deviceType = SystemProperties::GetDeviceType();
    for (uint16_t i = 0; i < typeNum; i++) {
        InspectTabBar inspectTabBar(nodeId, tag);
        auto attrsSize = inspectTabBar.attrs_.size();
        auto stylesSize = inspectTabBar.styles_.size();
        SystemProperties::SetDeviceType(static_cast<DeviceType>(i));
        inspectTabBar.PackAttrAndStyle();
        CheckTabBarAttrAndStyle(inspectTabBar, attrsSize, stylesSize);
    }
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectTabContentTest001
 * @tc.desc: InspectTabContent::InspectTabContent
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectTabContentTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectTabContent inspectTabContent(nodeId, tag);
    EXPECT_EQ(inspectTabContent.nodeId_, nodeId);
    EXPECT_EQ(inspectTabContent.tag_, tag);
}

/**
 * @tc.name: InspectTabContentTest002
 * @tc.desc: InspectTabContent::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectTabContentTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectTabContent inspectTabContent(nodeId, tag);
    auto attrsSize = inspectTabContent.attrs_.size();
    uint16_t attrsSizeInsert = 3;

    inspectTabContent.PackAttrAndStyle();
    EXPECT_EQ(inspectTabContent.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectTabContent.attrs_["scrollable"], "true");
    EXPECT_EQ(inspectTabContent.attrs_["disabled"], "false");
    EXPECT_EQ(inspectTabContent.attrs_["focusable"], "true");
}

/**
 * @tc.name: InspectTabsTest001
 * @tc.desc: InspectTabs::InspectTabs
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectTabsTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectTabs inspectTabs(nodeId, tag);
    EXPECT_EQ(inspectTabs.nodeId_, nodeId);
    EXPECT_EQ(inspectTabs.tag_, tag);
}

/**
 * @tc.name: InspectTabsTest002
 * @tc.desc: InspectTabs::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectTabsTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectTabs inspectTabs(nodeId, tag);
    auto attrsSize = inspectTabs.attrs_.size();
    uint16_t attrsSizeInsert = 4;

    inspectTabs.PackAttrAndStyle();
    EXPECT_EQ(inspectTabs.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectTabs.attrs_["index"], "0");
    EXPECT_EQ(inspectTabs.attrs_["vertical"], "false");
    EXPECT_EQ(inspectTabs.attrs_["disabled"], "false");
    EXPECT_EQ(inspectTabs.attrs_["focusable"], "true");
}

/**
 * @tc.name: InspectTextTest001
 * @tc.desc: InspectText::InspectText
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectTextTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectText inspectText(nodeId, tag);
    EXPECT_EQ(inspectText.nodeId_, nodeId);
    EXPECT_EQ(inspectText.tag_, tag);
}

/**
 * @tc.name: InspectTextTest002
 * @tc.desc: InspectText::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectTextTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    uint16_t typeNum = 6;
    DeviceType deviceType = SystemProperties::GetDeviceType();
    for (uint16_t i = 0; i < typeNum; i++) {
        InspectText inspectText(nodeId, tag);
        auto attrsSize = inspectText.attrs_.size();
        auto stylesSize = inspectText.styles_.size();
        SystemProperties::SetDeviceType(static_cast<DeviceType>(i));
        inspectText.PackAttrAndStyle();
        CheckTextAttrAndStyle(inspectText, attrsSize, stylesSize);
    }
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectTextAreaTest001
 * @tc.desc: InspectTextArea::InspectTextArea
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectTextAreaTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectTextArea inspectTextArea(nodeId, tag);
    EXPECT_EQ(inspectTextArea.nodeId_, nodeId);
    EXPECT_EQ(inspectTextArea.tag_, tag);
}

/**
 * @tc.name: InspectTextAreaTest002
 * @tc.desc: InspectTextArea::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectTextAreaTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    uint16_t typeNum = 6;
    DeviceType deviceType = SystemProperties::GetDeviceType();
    for (uint16_t i = 0; i < typeNum; i++) {
        InspectTextArea inspectTextArea(nodeId, tag);
        auto attrsSize = inspectTextArea.attrs_.size();
        auto stylesSize = inspectTextArea.styles_.size();
        SystemProperties::SetDeviceType(static_cast<DeviceType>(i));
        inspectTextArea.PackAttrAndStyle();
        CheckTextAreaAttrAndStyle(inspectTextArea, attrsSize, stylesSize);
    }
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectToggleTest001
 * @tc.desc: InspectToggle::InspectToggle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectToggleTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectToggle inspectToggle(nodeId, tag);
    EXPECT_EQ(inspectToggle.nodeId_, nodeId);
    EXPECT_EQ(inspectToggle.tag_, tag);
}

/**
 * @tc.name: InspectToggleTest002
 * @tc.desc: InspectToggle::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectToggleTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    uint16_t typeNum = 6;
    DeviceType deviceType = SystemProperties::GetDeviceType();
    for (uint16_t i = 0; i < typeNum; i++) {
        InspectToggle inspectToggle(nodeId, tag);
        auto attrsSize = inspectToggle.attrs_.size();
        auto stylesSize = inspectToggle.styles_.size();
        SystemProperties::SetDeviceType(static_cast<DeviceType>(i));
        inspectToggle.PackAttrAndStyle();
        CheckToggleAttrAndStyle(inspectToggle, attrsSize, stylesSize);
    }
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectToolbarItemTest001
 * @tc.desc: InspectToolbarItem::InspectToolbarItem
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectToolbarItemTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectToolbarItem inspectToolbarItem(nodeId, tag);
    EXPECT_EQ(inspectToolbarItem.nodeId_, nodeId);
    EXPECT_EQ(inspectToolbarItem.tag_, tag);
}

/**
 * @tc.name: InspectToolbarItemTest002
 * @tc.desc: InspectToolbarItem::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectToolbarItemTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectToolbarItem inspectToolbarItem(nodeId, tag);
    auto attrsSize = inspectToolbarItem.attrs_.size();
    auto stylesSize = inspectToolbarItem.styles_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 13;

    inspectToolbarItem.PackAttrAndStyle();
    EXPECT_EQ(inspectToolbarItem.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectToolbarItem.attrs_["disabled"], "false");
    EXPECT_EQ(inspectToolbarItem.attrs_["focusable"], "false");
    EXPECT_EQ(inspectToolbarItem.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectToolbarItem.styles_["color"], "#e6000000");
    EXPECT_EQ(inspectToolbarItem.styles_["font-size"], "16px");
    EXPECT_EQ(inspectToolbarItem.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectToolbarItem.styles_["font-style"], "normal");
    EXPECT_EQ(inspectToolbarItem.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectToolbarItem.styles_["text-decoration"], "none");
    EXPECT_EQ(inspectToolbarItem.styles_["font-family"], "sans-serif");
    EXPECT_EQ(inspectToolbarItem.styles_["background-size"], "auto");
    EXPECT_EQ(inspectToolbarItem.styles_["background-repeat"], "repeat");
    EXPECT_EQ(inspectToolbarItem.styles_["background-position"], "0px 0px");
    EXPECT_EQ(inspectToolbarItem.styles_["opacity"], "1");
    EXPECT_EQ(inspectToolbarItem.styles_["display"], "flex");
    EXPECT_EQ(inspectToolbarItem.styles_["visibility"], "visible");
}

/**
 * @tc.name: InspectToolbarTest001
 * @tc.desc: InspectToolbar::InspectToolbar
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectToolbarTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectToolbar inspectToolbar(nodeId, tag);
    EXPECT_EQ(inspectToolbar.nodeId_, nodeId);
    EXPECT_EQ(inspectToolbar.tag_, tag);
}

/**
 * @tc.name: InspectVideoTest001
 * @tc.desc: InspectVideo::InspectVideo
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectVideoTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectVideo inspectVideo(nodeId, tag);
    EXPECT_EQ(inspectVideo.nodeId_, nodeId);
    EXPECT_EQ(inspectVideo.tag_, tag);
}

/**
 * @tc.name: InspectVideoTest002
 * @tc.desc: InspectVideo::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(JSInspectorTest, InspectVideoTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectVideo inspectVideo(nodeId, tag);
    auto attrsSize = inspectVideo.attrs_.size();
    auto stylesSize = inspectVideo.styles_.size();
    uint16_t attrsSizeInsert = 5;
    uint16_t stylesSizeInsert = 1;

    inspectVideo.PackAttrAndStyle();
    EXPECT_EQ(inspectVideo.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectVideo.attrs_["muted"], "false");
    EXPECT_EQ(inspectVideo.attrs_["autoplay"], "false");
    EXPECT_EQ(inspectVideo.attrs_["controls"], "true");
    EXPECT_EQ(inspectVideo.attrs_["disabled"], "false");
    EXPECT_EQ(inspectVideo.attrs_["focusable"], "true");
    EXPECT_EQ(inspectVideo.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectVideo.styles_["object-fit"], "contain");
}
} // namespace OHOS::Ace::Framework
