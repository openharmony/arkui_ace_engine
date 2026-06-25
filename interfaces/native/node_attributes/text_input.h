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

/**
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Defines a set of TextInput enum and interface.
 *
 * @since 12
 */

/**
 * @file text_input.h
 *
 * @brief Defines a set of TextInput enum and interface.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_INPUT_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_INPUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the text input types.
 *
 * @since 12
 */
typedef enum {
    /** Normal input mode. */
    ARKUI_TEXTINPUT_TYPE_NORMAL = 0,
    /** Number input mode. */
    ARKUI_TEXTINPUT_TYPE_NUMBER = 2,
    /** Phone number input mode. */
    ARKUI_TEXTINPUT_TYPE_PHONE_NUMBER = 3,
    /** Email address input mode. */
    ARKUI_TEXTINPUT_TYPE_EMAIL = 5,
    /** Password input mode. */
    ARKUI_TEXTINPUT_TYPE_PASSWORD = 7,
    /** Numeric password input mode. */
    ARKUI_TEXTINPUT_TYPE_NUMBER_PASSWORD = 8,
    /** Lock screen password input mode. */
    ARKUI_TEXTINPUT_TYPE_SCREEN_LOCK_PASSWORD = 9,
    /** Username input mode. */
    ARKUI_TEXTINPUT_TYPE_USER_NAME = 10,
    /** New password input mode. */
    ARKUI_TEXTINPUT_TYPE_NEW_PASSWORD = 11,
    /** Number input mode with a decimal point. */
    ARKUI_TEXTINPUT_TYPE_NUMBER_DECIMAL = 12,
    /**
     * One time code input mode.
     * @since 20
     */
    ARKUI_TEXTINPUT_TYPE_ONE_TIME_CODE = 14,
} ArkUI_TextInputType;
/**
 * @brief Enumerates the styles of the Cancel button.
 *
 * @since 12
 */
typedef enum {
    /** The Cancel button is always displayed. */
    ARKUI_CANCELBUTTON_STYLE_CONSTANT = 0,
    /** The Cancel button is always hidden. */
    ARKUI_CANCELBUTTON_STYLE_INVISIBLE,
    /** The Cancel button is displayed when there is text input. */
    ARKUI_CANCELBUTTON_STYLE_INPUT,
} ArkUI_CancelButtonStyle;
/**
 * @brief Enumerates the autofill types.
 *
 * @since 12
 */
