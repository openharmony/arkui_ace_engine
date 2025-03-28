/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "common_method_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace {
    const auto ATTRIBUTE_TRANSFORM_NAME = "transform";
    const auto ATTRIBUTE_TRANSFORM_DEFAULT_VALUE = "{}";
    const auto ATTRIBUTE_CLICK_EFFECT_NAME = "clickEffect";
    const auto ATTRIBUTE_CLICK_EFFECT_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_DRAGGABLE_NAME = "draggable";
    const auto ATTRIBUTE_DRAGGABLE_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_MOTION_PATH_NAME = "motionPath";
    const auto ATTRIBUTE_MOTION_PATH_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_KEY_NAME = "id";
    const auto ATTRIBUTE_KEY_DEFAULT_VALUE = "";

    bool StrToArrayChar(char (&dst)[20], const char* src)
    {
        if (src == nullptr) {
            LOGE("Error: Source string is null.");
            return false;
        }
        size_t maxLen = sizeof(dst) - 1;
        size_t srcLen = std::strlen(src);
        if (srcLen > maxLen) {
            LOGE("Error: Source string is longer than destination buffer. String will be truncated.");
            return false;
        }
        for (size_t i = 0; i < srcLen && i < maxLen; ++i) {
            dst[i] = src[i];
        }
        dst[std::min(srcLen, maxLen)] = '\0';
        return true;
    }
} // namespace

void AssignArkValue(Ark_CustomObject& dst, const double (&value)[4][4])
{
    LOGE("This reverse converter is created for testing purposes only. Custom objects are not supported.");
    if (StrToArrayChar(dst.kind, "Matrix4")) {
        const int rowCount = sizeof(value) / sizeof(value[0]);
        for (int i = 0; i < rowCount; ++i) {
            dst.pointers[i] = (void*)value[i];
        }
    }
}

