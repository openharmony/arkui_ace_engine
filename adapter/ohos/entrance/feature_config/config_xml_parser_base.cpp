/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "config_xml_parser_base.h"

#include "arkui_feature_param_manager.h"
#include "interfaces/inner_api/ace/arkui_log.h"

namespace OHOS::Ace {

enum ParseXmlNodeIndex : uint32_t {
    PARSE_XML_UNDEFINED = 0,
    PARSE_XML_PERFORMANCE_OPT_CONFIG,
    PARSE_XML_BUNDLE_NAME,
    PARSE_XML_FEATURE,
};

std::vector<std::string> ConfigXMLParserBase::xmlNodeNameVec_ = {
    "undefine",             // PARSE_XML_UNDEFINED
    "PerformanceOptConfig", // PARSE_XML_PERFORMANCE_OPT_CONFIG
    "bundleName",           // PARSE_XML_BUNDLE_NAME
    "feature",              // PARSE_XML_FEATURE
};

std::vector<std::string> ConfigXMLParserBase::sysPaths_ = { "/system/variant/phone/base/",
    "/system/variant/tablet/base/", "/system/variant/pc/base/", "/system/variant/watch/base/",
    "/system/variant/tv/base/", "/system/variant/car/base/", "/system/variant/smarthomehost/base/" };

std::string ConfigXMLParserBase::configPath_ = "etc/arkui/arkui_performance_config.xml";

ConfigXMLParserBase::~ConfigXMLParserBase()
{
    Destroy();
}

void ConfigXMLParserBase::Destroy()
{
    if (xmlSysDocument_ != nullptr) {
        xmlFreeDoc(xmlSysDocument_);
        xmlSysDocument_ = nullptr;
    }
}

ParseErrCode ConfigXMLParserBase::LoadPerformanceConfigXML()
{
    for (const std::string& configRootPath : sysPaths_) {
        std::string graphicFilePath = configRootPath + configPath_;
        xmlSysDocument_ = xmlReadFile(graphicFilePath.c_str(), nullptr, 0);
        if (xmlSysDocument_ != nullptr) {
            LOGD("ConfigXMLParserBase success to get sys graphic config: %{public}s", graphicFilePath.c_str());
            break;
        }
    }
    if (!xmlSysDocument_) {
        LOGE("ConfigXMLParserBase read system file failed");
        return PARSE_SYS_FILE_LOAD_FAIL;
    }
    return PARSE_EXEC_SUCCESS;
}

ParseErrCode ConfigXMLParserBase::ParsePerformanceConfigXMLWithBundleName(const std::string& bundleName)
{
    if (!xmlSysDocument_) {
        LOGE("ConfigXMLParserBase xmlSysDocument_ is empty, should do LoadGraphicConfiguration first");
        return PARSE_SYS_FILE_LOAD_FAIL;
    }
    xmlNode* root = xmlDocGetRootElement(xmlSysDocument_);
    if (root == nullptr) {
        LOGE("ConfigXMLParserBase xmlDocGetRootElement failed");
        return PARSE_GET_ROOT_FAIL;
    }

    auto ret = ParseInternalWithBundleName(*root, bundleName);
    if (ret != PARSE_EXEC_SUCCESS) {
        LOGE("ConfigXMLParserBase ParseInternalWithBundleName failed");
    }
    return ret;
}

/*
<PerformanceOptConfig>
    <bundleName name="com.test.hap">
        <feature id="UINodeGcParamParser" enable="true"/>
        <feature id="SyncloadParser" enable="true" value="50"/>
    </bundleName>
    <bundleName name="com.huawei.hmos.photos">
        <feature id="UINodeGcParamParser" enable="true"/>
        <feature id="SyncloadParser" enable="true" value="20"/>
    </bundleName>
</PerformanceOptConfig>
*/

ParseErrCode ConfigXMLParserBase::ParseInternalWithBundleName(xmlNode& node, const std::string& bundleName)
{
    xmlNode* currNode = &node;
    auto ret = ParseXmlNodeNameWithIndex(*currNode, PARSE_XML_PERFORMANCE_OPT_CONFIG);
    if (ret != PARSE_EXEC_SUCCESS) {
        return ret;
    }

    currNode = currNode->children;
    if (currNode == nullptr) {
        return PARSE_GET_CHILD_FAIL;
    }

    for (; currNode; currNode = currNode->next) {
        if (ParseXmlNodeNameWithIndex(*currNode, PARSE_XML_BUNDLE_NAME) != PARSE_EXEC_SUCCESS) {
            continue;
        }

        std::string xmlBundleName = ExtractPropertyValue("name", *currNode);
        LOGI("ConfigXMLParserBase ParseInternalWithBundleName xmlBundleName %{public}s bundleName %{public}s",
            xmlBundleName.c_str(), bundleName.c_str());
        if (xmlBundleName == bundleName) {
            ParseFeatures(*(currNode->children));
            break;
        }
    }
    return ret;
}

void ConfigXMLParserBase::ParseFeatures(xmlNode& node)
{
    auto& featureMap = ArkUIFeatureParamManager::GetInstance().featureParamMap_;

    // travel features
    xmlNode* currNode = &node;
    for (; currNode; currNode = currNode->next) {
        if (ParseXmlNodeNameWithIndex(*currNode, PARSE_XML_FEATURE) != PARSE_EXEC_SUCCESS) {
            continue;
        }

        std::string featureName = ExtractPropertyValue("id", *currNode);
        auto it = featureMap.find(featureName);
        if (it != featureMap.end()) {
            it->second->ParseFeatureParam(*currNode);
        }
    }
}

std::string ConfigXMLParserBase::ExtractPropertyValue(const std::string& propName, xmlNode& node)
{
    LOGD("ConfigXMLParserBase extracting value : %{public}s", propName.c_str());
    std::string propValue = "";
    xmlChar* tempValue = nullptr;

    if (xmlHasProp(&node, reinterpret_cast<const xmlChar*>(propName.c_str()))) {
        tempValue = xmlGetProp(&node, reinterpret_cast<const xmlChar*>(propName.c_str()));
    }

    if (tempValue != nullptr) {
        LOGD("ConfigXMLParserBase not a empty tempValue");
        propValue = reinterpret_cast<const char*>(tempValue);
        xmlFree(tempValue);
        tempValue = nullptr;
    }

    return propValue;
}

ParseErrCode ConfigXMLParserBase::ParseXmlNodeNameWithIndex(xmlNode& node, uint32_t nodeNameIndex)
{
    if (nodeNameIndex >= xmlNodeNameVec_.size()) {
        return PARSE_SIZE_ERROR;
    }

    if (xmlStrcasecmp(node.name, reinterpret_cast<const xmlChar*>(xmlNodeNameVec_[nodeNameIndex].c_str())) != 0) {
        return PARSE_XML_NAME_ERROR;
    }

    return PARSE_EXEC_SUCCESS;
}
} // namespace OHOS::Ace
