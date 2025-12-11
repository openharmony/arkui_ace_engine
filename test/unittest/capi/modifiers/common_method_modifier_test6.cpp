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
    {ARK_UNIFORM_DATA_TYPE_ENTITY, "general.entity"},
    {ARK_UNIFORM_DATA_TYPE_OBJECT, "general.object"},
    {ARK_UNIFORM_DATA_TYPE_COMPOSITE_OBJECT, "general.composite-object"},
    {ARK_UNIFORM_DATA_TYPE_TEXT, "general.text"},
    {ARK_UNIFORM_DATA_TYPE_PLAIN_TEXT, "general.plain-text"},
    {ARK_UNIFORM_DATA_TYPE_HTML, "general.html"},
    {ARK_UNIFORM_DATA_TYPE_HYPERLINK, "general.hyperlink"},
    {ARK_UNIFORM_DATA_TYPE_XML, "general.xml"},
    {ARK_UNIFORM_DATA_TYPE_XHTML, "general.xhtml"},
    {ARK_UNIFORM_DATA_TYPE_RSS, "general.rss"},
    {ARK_UNIFORM_DATA_TYPE_SMIL, "com.real.smil"},
    {ARK_UNIFORM_DATA_TYPE_SOURCE_CODE, "general.source-code"},
    {ARK_UNIFORM_DATA_TYPE_SCRIPT, "general.script"},
    {ARK_UNIFORM_DATA_TYPE_SHELL_SCRIPT, "general.shell-script"},
    {ARK_UNIFORM_DATA_TYPE_CSH_SCRIPT, "general.csh-script"},
    {ARK_UNIFORM_DATA_TYPE_PERL_SCRIPT, "general.perl-script"},
    {ARK_UNIFORM_DATA_TYPE_PHP_SCRIPT, "general.php-script"},
    {ARK_UNIFORM_DATA_TYPE_PYTHON_SCRIPT, "general.python-script"},
    {ARK_UNIFORM_DATA_TYPE_RUBY_SCRIPT, "general.ruby-script"},
    {ARK_UNIFORM_DATA_TYPE_TYPE_SCRIPT, "general.type-script"},
    {ARK_UNIFORM_DATA_TYPE_JAVA_SCRIPT, "general.java-script"},
    {ARK_UNIFORM_DATA_TYPE_CSS, "general.css"},
    {ARK_UNIFORM_DATA_TYPE_C_HEADER, "general.c-header"},
    {ARK_UNIFORM_DATA_TYPE_C_SOURCE, "general.c-source"},
    {ARK_UNIFORM_DATA_TYPE_C_PLUS_PLUS_HEADER, "general.c-plus-plus-header"},
    {ARK_UNIFORM_DATA_TYPE_C_PLUS_PLUS_SOURCE, "general.c-plus-plus-source"},
    {ARK_UNIFORM_DATA_TYPE_JAVA_SOURCE, "general.java-source"},
    {ARK_UNIFORM_DATA_TYPE_TEX, "general.tex"},
    {ARK_UNIFORM_DATA_TYPE_MARKDOWN, "general.markdown"},
    {ARK_UNIFORM_DATA_TYPE_ASC_TEXT, "general.asc-text"},
    {ARK_UNIFORM_DATA_TYPE_RICH_TEXT, "general.rich-text"},
    {ARK_UNIFORM_DATA_TYPE_DELIMITED_VALUES_TEXT, "general.delimited-values-text"},
    {ARK_UNIFORM_DATA_TYPE_COMMA_SEPARATED_VALUES_TEXT, "general.comma-separated-values-text"},
    {ARK_UNIFORM_DATA_TYPE_TAB_SEPARATED_VALUES_TEXT, "general.tab-separated-values-text"},
    {ARK_UNIFORM_DATA_TYPE_EBOOK, "general.ebook"},
    {ARK_UNIFORM_DATA_TYPE_EPUB, "general.epub"},
    {ARK_UNIFORM_DATA_TYPE_AZW, "com.amazon.azw"},
    {ARK_UNIFORM_DATA_TYPE_AZW3, "com.amazon.azw3"},
    {ARK_UNIFORM_DATA_TYPE_KFX, "com.amazon.kfx"},
    {ARK_UNIFORM_DATA_TYPE_MOBI, "com.amazon.mobi"},
    {ARK_UNIFORM_DATA_TYPE_MEDIA, "general.media"},
    {ARK_UNIFORM_DATA_TYPE_IMAGE, "general.image"},
    {ARK_UNIFORM_DATA_TYPE_JPEG, "general.jpeg"},
    {ARK_UNIFORM_DATA_TYPE_PNG, "general.png"},
    {ARK_UNIFORM_DATA_TYPE_RAW_IMAGE, "general.raw-image"},
    {ARK_UNIFORM_DATA_TYPE_TIFF, "general.tiff"},
    {ARK_UNIFORM_DATA_TYPE_BMP, "com.microsoft.bmp"},
    {ARK_UNIFORM_DATA_TYPE_ICO, "com.microsoft.ico"},
    {ARK_UNIFORM_DATA_TYPE_PHOTOSHOP_IMAGE, "com.adobe.photoshop-image"},
    {ARK_UNIFORM_DATA_TYPE_AI_IMAGE, "com.adobe.illustrator.ai-image"},
    {ARK_UNIFORM_DATA_TYPE_FAX, "general.fax"},
    {ARK_UNIFORM_DATA_TYPE_JFX_FAX, "com.j2.jfx-fax"},
    {ARK_UNIFORM_DATA_TYPE_EFX_FAX, "com.js.efx-fax"},
    {ARK_UNIFORM_DATA_TYPE_XBITMAP_IMAGE, "general.xbitmap-image"},
    {ARK_UNIFORM_DATA_TYPE_GIF, "general.gif"},
    {ARK_UNIFORM_DATA_TYPE_TGA_IMAGE, "com.truevision.tga-image"},
    {ARK_UNIFORM_DATA_TYPE_SGI_IMAGE, "com.sgi.sgi-image"},
    {ARK_UNIFORM_DATA_TYPE_OPENEXR_IMAGE, "com.ilm.openexr-image"},
    {ARK_UNIFORM_DATA_TYPE_FLASHPIX_IMAGE, "com.kodak.flashpix.image"},
    {ARK_UNIFORM_DATA_TYPE_WORD_DOC, "com.microsoft.word.doc"},
    {ARK_UNIFORM_DATA_TYPE_EXCEL, "com.microsoft.excel.xls"},
    {ARK_UNIFORM_DATA_TYPE_PPT, "com.microsoft.powerpoint.ppt"},
    {ARK_UNIFORM_DATA_TYPE_WORD_DOT, "com.microsoft.word.dot"},
    {ARK_UNIFORM_DATA_TYPE_POWERPOINT_PPS, "com.microsoft.powerpoint.pps"},
    {ARK_UNIFORM_DATA_TYPE_EXCEL_XLT, "com.microsoft.excel.xlt"},
    {ARK_UNIFORM_DATA_TYPE_POWERPOINT_POT, "com.microsoft.powerpoint.pot"},
    {ARK_UNIFORM_DATA_TYPE_VISIO_VSD, "com.microsoft.visio.vsd"},
    {ARK_UNIFORM_DATA_TYPE_PDF, "com.adobe.pdf"},
    {ARK_UNIFORM_DATA_TYPE_POSTSCRIPT, "com.adobe.postscript"},
    {ARK_UNIFORM_DATA_TYPE_ENCAPSULATED_POSTSCRIPT, "com.adobe.encapsulated-postscript"},
    {ARK_UNIFORM_DATA_TYPE_VIDEO, "general.video"},
    {ARK_UNIFORM_DATA_TYPE_AVI, "general.avi"},
    {ARK_UNIFORM_DATA_TYPE_MPEG, "general.mpeg"},
    {ARK_UNIFORM_DATA_TYPE_MPEG4, "general.mpeg-4"},
    {ARK_UNIFORM_DATA_TYPE_VIDEO_3GPP, "general.3gpp"},
    {ARK_UNIFORM_DATA_TYPE_VIDEO_3GPP2, "general.3gpp2"},
    {ARK_UNIFORM_DATA_TYPE_TS, "general.ts"},
    {ARK_UNIFORM_DATA_TYPE_MPEGURL_VIDEO, "general.mpegurl-video"},
    {ARK_UNIFORM_DATA_TYPE_WINDOWS_MEDIA_WM, "com.microsoft.windows-media-wm"},
    {ARK_UNIFORM_DATA_TYPE_WINDOWS_MEDIA_WMV, "com.microsoft.windows-media-wmv"},
    {ARK_UNIFORM_DATA_TYPE_WINDOWS_MEDIA_WMP, "com.microsoft.windows-media-wmp"},
    {ARK_UNIFORM_DATA_TYPE_WINDOWS_MEDIA_WVX, "com.microsoft.windows-media-wvx"},
    {ARK_UNIFORM_DATA_TYPE_WINDOWS_MEDIA_WMX, "com.microsoft.windows-media-wmx"},
    {ARK_UNIFORM_DATA_TYPE_REALMEDIA, "com.real.realmedia"},
    {ARK_UNIFORM_DATA_TYPE_MATROSKA_VIDEO, "org.matroska.mkv"},
    {ARK_UNIFORM_DATA_TYPE_FLASH, "com.adobe.flash"},
    {ARK_UNIFORM_DATA_TYPE_AUDIO, "general.audio"},
    {ARK_UNIFORM_DATA_TYPE_AAC, "general.aac"},
    {ARK_UNIFORM_DATA_TYPE_AIFF, "general.aiff"},
    {ARK_UNIFORM_DATA_TYPE_ALAC, "general.alac"},
    {ARK_UNIFORM_DATA_TYPE_FLAC, "general.flac"},
    {ARK_UNIFORM_DATA_TYPE_MP3, "general.mp3"},
    {ARK_UNIFORM_DATA_TYPE_OGG, "general.ogg"},
    {ARK_UNIFORM_DATA_TYPE_PCM, "general.pcm"},
    {ARK_UNIFORM_DATA_TYPE_WINDOWS_MEDIA_WMA, "com.microsoft.windows-media-wma"},
    {ARK_UNIFORM_DATA_TYPE_WAVEFORM_AUDIO, "com.microsoft.waveform-audio"},
    {ARK_UNIFORM_DATA_TYPE_WINDOWS_MEDIA_WAX, "com.microsoft.windows-media-wax"},
    {ARK_UNIFORM_DATA_TYPE_AU_AUDIO, "general.au-audio"},
    {ARK_UNIFORM_DATA_TYPE_AIFC_AUDIO, "general.aifc-audio"},
    {ARK_UNIFORM_DATA_TYPE_MPEGURL_AUDIO, "general.mpegurl-audio"},
    {ARK_UNIFORM_DATA_TYPE_MPEG_4_AUDIO, "general.mpeg-4-audio"},
    {ARK_UNIFORM_DATA_TYPE_MP2, "general.mp2"},
    {ARK_UNIFORM_DATA_TYPE_MPEG_AUDIO, "general.mpeg-audio"},
    {ARK_UNIFORM_DATA_TYPE_ULAW_AUDIO, "general.ulaw-audio"},
    {ARK_UNIFORM_DATA_TYPE_SD2_AUDIO, "com.digidesign.sd2-audio"},
    {ARK_UNIFORM_DATA_TYPE_REALAUDIO, "com.real.realaudio"},
    {ARK_UNIFORM_DATA_TYPE_MATROSKA_AUDIO, "org.matroska.mka"},
    {ARK_UNIFORM_DATA_TYPE_FILE, "general.file"},
    {ARK_UNIFORM_DATA_TYPE_DIRECTORY, "general.directory"},
    {ARK_UNIFORM_DATA_TYPE_FOLDER, "general.folder"},
    {ARK_UNIFORM_DATA_TYPE_SYMLINK, "general.symlink"},
    {ARK_UNIFORM_DATA_TYPE_ARCHIVE, "general.archive"},
    {ARK_UNIFORM_DATA_TYPE_BZ2_ARCHIVE, "general.bz2-archive"},
    {ARK_UNIFORM_DATA_TYPE_OPG, "general.opg"},
    {ARK_UNIFORM_DATA_TYPE_TAZ_ARCHIVE, "general.taz-archive"},
    {ARK_UNIFORM_DATA_TYPE_WEB_ARCHIVE, "general.web-archive"},
    {ARK_UNIFORM_DATA_TYPE_DISK_IMAGE, "general.disk-image"},
    {ARK_UNIFORM_DATA_TYPE_ISO, "general.iso"},
    {ARK_UNIFORM_DATA_TYPE_TAR_ARCHIVE, "general.tar-archive"},
    {ARK_UNIFORM_DATA_TYPE_ZIP_ARCHIVE, "general.zip-archive"},
    {ARK_UNIFORM_DATA_TYPE_JAVA_ARCHIVE, "com.sun.java-archive"},
    {ARK_UNIFORM_DATA_TYPE_GNU_TAR_ARCHIVE, "org.gnu.gnu-tar-archive"},
    {ARK_UNIFORM_DATA_TYPE_GNU_ZIP_ARCHIVE, "org.gnu.gnu-zip-archive"},
    {ARK_UNIFORM_DATA_TYPE_GNU_ZIP_TAR_ARCHIVE, "org.gnu.gnu-zip-tar-archive"},
    {ARK_UNIFORM_DATA_TYPE_OPENXML, "org.openxmlformats.openxml"},
    {ARK_UNIFORM_DATA_TYPE_WORDPROCESSINGML_DOCUMENT, "org.openxmlformats.wordprocessingml.document"},
    {ARK_UNIFORM_DATA_TYPE_SPREADSHEETML_SHEET, "org.openxmlformats.spreadsheetml.sheet"},
    {ARK_UNIFORM_DATA_TYPE_PRESENTATIONML_PRESENTATION, "org.openxmlformats.presentationml.presentation"},
    {ARK_UNIFORM_DATA_TYPE_DRAWINGML_VISIO, "org.openxmlformats.drawingml.visio"},
    {ARK_UNIFORM_DATA_TYPE_DRAWINGML_TEMPLATE, "org.openxmlformats.drawingml.template"},
    {ARK_UNIFORM_DATA_TYPE_WORDPROCESSINGML_TEMPLATE, "org.openxmlformats.wordprocessingml.template"},
    {ARK_UNIFORM_DATA_TYPE_PRESENTATIONML_TEMPLATE, "org.openxmlformats.presentationml.template"},
    {ARK_UNIFORM_DATA_TYPE_PRESENTATIONML_SLIDESHOW, "org.openxmlformats.presentationml.slideshow"},
    {ARK_UNIFORM_DATA_TYPE_SPREADSHEETML_TEMPLATE, "org.openxmlformats.spreadsheetml.template"},
    {ARK_UNIFORM_DATA_TYPE_OPENDOCUMENT, "org.oasis.opendocument"},
    {ARK_UNIFORM_DATA_TYPE_OPENDOCUMENT_TEXT, "org.oasis.opendocument.text"},
    {ARK_UNIFORM_DATA_TYPE_OPENDOCUMENT_SPREADSHEET, "org.oasis.opendocument.spreadsheet"},
    {ARK_UNIFORM_DATA_TYPE_OPENDOCUMENT_PRESENTATION, "org.oasis.opendocument.presentation"},
    {ARK_UNIFORM_DATA_TYPE_OPENDOCUMENT_GRAPHICS, "org.oasis.opendocument.graphics"},
    {ARK_UNIFORM_DATA_TYPE_OPENDOCUMENT_FORMULA, "org.oasis.opendocument.formula"},
    {ARK_UNIFORM_DATA_TYPE_STUFFIT_ARCHIVE, "com.allume.stuffit-archive"},
    {ARK_UNIFORM_DATA_TYPE_RAR_ARCHIVE, "com.rarlab.rar-archive"},
    {ARK_UNIFORM_DATA_TYPE_SEVEN_ZIP_ARCHIVE, "org.7-zip.7-zip-archive"},
    {ARK_UNIFORM_DATA_TYPE_CALENDAR, "general.calendar"},
    {ARK_UNIFORM_DATA_TYPE_VCS, "general.vcs"},
    {ARK_UNIFORM_DATA_TYPE_ICS, "general.ics"},
    {ARK_UNIFORM_DATA_TYPE_CONTACT, "general.contact"},
    {ARK_UNIFORM_DATA_TYPE_DATABASE, "general.database"},
    {ARK_UNIFORM_DATA_TYPE_MESSAGE, "general.message"},
    {ARK_UNIFORM_DATA_TYPE_EXECUTABLE, "general.executable"},
    {ARK_UNIFORM_DATA_TYPE_PORTABLE_EXECUTABLE, "com.microsoft.portable-executable"},
    {ARK_UNIFORM_DATA_TYPE_SUN_JAVA_CLASS, "com.sun.java-class"},
    {ARK_UNIFORM_DATA_TYPE_VCARD, "general.vcard"},
    {ARK_UNIFORM_DATA_TYPE_NAVIGATION, "general.navigation"},
    {ARK_UNIFORM_DATA_TYPE_LOCATION, "general.location"},
    {ARK_UNIFORM_DATA_TYPE_FONT, "general.font"},
    {ARK_UNIFORM_DATA_TYPE_TRUETYPE_FONT, "general.truetype-font"},
    {ARK_UNIFORM_DATA_TYPE_TRUETYPE_COLLECTION_FONT, "general.truetype-collection-font"},
    {ARK_UNIFORM_DATA_TYPE_OPENTYPE_FONT, "general.opentype-font"},
    {ARK_UNIFORM_DATA_TYPE_POSTSCRIPT_FONT, "com.adobe.postscript-font"},
    {ARK_UNIFORM_DATA_TYPE_POSTSCRIPT_PFB_FONT, "com.adobe.postscript-pfb-font"},
    {ARK_UNIFORM_DATA_TYPE_POSTSCRIPT_PFA_FONT, "com.adobe.postscript-pfa-font"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_FORM, "openharmony.form"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_APP_ITEM, "openharmony.app-item"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_PIXEL_MAP, "openharmony.pixel-map"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_ATOMIC_SERVICE, "openharmony.atomic-service"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_PACKAGE, "openharmony.package"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_HAP, "openharmony.hap"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_HDOC, "openharmony.hdoc"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_HINOTE, "openharmony.hinote"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_STYLED_STRING, "openharmony.styled-string"},
    {ARK_UNIFORM_DATA_TYPE_OPENHARMONY_WANT, "openharmony.want"},
    {ARK_UNIFORM_DATA_TYPE_OFD, "general.ofd"},
    {ARK_UNIFORM_DATA_TYPE_CAD, "general.cad"},
    {ARK_UNIFORM_DATA_TYPE_OCTET_STREAM, "general.octet-stream"},
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
    FAIL() << "Test is not implemented yet";
}

