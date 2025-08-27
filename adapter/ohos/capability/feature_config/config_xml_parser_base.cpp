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

#include "adapter/ohos/capability/feature_config/config_xml_parser_base.h"

#include <array>

#include "adapter/ohos/capability/feature_config/feature_param_manager.h"
#include "base/log/log.h"

namespace OHOS::Ace {

enum ParseXmlNodeIndex : uint32_t {
    PARSE_XML_UNDEFINED = 0,
    PARSE_XML_PERFORMANCE_OPT_CONFIG,
    PARSE_XML_BUNDLE_NAME,
    PARSE_XML_FEATURE,
    PARSE_XML_MAX_SIZE,
};

namespace {
static const std::array<std::string, PARSE_XML_MAX_SIZE> XML_NODE_NAME_ARRAY = {
    "undefine",             // PARSE_XML_UNDEFINED
    "PerformanceOptConfig", // PARSE_XML_PERFORMANCE_OPT_CONFIG
    "bundleName",           // PARSE_XML_BUNDLE_NAME
    "feature",              // PARSE_XML_FEATURE
};

static const std::array<std::string, 1> SYS_PATH = { "/etc" };
static constexpr char CONFIG_PATH[] = "/arkui/arkui_async_build_config.xml";
} // namespace

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
    for (const std::string& configRootPath : SYS_PATH) {
        std::string graphicFilePath = configRootPath + CONFIG_PATH;
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
        LOGE("ConfigXMLParserBase xmlSysDocument is empty, LoadGraphicConfiguration first");
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

ParseErrCode ConfigXMLParserBase::ParseInternalWithBundleName(xmlNode& node, const std::string& bundleName)
{
    // skip root node
    xmlNode* currNode = node.children;
    if (currNode == nullptr) {
        return PARSE_GET_CHILD_FAIL;
    }

    // find first PerformanceOptConfig node
    auto ret = PARSE_EXEC_SUCCESS;
    for (; currNode; currNode = currNode->next) {
        ret = ParseXmlNodeNameWithIndex(*currNode, PARSE_XML_PERFORMANCE_OPT_CONFIG);
        if (ret == PARSE_EXEC_SUCCESS) {
            break;
        }
    }
    if (currNode == nullptr) {
        return PARSE_XML_NAME_ERROR;
    }

    currNode = currNode->children;
    if (currNode == nullptr) {
        return PARSE_GET_CHILD_FAIL;
    }

    // find parse feature nodes
    for (; currNode; currNode = currNode->next) {
        if (ParseXmlNodeNameWithIndex(*currNode, PARSE_XML_BUNDLE_NAME) != PARSE_EXEC_SUCCESS) {
            continue;
        }

        std::string xmlBundleName = ExtractPropertyValue("name", *currNode);
        if (xmlBundleName == bundleName && currNode->children) {
            ParseFeatures(*(currNode->children));
            break;
        }
    }
    return ret;
}

void ConfigXMLParserBase::ParseFeatures(xmlNode& node)
{
    auto& featureMap = FeatureParamManager::GetInstance().featureParamMap_;

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
    if (nodeNameIndex >= XML_NODE_NAME_ARRAY.size()) {
        return PARSE_SIZE_ERROR;
    }

    if (xmlStrcasecmp(node.name, reinterpret_cast<const xmlChar*>(XML_NODE_NAME_ARRAY[nodeNameIndex].c_str())) != 0) {
        return PARSE_XML_NAME_ERROR;
    }

    return PARSE_EXEC_SUCCESS;
}
} // namespace OHOS::Ace