typedef enum {
    /** Username. Password Vault, when enabled, can automatically save and fill in usernames. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_USER_NAME = 0,
    /** Password. Password Vault, when enabled, can automatically save and fill in passwords. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PASSWORD,
    /** New password. Password Vault, when enabled, can automatically generate a new password. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_NEW_PASSWORD,
    /** Full street address. The scenario-based autofill feature, when enabled, can automatically save and fill in full
     *  street addresses. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_FULL_STREET_ADDRESS,
    /** House number. The scenario-based autofill feature, when enabled, can automatically save and fill in house
     *  numbers. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_HOUSE_NUMBER,
    /** District and county. The scenario-based autofill feature, when enabled, can automatically save and fill in
     *  districts and counties. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_DISTRICT_ADDRESS,
    /** City. The scenario-based autofill feature, when enabled, can automatically save and fill in cities. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_CITY_ADDRESS,
    /** Province. The scenario-based autofill feature, when enabled, can automatically save and fill in provinces. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PROVINCE_ADDRESS,
    /** Country. The scenario-based autofill feature, when enabled, can automatically save and fill in countries. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_COUNTRY_ADDRESS,
    /** Full name. The scenario-based autofill feature, when enabled, can automatically save and fill in full names. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PERSON_FULL_NAME,
    /** Last name. The scenario-based autofill feature, when enabled, can automatically save and fill in last names. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PERSON_LAST_NAME,
    /** First name. The scenario-based autofill feature, when enabled, can automatically save and fill in first names.
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PERSON_FIRST_NAME,
    /** Phone number. The scenario-based autofill feature, when enabled, can automatically save and fill in phone
     *  numbers. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PHONE_NUMBER,
    /** Country code. The scenario-based autofill feature, when enabled, can automatically save and fill in country
     *  codes. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PHONE_COUNTRY_CODE,
    /** Phone number with country code. The scenario-based autofill feature, when enabled, can automatically save and
     *  fill in phone numbers with country codes. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_FULL_PHONE_NUMBER,
    /** Email address. The scenario-based autofill feature, when enabled, can automatically save and fill in email
     *  addresses. */
    ARKUI_TEXTINPUT_CONTENT_EMAIL_ADDRESS,
    /** Bank card number. The scenario-based autofill feature, when enabled, can automatically save and fill in bank
     *  card numbers. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_BANK_CARD_NUMBER,
    /** ID card number. The scenario-based autofill feature, when enabled, can automatically save and fill in ID card
     *  numbers. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_ID_CARD_NUMBER,
    /** Nickname. The scenario-based autofill feature, when enabled, can automatically save and fill in nicknames. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_NICKNAME,
    /** Address information without street address. The scenario-based autofill feature, when enabled, can automatically
     *  save and fill in address information without street addresses. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_DETAIL_INFO_WITHOUT_STREET,
    /** Standard address. The scenario-based autofill feature, when enabled, can automatically save and fill in standard
     *  addresses. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_FORMAT_ADDRESS,
    /**
     * Passport number. The scenario-based autofill feature, when enabled, can automatically save and fill in passport
     * numbers.
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PASSPORT_NUMBER,
    /**
     *  Passport validity. The scenario-based autofill feature, when enabled, can automatically save and fill in
     *  passport validities.
     *  @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_VALIDITY,
    /**
     *  Place of issue. The scenario-based autofill feature, when enabled, can automatically save and fill in
     *  place of issues.
     *  @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_ISSUE_AT,
    /**
     *  Tax organization. The scenario-based autofill feature, when enabled, can automatically save and fill in tax
     *  organizations.
     *  @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_ORGANIZATION,
    /**
     *  Tax id. The scenario-based autofill feature, when enabled, can automatically save and fill in standard Tax ids.
     *  @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_TAX_ID,
    /**
     *  City name and state name or state code. The scenario-based autofill feature, when enabled, can automatically
     *  save and fill in city names and state names or state codes.
     *  @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_ADDRESS_CITY_AND_STATE,
    /**
     *  Flight number. The scenario-based autofill feature, when enabled, can automatically save and fill in flight
     *  numbers.
     *  @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_FLIGHT_NUMBER,
    /**
     *  License number. The scenario-based autofill feature, when enabled, can automatically save and fill in license
     *  numbers.
     *  @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_LICENSE_NUMBER,
    /**
     *  License file number. The scenario-based autofill feature, when enabled, can automatically save and fill in
     *  license file numbers.
     *  @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_LICENSE_FILE_NUMBER,
    /**
     *  License plate number. The scenario-based autofill feature, when enabled, can automatically save and fill in
     *  license plate numbers.
     *  @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_LICENSE_PLATE,
    /**
     *  Engine number. The scenario-based autofill feature, when enabled, can automatically save and fill in engine
     *  numbers.
     *  @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_ENGINE_NUMBER,
    /**
     *  License chassis number. The scenario-based autofill feature, when enabled, can automatically save and fill in
     *  license chassis numbers.
     *  @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_LICENSE_CHASSIS_NUMBER,
} ArkUI_TextInputContentType;
/**
 * @brief Defines the text input style.
 *
 * @since 12
 */
typedef enum {
    /** Default style. The caret width is fixed at 1.5 vp, and the caret height is subject to the background height and
     *  font size of the selected text. */
    ARKUI_TEXTINPUT_STYLE_DEFAULT = 0,
    /** Inline input style. The background height of the selected text is the same as the height of the text box. */
    ARKUI_TEXTINPUT_STYLE_INLINE
} ArkUI_TextInputStyle;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_INPUT_H
/** @} */