namespace OHOS::Ace::NG {
using AllowDropTestStep = std::tuple<Ark_UniformDataType, std::string>;
static const std::vector<AllowDropTestStep> ALLOW_DROP_TEST_PLAN = {
    {ARK_UNIFORM_DATA_TYPE_ENTITY, "ENTITY"},
    {ARK_UNIFORM_DATA_TYPE_OBJECT, "OBJECT"},
    {ARK_UNIFORM_DATA_TYPE_COMPOSITE_OBJECT, "COMPOSITE_OBJECT"},
    {ARK_UNIFORM_DATA_TYPE_TEXT, "TEXT"},
    {ARK_UNIFORM_DATA_TYPE_PLAIN_TEXT, "PLAIN_TEXT"},
    {ARK_UNIFORM_DATA_TYPE_HTML, "HTML"},
    {ARK_UNIFORM_DATA_TYPE_HYPERLINK, "HYPERLINK"},
    {ARK_UNIFORM_DATA_TYPE_XML, "XML"},
    {ARK_UNIFORM_DATA_TYPE_XHTML, "XHTML"},
    {ARK_UNIFORM_DATA_TYPE_RSS, "RSS"},
    {ARK_UNIFORM_DATA_TYPE_SMIL, "SMIL"},
    {ARK_UNIFORM_DATA_TYPE_SOURCE_CODE, "SOURCE_CODE"},
    {ARK_UNIFORM_DATA_TYPE_SCRIPT, "SCRIPT"},
    {ARK_UNIFORM_DATA_TYPE_SHELL_SCRIPT, "SHELL_SCRIPT"},
    {ARK_UNIFORM_DATA_TYPE_CSH_SCRIPT, "CSH_SCRIPT"},
    {ARK_UNIFORM_DATA_TYPE_PERL_SCRIPT, "PERL_SCRIPT"},
    {ARK_UNIFORM_DATA_TYPE_PHP_SCRIPT, "PHP_SCRIPT"},
    {ARK_UNIFORM_DATA_TYPE_PYTHON_SCRIPT, "PYTHON_SCRIPT"},
    {ARK_UNIFORM_DATA_TYPE_RUBY_SCRIPT, "RUBY_SCRIPT"},
    {ARK_UNIFORM_DATA_TYPE_TYPE_SCRIPT, "TYPE_SCRIPT"},
    {ARK_UNIFORM_DATA_TYPE_JAVA_SCRIPT, "JAVA_SCRIPT"},
    {ARK_UNIFORM_DATA_TYPE_CSS, "CSS"},
    {ARK_UNIFORM_DATA_TYPE_C_HEADER, "C_HEADER"},
    {ARK_UNIFORM_DATA_TYPE_C_SOURCE, "C_SOURCE"},
    {ARK_UNIFORM_DATA_TYPE_C_PLUS_PLUS_HEADER, "C_PLUS_PLUS_HEADER"},
    {ARK_UNIFORM_DATA_TYPE_C_PLUS_PLUS_SOURCE, "C_PLUS_PLUS_SOURCE"},
    {ARK_UNIFORM_DATA_TYPE_JAVA_SOURCE, "JAVA_SOURCE"},
    {ARK_UNIFORM_DATA_TYPE_TEX, "TEX"},
    {ARK_UNIFORM_DATA_TYPE_MARKDOWN, "MARKDOWN"},
    {ARK_UNIFORM_DATA_TYPE_ASC_TEXT, "ASC_TEXT"},
    {ARK_UNIFORM_DATA_TYPE_RICH_TEXT, "RICH_TEXT"},
    {ARK_UNIFORM_DATA_TYPE_DELIMITED_VALUES_TEXT, "DELIMITED_VALUES_TEXT"},
    {ARK_UNIFORM_DATA_TYPE_COMMA_SEPARATED_VALUES_TEXT, "COMMA_SEPARATED_VALUES_TEXT"},
    {ARK_UNIFORM_DATA_TYPE_TAB_SEPARATED_VALUES_TEXT, "TAB_SEPARATED_VALUES_TEXT"},
    {ARK_UNIFORM_DATA_TYPE_EBOOK, "EBOOK"},
    {ARK_UNIFORM_DATA_TYPE_EPUB, "EPUB"},
    {ARK_UNIFORM_DATA_TYPE_AZW, "AZW"},
    {ARK_UNIFORM_DATA_TYPE_AZW3, "AZW3"},
    {ARK_UNIFORM_DATA_TYPE_KFX, "KFX"},
    {ARK_UNIFORM_DATA_TYPE_MOBI, "MOBI"},
    {ARK_UNIFORM_DATA_TYPE_MEDIA, "MEDIA"},
    {ARK_UNIFORM_DATA_TYPE_IMAGE, "IMAGE"},
    {ARK_UNIFORM_DATA_TYPE_JPEG, "JPEG"},
    {ARK_UNIFORM_DATA_TYPE_PNG, "PNG"},
    {ARK_UNIFORM_DATA_TYPE_RAW_IMAGE, "RAW_IMAGE"},
    {ARK_UNIFORM_DATA_TYPE_TIFF, "TIFF"},
    {ARK_UNIFORM_DATA_TYPE_BMP, "BMP"},
    {ARK_UNIFORM_DATA_TYPE_ICO, "ICO"},
    {ARK_UNIFORM_DATA_TYPE_PHOTOSHOP_IMAGE, "PHOTOSHOP_IMAGE"},
    {ARK_UNIFORM_DATA_TYPE_AI_IMAGE, "AI_IMAGE"},
    {ARK_UNIFORM_DATA_TYPE_FAX, "FAX"},
    {ARK_UNIFORM_DATA_TYPE_JFX_FAX, "JFX_FAX"},
    {ARK_UNIFORM_DATA_TYPE_EFX_FAX, "EFX_FAX"},
    {ARK_UNIFORM_DATA_TYPE_XBITMAP_IMAGE, "XBITMAP_IMAGE"},
    {ARK_UNIFORM_DATA_TYPE_GIF, "GIF"},
    {ARK_UNIFORM_DATA_TYPE_TGA_IMAGE, "TGA_IMAGE"},
    {ARK_UNIFORM_DATA_TYPE_SGI_IMAGE, "SGI_IMAGE"},
    {ARK_UNIFORM_DATA_TYPE_OPENEXR_IMAGE, "OPENEXR_IMAGE"},
    {ARK_UNIFORM_DATA_TYPE_FLASHPIX_IMAGE, "FLASHPIX_IMAGE"},
    {ARK_UNIFORM_DATA_TYPE_WORD_DOC, "WORD_DOC"},
    {ARK_UNIFORM_DATA_TYPE_EXCEL, "EXCEL"},
    {ARK_UNIFORM_DATA_TYPE_PPT, "PPT"},
    {ARK_UNIFORM_DATA_TYPE_WORD_DOT, "WORD_DOT"},
    {ARK_UNIFORM_DATA_TYPE_POWERPOINT_PPS, "POWERPOINT_PPS"},
    {ARK_UNIFORM_DATA_TYPE_EXCEL_XLT, "EXCEL_XLT"},
    {ARK_UNIFORM_DATA_TYPE_POWERPOINT_POT, "POWERPOINT_POT"},
    {ARK_UNIFORM_DATA_TYPE_VISIO_VSD, "VISIO_VSD"},
    {ARK_UNIFORM_DATA_TYPE_PDF, "PDF"},
    {ARK_UNIFORM_DATA_TYPE_POSTSCRIPT, "POSTSCRIPT"},
    {ARK_UNIFORM_DATA_TYPE_ENCAPSULATED_POSTSCRIPT, "ENCAPSULATED_POSTSCRIPT"},
    {ARK_UNIFORM_DATA_TYPE_VIDEO, "VIDEO"},
    {ARK_UNIFORM_DATA_TYPE_AVI, "AVI"},
    {ARK_UNIFORM_DATA_TYPE_MPEG, "MPEG"},
    {ARK_UNIFORM_DATA_TYPE_MPEG4, "MPEG4"},
    {ARK_UNIFORM_DATA_TYPE_VIDEO_3GPP, "VIDEO_3GPP"},
    {ARK_UNIFORM_DATA_TYPE_VIDEO_3GPP2, "VIDEO_3GPP2"},
    {ARK_UNIFORM_DATA_TYPE_TS, "TS"},
    {ARK_UNIFORM_DATA_TYPE_MPEGURL_VIDEO, "MPEGURL_VIDEO"},
    {ARK_UNIFORM_DATA_TYPE_WINDOWS_MEDIA_WM, "WINDOWS_MEDIA_WM"},
    {ARK_UNIFORM_DATA_TYPE_WINDOWS_MEDIA_WMV, "WINDOWS_MEDIA_WMV"},
    {ARK_UNIFORM_DATA_TYPE_WINDOWS_MEDIA_WMP, "WINDOWS_MEDIA_WMP"},
    {ARK_UNIFORM_DATA_TYPE_WINDOWS_MEDIA_WVX, "WINDOWS_MEDIA_WVX"},
    {ARK_UNIFORM_DATA_TYPE_WINDOWS_MEDIA_WMX, "WINDOWS_MEDIA_WMX"},
    {ARK_UNIFORM_DATA_TYPE_REALMEDIA, "REALMEDIA"},
    {ARK_UNIFORM_DATA_TYPE_MATROSKA_VIDEO, "MATROSKA_VIDEO"},
    {ARK_UNIFORM_DATA_TYPE_FLASH, "FLASH"},
    {ARK_UNIFORM_DATA_TYPE_AUDIO, "AUDIO"},
    {ARK_UNIFORM_DATA_TYPE_AAC, "AAC"},
    {ARK_UNIFORM_DATA_TYPE_AIFF, "AIFF"},
    {ARK_UNIFORM_DATA_TYPE_ALAC, "ALAC"},
    {ARK_UNIFORM_DATA_TYPE_FLAC, "FLAC"},
    {ARK_UNIFORM_DATA_TYPE_MP3, "MP3"},
    {ARK_UNIFORM_DATA_TYPE_OGG, "OGG"},
    {ARK_UNIFORM_DATA_TYPE_PCM, "PCM"},
    {ARK_UNIFORM_DATA_TYPE_WINDOWS_MEDIA_WMA, "WINDOWS_MEDIA_WMA"},
    {ARK_UNIFORM_DATA_TYPE_WAVEFORM_AUDIO, "WAVEFORM_AUDIO"},
    {ARK_UNIFORM_DATA_TYPE_WINDOWS_MEDIA_WAX, "WINDOWS_MEDIA_WAX"},
    {ARK_UNIFORM_DATA_TYPE_AU_AUDIO, "AU_AUDIO"},
    {ARK_UNIFORM_DATA_TYPE_AIFC_AUDIO, "AIFC_AUDIO"},
    {ARK_UNIFORM_DATA_TYPE_MPEGURL_AUDIO, "MPEGURL_AUDIO"},
    {ARK_UNIFORM_DATA_TYPE_MPEG_4_AUDIO, "MPEG_4_AUDIO"},
    {ARK_UNIFORM_DATA_TYPE_MP2, "MP2"},
    {ARK_UNIFORM_DATA_TYPE_MPEG_AUDIO, "MPEG_AUDIO"},
    {ARK_UNIFORM_DATA_TYPE_ULAW_AUDIO, "ULAW_AUDIO"},
    {ARK_UNIFORM_DATA_TYPE_SD2_AUDIO, "SD2_AUDIO"},
    {ARK_UNIFORM_DATA_TYPE_REALAUDIO, "REALAUDIO"},
    {ARK_UNIFORM_DATA_TYPE_MATROSKA_AUDIO, "MATROSKA_AUDIO"},
    {ARK_UNIFORM_DATA_TYPE_FILE, "FILE"},
    {ARK_UNIFORM_DATA_TYPE_DIRECTORY, "DIRECTORY"},
    {ARK_UNIFORM_DATA_TYPE_FOLDER, "FOLDER"},
    {ARK_UNIFORM_DATA_TYPE_SYMLINK, "SYMLINK"},
    {ARK_UNIFORM_DATA_TYPE_ARCHIVE, "ARCHIVE"},
    {ARK_UNIFORM_DATA_TYPE_BZ2_ARCHIVE, "BZ2_ARCHIVE"},
    {ARK_UNIFORM_DATA_TYPE_OPG, "OPG"},
    {ARK_UNIFORM_DATA_TYPE_TAZ_ARCHIVE, "TAZ_ARCHIVE"},
    {ARK_UNIFORM_DATA_TYPE_WEB_ARCHIVE, "WEB_ARCHIVE"},
    {ARK_UNIFORM_DATA_TYPE_DISK_IMAGE, "DISK_IMAGE"},
    {ARK_UNIFORM_DATA_TYPE_ISO, "ISO"},
    {ARK_UNIFORM_DATA_TYPE_TAR_ARCHIVE, "TAR_ARCHIVE"},
    {ARK_UNIFORM_DATA_TYPE_ZIP_ARCHIVE, "ZIP_ARCHIVE"},
    {ARK_UNIFORM_DATA_TYPE_JAVA_ARCHIVE, "JAVA_ARCHIVE"},
    {ARK_UNIFORM_DATA_TYPE_GNU_TAR_ARCHIVE, "GNU_TAR_ARCHIVE"},
    {ARK_UNIFORM_DATA_TYPE_GNU_ZIP_ARCHIVE, "GNU_ZIP_ARCHIVE"},
    {ARK_UNIFORM_DATA_TYPE_GNU_ZIP_TAR_ARCHIVE, "GNU_ZIP_TAR_ARCHIVE"},
    {ARK_UNIFORM_DATA_TYPE_OPENXML, "OPENXML"},
    {ARK_UNIFORM_DATA_TYPE_WORDPROCESSINGML_DOCUMENT, "WORDPROCESSINGML_DOCUMENT"},
    {ARK_UNIFORM_DATA_TYPE_SPREADSHEETML_SHEET, "SPREADSHEETML_SHEET"},
    {ARK_UNIFORM_DATA_TYPE_PRESENTATIONML_PRESENTATION, "PRESENTATIONML_PRESENTATION"},
    {ARK_UNIFORM_DATA_TYPE_DRAWINGML_VISIO, "DRAWINGML_VISIO"},
    {ARK_UNIFORM_DATA_TYPE_DRAWINGML_TEMPLATE, "DRAWINGML_TEMPLATE"},
    {ARK_UNIFORM_DATA_TYPE_WORDPROCESSINGML_TEMPLATE, "WORDPROCESSINGML_TEMPLATE"},
    {ARK_UNIFORM_DATA_TYPE_PRESENTATIONML_TEMPLATE, "PRESENTATIONML_TEMPLATE"},
    {ARK_UNIFORM_DATA_TYPE_PRESENTATIONML_SLIDESHOW, "PRESENTATIONML_SLIDESHOW"},
    {ARK_UNIFORM_DATA_TYPE_SPREADSHEETML_TEMPLATE, "SPREADSHEETML_TEMPLATE"},
    {ARK_UNIFORM_DATA_TYPE_OPENDOCUMENT, "OPENDOCUMENT"},
    {ARK_UNIFORM_DATA_TYPE_OPENDOCUMENT_TEXT, "OPENDOCUMENT_TEXT"},
    {ARK_UNIFORM_DATA_TYPE_OPENDOCUMENT_SPREADSHEET, "OPENDOCUMENT_SPREADSHEET"},
    {ARK_UNIFORM_DATA_TYPE_OPENDOCUMENT_PRESENTATION, "OPENDOCUMENT_PRESENTATION"},
    {ARK_UNIFORM_DATA_TYPE_OPENDOCUMENT_GRAPHICS, "OPENDOCUMENT_GRAPHICS"},
    {ARK_UNIFORM_DATA_TYPE_OPENDOCUMENT_FORMULA, "OPENDOCUMENT_FORMULA"},
    {ARK_UNIFORM_DATA_TYPE_STUFFIT_ARCHIVE, "STUFFIT_ARCHIVE"},
    {ARK_UNIFORM_DATA_TYPE_RAR_ARCHIVE, "RAR_ARCHIVE"},
    {ARK_UNIFORM_DATA_TYPE_SEVEN_ZIP_ARCHIVE, "SEVEN_ZIP_ARCHIVE"},
    {ARK_UNIFORM_DATA_TYPE_CALENDAR, "CALENDAR"},
    {ARK_UNIFORM_DATA_TYPE_VCS, "VCS"},
    {ARK_UNIFORM_DATA_TYPE_ICS, "ICS"},
    {ARK_UNIFORM_DATA_TYPE_CONTACT, "CONTACT"},
    {ARK_UNIFORM_DATA_TYPE_DATABASE, "DATABASE"},
    {ARK_UNIFORM_DATA_TYPE_MESSAGE, "MESSAGE"},
    {ARK_UNIFORM_DATA_TYPE_EXECUTABLE, "EXECUTABLE"},
    {ARK_UNIFORM_DATA_TYPE_PORTABLE_EXECUTABLE, "PORTABLE_EXECUTABLE"},
    {ARK_UNIFORM_DATA_TYPE_SUN_JAVA_CLASS, "SUN_JAVA_CLASS"},
    {ARK_UNIFORM_DATA_TYPE_VCARD, "VCARD"},
    {ARK_UNIFORM_DATA_TYPE_NAVIGATION, "NAVIGATION"},
    {ARK_UNIFORM_DATA_TYPE_LOCATION, "LOCATION"},
    {ARK_UNIFORM_DATA_TYPE_FONT, "FONT"},
    {ARK_UNIFORM_DATA_TYPE_TRUETYPE_FONT, "TRUETYPE_FONT"},
    {ARK_UNIFORM_DATA_TYPE_TRUETYPE_COLLECTION_FONT, "TRUETYPE_COLLECTION_FONT"},
    {ARK_UNIFORM_DATA_TYPE_OPENTYPE_FONT, "OPENTYPE_FONT"},
    {ARK_UNIFORM_DATA_TYPE_POSTSCRIPT_FONT, "POSTSCRIPT_FONT"},
    {ARK_UNIFORM_DATA_TYPE_POSTSCRIPT_PFB_FONT, "POSTSCRIPT_PFB_FONT"},
    {ARK_UNIFORM_DATA_TYPE_POSTSCRIPT_PFA_FONT, "POSTSCRIPT_PFA_FONT"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_FORM, "OPENHARMONY_FORM"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_APP_ITEM, "OPENHARMONY_APP_ITEM"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_PIXEL_MAP, "OPENHARMONY_PIXEL_MAP"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_ATOMIC_SERVICE, "OPENHARMONY_ATOMIC_SERVICE"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_PACKAGE, "OPENHARMONY_PACKAGE"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_HAP, "OPENHARMONY_HAP"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_HDOC, "OPENHARMONY_HDOC"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_HINOTE, "OPENHARMONY_HINOTE"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_STYLED_STRING, "OPENHARMONY_STYLED_STRING"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_WANT, "OPENHARMONY_WANT"},
    {ARK_UNIFORM_DATA_TYPE_OFD, "OFD"},
    {ARK_UNIFORM_DATA_TYPE_CAD, "CAD"},
    {ARK_UNIFORM_DATA_TYPE_OCTET_STREAM, "OCTET_STREAM"},
};

struct ClickEffect {
    Ark_ClickEffectLevel level;
    float scale;
};
void AssignArkValue(Ark_ClickEffect& dst, const ClickEffect& value)
{
    dst.level = value.level;
    dst.scale = Converter::ArkValue<Opt_Number>(value.scale);
}
struct MotionPathOptionTest {
    std::string path = "";
    std::optional<float> from = 0.0f;
    std::optional<float> to = 1.0f;
    std::optional<bool> rotatable = false;
};
void AssignArkValue(Ark_MotionPathOptions& dst, const MotionPathOptionTest& src)
{
    dst.path = Converter::ArkValue<Ark_String>(src.path);
    dst.from = Converter::ArkValue<Opt_Number>(src.from);
    dst.to = Converter::ArkValue<Opt_Number>(src.to);
    dst.rotatable = Converter::ArkValue<Opt_Boolean>(src.rotatable);
}
class CommonMethodModifierTest6 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;

    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }
};