/*
 * @tc.name: setTransformTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setTransformTestInvalidValues2, TestSize.Level1)
{
    FAIL() << "Test is not implemented yet";
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
HWTEST_F(CommonMethodModifierTest6, DISABLED_setClickEffectTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setClickEffect0, nullptr);
    using OneTestStep = std::tuple<Opt_ClickEffect, std::string>;
    const std::vector<OneTestStep> testPlan = {
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
HWTEST_F(CommonMethodModifierTest6, DISABLED_setClickEffectTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setClickEffect0, nullptr);
    using OneTestStep = std::tuple<Opt_ClickEffect, std::string>;
    const std::vector<OneTestStep> testPlan = {
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
HWTEST_F(CommonMethodModifierTest6, DISABLED_setAllowDropTestValidValues, TestSize.Level1)
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
HWTEST_F(CommonMethodModifierTest6, DISABLED_setAllowDropTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAllowDrop, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const std::string expectedValidValue = "com.adobe.pdf";
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
    using OneTestStep = std::tuple<Opt_Boolean, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Boolean>(true), "true"},
        {Converter::ArkValue<Opt_Boolean>(false), "false"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setDraggable(node_, &inputValue);
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
    using OneTestStep = std::tuple<Opt_MotionPathOptions, std::string>;
    MotionPathOptionTest defaultValue;
    MotionPathOptionTest validValue = {.path = "path", .from = 1.0f, .to = 2.0f, .rotatable = true};
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_MotionPathOptions>(defaultValue), ATTRIBUTE_MOTION_PATH_DEFAULT_VALUE},
        {Converter::ArkValue<Opt_MotionPathOptions>(validValue), ""},
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
    using OneTestStep = std::tuple<Opt_MotionPathOptions, std::string>;
    MotionPathOptionTest invalidValue1 = {.path = "path", .from = 2.0f, .to = 1.0f, .rotatable = true};
    MotionPathOptionTest invalidValue2 = {.path = "path", .from = -2.0f, .to = -1.0f, .rotatable = true};
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_MotionPathOptions>(invalidValue1), ""},
        {Converter::ArkValue<Opt_MotionPathOptions>(invalidValue2), ""},
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
HWTEST_F(CommonMethodModifierTest6, DISABLED_setKeyTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setKey, nullptr);
    using OneTestStep = std::tuple<Opt_String, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_String>("1"), "1"},
        {Converter::ArkValue<Opt_String>("2"), "2"},
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
    using OneTestStep = std::tuple<Opt_String, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_String>(""), ATTRIBUTE_KEY_DEFAULT_VALUE},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setKey(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        ASSERT_NE(fullJson, nullptr);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_KEY_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}
// GENERATED_ArkUICommonMethodModifier
}