//////////// Transform
/*
 * @tc.name: setTransformTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setTransformTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_TRANSFORM_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_TRANSFORM_DEFAULT_VALUE);
}

/*
 * @tc.name: setTransformTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setTransformTestValidValues, TestSize.Level1)
{
    LOGE("Custom objects are not supported.");
    ASSERT_NE(modifier_->setTransform0, nullptr);
    using OneTestStep = std::tuple<Ark_CustomObject, std::string>;
    double matrix1[4][4] = {{11, 12, 13, 14}, {21, 22, 23, 24}, {31, 32, 33, 34}, {41, 42, 43, 44}};
    double matrix2[4][4] = {{22, 24, 26, 28}, {42, 44, 46, 48}, {62, 64, 66, 68}, {82, 84, 86, 88}};
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_CustomObject>(matrix1),
            "{\"type\":\"matrix\",\"matrix\":\""
            "11.000000,21.000000,31.000000,41.000000,"
            "12.000000,22.000000,32.000000,42.000000,"
            "13.000000,23.000000,33.000000,43.000000,"
            "14.000000,24.000000,34.000000,44.000000,\"}"},
        {Converter::ArkValue<Ark_CustomObject>(matrix2),
            "{\"type\":\"matrix\",\"matrix\":\""
            "22.000000,42.000000,62.000000,82.000000,"
            "24.000000,44.000000,64.000000,84.000000,"
            "26.000000,46.000000,66.000000,86.000000,"
            "28.000000,48.000000,68.000000,88.000000,\"}"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setTransform0(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_TRANSFORM_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setTransformTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setTransformTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTransform0, nullptr);
    using OneTestStep = std::tuple<Ark_CustomObject, std::string>;
    Ark_CustomObject invalidValue1 = {};
    Ark_CustomObject invalidValue2 = {};
    Ark_CustomObject invalidValue3 = {};

    if (!StrToArrayChar(invalidValue2.kind, "invalidType")) {
        LOGE("Error copying string to invalidValue2.kind");
        return;
    }
    if (!StrToArrayChar(invalidValue3.kind, "Matrix4")) {
        LOGE("Error copying string to invalidValue3.kind");
        return;
    }
    static const std::vector<OneTestStep> testPlan = {
        {invalidValue1, ATTRIBUTE_TRANSFORM_DEFAULT_VALUE},
        {invalidValue2, ATTRIBUTE_TRANSFORM_DEFAULT_VALUE},
        {invalidValue3, ATTRIBUTE_TRANSFORM_DEFAULT_VALUE},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setTransform0(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_TRANSFORM_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}
//////////// ClickEffect
/*
 * @tc.name: setClickEffectTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setClickEffectTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_CLICK_EFFECT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_CLICK_EFFECT_DEFAULT_VALUE);
}

/*
 * @tc.name: setClickEffectTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setClickEffectTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setClickEffect0, nullptr);
    using OneTestStep = std::tuple<Opt_ClickEffect, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_ClickEffect>(ClickEffect({.level = ARK_CLICK_EFFECT_LEVEL_LIGHT, .scale = 0.5f})),
            "{\"level\":\"0\",\"scale\":\"0.500000\"}"},
        {Converter::ArkValue<Opt_ClickEffect>(ClickEffect({.level = ARK_CLICK_EFFECT_LEVEL_MIDDLE, .scale = 1.5f})),
            "{\"level\":\"1\",\"scale\":\"1.500000\"}"},
        {Converter::ArkValue<Opt_ClickEffect>(ClickEffect({.level = ARK_CLICK_EFFECT_LEVEL_HEAVY, .scale = 2.5f})),
            "{\"level\":\"2\",\"scale\":\"2.500000\"}"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setClickEffect0(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_CLICK_EFFECT_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setClickEffectTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setClickEffectTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setClickEffect0, nullptr);
    using OneTestStep = std::tuple<Opt_ClickEffect, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_ClickEffect>(), ""},
        {Converter::ArkValue<Opt_ClickEffect>(ClickEffect({.level = static_cast<Ark_ClickEffectLevel>(-1),
            .scale = 1.5f})),
            "{\"level\":\"0\",\"scale\":\"1.500000\"}"},
        {Converter::ArkValue<Opt_ClickEffect>(ClickEffect({.level = ARK_CLICK_EFFECT_LEVEL_HEAVY, .scale = -2.5f})),
            "{\"level\":\"2\",\"scale\":\"-2.500000\"}"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setClickEffect0(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_CLICK_EFFECT_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
    modifier_->setClickEffect0(node_, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_CLICK_EFFECT_NAME);
    auto expectedValue = "";
    EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
}

//////////// AllowDrop
/*
 * @tc.name: setAllowDropTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setAllowDropTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_TRUE((frameNode->GetAllowDrop()).empty()) << "Passed value -- empty set is true";
}

/*
 * @tc.name: setAllowDropTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setAllowDropTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAllowDrop, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> resultValue;
    Opt_Array_UniformDataType optArray;

    for (auto [inputValue, expectedValue]: ALLOW_DROP_TEST_PLAN) {
        optArray = Converter::ArkValue<Opt_Array_UniformDataType>(std::vector{inputValue}, Converter::FC);
        modifier_->setAllowDrop(node_, &optArray);
        resultValue = frameNode->GetAllowDrop();
        EXPECT_TRUE(resultValue.find(expectedValue) != resultValue.end()) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setAllowDropTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setAllowDropTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAllowDrop, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const std::string expectedValidValue = "PDF";
    
    // set valid value and check
    auto optArray = Converter::ArkValue<Opt_Array_UniformDataType>(
        std::vector{Ark_UniformDataType::ARK_UNIFORM_DATA_TYPE_PDF}, Converter::FC);
    modifier_->setAllowDrop(node_, &optArray);
    auto resultValue = frameNode->GetAllowDrop();
    EXPECT_TRUE(resultValue.find(expectedValidValue) != resultValue.end()) << "Passed value is: " << expectedValidValue;
    // set invalid value and check
    modifier_->setAllowDrop(node_, nullptr);
    resultValue = frameNode->GetAllowDrop();
    EXPECT_TRUE(resultValue.empty()) << "Passed value -- empty set is true";
}

//////////// Draggable
/*
 * @tc.name: setDraggableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setDraggableTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_DRAGGABLE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_DRAGGABLE_DEFAULT_VALUE);
}

/*
 * @tc.name: setDraggableTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setDraggableTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDraggable, nullptr);
    using OneTestStep = std::tuple<Ark_Boolean, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Boolean>(true), "true"},
        {Converter::ArkValue<Ark_Boolean>(false), "false"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setDraggable(node_, inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_DRAGGABLE_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

//////////// MotionPath
/*
 * @tc.name: setMotionPathTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setMotionPathTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_MOTION_PATH_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_MOTION_PATH_DEFAULT_VALUE);
}

/*
 * @tc.name: setMotionPathTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setMotionPathTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMotionPath, nullptr);
    using OneTestStep = std::tuple<Ark_MotionPathOptions, std::string>;
    MotionPathOptionTest defaultValue;
    MotionPathOptionTest validValue = {.path = "path", .from = 1.0f, .to = 2.0f, .rotatable = true};
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_MotionPathOptions>(defaultValue), ATTRIBUTE_MOTION_PATH_DEFAULT_VALUE},
        {Converter::ArkValue<Ark_MotionPathOptions>(validValue), ""},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setMotionPath(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_MOTION_PATH_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setMotionPathTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setMotionPathTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMotionPath, nullptr);
    using OneTestStep = std::tuple<Ark_MotionPathOptions, std::string>;
    MotionPathOptionTest invalidValue1 = {.path = "path", .from = 2.0f, .to = 1.0f, .rotatable = true};
    MotionPathOptionTest invalidValue2 = {.path = "path", .from = -2.0f, .to = -1.0f, .rotatable = true};
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_MotionPathOptions>(invalidValue1), ""},
        {Converter::ArkValue<Ark_MotionPathOptions>(invalidValue2), ""},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setMotionPath(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_MOTION_PATH_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

//////////// Key
/*
 * @tc.name: setKeyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setKeyTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_KEY_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_KEY_DEFAULT_VALUE);
}

/*
 * @tc.name: setKeyTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setKeyTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setKey, nullptr);
    using OneTestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_String>("1"), "1"},
        {Converter::ArkValue<Ark_String>("2"), "2"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setKey(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_KEY_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setKeyTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setKeyTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setKey, nullptr);
    using OneTestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_String>(""), ATTRIBUTE_KEY_DEFAULT_VALUE},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setKey(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_KEY_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}
// GENERATED_ArkUICommonMethodModifier
}
